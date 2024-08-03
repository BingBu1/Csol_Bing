#pragma once
namespace vgui {
	class Localize003{
	public:
		virtual void DefFun() = 0;
		virtual void Unk() = 0;
		virtual wchar_t* GetGameTextByCsoName(const char* text) = 0;
		virtual wchar_t* GetGameTextByCsoName(const char* text, int* Unk) = 0;
	};
}
#define VGUI_Localize003_INTERFACE_VERSION "VGUI_Localize003"