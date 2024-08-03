#include "main.h"
#include "±àÂë×ª»¯.h"
std::shared_ptr<char> &UnicodeToUnf8(std::wstring YourUnicode) {
	static std::shared_ptr<char> unf8;
	int to = WideCharToMultiByte(CP_UTF8, 0, YourUnicode.c_str(), -1, 0, 0, 0, 0);
	unf8 = std::shared_ptr<char>(new char[to]);
	memset(unf8.get(), 0, to);
	if (to > 0) {
		WideCharToMultiByte(CP_UTF8, 0, YourUnicode.c_str(), -1, unf8.get(), to, 0, 0);
	}
	return unf8;
}

std::wstring AnsiToUnicode(std::string YourAnsi) {
	int to = MultiByteToWideChar(0, 0, YourAnsi.c_str(), -1, 0, 0);
	WCHAR* unicode = new WCHAR[to];
	memset(unicode, 0, to);
	if (to > 0) {
		MultiByteToWideChar(0, 0, YourAnsi.c_str(), -1, unicode, to);
	}
	std::wstring temp = unicode;
	delete[] unicode;
	return temp;
}