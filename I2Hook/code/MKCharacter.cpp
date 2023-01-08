#include "MKCharacter.h"
#include "dcf2.h"

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1409725D0))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x141731F10))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x14096E0C0))(this, speed);
}

void MKCharacter::SetAbility(unsigned int id)
{
	*(int*)(this + 99068) = id;
}

int MKCharacter::GetAbility()
{
	return *(int*)(this + 99068);
}

void MKCharacter::ClearAbility()
{
	*(int*)(this + 99068) = 0;
}

void MKCharacter::ActivateHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1410CB9C0))(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1410CB940))(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName,float))_addr(0x1410CC940))(this, fname, size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FVector*))_addr(0x1410BBDA0))(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FRotator*))_addr(0x14094D570))(this, fname, rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	((void(__thiscall*)(MKCharacter*, MKScript*, int, int))_addr(0x14097A140))(this, script, function, 1);
}

void MKCharacter::BloodEffect(int type, FName name, float x, float y, float z, float unk, float size, float speed, bool attach)
{
	((void(__thiscall*)(MKCharacter*, int, FName, float, float, float, float, float, float, int))_addr(0x1409BDEA0))(this, type, name, x, y, z, unk, size, speed, attach);
}

USkeletalMeshComponent* MKCharacter::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x328);
}
