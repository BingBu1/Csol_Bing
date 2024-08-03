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
const_cast <charu8*>(u8"Shift键"),
const_cast <charu8*>(u8"Ctrl键") };

	charu8* ComFlyMode[] = {
	const_cast <charu8*>(u8"卡住飞天"),
	const_cast <charu8*>(u8"缓慢飞天") };
}

BasicCheat::BasicCheat(){
	CallEvent::Update += Make_Function(&BasicCheat::Update, this);
}

void BasicCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"Kz功能"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"超级连跳"), &Setting.Bunny); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"278地速"), &Setting.AutoSpeed);
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"功能"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"F7第三人称"), &Setting.Cam); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"U开局复活"), &Setting.Rpn); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"Del去黑雾"), &Setting.Fog); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"F2卡空"), &Setting.SetPlayerSpeedN);
	ImGui::Checkbox(XorString(u8"配件飞天"), &Setting.Flyer); ImGui::SameLine();
	ImGui::PushItemWidth(90);
	ImGui::Combo(XorString(u8"使用按键"), &FlyKey, ComFlyKey, IM_ARRAYSIZE(ComFlyKey)); ImGui::SameLine();
	ImGui::Combo(XorString(u8"飞天模式"), &FlyMode, ComFlyMode, IM_ARRAYSIZE(ComFlyMode));
	ImGui::PopItemWidth();
	ImGui::Checkbox(XorString(u8"Del老回房"), &Setting.ReturnRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"Del新安全回房"), &Setting.NewReturnRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"F9重连"), &Setting.ResetConnectRoom); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"优化生化帧数"), &Setting.ZombieFpsBest); ImGui::SameLine();
	if (ImGui::Checkbox(XorString(u8"防踢防屏蔽防举报"), &Setting.KickPass)) {
		!Setting.KickPass ? DropRoom.ChangeIsDrop(false) : (void)NULL;
	} ImGui::SameLine(); HelpMarker(XorString(u8"按F8防踢\n防踢时间到后会自动重连防止掉出大厅"));
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"买功子弹类"), ImVec2(-1, 0));
	ImGui::PushItemWidth(90);
	ImGui::Checkbox(XorString(u8"自动买功"), &Setting.BuyAttack); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"买功延时"), &Setting.ButAttackTimer); ImGui::SameLine();
	ImGui::InputInt(XorString(u8"买功金钱"), &Setting.BuyMoney, 0, 0);
	ImGui::Checkbox(XorString(u8"买主子弹"), &Setting.AmmoOne); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"主弹延时"), &Setting.AmmoBuySleepOne);
	ImGui::Checkbox(XorString(u8"买副子弹"), &Setting.AmmoTwo); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"副弹延时"), &Setting.AmmoBuySleepTwo);
	ImGui::Checkbox(XorString(u8"买防弹衣"), &Setting.Arrow); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"防弹延时"), &Setting.BuyArrowTimer);
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();


}

const DrawGuiIInfo& BasicCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"基础"),xorstr_(u8"基础功能"),false };
	return info;
}

void BasicCheat::Update(){

}
