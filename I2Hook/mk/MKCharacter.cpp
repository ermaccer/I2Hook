#include "MKCharacter.h"


void MKCharacter::SetLife(float life)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetLife);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetScale);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FVector*))pat)(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetSpeed);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, speed);
}

void MKCharacter::SetAbility(unsigned int id)
{
	*(int*)(this + 99068) = id;
}

void MKCharacter::SetBreakersAmount(PLAYER_NUM plr, int value)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetBreakers);
	if (pat)
		((void(__fastcall*)(PLAYER_NUM, int))pat)(plr, value);
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
	static uintptr_t pat = _pattern(PATID_MKCharacter_ActivateHeadTracking);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_KillHeadTracking);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetBoneSize);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FName, float))pat)(this, fname, size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_GetBonePos);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FName, FVector*))pat)(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_GetBoneRot);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FName, FRotator*))pat)(this, fname, rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScript*, int, int))pat)(this, script, function, 1);
}

USkeletalMeshComponent* MKCharacter::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x328);
}
