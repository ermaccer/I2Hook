#include "CharacterDefinition.h"

void CharacterDefinition::Set(const char* name, int64 loadout, int64 unk)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_Set);
	if (pat)
		((void(__fastcall*)(CharacterDefinition*, const char*, int64, int64))pat)(this, name, loadout, unk);
}
