#pragma once
class CatchMouse {
public:
	void CatchMouseInGame() {
		using CatchMouseInGame = void (__thiscall *)(PVOID _this);
		auto Mouse = (CatchMouseInGame)((((PULONG)(*(PULONG)(this))))[140]);
		Mouse(this);
	}
};
class VguiMenu {
public:
	int DMem[16];
	char DK[2];
	char IsMenu;
};
class VguiMenu2 {
public:
	int DMem[4];
	VguiMenu* Menu;
};
class Vgui2MenuGet
{
public:
	int Mem[261];
	VguiMenu2* Menu;
};
extern CatchMouse** MouseClass;