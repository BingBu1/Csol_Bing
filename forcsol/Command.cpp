#include "main.h"
void FastTry() {
	static int Dont = 0;
	if (Dont < 3)
	{
		Dont += 1;
		G_VguiPrint->PrintUnf_8(0, XorString(u8"按三次后重连（防误触）"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
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
void openno() { 功能.无后.value = true; };
void closeno() { 功能.无后.value = false; };
void OpenAero() { 功能.Aero.value = true; };
void CloseAero() { 功能.Aero.value = false; };
void OpenMcj() { 功能.mcj.value = true; };
void CloseMcj() { 功能.mcj.value = false; };
void OpenBunny() { 功能.bunny.value = true; };
void CloseBunny() { 功能.bunny.value = false; };
void OpenLight() { 功能.发光.value = true; };
void CloseLight() { 功能.发光.value = false; };
void OpenSelf() { 功能.自动同步.value = true; };
void CloseSelf() { 功能.自动同步.value = false; };
void Open() { 功能.跟踪线.value = true; };
void Close() { 功能.跟踪线.value = false; };
void Hello() { 功能.hello.value = true; };
void 躲猫猫透视() { 功能.躲猫猫透视.value = true; };
void C躲猫猫透视() { 功能.躲猫猫透视.value = false; };
void 摇头() { 功能.摇头.value = true; };
void C摇头() { 功能.摇头.value = false; };
void fastrun() { 功能.fastrun.value = true; };
void Cfastrun() { 功能.fastrun.value = false; };
char NameBuff[255];
void 名称打码() {
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
void C名称打码() {
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
	g_Engine.pfnAddCommand((char*)XorString("dmmts"), 躲猫猫透视);
	g_Engine.pfnAddCommand((char*)XorString("dmmtsc"), C躲猫猫透视);
	g_Engine.pfnAddCommand((char*)XorString("mcdm"), 名称打码);
	g_Engine.pfnAddCommand((char*)XorString("mcdmc"), C名称打码);
	g_Engine.pfnAddCommand((char*)XorString("yt"), 摇头);
	g_Engine.pfnAddCommand((char*)XorString("ytc"), C摇头);
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