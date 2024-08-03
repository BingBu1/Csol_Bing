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
	ImGui::BeginGroupPanel(XorString(u8"ָ����"), ImVec2(-1, 0));
	ImGui::InputTextMultiline(XorString(u8"��������ָ��"), TextBuff, sizeof(TextBuff));
	ImGui::Checkbox(XorString(u8"Lִ��ָ��"), &Setting.V);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& CommandExec::GetGuiInfo()const{
	static const DrawGuiIInfo info{ xorstr_(u8"ָ��"),xorstr_(u8"ָ����"), false };
	return info;
}

CommandBuyWeapon::CommandBuyWeapon() {
	CallEvent::Update += Make_Function(&CommandBuyWeapon::Update, this);
}

void CommandBuyWeapon::Update() noexcept {

}

void CommandBuyWeapon::DrawMenu() {
	ImGui::BeginGroupPanel(XorString(u8"�Զ��幺������"), ImVec2(-1, 0));
	ImGui::InputTextMultiline(XorString(u8"����������������\nitem_xxx������Ӣ��\n��ͬ������;����"), (char*)WeaponBuff.c_str(), WeaponBuff.Buf.size());
	ImGui::Checkbox(XorString(u8"K������"), &Setting.Weapon);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& CommandBuyWeapon::GetGuiInfo()const {
	static const DrawGuiIInfo info{ xorstr_(u8"�Զ��幺������"),xorstr_(u8"ָ����"), false };
	return info;
}
