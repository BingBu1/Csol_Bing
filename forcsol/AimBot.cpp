#include "main.h"
#include "Mymath.h"
#include "AimBot.h"
#include "Player.h"
#include "hitbox.h"
#include "ImguiDraw.h"
#include "PlayerStatus.hpp"
Vector vViewForward, vViewRight, vViewUp, vAimForward, vAimRight, vAimUp;
float forwardmove, sidemove, upmove;//backup for fixmove
int Aim_Arrary[10] = { Hit_Head,0,Hit_Body,Hit_abdomen,Hit_Rightshou,Hit_Leftshou,Hit_LeftArm,Hit_RightArm,Hit_LeftLeg,Hit_RightLeg };
void AimBot(usercmd_s* cmd);
void AimBotSilence(usercmd_s* cmd);
void NormalizeAngles(float* angles)
{
	for (int i = 0; i < 3; ++i)
	{
		float flRevolutions = angles[i] / 360;

		if (angles[i] > 180 || angles[i] < -180)
		{
			if (flRevolutions < 0)
			{
				flRevolutions = -flRevolutions;
			}

			flRevolutions = round(flRevolutions);

			if (angles[i] < 0)
			{
				angles[i] = (angles[i] + 360 * flRevolutions);
			}
			else
			{
				angles[i] = (angles[i] - 360 * flRevolutions);
			}
		}
	}
}
void FixMoveStart(struct usercmd_s* cmd)
{
	forwardmove = cmd->forwardmove;
	sidemove = cmd->sidemove;
	upmove = cmd->upmove;

	if (mymove.movetype == MOVETYPE_WALK)
		g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vViewForward, vViewRight, vViewUp);
	else
		g_Engine.pfnAngleVectors(cmd->viewangles, vViewForward, vViewRight, vViewUp);

}

void FixMoveEnd(struct usercmd_s* cmd)
{

	NormalizeAngles(cmd->viewangles);

	if (mymove.movetype == MOVETYPE_WALK)
		g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vAimForward, vAimRight, vAimUp);
	else
		g_Engine.pfnAngleVectors(cmd->viewangles, vAimForward, vAimRight, vAimUp);

	Vector forwardmove_normalized = forwardmove * vViewForward;
	Vector sidemove_normalized = sidemove * vViewRight;
	Vector upmove_normalized = upmove * vViewUp;
	
	cmd->forwardmove = DotProduct(forwardmove_normalized, vAimForward) + DotProduct(sidemove_normalized, vAimForward) + DotProduct(upmove_normalized, vAimForward);//向量点积
	cmd->sidemove = DotProduct(forwardmove_normalized, vAimRight) + DotProduct(sidemove_normalized, vAimRight) + DotProduct(upmove_normalized, vAimRight);//向量点积
	cmd->upmove = DotProduct(forwardmove_normalized, vAimUp) + DotProduct(sidemove_normalized, vAimUp) + DotProduct(upmove_normalized, vAimUp);//向量点积

	Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;//计算Move向量长度
	Vector vecMove, vecRealView(cmd->viewangles);
	VectorAngles(vMove, vecMove);
	flYaw = (cmd->viewangles.y - vecRealView.y + vecMove.y) * M_PI / 180.0f;

	cmd->forwardmove = cos(flYaw) * flSpeed;

	if (cmd->viewangles.x >= 90 || cmd->viewangles.x <= -90)
		cmd->forwardmove *= -1;

	cmd->sidemove = sin(flYaw) * flSpeed;
}
void MakeAngle(bool addangle, float* angles, struct usercmd_s* cmd)
{
	FixMoveStart(cmd);

	if (addangle)
	{
		cmd->viewangles[0] += angles[0];
		cmd->viewangles[1] += angles[1];
		cmd->viewangles[2] += angles[2];
	}
	else {
		cmd->viewangles[0] = angles[0];
		cmd->viewangles[1] = angles[1];
		cmd->viewangles[2] = angles[2];
	}

	FixMoveEnd(cmd);
}
void AimBotStart(usercmd_s* cmd) {
	if (!ImguiDraw::AimBot_.AimMode)
		AimBot(cmd);
	else
		AimBotSilence(cmd);
}
UINT AimGetId(bool Is) {
	int Id = -1;
	float AngleLength = 0, AngleSmall = 0;
	float  LengthLong = 0;
	float OutCalc[2];
	Vector Eyes = mymove.MeMove.origin + mymove.MeMove.view_ofs;
	for (int i = 1; i <= g_pEngine->GetMaxClients(); i++) {
		if (!(P_LoaclPlayer[i].Ent))
			continue;
		if (P_LoaclPlayer[i].index == P_Loacl.index)
			continue;
		if (!ImguiDraw::AimBot_.AimFriendMode && P_LoaclPlayer[i].team == P_Loacl.team)
			continue;
		if (ImguiDraw::AimBot_.AimFriendMode == 1 && P_LoaclPlayer[i].team != P_Loacl.team)
			continue;
		if (Is && !P_LoaclPlayer[i].IsVisible)
			continue;
		if (GetPlayerDead(i) && GetPlayerXYZ是否有效(i) == 0 && !P_LoaclPlayer[i].Valid)
			continue;
		if (!ImguiDraw::AimBot_.AimGetMode) {
			if (bCalcScreen(P_LoaclPlayer[i].Origin, OutCalc)) {
				float CenterX = g_Screen.iWidth / 2;
				float CenterY = g_Screen.iHeight / 2;
				Vector NewOrigin;
				NewOrigin = { fabsf(OutCalc[0] - CenterX) ,fabsf(OutCalc[1] - CenterY),0.f };
				AngleLength = NewOrigin.Make2D().Length();
				if (!AngleSmall || AngleLength < AngleSmall) {
					AngleSmall = AngleLength;
					Id = i;
				}
			}
		}
		else if (ImguiDraw::AimBot_.AimGetMode == 1) {
			Vector Origin = P_LoaclPlayer[i].Origin;
			Vector Angle, MousePos;
			g_pEngine->GetViewAngles(MousePos); //	鼠标角度
			VectorAngles(Origin - Eyes, Angle); //	将对面坐标转为角度
			Angle = Angle - MousePos; //对面鼠标坐标-自己鼠标坐标
			Angle.x = fabsf(Angle.x); //求绝对值
			Angle.y = fabsf(Angle.y);
			AngleLength = Angle.Length(); //求长度
			if (!AngleSmall || AngleLength < AngleSmall) { //如果最小为空 或 新的小于最小则赋值
				AngleSmall = AngleLength;
				Id = i;
			}
		}
		else if (ImguiDraw::AimBot_.AimGetMode == 2) {
			float  Length = (P_LoaclPlayer[i].Origin - Eyes).Length();
			if (!LengthLong || Length < LengthLong) {
				LengthLong = Length;
				Id = i;
			}
		}
	}
	if (Id != -1 && !GetPlayerDead(Id) && GetPlayerXYZ是否有效(P_LoaclPlayer[Id].index) && P_LoaclPlayer[Id].Valid)
		return Id;
	return -1;
}
void AimBot(usercmd_s* cmd) {
	Vector Eyes = mymove.MeMove.origin + mymove.MeMove.view_ofs;
	UINT Id = AimGetId();
	if (Id != -1 && !GetPlayerDead(Id) && GetPlayerXYZ是否有效(Id) && P_LoaclPlayer[Id].Valid) {
		Vector MouseAngle;
		Vector AimOrigin;
		if (P_LoaclPlayer[Id].Ent->IsInYourEyes == 1) {
			VectorAngles(P_LoaclPlayer[Id].Origin - P_Loacl.Origin, MouseAngle);
			g_pEngine->SetViewAngles(MouseAngle);
		}
		if (ImguiDraw::AimBot_.AimWhere == 1) {
			AimOrigin = P_HitBox[Id].Box[Hit_Head];
			AimOrigin.z -= 15.5f;
		}
		else {
			AimOrigin = P_HitBox[Id].Box[Aim_Arrary[ImguiDraw::AimBot_.AimWhere]];
		}
		VectorAngles(AimOrigin - Eyes, MouseAngle);
		if (ImguiDraw::AimBot_.AutoNoAngle)
			MouseAngle -= (mymove.punchangle * ImguiDraw::AimBot_.NoAngleValue);
		g_pEngine->SetViewAngles(MouseAngle);
	}
}

void AimBotSilence(usercmd_s* cmd) {
	Vector Eyes = mymove.MeMove.origin + mymove.MeMove.view_ofs;
	UINT Id = AimGetId();
	if (Id != -1 && !GetPlayerDead(Id) && GetPlayerXYZ是否有效(Id) && P_LoaclPlayer[Id].Valid) {
		Vector MouseAngle;
		Vector AimOrigin;

		if (ImguiDraw::AimBot_.AimWhere == 1) {
			AimOrigin = P_HitBox[Id].Box[Hit_Head];
			AimOrigin.z -= 15.5f;
		}
		else {
			AimOrigin = P_HitBox[Id].Box[Aim_Arrary[ImguiDraw::AimBot_.AimWhere]];
		}
		VectorAngles(AimOrigin - Eyes, MouseAngle);
		if (ImguiDraw::AimBot_.AutoNoAngle)
			MouseAngle -= (mymove.punchangle * ImguiDraw::AimBot_.NoAngleValue);
		MakeAngle(false, MouseAngle, cmd);
	}
}

void AimBotAutoKill(usercmd_s* cmd) {
	Vector Eyes = mymove.MeMove.origin + mymove.MeMove.view_ofs;
	UINT Id = AimGetId(true);
	static bool Can = false;
	if (Id != -1 && !GetPlayerDead(Id) && GetPlayerXYZ是否有效(P_LoaclPlayer[Id].index) && P_LoaclPlayer[Id].Valid) {
		Vector MouseAngle;
		Vector AimOrigin;
		if (ImguiDraw::AimBot_.AimWhere == 1) {
			AimOrigin = P_HitBox[Id].Box[Hit_Head];
			AimOrigin.z -= 15.5f;
		}
		else {
			AimOrigin = P_HitBox[Id].Box[Aim_Arrary[ImguiDraw::AimBot_.AimWhere]];
		}
		VectorAngles(AimOrigin - Eyes, MouseAngle);
		if (ImguiDraw::AimBot_.AutoNoAngle)
			MouseAngle -= (mymove.punchangle * ImguiDraw::AimBot_.NoAngleValue);
		MakeAngle(false, MouseAngle, cmd);
		if (!Can) {
			cmd->buttons |= IN_ATTACK;
			Can = true;
		}else {
			cmd->buttons &= ~IN_ATTACK;
			Can = false;
		}
		
	}
}
void AnitAimBot(usercmd_s* cmd) {
	FixMoveStart(cmd);
	if (!(cmd->buttons & IN_ATTACK) && !(cmd->buttons & IN_ATTACK2) && !(cmd->buttons & IN_USE)) {
		if (mymove.movetype == 3 && mymove.waterleave < 2 && !MainStatus->GetPlayerIsDeadByIndex(P_Loacl.Ent->index))
			cmd->viewangles.y = (float)(rand() % 361);//fmod(g_pEngine->GetClientTime() * 360.f, 360.f);
		if (cmd->viewangles.y > 180)
			cmd->viewangles.y -= 360;
	}
	FixMoveEnd(cmd);
}