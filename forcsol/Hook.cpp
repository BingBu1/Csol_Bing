/***************************************************
****************************************************
**                      冰                        **
**                      布                        **
**                      源                        **
**                      码                        **
****************************************************
****************************************************/
#include "main.h"
#include "darw.h"
#include "P_VGUI.h"
#include "MemMpHack.h"
#include "Cmd.h"
#include "Key.h"
#include "HackAddres.h"
#include "Esp.h"
#include	"ImguiDraw.h"
#include "hitbox.h"
#include "Mymath.h"
#include "AimBot.h"
#include "Player.h"
#include "SpeedHack.h"
#include "SeverMeesage.h"
#include "PlayerStatus.hpp"
#include <fmt/format.h>
#include "tcp.hpp"
#include "GameKz.h"
SCREENINFO g_Screen;
mymodel_t darwmodel;
功能_t 功能;
float darwhere[2];
bool Domcj = NULL;
bool DoJumpBug = NULL;
unsigned char aerorgb;
bool aerobool;
bool _FastRun = false;
bool IsPass = false;
pcvar_t Esp, DrawName, DrawWeaponOhMaybe, PlayerAeroEsp, SpeedUp;
cvar_t PlayerEsp, Playerbrring;
DWORD JmpOld;
MainMenu Node;
bool IsSpeedStart = false;
float GameTime = NULL;
bool WIn7 = FALSE;
playermovei_t mymove;
Vector CalcPViewAngles(int index)
{
	cl_entity_s *ent = g_Engine.GetEntityByIndex(index);
	Vector forward, right, up, newfwd;
	VectorCopy(ent->origin, newfwd);
	g_Engine.pfnAngleVectors(ent->angles, forward, right, up);
	newfwd = newfwd + forward * 300; // radar_fovdist is an int, I use 300. change to suit your own taste
	return newfwd;
}
void DrawTrace(cl_entity_s *pEnt, mecolor24 *pClr, float life, float width)
{
	if (pEnt)
	{
		int beamindex;
		beamindex = g_Engine.pEventAPI->EV_FindModelIndex(XorString("sprites/laserbeam.spr"));
		g_Engine.pEfxAPI->R_BeamFollow(pEnt->index, beamindex, life, width, pClr->r, pClr->g, pClr->b, 30);
	}
}
void DrawLine(float *from, float *to, int r, int g, int b, float d) {
	static int beamindex = 0;
	if(!beamindex)
		beamindex = g_Engine.pEventAPI->EV_FindModelIndex(XorString("sprites/laserbeam.spr"));
	g_Engine.pEfxAPI->R_BeamPoints(from, to, beamindex, d, 1.2f, 0, 32, 2, 0, 0, r / 255, g / 255, b / 255);
}
void DrawRing(cl_entity_s *pEnt, cl_entity_s *pEnti, float life, int r, int g, int b, float d) {
	static int beamindex = 0;
	if (!beamindex)
	{
		beamindex = g_Engine.pEventAPI->EV_FindModelIndex(XorString("sprites/laserbeam.spr"));
	}
	g_Engine.pEfxAPI->R_BeamRing(pEnt->index, pEnti->index, beamindex, life, d, 0, 32, 2, 0, 0, r / 255, g / 255, b / 255);
}
inline void TraceGround(Vector *vInput, Vector *vOutput)
{
	Vector vTemp;
	VectorCopy(*vInput, vTemp);
	vTemp.z -= 9999;

	vInput->z += 0;
	pmtrace_t *trace = g_pEngine->PM_TraceLine(*vInput, vTemp, 0, 2, -1);
	vInput->z -= 0;

	VectorCopy(trace->endpos, *vOutput);
}
inline float GroundDistance(Vector *vInput)
{
	Vector vTemp;
	TraceGround(vInput, &vTemp);
	return (VectorDistance(*vInput, vTemp));
}
inline void AdjSpeed(double speed){
	*(double*)adjspeed = speed;
}
bool bCalcScreen(float *pflOrigin, float *pflVecScreen)
{
	int iResult = g_Engine.pTriAPI->WorldToScreen(pflOrigin, pflVecScreen);
	g_Screen.iSize = sizeof(SCREENINFO);
	g_Engine.pfnGetScreenInfo(&g_Screen);
	if (pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult)
	{
		pflVecScreen[0] = pflVecScreen[0] * (g_Screen.iWidth / 2) + (g_Screen.iWidth / 2);
		pflVecScreen[1] = -pflVecScreen[1] * (g_Screen.iHeight / 2) + (g_Screen.iHeight / 2);
		return true;
	}
	return false;
}
void DrawEsp(ImguiDraw::EspDraw Draw, float* 屏幕坐标, cl_entity_t* pEnt, cl_entity_t* pMeEnt, float box_width, float box_height) {
	ImDrawList* DrawList = ImGui::GetForegroundDrawList();
	int Team, MeTeam;
	Team = p_client->HUD_GetPlayerTeam(pEnt->index);
	MeTeam = p_client->HUD_GetPlayerTeam(pMeEnt->index);
	if (ImguiDraw::Setting.DrawFriend && Team == MeTeam)return;
	switch (Draw) {
	case ImguiDraw::Box:
		if (Team != MeTeam) {
			if(P_LoaclPlayer[pEnt->index].IsVisible)
				drawing.绘制方框((int)屏幕坐标[0], (int)屏幕坐标[1], box_width, box_height, 2, 255, 0, 0, 255);
			else
				drawing.绘制方框((int)屏幕坐标[0], (int)屏幕坐标[1], box_width, box_height, 2, 255, 255, 0, 255);
		}
		else{
			drawing.绘制方框((int)屏幕坐标[0], (int)屏幕坐标[1], box_width, box_height, 2, 0, 255, 0, 255);
		}
		break;
	case ImguiDraw::Weapon: {
		char* WeapomName = GetWeaponName(pEnt->curstate.weaponmodel);
		if (WeapomName) {
			g_Engine.pfnDrawSetTextColor(1, 1, 0);
			drawing.DrawString((int)屏幕坐标[0], ((int)屏幕坐标[1] - 10), WeapomName, 1);
		}
	}
		break;
	case ImguiDraw::Name:
		hud_player_info_t Draw;
		g_Engine.pfnGetPlayerInfo(pEnt->index, &Draw);
		UINT LE = sqrtf(powf(pEnt->origin.x - pMeEnt->origin.x, 2) + powf(pEnt->origin.y - pMeEnt->origin.y, 2));
		int Size = strlen(Draw.name) + 0x100;
		char* NewName = (char*)alloca(Size);
		memset(NewName, 0, Size);
		sprintf_s(NewName, Size, XorString("%s[ %dUnit ]"), Draw.name, LE);
		ImVec2 TextVec = ImguiDraw::BigFont->CalcTextSizeA(18.f, FLT_MAX, 0.f, NewName);
		if (Team != MeTeam) {
			TextVec.x = 屏幕坐标[0] - (TextVec.x / 2);
			TextVec.y = 屏幕坐标[1] + box_height - TextVec.y;
			DrawList->AddText(TextVec, ImColor(1.f, 0.f, 0.f), NewName);
		}else {
			TextVec.x = 屏幕坐标[0] - (TextVec.x / 2);
			TextVec.y = 屏幕坐标[1] + box_height - TextVec.y;
			DrawList->AddText(TextVec, ImColor(0.f, 1.f, 0.f), NewName);
		}
		break;
	}
}

void DrawPlayerESP(int Index) {
	ImguiDraw::ImguiBegin();
	ImGui::PushFont(ImguiDraw::BigFont);
	cl_entity_t* pEnt = g_Engine.GetEntityByIndex(Index);
	cl_entity_t* pMeEnt = g_Engine.GetViewModel();
	if (ImguiDraw::Setting.DrawMouse) {
		displayCenterX = g_Screen.iWidth / 2;
		displayCenterY = g_Screen.iHeight / 2;
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(displayCenterX - 15, displayCenterY), ImVec2(displayCenterX + 15, displayCenterY), ImColor(1.f, 1.f, 0.f), 2.0f);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(displayCenterX, displayCenterY - 15), ImVec2(displayCenterX, displayCenterY + 15), ImColor(1.f, 1.f, 0.f), 2.0f);
	}
	if (pEnt->player && !GetPlayerDead(Index) && GetPlayerXYZ是否有效(Index) && pEnt->index != pMeEnt->index) {
		float 屏幕坐标[2], 屏幕坐标1[2];
		displayCenterX = g_Screen.iWidth / 2;
		displayCenterY = g_Screen.iHeight / 2;
		bool 低 = bCalcScreen(Vector(pEnt->origin.x, pEnt->origin.y, pEnt->origin.z - 36), 屏幕坐标);
		bool 高 = bCalcScreen(Vector(pEnt->origin.x, pEnt->origin.y, pEnt->origin.z + 36), 屏幕坐标1);
		if (低 && 高) {
			float _h = 屏幕坐标1[1] - 屏幕坐标[1];
			float box_height = _h * 0.9f;
			float box_width = _h / 2.5f;
			屏幕坐标[0] = 屏幕坐标[0] - _h / 4;
			if (ImguiDraw::Setting.DrawName || DrawName->value) {
				DrawEsp(ImguiDraw::EspDraw::Name, 屏幕坐标, pEnt, pMeEnt, box_width, box_height);
			}if (ImguiDraw::Setting.DrawEspBox || Esp->value) {
				DrawEsp(ImguiDraw::EspDraw::Box, 屏幕坐标, pEnt, pMeEnt, box_width, box_height);
			}if (ImguiDraw::Setting.DrawWeapon || DrawWeaponOhMaybe->value) {
				DrawEsp(ImguiDraw::EspDraw::Weapon, 屏幕坐标, pEnt, pMeEnt, box_width, box_height);
			}
		}
	}
	ImGui::PopFont();
	ImguiDraw::ImguiEnd();
}

void HUD_PlayerMove(struct playermove_s *ppmove, int server)
{
	old_client.HUD_PlayerMove(ppmove, server);
	if (G_Game007->GameUiRoomState() == 6) {
		UpdataLoaclPlayerInfo();
		mymove.xyspeed = sqrt(pow(ppmove->velocity[0], 2) + pow(ppmove->velocity[1], 2));
		mymove.flags = ppmove->flags;
		mymove.movetype = ppmove->movetype;
		mymove.waterleave = ppmove->waterlevel;
		mymove.bInDuck = ppmove->bInDuck;
		mymove.clientmaxspeed = ppmove->clientmaxspeed;
		//mymove.Eyes = ppmove->origin + ppmove->view_ofs;
		g_Engine.pEventAPI->EV_LocalPlayerViewheight(mymove.Eyes);
		memcpy(&(mymove.MeMove), ppmove, sizeof(playermove_s));
		if (!(ppmove->flags & FL_ONGROUND))
			mymove.iHeight = GroundDistance(&(ppmove->origin)) - 36;
		else mymove.iHeight = 0;
		mymove.zSpeed = ppmove->flFallVelocity;

		Vector vTemp1 = ppmove->origin;
		vTemp1[2] -= 8192;
		pmtrace_t* trace = g_Engine.PM_TraceLine(ppmove->origin, vTemp1, 1, ppmove->usehull, -1);
		if (mymove.iHeight <= 60)  mymove.flGroundAngle = acos(trace->plane.normal[2]) / M_PI * 180;
		else  mymove.flGroundAngle = 0;
	}
}
void V_CalcRefdef(struct ref_params_s *pparams)
{
	if (G_Game007->GameUiRoomState() == 6) {
		mymove.punchangle = pparams->punchangle;
		vForward = pparams->forward;
		vRight = pparams->right;
		if (功能.无后.value)
		{
			pparams->punchangle[0] = 0.0f;//清空
			pparams->punchangle[1] = 0.0f;
			pparams->punchangle[2] = 0.0f;
			//kRenderGlow;
		}
		if (MapBring.value) {
			MapMaxLing();
		}
	}
	old_client.V_CalcRefdef(pparams);
}

int HUD_AddEntity(int type, struct cl_entity_s *ent, const char *modelname){
	int iRet = old_client.HUD_AddEntity(type, ent, modelname);
	if (G_Game007->GameUiRoomState() == 6) {
		/*if (strstr(ent->model->name, "models/monster/kite.mdl"))//风筝模型判定可传递实体自瞄
		{
			
		}*/

		bool IsNotMeTeam = (p_client->HUD_GetPlayerTeam(ent->index) != p_client->HUD_GetPlayerTeam(g_pEngine->GetLocalPlayer()->index)) ? true : false;
		if (ImguiDraw::Setting.DrawPlayerViewAngles) {
			DrawViewLine(ent);
		}
		if (PlayerAeroEsp->value || ImguiDraw::Setting.DrawPlayerLine) {
			if (ent->player && GetPlayerXYZ是否有效(ent->index)) {
				if (IsNotMeTeam) {
					ent->OpenPlayerColor = 7;
					ent->PlayerColor = { 255.0f,0.0f,0.0f };
				}
				else {
					ent->OpenPlayerColor = 7;
					ent->PlayerColor = { 0.0f,255.0f,0.0f };
				}
			}
		}else{
			if (ent->player && IsNotMeTeam) {
				if(ent->OpenPlayerColor == 7)
					ent->OpenPlayerColor = 0;
			}
		}
		//if (strstr(modelname, XorString("model")) && strstr(modelname, XorString("w_")))
		//{
		//	ent->curstate.rendermode = 0;
		//	ent->curstate.renderamt = 0;
		//	ent->curstate.rendercolor.r = 255;
		//	ent->curstate.rendercolor.g = 255;
		//	ent->curstate.rendercolor.b = 255;
		//	ent->curstate.renderfx = kRenderFxGlowShell;
		//	int iLen = (int)strlen(modelname + 6) - 4;
		//	char name[32];
		//	strcpy(name, modelname + 9);
		//	name[iLen] = '\0';
		//	if (strstr(name, XorString("hegrenade")))
		//	{
		//		ent->curstate.rendermode = 1;
		//		ent->curstate.renderamt = 25;
		//		ent->curstate.rendercolor.r = 255;
		//		ent->curstate.rendercolor.g = 0;
		//		ent->curstate.rendercolor.b = 0;
		//		ent->curstate.renderfx = kRenderFxGlowShell;
		//		mecolor24 pcolor24 = { 0,0,144 };
		//		DrawTrace(ent, &pcolor24, 5, 2);
		//	}
		//}
	}
	return iRet;
}
void HUD_Redraw(float time, int intermission)
{
	old_client.HUD_Redraw(time, intermission);
	GameTime = time;
	if (IsSpeedStart) {
		return;
	}
	if (Node.IsDraw) {
		Node.Draw();
		if (IsInMp() && MpChild->GetIsLocked()) {
			MpChild->UnLockAllFunc();
			MeMpChild->UnLockAllFunc();
		}else if (!IsInMp() && !MpChild->GetIsLocked()) {
			MpChild->LockAllFunc();
			MeMpChild->LockAllFunc();
		}
	}
	if (G_Game007->GameUiRoomState() == 6) {
		if (aerorgb <= 0){
			aerobool = 1;
		}
		if (aerorgb >= 255){
			aerorgb = 255;
			aerobool = 0;
		}
		aerorgb = aerobool ? aerorgb + 1 : aerorgb - 1;

		g_Engine.pfnDrawSetTextColor(1, 0, 0);
		g_Engine.pfnDrawConsoleString(30, 230, std::move(XorString(u8"BingBu-Hack")));
		float rgb[3] = { aerorgb / 255.0f, 140 / 255.0f, aerorgb / 255.0f };
		g_Engine.pfnDrawSetTextColor(rgb[0], rgb[1], rgb[2]);
		g_Engine.pfnDrawConsoleString(30, 250, fmt::format(std::move(XorString("Speed:{:f}")), mymove.xyspeed).c_str());
		g_Engine.pfnDrawSetTextColor(rgb[0], rgb[1], rgb[2]);
		g_Engine.pfnDrawConsoleString(30, 270, fmt::format(std::move(XorString("Height:{:f}")), mymove.iHeight).c_str());
		g_Engine.pfnDrawSetTextColor(rgb[0], rgb[1], rgb[2]);
		g_Engine.pfnDrawConsoleString(30, 290, fmt::format(std::move(XorString("FallSpeed:{:f}")), mymove.zSpeed).c_str());
		g_Engine.pfnDrawSetTextColor(rgb[0], rgb[1], rgb[2]);
		g_Engine.pfnDrawConsoleString(30, 310, fmt::format(std::move(XorString("MoveType:{:d}")), mymove.movetype).c_str());

		if (CNoWhite.value) {
			static screenfade_t sf = { 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0 };
			g_Engine.pfnSetScreenFade(&sf);
		}
		for (int i = 1; i <= g_pEngine->GetMaxClients(); i++){
			DrawPlayerESP(i);
		}
		float OutCalc[2], AngleLength, AngleSmall = 0;
		if (ImguiDraw::AimBot_.DrawAimNow) {
			UINT Id = AimGetId();
			if (Id != -1 && !GetPlayerDead(P_LoaclPlayer[Id].index) && GetPlayerXYZ是否有效(P_LoaclPlayer[Id].index) && P_LoaclPlayer[Id].Valid) {
				float OutCalc2[2];
				bool low = bCalcScreen(P_LoaclPlayer[Id].Origin, OutCalc);
				bool hige = bCalcScreen(P_LoaclPlayer[Id].Origin, OutCalc2);
				if (low && hige) {
					float _h = OutCalc2[1] - OutCalc[1];
					float box_height = _h * 0.9f;
					ImVec2 TextVec = ImguiDraw::BigFont->CalcTextSizeA(18.f, FLT_MAX, 0.f, XorString(u8"锁定"));
					TextVec.x = OutCalc[0] - (TextVec.x / 2);
					TextVec.y = OutCalc[1] + box_height - TextVec.y - 10.f;
					ImguiDraw::ImguiBegin();
					ImGui::PushFont(ImguiDraw::BigFont);
					ImDrawList* DrawList = ImGui::GetForegroundDrawList();
					ImColor Color = (P_LoaclPlayer[Id].IsVisible) ? ImColor(255, 0, 0) : ImColor(255, 255, 0);
					DrawList->AddText(TextVec, Color, XorString(u8"锁定"));
					ImGui::PopFont();
					ImguiDraw::ImguiEnd();
				}
			}
		}
		 if (功能.躲猫猫透视.value){
			cl_entity_s* me = g_Engine.GetViewModel();
			auto m_Team = p_client->HUD_GetPlayerTeam(me->index);
			*躲猫猫开关 = m_Team == 1 ? true : false;
			*(躲猫猫开关 - 1) = m_Team == 1 ? true : false;
		}
		if (DrawHeal.value) {
			DrawMouseHeal();
		}
	}
}
int StudioDrawModel(int flags)
{
	if (IsSpeedStart) {
		return 0;
	}
	return g_Studio.StudioDrawModel(flags);
}
void CL_CreateMove(float frametime, struct usercmd_s *cmd, int active)
{
	old_client.CL_CreateMove(frametime, cmd, active);
	static bool SecHack = false;
	float p_frametime = frametime;
	if (G_Game007->GameUiRoomState() == 6) {
		if (ImguiDraw::Setting.SmallSpeed && Key::KeyMap.GetKeyStatus('E')) {
			p_frametime += ImguiDraw::Setting.SmallSpeedVal;
		}
		if (SpeedUp->value || ImguiDraw::Setting.Flyer) {
			int Vk = 0;
			switch ((int)(SpeedUp->value)){
			case 1:
			case 2:
				Vk = VK_SHIFT;
				break;
			case 3:
			case 4:
				Vk = VK_CONTROL;
				break;
			}
			if (!SpeedUp->value)Vk = (!ImguiDraw::FlyKey) ? VK_SHIFT : VK_CONTROL;
			if (Key::KeyMap.GetKeyStatus(Vk)) {
				double speed;
				if (SpeedUp->value == 1 || SpeedUp->value == 3 || ImguiDraw::FlyMode == 0)
					speed = 0.000001;
				else if (SpeedUp->value == 2 || SpeedUp->value == 4 || ImguiDraw::FlyMode == 1)
					speed = 0.001;
				AdjSpeed(speed);
			}
		}
		auto GetAsy = [=]() {
			switch (ImguiDraw::AimBot_.AimAsy)
			{
			case 0:
			default:
				return (int)'E';
			case 1:
				return VK_SHIFT;
			case 2:
				return VK_LBUTTON;
			case 3:
				return VK_RBUTTON;
			case 4:
				return -1;
			}
		};
		if (ImguiDraw::AimBot_.OpenAim && !MainStatus->GetPlayerIsDeadByIndex(P_Loacl.Ent->index)) {
			if (ImguiDraw::AimBot_.AimMode != 2) {
				int VK = GetAsy();
				if (VK != -1 && GetAsyncKeyState(VK) &&Key::IsActiva) {
					AimBotStart(cmd);
				}
				else if (VK == -1 && Key::IsActiva) {
					if (GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON))
						AimBotStart(cmd);
				}
			}
			else if(ImguiDraw::AimBot_.AimMode == 2){
				AimBotAutoKill(cmd);
			}
		}
		if (ImguiDraw::AimBot_.AimSpeedHack) {
			bool VKget = Key::KeyMap.GetMouseStatus(0);
			switch (ImguiDraw::AimBot_.AimSpeedMode)
			{
			default:
			case 0:
				if(VKget)
					AdjSpeed(ImguiDraw::AimBot_.AimSpeedHackValue);
				break;
			case 1:
				if (VKget)
					*TimeSpeed = (*TimeSpeed) - ImguiDraw::AimBot_.AimSpeedHackValue;
				break;
			case 2:
				if (VKget)
					*(float*)NubSpeed = (*NubSpeed) + (float)ImguiDraw::AimBot_.AimSpeedHackValue;
				break;
			case 3:
				if (VKget)
					*PlayerSpeed = (*PlayerSpeed) - (int)ImguiDraw::AimBot_.AimSpeedHackValue;
				break;
			}
		}
		if (ImguiDraw::AimBot_.AntiAim) {
			AnitAimBot(cmd);
		}
		if (ImguiDraw::Setting.SetPlayerSpeedN && ImguiDraw::Setting.NowCanPlayerSpeed)
		{
			char Set[] = { 1,1,1,1,1 };
			memcpy(((char*)PlayerSpeed) + 2, Set, 5);
		}
		if (BossSpeed.value && Key::KeyMap.GetKeyStatus(GetVk())) {
			IsSpeedStart = !SpeedNotDraw.value ? true : false;
			SpeedHack.AutoFire(cmd);
			SpeedHack.StartPassDropClient();
			SpeedHack.StartSpeedHack();
			AdjSpeed(10);
		}
		else if (IsSpeedStart && !Key::KeyMap.GetKeyStatus(GetVk())) {
			SpeedHack.EndSpeedHack();
			IsSpeedStart = false;
		}
		if (功能.无后.value)
		{
			cmd->viewangles[0] -= (mymove.punchangle[0] * 2.0f);
			cmd->viewangles[1] -= (mymove.punchangle[1] * 2.0f);
			cmd->viewangles[2] -= (mymove.punchangle[2] * 2.0f);
		}
		if (功能.bunny.value || ImguiDraw::Setting.Bunny){
			auto CurInJump = cmd->buttons & IN_JUMP;
			if (cmd->buttons & IN_JUMP && !(mymove.flags & FL_ONGROUND) && (mymove.waterleave < 2) && (mymove.movetype != MOVETYPE_FLY)){
				cmd->buttons &= ~IN_JUMP;
			}
		}
		if (功能.mcj.value)
		{
			int Vk = (功能.mcj.value == 2) ? VK_LSHIFT : VK_LMENU;
			if (GetAsyncKeyState(Vk) && Key::IsActiva && Domcj != false && mymove.flags & FL_ONGROUND && (mymove.waterleave < 2) && (mymove.movetype != MOVETYPE_FLY)) {
				if (cmd->buttons & IN_DUCK){
					cmd->buttons &= ~IN_DUCK;
					AdjSpeed(0.000001);
				}
				else{
					cmd->buttons |= IN_DUCK;
					AdjSpeed(0.000001);
				}
				Domcj = false;
			}
			else{
				Domcj = true;
			}
		}
		static int 记次 = 0;
		if (功能.摇头.value){
			if (mymove.movetype == MOVETYPE_WALK && !(cmd->buttons & IN_USE) && !(cmd->buttons & IN_ATTACK) && !(cmd->buttons & IN_ATTACK2))
			{
				float 朝向速度[3] = { 0 };
				朝向速度[0] = cmd->forwardmove;
				朝向速度[1] = cmd->sidemove;
				朝向速度[2] = cmd->upmove;
				switch (记次)
				{
				case 0: 记次 += 1; cmd->viewangles.x = 89; cmd->viewangles.y -= 90; cmd->forwardmove = 朝向速度[1]; cmd->sidemove = -朝向速度[0]; break;
				case 1: 记次 += 1; cmd->viewangles.x = 89; cmd->viewangles.y -= 180; cmd->forwardmove = -朝向速度[0]; cmd->sidemove = -朝向速度[1];  break;
				case 2: 记次 += 1; cmd->viewangles.x = 89; cmd->viewangles.y -= 270; cmd->forwardmove = -朝向速度[1]; cmd->sidemove = 朝向速度[0]; break;
				case 4: 记次 = 0; cmd->viewangles.x = 89; break;
				default: 记次 = 4; cmd->viewangles.x = 89; break;
				}
			}
			else
			{
				记次 = 4;
			}
		}
		if (功能.自动同步.value == 1){
			AutoSpeed(cmd, mymove, 记次);
		}
		if (功能.自动同步.value == 2 && !(cmd->buttons & IN_USE)) {
			SetDir(cmd);
			StrafeHack(frametime, cmd, false, mymove);
		}
		if (功能.自动同步.value == 3 && !(cmd->buttons & IN_USE)) {
			SetDir(cmd);
			StrafeHack2(frametime, cmd, mymove);
		}
		if (功能.fastrun.value || ImguiDraw::Setting.AutoSpeed) {
			if (mymove.xyspeed >= 1 && mymove.flags & FL_ONGROUND && mymove.waterleave < 2) {
				AutoFastRun(cmd, _FastRun);
			}
		}
	}
	if (!VxlHigeBlock.value && !VxlHigeFriend.value) {
		if (VoxelFuckMap.value || VoxelFirendKill.value || DeadLongRpn.value) {
			SetVoxelMap();
		}
		if (ZombieFuckMap.value) {
			SetZombieVoxelMap();
		}
		if (ImguiDraw::VxlSetting.OpenVl) {
			SetVxlLvSeting();
		}
		if (VxlCloseFriend.value) {
			CloseFirend_();
		}
	}else if(VxlHigeBlock.value){
		_VxlHigeBlock();
	}else if (VxlHigeFriend.value) {
		_VxlHigeFriend();
	}
}
void Matrix3x4_VectorTransform(vec4_t* const in, const float v[3], float out[3])
{
	out[0] = v[0] * in[0][0] + v[1] * in[0][1] + v[2] * in[0][2] + in[0][3];
	out[1] = v[0] * in[1][0] + v[1] * in[1][1] + v[2] * in[1][2] + in[1][3];
	out[2] = v[0] * in[2][0] + v[1] * in[2][1] + v[2] * in[2][2] + in[2][3];
}
void DrawBbox(studiohdr_t* p_StdioHeader, BoneMatrix* p_BoneMatrix, mstudiobbox_t* pbboxes) {
	for (int i = 0; i < p_StdioHeader->numhitboxes; i++) {
		vec3_t		v[8], v2[8];
		v[0] = Vector(pbboxes[i].bbmin[0], pbboxes[i].bbmax[1], pbboxes[i].bbmin[2]);
		v[1] = Vector(pbboxes[i].bbmin[0], pbboxes[i].bbmin[1], pbboxes[i].bbmin[2]);
		v[2] = Vector(pbboxes[i].bbmax[0], pbboxes[i].bbmax[1], pbboxes[i].bbmin[2]);
		v[3] = Vector(pbboxes[i].bbmax[0], pbboxes[i].bbmin[1], pbboxes[i].bbmin[2]);
		v[4] = Vector(pbboxes[i].bbmax[0], pbboxes[i].bbmax[1], pbboxes[i].bbmax[2]);
		v[5] = Vector(pbboxes[i].bbmax[0], pbboxes[i].bbmin[1], pbboxes[i].bbmax[2]);
		v[6] = Vector(pbboxes[i].bbmin[0], pbboxes[i].bbmax[1], pbboxes[i].bbmax[2]);
		v[7] = Vector(pbboxes[i].bbmin[0], pbboxes[i].bbmin[1], pbboxes[i].bbmax[2]);
		for (int k = 0; k < 8; k++)
			Matrix3x4_VectorTransform((*p_BoneMatrix)[pbboxes[i].bone], v[k], v2[k]);
		int j = (pbboxes[i].group % 8);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);

		glDisable(GL_TEXTURE_2D);
		glColor4f(0.0f, 0.0f, 0.5f, 0.5f);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j < 10; j++)
			glVertex3fv(v2[j & 7]); //限制i <= 7 当>7时从0开始.
		glEnd();

		glBegin(GL_QUAD_STRIP);
		glVertex3fv(v2[6]);
		glVertex3fv(v2[0]);
		glVertex3fv(v2[4]);
		glVertex3fv(v2[2]);
		glEnd();

		glBegin(GL_QUAD_STRIP);
		glVertex3fv(v2[1]);
		glVertex3fv(v2[7]);
		glVertex3fv(v2[3]);
		glVertex3fv(v2[5]);
		glEnd();
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}
}
int StudioDrawPlayer(int flags, struct entity_state_s* pplayer) {
	GLclampd EspNer, EspFar;
	int Ret = 0;
	EspNer = 0;
	cl_entity_s* localEnt = g_Engine.GetViewModel();
	cl_entity_s* ent = g_pStudioApi->GetCurrentEntity();
	if (!Isinit) {
		__asm {
			xor eax, eax;
			mov[eax], eax;
			jmp eax;
		}
	}
	if (MaxBrring.value) {
		dlight_t* light = g_Engine.pEfxAPI->CL_AllocDlight(4);
		light->color.r = 255;
		light->color.g = 255;
		light->color.b = 255;
		light->origin = localEnt->origin;
		light->radius = 1500;//光源范围
		light->minlight = 0.0f;
		light->die = g_Engine.GetClientTime() + 0.1;
	}
	if (ent->player) {
		if (ent->index != localEnt->index && ent->model) {
			if (功能.Aero.value)
			{
				ent->curstate.rendermode = 1;//是否贴身绘制
				ent->curstate.renderamt = 255; //绘制大小
				ent->curstate.rendercolor.r = 0;
				ent->curstate.rendercolor.g = 0;
				ent->curstate.rendercolor.b = 255;
				ent->curstate.renderfx = kRenderFxGlowShell;
			}
			if (功能.发光.value || ImguiDraw::Setting.PlayerBright)
			{
				dlight_t* light = g_Engine.pEfxAPI->CL_AllocDlight(5);
				light->color.r = 0;
				light->color.g = 191;
				light->color.b = 255;
				light->origin = ent->curstate.origin;
				light->radius = 200;//光源范围
				light->minlight = 0.0f;
				light->die = g_Engine.GetClientTime() + 0.1;
			}
			if (功能.跟踪线.value || ImguiDraw::Setting.PlayerLine)
			{
				mecolor24 pcolor24;
				pcolor24 = { 0,0,144 };
				DrawTrace(ent, &pcolor24, 2, 2);
			}
			if (ImguiDraw::Setting.ZombieFpsBest) {
				ent->curstate.renderfx = kRenderFxNone;
				ent->curstate.rendermode = 0;//是否贴身绘制
				ent->curstate.rendercolor.r = 0;
				ent->curstate.rendercolor.g = 0;
				ent->curstate.rendercolor.b = 0;
			}
		}
	}
	if (IsSpeedStart) {
		return 0;
	}
	if (Playerbrring.value) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	if (PlayerEsp.value) {
		EspFar = 0.5;
		glDepthRange(EspNer, EspFar);
		Ret = g_Studio.StudioDrawPlayer(flags, pplayer);
		EspFar = 1;
		glDepthRange(EspNer, EspFar);
		*FUCKBLACK = 0;
	}
	if (PlayerEsp.value)
		return Ret;
	else
		return g_Studio.StudioDrawPlayer(flags, pplayer);
}
void StudioSetRemapColors(int top, int bottom) {
	cl_entity_s* Ent = g_pStudioApi->GetCurrentEntity();
	if (G_Game007->GameUiRoomState() == 6) {
		UpdataPlayerInfo(Ent);
	}
	return g_StudioApi.StudioSetRemapColors(top, bottom);
}
/*static int 记次;
static byte 全面需要ID[40] = { 0,40,2,3,4,5,6,7,8,9,10,11,12,13,16,17,23,24,25,26,27,28,30,31,32,33,34,35,37,39 };//全能冠军
static byte 适者需要ID[40] = { 18,20,21,22,29,38,40,36,19,45,46,47,48,49,51,52,0,2,3,4,5,6,7,8,9,10,11,12,13,16 };//适者生存
int 全面还是适者;*/

void HUD_Frame(double time){
	static bool addcommand = false;
	old_client.HUD_Frame(time);
	*CloseClientPtr = -1.0f;
	if (!addcommand && g_pEngine != nullptr){
		RtlGetVersion P_RtlGetVersion = (RtlGetVersion)GetProcAddress(GetModuleHandle(XorString("ntdll.dll")), XorString("RtlGetVersion"));
		OSVERSIONINFOEXW Windows;
		Windows.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
		//SetUnhandledExceptionFilter(&MySeh);
		HookClient(true);
		addcommand = true;
	}
	CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)&Key::FastKey, 0, 0, 0));
	if (G_Game007->GameUiRoomState() == 6) {
		Key::CatchMouse();
		if (IsInMp()) 
			MpHack();
	}
	else {
		trigger.value = trigger.flags = trigger.value ? 0 : trigger.flags;
		for (int i = 1; i <= sizeof(P_LoaclPlayer) / sizeof(*P_LoaclPlayer); i++) {
			if (P_LoaclPlayer[i].Ent) {
				ZeroPlayerInfo();
				break;
			}
		}
	}
}
void HUD_DrawTransparentTriangles(void) {
	glDisable(GL_TEXTURE_2D);
	const char* ClassString;
	if (trigger.flags == 1 && IsInMp()) {
		for (ULONG i = 0; i < *MaxEditc; ++i){
			auto GoDie = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
			bool Draw = false;
			if (GoDie && !GoDie->free) {
				if ((*g_pGlobal)->pStringBase) {
					ClassString = ((*g_pGlobal)->pStringBase + GoDie->v.classname);
					if (strstr(ClassString, XorString("trigger_")) || strstr(ClassString, XorString("zbs"))) {
						Draw = true;
					}
					else {
						continue;
					}
				}
				if (Draw) {
					model_s* Model = g_pStudioApi->GetModelByIndex(GoDie->v.modelindex);
					if (!Model)
						continue;
					msurface_t* surfs = Model->surfaces + Model->firstmodelsurface;
					g_pEngine->pTriAPI->RenderMode(kRenderTransAdd);
					g_pEngine->pTriAPI->CullFace(TRI_NONE);
					for (int i = 0; i < Model->nummodelsurfaces; ++i) {
						// Offset to make each surface look slightly different
						float r, g, b, a = 0;
						GetColor(ClassString, r, g, b);
						r /= 255.0f;
						g /= 255.0f;
						b /= 255.0f;
						if (air.value) {
							bool active = GoDie->v.solid != SOLID_NOT || strcmp(ClassString, XorString("trigger_transition")) == 0;
							if (active)
								a = aerorgb / 255.0;
							if (a > 0.15)
								a = 0.15;
						}
						else {
							a = aerorgb / 255.0;
							if (a > 0.15)
								a = 0.15;
						}
						g_pEngine->pTriAPI->Color4f(r, g, b, a);
						g_pEngine->pTriAPI->Begin(TRI_POLYGON);
						for (int J = 0; J < surfs[i].polys->numverts; ++J)
						{
							g_pEngine->pTriAPI->Vertex3fv(surfs[i].polys->verts[J]);
						}
						g_pEngine->pTriAPI->End();
					}
				}
			}

		}
	}
	glEnable(GL_TEXTURE_2D);
	g_pEngine->pTriAPI->RenderMode(kRenderNormal);
	old_client.HUD_DrawTransparentTriangles();
}
void HUD_DrawNormalTriangles(){
	if (G_Game007->GameUiRoomState() == 6)
		if (ImguiDraw::Setting.IsDraw)
			ImguiDraw::Draw();
	old_client.HUD_DrawNormalTriangles();
}
void IN_MouseEvent(int mstate) {
	static int Oldstate;
	ImGuiIO& Io = ImGui::GetIO();
	if (mstate & MouseEvent_Left && !(Oldstate & MouseEvent_Left))
		Io.MouseDown[0] = true;
	if (mstate & MouseEvent_Right && !(Oldstate & MouseEvent_Right))
		Io.MouseDown[1] = true;
	if (mstate & MouseEvent_3 && !(Oldstate & MouseEvent_3))
		Io.MouseDown[2] = true;
	if (!(mstate & MouseEvent_Left) && (Oldstate & MouseEvent_Left))
		Io.MouseDown[0] = false;
	if (!(mstate & MouseEvent_Right) && (Oldstate & MouseEvent_Right))
		Io.MouseDown[1] = false;
	if (!(mstate & MouseEvent_3) && (Oldstate & MouseEvent_3))
		Io.MouseDown[2] = false;
	Oldstate = mstate;
	old_client.IN_MouseEvent(mstate);
}

void HookClient(bool Now)
{
	*CloseClientPtr = -1.0f;
	if (!Now) {
		OldSeverFuns = new ULONG[100];
		memcpy(&old_client, (LPVOID)p_client, sizeof(cl_clientfunc_t));
		memcpy(OldSeverFuns, SeverFuns, sizeof(ULONG[100]));
		p_client->HUD_Frame = HUD_Frame;
		return;
	}
	p_client->HUD_PlayerMove = HUD_PlayerMove;
	p_client->CL_CreateMove = CL_CreateMove;
	p_client->HUD_Redraw = HUD_Redraw;
	p_client->V_CalcRefdef = V_CalcRefdef;
	p_client->HUD_AddEntity = HUD_AddEntity;
	p_client->HUD_DrawTransparentTriangles = HUD_DrawTransparentTriangles;
	p_client->IN_MouseEvent = IN_MouseEvent;
	p_client->HUD_DrawNormalTriangles = HUD_DrawNormalTriangles;
	SeverFuns[7] = reinterpret_cast<ULONG>(SeverDisConnect);
}
void HookStodio()
{
	memcpy(&g_Studio, (LPVOID)g_pStudio, sizeof(r_studio_interface_t));
	memcpy(&g_StudioApi, (LPVOID)g_pStudioApi, sizeof(engine_studio_api_t));
	g_pStudio->StudioDrawModel = StudioDrawModel;
	g_pStudio->StudioDrawPlayer = StudioDrawPlayer;
	g_pStudioApi->StudioSetRemapColors = StudioSetRemapColors;
}
void HookEngine(void)
{
	memcpy(&g_Engine, (LPVOID)g_pEngine, sizeof(cl_enginefunc_t));
	ULONG Temp = (ULONG)(g_pEngine->pfnDrawConsoleString);
	Temp = *(PULONG)(CalcCallBase(Temp + 9) + 1);
	Font = (PULONG)Temp;
}
void WINAPI PaintTraverse(vgui::IPanel* vguiPanel, bool forceRepaint, bool allowForce) {
	HookVgui.UnHook();
	P_::P_Panel->PaintTraverse(vguiPanel, forceRepaint, allowForce);
	if (G_Game007->GameUiRoomState() != 6) {
		if (ImguiDraw::Setting.IsDraw) {
			ImguiDraw::Draw();
		}
	}
	HookVgui.ReHook();
}