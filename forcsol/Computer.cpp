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

		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000);// �������ڴ淵�ؾ��
		if (!hHandle)
			return;
		
		auto MemLock = reinterpret_cast<wchar_t*>(GlobalLock(hHandle)); //ʵ�ʷ����ڴ�
		if (!MemLock)
			return;
		
		PassWordMem = reinterpret_cast<wchar_t*>(&(UiClass->ComputerPassWord));
		if (UiClass->ComputerLength > 8) 
			PassWordMem = *reinterpret_cast<wchar_t**>(reinterpret_cast<wchar_t*>(&(UiClass->ComputerPassWord)));
		
		lstrcpyW(MemLock, PassWordMem);//�����ı������а��ڴ�
		std::shared_ptr<char>& Unf8PassWord = UnicodeToUnf8(PassWordMem); //����ת��
		SetClipboardData(CF_UNICODETEXT, hHandle); //���ü��а�
		//�ͷ�
		GlobalUnlock(hHandle);
		GlobalFree(hHandle);
		CloseClipboard();
		std::string PassWorld = fmt::format(XorString(u8"����Ϊ:{}���Ѱ����Զ����Ƶ����а�"), Unf8PassWord.get());
		G_VguiPrint->PrintUnf_8(3, PassWorld.c_str(), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		return;
	}
	G_VguiPrint->PrintUnf_8(3, XorString(u8"����δ�򿪹����ԡ�"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
}