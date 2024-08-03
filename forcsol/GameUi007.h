#pragma once
#include <Windows.h>
#include "DropRoom.h"
class GameUi007 
{
public:
	void GameuiCant(int i) {
		typedef int(__thiscall* fo)(void*, int);
		reinterpret_cast<fo>(((int*)(*(int*)(this))))(this, i);
	};
	void GameUiInterface(int Inx) {
		typedef int(__thiscall* fo)(void*, int);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[25])(this, Inx);
	}
	int GameUiRoomState() {
		typedef int(__thiscall* fo)(void*);
		auto RoomState = reinterpret_cast<fo>(((int*)(*(int*)(this)))[28])(this);
		return DropRoom.GetIsDrop() ? 6 : RoomState;
	};//获取游戏状态
	void GameUiEscBox() {
		typedef int(__thiscall* fo)(void*);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[30])(this);
	};//打开游戏EscBox
	void GameUiNetwork(bool 是否选择) {
		typedef int(__thiscall* fo)(void*, bool 是否选择);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[40])(this, 是否选择);//网络网吧什么的
	};
	void GameUiMessageBoxAnsi(const char* 标题, const char* 内容, ::byte 字节) {
		typedef int(__thiscall* fo)(void*, const char* 标题, const char* 内容, ::byte 字节);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[42])(this, 标题, 内容, 字节);
	};
	void GameUiMessageBoxUnf8(const char* 标题, const char* 内容, ::byte 字节, int* RetCood = nullptr) {
		int Temp = 0;
		typedef int(__thiscall* fo)(void*, int*Unk,const char* 标题, const char* 内容, ::byte 字节);
		if (RetCood == nullptr) {
			reinterpret_cast<fo>(((int*)(*(int*)(this)))[43])(this, &Temp, 标题, 内容, 字节);
		}else{
			reinterpret_cast<fo>(((int*)(*(int*)(this)))[43])(this, RetCood, 标题, 内容, 字节);
		}
	};
};
