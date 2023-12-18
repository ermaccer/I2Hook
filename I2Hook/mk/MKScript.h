#pragma once
#include "..\utils.h"

// from mkoasm
#pragma pack(push, 1)
struct mko_function_header_mk10 {
	char* functionName; // offset in mko
	int64 functionOffset;
	int64 field16;
	int64 field24;
	int64 field32;
	unsigned int functionHash;
	int size;
	int field48;
	int field52;
	int num_args;
	int function_index;
	int local_fixup_count;
	int  checked_object_count;
	unsigned int paramsHash;
	int field72;
};
#pragma pack(pop)

class MKScript {
public:
    char pad[88];
    int numFunctions;
    int numVariables;
    char _pad[28];
    int bytecodeSize;
    char __pad[184];

	mko_function_header_mk10** functions;

    int GetFunctionID(int hash);
};

MKScript* GetScript(const char* name);

VALIDATE_OFFSET(MKScript, numFunctions, 88);
VALIDATE_OFFSET(MKScript, numVariables, 92);
VALIDATE_OFFSET(MKScript, bytecodeSize, 124);
VALIDATE_OFFSET(MKScript, functions, 312);