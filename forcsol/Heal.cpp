#include "main.h"
P_ClientBuff Client_ReadBuff;
void DrawMouseHeal(){
	Darwingclass Draw;
	char Buff[100];
	sprintf(Buff, XorString("Heal : %d%%"), Client_ReadBuff->MouseOnPlayerHeal);
	float F = ((float)(Client_ReadBuff->MouseOnPlayerHeal)) / 100.0f;
	Draw.绘制方框(550, 70, 128, 20, 2, 255, 255, 255, 100);
	Draw.绘制方块(552, 72, ((float)126) * F, 16, 0, 255, 0, 100);
	g_Engine.pfnDrawSetTextColor(0, 1, 0);
	g_pEngine->pfnDrawConsoleString(576, 72, Buff);
}