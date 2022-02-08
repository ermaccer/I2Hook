#include "PlayerInfo.h"
#include "mk10utils.h"

void PlayerInfo::SetMeter(float value)
{
	((void(__fastcall*)(PlayerInfo*, float))_addr(0x140B70C20))(this, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)(this + 0x338) = value;
	*(float*)(this + 0x338 + 4) = value;
}
