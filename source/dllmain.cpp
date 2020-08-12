//i2 hook
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10utils.h"
#include <iostream>

// timer 0x1442CFE7C
// kill p2 0x1442CFF10


using namespace Memory::VP;
using namespace hook;


int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}


const char* __fastcall SwapGameName()
{
	return "Injustice™ 2 | I2Hook";
}


bool __fastcall SetFlagNull()
{
	bool result = 0;
	Patch<int>(GetMKXAddr(0x14444D58C), 0);

	return result;

}


void OnInitializeHook()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);

	printf("I2Hook::OnInitializeHook() | Begin!\n");
	printf("I2Hook::OnInitializeHook() | Game detected: %s\n", (char*)GetMKXAddr(0x143455150));
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));

	// 60 fps
	Patch<char>(GetMKXAddr(0x145EDC870 + 1), 0);
	InjectHook(GetMKXAddr(0x14A370B70), tramp->Jump(SetFlagNull), PATCH_JUMP);
}
