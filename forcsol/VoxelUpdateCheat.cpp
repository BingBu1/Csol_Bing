#include "VoxelUpdateCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;

namespace ImguiDraw {
	charu8* VxlVlTable[] = {
	const_cast <charu8*>(u8"最大等级"),
	const_cast <charu8*>(u8"所需经验"),
	const_cast <charu8*>(u8"追加经验"),
	const_cast <charu8*>(u8"提升攻击"),
	const_cast <charu8*>(u8"提升生命"),
	const_cast <charu8*>(u8"提升护甲"),
	const_cast <charu8*>(u8"经验倍率") };
}

void VoxelUpdateCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"等级作弊"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"开启等级"), &VxlSetting.OpenVl);
	ImGui::PushItemWidth(90);
	ImGui::InputInt(VxlVlTable[0], &(VxlSetting.VlSeting[0])); ImGui::SameLine();
	ImGui::InputInt(VxlVlTable[1], &(VxlSetting.VlSeting[1]));
	ImGui::InputInt(VxlVlTable[2], &(VxlSetting.VlSeting[2])); ImGui::SameLine();
	ImGui::InputInt(VxlVlTable[3], &(VxlSetting.VlSeting[3]));
	ImGui::InputInt(VxlVlTable[4], &(VxlSetting.VlSeting[4])); ImGui::SameLine();
	ImGui::InputInt(VxlVlTable[5], &(VxlSetting.VlSeting[5]));
	ImGui::InputInt(VxlVlTable[6], &(VxlSetting.VlSeting[6]));
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& VoxelUpdateCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"等级"),xorstr_(u8"缔造者功能") ,false };
	return info;
}
