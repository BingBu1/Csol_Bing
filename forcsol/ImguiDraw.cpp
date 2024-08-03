#include "main.h"
#include "ImguiDraw.h"
#include "GroupPanel.h"
#include "AimBot.h"
#include <vector>
#include <string>
#include "CheatManagerBase.h"
#include "CommandExec.h"
#include "Events.h"
using namespace std;



namespace ImguiDraw {
	ImFont* Font = nullptr, * BigFont = nullptr;
	bool IsMove = false;
	char TextBuff[255];
	ImGuiTextBuffer WeaponBuff;
	int FlyKey, FlyMode;
	int Tab;
	CheateValue Setting;
	VxlBool_t VxlSetting;
	AimBot AimBot_;
	static vector<string> ListName = { 
		reinterpret_cast<const char*>(u8"指令区"),
		reinterpret_cast<const char*>(u8"基础功能"),
		reinterpret_cast<const char*>(u8"视觉功能"),
		reinterpret_cast<const char*>(u8"缔造者功能"),
		reinterpret_cast<const char*>(u8"自瞄相关"),
		reinterpret_cast<const char*>(u8"脚本功能-测试"),
		reinterpret_cast<const char*>(u8"卡模式"),
		reinterpret_cast<const char*>(u8"微加速") ,
		reinterpret_cast<const char*>(u8"开发者") };
	static string Currnt = ListName[0];
	static char PassWorld[10];
	bool IsDeveloper = false;

	void MeStyle(ImGuiStyle* dst = nullptr) noexcept {
		ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
		//style->WindowMinSize = ImVec2(900, 400);
		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->WindowRounding = 10.f;
		style->WindowPadding = ImVec2(8, 10);
		style->FrameRounding = 10.f;
		style->Colors[ImGuiCol_TitleBg] = ImColor(0x33, 0x43, 0x35, 0xFF * 0.5);
		style->Colors[ImGuiCol_TitleBgActive] = ImColor(0x33, 0x43, 0x35, 0xFF);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0x33, 0x43, 0x35, 0xFF * 0.5);

		style->Colors[ImGuiCol_Separator] = ImColor(100, 100, 100);
		style->Colors[ImGuiCol_SeparatorActive] = ImColor(100, 100, 100);
		style->Colors[ImGuiCol_SeparatorHovered] = ImColor(100, 100, 100);
	}

	void Render()noexcept {
		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, 128.f);
		ImGui::Spacing();
		auto DrawList = ImGui::GetWindowDrawList();
		if (ImGui::BeginListBox("##listbox 2", ImVec2(175, -FLT_MIN))) {
			auto Index = 0;
			for (auto Name : ListName) {
				const bool Is = Currnt == Name;
				if (ImGui::Selectable(Name.c_str(), Is)) {
					Currnt = Name;
					Tab = Index;
				}
				Index++;
			}
			ImGui::EndListBox();
		}
		ImGui::SetCursorPosY(ImGui::GetWindowHeight());
		auto Windows = ImGui::GetCurrentWindow();
		DrawList->AddText(ImVec2((Windows->DC.CursorPos.x + 15.f), Windows->DC.CursorPos.y - 30.f), ImColor(255, 255, 255), "BingBuHack");
		ImGui::NextColumn();
	}
	
	void Draw() {
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		CallEvent::DrawEvent();//调用注册的Event

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiBegin() {
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	void ImguiEnd() {
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	void InitBuff() {
		WeaponBuff.Buf.resize(100);
		memset((PVOID)WeaponBuff.c_str(), 0, WeaponBuff.size());
	}
	void InitImgui() {
		ImGui::CreateContext();
		ImGui_ImplOpenGL2_Init();
		ImGui_ImplWin32_Init(*reinterpret_cast<HWND*>(P_WindowHWND + 0xC));
		ImguiDraw::MeStyle();
		ImGuiIO& Io = ImGui::GetIO();
		Font = Io.Fonts->AddFontFromFileTTF(XorString("C:\\Windows\\Fonts\\msyh.ttc"), 14.0f, NULL, Io.Fonts->GetGlyphRangesChineseFull());
		Font = (!Font) ? Io.Fonts->AddFontFromFileTTF(XorString("C:\\Windows\\Fonts\\msyh.ttf"), 14.0f, NULL, Io.Fonts->GetGlyphRangesChineseFull()) : Font;
		BigFont = Io.Fonts->AddFontFromFileTTF(XorString("C:\\Windows\\Fonts\\msyhbd.ttc"), 18.0f, NULL, Io.Fonts->GetGlyphRangesChineseFull());
		BigFont = (!BigFont) ? Io.Fonts->AddFontFromFileTTF(XorString("C:\\Windows\\Fonts\\msyhbd.ttf"), 18.0f, NULL, Io.Fonts->GetGlyphRangesChineseFull()) : BigFont;
		ImGui::GetStyle().FrameRounding = 10.f;
		InitBuff();

		auto& manager = CheatManagerBase::GetInstance();
		manager.Init();
	}
}