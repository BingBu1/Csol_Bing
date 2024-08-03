#include "zs_BuyBug.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;
void zs_BuyBug::DrawMenu() {
	ImGui::BeginGroupPanel(XorString(u8"购买"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"灾变无视购买区"), &Setting.Zbs_BuyZone); ImGui::SameLine(); HelpMarker(XorString(u8"选人物前勾选，选人物自动复活后可取消勾选。\n注意死亡后失效."));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& zs_BuyBug::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"灾变购买bug"),xorstr_(u8"脚本功能") ,false };
	return info;
}