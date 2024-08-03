#pragma once
extern DWORD CallBase;
class VguiPrint
{
public:
	void PrintUnf_8(int TextType, const char* Text, ::byte r, ::byte g, ::byte b, float DontK, float DontK2, float DontK3, float DontK4, float DontK5, float DontK6, ::byte Zero, ::byte Zero2) {
		typedef void(__thiscall* Fo)(void*, int TextType, const char* Text, ::byte r, ::byte g, ::byte b, float DontK, float DontK2, float DontK3, float DontK4, float DontK5, float DontK6, ::byte Zero, ::byte Zero2);
		reinterpret_cast<Fo>(CallBase)(this, TextType, Text, r, g, b, DontK, DontK2, DontK3, DontK4, DontK5, DontK6, Zero, Zero2);
	}
};

class ClientPrintClass
{
public:
	VguiPrint* GetVguiPrintClass() {
		typedef int(__thiscall* fo)(void*);
		return (VguiPrint *)reinterpret_cast<fo>(((int*)(*(int*)(this)))[68])(this);
	};
};

extern ClientPrintClass* G_ClientPrint;
extern VguiPrint* G_VguiPrint;