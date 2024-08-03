#include "main.h"
#include "SpeedHack.h"
#include "ImguiDraw.h"
double *TimeSpeed;
double* HigePingBase[5];
float* TimtOut[2];
float* CheckSpeedHack;
byte* Check;
UINT* NubSpeed, * PlayerSpeed;
int* GameSce;
double* VeryHigeSpeedHack = nullptr;
int GetVk() {
	switch (((int)Vk.value)){
	case 0:
		return VK_E;
	case 1:
		return VK_SHIFT;
	case 2:
		return VK_V;
	case 3:
		return VK_R;
	default:
		return VK_E;
	}
}

void SpeedHack_::AutoResetRoom(){
	if (this->IsNeedResetRoom) {
		g_pEngine->pfnClientCmd(XorString("fs_lazy_precache 2;retry"));
		IsNeedResetRoom = false;
	}
}

void SpeedHack_::StartSpeedHack() {
	if (BugScer.value && !SecHack) *GameSce = -1;
	if (!ImguiDraw::IsDeveloper) {
		AutoResetRoom();
		if (!IsSpeedStart)FirstTime = clock();
		if (clock() - FirstTime >= 8000) this->IsNeedResetRoom = true;
	}
	IsSpeedStart = true;
	*TimeSpeed = 0.0;
	*NubSpeed = 0;
	*PlayerSpeed = 0;
	switch ((int)HighUpload.value) {
	case 1:
		*VeryHigeSpeedHack = 0.000008;
		break;
	case 2:
		*VeryHigeSpeedHack = 0.0008;
		break;
	case 3:
		*VeryHigeSpeedHack = 10;
		break;
	}
}

void SpeedHack_::StartPassDropClient(){
	*((UINT*)TimtOut[0]) = Inf;
	*((UINT*)TimtOut[1]) = NInf;
	*((UINT*)CheckSpeedHack) = Inf;
	*Check = 0;
}

void SpeedHack_::EndSpeedHack(){
	this->fire = false;
	this->SecHack = false;
	IsNeedResetRoom = false;
	IsSpeedStart = false;
	if (*GameSce == -1)*GameSce = 2;
	FuckHigePing();
	G_VguiPrint->PrintUnf_8(0, XorString(u8"¼ÓËÙÍê±Ï¡£"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}

void SpeedHack_::AutoFire(usercmd_s* cmd){
	switch ((int)autoFire.value){
	case 1:
		cmd->buttons = !fire ? cmd->buttons | IN_ATTACK : cmd->buttons & ~IN_ATTACK;
		fire = !fire ? true : false;
		return;
	case 2:
		cmd->buttons = !fire ? cmd->buttons | IN_ATTACK2 : cmd->buttons & ~IN_ATTACK2;
		fire = !fire ? true : false;
		return;
	case 3:
		cmd->buttons = !fire ? cmd->buttons | IN_ATTACK : cmd->buttons & ~IN_ATTACK;
		cmd->buttons = !fire ? cmd->buttons | IN_ATTACK2 : cmd->buttons & ~IN_ATTACK2;
		fire = !fire ? true : false;
		return;
	}
}

void FuckHigePing() {
	*HigePingBase[0] = 0.0;
	*HigePingBase[1] = 0.0;
	*HigePingBase[2] = 0.0;
	*HigePingBase[3] = 0.0;
	*((float*)HigePingBase[4]) = 0.0f;
	*VeryHigeSpeedHack = DefineSpeed;
}

void __stdcall StartSecHack() {
	*GameSce = -1;
	Sleep(1000);
	*GameSce = 2;
}