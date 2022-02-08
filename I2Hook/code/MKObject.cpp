#include "MKObject.h"
#include "mk10utils.h"
#include <iostream>

void MKObject::GetPos(FVector* dest)
{
	((void(__fastcall*)(MKObject*, FVector*))_addr(0x141721CB0))(this, dest);
}
