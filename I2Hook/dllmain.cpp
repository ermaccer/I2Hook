// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "gui/dx11hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "plugin/Menu.h"
#include "plugin/Settings.h"
#include "plugin/Hooks.h"
#include "plugin/PatternSolver.h"
#include "plugin/PluginInterface.h"

#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"

#include "mk/GameInfo.h"
#include "mk/Scaleform.h"
#include "mk/MKModifier.h"

#include "helper/eGamepadManager.h"

#include <iostream>
#include <Commctrl.h>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")

using namespace Memory::VP;

int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }

int64 pat_frameSkip = 0;

bool SetFrameskip_Hook()
{
	Patch<int>(pat_frameSkip, 0);
	return 0;
}

int64 SetFrameSkip_GetPattern()
{
	int64 pat = PatternSolver::GetPattern("E8 ? ? ? ? 85 C0 74 0C BA ? ? ? ? 33 C9 E8", 1);
	if (pat)
	{
		int64 pat2 = PatternSolver::GetPattern("8B 1D ? ? ? ? 8B FB 81 E7 ? ? ? ? 33 C0 44 8B C0 85 DB 41 0F 95 C0", 2);
		if (!pat2)
			return 0;

		unsigned int offset = *(unsigned int*)(pat);
		unsigned int offset2 = *(unsigned int*)(pat2);
		pat_frameSkip = (pat2 + offset2 + 4);

		return (pat + offset + 4);
	}
	return 0;
}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	eLog::Message(__FUNCTION__, "INFO: I2Hook (%s | %s) Begin!", I2HOOK_VERSION, __DATE__);

	Notifications->Init();
	FGGameInfo::FindGameInfo();
	Scaleform::FindData();

	if (SettingsMgr->bEnableGamepadSupport)
		eGamepadManager::Initialize();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));

	if (SettingsMgr->bEnable60FPSFrontend)
	{
		if (int64 fs_pat = SetFrameSkip_GetPattern())
			InjectHook(fs_pat, tramp->Jump(SetFrameskip_Hook), HookType::Jump);
	}

	if (SettingsMgr->bDisableTOCChecks)
		InjectHook(_pattern(PATID_TocCheck), tramp->Jump(GenericTrueReturn), HookType::Jump);

	InjectHook(_pattern(PATID_MKProcDispatch_Hook), tramp->Jump(MKProcDispatch_Hook));
	InjectHook(_pattern(PATID_RecordEvent_Hook), tramp->Jump(RecordEvent_Hook));

	Nop(_pattern(PATID_CameraPositionNOP), 7);
	Nop(_pattern(PATID_CameraRotationNOP), 8);

	InjectHook(_pattern(PATID_CameraPositionHook), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_pattern(PATID_CameraRotationHook), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_pattern(PATID_Dispatch_Hook), tramp->Jump(Dispatch_Hook));

	ReadCall(_pattern(PATID_ProcessDOFSettings), pProcessDOFSettings);
	InjectHook(_pattern(PATID_ProcessDOFSettings), tramp->Jump(ProcessDOFSettings));

	ReadCall(_pattern(PATID_PlayerInfo_GetDrone), pPlayerInfo_GetDrone);
	ReadCall(_pattern(PATID_PlayerInfo_MakeDrone), pPlayerInfo_MakeDrone);

	InjectHook(_pattern(PATID_FightStartupAddModifiers), tramp->Jump(PluginFightStartupAddModifiers));

	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
	{
		// only hook if xinputgetstate was loaded
		if (eGamepadManager::hXInputDLL && eGamepadManager::pXInputGetStateFunc)
		{
			uintptr_t xinput_addr = _pattern(PATID_XInputGetState_Hook);
			xinput_addr += *(unsigned int*)(xinput_addr)+4;

			InjectHook(xinput_addr, tramp->Jump(XInputGetState_Hook), HookType::Jump);
		}

	}


	HANDLE h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX11Hook_Thread), 0, NULL, 0);

	if (!(h == nullptr)) CloseHandle(h);
}



bool ValidateGameVersion()
{
	PatternSolver::Initialize();

	if (PatternSolver::CheckMissingPatterns())
	{
		int nButtonPressed = 0;
		TASKDIALOGCONFIG config;
		ZeroMemory(&config, sizeof(TASKDIALOGCONFIG));

		const TASKDIALOG_BUTTON buttons[] = {
			{ IDOK, L"Launch anyway\nThe game might crash or have missing features!" },
			{ IDNO, L"Exit" }
		};
		config.cbSize = sizeof(config);

		config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_CAN_BE_MINIMIZED | TDF_USE_COMMAND_LINKS;
		config.pszMainIcon = TD_WARNING_ICON;

		config.pszWindowTitle = L"Warning";
		config.pszMainInstruction = L"I2Hook";
		config.pszContent = L"Could not start I2Hook!\n\n"
			L"One or more code patterns could not be found, this might indicate"
			L" that game version is not supported or the plugin has not been updated.\n\n"
			L"I2Hook officially is only tested with latest Steam version.\n"
			L"Check log for more details.\n";


		config.pButtons = buttons;
		config.cButtons = ARRAYSIZE(buttons);

		if (SUCCEEDED(TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)))
		{
			switch (nButtonPressed)
			{
			case IDOK:
				return true;
				break;
			case IDNO:
				exit(0);
				break;
			default:
				break;
			}
		}

	}

	return true;

}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
#ifdef _60_ONLY
		Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));

		if (int64 fs_pat = SetFrameSkip_GetPattern())
			InjectHook(fs_pat, tramp->Jump(SetFrameskip_Hook), PATCH_JUMP);
		else
			MessageBoxA(0, "Could not find required patterns!", "I2Hook_60only", MB_ICONERROR);
#else
		eLog::Initialize();

		if (ValidateGameVersion())
		{
			OnInitializeHook();
		}
#endif
	}

}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
#ifndef _60_ONLY
		eGamepadManager::Shutdown();
		GUIImplementation::Shutdown();
		PluginInterface::UnloadPlugins();
#endif
		break;
	}
	return TRUE;
}
