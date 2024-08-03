#include "main.h"
#include "SeverMeesage.h"
#include "SpeedHack.h"
#include "Mymath.h"
#include "ImguiDraw.h"
#include "DropRoom.h"
#include <Windows.h>
static PULONG OldSize;
ULONG Size;

void ByPassRtlUnwind() {
	static bool Isinit = false;
	DWORD OldProtect = NULL;
	if (Isinit)return;
	Isinit = true;
	/*
		ret 0x10 阻止这个函数展开SEH否则遍历异常栈时必定闪退
	*/
	const BYTE ShellCode[] = {
		0xC2,0x10,0x00
	};
	auto pfnRtlUnwind = GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlUnwind");
	VirtualProtect(pfnRtlUnwind, 3, PAGE_EXECUTE_READWRITE, &OldProtect);
	memcpy(pfnRtlUnwind, ShellCode, sizeof(ShellCode) / sizeof(BYTE));
	VirtualProtect(pfnRtlUnwind, 3, OldProtect, &OldProtect);
}

std::string GetMessages()noexcept {
	using Call = char*(*)();
	auto Funs = CalcCallBase(OldSeverFuns[7] + 0x15);
	Call Get = reinterpret_cast<Call>(Funs);
	OldSize = *reinterpret_cast<PULONG*>(Funs + 2);
	Size = *OldSize;
	return std::string(Get());
}

__forceinline void RusumeSizeAndCallBack() {
	using Call = void(*)();
	*OldSize = Size;
	reinterpret_cast<Call>(OldSeverFuns[7])();
}

void SeverDisConnect()noexcept {
	ByPassRtlUnwind();
	std::string MessagesNames = GetMessages();
	if (SpeedHackAutoRoom.value && MessagesNames == "Reliable channel overflowed") {
		g_pEngine->pfnClientCmd(XorString("fs_lazy_precache 2;retry"));
		return;
	}
	if (MessagesNames == "Kicked") {
		if (ImguiDraw::Setting.KickPass && DropRoom.GetIsDrop()) {
			DropRoom.ChangeIsDrop(false);
			g_pEngine->pfnClientCmd(XorString("fs_lazy_precache 2;retry"));
			return;
		}
		RusumeSizeAndCallBack();
		return;
	}
	RusumeSizeAndCallBack();
}