/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Gui_Actor.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_GUI_ACTOR_INC__
#define __PGL_GUI_ACTOR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
//#include "pgl_Utility_Types.h"
#include "pgl_Utility_Container.h"
#include "pgl_Gui_Render.h"
#include "pgl_Engine_Scene.h"
#include "pgl_Resource_TexMgr.h"
#include "mgl_Utility_common.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"
#include "mgl_Core_Shape.h"
#include "mmi_pgl_gui_actor.h"


/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
/*Interal build-in interface for engine!*/
ePgl_RetCode pgl_Gui_Space_Create(EngineHandleID engineID);
pgl_void pgl_Gui_Space_Destroy(EngineHandleID engineID);
pgl_void pgl_Gui_Space_Render(EngineHandleID engineID, ePgl_Layer_Type elayer, pgl_float sceneAlpha);
pgl_void pgl_Gui_Space_Update(EngineHandleID engineID);
pgl_void pgl_Gui_Space_Clear(EngineHandleID engineID);
/*Interal Gui Picking APIs*/
pgl_boolean pgl_Gui_TouchesBegan(EngineHandleID engineID, SceneHandleID sceneID, ePgl_Layer_Type elayer, pgl_u32 nTSx, pgl_u32 nTSy);
pgl_void pgl_Gui_TouchesEnded(EngineHandleID engineID);
pgl_void pgl_Gui_TouchesMoved(EngineHandleID engineID, pgl_u32 nTSx, pgl_u32 nTSy);

#endif

