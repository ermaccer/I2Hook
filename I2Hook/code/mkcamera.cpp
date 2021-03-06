#include "mkcamera.h"
#include "dcf2menu.h"
#include <iostream>

MKCamera* TheCamera;

void MKCamera::SetPosition(FVector * pos)
{
	TheCamera = this;
	*(float*)(this + 0x584) = pos->X;
	*(float*)(this + 0x584 + 4) = pos->Y;
	*(float*)(this + 0x584 + 8) = pos->Z;

	((void(__thiscall*)(MKCamera*, FVector*))_addr(0x141A10140))(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	TheCamera = this;
	*(int*)(this + 0x584 + 12) = rot->Pitch;
	*(int*)(this + 0x584 + 12 + 4) = rot->Yaw;
	*(int*)(this + 0x584 + 12 + 8) = rot->Roll;

	((void(__thiscall*)(MKCamera*, FRotator*))_addr(0x14AEA2640))(this, rot);
}

void MKCamera::SetFOV(float FOV)
{
	*(float*)(this + 0x584 + 24) = FOV;
}

float MKCamera::GetFOV()
{
	return *(float*)(this + 0x584 + 24);
}

void MKCamera::HookedSetPosition(FVector * pos)
{
	if (TheMenu->bCustomFOV)
		SetFOV(TheMenu->camFov);
	else
		TheMenu->camFov = GetFOV();

	float oneTime = 0.0f;
	if (!TheMenu->bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->bYObtained = true;
	}

	if (TheMenu->bEnableCustomCameras)
	{
		FVector plrPos;
		FVector p2;
		DCF2::GetCharacterPosition(&plrPos, PLAYER1);
		DCF2::GetCharacterPosition(&p2, PLAYER2);
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			pos->X = 5 + TheMenu->fAdjustCamX3;
			pos->Y = oneTime - 330.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Y += TheMenu->fAdjustCam3;
			pos->Z = 210.0f + plrPos.Z;
			pos->Z += TheMenu->fAdjustCamZ3;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 210.0f + plrPos.Z;
				pos->Z += TheMenu->fAdjustCamZ3;
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_3RDPERSON2:
			pos->X = 5;
			pos->Y = oneTime - 230.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 260.0f + plrPos.Z;;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 260.0f;
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON:
			pos->X = TheMenu->fAdjustCamX;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += TheMenu->fAdjustCam * -1;
			else
				pos->Y += TheMenu->fAdjustCam;
			pos->Z = TheMenu->fAdjustCamZ + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON_MID:
			pos->X = 16.0f;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += 23.0f * -1;
			else
				pos->Y += 23.0f;
			pos->Z = 124.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		case CAMERA_MK11:
			pos->X += 120.0f;
			pos->Z += 25.0f;

			TheMenu->camPos = *pos;
			break;
		}
		SetPosition(pos);
	}
	else
	{
		if (!TheMenu->bCustomCamera)
		{
			TheMenu->camPos = *pos;
			SetPosition(pos);
		}
		else
		{
			SetPosition(&TheMenu->camPos);
		}
	}

}

void MKCamera::HookedSetRotation(FRotator * rot)
{
	if (TheMenu->bEnableCustomCameras)
	{
		FVector p1, p2;
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			rot->Pitch = -900;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			DCF2::GetCharacterPosition(&p1, PLAYER1);
			DCF2::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -900;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_3RDPERSON2:
			rot->Pitch = -4000;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			DCF2::GetCharacterPosition(&p1, PLAYER1);
			DCF2::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -4000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			DCF2::GetCharacterPosition(&p1, PLAYER1);
			DCF2::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON_MID:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			DCF2::GetCharacterPosition(&p1, PLAYER1);
			DCF2::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_MK11:
			rot->Pitch -= 1258;
			TheMenu->camRot = *rot;
			break;
		}

		SetRotation(rot);
	}
	else
	{
		if (!TheMenu->bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			SetRotation(rot);
		}
		else
			SetRotation(&TheMenu->camRot);
	}

}

