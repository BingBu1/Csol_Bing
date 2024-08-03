#pragma once
#include <codecvt>
#include <string>
__forceinline std::string unf16tounf8(wchar_t * String) {
	std::wstring u16(String);
	return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(u16);
}