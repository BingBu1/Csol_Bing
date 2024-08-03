#include "ViewCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;
void ViewCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"绘制类"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"绘制方框"), &Setting.DrawEspBox); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"绘制名称"), &Setting.DrawName); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"绘制武器"), &Setting.DrawWeapon); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"绘制准星"), &Setting.DrawMouse);
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"内存绘制"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"描边透视"), &Setting.DrawPlayerLine); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"人物发光"), &Setting.PlayerBright); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"追踪线"), &Setting.PlayerLine); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"他人瞄准线"), &Setting.DrawPlayerViewAngles);
	ImGui::EndGroupPanel();
	ImGui::BeginGroupPanel(XorString(u8"队友"), ImVec2(-1, 0));
	ImGui::Combo(XorString(u8"绘制队友##Esp"), &Setting.DrawFriend, XorString(u8"画队友\0不画\0"));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& ViewCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"视觉"),xorstr_(u8"视觉功能") ,false };
	return info;
}
