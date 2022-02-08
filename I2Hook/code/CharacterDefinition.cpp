#include "CharacterDefinition.h"

void CharacterDefinition::Set(const char* name, int64 loadout, int64 unk)
{
	((void(__fastcall*)(CharacterDefinition*, const char*, int64, int64))_addr(0x140B6A420))(this, name, loadout, unk);
}
