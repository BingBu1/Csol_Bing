#include "zs_BuyBug.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
using namespace ImguiDraw;
void zs_BuyBug::DrawMenu() {
	ImGui::BeginGroupPanel(XorString(u8"����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"�ֱ����ӹ�����"), &Setting.Zbs_BuyZone); ImGui::SameLine(); HelpMarker(XorString(u8"ѡ����ǰ��ѡ��ѡ�����Զ�������ȡ����ѡ��\nע��������ʧЧ."));
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& zs_BuyBug::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"�ֱ乺��bug"),xorstr_(u8"�ű�����") ,false };
	return info;
}