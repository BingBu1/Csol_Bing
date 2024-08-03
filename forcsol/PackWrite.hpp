#pragma once
#include "BasePack.hpp"

class PackWrite : public BasePack {
public:
	static PackWrite* GetInstance() {
		if (!m_Instace) {
			m_Instace = new PackWrite;
		}
		return m_Instace;
	}
	PackWrite() : WriteOffset() {};

	PackWrite(size_t Length) : WriteOffset() {
		PackBuff.resize(Length);
	}

	PackWrite(BYTE* buff, size_t Length) : WriteOffset(Length), BasePack(buff, Length) {
	}

	inline BYTE* GetBytes() {
		return PackBuff.data();
	}

	inline size_t GetSize() {
		return PackBuff.size();
	}

	inline void WriteByBits(void* Buff, size_t Length) {
		auto ByteWrite = static_cast<BYTE*>(Buff);
		PackBuff.resize(PackBuff.size() + Length);
		auto WriteBuff = PackBuff.begin() + WriteOffset;
		for (size_t i = 0; i < Length; i++, ByteWrite++) {
			WriteBuff[i] = *ByteWrite;
		}
		WriteOffset += Length;
	}

	inline void WriteByte(BYTE Write) {
		auto WriteBuff = std::make_unique<BYTE>(Write);
		WriteByBits(WriteBuff.get(), sizeof(Write));
	}

	inline void WriteChar(char Write) {
		auto WriteBuff = std::make_unique<char>(Write);
		WriteByBits(WriteBuff.get(), sizeof(Write));
	}

	inline void WriteInt(int Write) {
		auto WriteBuff = std::make_unique<int>(Write);
		WriteByBits(WriteBuff.get(), sizeof(Write));
	}

	inline void WriteShort(short Write) {
		auto WriteBuff = std::make_unique<short>(Write);
		WriteByBits(WriteBuff.get(), sizeof(Write));
	}

	inline void WriteString(std::string Str) {
		WriteByBits(Str.data(), Str.size() + 1);
	}

private:
	inline static PackWrite* m_Instace;
	int WriteOffset;
};