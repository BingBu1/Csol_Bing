#include "main.h"
#include "Timer.h"
void Timer::Init(float nElapse) {
	if (!this->IsInit) {
		this->nElapse = nElapse;
		this->GameTimer = g_pEngine->GetClientTime();
		this->NeedTimer = GameTimer;
		IsInit = true;
	}
}
void Timer::Updata() {
	if (!this->IsNeedUpdata) {
		this->GameTimer = g_pEngine->GetClientTime();
		this->NeedTimer = (NeedTimer > GameTimer) ? GameTimer : NeedTimer;
	}else {
		this->GameTimer = g_pEngine->GetClientTime();
		this->NeedTimer = GameTimer;
		IsNeedUpdata = false;
	}
	
}
bool Timer::GetIsCan() {
	if (this->GameTimer > (this->NeedTimer + this->nElapse)) {
		this->IsNeedUpdata = true;
		return true;
	}
	return false;
}
void Timer::SetElapse(float nElapse) {
	this->nElapse = nElapse;
}