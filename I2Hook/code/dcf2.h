#pragma once
#include "mk10utils.h"
#define GFG_GAME_INFO 0x14410C6D8

#define I2HOOK_VERSION "0.2"

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

	void SlowGameTimeForXTicks(float speed, int ticks);

	void SetCharacterLife(int64 obj, float life);

	char* GetCharacterName(PLAYER_NUM plr);


	void  GetCharacterPosition(FVector* vec,PLAYER_NUM plr);

	// mkx recreation
	void SetCharacter(PLAYER_NUM plr, char* name);
}

namespace DCF2Hooks {
	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);
	int64 __fastcall HookLoadCharacter(int64 ptr, char * name);

}