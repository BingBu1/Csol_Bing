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
		ImGui::TableSetupColumn(xorstr_(u8"人物名"), ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 1);
		ImGui::TableSetupColumn(xorstr_("Index"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 2);
		ImGui::TableSetupColumn(xorstr_(u8"执行"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
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
			if (ImGui::SmallButton(xorstr_(u8"卡这个"))) {
				ExecJoinClass(Index);
			}ImGui::SameLine(); HelpMarker(xorstr_(u8"请在选人物之前使用此功能."));
			ImGui::PopID();
		}
		ImGui::EndTable();
	}
}

const DrawGuiIInfo& JoinClass::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"角色"),xorstr_(u8"卡人物"),false };
	return info;
}

void JoinClass::Init()noexcept {
	Names.push_back({ xorstr_(u8"707特种部队"),12 });
	Names.push_back({ xorstr_(u8"雷霆小组"),13 });
	Names.push_back({ xorstr_(u8"炎龙特种部队"),14 });
	Names.push_back({ xorstr_(u8"警视厅卫队"),15 });
	Names.push_back({ xorstr_(u8"红帽子"),16 });
	Names.push_back({ xorstr_(u8"风暴小组"),17 });
	Names.push_back({ xorstr_(u8"蒙面行者"),18 });
	Names.push_back({ xorstr_(u8"落日军团"),19 });
	Names.push_back({ xorstr_(u8"葛雷斯"),20 });
	Names.push_back({ xorstr_(u8"娜塔莎"),21 });
	Names.push_back({ xorstr_(u8"崔志云"),22 });
	Names.push_back({ xorstr_(u8"杰西卡"),23 });
	Names.push_back({ xorstr_(u8"伊琳娜"),24 });
	Names.push_back({ xorstr_(u8"安娜"),25 });
	Names.push_back({ xorstr_(u8"杰拉德"),26 });
	Names.push_back({ xorstr_(u8"大卫·布莱克"),27 });
	Names.push_back({ xorstr_(u8"崔志云（球衣）"),28 });
	Names.push_back({ xorstr_(u8"落日军团（球衣）"),29 });
	Names.push_back({ xorstr_(u8"麦克斯（球衣）"),30 });
	Names.push_back({ xorstr_(u8"安娜（球衣）"),31 });
	Names.push_back({ xorstr_(u8"熏"),32 });
	Names.push_back({ xorstr_(u8"梦瑶"),33 });
	Names.push_back({ xorstr_(u8"丛林猛虎"),34 });
	Names.push_back({ xorstr_(u8"巡游者（红）"),35 });
	Names.push_back({ xorstr_(u8"巡游者（蓝）"),36 });
	Names.push_back({ xorstr_(u8"保卫者（红）"),37 });
	Names.push_back({ xorstr_(u8"保卫者（蓝）"),38 });
	Names.push_back({ xorstr_(u8"爱丽丝（红）"),39 });
	Names.push_back({ xorstr_(u8"爱丽丝（蓝）"),40 });
	Names.push_back({ xorstr_(u8"亨特"),41 });
	Names.push_back({ xorstr_(u8"黑桃"),42 });
	Names.push_back({ xorstr_(u8"费尔南多"),45 });
	Names.push_back({ xorstr_(u8"布莱尔"),46 });
	Names.push_back({ xorstr_(u8"恩佐"),47 });
	Names.push_back({ xorstr_(u8"露西亚"),48 });
	Names.push_back({ xorstr_(u8"娜塔莎（休闲装）"),50 });
	Names.push_back({ xorstr_(u8"杰西卡（裙装）"),51 });
	Names.push_back({ xorstr_(u8"黑鸦"),52 });
	Names.push_back({ xorstr_(u8"米迦勒"),53 });
	Names.push_back({ xorstr_(u8"安娜（校服）"),58 });
	Names.push_back({ xorstr_(u8"爱丽丝（女仆装）"),59 });
	Names.push_back({ xorstr_(u8"沃尔特"),62 });
	Names.push_back({ xorstr_(u8"卡尔托"),63 });
	Names.push_back({ xorstr_(u8"崔志云（礼服）"),64 });
	Names.push_back({ xorstr_(u8"露西亚（抹胸）"),65 });
	Names.push_back({ xorstr_(u8"玲"),66 });
	Names.push_back({ xorstr_(u8"伊莎"),67 });
	Names.push_back({ xorstr_(u8"亨利·斯托尔诺"),68 });
	Names.push_back({ xorstr_(u8"简·史密斯"),69 });
	Names.push_back({ xorstr_(u8"艾琳"),70 });
	Names.push_back({ xorstr_(u8"多米尼克"),71 });
	Names.push_back({ xorstr_(u8"索伊"),72 });
	Names.push_back({ xorstr_(u8"吉姆"),73 });
	Names.push_back({ xorstr_(u8"海莉"),74 });
	Names.push_back({ xorstr_(u8"克里克斯"),75 });
	Names.push_back({ xorstr_(u8"陈世妍（CT）"),76 });
	Names.push_back({ xorstr_(u8"陈世妍（TR）"),77 });
	Names.push_back({ xorstr_(u8"朱迪"),81 });
	Names.push_back({ xorstr_(u8"夏迪"),82 });
	Names.push_back({ xorstr_(u8"威斯克"),83 });
	Names.push_back({ xorstr_(u8"永明"),84 });
	Names.push_back({ xorstr_(u8"健明"),85 });
	Names.push_back({ xorstr_(u8"【邪皇】芙勒蒂卡"),86 });
	Names.push_back({ xorstr_(u8"【圣地】卡特琳娜"),87 });
	Names.push_back({ xorstr_(u8"【无双】崔志云"),88 });
	Names.push_back({ xorstr_(u8"【血契】安娜"),89 });
	Names.push_back({ xorstr_(u8"【狼魂】娜塔莉亚"),90 });
	Names.push_back({ xorstr_(u8"【血契】伊丽莎白"),91 });
	Names.push_back({ xorstr_(u8"【海皇】米迦勒"),92 });
	Names.push_back({ xorstr_(u8"丽莎"),93 });
	Names.push_back({ xorstr_(u8"米拉"),94 });
	Names.push_back({ xorstr_(u8"【永恒】费尔南多"),95 });
	Names.push_back({ xorstr_(u8"【深渊】布莱尔"),96 });
	Names.push_back({ xorstr_(u8"【朱雀】罗莎贝拉"),97 });
	Names.push_back({ xorstr_(u8"露西亚-特战任务"),98 });
	Names.push_back({ xorstr_(u8"米迦勒-海贼甜心"),99 });
	Names.push_back({ xorstr_(u8"【战狂】阿克赛恩"),100 });
	Names.push_back({ xorstr_(u8"【圣灵】阿塔尼斯"),101 });
	Names.push_back({ xorstr_(u8"大卫·布莱克（法外狂徒）"),102 });
	Names.push_back({ xorstr_(u8"杰拉德-联邦警长"),103 });
	Names.push_back({ xorstr_(u8"【魔龙】埃希娅"),104 });
	Names.push_back({ xorstr_(u8"【天使】乌列尔"),105 });
	Names.push_back({ xorstr_(u8"艾琳-泳装少女"),106 });
	Names.push_back({ xorstr_(u8"多米尼克-沙滩男孩"),107 });
	Names.push_back({ xorstr_(u8"【蜜桃】奈奈"),108 });
	Names.push_back({ xorstr_(u8"【夜月】娜娜"),109 });
	Names.push_back({ xorstr_(u8"亨利-厄运绅士"),110 });
	Names.push_back({ xorstr_(u8"伊琳娜-僵尸新娘"),111 });
	Names.push_back({ xorstr_(u8"【女王】梅丽莎"),112 });
	Names.push_back({ xorstr_(u8"【哨兵】卡巴斯"),113 });
	Names.push_back({ xorstr_(u8"韩国棒子1"),114 });
	Names.push_back({ xorstr_(u8"韩国棒子2"),115 });
	Names.push_back({ xorstr_(u8"【训练兵】熏"),116 });
	Names.push_back({ xorstr_(u8"【教官】杰拉德"),117 });
	Names.push_back({ xorstr_(u8"【教父】大卫布莱克"),118 });
	Names.push_back({ xorstr_(u8"【探员】葛雷斯"),119 });
	Names.push_back({ xorstr_(u8"【战神】杰西卡"),120 });
	Names.push_back({ xorstr_(u8"【理事长】索伊"),121 });
	Names.push_back({ xorstr_(u8"【龙骑士】贝伦"),122 });
	Names.push_back({ xorstr_(u8"【精灵】露西安"),123 });
	Names.push_back({ xorstr_(u8"【火喵】克莱尔"),124 });
	Names.push_back({ xorstr_(u8"【幻音】泰莉莎"),125 });
	Names.push_back({ xorstr_(u8"【血猎者】卡罗琳"),126 });
	Names.push_back({ xorstr_(u8"【审查官】伊森"),127 });
	Names.push_back({ xorstr_(u8"【佣兵】洛昂"),128 });
	Names.push_back({ xorstr_(u8"【少女】洛研"),129 });
	Names.push_back({ xorstr_(u8"【偶像】艾琳"),130 });
	Names.push_back({ xorstr_(u8"【特情】伊琳娜"),131 });
	Names.push_back({ xorstr_(u8"【影杀】凯"),132 });
	Names.push_back({ xorstr_(u8"【影卫】霖"),133 });
	Names.push_back({ xorstr_(u8"【心灵】玛丽亚"),134 });
	Names.push_back({ xorstr_(u8"【不灭】埃里克"),135 });
	Names.push_back({ xorstr_(u8"【暗夜】诺克斯"),136 });
	Names.push_back({ xorstr_(u8"【冰雪】斯卡蒂"),137 });
}

void JoinClass::ExecJoinClass(int Index) noexcept{
	auto Command = fmt::format(xorstr_("joinclass {:d}"), Index);
	Cmd_ExecuteString(Command.c_str());
}
