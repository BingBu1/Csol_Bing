#include "main.h"
void FastTry() {
	static int Dont = 0;
	if (Dont < 3)
	{
		Dont += 1;
		G_VguiPrint->PrintUnf_8(0, XorString(u8"�����κ����������󴥣�"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	}else {
		Dont = 0;
		g_pEngine->pfnClientCmd((char*)XorString("fs_lazy_precache 2;retry"));
	}
}

void MpRpn() {
	edict_s* Me = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		edict_s* GoDie = g_pEngineFuncs_t->pfnPEntityOfEntIndex(i);
		if (GoDie && GoDie != Me && !GoDie->free && GoDie->pvPrivateData) {
			g_pEngineFuncs_t->pfnClientCommand(GoDie, (char*)XorString("rpn\n"));
		}
	}
}
void openno() { ����.�޺�.value = true; };
void closeno() { ����.�޺�.value = false; };
void OpenAero() { ����.Aero.value = true; };
void CloseAero() { ����.Aero.value = false; };
void OpenMcj() { ����.mcj.value = true; };
void CloseMcj() { ����.mcj.value = false; };
void OpenBunny() { ����.bunny.value = true; };
void CloseBunny() { ����.bunny.value = false; };
void OpenLight() { ����.����.value = true; };
void CloseLight() { ����.����.value = false; };
void OpenSelf() { ����.�Զ�ͬ��.value = true; };
void CloseSelf() { ����.�Զ�ͬ��.value = false; };
void Open() { ����.������.value = true; };
void Close() { ����.������.value = false; };
void Hello() { ����.hello.value = true; };
void ��èè͸��() { ����.��èè͸��.value = true; };
void C��èè͸��() { ����.��èè͸��.value = false; };
void ҡͷ() { ����.ҡͷ.value = true; };
void Cҡͷ() { ����.ҡͷ.value = false; };
void fastrun() { ����.fastrun.value = true; };
void Cfastrun() { ����.fastrun.value = false; };
char NameBuff[255];
void ���ƴ���() {
	int myindex;
	if (g_Engine.GetViewModel()->index)
	{
		myindex = g_Engine.GetViewModel()->index;
		hud_player_info_t PlayerNameInfo;
		g_pEngine->pfnGetPlayerInfo(myindex, &PlayerNameInfo);
		memcpy(NameBuff, PlayerNameInfo.name, strlen(PlayerNameInfo.name) + 1);
		memcpy(PlayerNameInfo.name, XorString("HelloWorld\0"), 12);
	}
};
void C���ƴ���() {
	if (strlen(NameBuff)) {
		int myindex;
		myindex = g_Engine.GetViewModel()->index;
		hud_player_info_t PlayerNameInfo;
		g_pEngine->pfnGetPlayerInfo(myindex, &PlayerNameInfo);
		memcpy(PlayerNameInfo.name, NameBuff, strlen(NameBuff));
	}
}
void InitCommand() {
	/*g_Engine.pfnAddCommand((char*)XorString("opennopunchangle"), openno);
	g_Engine.pfnAddCommand((char*)XorString("closepunchangle"), closeno);
	g_Engine.pfnAddCommand((char*)XorString("openaero"), OpenAero);
	g_Engine.pfnAddCommand((char*)XorString("closeaero"), CloseAero);
	g_Engine.pfnAddCommand((char*)XorString("openmcj"), OpenMcj);
	g_Engine.pfnAddCommand((char*)XorString("closemcj"), CloseMcj);
	g_Engine.pfnAddCommand((char*)XorString("openbunny"), OpenBunny);
	g_Engine.pfnAddCommand((char*)XorString("closebunny"), CloseBunny);
	g_Engine.pfnAddCommand((char*)XorString("openlight"), OpenLight);
	g_Engine.pfnAddCommand((char*)XorString("closelight"), CloseLight);
	g_Engine.pfnAddCommand((char*)XorString("openself"), OpenSelf);
	g_Engine.pfnAddCommand((char*)XorString("closeself"), CloseSelf);
	g_Engine.pfnAddCommand((char*)XorString("open"), Open);
	g_Engine.pfnAddCommand((char*)XorString("close"), Close);
	g_Engine.pfnAddCommand((char*)XorString("sdwerfghzxcpiosafds"), Hello);
	g_Engine.pfnAddCommand((char*)XorString("dmmts"), ��èè͸��);
	g_Engine.pfnAddCommand((char*)XorString("dmmtsc"), C��èè͸��);
	g_Engine.pfnAddCommand((char*)XorString("mcdm"), ���ƴ���);
	g_Engine.pfnAddCommand((char*)XorString("mcdmc"), C���ƴ���);
	g_Engine.pfnAddCommand((char*)XorString("yt"), ҡͷ);
	g_Engine.pfnAddCommand((char*)XorString("ytc"), Cҡͷ);
	g_Engine.pfnAddCommand((char*)XorString("ft"), fastrun);
	g_Engine.pfnAddCommand((char*)XorString("ftc"), Cfastrun);*/
	//InitZombieCmd();
	/*Esp = g_Engine.pfnRegisterVariable((char*)XorString("bi_esp"), "0", 0);
	DrawName = g_Engine.pfnRegisterVariable((char*)XorString("bi_espname"), "0", 0);
	DrawWeaponOhMaybe = g_Engine.pfnRegisterVariable((char*)XorString("bi_espweapon"), "0", 0);
	PlayerAeroEsp = g_Engine.pfnRegisterVariable((char*)XorString("bi_espaero"), "0", 0);
	SpeedUp = g_Engine.pfnRegisterVariable((char*)XorString("bi_speedup"), "0", 0);*/
	Esp = new cvar_t;
	DrawName = Esp;
	DrawWeaponOhMaybe = Esp;
	PlayerAeroEsp = Esp;
	SpeedUp = Esp;
	Esp->value = 0;
	TextClassInit();
}