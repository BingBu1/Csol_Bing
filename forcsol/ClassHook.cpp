#include "ClassHook.h"
bool ClassHook::MeClassHook::SetClassHook(void* ClassBase) {
	ULONG Len = 0;
	PULONG VirBase = (PULONG)(*((PULONG)ClassBase));
	PULONG OldBase = (PULONG)(*((PULONG)ClassBase));
	OldClassTable = *(PULONG)ClassBase;
	HookClass = (ULONG)ClassBase;
	while (*VirBase != 0) {
		Len += 4;
		VirBase++;
	}
	PVOID NewTable = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Len);
	AllocMem = (ULONG)NewTable;
	if (NewTable) {
		memcpy(NewTable, OldBase, Len);
		*(PULONG)ClassBase = (ULONG)NewTable;
		return true;
	}
	return false;
}
void ClassHook::MeClassHook::HookInx(ULONG Inx, PVOID Fun) {
	((PULONG)AllocMem)[Inx] = (ULONG)Fun;
}
void ClassHook::MeClassHook::UnHook() {
	if (HookClass) {
		(*(PULONG)HookClass) = OldClassTable;
	}
}
void ClassHook::MeClassHook::ReHook() {
	if (HookClass) {
		(*(PULONG)HookClass) = this->AllocMem;
	}
}
void ClassHook::MeClassHook::DeleteMem() {
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, (PVOID)AllocMem);
}