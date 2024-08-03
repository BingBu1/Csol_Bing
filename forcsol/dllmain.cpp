// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "main.h"
#include <iostream>
#include <string>
#include <minidumpapiset.h>
#include <Shlobj_core.h>
#include <unordered_set>
#include "GameUi007.h"
#include "NT_DDK.h"
#include "Interface.h"
#include "VguiPanle.h"
#include "ISurface.h"
#include "ClassHook.h"
#include "P_VGUI.h"
#include "MemMpHack.h"
#include "Cmd.h"
#include "ImguiDraw.h"
#include "VguiLocalize003.h"
#include "HackAddres.h"
#include "Key.h"
#include "Mymath.h"
#include "tcp.hpp"

#include "LockMode.h"
#include "JoinLocal.h"
#include "SeverMeesage.h"
#include "DropRoom.h"
#include "GamePack.h"
#include "EnumGameItem.h"

#include "MemHelper.hpp"
#include "PlayerStatus.hpp"
#include "util.hpp"
#include "DebugLog.h"
using namespace std;
cl_enginefunc_t* g_pEngine = nullptr;
cl_enginefunc_t  g_Engine;
cl_clientfunc_t* p_client;
r_studio_interface_t* g_pStudio;
r_studio_interface_t g_Studio;
engine_studio_api_t* g_pStudioApi;
engine_studio_api_t g_StudioApi;
enginefuncs_t* g_pEngineFuncs_t;
globalvars_t** g_pGlobal;
GameUi007* G_Game007;
cl_clientfunc_t old_client;
Vgui2MenuGet* GetVguiMenu = nullptr;
TCHAR tochar[20] = "";
hwandclient_t GameMoudle;
DWORD adjspeed;
double* Adj_Speed;
ULONG P_WindowHWND = 0;
bool Isinit = false;
int* ClientInit = nullptr;
WNDPROC lpWndProc = nullptr;
PFLOAT CloseClientPtr = nullptr;
ClassHook::MeClassHook HookVgui;
CatchMouse** MouseClass = nullptr;
ClientPrintClass* G_ClientPrint = nullptr;
VguiPrint* G_VguiPrint = nullptr;
bool IsVip = false;
std::unordered_set<PVOID> ErrorSet;

Tcp SocketTcp(13145);

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask){
	for (; *szMask; ++szMask, ++pData, ++bMask)
	{
		if (*szMask == 'x' && *pData != *bMask)
		{
			return false;
		}
	}
	return (*szMask) == NULL;
}
DWORD dwFindPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, const char* szMask,int GetInx){
	UCHAR Inx = 0;
	try {
		for (DWORD i = NULL; i < dwSize; i++){
			if (bDataCompare((BYTE*)(dwAddress + i), pbMask, szMask)){
				if (!GetInx) {
					return (DWORD)(dwAddress + i);
				}else {
					if (Inx < GetInx) {
						Inx += 1;
					}else {
						return (DWORD)(dwAddress + i);
					}
				}
			}
		}
		return 0;
	}
	catch (...) {
		return 0;
	}
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (G_Game007->GameUiRoomState() == 6) {
		if (Node.GetNowIsInChild() && Node.GetNowChildClass()->GetNowClass()->IsColorClass()) {
			Node.GetNowChildClass()->GetNowClass()->WinProc(Message, wParam);
		}
		if (wParam == VK_RETURN && Message == WM_KEYDOWN) {
			if (Node.IsDraw) {
				if (Node.GetNowIsInChild() && Node.GetNowChildClass()->GetNowClass()->IsColorClass()) {
					((ColorClass*)Node.GetNowChildClass()->GetNowClass())->InGetCharColor();
					return 0;
				}
			}
		}
	}
	if (Message == WM_KEYUP && G_Game007->GameUiRoomState() == 6) {
		switch (wParam){
		case VK_HOME:
			!Node.IsDraw ? Node.IsDraw = true : Node.IsDraw = false;
			break;
		case VK_LEFT:
			if (Node.IsDraw) {
				if (Node.GetNowIsInChild() && Node.GetNowChildClass() != nullptr) {
					if (!(Node.GetNowChildClass()->GetNowValue())) {
						if (Node.GetNowChildClass()->GetNowClass()->IsColorClass()) {
							Node.GetNowChildClass()->GetNowClass()->ColorValue(false);
							break;
						}
						Node.BackMain();
						break;
					}
				}
				if (Node.GetNowIsInChild()) {
					if (!Node.GetNowChildClass()->GetIsBestChar())
						Node.SetChildValue(Node.GetNowChildClass()->Now, false);
					else
						Node.GetNowChildClass()->SetBestValue(Node.GetNowChildClass()->Now, false);
				}
				else {
					if (!Node.GetNowIsInChild() && !Node.GetIsBestChar())
						Node.SetValue(Node.Now, false);
					else if (!Node.GetNowIsInChild()) {
						Node.SetBestValue(Node.Now, false);
					}
				}
			}
			break;
		case VK_BACK:
			Node.BackMain();
			break;
		case VK_RIGHT:
			if (Node.IsDraw) {
				if (!Node.GetNowIsInChild() && Node.GetNowChildClass() != nullptr) {
					Node.GoChild();
					break;
				}
				if (Node.GetNowChildClass() != nullptr && Node.GetNowChildClass()->GetNowClass()->IsColorClass()) {
					Node.GetNowChildClass()->GetNowClass()->ColorValue(true);
				}
				if (Node.GetNowIsInChild()) {
					if (!Node.GetNowChildClass()->GetIsBestChar())
						Node.SetChildValue(Node.GetNowChildClass()->Now, true);
					else
						Node.GetNowChildClass()->SetBestValue(Node.GetNowChildClass()->Now, true);
				}
				else {
					if (!Node.GetNowIsInChild() && !Node.GetIsBestChar())
						Node.SetValue(Node.Now, true);
					else if (!Node.GetNowIsInChild()) {
						Node.SetBestValue(Node.Now, true);
					}
				}
			}
			break;
		case VK_UP:
			if (Node.IsDraw) {
				if (!Node.GetNowIsInChild()) {
					Node.UpOrDown(false);
				}
				else {
					Node.ChildUpOrDown(false);
				}
			}
			break;
		case VK_DOWN:
			if (Node.IsDraw) {
				if (!Node.GetNowIsInChild()) {
					Node.UpOrDown(true);
				}
				else {
					Node.ChildUpOrDown(true);
				}
			}
				
			break;
		case VK_PRIOR:
			if (Node.IsDraw) {
				if (Node.GetNowIsInChild()) {
					Node.GetNowChildClass()->UpOrNextPage(true);
				}
			}
			break;
		case VK_NEXT:
			if (Node.IsDraw) {
				if (Node.GetNowIsInChild()) {
					Node.GetNowChildClass()->UpOrNextPage(false);
				}
			}
			break;
		default:
			break;
		}
		
	}
	if (Message == WM_KEYUP && wParam == VK_HOME && G_Game007->GameUiRoomState() == 6) {
		ImguiDraw::Setting.IsDraw = Node.IsDraw;
	}else if (Message == WM_KEYUP && wParam == VK_HOME) {
		!ImguiDraw::Setting.IsDraw ? ImguiDraw::Setting.IsDraw = true : ImguiDraw::Setting.IsDraw = false;
	}
	if (ImguiDraw::Setting.IsDraw) {
		ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam);
		ImGui::GetIO().MouseDrawCursor = false;
	}
	Key::KeyCallBack(Message, wParam, lParam);
	if(Message == WM_ACTIVATE)(LOWORD(wParam) == WA_INACTIVE) ? Key::IsActiva = false : Key::IsActiva = true;
	return CallWindowProc(lpWndProc, hWnd, Message, wParam, lParam);
}
DWORD 阵营基质;
bool(*g_pfnLoadTGA)(const char *filename, unsigned char *buffer, int bufferSize, int *wide, int *tall);
unsigned char*躲猫猫开关;
DWORD 矩阵基质;
DWORD Adjspeed总开关;
DWORD *判断空气墙;
DWORD* g_GameUi;
DWORD 校对基质;
DWORD MpZ;
DWORD *FUCKBLACK;
DWORD CallBase;
void InitBase(){
	DWORD temp;
	//temp = dwFindPattern(模块结构.client, 0x0122A000, (BYTE*)"\x75\x1B\x3B\xFB\x75\x17\x3B\xC3\x0F\x85", "xxxxxxxxxx");
	//阵营基质 = *(DWORD*)(temp - 0xC6);
	//temp = dwFindPattern(模块结构.hw, 0x0122A000, (BYTE*)"\x6A\x01\xFF\x75\x18\xFF\x75\x14\xFF\x75\x10\xFF\x75\x0C\xFF\x75\x08\xE8", "xxxxxxxxxxxxxxxxxx");
	//g_pfnLoadTGA = (bool(*)(const char *, unsigned char *, int, int *, int *))((temp - 3));
	/*temp = dwFindPattern((DWORD)GetModuleHandle("mp.dll"), 0x0122A000, (BYTE*)"\x29\x4F\x1C\x83\xFB\xFF\x0F\x84", "x??xxxxx");
	HOOK生化Z技能 = ((mpzombiez_t*)(*(DWORD*)(temp + 0x39)));
	temp = dwFindPattern(模块结构.hw, 0x0122A000, (BYTE*)"\x7C\xB0\xBE\x64\x00\x00\x00", "xxxxxxx");
	Adjspeed总开关 = (*(DWORD*)(temp + 0x79));*/
	//temp = dwFindPattern(模块结构.hw, 0x0122A000, (BYTE*)"\x83\xF9\x32\x75\x18\x68", "xxxxxx");
	//g_pEngineFuncs_t = (enginefuncs_t*)(*(DWORD*)(temp - 0xC));
	//g_GameUi = ((DWORD*) * (DWORD*) * (DWORD*)(temp - 6));
	//temp = dwFindPattern(模块结构.client, 0x0122A000, (BYTE*)XorString("\x33\xC0\xEB\x7E"), (char*)XorString("xxxx"));
	//躲猫猫开关 = (byte*)(*(DWORD*)(temp - 0x9) + 0xA7);
	temp = dwFindPattern(GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xF9\x32\x75\x18\x68"), (char*)xorstr_("xxxxxx"));
	g_pEngineFuncs_t = (enginefuncs_t*)(*(DWORD*)(temp - 0xC));
	temp = dwFindPattern((DWORD)GameMoudle.Mp, 0x0122A000, (BYTE*)xorstr_("\x72\x0A\xC7\x80\x00\x00\x00\x00\x00"), (char*)xorstr_("xxxx????x"));
	g_pGlobal = (globalvars_t**)(*(DWORD*)(temp - 0x46));
	temp = dwFindPattern(GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x74\x00\x8B\x01\x6A\xFF\x68"), (char*)xorstr_("x?xxxxx"));
	G_Game007 = (GameUi007*)(*(DWORD*)*(DWORD*)(temp - 6));
	temp = dwFindPattern(GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x0F\x5A\xC0\x50\x8D\x45\x00\x50\x51"), (char*)xorstr_("xxxxxx?xx"));
	校对基质 = (*(DWORD*)(temp - 0x1EB));
	//temp = dwFindPattern((DWORD)模块结构.Mp, 0x0122A000, (BYTE*)xorstr_("\x2B\xC8\xC1\xF9\x02\x3B\xCA\x72\x00"), (char*)xorstr_("xxxxxxxx?"));
	//MpZ = (*(DWORD*)(temp - 0x4));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xFE\x08\x7C\xB0\xBE\x64"), (char*)xorstr_("xxxxxxx"));
	if (temp) {
		adjspeed = (*(DWORD*)(temp + 0xE));
		Adj_Speed = *reinterpret_cast<double**>(temp + 0x16);
		//SetMemCanReadWrite(*reinterpret_cast<void**>(temp + 0x16));
	}else {
		temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xFE\x08\x7C\xB0"), (char*)xorstr_("xxxxx")); //不同服特征不一
		adjspeed = (*(DWORD*)(temp + 0x10));
	}	
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x75\x3B\x68\x71\x0B\x00\x00\xFF\x15"), (char*)xorstr_("xxxxxxxxx"));
	FUCKBLACK = ((DWORD*)*(DWORD*)(temp + 0x38));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xF8\x01\x74\x0D\x83\xF8\x05\x74\x08"), (char*)xorstr_("xxxxxxxxxx"));
	TimeSpeed = ((double*)*(DWORD*)(temp - 0x3A));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x75\xC2\x33\xC0\x38"), (char*)xorstr_("xxxxx"));
	NubSpeed = ((UINT*)*(DWORD*)(temp - 0x8FE));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\xE9\x00\x00\x00\x00\x6A\x02\x50\xE8\x00\x00\x00\x00\x8B\x3D"), (char*)xorstr_("x????xxxx????xx"));
	PlayerSpeed = ((UINT*)*(DWORD*)(temp + 0x1B));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\xEB\x7C\xF2\x0F\x10\x0D"), (char*)xorstr_("xxxxxx"));
	HigePingBase[0] = ((double*)*(DWORD*)(temp + 0x68));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x20\x85\xC0\x75\x22"), (char*)xorstr_("xxxxxxx"));
	HigePingBase[1] = ((double*)*(DWORD*)(temp - 0x52F));
	HigePingBase[2] = ((double*)*(DWORD*)(temp - 0x519));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x89\x8D\xA8\xF7\xFF\xFF"), (char*)xorstr_("xxxxxx"));
	HigePingBase[3] = ((double*)((*(DWORD*)(temp + 0x1C)) + 0x38));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x76\x3A\xF3\x0F\x5E\xD9"), (char*)xorstr_("xxxxxx"));
	HigePingBase[4] = ((double*)*(DWORD*)(temp - 0xB0));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x0F\x5A\xC0\x66\x0F\x2F\xC8\x0F\x86\x84"), (char*)xorstr_("xxxxxxxxxx"));
	TimtOut[0] = ((float*)*(DWORD*)(temp - 0x4));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x0F\x2F\xC1\x76\x48\xF2\x0F"), (char*)xorstr_("xxxxxxx"));
	TimtOut[1] = ((float*)*(DWORD*)(temp - 0x4));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\xE9\x00\x00\x00\x00\x6A\x02\x50\xE8\x00\x00\x00\x00\x8B\x3D"), (char*)xorstr_("x????xxxx????xx"));
	GameSce = ((int*)*(DWORD*)(temp + 0x122));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\x3D\x00\x00\x00\x00\x00\x75\x15\xE8"), (char*)xorstr_("xx?????xxx"));
	CheckSpeedHack = ((float*)*(DWORD*)(temp + 0x104));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\x3D\x00\x00\x00\x00\x00\x75\x15\xE8"), (char*)xorstr_("xx?????xxx"));
	Check = ((unsigned char*)*(DWORD*)(temp + 0x110));//SV_SpeedHackCheck2
	temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\x6A\x1E\x68\x98\x00\x00\x00\x68\xFF\x00\x00\x00\x84\xC0"), (char*)xorstr_("xxxxxxxxxxxxxx"));
	G_ClientPrint = ((ClientPrintClass*)(*(DWORD*)*(DWORD*)(temp - 0x7B)));
	CallBase = ((*(DWORD*)(temp + 0x1F)) + (temp + 0x1E + 5));
	G_VguiPrint = G_ClientPrint->GetVguiPrintClass();
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x68\x03\x01\x00\x00\xFF\x75\x08\x68"), (char*)xorstr_("xxxxxxxxx"));
	IfLocal = (char*)((*(DWORD*)(temp + 0x9)));
	temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\xB8\x01\x00\x00\x00\x83\x0D"), (char*)xorstr_("xxxxxxx"));
	Client_ReadBuff = (P_ClientBuff)(*(UINT*)(temp - 0x4));
	temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\x85\xC0\x75\x34\x68\x08\x02\x00\x00\xE8"), (char*)xorstr_("xxxxxxxxxx"));
	ComputerUi = (*(PUINT)(temp - 0x4));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x10\x85\xC0\x7E\x0F"), (char*)xorstr_("xxxxxxx"));
	BlockEntity = (PBlock*)(*(PUINT)(temp + 0x10));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xF8\xFD\x75\x4C\xC6\x05"), (char*)xorstr_("xxxxxxx"));
	PlayerVox = (P_PlayerVxlOring)(*(PUINT)(temp - 0x270));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\xC7\x45\x00\x76\x78\x6C\x5F\xFF"), (char*)xorstr_("xx?xxxxx"));
	CmdCall = (EncryptionCall)((*(PUINT)(temp + 0x49)) + (temp + 0x49 + 0x4));
	//temp = dwFindPattern((DWORD)GameMoudle.Mp, 0x0122A000, (BYTE*)xorstr_("\x74\x30\x6A\x01\x6A\x00\x6A\x00\x8B\xC8"), (char*)xorstr_("xxxxxxxxxx"));
	//CreateThis = *((PULONG*)(temp + 0x7E));
	//temp = dwFindPattern((DWORD)GameMoudle.Mp, 0x0122A000, (BYTE*)xorstr_("\x74\x30\x6A\x01\x6A\x00\x6A\x00\x8B\xC8"), (char*)xorstr_("xxxxxxxxxx"));
	//ChaCheThis = *((PULONG)(temp - 0x14));
	//temp = dwFindPattern((DWORD)GameMoudle.Mp, 0x0122A000, (BYTE*)xorstr_("\x74\x30\x6A\x01\x6A\x00\x6A\x00\x8B\xC8"), (char*)xorstr_("xxxxxxxxxx"));
	//FindBossInxCall = temp - 0xE;
	//ChaCheTheEditc = temp + 0x5B;
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x04\x85\xC0\x0F\x84\x00\x00\x00\x00\x6A\x00\xE8\x00\x00\x00\x00\x8B\xF0"), (char*)xorstr_("xxxxxxx????xxx????xx")); // 85 C0 0F 84 89 00 00 00 6A 00 E8
	GetList = (GetVoxelBlockListHead)CalcCallBase(temp + 0x3A);
	GetUnk = (GetUnkClass)CalcCallBase(temp + 0xE);
	SetList = (SetListCall)CalcCallBase(temp + 0x5F);
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x2B\xCE\xD3\xE2\x8B\xCE\xD3\xE8\x0B\xD0\x83"), (char*)xorstr_("xxxxxxxxxxx"));
	VeryHigeSpeedHack = (double*)(*(ULONG*)(temp + 0x70));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)("\x0F\x8C\x00\x00\x00\x00\xEB\x13\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8b"), (char*)("xx????xxx????x????x"));
	SvGameAddFullPuck = (PULONG)(*(PULONG)(temp - 0x37));
	OldSvGameAddFullPuck = (*SvGameAddFullPuck);
	*SvGameAddFullPuck = (ULONG)&MyAddToFullPack; //直接HOOK
	temp = dwFindPattern((DWORD)GameMoudle.Vgui2, 0x0122A000, (BYTE*)xorstr_("\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC3"), (char*)xorstr_("x????x????xx????????x"));//
	GetVguiMenu = reinterpret_cast<Vgui2MenuGet*>(*reinterpret_cast<PULONG>(temp + 0xC));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x55\x8B\xEC\xB9\x00\x00\x00\x00\x5D\xE9"), (char*)xorstr_("xxxx????xx"), 1);
	P_WindowHWND = *reinterpret_cast<PULONG>(temp + 0x4);
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x76\x1F\xF3\x0F\x58\xC6\x0F"), (char*)xorstr_("xxxxxxx"));
	CloseClientPtr = ((*(PULONG)(temp + 0x73)) > (GameMoudle.hw + 0x1A00000)) ? (PFLOAT)(*(PULONG)(temp + 0x72)) : (PFLOAT)(*(PULONG)(temp + 0x73)); //特定服偏移不一样
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x03\xF9\x83\x3F\x00\x0F\x85"), (char*)xorstr_("xxxxxxx"));
	MaxEditc = (PULONG)(*(PULONG)(temp - 0x25));
	temp = dwFindPattern((DWORD)GameMoudle.Vgui2, 0x0122A000, (BYTE*)xorstr_("\x84\xC0\x74\x0E\x8B\x0D\x00\x00\x00\x00\x8B\x01"), (char*)xorstr_("xxxxxx????xx"));
	MouseClass = (CatchMouse**)(*(PULONG)(temp + 6));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("connect local"), (char*)xorstr_("xxxxxxxxxxxxxx"));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)(&temp), (char*)("xxxx"));
	ExecuteFun = (P_Execute)(CalcCallBase(temp + 5));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x75\xF3\x5D\xC3\x8B\x45"), (char*)xorstr_("xxxxxx"));
	MpBuyWeapon = (PULONG)((*((PULONG)(temp - 0x37))) + 0x4BC);
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xB8\x9C\x00\x00\x00\x00\x0F\x8E"), (char*)xorstr_("xxxxxxxxx"));
	Sdk::m_pStudioHeader = (studiohdr_t**)(*(PULONG)(temp - 0xE));
	temp = dwFindPattern((DWORD)GameMoudle.Mp, 0x0122A000, (BYTE*)xorstr_("\x8B\x46\x00\xC7\x80\x30\x01\x00\x00\x33\x33\x33\x3F"), (char*)xorstr_("xx?xxxxxxxxxx"), 2);
	ShootTimed2 = (P_ShootTimed2)(temp - 0xEC);
	HasGrenade = *(PULONG)(temp + 0x37);
	temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\x2B\x0D\x00\x00\x00\x00\x89\x35\x00\x00\x00\x00"), xorstr_("xx????xx????"));
	Key::CsolMoney = (*(PULONG*)(temp + 0x2));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x84\xC0\x74\x04\x33\xC0\xEB\x07\x0F"), xorstr_("xxxxxxxxx"));
	Mode = *(char**)(temp + 0xA6);
	//temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\x74\x1A\x83\xC1\x00\x89"), xorstr_("xxxx?x"));
	//JoinLocal.Init(**reinterpret_cast<MapStruct***>(temp + 0x16C));
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x08\xFF\x34\xBD"), xorstr_("xxxxxx"));
	SeverFuns = *reinterpret_cast<PULONG*>(temp + 0x6);
	temp = dwFindPattern((DWORD)GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x6A\x00\x6A\x00\x51\x6A\x01\xB9\x00\x00\x00\x00\xE8"), xorstr_("xxxxxxxx????x"));
	DropRoom.Init(reinterpret_cast<DropCall>(CalcCallBase(temp + 0xD)), *reinterpret_cast<void**>(temp + 0x8));
	temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("\xC7\x05\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x0F\x11\x05\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00"), xorstr_("xx????xxxxxxx????xx????xxxx"));
	EnumGameItem::GetInstance().P_ClientWeapon = *reinterpret_cast<PULONG32>(temp + 0x13);
}

void InitHack(){
	do{
		GameMoudle.client = (DWORD)GetModuleHandleA(xorstr_("client.dll"));
		GameMoudle.hw = (DWORD)GetModuleHandleA(xorstr_("hw.dll"));
		GameMoudle.Mp = (DWORD)GetModuleHandleA(xorstr_("mp.dll"));
		GameMoudle.Vgui2 = (DWORD)GetModuleHandleA(xorstr_("vgui2.dll"));
		if (GameMoudle.client && GameMoudle.hw && GameMoudle.Mp && GameMoudle.Vgui2) {
			InitBase();
			InitCommand();
			DebugViewPrintf("Init Base Ok\n");
			cl_clientfunc_t* dw_client = *reinterpret_cast<cl_clientfunc_t**>(dwFindPattern(GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x0C\x85\xC0\x74\x0A\x68\x00\x00\x00\x00\xFF\xD0"), xorstr_("xxxxxxxx????xx")) + 0x39);
			if (!g_pEngine){
				if (dw_client != nullptr) {
					ULONG Initialize = reinterpret_cast<ULONG>(dw_client->Initialize);
					cl_enginefunc_t* dwEngine = *reinterpret_cast<cl_enginefunc_t**>(Initialize + 0x34);
					if (dwEngine != nullptr){
						g_pEngine = dwEngine;
						if (g_pEngine->pfnSPR_Load != nullptr)
							HookEngine();
						else  g_pEngine = NULL;
					}
				}
			}
			DebugViewPrintf("Init Engine Ok\n");
			if (!p_client) {
				if (dw_client != nullptr){
					p_client = dw_client;
					HookClient(false);
					阵营基质 = GetTheTeamAddes((DWORD)(p_client->HUD_GetPlayerTeam));
					MainStatus = reinterpret_cast<decltype(MainStatus)>(GetTheTeamAddes(reinterpret_cast<DWORD>(p_client->HUD_GetPlayerTeam)));
				}
				DWORD dwStudio = dwFindPattern(GameMoudle.hw, 0x0122A000, (BYTE*)xorstr_("\x83\xC4\x08\x56\xFF\xD0\x8B\x35"),xorstr_("xxxxxxxx"));
				if (dwStudio && p_client){
					ULONG StdioInterFace = reinterpret_cast<ULONG>(p_client->HUD_GetStudioModelInterface);
					g_pStudioApi = *reinterpret_cast<engine_studio_api_t**>(StdioInterFace + 0x34);
					dwStudio = *reinterpret_cast<PDWORD>(dwStudio + 0x35);
					g_pStudio = *reinterpret_cast<r_studio_interface_t**>(dwStudio);
					HookStodio();
				}
			}
			DebugViewPrintf("Init clientHook Ok\n");
			auto Vgui2InterFace = FindCreateInterFace(xorstr_("vgui2.dll"));
			P_::P_Panel = reinterpret_cast<vgui::IPanel*>(Vgui2InterFace(_c(VGUI_PANEL_INTERFACE_VERSION), nullptr));
			P_::P_Surface = reinterpret_cast<vgui::ISurface*>(Vgui2InterFace(_c(VGUI_SURFACE_INTERFACE_VERSION), nullptr));
			P_::P_Localize003 = reinterpret_cast<vgui::Localize003*>(Vgui2InterFace(_c(VGUI_Localize003_INTERFACE_VERSION), nullptr));
			ImguiDraw::InitImgui();
			DebugViewPrintf("Init Imgui Ok\n");
			if (P_WindowHWND) {
				lpWndProc = (WNDPROC)SetWindowLongA(*reinterpret_cast<HWND*>(P_WindowHWND + 0xC), GWL_WNDPROC, (LONG)WinProc);
				SetWindowDisplayAffinity(*reinterpret_cast<HWND*>(P_WindowHWND + 0xC), 0);
			}
			DebugViewPrintf("Init WndProcHook Ok\n");
			if (HookVgui.SetClassHook(P_::P_Panel)) {
				HookVgui.HookInx(50, PaintTraverse);
			}
			DebugViewPrintf("Init ImguiHook Ok\n");
			if (G_Game007) {
				G_Game007->GameUiMessageBoxUnf8(xorstr_(u8"载入完毕"), xorstr_(u8"扩展功能初始化成功"), -1);
			}
			GamePack::GetInstance();
			try { *ClientInit = 1; ClientInit = 0; }
			catch (...) {}
			break;
		}
		Sleep(100);
	} while (true);
}

LONG WINAPI MySeh(_EXCEPTION_POINTERS* ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode != 0xC0000005) {
		return EXCEPTION_CONTINUE_EXECUTION; //忽略不知道什么几把错误。
	}
	std::string path;
	char pathTmp[265];
	if (ErrorSet.count(ExceptionInfo->ExceptionRecord->ExceptionAddress)) {
		return EXCEPTION_CONTINUE_SEARCH;
	}
	SHGetSpecialFolderPath(0, pathTmp, CSIDL_DESKTOPDIRECTORY, 0);
	path = pathTmp;
	path += xorstr_("\\MiNidump.dmp");
	DeleteFile(path.c_str());
	HANDLE hFile = CreateFile(path.c_str(), GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL
	);
	MINIDUMP_EXCEPTION_INFORMATION exptInfo;
	exptInfo.ThreadId = ::GetCurrentThreadId();
	exptInfo.ExceptionPointers = ExceptionInfo;
	MiniDumpWriteDump(GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile, MiniDumpNormal,
		&exptInfo, NULL, NULL);
	auto ErrorText = fmt::format(xorstr_("冰布辅助捕捉到重大错误喵~\n异常错误代码: {:X} 喵呜~\n异常地址: {:p} 喵呜~\n请联系管理员发送桌面路径{}文件喵~。\n是否忽略异常继续运行。"),
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		ExceptionInfo->ExceptionRecord->ExceptionAddress,
		path
	);
	CloseHandle(hFile);
	if (!ErrorSet.count(ExceptionInfo->ExceptionRecord->ExceptionAddress) && MessageBox(0, ErrorText.c_str(), xorstr_("提示"), MB_YESNO) == IDYES) {
		ErrorSet.insert(ExceptionInfo->ExceptionRecord->ExceptionAddress);
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void InitTcp(HMODULE hModule) {
	static int a;
	SocketTcp.Start();
	while (!SocketTcp.GetIsInit()){
		Sleep(1000);
	}
	DDEEPP(hModule, &a, SocketTcp.GetIsVip(), 1 << 31);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved ){
	if (dwReason == DLL_PROCESS_ATTACH){
		//AddVectoredExceptionHandler(1, &MySeh);
		//OpenConsoleDebug();
		m_DllModule = hModule;
		thread m_tcp(InitTcp, hModule);
		m_tcp.detach();
		DisableThreadLibraryCalls((HINSTANCE)hModule);
	}
	return TRUE;
}

void  DDEEPP(HMODULE hModule, int* IsInitClient, bool _IsVip, int FuckNum) {
	//断链↓
	if (Isinit == true) {
		if ((FuckNum >> 31) != 1) {
			__asm {
			Nee:
				sub esp, 04;
				jmp Nee;
			}
		}
	}
	Isinit = true;
	IsVip = _IsVip;
	ClientInit = IsInitClient;
	thread m_hackTherad(InitHack);
	m_hackTherad.join();
	_TEB* pTeb = NtCurrentTeb();
	PPEB pPeb = pTeb->Peb;
	PLIST_ENTRY pList = &pPeb->LoaderData->InLoadOrderModuleList;
	for (PLIST_ENTRY pEntry = pList->Flink; pEntry != pList; pEntry = pEntry->Flink){
		PLDR_MODULE pModule = (PLDR_MODULE)pEntry;
		if (pModule->BaseAddress == hModule){
			pEntry = &pModule->InLoadOrderModuleList;
			pEntry->Blink->Flink = pEntry->Flink;
			pEntry->Flink->Blink = pEntry->Blink;
			pEntry = &pModule->InMemoryOrderModuleList;
			pEntry->Blink->Flink = pEntry->Flink;
			pEntry->Flink->Blink = pEntry->Blink;
			pEntry = &pModule->InInitializationOrderModuleList;
			pEntry->Blink->Flink = pEntry->Flink;
			pEntry->Flink->Blink = pEntry->Blink;
			pEntry = &pModule->HashTableEntry;
			pEntry->Blink->Flink = pEntry->Flink;
			pEntry->Flink->Blink = pEntry->Blink;
			memset(pModule->FullDllName.Buffer, 0, pModule->FullDllName.Length);
			memset(pModule, 0, sizeof(LDR_MODULE));
			break;
		}
	}
	//↑
}
