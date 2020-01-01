
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_fishfury_mainscene.h
*
*
* HISTORY
*      2012.01.05       Andy Wang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_FISHFURY_MAINSCENE_INC__
#define __MMI_FISHFURY_MAINSCENE_INC__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_headers.h"

#include "mgl_Scene_Environment.h"
#include "mmi_fishfurygame_priv.h"


/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

#define START_ICON_WIDTH    132
#define START_ICON_HEIGHT   48
#define START_POS_X         328
#define START_POS_Y         265

#define MUSIC_ICON_WIDTH    36
#define MUSIC_ICON_HEIGHT   36
#define MUSIC_POS_X         20
#define MUSIC_POS_Y         275

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void FishFury_MainScene_OnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
#endif

