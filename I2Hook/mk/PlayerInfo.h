#pragma once
#include "../utils.h"

class AIDrone {
public:
	void Set(const char* script, int unk);
	void SetLevel(float level);
};

class PlayerInfo {
public:
	void SetMeter(float value);
	void SetDamageMult(float value);
	void MakeDrone();
	void MakeHuman();

	AIDrone* GetDrone();
};

extern AIDrone*(*pPlayerInfo_GetDrone)(PlayerInfo*);
extern AIDrone* (*pPlayerInfo_MakeDrone)(PlayerInfo*);