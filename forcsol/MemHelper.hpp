#pragma once
#include <Windows.h>

bool SetMemCanReadWrite(PVOID Vitualbase) {
	MEMORY_BASIC_INFORMATION QueryInfo;
	ULONG Tmp = 0;
	if (VirtualQuery(Vitualbase, &QueryInfo, sizeof(MEMORY_BASIC_INFORMATION))) {
		VirtualProtect(QueryInfo.BaseAddress, QueryInfo.RegionSize, PAGE_READWRITE | ~PAGE_WRITECOPY, &Tmp);
	}
	return false;
}