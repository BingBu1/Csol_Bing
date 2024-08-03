#include <Windows.h>
#include "LockMode.h"
#include "ImguiDraw.h"
void LockModeClass::ReadModeBase(){
	memcpy(Base, Mode, sizeof(this->Base));
}

void LockModeClass::ResetModeBase(){
	memcpy(Mode, Base, sizeof(this->Base));
	IsRead = false;
	ImguiDraw::Setting.LockMode = false;
}

void LockModeClass::StartLock(){
	if (!IsRead) {
		memcpy(NowBase, Mode, sizeof(this->NowBase));
		IsRead = true;
	}
	memcpy(Mode, NowBase, sizeof(this->NowBase));
}
