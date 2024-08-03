#include "main.h"
#include "darw.h"
#include <fmt/format.h>
void FloatClass::MainInit(int x, int y, char* YouDrawText, void* Fun, float* Value)noexcept {
	this->x = x;
	this->y = y;
	this->Text = std::string(YouDrawText);
	Name = std::string(YouDrawText);
	if (!Num)Num = 1;
	if (Value != nullptr)IsHaveValue = true;
	Now = 0;
	IsDraw = true;
	CallBackFun = Fun;
	this->Value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = this;
	Last = this;
	Next = nullptr;
	CanLock = true;
	if (y == NULL && Num % MaxPageNum == 1)
		this->y = DefaultY;
}

void FloatClass::Init(int x, int y, char* YouDrawText, void* Fun, float* Value, ChildClass* YouMain)noexcept {
	this->x = x;
	this->y = (y == NULL) ? (YouMain->Last->y + 30) : y;
	this->Text = std::string(YouDrawText);
	if (Value != nullptr)IsHaveValue = true;
	Name = std::string(YouDrawText);
	CallBackFun = Fun;
	this->Value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = YouMain;
	Next = nullptr;
	YouMain->Last = this;
	Main->Add(this);
	CanLock = true;
	YouMain->PageNum = !(Main->Num % MaxPageNum) ? (Main->Num / MaxPageNum) - 1 : YouMain->PageNum = Main->Num / MaxPageNum;
	if (y == NULL && Main->Num % MaxPageNum == 1)
		this->y = DefaultY;
}

void FloatClass::Panit(bool NOW)noexcept {
	Darwingclass Draw;
	std::string DrawString;
	if (this->Value != nullptr) {
		DrawString = fmt::format("{:s}    {:f}", this->Text.c_str(), *this->Value);
	}else {
		DrawString = this->Text;
	}
	if (GetNowIsInChild() && NOW) {
		Draw.绘制方块(this->x, this->y, 150, 22, 100, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
		Draw.DrawString(this->x + 2, this->y + 2, DrawString.c_str(), 1);
	}
	else {
		if (!this->IsLock) {
			Draw.绘制方块(this->x, this->y, 150, 22, 0, 0, 200, 100);
			g_Engine.pfnDrawSetTextColor(0, 1, 0);
			Draw.DrawString(this->x + 2, this->y + 2, DrawString.c_str(), 1);
		}
		else {
			Draw.绘制方块(this->x, this->y, 150, 22, 128, 128, 128, 100);
			g_Engine.pfnDrawSetTextColor(0, 1, 0);
			Draw.DrawString(this->x + 2, this->y + 2, DrawString.c_str(), 1);
		}
	}
}

void FloatClass::SetChangeValue(float Value)noexcept {
	this->ChangeFloatValue = Value;
}

void FloatClass::SetMaxMin(float Max, float Min)noexcept {
	this->Max = Max;
	this->Min = Min;
}

void FloatClass::ChangeValue(bool SetValue)noexcept {
	if (SetValue) {
		*this->Value = this->ChangeFloatValue + *this->Value >= this->Max ? this->Max : this->ChangeFloatValue + *this->Value;
	}else {
		*this->Value = *this->Value - this->ChangeFloatValue <= this->Max ? this->Min : *this->Value - this->ChangeFloatValue;
	}
}

bool FloatClass::GetValueIsMin()noexcept {
	return *this->Value == Min ? false : true;
}
