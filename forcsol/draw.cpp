#include "stdafx.h"
#include "main.h"
#include "darw.h"
#include "P_VGUI.h"
PULONG Font = nullptr;
int SetFont(int YFont) {
	if (Font) {
		int OldFont = *Font;
		*Font = YFont;
		return OldFont;
	}
	return -1;
}
void Darwingclass::���Ʒ���(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_Engine.pfnTintRGBA(x, y, w, h, r, g, b, a);
}
void Darwingclass::��������(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_Engine.pfnTintRGBA(x, y, w, h, r, g, b, a);
}
void Darwingclass::Vgui����(int x, int y, int w, int h, int linewidth, int r, int g, int b, int a)
{
	//        X						Y					W					H				R  G  B  A
	P_::P_Surface->DrawSetColor(r, g, b, a);
	P_::P_Surface->DrawLine(x, y, w, linewidth); // top
	P_::P_Surface->DrawLine(x + w - linewidth, y + linewidth, linewidth, h - linewidth); // right
	P_::P_Surface->DrawLine(x, y + linewidth, linewidth, h - linewidth); // left
	P_::P_Surface->DrawLine(x + linewidth, y + h - linewidth, w - linewidth * 2, linewidth); //bottom
}
void Darwingclass::���Ʒ���(int x, int y, int w, int h, int linewidth, int r, int g, int b, int a)
{
	//        X						Y					W					H				R  G  B  A
	��������(x, y, w, linewidth, r, g, b, a); // top
	��������(x + w - linewidth, y + linewidth, linewidth, h - linewidth, r, g, b, a); // right
	��������(x, y + linewidth, linewidth, h - linewidth, r, g, b, a); // left
	��������(x + linewidth, y + h - linewidth, w - linewidth * 2, linewidth, r, g, b, a); // bottom
}
void Darwingclass::DrawString(int x, int y, char* String, int Font) {
	int Old = SetFont(Font);
	g_pEngine->pfnDrawConsoleString(x, y, String);
	SetFont(Old);
}
void Darwingclass::DrawString(int x, int y, const char* String, int Font) {
	int Old = SetFont(Font);
	g_pEngine->pfnDrawConsoleString(x, y, (char*)String);
	SetFont(Old);
}
void MainMenu::Draw()noexcept {
	MainMenu* Temp;
	Temp = GetMainDraw();
	int TemNum = Temp->Num;
	if (Now < 0 || Now > Num) {
		Now = 0;
	}
	for (int i = 0; i < TemNum; i++){
		if (i == Now)
			Temp->Panit(true);
		else
			Temp->Panit(false);
		if (Temp->Next != nullptr) Temp = Temp->Next;
		else break;
	}
}

void MainMenu::Add(MainMenu* YourText) {
	MainMenu* Temp;
	for (Temp = GetMainDraw(); Temp->Next; Temp = Temp->Next);
	Temp->Next = YourText;
	Num += 1;
}

void MainMenu::Panit(bool NOW)noexcept {
	Darwingclass Draw;
	std::string d_Text;
	if (IsHaveBool && this->value != nullptr) {
		if (IsBestChar) {
			d_Text = fmt::format(xorstr_("{}    {}"), this->Text, BestChar[(int)value->value]);
		}else {
			d_Text = fmt::format(xorstr_("{}    {}"), this->Text, value->value ? xorstr_(u8"��") : xorstr_(u8"��"));
		}
	}else{
		d_Text = this->Text;
	}
	if (!GetNowIsInChild() && NOW) {
		Draw.���Ʒ���(this->x, this->y, 150, 22, 100, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(1, 0, 0);
		Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
	}
	else {
		Draw.���Ʒ���(this->x, this->y, 150, 22, 0, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(0, 1, 0);
		Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
	}
	if (this->DrawChild != nullptr && NOW) {
		this->DrawChild->Draw();
	}
}

bool MainMenu::SetValue(int SetLink, int SetValueNumb) {
	MainMenu* Temp = GetMainDraw();
	bool CanSet = true;
	for (int i = 0; i < SetLink; i++)
	{
		if (Temp->Next == NULL) {
			CanSet = false;
			break;
		}
		else {
			Temp = Temp->Next;
		}
	}
	if (CanSet) {
		if (Temp->value != nullptr && Temp->IsHaveBool) {
			Temp->value->value = SetValueNumb;
		}
		
		if (Temp->CallBackFun != nullptr) {
			typedef void (*VoidCall)();
			((VoidCall)Temp->CallBackFun)();
		}	
		return true;
	}
	return false;
}
bool MainMenu::SetChildValue(int SetLink, int SetValueNumb) {
	ChildClass* Temp = GetNowClass()->DrawChild;
	bool CanSet = true;
	for (int i = 0; i < SetLink; i++)
	{
		if (Temp->Next == NULL) {
			CanSet = false;
			break;
		}
		else {
			Temp = Temp->Next;
		}
	}
	if (CanSet && !Temp->IsLock) {
		if (Temp->IsHaveValue) {
			//Temp->value->value = SetValueNumb;
			Temp->ChangeValue(SetValueNumb);
		}
		if (Temp->CallBackFun != nullptr) {
			typedef void (*VoidCall)();
			((VoidCall)Temp->CallBackFun)();
		}
		return true;
	}
	return false;
}
MainMenu* MainMenu::GetNowClass() {
	MainMenu* temp;	int i;
	for (temp = GetMainDraw(), i = 0; temp->Next && i < Now; temp = temp->Next, i++);
	return temp;
}
bool MainMenu::SetBestValue(int SetLink, int SetValueNumb) {
	MainMenu* Temp = GetMainDraw();
	bool CanSet = true;
	for (int i = 0; i < SetLink; i++)
	{
		if (Temp->Next == NULL) {
			CanSet = false;
			break;
		}
		else {
			Temp = Temp->Next;
		}
	}
	if (CanSet) {
		if (SetValueNumb) {
			if (Temp->value->value < (Temp->BestcharCont - 1))
			{
				Temp->value->value += 1;
			}
		}
		else {
			int Cont = Temp->value->value - 1;
			if (Cont >= 0) {
				Temp->value->value -= 1;
			}
		}
	}
	return false;
}
void MainMenu::MainInit(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* Child, bool IsHaveDraw) noexcept {
	this->x = x;
	this->y = y;
	this->Text = std::string(YouDrawText);
	this->Name = std::string(YouDrawText);
	if (!Num)Num = 1;
	if (Value != nullptr)IsHaveValue = true;
	Now = 0;
	IsDraw = true;
	CallBackFun = Fun;
	value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = this;
	DrawChild = Child;
	NowIsInChild = false;
	IsHaveBool = IsHaveDraw;
	Last = this;
	Next = nullptr;
	CanLock = true;
}
void MainMenu::Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* Child, bool IsHaveDraw) noexcept {
	this->x = x;
	this->y = (y == NULL) ? (Node.Last->y + 30) : y;
	GetMainDraw()->Last = this;
	if (Value != nullptr)IsHaveValue = true;
	this->Text = std::string(YouDrawText);
	this->Name = std::string(YouDrawText);
	CallBackFun = Fun;
	Node.Add(this);
	value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = GetMainDraw();
	DrawChild = Child;
	IsHaveBool = IsHaveDraw;
	Next = nullptr;
	CanLock = true;
}
bool MainMenu::GetIsBestChar() {
	MainMenu* Temp = GetMainDraw();
	bool CanSet = true;
	int Now = Temp->Now;
	for (int i = 0; i < Now; i++)
	{
		if (Temp->Next == NULL) {
			CanSet = false;
			break;
		}
		else {
			Temp = Temp->Next;
		}
	}
	if (CanSet) {
		return Temp->IsBestChar;
	}
	return false;
}
void MainMenu::UpOrDown(bool TrueIsUp) {
	if (TrueIsUp) {
		int temp = 0;
		temp = Now + 1;
		if (temp >= 0 && temp < Num) {
			Now += 1;
			NowPage = Now / MaxPageNum;
		}
	}
	else {
		int temp = 0;
		temp = Now - 1;
		if (temp >= 0 && temp < Num) {
			Now -= 1;
			NowPage = Now / MaxPageNum;
		}
	}
}
void MainMenu::ChildUpOrDown(bool TrueIsUp) {
	auto NowClass = GetNowChildClass();
	if (TrueIsUp) {
		int temp = 0;
		temp = NowClass->Now + 1;
		if (temp >= 0 && temp < NowClass->Num) {
			NowClass->Now += 1;
			NowClass->NowPage = NowClass->Now / MaxPageNum;
		}
	}else {
		int temp = 0;
		temp = NowClass->Now - 1;
		if (temp >= 0 && temp < NowClass->Num) {
			NowClass->Now -= 1;
			NowClass->NowPage = NowClass->Now / MaxPageNum;
		}
	}
}
void MainMenu::SetBestChar(int i, ...) {
	IsBestChar = true;
	BestcharCont = i;
	va_list List;
	va_start(List, i);
	for (int o = 0; o < i; o++)
	{
		BestChar[o] = va_arg(List, char*);
	}
	va_end(List);
}
void MainMenu::GoChild() {
	NowIsInChild = true;
}
void MainMenu::BackMain() {
	NowIsInChild = false;
}
bool MainMenu::GetValueIsMin(){
	return this->value->value == 0 ? false : true;
}
�������� Darwingclass::WorldtoScreen(Vector ����)
{
	int �Ǵ� = 0;
	float p����[4][4];
	float(&����)[4][4] = p����;
	memcpy(p����, reinterpret_cast<float*>(�������), sizeof(p����));
	�������� ���� = { NULL };
	const int ��Ļ�� = g_pEngine->GetWindowCenterX();
	const int ��Ļ�� = g_pEngine->GetWindowCenterY();
	const int �ӽǿ� = ��Ļ�� / 2;
	const int �ӽǸ� = ��Ļ�� / 2;
	float ViewW = ����[2][0] * ����.x + ����[2][1] * ����.y + ����[2][2] * ����.z + ����[2][3];
	if (ViewW <= 0.01)
		return ����;
	ViewW = 1 / ViewW;
	int BoxX0 = �ӽǿ� + (����[0][0] * ����.x + ����[0][1] * ����.y + ����[0][2] * ����.z + ����[0][3]) * ViewW * �ӽǿ�;
	int BoxY0 = �ӽǸ� - (����[1][0] * ����.x + ����[1][1] * ����.y + ����[1][2] * (����.z + 60.0f) + ����[1][3]) * ViewW * �ӽǸ�;
	int BoxY1 = �ӽǸ� - (����[1][0] * ����.x + ����[1][1] * ����.y + ����[1][2] * (����.z - 10.0f) + ����[1][3]) * ViewW * �ӽǸ�;
	����.��� = BoxX0 - (BoxY0 - BoxY1) / 4;
	����.���� = BoxY0;
	����.�߶� = BoxY1 - BoxY0;
	����.��� = ����.�߶� / 2;
	return ����;
}
Darwingclass drawing;