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
