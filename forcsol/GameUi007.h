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
	};//��ȡ��Ϸ״̬
	void GameUiEscBox() {
		typedef int(__thiscall* fo)(void*);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[30])(this);
	};//����ϷEscBox
	void GameUiNetwork(bool �Ƿ�ѡ��) {
		typedef int(__thiscall* fo)(void*, bool �Ƿ�ѡ��);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[40])(this, �Ƿ�ѡ��);//��������ʲô��
	};
	void GameUiMessageBoxAnsi(const char* ����, const char* ����, ::byte �ֽ�) {
		typedef int(__thiscall* fo)(void*, const char* ����, const char* ����, ::byte �ֽ�);
		reinterpret_cast<fo>(((int*)(*(int*)(this)))[42])(this, ����, ����, �ֽ�);
	};
	void GameUiMessageBoxUnf8(const char* ����, const char* ����, ::byte �ֽ�, int* RetCood = nullptr) {
		int Temp = 0;
		typedef int(__thiscall* fo)(void*, int*Unk,const char* ����, const char* ����, ::byte �ֽ�);
		if (RetCood == nullptr) {
			reinterpret_cast<fo>(((int*)(*(int*)(this)))[43])(this, &Temp, ����, ����, �ֽ�);
		}else{
			reinterpret_cast<fo>(((int*)(*(int*)(this)))[43])(this, RetCood, ����, ����, �ֽ�);
		}
	};
};
