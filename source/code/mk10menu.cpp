#include "mk10menu.h"
#include "mk10utils.h"
#include <iostream>
#include <Windows.h>
#include <imgui.h>
#include "eSettingsManager.h"

bool bShowMessageError = 0;

// TODO: replace with auto scan?

const char* szCharacters[] = {
	// place npcs first for easy access
	"Rain_A",
	"Baraka_A",
	"Sindel_A",
	"Tanya_A",
	"ShinnokBoss_A",
	// rest of the cast
	"CHAR_Alien_A",
	"char_aztec_a", "CHAR_Aztec_B", "CHAR_Aztec_E",
	"CHAR_BoRaiChoDLC_A",
	"char_cagejr_a", "CHAR_CageJr_B", "CHAR_CageJr_N", "CHAR_CageJr_O",
	"CHAR_Ermac_A", "CHAR_Ermac_B","CHAR_Ermac_H","CHAR_Ermac_N","CHAR_Ermac_V",
	"Char_Goro_A",
	"CHAR_Jason_A",
	"CHAR_JaxJr_A", "CHAR_JaxJr_B","CHAR_JaxJr_N","CHAR_JaxJr_O",
	"CHAR_Jax_A", "CHAR_Jax_B", "CHAR_Jax_C", "CHAR_Jax_M", "CHAR_Jax_P", "CHAR_Jax_Y",
	"CHAR_JohnnyCage_A", "CHAR_JohnnyCage_B","CHAR_JohnnyCage_C","CHAR_JohnnyCage_M", "CHAR_JohnnyCage_P","CHAR_JohnnyCage_Z",
	"CHAR_Kano_A","CHAR_Kano_B","CHAR_Kano_K","CHAR_Kano_T",
	"CHAR_KenshiJr_A","CHAR_KenshiJr_B","CHAR_KenshiJr_L",
	"CHAR_Kenshi_A","CHAR_Kenshi_B","CHAR_Kenshi_F",
	"CHAR_Kitana_A","CHAR_Kitana_B","CHAR_Kitana_C","CHAR_Kitana_E","CHAR_Kitana_F","CHAR_Kitana_M",
	"CHAR_KungLaoJr_A","CHAR_KungLaoJr_B","CHAR_KungLaoJr_E",
	"CHAR_KungLao_A","CHAR_KungLao_B","CHAR_KungLao_C","CHAR_KungLao_Y","CHAR_KungLao_Z",
	"char_ladybug_a","CHAR_LadyBug_B","char_ladybug_L",
	"CHAR_LeatherFace_A","CHAR_LeatherFace_B","CHAR_LeatherFace_C",
	"CHAR_LiuKang_A","CHAR_LiuKang_B","CHAR_LiuKang_C","CHAR_LiuKang_E","CHAR_LiuKang_T","CHAR_LiuKang_Z",
	"CHAR_MasterMale_A","CHAR_MasterMale_B","CHAR_MasterMale_E",
	"CHAR_Mileena_A","CHAR_Mileena_B","CHAR_Mileena_C","CHAR_Mileena_H","CHAR_Mileena_M",
	"CHAR_Nomad_A","CHAR_Nomad_B","CHAR_Nomad_L",
	"CHAR_Predator_A",
	"CHAR_QuanChi_A","CHAR_QuanChi_B","CHAR_QuanChi_Y",
	"CHAR_Raiden_A","CHAR_Raiden_B","CHAR_Raiden_C","CHAR_Raiden_I",
	"CHAR_Reptile_A","CHAR_Reptile_B","CHAR_Reptile_H","CHAR_Reptile_N",
	"char_scorpion_a","CHAR_Scorpion_B","CHAR_Scorpion_C","CHAR_Scorpion_J","CHAR_Scorpion_M","CHAR_Scorpion_N","CHAR_Scorpion_P","CHAR_Scorpion_V",
	"CHAR_Shinnok_A","CHAR_Shinnok_B","CHAR_Shinnok_F",
	"CHAR_Sonya_A","CHAR_Sonya_B","CHAR_Sonya_C","CHAR_Sonya_K","CHAR_Sonya_T",
	"char_subzero_a","CHAR_SubZero_B","CHAR_SubZero_C","CHAR_SubZero_K","CHAR_SubZero_N","CHAR_SubZero_V",
	"CHAR_TanyaDLC_A",
	"CHAR_Tremor_A",
	"Char_Triborg_A",


};

static int64 timer = GetTickCount64();

MK10Menu* TheMenu = new MK10Menu();

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


void MK10Menu::Initialize()
{
	bIsActive = false;
	iCurrentTab = 0;

	printf("I2Hook::Initialize() | Menu initialize\n");
}

void MK10Menu::Process()
{
	UpdateControls();
}

void MK10Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin("I2Hook by ermaccer");
	if (ImGui::Button("Cheats")) iCurrentTab = TAB_CHEATS;


	if (iCurrentTab == TAB_CHEATS)
	{
	}
	ImGui::End();
}

void MK10Menu::UpdateControls()
{
	if (GetAsyncKeyState(VK_F1))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bIsActive ^= 1;
	}
}

bool MK10Menu::GetActiveState()
{
	return bIsActive;
}

void PushErrorMessage(const char * message)
{
	if (!bShowMessageError)
	{
		bShowMessageError = true;
		ImGui::Begin("ERROR", &bShowMessageError);
		ImGui::Text(message);
		if (ImGui::Button("OK"))
			bShowMessageError = false;
		ImGui::End();
	}

}
