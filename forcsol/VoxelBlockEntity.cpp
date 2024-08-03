#include "main.h"
PBlock *BlockEntity = nullptr;
P_PlayerVxlOring PlayerVox = nullptr;
EncryptionCall CmdCall = nullptr;
GetVoxelBlockListHead GetList = nullptr;
GetUnkClass GetUnk = nullptr;
SetListCall SetList = nullptr;

SetListThread* SetListThreadStruct(SetListThread Struct) {
	static SetListThread A;
	static char Tmp[100];
	memcpy(Tmp, Struct.SetBuff, strlen(Struct.SetBuff) + 1);
	A.Index = Struct.Index;
	A.SetBuff = Tmp;
	return &A;
}

void SetBlock(char* BlockChar, int BlockInx) {
	switch ((int)HowBlock.value)
	{
	case 0:
		if (*BlockEntity) {
			char Buff[0x255];
			sprintf(Buff, XorString("vxl_cmd %d %d %d %d %s"), BlockInx, (*BlockEntity)->x, (*BlockEntity)->y, (*BlockEntity)->z, BlockChar);
			g_pEngine->pfnServerCmd(Buff);
			G_VguiPrint->PrintUnf_8(3, XorString(u8"当前修改模式必须在使用方块一瞬间使用。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		}
		break;
	case 1:
		if (PlayerVox) {
			char Buff[0x255];
			sprintf(Buff, XorString("vxl_cmd %d %d %d %d %s"), BlockInx, PlayerVox->x, PlayerVox->y, PlayerVox->z - 1, BlockChar);
			g_pEngine->pfnServerCmd(Buff);
			G_VguiPrint->PrintUnf_8(3, XorString(u8"当前修改模式修改当前坐标的方块"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		}
		break;
	case 2:
		if (PlayerVox) {
			char Buff[0x255];
			sprintf(Buff, XorString("vxl_cmd %d %d %d %d %s"), BlockInx, PlayerVox->x, PlayerVox->y, (PlayerVox->z) - 2, BlockChar);
			g_pEngine->pfnServerCmd(Buff);
			G_VguiPrint->PrintUnf_8(3, XorString(u8"当前修改模式修改脚下的方块。"), 255, 0, 0, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0, 0);
		}
		break;
	}
}
void SetGlodTry() {
	char *glodstr = (char*)XorString("TQwFAAAAgAEAAAAB");
	SetBlock(glodstr, GoldTry);
}
void SetAk47L() {
	char* glodstr = (char*)XorString("TRAJAAAAgDIAAAABAACAPw==");
	SetBlock(glodstr, WeaponBox);
}
void VoxelNpcA() {
	char* glodstr = (char*)XorString("T2IAAAAmDgAAIMT/vwFhAAAAg+EBAGlkbGUmBC4ALhCmBIPa");
	SetBlock(glodstr, Npc);
}
void VoxelC41() {
	char* glodstr = (char*)XorString("TRILAAAAgDEAMzQAAAAAAAAA");
	SetBlock(glodstr, C4Block);
}
void RollSell() {
	TheSellBlock MyBlock = { 0 };
	MyBlock.OneBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.OneBlock[1] = 1000000000;
	MyBlock.TwoBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.TwoBlock[1] = 1000000000;
	MyBlock.ThreeBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.ThreeBlock[1] = 1000000000;
	MyBlock.FourBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.FourBlock[1] = 1000000000;
	MyBlock.FiveBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.FiveBlock[1] = 1000000000;
	char Buff[100];
	char Buff2[255];
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), SellBlock, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MyBlock, sizeof(TheSellBlock), Buff, SubTextSize - strlen(Buff2));
	SetBlock(Buff, SellBlock);
}
void RollBuy() {
	TheBuyBlock MyBlock = { 0 };
	MyBlock.OneBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.OneBlock[1] = 1;
	MyBlock.OneBlock[2] = 1;
	MyBlock.TwoBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.TwoBlock[1] = 1;
	MyBlock.TwoBlock[2] = 1;
	MyBlock.ThreeBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.ThreeBlock[1] = 1;
	MyBlock.ThreeBlock[2] = 1;
	MyBlock.FourBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.FourBlock[1] = 1;
	MyBlock.FourBlock[2] = 1;
	MyBlock.FiveBlock[0] = g_pEngine->pfnRandomLong(1, 199);
	MyBlock.FiveBlock[1] = 1;
	MyBlock.FiveBlock[2] = 1;
	char Buff[100];
	char Buff2[255];
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), BuyBlock, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MyBlock, sizeof(TheBuyBlock), Buff, SubTextSize - strlen(Buff2));
	SetBlock(Buff, BuyBlock);
}
void SetGoldBlock() {
	SetBlock((char*)XorString("TQ8IAAAAgA8nAAAPJ"), GoldBlock);
}
void SetWarehouse() {
	SetBlock((char*)XorString("TRZICAAAgAAAAAOdAQBkAAAAZAAAAA=="), Warehouse);
}
void SVB(USHORT Inx, bool IsRest, float RestTime) {
	PropsBlock MeBlock = { 0 };
	MeBlock.Inx = Inx;
	MeBlock.IsReset = IsRest;
	MeBlock.ResetTime = RestTime;
	char Buff[100];
	char Buff2[255];
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), Props, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MeBlock, sizeof(PropsBlock), Buff, SubTextSize - strlen(Buff2));
	SetBlock(Buff, Props);
	__asm {
		leave;
		ret 0xC;
	}
}
void SWB(int Inx, bool IsRest, float RestTime) {
	TheWeaponBox MeBlock = { 0 };
	MeBlock.Inx = Inx;
	MeBlock.IsReset = IsRest;
	MeBlock.ResetTime = RestTime;
	char Buff[100];
	char Buff2[255];
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), WeaponBox, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MeBlock, sizeof(TheWeaponBox), Buff, SubTextSize - strlen(Buff2));
	SetBlock(Buff, WeaponBox);
	__asm {
		leave;
		ret 0xC;
	}
}
void FuckComputer() {
	Computuer MyBlock = { 0 };
	MyBlock.CanSee = false;
	lstrcpyW(MyBlock.DefString, (XorStringW(L"此地图已被决心辅|助破丨解。")));//此地图已被决心辅|助破丨解。
	lstrcpyW(MyBlock.SurString, (XorStringW(L"大哥强的")));//大哥强的
	lstrcpyW(MyBlock.FalString, (XorStringW(L"不买辅助你试你丨妈呢")));//不买辅助你试你妈呢
	lstrcpyW(MyBlock.PassWord, (XorStringW(L"bingbu")));//bingbu
	char Buff[0x255];
	char Buff2[255];
	sprintf(Buff2, XorString("vxl_cmd %d %d %d %d %s"), Computer, PlayerVox->x, PlayerVox->y, (PlayerVox->z), "");
	CmdCall(&MyBlock, sizeof(Computuer), Buff, SubTextSize - strlen(Buff2));
	SetBlock(Buff, Computer);
}

