#include "main.h"
#include "HookMessage.h"
PUserMsg pUserMsgBase;
PUserMsg UserMsgByName(char* szMsgName)
{
	PUserMsg Ptr = nullptr;
	Ptr = pUserMsgBase;
	while (Ptr->next)
	{
		if (!strcmp(Ptr->name, szMsgName))
			return Ptr;
		Ptr = Ptr->next;
	}
	Ptr->pfn = 0;
	return Ptr;
}

pfnUserMsgHook HookUserMsg(char* szMsgName, pfnUserMsgHook pfn)
{
	PUserMsg Ptr = nullptr;
	pfnUserMsgHook Original = nullptr;
	Ptr = UserMsgByName(szMsgName);
	if (Ptr->pfn != 0) {
		Original = Ptr->pfn;
		Ptr->pfn = pfn;
		return Original;
	}

	return Original;
}