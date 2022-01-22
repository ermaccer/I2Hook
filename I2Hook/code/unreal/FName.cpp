#include "FName.h"
#include "..\dcf2.h"

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*,EFindName, int))_addr(0x1421D81E0))(this, Name, FindType, formal);
}
