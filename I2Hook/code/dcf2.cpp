#include "dcf2.h"
#include "dcf2menu.h"
#include "mk10utils.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include <Windows.h>
#include "mkcamera.h"

int64 hud_property = 0;

static int64 gametimer = GetTickCount64();

void __fastcall DCF2Hooks::HookProcessStuff()
{
	TheMenu->Process();
	Notifications->Update();


	if (TheMenu->bNoHealthPlayer1)
	{
		if (DCF2::GetCharacterObject(PLAYER1))
			DCF2::SetCharacterLife(DCF2::GetCharacterObject(PLAYER1), 0.0f);
	}
	if (TheMenu->bNoHealthPlayer2)
	{
		if (DCF2::GetCharacterObject(PLAYER2))
			DCF2::SetCharacterLife(DCF2::GetCharacterObject(PLAYER2), 0.0f);
	}
	if (TheMenu->bInfiniteHealthPlayer1)
	{
		if (DCF2::GetCharacterObject(PLAYER1))
			DCF2::SetCharacterLife(DCF2::GetCharacterObject(PLAYER1), 1.0f);
	}
	if (TheMenu->bInfiniteHealthPlayer2)
	{
		if (DCF2::GetCharacterObject(PLAYER2))
			DCF2::SetCharacterLife(DCF2::GetCharacterObject(PLAYER2), 1.0f);
	}

	if (!(DCF2::GetCharacterObject(PLAYER1)) || !(DCF2::GetCharacterObject(PLAYER2)))
	{
		if (TheMenu->bEnableCustomCameras)
			TheMenu->bEnableCustomCameras = false;
	}

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


	if (TheMenu->bForceMoveCamera)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	((void(__fastcall*)())(0x149AD72E0))();
}

void __fastcall DCF2Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("I2Hook::Info() | Starting a new fight!\n");
	TheMenu->bEnableCustomCameras = false;
	TheMenu->bCustomCamera = false;
	TheMenu->bCustomCameraRot = false;
	TheMenu->bYObtained = false;

	if (TheMenu->bPlayer1ModifierEnabled)
		DCF2::SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->bPlayer2ModifierEnabled)
		DCF2::SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

	printf("I2Hook::Info() | %s VS %s\n", DCF2::GetCharacterName(PLAYER1), DCF2::GetCharacterName(PLAYER2));

	((void(__fastcall*)(int64, int64, int64, int64))_addr(0x14172B4C0))(eventID, a2, a3, a4);
}


int64 DCF2Hooks::HookSetProperty(int64 ptr, char * name, int64 unk)
{
	hud_property = ptr;
	return ((int64(__fastcall*)(int64, char*, int64))_addr(0x1421DFCE0))(ptr, name, unk);
}

void DCF2Hooks::HookReadPropertyValue(int64 ptr, int* unk, int* value)
{
	int input = *value;
	if (ptr == hud_property)
	{
		if (TheMenu->bForceDisableHUD)
			input ^= 1;
	}

	*unk = *(int*)(ptr + 296) & input | *unk & ~*(int*)(ptr + 296);
}




int64 DCF2::GetCharacterObject(PLAYER_NUM plr)
{
	int64 info = GetCharacterInfo(plr);
	if (info)
		return ((int64(__fastcall*)(int64, int))_addr(0x1477E5E50))(info, 0);
}

int64 DCF2::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x1465018D0))(gameinfo, plr);
}

PLAYER_NUM DCF2::GetPlayerIDFromData(int64 data)
{
	if (data == GetCharacterInfo(PLAYER2))
		return PLAYER2;
	else
		return PLAYER1;
}

void DCF2::SetCharacterMKX(PLAYER_NUM plr, char * name)
{
	int64 ptr = GetCharacterInfo(plr);
	int64 chr = (ptr + 192);
	DCF2::SetCharacter(chr, name, 0, 0);
}

void DCF2::SetCharacter(int64 chr, char * name, int64 ptr, int64 unk)
{
	((void(__fastcall*)(int64, const char*, int64, int64))_addr(0x147829EA0))(chr, name, ptr, unk);
}

void DCF2::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x1473892D0))(speed, ticks, 0);
}

void DCF2::SetCharacterLife(int64 obj, float life)
{
	((void(__fastcall*)(int64, float))_addr(0x1472C7DD0))(obj, life);
}

char * DCF2::GetCharacterName(PLAYER_NUM plr)
{
	int64 info = GetCharacterInfo(plr);
	character_info* chr = *(character_info**)(info + 192);

	return chr->name;
}

void DCF2::GetCharacterPosition(FVector * vec,PLAYER_NUM plr)
{
	((void(__fastcall*)(int64, FVector*))_addr(0x14780CEA0))(GetCharacterInfo(plr), vec);
}

