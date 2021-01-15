#include "dcf2menu.h"
#include <Windows.h>
#include <iostream>
#include "..\imgui\imgui.h"
#include "..\code\mk10utils.h"
#include "dcf2.h"
#include <windows.h>
#include "eSettingsManager.h"

static int64 timer = GetTickCount64();

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

	bFocused = false;
}

void DCF2Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin("I2Hook by ermaccer (0.1)");

	if (ImGui::Button("Speed Modifier")) iCurrentTab = TAB_SPEED;

	if (SettingsMgr->bHookCamera)
	{
		ImGui::SameLine();
		if (ImGui::Button("Camera Control")) iCurrentTab = TAB_CAMERA;
	}

	ImGui::Separator();

	if (iCurrentTab == TAB_SPEED)
	{
		ImGui::Text("Gamespeed Control");
		ImGui::SameLine(); ShowHelpMarker("Hotkey - F5");

		ImGui::InputFloat("Speed", &fSlowMotionSpeed, 0.1);
		if (fSlowMotionSpeed > 2.0f) fSlowMotionSpeed = 2.0f;
		if (fSlowMotionSpeed < 0.0f) fSlowMotionSpeed = 0.0f;
		if (ImGui::Button("Apply"))
			DCF2::SlowGameTimeForXTicks(fSlowMotionSpeed, 0x7FFFFFFF);
		ImGui::SameLine();
		if (ImGui::Button("Reset"))
			DCF2::SlowGameTimeForXTicks(fSlowMotionSpeed, 1);


	}
	if (iCurrentTab == TAB_CAMERA)
	{

		ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
		ImGui::InputFloat3("X | Y | Z", &camPos.X);
		ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
		ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);

		ImGui::Checkbox("Custom FOV", &bCustomFOV);
		ImGui::InputFloat("FOV", &camFov);
		
		ImGui::Separator();
		ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
		ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
		ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
		ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);

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
	if (GetAsyncKeyState(VK_F1))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bIsActive ^= 1;
	}

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
			float newVal = TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = newVal;


			float newValY = TheMenu->camRot.Pitch;

			if (bInvertMouseY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = newValY;
		}
	}
}

bool DCF2Menu::GetActiveState()
{
	return bIsActive;
}
