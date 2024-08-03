#pragma once
#include <Windows.h>
namespace _Find {
	__forceinline bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask) {
		for (; *szMask; ++szMask, ++pData, ++bMask)
		{
			if (*szMask == 'x' && *pData != *bMask)
			{
				return false;
			}
		}
		return (*szMask) == NULL;
	}
	__forceinline DWORD dwFindPattern(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, const char* szMask, int GetInx = 0) {
		UCHAR Inx = 0;
		try {
			for (DWORD i = NULL; i < dwSize; i++) {
				if (bDataCompare((BYTE*)(dwAddress + i), pbMask, szMask)) {
					if (!GetInx) {
						return (DWORD)(dwAddress + i);
					}
					else {
						if (Inx < GetInx) {
							Inx += 1;
						}
						else {
							return (DWORD)(dwAddress + i);
						}
					}
				}
			}
			return 0;
		}
		catch (...) {
			return 0;
		}
	}
}
