#pragma once
#include "..\mk\Engine.h"
#ifndef _60_ONLY
extern "C" {
	__declspec(dllexport) bool I2HOOK_GetMenuActive();
	__declspec(dllexport) MKCharacter* I2HOOK_GetCharacterObject(PLAYER_NUM id);
	__declspec(dllexport) PlayerInfo* I2HOOK_GetPlayerInfo(PLAYER_NUM id);
	__declspec(dllexport) FGGameInfo* I2HOOK_GetGameInfo();
	__declspec(dllexport) void I2HOOK_ImGui_Text(const char* text);
	__declspec(dllexport) bool I2HOOK_ImGui_Checkbox(const char* text, bool* value);
	__declspec(dllexport) bool I2HOOK_ImGui_Button(const char* text);
	__declspec(dllexport) bool I2HOOK_ImGui_InputInt(const char* text, int* value);
	__declspec(dllexport) bool I2HOOK_ImGui_InputFloat(const char* text, float* value);
	__declspec(dllexport) bool I2HOOK_ImGui_InputText(const char* label, char* buff, size_t size);
	__declspec(dllexport) bool I2HOOK_ImGui_BeginCombo(const char* label, const char* previewValue);
	__declspec(dllexport) void I2HOOK_ImGui_EndCombo();
	__declspec(dllexport) bool I2HOOK_ImGui_Selectable(const char* label, bool selected);
	__declspec(dllexport) void I2HOOK_ImGui_SetItemDefaultFocus();
	__declspec(dllexport) void I2HOOK_ImGui_Separator();
	__declspec(dllexport) bool I2HOOK_ImGui_CollapsingHeader(const char* label);
}
#endif