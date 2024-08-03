#pragma once
#include "BasePack.hpp"
class PackRead : public BasePack {
public:
	static PackRead* GetInstance() {
		if (!m_Instace) {
			m_Instace = new PackRead;
		}
		return m_Instace;
	}
	PackRead() = default;

	PackRead(BYTE* buff, size_t Length) : NowReadLength(), MaxReadLength(Length), BasePack(buff, Length) {

	}

	inline void SetReadOffset(size_t Length) {
		NowReadLength = Length;
	}

	inline std::shared_ptr<BYTE> ReadByBits(size_t ReadLength) {
		std::shared_ptr<BYTE> Buff(new BYTE[ReadLength]);
		auto ReadPonit = PackBuff.data() + NowReadLength;
		memcpy(Buff.get(), ReadPonit, ReadLength);
		NowReadLength += ReadLength;
		if (NowReadLength > MaxReadLength) {

		}
		return Buff;
	}

	inline char ReadChar() {
		auto ReadPoint = ReadByBits(1);
		if (ReadPoint) {
			return *reinterpret_cast<char*> (ReadPoint.get());
		}
		return 0;
	}

	inline BYTE ReadByte() {
		auto ReadPoint = ReadByBits(1);
		if (ReadPoint) {
			return *ReadPoint;
		}
		return 0;
	}

	inline int ReadInt() {
		auto ReadPoint = ReadByBits(4);
		if (ReadPoint) {
			return *reinterpret_cast<int*> (ReadPoint.get());
		}
		return 0;
	}

	inline short ReadShort() {
		auto ReadPoint = ReadByBits(2);
		if (ReadPoint) {
			return *reinterpret_cast<short*> (ReadPoint.get());
		}
		return 0;
	}

	inline std::string ReadString(){
		std::string RetVal{};
		do {
			auto R_Char = ReadChar();
			RetVal.push_back(R_Char);
			if (R_Char == '\0')
				break;
		} while (true);
		return RetVal;
	}

private:
	inline static PackRead* m_Instace;
	int NowReadLength;
	int MaxReadLength;
};