#pragma once

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};


struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator
{
	int Pitch;
	int Yaw;
	int Roll;
};

struct character_info {
	char	name[16];
};