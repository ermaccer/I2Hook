#include "Menu.h"
#include "Settings.h"
#include "AnimationTool.h"
#include "../helper/eKeyboardMan.h"
#include "../helper/eMouse.h"
#include "../mk/Scaleform.h"

#include "../gui/notifications.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl.h"

#include <random>
#include <math.h>
#include <iostream>
#include <Windows.h>


using namespace Memory::VP;

std::random_device rd;
std::mt19937 mt(rd());

char textBuffer[260] = {};
const char* szCharacters[] = {
	// npcs
	"CHAR_Brainiac_BOSS",
	"CHAR_NightWing_MSTR",
	// main cast
	"CHAR_CaptainCold_A",
	"CHAR_Cheetah_A",
	"CHAR_Cyborg_A",
	"CHAR_Flash_A",
	"CHAR_Flash_B",
	"CHAR_GreenLantern_A",
	"CHAR_Supergirl_A",
	"CHAR_Superman_B",
	"CHAR_Raiden_A",
	"CHAR_Batman_A",
	"CHAR_GreenLantern_DCF1",
	"CHAR_Aquaman_MSTR",
	"CHAR_Atom_MSTR",
	"CHAR_Atrocitus_MSTR",
	"CHAR_Bane_MSTR",
	"CHAR_Batman_MSTR",
	"CHAR_BlackAdam_MSTR",
	"CHAR_BlackCanary_MSTR",
	"CHAR_BlackManta_MSTR",
	"CHAR_BlueBeetle_MSTR",
	"CHAR_Brainiac_MSTR",
	"CHAR_CaptainCold_MSTR",
	"CHAR_Catwoman_MSTR",
	"CHAR_Cheetah_MSTR",
	"CHAR_Cyborg_MSTR",
	"CHAR_DamianWayne_MSTR",
	"CHAR_Darkseid_MSTR",
	"CHAR_Deadshot_MSTR",
	"CHAR_Donatello_MSTR",
	"CHAR_DrFate_MSTR",
	"CHAR_Enchantress_MSTR",
	"CHAR_Firestorm_MSTR",
	"Char_Flash_MSTR",
	"CHAR_GorillaGrodd_MSTR",
	"CHAR_GreenArrow_MSTR",
	"CHAR_GreenLantern_MSTR",
	"CHAR_HarleyQuinn_MSTR",
	"CHAR_Hellboy_MSTR",
	"CHAR_Joker_MSTR",
	"CHAR_Leonardo_MSTR",
	"CHAR_Michelangelo_MSTR",
	"CHAR_PoisonIvy_MSTR",
	"CHAR_Raiden_MSTR",
	"CHAR_Raphael_MSTR",
	"CHAR_RedHood_MSTR",
	"CHAR_Scarecrow_MSTR",
	"CHAR_StarFire_MSTR",
	"CHAR_SubZero_MSTR",
	"CHAR_Supergirl_MSTR",
	"CHAR_Superman_A",
	"CHAR_Superman_MSTR",
	"CHAR_SwampThing_MSTR",
	"CHAR_TMNT_MSTR",
	"CHAR_WonderWoman_MSTR",

	// story and ??
	"NT_Raphael",
	"NT_StoryDefault",
	"NT_Mutagen",
	"NT_Michelangelo",
	"NT_Leonardo",
	"NT_Krang",
	"NT_Donatello",
	"SZ_Unmasked",
	"SF_StoryDefault",
	"SZ_StoryDefault",
	"RA_StoryDefault",
	"RH_StoryDefault",
	"HB_StoryDefault",
	"RA_Classic",
	"EC_StoryDefault",
	"WW_StoryDefault",
	"AM_StoryDefault",
	"WW_ChapterOne",
	"WW_DLC1",
	"ST_Preset01",
	"ST_StoryDefault",
	"SU_StoryDefault",
	"ST_Marketing",
	"SG_StoryDefault",
	"SU_ChapterOne",
	"PI_StoryDefault",
	"SC_StoryDefault",
	"JK_StoryDefault",
	"HQ_Jester",
	"HQ_StoryDefault",
	"GA_StoryDefault",
	"GL_StoryDefault",
	"GG_StoryDefault",
	"GA_Mask",
	"FL_StoryDefault",
	"DF_StoryDefault",
	"FS_StoryDefault",
	"DE_StoryDefault",
	"DS_StoryDefault",
	"DW_NightWing",
	"DW_StoryDefault",
	"DW_CapeNHood",
	"DW_ChapterOne",
	"CY_ChapterOne",
	"CY_StoryDefault",
	"CW_StoryDefault",
	"CH_StoryDefault",
	"BR_StoryDefault",
	"CC_StoryDefault",
	"BC_StoryDefault",
	"BB_StoryDefault",
	"BM_StoryDefault",
	"BA_StoryDefault",
	"BM_Mark11",
	"BM_Montage",
	"BM_Brainiac",
	"BM_ChapterOne",
	"AT_StoryDefault",
	"BN_StoryDefault",
	"AQ_StoryDefault",


};

const char* szTagCharacters[] = {
	"Aquaman",
	"Atom",
	"Atrocitus",
	"Bane",
	"Batman",
	"BlackAdam",
	"BlackCanary",
	"BlackManta",
	"BlueBeetle",
	"Brainiac",
	"CaptainCold",
	"Catwoman",
	"Cheetah",
	"Cyborg",
	"DamianWayne",
	"Darkseid",
	"Deadshot",
	"DrFate",
	"Enchantress",
	"Firestorm",
	"Flash",
	"GorillaGrodd",
	"GreenArrow",
	"GreenLantern",
	"Hellboy",
	"Joker",
	"PoisonIvy",
	"Raiden",
	"RedHood",
	"Scarecrow",
	"StarFire",
	"SubZero",
	"Supergirl",
	"Superman",
	"SwampThing",
	"TMNT",
	"WonderWoman",
};

const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid",
	"Mortal Kombat 11",
	"Head Perspective",
	"9:16",
};

const char* szStageNames[]{
  "BGND_ArkhamAsylum",
  "BGND_Atlantis",
  "BGND_BatCave",
  "BGND_BrainiacShip",
  "BGND_FortressOfSolitude",
  "BGND_GorillaCity",
  "BGND_GothamCity",
  "BGND_JokerPlayground",
  "BGND_Kahndaq",
  "BGND_Metropolis",
  "BGND_RedSunPrison",
  "BGND_SlaughterSwamp",
  "BGND_CharacterTest",
  "BGND_DCF2Physics",
  "BGND_EmptyMap",
};


const char* szBones[] = {
	"Head",
	"Hips",
	"Jaw",
	"LeftArm",
	"LeftEye",
	"LeftFoot",
	"LeftForeArm",
	"LeftHand",
	"LeftLeg",
	"Neck",
	"Neck1",
	"Reference",
	"RightArm",
	"RightEye",
	"RightFoot",
	"RightHand",
	"RightLeg",
	"Spine",
	"Spine1",
	"Spine2",
	"Spine3",
};

const char* szAI[] = {
	"AI_ButtonMasher.mko",
	"AI_DebugOnlineButtonMasher.mko",
	"AI_Dummy.mko",
	"AI_Fighter.mko",
	"AI_Flying.mko",
	"AI_Normal.mko",
	"AI_SingleMove.mko",
	"AI_Test.mko",
	"AI_Training.mko",
	"AI_Verifier.mko",
};


int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}


DCF2Menu* TheMenu = new DCF2Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


DCF2Menu::DCF2Menu()
{
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szPlayer1Bone, szBones[0]);
	sprintf(szPlayer2Bone, szBones[0]);
	sprintf(szPlayer1TagAssistCharacter, szTagCharacters[0]);
	sprintf(szPlayer2TagAssistCharacter, szTagCharacters[0]);
	sprintf(szPlayer1AI, szAI[0]);
	sprintf(szPlayer2AI, szAI[0]);
}

void DCF2Menu::OnActivate()
{
	m_bIsActive ^= 1;
}

void DCF2Menu::OnToggleSlowMotion()
{
	if (m_bIsActive)
		return;

	m_bSlowMotion ^= 1;
}

void DCF2Menu::OnToggleFreezeWorld()
{
	if (m_bIsActive)
		return;

	m_bFreezeWorld ^= 1;
}

void DCF2Menu::OnToggleCustomCameras()
{
	if (m_bIsActive)
		return;

	if (GetObj(PLAYER1) && GetObj(PLAYER2))
		m_bCustomCameras ^= 1;
	else
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Custom cameras can only be activated in game!");
	}
}

void DCF2Menu::OnResetStageInteractables()
{
	if (m_bIsActive)
		return;

	if (GetObj(PLAYER1) && GetObj(PLAYER2))
		GetGameInfo()->ResetStageInteractables();
	else
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Stage objects can only be reset in game!");
	}
}

void DCF2Menu::OnToggleFreeCamera()
{
	if (m_bIsActive)
		return;

	m_bFreeCam ^= 1;
}

void DCF2Menu::OnToggleHUD()
{
	if (m_bIsActive)
		return;

	m_bHideHUD ^= 1;

	if (Scaleform::ms_bActive)
	{
		if (m_bHideHUD)
			*Scaleform::ms_bActive = false;
		else
			*Scaleform::ms_bActive = true;
	}
}

void DCF2Menu::Draw()
{
	if (!m_bIsActive)
		return;


	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin("I2Hook by ermaccer", &m_bIsActive, ImGuiWindowFlags_MenuBar);


	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::BeginMenu("About"))
			{
				ImGui::MenuItem("Version: " I2HOOK_VERSION);
				ImGui::MenuItem("Date: " __DATE__);
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Script Reference"))
				m_bSubmenuActive[SUBMENU_SCRIPT] = true;

			ImGui::EndMenu();
		}
		if (!SettingsMgr->bDisableAnimationTool)
		{
			if (ImGui::BeginMenu("Posing"))
			{
				m_bSubmenuActive[SUBMENU_ANIMATIONTOOL] = true;
				ImGui::EndMenu();
			}
		}

	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character"))
		{
			DrawCharacterTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage"))
		{
			DrawStageTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Modifiers"))
		{
			DrawModifiersTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			DrawCheatsTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Script"))
		{
			DrawScriptTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	if (m_bSubmenuActive[SUBMENU_SCRIPT])
		DrawScriptReference();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();

	if (m_bSubmenuActive[SUBMENU_ANIMATIONTOOL])
		DrawAnimationTool();
}

void DCF2Menu::Process()
{
	UpdateControls();
	if (!SettingsMgr->bDisableAnimationTool)
	{
		static uintptr_t pat = _pattern(PATID_AnimationToolCode);
		if (pat)
		{
			if (AnimationTool::ms_bActive)
			{
				Nop(pat, 3);
			}
			else
			{
				Patch<unsigned char>(pat, 0x48);
				Patch<unsigned char>(pat + 1, 0x8B);
				Patch<unsigned char>(pat + 2, 0x08);
			}
			AnimationTool::ProcessPosing();

			if (!GetObj(PLAYER1))
			{
				Patch<unsigned char>(pat, 0x48);
				Patch<unsigned char>(pat + 1, 0x8B);
				Patch<unsigned char>(pat + 2, 0x08);
			}
		}
	}
}

void DCF2Menu::UpdateControls()
{
	if (!m_bIsActive)
		ProcessScriptHotkeys();
}

void DCF2Menu::UpdateFreecam()
{
	if (TheMenu->m_bFreeCam)
	{
		if (TheCamera)
		{
			FVector fwd = TheCamera->GetMatrix().GetForward();
			FVector strafe = TheCamera->GetMatrix().GetRight();
			FVector up = TheCamera->GetMatrix().GetUp();

			// forward

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * 1;


			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBackward))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * -1;

			// strafe

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * -1;

			// up

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * -1;


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

			// mouse
			{
				if (!TheMenu->m_bIsActive && TheMenu->m_bMouseControl)
				{
					TheMenu->camRot.Pitch += eMouse::GetDeltaY();
					TheMenu->camRot.Yaw += eMouse::GetDeltaX();
				}
			}
		}
	}
}

void DCF2Menu::DrawCharacterTab()
{
	ImGui::Checkbox("Enable Player 1 Modifier", &m_bPlayer1Modifier);

	if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
		{
			bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
			if (ImGui::Selectable(szCharacters[n], is_selected))
				sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}

	ImGui::Separator();
	ImGui::Checkbox("Enable Player 2 Modifier", &m_bPlayer2Modifier);

	if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
		{
			bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
			if (ImGui::Selectable(szCharacters[n], is_selected))
				sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::Separator();

}

void DCF2Menu::DrawStageTab()
{
	ImGui::Checkbox("Enable Stage Modifier", &m_bStageModifier);

	if (ImGui::BeginCombo("Stage", szStageModifierStage))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
		{
			bool is_selected = (szStageModifierStage == szStageNames[n]);
			if (ImGui::Selectable(szStageNames[n], is_selected))
				sprintf(szStageModifierStage, szStageNames[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
}

void DCF2Menu::DrawModifiersTab()
{
	if (ImGui::BeginTabBar("##modifiers"))
	{
		if (ImGui::BeginTabItem("Tag Assists"))
		{
			ImGui::Checkbox("Player 1 Tag Assist Modifier", &m_bTagAssist);

			if (ImGui::BeginCombo("Player 1 Tag Assist Character", szPlayer1TagAssistCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szTagCharacters); n++)
				{
					bool is_selected = (szPlayer1TagAssistCharacter == szTagCharacters[n]);
					if (ImGui::Selectable(szTagCharacters[n], is_selected))
						sprintf(szPlayer1TagAssistCharacter, szTagCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::Checkbox("Player 2 Tag Assist Modifier", &m_bTagAssistP2);

			if (ImGui::BeginCombo("Player 2 Tag Assist Character", szPlayer2TagAssistCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szTagCharacters); n++)
				{
					bool is_selected = (szPlayer2TagAssistCharacter == szTagCharacters[n]);
					if (ImGui::Selectable(szTagCharacters[n], is_selected))
						sprintf(szPlayer2TagAssistCharacter, szTagCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::Separator();

			ImGui::TextWrapped("If you get load crashes enable modifier in-game then restart or rematch (when online).");
			ImGui::TextWrapped("Restart match when you toggle these in game!");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Abilities"))
		{
			ImGui::Checkbox("Player 1 Custom Abilities", &m_bP1CustomAbilities);
			ImGui::SameLine(); ShowHelpMarker("Set these on select screen! Changing these in game might make moves locked.");
			ImGui::Separator();


			for (int i = 0; i < sizeof(m_P1Abilities) / sizeof(m_P1Abilities[0]); i++)
			{
				sprintf(textBuffer, "Ability %d", i + 1);

				ImGui::Checkbox(textBuffer, &m_P1Abilities[i]);

				if (i % 2 == 0)
					ImGui::SameLine();
			}


			if (GetObj(PLAYER1))
			{
				if (ImGui::Button("Get##p1"))
				{
					int abilities = GetObj(PLAYER1)->GetAbility();

					for (int i = 0; i < sizeof(m_P1Abilities) / sizeof(m_P1Abilities[0]); i++)
					{
						int id = (int)pow(2, i);
						m_P1Abilities[i] = abilities & id;
					}
				}

			}
			ImGui::Separator();
			ImGui::Checkbox("Player 2 Custom Abilities", &m_bP2CustomAbilities);
			ImGui::Separator();

			for (int i = 0; i < sizeof(m_P2Abilities) / sizeof(m_P2Abilities[0]); i++)
			{
				sprintf(textBuffer, "Ability %d##p2", i + 1);

				ImGui::Checkbox(textBuffer, &m_P2Abilities[i]);

				if (i % 2 == 0)
					ImGui::SameLine();
			}


			if (GetObj(PLAYER2))
			{
				if (ImGui::Button("Get##p2"))
				{
					int abilities = GetObj(PLAYER2)->GetAbility();

					for (int i = 0; i < sizeof(m_P2Abilities) / sizeof(m_P2Abilities[0]); i++)
					{
						int id = (int)pow(2, i);
						m_P2Abilities[i] = abilities & id;
					}
				}

			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Skeleton"))
		{
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				if (!m_bDisableHeadTracking)
					ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Enable 'Disable Head Tracking' in Misc. section before editing head data!\nRestart match after enabling it.");
				ImGui::TextWrapped("Player 1");
				ImGui::Separator();
				if (ImGui::BeginCombo("Bone##p1", szPlayer1Bone))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szBones); n++)
					{
						bool is_selected = (szPlayer1Bone == szBones[n]);
						if (ImGui::Selectable(szBones[n], is_selected))
							sprintf(szPlayer1Bone, szBones[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
					ImGui::EndCombo();
				}
				static float boneSizeP1 = 0.0f;
				ImGui::InputFloat("Size##p1", &boneSizeP1);


				if (ImGui::Button("Change Bone", { -FLT_MIN, 0 }))
				{
					Notifications->SetNotificationTime(2500);
					Notifications->PushNotification("Changed %s", szPlayer1Bone);
					GetObj(PLAYER1)->SetBoneSize(szPlayer1Bone, boneSizeP1);
				}

				ImGui::TextWrapped("Player 2");
				ImGui::Separator();

				if (ImGui::BeginCombo("Bone##p2", szPlayer2Bone))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szBones); n++)
					{
						bool is_selected = (szPlayer2Bone == szBones[n]);
						if (ImGui::Selectable(szBones[n], is_selected))
							sprintf(szPlayer2Bone, szBones[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
					ImGui::EndCombo();
				}
				static float boneSizeP2 = 0.0f;
				ImGui::InputFloat("Size##p2", &boneSizeP2);


				if (ImGui::Button("Change Bone##p2", { -FLT_MIN, 0 }))
				{
					Notifications->SetNotificationTime(2500);
					Notifications->PushNotification("Changed %s", szPlayer1Bone);
					GetObj(PLAYER2)->SetBoneSize(szPlayer2Bone, boneSizeP2);
				}

				ImGui::Separator();
				ImGui::TextWrapped("Presets");
				if (ImGui::Button("Big Heads", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("Head", 1.5f);
					GetObj(PLAYER2)->SetBoneSize("Head", 1.5f);
					GetObj(PLAYER1)->SetBoneSize("Neck", 1.5f);
					GetObj(PLAYER2)->SetBoneSize("Neck", 1.5f);
				}
				if (ImGui::Button("Big Fists", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftHand", 3.0f);
					GetObj(PLAYER1)->SetBoneSize("RightHand", 3.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftHand", 3.0f);
					GetObj(PLAYER2)->SetBoneSize("RightHand", 3.0f);
				}
				if (ImGui::Button("Googly Eyes", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftEye", 2.0f);
					GetObj(PLAYER1)->SetBoneSize("RightEye", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftEye", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("RightEye", 2.0f);
				}
				if (ImGui::Button("Large Feet", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftFoot", 2.0f);
					GetObj(PLAYER1)->SetBoneSize("RightFoot", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftFoot", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("RightFoot", 2.0f);
				}
				if (ImGui::Button("Reset All", { -FLT_MIN, 0 }))
				{
					for (int i = 0; i < sizeof(szBones) / sizeof(szBones[0]); i++)
					{
						GetObj(PLAYER1)->SetBoneSize(szBones[i], 1.0f);
						GetObj(PLAYER2)->SetBoneSize(szBones[i], 1.0f);
					}
				}
				ImGui::Separator();
			}
			else
				ImGui::TextWrapped("Skeleton options are only available in-game!");

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("AI"))
		{
			ImGui::TextWrapped("Reload match to change if players are AI controlled.");
			ImGui::Separator();
			ImGui::Checkbox("Change Player 1 AI", &m_bAIDroneModifierP1);

			if (ImGui::BeginCombo("Player 1 AI", szPlayer1AI))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szAI); n++)
				{
					bool is_selected = (szPlayer1AI == szAI[n]);
					if (ImGui::Selectable(szAI[n], is_selected))
						sprintf(szPlayer1AI, szAI[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}

			ImGui::SliderInt("Player 1 AI Level", &m_nAIDroneLevelP1, 0, 19);
			ImGui::Separator();
			ImGui::Checkbox("Change Player 2 AI", &m_bAIDroneModifierP2);

			if (ImGui::BeginCombo("Player 2 AI", szPlayer2AI))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szAI); n++)
				{
					bool is_selected = (szPlayer2AI == szAI[n]);
					if (ImGui::Selectable(szAI[n], is_selected))
						sprintf(szPlayer2AI, szAI[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::SliderInt("Player 2 AI Level", &m_nAIDroneLevelP2, 0, 19);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Tower Modifiers"))
		{
			ImGui::TextWrapped("Reload match to apply changes.");
			ImGui::Separator();
			ImGui::Checkbox("Add Tower Modifiers", &m_bAddGlobalModifiers);
			ImGui::Separator();

			enum EModifierFlagType {
				ModifierFlagType_Both,
				ModifierFlagType_P1Only,
				ModifierFlagType_P2Only,
			};
			static int flagType = ModifierFlagType_Both;


			ImGui::TextWrapped("Target");
			ImGui::Separator();
			ImGui::RadioButton("Both", &flagType, ModifierFlagType_Both); ImGui::SameLine();
			ImGui::RadioButton("Player 1 Only", &flagType, ModifierFlagType_P1Only); ImGui::SameLine();
			ImGui::RadioButton("Player 2 Only", &flagType, ModifierFlagType_P2Only);
			ImGui::Separator();

			static char modifierName[256] = {};
			static ImGuiTextFilter filter;
			ImGui::Text("Search Modifiers");
			ImGui::PushItemWidth(-FLT_MIN);
			filter.Draw("##modlist");
			ImGui::PopItemWidth();
			ImGui::BeginChild("##list", { 0, 125.0f }, true);
			{

				for (int i = 0; i < NUM_MODIFIERS; i++)
				{
					if (filter.PassFilter(szModifiers[i]))
					{
						bool is_selected = (modifierName == szModifiers[i]);
						if (ImGui::Selectable(szModifiers[i], is_selected))
						{
							sprintf(modifierName, "%s", szModifiers[i]);
						}
					}


				}
			}
			ImGui::EndChild();
			if (strlen(modifierName) > 0)
				ImGui::TextWrapped("Selected: %s", modifierName);
			if (ImGui::Button("Add", { -FLT_MIN, 0 }))
			{
				ModifierEntry entry;
				entry.name = modifierName;
				switch (flagType)
				{
				case ModifierFlagType_Both:
					entry.flag = ModifierEntryFlag_P1 | ModifierEntryFlag_P2;
					break;
				case ModifierFlagType_P1Only:
					entry.flag = ModifierEntryFlag_P1;
					break;
				case ModifierFlagType_P2Only:
					entry.flag = ModifierEntryFlag_P2;
					break;
				default:
					break;
				}
				m_ModifiersList.push_back(entry);
			}
			if (ImGui::Button("Add Random", { -FLT_MIN, 0 }))
			{
				std::uniform_int_distribution<int> random_dist(0, NUM_MODIFIERS);

				int randomID = random_dist(mt);

				ModifierEntry entry;
				entry.name = szModifiers[randomID];
				switch (flagType)
				{
				case ModifierFlagType_Both:
					entry.flag = ModifierEntryFlag_P1 | ModifierEntryFlag_P2;
					break;
				case ModifierFlagType_P1Only:
					entry.flag = ModifierEntryFlag_P1;
					break;
				case ModifierFlagType_P2Only:
					entry.flag = ModifierEntryFlag_P2;
					break;
				default:
					break;
				}
				m_ModifiersList.push_back(entry);
			}

			ImGui::Separator();
			unsigned int numModifiers = m_ModifiersList.size();
			if (numModifiers > 0)
			{
				ImGui::TextWrapped("Modifiers to activate:");
				ImGui::Separator();
				for (unsigned int i = 0; i < m_ModifiersList.size(); i++)
				{
					char modifierLabel[64] = {};
					sprintf(modifierLabel, "%d - %s##gm%d", i + 1, m_ModifiersList[i].name.c_str(), i);
					char* modifierLabelType = "##";
					if (m_ModifiersList[i].flag & ModifierEntryFlag_P1)
						modifierLabelType = "P1##";
					if (m_ModifiersList[i].flag & ModifierEntryFlag_P2)
						modifierLabelType = "P2##";
					if (m_ModifiersList[i].flag & ModifierEntryFlag_P1 && m_ModifiersList[i].flag & ModifierEntryFlag_P2)
						modifierLabelType = "Both##";
					ImGui::LabelText(modifierLabelType, modifierLabel);
				}
				if (ImGui::Button("Delete Last", { -FLT_MIN, 0 }))
				{
					m_ModifiersList.erase(m_ModifiersList.end() - 1);
				}
				if (ImGui::Button("Clear", { -FLT_MIN, 0 }))
				{
					m_ModifiersList.clear();
				}

			}



			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void DCF2Menu::DrawPlayerTab()
{
	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		ImGui::Checkbox("Change Player Speed", &m_bChangePlayerSpeed);
		ImGui::SliderFloat("Player 1", &m_fP1Speed, 0.0, 10.0f);
		ImGui::SliderFloat("Player 2", &m_fP2Speed, 0.0, 10.0f);
		if (ImGui::Button("Reset Speed"))
		{
			m_fP1Speed = 1.0f;
			m_fP2Speed = 1.0f;
			if (GetObj(PLAYER1))
				GetObj(PLAYER1)->SetSpeed(m_fP1Speed);
			if (GetObj(PLAYER2))
				GetObj(PLAYER2)->SetSpeed(m_fP1Speed);
		}

		ImGui::Checkbox("Change Player Scale", &m_bChangePlayerScale);
		ImGui::InputFloat3("Player 1 ", &m_vP1Scale.X);
		ImGui::InputFloat3("Player 2 ", &m_vP2Scale.X);

		if (ImGui::Button("Reset Scale"))
		{
			m_vP1Scale = { 1.0f,1.0f,1.0f };
			m_vP2Scale = { 1.0f,1.0f,1.0f };
			if (GetObj(PLAYER1))
				GetObj(PLAYER1)->SetScale(&m_vP1Scale);
			if (GetObj(PLAYER2))
				GetObj(PLAYER2)->SetScale(&m_vP2Scale);
		}


		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SameLine(); ShowHelpMarker("Read only!");
		if (GetObj(PLAYER1))
		{
			GetCharacterPosition(&plrPos, PLAYER1);
			ImGui::InputFloat3("X | Y | Z", &plrPos.X);
		}
		if (GetObj(PLAYER2))
		{
			GetCharacterPosition(&plrPos2, PLAYER2);
			ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
		}
	}
	else
		ImGui::Text("Player options are only available in-game!");
}

void DCF2Menu::DrawSpeedTab()
{
	ImGui::Text("Gamespeed");
	ImGui::SameLine(); ShowHelpMarker("Hotkey - F5");

	ImGui::InputFloat("Speed", &m_fSlowMotionSpeed, 0.1f);
	if (m_fSlowMotionSpeed > 2.0f) m_fSlowMotionSpeed = 2.0f;
	if (m_fSlowMotionSpeed < 0.0f) m_fSlowMotionSpeed = 0.0f;
	if (ImGui::Button("Apply"))
		SlowGameTimeForXTicks(m_fSlowMotionSpeed, 0x7FFFFFFF);
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
		SlowGameTimeForXTicks(m_fSlowMotionSpeed, 1);

	ImGui::Separator();
	ImGui::Text("Tick this checkbox if you want to freeze game with a button, this might cause\nissues with pause menus and stuff so enable only when needed!");
	ImGui::Checkbox("Hook Freeze World", &m_bHookDispatch);

	if (m_bHookDispatch)
	{
		ImGui::Checkbox("Freeze World", &m_bFreezeWorld);
		ImGui::SameLine();
		ShowHelpMarker("Hotkey - F2");
	}


}

void DCF2Menu::DrawCameraTab()
{
	ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
	ImGui::InputFloat3("X | Y | Z", &camPos.X);
	ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
	ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);

	ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
	ImGui::InputFloat("FOV", &camFov);

	ImGui::Separator();
	ImGui::Checkbox("Enable Free Camera", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with keyboard. Keys can be changed in the Settings menu or in the .ini file.");

	if (m_bFreeCam)
	{
		ImGui::InputFloat("Free Camera Speed", &m_fFreeCameraSpeed);
		ImGui::InputInt("Free Camera Rotation Speed", &m_nFreeCameraRotationSpeed);
		ImGui::Checkbox("Mouse Control", &m_bMouseControl);
	}




	ImGui::Separator();
	ImGui::Checkbox("Disable DOF", &m_bDisableDOF);
	ImGui::Checkbox("Force Camera To Move", &m_bForceCameraUpdate);
	ImGui::SameLine(); ShowHelpMarker("Check this option if camera doesn't move in cinematics.");

	ImGui::Separator();

	ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);
	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{

		if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
			{
				bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
				if (ImGui::Selectable(szCameraModes[n], is_selected))
					sprintf(szCurrentCameraOption, szCameraModes[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
		if (m_nCurrentCustomCamera == CAMERA_1STPERSON || m_nCurrentCustomCamera == CAMERA_1STPERSON_MID)
		{
			ImGui::InputFloat("FPS Camera Offset", &m_fAdjustCustomCameraY);
			ImGui::InputFloat("FPS Up/Down Offset", &m_fAdjustCustomCameraZ);
			ImGui::InputFloat("FPS Left/Right Offset", &m_fAdjustCustomCameraX);
		}
		else if (m_nCurrentCustomCamera == CAMERA_3RDPERSON)
		{
			ImGui::InputFloat("TPP Camera Offset", &m_fAdjustCustomCameraThirdPersonY);
			ImGui::InputFloat("TPP Up/Down Offset", &m_fAdjustCustomCameraThirdPersonZ);
			ImGui::InputFloat("TPP Left/Right Offset", &m_fAdjustCustomCameraThirdPersonX);
		}
		else if (m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING)
		{
			ImGui::InputFloat("Up/Down Angle Offset", &m_fAdjustCustomHeadCameraY);
			ImGui::InputFloat("Up/Down Offset", &m_fAdjustCustomHeadCameraZ);
			ImGui::InputFloat("Left/Right Offset", &m_fAdjustCustomHeadCameraX);

			ImGui::Checkbox("Don't Flip Camera", &m_bDontFlipCamera);
			ImGui::SameLine(); ShowHelpMarker("Use this option for head tracked cinematics.");
			ImGui::Checkbox("Use Player Two As Source", &m_bUsePlayerTwoAsTracker);
			ImGui::TextWrapped("Toggle 'Disable Head Tracking' in Misc. section first to use this mode properly. Toggle it at select screen.");
			ImGui::TextWrapped("Recommended to set FOV value to at least 110 to make this mode look right!");
		}
	}
	else
		ImGui::Text("Custom cameras will appear once in-game!");
}

void DCF2Menu::DrawCheatsTab()
{
	ImGui::Separator();
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 14 * ImGui::GetFontSize());

	ImGui::Text("Infinite Health");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
	ImGui::NextColumn();


	ImGui::Text("Zero Health\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
	ImGui::NextColumn();

	ImGui::Text("Infinite Meter\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##super", &m_bInfiniteMeterP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##super", &m_bInfiniteMeterP2);
	ImGui::NextColumn();

	ImGui::Text("Zero Meter\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##0super", &m_bZeroMeterP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##0super", &m_bZeroMeterP2);
	ImGui::NextColumn();

	ImGui::Text("Infinite Clashes\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##breakers", &m_bInfiniteBreakersP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##breakers", &m_bInfiniteBreakersP2);
	ImGui::Separator();

	ImGui::Columns(1);
}

void DCF2Menu::DrawMiscTab()
{
	if (ImGui::Button("Hide FightHUD"))
		HideHUD();
	ImGui::SameLine();
	if (ImGui::Button("Show FightHUD"))
		ShowHUD();

	ImGui::Checkbox("Hide FightHUD In Game", &m_bAutoHideHUD);

	if (ImGui::Checkbox("Disable HUD", &m_bHideHUD))
	{
		if (Scaleform::ms_bActive)
		{
			if (m_bHideHUD)
				*Scaleform::ms_bActive = false;
			else
				*Scaleform::ms_bActive = true;
		}
	}

	ImGui::Checkbox("Disable Head Tracking", &m_bDisableHeadTracking);
	ImGui::SameLine();
	ShowHelpMarker("Disables P1 head looking at P2. Automatically enabled with 'Head Perspective' custom camera.");

	ImGui::Checkbox("Disable Combo Scaling", &m_bDisableComboScaling);
}

void DCF2Menu::DrawScriptTab()
{
	enum EScriptTabMode {
		ScriptTab_Basic,
		ScriptTab_Advanced,
	};
	static int scriptMode = ScriptTab_Basic;


	ImGui::TextWrapped("Execution Type");
	ImGui::Separator();
	ImGui::RadioButton("On Player1", &m_nScriptExecuteType, SCRIPT_P1); ImGui::SameLine();
	ImGui::RadioButton("On Player2", &m_nScriptExecuteType, SCRIPT_P2);
	ImGui::Separator();

	static char szScriptSource[256] = {};
	ImGui::TextWrapped("Script Source (.MKO)");
	ImGui::SameLine();
	ShowHelpMarker(".MKO file names can be found in MKScript folder.");
	ImGui::PushItemWidth(-FLT_MIN);
	ImGui::InputText("##scriptsrc", szScriptSource, sizeof(szScriptSource));
	ImGui::PopItemWidth();

	static unsigned int voidArgsHash = _hash("void.");

	m_pScript = GetScript(szScriptSource);
	if (m_pScript)
	{
		ImGui::Separator();

		static int functionIndex = 0;
		static char szFunction[256] = {};
		static mko_function_header_mk10 lastFunction = {};
		static int hash = 0;

		if (scriptMode == ScriptTab_Basic)
		{
			ImGui::Text("Function List");
			static ImGuiTextFilter filter;
			ImGui::Text("Search");
			ImGui::PushItemWidth(-FLT_MIN);
			filter.Draw("##fnlist");
			ImGui::PopItemWidth();
			ImGui::BeginChild("##list", { 0, 125.0f }, true);
			{
				static int selectID = 0;
				for (int i = 0; i < m_pScript->numFunctions; i++)
				{
					if (m_pScript->functions[i]->functionName)
					{
						if (filter.PassFilter(m_pScript->functions[i]->functionName))
						{
							bool is_selected = (selectID == i);
							if (ImGui::Selectable(m_pScript->functions[i]->functionName, is_selected))
							{
								selectID = i;

								sprintf(szFunction, "%s", m_pScript->functions[i]->functionName);
								lastFunction = *m_pScript->functions[i];

							}
						}
					}


				}
			}
			ImGui::EndChild();
			if (strlen(szFunction) > 0)
			{
				ImGui::TextWrapped("Selected function: %s", szFunction);
				if (lastFunction.paramsHash == voidArgsHash)
					ImGui::TextColored(ImVec4(0.6, 1.0, 0.6, 1.0), "This function (probably) can be called.");
				else
					ImGui::TextColored(ImVec4(1.0, 0.6, 0.6, 1.0), "This function will probably crash the game.");
			}

		}

		static eScriptKeyBind bind;
		if (ImGui::Button("Add Hotkey"))
		{
			m_nHash = _hash(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			bind.functionHash = m_nHash;
			sprintf(bind.scriptName, "%s", szScriptSource);
			bind.type = (eScriptExecuteType)m_nScriptExecuteType;

			m_bPressingKey = true;
		}

		if (m_bPressingKey)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				bind.key = result;
				m_vKeyBinds.push_back(bind);
				m_bPressingKey = false;
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Run"))
		{
			m_nHash = _hash(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			RunLastScript();
		}
	}
	else
	{
		if (strlen(szScriptSource) > 0)
			ImGui::TextWrapped("Cannot load %s!", szScriptSource);
	}


	ImGui::Separator();
	ImGui::TextWrapped("Registered hotkeys:");
	for (unsigned int i = 0; i < m_vKeyBinds.size(); i++)
	{
		ImGui::TextWrapped("%s - Run [0x%X] from %s", eKeyboardMan::KeyToString(m_vKeyBinds[i].key), m_vKeyBinds[i].functionHash, m_vKeyBinds[i].scriptName);
	}

	if (ImGui::Button("Clear All"))
		m_vKeyBinds.clear();
}

void DCF2Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 35 * ImGui::GetFontSize(), 35 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys",
		"Mouse"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
		MOUSE
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to i2hook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("##", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:
		ImGui::TextWrapped("These settings control I2Hook.ini options. Any changes require game restart to take effect.");
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		ImGui::Checkbox("Gamepad Support", &SettingsMgr->bEnableGamepadSupport);
		ImGui::Checkbox("60 FPS Patch", &SettingsMgr->bEnable60FPSFrontend);
		ImGui::Checkbox("Disable TOC Checks", &SettingsMgr->bDisableTOCChecks);
		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Keys reset! Remember to save.");

		}
		ImGui::Separator();
		ImGui::LabelText("##", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iToggleSlowMoKey, "Toggle Gamespeed/Slow Motion", "slomo");
		KeyBind(&SettingsMgr->iToggleFreezeWorldKey, "Freeze World", "freeze");
		ImGui::Separator();
		ImGui::LabelText("##", "Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyForward, "Forward", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyBackward, "Back", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyLeft, "Left", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRight, "Right", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyUp, "Up", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyDown, "Down", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("##", "Misc");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleFreeCameraKey, "Toggle Free Camera", "fcam");
		KeyBind(&SettingsMgr->iToggleHUDKey, "Toggle HUD", "thud");
		KeyBind(&SettingsMgr->iToggleCustomCamKey, "Toggle Custom Cameras", "ccam");
		KeyBind(&SettingsMgr->iResetStageInteractablesKey, "Reset Stage Objects", "r_stage");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	case MOUSE:
		ImGui::TextWrapped("All user settings are saved to i2hook_user.ini.");
		ImGui::Text("Sensitivity");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::SliderInt("##", &SettingsMgr->mouse.sens, 1, 50);
		ImGui::PopItemWidth();
		ImGui::Checkbox("Invert X", &SettingsMgr->mouse.invert_x);
		ImGui::Checkbox("Invert Y", &SettingsMgr->mouse.invert_y);
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to I2Hook.ini and i2hook_user.ini!");
		GUIImplementation::RequestFontReload();
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void DCF2Menu::DrawScriptReference()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 35 * ImGui::GetFontSize(), 35 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Script Reference", &m_bSubmenuActive[SUBMENU_SCRIPT]);

	static int secID = 0;
	static const char* scriptSections[] = {
		"General",
		"Usage",
	};

	enum eScriptRef {
		GEN,
		USG,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(scriptSections); n++)
	{
		bool is_selected = (secID == n);
		if (ImGui::Selectable(scriptSections[n], is_selected))
			secID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (secID)
	{
	case GEN:
		ImGui::TextWrapped("You can find script functions in the MKScript folder. Open .mko file of interest with notepad or"
			" any hex editor. To find functions that can be executed look for strings starting with 'Rx', 'pFunc','p'.");
		break;
	case USG:
		ImGui::BulletText("On Player1 - selected function will execute on Player 1 object.\nUse with character scripts or FightEngine");
		ImGui::BulletText("On Player2 - selected function will execute on Player 2 object.\nUse with character scripts or FightEngine");

		ImGui::TextWrapped("Some common player functions:");
		ImGui::BulletText("RoundOverWinnerTaunt");
		ImGui::BulletText("RoundOverWinnerTauntOne");
		ImGui::BulletText("RoundOverWinnerTauntTwo");

		ImGui::TextWrapped("Some common FightEngine.mko functions:");
		ImGui::BulletText("RxIceBall");
		break;
	default:
		break;
	}

	ImGui::EndChild();

	ImGui::End();
}

void DCF2Menu::DrawAnimationTool()
{
	AnimationTool::Draw();
}

void DCF2Menu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}
}

void DCF2Menu::KeyBind(int* var, char* bindName, char* name)
{
	ImGui::LabelText("", bindName);
	DrawKeyBind(name, var);
}

#ifdef _DEBUG
void DCF2Menu::DrawDebug()
{
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
	ImGui::SetNextWindowPos(ImVec2(10, 5));
	ImGui::Begin("devtext", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::PopStyleVar(1);
	ImGui::Text("I2Hook %s Debug (%.2f FPS)", I2HOOK_VERSION, ImGui::GetIO().Framerate);
	ImGui::Text("");
	ImGui::Text("Player 1 Object: 0x%p Info: 0x%p", GetObj(PLAYER1), GetInfo(PLAYER1));
	ImGui::Text("Player 2 Object: 0x%p Info: 0x%p", GetObj(PLAYER2), GetInfo(PLAYER2));
	if (GetObj(PLAYER1))
	ImGui::Text("Player 1 Skeleton: 0x%p", GetObj(PLAYER1)->GetSkeleton());
	ImGui::Text("P1: %s", GetCharacterName(PLAYER1));
	ImGui::Text("P2: %s", GetCharacterName(PLAYER2));
	ImGui::End();
}
#endif

bool DCF2Menu::GetActiveState()
{
	return m_bIsActive;
}

void DCF2Menu::RunLastScript()
{
	if (m_pScript->GetFunctionID(m_nHash))
	{
		switch (m_nScriptExecuteType)
		{
		case SCRIPT_P1:
			GetObj(PLAYER1)->ExecuteScript(m_pScript, m_nHash);
			break;
		case SCRIPT_P2:
			GetObj(PLAYER2)->ExecuteScript(m_pScript, m_nHash);
			break;
		default:
			break;
		}
	}
	else
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("Function %x does not exist!", m_nHash);
	}
}

void DCF2Menu::ProcessScriptHotkeys()
{
	for (int i = 0; i < m_vKeyBinds.size(); i++)
	{
		if (GetAsyncKeyState(m_vKeyBinds[i].key) & 0x1)
		{
			MKScript* script = GetScript(m_vKeyBinds[i].scriptName);
			if (script->GetFunctionID(m_vKeyBinds[i].functionHash))
			{
				switch (m_vKeyBinds[i].type)
				{
				case SCRIPT_P1:
					GetObj(PLAYER1)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				case SCRIPT_P2:
					GetObj(PLAYER2)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				default:
					break;
				}
			}
			else
			{
				Notifications->SetNotificationTime(3500);
				Notifications->PushNotification("Function %x does not exist!", m_vKeyBinds[i].functionHash);
			}
		}
	}
}

char * GetI2HookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "I2Hook by ermaccer (%s)", I2HOOK_VERSION);
	return buffer;
}
