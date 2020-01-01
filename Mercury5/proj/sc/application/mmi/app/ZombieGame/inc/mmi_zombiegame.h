
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_zombiegame.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_ZOMBIEGAME_H__
#define __MMI_ZOMBIEGAME_H__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_zombiegame_priv.h"
#include "mmi_zombiegame_id.h"
#include "mmi_zombiegame_mainscene.h"
#include "mmi_zombiegame_levelscene.h"
#include "mmi_zombiegame_gamescene.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define ZOMBIE_SCENE_SWITCH_STEP    6
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
MAE_Ret ZombieGameNew(MAE_ClsId id, void **ppObj);
#else
MAE_Ret ZombieGameNew(void **ppObj);
MAE_Ret ZombieGame_Release(void *ppObj);
boolean ZombieGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameTouchCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif

#endif //__MMI_ZOMBIEGAME_H__
