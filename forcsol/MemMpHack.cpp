#include "main.h"
#include "MemMpHack.h"
PULONG MaxEditc = nullptr;
PULONG MpBuyWeapon = nullptr;
P_ShootTimed2 ShootTimed2 = nullptr;
ULONG HasGrenade = 0;
void MpHack() {
	edict_s* P_Edict[50];
	memset(P_Edict, 0, sizeof(P_Edict));
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++){
		P_Edict[i] = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
	}
	if (MpHeal.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				P_Edict[i]->v.health = 9999999.0f;
				P_Edict[i]->v.max_health = 9999999.0f;
			}
		}
	}
	if (MpSpeed.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				g_pEngineFuncs_t->pfnSetClientMaxspeed(P_Edict[i], 399);
			}
		}
	}
	if (MpFire.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				CBasePlayer* Player = (CBasePlayer*)P_Edict[i]->pvPrivateData;
				PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
				if (*p_ActiveItem) {
					float* Fire = (float*)((*((PULONG)p_ActiveItem)) + FireCooling);
					*Fire = static_cast<float>(-1);
				}
			}
		}
	}
	if (MpRightFire.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				CBasePlayer* Player = (CBasePlayer*)P_Edict[i]->pvPrivateData;
				PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
				if (*p_ActiveItem) {
					float* Fire = (float*)((*((PULONG)p_ActiveItem)) + RightFireCooling);
					*Fire = static_cast<float>(-0.001000000047);
				}
			}
		}
	}
	if (MpAllInfAmmo.value) {
		static byte SetStaic = 0;
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				CBasePlayer* Player = (CBasePlayer*)P_Edict[i]->pvPrivateData;
				PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
				if (*p_ActiveItem) {
					PCHAR Ammo = (PCHAR)((*((PULONG)p_ActiveItem)) + Ammo1);
					PULONG _Ammo3 = (PULONG)((*((PULONG)p_ActiveItem)) + Ammo3);
					(*(PULONG)Ammo) = 200;
					(*(PULONG)(Ammo + 8)) = 200;
					if (MpAllInfAmmo.value == 2 || MpAllInfAmmo.value == 3) {
						if (MpAllInfAmmo.value  ==  3) {
							PFLOAT p_WeaponTimer = (PFLOAT)((*((PULONG)p_ActiveItem)) + WeaponTimer);
							*p_WeaponTimer = 1;
						}
						switch (SetStaic)
						{
						case 0:
							*_Ammo3 = 1;
							break;
						case 1:
							*_Ammo3 = 2;
							break;
						default:
							*_Ammo3 = 8;
							break;
						}
					}
				}
			}
		}
		SetStaic = (SetStaic <= 2) ? (SetStaic = SetStaic + 1) : 0;
	}
	if (MpFlySky.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				if (P_Edict[i]->v.button & IN_JUMP) {
					P_Edict[i]->v.velocity.z = 250;
				}
			}
		}
	}
	if (MpBuyMyG.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				ClientPrint(P_Edict[i], 4, XorString(u8"欢迎来到神仙房,买G+群427521116"), 0, 0, 0, 0, 1, 0, 0, 0);
			}
		}
	}
	if (MpAngle.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				P_Edict[i]->v.punchangle = { 0.0f , 0.0f , 0.0f };
			}
		}
	}
	if (MpLockWeapon.value) {
		edict_s* Me = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++) {
			if (P_Edict[i] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData && P_Edict[i] != Me) {
				CBasePlayer* Player = (CBasePlayer*)P_Edict[i]->pvPrivateData;
				PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
				if (*p_ActiveItem) {
					*p_ActiveItem = *(PULONG)(((char*)Me->pvPrivateData) + pActiveItem);//共享房主武器
				}
			}
		}
	}
	if (MeMpHeal.value) {
		if (P_Edict[1] && !P_Edict[1]->free && P_Edict[1]->pvPrivateData) {
			P_Edict[1]->v.health = 9999999.0f;
			P_Edict[1]->v.max_health = 9999999.0f;
		}
	}
	if (MeMpFire.value) {
		if (P_Edict[1] && !P_Edict[1]->free && P_Edict[1]->pvPrivateData) {
			CBasePlayer* Player = (CBasePlayer*)P_Edict[1]->pvPrivateData;
			PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
			if (*p_ActiveItem) {
				float* Fire = (float*)((*((PULONG)p_ActiveItem)) + FireCooling);
				*Fire = -1;
			}
		}
	}
	if (MeMpRightFire.value) {
		if (P_Edict[1] && !P_Edict[1]->free && P_Edict[1]->pvPrivateData) {
			CBasePlayer* Player = (CBasePlayer*)P_Edict[1]->pvPrivateData;
			PULONG p_ActiveItem = (PULONG)(((char*)Player) + pActiveItem);
			if (*p_ActiveItem) {
				float* Fire = (float*)((*((PULONG)p_ActiveItem)) + RightFireCooling);
				*Fire = -1;
			}
		}
	}
	if (MeMpMouseTp.value) {
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++){
			g_pEngineFuncs_t->pfnMakeVectors(P_Edict[1]->v.v_angle);
			Vector End, Dir = (*g_pGlobal)->v_forward * 128;
			End = P_Edict[1]->v.origin + P_Edict[1]->v.view_ofs + Dir;
			if (P_Edict[i] && P_Edict[i] != P_Edict[1] && !P_Edict[i]->free && P_Edict[i]->pvPrivateData) {
				std::string_view ClassName = STRING(P_Edict[i]->v.classname);
				if (ClassName == XorString("player")) {
					P_Edict[i]->v.origin = End;
				}
			}
		}
	}
	if (MeMpSpeedHack.value) {
		g_pEngineFuncs_t->pfnSetClientMaxspeed(P_Edict[1], 399.0f);
	}
	if (MeMpNoAngle.value) {
		if (P_Edict[1] && !P_Edict[1]->free && P_Edict[1]->pvPrivateData) {
			VectorClear(P_Edict[1]->v.punchangle);
		}
	}
	if (MeMpMouseMonsterTp.value) {
		for (ULONG i = 1; i < *MaxEditc; i++) {
			edict_s* T_Edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
			g_pEngineFuncs_t->pfnMakeVectors(P_Edict[1]->v.v_angle);
			Vector End, Dir = (*g_pGlobal)->v_forward * 128;
			End = P_Edict[1]->v.origin + P_Edict[1]->v.view_ofs + Dir;
			if (T_Edict && T_Edict != P_Edict[1] && !T_Edict->free && T_Edict->pvPrivateData) {
				if (T_Edict->v.classname) {
					std::string_view ClassName = STRING(T_Edict->v.classname);
					if (ClassName == XorString("monster_entity")) {
						T_Edict->v.origin = End;
					}
				}
			}
		}
	}
	if (MpGrad.value) {
		edict_s* P_edict = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		CBasePlayer* P_Player = (CBasePlayer*)P_edict->pvPrivateData;
		if (ShootTimed2) {
			static auto i = 1;
			*(PULONG)((ULONG)(P_edict->pvPrivateData) + HasGrenade) = i;
			g_pEngineFuncs_t->pfnMakeVectors(P_Player->pev->v_angle + P_Player->pev->punchangle);
			Vector Speed = (*g_pGlobal)->v_forward * 750 + P_Player->pev->velocity;
			ShootTimed2(P_Player->pev, P_edict->v.origin, Speed, 1.5, p_client->HUD_GetPlayerTeam(1), 10);
			i = (i <= 19) ? i + 1 : 0;
		}
	}
	if (GetAsyncKeyState(VK_F12) & AsyPush)
	{
		edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		test->v.health = 999666999.0f;
		test->v.max_health = 999666999.0f;
		CBasePlayer* P_Player = (CBasePlayer*)test->pvPrivateData;
		for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
		{
			edict_s* GoDie = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
			if (GoDie && GoDie != test && !GoDie->free && GoDie->pvPrivateData) {
				CBasePlayer* Player = (CBasePlayer*)GoDie->pvPrivateData;
				if (Player->pev->team != test->v.team) {
					DamageBit Dam = { 0,1 ,0 };
					TakeDamage(Player, Player->pev, P_Player->pev, 100000, DMG_FALL, &Dam);
				}
				g_pEngineFuncs_t->pfnClientCommand(GoDie, (char*)XorString("gl_fog 0\n"));
				RemoveAllItems(0, GoDie);
				GivePlayerItemForName(XorString("weapon_sgmissile"), GoDie);
				GivePlayerItemForName(XorString("weapon_laserguide"), GoDie);
				g_pEngineFuncs_t->pfnClientCommand(GoDie, (char*)XorString("weapon_laserguide\n"));
			}
		}
		G_VguiPrint->PrintUnf_8(3, XorString(u8"全房去黑雾完毕"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		if (test && !test->free && test->pvPrivateData)
		{
			RemoveAllItems(0, test);
			GivePlayerItemForName(XorString("weapon_mountgun"), test);
			g_pEngineFuncs_t->pfnClientCommand(test, (char*)XorString("gl_fog 0\n"));
			g_pEngineFuncs_t->pfnClientPrintf(test, print_center, XorString("Hello I Am God You Are Fog is mu da mu da"));
			g_pEngineFuncs_t->pfnPrecacheModel((char*)XorString("models/monster/kite.mdl"));
			g_pEngineFuncs_t->pfnSetModel(test, XorString("models/monster/kite.mdl"));//之前的尝试设置模型
			char* model[] = { (char*)XorString("allstarchicken") };//小鸡
			char* infobuffer = g_pEngineFuncs_t->pfnGetInfoKeyBuffer(test);//ClientKey
			if (strcmp(g_pEngineFuncs_t->pfnInfoKeyValue(infobuffer, (char*)XorString("model")), model[0]))
				g_pEngineFuncs_t->pfnSetClientKeyValue(1, infobuffer, (char*)XorString("model"), model[0]);//改变ClientKey模型,怪物模型无法设置
		}
	}
}