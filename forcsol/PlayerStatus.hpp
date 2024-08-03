#pragma once

#pragma pack(1)
class PlayerStatus{
public:
	__forceinline PlayerStatus* GetByIndex(int Index);
	inline short GetPlayerTeamByIndex(int Index) { return GetByIndex(Index)->team; }
	inline int GetPlayerIsDeadByIndex(int Index) { return GetByIndex(Index)->IsDead; }
	inline int GetHealByIndex(int Index) { return GetByIndex(Index)->NowHeal; }
	inline std::vector<float>& GetOriginByIndex(int Index) { auto temp = GetByIndex(Index); return temp->GetOrigin(); }
	inline void SetHeadHealByIndex(int Index, bool SetBool) { GetByIndex(Index)->SetHeadHeal(SetBool); }
	
	inline short GetPlayerTeam() { return this->team; }
	inline int GetPlayerIsDead() { return this->IsDead; }
	inline int GetHeal() { return this->NowHeal; }
	inline std::vector<float>&GetOrigin() { return std::vector<float>({ origin[0] ,origin[1] ,origin[2] }); }
	inline void SetHeadHeal(bool SetBool) { this->CanSeeHeadHeal = SetBool; this->HeadHealRead = SetBool; }
private:
	short team;
	char teamName[0x10];
	int IsDead;
	void* Unkown;
	int LookingHeal;
	char Unkown1[0x20];
	int PlayerInfoSetUnKown;
	bool CanSeeHeadHeal;
	bool Unkown2;
	short HeadHealRead;
	int Unkown3;
	int NowHeal;
	int Unkown4[2];
	float origin[3];
	char Unkown5[0x1CE];
};
#pragma pack()

__forceinline PlayerStatus* PlayerStatus::GetByIndex(int Index) {
	return this + Index;
}

inline PlayerStatus* MainStatus;