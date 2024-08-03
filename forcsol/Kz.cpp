#include "main.h"
byte 方向 = 1;
byte strafe_dir = 0;
Vector vForward, vRight;
void AutoSpeed(usercmd_s* cmd , playermovei_t mymove , int 记次) {
	static bool 是否第一次;
	double 除 = 25.0;
	if (!(mymove.flags & FL_ONGROUND) && (mymove.waterleave) < 2 && (mymove.movetype != MOVETYPE_FLY) && !功能.摇头.value)
	{
		if (cmd->buttons & IN_FORWARD)
		{
			除 = 25.0;
			方向 = 1;
		}
		if (cmd->buttons & IN_BACK)
		{
			除 = -25.0;
			方向 = 2;
		}
		if (cmd->buttons & IN_MOVERIGHT)
		{
			除 = 25.0;
			方向 = 3;
		}
		if (cmd->buttons & IN_MOVELEFT)
		{
			除 = -25.0;
			方向 = 4;
		}
		switch (方向)
		{
		case 1:
			if (mymove.xyspeed > 0)
			{
				cmd->forwardmove = 除 / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->forwardmove = 25.001f;
			}
			if (是否第一次)
			{
				cmd->sidemove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->sidemove -= 350.0f;
				是否第一次 = true;
			}
			break;
		case 2:
			if (mymove.xyspeed > 0)
			{
				cmd->forwardmove = -(除 / (mymove.xyspeed / mymove.clientmaxspeed));
			}
			else
			{
				cmd->forwardmove = -25.001f;
			}
			if (是否第一次)
			{
				cmd->sidemove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->sidemove -= 350.0f;
				是否第一次 = true;
			}
			break;
		case 3:
			if (mymove.xyspeed > 0)
			{
				cmd->sidemove = 除 / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->sidemove = 25.001f;
			}
			if (是否第一次)
			{
				cmd->forwardmove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->forwardmove -= 350.0f;
				是否第一次 = true;
			}
			break;
		default:
			if (mymove.xyspeed > 0)
			{
				cmd->sidemove = -(除 / (mymove.xyspeed / mymove.clientmaxspeed));
			}
			else
			{
				cmd->sidemove = -25.001f;
			}
			if (是否第一次)
			{
				cmd->forwardmove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->forwardmove -= 350.0f;
				是否第一次 = true;
			}
			break;
		}
	}
	else if (!(mymove.flags & FL_ONGROUND) && (mymove.waterleave) < 2 && (mymove.movetype != MOVETYPE_FLY) && 功能.摇头.value)//对摇头的同步
	{
		switch (记次)
		{
		case 1:
			if (mymove.xyspeed > 0)
			{
				cmd->sidemove = -(除) / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->sidemove = -25.001f;
			}
			if (是否第一次)
			{
				cmd->forwardmove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->forwardmove -= 350.0f;
				是否第一次 = true;
			}
			break;
		case 2:
			if (mymove.xyspeed > 0)
			{
				cmd->forwardmove = -(除) / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->forwardmove = -25.001f;
			}
			if (是否第一次)
			{
				cmd->sidemove += -350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->sidemove -= -350.0f;
				是否第一次 = true;
			}
			break;
		case 3:
			if (mymove.xyspeed > 0)
			{
				cmd->sidemove = 除 / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->sidemove = 25.001f;
			}
			if (是否第一次)
			{
				cmd->forwardmove += -350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->forwardmove -= -350.0f;
				是否第一次 = true;
			}
			break;
		default:
			if (mymove.xyspeed > 0)
			{
				cmd->forwardmove = 除 / (mymove.xyspeed / mymove.clientmaxspeed);
			}
			else
			{
				cmd->forwardmove = 25.001f;
			}
			if (是否第一次)
			{
				cmd->sidemove += 350.0f;
				是否第一次 = false;
			}
			else
			{
				cmd->sidemove -= 350.0f;
				是否第一次 = true;
			}
			break;
		}
	}
}
float YawForVec(float* fwd)
{
	if (fwd[1] == 0 && fwd[0] == 0)
	{
		return 0;
	}
	else
	{
		float yaw = (atan2(fwd[1], fwd[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;
		return yaw;
	}
}
void SetDir(usercmd_s* cmd) {
	if (cmd->buttons & IN_MOVERIGHT)
		strafe_dir = 2;
	else if (cmd->buttons & IN_BACK)
		strafe_dir = 3;
	else if (cmd->buttons & IN_MOVELEFT)
		strafe_dir = 4;
	else
		strafe_dir = 1;
}
void StrafeHack(float frametime, struct usercmd_s* cmd, float crazy , playermovei_t ppmove)
{
	if (!(ppmove.flags & FL_ONGROUND) && ppmove.movetype != 5 && ppmove.waterleave < 2)
	{
		float dir = 0;

		int dir_value = strafe_dir;

		if (dir_value == 1)dir = 0;
		else if (dir_value == 2)	dir = 90;
		else if (dir_value == 3)	dir = 180;
		else if (dir_value == 4)	dir = -90;

		if (ppmove.xyspeed < 15)
		{
			cmd->forwardmove = 400;
			cmd->sidemove = 0;
		}

		float va_real[3] = { 0,0,0 };
		g_Engine.GetViewAngles(va_real); va_real[1] += dir;
		float vspeed[3] = { ppmove.MeMove.velocity.x / ppmove.MeMove.velocity.Length(),ppmove.MeMove.velocity.y / ppmove.MeMove.velocity.Length(),0.0f };
		float va_speed = YawForVec(vspeed);
		float adif = va_speed - va_real[1];
		while (adif < -180)adif += 360;
		while (adif > 180)adif -= 360;
		cmd->sidemove = (437.8928) * (adif > 0 ? 1 : -1);
		cmd->forwardmove = 0;
		bool onlysidemove = (abs(adif) >= atan(30.f / ppmove.MeMove.velocity.Length2D()) / M_PI * 180);
		int aaddtova = 0;

		cmd->viewangles[1] -= (-(adif));

		float fs = 0;
		if (!onlysidemove)
		{
			static float lv = 0;
			Vector fw = vForward; fw[2] = 0; fw = fw.Normalize();
			float vel = POW(fw[0] * ppmove.MeMove.velocity.x) + POW(fw[1] * ppmove.MeMove.velocity.y);

			fs = lv;
			lv = sqrt(69.f * 100000 / vel);
			static float lastang = 0;
			float ca = abs(adif);
			lastang = ca;
		}

		float ang = atan(fs / cmd->sidemove) / M_PI * 180;
		cmd->viewangles.y += ang;

		if (crazy != 0)
		{
			static int _crazy = 1;
			_crazy *= (-1);
			cmd->viewangles.x = 89 * _crazy;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;
		if (strafe_dir == 1)
		{
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
		}
		else if (strafe_dir == 2)
		{
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
		}
		else if (strafe_dir == 3)
		{
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
		}
		else if (strafe_dir == 4)
		{
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
		}
	}

}

void AutoFastRun(usercmd_s* cmd, bool& _FastRun) {
	if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVELEFT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVERIGHT))
	{
		if (_FastRun)
		{
			_FastRun = false;
			cmd->sidemove -= 89.6f;
			cmd->forwardmove -= 89.6f;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 89.6f;
			cmd->forwardmove += 89.6f;
		}
	}
	else if ((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVERIGHT) || (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVELEFT))
	{
		if (_FastRun)
		{
			_FastRun = false;
			cmd->sidemove -= 89.6f;
			cmd->forwardmove += 89.6f;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 89.6f;
			cmd->forwardmove -= 89.6f;
		}
	}
	else if (cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK)
	{
		if (_FastRun)
		{
			_FastRun = false;
			cmd->sidemove -= 126.6f;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 126.6f;
		}
	}
	else if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT)
	{
		if (_FastRun)
		{
			_FastRun = false;
			cmd->forwardmove -= 126.6f;
		}
		else
		{
			_FastRun = true;
			cmd->forwardmove += 126.6f;
		}
	}
}
void StrafeHack2(float frametime, struct usercmd_s* cmd, playermovei_t mymove)
{
	if (!(mymove.MeMove.flags & FL_ONGROUND) && (mymove.MeMove.movetype != 5) && mymove.waterleave < 2)
	{
		float dir = 0.0f;

		int dir_value = strafe_dir;

		if (dir_value == 1)dir = 0 * static_cast<float>(M_PI) / 180.0f;
		else if (dir_value == 2)	dir = 90 * static_cast<float>(M_PI) / 180.0f;
		else if (dir_value == 3)	dir = 180 * static_cast<float>(M_PI) / 180.0f;
		else if (dir_value == 4)	dir = -90 * static_cast<float>(M_PI) / 180.0f;

		if (mymove.xyspeed < 15.0f)
		{
			if (cmd->buttons & IN_FORWARD)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = 900;
			}
			else if (cmd->buttons & IN_BACK)
			{
				if (cmd->buttons & IN_MOVELEFT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons & IN_MOVERIGHT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = -900;
			}
			else if (cmd->buttons & IN_MOVELEFT)
				cmd->sidemove = -900;
			else if (cmd->buttons & IN_MOVERIGHT)
				cmd->sidemove = 900;
			else
				cmd->forwardmove = 900;
		}
		else
		{
			float va_speed = atan2(mymove.MeMove.velocity.y, mymove.MeMove.velocity.x);

			float va[3] = {};
			g_Engine.GetViewAngles(va);

			float adif = va_speed - va[1] * static_cast<float>(M_PI) / 180.0f - dir;

			adif = sin(adif);
			adif = atan2(adif, sqrt(1 - adif * adif));

			cmd->sidemove = (437.8928) * (adif > 0 ? 1 : -1);
			cmd->forwardmove = 0;

			float angle;
			float osin, ocos, nsin, ncos;

			angle = cmd->viewangles.y * static_cast<float>(M_PI) / 180.0f;
			osin = sin(angle);
			ocos = cos(angle);

			angle = 2.0f * cmd->viewangles.y * static_cast<float>(M_PI) / 180.0f - va_speed + dir;
			nsin = sin(angle);
			ncos = cos(angle);

			cmd->forwardmove = cmd->sidemove * (osin * ncos - ocos * nsin);
			cmd->sidemove *= osin * nsin + ocos * ncos;

			float fs = 0;
			if (atan2(30.f / mymove.xyspeed, 1.0f) >= abs(adif))
			{
				Vector vBodyDirection;

				if (dir_value & 1)
					vBodyDirection = vForward;
				else
					vBodyDirection = vRight;

				vBodyDirection[2] = 0;
				vBodyDirection = vBodyDirection.Normalize();

				float vel = POW(vBodyDirection[0] * mymove.MeMove.velocity[0]) + POW(vBodyDirection[1] * mymove.MeMove.velocity[1]);

				fs = sqrt(69.0 * 100000 / vel);
			}

			cmd->forwardmove += fs;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;

		switch ((int)strafe_dir)
		{
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}
	}
}