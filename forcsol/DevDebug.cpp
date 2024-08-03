#include "DevDebug.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "GamePack.h"
#include "util.hpp"
using namespace ImguiDraw;
DevDebug::DevDebug() : InPutPassWorld() {
	PassWorld = xorstr_("H114514");
}
void DevDebug::DrawMenu(){
	ImGui::BeginGroupPanel(xorstr_(u8"开发者模式"), ImVec2(-1, 0));
	if (!IsDeveloper) {
		ImGui::InputText(xorstr_(u8"密码"), InPutPassWorld, sizeof(InPutPassWorld)); ImGui::SameLine();
		if (ImGui::Button(xorstr_(u8"确认")) && std::string_view(InPutPassWorld) == PassWorld) {
			IsDeveloper = true;
		}
	}
	else {
		ImGui::Text(xorstr_(u8"加速限制已解放"));
		if (ImGui::Button(xorstr_("Test SendPack StartGame"))) {
			auto Pack = GamePack::GetInstance();
			Pack->BuyItem(0);
		}
		if (ImGui::Button(xorstr_("Test SendPack AA"))) {
			auto Pack = GamePack::GetInstance();
			Pack->Discipline(util::UTF8_To_CP(u8"两年半爱练球"));
		}
	}
	ImGui::EndGroupPanel();
}
const DrawGuiIInfo& DevDebug::GetGuiInfo() const {
	static const DrawGuiIInfo info{ xorstr_(u8"Debug"),xorstr_(u8"开发者"),false };
	return info;
}