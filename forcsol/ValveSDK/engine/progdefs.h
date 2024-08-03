/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef PROGDEFS_H
#define PROGDEFS_H
#ifdef _WIN32
#pragma once
#endif

typedef struct
{	
	float		time;
	float		frametime;
	float		force_retouch;
	string_t	mapname;
	string_t	startspot;
	float		deathmatch;
	float		coop;
	float		teamplay;
	float		serverflags;
	float		found_secrets;
	vec3_t		v_forward;
	vec3_t		v_up;
	vec3_t		v_right;
	float		trace_allsolid;
	float		trace_startsolid;
	float		trace_fraction;
	vec3_t		trace_endpos;
	vec3_t		trace_plane_normal;
	float		trace_plane_dist;
	edict_t		*trace_ent;
	float		trace_inopen;
	float		trace_inwater;
	int			trace_hitgroup;
	int			trace_flags;
	int			msg_entity;
	int			cdAudioTrack;
	int			maxClients;
	int			maxEntities;
	const char	*pStringBase;

	void		*pSaveData;
	vec3_t		vecLandmarkOffset;
} globalvars_t;


typedef struct entvars_s
{
	string_t	classname;
	string_t	globalname;

	vec3_t		origin; //8
	vec3_t		oldorigin;//14
	vec3_t		velocity;//20
	vec3_t		basevelocity;//2c
	vec3_t      clbasevelocity;  //38 Base velocity that was passed in to server physics so 
							     //  client can predict conveyors correctly.  Server zeroes it, so we need to store here, too.
	vec3_t		movedir;//44

	vec3_t		angles;			// 50 Model angles
	vec3_t		avelocity;		// 5c angle velocity (degrees per second)
	vec3_t		punchangle;		// 68 auto-decaying view angle adjustment
	vec3_t		v_angle;		// 74 Viewing angle (player only)

	// For parametric entities
	vec3_t		endpos;//80
	vec3_t		startpos;//8c
	vec3_t		NewVec;//98
	int			NewAdd;//A4
	float		impacttime;//A8
	float		starttime;//AC

	int			fixangle;		// B0 0:nothing, 1:force view angles, 2:add avelocity
	float		idealpitch;//B4
	float		pitch_speed;//B8
	float		ideal_yaw;//BC
	float		yaw_speed;//C0

	int			modelindex;//C4
	string_t	model;//C8

	int			viewmodel;		//CC player's viewmodel
	int			weaponmodel;	//D0 what other players see
	
	vec3_t		absmin;		//D4  BB max translated to world coord
	vec3_t		absmax;		//E0 BB max translated to world coord
	vec3_t		mins;		//EC local BB min
	vec3_t		maxs;		//F8 local BB max
	vec3_t		size;		//104 maxs - mins

	float		ltime;//110
	float		nextthink;//114

	int			movetype;//118
	int			solid;//11c

	int			skin;//120			
	int			body;			//124 sub-model selection for studiomodels
	int 		effects;//128
	
	float		gravity;		//12C % of "normal" gravity
	float		friction;		//130 inverse elasticity of MOVETYPE_BOUNCE
	
	int			light_level;//134

	int			sequence;		//138 animation sequence
	int			gaitsequence;	//13C movement animation sequence for player (0 for none)
	float		frame;			//140 % playback position in animation sequences (0..255)
	float		animtime;		//144 world time when frame was set
	float		framerate;		//148 animation playback rate (-8x to 8x)
	::byte		controller[4];	// bone controller setting (0..255)
	::byte		blending[2];	// blending amount between sub-sequences (0..255)

	float		scale;			//154 sprite rendering scale (0..255)

	int			rendermode;//158
	float		renderamt;//15C
	vec3_t		rendercolor;//168
	int			renderfx;//16C

	float		health;//170
	float		frags;
	int			ph42;
	int			ph43;
	int			ph44;
	int			weapons;  // bit mask for available weapons
	float		takedamage;

	int			deadflag;
	vec3_t		view_ofs;	// eye position

	int			button;
	int			impulse;

	edict_t		*chain;			// Entity pointer when linked into a linked list
	edict_t		*dmg_inflictor;
	edict_t		*enemy;
	edict_t		*aiment;		// entity pointer when MOVETYPE_FOLLOW
	edict_t		*owner;
	edict_t		*groundentity;

	int			spawnflags;//1BC
	int			flags;//1C0
	int			ph106;//1C4
	int			Unk22;//1C8
	
	int			colormap;		//1CC low::byte topcolor, high::byte bottomcolor
	int			team;//1d0

	float		max_health;//1D4
	float		teleport_time;//1D8
	float		armortype;//1DC
	float		armorvalue;//1E0
	int			waterlevel;//1E4
	int			watertype;//1E8
	
	string_t	target;//1EC
	string_t	targetname;//1F0
	string_t	netname;//1F4
	string_t	message;//1F8

	float		dmg_take;//1FC
	float		dmg_save;//200
	float		dmg;//204
	float		dmgtime;//208
	
	string_t	noise;//20c
	string_t	noise1;//210
	string_t	noise2;//214
	string_t	noise3;//218
	
	float		speed;//21c
	float		air_finished;//220
	float		pain_finished;//224
	float		radsuit_finished;//228
	int			NewUnk;//22c
	
	edict_t		*pContainingEntity;//230

	int			playerclass;//234
	float		maxspeed;//238

	float		fov;//23c
	int			weaponanim;//240

	int			pushmsec;//244

	int			bInDuck;//248
	int			flTimeStepSound;
	int			flSwimTime;
	int			flDuckTime;
	int			iStepLeft;
	float		flFallVelocity;

	int			gamestate;

	int			oldbuttons;

	int			groupinfo;

	// For mods
	int			iuser1;
	int			iuser2;
	int			iuser3;
	int			iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
	edict_t		*euser1;
	edict_t		*euser2;
	edict_t		*euser3;
	edict_t		*euser4;
} entvars_t;


#endif // PROGDEFS_H