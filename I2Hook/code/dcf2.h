#pragma once

#include "mk10utils.h"
#include "MKStructs.h"
#include "MKCharacter.h"
#include "unreal/FVector.h"
#include "GameInfo.h"
#include "PlayerInfo.h"
#include "CharacterDefinition.h"

#define GFG_GAME_INFO 0x14417DF30

#define I2HOOK_VERSION "0.4.9"


MKCharacter*	 GetObj(PLAYER_NUM plr);
PlayerInfo*		 GetInfo(PLAYER_NUM plr);

void	SetCharacterMKX(PLAYER_NUM plr, char* name); // mkx recreation

void	SetCharacterBreakers(PLAYER_NUM plr, int amount);

char*	GetCharacterName(PLAYER_NUM plr);
void	GetCharacterPosition(FVector* vec,PLAYER_NUM plr);

void HideHUD();
void ShowHUD();


void	SlowGameTimeForXTicks(float speed, int ticks);
void	world_to_screen(FVector* pos, float* x, float* y);

void		LoadModifierAssets();

unsigned int HashString(const char* input);

namespace Hooks {
	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);

	void   HookDispatch(int64 ptr, int a2);
	int64  HookSetProperty(int64 ptr, char* name, int64 unk);
	void   HookReadPropertyValue(int64 ptr, int* unk, int* value);

}