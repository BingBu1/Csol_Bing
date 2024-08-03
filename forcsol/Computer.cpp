#include "main.h"
#include <fmt/format.h>
#include <Windows.h>
ComputerUiClass* UiClass = nullptr;
UINT ComputerUi = NULL;
void ComputerPass() {
	if (!UiClass)
		UiClass = (*(ComputerUiClass**)(ComputerUi));
	if (UiClass) {
		wchar_t* PassWordMem = nullptr;
		OpenClipboard(NULL);
		EmptyClipboard();

		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000);// 分配虚内存返回句柄
		if (!hHandle)
			return;
		
		auto MemLock = reinterpret_cast<wchar_t*>(GlobalLock(hHandle)); //实际分配内存
		if (!MemLock)
			return;
		
		PassWordMem = reinterpret_cast<wchar_t*>(&(UiClass->ComputerPassWord));
		if (UiClass->ComputerLength > 8) 
			PassWordMem = *reinterpret_cast<wchar_t**>(reinterpret_cast<wchar_t*>(&(UiClass->ComputerPassWord)));
		
		lstrcpyW(MemLock, PassWordMem);//复制文本到剪切板内存
		std::shared_ptr<char>& Unf8PassWord = UnicodeToUnf8(PassWordMem); //编码转换
		SetClipboardData(CF_UNICODETEXT, hHandle); //设置剪切板
		//释放
		GlobalUnlock(hHandle);
		GlobalFree(hHandle);
		CloseClipboard();
		std::string PassWorld = fmt::format(XorString(u8"密码为:{}，已帮您自动复制到剪切板"), Unf8PassWord.get());
		G_VguiPrint->PrintUnf_8(3, PassWorld.c_str(), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		return;
	}
	G_VguiPrint->PrintUnf_8(3, XorString(u8"您还未打开过电脑。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}