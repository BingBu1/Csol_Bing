#pragma once
#include<Windows.h>
#include<iostream>
#include<vector>
#include <string>
#include<time.h>

#define BLOCKMAXSIZE 409600//每次读取内存的最大大小

/*
	利用Sunday算法快速定位特征
*/
class SunDaySearch{
public:
	SunDaySearch();
	~SunDaySearch();
	inline int SearchMemory(std::string Tzm, unsigned __int64 StartAddress, unsigned __int64 SearchSize, std::vector<unsigned __int64>& ResultArray);
private:
	inline void SearchMemoryBlock(WORD* Tzm, WORD TzmLength, unsigned __int64 StartAddress, SIZE_T size, std::vector<unsigned __int64>& ResultArray);
	inline WORD GetTzmArray(char* Tzm, WORD* TzmArray);
	inline void GetNext(short* next, WORD* Tzm, WORD TzmLength);
	inline void DelStringBlank(std::string& str);
private:
	BYTE* MemoryData;//每次将读取的内存读入这里
	short Next[260];
	WORD* TzmArray;
};

SunDaySearch::SunDaySearch() : MemoryData(), Next(), TzmArray() {}


SunDaySearch::~SunDaySearch(){
	delete[] TzmArray;
}
/*
	删除String全部空格
*/
void SunDaySearch::DelStringBlank(std::string& str) {
	std::string Tmp;
	for (auto& C : str) {
		if (C != ' ') {
			Tmp.push_back(C);
		}
	}
	str = Tmp;
}

WORD SunDaySearch::GetTzmArray(char* Tzm, WORD* TzmArray) {
	int len = 0;
	auto Strlen_ = strlen(Tzm);
	WORD TzmLength = Strlen_ / 2;
	//将十六进制特征码转为十进制
	for (int i = 0; i < Strlen_; ) {
		char num[2];
		num[0] = Tzm[i++];
		num[1] = Tzm[i++];
		if (num[0] != '?' && num[1] != '?'){
			int sum = 0;
			WORD a[2]{};
			for (int i = 0; i < 2; i++){
				if (num[i] >= '0' && num[i] <= '9')
					a[i] = num[i] - '0';
				else if (num[i] >= 'a' && num[i] <= 'z')
					a[i] = num[i] - 87;
				else if (num[i] >= 'A' && num[i] <= 'Z')
					a[i] = num[i] - 55;
			}
			sum = a[0] * 16 + a[1];
			TzmArray[len++] = sum;
		}
		else
			TzmArray[len++] = 256;
	}
	return TzmLength;
}

void SunDaySearch::GetNext(short* next, WORD* Tzm, WORD TzmLength) {
	//特征码（字节集）的每个字节的范围在0-255（0-FF）之间，256用来表示问号，到260是为了防止越界
	for (int i = 0; i < 260; i++)
		next[i] = -1;
	for (int i = 0; i < TzmLength; i++)
		next[Tzm[i]] = i;
}

void SunDaySearch::SearchMemoryBlock(WORD* Tzm, WORD TzmLength, unsigned __int64 StartAddress, SIZE_T size, std::vector<unsigned __int64>& ResultArray) {
	MemoryData = (BYTE*)StartAddress;
	for (UINT i = 0u, j, k; i < size;)
	{
		j = i; k = 0;

		for (; k < TzmLength && j < size && (Tzm[k] == MemoryData[j] || Tzm[k] == 256); k++, j++);

		if (k == TzmLength)
		{
			ResultArray.push_back(StartAddress + i);
		}

		if ((i + TzmLength) >= size)
		{
			return;
		}

		int num = Next[MemoryData[i + TzmLength]];
		if (num == -1)
			i += (TzmLength - Next[256]);//如果特征码有问号，就从问号处开始匹配，如果没有就i+=-1
		else
			i += (TzmLength - num);
	}
}

int SunDaySearch::SearchMemory(std::string Tzm, unsigned __int64 StartAddress, unsigned __int64 SearchSize, std::vector<unsigned __int64>& ResultArray) {
	int i = 0;
	SIZE_T BlockSize;
	MEMORY_BASIC_INFORMATION mbi{};
	auto EndAddress = StartAddress + SearchSize;

	DelStringBlank(Tzm);
	WORD TzmLength = Tzm.length() / 2;
	WORD* TzmArray = new WORD[TzmLength];

	GetTzmArray(Tzm.data(), TzmArray);
	GetNext(Next, TzmArray, TzmLength);

	//初始化结果数组
	ResultArray.clear();

	while (VirtualQuery((LPCVOID)StartAddress, &mbi, sizeof(mbi)) != 0)
	{
		//获取可读可写和可读可写可执行的内存块
		if (mbi.Protect == PAGE_EXECUTE_READ)
		{
			i = 0;
			BlockSize = mbi.RegionSize;
			//搜索这块内存
			while (BlockSize >= BLOCKMAXSIZE) {
				SearchMemoryBlock(TzmArray, TzmLength, StartAddress + (BLOCKMAXSIZE * i), BLOCKMAXSIZE, ResultArray);
				BlockSize -= BLOCKMAXSIZE; i++;
			}
			SearchMemoryBlock(TzmArray, TzmLength, StartAddress + (BLOCKMAXSIZE * i), BlockSize, ResultArray);
		}
		StartAddress += mbi.RegionSize;

		if (EndAddress != 0 && StartAddress > EndAddress)
		{
			return ResultArray.size();
		}
	}
	return ResultArray.size();
}