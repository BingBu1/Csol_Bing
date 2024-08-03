#pragma once
#include "main.h"
#include "PackRead.hpp"
#include "PackWrite.hpp"
#include "DebugLog.h"

#include <tuple>

typedef int(*PfnEVP_EncryptUpdate)(VOID* ctx, unsigned char* out, int* outl, unsigned char* in, int inl);
typedef int(*PfnEVP_DecryptUpdate)(VOID* ctx, unsigned char* out, int* outl, const unsigned char* in, int inl);
typedef int(*PfnEVP_EncryptInit)  (VOID* ctx, const VOID* type, unsigned char* key, unsigned char* iv);

typedef struct PackHead {
	BYTE Head; // 都是0x55
	BYTE Seq; // 封包计次
	short Length; // 封包长度
	PackHead() {
		memset(this, 0, sizeof(PackHead));
		Head = 0x55;
	};
};


class GamePack{
public:
	static GamePack* GetInstance() {
		if (!m_Instace) {
			m_Instace = new GamePack;
		}
		return m_Instace;
	}
	GamePack();
	static int __stdcall ext_send(SOCKET s, const char* buf, int len, int flag);
	static int WINAPIV ext_EncryptInit(VOID* ctx, const VOID* type, unsigned char* key, unsigned char* iv);
	static int WINAPIV ext_EncryptUpdate(VOID* ctx, unsigned char* out, int* outl, unsigned char* in, int inl);

	void DebugPackRead(unsigned char* out, int in1);
	std::tuple<bool, BYTE>GetPackSeq();


	/*
		开始游戏
	*/
	bool StartGame();

	/*
		选择武器
	*/
	bool BuyItem(int Index);
	/*
		刷纪律
	*/
	bool Discipline(std::string name);
private:
	bool MakePack(PackWrite* Pack);
	bool SendPack(PackWrite* Pack);
private:
	inline static GamePack* m_Instace;
	SOCKET GameSocket;
	ULONG m_PackSeqAddress;
	PVOID m_Gamectx;
	PfnEVP_DecryptUpdate EVP_DecryptUpdate007;
	PfnEVP_EncryptUpdate EVP_EncryptUpdate007;
	PfnEVP_EncryptInit	EVP_EncryptInit007;
};

