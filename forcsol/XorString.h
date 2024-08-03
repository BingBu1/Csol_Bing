#pragma once
#include <Windows.h>
#define In
#define Out
class XorString {
	inline void InitXorKey(int MeKey) { Key = MeKey; };
	void Xor(In char* String ,Out char *OutString) {
		for (; *String; String++, OutString++)
		{
			*OutString = ((*String) ^ Key);//“ÏªÚ
		}
	}
	int Key = 0;
};