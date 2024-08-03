#include "main.h"
#include "darw.h"
void ColorClass::Panit(bool Now) noexcept {
	Darwingclass Draw;
	if (GetNowIsInChild() && Now) {
		Draw.绘制方块(this->x, this->y, 200, 22, 100, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(1, 0, 0);
		Draw.DrawString(this->x + 2, this->y + 2, (char*)this->Text.c_str(), 1);
		char R[50], G[50], B[50];
		sprintf(R, "R:%d", this->DrawColor->r);
		sprintf(G, "G:%d", this->DrawColor->g);
		sprintf(B, "B:%d", this->DrawColor->b);
		if (!IsInChar) {
			g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
			Draw.DrawString(this->x + 100, this->y + 2, R, 1);
			g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
			Draw.DrawString(this->x + 140, this->y + 2, G, 1);
			g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
			Draw.DrawString(this->x + 180, this->y + 2, B, 1);
		}
		else {
			switch (CharNow)
			{
			case 1:
				Draw.绘制方块(this->x + 100, this->y + 1, 32, 15, this->DrawColor->r, this->DrawColor->g, this->DrawColor->b, 255);
				break;
			case 2:
				Draw.绘制方块(this->x + 140, this->y + 1, 32, 15, this->DrawColor->r, this->DrawColor->g, this->DrawColor->b, 255);
				break;
			case 3:
				Draw.绘制方块(this->x + 180, this->y + 1, 32, 15, this->DrawColor->r, this->DrawColor->g, this->DrawColor->b, 255);
				break;
			}
			g_Engine.pfnDrawSetTextColor(0, 1, 0);
			Draw.DrawString(this->x + 100, this->y + 2, R, 1);
			g_Engine.pfnDrawSetTextColor(0, 1, 0);
			Draw.DrawString(this->x + 140, this->y + 2, G, 1);
			g_Engine.pfnDrawSetTextColor(0, 1, 0);
			Draw.DrawString(this->x + 180, this->y + 2, B, 1);
		}
	}
	else {
		g_Engine.pfnDrawSetTextColor(0, 1, 0);
		if (!this->IsLock) {
			Draw.绘制方块(this->x, this->y, 200, 22, 0, 0, 200, 100);
			Draw.DrawString(this->x + 2, this->y + 2, (char*)this->Text.c_str(), 1);
			Draw.绘制方块(this->x + 150, this->y + 2, 32, 15, this->DrawColor->r, this->DrawColor->g, this->DrawColor->b, 255);
		}else {
			Draw.绘制方块(this->x, this->y, 200, 22, 128, 128, 128, 100);
			Draw.DrawString(this->x + 2, this->y + 2, (char*)this->Text.c_str(), 1);
			Draw.绘制方块(this->x + 150, this->y + 2, 32, 15, this->DrawColor->r, this->DrawColor->g, this->DrawColor->b, 255);
		}
	}
}
void ColorClass::Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* YouMain,color24 *Color)noexcept {
	this->x = x;
	this->y = (y == NULL) ? (YouMain->Last->y + 30) : y;
	this->Text = std::string(YouDrawText);
	if (Value != nullptr)IsHaveValue = true;
	Name = std::string(YouDrawText);
	CallBackFun = Fun;
	value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = YouMain;
	Next = nullptr;
	YouMain->Last = this;
	Main->Add(this);
	DrawColor = Color;
	YouMain->PageNum = !(Main->Num % MaxPageNum) ? (Main->Num / MaxPageNum) - 1 : YouMain->PageNum = Main->Num / MaxPageNum;
	if (y == NULL && Main->Num % MaxPageNum == 1)
		this->y = DefaultY;
}
void ColorClass::InGetCharColor() {
	CharNow = (CharNow < 3) ? CharNow += 1 : 0;
	this->IsInChar = (!this->IsInChar || CharNow != 0) ? true : false;
	memset(this->NumTemp, 0, 7);
	InputCount = 0;
}
void ColorClass::ColorValue(bool SubOrAdd) {
	if(!SubOrAdd){
		switch (CharNow)
		{
		case 1:
			this->DrawColor->r = (this->DrawColor->r > 0) ? this->DrawColor->r - 1 : this->DrawColor->r;
			break;
		case 2:
			this->DrawColor->g = (this->DrawColor->g > 0) ? this->DrawColor->g - 1 : this->DrawColor->g;
			break;
		case 3:
			this->DrawColor->b = (this->DrawColor->b > 0) ? this->DrawColor->b - 1 : this->DrawColor->b;
			break;
		}
	}
	else {
		switch (CharNow)
		{
		case 1:
			this->DrawColor->r = (this->DrawColor->r < 255) ? this->DrawColor->r + 1 : this->DrawColor->r;
			break;
		case 2:
			this->DrawColor->g = (this->DrawColor->g < 255) ? this->DrawColor->g + 1 : this->DrawColor->g;
			break;
		case 3:
			this->DrawColor->b = (this->DrawColor->b < 255) ? this->DrawColor->b + 1 : this->DrawColor->b;
			break;
		}
	}
}
void ColorClass::WinProc(UINT Message, WPARAM wParam) {
	if (IsInChar && Message == WM_KEYDOWN) {
		__asm {
			cmp wParam, ('0'-1)
			jbe JmpRet
			cmp wParam, '9'
			jae JmpRet
		}
		Hello:
		switch (CharNow)
		{
		case 1:
			if (InputCount < 3) {
				NumTemp[InputCount] = wParam;
				this->DrawColor->r = atoi(this->NumTemp);
				InputCount += 1;
			}
			break;
		case 2:
			if (InputCount < 3) {
				NumTemp[InputCount] = wParam;
				this->DrawColor->g = atoi(this->NumTemp);
				InputCount += 1;
			}
			break;
		case 3:
			if (InputCount < 3) {
				NumTemp[InputCount] = wParam;
				this->DrawColor->b = atoi(this->NumTemp);
				InputCount += 1;
			}
			break;
		}
	JmpRet:
		if (wParam>= VK_NUMPAD0) {
			if (wParam <= VK_NUMPAD9) {
				wParam -= 0x30;
				goto Hello;
			}
		}
		return;
		
	}
}