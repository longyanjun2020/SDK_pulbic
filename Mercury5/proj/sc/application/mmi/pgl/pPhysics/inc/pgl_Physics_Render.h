/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Physics_Render.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_PHYSICS_RENDER_INC__
#define __PGL_PHYSICS_RENDER_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "pgl_Utility_Types.h"
#include "pgl_Resource_TexMgr.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef struct pglConstraintRenderInfo_tag
{
    pgl_boolean bVisual;
    Color4f color;
    pgl_u8 lineWidth;
}pglConstraintRenderInfo;

typedef struct pglPhysicsActorRenderInfo_tag
{
    EngineHandleID engineID;
    pgl_s32 hPhysicsSpace;
    pgl_u16 physicsSceneHandleId;
    pgl_u32 physicsSceneNodeId;
    pgl_float physicsSceneAlpha;
    pglConstraintRenderInfo constraintRenderInfo;
}pglPhysicsActorRenderInfo;

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
ePgl_RetCode pgl_Physics_RenderMgr_Create(pglPhysicsActorRenderInfo *pRenderInfo);
pgl_void pgl_Physics_RenderMgr_Release(pglPhysicsActorRenderInfo *pRenderInfo);
pgl_void pgl_Physics_Render_World(pglPhysicsActorRenderInfo *pRenderInfo);      
#endif

