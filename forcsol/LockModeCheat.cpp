#include "LockModeCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "LockMode.h"
using namespace ImguiDraw;
LockModeCheat::LockModeCheat(){
	CallEvent::Update += Make_Function(&LockModeCheat::Update, this);
}
void LockModeCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"��ģʽ��"), ImVec2(-1, 0));
	if (ImGui::Button(XorString(u8"��ȡ��ǰģʽ")))LockModeMager.ReadModeBase();
	ImGui::SameLine();
	if (ImGui::Button(XorString(u8"��ԭ֮ǰ��ȡģʽ")))LockModeMager.ResetModeBase();
	ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"��ʼ����ǰ"), &Setting.LockMode);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& LockModeCheat::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"ModeLock"),xorstr_(u8"��ģʽ") ,false };
	return info;
}

void LockModeCheat::Update() noexcept{
	if (ImguiDraw::Setting.LockMode) {
		LockModeMager.StartLock();
	}
}
