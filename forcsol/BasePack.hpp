#pragma once
#include <vector>
#include <memory>
#include <Windows.h>

class BasePack {
public:
	BasePack() = default;

	BasePack(BYTE* buff, size_t Length) {
		PackBuff.resize(Length);
		memcpy(PackBuff.data(), buff, Length);
	}

public:
	std::vector<BYTE> PackBuff;
};