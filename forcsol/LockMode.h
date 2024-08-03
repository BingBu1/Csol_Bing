#pragma once

class LockModeClass{
public:
	void ReadModeBase();
	void ResetModeBase();
	void StartLock();
private:
	char Base[2000];
	char NowBase[2000];
	bool IsRead;
};

inline LockModeClass LockModeMager;
inline char* Mode;