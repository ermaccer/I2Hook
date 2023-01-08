#pragma once
#include "TArray.h"
#include "FVector.h"
#include "FQuat.h"
#include "FName.h"


struct FBoneAtom {
	FQuat Rotation;
	FVector Translation;
	float JointRadius;
	FVector Scale;
};


struct FSkeletonPose {
	char pad[16];
	TArray<FBoneAtom> BoneAtoms;
};


class USkeletalMeshComponent {
public:
	char pad[0x720];
	FSkeletonPose pose;

	void GetBoneName(FName& name, int BoneIndex);
};