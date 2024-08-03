#pragma once
#include <debugapi.h>
#include <fmt/format.h>
#define DebugEnd 0
#if DebugEnd == 1
#define DebugViewPrintf(String,...)( DebugViewPrintf_(fmt::format((String),__VA_ARGS__ )))
//#define DebugViewPrintf(String)DebugViewPrintf_(xorstr_(String))
#else
#define DebugViewPrintf(String) (void)0
#endif

inline void DebugViewPrintf_(std::string &String) {
	String = "[Bing] :" + String;
	OutputDebugString(String.c_str());
	fmt::print(String);
}

inline void OpenConsoleDebug() {
	if (AllocConsole()) {
		freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitle(TEXT("Bing - Debug"));
	}
}