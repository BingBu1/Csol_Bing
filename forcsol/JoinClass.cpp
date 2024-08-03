#include <vector>
#include <string>
#include "JoinClass.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "Cmd.h"
#include <fmt/format.h>
JoinClass::JoinClass(){
	Init();
}

void JoinClass::DrawMenu(){
	static ImGuiTableFlags flags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;

	if (ImGui::BeginTable(xorstr_("JoinClass"), 3, flags)) {
		ImGui::TableSetupColumn(xorstr_(u8"������"), ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 1);
		ImGui::TableSetupColumn(xorstr_("Index"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 2);
		ImGui::TableSetupColumn(xorstr_(u8"ִ��"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
		ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
		ImGui::TableHeadersRow();
		for (auto& [Name, Index] : this->Names) {
			ImGui::PushID(Index);
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(Name.c_str());
			
			ImGui::TableNextColumn();
			ImGui::Text(xorstr_("JoinIndex:%d"), Index);
			
			
			ImGui::TableNextColumn();
			if (ImGui::SmallButton(xorstr_(u8"�����"))) {
				ExecJoinClass(Index);
			}ImGui::SameLine(); HelpMarker(xorstr_(u8"����ѡ����֮ǰʹ�ô˹���."));
			ImGui::PopID();
		}
		ImGui::EndTable();
	}
}

const DrawGuiIInfo& JoinClass::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"��ɫ"),xorstr_(u8"������"),false };
	return info;
}

void JoinClass::Init()noexcept {
	Names.push_back({ xorstr_(u8"707���ֲ���"),12 });
	Names.push_back({ xorstr_(u8"����С��"),13 });
	Names.push_back({ xorstr_(u8"�������ֲ���"),14 });
	Names.push_back({ xorstr_(u8"����������"),15 });
	Names.push_back({ xorstr_(u8"��ñ��"),16 });
	Names.push_back({ xorstr_(u8"�籩С��"),17 });
	Names.push_back({ xorstr_(u8"��������"),18 });
	Names.push_back({ xorstr_(u8"���վ���"),19 });
	Names.push_back({ xorstr_(u8"����˹"),20 });
	Names.push_back({ xorstr_(u8"����ɯ"),21 });
	Names.push_back({ xorstr_(u8"��־��"),22 });
	Names.push_back({ xorstr_(u8"������"),23 });
	Names.push_back({ xorstr_(u8"������"),24 });
	Names.push_back({ xorstr_(u8"����"),25 });
	Names.push_back({ xorstr_(u8"������"),26 });
	Names.push_back({ xorstr_(u8"������������"),27 });
	Names.push_back({ xorstr_(u8"��־�ƣ����£�"),28 });
	Names.push_back({ xorstr_(u8"���վ��ţ����£�"),29 });
	Names.push_back({ xorstr_(u8"���˹�����£�"),30 });
	Names.push_back({ xorstr_(u8"���ȣ����£�"),31 });
	Names.push_back({ xorstr_(u8"Ѭ"),32 });
	Names.push_back({ xorstr_(u8"����"),33 });
	Names.push_back({ xorstr_(u8"�����ͻ�"),34 });
	Names.push_back({ xorstr_(u8"Ѳ���ߣ��죩"),35 });
	Names.push_back({ xorstr_(u8"Ѳ���ߣ�����"),36 });
	Names.push_back({ xorstr_(u8"�����ߣ��죩"),37 });
	Names.push_back({ xorstr_(u8"�����ߣ�����"),38 });
	Names.push_back({ xorstr_(u8"����˿���죩"),39 });
	Names.push_back({ xorstr_(u8"����˿������"),40 });
	Names.push_back({ xorstr_(u8"����"),41 });
	Names.push_back({ xorstr_(u8"����"),42 });
	Names.push_back({ xorstr_(u8"�Ѷ��϶�"),45 });
	Names.push_back({ xorstr_(u8"������"),46 });
	Names.push_back({ xorstr_(u8"����"),47 });
	Names.push_back({ xorstr_(u8"¶����"),48 });
	Names.push_back({ xorstr_(u8"����ɯ������װ��"),50 });
	Names.push_back({ xorstr_(u8"��������ȹװ��"),51 });
	Names.push_back({ xorstr_(u8"��ѻ"),52 });
	Names.push_back({ xorstr_(u8"������"),53 });
	Names.push_back({ xorstr_(u8"���ȣ�У����"),58 });
	Names.push_back({ xorstr_(u8"����˿��Ů��װ��"),59 });
	Names.push_back({ xorstr_(u8"�ֶ���"),62 });
	Names.push_back({ xorstr_(u8"������"),63 });
	Names.push_back({ xorstr_(u8"��־�ƣ������"),64 });
	Names.push_back({ xorstr_(u8"¶���ǣ�Ĩ�أ�"),65 });
	Names.push_back({ xorstr_(u8"��"),66 });
	Names.push_back({ xorstr_(u8"��ɯ"),67 });
	Names.push_back({ xorstr_(u8"������˹�ж�ŵ"),68 });
	Names.push_back({ xorstr_(u8"��ʷ��˹"),69 });
	Names.push_back({ xorstr_(u8"����"),70 });
	Names.push_back({ xorstr_(u8"�������"),71 });
	Names.push_back({ xorstr_(u8"����"),72 });
	Names.push_back({ xorstr_(u8"��ķ"),73 });
	Names.push_back({ xorstr_(u8"����"),74 });
	Names.push_back({ xorstr_(u8"�����˹"),75 });
	Names.push_back({ xorstr_(u8"��������CT��"),76 });
	Names.push_back({ xorstr_(u8"��������TR��"),77 });
	Names.push_back({ xorstr_(u8"���"),81 });
	Names.push_back({ xorstr_(u8"�ĵ�"),82 });
	Names.push_back({ xorstr_(u8"��˹��"),83 });
	Names.push_back({ xorstr_(u8"����"),84 });
	Names.push_back({ xorstr_(u8"����"),85 });
	Names.push_back({ xorstr_(u8"��а�ʡ�ܽ�յٿ�"),86 });
	Names.push_back({ xorstr_(u8"��ʥ�ء���������"),87 });
	Names.push_back({ xorstr_(u8"����˫����־��"),88 });
	Names.push_back({ xorstr_(u8"��Ѫ��������"),89 });
	Names.push_back({ xorstr_(u8"���ǻ꡿��������"),90 });
	Names.push_back({ xorstr_(u8"��Ѫ��������ɯ��"),91 });
	Names.push_back({ xorstr_(u8"�����ʡ�������"),92 });
	Names.push_back({ xorstr_(u8"��ɯ"),93 });
	Names.push_back({ xorstr_(u8"����"),94 });
	Names.push_back({ xorstr_(u8"�����㡿�Ѷ��϶�"),95 });
	Names.push_back({ xorstr_(u8"����Ԩ��������"),96 });
	Names.push_back({ xorstr_(u8"����ȸ����ɯ����"),97 });
	Names.push_back({ xorstr_(u8"¶����-��ս����"),98 });
	Names.push_back({ xorstr_(u8"������-��������"),99 });
	Names.push_back({ xorstr_(u8"��ս�񡿰�������"),100 });
	Names.push_back({ xorstr_(u8"��ʥ�顿������˹"),101 });
	Names.push_back({ xorstr_(u8"�����������ˣ������ͽ��"),102 });
	Names.push_back({ xorstr_(u8"������-�����"),103 });
	Names.push_back({ xorstr_(u8"��ħ������ϣ�"),104 });
	Names.push_back({ xorstr_(u8"����ʹ�����ж�"),105 });
	Names.push_back({ xorstr_(u8"����-Ӿװ��Ů"),106 });
	Names.push_back({ xorstr_(u8"�������-ɳ̲�к�"),107 });
	Names.push_back({ xorstr_(u8"�����ҡ�����"),108 });
	Names.push_back({ xorstr_(u8"��ҹ�¡�����"),109 });
	Names.push_back({ xorstr_(u8"����-������ʿ"),110 });
	Names.push_back({ xorstr_(u8"������-��ʬ����"),111 });
	Names.push_back({ xorstr_(u8"��Ů����÷��ɯ"),112 });
	Names.push_back({ xorstr_(u8"���ڱ�������˹"),113 });
	Names.push_back({ xorstr_(u8"��������1"),114 });
	Names.push_back({ xorstr_(u8"��������2"),115 });
	Names.push_back({ xorstr_(u8"��ѵ������Ѭ"),116 });
	Names.push_back({ xorstr_(u8"���̹١�������"),117 });
	Names.push_back({ xorstr_(u8"���̸�������������"),118 });
	Names.push_back({ xorstr_(u8"��̽Ա������˹"),119 });
	Names.push_back({ xorstr_(u8"��ս�񡿽�����"),120 });
	Names.push_back({ xorstr_(u8"�����³�������"),121 });
	Names.push_back({ xorstr_(u8"������ʿ������"),122 });
	Names.push_back({ xorstr_(u8"�����顿¶����"),123 });
	Names.push_back({ xorstr_(u8"��������������"),124 });
	Names.push_back({ xorstr_(u8"��������̩��ɯ"),125 });
	Names.push_back({ xorstr_(u8"��Ѫ���ߡ�������"),126 });
	Names.push_back({ xorstr_(u8"�����١���ɭ"),127 });
	Names.push_back({ xorstr_(u8"��Ӷ�����尺"),128 });
	Names.push_back({ xorstr_(u8"����Ů������"),129 });
	Names.push_back({ xorstr_(u8"��ż�񡿰���"),130 });
	Names.push_back({ xorstr_(u8"�����顿������"),131 });
	Names.push_back({ xorstr_(u8"��Ӱɱ����"),132 });
	Names.push_back({ xorstr_(u8"��Ӱ������"),133 });
	Names.push_back({ xorstr_(u8"�����顿������"),134 });
	Names.push_back({ xorstr_(u8"�����𡿰����"),135 });
	Names.push_back({ xorstr_(u8"����ҹ��ŵ��˹"),136 });
	Names.push_back({ xorstr_(u8"����ѩ��˹����"),137 });
}

void JoinClass::ExecJoinClass(int Index) noexcept{
	auto Command = fmt::format(xorstr_("joinclass {:d}"), Index);
	Cmd_ExecuteString(Command.c_str());
}
