#include "GameInfo.h"
#include "dcf2.h"
#include "mk10utils.h"

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}

void FGGameInfo::SetStage(const char* stage)
{
	((void(__thiscall*)(FGGameInfo*, const char*))_addr(0x1411C8C00))(this, stage);
}

void FGGameInfo::ResetStageInteractables()
{
	int64 bgnd_info = *(int64*)(this + 48);

	((void(__fastcall*)(int64))_addr(0x1408A8750))(bgnd_info);
}

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	return ((PlayerInfo * (__fastcall*)(FGGameInfo*, PLAYER_NUM))_addr(0x140595DA0))(this, plr);
}


