#pragma once
#include "..\mk\Engine.h"
#include "..\mk\MKCharacter.h"
#include "..\mk\CharacterDefinition.h"
#include "Menu.h"
#include "..\gui\notifications.h"
#include "..\helper\eMouse.h"
#include "PluginInterface.h"

void MKProcDispatch_Hook();
void Dispatch_Hook(int64 ptr, int a2);
void RecordEvent_Hook(int64 eventID, int64 a2, int64 a3, int64 a4);

void PluginDispatch();
void PluginFightStartup();