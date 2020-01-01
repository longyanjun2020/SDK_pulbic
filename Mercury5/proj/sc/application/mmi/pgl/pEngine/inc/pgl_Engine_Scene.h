/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Engine_Scene.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_ENGINE_SCENE_INC__
#define __PGL_ENGINE_SCENE_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
//#include "pgl_Utility_Types.h"
#include "pgl_Utility_Container.h"
#include "mmi_pgl_engine_scene.h"
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
ePgl_RetCode pgl_Engine_SceneMgr_Create(EngineHandleID engineID, pgl_s32 iterations, Vertex2D space_gravity);
pgl_void pgl_Engine_SceneMgr_Destroy(EngineHandleID engineID);
hList pgl_Engine_Scene_GetListHandle(EngineHandleID engineID, SceneHandleID sceneID, ePgl_Layer_Type elayer);
pgl_void pgl_Engine_Scene_Update(EngineHandleID engineID, SceneHandleID sceneID);
pgl_void pgl_Engine_Scene_OnFoucs(EngineHandleID engineID, SceneHandleID sceneID);
pgl_void pgl_Engine_Scene_UnFoucs(EngineHandleID engineID, SceneHandleID sceneID);
pgl_boolean pgl_Engine_Scene_UserDefinedDrawBG(EngineHandleID engineID, SceneHandleID sceneID);

#endif

