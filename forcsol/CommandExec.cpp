#include "CommandExec.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;
CommandExec::CommandExec(){
	CallEvent::Update += Make_Function(&CommandExec::Update, this);
}

void CommandExec::Update() noexcept{
	
}

void CommandExec::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"指令区"), ImVec2(-1, 0));
	ImGui::InputTextMultiline(XorString(u8"输入您的指令"), TextBuff, sizeof(TextBuff));
	ImGui::Checkbox(XorString(u8"L执行指令"), &Setting.V);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& CommandExec::GetGuiInfo()const{
	static const DrawGuiIInfo info{ xorstr_(u8"指令"),xorstr_(u8"指令区"), false };
	return info;
}

CommandBuyWeapon::CommandBuyWeapon() {
	CallEvent::Update += Make_Function(&CommandBuyWeapon::Update, this);
}

void CommandBuyWeapon::Update() noexcept {

}

void CommandBuyWeapon::DrawMenu() {
	ImGui::BeginGroupPanel(XorString(u8"自定义购买武器"), ImVec2(-1, 0));
	ImGui::InputTextMultiline(XorString(u8"输入您的武器代码\nitem_xxx或武器英文\n不同武器用;隔开"), (char*)WeaponBuff.c_str(), WeaponBuff.Buf.size());
	ImGui::Checkbox(XorString(u8"K键购买"), &Setting.Weapon);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& CommandBuyWeapon::GetGuiInfo()const {
	static const DrawGuiIInfo info{ xorstr_(u8"自定义购买武器"),xorstr_(u8"指令区"), false };
	return info;
}
