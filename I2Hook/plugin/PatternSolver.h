#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_MKProcDispatch_Hook,
	PATID_RecordEvent_Hook,
	PATID_CameraPositionNOP,
	PATID_CameraRotationNOP,
	PATID_CameraPositionHook,
	PATID_CameraRotationHook,
	PATID_Dispatch_Hook,

	PATID_CharacterDefinition_Set,

	PATID_MKProcDispatch,
	PATID_Dispatch,
	PATID_RecordEvent,
	PATID_GetObj,
	PATID_HideHUD,
	PATID_ShowHUD,
	PATID_SlowGameTimeForXTicks,

	PATID_FGGameInfo_FindGameInfo,
	PATID_FGGameInfo_SetStage,
	PATID_FGGameInfo_ResetStageInteractables0,
	PATID_FGGameInfo_ResetStageInteractables1,
	PATID_FGGameInfo_ResetStageInteractables2,
	PATID_FGGameInfo_GetInfo, 
	
	PATID_MKCamera_SetPosition,
	PATID_MKCamera_SetRotation,

	PATID_MKCharacter_SetLife,
	PATID_MKCharacter_SetScale,
	PATID_MKCharacter_SetSpeed,
	PATID_MKCharacter_SetBreakers,
	PATID_MKCharacter_ActivateHeadTracking,
	PATID_MKCharacter_KillHeadTracking,
	PATID_MKCharacter_SetBoneSize,
	PATID_MKCharacter_GetBonePos,
	PATID_MKCharacter_GetBoneRot,
	PATID_MKCharacter_ExecuteScript,

	PATID_LoadModifierAssets,
	PATID_MKModifier_Constructor,
	PATID_MKModifier_Activate,
	PATID_MKTagModifier_Constructor,
	PATID_MKTagModifier_Activate,
	PATID_MKTagModifier_Activate2,

	PATID_MKObject_GetPos,

	PATID_GetScript0,
	PATID_GetScript1,
	PATID_MKScript_GetFunctionID,

	PATID_PlayerInfo_SetMeter,
	PATID_PlayerInfo_GetDrone,
	PATID_PlayerInfo_MakeDrone,
	PATID_PlayerInfo_MakeHuman,
	PATID_AIDrone_Set,
	PATID_AIDrone_SetLevel,

	PATID_AnimationToolCode,

	PATID_FName_FName,
	PATID_GetNames,
	PATID_USkeletalMeshComponent_GetBoneName,

	PATID_XInputGetState_Hook,
	PATID_GetScaleform,
	PATID_ProcessDOFSettings,

	PATID_TocCheck,
	PATID_FightStartupAddModifiers,

	PATID_Total_Patterns
};


class PatternSolver {
public:
	static uintptr_t ms_patterns[PATID_Total_Patterns];

	static uintptr_t GetPattern(const char* szPattern, int offset);

	static void			Initialize();
	static int			GetNumPatternsOK();
	static bool			CheckMissingPatterns();
	static const char*	GetPatternName(int id);

};


uintptr_t _pattern(EPatternID id);