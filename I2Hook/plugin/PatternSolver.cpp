#include "PatternSolver.h"
#include "..\utils\Patterns.h"
#include "..\gui\log.h"
#include <chrono>

uintptr_t PatternSolver::ms_patterns[PATID_Total_Patterns];


uintptr_t PatternSolver::GetPattern(const char* szPattern, int offset)
{
    uintptr_t addr = 0;
    try {
        addr = (uintptr_t)hook::txn::get_pattern(szPattern, offset);
    }
    TXN_CATCH();

    return addr;
}

void PatternSolver::Initialize()
{
    eLog::Message(__FUNCTION__, "Starting pattern search");

    for (int i = 0; i < PATID_Total_Patterns; i++)
        ms_patterns[i] = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    ms_patterns[PATID_MKProcDispatch_Hook] = GetPattern("E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? E8", 0);
    ms_patterns[PATID_RecordEvent_Hook] = GetPattern("E8 ? ? ? ? 33 C0 48 8D 54 24 ? 45 33 C9 48 89 44 24 ? B9 ? ? ? ? 48 89 44 24 ? 48 89 44 24", 0);
    ms_patterns[PATID_CameraPositionNOP] = GetPattern("8B 87 ? ? ? ? 0F 11 87", 6);
    ms_patterns[PATID_CameraRotationNOP] = GetPattern("48 8B CF F2 0F 11 8F", 3);
    ms_patterns[PATID_CameraPositionHook] = GetPattern("89 87 ? ? ? ? E8 ? ? ? ? 48 8D 54 24", 6);
    ms_patterns[PATID_CameraRotationHook] = GetPattern("48 8D 54 24 ? 48 8B CF E8 ? ? ? ? 4C 8D 9C 24 ? ? ? ? 49 8B 5B 10 41 0F 28 73", 8);
    ms_patterns[PATID_Dispatch_Hook] = GetPattern("E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 83 3D", 0);
    
    ms_patterns[PATID_CharacterDefinition_Set] = GetPattern("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 C7 45 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 70", 0);
    
    
    ms_patterns[PATID_MKProcDispatch] = GetPattern("48 8B C4 41 56 48 83 EC 60 48 C7 40 ? ? ? ? ? 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 48 8D 0D ? ? ? ? E8", 0);
    ms_patterns[PATID_Dispatch] = GetPattern("8B 51 18 39 51 14 74 0D 48 8B 01 89 51 14 48 FF A0 F8 00 00 00", 0);
    ms_patterns[PATID_RecordEvent] = GetPattern("41 56 48 83 EC 40 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 8B D9", 0);
    // PLAYERINFO
    ms_patterns[PATID_GetObj] = GetPattern("40 53 48 83 EC 20 8B 41 28 3D ? ? ? ? 73 40 8B D0 4C 8D 05 ? ? ? ? 8B 41 2C 41 39 04 90 75 2E 48 8B 59 20 48 85 DB 74 25 48 8B 03 48 8B CB", 0);
    ms_patterns[PATID_HideHUD] = GetPattern("48 89 74 24 ? 57 48 83 EC 20 8B F9 8B F2 48 8B 0D ? ? ? ? F6 81 ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 01 BA ? ? ? ? FF 90 ? ? ? ? 85 C0 0F 85 ? ? ? ? E8", 0);
    ms_patterns[PATID_ShowHUD] = GetPattern("48 89 74 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 8B F2 8B F9 F6 80 ? ? ? ? ? 0F 85 ? ? ? ? E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 48 89 5C 24 ? 48 8B 1D ? ? ? ? F6 83 ? ? ? ? ? 75 5B F7 D7", 0);
    ms_patterns[PATID_SlowGameTimeForXTicks] = GetPattern("40 57 48 83 EC 50 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 0F 29 74 24 ? 8B FA F3 0F 10 35", 0);
    
    ms_patterns[PATID_FGGameInfo_FindGameInfo] = GetPattern("48 8B 15 ? ? ? ? 45 33 C9 48 81 C2 ? ? ? ? B9 07 00 FF 00 45 8D 41 04 E8 ? ? ? ? 33 C0", 3);
    ms_patterns[PATID_FGGameInfo_SetStage] = GetPattern("48 8B 05 ? ? ? ? 48 8B 48 30 48 83 C1 08 E9", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables0] = GetPattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B F9 B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? 33 C9 E8 ? ? ? ? BB ? ? ? ? 0F 1F 00 8B CB", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables1] = GetPattern("48 89 5C 24 ? 56 48 83 EC 40 41 B9 ? ? ? ? 48 8D 91 ? ? ? ? 48 8B F1 45 8B C1 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 44 24 ? 48 85 C0 74 56", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables2] = GetPattern("48 83 EC 48 41 B9 ? ? ? ? 48 8D 91 ? ? ? ? 45 8B C1 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 44 24 ? 48 85 C0 74 59 48 89 5C 24 ? 0F 1F 00 8B 54 24 30", 0);

    ms_patterns[PATID_FGGameInfo_GetInfo] = GetPattern("83 FA 03 77 0C 48 63 C2 48 8B 84 C1 ? ? ? ? C3", 0);

    ms_patterns[PATID_MKCamera_SetPosition] = GetPattern("40 53 48 83 EC 20 F2 0F 10 02 48 8B D9 F2 0F 11 81 F8 00 00 00 8B 42 08 BA ? ? ? ? 89 81 ? ? ? ? E8 ? ? ? ? 48 8D 8B ? ? ? ? E8", 0);
    ms_patterns[PATID_MKCamera_SetRotation] = GetPattern("40 53 48 83 EC 20 F2 0F 10 02 48 8B D9 F2 0F 11 81 04 01 00 00 8B 42 08 BA", 0);
    
    ms_patterns[PATID_MKCharacter_SetLife] = GetPattern("40 53 48 81 EC ? ? ? ? 48 C7 44 24 ? ? ? ? ? 0F 29 74 24 ? 0F 28 F1 48 8B D9 48 8B 05 ? ? ? ? 83 78 1C 00 74 34 83 3D ? ? ? ? ? 74 2B 83 3D", 0);
    ms_patterns[PATID_MKCharacter_SetScale] = GetPattern("48 8B 49 20 48 85 C9 74 09 48 85 D2 0F 85 ? ? ? ? C3", 0);
    ms_patterns[PATID_MKCharacter_SetSpeed] = GetPattern("40 53 48 83 EC 30 0F 29 74 24 ? 48 8B D9 0F 28 F1 E8 ? ? ? ? 0F 28 CE F3 0F 11 B3 ? ? ? ? 48 8B CB 0F 28 74 24", 0);
    ms_patterns[PATID_MKCharacter_SetBreakers] = GetPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B FA 8B F1 E8 ? ? ? ? 48 8B D8 48 85 C0 74 69 48 8B C8 E8 ? ? ? ? 3B C7 74 5D 8B D7 48 8B CB E8 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 3F", 0);
    
    ms_patterns[PATID_MKCharacter_ActivateHeadTracking] = GetPattern("48 83 EC 38 8B 81 ? ? ? ? 0F 29 74 24 ? 0F 28 F1 3D ? ? ? ? 73 53 8B D0 4C 8D 05 ? ? ? ? 8B 81 ? ? ? ? 41 39 04 90 75 3E 48 89 5C 24 ? 48 8B 99 ? ? ? ? 48 85 DB 74 28", 0);
    ms_patterns[PATID_MKCharacter_KillHeadTracking] = GetPattern("48 83 EC 38 8B 81 ? ? ? ? 0F 29 74 24 ? 0F 28 F1 3D ? ? ? ? 73 56 8B D0 4C 8D 05 ? ? ? ? 8B 81 ? ? ? ? 41 39 04 90 75 41 48 89 5C 24 ? 48 8B 99 ? ? ? ? 48 85 DB 74 2B 48 8B 03 48 8B CB FF 50 58", 0);
    
    ms_patterns[PATID_MKCharacter_SetBoneSize] = GetPattern("48 89 54 24 ? 48 83 EC 28 48 8B 89 ? ? ? ? 48 8D 54 24 ? E8 ? ? ? ? 48 83 C4 28 C3 CC 48 8B C4", 0);
    ms_patterns[PATID_MKCharacter_GetBonePos] = GetPattern("4D 85 C0 74 62 53 48 83 EC 70 33 C0 49 8B D8 48 89 84 24 ? ? ? ? 48 3B D0 74 46 48 3B 15 ? ? ? ? 74 3D 48 3B 15", 0);
    ms_patterns[PATID_MKCharacter_GetBoneRot] = GetPattern("4D 85 C0 74 48 53 48 81 EC ? ? ? ? 49 8B D8 C7 44 24 ? ? ? ? ? 4C 8B C2 45 33 C9 48 8D 54 24 ? E8", 0);
    ms_patterns[PATID_MKCharacter_ExecuteScript] = GetPattern("40 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 C7 44 24 ? ? ? ? ? 48 89 9C 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 8B F9 45 8B F0", 0);
    
    ms_patterns[PATID_MKObject_GetPos] = GetPattern("40 53 48 83 EC 70 48 8B DA 48 8B 51 20 48 85 D2 74 3F 48 85 DB 74 3A 44 8B 41 30 45 85 C0 74 37 41 83 E8 01 74 0B 41 83 E8 01", 0);
   
    ms_patterns[PATID_GetScript0] = GetPattern("40 57 48 83 EC 70 48 C7 44 24 ? ? ? ? ? 48 89 9C 24 ? ? ? ? 48 8B D9 48 8B D1 33 C9 E8 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 33 FF 48 85 DB 74 19", 0);
    ms_patterns[PATID_GetScript1] = GetPattern("41 56 48 83 EC 40 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 8B F1 41 8B E8 48 8B DA 4C 8B F1 48 85 D2 74 19 80 3A 00 74 14 48 83 C8 FF 0F 1F 00 48 FF C0", 0);
    ms_patterns[PATID_MKScript_GetFunctionID] = GetPattern("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8D 99 88 01 00 00 8B FA 44 8B 43 08", 0);
    
    ms_patterns[PATID_PlayerInfo_SetMeter] = GetPattern("40 53 48 83 EC 40 48 8B 05 ? ? ? ? 48 8B D9 0F 29 74 24 ? 0F 28 F1 83 78 1C 00 74 34 83 3D", 0);
    
    ms_patterns[PATID_AnimationToolCode] = GetPattern("41 0F 59 C0 F3 44 0F 59 44 11", 11);
    
    ms_patterns[PATID_FName_FName] = GetPattern("40 53 48 83 EC 30 45 8B C8 C7 44 24 ? ? ? ? ? 45 33 C0 48 8B D9 E8 ? ? ? ? 48 8B C3 48 83 C4 30 5B C3", 0);
    ms_patterns[PATID_GetNames] = GetPattern("48 8B 05 ? ? ? ? 48 8B 0C C8 48 83 C1 10 E8 ? ? ? ? 0F 28 F0 48 8D 4C 24 ? E8 ? ? ? ? 90", 3);
    ms_patterns[PATID_USkeletalMeshComponent_GetBoneName] = GetPattern("40 53 48 83 EC 20 48 8B 89 ? ? ? ? 48 8B DA 48 8B 89 ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3", 0);
    
    ms_patterns[PATID_XInputGetState_Hook] = GetPattern("48 8D 54 24 ? E8 ? ? ? ? 85 C0 74 1F 41 B9", 6);
    ms_patterns[PATID_GetScaleform] = GetPattern("83 3D ? ? ? ? ? 0F 84 ? ? ? ? E8 ? ? ? ? 85 C0 75 09", 2);
    ms_patterns[PATID_ProcessDOFSettings] = GetPattern("48 8D 4B 48 E8 ? ? ? ? 3C 02 75 20 F3 0F 10 5C 24 ? 4D 8D 46 481", 4);
    ms_patterns[PATID_TocCheck] = GetPattern("48 89 54 24 ? 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 48 48 C7 44 24 ? ? ? ? ? 4D 8B E1 49 8B E8 48 8B FA 4C 8B F9 48 8D 99 ? ? ? ? 48 89 9C 24 ? ? ? ? 48 8B CB FF 15 ? ? ? ? 90", 0);


    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    auto timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    eLog::Message(__FUNCTION__, "Checked %d patterns in %dms (%ds)", PATID_Total_Patterns, time.count(), timeSeconds.count());

}

int PatternSolver::GetNumPatternsOK()
{
    int patternNum = 0;

    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i]) patternNum++;
    return patternNum;
}

bool PatternSolver::CheckMissingPatterns()
{
    int missingPatterns = 0;
    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i] == 0)
        {
            missingPatterns++;
            eLog::Message(__FUNCTION__, "ERROR: Could not find %s!", GetPatternName(i));
        }
    return missingPatterns > 0;
}

const char* PatternSolver::GetPatternName(int id)
{
    if (id >= PATID_Total_Patterns)
        return "UNKNOWN";

    static const char* szPatternNames[PATID_Total_Patterns] = {
        "MKProcDispatch_Hook",
        "RecordEvent_Hook",
        "CameraPositionNOP",
        "CameraRotationNOP",
        "CameraPositionHook",
        "CameraRotationHook",
        "Dispatch_Hook",
        "CharacterDefinition_Set",
        "MKProcDispatch",
        "Dispatch",
        "RecordEvent",
        "GetObj",
        "HideHUD",
        "ShowHUD",
        "SlowGameTimeForXTicks",
        "FGGameInfo_FindGameInfo",
        "FGGameInfo_SetStage",
        "FGGameInfo_ResetStageInteractables0",
        "FGGameInfo_ResetStageInteractables1",
        "FGGameInfo_ResetStageInteractables2",
        "FGGameInfo_GetInfo",
        "MKCamera_SetPosition",
        "MKCamera_SetRotation",
        "MKCharacter_SetLife",
        "MKCharacter_SetScale",
        "MKCharacter_SetSpeed",
        "MKCharacter_SetBreakers",
        "MKCharacter_ActivateHeadTracking",
        "MKCharacter_KillHeadTracking",
        "MKCharacter_SetBoneSize",
        "MKCharacter_GetBonePos",
        "MKCharacter_GetBoneRot",
        "MKCharacter_ExecuteScript",
        "MKObject_GetPos",
        "GetScript0",
        "GetScript1",
        "MKScript_GetFunctionID",
        "PlayerInfo_SetMeter",
        "AnimationToolCode",
        "FName_FName",
        "GetNames",
        "USkeletalMeshComponent_GetBoneName",
        "XInputGetState_Hook",
        "GetScaleform",
        "ProcessDOFSettings"
        "TocCheck",
    };  

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
