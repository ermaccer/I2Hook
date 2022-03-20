#include "dcf2menu.h"
#include <Windows.h>
#include <iostream>
#include "..\imgui\imgui.h"
#include "..\code\mk10utils.h"
#include "dcf2.h"
#include <windows.h>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCharacter.h"
#include "helper/eKeyboardMan.h"
#include "..\eDirectX11Hook.h"


static int64 timer = GetTickCount64();
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
	"Char_Template",
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
const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid",
	"Mortal Kombat 11",
	"Head Perspective"
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


void DCF2Menu::Initialize()
{
	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;

	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szPlayer1Bone, szBones[0]);
	sprintf(szPlayer2Bone, szBones[0]);
}

void DCF2Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetI2HookVersion(), &m_bIsActive, ImGuiWindowFlags_MenuBar);


	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Script Reference"))
				m_bSubmenuActive[SUBMENU_SCRIPT] = true;
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			DrawCharacterTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{
			DrawStageTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Modifiers"))
		{
			DrawModifiersTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
		{
			DrawPlayerTab();
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
}

void DCF2Menu::Process()
{
	UpdateControls();
	if (m_bIsFocused && m_bFreeCamMouseControl)
		UpdateMouse();
}

void DCF2Menu::UpdateControls()
{
	if (!m_bIsActive)
	{
		if (GetAsyncKeyState(SettingsMgr->iToggleCustomCamKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				m_bCustomCameras ^= 1;
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Custom cameras can only be activated in game!");
			}
		}
		if (GetAsyncKeyState(SettingsMgr->iResetStageInteractablesKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				GetGameInfo()->ResetStageInteractables();
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Stage objects can only be reset in game!");
			}
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleSlowMoKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			TheMenu->m_bSlowMotion ^= 1;
			if (TheMenu->m_bSlowMotion)
				SlowGameTimeForXTicks(m_fSlowMotionSpeed, 0x7FFFFFFF);
			else
				SlowGameTimeForXTicks(1.0, 10);
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleFreezeWorldKey))
		{
			if (m_bHookDispatch)
			{
				if (GetTickCount64() - timer <= 150) return;
				timer = GetTickCount64();
				m_bFreezeWorld ^= 1;
			}
		}
		ProcessScriptHotkeys();
	}

}

void DCF2Menu::UpdateMouse()
{
	if (m_bIsActive) return;

	GetCursorPos(&curMouse);
	mouseSpeedX = curMouse.x - orgMouse.x;
	mouseSpeedY = curMouse.y - orgMouse.y;


	if (m_bIsFocused)
	{
		if (TheMenu->m_bFreeCam)
		{
			float newVal = (float)TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = (int)newVal;


			float newValY = (float)TheMenu->camRot.Pitch;

			if (m_bFreeCamMouseInvertY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = (int)newValY;
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
		if (ImGui::BeginTabItem("Abilities"))
		{
			ImGui::Checkbox("Player 1 Custom Abilities", &m_bP1CustomAbilities);
			ImGui::SameLine(); ShowHelpMarker("Set these on select screen! Changing these in game might make moves locked. Hold L SHIFT to view numeric value.");
			ImGui::Separator();


			for (int i = 0; i < sizeof(m_P1Abilities) / sizeof(m_P1Abilities[0]); i++)
			{
				int val = (int)pow(2, i);
				if (GetAsyncKeyState(VK_LSHIFT))
					sprintf(textBuffer, "Ability %d (%d)", i + 1, val);
				else
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
				int val = (int)pow(2, i);
				if (GetAsyncKeyState(VK_LSHIFT))
					sprintf(textBuffer, "Ability %d (%d)##p2", i + 1, val);
				else
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
					Notifications->SetNotificationTime(2500);
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
		/*if (ImGui::BeginTabItem("Blood"))
		{
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				static int bloodType = 0;
				static FVector bloodPos = {};
				static bool bloodBoneAttach = false;
				static float bloodAngle = 0, bloodSize = 0, bloodSpeed = 0;
				ImGui::TextWrapped("Blood FX Params");
				ImGui::InputInt("Type", &bloodType);
				ImGui::InputFloat3("Position", &bloodPos.X);
				ImGui::InputFloat("Angle", &bloodAngle);
				ImGui::InputFloat("Size", &bloodSize);
				ImGui::InputFloat("Speed", &bloodSpeed);
				static char bloodName[64] = {};
				ImGui::InputText("Bone Name", bloodName, sizeof(bloodName));
				ImGui::Checkbox("Bone Attach", &bloodBoneAttach);

				static int bloodForWho = 0;
				ImGui::RadioButton("Player1", &bloodForWho, 0); ImGui::SameLine();
				ImGui::RadioButton("Player2", &bloodForWho, 1);

				if (ImGui::Button("Spawn"))
				{
					FName bone(bloodName, FNAME_Add, 1);
					if (bloodForWho)
						GetObj(PLAYER2)->BloodEffect(bloodType, bone, bloodPos.X, bloodPos.Y,bloodPos.Z, bloodAngle, bloodSize, bloodSpeed, bloodBoneAttach);
					else
						GetObj(PLAYER1)->BloodEffect(bloodType, bone, bloodPos.X, bloodPos.Y, bloodPos.Z, bloodAngle, bloodSize, bloodSpeed, bloodBoneAttach);
				}


			} 
			else
				ImGui::TextWrapped("Blood options are only available in-game!");

			ImGui::EndTabItem();
		}
		*/
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
	ImGui::Text("Gamespeed Control");
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
	ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

	if (m_bFreeCam)
	{
		if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

		ImGui::InputFloat("Freecam Speed", &m_fFreeCameraSpeed);
		ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);

		ImGui::Separator();
		ImGui::Checkbox("Mouse Control", &m_bFreeCamMouseControl);

		if (m_bFreeCamMouseControl)
		{
			ImGui::SameLine();  ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "This feature is not yet finished!");
			ImGui::Checkbox("Invert Y", &m_bFreeCamMouseInvertY);
			ImGui::SliderInt("Mouse Smoothness", &mouseSens, 1, 15);
		}
	}




	ImGui::Separator();
	ImGui::Checkbox("Force Camera To Move", &m_bForceCameraUpdate);
	ImGui::SameLine(); ShowHelpMarker("Check this option if you can't move camera anymore in win poses and some cinematics.");


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
	ImGui::SetColumnWidth(0, 11.5f * ImGui::GetFontSize());

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
	ImGui::Checkbox("Disable HUD Completely", &m_bDisableHUD);
	ImGui::SameLine();
	ShowHelpMarker("You'll need to go in-game/back to menu for this option to take effect.");
	ImGui::Checkbox("Disable Head Tracking", &m_bDisableHeadTracking);
	ImGui::SameLine();
	ShowHelpMarker("Disables P1 head looking at P2. Automatically enabled with 'Head Perspective' custom camera.");

	ImGui::Checkbox("Disable Combo Scaling", &m_bDisableComboScaling);
}

void DCF2Menu::DrawScriptTab()
{
	ImGui::RadioButton("On Player1", &m_nScriptExecuteType, SCRIPT_P1); ImGui::SameLine();
	ImGui::RadioButton("On Player2", &m_nScriptExecuteType, SCRIPT_P2);

	static char szScriptSource[256] = {};
	ImGui::InputText("Script Source", szScriptSource, sizeof(szScriptSource));
	ImGui::Separator();

	m_pScript = GetScript(szScriptSource);
	if (m_pScript)
	{
		static int functionIndex = 0;
		static char szFunction[256] = {};

		static int hash = 0;
		ImGui::TextWrapped("Functions with params are not supported!");

		ImGui::InputText("Function Name", szFunction, sizeof(szFunction));
		ImGui::InputInt("Function Index", &functionIndex, 1, 100, ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine(); ShowHelpMarker("Read only.");

		static eScriptKeyBind bind;
		if (ImGui::Button("Add Hotkey"))
		{
			m_nHash = HashString(szFunction);
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
			m_nHash = HashString(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			RunLastScript();
		}

	}
	else
	{
		if (strlen(szScriptSource) > 0)
			ImGui::TextWrapped("%s not available!", szScriptSource);
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
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
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
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		break;
	case INI:
		ImGui::TextWrapped("These settings control I2Hook.ini options. Any changes require game restart to take effect.");
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		ImGui::Checkbox("Gamepad Support", &SettingsMgr->bEnableGamepadSupport);
		ImGui::Checkbox("60 FPS Patch", &SettingsMgr->bEnable60FPSFrontend);
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
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iToggleSlowMoKey, "Toggle Gamespeed/Slow Motion", "slomo");
		KeyBind(&SettingsMgr->iToggleFreezeWorldKey, "Freeze World", "freeze");
		ImGui::Separator();
		ImGui::LabelText("", "Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyXPlus, "X+", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyXMinus, "X-", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYPlus, "Y+", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYMinus, "Y-", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZPlus, "Z+", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZMinus, "Z-", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("", "Misc");
		ImGui::Separator();
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
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to I2Hook.ini and i2hook_user.ini!");
		eDirectX11Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void DCF2Menu::DrawScriptReference()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
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
	ImGui::Text("Player 1 Object: 0x%X Info: 0x%X", GetObj(PLAYER1), GetInfo(PLAYER1));
	ImGui::Text("Player 2 Object: 0x%X Info: 0x%X", GetObj(PLAYER2), GetInfo(PLAYER2));
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
