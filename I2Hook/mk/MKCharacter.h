#pragma once
#include "PlayerInfo.h"
#include "CharacterDefinition.h"
#include "GameInfo.h"
#include "MKScript.h"
#include "MKObject.h"

#include "..\unreal\SkeletalMesh.h"
#include "..\unreal\FRotator.h"
#include "..\unreal\FVector.h"
#include "..\utils.h"

class MKCharacter : public MKObject {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetAbility(unsigned int id);
	static void SetBreakersAmount(PLAYER_NUM plr, int value);

	int GetAbility();

	void ClearAbility();

	void ActivateHeadTracking();
	void KillHeadTracking();

	void SetBoneSize(const char* name, float size);

	void GetBonePos(const char* name, FVector* pos);
	void GetBoneRot(const char* name, FRotator* rot);


	void ExecuteScript(MKScript* script, int function);

	USkeletalMeshComponent* GetSkeleton();
};

