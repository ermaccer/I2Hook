#include "MKModifier.h"
#include "mk10utils.h"

TagAssistModifier::TagAssistModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x140B38390))(this, character, 0);
}

void TagAssistModifier::Activate(int64 info)
{
	((void(__fastcall*)(BaseModifier*, int64))_addr(0x140B3E1A0))(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	return  nullptr;
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B85BD0))(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	//((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))_addr(0x1405581D0))(this, obj);
}
