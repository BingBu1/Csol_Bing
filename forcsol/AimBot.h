#pragma once
#include "hitbox.h"
#include <Windows.h>
void FixMoveEnd(struct usercmd_s* cmd);
void FixMoveStart(struct usercmd_s* cmd);
void AimBotStart(struct usercmd_s* cmd);
void AnitAimBot(usercmd_s* cmd);
UINT AimGetId(bool Is = false);
void AimBotAutoKill(usercmd_s* cmd);

struct AimBot{
	bool OpenAim;
	bool AntiAim;
	bool AutoNoAngle;
	bool DrawAimNow;
	bool AimSpeedHack;
	bool NotGlass;
	float NoAngleValue = 1.45f;
	double AimSpeedHackValue = 0.02f;
	int AimWhere;
	int AimMode;
	int AimGetMode;
	int AimAsy;
	int AimSpeedMode;
	int AimFriendMode;
};
