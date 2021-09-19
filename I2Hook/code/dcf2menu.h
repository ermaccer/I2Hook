#pragma once
#include "dcf2.h"
#include <Windows.h>
// as usual, based on mh2 debug menu

enum eTabs {
	TAB_SPEED,
	TAB_CAMERA
};

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	CAMERA_MK11,
	TOTAL_CUSTOM_CAMERAS
};




class DCF2Menu {
private:
	int  iCurrentTab;
public:
	bool bIsActive;

	bool	 bSlowMotionEnabled;
	int      iSlowMotionTicks;
	float	 fSlowMotionSpeed;
	bool     bFreezeWorld;
	// window data
	

	// characters

	int  iCharacterModifierMode;
	char szCurrentModifier[128] = {};
	bool bPlayer1ModifierEnabled;
	bool bPlayer2ModifierEnabled;
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};

	bool bChangePlayerSpeed;
	float fPlayer1Speed;
	float fPlayer2Speed;


	bool bChangePlayerScale;
	FVector fPlayer1Scale;
	FVector fPlayer2Scale;

	bool bFocused;
	bool bHookDispatch;
	// cheats
	bool bInfiniteHealthPlayer1;
	bool bInfiniteHealthPlayer2;
	bool bNoHealthPlayer1;
	bool bNoHealthPlayer2;

	// camera

	bool bCustomCamera;
	bool bCustomFOV;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	float camFov;

	// player 
	FVector plrPos;
	FVector plrPos2;


	// cam mouse
	bool bEnableMouseControl;
	bool bInvertMouseY;
	POINT orgMouse;
	POINT curMouse;
	int     mouseSpeedX;
	int     mouseSpeedY;
	int     mouseSens;


	bool bFreeCameraMovement;
	float fFreeCameraSpeed;
	int  iFreeCameraRotSpeed;
	bool bEnableCustomCameras;
	int  iCurrentCustomCamera;
	char szCurrentCameraOption[128];
	bool bYObtained;


	float fAdjustCam;
	float fAdjustCamZ;
	float fAdjustCamX;

	float fAdjustCam3;
	float fAdjustCamZ3;
	float fAdjustCamX3;

	// stage
	bool bStageModifier;
	char szStageModifierStage[128] = {};

	bool bForceMoveCamera;
	bool bForceDisableHUD;
	bool bAutoHideHUD;

	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	void UpdateMouse();
	bool GetActiveState();

	void EditCharacter(PLAYER_NUM plr);
};


extern DCF2Menu* TheMenu;
char* GetI2HookVersion();