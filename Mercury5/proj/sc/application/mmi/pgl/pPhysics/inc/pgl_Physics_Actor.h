/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Physics_Actor.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_PHYSICS_ACTOR_INC__
#define __PGL_PHYSICS_ACTOR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
//#include "pgl_Utility_Types.h"
//#include "pgl_Engine_Core.h"
#include "pgl_Utility_Container.h"
#include "pgl_Physics_Render.h"
#include "pgl_Resource_TexMgr.h"
#include "mgl_Utility_common.h"
#include "mgl_Texture_ImgMgr.h"
#include "pgl_Engine_Scene.h"
#include "mmi_pgl_physics_actor.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

typedef struct PglPhysicsSpaceInfo_tag
{
    pgl_s32 iterations;
    Vertex2D space_gravity;
}PglPhysicsSpaceInfo_t;

typedef struct PglActorData_t_tag
{
    EngineHandleID      engineID;
    ePgl_Shape_Type     shapeType;
    cpDataPointer       pUserData;
    PglActorTouchesCBFunc_t touchesCBFunc;
    hTexRes             TexID;
    Color4f             color;
    pgl_float           width;
    pgl_float           height;
    mgl_float           depth;
    pgl_u32             curTimerStep;
    pgl_u8              curFragment;
    pgl_u32             curLoopCycle;
    pgl_u32             fragmentStep;       //PGL_SPRITE_FIX_FRAME : Fix current frame!
    pgl_u32             spriteLoopCycle;    //PGL_SPRITE_INFINITY_LOOP : Infinity loop!
    pgl_s32             status;
}PglActorData_t;

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
/*Interal build-in interface for engine!*/
ePgl_RetCode pgl_Physics_Space_Create(EngineHandleID engineID, PglPhysicsSpaceInfo_t *pglSpaceInfo);
pgl_void pgl_Physics_Space_Reset(EngineHandleID engineID, PglPhysicsSpaceInfo_t *pglSpaceInfo);
pgl_void pgl_Physics_Space_Destroy(EngineHandleID engineID);
pgl_void pgl_Physics_Space_Render(EngineHandleID engineID, pgl_float sceneAlpha);
pgl_void pgl_Physics_Space_Update(EngineHandleID engineID, pgl_u16 fps);

/*Interal Physics Picking APIs*/
pgl_boolean pgl_Physics_TouchesBegan(EngineHandleID engineID, SceneHandleID sceneID, pgl_u32 nTSx, pgl_u32 nTSy);
pgl_void pgl_Physics_TouchesEnded(EngineHandleID engineID);
pgl_void pgl_Physics_TouchesMoved(EngineHandleID engineID, pgl_u32 nTSx, pgl_u32 nTSy);

#endif

