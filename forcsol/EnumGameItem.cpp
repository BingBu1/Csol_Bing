#include "EnumGameItem.h"
#include "main.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"

#include <xorstr.hpp>
#include <fmt/format.h>

#include "Events.h"
#include "dwFindPattern.hpp"
#include "helper.hpp"
#include <mutex>
std::mutex m_EnumMutex;
EnumGameItem::EnumGameItem() : IsInit(false), WeaponItemList(), LastIndex(), P_CurrentIndex(), CurentIndex()
{
	CallEvent::Update += Make_Function(&EnumGameItem::Update, this);
}
void EnumGameItem::DrawMenu(){
    if (!IsInit && ImGui::Button(xorstr_(u8"获取"))) {
        StartEnumItems();
        IsInit = true;
    }
	static ImGuiTableFlags flags =
		ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
		| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
		| ImGuiTableFlags_ScrollY;
	ImGui::Checkbox(xorstr_(u8"N键开随"), &Start);
	if (ImGui::BeginTable(xorstr_("WeaponList"), 4, flags)) {
        std::lock_guard<std::mutex> locked(m_EnumMutex);
        ImGui::TableSetupColumn(xorstr_(u8"武器名"), ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, 1);
		ImGui::TableSetupColumn(xorstr_("ItemIndex"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 2);
		ImGui::TableSetupColumn(xorstr_(u8"英文代号"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
        ImGui::TableSetupColumn(xorstr_(u8"随机选这个"), ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
		ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
		ImGui::TableHeadersRow();
		for (auto& Item_ : this->WeaponItemList) {
			ImGui::PushID(Item_.ItemIndex);
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(Item_.ChineseName.c_str());

			ImGui::TableNextColumn();
            ImGui::Text(Item_.ItemName.c_str());

            ImGui::TableNextColumn();
            ImGui::Text(Item_.WeaponName.c_str());

            ImGui::TableNextColumn();

            if(ImGui::Checkbox(xorstr_(u8"随机武器这个！"),&Item_.CheckBoxNeed)) {
                if (Item_.CheckBoxNeed) {
                    CurentIndex.push_back(Item_.ItemIndex);
                } else {
					auto f_er = std::find(CurentIndex.begin(), CurentIndex.end(), Item_.ItemIndex);
                    CurentIndex.erase(f_er);
                }
            }
			ImGui::PopID();
		}
		ImGui::EndTable();
	}
}
const DrawGuiIInfo& EnumGameItem::GetGuiInfo() const{
    static const DrawGuiIInfo info{ xorstr_("List"),xorstr_(u8"随机武器。"),false };
    return info;
}

void EnumGameItem::StartEnumItems(){
    CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(&Thread), nullptr, NULL, nullptr);
}

void EnumGameItem::Thread(){
    std::lock_guard<std::mutex> locked(m_EnumMutex);
    auto ItemsEnum = EnumItem::GetInstance();
    if (!ItemsEnum)return;
    auto& WeaponList = EnumGameItem::GetInstance().GetWeaponList();
    ItemStruct s_Item = {};
    for (size_t i = 0; i < 9999; i++){
        Item* Item_ = ItemsEnum->GetItem(i);
        if (!Item_)continue;
        std::string_view ItemType = Item_->GetItemTypeName();
        if (ItemType == xorstr_("Equipment")) {
            s_Item.ItemIndex = i;
            s_Item.ItemName = fmt::format(xorstr_("item_{:d}"), i);
            s_Item.ChineseName = unf16tounf8(Item_->GetItemChineseName());
            s_Item.WeaponName = Item_->GetItemWeaponName();
            WeaponList.push_back(s_Item);
        }
    }
}

void EnumGameItem::Update(){
    if (!Start)
        return;
    static bool StartIndex = false;
    if (G_Game007->GameUiRoomState() == 6) {
        if (GetAsyncKeyState('N')) {
            StartIndex = true;
        }
		if (StartIndex && CurentIndex.size()) {
            P_CurrentIndex = reinterpret_cast<PULONG32>(*reinterpret_cast<PULONG32>(this->P_ClientWeapon) + 0x1c4);
            for (auto& index : CurentIndex) {
                if (*P_CurrentIndex == index) {
                    this->LastIndex = 0;
                    StartIndex = false;
                    *P_CurrentIndex = 1;
                    return;
                }
            }
            if (*P_CurrentIndex != 0) {
                *P_CurrentIndex = 0;
                g_pEngine->pfnServerCmd((char*)XorString("vxl_BuyZone"));
            }
        }
    }
}

EnumItem* EnumItem::GetInstance(){
    using ItemClassGetInterFace = EnumItem * (*)();
    ULONG GameUi = reinterpret_cast<ULONG>(GetModuleHandleA(xorstr_("GameUi.dll")));
	auto TempAddress = _Find::dwFindPattern(GameUi, 0x0122A000, reinterpret_cast<PBYTE>("\x8B\x08\xFF\x00\x8B\x51\x0C"), xorstr_("xxx?xxx"));
    ItemClassGetInterFace* GetInstance = *reinterpret_cast<ItemClassGetInterFace**> (TempAddress - 0xC);
    if (GetInstance) {
        return (*GetInstance) ();
    }
    return nullptr;
}
