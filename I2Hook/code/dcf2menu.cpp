#include "dcf2menu.h"
#include <Windows.h>
#include <iostream>
#include "..\imgui\imgui.h"
#include "..\code\mk10utils.h"
#include "dcf2.h"
#include <windows.h>
#include "eSettingsManager.h"
#include "eNotifManager.h"

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
	bPlayer1ModifierEnabled = false;
	bPlayer2ModifierEnabled = false;

	bSlowMotionEnabled = false;
	iSlowMotionTicks = 100;
	fSlowMotionSpeed = 0.5f;
	bCustomCamera = false;
	bCustomCameraRot = false;
	bCustomFOV = false;
	iCurrentTab = 0;
	bSlowMotionEnabled = 0;
	fSlowMotionSpeed = 0.5f;
	fFreeCameraSpeed = 5.25f;
	iFreeCameraRotSpeed = 120;
	bIsActive = false;

	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	mouseSens = 5;
	bInvertMouseY = true;

	bInfiniteHealthPlayer1 = false;
	bInfiniteHealthPlayer2 = false;
	bNoHealthPlayer1 = false;
	bNoHealthPlayer2 = false;

	bEnableCustomCameras = false;
	iCurrentCustomCamera = -1;
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	fAdjustCamZ = 161.0f;
	fAdjustCamX = -10.0f;
	fAdjustCam3 = 0;
	fAdjustCamX3 = 0;
	fAdjustCamZ3 = 0;
	bYObtained = false;
	bFocused = false;
	bForceMoveCamera = false;
	bForceDisableHUD = false;
}

void DCF2Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetI2HookVersion());


	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			ImGui::Checkbox("Enable Player 1 Modifier", &bPlayer1ModifierEnabled);

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
			ImGui::Checkbox("Enable Player 2 Modifier", &bPlayer2ModifierEnabled);

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
		if (ImGui::BeginTabItem("Speed Modifier"))
			{
				ImGui::Text("Gamespeed Control");
				ImGui::SameLine(); ShowHelpMarker("Hotkey - F5");

				ImGui::InputFloat("Speed", &fSlowMotionSpeed, 0.1f);
				if (fSlowMotionSpeed > 2.0f) fSlowMotionSpeed = 2.0f;
				if (fSlowMotionSpeed < 0.0f) fSlowMotionSpeed = 0.0f;
				if (ImGui::Button("Apply"))
					DCF2::SlowGameTimeForXTicks(fSlowMotionSpeed, 0x7FFFFFFF);
				ImGui::SameLine();
				if (ImGui::Button("Reset"))
					DCF2::SlowGameTimeForXTicks(fSlowMotionSpeed, 1);
				ImGui::EndTabItem();
			}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);

			ImGui::Checkbox("Custom FOV", &bCustomFOV);
			ImGui::InputFloat("FOV", &camFov);

			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
			ImGui::SameLine(); ShowHelpMarker("Requires all toggles enabled!\nYou can configure keys in .ini file.");
			ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
			ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);



			ImGui::Separator();
			ImGui::Text("Check this option if the game you can't move camera anymore win poses.");
			ImGui::Checkbox("Force Camera To Move", &bForceMoveCamera);


			if (bFreeCameraMovement)
			{
				ImGui::Separator();
				ImGui::Checkbox("Mouse Control", &bEnableMouseControl);

				if (bEnableMouseControl)
				{
					ImGui::Checkbox("Invert Y", &bInvertMouseY);
					ImGui::SliderInt("Mouse Smoothness", &mouseSens, 1, 15);
				}
			}

			ImGui::Separator();
			if (DCF2::GetCharacterObject(PLAYER1) && DCF2::GetCharacterObject(PLAYER2))
			{
				ImGui::Checkbox("Custom Cameras", &bEnableCustomCameras);

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
				iCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
				if (iCurrentCustomCamera == CAMERA_1STPERSON || iCurrentCustomCamera == CAMERA_1STPERSON_MID)
				{
					ImGui::InputFloat("FPS Camera Offset", &fAdjustCam);
					ImGui::InputFloat("FPS Up/Down Offset", &fAdjustCamZ);
					ImGui::InputFloat("FPS Left/Right Offset", &fAdjustCamX);
				}
				else if (iCurrentCustomCamera == CAMERA_3RDPERSON)
				{
					ImGui::InputFloat("TPP Camera Offset", &fAdjustCam3);
					ImGui::InputFloat("TPP Up/Down Offset", &fAdjustCamZ3);
					ImGui::InputFloat("TPP Left/Right Offset", &fAdjustCamX3);
				}
			}
			else
				ImGui::Text("Custom cameras will appear once ingame!");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
			{

				ImGui::Text("Position");
				ImGui::SameLine(); ShowHelpMarker("Preview only!");
				if (DCF2::GetCharacterObject(PLAYER1))
				{
					DCF2::GetCharacterPosition(&plrPos, PLAYER1);
					ImGui::InputFloat3("X | Y | Z", &plrPos.X);
				}
				if (DCF2::GetCharacterObject(PLAYER2))
				{
					DCF2::GetCharacterPosition(&plrPos2, PLAYER2);
					ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
				}
				ImGui::EndTabItem();
			}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Text("Player 1");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health", &bInfiniteHealthPlayer1);
			ImGui::Checkbox("Zero Health", &bNoHealthPlayer1);

			ImGui::Separator();

			ImGui::Text("Player 2");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health ", &bInfiniteHealthPlayer2);
			ImGui::Checkbox("Zero Health ", &bNoHealthPlayer2);

			ImGui::Separator();

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc."))
		{
			ImGui::Checkbox("Disable HUD Completely", &bForceDisableHUD);
			ImGui::SameLine();
			ShowHelpMarker("You'll need to go in-game/back to menu for this option to take effect.");

			ImGui::EndTabItem();
		}
	}
}

void DCF2Menu::Process()
{
	UpdateControls();
	if (bFocused && bEnableMouseControl)
		UpdateMouse();
}

void DCF2Menu::UpdateControls()
{
	if (GetAsyncKeyState(VK_F5))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		TheMenu->bSlowMotionEnabled ^= 1;
		if (TheMenu->bSlowMotionEnabled)
			DCF2::SlowGameTimeForXTicks(fSlowMotionSpeed, 0x7FFFFFFF);
		else
			DCF2::SlowGameTimeForXTicks(1.0, 10);
	}

}

void DCF2Menu::UpdateMouse()
{
	if (bIsActive) return;

	GetCursorPos(&curMouse);
	mouseSpeedX = curMouse.x - orgMouse.x;
	mouseSpeedY = curMouse.y - orgMouse.y;


	if (bFocused)
	{
		if (TheMenu->bFreeCameraMovement)
		{
			float newVal = (float)TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = (int)newVal;


			float newValY = (float)TheMenu->camRot.Pitch;

			if (bInvertMouseY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = (int)newValY;
		}
	}
}

bool DCF2Menu::GetActiveState()
{
	return bIsActive;
}

void DCF2Menu::EditCharacter(PLAYER_NUM plr)
{
	int64 info = DCF2::GetCharacterInfo(plr);
	if (info)
	{
		ImGui::Text("Name:");
		ImGui::SameLine();
		ImGui::Text(DCF2::GetCharacterName(plr));
		int& level = *(int*)(info + 324);

		ImGui::InputInt("Level", &level);
	}
}

char * GetI2HookVersion()
{
	char buffer[512];
	sprintf(buffer, "I2Hook by ermaccer (%s)",I2HOOK_VERSION);
	return buffer;
}
