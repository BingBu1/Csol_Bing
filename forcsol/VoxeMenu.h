#pragma once
#include "externFun.h"
#include "externbase.h"
#include "xorstr.hpp"
#include "Mymath.h"
using InitCall = void(__thiscall*)(PVOID This);
using OpenMenu = void(__thiscall*)(PVOID This);

class BaseClass {
	virtual void Init() = 0;
	virtual void Open() = 0;
};

class Lua : public BaseClass{
public:
	virtual void Init() override {
		if (GameMoudle.client) {
			auto temp = dwFindPattern(GameMoudle.client, 0x0122A000, (BYTE*)xorstr_("#CSO_Script_OnlySingle"), xorstr_("xxxxxxxxxxxxxxxxxxxxxx"));
			temp = dwFindPattern((DWORD)GameMoudle.client, 0x0122A000, (BYTE*)(&temp), "xxxx");
			NewSize = *reinterpret_cast<PULONG>(temp - 0x7C);
			InitFuns = reinterpret_cast<InitCall>(CalcCallBase(temp - 0x5F));
			FunsOffset = *reinterpret_cast<PULONG>(temp - 0x44);
			P_This = new char[NewSize];
			InitFuns(P_This);
		}
	}
	virtual void Open() override {
		if (!P_This)Init();
		OpenMenu Tmp = *reinterpret_cast <OpenMenu*>(*reinterpret_cast<PULONG>(P_This) + FunsOffset);
		Tmp(P_This);
	}
private:
	ULONG NewSize;
	InitCall InitFuns;
	ULONG FunsOffset;
	PVOID P_This;
};

inline Lua LuaMenu;