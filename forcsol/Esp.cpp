#include	"Esp.h"
void DrawViewLine(cl_entity_s* Ent) {
	if (Ent && Ent->player && !GetPlayerDead(Ent->index)) {
		vec3_t Start, End, For, Side, Up;
		VectorCopy(Ent->curstate.origin, Start);
		g_pEngine->pfnAngleVectors(Ent->curstate.angles, For, Side, Up);
		For[2] = -For[2];
		Start[0] += For[0] * 10;
		Start[1] += For[1] * 10;
		Start[2] += For[2] * 10 + 17;
		End = Start + For * 999;
		if (p_client->HUD_GetPlayerTeam(Ent->index) == p_client->HUD_GetPlayerTeam(g_pEngine->GetLocalPlayer()->index))
			DrawLine(Start, End, 0, 0, 255.0f, 0.001f);
		else
			DrawLine(Start, End, 255.f, 0.f, 0.f, 0.001f);
	}
}