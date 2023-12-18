#include "MKObject.h"

void MKObject::GetPos(FVector* dest)
{
	static uintptr_t pat = _pattern(PATID_MKObject_GetPos);
	if (pat)
		((void(__fastcall*)(MKObject*, FVector*))pat)(this, dest);
}
