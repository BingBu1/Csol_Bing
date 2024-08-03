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
	int OneBlock[2];		//[0] ��ƷInx [1] ��Ʒ�۸�
	int TwoBlock[2];
	int ThreeBlock[2];
	int FourBlock[2];
	int FiveBlock[2];
}TheSellBlock;

typedef struct _TheBuyBlock {
	int OneBlock[3];		//[0] ��ƷInx [1] ��Ʒ�۸� [2]��������
	int TwoBlock[3];
	int ThreeBlock[3];
	int FourBlock[3];
	int FiveBlock[3];
}TheBuyBlock;

typedef struct _LuaBlock {
	char LuaFun[0x20];			//Lua������
	char LuaParameter[0x20];	// ����
}LuaBlock;

#pragma  pack(1)	//ȡ������
typedef struct _PropsBlock {
	short Inx;			//��ƷInx
	bool IsReset;		//�Ƿ�����ˢ��
	float ResetTime;	//ˢ��ʱ��
}PropsBlock;

typedef struct _WeaponBox {
	int Inx;			//����Inx
	bool IsReset;		//�Ƿ�����ˢ��
	float ResetTime;	//ˢ��ʱ��
}TheWeaponBox;

typedef struct _Computuer {
	WCHAR DefString[0xB5];	//��������
	WCHAR SurString[0xB5];	// �ɹ�����
	WCHAR FalString[0xB5];	// ʧ�ܻ���
	WCHAR PassWord[0x20];	//����
	short Not;				//�ַ���\00��β
	bool CanSee;			//�Ƿ���������
}Computuer;

typedef struct _DamageBlock {
	int Start; //��ʼ��ɢ�뾶
	int End;//�����ɢ�뾶
	float Timer;//ÿ����ɢ���ٰ뾶
}DamageBlock;

#pragma  pack()		//�ָ�Ĭ�϶���

SetListThread* SetListThreadStruct(SetListThread Struct);