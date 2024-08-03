#include "main.h"
#include "MemMpHack.h"
#include "Mymath.h"
#include "JoinLocal.h"
#include <string>
#include <vector>
PULONG CreateThis = nullptr;
PULONG SvGameAddFullPuck = nullptr;
ULONG OldSvGameAddFullPuck = NULL;
ULONG FindBossInxCall = NULL;
ULONG ChaCheTheEditc = NULL;
ULONG ChaCheThis = NULL;
void ClientPrint(edict_t* client, int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4, int Msg_dst, int Idnt2, int Idnt3, int Idnt4)
{
	g_pEngineFuncs_t->pfnMessageBegin(Msg_dst, 0x4B, NULL, client);
	g_pEngineFuncs_t->pfnWriteByte(msg_dest);
	g_pEngineFuncs_t->pfnWriteByte(Idnt2);
	g_pEngineFuncs_t->pfnWriteByte(Idnt3);
	g_pEngineFuncs_t->pfnWriteByte(Idnt3);
	g_pEngineFuncs_t->pfnWriteString(msg_name);
	if (param1)
		g_pEngineFuncs_t->pfnWriteString(param1);

	if (param2)
		g_pEngineFuncs_t->pfnWriteString(param2);

	if (param3)
		g_pEngineFuncs_t->pfnWriteString(param3);

	if (param4)
		g_pEngineFuncs_t->pfnWriteString(param4);

	g_pEngineFuncs_t->pfnMessageEnd();
}

void GivePlayerItemForName(const char* ItemName, edict_t* Player)
{
	typedef void(__thiscall* Fun)(PVOID, const char*, bool);
	static Fun PFun = (Fun)(((DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("weapon_bazooka"))) + 0x5);
	if (PFun) {
		PFun(Player->pvPrivateData, ItemName, 1);
	}
}
void RemoveAllItems(BOOL removeSuit, edict_t* Player) {
	typedef void(__thiscall* Fun)(PVOID, BOOL);
	static Fun PFun = (Fun)(((DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("weapon_thanatos7"))) + 0x5F);
	if (PFun) {
		PFun(Player->pvPrivateData, removeSuit);
	}
}
void TakeDamage(CBasePlayer* This, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType, DamageBit* bitsDamage) {
	using TakeDamage2 = void(__thiscall*)(CBasePlayer* This, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, int bitsDamageType, DamageBit* Unk);
	TakeDamage2 PFun = (TakeDamage2)(((DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("weapon_rpg7"))) + 0x23);
	if (((int)PFun) > 0x1000) {
		PFun(This, pevInflictor, pevAttacker, flDamage, bitsDamageType, bitsDamage);
	}
}
CBaseEntity* SpawnMosterCall(int Unk, ULONG MosterInxm, int Unk2, float* velocity, float* MosterBox){
	using CreateMoster = CBasePlayer * (__thiscall*)(ULONG This, int Unk, ULONG MosterInxm, int Unk2, float* velocity, float* MosterBox);
	using FindBossInx = PULONG(__thiscall*)(ULONG This, PULONG BossInx);
	using ChaCheBoss = PULONG(__thiscall*)(ULONG This, ULONG BossInx);
	CreateMoster PFun = (CreateMoster)(((DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("cronobotics54_missile"))) + 0x28);
	FindBossInx PFindBossInx = (FindBossInx)CalcCallBase(FindBossInxCall);
	ChaCheBoss PChaCheBoss = (ChaCheBoss)CalcCallBase(ChaCheTheEditc);
	if ((int)PFun > 0x1000 && (int)PFindBossInx > 0x1000) {
		/*PULONG MosterInx = PFindBossInx(ChaCheThis, &MosterInxm);
		PChaCheBoss(*CreateThis, MosterInxm);*/
		return PFun(*CreateThis, Unk, MosterInxm, Unk2, velocity, MosterBox);
	}
	return nullptr;
}

CBaseEntity* Create(const char* szName, const Vector& vecOrigin, const Vector& vecAngles, edict_t* pentOwner) {
	using Create_ = CBaseEntity * (*)(const char* szName, const Vector& vecOrigin, const Vector& vecAngles, edict_t* pentOwner, bool Unk);
	static Create_ PFun = (Create_)(((DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("weapon_at4"))) + 0x5A);
	return PFun(szName, vecOrigin, vecAngles, pentOwner, 0);
}

void RemveAllWeapon() {
	char Buff[255];
	hud_player_info_t PlayerNameInfo;
	int myindex = g_Engine.GetViewModel()->index;
	g_pEngine->pfnGetPlayerInfo(myindex, &PlayerNameInfo);
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData) {
			RemoveAllItems(0, P_Edict);
			sprintf(Buff, XorString(u8"%s到你身边把你的武器扔进了垃圾堆"), PlayerNameInfo.name);
			ClientPrint(P_Edict, 4, Buff, 0, 0, 0, 0, 1, 0, 0, 0);
		}
	}
}
void KillAll() {
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	CBasePlayer* FuckEd = (CBasePlayer*)(Player->pvPrivateData);
	g_pEngineFuncs_t->pfnCVarSetFloat(XorString("mp_friendlyfire"), 1);
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData && P_Edict != Player) {
			int myindex = g_Engine.GetViewModel()->index;
			char Buff[255];
			hud_player_info_t PlayerNameInfo;
			g_pEngine->pfnGetPlayerInfo(myindex, &PlayerNameInfo);
			sprintf(Buff, XorString(u8"%s是神他说你死吧，所以你就死了。"), PlayerNameInfo.name);
			ClientPrint(P_Edict, 4, Buff, 0, 0, 0, 0, 1, 0, 0, 0);
			DamageBit Dam = { 0,1 ,0 };
			TakeDamage(((CBasePlayer*)P_Edict->pvPrivateData), ((CBasePlayer*)P_Edict->pvPrivateData)->pev, FuckEd->pev, 10000000, DMG_FALL, &Dam);
		}
	}
	g_pEngineFuncs_t->pfnCVarSetFloat(XorString("mp_friendlyfire"), 0);
}
void KillAllMonster() {
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	CBasePlayer* FuckEd = (CBasePlayer*)(Player->pvPrivateData);
	for (ULONG i = 1; i < *MaxEditc; i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData && P_Edict != Player) {
			if (P_Edict->v.classname) {
				const char* ClassName = (*g_pGlobal)->pStringBase + P_Edict->v.classname;
				if (!strcmp(ClassName, XorString("monster_entity"))) {
					CBasePlayer* P_MonsterClass = (CBasePlayer*)P_Edict->pvPrivateData;
					if (P_MonsterClass->pev->health && P_MonsterClass) {
						DamageBit Dam = { 0,1,0 };
						P_MonsterClass->TakeDamage(P_MonsterClass->pev, FuckEd->pev, 99999999.0f, (DMG_NEVERGIB | DMG_BULLET), &Dam);
					}
				}
			}
		}
	}
}
void FireDamPlayer() {
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	CBasePlayer* FuckEd = (CBasePlayer*)(Player->pvPrivateData);
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData && P_Edict != Player) {
			if (P_Edict->v.classname) {
				WeaponFireDam* Dam = reinterpret_cast<WeaponFireDam*>(reinterpret_cast<ULONG32>(P_Edict->pvPrivateData) + NewFireDam);
				Dam->FireDam = 10000; //灼烧伤害
				Dam->FireNum = 10; //灼烧次数
				Dam->FireCanDied = true;
				Dam->FireBody = 1;
				VectorCopy(Dam->FireOring, P_Edict->v.origin);
				Dam->Frompev = FuckEd->pev; //灼烧来自谁
			}
		}
	}
	
}
void GiveYouFaceABox() {
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	CBasePlayer* FuckEd = (CBasePlayer*)(Player->pvPrivateData);
	g_pEngineFuncs_t->pfnCVarSetFloat(XorString("mp_friendlyfire"), 1);
	for (int i = 2; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData) {
			ULONG DmgInx = DMG_GENERIC;
			switch ((int)MpFuckInxCv.value)
			{
			case 0:
				break;
			case 1:
				DmgInx = DMG_BURN;
				break;
			case 2:
				DmgInx = DMG_FALL;
				break;
			case 3:
				DmgInx = DMG_RADIATION;
				break;
			case 4:
				DmgInx = DMG_FALL;
				break;
			case 5:
				DmgInx = DMG_DROWN;
				break;
			case 6:
				DmgInx = DMG_ACID;
				break;
			case 7:
				DmgInx = DMG_SLOWFREEZE;
				break;
			case 8:
				DmgInx = DMG_EXPLOSION;
				break;
			default:
				DmgInx = DMG_SHOWNHUD;
				break;
			}
			DamageBit Dam = { 0,1 ,0 };
			TakeDamage(((CBasePlayer*)P_Edict->pvPrivateData), ((CBasePlayer*)P_Edict->pvPrivateData)->pev, FuckEd->pev, 10, DmgInx, &Dam);
			int myindex = g_Engine.GetViewModel()->index;
			char Buff[255];
			hud_player_info_t PlayerNameInfo;
			g_pEngine->pfnGetPlayerInfo(myindex, &PlayerNameInfo);
			sprintf(Buff, XorString(u8"%s给了全房所有人一个拳头"), PlayerNameInfo.name);
			ClientPrint(P_Edict, 4, Buff, 0, 0, 0, 0, 1, 0, 0, 0);
			ClientPrint(Player, 4, Buff, 0, 0, 0, 0, 1, 0, 0, 0);
		}
	}
	g_pEngineFuncs_t->pfnCVarSetFloat(XorString("mp_friendlyfire"), 0);
}
void CreateFlyHen() {
	G_VguiPrint->PrintUnf_8(0, XorString(u8"本功能为测试版,仅支持一部分地图"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	int MosterInx = 0;
	switch ((int)MpSetsv.value)
	{
	case 0:
		MosterInx = 红色小奥;
		break;
	case 1:
		MosterInx = 本图小BOSS;
		break;
	case 2:
		MosterInx = 1;
		break;
	default:
		MosterInx = 2;
		break;
	}
	float c[3] = { 0 };
	CBaseEntity * pEnt = SpawnMosterCall(1, MosterInx, 1, Player->v.origin +  (*g_pGlobal)->v_forward * 128, c);
	if (pEnt) {
		pEnt->pev->rendermode = 1;//是否贴身绘制
		pEnt->pev->renderamt = 255; //绘制大小
		pEnt->pev->rendercolor.x = 255;
		pEnt->pev->rendercolor.y = 215;
		pEnt->pev->rendercolor.z = 0;
		pEnt->pev->renderfx = kRenderFxGlowShell;
	}
	//Create("monster_zombie", Player->v.origin + (*g_pGlobal)->v_forward * 128, c, 0, 0);
	/*SpawnMosterCall(1, FlyHen, 1, Player->v.origin, c);
	SpawnMosterCall(1, FlyHen2, 1, Player->v.origin, c);
	SpawnMosterCall(1, FlyHen3, 1, Player->v.origin, c);*/
}

int MyAddToFullPack(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet) {
	using AddToFullPack = int (*)(struct entity_state_s* state, int e, edict_t* ent, edict_t* host, int hostflags, int player, unsigned char* pSet);
	AddToFullPack Oldcall = (AddToFullPack)(OldSvGameAddFullPuck);
	if (trigger.flags != 2)
		return Oldcall(state, e, ent, host, hostflags, player, pSet);
	if (Oldcall && trigger.flags == 2) {
		auto oldEffects = ent->v.effects;
		auto oldRendermode = ent->v.rendermode;
		auto oldRenderColor = ent->v.rendercolor;
		auto oldRenderAmount = ent->v.renderamt;
		auto oldRenderFx = ent->v.renderfx;
		auto oldPlayereffects = NULL;
		const char* classname = (*g_pGlobal)->pStringBase + ent->v.classname;
		if (MpLeave.value) {
			if (!strcmp(classname, XorString("player"))) {
				if (ent == g_pEngineFuncs_t->pfnPEntityOfEntIndex(1)) {
					oldPlayereffects = ent->v.effects;
					ent->v.effects |= EF_NODRAW;
				}
			}
		}
		bool is_trigger = (strncmp(classname, XorString("trigger_"), 8) == 0 || strncmp(classname, XorString("zbs"), 3) == 0);
		if (is_trigger) {
			ent->v.effects &= ~EF_NODRAW;
			ent->v.rendermode = kRenderTransColor;
			if (ent->v.solid == SOLID_NOT && strcmp(classname + 8, XorString("transition")) != 0)
				ent->v.renderfx = kRenderNormal;
			else
				ent->v.renderfx = kRenderFxPulseFast;
			GetColor(classname, ent->v.rendercolor.x, ent->v.rendercolor.y, ent->v.rendercolor.z);
			ent->v.renderamt = aerorgb;
			if (ent->v.renderamt > 200.0f) {
				ent->v.renderamt = 200;
			}
		}
		else if (!is_trigger && MpDrawAll.value) {
			ent->v.effects &= ~EF_NODRAW;
			ent->v.rendermode = kRenderNormal;
			GetColor(classname, ent->v.rendercolor.x, ent->v.rendercolor.y, ent->v.rendercolor.z);
			ent->v.renderamt = aerorgb;
			if (ent->v.renderamt > 200.0f) {
				ent->v.renderamt = 200;
			}
		}
		auto ret = Oldcall(state, e, ent, host, hostflags, player, pSet);
		ent->v.effects = oldEffects;
		ent->v.rendermode = oldRendermode;
		ent->v.rendercolor = oldRenderColor;
		ent->v.renderamt = oldRenderAmount;
		ent->v.renderfx = oldRenderFx;
		if (oldPlayereffects) {
			ent->v.effects = oldPlayereffects;
		}
		return ret;
	}
	return 0;
}

void Mp都给老子飞() {
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		ClientPrint(P_Edict, 4, XorString(u8"感受神的力量"), 0, 0, 0, 0, 1, 0, 0, 0);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData) {
			P_Edict->v.velocity.z = 100000.0f;
			P_Edict->v.velocity.x *= 100000.0f;
			P_Edict->v.velocity.y *= 100000.0f;
		}
	}
}
void Svdex() {
	edict_s* Player = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	float FuckTime = ((*g_pGlobal)->time) + 3;
	while ((FuckTime - ((*g_pGlobal)->time)) >= 0) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
			{
				if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData) {
					char Buff[255];
					sprintf(Buff, XorString(u8"还有%f秒您就要掉线了,当然除了房主."), FuckTime - ((*g_pGlobal)->time));
					ClientPrint(P_Edict, 4, Buff, 0, 0, 0, 0, 1, 0, 0, 0);
				}
			}
			Sleep(1);
		}
	}
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		{
			if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData && P_Edict != Player) {
				GivePlayerItemForName(XorString("weapon_svdex"), P_Edict);
			}
		}
	}
}
void 送你一个大礼物() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Svdex, NULL, 0, NULL);
}
void MpSetModle() {
	const std::vector<std::string> model = { XorString("Null"),XorString("allstarchicken") ,XorString("allstarrevenant"),XorString("allstarball"),XorString("allstardron"),XorString("hero"),XorString("allstarsnow"),XorString("allstarmogi") };//模型名
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
		edict_s* P_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (P_Edict && !P_Edict->free && P_Edict->pvPrivateData) {
			char* infobuffer = g_pEngineFuncs_t->pfnGetInfoKeyBuffer(P_Edict);//ClientKey
			g_pEngineFuncs_t->pfnSetClientKeyValue(i, infobuffer, _c("model"), (char*)model[(int)MpMyModle.value].c_str());//改变ClientKey模型,怪物模型无法设置
			ClientPrint(P_Edict, 4, XorString(u8"都给老子变。"), 0, 0, 0, 0, 1, 0, 0, 0);
		}
	}
}
void JoinClass(){
	JoinLocal.JoinLocal();
}