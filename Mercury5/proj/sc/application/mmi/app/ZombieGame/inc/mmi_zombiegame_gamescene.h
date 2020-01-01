
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_zombiegame_gamescene.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_ZOMBIEGAME_GAMESCENE__
#define __MMI_ZOMBIEGAME_GAMESCENE__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_zombiegame.h"
#include "mmi_zombiegame_actors.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef struct 
{
	eZOMBIE_ACTOR_TYPE ActorType;
    pgl_u8  ActorSize;
	pgl_float pos_x, pos_y;
}Zombie_LevelInfo_t;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void Zombie_GameScene_OnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
pgl_void Zombie_GameScene_UnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
pgl_void Zombie_GameScene_AnimationCB(void *pApplet, void *userData);
#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
void Zombie_Game_FlashBtnClickCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);
#endif
#endif //__MMI_ZOMBIEGAME_GAMESCENE__
