#pragma once

#define GFG_GAME_INFO 0x14410C6D8

struct FG_GAME_INFO {
	char pad[0xFDC];
	int  iTimer;
};