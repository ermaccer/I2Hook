#pragma once
#include "mk10utils.h"
#define GFG_GAME_INFO 0x14410C6D8

struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator
{
	int Pitch;
	int Yaw;
	int Roll;
};

namespace DCF2 {
	void SlowGameTimeForXTicks(float speed, int ticks);

	void __fastcall ActorCamSetPos(int64 ptr, FVector* pos);
	void __fastcall ActorCamSetRot(int64 ptr, FRotator* rot);
}

namespace DCF2Hooks {
	// hooks
	void __fastcall HookProcessStuff();


	void __fastcall HookActorCamSetPos(int64 ptr, FVector* pos);
	void __fastcall HookActorCamSetRot(int64 ptr, FRotator* rot);

}