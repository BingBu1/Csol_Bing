#include "main.h"
#include "P_VGUI.h"
DWORD GetTheTeamAddes(DWORD Hud_Getplayerteam)
{
	DWORD temp = 0;
	__asm
	{
		mov ecx, [Hud_Getplayerteam];
		mov ecx, [ecx + 0x14];
		mov[temp], ecx;
	}
	return temp;
}
byte GetPlayerDead(int inx){
	byte temp = 0;
	__asm
	{
		mov ecx, [��Ӫ����];
		lea ecx, [ecx + 0x12];
		imul eax, inx, ��Ӫƫ��;
		mov al, byte ptr [eax + ecx];
		mov temp, al;
	}
	return temp;
}
int GetPlayerXYZ�Ƿ���Ч(int inx)
{
	return *(int*)((У�Ի��� + (inx - 1) * 0x28));
}
void GameUi(int inx)
{
	_asm
	{
		mov ecx, [g_GameUi];
		test ecx, ecx;
		je ����;
		mov eax, [ecx];
		push inx;
		call dword ptr[eax + 0x64];
	����:
	}
}
void GameUiMessageBox(const char* ����, const char* ����, byte �ֽ�)
{
	__asm
	{
		mov ecx, [g_GameUi];
		test ecx, ecx;
		je ����;
		mov eax, [ecx];
		push �ֽ�;
		push ����;
		push ����;
		call dword ptr[eax + 0xAC];
	����:
	}
}
bool IfInGameRoom()
{
	__asm {
		mov ecx, [g_GameUi];
		cmp dword ptr[ecx + 0x168], 0x6;
		je ������;
		xor eax, eax;
		ret;
	������:
		mov al, 01;
		ret
	}
}
void GameUiEscBox()
{
	__asm
	{
		mov ecx, [g_GameUi];
		test ecx, ecx;
		je ����;
		mov eax, [ecx];
		call dword ptr[eax + 0x78];
	����:
	}
}
char* GetWeaponName(int WeaponModleinx){
	model_s *Model = g_pStudioApi->GetModelByIndex(WeaponModleinx);
	if (!Model){
		return nullptr;
	}
	static char Temp[30], Buffer[40];
	int length = strlen(Model->name);//ģ���ļ��ĸ�ʽmodles/p_xxx.mdl
	length -= 9;
	memcpy(Temp, Model->name + 9, length);
	Temp[length - 4] = 0;
	char* Fuck = strchr(Temp, '_');
	if(Fuck)Fuck[0] = 0;
	sprintf(Buffer, XorString("#CSO_%s"), Temp);
	wchar_t* P_Uncode = P_::P_Localize003->GetGameTextByCsoName(Buffer); //����CSO_Ch
	WideCharToMultiByte(CP_UTF8, 0, P_Uncode, -1, Buffer, sizeof(Buffer), NULL, NULL);
	return Buffer;
}
DWORD JmpCalc(void* JmpTO, void* JmpOld) {
	return ((DWORD)JmpTO - (DWORD)JmpOld) - 5;
}

byte GetProcessState() {
	//PSYSTEM_PROCESS_INFORMATION Mem;
	//DWORD RetLenght;
	//NTSTATUS TheRet = P_NtApi._NtQuerySystemInformation(5, Mem, sizeof(Mem), &RetLenght);
	//if (TheRet == STATUS_INFO_LENGTH_MISMATCH || TheRet == STATUS_ACCESS_VIOLATION) {
	//	Mem = (PSYSTEM_PROCESS_INFORMATION)alloca(RetLenght);
	//	TheRet = P_NtApi._NtQuerySystemInformation(5, Mem, RetLenght, &RetLenght);
	//}
	//if (NT_SUCCESS(TheRet)) {
	//	do
	//	{
	//		if (Mem->UniqueProcessId == (HANDLE)NgsPid) {
	//			for (DWORD i = 0; i < Mem->NumberOfThreads; i++) {
	//				if (Mem->Threads[i].ThreadState != 5 && Mem->Threads[i].WaitReason != 5)
	//				{
	//					Mem = NULL;
	//					return 1;
	//				}
	//			}
	//		}
	//		if (Mem->NextEntryOffset == 0) {
	//			Mem = NULL;
	//			break;
	//		}
	//		Mem = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)Mem + Mem->NextEntryOffset);//ƫ�Ƶ���һ�ݽṹ
	//	} while (TRUE);
	//	return 0;
	//}
	//else {
	//	Mem = NULL;
	//	return 0;
	//}
}
void GetColor(const char* classname, float& r, float& g, float& b) {
	if (strstr(classname, XorString("once"))) {
		r = 0;
		g = 255.0f;
		b = 255.0f;
	}
	else if (strstr(classname, XorString("hurt"))) {
		r = 255.0f;
		b = 0;
		g = 0;
	}
	else if (strstr(classname, XorString("multiple"))) {
		r = 0;
		b = 0;
		g = 255.0f;
	}
	else if (strstr(classname, XorString("transition"))) {
		// Magenta
		r = 203.0f;
		g = 103.0f;
		b = 212.0f;
	}
	else if (strstr(classname, XorString("waterydeath"))) {
		r = 255.0f;
		b = 0;
		g = 0;
	}
	else if (strstr(classname, XorString("zbstrigger"))) {
		r = 0;
		g = 255.0f;
		b = 255.0f;
	}
	else if (strstr(classname, XorString("zbsbreak"))) {
		r = 64.0f;
		g = 224.0f;
		b = 208.0f;
	}
	else {
		r = 255.0f;
		b = 255.0f;
		g = 255.0f;
	}
}

bool IsInMp() {
	if (!strcmp(XorString("local"), IfLocal)) {
		return true;
	}
	return false;
}

template <typename R, typename ... List>R ReadPonitInf(List...TheList) {
	ULONG p_arg[] = { (ULONG)TheList... };
	ULONG RetNum = NULL;
	try {
		for (ULONG i : p_arg)
		{
			RetNum += i;
			RetNum = *((PULONG)RetNum);
		}
	}catch (...){
		return -1;
	}
	return (R)RetNum;
}