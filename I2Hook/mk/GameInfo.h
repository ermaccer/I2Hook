#pragma once
#include "PlayerInfo.h"
#include "..\utils.h"

enum  PLAYER_NUM
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS
};

class FGGameInfo {
public:
	static void FindGameInfo();
	static uintptr_t pGameInfo;
	void SetStage(const char* stage);
	void ResetStageInteractables();
	PlayerInfo* GetInfo(PLAYER_NUM plr);
};


FGGameInfo* GetGameInfo();