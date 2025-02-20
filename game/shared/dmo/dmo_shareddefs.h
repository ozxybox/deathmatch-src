//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef DMO_SHAREDDEFS_H
#define DMO_SHAREDDEFS_H
#ifdef _WIN32
#pragma once
#endif

//=========================
// GAMEPLAY RELATED OPTIONS
//=========================
// NOTES: The Wizard automatically replaces these strings! If you extract the source as is, you will have to add the defines manually!
//
// Will your mod be team based?
// define DMO_USE_TEAMS
#define DMO_USE_TEAMS

//
// Do you use player classes?
// define DMO_USE_PLAYERCLASSES
#define DMO_USE_PLAYERCLASSES

//================================
// PLAYER MOVEMENT RELATED OPTIONS
//================================

//
// Do your players have stamina? - this is a pre-requisite for sprinting, if you define sprinting, and don't uncomment this, it will be included anyway.
// define DMO_USE_STAMINA
#define DMO_USE_STAMINA

//
// Are your players able to sprint?
// define DMO_USE_SPRINTING
#define DMO_USE_SPRINTING

//Tony; stamina is a pre-requisite to sprinting, if you don't declare stamina but you do declare sprinting
//stamina needs to be included.
#if defined ( DMO_USE_SPRINTING ) && !defined( DMO_USE_STAMINA )
#define DMO_USE_STAMINA
#endif
//
// Can your players go prone?
// define DMO_USE_PRONE
//#define DMO_USE_PRONE

//=====================
// EXTRA WEAPON OPTIONS
//=====================

//
// If you're allowing sprinting, do you want to be able to shoot while sprinting?
// define DMO_SHOOT_WHILE_SPRINTING
#define DMO_SHOOT_WHILE_SPRINTING

//
// Do you want your players to be able to shoot while climing ladders?
// define DMO_SHOOT_ON_LADDERS
#define DMO_SHOOT_ON_LADDERS

//
// Do you want your players to be able to shoot while jumping?
// define DMO_SHOOT_WHILE_JUMPING
#define DMO_SHOOT_WHILE_JUMPING



#define DMO_GAME_DESCRIPTION	"Deathmatch Mod"
//================================================================================
// Most elements below here are specific to the options above.
//================================================================================

#if defined ( DMO_USE_TEAMS )

enum sdkteams_e
	{
		DMO_TEAM_BLUE = LAST_SHARED_TEAM+1,
		DMO_TEAM_RED,
	};

#endif // DMO_USE_TEAMS

#if defined ( DMO_USE_PRONE )

	#define TIME_TO_PRONE	1.2f
	#define VEC_PRONE_HULL_MIN	DMOGameRules()->GetDMOViewVectors()->m_vProneHullMin
	#define VEC_PRONE_HULL_MAX	DMOGameRules()->GetDMOViewVectors()->m_vProneHullMax
	#define VEC_PRONE_VIEW DMOGameRules()->GetDMOViewVectors()->m_vProneView

#endif // DMO_USE_PRONE

#if defined ( DMO_USE_SPRINTING )

	#define INITIAL_SPRINT_STAMINA_PENALTY 15
	#define LOW_STAMINA_THRESHOLD	35

#endif // DMO_USE_SPRINTING

#if defined ( DMO_USE_PLAYERCLASSES )
	#define DMO_NUM_PLAYERCLASSES 3		//Tony; our template sample has 3 player classes.
	#define DMO_PLAYERCLASS_IMAGE_LENGTH 64

	#define PLAYERCLASS_RANDOM		-2
	#define PLAYERCLASS_UNDEFINED	-1

	#if defined ( DMO_USE_TEAMS )
		//Tony; using teams with classes, so make sure the team class panel names are defined.
		#define PANEL_CLASS_BLUE		"class_blue"
		#define PANEL_CLASS_RED			"class_red"

		extern const char *pszTeamBlueClasses[];
		extern const char *pszTeamRedClasses[];
	#else
		#define PANEL_CLASS_NOTEAMS		"class_noteams"
		extern const char *pszPlayerClasses[];
	#endif // DMO_USE_TEAMS

#endif // DMO_USE_PLAYERCLASSES

#define DMO_PLAYER_MODEL "models/police.mdl"

//Tony; We need to precache all possible player models that we're going to use
extern const char *pszPossiblePlayerModels[];

extern const char *pszTeamNames[];

//Tony; these defines handle the default speeds for all of these - all are listed regardless of which option is enabled.
#define DMO_DEFAULT_PLAYER_RUNSPEED			220
#define DMO_DEFAULT_PLAYER_SPRINTSPEED		330
#define DMO_DEFAULT_PLAYER_PRONESPEED		50

//--------------------------------------------------------------------------------------------------------
//
// Weapon IDs for all DMO Game weapons
//
typedef enum
{
	WEAPON_NONE = 0,

	DMO_WEAPON_NONE = WEAPON_NONE,
	DMO_WEAPON_MP5,
	DMO_WEAPON_SHOTGUN,
	DMO_WEAPON_GRENADE,
	DMO_WEAPON_PISTOL,
	DMO_WEAPON_CROWBAR,
	DMO_WEAPON_LASERSNIPER,
	DMO_WEAPON_SAWSHOT,

	
	WEAPON_MAX,		// number of weapons weapon index
} DMOWeaponID;

typedef enum
{
	FM_AUTOMATIC = 0,
	FM_SEMIAUTOMATIC,
	FM_BURST,

} DMO_Weapon_Firemodes;

const char *WeaponIDToAlias( int id );
int AliasToWeaponID( const char *alias );


// The various states the player can be in during the join game process.
enum DMOPlayerState
{
	// Happily running around in the game.
	// You can't move though if CSGameRules()->IsFreezePeriod() returns true.
	// This state can jump to a bunch of other states like STATE_PICKINGCLASS or STATE_DEATH_ANIM.
	STATE_ACTIVE=0,
	
	// This is the state you're in when you first enter the server.
	// It's switching between intro cameras every few seconds, and there's a level info 
	// screen up.
	STATE_WELCOME,			// Show the level intro screen.
	
	// During these states, you can either be a new player waiting to join, or
	// you can be a live player in the game who wants to change teams.
	// Either way, you can't move while choosing team or class (or while any menu is up).
#if defined ( DMO_USE_TEAMS )
	STATE_PICKINGTEAM,			// Choosing team.
#endif
#if defined ( DMO_USE_PLAYERCLASSES )
	STATE_PICKINGCLASS,			// Choosing class.
#endif
	
	STATE_DEATH_ANIM,			// Playing death anim, waiting for that to finish.
	STATE_OBSERVER_MODE,		// Noclipping around, watching players, etc.

	NUM_PLAYER_STATES
};
#define DMO_PLAYER_DEATH_TIME	5.0f	//Minimum Time before respawning

// Special Damage types
enum
{
	DMO_DMG_CUSTOM_NONE = 0,
	DMO_DMG_CUSTOM_SUICIDE,
};

// Player avoidance
#define PUSHAWAY_THINK_INTERVAL		(1.0f / 20.0f)

#endif // DMO_SHAREDDEFS_H
