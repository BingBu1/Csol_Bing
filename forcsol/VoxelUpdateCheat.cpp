#include "VoxelUpdateCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;

namespace ImguiDraw {
	charu8* VxlVlTable[] = {
	const_cast <charu8*>(u8"���ȼ�"),
	const_cast <charu8*>(u8"���辭��"),
	const_cast <charu8*>(u8"׷�Ӿ���"),
	const_cast <charu8*>(u8"��������"),
	const_cast <charu8*>(u8"��������"),
	const_cast <charu8*>(u8"��������"),
	const_cast <charu8*>(u8"���鱶��") };
}

void VoxelUpdateCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"�ȼ�����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"�����ȼ�"), &VxlSetting.OpenVl);
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
	static const DrawGuiIInfo info{ xorstr_(u8"�ȼ�"),xorstr_(u8"�����߹���") ,false };
	return info;
}
