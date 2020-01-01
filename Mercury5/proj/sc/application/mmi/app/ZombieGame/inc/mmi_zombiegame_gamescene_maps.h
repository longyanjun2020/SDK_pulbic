
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_zombiegame_gamescene_maps.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_ZOMBIEGAME_GAMESCENE_MAP__
#define __MMI_ZOMBIEGAME_GAMESCENE_MAP__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

const Zombie_LevelInfo_t Zombie_Level1[] = 
{   
	////// Level 1
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,    176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,        272.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,         176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,         176.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,        272.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,         176.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,        240.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,        272.0f,         192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                          180.0f,         144.0f},
};


const  Zombie_LevelInfo_t Zombie_Level2[] = 
{
	// Level 2
	{eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,      176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          240.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           176.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          176.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          208.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           176.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            180.0f,         112.0f},
};

const  Zombie_LevelInfo_t Zombie_Level3[] = 
{
    // Level 3
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      272.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          272.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           368.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           176.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          208.0f,        192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            200.0f,        144.0f},
};

const  Zombie_LevelInfo_t Zombie_Level4[] = 
{
    // Level 4
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      226.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           184.0f,         256.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,          250.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           208.0f,         224.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,          240.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          272.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          240.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            232.0f,         112.0f},
};

const  Zombie_LevelInfo_t Zombie_Level5[] = 
{
    // Level 5
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          240.0f,         288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,          292.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      356.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          240.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          240.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           176.0f,         192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            190.0f,         144.0f},
};

const  Zombie_LevelInfo_t Zombie_Level6[] = 
{
    // Level 6
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           272.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           336.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          272.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          304.0f,         256.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_L,          240.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           336.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           304.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          336.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          368.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            340.0f,         112.0f},
};


const  Zombie_LevelInfo_t Zombie_Level7[] = 
{
    // Level 7
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          176.0f,         256.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,          208.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           160.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          208.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          240.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          224.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            216.0f,         112.0f},
};

const  Zombie_LevelInfo_t Zombie_Level8[] = 
{
    // Level 8
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           176.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,      336.0f,         288.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,          176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           240.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          336.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           192.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          224.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          224.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            216.0f,         112.0f},
};


const  Zombie_LevelInfo_t Zombie_Level9[] = 
{
    // Level 9
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         288.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,          208.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           336.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           176.0f,         256.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,      336.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          176.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          208.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          192.0f,         192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            184.0f,         144.0f},
};


const  Zombie_LevelInfo_t Zombie_Level10[] = 
{
    // Level 10
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_M,           48.0f,          288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          120.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_M,           176.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           48.0f,          256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           256.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           338.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           400.0f,         256.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            70.0f,          208.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,           338.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           338.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           338.0f,         128.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,      338.0f,         96.0f},

};


const  Zombie_LevelInfo_t Zombie_Level11[] = 
{
    // Level 11
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           128.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,      336.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,           128.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          160.0f,         256.0f},
    {eZOMBIE_ACTOR_TIRE,             eZOMBIE_TIRE_SIZE_M,         192.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          128.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           160.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           128.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          224.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          128.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           160.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            160.0f,         112.0f},


};

const  Zombie_LevelInfo_t Zombie_Level12[] = 
{
    // Level 12
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,           108.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          140.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          220.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           252.0f,           288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,      376.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           220.0f,           256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           220.0f,           224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          284.0f,           224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          284.0f,           192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            116.0f,           240.0f},
};


const  Zombie_LevelInfo_t Zombie_Level13[] = 
{
    // Level 13
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_M,           108.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          172.0f,           288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_S,      324.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,           356.0f,           288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,           108.0f,           256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,           300.0f,           256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          140.0f,           224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,          308.0f,           224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          356.0f,           224.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                            140.0f,           176.0f},
};

const  Zombie_LevelInfo_t Zombie_Level14[] = 
{
    // Level 14
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,          206.0f,         288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,         286.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,     366.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          238.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,         126.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,         206.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,          126.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,         126.0f,         160.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,         166.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,         206.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,          110.0f,         128.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                           116.0f,         80.0f},
};

const  Zombie_LevelInfo_t Zombie_Level15[] = 
{
    // Level 15
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          140.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          252.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,     364.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,         108.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,         220.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,         332.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,          108.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,          236.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,         172.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,         268.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,          172.0f,         96.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                           186.0f,         48.0f},
};

const  Zombie_LevelInfo_t Zombie_Level16[] = 
{
    // Level 16
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          48.0f,          288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,         80.0f,          288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,     208.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,          368.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          432.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,          32.0f,          256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,         426.0f,         256.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                           60.0f,          208.0f},
};

const  Zombie_LevelInfo_t Zombie_Level17[] = 
{
    // Level 17
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,          96.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,     144.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,         272.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          304.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,         296.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,          400.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,         56.0f,          224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_R,          400.0f,         192.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,          440.0f,         160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                           392.0f,         144.0f},
};


const  Zombie_LevelInfo_t Zombie_Level18[] = 
{
    // Level 18
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             56.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,        344.0f,        288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             440.0f,        288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             56.0f,         256.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,            120.0f,        256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             56.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             88.0f,         224.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            56.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            120.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,            72.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            104.0f,        160.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              80.0f,         112.0f},
};


const  Zombie_LevelInfo_t Zombie_Level19[] = 
{
    // Level 19
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            176.0f,        288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        240.0f,        288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,            336.0f,        288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             272.0f,         256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             166.0f,         224.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,            240.0f,         224.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             346.0f,         224.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_L,            176.0f,         160.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_L,            272.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,            198.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            256.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,            314.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             240.0f,         128.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              240.0f,          80.0f},

};

const  Zombie_LevelInfo_t Zombie_Level20[] = 
{
    // Level 20
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             156.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             252.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             316.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             412.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             172.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             332.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             236.0f,         224.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        156.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             380.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            212.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            356.0f,         192.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              276.0f,         176.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             196.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             340.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             236.0f,         128.0f},

};

const  Zombie_LevelInfo_t Zombie_Level21[] = 
{
    // Level 21
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,        126.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             318.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            318.0f,         256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             350.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,            382.0f,          256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             318.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            350.0f,         192.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,            382.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,            350.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,            414.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             318.0f,         128.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            318.0f,         96.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             414.0f,          96.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              326.0f,         48.0f},

};


const  Zombie_LevelInfo_t Zombie_Level22[] = 
{
    // Level 22
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            126.0f,         288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            254.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        382.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             174.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             304.0f,         256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             174.0f,         224.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,            254.0f,         224.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             368.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             198.0f,         192.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             270.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             310.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            214.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            326.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,            126.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,            414.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             142.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             342.0f,         128.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            270.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             222.0f,         96.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              262.0f,         48.0f},
};

const  Zombie_LevelInfo_t Zombie_Level23[] = 
{
    // Level 23
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        112.0f,         288.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            176.0f,         288.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            272.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            176.0f,         224.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            208.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            272.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             160.0f,         192.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             224.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             256.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,            150.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,             192.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S1,            296.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             112.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             240.0f,         128.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              216.0f,         80.0f},
};

const  Zombie_LevelInfo_t Zombie_Level24[] = 
{
    // Level 24
    {eZOMBIE_ACTOR_ZOMBIE,          0,                               36.0f,         48.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,             44.0f,         96.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,              28.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,             60.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              28.0f,         160.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,              156.0f,        160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             28.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             124.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              156.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,             204.0f,        224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              236.0f,        224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,             284.0f,        256.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_L,         364.0f,        288.0f},
};


const  Zombie_LevelInfo_t Zombie_Level25[] = 
{
    // Level 25
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,        176.0f,         288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,        240.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_S,    352.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,         176.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,        208.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,        272.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,         208.0f,         192.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,        240.0f,         160.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,        304.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,         224.0f,         128.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                          264.0f,         80.0f},
};

const  Zombie_LevelInfo_t Zombie_Level26[] = 
{
    // Level 26
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,         382.0f,       288.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                               94.0f,         80.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,              62.0f,        128.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,             78.0f,        160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             62.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             126.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,              174.0f,        160.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,             190.0f,        192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,             174.0f,        224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,             238.0f,        224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_L,              286.0f,        192.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_M,             302.0f,        224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,             286.0f,        256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,             350.0f,        256.0f},
};

const  Zombie_LevelInfo_t Zombie_Level27[] = 
{
    // Level 27
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              16.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,              208.0f,        288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_H,         344.0f,        288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,             192.0f,        256.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                               198.0f,        208.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             48.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             80.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              16.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,             32.0f,         96.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,              64.0f,         96.0f},
    {eZOMBIE_ACTOR_BOX,            eZOMBIE_BOX_SIZE_S0,              96.0f,         96.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             376.0f,        160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IH,             408.0f,        160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,              344.0f,        128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,             360.0f,        96.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,              392.0f,        96.0f},
    {eZOMBIE_ACTOR_BOX,            eZOMBIE_BOX_SIZE_S0,              424.0f,        96.0f},

};

const  Zombie_LevelInfo_t Zombie_Level28[] = 
{
    // Level 28
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             156.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,            188.0f,         256.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        220.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             284.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IM,            316.0f,         256.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            220.0f,         256.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            348.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             188.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             316.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             220.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            220.0f,         160.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,            268.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            316.0f,         160.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            244.0f,         128.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            292.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             220.0f,         96.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              260.0f,         48.0f},

};

const  Zombie_LevelInfo_t Zombie_Level29[] = 
{
    // Level 29
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        156.0f,         288.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             332.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             180.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             212.0f,         256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             340.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            188.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            236.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            284.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            332.0f,         224.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,            212.0f,         192.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,            260.0f,         192.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_S,            308.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             212.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_M,             276.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            236.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            284.0f,         128.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              252.0f,         80.0f},

};


const  Zombie_LevelInfo_t Zombie_Level30[] = 
{
    // Level 30
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            156.0f,         288.0f},
    {eZOMBIE_ACTOR_PLATFORM,        eZOMBIE_PLATFORM_SIZE_M,        244.0f,         288.0f},
    {eZOMBIE_ACTOR_TIRE,            eZOMBIE_TIRE_SIZE_M,            332.0f,         288.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             196.0f,         256.0f},
    {eZOMBIE_ACTOR_BOM,             eZOMBIE_BOM_SIZE_S,             324.0f,         256.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             212.0f,         224.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,            156.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_IL,            364.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            212.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_S0,            308.0f,         192.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             132.0f,         160.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             292.0f,         160.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            228.0f,         128.0f},
    {eZOMBIE_ACTOR_RISE,            eZOMBIE_RISE_SIZE_S,            292.0f,         128.0f},
    {eZOMBIE_ACTOR_BOX,             eZOMBIE_BOX_SIZE_H,             212.0f,         96.0f},
    {eZOMBIE_ACTOR_ZOMBIE,          0,                              252.0f,         48.0f},
};

    
/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/

#endif //__MMI_ZOMBIEGAME_GAMESCENE_MAP__
