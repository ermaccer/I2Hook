#pragma once
#include <vector>
#include "../mk/CharacterDefinition.h"
#include "../mk/MKCharacter.h"
#include "../mk/MKCamera.h"
#include "../mk/MKModifier.h"
#include "PluginInterface.h"

#include "../helper/eKeyboardMan.h"
#include "../utils.h"

#define NUM_MODIFIERS 268
#define I2HOOK_VERSION "0.5.2"


enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	CAMERA_MK11,
	CAMERA_HEAD_TRACKING,
	CAMERA_9_16,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	SUBMENU_SCRIPT,
	SUBMENU_ANIMATIONTOOL,
	TOTAL_SUBMENUS
};

enum eScriptExecuteType {
	SCRIPT_P1,
	SCRIPT_P2,
	SCRIPT_GLOBAL
};

enum eModifierEntryFlag {
	ModifierEntryFlag_P1 = 1,
	ModifierEntryFlag_P2 = 2,
};

struct eScriptKeyBind {
	eScriptExecuteType type;
	eVKKeyCode key;
	char scriptName[128] = {};
	unsigned int functionHash;
};

struct ModifierEntry {
	std::string name;
	int flag;
};

extern const char* szModifiers[NUM_MODIFIERS];

class DCF2Menu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool     m_bFreezeWorld = false;
	bool	 m_bIsFocused = true;
	bool	 m_bHookDispatch = false;
	bool	 m_bForceCameraUpdate = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bDontFlipCamera = false;
	bool	 m_bDisableHeadTracking = false;
	bool	 m_bUsePlayerTwoAsTracker = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	bool	 m_bHideHUD = false;
	bool	 m_bAutoHideHUD = false;
	bool	 m_bMouseControl = false;
	bool	 m_bDisableDOF = false;

	// cheats
	bool	m_bInfiniteHealthP1 = false;
	bool	m_bInfiniteHealthP2 = false;
	bool	m_bNoHealthP1 = false;
	bool	m_bNoHealthP2 = false;
	bool	m_bInfiniteBreakersP1 = false;
	bool	m_bInfiniteBreakersP2 = false;
	bool	m_bInfiniteMeterP1 = false;
	bool	m_bInfiniteMeterP2 = false;
	bool	m_bZeroMeterP1 = false;
	bool	m_bZeroMeterP2 = false;

	bool	m_bChangePlayerSpeed = false;
	bool	m_bChangePlayerScale = false;
	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;

	bool	m_bTagAssist = false;
	bool	m_bTagAssistP2 = false;
	bool	m_bAddGlobalModifiers = false;
	bool    m_bDisableComboScaling = false;
	bool	m_bAIDroneModifierP1 = false;
	bool	m_bAIDroneModifierP2 = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomCameraX = -10.0f;
	float	 m_fAdjustCustomCameraY = 0.0f;
	float	 m_fAdjustCustomCameraZ = 161.0f;
	float	 m_fAdjustCustomCameraThirdPersonX = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonY = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraX = 0.0f;
	float	 m_fAdjustCustomHeadCameraY = 1200.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fFreeCameraSpeed = 5.25f;

	int  m_nFreeCameraRotationSpeed = 120;
	int  m_nCurrentCustomCamera = CAMERA_3RDPERSON;
	int  m_nCurrentCharModifier = 0;

	int  m_nAIDroneLevelP1 = 0;
	int  m_nAIDroneLevelP2 = 0;

	int  m_nP1Abilities = 0;
	int  m_nP2Abilities = 0;

	int* m_pCurrentVarToChange = nullptr;

	bool m_bP1CustomAbilities = false;
	bool m_P1Abilities[20] = {};
	bool m_bP2CustomAbilities = false;
	bool m_P2Abilities[20] = {};

	int  m_nScriptExecuteType = 0;
	unsigned int m_nHash = 0;
	MKScript* m_pScript;

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };


	char szCurrentModifier[128] = {};
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[64] = {};
	char szStageModifierStage[128] = {};
	char szPlayer1TagAssistCharacter[128] = {};
	char szPlayer2TagAssistCharacter[128] = {};

	char szPlayer1Bone[128] = {};
	char szPlayer2Bone[128] = {};

	char szPlayer1AI[128] = {};
	char szPlayer2AI[128] = {};

	TagAssistModifier* m_pTagAssistP1;
	TagAssistModifier* m_pTagAssistP2;


	std::vector<ModifierEntry> m_ModifiersList;

	// camera

	FVector  camPos;
	FRotator camRot;
	float	 camFov;

	// player 
	FVector plrPos;
	FVector plrPos2;

	std::vector<eScriptKeyBind> m_vKeyBinds;

	DCF2Menu();

	void	 OnActivate();
	void	 OnToggleSlowMotion();
	void	 OnToggleFreezeWorld();
	void	 OnToggleCustomCameras();
	void	 OnResetStageInteractables();
	void	 OnToggleFreeCamera();
	void	 OnToggleHUD();

	void	 Draw();
	void	 Process();
	void	 UpdateControls();
	void	 UpdateFreecam();
			 
	void	 DrawCharacterTab();
	void	 DrawStageTab();
	void	 DrawModifiersTab();
	void	 DrawPlayerTab();
	void	 DrawSpeedTab();
	void	 DrawCameraTab();
	void	 DrawCheatsTab();
	void	 DrawMiscTab();
	void	 DrawScriptTab();
			 
	void	 DrawSettings();
	void	 DrawScriptReference();
	void	 DrawAnimationTool();

	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);

#ifdef _DEBUG
	static void DrawDebug();
#endif

	bool GetActiveState();

	void RunLastScript();

	void ProcessScriptHotkeys();
};


extern DCF2Menu* TheMenu;
char* GetI2HookVersion();