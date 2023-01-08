#pragma once
#include <Windows.h>

// as usual, pluginmh/mugenhook

struct eMouseSettings {
	int sens;
	bool invert_y;
	bool invert_x;
};

class eSettingsManager {
public:
	void Init();

	bool bEnableConsoleWindow;
	bool bEnable60FPSFrontend;

	bool bEnableGamepadSupport;

	bool bDisableAnimationTool;

	// generic
	int iHookMenuOpenKey;
	int iToggleCustomCamKey;
	int iToggleSlowMoKey = VK_F5;
	int iToggleFreezeWorldKey = VK_F2;
	int iResetStageInteractablesKey;
	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;

	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;
	int iFreeCameraKeyPitchPlus;
	int iFreeCameraKeyPitchMinus;
	int iFreeCameraKeyRollPlus;
	int iFreeCameraKeyRollMinus;

	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	eMouseSettings mouse;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();

};

extern eSettingsManager* SettingsMgr;