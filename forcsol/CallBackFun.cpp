#include "main.h"
#include "ImguiDraw.h"
const char* IfLocal = nullptr;
void DefCallBackFun() {
	p_client->HUD_NoticePrint((char*)XorString(u8"DefCallBack"), 0);
}
void UseCallBackFun() {
	p_client->HUD_NoticePrint((char*)XorString(u8"С�����������ҿ����ƶ��Լ�����/PaUp PaDn��ҳ"), 0);
	p_client->HUD_NoticePrint((char*)XorString(u8"�˸���ص����ܲ˵�"), 0);
	p_client->HUD_NoticePrint((char*)XorString(u8"Home����/���ز˵�"), 0);
	G_VguiPrint->PrintUnf_8(3, XorString(u8"С�����������ҿ����ƶ��Լ�����/PaUp PaDn��ҳ"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	G_VguiPrint->PrintUnf_8(14, XorString(u8"�˸���ص����ܲ˵�"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	G_VguiPrint->PrintUnf_8(4, XorString(u8"Home����/���ز˵�"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void CallBackAxe() {
	if (G_Game007->GameUiRoomState() == 6) {
		if (ImguiDraw::Setting.AxeDefine)
			G_VguiPrint->PrintUnf_8(4, XorString(u8"��סTʹ�ã�ע���ű�����߱��������"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	}
	else {
		G_Game007->GameUiMessageBoxUnf8(XorString(u8"��ʾ"), XorString(u8"��סTʹ�ã�ע���ű�����߱��������"), 0);
	}
}
void CallBackGodAxe() {
	if (G_Game007->GameUiRoomState() == 6) {
		if (ImguiDraw::Setting.AxeGod)
			G_VguiPrint->PrintUnf_8(4, XorString(u8"����Vʹ�ã�ע���ű�����߱��������"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
	}
	else {
		G_Game007->GameUiMessageBoxUnf8(XorString(u8"��ʾ"), XorString(u8"��Vʹ�ã�ע���ű�����߱��������"), 0);
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
		G_VguiPrint->PrintUnf_8(0, XorString(u8"�������⿪��������������ĻЧ����"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void smoke_event(event_args_t* s) { };
void FNoSmock() {
	if (NoSmoke.value) g_Engine.pfnHookEvent((char*)XorString("events/createsmoke.sc"), smoke_event);
}
void T_DelMenu() {
	if (C_DelMenu.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"F4���β˵�"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void T_GetAmmo() {
	if (C_GetAmmo.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"O����ȡ�����ӵ�Ȩ��"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void BoomBoomBoom() {
	if (BoomValue.value)
		G_VguiPrint->PrintUnf_8(0, XorString(u8"F3ˢ�ĸ���"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void AutoStrafe() {
	G_VguiPrint->PrintUnf_8(0, XorString(u8"��סE��ʱ����ͬ��Ч����"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}
void Trigger() {
	if (trigger.value) {
		if (strcmp(XorString("local"), IfLocal)) {
			G_VguiPrint->PrintUnf_8(0, XorString(u8"��ǰ���Ǳ����Ѱ����Զ�ȡ���ù���"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
			trigger.value = 0;
		}
		else {
			trigger.flags = trigger.value == 1 ? 1 : 2;
		}
	}
	else if (!trigger.value) trigger.flags = 0;
}