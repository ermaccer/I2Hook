#include "MKCharacter.h"
#include "dcf2.h"
void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1472C7DD0))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x149AEC310))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1472BD780))(this, speed);
}