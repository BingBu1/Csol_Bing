#pragma once
#define PlayerBlock 3
#define GoldTry 49
#define WeaponBox 27
#define Props 24
#define Npc 42
#define C4Block 34
#define SellBlock 50
#define GoldBlock 55
#define Warehouse 58
#define BuyBlock 76
#define Computer 30
#define Damge 47
#define SubTextSize 0x1000

typedef void (*EncryptionCall)(void* BlockPtr, int TheBlockSize, char* RetBuff, int TheSubTextSize);


typedef struct _BlockIndex {
	ULONG ClassCallFun;
	int Unk;
	int Index;//10
}BlockIndex, * P_BlockIndex;

typedef struct _BlockClass {
	ULONG ClassCallFun;
	int oring[3];
	int Unk;//10
	P_BlockIndex IndexClass;
}BlockClass, * P_BlockClass;

typedef struct _BlockList {
	_BlockList* NextList;
	int Unkn[2];
	P_BlockClass NowListBlockClass;
}BlockList, * P_BlockList;

typedef struct _BlockListEnd {
	ULONG Unk4[7];
	ULONG Unk3;//1c
	ULONG Unk2;//20
	ULONG Unk1;//24
	ULONG Unk;//28
	P_BlockList TheBlockList; //2c
	ULONG Ecx;//30 [eax+48]
	ULONG Ecx2;//34 [eax+44]
	ULONG NeedEsp[0x100];
}BlockListEnd;

typedef struct _Unk {
	ULONG Unk[17];
	ULONG DontKonw;//+44
	ULONG DontKonw2;//+48
	P_BlockList* P_BlockList; //+4C
}Unk, * P_Unk;

struct SetListThread
{
	int Index;
	char* SetBuff;
};
using GetVoxelBlockListHead = BlockListEnd * (__stdcall *)(int IsHaveMeClass, int MeBlockClass);
using GetUnkClass = P_Unk(*)(int ClassInx);
using SetListCall = void(__thiscall*)(ULONG Class, ULONG Class44);

typedef struct _Block {
	int DrawBlockInx;
	short x, y, z;
}Block, * PBlock;

typedef struct _PlayerVxlOring {
	int x, y, z, roll;
}PlayerVxlOring, * P_PlayerVxlOring;

typedef struct _TheSellBlock {
	int OneBlock[2];		//[0] 物品Inx [1] 物品价格
	int TwoBlock[2];
	int ThreeBlock[2];
	int FourBlock[2];
	int FiveBlock[2];
}TheSellBlock;

typedef struct _TheBuyBlock {
	int OneBlock[3];		//[0] 物品Inx [1] 物品价格 [2]出售类型
	int TwoBlock[3];
	int ThreeBlock[3];
	int FourBlock[3];
	int FiveBlock[3];
}TheBuyBlock;

typedef struct _LuaBlock {
	char LuaFun[0x20];			//Lua函数名
	char LuaParameter[0x20];	// 参数
}LuaBlock;

#pragma  pack(1)	//取消对齐
typedef struct _PropsBlock {
	short Inx;			//物品Inx
	bool IsReset;		//是否允许刷新
	float ResetTime;	//刷新时间
}PropsBlock;

typedef struct _WeaponBox {
	int Inx;			//武器Inx
	bool IsReset;		//是否允许刷新
	float ResetTime;	//刷新时间
}TheWeaponBox;

typedef struct _Computuer {
	WCHAR DefString[0xB5];	//基本画面
	WCHAR SurString[0xB5];	// 成功画面
	WCHAR FalString[0xB5];	// 失败画面
	WCHAR PassWord[0x20];	//密码
	short Not;				//字符串\00结尾
	bool CanSee;			//是否隐藏密码
}Computuer;

typedef struct _DamageBlock {
	int Start; //开始扩散半径
	int End;//最大扩散半径
	float Timer;//每秒扩散多少半径
}DamageBlock;

#pragma  pack()		//恢复默认对齐

SetListThread* SetListThreadStruct(SetListThread Struct);