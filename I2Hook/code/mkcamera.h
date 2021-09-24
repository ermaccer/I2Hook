#pragma once
#include "dcf2.h"
// generic layer for other plugins too
class MKCamera {
private:
	char pad[0x584];
	FVector  camPos;
	FRotator camRot;
	float	 camFov;
public:
	void SetPosition(FVector* pos);
	void SetRotation(FRotator* rot);
	void SetFOV(float FOV);
	float GetFOV();

	void HookedSetPosition(FVector* pos);
	void HookedSetRotation(FRotator* rot);
};

extern MKCamera* TheCamera;