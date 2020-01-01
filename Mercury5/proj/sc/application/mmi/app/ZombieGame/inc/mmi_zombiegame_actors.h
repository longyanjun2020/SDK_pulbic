
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_zombiegame_actors.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_ZOMBIEGAME_ACTORS__
#define __MMI_ZOMBIEGAME_ACTORS__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_headers.h"
#include "mmi_zombiegame_priv.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define ZOMBIE_EXPLOSION_SIZE   64.0f
#define ZOMBIE_ZOMBIE_CHARACTER_MASS                (0.5f)
#define ZOMBIE_ZOMBIE_CHARACTER_RESTITUTION         (0.8f)
#define ZOMBIE_QUAD_SMALL_BOX_MASS                  (0.5f)
#define ZOMBIE_HORIZONTAL_MIDDLE_BOX_MASS           (1.0f)
#define ZOMBIE_HORIZONTAL_LARGE_BOX_MASS            (1.5f)
#define ZOMBIE_HORIZONTAL_HUGE_BOX_MASS             (2.5f)
#define ZOMBIE_VERTICAL_MIDDLE_BOX_MASS             (ZOMBIE_HORIZONTAL_MIDDLE_BOX_MASS)
#define ZOMBIE_VERTICAL_LARGE_BOX_MASS              (ZOMBIE_HORIZONTAL_LARGE_BOX_MASS)
#define ZOMBIE_VERTICAL_HUGE_BOX_MASS               (ZOMBIE_HORIZONTAL_HUGE_BOX_MASS)
#define ZOMBIE_QUAD_MIDDLE_BOX_MASS                 (ZOMBIE_HORIZONTAL_HUGE_BOX_MASS)

#define ZOMBIE_PLATFORM_SMALL_MASS                  (ZOMBIE_QUAD_SMALL_BOX_MASS)
#define ZOMBIE_PLATFORM_MIDDLE_MASS                 (ZOMBIE_HORIZONTAL_MIDDLE_BOX_MASS)
#define ZOMBIE_PLATFORM_LARGE_MASS                  (ZOMBIE_HORIZONTAL_LARGE_BOX_MASS)
#define ZOMBIE_PLATFORM_HUGE_MASS                   (ZOMBIE_HORIZONTAL_HUGE_BOX_MASS)

#define ZOMBIE_TIRE_RESTITUTION                     (1.0f)
#define ZOMBIE_TIRE_SMALL_MASS                      (ZOMBIE_QUAD_SMALL_BOX_MASS)
#define ZOMBIE_TIRE_MIDDLE_MASS                     (ZOMBIE_HORIZONTAL_MIDDLE_BOX_MASS)
#define ZOMBIE_TIRE_LARGE_MASS                      (ZOMBIE_HORIZONTAL_LARGE_BOX_MASS)
#define ZOMBIE_TIRE_HUGE_MASS                       (ZOMBIE_HORIZONTAL_HUGE_BOX_MASS)

#define ZOMBIE_BALLOON_SMALL_MASS                   (1.0f)
#define ZOMBIE_BALLOON_MIDDLE_MASS                  (1.0f)
#define ZOMBIE_BALLOON_LARGE_MASS                   (1.5f)
#define ZOMBIE_BALLOON_UPWARD_FORCE                 (-120.0f)

#define ZOMBIE_BOMB_RESTITUTION                     (1.0f)
#define ZOMBIE_BOMB_SMALL_MASS                      (0.5f)
#define ZOMBIE_BOMB_MIDDLE_MASS                     (1.0f)
#define ZOMBIE_BOMB_LARGE_MASS                      (1.5f)
#define ZOMBIE_BOMB_EXPLOSION_MASS                  (50.0f)

#define ZOMBIE_ANIM_EXPLOSION_FRAGMENT              (3)
#define ZOMBIE_ANIM_DEAD_FRAGMENT                   (5)
#define ZOMBIE_ANIM_LIGHT_FRAGMENT                  (4)
#define ZOMBIE_ANIM_FLAG_FRAGMENT                   (4)

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/


enum
{
    eZOMBIE_BOX_SIZE_S0=0,
    eZOMBIE_BOX_SIZE_S1,
    eZOMBIE_BOX_SIZE_M,
    eZOMBIE_BOX_SIZE_IM,
    eZOMBIE_BOX_SIZE_L,
    eZOMBIE_BOX_SIZE_IL,
    eZOMBIE_BOX_SIZE_H,
    eZOMBIE_BOX_SIZE_IH,
    eZOMBIE_BOX_SIZE_R,
    eZOMBIE_BOX_SIZE_LOCK,
    eZOMBIE_BOX_SIZE_UNLOCK,
    eZOMBIE_BOX_SIZE_MAX,
};


enum
{
    eZOMBIE_PLATFORM_SIZE_S=0,
    eZOMBIE_PLATFORM_SIZE_M,
    eZOMBIE_PLATFORM_SIZE_L,
    eZOMBIE_PLATFORM_SIZE_H,
    eZOMBIE_PLATFORM_SIZE_MAX,
};

enum
{
    eZOMBIE_TIRE_SIZE_S=0,
    eZOMBIE_TIRE_SIZE_M,
    eZOMBIE_TIRE_SIZE_L,
    eZOMBIE_TIRE_SIZE_MAX,
};

enum
{
    eZOMBIE_RISE_SIZE_S=0,
    eZOMBIE_RISE_SIZE_M,
    eZOMBIE_RISE_SIZE_L,
    eZOMBIE_RISE_SIZE_MAX,
};

enum
{
    eZOMBIE_BOM_SIZE_S=0,
    eZOMBIE_BOM_SIZE_M,
    eZOMBIE_BOM_SIZE_MAX,
};

enum
{
    eZOMBIE_BOX_LEVEL_1 = 0,
    eZOMBIE_BOX_LEVEL_2,
    eZOMBIE_BOX_LEVEL_3,
    eZOMBIE_BOX_LEVEL_4,
    eZOMBIE_BOX_LEVEL_5,
    eZOMBIE_BOX_LEVEL_6,
    eZOMBIE_BOX_LEVEL_7,
    eZOMBIE_BOX_LEVEL_8,
    eZOMBIE_BOX_LEVEL_9,    
    eZOMBIE_BOX_LEVEL_10,
    eZOMBIE_BOX_LEVEL_11,
    eZOMBIE_BOX_LEVEL_12,
    eZOMBIE_BOX_LEVEL_13,
    eZOMBIE_BOX_LEVEL_14,
    eZOMBIE_BOX_LEVEL_15,
    eZOMBIE_BOX_LEVEL_16,
    eZOMBIE_BOX_LEVEL_17,
    eZOMBIE_BOX_LEVEL_18,
    eZOMBIE_BOX_LEVEL_19,    
    eZOMBIE_BOX_LEVEL_20,
    eZOMBIE_BOX_LEVEL_21,
    eZOMBIE_BOX_LEVEL_22,
    eZOMBIE_BOX_LEVEL_23,
    eZOMBIE_BOX_LEVEL_24,
    eZOMBIE_BOX_LEVEL_25,
    eZOMBIE_BOX_LEVEL_26,
    eZOMBIE_BOX_LEVEL_27,
    eZOMBIE_BOX_LEVEL_28,
    eZOMBIE_BOX_LEVEL_29,    
    eZOMBIE_BOX_LEVEL_30,
    eZOMBIE_BOX_LEVEL_MAX
};


enum
{
    eZOMBIE_ACTOR_ZOMBIE,
    eZOMBIE_ACTOR_ZOMBIE_ANIM_DEAD,        
    eZOMBIE_ACTOR_BOX,
    eZOMBIE_ACTOR_PLATFORM=eZOMBIE_ACTOR_BOX+eZOMBIE_BOX_SIZE_MAX,
    eZOMBIE_ACTOR_TIRE=eZOMBIE_PLATFORM_SIZE_MAX+eZOMBIE_ACTOR_PLATFORM,
    eZOMBIE_ACTOR_RISE=eZOMBIE_TIRE_SIZE_MAX+eZOMBIE_ACTOR_TIRE,
    eZOMBIE_ACTOR_BOM=eZOMBIE_RISE_SIZE_MAX+eZOMBIE_ACTOR_RISE,
    eZOMBIE_ACTOR_EXPLOSION=eZOMBIE_BOM_SIZE_MAX+eZOMBIE_ACTOR_BOM,
    eZOMBIE_ACTOR_BOX_LEVEL,        
    eZOMBIE_ACTOR_SEGEMNT=eZOMBIE_ACTOR_BOX_LEVEL+eZOMBIE_BOX_LEVEL_MAX,
    eZOMBIE_ACTOR_NODE_MAX,
};
typedef mgl_u16 eZOMBIE_ACTOR_TYPE;

enum
{
    eZOMBIE_SOUND_BTN_PRESS,
    eZOMBIE_SOUND_TIRE_ELASTC,
    eZOMBIE_SOUND_ZOMBIE_DIE,
    eZOMBIE_SOUND_EXPLOSION,
    eZOMBIE_SOUND_BOX_ELIMINATE,
    eZOMBIE_SOUND_MAX,
};
typedef pgl_u16 eZOMBIE_SOUND_TYPE;

enum
{
    eZOMBIE_GUI_BUTTON_START = 0,
    eZOMBIE_GUI_BUTTON_MENU,
    eZOMBIE_GUI_BUTTON_RESTART,
    eZOMBIE_GUI_BUTTON_LEVEL,
    eZOMBIE_GUI_BUTTON_SOUND,
#ifdef ZOMBIEGAME_ON_CMODEL
    eZOMBIE_GUI_BUTTON_FLASHING,
#endif
    eZOMBIE_GUI_BUTTON_PREVIOUS,
    eZOMBIE_GUI_BUTTON_NEXT,
	eZOMBIE_GUI_BUTTON_NULL,
    eZOMBIE_GUI_BUTTON_MAX
};
typedef pgl_u16 eZOMBIE_BUTTON_TYPE;


enum
{
    //BG...
    eZOMBIE_GUI_MAINMENU_SCENE_BG = eZOMBIE_ACTOR_NODE_MAX,
    eZOMBIE_GUI_LEVELMENU_SCENE_BG,
    //BUTTON
    eZOMBIE_GUI_BUTTON,
    //IMAGE...
    eZOMBIE_GUI_IMAGE_FAIL = eZOMBIE_GUI_BUTTON + eZOMBIE_GUI_BUTTON_MAX * 2,
    eZOMBIE_GUI_IMAGE_COMPLETE,
    eZOMBIE_GUI_IMAGE_0,
    eZOMBIE_GUI_IMAGE_1,
    eZOMBIE_GUI_IMAGE_2,
    eZOMBIE_GUI_IMAGE_3,
    eZOMBIE_GUI_IMAGE_4,
    eZOMBIE_GUI_IMAGE_5,
    eZOMBIE_GUI_IMAGE_6,
    eZOMBIE_GUI_IMAGE_7,
    eZOMBIE_GUI_IMAGE_8,
    eZOMBIE_GUI_IMAGE_9,
    eZOMBIE_GUI_IMAGE_LEVEL,
    eZOMBIE_GUI_ZOMBIE_JUMP_1,
    eZOMBIE_GUI_ZOMBIE_JUMP_2,
    eZOMBIE_GUI_ZOMBIE_JUMP_3,
    eZOMBIE_GUI_ZOMBIE_JUMP_4,
    eZOMBIE_GUI_ZOMBIE_DOWN_1,    
    eZOMBIE_GUI_ZOMBIE_DOWN_2,
    eZOMBIE_GUI_ZOMBIE_DOWN_3,
    eZOMBIE_GUI_ZOMBIE_DOWN_4,
    eZOMBIE_GUI_ZOMBIE_HELP_1,    
    eZOMBIE_GUI_ZOMBIE_HELP_2,
    eZOMBIE_GUI_ZOMBIE_HELP_3,
    eZOMBIE_GUI_ZOMBIE_HELP_4,    
    eZOMBIE_GUI_LIGHT_ANIM_LEFT,
    eZOMBIE_GUI_LIGHT_ANIM_RIGHT, 
    eZOMBIE_GUI_ANIM_FLAG,
    eZOMBIE_GUI_MAINMENU_SCENE_MAX,
};
typedef mgl_u16 eZOMBIE_GUI_TYPE;

#define     ZOMBIE_MAX_TEXTURE_NUM     eZOMBIE_GUI_MAINMENU_SCENE_MAX
/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void Zombie_Prepare_AllResID(void *pApplet);
hActor Zombie_Add_Actor(void *pApplet, SceneHandleID SceneID, eZOMBIE_ACTOR_TYPE  NodeType, 
				pgl_u8 NodeSize, pgl_float NodePosX, pgl_float NodePosY, PglActorTouchesCBFunc_t *pActorTouchCB);
pgl_void Zombie_Add_AddSeg(EngineHandleID engineID, SceneHandleID SceneID);
hGuiActor Zombie_AddButtonNode(void *pApplet, SceneHandleID SceneID,
                               eZOMBIE_BUTTON_TYPE eBtnType, 
                               pgl_float GuiPosX, pgl_float GuiPosY, 
                               mgl_float GuiWidth, pgl_float GuiHeight,
                                  GuiActorTouchesCBFunc_t  *pGUITouchCB);
hGuiActor Zombie_AddImageNode(void *pApplet, SceneHandleID SceneID, eZOMBIE_GUI_TYPE NodeType, pgl_float GuiPosX, pgl_float GuiPosY, pgl_float GuiWidth, pgl_float GuiHeight);
hGuiActor Zombie_AddAnimateImageNode(void *pApplet, SceneHandleID SceneID, eZOMBIE_GUI_TYPE eNodeType, pgl_float GuiPosX, pgl_float GuiPosY, mgl_float GuiWidth, pgl_float GuiHeight);
pgl_void Zombie_PlaySound(void *pApplet, pgl_u16 nIdx);
#endif //__MMI_ZOMBIEGAME_ACTORS__
