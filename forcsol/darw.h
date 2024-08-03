#pragma once
#include <string>
#include <fmt/format.h>
#include <unordered_map>
class ChildClass;
class MainMenu;
class Darwingclass;
extern Darwingclass drawing;
extern MainMenu Node;
extern PULONG Font;
#define MaxPageNum 10
#define DefaultY 70
struct BestString {
	std::string String;
	BestString* NextString;
};

struct 方框数据
{
	int 左边;
	int 顶边;
	int 宽度;
	int 高度;
};
class Darwingclass
{
public:
	void 绘制方框(int x, int y, int w, int h, int linewidth, int r, int g, int b, int a);
	void Vgui方框(int x, int y, int w, int h, int linewidth, int r, int g, int b, int a);
	void 绘制线条(int x, int y, int w, int h, int r, int g, int b, int a);
	void 绘制方块(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawString(int x, int y, char* String, int Font);
	void DrawString(int x, int y, const char* String, int Font);
	方框数据 WorldtoScreen(Vector 坐标);
private:

};
class Base {
public:
	virtual void ColorValue(bool SubOrAdd) = 0;
	virtual void SetCantLock() = 0;
	virtual void SetLock() = 0;
	virtual bool GetIsLocked() = 0;
};
class MainMenu : public Base {
public:
	MainMenu()noexcept : Text(), Name(), IsDraw(true), CallBackFun(nullptr), IsBestChar(), BestcharCont(), NowIsInChild(), Now(), Num(), IsHaveValue(false),
		Next(), Last(), Main(), DrawChild(), BestChar(), IsLock()
	{}
	virtual void MainInit(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* Child, bool IsHaveDraw = true)noexcept;
	virtual void Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* Child, bool IsHaveDraw = true)noexcept;
	virtual void Draw()noexcept;
	virtual void Add(MainMenu* YourText);
	virtual void Panit(bool NOW)noexcept;
	virtual void UpOrDown(bool TrueIsUp);
	virtual void SetBestChar(int i, ...);
	virtual bool SetValue(int SetLink, int SetValueNumb);
	virtual bool SetBestValue(int SetLink, int SetValueNumb);
	virtual void ChildUpOrDown(bool TrueIsUp);
	virtual bool SetChildValue(int SetLink, int SetValueNumb);
	virtual void ChangeValue(bool SetValue) {};
	virtual bool GetIsBestChar();
	virtual void GoChild();
	virtual void BackMain();
	virtual bool GetValueIsMin();
	virtual MainMenu* GetMainDraw()noexcept { return Node.Main; };
	virtual MainMenu* GetNowClass();
	virtual BOOL IsColorClass(void) noexcept { return FALSE; };
	int GetNowIsInChild()noexcept { return Node.NowIsInChild; };
	int GetNow()noexcept { return Node.Now; };
	auto GetNowChildClass()noexcept { return this->GetNowClass()->DrawChild; }
	virtual void ColorValue(bool SubOrAdd) {}
	virtual void SetCantLock() { this->CanLock = false; }
	virtual void SetLock() { this->IsLock = true; }
	virtual bool GetIsLocked() { return this->IsLock; }
public:
	int x;
	int y;
	int Num;
	int Now;
	bool IsDraw;
	pcvar_t value;
protected:
	MainMenu* Next;
	MainMenu* Last;
	MainMenu* Main;
	ChildClass* DrawChild;
	int PageNum;
	int NowPage;
	std::string Text;
	std::string Name;
	char* BestChar[7];
	void* CallBackFun;
	bool IsBestChar;
	int BestcharCont;
	bool NowIsInChild;
	bool IsHaveBool;
	bool CanLock;
	bool IsHaveValue;
	bool IsLock;
};

class ChildClass : public MainMenu{
public:
	ChildClass() noexcept : MainMenu(), Next(), Last(), Main(), PageNum(), NowPage(), BestChar(), head(nullptr), end(nullptr) {}
	virtual void MainInit(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value)noexcept;
	virtual void Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* YouMain)noexcept;
	virtual void Add(ChildClass* YourText)noexcept;
	virtual void Add(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value)noexcept;
	virtual void AddColor(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, color24* Color)noexcept;
	virtual void AddFloat(int x, int y, char* YouDrawText, void* Fun, float* Value)noexcept;
	virtual void Draw()noexcept;
	virtual void Panit(bool NOW)noexcept;
	virtual bool SetBestValue(int Index, int SetValue);
	virtual void SetBestChar(int i, ...);
	virtual bool GetIsBestChar();
	virtual ChildClass* GetMainDraw()noexcept { return Main; };
	virtual void UpOrNextPage(bool IsUp)noexcept;
	virtual ChildClass* FindChildClassByName(char* Name)noexcept;
	virtual ChildClass* GetNowClass()  noexcept override;
	virtual void ChangeValue(bool SetValue) noexcept override;
	virtual void LockAllFunc();
	virtual void UnLockAllFunc();
	int GetNowValue() noexcept;
	virtual BOOL IsColorClass(void) noexcept  { return FALSE; };
	virtual void WinProc(UINT Message, WPARAM wParam) { };
	virtual void ColorValue(bool SubOrAdd) {}
public:
	template<typename ..._T>
	void SetBestChar2(_T&&... Parm)noexcept {
		::std::vector<std::string> Tmp = { std::forward<std::string>(Parm) ... };
		this->IsBestChar = true;
		this->BestcharCont = Tmp.size();
		auto Tmp2 = this->BestChar = new BestString;
		for (auto i : Tmp) {
			Tmp2->String = i;
			Tmp2->NextString = new BestString;
			Tmp2 = Tmp2->NextString;
		}
	}
public:
	ChildClass* Next;
	ChildClass* Last;
	ChildClass* Main;
	int PageNum;
	int NowPage;
	BestString* BestChar;
	std::unordered_map<int, ChildClass*>* head, * end;
};

class ColorClass : public ChildClass{
public:
	ColorClass() noexcept : ChildClass(), NumTemp(), InputCount(), CharNow(), IsInChar(), DrawColor() {}
	virtual void Panit(bool NOW)noexcept override;
	virtual BOOL IsColorClass(void) noexcept { return TRUE; };
	void Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* YouMain, color24 *Color)noexcept;
	void InGetCharColor();
	virtual void ColorValue(bool SubOrAdd) override;
	virtual bool GetValueIsMin() override { return false; };
	virtual void WinProc(UINT Message, WPARAM wParam);
private:
	color24* DrawColor;
	bool IsInChar;
	int CharNow;
	char NumTemp[7];
	char InputCount;
};

class FloatClass : public ChildClass {
public:
	FloatClass() noexcept : ChildClass(), ChangeFloatValue(0.1f) {}
	virtual void MainInit(int x, int y, char* YouDrawText, void* Fun, float* Value)noexcept;
	virtual void Init(int x, int y, char* YouDrawText, void* Fun, float* Value, ChildClass* YouMain)noexcept;
	virtual void Panit(bool NOW)noexcept override;
	void SetChangeValue(float Value)noexcept;
	void SetMaxMin(float Max, float Min)noexcept;
	virtual void ChangeValue(bool SetValue)noexcept override;
	virtual bool GetValueIsMin()noexcept override;
	virtual BOOL IsColorClass(void) noexcept { return FALSE; };
private:
	float* Value;
	float ChangeFloatValue;
	float Max, Min;
};

extern ChildClass* MpChild;
extern ChildClass* MeMpChild;