#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

extern void(__fastcall* pProcessDOFSettings)(int64, int64, int64, int64, int64);
void ProcessDOFSettings(int64 a1, int64 a2, int64 settings, int64 a4, int64 a5);

void MKProcDispatch_Hook();
void Dispatch_Hook(int64 ptr, int a2);
void RecordEvent_Hook(int64 eventID, int64 a2, int64 a3, int64 a4);

void PluginDispatch();
void PluginFightStartup();
void PluginFightStartupAddModifiers();