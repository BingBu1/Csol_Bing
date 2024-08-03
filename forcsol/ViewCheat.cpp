#include "ViewCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;
void ViewCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"������"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"���Ʒ���"), &Setting.DrawEspBox); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"��������"), &Setting.DrawName); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"��������"), &Setting.DrawWeapon); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"����׼��"), &Setting.DrawMouse);
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"�ڴ����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"���͸��"), &Setting.DrawPlayerLine); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"���﷢��"), &Setting.PlayerBright); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"׷����"), &Setting.PlayerLine); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"������׼��"), &Setting.DrawPlayerViewAngles);
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"����"), ImVec2(-1, 0));
	ImGui::Combo(XorString(u8"���ƶ���##Esp"), &Setting.DrawFriend, XorString(u8"������\0����\0"));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& ViewCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"�Ӿ�"),xorstr_(u8"�Ӿ�����") ,false };
	return info;
}
