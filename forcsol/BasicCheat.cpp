#include "BasicCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "DropRoom.h"
using namespace ImguiDraw;
namespace ImguiDraw {
	charu8* ComFlyKey[] = {
const_cast <charu8*>(u8"Shift��"),
const_cast <charu8*>(u8"Ctrl��") };

	charu8* ComFlyMode[] = {
	const_cast <charu8*>(u8"��ס����"),
	const_cast <charu8*>(u8"��������") };
}

BasicCheat::BasicCheat(){
	CallEvent::Update += Make_Function(&BasicCheat::Update, this);
}

void BasicCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"Kz����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"��������"), &Setting.Bunny); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"278����"), &Setting.AutoSpeed);
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"F7�����˳�"), &Setting.Cam); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"U���ָ���"), &Setting.Rpn); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"Delȥ����"), &Setting.Fog); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"F2����"), &Setting.SetPlayerSpeedN);
	ImGui::Checkbox(XorString(u8"�������"), &Setting.Flyer); ImGui::SameLine();
	ImGui::PushItemWidth(90);
	ImGui::Combo(XorString(u8"ʹ�ð���"), &FlyKey, ComFlyKey, IM_ARRAYSIZE(ComFlyKey)); ImGui::SameLine();
	ImGui::Combo(XorString(u8"����ģʽ"), &FlyMode, ComFlyMode, IM_ARRAYSIZE(ComFlyMode));
	ImGui::PopItemWidth();
	ImGui::Checkbox(XorString(u8"Del�ϻط�"), &Setting.ReturnRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"Del�°�ȫ�ط�"), &Setting.NewReturnRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"F9����"), &Setting.ResetConnectRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"�Ż�����֡��"), &Setting.ZombieFpsBest); ImGui::SameLine();
	if (ImGui::Checkbox(XorString(u8"���߷����η��ٱ�"), &Setting.KickPass)) {
		!Setting.KickPass ? DropRoom.ChangeIsDrop(false) : (void)NULL;
	} ImGui::SameLine(); HelpMarker(XorString(u8"��F8����\n����ʱ�䵽����Զ�������ֹ��������"));
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"���ӵ���"), ImVec2(-1, 0));
	ImGui::PushItemWidth(90);
	ImGui::Checkbox(XorString(u8"�Զ���"), &Setting.BuyAttack); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"����ʱ"), &Setting.ButAttackTimer); ImGui::SameLine();
	ImGui::InputInt(XorString(u8"�򹦽�Ǯ"), &Setting.BuyMoney, 0, 0);
	ImGui::Checkbox(XorString(u8"�����ӵ�"), &Setting.AmmoOne); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"������ʱ"), &Setting.AmmoBuySleepOne);
	ImGui::Checkbox(XorString(u8"���ӵ�"), &Setting.AmmoTwo); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"������ʱ"), &Setting.AmmoBuySleepTwo);
	ImGui::Checkbox(XorString(u8"�������"), &Setting.Arrow); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"������ʱ"), &Setting.BuyArrowTimer);
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();


}

const DrawGuiIInfo& BasicCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"����"),xorstr_(u8"��������"),false };
	return info;
}

void BasicCheat::Update(){

}
