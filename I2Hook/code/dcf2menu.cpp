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

static int64 timer = GetTickCount64();
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
	"Mortal Kombat 11"
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
	m_bPlayer1Modifier = false;
	m_bPlayer2Modifier = false;
	m_bSlowMotion = false;
	m_fSlowMotionSpeed = 0.5f;
	m_bCustomCameraPos = false;
	m_bCustomCameraRot = false;
	m_bCustomCameraFOV = false;
	m_bSlowMotion = 0;
	m_fSlowMotionSpeed = 0.5f;
	m_fFreeCameraSpeed = 5.25f;
	m_nFreeCameraRotationSpeed = 120;
	m_bIsActive = false;

	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	mouseSens = 5;
	m_bFreeCamMouseInvertY = true;

	m_bInfiniteHealthP1 = false;
	m_bInfiniteHealthP2 = false;
	m_bNoHealthP1 = false;
	m_bNoHealthP2 = false;

	m_bCustomCameras = false;
	m_nCurrentCustomCamera = -1;
	m_bStageModifier = false;
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	m_fAdjustCustomCameraZ = 161.0f;
	m_fAdjustCustomCameraX = -10.0f;
	m_fAdjustCustomCameraThirdPersonY = 0;
	m_fAdjustCustomCameraThirdPersonX = 0;
	m_fAdjustCustomCameraThirdPersonZ = 0;
	m_bYObtained = false;
	m_bIsFocused = false;
	m_bForceCameraUpdate = false;
	m_bDisableHUD = false;
	m_bAutoHideHUD = false;
	m_bChangePlayerSpeed = false;
	m_bChangePlayerScale = false;
	m_fP1Speed = 1.0f;
	m_fP2Speed = 1.0f;
	m_vP1Scale = { 1.0f,1.0f,1.0f };
	m_vP2Scale = { 1.0f,1.0f,1.0f };
	m_bFreezeWorld = false;
	m_bHookDispatch = false;

	m_bInfiniteBreakersP1 = false;
	m_bInfiniteBreakersP2 = false;
	m_bZeroMeterP1 = false;
	m_bZeroMeterP2 = false;
}

void DCF2Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetI2HookVersion(),&m_bIsActive);

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
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

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
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
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
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


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
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
			ImGui::SameLine(); ShowHelpMarker("Check this option if the game you can't move camera anymore in win poses and some cinematics.");


			ImGui::Separator();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);

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
			}
			else
				ImGui::Text("Custom cameras will appear once in-game!");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
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

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Separator();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 150);

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

			ImGui::EndTabItem();


		}
		if (ImGui::BeginTabItem("Misc."))
		{
			ImGui::Checkbox("Disable HUD Completely", &m_bDisableHUD);
			ImGui::SameLine();
			ShowHelpMarker("You'll need to go in-game/back to menu for this option to take effect.");
			ImGui::EndTabItem();
		}


		ImGui::EndTabBar();
	}
}

void DCF2Menu::Process()
{
	UpdateControls();
	if (m_bIsFocused && m_bFreeCamMouseControl)
		UpdateMouse();
}

void DCF2Menu::UpdateControls()
{
	if (GetAsyncKeyState(VK_F5))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		TheMenu->m_bSlowMotion ^= 1;
		if (TheMenu->m_bSlowMotion)
			SlowGameTimeForXTicks(m_fSlowMotionSpeed, 0x7FFFFFFF);
		else
			SlowGameTimeForXTicks(1.0, 10);
	}

	if (GetAsyncKeyState(VK_F2))
	{
		if (m_bHookDispatch)
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			m_bFreezeWorld ^= 1;
		}
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

bool DCF2Menu::GetActiveState()
{
	return m_bIsActive;
}

char * GetI2HookVersion()
{
	char buffer[512];
	sprintf(buffer, "I2Hook by ermaccer (%s)", I2HOOK_VERSION);
	return buffer;
}
