#include "main.h"
#include "Cmd.h"
#include "Timer.h"
#include "ImguiDraw.h"
#include "VoxeMenu.h"
void SetVoxelMap() {
	static byte DontTouchMe = 0;
	if (DontTouchMe == 5) {
		if (VoxelFuckMap.value == 1)
			Cmd_ExecuteString((char*)XorString("vxl_humandestroy 1"), cmd_source::src_command);
		else if (VoxelFuckMap.value == 2 && (GetAsyncKeyState(84) & AsyDown))
			Cmd_ExecuteString((char*)XorString("vxl_humandestroy 1"), cmd_source::src_command);
		else
			Cmd_ExecuteString((char*)XorString("vxl_humandestroy 0"), cmd_source::src_command);
		if (VoxelFirendKill.value) {
			Cmd_ExecuteString((char*)XorString("vxl_enemyfire 1"), cmd_source::src_command);
			Cmd_ExecuteString((char*)XorString("vxl_friendlyfire 1"), cmd_source::src_command);
		}
		if (DeadLongRpn.value)
			Cmd_ExecuteString((char*)XorString("vxl_respawntime 999999999999"), cmd_source::src_command);
	}
	DontTouchMe += 1;
}
void SetZombieVoxelMap() {
	static float FuckTimer;
	if (GameTime - FuckTimer > 3.0f || GameTime - FuckTimer < -3.0f)
		FuckTimer = 0.0f;
	if ((GameTime - FuckTimer) > 0.3f) {
		if (ZombieFuckMap.value) {
			if (ZombieFuckMap.value == 1) {
				g_pEngine->pfnClientCmd((char*)XorString("vxl_zombidestroy 1"));
			}
			if (ZombieFuckMap.value == 2) {
				if (GetAsyncKeyState(82)) {
					g_pEngine->pfnClientCmd((char*)XorString("vxl_zombidestroy 1"));
				}else {
					g_pEngine->pfnClientCmd((char*)XorString("vxl_zombidestroy 0"));
				}
			}
		}
		else {
			g_pEngine->pfnClientCmd((char*)XorString("vxl_zombidestroy 0"));
		}
	}
	FuckTimer = ((GameTime - FuckTimer) > 0.3f) ? GameTime + 0.3f : FuckTimer;
}
void VoxelReset() {
	g_pEngine->pfnClientCmd((char*)XorString("vxl_restart"));
}
void VoxelSkyFun() {
	//u8"无", u8"暴风前夕", u8"多云的天空", u8"庄严的天空", u8"白天的天空"
	char* temp = (char*)alloca(255);
	memcpy(temp, XorString("vxl_skyname "), 13);
	switch ((int)(VoxelSkyValuel.value))
	{
	case 0:
		temp = strcat(temp, XorString("none"));
		break;
	case 1:
		temp = strcat(temp, XorString("de_2storm"));
		break;
	case 2:
		temp = strcat(temp, XorString("hs4_"));
		break;
	case 3:
		temp = strcat(temp, XorString("Z4line_"));
		break;
	case 4:
		temp = strcat(temp, XorString("maple_"));
		break;
	}
	g_pEngine->pfnServerCmd(temp);
}
void VoxelBuy() {
	g_pEngine->pfnServerCmd((char*)XorString("vxl_BuyZone"));
}
void VoxelBrigth() {
	switch ((int)VoxelBringht.value){
	case 1:
		g_pEngine->pfnClientCmd((char*)XorString("vxl_daylight 255 255 255;vxl_invlight 255 255 255;vxl_remove_dim_light 0"));
		break;
	case 2:
		g_pEngine->pfnClientCmd((char*)XorString("vxl_daylight 0 0 0;vxl_invlight 0 0 0;"));
		if (IsVip) {
			g_pEngine->pfnClientCmd((char*)XorString("vxl_remove_dim_light 1"));
		}
		break;
	}
}
void FriendDam() {
	if (VoxelFirendKill.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_enemyfire 1"));
		g_pEngine->pfnServerCmd((char*)XorString("vxl_friendlyfire 1"));
	}else {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_enemyfire 0"));
		g_pEngine->pfnServerCmd((char*)XorString("vxl_friendlyfire 0"));
	}
}
void NoResetTrigger() {
	if (VxlResetTrigger.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_resettrigger 0"));
	}
	else {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_resettrigger 1"));
	}
}
void DeadRpnTime() {
	if (DeadLongRpn.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_respawntime 999999999999"));
	}
	else {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_respawntime 0"));
	}
}
void VoxelZombieRedX() {
	if (ZombieRedX.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_zombiseethru 1"));
	}else{
		g_pEngine->pfnServerCmd((char*)XorString("vxl_zombiseethru 0"));
	}
}
void VoxelInitBackSet() {
	if (InitBack.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_initback 1"));
	}else{
		g_pEngine->pfnServerCmd((char*)XorString("vxl_initback 0"));
	}
}
void SetFireDam() {
	switch ((int)FireDam.value) {
	case 0:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_seekerpenalty 5"));
		break;
	case 1:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_seekerpenalty 100"));
		break;
	case 2:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_seekerpenalty 0"));
		break;
	}
}
void SetFog() {
	if (FogValue.value) {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_fogon 1"));
	}else {
		g_pEngine->pfnServerCmd((char*)XorString("vxl_fogon 0"));
	}
}
DWORD WINAPI VxlSetBlockListTest(LPVOID lpThreadParameter) {
	SetListThread* ListSet = (SetListThread*)lpThreadParameter;
	char Buff[255];
	int Inc = 0;
	auto Unk = GetUnk(0);
	if (!Unk)
		return;

	P_Unk VxlBlockList = GetUnk(0);
	//如果相等说明没有装置
	if ((ULONG)(VxlBlockList->P_BlockList) == (ULONG)((*VxlBlockList->P_BlockList)))
		return;
	P_BlockList List = *(VxlBlockList->P_BlockList);
	p_client->HUD_NoticePrint((char*)XorString(u8"正在遍历中..请等待。如果时间过长说明装置过多不是卡死。"), 0);
	do {
		P_BlockClass Block = List->NowListBlockClass;
		if (Block->IndexClass->Index == ListSet->Index) {
			sprintf(Buff, XorString("vxl_cmd %d %d %d %d %s"), ListSet->Index, Block->oring[0], Block->oring[1], Block->oring[2], ListSet->SetBuff);
			g_pEngine->pfnServerCmd(Buff);
			Sleep(100);
			Inc += 1;
			sprintf(Buff, XorString(u8"报废-正在报废:%d个装置"), Inc);
			p_client->HUD_NoticePrint(Buff, 0);
		}
		List = List->NextList;
	} while (((ULONG)(VxlBlockList->P_BlockList)) != (ULONG)List);
	sprintf(Buff, XorString(u8"报废-修改完毕.此次报废共:%d个装置"), Inc);
	p_client->HUD_NoticePrint(Buff, 0);
	return 0;
}
void KillAllPushBlock() {
	SetListThread Tmp = { 23, _c("TQwFAAAAgAABAAAA") };
	CloseHandle(CreateThread(0, 0, VxlSetBlockListTest, SetListThreadStruct(Tmp), 0, 0));
}
void KillAllDamBlock() {
	char Buff[100];
	char Buff2[255];
	DamageBlock MyBlock;
	MyBlock.Start = 0;
	MyBlock.End = 0;
	MyBlock.Timer = 0.01f;
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), Damge, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MyBlock, sizeof(DamageBlock), Buff, SubTextSize - strlen(Buff2));
	SetListThread Tmp = { Damge, Buff };
	CloseHandle(CreateThread(0, 0, VxlSetBlockListTest, SetListThreadStruct(Tmp), 0, 0));
}
void KillAllWeaponBlock() {
	char Buff[100];
	char Buff2[255];
	TheWeaponBox MyBlock;
	MyBlock.Inx = 0;
	MyBlock.IsReset = true;
	MyBlock.ResetTime = 1.f;
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), WeaponBox, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MyBlock, sizeof(TheWeaponBox), Buff, SubTextSize - strlen(Buff2));
	SetListThread Tmp = { WeaponBox, Buff };
	CloseHandle(CreateThread(0, 0, VxlSetBlockListTest, SetListThreadStruct(Tmp), 0, 0));
}

void SetFogStatc() {
	char Fog[255], Color[255];
	sprintf(Fog, XorString("vxl_fogcolor %d %d %d"), FogColor.r, FogColor.g, FogColor.b);
	sprintf(Color, XorString(u8"本次颜色: %d %d %d"), FogColor.r, FogColor.g, FogColor.b);
	g_pEngine->pfnServerCmd(Fog);
	G_VguiPrint->PrintUnf_8(4, Color, 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	switch ((int)FogStatcValue.value) {
	case 1:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_fogdensity 1.0"));
		g_pEngine->pfnServerCmd(Fog);
		break;
	case 2:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_fogdensity 0.0"));
		g_pEngine->pfnServerCmd(Fog);
		break;
	}
}
void AutoSetBright() {
	Cmd_ExecuteString(XorString("vxl_fogdensity 1.0"), cmd_source::src_command);
	Cmd_ExecuteString(XorString("vxl_fogon 1"), cmd_source::src_command);
	Cmd_ExecuteString(XorString("vxl_fogcolor 0 0 0"), cmd_source::src_command);// 设置迷雾
	Cmd_ExecuteString(XorString("vxl_skyname none"), cmd_source::src_command);//设置天空

	Cmd_ExecuteString(XorString("vxl_daylight 0 0 0"), cmd_source::src_command);
	Cmd_ExecuteString(XorString("vxl_invlight 0 0 0"), cmd_source::src_command);
	Cmd_ExecuteString(XorString("vxl_remove_dim_light 1"), cmd_source::src_command);//关灯

	Cmd_ExecuteString(XorString("vxl_visdist 1"), cmd_source::src_command);//最小化视野
}
DWORD WINAPI StartRGB(LPVOID lpThreadParameter) {
	static Timer GetTimer;
	GetTimer.Init(1.0f);
	while (VxlRGBFOG.value)
	{
		GetTimer.Updata();
		if (GetTimer.GetIsCan()) {
			Cmd_ExecuteString(XorString("vxl_fogdensity 1.0"), cmd_source::src_command);
			Cmd_ExecuteString(XorString("vxl_fogon 1"), cmd_source::src_command);

			Cmd_ExecuteString(XorString("vxl_skyname none"), cmd_source::src_command);//设置天空

			Cmd_ExecuteString(XorString("vxl_daylight 0 0 0"), cmd_source::src_command);
			Cmd_ExecuteString(XorString("vxl_invlight 0 0 0"), cmd_source::src_command);
			Cmd_ExecuteString(XorString("vxl_remove_dim_light 1"), cmd_source::src_command);//关灯

			Cmd_ExecuteString(XorString("vxl_visdist 1"), cmd_source::src_command);//最小化视野
		}
		color24 Color = { static_cast<byte>(g_pEngine->pfnRandomLong(0, 255))  ,static_cast<byte>(g_pEngine->pfnRandomLong(0, 255)),static_cast<byte>(g_pEngine->pfnRandomLong(0, 255)) };
		char Cmd[255];
		sprintf(Cmd, XorString("vxl_fogcolor %d %d %d"), Color.r, Color.b, Color.g);
		Cmd_ExecuteString(Cmd, cmd_source::src_command);
		Sleep(100);
	}
	return 0;
}
DWORD WINAPI StartMapSet(LPVOID lpThreadParameter) {
	static Timer GetTimer;
	color24 Color;
	GetTimer.Init(1.0f);
	while (VxlMapLight.value)
	{
		GetTimer.Updata();
		if (GetTimer.GetIsCan()) {
			Cmd_ExecuteString(XorString("vxl_fogdensity 1.0"), cmd_source::src_command);
			Cmd_ExecuteString(XorString("vxl_fogon 1"), cmd_source::src_command);

			Cmd_ExecuteString(XorString("vxl_skyname none"), cmd_source::src_command);//设置天空

			Cmd_ExecuteString(XorString("vxl_visdist 1"), cmd_source::src_command);//最小化视野
			if (VxlMapLight.value == 1) {
				Cmd_ExecuteString(XorString("vxl_daylight 0 0 0"), cmd_source::src_command);
				Cmd_ExecuteString(XorString("vxl_invlight 0 0 0"), cmd_source::src_command);
			}
			else if (VxlMapLight.value == 2) {
				Cmd_ExecuteString(XorString("vxl_daylight 255 255 255"), cmd_source::src_command);
				Cmd_ExecuteString(XorString("vxl_invlight 255 255 255"), cmd_source::src_command);
			}
		}
		if (VxlMapLight.value == 1) {
			Color = { 0,0,0 };
			Cmd_ExecuteString(XorString("vxl_remove_dim_light 1"), cmd_source::src_command);//关灯
		}
		else {
			Color = { 255,255,255 };
			Cmd_ExecuteString(XorString("vxl_remove_dim_light 0"), cmd_source::src_command);//开灯
		}
			
		char Cmd[255];
		sprintf(Cmd, XorString("vxl_fogcolor %d %d %d"), Color.r, Color.b, Color.g);
		Cmd_ExecuteString(Cmd, cmd_source::src_command);
		Sleep(100);
	}
	return 0;
}
void RGBFog() {
	if(VxlRGBFOG.value && IsVip)
		CloseHandle(CreateThread(0, 0, StartRGB, 0, 0, 0));
}
void SetMapLight() {
	if (VxlMapLight.value && IsVip) {
		CloseHandle(CreateThread(0, 0, StartMapSet, 0, 0, 0));
	}
}
void DontWantToRpn() {
	if (NotRpn_.value && IsVip) {
		Cmd_ExecuteString(_c("vxl_respawn 0"), cmd_source::src_command);
	}else if (!NotRpn_.value && IsVip) {
		Cmd_ExecuteString(_c("vxl_respawn 1"), cmd_source::src_command);
	}
}
void __VxlHigeBlock() {
	G_VguiPrint->PrintUnf_8(4, XorString(u8"警告！高频开启后可能会发生卡顿。已自动屏蔽其他锁定指令。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void __VxlHigeFriend() {
	G_VguiPrint->PrintUnf_8(4, XorString(u8"警告！高频开启后可能会发生卡顿。已自动屏蔽其他锁定指令。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void _VxlHigeBlock() {
	Cmd_ExecuteString(XorString("vxl_humandestroy 1"), cmd_source::src_command);
}
void _VxlHigeFriend() {
	Cmd_ExecuteString(XorString("vxl_enemyfire 1"), cmd_source::src_command);
	//Cmd_ExecuteString(XorString("vxl_friendlyfire 1"), cmd_source::src_command);
}
void LoadMapSave() {
	G_VguiPrint->PrintUnf_8(4, XorString(u8"执行完毕"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	g_pEngine->pfnServerCmd((char*)XorString("vxl_load_gamesave"));
}
void SaveMap() {
	G_VguiPrint->PrintUnf_8(4, XorString(u8"成功保存"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	g_pEngine->pfnServerCmd((char*)XorString("vxl_savenow"));
}
void GetBlockWeapon() {
	G_VguiPrint->PrintUnf_8(4, XorString(u8"刷取成功"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	g_pEngine->pfnClientCmd((char*)XorString("vxl_BuyZone;vxljunkgun;usp;p228"));
}
void CanYouSeeMe_() {
	switch ((int)VoxelSee.value)
	{
	case 1:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_visdist 1"));
		break;
	case 2:
		g_pEngine->pfnServerCmd((char*)XorString("vxl_visdist 9999"));
		break;
	}
}
void SetVxlLvSeting() {
	char Cmd[255];
	static Timer Cmd_;
	Cmd_.Init(0.3f);
	Cmd_.Updata();
	if (Cmd_.GetIsCan()) {
		if (ImguiDraw::VxlSetting.OpenVl) {
			sprintf(Cmd, XorString("vxl_lv_setting %d %d %d %d %d %d %d %d %d"), ImguiDraw::VxlSetting.VlSeting[0], ImguiDraw::VxlSetting.VlSeting[1], ImguiDraw::VxlSetting.VlSeting[2],
				ImguiDraw::VxlSetting.VlSeting[3], ImguiDraw::VxlSetting.VlSeting[4], ImguiDraw::VxlSetting.VlSeting[5], ImguiDraw::VxlSetting.VlSeting[6], 1, 0);
			Cmd_ExecuteString(XorString("vxl_lv_enable 1"), cmd_source::src_command);
			Cmd_ExecuteString(Cmd, cmd_source::src_command);
		}
		else
			Cmd_ExecuteString(XorString("vxl_lv_enable 0"), cmd_source::src_command);
	}
}
void CloseFirend_() {
	static Timer Cmd_;
	Cmd_.Init(0.3f);
	Cmd_.Updata();
	if (Cmd_.GetIsCan()) {
		Cmd_ExecuteString(XorString("vxl_enemyfire 0"), cmd_source::src_command);
	}
}

void VxlOpenLuaMenu_() {
	LuaMenu.Open();
}