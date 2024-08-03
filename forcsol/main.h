#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <time.h>
#include "ValveSDK/engine/wrect.h"
#include "ValveSDK/engine/cl_dll.h"
#include "ValveSDK/engine/r_studioint.h"
#include "ValveSDK/engine/cl_entity.h"
#include "ValveSDK/misc/com_model.h"
#include "ValveSDK/engine/triangleapi.h"
#include "ValveSDK/engine/pmtrace.h"
#include "ValveSDK/engine/pm_defs.h"
#include "ValveSDK/engine/pm_info.h"
#include "ValveSDK/common/ref_params.h"
#include "ValveSDK/common/studio_event.h"
#include "ValveSDK/common/net_api.h"
#include "ValveSDK/common/r_efx.h"
#include "ValveSDK/engine/cvardef.h"
#include "ValveSDK/engine/util_vector.h"
#include "ValveSDK/misc/parsemsg.h"
#include "ValveSDK/engine/studio.h"
#include "ValveSDK/engine/event_args.h"
#include "ValveSDK/engine/event_flags.h"
#include "ValveSDK/common/event_api.h"
#include "ValveSDK/common/screenfade.h"
#include "ValveSDK/engine/keydefs.h"
#include "ValveSDK/engine/eiface.h"
#include "ValveSDK/common/interface.h"
#include "ValveSDK/mp/util.h"
#include "ValveSDK/mp/cbase.h"
#include "ValveSDK/mp/basemonster.h"
#include "ValveSDK/mp/player.h"
#include "cl_clientfuncs.h"
#include "编码转化.h"
#include "荣誉.h"
#include "NT_DDK.h"
#include "GameUi007.h"
#include "darw.h"
#include "ClientPrint.h"
#include "heal.h"
#include "Computer.h"
#include "VoxelBlockEntity.h"
#include "MpBase.h"
#include "VguiMenu.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include	"imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"
#include <xorstr.hpp>
#include <gl/GL.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment( lib, "dbghelp.lib" )

#define VK_E 0x45
#define VK_V 0x56
#define VK_R 0x52
#define Inf 0x7F800000;
#define NInf 0xFF800000;
#define DefineSpeed 0.0000008
#define DelteFunMem(x) (delete[]##x)
#define Dll_Export extern "C" __declspec(dllexport)
#define AsyDown (1<<15)
#define AsyPush 0x1
#define MouseEvent_Left (1<<0)
#define MouseEvent_Right (1<<1)
#define MouseEvent_3 (1<<2)


//--
#define POW(x) ((x)*(x))
#define VectorDistance(a,b) sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define 阵营数组 0x220

extern DWORD 阵营基质;

typedef struct mymodel
{
	char* modelname;
	cl_entity_s *ent;
}mymodel_t;

typedef struct 功能
{
	cvar_s 无后;
	cvar_s 发光;
	cvar_s Aero;
	cvar_s mcj;
	cvar_s bunny;
	cvar_s 自动同步;
	cvar_s 跟踪线;
	cvar_s hello;
	cvar_s 躲猫猫透视;
	cvar_s 名称打码;
	cvar_s 摇头;
	cvar_s fastrun;
}功能_t;

typedef struct hwandclient
{
	DWORD hw;
	DWORD client;
	DWORD Mp;
	DWORD Vgui2;
}hwandclient_t;

typedef struct TUserMsg
{
	int number;
	int size;
	char name[16];
	struct TUserMsg* next;
	pfnUserMsgHook pfn;
} *PUserMsg;

typedef struct playmove
{
	int flags;//状态
	int movetype;//人物行走状态
	int waterleave;//水深等级
	float maxspeed;
	float clientmaxspeed;
	int bInDuck;
	float flGroundAngle;
	float xyspeed;
	Vector punchangle;
	Vector velocity;
	float iHeight;
	float zSpeed;
	Vector Eyes;
	playermove_s MeMove;
}playermovei_t;

//--
#define 阵营偏移 0x274;
#define 状态偏移 0x12;
#define 有效偏移 0x28;

inline HMODULE m_DllModule;

#include "externbase.h"
#include "externFun.h"
#include "HackAddres.h"
