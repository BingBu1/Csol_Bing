#pragma once
#include <Windows.h>
#include <string_view>
#include <string>
#include <algorithm>
namespace util{
	inline void tolower(std::string& string) {
		int Index = 0;
		for (auto &i : string){
			string[Index] = std::tolower(i);
			Index++;
		}
	}
	inline bool HookIatTable(PVOID BaseAddress, const char* DllName, const char* FunName, PVOID Orgin, PVOID OldFunsAddress = nullptr) {
		auto DosHead = static_cast<PIMAGE_DOS_HEADER>(BaseAddress);
		auto NtHead = reinterpret_cast<PIMAGE_NT_HEADERS>(static_cast<PUCHAR>(BaseAddress) + DosHead->e_lfanew);
		auto ImportDate = NtHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
		auto ImportDes = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(ImportDate.VirtualAddress + reinterpret_cast<ULONG32>(BaseAddress));
		while (ImportDes->Name) {
			if (DllName) {
				std::string imp_DllName = reinterpret_cast<const char*>(static_cast<PUCHAR>(BaseAddress) + ImportDes->Name);
				tolower(imp_DllName);
				if (imp_DllName == DllName) {
					PIMAGE_THUNK_DATA OriginFirstThunk = reinterpret_cast<PIMAGE_THUNK_DATA>(static_cast<PUCHAR>(BaseAddress) + ImportDes->OriginalFirstThunk);
					PIMAGE_THUNK_DATA FirstThukn = reinterpret_cast<PIMAGE_THUNK_DATA>(static_cast<PUCHAR>(BaseAddress) + ImportDes->FirstThunk);
					while (OriginFirstThunk->u1.AddressOfData) {
						auto  FuntionName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(static_cast<PUCHAR>(BaseAddress) + OriginFirstThunk->u1.AddressOfData);
						if (!strcmp(FuntionName->Name, FunName)) {
							if (OldFunsAddress)
								*reinterpret_cast<PVOID*>(OldFunsAddress) = reinterpret_cast<PVOID>(FirstThukn->u1.Function);
							DWORD OldProect{};
							VirtualProtect(&(FirstThukn->u1.Function), 0x1000, PAGE_EXECUTE_READWRITE, &OldProect);
							FirstThukn->u1.Function = reinterpret_cast<DWORD> (Orgin);
							return true;
						}
						FirstThukn++;
						OriginFirstThunk++;
					}
				}
			}
			ImportDes++;
		}
		return false;
	}
	inline bool HookIatTable2(PVOID BaseAddress, const char* DllName, const char* FunName, PVOID Orgin, PVOID OldFunsAddress = nullptr) {
		auto DosHead = static_cast<PIMAGE_DOS_HEADER>(BaseAddress);
		auto NtHead = reinterpret_cast<PIMAGE_NT_HEADERS>(static_cast<PUCHAR>(BaseAddress) + DosHead->e_lfanew);
		auto ImportDate = NtHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
		auto ImportDes = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(ImportDate.VirtualAddress + reinterpret_cast<ULONG32>(BaseAddress));
		auto FunsAddress = GetProcAddress(GetModuleHandle(DllName), FunName);
		if (!FunsAddress)return false;
		while (ImportDes->Name) {
			PIMAGE_THUNK_DATA OriginFirstThunk = reinterpret_cast<PIMAGE_THUNK_DATA>(static_cast<PUCHAR>(BaseAddress) + ImportDes->OriginalFirstThunk);
			PIMAGE_THUNK_DATA FirstThukn = reinterpret_cast<PIMAGE_THUNK_DATA>(static_cast<PUCHAR>(BaseAddress) + ImportDes->FirstThunk);
			while (FirstThukn->u1.Function) {
				if (FirstThukn->u1.Function == reinterpret_cast<DWORD>(FunsAddress)) {
					if (OldFunsAddress)
						*reinterpret_cast<PVOID*>(OldFunsAddress) = reinterpret_cast<PVOID>(FirstThukn->u1.Function);
					DWORD OldProect{};
					VirtualProtect(&(FirstThukn->u1.Function), 0x1000, PAGE_EXECUTE_READWRITE, &OldProect);
					FirstThukn->u1.Function = reinterpret_cast<DWORD> (Orgin);
					return true;
				}
				FirstThukn++;
				OriginFirstThunk++;
			}
			ImportDes++;
		}
		return false;
	}

	inline std::string UTF8_To_CP(std::string Str) {
		WCHAR Char[255]{};
		char Char_[255]{};
		MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), -1, Char, sizeof(Char));
		WideCharToMultiByte(CP_OEMCP, 0, Char, -1, Char_, sizeof(Char_), 0, 0);
		return Char_;
	}
}