#include "main.h"
#include <thread>
static byte 全面需要ID[40] = { 0,40,2,3,4,5,6,7,8,9,10,11,12,13,16,17,23,24,25,26,27,28,30,31,32,33,34,35,37,39 };//全能冠军
static byte 适者需要ID[40] = { 18,20,21,22,29,38,40,36,19,45,46,47,48,49,51,52,0,2,3,4,5,6,7,8,9,10,11,12,13,16 };//适者生存
#define Call1 0x27B8D
#define Call2 0xB06E
#define Call3 0x110F4
#define Call4 0x22DB3
void SleepExx(int HowLong) {
	for (int i = 0; i < 10000; i++)
	{
		edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		if (test)
		{
			DWORD id;
			id = 适者需要ID[0];
			DWORD mp = GameMoudle.Mp;
			DWORD Thecall = mp + Call1;
			DWORD Thecall2 = mp + Call2;
			DWORD Thecall3 = mp + Call3;
			DWORD Thecall4 = mp + Call4;
			/*g_pEngineFuncs_t->pfnMessageBegin(MSG_ONE, 202, 0, test);
			g_pEngineFuncs_t->pfnWriteByte(1);
			g_pEngineFuncs_t->pfnWriteByte(id);//指定技能
			g_pEngineFuncs_t->pfnMessageEnd();*/
			char Buff[100];
			sprintf(Buff, XorString(u8"正在执行技能执行到:%d次"), i + 1);
			p_client->HUD_NoticePrint(Buff, 2);
			__asm {
				mov eax, [MpZ];
				mov eax, [eax];
				mov eax, [eax];
				mov edi, eax;
				push[edi + 0x8];
				call Thecall;
				mov esi, eax;
				push esi;
				lea ecx, [edi + 0x20];
				push 1;
				push id;
				call Thecall2;
				mov ecx, edi;
				push id;
				call Thecall3;
				pop esi;
				mov ecx, esi;
				call Thecall4;
			}
		}
		Sleep(HowLong);
	}
}
void FuckOne() {
	for (int i = 0; i < 30; i++)
	{
		edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		if (test)
		{
			DWORD id;
			id = 全面需要ID[i];
			DWORD mp = GameMoudle.Mp;
			DWORD Thecall = mp + Call1;
			DWORD Thecall2 = mp + Call2;
			DWORD Thecall3 = mp + Call3;
			DWORD Thecall4 = mp + Call4;
			g_pEngineFuncs_t->pfnMessageBegin(MSG_ONE, 202, 0, test);
			g_pEngineFuncs_t->pfnWriteByte(1);
			g_pEngineFuncs_t->pfnWriteByte(id);//指定技能
			g_pEngineFuncs_t->pfnMessageEnd();
			__asm {
				mov eax, [MpZ];
				mov eax, [eax];
				mov eax, [eax];
				mov edi, eax;
				push[edi + 0x8];
				call Thecall;
				mov esi, eax;
				push esi;
				lea ecx, [edi + 0x20];
				push 1;
				push id;
				call Thecall2;
				mov ecx, edi;
				push id;
				call Thecall3;
				pop esi;
				mov ecx, esi;
				call Thecall4;
			}
		}
	}
}
void FuckTwo() {
	for (int i = 0; i < 30; i++)
	{
		edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		if (test)
		{
			DWORD id;
			id = 适者需要ID[i];
			DWORD mp = GameMoudle.Mp;
			DWORD Thecall = mp + Call1;
			DWORD Thecall2 = mp + Call2;
			DWORD Thecall3 = mp + Call3;
			DWORD Thecall4 = mp + Call4;
			g_pEngineFuncs_t->pfnMessageBegin(MSG_ONE, 202, 0, test);
			g_pEngineFuncs_t->pfnWriteByte(1);
			g_pEngineFuncs_t->pfnWriteByte(id);//指定技能
			g_pEngineFuncs_t->pfnMessageEnd();
			__asm {
				mov eax, [MpZ];
				mov eax, [eax];
				mov eax, [eax];
				mov edi, eax;
				push[edi + 0x8];
				call Thecall;
				mov esi, eax;
				push esi;
				lea ecx, [edi + 0x20];
				push 1;
				push id;
				call Thecall2;
				mov ecx, edi;
				push id;
				call Thecall3;
				pop esi;
				mov ecx, esi;
				call Thecall4;
			}
		}
	}
}
void FuckThree() {
	int HowLong = 20;
	std::thread SleepN(SleepExx, HowLong);
	SleepN.detach();
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SleepExx, 0, 0, 0);
}
void MyJjia() {
	DWORD TheJJiaCall = (DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("?DeadEnd_PathInfo@CFuncTrackTrain@@QAEXXZ"));
	if (TheJJiaCall) {
		TheJJiaCall += 0x78;
		for (int i = 0; i < 101; i++)
		{
			edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
			PVOID ecxx = test->pvPrivateData;
			__asm {
				mov ecx, ecxx;
				mov[ecx + 0x288C], 0xA;//机甲充能
				mov[ecx + 0x2874], 3;
				call TheJJiaCall;
			}
			char Buff[100];
			sprintf(Buff, XorString(u8"正在执行装甲执行到:%d次"), i + 1);
			p_client->HUD_NoticePrint(Buff, 2);
			Sleep(200);
		}
	}
}
void FuckFour() {
	std::thread a(MyJjia);
	a.detach();
}
bool RetTure() { __asm {xor eax,eax} };
void __stdcall ZombieCall(int ZombieInx) {
	DWORD TheZombieCall = (DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("?ManagerUse@CMultiManager@@QAEXPAVCBaseEntity@@0W4USE_TYPE@@M@Z"));
	DWORD BindBotClass = (DWORD)GetProcAddress((HMODULE)GameMoudle.Mp, XorString("?RemoveThink@CEventHostage@@QAEXXZ"));
	int _ZombieInx = ZombieInx;
	if (TheZombieCall) {
		TheZombieCall += 5;
		BindBotClass += 0xA5;
		edict_t* MyED = new edict_t;
		MyED->pvPrivateData = (DWORD*)VirtualAlloc(NULL, 0x4000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		edict_s* test = g_pEngineFuncs_t->pfnPEntityOfEntIndex(1);
		PVOID ecxx = test->pvPrivateData;
		PVOID BotClass = MyED->pvPrivateData;
		*(PDWORD)BotClass = (DWORD)VirtualAlloc(NULL, 0x600, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		for (int i = 0; i < 10001; i++)
		{
			__asm {
				mov eax, MyED; //伪造实体
				mov eax, [eax + 0x80]; //伪造类
				mov[eax + 0x13D4], 0x0; //伪造是否已经被感染
				mov eax, [eax]; //eax = 伪造类虚函数表
				mov ecx, RetTure; // 伪造函数
				mov[eax + 0x1E8], ecx; // IsBot = 伪造函数
				mov eax, ecxx; //自己的类
				mov[eax + 0x13D4], 0x1; //伪造自己为僵尸
				push ecx; //保存ecx
				mov ecx, _ZombieInx; //设置ecx = 僵尸序号
				mov[eax + 0x13F5], ecx; //赋值僵尸序号
				pop ecx; //弹栈
				push BotClass; //压入伪造类
				push ecxx; //压入自己类
				call TheZombieCall; // call 荣誉call
			}
			char Buff[100];
			sprintf(Buff, (char *)u8"正在执行僵尸执行到:%d次", i + 1);
			p_client->HUD_NoticePrint(Buff, 2);
			Sleep(50);
		}
		delete MyED;
		VirtualFree(BotClass, 0x0, MEM_RELEASE);
	}
}
void FuckZombie() {
	int i = 0;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie1() {
	int i = 1;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie2() {
	int i = 2;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie3() {
	int i = 3;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie4() {
	int i = 4;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie5() {
	int i = 5;
	std::thread a(ZombieCall, i);a.detach();
}
void FuckZombie6() {
	int i = 6;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie7() {
	int i = 7;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie8() {
	int i = 8;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie9() {
	int i = 9;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie10() {
	int i = 10;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie11() {
	int i = 11;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie12() {
	int i = 12;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie13() {
	int i = 13;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie14() {
	int i = 14;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie15() {
	int i = 15;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie16() {
	int i = 16;
	std::thread a(ZombieCall, i); a.detach();
}
void FuckZombie17() {
	int i = 17;
	std::thread a(ZombieCall, i); a.detach();
}
void InitZombieCmd() {
	/*
		荣誉
	*/
	g_Engine.pfnAddCommand((char*)XorString("qngj"), FuckOne);
	g_Engine.pfnAddCommand((char*)XorString("szsc"), FuckTwo);
	g_Engine.pfnAddCommand((char*)XorString("jjjh"), FuckThree);
	g_Engine.pfnAddCommand((char*)XorString("zzjq"), FuckFour);
	/*
		僵尸
	*/
	g_Engine.pfnAddCommand((char*)XorString("ptjs"), FuckZombie);
	g_Engine.pfnAddCommand((char*)XorString("aybb"), FuckZombie1);
	g_Engine.pfnAddCommand((char*)XorString("zetf"), FuckZombie2);
	g_Engine.pfnAddCommand((char*)XorString("wgss"), FuckZombie3);
	g_Engine.pfnAddCommand((char*)XorString("mwgy"), FuckZombie4);
	g_Engine.pfnAddCommand((char*)XorString("emzz"), FuckZombie5);
	g_Engine.pfnAddCommand((char*)XorString("emls"), FuckZombie6);
	g_Engine.pfnAddCommand((char*)XorString("szz"), FuckZombie7);
	g_Engine.pfnAddCommand((char*)XorString("sxny"), FuckZombie8);
	g_Engine.pfnAddCommand((char*)XorString("swxk"), FuckZombie9);
	g_Engine.pfnAddCommand((char*)XorString("fhjw"), FuckZombie10);
	g_Engine.pfnAddCommand((char*)XorString("tknw"), FuckZombie11);
	g_Engine.pfnAddCommand((char*)XorString("bngg"), FuckZombie12);
	g_Engine.pfnAddCommand((char*)XorString("htym"), FuckZombie13);
	g_Engine.pfnAddCommand((char*)XorString("zlkl"), FuckZombie14);
	g_Engine.pfnAddCommand((char*)XorString("bdkm"), FuckZombie15);
	g_Engine.pfnAddCommand((char*)XorString("dyel"), FuckZombie16);
	g_Engine.pfnAddCommand((char*)XorString("cyeg"), FuckZombie17);
}