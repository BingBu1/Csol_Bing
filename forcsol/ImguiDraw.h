#pragma once
#include "imgui/imgui.h"
#include "AimBot.h"
#include "LockMode.h"
#if _HAS_CXX20
using  charu8 = char8_t;
#else
using  charu8 = char;
#endif

#pragma pack(1)
namespace ImguiDraw {
	struct CheateValue {
		bool IsDraw = true;
		bool Bunny = 0;
		bool AutoSpeed = 0;
		bool Flyer = 0;

		bool DrawName = 0,
			DrawEspBox = 0,
			DrawPlayerLine = 0,
			DrawWeapon = 0,
			DrawMouse = 0,
			PlayerBright = 0,
			PlayerLine = 0,
			DrawPlayerViewAngles = 0;
		int DrawFriend = 0;
		bool ReturnRoom = 0;
		bool NewReturnRoom = 0;
		bool SetPlayerSpeedN = 0, NowCanPlayerSpeed = 0;
		bool AxeDefine = 0;
		bool AxeGod = 0;
		bool AxeAuto = 0;
		bool AxeGodAuto = 0;
		int AxeGodSleep[2] = { 1250 ,130 };
		int AxeGodModeIsMe = 0;
		int AxeGodIsme = 0;
		int AxeMode = 0;
		int AxeBuyMode = 0;
		float AxeSleep = 0.3f;
		bool V = 0;
		bool Weapon = 0;
		bool Cam = 0;
		bool Rpn = 0;
		bool Fog = 0;
		bool BuyAttack = 0;
		bool AmmoOne, AmmoTwo = 0, Arrow = 0;
		bool ResetConnectRoom = 0, ZombieFpsBest = 0, KickPass = 0;
		bool Zbs_BuyZone = 0, LockMode = 0, SmallSpeed = 0;
		float AmmoBuySleepOne = 0.3f, AmmoBuySleepTwo = 0.3f, ButAttackTimer = 0.3f, BuyArrowTimer = 0.3f,
			SmallSpeedVal = 0.003f;
		int BuyMoney = 8000, SmallSpeedKey = 0;
	};
	struct VxlBool_t {
		bool OpenVl = 0;
		bool SetVlSeting = 0;
		int VlSeting[7] = { 255,0,1,999,999,999,100 };
	};
}
#pragma pack()
namespace ImguiDraw {
	enum EspDraw
	{
		Box,
		Weapon,
		Name,
		Mouse
	};

	void Draw();
	void DrawMenu()noexcept;
	void InitImgui();
	void ImguiBegin();
	void ImguiEnd();


	extern char TextBuff[255];
	extern int FlyKey, FlyMode;
	extern charu8* ComFlyKey[];
	extern charu8* ComFlyMode[];
	extern ImFont* Font, * BigFont;
	extern CheateValue Setting;
	extern VxlBool_t VxlSetting;
	extern ImGuiTextBuffer WeaponBuff;
	extern AimBot AimBot_;
	extern bool IsDeveloper;
}