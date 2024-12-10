#include "MKModifier.h"

Modifier::Modifier(const char* name)
{
	static uintptr_t pat = _pattern(PATID_MKModifier_Constructor);
	if (pat)
		((void(__fastcall*)(Modifier*, const char*))pat)(this, name);
}

void Modifier::Activate(MKCharacter* character)
{
	static uintptr_t pat = _pattern(PATID_MKModifier_Activate);
	if (pat)
		((void(__fastcall*)(Modifier*, MKCharacter*))pat)(this, character);
}

void MKModifier::ActivateModifier(const char* name, PLAYER_NUM player)
{
	Modifier mod(name);
	MKCharacter* obj = GetObj(player);
	if (obj)
		mod.Activate(obj);
}

void LoadModifierAssets()
{
	static uintptr_t pat = _pattern(PATID_LoadModifierAssets);
	if (pat)
		((void(__fastcall*)(FGGameInfo*))pat)(GetGameInfo());
}

TagAssistModifier::TagAssistModifier(const char* character)
{
	static uintptr_t pat = _pattern(PATID_MKTagModifier_Constructor);
	if (pat)
		((void(__fastcall*)(TagAssistModifier*, const char*))pat)(this, character);
}

void TagAssistModifier::Activate(PLAYER_NUM player)
{
	static uintptr_t pat = _pattern(PATID_MKTagModifier_Activate);
	if (pat)
		((void(__fastcall*)(TagAssistModifier*, PlayerInfo*))pat)(this, GetInfo(player));
}

void TagAssistModifier::ActivateObject(PLAYER_NUM player)
{
	static uintptr_t pat = _pattern(PATID_MKTagModifier_Activate2);
	if (pat)
		((void(__fastcall*)(TagAssistModifier*, MKCharacter*))pat)(this, GetObj(player));
}

