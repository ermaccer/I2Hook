#pragma once
#include "MKStructs.h"
#include "mk10utils.h"


class MKCharacter {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetAbility(unsigned int id);

	int GetAbility();

	void ClearAbility();

};

