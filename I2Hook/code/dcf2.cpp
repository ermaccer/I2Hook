#include "dcf2.h"
#include "dcf2menu.h"
#include "mk10utils.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include <Windows.h>

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




	((void(__fastcall*)())(0x1498F27F0))();
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

	((void(__fastcall*)(int64, int64, int64, int64))_addr(0x1416EC5B0))(eventID, a2, a3, a4);
}

int64 __fastcall DCF2Hooks::HookLoadCharacter(int64 ptr, char * name)
{
	// mk11 select screen swap, not sure if needed
	if (name)
	{

			if (TheMenu->bPlayer1ModifierEnabled)
			{
				if (ptr == DCF2::GetCharacterInfo(PLAYER1))
				{

					char* original_name = name;
					printf("I2Hook::Info() | Setting Player %d as %s\n",DCF2::GetPlayerIDFromData(ptr), TheMenu->szPlayer1ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer1ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], original_name);

					// crash fix
					TheMenu->bPlayer1ModifierEnabled = false;
				}
			}
			if (TheMenu->bPlayer2ModifierEnabled)
			{
				if (ptr == DCF2::GetCharacterInfo(PLAYER2))
				{
					char* original_name = name;
					printf("I2Hook::Info() | Setting Player %d as %s\n", DCF2::GetPlayerIDFromData(ptr), TheMenu->szPlayer2ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer2ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], original_name);
					TheMenu->bPlayer2ModifierEnabled = false;
				}
			}

	}
	return ((int64(__fastcall*)(int64, char*))_addr(0x145EAEC10))(ptr, name);
}




int64 DCF2::GetCharacterObject(PLAYER_NUM plr)
{
	int64 info = GetCharacterInfo(plr);
	if (info)
		return ((int64(__fastcall*)(int64, int))_addr(0x1472D7AA0))(info, 0);
}

int64 DCF2::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x145EB53B0))(gameinfo, plr);
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
	((void(__fastcall*)(int64, const char*, int64, int64))_addr(0x14730AD10))(chr, name, ptr, unk);
}

void DCF2::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x146E107F0))(speed, ticks, 0);
}

void DCF2::SetCharacterLife(int64 obj, float life)
{
	((void(__fastcall*)(int64, float))_addr(0x146D71630))(obj, life);
}

char * DCF2::GetCharacterName(PLAYER_NUM plr)
{
	int64 info = GetCharacterInfo(plr);
	character_info* chr = *(character_info**)(info + 192);

	return chr->name;
}

void DCF2::GetCharacterPosition(FVector * vec,PLAYER_NUM plr)
{
	((void(__fastcall*)(int64, FVector*))_addr(0x1472ED830))(GetCharacterInfo(plr), vec);
}

void DCF2::SetCharacter(PLAYER_NUM plr, char * name)
{
	((void(__fastcall*)(int64, char*))_addr(0x145EAEC10))(GetCharacterInfo(plr), name);
}

