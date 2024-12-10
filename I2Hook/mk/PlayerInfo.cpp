#include "PlayerInfo.h"

AIDrone* (*pPlayerInfo_GetDrone)(PlayerInfo*) = nullptr;
AIDrone* (*pPlayerInfo_MakeDrone)(PlayerInfo*) = nullptr;

void PlayerInfo::SetMeter(float value)
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_SetMeter);
	if (pat)
		((void(__fastcall*)(PlayerInfo*, float))pat)(this, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)(this + 0x338) = value;
	*(float*)(this + 0x338 + 4) = value;
}

void PlayerInfo::MakeDrone()
{
	if (pPlayerInfo_MakeDrone)
		pPlayerInfo_MakeDrone(this);
}

void PlayerInfo::MakeHuman()
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_MakeHuman);
	if (pat)
		((void(__fastcall*)(PlayerInfo*))pat)(this);
}

AIDrone* PlayerInfo::GetDrone()
{
	if (pPlayerInfo_GetDrone)
		return pPlayerInfo_GetDrone(this);
	return nullptr;
}

void AIDrone::Set(const char* script, int unk)
{
	static uintptr_t pat = _pattern(PATID_AIDrone_Set);
	if (pat)
		((void(__fastcall*)(AIDrone*, const char*, int))pat)(this, script, unk);
}

void AIDrone::SetLevel(float level)
{
	static uintptr_t pat = _pattern(PATID_AIDrone_SetLevel);
	if (pat)
		((void(__fastcall*)(AIDrone*, float))pat)(this, level);
}
