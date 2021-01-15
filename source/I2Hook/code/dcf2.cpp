#include "dcf2.h"
#include "dcf2menu.h"
#include "mk10utils.h"
#include <iostream>
#include "eSettingsManager.h"
#include <Windows.h>

static int64 gametimer = GetTickCount64();

void __fastcall DCF2Hooks::HookProcessStuff()
{
	TheMenu->Process();

	if (TheMenu->bFreeCameraMovement)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}




	((void(__fastcall*)())(0x1498F27F0))();
}


void __fastcall DCF2Hooks::HookActorCamSetPos(int64 ptr, FVector * pos)
{
	if (TheMenu->bCustomFOV)
		*(float*)(ptr + 0x584 + 24) = TheMenu->camFov;
	else
		TheMenu->camFov = *(float*)(ptr + 0x584 + 24);

	if (!TheMenu->bCustomCamera)
	{
		TheMenu->camPos = *pos;
		DCF2::ActorCamSetPos(ptr, pos);
	}
	else
	{
		DCF2::ActorCamSetPos(ptr, &TheMenu->camPos);
	}

}

void __fastcall DCF2Hooks::HookActorCamSetRot(int64 ptr, FRotator * rot)
{
	if (!TheMenu->bCustomCameraRot)
	{
		TheMenu->camRot = *rot;
		DCF2::ActorCamSetRot(ptr, rot);
	}
	else
		DCF2::ActorCamSetRot(ptr, &TheMenu->camRot);
}

void DCF2::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x146E107F0))(speed, ticks, 0);
}

void __fastcall DCF2::ActorCamSetPos(int64 ptr, FVector * pos)
{
	*(float*)(ptr + 0x584) = pos->X;
	*(float*)(ptr + 0x584 + 4) = pos->Y;
	*(float*)(ptr + 0x584 + 8) = pos->Z;
	((void(__fastcall*)(int64, FVector*))_addr(0x141A10140))(ptr, pos);
}

void __fastcall DCF2::ActorCamSetRot(int64 ptr, FRotator * rot)
{
	*(int*)(ptr + 0x584 + 12) = rot->Pitch;
	*(int*)(ptr + 0x584 + 12 + 4) = rot->Yaw;
	*(int*)(ptr + 0x584 + 12 + 8) = rot->Roll;
	((void(__fastcall*)(int64, FRotator*))_addr(0x14AEA2640))(ptr, rot);
}
