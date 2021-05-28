//i2 hook
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10utils.h"
#include "code/dcf2menu.h"
#include <iostream>
#include "includes.h"
#include "code/dcf2.h"
#include "code/eSettingsManager.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"

// timer 0x1442CFE7C
// kill p2 0x1442CFF10

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->bFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->bFocused = true;
		break;
	default:
		break;
	}
	if (TheMenu->GetActiveState())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
bool first_msg = true;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;

	if (first_msg)
	{
		Notifications->SetNotificationTime(7500);
		Notifications->PushNotification("I2Hook %s is running! Press F1 to open the menu.", I2HOOK_VERSION);
		first_msg = false;
	}

	Notifications->Draw();
	if (TheMenu->GetActiveState())
		TheMenu->Draw();
	ImGui::EndFrame();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}



DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}


using namespace Memory::VP;
using namespace hook;


int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}




bool __fastcall SetFlagNull()
{
	bool result = 0;
	Patch<int>(_addr(0x14444D58C), 0);

	return result;

}


void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}

	printf("I2Hook::OnInitializeHook() | Begin!\n");
	TheMenu->Initialize();
	Notifications->Init();
	printf("I2Hook::OnInitializeHook() | Game detected: %s\n", (char*)_addr(0x143455150));
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));


	// 60 fps
	if (SettingsMgr->bEnable60FPSFrontend)
	{
		Patch<char>(_addr(0x145EDC870 + 1), 0);
		InjectHook(_addr(0x14A370B70), tramp->Jump(SetFlagNull), PATCH_JUMP);
	}


	InjectHook(_addr(0x145E1AC78), tramp->Jump(DCF2Hooks::HookProcessStuff));
	InjectHook(_addr(0x14599F39E), tramp->Jump(DCF2Hooks::HookStartupFightRecording));

	Nop(_addr(0x14AD1C597), 7);
	Nop(_addr(0x14AD1C5A7), 8);
	InjectHook(_addr(0x14AD1C5B5), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x14AD1C5C2), tramp->Jump(&MKCamera::HookedSetRotation));

}



bool CheckGame()
{
	char* gameName = (char*)_addr(0x143455150);

	if (strncmp(gameName, "Injustice", strlen("Injustice")) == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nI2Hook only supports latest (or it needs to be updated) Steam executable.", 0, MB_ICONINFORMATION);
		return false;
	}
}




BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (CheckGame())
		{
			SettingsMgr->Init();

			if (SettingsMgr->b60FPSModeOnly)
			{
				Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
				Patch<char>(_addr(0x145EDC870 + 1), 0);
				InjectHook(_addr(0x14A370B70), tramp->Jump(SetFlagNull), PATCH_JUMP);
			}
			else
			{
				DisableThreadLibraryCalls(hMod);
				CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
				OnInitializeHook();
			}
		}



		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}