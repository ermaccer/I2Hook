#include "Hooks.h"

void MKProcDispatch_Hook()
{
	PluginDispatch();
	MKProcDispatch();
}

void Dispatch_Hook(int64 ptr, int a2)
{
	if (TheMenu->m_bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->m_bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int)) * (int64*)(arg + 0xF8))(ptr, a2);
	}
	else
		Dispatch(ptr, a2);
}

void RecordEvent_Hook(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	PluginFightStartup();
	RecordEvent(eventID, a2, a3, a4);
}

void PluginDispatch()
{
	TheMenu->Process();
	Notifications->Update();
	eMouse::UpdateMouse();

	MKCharacter* p1 = GetObj(PLAYER1);
	MKCharacter* p2 = GetObj(PLAYER2);
	PlayerInfo* p1_info = GetInfo(PLAYER1);
	PlayerInfo* p2_info = GetInfo(PLAYER2);

	if (TheMenu->m_bSlowMotion)
		SlowGameTimeForXTicks(TheMenu->m_fSlowMotionSpeed, 10);

	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (p1)	p1->SetSpeed(TheMenu->m_fP1Speed);
		if (p2)	p2->SetSpeed(TheMenu->m_fP2Speed);
	}
	if (TheMenu->m_bChangePlayerScale)
	{
		if (p1) p1->SetScale(&TheMenu->m_vP1Scale);
		if (p2) p2->SetScale(&TheMenu->m_vP2Scale);
	}

	if (p1)
	{
		if (TheMenu->m_bInfiniteHealthP1)	p1->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)		p1->SetLife(0.0f);
		if (TheMenu->m_bInfiniteMeterP1) p1_info->SetMeter(1.0f);
		if (TheMenu->m_bZeroMeterP1)	p1_info->SetMeter(0.0f);
		if (TheMenu->m_bInfiniteBreakersP1) MKCharacter::SetBreakersAmount(PLAYER1, 1);


		if (TheMenu->m_bDisableComboScaling)
		{
			if (p1_info)
				p1_info->SetDamageMult(1.0f);
		}

		if (TheMenu->m_bAutoHideHUD)
			HideHUD();
		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP1Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P1Abilities) / sizeof(TheMenu->m_P1Abilities[0]); i++)
			{
				if (TheMenu->m_P1Abilities[i])
					TheMenu->m_nP1Abilities += (int)pow(2, i);
			}
			p1->SetAbility(TheMenu->m_nP1Abilities);
		}

		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING && TheMenu->m_bCustomCameras)
		{
			if (TheMenu->m_bUsePlayerTwoAsTracker)
				p2->SetBoneSize("Head", 0.1f);
			else
				p1->SetBoneSize("Head", 0.1f);

			TheMenu->m_bDisableHeadTracking = true;
		}

		if (TheMenu->m_bDisableHeadTracking)
		{
			if (TheMenu->m_bUsePlayerTwoAsTracker)
				p2->KillHeadTracking();
			else
				p1->KillHeadTracking();

		}
	}


	if (p2)
	{
		if (TheMenu->m_bInfiniteHealthP2)	p2->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP2)		p2->SetLife(0.0f);
		if (TheMenu->m_bInfiniteMeterP2) p2_info->SetMeter(1.0f);
		if (TheMenu->m_bZeroMeterP2)	p2_info->SetMeter(0.0f);
		if (TheMenu->m_bInfiniteBreakersP2) MKCharacter::SetBreakersAmount(PLAYER2, 1);

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p2_info)
				p2_info->SetDamageMult(1.0f);
		}

		if (TheMenu->m_bAutoHideHUD)
			HideHUD();

		if (TheMenu->m_bP2CustomAbilities)
		{
			TheMenu->m_nP2Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P2Abilities) / sizeof(TheMenu->m_P2Abilities[0]); i++)
			{
				if (TheMenu->m_P2Abilities[i])
					TheMenu->m_nP2Abilities += (int)pow(2, i);
			}
			p2->SetAbility(TheMenu->m_nP2Abilities);
		}

		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING && TheMenu->m_bCustomCameras)
		{
			if (TheMenu->m_bUsePlayerTwoAsTracker)
				p2->SetBoneSize("Head", 0.1f);
			else
				p1->SetBoneSize("Head", 0.1f);

			TheMenu->m_bDisableHeadTracking = true;
		}
	}

	TheMenu->UpdateFreecam();

	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	PluginInterface::OnFrameTick();
}

void PluginFightStartup()
{
	printf("I2Hook::Info() | Starting a new fight!\n");
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;

	if (TheMenu->m_bStageModifier)
		GetGameInfo()->SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->m_bPlayer1Modifier)
		SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

	printf("I2Hook::Info() | %s VS %s\n", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));
	PluginInterface::OnFightStartup();
}
