#include "main.h"
/*
	遍历链表绘制菜单
*/
void ChildClass::Draw()noexcept {
	static Darwingclass* _Draw = new Darwingclass;
	ChildClass* Temp = this;
	int TheNum = Temp->Num;
	int ThePageNum = Temp->NowPage * MaxPageNum; //算出页上限
	if (Temp->NowPage < Temp->PageNum) {
		ThePageNum ? TheNum = MaxPageNum : TheNum > MaxPageNum ? TheNum = MaxPageNum : NULL;
	}else if (ThePageNum && Temp->NowPage == Temp->PageNum) {
		TheNum = Temp->Num % MaxPageNum ? Temp->Num % MaxPageNum : MaxPageNum;
	}
	if (this->PageNum) {
		ChildClass* End = (*this->end)[this->NowPage];
		auto  PageString = fmt::format(XorString(u8"当前页({:d}/{:d})"), this->NowPage, this->PageNum);
		_Draw->绘制方块(End->x, End->y + 30, 150, 22, 0, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(0, 1, 0);
		_Draw->DrawString(End->x, End->y + 32, PageString.c_str(), 1);
	}
	int TheNow = ThePageNum;
	for (auto i = (*this->head)[this->NowPage]; i != (*this->end)[this->NowPage]->Next; i = i->Next) {
		//是否是当前选中的菜单子页
		if (TheNow == Now)i->Panit(true);
		else i->Panit(false);
		TheNow++;
	}
}
/*
	设置特殊开关值
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
	主子项初始化
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
	次子项初始化
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
	添加子项到链表当中
*/
void ChildClass::Add(ChildClass* YourText)noexcept {
	ChildClass* Temp;
	for (Temp = GetMainDraw(); Temp->Next; Temp = Temp->Next);
	Temp->Next = YourText;
	Num += 1;
}
/*
	添加一份匿名子项
*/
void ChildClass::Add(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value)noexcept {
	ChildClass* Temp = new ChildClass, * Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this);
}
/*
	添加一份匿名颜色子项
*/
void ChildClass::AddColor(int x, int y, char* YouDrawText, void* Fun, pcvar_t Value, color24* Color)noexcept {
	ColorClass* Temp = new ColorClass;
	auto Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this, Color);
}
/*
	添加一份匿名Float子项
*/
void ChildClass::AddFloat(int x, int y, char* YouDrawText, void* Fun, float* Value) noexcept{
	FloatClass* Temp = new FloatClass;
	auto Tmp = this;
	Temp->Init(x, y, YouDrawText, Fun, Value, this);
}
/*
	开始绘制单个菜单
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
			d_Text = fmt::format(XorString("{}    {}"), this->Text, value->value ? XorString(u8"开") : XorString(u8"关"));
		}
	}else d_Text = this->Text;
	if (GetNowIsInChild() && NOW) {
		Draw.绘制方块(this->x, this->y, 150, 22, 100, 0, 200, 100);
		g_Engine.pfnDrawSetTextColor(1.f, 0.84f, 0); //255 215 0
		Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
	}
	else {
		g_Engine.pfnDrawSetTextColor(0, 1.f, 0);
		if (!this->IsLock) {
			Draw.绘制方块(this->x, this->y, 150, 22, 0, 0, 200, 100);
			Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
		}else {
			Draw.绘制方块(this->x, this->y, 150, 22, 128, 128, 128, 100);
			Draw.DrawString(this->x + 2, this->y + 2, d_Text.c_str(), 1);
		}	
	}
}
/*
	获取当前选中的菜单Inx
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
	连续清空内存
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
	初始化特殊字符串
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
	获取当前菜单是否属于特殊Value
*/
bool ChildClass::GetIsBestChar() {
	ChildClass* Temp = GetMainDraw(), *i;
	int Now = Temp->Now, c = 0;
	for (i = Temp, c = 0; c < Now && i; c++, i = i->Next);
	return i->IsBestChar;
}
/*
	翻页
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
	锁定当前菜单所有子项-任意一个子项调用都可
*/
void ChildClass::LockAllFunc() {
	ChildClass* Temp = GetMainDraw();
	for (; Temp; Temp = Temp->Next) {
		if (Temp->CanLock)Temp->IsLock = true;
	}
}
/*
	解锁定当前菜单所有子项-任意一个子项调用都可
*/
void ChildClass::UnLockAllFunc() {
	ChildClass* Temp = GetMainDraw();
	for (; Temp; Temp = Temp->Next) {
		if (Temp->CanLock)Temp->IsLock = false;
	}
}
/*
	用名字搜索子项
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
	value菜单功能的开关结构
*/
cvar_t DefCvar, MapBring, Vk, BossSpeed, autoFire, BugScer, HighUpload, CNoWhite, NoSmoke, trigger, air, DrawHeal, VoxelFuckMap, VoxelSkyValuel, VoxelBringht, VoxelFirendKill, HowBlock
, DeadLongRpn, ZombieFuckMap, ZombieRedX, InitBack, FireDam, FogValue, FogStatcValue, BoomValue, VxlFuckRoomPlayer, MaxBrring, VoxelSee, VxlRGBFOG, VxlHigeBlock, C_DelMenu, C_GetAmmo, VxlMapLight
, NotRpn_, VoxelBuyBugB, VxlHigeFriend, VxlResetTrigger, VxlCloseFriend, SpeedHackAutoRoom, SpeedNotDraw, Like嗨丝;

cvar_t MpHeal, MpSpeed, MpFire, MpRightFire, MpDrawAll, MpFuckInxCv, MpFlySky, MpBuyMyG, MpAllInfAmmo, MpMyModle, MpLeave, MpSetsv, MpAngle, MpLockWeapon, MpGrad;

cvar_t MeMpHeal, MeMpFire, MeMpRightFire, MeMpMouseTp, MeMpSpeedHack, MeMpNoAngle, MeMpMouseMonsterTp;

color24 MapColor, FogColor;
/*
	因为需要在其他函数锁定子类所以定义为全局
*/
ChildClass* MpChild = new ChildClass;
ChildClass* MeMpChild = new ChildClass;
/*
	***************************************

	初始化菜单函数所有要绘制的菜单都塞这里

	***************************************
*/
void TextClassInit() {
	//申请内存
	MainMenu* Two = new MainMenu;
	MainMenu* UseDes = new MainMenu;
	MainMenu* Fuck = new MainMenu;
	MainMenu* Voxel = new MainMenu;
	MainMenu* Mp = new MainMenu;
	MainMenu* MeMp = new MainMenu;
	MainMenu* Vip = new MainMenu;
	//主次项
	ChildClass* MainChild = new ChildClass;
	ChildClass* SecChild = new ChildClass;
	ChildClass* VoxelChild = new ChildClass;
	//副次项
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
	//主class初始化
	Node.MainInit(200, DefaultY, _c(u8"视觉效果\\基础功能"), nullptr, &Playerbrring, MainChild, false);
	//次要初始化
	Two->Init(200, NULL, _c(u8"加速秒杀"), nullptr, &Playerbrring, SecChild, false);
	//缔造功能初始化
	Voxel->Init(200, NULL, _c(u8"缔造者功能"), nullptr, &Playerbrring, VoxelChild, false);
	Vip->Init(200, NULL, _c(u8"缔造Vip功能"), nullptr, nullptr, FuckVoxelMap, false);
	//本地初始化
	Mp->Init(200, NULL, _c(u8"本地功能"), nullptr, nullptr, MpJoinLocal, false);
	MeMp->Init(200, NULL, _c(u8"本地(单人)\\开发中"), nullptr, nullptr, MeMpChild, false);
	//使用说明永远处在最后
	UseDes->Init(200, NULL, _c(u8"按键功能说明"), &UseCallBackFun, &DefCvar, nullptr, false);
	Fuck->Init(200, NULL, _c(u8"小键盘箭头操作本菜单"), nullptr, nullptr, nullptr, false);
	//视觉效果次要主class初始化
	MainChild->MainInit(360, DefaultY, _c(u8"纯透视"), nullptr, &PlayerEsp);
	Child->Init(360, NULL, _c(u8"人物加亮"), nullptr, &Playerbrring, MainChild);
	MapChild->Init(360, NULL, _c(u8"地图高亮"), &MapMaxLing, &MapBring, MainChild);
	NoWhite->Init(360, NULL, _c(u8"无视闪光"), &NOWhite, &CNoWhite, MainChild);
	NoSmock->Init(360, NULL, _c(u8"无视烟雾弹"), &FNoSmock, &NoSmoke, MainChild);
	DrawMouseHeal->Init(360, NULL, _c(u8"鼠标显血"), nullptr, &DrawHeal, MainChild);
	InfBoom->Init(360, NULL, _c(u8"英雄无限幽浮"), &BoomBoomBoom, &BoomValue, MainChild);
	AutoMcj->Init(360, NULL, _c(u8"MCJ"), nullptr, &(功能.mcj), MainChild);
	AutoMcj->SetBestChar2( _c(u8"关"), _c(u8"Alt键MCJ"), _c(u8"Shift键MCJ"));
	AutoSpeed->Init(360, NULL, _c(u8"自动同步"), &AutoStrafe, &(功能.自动同步), MainChild);
	AutoSpeed->SetBestChar2( _c(u8"关"), _c(u8"方式一"), _c(u8"方式二"), _c(u8"方式三"));
	VoxelBuyBug->Init(360, NULL, _c(u8"强制购买"), &VoxelBuy, nullptr, MainChild);
	VoxelBuyBugByB->Init(360, NULL, _c( u8"B键强制购买"), nullptr, &VoxelBuyBugB, MainChild);
	GMaxBrring->Init(360, NULL, _c(u8"自身创建光源"), nullptr, &MaxBrring, MainChild);
	FastReset->Init(360, NULL, _c(u8"快速重连"), &FastTry, nullptr, MainChild);//fs_lazy_precache 2;
	DelMenu->Init(360, NULL, _c(u8"屏蔽菜单"), &T_DelMenu, &C_DelMenu, MainChild);
	GetAmmo->Init(360, NULL, _c(u8"获取子弹权限"), &T_GetAmmo, &C_GetAmmo, MainChild);
	MainChild->Add(360, NULL, _c(u8"全房点赞"), nullptr, &Like嗨丝);
	//加速次要子项初始化
	SecChild->MainInit(360, DefaultY, _c(u8"加速按键"), nullptr, &Vk);
	SecChild->SetBestChar2( _c(u8"E键"), _c(u8"shift键"), _c(u8"V键"), _c(u8"R键"));
	SpeedHack->Init(360, NULL, _c(u8"秒杀加速"), nullptr, &BossSpeed, SecChild);
	AtuoFireH->Init(360, NULL, _c(u8"自动开枪"), nullptr, &autoFire, SecChild);
	AtuoFireH->SetBestChar2( _c(u8"关"), _c(u8"左键"), _c(u8"右键"), _c(u8"左右键"));
	GameIf->Init(360, NULL, _c(u8"卡屏增强"), nullptr, &BugScer, SecChild);
	HighUploadSpeed->Init(360, NULL, _c(u8"超高流量加速模式"), nullptr, &HighUpload, SecChild);
	HighUploadSpeed->SetBestChar2( _c(u8"关"), _c(u8"微微"), _c(u8"普通"), _c(u8"拉满"));
	SpeedHackDisconnetAuto->Init(360, NULL, _c(u8"闪大厅自动重连"), nullptr, &SpeedHackAutoRoom, SecChild);
	SecChild->Add(360, NULL, _c(u8"关闭加速时优化"), nullptr, &SpeedNotDraw);
	//缔造者子项初始化
	VoxelChild->MainInit(360, DefaultY, _c(u8"破解电脑密码"), &ComputerPass, nullptr);
	HowFuckBlock->Init(360, NULL, _c(u8"方块修改方式"), nullptr, &HowBlock, VoxelChild);
	HowFuckBlock->SetBestChar2( _c(u8"按E瞬间\\使用瞬间"), _c(u8"当前坐标"), _c(u8"脚下一格方块"));
	VoxelSky->Init(360, NULL, _c(u8"全房换天"), &VoxelSkyFun, &VoxelSkyValuel, VoxelChild);
	VoxelSky->SetBestChar2( _c(u8"无"), _c(u8"暴风前夕"), _c(u8"多云的天空"), _c(u8"庄严的天空"), _c(u8"白天的天空"));
	VoxelGlodTry->Init(360, NULL, _c(u8"修改当前游戏币检查1金币"), &SetGlodTry, nullptr, VoxelChild);
	VoxelWeaponBox->Init(360, NULL, _c(u8"修改武器盒旋风AK"), &SetAk47L, nullptr, VoxelChild);
	VoxelSkyBright->Init(360, NULL, _c(u8"地图亮度"), &VoxelBrigth, &VoxelBringht, VoxelChild);
	VoxelSkyBright->SetBestChar2( _c(u8"无"), _c(u8"最亮"), _c(u8"最暗"));
	VoxelNpc->Init(360, NULL, _c(u8"Npc修改通过"), &VoxelNpcA, nullptr, VoxelChild);
	VoxelC4->Init(360, NULL, _c(u8"修改C4密码为1"), &VoxelC41, nullptr, VoxelChild);
	ResetVoxel->Init(360, NULL, _c(u8"初始化全图"), &VoxelReset, nullptr, VoxelChild);//1.末尾页
	VoxelZombieFuckMap->Init(360, NULL, _c(u8"僵尸拆图"), &SetZombieVoxelMap, &ZombieFuckMap, VoxelChild);
	VoxelZombieFuckMap->SetBestChar2( _c(u8"关"), _c(u8"自动执行"), _c(u8"按R执行"));
	IsZombieRedX->Init(360, NULL, _c(u8"禁止僵尸透视"), &VoxelZombieRedX, &ZombieRedX, VoxelChild);
	VoxelInitBack->Init(360, NULL, _c(u8"禁止还原拆除方块"), &VoxelInitBackSet, &InitBack, VoxelChild);
	Rool->Init(360, NULL, _c(u8"随机出售方块"), &RollSell, nullptr, VoxelChild);
	BuyRool->Init(360, NULL, _c(u8"随机购买方块"), &RollBuy, nullptr, VoxelChild);
	Gold9999->Init(360, NULL, _c(u8"金币方块改9999"), &SetGoldBlock, nullptr, VoxelChild);
	WarehouseBlock->Init(360, NULL, _c(u8"个人储蓄100%%利率"), &SetWarehouse, nullptr, VoxelChild);
	VoxelFireDam->Init(360, NULL, _c(u8"捉迷藏射击惩罚"), &SetFireDam, &FireDam, VoxelChild);//2.末尾页
	VoxelFireDam->SetBestChar2(_c(u8"关闭"), _c(u8"未中必死"), _c(u8"无伤害"));
	VoxelComputerPass->Init(360, NULL, _c(u8"修改电脑 密码:bingbu"), &FuckComputer, nullptr, VoxelChild);
	LoadVxlSave->Init(360, NULL, _c(u8"存档图复制仓库"), &LoadMapSave, nullptr, VoxelChild);
	VxlSave->Init(360, NULL, _c(u8"存档图强制存档"), &SaveMap, nullptr, VoxelChild);
	VxlGetBlockWeapon->Init(360, NULL, _c(u8"刷缔造者方块枪"), &GetBlockWeapon, nullptr, VoxelChild);
	VxlCanYouSeeMe->Init(360, NULL, _c(u8"视距"), &CanYouSeeMe_, &VoxelSee, VoxelChild);
	VxlCanYouSeeMe->SetBestChar2( _c(u8"无"), _c(u8"最小"), _c(u8"最大"));
	VxlResetT->Init(360, NULL, _c(u8"是否还原装置"), &NoResetTrigger, &VxlResetTrigger, VoxelChild); 
	//vip
	FuckVoxelMap->MainInit(360, NULL, _c(u8"拆图模式"), &SetVoxelMap, &VoxelFuckMap);
	FuckVoxelMap->SetBestChar2( _c(u8"关"), _c(u8"自动执行"), _c(u8"按T执行"));
	VxlFuckRoom->Init(360, NULL, _c(u8"缔造者卡房"), nullptr, &VxlFuckRoomPlayer, FuckVoxelMap);
	VxlFuckRoom->SetBestChar2( _c(u8"关"), _c(u8"按P卡房"));
	MapColor = { 255,0,255 };
	VxlMapColor->Init(360, NULL, _c(u8"卡房颜色"), nullptr, nullptr, FuckVoxelMap, &MapColor);
	VoxelFriendDam->Init(360, NULL, _c(u8"友军伤害"), &FriendDam, &VoxelFirendKill, FuckVoxelMap);
	DeadSuperLongRpn->Init(360, NULL, _c(u8"死亡超长复活时间"), &DeadRpnTime, &DeadLongRpn, FuckVoxelMap);
	Fog->Init(360, NULL, _c(u8"开关地图烟雾"), &SetFog, &FogValue, FuckVoxelMap);
	FogStatc->Init(360, NULL, _c(u8"烟雾设置"), &SetFogStatc, &FogStatcValue, FuckVoxelMap);
	FogStatc->SetBestChar2( _c(u8"无设置"), _c(u8"最浓"), _c(u8"最淡"));
	FogColor = { 255,255,0 };
	VxlFogColor->Init(360, NULL, _c(u8"烟雾颜色"), nullptr, nullptr, FuckVoxelMap, &FogColor);
	VxlAutoBright->Init(360, NULL, _c(u8"一键关灯"), &AutoSetBright, nullptr, FuckVoxelMap);
	VxlRGBFog->Init(360, NULL, _c(u8"RGB模式"), &RGBFog, &VxlRGBFOG, FuckVoxelMap);
	VxlSetMapLight->Init(360, NULL, _c(u8"锁定关灯"), &SetMapLight, &VxlMapLight, FuckVoxelMap);
	VxlSetMapLight->SetBestChar2( _c(u8"关"), _c(u8"黑"), _c(u8"白"));
	VxlNotRpn->Init(360, NULL, _c(u8"禁止复活"), &DontWantToRpn, &NotRpn_, FuckVoxelMap);
	VxlHigeFuckBlock->Init(360, NULL, _c(u8"高频拆图模式"), &__VxlHigeBlock, &VxlHigeBlock, FuckVoxelMap);
	VxlHigeFuckFriend->Init(360, NULL, _c(u8"高频友伤"), &__VxlHigeFriend, &VxlHigeFriend, FuckVoxelMap);
	VxlCloseFriendFire->Init(360, NULL, _c(u8"锁定关闭友伤"), nullptr, &VxlCloseFriend, FuckVoxelMap);
	VxlKillPushBlock->Init(360, NULL, _c(u8"报废所有推动方块"), &KillAllPushBlock, nullptr, FuckVoxelMap);
	VxlKillDamBlock->Init(360, NULL, _c(u8"报废所有扩散伤害方块"), &KillAllDamBlock, nullptr, FuckVoxelMap);
	VxlKillWeaponBlock->Init(360, NULL, _c(u8"报废所有武器方块"), &KillAllWeaponBlock, nullptr, FuckVoxelMap);
	VxlOpenLuaMenu->Init(360, NULL, _c(u8"呼出偷Lua菜单"), &VxlOpenLuaMenu_, nullptr, FuckVoxelMap);
	if (!IsVip)FuckVoxelMap->LockAllFunc();
		
	//本地功能
	MpJoinLocal->MainInit(360, DefaultY, _c(u8"进入本地"), &JoinClass, nullptr);
	MpJoinLocal->SetCantLock();
	MpChild->Init(360, NULL, _c(u8"全房锁血"), nullptr, &MpHeal, MpJoinLocal);
	MpMaxSpeed->Init(360, NULL, _c(u8"全房地速399"), nullptr, &MpSpeed, MpJoinLocal);
	MpFuckAllWeapon->Init(360, NULL, _c(u8"除去全房武器"), &RemveAllWeapon, nullptr, MpJoinLocal);
	MpFuckAll->Init(360, NULL, _c(u8"全房西内"), &KillAll, nullptr, MpJoinLocal);
	MpFireSpeed->Init(360, NULL, _c(u8"左键加速"), nullptr, &MpFire, MpJoinLocal);
	MpRightFireSpeed->Init(360, NULL, _c(u8"右键加速"), nullptr, &MpRightFire, MpJoinLocal);
	MpFuckFlyken->Init(360, NULL, _c(u8"生成本图Boss"), &CreateFlyHen, nullptr, MpJoinLocal);
	Drawtrigger->Init(360, NULL, _c(u8"绘制触发方块"), &Trigger, &trigger, MpJoinLocal);
	Drawtrigger->SetBestChar2( _c(u8"关"), _c(u8"方式一"), _c(u8"方式二"));
	IsDrawAir->Init(360, NULL, _c(u8"过滤空气方块"), nullptr, &air, MpJoinLocal);
	MpDrawAllEdit->Init(360, NULL, _c(u8"是否绘制所有实体"), nullptr, &MpDrawAll, MpJoinLocal);//末尾页
	MpFuckAllMan->Init(360, NULL, _c(u8"给所有人一拳"), &GiveYouFaceABox, nullptr, MpJoinLocal);
	MpFuckInx->Init(360, NULL, _c(u8"一拳伤害类型"), nullptr, &MpFuckInxCv, MpJoinLocal);
	MpFuckInx->SetBestChar2( _c(u8"拳头"), _c(u8"火焰"), _c(u8"摔伤"), _c(u8"辐射"), _c(u8"碾压"), _c(u8"淹死"), _c(u8"酸"), _c(u8"冻结"), _c(u8"爆炸"), _c(u8"所有"));
	MpAllManFly->Init(360, NULL, _c(u8"全房空格飞天"), nullptr, &MpFlySky, MpJoinLocal);
	MpFuckAllfly->Init(360, NULL, _c(u8"神罗天征"), &Mp都给老子飞, nullptr, MpJoinLocal);
	MpInfAmmo->Init(360, NULL, _c(u8"无限子弹"), nullptr, &MpAllInfAmmo, MpJoinLocal);
	MpInfAmmo->SetBestChar2( _c(u8"关"), _c(u8"方式一"), _c(u8"方式二"), _c(u8"方式三"));
	MpFuckModle->Init(360, NULL, _c(u8"全房更改模型"), &MpSetModle , &MpMyModle, MpJoinLocal);
	MpFuckModle->SetBestChar2( _c(u8"默认"), _c(u8"小鸡"), _c(u8"炎魔"), _c(u8"足球"), _c(u8"无人机"), _c(u8"英雄"), _c(u8"雪人"), _c(u8"蚊子"));
	MpLeaveMe->Init(360, NULL, _c(u8"房主隐形"), nullptr, &MpLeave, MpJoinLocal);
	MpBuyG->Init(360, NULL, _c(u8"宣传辅助"), nullptr, &MpBuyMyG, MpJoinLocal);
	MpSet->Init(360, NULL, _c(u8"鼠标处生成"), &CreateFlyHen, nullptr, MpJoinLocal);
	MpTheSet->Init(360, NULL, _c(u8"生成类型"), nullptr, &MpSetsv, MpJoinLocal);
	MpTheSet->SetBestChar2( _c(u8"蜜汁小奥"), _c(u8"本图小BOOS"), _c(u8"普通小奥"), _c(u8"母体"));
	MpFuckAllRpn->Init(360, NULL, _c(u8"全房复活"), &MpRpn, nullptr, MpJoinLocal);
	MpAllNoViewAngle->Init(360, NULL, _c(u8"无后坐力"), nullptr, &MpAngle, MpJoinLocal);
	MpAllLockWeapon->Init(360, NULL, _c(u8"强制锁全房武器"), nullptr, &MpLockWeapon, MpJoinLocal);
	MpGGG->Init(360, NULL, _c(u8"喷射手雷"), nullptr, &MpGrad, MpJoinLocal);
	//MpFuckYouSvdex->Init(360, 100, u8"给我掉线!", &送你一个大礼物, nullptr, MpChild);



	//本地功能(单人)
	MeMpChild->MainInit(360, DefaultY, _c(u8"锁血"), nullptr, &MeMpHeal);
	MeMpFireSpeed->Init(360, NULL, _c(u8"左键加速"), nullptr, &MeMpFire, MeMpChild);
	MeMpRightFireSpeed->Init(360, NULL, _c(u8"右键加速"), nullptr, &MeMpRightFire, MeMpChild);
	MeMpOhFuckYou->Init(360, NULL, _c(u8"鼠标处吸人"), nullptr, &MeMpMouseTp, MeMpChild);
	MeMpSpeed->Init(360, NULL, _c(u8"399移速"), nullptr, &MeMpSpeedHack, MeMpChild);
	MeMpNoViewAngle->Init(360, NULL, _c(u8"无后坐力"), nullptr, &MeMpNoAngle, MeMpChild);
	MeMpMonsterTp->Init(360, NULL, _c(u8"灾变吸怪"), nullptr, &MeMpMouseMonsterTp, MeMpChild);
	MeMpKillAllMonster->Init(360, NULL, _c(u8"灾变小怪西内"), &KillAllMonster, nullptr, MeMpChild);
	MeMpFireFuck->Init(360, NULL, _c(u8"灼烧所有人"), &FireDamPlayer, nullptr, MeMpChild);
}