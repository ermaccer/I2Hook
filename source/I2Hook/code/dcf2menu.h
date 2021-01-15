#pragma once
#include "dcf2.h"
#include <Windows.h>
// as usual, based on mh2 debug menu

enum eTabs {
	TAB_SPEED,
	TAB_CAMERA
};
	

class DCF2Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool	 bSlowMotionEnabled;
	int      iSlowMotionTicks;
	float	 fSlowMotionSpeed;

	// window data

	bool bFocused;


	// camera

	bool bCustomCamera;
	bool bCustomFOV;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	float camFov;


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
	int  iSlowMoRefreshDelay;
	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	void UpdateMouse();
	bool GetActiveState();
};


extern DCF2Menu* TheMenu;