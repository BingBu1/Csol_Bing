#include "main.h"
#include "ImguiDraw.h"
const char* IfLocal = nullptr;
void DefCallBackFun() {
	p_client->HUD_NoticePrint((char*)XorString(u8"DefCallBack"), 0);
}
void UseCallBackFun() {
	p_client->HUD_NoticePrint((char*)XorString(u8"小键盘上下左右控制移动以及开关/PaUp PaDn翻页"), 0);
	p_client->HUD_NoticePrint((char*)XorString(u8"退格键回到功能菜单"), 0);
	p_client->HUD_NoticePrint((char*)XorString(u8"Home呼出/隐藏菜单"), 0);
	G_VguiPrint->PrintUnf_8(3, XorString(u8"小键盘上下左右控制移动以及开关/PaUp PaDn翻页"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	G_VguiPrint->PrintUnf_8(14, XorString(u8"退格键回到功能菜单"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	G_VguiPrint->PrintUnf_8(4, XorString(u8"Home呼出/隐藏菜单"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void CallBackAxe() {
	if (G_Game007->GameUiRoomState() == 6) {
		if (ImguiDraw::Setting.AxeDefine)
			G_VguiPrint->PrintUnf_8(4, XorString(u8"按住T使用，注本脚本需求弑神和神鬼开天"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	}
	else {
		G_Game007->GameUiMessageBoxUnf8(XorString(u8"提示"), XorString(u8"按住T使用，注本脚本需求弑神和神鬼开天"), 0);
	}
}
void CallBackGodAxe() {
	if (G_Game007->GameUiRoomState() == 6) {
		if (ImguiDraw::Setting.AxeGod)
			G_VguiPrint->PrintUnf_8(4, XorString(u8"按下V使用，注本脚本需求弑神和神鬼开天"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	}
	else {
		G_Game007->GameUiMessageBoxUnf8(XorString(u8"提示"), XorString(u8"按V使用，注本脚本需求弑神和神鬼开天"), 0);
	}
}
void MapMaxLing() {
	if (MapBring.value) {
		g_pEngine->OverrideLightmap(1);
		g_pEngine->SetLightmapColor(1.0f, 1.0f, 1.0f);
		g_pEngine->SetLightmapDarkness(1.f);
	}
	else {
		g_pEngine->OverrideLightmap(0);
	}
}
void NOWhite() {
	if (CNoWhite.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"无视闪光开启（包括其他屏幕效果）"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void smoke_event(event_args_t* s) { };
void FNoSmock() {
	if (NoSmoke.value) g_Engine.pfnHookEvent((char*)XorString("events/createsmoke.sc"), smoke_event);
}
void T_DelMenu() {
	if (C_DelMenu.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"F4屏蔽菜单"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void T_GetAmmo() {
	if (C_GetAmmo.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"O键获取购买子弹权限"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void BoomBoomBoom() {
	if (BoomValue.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"F3刷幽浮。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void AutoStrafe() {
	G_VguiPrint->PrintUnf_8(0, XorString(u8"按住E暂时屏蔽同步效果。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void Trigger() {
	if (trigger.value) {
		if (strcmp(XorString("local"), IfLocal)) {
			G_VguiPrint->PrintUnf_8(0, XorString(u8"当前不是本地已帮您自动取消该功能"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
			trigger.value = 0;
		}
		else {
			trigger.flags = trigger.value == 1 ? 1 : 2;
		}
	}
	else if (!trigger.value) trigger.flags = 0;
}