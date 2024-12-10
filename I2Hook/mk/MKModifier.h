#pragma once
#include "../mk/MKCharacter.h"
#include "../mk/Engine.h"
#include "../utils.h"

class BaseModifier {
public:
	char data[72] = {};
};


class Modifier : public BaseModifier {
public:
	Modifier(const char* name);
	void Activate(MKCharacter* character);
};


class TagAssistModifier : public BaseModifier {
public:
	TagAssistModifier(const char* character);
	void Activate(PLAYER_NUM player);
	void ActivateObject(PLAYER_NUM player);
};


class MKModifier {
public:
	static void ActivateModifier(const char* name, PLAYER_NUM player);
};


void		LoadModifierAssets();