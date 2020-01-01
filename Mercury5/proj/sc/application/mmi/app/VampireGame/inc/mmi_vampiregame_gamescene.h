
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_vampiregame_gamescene.h
*
*
* HISTORY
*      2012.02.22       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_VAMPIREGAME_GAMESCENE__
#define __MMI_VAMPIREGAME_GAMESCENE__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_vampiregame.h"
#include "mmi_vampiregame_actors.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void Vampire_GameScene_OnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
pgl_void Vampire_GameScene_UnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
pgl_void Vampire_GameScene_Update(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
#endif //__MMI_VAMPIREGAME_GAMESCENE__
