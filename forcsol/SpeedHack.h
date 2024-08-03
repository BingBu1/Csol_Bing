#pragma once
class SpeedHack_{
public:
	void AutoResetRoom();
	void StartSpeedHack();
	void StartPassDropClient();
	void EndSpeedHack();
	void AutoFire(usercmd_s* cmd);
	bool GetIsSpeedHacking() { return this->IsSpeedStart; }
private:
	bool fire;
	bool SecHack;
	bool IsSpeedStart;
	bool IsNeedResetRoom;
	int FirstTime;
};
inline SpeedHack_ SpeedHack;