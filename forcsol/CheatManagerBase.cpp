#include "externbase.h"
#include <xorstr.hpp>
#include<fmt/format.h>

#include "CheatManagerBase.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"

#include "Events.h"
#include "CommandExec.h"
#include "BasicCheat.h"
#include "ViewCheat.h"
#include "VoxelUpdateCheat.h"
#include "AimBotCheat.h"
#include "GodAxeAuto.h"
#include "zs_BuyBug.h"
#include "LockModeCheat.h"
#include "DevDebug.h"
#include "JoinClass.h"
#include "EnumGameItem.h"
#include <Windows.h>

CheatManagerBase::CheatManagerBase(){
	CallEvent::DrawEvent += Make_Function(&CheatManagerBase::Render, this);
}

void CheatManagerBase::Init(){
#define GetInit(className) &##className##::GetInstance()
	AddDrawNodes({
			GetInit(CommandExec),
			GetInit(CommandBuyWeapon),
			GetInit(BasicCheat),
			GetInit(ViewCheat),
			GetInit(VoxelUpdateCheat),
			GetInit(AimBotCheat),
			GetInit(zs_BuyBug),
			GetInit(GodAxeAuto),
			GetInit(LockModeCheat),
			GetInit(JoinClass),
			GetInit(EnumGameItem),
			GetInit(DevDebug)
		});

	AddDrawSecl({
		xorstr_(u8"指令区") ,
		xorstr_(u8"基础功能"),
		xorstr_(u8"视觉功能"),
		xorstr_(u8"缔造者功能"),
		xorstr_(u8"自瞄相关"),
		xorstr_(u8"脚本功能"),
		xorstr_(u8"卡模式"),
		xorstr_(u8"卡人物"),
		xorstr_(u8"随机武器。"),
		xorstr_(u8"开发者")
		});
}

void CheatManagerBase::PushNode(DrawNode* Node) {
	auto& Info = Node->GetGuiInfo();
	if (!m_DrawBaseMap.count(Info.FormMainSecl)) {
		m_DrawBaseMap[Info.FormMainSecl] = {};
	}
	auto &NodeMain = m_DrawBaseMap[Info.FormMainSecl];
	if (!NodeMain.count(Info.Name)) {
		NodeMain[Info.Name] = {};
	}
	auto& List = NodeMain[Info.Name];
	List.push_back(Node);
}

void CheatManagerBase::AddDrawNodes(std::vector<DrawNode*> Node) {
	for (auto& Ptr : Node) {
		PushNode(Ptr);
	}
}

void CheatManagerBase::AddDrawSecl(std::vector<std::string> Node) {
	for (auto& Name : Node) {
		SeclVector.push_back(Name);
	}
	Current = &SeclVector[0];
}

void CheatManagerBase::Render() noexcept{
	if (!IsMove) {
		ImGui::SetNextWindowPos(ImVec2(300, 300));
		ImGui::SetNextWindowSize(ImVec2(700, 400));
		IsMove = true;
	}
	ImGui::Begin(XorString(u8"冰布 - 金杰再见。"), &ImguiDraw::Setting.IsDraw, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImGui::PushFont(ImguiDraw::Font);
	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 128.f);
	ImGui::Spacing();
	auto DrawList = ImGui::GetWindowDrawList();
	if (ImGui::BeginListBox("##listbox 2", ImVec2(175, -FLT_MIN))) {
		auto Index = 0;
		for (auto& Name : SeclVector) {
			const bool Is = Current == &Name;
			if (ImGui::Selectable(Name.c_str(), Is)) {
				Current = &Name;
				CurrentIndex = Index;
			}
			Index++;
		}
		ImGui::EndListBox();
	}
	ImGui::SetCursorPosY(ImGui::GetWindowHeight());
	auto Windows = ImGui::GetCurrentWindow();
	DrawList->AddText(ImVec2((Windows->DC.CursorPos.x + 15.f), Windows->DC.CursorPos.y - 30.f), ImColor(255, 255, 255), "BingBuHack");
	ImGui::NextColumn();
	
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	ImGui::BeginChild("ChildWindows", ImVec2(0, -1), true);
	ImGui::Text((*Current).c_str());
	ImGui::Separator();
	auto& DrawMainNode = m_DrawBaseMap[*Current];
	for (auto& [Name, List] : DrawMainNode) {
		DrawChilnd(Name, List);
	}
	ImGui::Text(XorString(u8"游戏内调整菜单请按Esc,Home隐藏本菜单"));
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::PopFont();
	ImGui::End();
}

void CheatManagerBase::DrawChilnd(const std::string &Name,std::vector<DrawNode*>&NodeList) noexcept{
	for (auto& Node : NodeList) {
		const bool Grop = Node->GetGuiInfo().IsGrop;
		if(Grop)
			ImGui::BeginGroupPanel(Name.c_str(), ImVec2(-1, 0));
		ImGui::PushID(Node);
		Node->DrawMenu();
		ImGui::PopID();
		if(Grop)
			ImGui::BeginGroupPanel(Name.c_str(), ImVec2(-1, 0));
	}
}
