#include "AimBotCheat.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "ImguiDraw.h"
#include <xorstr.hpp>
#include "Events.h"
#include "AimBot.h"
using namespace ImguiDraw;
void AimBotCheat::DrawMenu(){
	ImGui::BeginGroupPanel(XorString(u8"����ģʽ����"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"HitBox����"), &AimBot_.OpenAim);
	ImGui::PushItemWidth(80);
	ImGui::Combo(XorString(u8"��λ"), &AimBot_.AimWhere, XorString(u8"ͷ��\0����\0�ز�\0����\0�Ҽ�\0���\0����\0����\0����\0����\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"����ģʽ"), &AimBot_.AimMode, XorString(u8"Ĭ��\0�ӵ�׷��\0ɱ¾�⻷\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"���鰴��"), &AimBot_.AimAsy, XorString(u8"E��\0Shift��\0���\0�Ҽ�\0���Ҽ�\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"���鷽ʽ"), &AimBot_.AimGetMode, XorString(u8"����Ļ��\0 360��\0����ģʽ\0"));
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"���鸨������"), ImVec2(-1, 0));
	ImGui::PushItemWidth(80);
	ImGui::Checkbox(XorString(u8"����ѹǹ"), &AimBot_.AutoNoAngle); ImGui::SameLine();
	ImGui::InputFloat(XorString(u8"ѹǹ����"), &AimBot_.NoAngleValue); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"׷����ʾ����"), &AimBot_.DrawAimNow);
	ImGui::Checkbox(XorString(u8"ɱ¾�⻷���Բ���"), &AimBot_.NotGlass); ImGui::SameLine();
	ImGui::Checkbox(XorString(u8"��ǹʱ�ӵ�����"), &AimBot_.AimSpeedHack);
	ImGui::InputDouble(XorString(u8"���ٱ���"), &AimBot_.AimSpeedHackValue); ImGui::SameLine();
	ImGui::Combo(XorString(u8"����ģʽ"), &AimBot_.AimSpeedMode, XorString(u8"֡�ʼ���\0Timer����\0Client����\0�����������.\0")); ImGui::SameLine();
	ImGui::Combo(XorString(u8"ѡ��##Aim"), &AimBot_.AimFriendMode, XorString(u8"�������\0�������\0��������\0"));
	ImGui::PopItemWidth();
	ImGui::EndGroupPanel();

	ImGui::BeginGroupPanel(XorString(u8"������"), ImVec2(-1, 0));
	ImGui::Checkbox(XorString(u8"���ݷ�����"), &AimBot_.AntiAim);
	ImGui::EndGroupPanel();
}

const DrawGuiIInfo& AimBotCheat::GetGuiInfo() const{
	static const DrawGuiIInfo info{ xorstr_(u8"Aim"),xorstr_(u8"�������"),false };
	return info;
}
