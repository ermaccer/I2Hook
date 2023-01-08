#include "FName.h"
#include "..\dcf2.h"

FName::FName()
{
	Index = -1;
	Number = 0;
}

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*,EFindName, int))_addr(0x1421D81E0))(this, Name, FindType, formal);
}

TArray<FNameEntry*>* GetNames()
{
	return (TArray< FNameEntry* >*)_addr(0x1444B7278);
}

char* GetName(int index)
{
	if (GetNames()->Data[index])
		return GetNames()->Data[index]->name;
	else
		return "n/a";
}
