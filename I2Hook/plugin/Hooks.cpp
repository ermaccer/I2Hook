#include "Hooks.h"
#include "..\mk\MKModifier.h"


void(__fastcall* pProcessDOFSettings)(int64, int64, int64, int64, int64) = 0;

void ProcessDOFSettings(int64 a1, int64 a2, int64 settings, int64 a4, int64 a5)
{
	if (TheMenu->m_bDisableDOF)
	{
		*(int*)(settings + 32) = 0;
	}

	if (pProcessDOFSettings)
		pProcessDOFSettings(a1, a2, settings, a4, a5);
}

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

		if (TheMenu->m_bAIDroneModifierP1)
		{
			if (AIDrone* drone = p1_info->GetDrone())
			{
				drone->Set(TheMenu->szPlayer1AI, 0);
				drone->SetLevel(TheMenu->m_nAIDroneLevelP1);
			}
		
		}



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

		if (TheMenu->m_bAIDroneModifierP2)
		{
			if (AIDrone* drone = p2_info->GetDrone())
			{
				drone->Set(TheMenu->szPlayer2AI, 0);
				drone->SetLevel(TheMenu->m_nAIDroneLevelP2);
			}

		}

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
	eLog::Message("I2Hook::Info()", "Starting a new fight!");
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;
	TheMenu->m_pTagAssistP1 = nullptr;
	TheMenu->m_pTagAssistP2 = nullptr;

	if (TheMenu->m_bStageModifier)
		GetGameInfo()->SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->m_bPlayer1Modifier)
		SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

	if (TheMenu->m_bTagAssist)
	{
		TheMenu->m_pTagAssistP1 = new TagAssistModifier(TheMenu->szPlayer1TagAssistCharacter);
		TheMenu->m_pTagAssistP1->Activate(PLAYER1);


		LoadModifierAssets();
		eLog::Message("I2Hook::Info()", "P1 Tag Assist: %s", TheMenu->szPlayer1TagAssistCharacter);
	}
	if (TheMenu->m_bTagAssistP2)
	{
		TheMenu->m_pTagAssistP2 = new TagAssistModifier(TheMenu->szPlayer2TagAssistCharacter);
		TheMenu->m_pTagAssistP2->Activate(PLAYER2);

		LoadModifierAssets();
		eLog::Message("I2Hook::Info()", "P2 Tag Assist: %s", TheMenu->szPlayer2TagAssistCharacter);
	}

	eLog::Message("I2Hook::Info()", "%s VS %s", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));
	PluginInterface::OnFightStartup();
}

void PluginFightStartupAddModifiers()
{
	if (TheMenu->m_bTagAssist)
	{
		if (TheMenu->m_pTagAssistP1)
			TheMenu->m_pTagAssistP1->ActivateObject(PLAYER1);
	}

	if (TheMenu->m_bTagAssistP2)
	{
		if (TheMenu->m_pTagAssistP2)
			TheMenu->m_pTagAssistP2->ActivateObject(PLAYER1);
	}


	if (TheMenu->m_bAIDroneModifierP1)
		SetCharacterAI(PLAYER1, TheMenu->szPlayer1AI, TheMenu->m_nAIDroneLevelP1);
	if (TheMenu->m_bAIDroneModifierP2)
		SetCharacterAI(PLAYER2, TheMenu->szPlayer2AI, TheMenu->m_nAIDroneLevelP2);

	if (!TheMenu->m_bAddGlobalModifiers)
		return;

	unsigned int numModifiers = TheMenu->m_ModifiersList.size();

	std::string modifiersNames = "";
	for (int i = 0; i < numModifiers; i++)
	{
		ModifierEntry& modifier = TheMenu->m_ModifiersList[i];

		modifiersNames += modifier.name.c_str();
		modifiersNames += "(";
		if (modifier.flag & ModifierEntryFlag_P1)
			modifiersNames += "P1";
		if (modifier.flag & ModifierEntryFlag_P2)
			modifiersNames += "P2";
		modifiersNames += ")";
		if (!(i == numModifiers - 1))
			modifiersNames += ",";
	}

	eLog::Message("I2Hook::Info()", "Used modifiers: %s", modifiersNames.c_str());

	for (int i = 0; i < numModifiers; i++)
	{
		ModifierEntry& modifier = TheMenu->m_ModifiersList[i];

		if (modifier.flag & ModifierEntryFlag_P1)
			MKModifier::ActivateModifier(TheMenu->m_ModifiersList[i].name.c_str(), PLAYER1);

		if (modifier.flag & ModifierEntryFlag_P2)
			MKModifier::ActivateModifier(TheMenu->m_ModifiersList[i].name.c_str(), PLAYER2);
	}
}
