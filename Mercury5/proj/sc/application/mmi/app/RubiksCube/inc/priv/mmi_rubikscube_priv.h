////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_rubikscube_priv.h
* @version
* @brief   Rubiks Cube Game applet private header file
*
*/

#ifndef __MMI_RUBIKSCUBE_PRIV_H__
#define __MMI_RUBIKSCUBE_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "rubikscube.h"

#include "melody_data.h"
#include "mmi_srv_audio.h"

#include "RubiksCube_resource.h"

#include "mgl_Egl.h"
#include "mgl_Core_Types.h"
#include "mgl_ErrCode.h"

#include "rubikscube.h"
//#include "rubikscube_maps.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
enum 
{
	RUBIKSCUBE_WND_DESKTOP = WND_ID_APP_BASE,
};

enum
{
	RUBIKSCUBE_BG_IMAGEWIDGET = APP_WDG_START,
};
/*=============================================================*/
// Data type definition
/*=============================================================*/
#define RUBIKSCUBE_MAP_NUM  30
#define MAX_RUBIKS_FACE          3
#define MAX_RUBIKS_GRID          6
#define MAX_RUBIKS_FACE_NODES    MAX_RUBIKS_GRID*MAX_RUBIKS_GRID
#define MAX_RUBIKS_NODES         MAX_RUBIKS_GRID*MAX_RUBIKS_GRID*MAX_RUBIKS_FACE

typedef struct
{
    mgl_u8          nSwitchIDX[2];
    mgl_u8          nCnt;   //Should be 2
    mgl_boolean     bPathConnect;
}RubiksSwitchList_t;

typedef struct
{
    mgl_u8      nNodeType;
    mgl_u8      nNodeSubType;
    mgl_u8      nNodeGroup;
    mgl_boolean bSwitchNode;
}RubiksPlaneList_t;

//Enum
typedef enum
{
    SCENE_PLANE_0,
    SCENE_PLANE_1,
    SCENE_PLANE_2,
    SCENE_PLANE_WORLD,
	SCENE_PLANE_OTHER,
    SCENE_PLANE_MAX,
} Scene_Face_e;


typedef enum
{
    WORLD_NODE_GROUP_0,
    WORLD_NODE_GROUP_1,
    WORLD_NODE_GROUP_2,
    WORLD_NODE_MENU,
	WORLD_NODE_MENU1,
    WORLD_NODE_BG,    
    WORLD_NODE_CONGRATS,
	WORLD_NODE_SHADOW,
    WORLD_NODE_MAX_NUM,
} WorldNode_Type_e;

typedef enum
{
	//OTHER_NODE_LOGO,
	OTHER_NODE_BACK,
	OTHER_NODE_LEVEL,
	OTHER_NODE_HELP_PAGE,
	OTHER_NODE_MAX_NUM,
} OtherNode_Type_e;

typedef enum
{
    RUBIKS_DIR_UP = 0,
    RUBIKS_DIR_DN,
    RUBIKS_DIR_LEFT,
    RUBIKS_DIR_RIGHT,
    RUBIKS_DIR_MAX,
    RUBIKS_DIR_NULL=0xff,
} RubiksDirect_e;

typedef enum
{
    CUBE_FACE0 = 0,
    CUBE_FACE1,
    CUBE_FACE2,
} CubeFace_e;

typedef enum
{
    SWITCH_DISABLE = 0,
    SWITCH_ENABLE,
    SWITCH_OK,
} SwitchStatus_e;

typedef enum
{
    PLANE_TYPE_EMPTY = 0,
    PLANE_TYPE_SWITCH_1,
    PLANE_TYPE_SWITCH_2,
    PLANE_TYPE_SWITCH_3,
    PLANE_TYPE_SWITCH_4,
    PLANE_TYPE_SWITCH_5,
    PLANE_TYPE_SWITCH_6,
    PLANE_TYPE_SWITCH_7,
    PLANE_TYPE_BLOCK,
    PLANE_TYPE_SWITCH_MAX,
} CubePlane_Type_e;

typedef enum
{
    SET_START = 0,
    SET_LENGTH,
    SET_GRIDLEN,
    SET_PATHNUM,
} Configure_Type_e;

typedef enum
{
    GAME_STATUS_MENU,
    GAME_STATUS_LOAD,
    GAME_STATUS_PLAY,
    GAME_STATUS_WIN,
    GAME_STATUS_COMPLETE,
	GAME_STATUS_HELP,
	GAME_STATUS_SELECT,
	GAME_STATUS_ROTATION,
	GAME_STATUS_PRESSED,
} Game_Status_e;

typedef enum
{
	RUBIKS_ITEMS_PLAY,
	RUBIKS_ITEMS_MUSIC,
	RUBIKS_ITEMS_HELP,

    RUBIKS_ITEMS_NEWGAME,
    RUBIKS_ITEMS_CONTINUE,
    RUBIKS_ITEMS_SELECT,
    
	RUBIKS_ITEMS_MAX,
} Item_Type_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

typedef struct
{
	APPLET_BASE_ELEMENTS;
    mgl_boolean	bTouched;
	mgl_ErrCode eNoRotCube;
    mgl_u16     u16SceneHandleId[SCENE_PLANE_MAX];
    mgl_u16     u16GridLen;
    mgl_u16     u16PlaneSize;
    mgl_u16     u16MenuItem_type;
    mgl_boolean bEnableMusic;
    mgl_u8      u8LevelIDX;
    mgl_u8      u8PaintType;
    mgl_u8      u8MaxPath;
    mgl_u8      u8GameStatus;
    mgl_u8      u8CurFace;
	mgl_u8		u8MenuLevel;
    
    mgl_float   fGlobal_alpha;
    mgl_s32     nTS_CurrentX, nTS_CurrentY;
    mgl_u32     nodeID[WORLD_NODE_MAX_NUM];
	mgl_u32		node_other_ID[OTHER_NODE_MAX_NUM];
    mgl_u32     node_Face0_ID[MAX_RUBIKS_FACE_NODES]; 
    mgl_u32     node_Face1_ID[MAX_RUBIKS_FACE_NODES]; 
    mgl_u32     node_Face2_ID[MAX_RUBIKS_FACE_NODES]; 

	mgl_u32		*pNode1;
	mgl_u32		*pNode2;

    Vertex2D    v2D_Grid[MAX_RUBIKS_FACE_NODES];
    Vertex2D    v2D_Group;

    RubiksPlaneList_t        tPlaneList[MAX_RUBIKS_NODES];
    RubiksSwitchList_t       tSwitchList[PLANE_TYPE_SWITCH_7];
	mgl_float   rotX, rotY;
	mgl_float	menu_rotate;
	mgl_float	menu_trans;

	boolean bSuspendMode;
    boolean bDraw;
	boolean bExit;
	boolean bPause;
	boolean	bBackPress;
	boolean bViewturn;
	boolean bQuit;

	//ICFGSrv *pICFGSrv;
#ifndef __G3D_MMI__
	IWidget *pBgImgWdg;
#endif
	IWidget *pTextWdg;
	mgl_u32 nTextRawDataID[RUBIKSCUBE_MAP_NUM];

	
	mgl_u8 current_level;
	mgl_u8 cfg_level;
	mgl_u16 sg_cur_gridsize;
	u32 cfg_data;
}RubiksCubeApp_t;

MAE_Ret  RubiksCubeApp_Ctor (RubiksCubeApp_t *pThis);
MAE_Ret  RubiksCubeApp_Dtor (RubiksCubeApp_t *pThis);

boolean  RubiksCubeApp_DefHandleEvent (RubiksCubeApp_t *pWdg, u32 evt, u32 P1, u32 P2);
void     RubiksCubeApp_Draw (RubiksCubeApp_t *pWdg);


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret RubiksCubeConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret RubiksCubeDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean RubiksCubeStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean RubiksCubeStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean RubiksCubeKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean RubiksCubeTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

boolean RubiksCubeHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean RubiksCubeGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);

MAE_Ret RubiksCubeWndDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret RubiksCubeWndCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

#endif 
