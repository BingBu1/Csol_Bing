#include <math.h>
#include <Windows.h>
#define Pi 3.1415926535898
constexpr float GetToR() {
	return 180 / Pi;
}
void VectorAngles(const float* forward, float* angles)
{

	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / Pi);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / Pi);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < -180) { angles[1] += 360; }
	while (angles[1] > 180) { angles[1] -= 360; }
}

ULONG CalcCallBase(ULONG CallBase) {
	ULONG Base = *(PULONG)CallBase;
	ULONG NextAsm = CallBase + 4;
	return Base + NextAsm;
}