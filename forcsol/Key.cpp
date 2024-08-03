#include "main.h"
#include "ImguiDraw.h"
#include "Key.h"
#include "Cmd.h"
#include "Timer.h"
#include <unordered_map>

#include "Events.h"
#include "DropRoom.h"
#include "GamePack.h"
#include "util.hpp"
using namespace std;
namespace Key {
	static unsigned char NeedCatchMouse = false, _Attack;
	void TimeOutRet() noexcept {
		*TimtOut[0] = 0.f;
		Sleep(1000);
		*TimtOut[0] = 30.f;
	}
	void BuyWeapon() noexcept {
		if (*MpBuyWeapon) {
			g_pEngine->pfnClientCmd((char*)ImguiDraw::WeaponBuff.c_str());
			return;
		}
		else {
			*MpBuyWeapon = 1;
			Sleep(100);
			g_pEngine->pfnClientCmd((char*)ImguiDraw::WeaponBuff.c_str());
			Sleep(100);
			*MpBuyWeapon = 0;
		}
	}
	void AxeAutoGod() noexcept{
		while (ImguiDraw::Setting.AxeGodAuto) {
			if (!ImguiDraw::Setting.AxeBuyMode) {
				NeedCatchMouse = 1;
				Cmd_ExecuteString(XorString("vxl_BuyZone"), cmd_source_t::src_command);
			}
			Cmd_ExecuteString(XorString("item_8047"), cmd_source_t::src_command);
			Sleep(100);
			Cmd_ExecuteString(XorString("item_8530"), cmd_source_t::src_command);
			Cmd_ExecuteString(XorString("+attack2"), cmd_source_t::src_command);
			Sleep(ImguiDraw::Setting.AxeGodSleep[0]);
			Cmd_ExecuteString(XorString("-attack2"), cmd_source_t::src_command);
			Cmd_ExecuteString(XorString("+attack"), cmd_source_t::src_command);
			Sleep(ImguiDraw::Setting.AxeGodSleep[1]);
			Cmd_ExecuteString(XorString("-attack"), cmd_source_t::src_command);
		}
	}
	void FastKey() noexcept {
		CallEvent::Update();
		//仅游戏内生效的
		if (Like嗨丝.value) {
			hud_player_info_t Draw{};
			for (size_t i = 0; i < g_Engine.GetMaxClients(); i++) {
				cl_entity_t* pEnt = g_Engine.GetEntityByIndex(i);
				if (pEnt && pEnt->player) {
					auto Pack = GamePack::GetInstance();
					g_Engine.pfnGetPlayerInfo(pEnt->index, &Draw); //获取实体
					Pack->Discipline(util::UTF8_To_CP(Draw.name)); //点赞
				}
			}

		}
		if (G_Game007->GameUiRoomState() == 6 && Key::IsActiva) {
			if (ImguiDraw::Setting.BuyAttack) {
				static Timer Ti;
				Ti.Init(ImguiDraw::Setting.ButAttackTimer);
				Ti.SetElapse(ImguiDraw::Setting.ButAttackTimer);
				Ti.Updata();
				if (Ti.GetIsCan() && *Key::CsolMoney >= ImguiDraw::Setting.BuyMoney) {
					Cmd_ExecuteString(XorString("dmgup"), cmd_source_t::src_command);
				}
			}
			if (ImguiDraw::Setting.AmmoOne) {
				static Timer Ti;
				Ti.Init(ImguiDraw::Setting.AmmoBuySleepOne);
				Ti.SetElapse(ImguiDraw::Setting.AmmoBuySleepOne);
				Ti.Updata();
				if (Ti.GetIsCan()) {
					Cmd_ExecuteString(XorString("primammo"), cmd_source_t::src_command);
				}
			}
			if (ImguiDraw::Setting.AmmoTwo) {
				static Timer Ti;
				Ti.Init(ImguiDraw::Setting.AmmoBuySleepTwo);
				Ti.SetElapse(ImguiDraw::Setting.AmmoBuySleepTwo);
				Ti.Updata();
				if (Ti.GetIsCan()) {
					Cmd_ExecuteString(XorString("secammo"), cmd_source_t::src_command);
				}
			}
			if (ImguiDraw::Setting.Arrow) {
				static Timer Ti;
				Ti.Init(ImguiDraw::Setting.BuyArrowTimer);
				Ti.SetElapse(ImguiDraw::Setting.BuyArrowTimer);
				Ti.Updata();
				if (Ti.GetIsCan() && *Key::CsolMoney > 1000) {
					Cmd_ExecuteString(XorString("item_28"), cmd_source_t::src_command);
				}
			}
			if (VxlFuckRoomPlayer.value && GetAsyncKeyState(0x50) && IsVip) {
				static bool Q = false;
				static float FuckTimer;
				if (GameTime - FuckTimer > 3.0f || GameTime - FuckTimer < -3.0f)
					FuckTimer = 0.0f;
				if ((GameTime - FuckTimer) > 0.3f) {
					if (Q) {
						char Cmd[255];// = "vxl_daylight 255 255 255;vxl_invlight 255 255 255;vxl_remove_dim_light 0";
						sprintf(Cmd, XorString("vxl_daylight %d %d %d;vxl_invlight %d %d %d;vxl_remove_dim_light 0;vxl_visdist 9999"), MapColor.r, MapColor.g, MapColor.b, MapColor.r, MapColor.g, MapColor.b);
						g_pEngine->pfnClientCmd(Cmd);
						Q = false;
					}
					else {
						g_pEngine->pfnClientCmd((char*)XorString("vxl_daylight 0 0 0;vxl_invlight 0 0 0;vxl_remove_dim_light 1;vxl_visdist 9999"));
						Q = true;
					}
				}
				FuckTimer = ((GameTime - FuckTimer) > 0.3f) ? GameTime + 0.3f : FuckTimer;
			}
			if (ImguiDraw::Setting.AxeDefine) {
				static Timer AxeTime, XiXiHaHa;
				if (GetAsyncKeyState('T') & AsyDown && !ImguiDraw::Setting.AxeMode || ImguiDraw::Setting.AxeAuto) {
					AxeTime.Init(0.2f);
					AxeTime.Updata();
					AxeTime.SetElapse(ImguiDraw::Setting.AxeSleep);
					if (AxeTime.GetIsCan()) {
						if (!ImguiDraw::Setting.AxeBuyMode) {
							NeedCatchMouse = 2;
							Cmd_ExecuteString(XorString("vxl_BuyZone"), cmd_source_t::src_command);
						}
						Cmd_ExecuteString(XorString("+attack"), cmd_source_t::src_command);
						Cmd_ExecuteString(XorString("item_8047"), cmd_source_t::src_command);
						Cmd_ExecuteString(XorString("item_8530"), cmd_source_t::src_command);
						_Attack = true;
					}
				}
				else if (_Attack) {
					Cmd_ExecuteString(XorString("-attack"), cmd_source_t::src_command);
					_Attack = false;
				}
				if (GetAsyncKeyState('T') && ImguiDraw::Setting.AxeMode) {
					XiXiHaHa.Init(1.f);
					XiXiHaHa.Updata();
					if (XiXiHaHa.GetIsCan()) {
						ImguiDraw::Setting.AxeAuto = (!ImguiDraw::Setting.AxeAuto) ? true : false;
					}
				}
			}
			if (ImguiDraw::Setting.AxeGod && GetAsyncKeyState('V') & AsyPush) {
				(!ImguiDraw::Setting.AxeGodAuto) ? ImguiDraw::Setting.AxeGodAuto = true : ImguiDraw::Setting.AxeGodAuto = false;
				if (ImguiDraw::Setting.AxeGodAuto)
					CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)AxeAutoGod, 0, 0, 0));
			}
			if (ImguiDraw::Setting.Zbs_BuyZone) {
				static Timer Timer;
				Timer.Init(0.3f);
				Timer.Updata();
				if (Timer.GetIsCan()) {
					Cmd_ExecuteString(XorString("cl_prebuy \"item_164\""), cmd_source_t::src_command);
					Cmd_ExecuteString(XorString("rpn"), cmd_source_t::src_command);
				}
			}
		}
	}
	void CatchMouse() {
		if (NeedCatchMouse && GetVguiMenu && GetVguiMenu->Menu) {
			GetVguiMenu->Menu->Menu->IsMenu = 0;
			(*MouseClass)->CatchMouseInGame();
			NeedCatchMouse -= 1;
		}
		if (C_DelMenu.value && GetAsyncKeyState(VK_F4) & AsyPush) {
			if (GetVguiMenu && GetVguiMenu->Menu) {
				GetVguiMenu->Menu->Menu->IsMenu = 0;
				(*MouseClass)->CatchMouseInGame();
			}
		}
	}
	void KeyCallBack(UINT Message, WPARAM wParam, LPARAM lParam) noexcept {
		KeyMap.Update(wParam, Message, wParam);
		switch (Message) {
		case WM_KEYUP:
			break;
		case WM_KEYDOWN:
			if (ImguiDraw::Setting.V && wParam == 'L') {
				g_pEngine->pfnClientCmd(ImguiDraw::TextBuff);
			}
			if (G_Game007->GameUiRoomState() == 6) {
				if (ImguiDraw::Setting.Weapon && wParam == 'K') {
					CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)BuyWeapon, 0, 0, 0));
				}
				if (BoomValue.value && wParam == VK_F3)
				{
					Cmd_ExecuteString(XorString("vxl_BuyZone"), cmd_source::src_command);
					Cmd_ExecuteString(XorString("item_31"), cmd_source::src_command);
					Cmd_ExecuteString(XorString("item_8286"), cmd_source::src_command);
					NeedCatchMouse = true;
				}
				if (C_GetAmmo.value && wParam == 'O') {
					Cmd_ExecuteString(XorString("vxl_BuyZone"), cmd_source::src_command);
					NeedCatchMouse += 1;
				}
				if (ImguiDraw::Setting.Rpn && wParam == 'U') {
					Cmd_ExecuteString("rpn", cmd_source_t::src_command);
				}
				if (ImguiDraw::Setting.Cam && wParam == VK_F7) {
					static bool V = false;
					!V ? V = true : V = false;
					if (V) {
						Cmd_ExecuteString(XorString("cam_command 1"), cmd_source_t::src_command);
						Cmd_ExecuteString(XorString("cam_idealyaw 360"), cmd_source_t::src_command);
					}
					else {
						Cmd_ExecuteString(XorString("cam_command 2"), cmd_source_t::src_command);
					}
				}
				if (ImguiDraw::Setting.Fog && wParam == VK_DELETE) {
					static bool V = false;
					!V ? V = true : V = false;
					if (V) Cmd_ExecuteString(XorString("gl_fog 0"), cmd_source_t::src_command);
					else Cmd_ExecuteString(XorString("gl_fog 1"), cmd_source_t::src_command);
				}
				if (ImguiDraw::Setting.NewReturnRoom && wParam == VK_DELETE) {
					Cmd_ExecuteString(XorString("dropclient"), cmd_source_t::src_command);
				}
				if (ImguiDraw::Setting.ReturnRoom && wParam == VK_DELETE) {
					CloseHandle(CreateThread(0, 0, (PTHREAD_START_ROUTINE)&TimeOutRet, 0, 0, 0));
				}
				if (ImguiDraw::Setting.SetPlayerSpeedN && wParam == VK_F2) {
					!ImguiDraw::Setting.NowCanPlayerSpeed ? ImguiDraw::Setting.NowCanPlayerSpeed = true : ImguiDraw::Setting.NowCanPlayerSpeed = false;
				}
				if (ImguiDraw::Setting.ResetConnectRoom && wParam == VK_F9) {
					Cmd_ExecuteString(XorString("fs_lazy_precache 2"), cmd_source_t::src_command);
					Cmd_ExecuteString(XorString("retry"), cmd_source_t::src_command);
				}
				if (VoxelBuyBugB.value && wParam == 'B') {
					Cmd_ExecuteString(XorString("vxl_BuyZone"), cmd_source_t::src_command);
				}
				if (ImguiDraw::Setting.KickPass && wParam == VK_F8) {
					DropRoom.Drop();
					DropRoom.ChangeIsDrop(true);
				}
			}
			break;
		}
	}



	void KeyMap_::Update(int Key, int Message, int wParam)noexcept {
		switch (Message) {
		case WM_KEYUP:
		case WM_SYSKEYUP:
			Key_Map[Key] = false;
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			Key_Map[Key] = true;
			break;
		case WM_KILLFOCUS:
			for (auto& [Key, Value] : Key_Map)Value = false;
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
		{
			int button = 0;
			if (Message == WM_LBUTTONDOWN || Message == WM_LBUTTONDBLCLK) { button = 0; }
			if (Message == WM_RBUTTONDOWN || Message == WM_RBUTTONDBLCLK) { button = 1; }
			if (Message == WM_MBUTTONDOWN || Message == WM_MBUTTONDBLCLK) { button = 2; }
			if (Message == WM_XBUTTONDOWN || Message == WM_XBUTTONDBLCLK) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
			Mouse_Map[button] = true;
			break;
		}
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		{
			int button = 0;
			if (Message == WM_LBUTTONUP) { button = 0; }
			if (Message == WM_RBUTTONUP) { button = 1; }
			if (Message == WM_MBUTTONUP) { button = 2; }
			if (Message == WM_XBUTTONUP) { button = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4; }
			Mouse_Map[button] = false;
			break;
		}
		}
	}

	bool KeyMap_::GetKeyStatus(int Key){
		if (!Key_Map.count(Key))return false;
		return Key_Map[Key];
	}

	bool KeyMap_::GetMouseStatus(int Buttons){
		if (!Mouse_Map.count(Buttons))return false;
		return Mouse_Map[Buttons];
	}
}
