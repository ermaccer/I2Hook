#include "GameInfo.h"
#include "dcf2.h"
#include "mk10utils.h"

MKScript* GetScript(const char* name)
{
	int64 package = ((int64(__fastcall*)(const char*))_addr(0x1403CD5A0))("MainlineManaged.SystemPackages.FightingArt");
	if (package)
	{
		MKScript* script = ((MKScript * (__fastcall*)(int64, const char*, int, int))_addr(0x141182CF0))(package, name, 1, 0);
		return script;

	}
	return nullptr;
}

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

int MKScript::GetFunctionID(int hash)
{
	return ((int(__thiscall*)(MKScript*, int, int))_addr(0x14171E270))(this, hash, 0);
}
