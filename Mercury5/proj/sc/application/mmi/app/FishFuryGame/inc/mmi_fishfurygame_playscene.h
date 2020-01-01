/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_fishfury_playscene.h
*
*
* HISTORY
*      2012.01.05       Andy Wang         Initial Version
*
*-----------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_headers.h"
#include "mgl_Scene_Environment.h"
#include "mmi_fishfurygame_priv.h"


/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#ifndef __MMI_FISHFURYGAME_PLAYSCENE_INC__
#define __MMI_FISHFURYGAME_PLAYSCENE_INC__

//#define FOOT_PRINT_RENDER

#define INIT_X      (40)
#define INIT_Y      (220)

#define FISHFURY_STATUS_INIT                0x0000
#define FISHFURY_STATUS_FIRE                0x0001
#define FISHFURY_STATUS_REMOVE_BOMO_BIRD    0x0002
#define FISHFURY_STATUS_REMOVE_SHAPE        0x0004
#define FISHFURY_STATUS_SPLIT_BIRD          0x0010
#define FISHFURY_STATUS_ADD_FOOTPRINT       0x0020
#define FISHFURY_STATUS_ADD_NEXT_BIRD       0x0040
#define FISHFURY_STATUS_RESETGAME           0x8000

#define FISHFURY_PREPARE_TIME           110
#define FISHFURY_REMOVE_TIME            100
#define FISHFURY_RESET_TIME         90

#define NUM_BOMOS 10
#define NUM_BREAKS 8
#define NUM_REMOVE_SHAPE 64
#define MAX_FOOTPRINTFS 320
#define FOOTPRINTFS_TIMER 50

#define  XSHIFT     260.0f
#define  YSHIFT     70.0f

#define FIRE_X 60.0f
#define FIRE_Y 197.0f
#define FIRE_SHIFT_X 40.0f
#define FIRE_SHIFT_Y 40.0f

#define SLING1_X1 60.0f
#define SLING1_Y1 210.0f
#define SLING1_X2 80.0f
#define SLING1_Y2 210.0f
#define SLING2_X1 80.0f
#define SLING2_Y1 210.0f
#define SLING2_X2 60.0f
#define SLING2_Y2 210.0f
#define SLING_SHIFT_X 10.0f
#define SLING_SHIFT_Y 10.0f

#define ABS(_v) (((_v)<0.0f)?(-(_v)):(_v))

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef struct
{
    u8  idx;
    u32 birdType;
}AB_Bird;

typedef struct
{
    u32 shapeType;
    float x, y;
    float width, height;
    float angle;
}AB_Object;

typedef struct
{
    const AB_Bird *birds;
    u32 birds_num;

    const AB_Object *items;
    u32 item_num;
}AB_Level;

typedef struct
{
    int status;
    int countdown;
    hActor hactor;
} RemoveShape;

typedef enum
{
    PIG_TYPE= 0,
    WOOD_TYPE,
    ICE_TYPE,
    ROCK_TYPE,
    BALL_TYPE,
    BOX_TYPE,
    PLANE_TYPE,
} Type_e;

typedef enum
{
    COLLISION_TYPE_OTHER = 0,
    COLLISION_TYPE_WOOD,
    COLLISION_TYPE_ICE,
    COLLISION_TYPE_ROCK,
    COLLISION_TYPE_BIRD,
    COLLISION_TYPE_BOMO,
    COLLISION_TYPE_PIG,
    COLLISION_TYPE_GROUND,
    COLLISION_TYPE_NULL,
}CollisionType_e;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void FishFury_PlayScene_OnFocus(EngineHandleID engineID, SceneHandleID nSceneID, void *userData);
pgl_void FishFury_CheckCamera(FishFuryGameAppData_t *pThis, EngineHandleID engineID);
#endif

