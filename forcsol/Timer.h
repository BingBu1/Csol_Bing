#pragma once
class Timer
{
public:
	void Init(float nElapse);
	void SetElapse(float nElapse);
	void Updata();
	bool GetIsCan();
private:
	bool IsInit;
	bool IsNeedUpdata;
	float GameTimer;
	float NeedTimer;
	float nElapse;
};
