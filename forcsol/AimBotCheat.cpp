#include "AimBotCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "AimBot.h"
using namespace ImguiDraw;
void AimBotCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"自瞄模式设置"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"HitBox自瞄"), &AimBot_.OpenAim);
	ImGui::PushItemWidth(80);
	ImGui::Combo(XorString(u8"部位"), &AimBot_.AimWhere, XorString(u8"头部\0脖子\0胸部\0腹部\0右肩\0左肩\0左手\0右手\0左腿\0右腿\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"自瞄模式"), &AimBot_.AimMode, XorString(u8"默认\0子弹追踪\0杀戮光环\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"自瞄按键"), &AimBot_.AimAsy, XorString(u8"E键\0Shift键\0左键\0右键\0左右键\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"自瞄方式"), &AimBot_.AimGetMode, XorString(u8"仅屏幕内\0 360°\0距离模式\0"));
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"自瞄辅助设置"), ImVec2(-1, 0));
	ImGui::PushItemWidth(80);
	ImGui::Checkbox(XorString(u8"自瞄压枪"), &AimBot_.AutoNoAngle); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"压枪倍率"), &AimBot_.NoAngleValue); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"追踪显示锁定"), &AimBot_.DrawAimNow);
	ImGui::Checkbox(XorString(u8"杀戮光环忽略玻璃"), &AimBot_.NotGlass); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"开枪时子弹加速"), &AimBot_.AimSpeedHack);
	ImGui::InputDouble(XorString(u8"加速倍率"), &AimBot_.AimSpeedHackValue); ImGui::SameLine();
	ImGui::Combo(XorString(u8"加速模式"), &AimBot_.AimSpeedMode, XorString(u8"帧率加速\0Timer加速\0Client加速\0人物加速慎用.\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"选敌##Aim"), &AimBot_.AimFriendMode, XorString(u8"自瞄敌人\0自瞄队友\0自瞄所有\0"));
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"反自瞄"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"陀螺反自瞄"), &AimBot_.AntiAim);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& AimBotCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"Aim"),xorstr_(u8"自瞄相关"),false };
	return info;
}
