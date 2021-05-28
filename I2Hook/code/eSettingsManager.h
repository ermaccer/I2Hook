#pragma once


// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	bool b60FPSModeOnly;

	bool bEnableConsoleWindow;
	bool bEnable60FPSFrontend;


	int iHookMenuOpenKey;
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



};

extern eSettingsManager* SettingsMgr;