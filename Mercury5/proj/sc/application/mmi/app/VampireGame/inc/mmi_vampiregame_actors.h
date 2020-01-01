
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_vampiregame_actors.h
*
*
* HISTORY
*      2012.02.22       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_VAMPIREGAME_ACTORS__
#define __MMI_VAMPIREGAME_ACTORS__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_headers.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define VAMPIRE_EXPLOSION_SIZE              64.0f

#ifdef C_MODEL
#define VAMPIRE_ACTOR_WAITING_TIMER         20
#define VAMPIRE_ACTOR_DEAD_TIMER            8
#define VAMPIRE_ACTOR_BITE_TIMER            10
#define VAMPIRE_ACTOR_BAT_TIMER             20
#define VAMPIRE_ACTOR_MALLET_TIMER          6
#define VAMPIRE_ACTOR_DARKCLOUND_TIMER      30
#define VAMPIRE_ACTOR_DARKCLOUND_MOVE_TIMER      100
#define VAMPIRE_ACTOR_STARTSWITCH_TIMER     10
#define VAMPIRE_ACTOR_SMOKE_TIMER     10
#else
#define VAMPIRE_ACTOR_WAITING_TIMER         10
#define VAMPIRE_ACTOR_DEAD_TIMER            2
#define VAMPIRE_ACTOR_BITE_TIMER            5
#define VAMPIRE_ACTOR_BAT_TIMER             5
#define VAMPIRE_ACTOR_MALLET_TIMER          2
#define VAMPIRE_ACTOR_DARKCLOUND_TIMER      5
#define VAMPIRE_ACTOR_DARKCLOUND_MOVE_TIMER      30
#define VAMPIRE_ACTOR_STARTSWITCH_TIMER     4
#define VAMPIRE_ACTOR_SMOKE_TIMER     4

#endif
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

enum
{
    eVAMPIRE_ACTOR_GOODVAMPIRE,
    eVAMPIRE_ACTOR_GOODVAMPIRE_BITE,
    eVAMPIRE_ACTOR_GOODVAMPIRE_DEAD,
    eVAMPIRE_ACTOR_GOODGIRLVAMPIRE,
    eVAMPIRE_ACTOR_GOODGIRLVAMPIRE_BITE,
    eVAMPIRE_ACTOR_GOODGIRLVAMPIRE_DEAD,
    eVAMPIRE_ACTOR_BADVAMPIRE,
    eVAMPIRE_ACTOR_BADVAMPIRE_BITE,
    eVAMPIRE_ACTOR_BADVAMPIRE_DEAD,
    eVAMPIRE_ACTOR_BADGIRLVAMPIRE,
    eVAMPIRE_ACTOR_BADGIRLVAMPIRE_BITE,
    eVAMPIRE_ACTOR_BADGIRLVAMPIRE_DEAD,
    eVAMPIRE_ACTOR_HUMAN,
    eVAMPIRE_ACTOR_GIRL,
    eVAMPIRE_ACTOR_CLERGYMAN,
    eVAMPIRE_ACTOR_GARLIC,
    eVAMPIRE_ACTOR_BOX,
    eVAMPIRE_ACTOR_BOX_STEP,
    eVAMPIRE_ACTOR_ROCK,
    eVAMPIRE_ACTOR_WHEEL,
    eVAMPIRE_ACTOR_CONCAVEWHEEL,
    eVAMPIRE_ACTOR_BAT,
    eVAMPIRE_ACTOR_CLOUD_1,
    eVAMPIRE_ACTOR_CLOUD_2,
    eVAMPIRE_ACTOR_CLOUD_3,
    eVAMPIRE_ACTOR_MALLET,
    eVAMPIRE_ACTOR_DARKCLOUD,
    eVAMPIRE_ACTOR_SMOKE,

    eVAMPIRE_ACTOR_SEGEMNT,
    eVAMPIRE_ACTOR_BOUND,
    eVAMPIRE_ACTOR_NODE_MAX,
};
typedef pgl_u16 eVAMPIRE_ACTOR_TYPE;

enum
{
    //BG...
    eVAMPIRE_GUI_MAINMENU_SCENE_BG = eVAMPIRE_ACTOR_NODE_MAX,
    eVAMPIRE_GUI_LEVELMENU_SCENE_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_1_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_2_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_3_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_4_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_5_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_6_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_7_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_8_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_9_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_10_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_11_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_12_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_13_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_14_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_15_BG,
    eVAMPIRE_GUI_PLAY_SCENE_LEVEL_16_BG,
    //BUTTOM...
    eVAMPIRE_GUI_BUTTOM_LEVEl_CLOSE,
    eVAMPIRE_GUI_BUTTOM_MAINMENU_START,
    eVAMPIRE_GUI_BUTTOM_MAINMENU_STARTPRESS,
    eVAMPIRE_GUI_BUTTOM_LEVEl_1,
    eVAMPIRE_GUI_BUTTOM_LEVEl_2,
    eVAMPIRE_GUI_BUTTOM_LEVEl_3,
    eVAMPIRE_GUI_BUTTOM_LEVEl_4,
    eVAMPIRE_GUI_BUTTOM_LEVEl_5,
    eVAMPIRE_GUI_BUTTOM_LEVEl_6,
    eVAMPIRE_GUI_BUTTOM_LEVEl_7,
    eVAMPIRE_GUI_BUTTOM_LEVEl_8,
    eVAMPIRE_GUI_BUTTOM_LEVEl_9,
    eVAMPIRE_GUI_BUTTOM_LEVEl_10,
    eVAMPIRE_GUI_BUTTOM_LEVEl_11,
    eVAMPIRE_GUI_BUTTOM_LEVEl_12,
    eVAMPIRE_GUI_BUTTOM_LEVEl_13,
    eVAMPIRE_GUI_BUTTOM_LEVEl_14,
    eVAMPIRE_GUI_BUTTOM_LEVEl_15,
    eVAMPIRE_GUI_BUTTOM_LEVEl_16,
    eVAMPIRE_GUI_BUTTOM_HOME,
    eVAMPIRE_GUI_BUTTOM_HOME_PRESS,
    eVAMPIRE_GUI_BUTTOM_RESTART,
    eVAMPIRE_GUI_BUTTOM_RESTART_PRESS,
    eVAMPIRE_GUI_BUTTOM_LEVEL,
    eVAMPIRE_GUI_BUTTOM_LEVEL_PRESS,
    eVAMPIRE_GUI_BUTTOM_BACK,
    eVAMPIRE_GUI_BUTTOM_BACK_PRESS,
    eVAMPIRE_GUI_BUTTOM_PREVIOUS,
    eVAMPIRE_GUI_BUTTOM_PREVIOUS_PRESS,
    eVAMPIRE_GUI_BUTTOM_NEXT,
    eVAMPIRE_GUI_BUTTOM_NEXT_PRESS,
    eVAMPIRE_GUI_BUTTOM_LEVELS,
    eVAMPIRE_GUI_BUTTOM_LEVELS_PRESS,
    eVAMPIRE_GUI_BUTTOM_SOUND,
    eVAMPIRE_GUI_BUTTOM_SOUND_CLOSE,
	eVAMPIRE_GUI_BUTTOM_NULL,
    //IMAGE...
    eVAMPIRE_GUI_IMAGE_LOST,
    eVAMPIRE_GUI_IMAGE_WIN,
    eVAMPIRE_GUI_IMAGE_CHECK,
    eVAMPIRE_GUI_IMAGE_0,
    eVAMPIRE_GUI_IMAGE_1,
    eVAMPIRE_GUI_IMAGE_2,
    eVAMPIRE_GUI_IMAGE_3,
    eVAMPIRE_GUI_IMAGE_4,
    eVAMPIRE_GUI_IMAGE_5,
    eVAMPIRE_GUI_IMAGE_6,
    eVAMPIRE_GUI_IMAGE_7,
    eVAMPIRE_GUI_IMAGE_8,
    eVAMPIRE_GUI_IMAGE_9,
    eVAMPIRE_GUI_IMAGE_L,
    
    eVAMPIRE_ACTOR_CAPTION_1,
    eVAMPIRE_ACTOR_CAPTION_2,
    eVAMPIRE_ACTOR_CAPTION_3,
    eVAMPIRE_ACTOR_CAPTION_4,
    eVAMPIRE_ACTOR_CAPTION_5,

    eVAMPIRE_GUI_MAINMENU_SCENE_MAX,
};
typedef pgl_u16 eVAMPIRE_GUI_TYPE;


enum
{
    eVAMPIRE_SOUND_PASS,
    eVAMPIRE_SOUND_BITE,
    eVAMPIRE_SOUND_PRESS,
    eVAMPIRE_SOUND_EXPLOSION,
    eVAMPIRE_SOUND_NODE_MAX,
};
typedef pgl_u16 eVAMPIRE_SOUND_TYPE;

#define     VAMPIRE_MAX_TEXTURE_NUM     eVAMPIRE_GUI_MAINMENU_SCENE_MAX
/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void Vampire_Prepare_AllResID(void *pApplet);
hActor Vampire_Add_Actor(void *pApplet, SceneHandleID SceneID, eVAMPIRE_ACTOR_TYPE  NodeType, pgl_float pos_x, pgl_float pos_y,
                         pgl_float size_w, pgl_float size_h,  pgl_float angle, PglActorTouchesCBFunc_t *pActorTouchCB);

pgl_void Vampire_Add_AddSeg(EngineHandleID engineID, SceneHandleID SceneID, ePgl_Actor_Name actor_name, pgl_float x1, pgl_float y1 , pgl_float x2, pgl_float y2);
hGuiActor Vampire_AddGUINode(void *pApplet, SceneHandleID SceneID, ePgl_Layer_Type elayer, eVAMPIRE_GUI_TYPE  NodeType,
                                  mgl_float GuiPosX, mgl_float GuiPosY, mgl_float GuiWidth, mgl_float GuiHeight,
                                  GuiActorTouchesCBFunc_t  *pGUITouchCB);
#ifdef C_MODEL
char*  Vampire_Get_ImageResID(eVAMPIRE_GUI_TYPE type);
#else
pgl_u32 Vampire_Get_ImageResID(eVAMPIRE_GUI_TYPE type);
#endif
pgl_void VampireGame_PlaySound(pgl_u16 nIdx);
#endif //__MMI_VAMPIREGAME_ACTORS__
