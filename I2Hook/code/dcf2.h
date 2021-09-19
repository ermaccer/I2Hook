#pragma once
#include "mk10utils.h"
#define GFG_GAME_INFO 0x14417DF30

#define I2HOOK_VERSION "0.4"

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};


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

struct character_info {
	char	name[16];
};

namespace DCF2 {

	int64 GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);

	PLAYER_NUM GetPlayerIDFromData(int64 data);

	// mkx recreation
	void SetCharacterMKX(PLAYER_NUM plr, char* name);
	void SetCharacter(int64 chr, char* name, int64 ptr, int64 unk);
	void SetStage(const char* stage);

	void SlowGameTimeForXTicks(float speed, int ticks);

	void SetCharacterLife(int64 obj, float life);

	void SetCharacterScale(int64 obj, FVector* scale);
	void SetCharacterSpeed(int64 obj, float speed);
	char* GetCharacterName(PLAYER_NUM plr);


	void  GetCharacterPosition(FVector* vec,PLAYER_NUM plr);

}

namespace DCF2Hooks {
	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);

	void   HookDispatch(int64 ptr, int a2);
	int64  HookSetProperty(int64 ptr, char* name, int64 unk);
	void   HookReadPropertyValue(int64 ptr, int* unk, int* value);

}