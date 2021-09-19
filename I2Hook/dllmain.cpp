//i2 hook
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10utils.h"
#include "code/dcf2menu.h"
#include <iostream>
#include "includes.h"
#include "code/dcf2.h"
#include "code/eSettingsManager.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"

#include "eDirectX11Hook.h"

using namespace Memory::VP;
using namespace hook;


int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}


bool __fastcall SetFlagNull()
{
	Patch<int>(_addr(0x1445404EC), 0);
	return 0;

}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}

	printf("I2Hook::OnInitializeHook() | Begin!\n");
	TheMenu->Initialize();
	Notifications->Init();
	printf("I2Hook::OnInitializeHook() | Game detected: %s\n", (char*)_addr(0x1434B1FC0));
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));


	if (SettingsMgr->bEnable60FPSFrontend)
		InjectHook(_addr(0x14A449B00), tramp->Jump(SetFlagNull), PATCH_JUMP);


	InjectHook(_addr(0x14646DBFF), tramp->Jump(DCF2Hooks::HookProcessStuff));
	InjectHook(_addr(0x145EFF3EE), tramp->Jump(DCF2Hooks::HookStartupFightRecording));

	Nop(_addr(0x14AE26B63), 7);
	Nop(_addr(0x14AE26B73), 8);
	InjectHook(_addr(0x14AE26B81), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x14AE26B8E), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_addr(0x14B294260), tramp->Jump(DCF2Hooks::HookReadPropertyValue), PATCH_JUMP);
	InjectHook(_addr(0x1419C37E8), tramp->Jump(DCF2Hooks::HookSetProperty));

	InjectHook(_addr(0x14ACA7225), tramp->Jump(DCF2Hooks::HookDispatch));
}



bool ValidateGameVersion()
{
	char* gameName = (char*)_addr(0x1434B1FC0);

	if (strncmp(gameName, "Injustice", strlen("Injustice")) == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nI2Hook only supports latest (or it needs to be updated) Steam executable.", 0, MB_ICONINFORMATION);
		return false;
	}
}




BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (ValidateGameVersion())
		{
			SettingsMgr->Init();

			if (SettingsMgr->b60FPSModeOnly)
			{
				Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
				InjectHook(_addr(0x14A449B00), tramp->Jump(SetFlagNull), PATCH_JUMP);
			}
			else
			{
				eDirectX11Hook::Init();
				DisableThreadLibraryCalls(hMod);
				CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);
				OnInitializeHook();
			}
		}



		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}