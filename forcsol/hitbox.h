#pragma once
#include "ValveSDK/engine/util_vector.h"
#ifndef Aim_Body
#define Hit_Head 11
#define Hit_Body 2
#define Hit_Leftshou 12
#define Hit_Rightshou 16
#define Hit_LeftArm 14
#define Hit_RightArm 19
#define Hit_LeftLeg 4
#define Hit_RightLeg 7
#define Hit_Leftshou 19
#define Hit_abdomen 1 
#define Hit_Dick 0

#define Aim_Body
#endif // !Aim_Body
struct HitBox
{
	Vector Box[35];
	int BoxNum;
}; extern HitBox P_HitBox[33];