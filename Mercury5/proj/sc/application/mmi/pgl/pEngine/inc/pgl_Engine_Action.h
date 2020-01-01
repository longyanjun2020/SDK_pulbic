/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Engine_Action.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_ENGINE_ACTION_INC__
#define __PGL_ENGINE_ACTION_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
//#include "pgl_Utility_Types.h"
#include "pgl_Utility_Container.h"
#include "pgl_Physics_Actor.h"
#include "pgl_Gui_Actor.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
enum
{
    ePGL_ACTION_ACTOR_PHYSICS = 0,
    ePGL_ACTION_ACTOR_GUI,
    ePGL_ACTION_ACTOR_MAX,
} ;
typedef pgl_s16 ePgl_Action_ActorType;


enum
{
    ePGL_ACTION_AMIN_MOVE_TO = 0,
    ePGL_ACTION_AMIN_JUMP_TO,
    ePGL_ACTION_AMIN_ROTATION_TO,
    ePGL_ACTION_AMIN_DELAY,
    ePGL_ACTION_AMIN_MAX,
} ;
typedef pgl_s16 ePgl_Action_Type;

typedef struct pglMoveTo_tag
{
    pgl_float start_pos_x;
    pgl_float start_pos_y;
    pgl_float end_pos_x;
    pgl_float end_pos_y;
    pgl_float delta_x;
    pgl_float delta_y;
}pglMoveTo;

typedef struct pglJumpTo_tag
{
    pgl_float start_pos_x;
    pgl_float start_pos_y;
    pgl_float height_x;
    pgl_float height_y;
    pgl_float jump_Frame;
    //pgl_float jumps;
}pglJumpTo;

typedef struct pglRotationTo_tag
{
    pgl_float delta_angle;
    pgl_float end_angle;
}pglRotationTo;

typedef pgl_void (*FPPglActorDelayCBFunc)(hActor hActorNode, pgl_void *pUserData);
typedef struct pglDelay_tag
{
    FPPglActorDelayCBFunc fpDelayCBFunc;
    pgl_void				*pUserData;
}pglDelay;

typedef struct pglActorActionInfo_tag
{
    pgl_float             duration;
    ePgl_Action_Type    actionType;
    union
    {
        pglMoveTo       moveTo;
        pglJumpTo       jumpTo;
        pglRotationTo   rotationTo;
        pglDelay delay;
    }uActionParams;
}pglActorActionInfo;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
ePgl_RetCode pgl_Engine_ActionMgr_Create(EngineHandleID engineID);
pgl_void pgl_Engine_ActionMgr_Destroy(EngineHandleID engineID);
pgl_void pgl_Engine_ActionMgr_Clear(EngineHandleID engineID);
pgl_void pgl_Engine_ActionMgr_Update(EngineHandleID engineID);
pgl_void pgl_Engine_AddAction(EngineHandleID engineID, hActor hAct, ePgl_Action_ActorType actorType, pglActorActionInfo *pActionInfo);
pgl_void pgl_Engine_RemoveAction(EngineHandleID engineID, hActor hAct, ePgl_Action_ActorType actorType);

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/

#endif
