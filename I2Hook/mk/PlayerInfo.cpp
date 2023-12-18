#include "PlayerInfo.h"

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
