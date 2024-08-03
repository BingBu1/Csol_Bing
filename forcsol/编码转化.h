#pragma once
#include <memory>
std::shared_ptr<char> &UnicodeToUnf8(std::wstring YourUnicode);
std::wstring AnsiToUnicode(std::string YourAnsi);
