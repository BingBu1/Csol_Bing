#include "main.h"
#include "hitbox.h"
#include "Player.h"
#include "Esp.h"
#include "ImguiDraw.h"
PlayerLoaclInfo P_LoaclPlayer[33];
LoaclPlayer P_Loacl;
HitBox P_HitBox[33];
int Cstrike_SequenceInfo[] =
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, // 0..9   
	0,	1,	2,	0,	1,	2,	0,	1,	2,	0, // 10..19 
	1,	2,	0,	1,	1,	2,	0,	1,	1,	2, // 20..29 
	0,	1,	2,	0,	1,	2,	0,	1,	2,	0, // 30..39 
	1,	2,	0,	1,	2,	0,	1,	2,	0,	1, // 40..49 
	2,	0,	1,	2,	0,	0,	0,	8,	0,	8, // 50..59 
	0, 16,	0, 16,	0,	0,	1,	1,	2,	0, // 60..69 
	1,	1,	2,	0,	1,	0,	1,	0,	1,	2, // 70..79 
	0,	1,	2, 32, 40, 32, 40, 32, 32, 32, // 80..89
	33, 64, 33, 34, 64, 65, 34, 32, 32, 4, // 90..99
	4,	4,	4,	4,	4,	4,	4,	4,	4,	4, // 100..109
	4,	4,	4,	4,	4,	4,	4,	4,	4,	4	// 110..119
};
void ZeroPlayerInfo() {
	memset(P_HitBox, 0, sizeof(P_HitBox));
	memset(P_LoaclPlayer, 0, sizeof(P_LoaclPlayer));
}
void UpdataPlayerInfo(cl_entity_s *ent) {
	if (ent->player)
	{
		pmtrace_t Pm;
		auto TaceFlag = (ImguiDraw::AimBot_.NotGlass) ? (PM_GLASS_IGNORE | PM_STUDIO_IGNORE | PM_STUDIO_BOX) : (PM_STUDIO_IGNORE | PM_STUDIO_BOX);
		P_LoaclPlayer[ent->index].Ent = ent;
		P_LoaclPlayer[ent->index].team = p_client->HUD_GetPlayerTeam(ent->index);
		P_LoaclPlayer[ent->index].index = ent->index;
		P_LoaclPlayer[ent->index].Origin = (ent->origin.x && ent->origin.y && ent->origin.z) ? ent->origin : ent->curstate.origin;
		g_pEngine->pEventAPI->EV_SetTraceHull(2);
		g_pEngine->pEventAPI->EV_PlayerTrace(mymove.MeMove.origin + mymove.MeMove.view_ofs, P_LoaclPlayer[ent->index].Origin, TaceFlag, -1, &Pm);
		P_LoaclPlayer[ent->index].IsVisible = (Pm.fraction >= 1.0f) ? true : false;
		P_LoaclPlayer[ent->index].Valid = (isValidEnt(ent) && GetPlayerXYZÊÇ·ñÓÐÐ§(ent->index)) ? true : false;
		model_t* pModel = g_pStudioApi->SetupPlayerModel(ent->index);
		if (pModel) {
			studiohdr_t* p_StdioHeader = (studiohdr_t*)g_pStudioApi->Mod_Extradata(pModel);
			BoneMatrix* p_BoneMatrix = (BoneMatrix*)g_pStudioApi->StudioGetBoneTransform();
			mstudiobbox_t* pbboxes = (mstudiobbox_t*)((byte*)p_StdioHeader + p_StdioHeader->hitboxindex);
			Vector vBBMin, vBBMax;
			for (int c = 0; c < p_StdioHeader->numhitboxes; c++) {
				Matrix3x4_VectorTransform((*p_BoneMatrix)[pbboxes[c].bone], pbboxes[c].bbmin, vBBMin);
				Matrix3x4_VectorTransform((*p_BoneMatrix)[pbboxes[c].bone], pbboxes[c].bbmax, vBBMax);
				P_HitBox[ent->index].Box[c] = (vBBMin + vBBMax) * 0.5f;
				P_HitBox[ent->index].BoxNum = p_StdioHeader->numhitboxes;
			}
		}
	}
}
void UpdataLoaclPlayerInfo() {
	cl_entity_s* localEnt = g_Engine.GetViewModel();
	P_Loacl.Ent = localEnt;
	P_Loacl.team = p_client->HUD_GetPlayerTeam(localEnt->index);
	P_Loacl.index = localEnt->index;
	P_Loacl.Origin = (localEnt->origin) ? localEnt->origin : localEnt->curstate.origin;
}
bool isValidEnt(cl_entity_s* ent)
{
	auto Loacl = g_Engine.GetLocalPlayer();
	if ((ent->index != Loacl->index) && !(ent->curstate.effects & EF_NODRAW) && ent->player && (ent->model->name != 0 || ent->model->name != "") && !(ent->curstate.messagenum < Loacl->curstate.messagenum) && ent->curstate.movetype != 6 && ent->curstate.movetype != 0)
		return true;
	else
		return false;
}
int GetSequence(cl_entity_s* Ent) {
	return Cstrike_SequenceInfo[Ent->curstate.sequence];
}