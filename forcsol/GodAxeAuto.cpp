#include "GodAxeAuto.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "CallBackFun.h"
using namespace ImguiDraw;
void GodAxeAuto::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"���ˢ���"), ImVec2(-1, 0));
	if (ImGui::Checkbox(XorString(u8"��������Ӱ�쵶"), &Setting.AxeDefine))
		CallBackAxe();
	ImGui::PushItemWidth(60);
	ImGui::InputFloat(XorString(u8"�л��ӳ�"), &Setting.AxeSleep); ImGui::SameLine();
	ImGui::Combo(XorString(u8"ʹ��ģʽ"), &Setting.AxeMode, XorString(u8"����ʱ\0�л�\0\0")); ImGui::SameLine();
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"����޵к�"), ImVec2(-1, 0));
	if (ImGui::Checkbox(XorString(u8"����޷��޵к�"), &Setting.AxeGod))
		CallBackGodAxe();
	ImGui::SameLine();
	ImGui::PushItemWidth(80);
	ImGui::Combo(XorString(u8"ѡ��ģʽ"), &Setting.AxeGodModeIsMe, XorString(u8"�����Զ�\0��Ҫ�Լ�����\0\0"));
	if (!Setting.AxeGodModeIsMe) {
		ImGui::Combo(XorString(u8"����ģʽ"), &Setting.AxeGodIsme, XorString(u8"�����ػ�\0���ػ�\0\0"));
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
		ImGui::InputInt(XorString(u8"�Ҽ�����ʱ��(ms)"), &Setting.AxeGodSleep[0], 0, 0); ImGui::SameLine();
		ImGui::InputInt(XorString(u8"���������ʱ��(ms)"), &Setting.AxeGodSleep[1], 0, 0);
	}
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"�����Ƿ�ǿ�ƹ���"), ImVec2(-1, 0));
	ImGui::Combo(XorString(u8"ǿ�ƹ���"), &Setting.AxeBuyMode, XorString(u8"��\0��\0\0"));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& GodAxeAuto::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"���ű�"),xorstr_(u8"�ű�����"),false };
	return info;
}
