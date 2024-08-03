#include "GameKz.h"
void GameKz::Bhop(usercmd_s* cmd){
	auto CurInJump = cmd->buttons & IN_JUMP;
	static auto LastFramIsJmp = 0;
	if (cmd->buttons & IN_JUMP && !(mymove.flags & FL_ONGROUND) && (mymove.waterleave < 2) && (mymove.movetype != MOVETYPE_FLY)) {
		cmd->buttons &= ~IN_JUMP;
		LastFramIsJmp = CurInJump;
	}
}
