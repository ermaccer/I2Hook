#include "SkeletalMesh.h"
#include "..\dcf2.h"

void USkeletalMeshComponent::GetBoneName(FName& name, int BoneIndex)
{
	((void(__fastcall*)(USkeletalMeshComponent*,FName&, int))_addr(0x142149C80))(this, name, BoneIndex);
}
