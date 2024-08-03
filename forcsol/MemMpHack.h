#pragma once
class CGrenade;
struct DamageBit{
	int DamageByte;
	int IsHaveDamageAdd;
	bool IsFireFuckingYou;
};

struct WeaponFireDam {
	entvars_t* Frompev;
	int FireNum;
	float FireDam;
	bool FireCanDied;
	int FireBody;
	Vector FireOring;
	int FireDkonw;
};

using P_ShootTimed2 = CGrenade * (*)(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time, int iTeam, unsigned short usEvent);

void MpHack();
void JoinClass();
extern PULONG MaxEditc;
extern PULONG MpBuyWeapon;
extern globalvars_t** g_pGlobal;
extern ULONG HasGrenade;