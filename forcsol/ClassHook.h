#pragma once
#include <Windows.h>
namespace ClassHook {
	class MeClassHook
	{
	public:
		bool SetClassHook(void* ClassBase);
		void HookInx(ULONG Inx, PVOID Fun);
		void UnHook();
		void ReHook();
		void DeleteMem();
	private:
		ULONG OldClassTable;
		ULONG HookClass;
		ULONG AllocMem;
	};
};