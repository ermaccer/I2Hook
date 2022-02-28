#pragma once
#include "MKStructs.h"
#include "mk10utils.h"
#include "unreal/FVector.h"
#include "GameInfo.h"

class MKCharacter {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetAbility(unsigned int id);

	int GetAbility();

	void ClearAbility();

	void ActivateHeadTracking();
	void KillHeadTracking();

	void SetBoneSize(const char* name, float size);

	void GetBonePos(const char* name, FVector* pos);
	void GetBoneRot(const char* name, FRotator* rot);


	void ExecuteScript(MKScript* script, int function);
};

