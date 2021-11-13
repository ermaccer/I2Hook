#include "dcf2.h"
#include "dcf2menu.h"
#include "mk10utils.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include <Windows.h>
#include "mkcamera.h"
#include "MKCharacter.h"
#include <math.h>
#include "MKModifier.h"
int64 hud_property = 0;

void __fastcall Hooks::HookProcessStuff()
{
	TheMenu->Process();
	Notifications->Update();


	if (GetObj(PLAYER1))
	{
		if (TheMenu->m_bInfiniteBreakersP1)
			SetCharacterBreakers(PLAYER1, 1);
		if (TheMenu->m_bNoHealthP1)
			GetObj(PLAYER1)->SetLife(0.0f);
		if (TheMenu->m_bInfiniteHealthP1)
			GetObj(PLAYER1)->SetLife(1.0f);
		if (TheMenu->m_bInfiniteMeterP1)
			SetCharacterMeter(GetInfo(PLAYER1), 1.0f);
		if (TheMenu->m_bZeroMeterP1)
			SetCharacterMeter(GetInfo(PLAYER1), 0.0f);

		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP1Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P1Abilities) / sizeof(TheMenu->m_P1Abilities[0]); i++)
			{
				if (TheMenu->m_P1Abilities[i])
				{
					TheMenu->m_nP1Abilities += pow(2, i);
				}
			}
			GetObj(PLAYER1)->SetAbility(TheMenu->m_nP1Abilities);
		}
	}


	if (GetObj(PLAYER2))
	{
		if (TheMenu->m_bInfiniteBreakersP2)
			SetCharacterBreakers(PLAYER2, 1);
		if (TheMenu->m_bNoHealthP2)
			GetObj(PLAYER2)->SetLife(0.0f);
		if (TheMenu->m_bInfiniteHealthP2)
			GetObj(PLAYER2)->SetLife(1.0f);
		if (TheMenu->m_bInfiniteMeterP2)
			SetCharacterMeter(GetInfo(PLAYER2), 1.0f);
		if (TheMenu->m_bZeroMeterP2)
			SetCharacterMeter(GetInfo(PLAYER2), 0.0f);

		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP2Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P2Abilities) / sizeof(TheMenu->m_P2Abilities[0]); i++)
			{
				if (TheMenu->m_P2Abilities[i])
				{
					TheMenu->m_nP2Abilities += pow(2, i);
				}
			}
			GetObj(PLAYER2)->SetAbility(TheMenu->m_nP2Abilities);
		}
	}


	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetSpeed(TheMenu->m_fP1Speed);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetSpeed(TheMenu->m_fP2Speed);
	}
	if (TheMenu->m_bChangePlayerScale)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetScale(&TheMenu->m_vP1Scale);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetScale(&TheMenu->m_vP2Scale);
	}


	if (!(GetObj(PLAYER1)) || !(GetObj(PLAYER2)))
	{
		if (TheMenu->m_bCustomCameras)
			TheMenu->m_bCustomCameras = false;
	}



	if (TheMenu->m_bFreeCam)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->m_fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}


	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	((void(__fastcall*)())(_addr(0x141725320)))();
}

void __fastcall Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("I2Hook::Info() | Starting a new fight!\n");
	TheMenu->m_bCustomCameras = false;
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;

	if (TheMenu->m_bStageModifier)
		SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->m_bPlayer1Modifier)
		SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

	printf("I2Hook::Info() | %s VS %s\n", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));

	((void(__fastcall*)(int64, int64, int64, int64))_addr(0x14172B460))(eventID, a2, a3, a4);
}


void Hooks::HookDispatch(int64 ptr, int a2)
{
	if (TheMenu->m_bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->m_bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int))*(int64*)(arg + 0xF8))(ptr, a2);
	}
	else
		((int64(__fastcall*)(int64, int))_addr(0x1411CC8C0))(ptr, a2);
}

int64 Hooks::HookSetProperty(int64 ptr, char * name, int64 unk)
{
	hud_property = ptr;
	return ((int64(__fastcall*)(int64, char*, int64))_addr(0x1421D81E0))(ptr, name, unk);
}

void Hooks::HookReadPropertyValue(int64 ptr, int* unk, int* value)
{
	int input = *value;
	if (ptr == hud_property)
	{
		if (TheMenu->m_bDisableHUD)
			input ^= 1;
	}

	*unk = *(int*)(ptr + 296) & input | *unk & ~*(int*)(ptr + 296);
}



MKCharacter * GetObj(PLAYER_NUM plr)
{
	int64 info = GetInfo(plr);
	if (info)
		return ((MKCharacter*(__fastcall*)(int64, int))_addr(0x140B53010))(info, 0);
	else
		return 0;
}


int64 GetInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x140595DA0))(gameinfo, plr);
}

void SetCharacterMKX(PLAYER_NUM plr, char * name)
{
	int64 ptr = GetInfo(plr);
	int64 chr = (ptr + 192);
	SetCharacter(chr, name, 0, 0);
}

void SetCharacter(int64 chr, char * name, int64 ptr, int64 unk)
{
	((void(__fastcall*)(int64, const char*, int64, int64))_addr(0x140B6A420))(chr, name, ptr, unk);
}

void SetCharacterMeter(int64 chr, float meter)
{
	((void(__fastcall*)(int64, float))_addr(0x140B70C20))(chr, meter);
}

void SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))_addr(0x1411C8C00))(gameinfo, stage);
}

void SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x1409C4630))(speed, ticks, 0);
}

void SetTagAssist(PLAYER_NUM plr, char * character)
{
	((void(__fastcall*)(int64, char*))_addr(0x140B70E50))(GetInfo(plr), character);

}

void LoadModifierAssets()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	((void(__fastcall*)(int64, bool))_addr(0x1405A0C30))(gameinfo, 1);
}

void SetCharacterLife(int64 obj, float life)
{
	((void(__fastcall*)(int64, float))_addr(0x1409725D0))(obj, life);
}

void SetCharacterScale(int64 obj, FVector * scale)
{
	((void(__fastcall*)(int64, FVector*))_addr(0x149AEC310))(obj, scale);
}

void SetCharacterSpeed(int64 obj, float speed)
{
	((void(__fastcall*)(int64, float))_addr(0x1472BD780))(obj, speed);
}

void SetCharacterBreakers(PLAYER_NUM plr, int amount)
{
	((void(__fastcall*)(PLAYER_NUM, int))_addr(0x1407CA380))(plr, amount);
}



char * GetCharacterName(PLAYER_NUM plr)
{
	int64 info = GetInfo(plr);
	character_info* chr = *(character_info**)(info + 192);

	return chr->name;
}

void GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	((void(__fastcall*)(int64, FVector*))_addr(0x140B5BF00))(GetInfo(plr), vec);
}

