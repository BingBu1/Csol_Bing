#pragma once
using DropCall = void(__thiscall*)(const void*, bool, const char*, bool, bool);
class DropRoom_ {
public:
	DropRoom_() : DropFuns(), _this(), IsDrop() {}
	DropRoom_(DropCall Funs, const void* _this) : DropFuns(Funs), _this(_this) {}
	void Init(DropCall a, const void* b) { DropFuns = a; _this = b; }
	void Drop()noexcept;
	void ChangeIsDrop(bool IsDrop_) { IsDrop = IsDrop_; }
	bool GetIsDrop() { return this->IsDrop; }
private:
	DropCall DropFuns;
	const void* _this;
	bool IsDrop;
};
inline DropRoom_ DropRoom;