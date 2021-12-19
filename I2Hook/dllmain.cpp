//i2 hook
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "code/mk10utils.h"
#include "code/dcf2menu.h"
#include <iostream>
#include "includes.h"
#include "code/dcf2.h"
#include "code/eSettingsManager.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"
#include "code/dcf2menu.h"
#include "code/eGamepadManager.h"
#include "eDirectX11Hook.h"


using namespace Memory::VP;

int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}


bool __fastcall SetFlagNull()
{
	Patch<int>(_addr(0x1445404BC), 0);
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
	printf("I2Hook::OnInitializeHook() | Game detected: %s\n", (char*)_addr(0x1434B1F90));
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));


	if (SettingsMgr->bEnable60FPSFrontend)
		InjectHook(_addr(0x141BCF2F0), tramp->Jump(SetFlagNull), PATCH_JUMP);

	InjectHook(_addr(0x140559A88), tramp->Jump(Hooks::HookProcessStuff));
	InjectHook(_addr(0x1403D8E0E), tramp->Jump(Hooks::HookStartupFightRecording));

	Nop(_addr(0x14206A373), 7);
	Nop(_addr(0x14206A383), 8);
	InjectHook(_addr(0x14206A391), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x14206A39E), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_addr(0x142218B00), tramp->Jump(Hooks::HookReadPropertyValue), PATCH_JUMP);
	InjectHook(_addr(0x1419C373F), tramp->Jump(Hooks::HookSetProperty));

	InjectHook(_addr(0x141FD85E0), tramp->Jump(Hooks::HookDispatch));

	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
		InjectHook(_addr(0x142CB34BC), tramp->Jump(XInputGetState_Hook), PATCH_JUMP);
}



bool ValidateGameVersion()
{
	char* gameName = (char*)_addr(0x1434B1F90);

	if (strncmp(gameName, "Injustice", strlen("Injustice")) == 0)
		return true;
	else
	{
		MessageBoxA(0, "Invalid game version!\nI2Hook only supports latest Steam executable.\n\n"
			"If you still cannot run the plugin and made sure that the game is updated, I2Hook needs to be updated.", 0, MB_ICONINFORMATION);
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
#ifdef _60_ONLY
			Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
			InjectHook(_addr(0x141BCF2F0), tramp->Jump(SetFlagNull), PATCH_JUMP);
#else
			SettingsMgr->Init();
			OnInitializeHook();
			eDirectX11Hook::Init();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);
#endif			
		}
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}