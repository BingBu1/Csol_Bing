#include "GodAxeAuto.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "CallBackFun.h"
using namespace ImguiDraw;
void GodAxeAuto::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"神鬼刷左宏"), ImVec2(-1, 0));
	if (ImGui::Checkbox(XorString(u8"神鬼左键无影快刀"), &Setting.AxeDefine))
		CallBackAxe();
	ImGui::PushItemWidth(60);
	ImGui::InputFloat(XorString(u8"切换延迟"), &Setting.AxeSleep); ImGui::SameLine();
	ImGui::Combo(XorString(u8"使用模式"), &Setting.AxeMode, XorString(u8"按下时\0切换\0\0")); ImGui::SameLine();
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"神鬼无敌宏"), ImVec2(-1, 0));
	if (ImGui::Checkbox(XorString(u8"神鬼无缝无敌宏"), &Setting.AxeGod))
		CallBackGodAxe();
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::Combo(XorString(u8"选择模式"), &Setting.AxeGodModeIsMe, XorString(u8"辅助自动\0我要自己调！\0\0"));
	if (!Setting.AxeGodModeIsMe) {
		ImGui::Combo(XorString(u8"攻击模式"), &Setting.AxeGodIsme, XorString(u8"不出重击\0出重击\0\0"));
		switch (Setting.AxeGodIsme)
		{
		case 0:
			Setting.AxeGodSleep[0] = 250;
			Setting.AxeGodSleep[1] = 1400;
			break;
		case 1:
			Setting.AxeGodSleep[0] = 140;
			Setting.AxeGodSleep[1] = 2000;
			break;
		}
	}
	else {
		ImGui::InputInt(XorString(u8"右键按下时间(ms)"), &Setting.AxeGodSleep[0], 0, 0); ImGui::SameLine();
		ImGui::InputInt(XorString(u8"左键键按下时间(ms)"), &Setting.AxeGodSleep[1], 0, 0);
	}
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"神鬼宏是否强制购买"), ImVec2(-1, 0));
	ImGui::Combo(XorString(u8"强制购买"), &Setting.AxeBuyMode, XorString(u8"是\0否\0\0"));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& GodAxeAuto::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"神鬼脚本"),xorstr_(u8"脚本功能"),false };
	return info;
}
