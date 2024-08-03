#pragma once
#include "DrawBase.h"
#include <vector>
#include <Windows.h>
struct ItemStruct{
	std::string ChineseName;
	std::string WeaponName;
	std::string ItemName;
	int ItemIndex;
	bool CheckBoxNeed;
};

class Item{
private:
	virtual void UnkFun() = 0;
	virtual void UnkFun11() = 0;
public:
	virtual wchar_t* GetItemChineseName() = 0;
private:
	virtual void UnkFun1() = 0;
	virtual void UnkFun2() = 0;
	virtual void UnkFun3() = 0;
	virtual void UnkFun4() = 0;
	virtual void UnkFun5() = 0;
	virtual void UnkFun6() = 0;
	virtual void UnkFun7() = 0;
	virtual void UnkFun8() = 0;
	virtual void UnkFun9() = 0;
	virtual void UnkFun10() = 0;
public:
	virtual char* GetItemWeaponName() = 0;
	virtual char* GetItemTypeName() = 0;
};

class EnumItem {
private:
	virtual void UnkFun() = 0;
	virtual void UnkFun1() = 0;
	virtual void UnkFun2() = 0;
public:
	virtual Item* GetItem(int ItemIndex) = 0;
	static EnumItem* GetInstance();
};


class EnumGameItem :public DrawNode {
public:
	static auto& GetInstance() {
		static EnumGameItem Inter;
		return Inter;
	}
	EnumGameItem();
	virtual void DrawMenu()override;
	virtual const DrawGuiIInfo& GetGuiInfo()const override;
	void StartEnumItems();
	static void Thread();
	void Update();
	std::vector<ItemStruct>& GetWeaponList() { return WeaponItemList; };
public:
	ULONG32 P_ClientWeapon;
private:
	std::vector<ItemStruct>WeaponItemList;
	std::vector<std::string> BuyWeapon;
	ULONG32 LastIndex;
	std::vector<ULONG32> CurentIndex;
	PULONG32 P_CurrentIndex;
	bool IsInit;
	bool Start;
};