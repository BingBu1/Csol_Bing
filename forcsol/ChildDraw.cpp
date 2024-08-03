#include "main.h"
/*
	����������Ʋ˵�
*/
void ChildClass::Draw()noexcept {
	static Darwingclass* _Draw = new Darwingclass;
	ChildClass* Temp = this;
	int TheNum = Temp->Num;
	int ThePageNum = Temp->NowPage * MaxPageNum; //���ҳ����
	if (Temp->NowPage < Temp->PageNum) {
		ThePageNum ? TheNum = MaxPageNum : TheNum > MaxPageNum ? TheNum = MaxPageNum : NULL;
	}else if (ThePageNum && Temp->NowPage == Temp->PageNum) {
		TheNum = Temp->Num % MaxPageNum ? Temp->Num % MaxPageNum : MaxPageNum;
	}
	if (this->PageNum) {
		ChildClass* End = (*this->end)[this->NowPage];
		auto  PageString = fmt::format(XorString(u8"��ǰҳ({:d}/{:d})"), this->NowPage, this->PageNum);
		_Draw->���Ʒ���(End->x, End->y + 30, 150, 22, 0, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(0, 1, 0);
		_Draw->DrawString(End->x, End->y + 32, PageString.c_str(), 1);
	}
	int TheNow = ThePageNum;
	for (auto i = (*this->head)[this->NowPage]; i != (*this->end)[this->NowPage]->Next; i = i->Next) {
		//�Ƿ��ǵ�ǰѡ�еĲ˵���ҳ
		if (TheNow == Now)i->Panit(true);
		else i->Panit(false);
		TheNow++;
	}
}
/*
	�������⿪��ֵ
*/
bool ChildClass::SetBestValue(int SetLink, int SetValueNumb) {
	ChildClass* Temp = GetMainDraw();
	bool CanSet = true;
	for (int i = 0; i < SetLink && Temp->Next; Temp = Temp->Next, i++);
	CanSet = (Temp) ? true : false;
	if (CanSet && !Temp->IsLock) {
		if (SetValueNumb) {
			Temp->value->value = (Temp->value->value < (Temp->BestcharCont - 1)) ? Temp->value->value + 1 : Temp->value->value;
		}else {
			Temp->value->value = (Temp->value->value - 1 >= 0) ? Temp->value->value - 1 : Temp->value->value;
		}
		if (Temp->CallBackFun) {
			using VoidCall = void(*)();
			reinterpret_cast<VoidCall>(Temp->CallBackFun)();
		}
		return true;
	}
	return false;
}
/*
	�������ʼ��
*/
void ChildClass::MainInit(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value)noexcept {
	this->x = x;
	this->y = y;
	this->Text = std::string(YouDrawText);
	Name = std::string(YouDrawText);
	if (!Num)Num = 1;
	if (Value != nullptr)IsHaveValue = true;
	Now = 0;
	IsDraw = true;
	CallBackFun = Fun;
	value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = this;
	Last = this;
	Next = nullptr;
	CanLock = true;
	head = new std::unordered_map<int, ChildClass*>;
	end = new std::unordered_map<int, ChildClass*>;
	(*head)[0] = this;
	if (y == NULL && Num % MaxPageNum == 1)
		this->y = DefaultY;
}
/*
	�������ʼ��
*/
void ChildClass::Init(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, ChildClass* YouMain)noexcept {
	this->x = x;
	this->y = (y == NULL) ? (YouMain->Last->y + 30) : y;
	this->Text = std::string(YouDrawText);
	Name = std::string(YouDrawText);
	if (Value != nullptr)IsHaveValue = true;
	CallBackFun = Fun;
	value = Value;
	IsBestChar = false;
	BestcharCont = 0;
	Main = YouMain;
	Next = nullptr;
	YouMain->Last = this;
	YouMain->Add(this);
	CanLock = true;
	YouMain->PageNum = !(Main->Num % MaxPageNum) ? (Main->Num / MaxPageNum) - 1 : Main->Num / MaxPageNum;
	(*YouMain->head)[YouMain->PageNum] = Main->Num % MaxPageNum == 1 ? this : (*YouMain->head)[YouMain->PageNum];
	(*YouMain->end)[YouMain->PageNum] = this;
	if (y == NULL && Main->Num % MaxPageNum == 1)
		this->y = DefaultY;
}
/*
	������������
*/
void ChildClass::Add(ChildClass* YourText)noexcept {
	ChildClass* Temp;
	for (Temp = GetMainDraw(); Temp->Next; Temp = Temp->Next);
	Temp->Next = YourText;
	Num += 1;
}
/*
	���һ����������
*/
void ChildClass::Add(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value)noexcept {
	ChildClass* Temp = new ChildClass, * Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this);
}
/*
	���һ��������ɫ����
*/
void ChildClass::AddColor(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, color24* Color)noexcept {
	ColorClass* Temp = new ColorClass;
	auto Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this, Color);
}
/*
	���һ������Float����
*/
void ChildClass::AddFloat(int x, int y, char* YouDrawText, void* Fun, float* Value) noexcept{
	FloatClass* Temp = new FloatClass;
	auto Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this);
}
/*
	��ʼ���Ƶ����˵�
*/
void ChildClass::Panit(bool NOW)noexcept {
	Darwingclass Draw;
	std::string d_Text;
	if (this->value != nullptr) {
		if (this->IsBestChar) {
			BestString* DrawString = BestChar;
			for (int i = 0; i < value->value; i++){
				DrawString = DrawString->NextString;
			}
			d_Text = fmt::format(XorString("{}    {}"), this->Text, DrawString->String);
		}
		else {
			d_Text = fmt::format(XorString("{}    {}"), this->Text, value->value ? XorString(u8"��") : XorString(u8"��"));
		}
	}else d_Text = this->Text;
	if (GetNowIsInChild() && NOW) {
		Draw.���Ʒ���(this->x, this->y, 150, 22, 100, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
		Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
	}
	else {
		g_Engine.pfnDrawSetTextColor(0, 1.f, 0);
		if (!this->IsLock) {
			Draw.���Ʒ���(this->x, this->y, 150, 22, 0, 0, 200, 100);
			Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
		}else {
			Draw.���Ʒ���(this->x, this->y, 150, 22, 128, 128, 128, 100);
			Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
		}	
	}
}
/*
	��ȡ��ǰѡ�еĲ˵�Inx
*/
int ChildClass::GetNowValue() noexcept {
	ChildClass* temp; int i;
	for (temp = GetMainDraw(), i = 0; temp->Next && i < Now; temp = temp->Next, i++);
	return temp->IsHaveValue ? temp->GetValueIsMin() : false;
	//ChildClass* Temp = GetMainDraw();
	//int TemNow = Temp->Now;
	//bool CanSet = true;
	//for (int i = 0; i < TemNow; i++)
	//{
	//	if (Temp->Next == NULL) {
	//		CanSet = false;
	//		break;
	//	}
	//	else {
	//		Temp = Temp->Next;
	//	}
	//}
	//if (CanSet) {
	//	if (Temp->IsHaveValue) {
	//		return Temp->GetValueIsMin();
	//	}else {
	//		return false;
	//	}
	//}
	//return false;
}
/*
	��������ڴ�
*/
void ZeroMem(int size,int num, ...) {
	va_list List;
	va_start(List, num);
	for (int o = 0; o < num; o++){
		RtlZeroMemory(va_arg(List, MainMenu*), size);
	}
	va_end(List);
}
/*
	��ʼ�������ַ���
*/
void ChildClass::SetBestChar(int i, ...) {
	this->IsBestChar = true;
	this->BestcharCont = i;
	va_list List;
	va_start(List, i);
	this->BestChar = new BestString;
	BestString* Now = this->BestChar;
	for (int o = 0; o < i; o++){
		Now->String = std::string(va_arg(List, char*));
		Now->NextString = new BestString;
		Now = Now->NextString;
	}
	va_end(List);
}
/*
	��ȡ��ǰ�˵��Ƿ���������Value
*/
bool ChildClass::GetIsBestChar() {
	ChildClass* Temp = GetMainDraw(), *i;
	int Now = Temp->Now, c = 0;
	for (i = Temp, c = 0; c < Now && i; c++, i = i->Next);
	return i->IsBestChar;
}
/*
	��ҳ
*/
void ChildClass::UpOrNextPage(bool IsUp)noexcept {
	ChildClass* Temp = GetMainDraw();
	if (IsUp) {
		if (Temp->NowPage > 0) {
			Temp->Now = (Temp->NowPage - 1) * 10;
			Temp->NowPage -= 1;
		}
	}else {
		if (Temp->NowPage < Temp->PageNum) {
			Temp->Now = (Temp->NowPage + 1) * 10;
			Temp->NowPage += 1;
		}
	}
}
/*
	������ǰ�˵���������-����һ��������ö���
*/
void ChildClass::LockAllFunc() {
	ChildClass* Temp = GetMainDraw();
	for (; Temp; Temp = Temp->Next) {
		if (Temp->CanLock)Temp->IsLock = true;
	}
}
/*
	��������ǰ�˵���������-����һ��������ö���
*/
void ChildClass::UnLockAllFunc() {
	ChildClass* Temp = GetMainDraw();
	for (; Temp; Temp = Temp->Next) {
		if (Temp->CanLock)Temp->IsLock = false;
	}
}
/*
	��������������
*/
ChildClass* ChildClass::FindChildClassByName(char* Name)noexcept {
	static ChildClass* Temp = GetMainDraw();
	for (; Temp; Temp = Temp->Next){
		if (Temp->Name == Name) {
			return Temp;
		}
	}
	return nullptr;
}
ChildClass* ChildClass::GetNowClass() noexcept {
	ChildClass* temp;	int i;
	for (temp = GetMainDraw(), i = 0; temp->Next && i < Now; temp = temp->Next, i++);
	return temp;
}
void ChildClass::ChangeValue(bool SetValue)noexcept {
	SetValue ? this->value->value = true : this->value->value = false;
}
/*
	value�˵����ܵĿ��ؽṹ
*/
cvar_t DefCvar, MapBring, Vk, BossSpeed, autoFire, BugScer, HighUpload, CNoWhite, NoSmoke, trigger, air, DrawHeal, VoxelFuckMap, VoxelSkyValuel, VoxelBringht, VoxelFirendKill, HowBlock
, DeadLongRpn, ZombieFuckMap, ZombieRedX, InitBack, FireDam, FogValue, FogStatcValue, BoomValue, VxlFuckRoomPlayer, MaxBrring, VoxelSee, VxlRGBFOG, VxlHigeBlock, C_DelMenu, C_GetAmmo, VxlMapLight
, NotRpn_, VoxelBuyBugB, VxlHigeFriend, VxlResetTrigger, VxlCloseFriend, SpeedHackAutoRoom, SpeedNotDraw, Like��˿;

cvar_t MpHeal, MpSpeed, MpFire, MpRightFire, MpDrawAll, MpFuckInxCv, MpFlySky, MpBuyMyG, MpAllInfAmmo, MpMyModle, MpLeave, MpSetsv, MpAngle, MpLockWeapon, MpGrad;

cvar_t MeMpHeal, MeMpFire, MeMpRightFire, MeMpMouseTp, MeMpSpeedHack, MeMpNoAngle, MeMpMouseMonsterTp;

color24 MapColor, FogColor;
/*
	��Ϊ��Ҫ���������������������Զ���Ϊȫ��
*/
ChildClass* MpChild = new ChildClass;
ChildClass* MeMpChild = new ChildClass;
/*
	***************************************

	��ʼ���˵���������Ҫ���ƵĲ˵���������

	***************************************
*/
void TextClassInit() {
	//�����ڴ�
	MainMenu* Two = new MainMenu;
	MainMenu* UseDes = new MainMenu;
	MainMenu* Fuck = new MainMenu;
	MainMenu* Voxel = new MainMenu;
	MainMenu* Mp = new MainMenu;
	MainMenu* MeMp = new MainMenu;
	MainMenu* Vip = new MainMenu;
	//������
	ChildClass* MainChild = new ChildClass;
	ChildClass* SecChild = new ChildClass;
	ChildClass* VoxelChild = new ChildClass;
	//������
	ChildClass* Child = new ChildClass;
	ChildClass* MapChild = new ChildClass;
	ChildClass* NoWhite = new ChildClass;
	ChildClass* NoSmock = new ChildClass;
	ChildClass* SpeedHack = new ChildClass;
	ChildClass* AtuoFireH = new ChildClass;
	ChildClass* GameIf = new ChildClass;
	ChildClass* HighUploadSpeed = new ChildClass;
	ChildClass* Drawtrigger = new ChildClass;
	ChildClass* IsDrawAir = new ChildClass;
	ChildClass* DrawMouseHeal = new ChildClass;
	ChildClass* FuckVoxelMap = new ChildClass;
	ChildClass* ResetVoxel = new ChildClass;
	ChildClass* VoxelBuyBug = new ChildClass;
	ChildClass* VoxelBuyBugByB = new ChildClass;
	ChildClass* VoxelSky = new ChildClass;
	ChildClass* VoxelGlodTry = new ChildClass;
	ChildClass* VoxelWeaponBox = new ChildClass;
	ChildClass* VoxelSkyBright = new ChildClass;
	ChildClass* VoxelFriendDam = new ChildClass;
	ChildClass* VoxelNpc = new ChildClass;
	ChildClass* VoxelC4 = new ChildClass;
	ChildClass* HowFuckBlock = new ChildClass;
	ChildClass* DeadSuperLongRpn = new ChildClass;
	ChildClass* VoxelZombieFuckMap = new ChildClass;
	ChildClass* IsZombieRedX = new ChildClass;
	ChildClass* VoxelInitBack = new ChildClass;
	ChildClass* Rool = new ChildClass;
	ChildClass* BuyRool = new ChildClass;
	ChildClass* Gold9999 = new ChildClass; 
	ChildClass* WarehouseBlock = new ChildClass;
	ChildClass* VoxelFireDam = new ChildClass;
	ChildClass* Fog = new ChildClass;
	ChildClass* FogStatc = new ChildClass;
	ChildClass* MpMaxSpeed = new ChildClass;
	ChildClass* MpFuckAllWeapon = new ChildClass;
	ChildClass* MpFuckAll = new ChildClass;
	ChildClass* MpFireSpeed = new ChildClass;
	ChildClass* MpRightFireSpeed = new ChildClass;
	ChildClass* MpFuckFlyken = new ChildClass;
	ChildClass* MpDrawAllEdit = new ChildClass;
	ChildClass* MpFuckAllMan = new ChildClass;
	ChildClass* MpFuckInx = new ChildClass;
	ChildClass* MpAllManFly = new ChildClass;
	ChildClass* MpFuckAllfly = new ChildClass;
	ChildClass* MpBuyG = new ChildClass;
	ChildClass* MpInfAmmo = new ChildClass;
	ChildClass* MpFuckModle = new ChildClass;
	ChildClass* MpLeaveMe = new ChildClass;
	ChildClass* MpSet = new ChildClass;
	ChildClass* MpTheSet = new ChildClass;
	ChildClass* FastReset = new ChildClass;
	ChildClass* MpFuckAllRpn = new ChildClass;
	ChildClass* MpAllNoViewAngle = new ChildClass;
	ChildClass* MpAllLockWeapon = new ChildClass;
	ChildClass* MpGGG= new ChildClass;
	ChildClass* InfBoom = new ChildClass;
	ChildClass* VoxelComputerPass = new ChildClass;
	ChildClass* AutoMcj = new ChildClass;
	ChildClass* AtouSpeed = new ChildClass;
	ChildClass* LoadVxlSave = new ChildClass;
	ChildClass* VxlSave = new ChildClass;
	ChildClass* MeMpFireSpeed = new ChildClass;
	ChildClass* MeMpRightFireSpeed = new ChildClass;
	ChildClass* MeMpOhFuckYou = new ChildClass;
	ChildClass* MeMpSpeed = new ChildClass;
	ChildClass* MeMpNoViewAngle = new ChildClass;
	ChildClass* MeMpMonsterTp = new ChildClass;
	ChildClass* AutoSpeed = new ChildClass;
	ChildClass* MeMpKillAllMonster = new ChildClass;
	ChildClass* VxlGetBlockWeapon = new ChildClass;
	ChildClass* VxlFuckRoom = new ChildClass;
	ChildClass* VxlCanYouSeeMe = new ChildClass;
	ChildClass* MeMpFireFuck = new ChildClass;
	ChildClass* GMaxBrring = new ChildClass;
	ChildClass* VxlAutoBright = new ChildClass;
	ChildClass* VxlRGBFog = new ChildClass;
	ChildClass* VxlHigeFuckBlock = new ChildClass;
	ChildClass* VxlHigeFuckFriend = new ChildClass;
	ChildClass* DelMenu = new ChildClass;
	ChildClass* GetAmmo = new ChildClass;
	ChildClass* VxlKillPushBlock = new ChildClass;
	ChildClass* VxlKillDamBlock = new ChildClass;
	ChildClass* VxlKillWeaponBlock = new ChildClass;
	ChildClass* VxlSetMapLight = new ChildClass;
	ChildClass* VxlNotRpn = new ChildClass;
	ChildClass* VxlResetT = new ChildClass;
	ChildClass* VxlCloseFriendFire = new ChildClass;
	ChildClass* VxlOpenLuaMenu = new ChildClass;
	ChildClass* MpJoinLocal = new ChildClass;
	ChildClass* SpeedHackDisconnetAuto = new ChildClass;
	//Color
	ColorClass* VxlMapColor = new ColorClass;
	ColorClass* VxlFogColor = new ColorClass;
	//��class��ʼ��
	Node.MainInit(200, DefaultY, _c(u8"�Ӿ�Ч��\\��������"), nullptr, &Playerbrring, MainChild, false);
	//��Ҫ��ʼ��
	Two->Init(200, NULL, _c(u8"������ɱ"), nullptr, &Playerbrring, SecChild, false);
	//���칦�ܳ�ʼ��
	Voxel->Init(200, NULL, _c(u8"�����߹���"), nullptr, &Playerbrring, VoxelChild, false);
	Vip->Init(200, NULL, _c(u8"����Vip����"), nullptr, nullptr, FuckVoxelMap, false);
	//���س�ʼ��
	Mp->Init(200, NULL, _c(u8"���ع���"), nullptr, nullptr, MpJoinLocal, false);
	MeMp->Init(200, NULL, _c(u8"����(����)\\������"), nullptr, nullptr, MeMpChild, false);
	//ʹ��˵����Զ�������
	UseDes->Init(200, NULL, _c(u8"��������˵��"), &UseCallBackFun, &DefCvar, nullptr, false);
	Fuck->Init(200, NULL, _c(u8"С���̼�ͷ�������˵�"), nullptr, nullptr, nullptr, false);
	//�Ӿ�Ч����Ҫ��class��ʼ��
	MainChild->MainInit(360, DefaultY, _c(u8"��͸��"), nullptr, &PlayerEsp);
	Child->Init(360, NULL, _c(u8"�������"), nullptr, &Playerbrring, MainChild);
	MapChild->Init(360, NULL, _c(u8"��ͼ����"), &MapMaxLing, &MapBring, MainChild);
	NoWhite->Init(360, NULL, _c(u8"��������"), &NOWhite, &CNoWhite, MainChild);
	NoSmock->Init(360, NULL, _c(u8"��������"), &FNoSmock, &NoSmoke, MainChild);
	DrawMouseHeal->Init(360, NULL, _c(u8"�����Ѫ"), nullptr, &DrawHeal, MainChild);
	InfBoom->Init(360, NULL, _c(u8"Ӣ�������ĸ�"), &BoomBoomBoom, &BoomValue, MainChild);
	AutoMcj->Init(360, NULL, _c(u8"MCJ"), nullptr, &(����.mcj), MainChild);
	AutoMcj->SetBestChar2( _c(u8"��"), _c(u8"Alt��MCJ"), _c(u8"Shift��MCJ"));
	AutoSpeed->Init(360, NULL, _c(u8"�Զ�ͬ��"), &AutoStrafe, &(����.�Զ�ͬ��), MainChild);
	AutoSpeed->SetBestChar2( _c(u8"��"), _c(u8"��ʽһ"), _c(u8"��ʽ��"), _c(u8"��ʽ��"));
	VoxelBuyBug->Init(360, NULL, _c(u8"ǿ�ƹ���"), &VoxelBuy, nullptr, MainChild);
	VoxelBuyBugByB->Init(360, NULL, _c( u8"B��ǿ�ƹ���"), nullptr, &VoxelBuyBugB, MainChild);
	GMaxBrring->Init(360, NULL, _c(u8"��������Դ"), nullptr, &MaxBrring, MainChild);
	FastReset->Init(360, NULL, _c(u8"��������"), &FastTry, nullptr, MainChild);//fs_lazy_precache 2;
	DelMenu->Init(360, NULL, _c(u8"���β˵�"), &T_DelMenu, &C_DelMenu, MainChild);
	GetAmmo->Init(360, NULL, _c(u8"��ȡ�ӵ�Ȩ��"), &T_GetAmmo, &C_GetAmmo, MainChild);
	MainChild->Add(360, NULL, _c(u8"ȫ������"), nullptr, &Like��˿);
	//���ٴ�Ҫ�����ʼ��
	SecChild->MainInit(360, DefaultY, _c(u8"���ٰ���"), nullptr, &Vk);
	SecChild->SetBestChar2( _c(u8"E��"), _c(u8"shift��"), _c(u8"V��"), _c(u8"R��"));
	SpeedHack->Init(360, NULL, _c(u8"��ɱ����"), nullptr, &BossSpeed, SecChild);
	AtuoFireH->Init(360, NULL, _c(u8"�Զ���ǹ"), nullptr, &autoFire, SecChild);
	AtuoFireH->SetBestChar2( _c(u8"��"), _c(u8"���"), _c(u8"�Ҽ�"), _c(u8"���Ҽ�"));
	GameIf->Init(360, NULL, _c(u8"������ǿ"), nullptr, &BugScer, SecChild);
	HighUploadSpeed->Init(360, NULL, _c(u8"������������ģʽ"), nullptr, &HighUpload, SecChild);
	HighUploadSpeed->SetBestChar2( _c(u8"��"), _c(u8"΢΢"), _c(u8"��ͨ"), _c(u8"����"));
	SpeedHackDisconnetAuto->Init(360, NULL, _c(u8"�������Զ�����"), nullptr, &SpeedHackAutoRoom, SecChild);
	SecChild->Add(360, NULL, _c(u8"�رռ���ʱ�Ż�"), nullptr, &SpeedNotDraw);
	//�����������ʼ��
	VoxelChild->MainInit(360, DefaultY, _c(u8"�ƽ��������"), &ComputerPass, nullptr);
	HowFuckBlock->Init(360, NULL, _c(u8"�����޸ķ�ʽ"), nullptr, &HowBlock, VoxelChild);
	HowFuckBlock->SetBestChar2( _c(u8"��E˲��\\ʹ��˲��"), _c(u8"��ǰ����"), _c(u8"����һ�񷽿�"));
	VoxelSky->Init(360, NULL, _c(u8"ȫ������"), &VoxelSkyFun, &VoxelSkyValuel, VoxelChild);
	VoxelSky->SetBestChar2( _c(u8"��"), _c(u8"����ǰϦ"), _c(u8"���Ƶ����"), _c(u8"ׯ�ϵ����"), _c(u8"��������"));
	VoxelGlodTry->Init(360, NULL, _c(u8"�޸ĵ�ǰ��Ϸ�Ҽ��1���"), &SetGlodTry, nullptr, VoxelChild);
	VoxelWeaponBox->Init(360, NULL, _c(u8"�޸�����������AK"), &SetAk47L, nullptr, VoxelChild);
	VoxelSkyBright->Init(360, NULL, _c(u8"��ͼ����"), &VoxelBrigth, &VoxelBringht, VoxelChild);
	VoxelSkyBright->SetBestChar2( _c(u8"��"), _c(u8"����"), _c(u8"�"));
	VoxelNpc->Init(360, NULL, _c(u8"Npc�޸�ͨ��"), &VoxelNpcA, nullptr, VoxelChild);
	VoxelC4->Init(360, NULL, _c(u8"�޸�C4����Ϊ1"), &VoxelC41, nullptr, VoxelChild);
	ResetVoxel->Init(360, NULL, _c(u8"��ʼ��ȫͼ"), &VoxelReset, nullptr, VoxelChild);//1.ĩβҳ
	VoxelZombieFuckMap->Init(360, NULL, _c(u8"��ʬ��ͼ"), &SetZombieVoxelMap, &ZombieFuckMap, VoxelChild);
	VoxelZombieFuckMap->SetBestChar2( _c(u8"��"), _c(u8"�Զ�ִ��"), _c(u8"��Rִ��"));
	IsZombieRedX->Init(360, NULL, _c(u8"��ֹ��ʬ͸��"), &VoxelZombieRedX, &ZombieRedX, VoxelChild);
	VoxelInitBack->Init(360, NULL, _c(u8"��ֹ��ԭ�������"), &VoxelInitBackSet, &InitBack, VoxelChild);
	Rool->Init(360, NULL, _c(u8"������۷���"), &RollSell, nullptr, VoxelChild);
	BuyRool->Init(360, NULL, _c(u8"������򷽿�"), &RollBuy, nullptr, VoxelChild);
	Gold9999->Init(360, NULL, _c(u8"��ҷ����9999"), &SetGoldBlock, nullptr, VoxelChild);
	WarehouseBlock->Init(360, NULL, _c(u8"���˴���100%%����"), &SetWarehouse, nullptr, VoxelChild);
	VoxelFireDam->Init(360, NULL, _c(u8"׽�Բ�����ͷ�"), &SetFireDam, &FireDam, VoxelChild);//2.ĩβҳ
	VoxelFireDam->SetBestChar2(_c(u8"�ر�"), _c(u8"δ�б���"), _c(u8"���˺�"));
	VoxelComputerPass->Init(360, NULL, _c(u8"�޸ĵ��� ����:bingbu"), &FuckComputer, nullptr, VoxelChild);
	LoadVxlSave->Init(360, NULL, _c(u8"�浵ͼ���Ʋֿ�"), &LoadMapSave, nullptr, VoxelChild);
	VxlSave->Init(360, NULL, _c(u8"�浵ͼǿ�ƴ浵"), &SaveMap, nullptr, VoxelChild);
	VxlGetBlockWeapon->Init(360, NULL, _c(u8"ˢ�����߷���ǹ"), &GetBlockWeapon, nullptr, VoxelChild);
	VxlCanYouSeeMe->Init(360, NULL, _c(u8"�Ӿ�"), &CanYouSeeMe_, &VoxelSee, VoxelChild);
	VxlCanYouSeeMe->SetBestChar2( _c(u8"��"), _c(u8"��С"), _c(u8"���"));
	VxlResetT->Init(360, NULL, _c(u8"�Ƿ�ԭװ��"), &NoResetTrigger, &VxlResetTrigger, VoxelChild); 
	//vip
	FuckVoxelMap->MainInit(360, NULL, _c(u8"��ͼģʽ"), &SetVoxelMap, &VoxelFuckMap);
	FuckVoxelMap->SetBestChar2( _c(u8"��"), _c(u8"�Զ�ִ��"), _c(u8"��Tִ��"));
	VxlFuckRoom->Init(360, NULL, _c(u8"�����߿���"), nullptr, &VxlFuckRoomPlayer, FuckVoxelMap);
	VxlFuckRoom->SetBestChar2( _c(u8"��"), _c(u8"��P����"));
	MapColor = { 255,0,255 };
	VxlMapColor->Init(360, NULL, _c(u8"������ɫ"), nullptr, nullptr, FuckVoxelMap, &MapColor);
	VoxelFriendDam->Init(360, NULL, _c(u8"�Ѿ��˺�"), &FriendDam, &VoxelFirendKill, FuckVoxelMap);
	DeadSuperLongRpn->Init(360, NULL, _c(u8"������������ʱ��"), &DeadRpnTime, &DeadLongRpn, FuckVoxelMap);
	Fog->Init(360, NULL, _c(u8"���ص�ͼ����"), &SetFog, &FogValue, FuckVoxelMap);
	FogStatc->Init(360, NULL, _c(u8"��������"), &SetFogStatc, &FogStatcValue, FuckVoxelMap);
	FogStatc->SetBestChar2( _c(u8"������"), _c(u8"��Ũ"), _c(u8"�"));
	FogColor = { 255,255,0 };
	VxlFogColor->Init(360, NULL, _c(u8"������ɫ"), nullptr, nullptr, FuckVoxelMap, &FogColor);
	VxlAutoBright->Init(360, NULL, _c(u8"һ���ص�"), &AutoSetBright, nullptr, FuckVoxelMap);
	VxlRGBFog->Init(360, NULL, _c(u8"RGBģʽ"), &RGBFog, &VxlRGBFOG, FuckVoxelMap);
	VxlSetMapLight->Init(360, NULL, _c(u8"�����ص�"), &SetMapLight, &VxlMapLight, FuckVoxelMap);
	VxlSetMapLight->SetBestChar2( _c(u8"��"), _c(u8"��"), _c(u8"��"));
	VxlNotRpn->Init(360, NULL, _c(u8"��ֹ����"), &DontWantToRpn, &NotRpn_, FuckVoxelMap);
	VxlHigeFuckBlock->Init(360, NULL, _c(u8"��Ƶ��ͼģʽ"), &__VxlHigeBlock, &VxlHigeBlock, FuckVoxelMap);
	VxlHigeFuckFriend->Init(360, NULL, _c(u8"��Ƶ����"), &__VxlHigeFriend, &VxlHigeFriend, FuckVoxelMap);
	VxlCloseFriendFire->Init(360, NULL, _c(u8"�����ر�����"), nullptr, &VxlCloseFriend, FuckVoxelMap);
	VxlKillPushBlock->Init(360, NULL, _c(u8"���������ƶ�����"), &KillAllPushBlock, nullptr, FuckVoxelMap);
	VxlKillDamBlock->Init(360, NULL, _c(u8"����������ɢ�˺�����"), &KillAllDamBlock, nullptr, FuckVoxelMap);
	VxlKillWeaponBlock->Init(360, NULL, _c(u8"����������������"), &KillAllWeaponBlock, nullptr, FuckVoxelMap);
	VxlOpenLuaMenu->Init(360, NULL, _c(u8"����͵Lua�˵�"), &VxlOpenLuaMenu_, nullptr, FuckVoxelMap);
	if (!IsVip)FuckVoxelMap->LockAllFunc();
		
	//���ع���
	MpJoinLocal->MainInit(360, DefaultY, _c(u8"���뱾��"), &JoinClass, nullptr);
	MpJoinLocal->SetCantLock();
	MpChild->Init(360, NULL, _c(u8"ȫ����Ѫ"), nullptr, &MpHeal, MpJoinLocal);
	MpMaxSpeed->Init(360, NULL, _c(u8"ȫ������399"), nullptr, &MpSpeed, MpJoinLocal);
	MpFuckAllWeapon->Init(360, NULL, _c(u8"��ȥȫ������"), &RemveAllWeapon, nullptr, MpJoinLocal);
	MpFuckAll->Init(360, NULL, _c(u8"ȫ������"), &KillAll, nullptr, MpJoinLocal);
	MpFireSpeed->Init(360, NULL, _c(u8"�������"), nullptr, &MpFire, MpJoinLocal);
	MpRightFireSpeed->Init(360, NULL, _c(u8"�Ҽ�����"), nullptr, &MpRightFire, MpJoinLocal);
	MpFuckFlyken->Init(360, NULL, _c(u8"���ɱ�ͼBoss"), &CreateFlyHen, nullptr, MpJoinLocal);
	Drawtrigger->Init(360, NULL, _c(u8"���ƴ�������"), &Trigger, &trigger, MpJoinLocal);
	Drawtrigger->SetBestChar2( _c(u8"��"), _c(u8"��ʽһ"), _c(u8"��ʽ��"));
	IsDrawAir->Init(360, NULL, _c(u8"���˿�������"), nullptr, &air, MpJoinLocal);
	MpDrawAllEdit->Init(360, NULL, _c(u8"�Ƿ��������ʵ��"), nullptr, &MpDrawAll, MpJoinLocal);//ĩβҳ
	MpFuckAllMan->Init(360, NULL, _c(u8"��������һȭ"), &GiveYouFaceABox, nullptr, MpJoinLocal);
	MpFuckInx->Init(360, NULL, _c(u8"һȭ�˺�����"), nullptr, &MpFuckInxCv, MpJoinLocal);
	MpFuckInx->SetBestChar2( _c(u8"ȭͷ"), _c(u8"����"), _c(u8"ˤ��"), _c(u8"����"), _c(u8"��ѹ"), _c(u8"����"), _c(u8"��"), _c(u8"����"), _c(u8"��ը"), _c(u8"����"));
	MpAllManFly->Init(360, NULL, _c(u8"ȫ���ո����"), nullptr, &MpFlySky, MpJoinLocal);
	MpFuckAllfly->Init(360, NULL, _c(u8"��������"), &Mp�������ӷ�, nullptr, MpJoinLocal);
	MpInfAmmo->Init(360, NULL, _c(u8"�����ӵ�"), nullptr, &MpAllInfAmmo, MpJoinLocal);
	MpInfAmmo->SetBestChar2( _c(u8"��"), _c(u8"��ʽһ"), _c(u8"��ʽ��"), _c(u8"��ʽ��"));
	MpFuckModle->Init(360, NULL, _c(u8"ȫ������ģ��"), &MpSetModle , &MpMyModle, MpJoinLocal);
	MpFuckModle->SetBestChar2( _c(u8"Ĭ��"), _c(u8"С��"), _c(u8"��ħ"), _c(u8"����"), _c(u8"���˻�"), _c(u8"Ӣ��"), _c(u8"ѩ��"), _c(u8"����"));
	MpLeaveMe->Init(360, NULL, _c(u8"��������"), nullptr, &MpLeave, MpJoinLocal);
	MpBuyG->Init(360, NULL, _c(u8"��������"), nullptr, &MpBuyMyG, MpJoinLocal);
	MpSet->Init(360, NULL, _c(u8"��괦����"), &CreateFlyHen, nullptr, MpJoinLocal);
	MpTheSet->Init(360, NULL, _c(u8"��������"), nullptr, &MpSetsv, MpJoinLocal);
	MpTheSet->SetBestChar2( _c(u8"��֭С��"), _c(u8"��ͼСBOOS"), _c(u8"��ͨС��"), _c(u8"ĸ��"));
	MpFuckAllRpn->Init(360, NULL, _c(u8"ȫ������"), &MpRpn, nullptr, MpJoinLocal);
	MpAllNoViewAngle->Init(360, NULL, _c(u8"�޺�����"), nullptr, &MpAngle, MpJoinLocal);
	MpAllLockWeapon->Init(360, NULL, _c(u8"ǿ����ȫ������"), nullptr, &MpLockWeapon, MpJoinLocal);
	MpGGG->Init(360, NULL, _c(u8"��������"), nullptr, &MpGrad, MpJoinLocal);
	//MpFuckYouSvdex->Init(360, 100, u8"���ҵ���!", &����һ��������, nullptr, MpChild);



	//���ع���(����)
	MeMpChild->MainInit(360, DefaultY, _c(u8"��Ѫ"), nullptr, &MeMpHeal);
	MeMpFireSpeed->Init(360, NULL, _c(u8"�������"), nullptr, &MeMpFire, MeMpChild);
	MeMpRightFireSpeed->Init(360, NULL, _c(u8"�Ҽ�����"), nullptr, &MeMpRightFire, MeMpChild);
	MeMpOhFuckYou->Init(360, NULL, _c(u8"��괦����"), nullptr, &MeMpMouseTp, MeMpChild);
	MeMpSpeed->Init(360, NULL, _c(u8"399����"), nullptr, &MeMpSpeedHack, MeMpChild);
	MeMpNoViewAngle->Init(360, NULL, _c(u8"�޺�����"), nullptr, &MeMpNoAngle, MeMpChild);
	MeMpMonsterTp->Init(360, NULL, _c(u8"�ֱ�����"), nullptr, &MeMpMouseMonsterTp, MeMpChild);
	MeMpKillAllMonster->Init(360, NULL, _c(u8"�ֱ�С������"), &KillAllMonster, nullptr, MeMpChild);
	MeMpFireFuck->Init(360, NULL, _c(u8"����������"), &FireDamPlayer, nullptr, MeMpChild);
}