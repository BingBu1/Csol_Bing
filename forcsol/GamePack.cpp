#include "GamePack.h"
#include "util.hpp"
#include "Sunday.hpp"
GamePack::GamePack() :GameSocket(), m_PackSeqAddress(), EVP_DecryptUpdate007(), EVP_EncryptUpdate007(), EVP_EncryptInit007(), m_Gamectx() {
    util::HookIatTable2((PVOID)GameMoudle.hw, "wsock32.dll", "send", ext_send);
    util::HookIatTable2((PVOID)GameMoudle.hw, "libeay32.dll", "EVP_EncryptInit", ext_EncryptInit, &EVP_EncryptInit007);
    util::HookIatTable2((PVOID)GameMoudle.hw, "libeay32.dll", "EVP_EncryptUpdate", ext_EncryptUpdate, &EVP_EncryptUpdate007);
}

int __stdcall GamePack::ext_send(SOCKET s, const char* buf, int len, int flag){
    auto Pack = GetInstance();
    Pack->GameSocket = s;
    return send(s, buf, len, flag);
}

int WINAPIV GamePack::ext_EncryptInit(VOID* ctx, const VOID* type, unsigned char* key, unsigned char* iv){
    auto Pack = GetInstance();
    Pack->m_Gamectx = ctx;
    return Pack->EVP_EncryptInit007(ctx, type, key, iv);
}

int WINAPIV GamePack::ext_EncryptUpdate(VOID* ctx, unsigned char* out, int* outl, unsigned char* in, int inl){
    auto Pack = GetInstance();
#if DebugEnd
    Pack->DebugPackRead(in, inl); //°ü
#endif
    return Pack->EVP_EncryptUpdate007(ctx, out, outl, in, inl);
}

void GamePack::DebugPackRead(unsigned char* out, int in1) {
    BYTE* PackBuff = out;
    PackHead PakcHead{};
    auto Pack_Read = std::make_shared<PackRead>(out, 4);
    PakcHead.Head = Pack_Read->ReadByte();
    PakcHead.Seq = Pack_Read->ReadByte();
    PakcHead.Length = Pack_Read->ReadShort();
    if (PakcHead.Head != 0x55) {
		DebugViewPrintf("[{}] PackHead Not 0x55,Head is :{:02X}\n", __FUNCTION__, PakcHead.Head);
        return;
    }
	DebugViewPrintf("[{}] PackLength : 0x{:X}\n", __FUNCTION__, PakcHead.Length);
    auto m_PackRead = std::make_shared<PackRead>(PackBuff + 4, PakcHead.Length);
    auto Index = m_PackRead->ReadByte();
    auto VecPack = std::vector<BYTE>(in1);
    memcpy(VecPack.data(), out, in1);
	DebugViewPrintf("[{}] Index = {} Size 0x{:X} {:02X}\n", __FUNCTION__, Index, in1, fmt::join(VecPack.begin(), VecPack.end(), " "));
}

std::tuple<bool, BYTE> GamePack::GetPackSeq(){
    if (!m_PackSeqAddress) {
        SunDaySearch SunDay;
        std::vector<ULONG64>RetVal;
        SunDay.SearchMemory(xorstr_("56 8B F1 8B 0D ?? ?? ?? ?? 8B 06 FF 70 F4 50"), GameMoudle.hw, 0x0122A000, RetVal);
        ULONG32 RetVal_ = RetVal[0];
		m_PackSeqAddress = *reinterpret_cast<PULONG32>(RetVal_ + 0x5);
    }
    int Base = *reinterpret_cast<PULONG32>(*reinterpret_cast<PULONG32>(m_PackSeqAddress) + 0x4);
    if (!Base || Base == 0xFFFFFFFF)
        return std::make_tuple<bool, BYTE>(false, 0);
    BYTE* Seq = (PBYTE)(Base + 0x3A);
    return std::make_tuple<bool, BYTE>(true, InterlockedIncrement((LPLONG)Seq));
}

bool GamePack::StartGame(){
    auto IPackWrite = std::make_shared<PackWrite>();
    IPackWrite->WriteByte(0x41);
    IPackWrite->WriteByte(0x04);
    return MakePack(IPackWrite.get());
}

bool GamePack::BuyItem(int Index){
    auto IPackWrite = std::make_shared<PackWrite>();
    IPackWrite->WriteByte(0x4D);
    IPackWrite->WriteByte(0x02);
    IPackWrite->WriteByte(0x01);
    IPackWrite->WriteShort(Index);
    return MakePack(IPackWrite.get());
}

bool GamePack::Discipline(std::string name){
    auto IPackWrite = std::make_shared<PackWrite>();
    IPackWrite->WriteByte(0x65);
    IPackWrite->WriteByte(0x01);
    IPackWrite->WriteString(name);
	return MakePack(IPackWrite.get());
}

bool GamePack::MakePack(PackWrite* Pack){
    auto GetSeq = this->GetPackSeq();
    if (!std::get<bool>(GetSeq))return false;
    auto Seq = std::get<BYTE>(GetSeq);
    PackHead Pack_Head;
    Pack_Head.Seq = Seq;
    Pack_Head.Length = Pack->GetSize();

    PackWrite IPackWrite;
    IPackWrite.WriteByBits(&Pack_Head, sizeof(PackHead));
    IPackWrite.WriteByBits(Pack->GetBytes(), Pack->GetSize());
    return SendPack(&IPackWrite);
}

bool GamePack::SendPack(PackWrite* Pack){
    std::vector<BYTE>VecEncypt{};
    VecEncypt.resize(Pack->GetSize() * 2);

    int EncyptOutLength{};
    int Ret = EVP_EncryptUpdate007(this->m_Gamectx, VecEncypt.data(), &EncyptOutLength, Pack->GetBytes(), Pack->GetSize());
    if (!Ret)
        return false;

	if (!send(this->GameSocket, (const char*)VecEncypt.data(), EncyptOutLength, 0))
        return false;
    return true;
}
