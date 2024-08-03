#pragma once
#include "main.h"
#include "ClassHook.h"
#include "VguiPanle.h"
extern DWORD adjspeed;
extern double* Adj_Speed;
extern hwandclient_t GameMoudle;
extern cl_enginefunc_t* g_pEngine;
extern cl_enginefunc_t  g_Engine;
extern cl_clientfunc_t* p_client;
extern r_studio_interface_t* g_pStudio;
extern r_studio_interface_t g_Studio;
extern engine_studio_api_t* g_pStudioApi;
extern engine_studio_api_t g_StudioApi;
extern enginefuncs_t* g_pEngineFuncs_t;
extern GameUi007* G_Game007;
extern cl_clientfunc_t old_client;
extern Vgui2MenuGet* GetVguiMenu;
extern playermovei_t mymove;
extern SCREENINFO g_Screen;
extern ::byte* 躲猫猫开关;
extern DWORD 矩阵基质;
extern DWORD Adjspeed总开关;
extern DWORD* 判断空气墙;
extern DWORD* g_GameUi;
extern pfnUserMsgHook pSetFOV;
extern DWORD 校对基质;
extern float displayCenterX, displayCenterY;
extern DWORD MpZ;
extern WNDPROC lpWndProc;
extern DWORD* FUCKBLACK;
extern cvar_t PlayerEsp, Playerbrring;
extern cvar_t DefCvar, MapBring, Vk, BossSpeed, autoFire, BugScer, HighUpload, CNoWhite, NoSmoke,
trigger, air, DrawHeal, VoxelFuckMap, VoxelSkyValuel, VoxelBringht, VoxelFirendKill, HowBlock, DeadLongRpn, ZombieFuckMap, ZombieRedX, InitBack, FireDam, FogValue, FogStatcValue,
MpHeal, MpSpeed, MpFire, MpRightFire, MpDrawAll, MpFuckInxCv, MpFlySky, MpBuyMyG, MpAllInfAmmo, MpMyModle, MpLeave, MpSetsv, MpAngle, MpLockWeapon, BoomValue, MeMpHeal, MeMpFire
, MeMpRightFire, MeMpMouseTp, MeMpSpeedHack, MeMpNoAngle, MeMpMouseMonsterTp, VxlFuckRoomPlayer, MaxBrring, VoxelSee, VxlRGBFOG, VxlHigeBlock, C_DelMenu, C_GetAmmo, VxlMapLight,
NotRpn_, VoxelBuyBugB, VxlHigeFriend, VxlResetTrigger, MpGrad, VxlCloseFriend, SpeedHackAutoRoom, SpeedNotDraw, Like嗨丝;
extern color24 MapColor, FogColor;
extern double* TimeSpeed, * HigePingBase[5];
extern UINT* NubSpeed, * PlayerSpeed;
extern pcvar_t Esp, DrawName, DrawWeaponOhMaybe, PlayerAeroEsp, SpeedUp;
extern float* TimtOut[2];
extern int* GameSce;
extern float* CheckSpeedHack;
extern ::byte* Check;
extern const char* IfLocal;
extern P_ClientBuff Client_ReadBuff;
extern UINT ComputerUi;
extern PBlock* BlockEntity;
extern P_PlayerVxlOring PlayerVox;
extern EncryptionCall CmdCall;
extern bool Isinit;
extern PULONG CreateThis;
extern ULONG FindBossInxCall;
extern ULONG ChaCheThis;
extern PULONG SvGameAddFullPuck;
extern ULONG OldSvGameAddFullPuck;
extern double* VeryHigeSpeedHack;
extern GetVoxelBlockListHead GetList;
extern GetUnkClass GetUnk;
extern SetListCall SetList;
extern ::byte aerorgb;
extern ULONG ChaCheTheEditc;
extern 功能_t 功能;
extern ULONG P_WindowHWND;
extern PFLOAT CloseClientPtr;
extern ClassHook::MeClassHook HookVgui;
extern Vector vForward, vRight;
extern float GameTime;
extern bool IsVip;
extern P_ShootTimed2 ShootTimed2;
extern bool WIn7;