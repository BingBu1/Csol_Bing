#pragma once
#include "hitbox.h"
void UpdataPlayerInfo(cl_entity_s* ent);
void UpdataLoaclPlayerInfo();
void ZeroPlayerInfo();
bool isValidEnt(cl_entity_s* ent);
class LoaclPlayer
{
public:
	int team;
	int index;
	Vector Origin, PunChange;
	cl_entity_s* Ent;
}; extern LoaclPlayer P_Loacl;

class PlayerLoaclInfo
{
public:
	bool IsVisible, Valid;
	int team;
	int index;
	Vector Origin;
	struct cl_entity_s* Ent;
}; extern PlayerLoaclInfo P_LoaclPlayer[33];
int GetSequence(cl_entity_s* Ent);