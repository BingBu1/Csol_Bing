#include <Windows.h>
#include "Interface.h"
#include "XorString3.h"
CreateInterFace FindCreateInterFace(char* ModleName) {
	CreateInterFace P_Init = 0;
	HMODULE ModleHandle = GetModuleHandle(ModleName);
	if (ModleHandle) {
		return (CreateInterFace)GetProcAddress(ModleHandle, _c(InterFace));
	}
	return nullptr;
}