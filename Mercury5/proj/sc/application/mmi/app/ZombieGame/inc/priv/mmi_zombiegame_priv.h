////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
* @file    mmi_zombiegame_priv.h
* @version
* @brief   ZombieGame applet private header file
*
*/

#ifndef __MMI_ZOMBIEGAME_PRIV_H__
#define __MMI_ZOMBIEGAME_PRIV_H__

/*=============================================================*/
// Platform definition
/*=============================================================*/
#ifdef C_MODEL
    #define ZOMBIEGAME_ON_CMODEL
#else
    #define ZOMBIEGAME_ON_MAE_PLATFORM
#endif

/*=============================================================*/
// Include files
/*=============================================================*/

#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
#include "mmi_baseapplet.h"
#include "mmi_srv_audio.h"
#include "mmi_log.h"
#include "mmi_layout.h"
#include "mmi_srv_audioenv.h"
#include "mmi_srv_cfg.h"
#include "mmi_common_cfg.h"
#include "ZombieGame_resource.h"
#else
//Commnet to avoid abuse api check
//#include "WinMain.h"
#endif

#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"
#include "mgl_Scene_Environment.h"
#include "mmi_pgl_headers.h"
#include "mmi_zombiegame_actors.h"

/*=============================================================*/
// Zombie Game Layout Definitions
/*=============================================================*/
#ifdef ZOMBIEGAME_ON_CMODEL
#define RS_MAIN_LCD_WIDTH                                               (MAIN_LCD_WIDTH)
#define RS_MAIN_LCD_HEIGHT                                              (MAIN_LCD_HEIGHT)
#define MMI_LEVEL_23                                                    (23)                                                       
typedef void                                                            IApplet;
#endif

#define ZOMBIE_ZOMBIE_CHARACTER_WIDTH                                   (48.0f)
#define ZOMBIE_ZOMBIE_CHARACTER_HEIGHT                                  (48.0f)
//Box
#define ZOMBIE_QUAD_SMALL_BOX_WIDTH                                     (32.0f)
#define ZOMBIE_QUAD_SMALL_BOX_HEIGHT                                    (32.0f)
#define ZOMBIE_QUAD_MIDDLE_BOX_WIDTH                                    (64.0f)
#define ZOMBIE_QUAD_MIDDLE_BOX_HEIGHT                                   (64.0f)
#define ZOMBIE_HORIZONTAL_MIDDLE_BOX_WIDTH                              (64.0f)
#define ZOMBIE_HORIZONTAL_MIDDLE_BOX_HEIGHT                             (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_HORIZONTAL_LARGE_BOX_WIDTH                               (96.0f)
#define ZOMBIE_HORIZONTAL_LARGE_BOX_HEIGHT                              (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_HORIZONTAL_HUGE_BOX_WIDTH                                (128.0f)
#define ZOMBIE_HORIZONTAL_HUGE_BOX_HEIGHT                               (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_VERTICAL_MIDDLE_BOX_WIDTH                                (ZOMBIE_QUAD_SMALL_BOX_WIDTH)
#define ZOMBIE_VERTICAL_MIDDLE_BOX_HEIGHT                               (64.0f)
#define ZOMBIE_VERTICAL_LARGE_BOX_WIDTH                                 (ZOMBIE_QUAD_SMALL_BOX_WIDTH)
#define ZOMBIE_VERTICAL_LARGE_BOX_HEIGHT                                (96.0f)
#define ZOMBIE_VERTICAL_HUGE_BOX_WIDTH                                  (ZOMBIE_QUAD_SMALL_BOX_WIDTH)
#define ZOMBIE_VERTICAL_HUGE_BOX_HEIGHT                                 (128.0f)
//Platform
#define ZOMBIE_PLATFORM_SMALL_WIDTH                                     (32.0f)
#define ZOMBIE_PLATFORM_SMALL_HEIGHT                                    (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_PLATFORM_MIDDLE_WIDTH                                    (64.0f)
#define ZOMBIE_PLATFORM_MIDDLE_HEIGHT                                   (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_PLATFORM_LARGE_WIDTH                                     (96.0f)
#define ZOMBIE_PLATFORM_LARGE_HEIGHT                                    (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_PLATFORM_HUGE_WIDTH                                      (128.0f)
#define ZOMBIE_PLATFORM_HUGE_HEIGHT                                     (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
//Tire
#define ZOMBIE_TIRE_SMALL_WIDTH                                         (32.0f)
#define ZOMBIE_TIRE_SMALL_HEIGHT                                        (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_TIRE_MIDDLE_WIDTH                                        (64.0f)
#define ZOMBIE_TIRE_MIDDLE_HEIGHT                                       (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_TIRE_LARGE_WIDTH                                         (96.0f)
#define ZOMBIE_TIRE_LARGE_HEIGHT                                        (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_TIRE_HUGE_WIDTH                                          (128.0f)
#define ZOMBIE_TIRE_HUGE_HEIGHT                                         (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
//Balloon
#define ZOMBIE_BALLOON_SMALL_WIDTH                                      (32.0f)
#define ZOMBIE_BALLOON_SMALL_HEIGHT                                     (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_BALLOON_MIDDLE_WIDTH                                     (64.0f)
#define ZOMBIE_BALLOON_MIDDLE_HEIGHT                                    (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_BALLOON_LARGE_WIDTH                                      (96.0f)
#define ZOMBIE_BALLOON_LARGE_HEIGHT                                     (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_BALLOON_HUGE_WIDTH                                       (128.0f)
#define ZOMBIE_BALLOON_HUGE_HEIGHT                                      (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
//Bomb
#define ZOMBIE_BOMB_SMALL_WIDTH                                         (32.0f)
#define ZOMBIE_BOMB_SMALL_HEIGHT                                        (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_BOMB_MIDDLE_WIDTH                                        (64.0f)
#define ZOMBIE_BOMB_MIDDLE_HEIGHT                                       (ZOMBIE_QUAD_SMALL_BOX_HEIGHT)
#define ZOMBIE_BOMB_EXPLOSION_WIDTH                                     (64.0f)
#define ZOMBIE_BOMB_EXPLOSION_HEIGHT                                    (64.0f)
//Button
#define ZOMBIE_BUTTON_START_WIDTH                                       (160.0f)
#define ZOMBIE_BUTTON_START_HEIGHT                                      (26.0f)
#define ZOMBIE_BUTTON_FLASHING_WIDTH                                    (116.0f)
#define ZOMBIE_BUTTON_FLASHING_HEIGHT                                   (126.0f)
#define ZOMBIE_BUTTON_FLASHING_POS_X                                    (480 - ZOMBIE_BUTTON_FLASHING_WIDTH)
#define ZOMBIE_BUTTON_FLASHING_POS_Y                                    (0)

#define ZOMBIE_BUTTON_LEVEL_WIDTH                                       (30.0f)
#define ZOMBIE_BUTTON_LEVEL_HEIGHT                                      (30.0f)
#define ZOMBIE_BUTTON_LEVEL_POS_X                                       (10.0f)
#define ZOMBIE_BUTTON_LEVEL_POS_Y                                       (320 - ZOMBIE_BUTTON_LEVEL_HEIGHT - 5.0f)

#define ZOMBIE_BUTTON_MENU_WIDTH                                        (ZOMBIE_BUTTON_LEVEL_WIDTH)
#define ZOMBIE_BUTTON_MENU_HEIGHT                                       (ZOMBIE_BUTTON_LEVEL_HEIGHT)
#define ZOMBIE_BUTTON_MENU_POS_X                                        (ZOMBIE_BUTTON_LEVEL_POS_X + ZOMBIE_BUTTON_LEVEL_WIDTH + 10)
#define ZOMBIE_BUTTON_MENU_POS_Y                                        (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_BUTTON_PREVIOUS_WIDTH                                    (ZOMBIE_BUTTON_LEVEL_WIDTH)
#define ZOMBIE_BUTTON_PREVIOUS_HEIGHT                                   (ZOMBIE_BUTTON_LEVEL_HEIGHT)
#define ZOMBIE_BUTTON_PREVIOUS_POS_X                                    (130.0f)
#define ZOMBIE_BUTTON_PREVIOUS_POS_Y                                    (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_IMAGE_LEVEL_WIDTH                                        (66.0f)
#define ZOMBIE_IMAGE_LEVEL_HEIGHT                                       (26.0f)
#define ZOMBIE_IMAGE_LEVEL_POS_X                                        (ZOMBIE_BUTTON_PREVIOUS_POS_X + ZOMBIE_BUTTON_PREVIOUS_WIDTH + 25)
#define ZOMBIE_IMAGE_LEVEL_POS_Y                                        (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_IMAGE_LEVEL_NUM_WIDTH                                    (24.0f)
#define ZOMBIE_IMAGE_LEVEL_NUM_HEIGHT                                   (28.0f)
#define ZOMBIE_IMAGE_LEVEL_NUM1_POS_X                                   (ZOMBIE_IMAGE_LEVEL_POS_X + ZOMBIE_IMAGE_LEVEL_WIDTH + 5)
#define ZOMBIE_IMAGE_LEVEL_NUM2_POS_X                                   (ZOMBIE_IMAGE_LEVEL_NUM1_POS_X + ZOMBIE_IMAGE_LEVEL_NUM_WIDTH)
#define ZOMBIE_IMAGE_LEVEL_NUM_POS_Y                                    (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_BUTTON_NEXT_WIDTH                                        (ZOMBIE_BUTTON_PREVIOUS_WIDTH)
#define ZOMBIE_BUTTON_NEXT_HEIGHT                                       (ZOMBIE_BUTTON_PREVIOUS_HEIGHT)
#define ZOMBIE_BUTTON_NEXT_POS_X                                        (320.0f)
#define ZOMBIE_BUTTON_NEXT_POS_Y                                        (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_BUTTON_SOUND_WIDTH                                       (ZOMBIE_BUTTON_PREVIOUS_WIDTH)
#define ZOMBIE_BUTTON_SOUND_HEIGHT                                      (ZOMBIE_BUTTON_PREVIOUS_HEIGHT)
#define ZOMBIE_BUTTON_SOUND_POS_X                                       (ZOMBIE_BUTTON_NEXT_POS_X + 2 * ZOMBIE_BUTTON_NEXT_WIDTH + 15)
#define ZOMBIE_BUTTON_SOUND_POS_Y                                       (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_BUTTON_RESTART_WIDTH                                     (ZOMBIE_BUTTON_PREVIOUS_WIDTH)
#define ZOMBIE_BUTTON_RESTART_HEIGHT                                    (ZOMBIE_BUTTON_PREVIOUS_HEIGHT)
#define ZOMBIE_BUTTON_RESTART_POS_X                                     (ZOMBIE_BUTTON_SOUND_POS_X + ZOMBIE_BUTTON_SOUND_WIDTH + 10)
#define ZOMBIE_BUTTON_RESTART_POS_Y                                     (ZOMBIE_BUTTON_LEVEL_POS_Y)

#define ZOMBIE_IMAGE_COMPLETE_WIDTH                                     (380.0f)
#define ZOMBIE_IMAGE_COMPLETE_HEIGHT                                    (106.0f)
#define ZOMBIE_IMAGE_COMPLETE_POS_X                                     ((480 - ZOMBIE_IMAGE_COMPLETE_WIDTH)/2)
#define ZOMBIE_IMAGE_COMPLETE_POS_Y                                     ((320 - ZOMBIE_IMAGE_COMPLETE_HEIGHT)/2)

#define ZOMBIE_IMAGE_FAIL_WIDTH                                         (188.0f)
#define ZOMBIE_IMAGE_FAIL_HEIGHT                                        (104.0f)
#define ZOMBIE_IMAGE_FAIL_POS_X                                         ((480 - ZOMBIE_IMAGE_FAIL_WIDTH)/2)
#define ZOMBIE_IMAGE_FAIL_POS_Y                                         ((320 - ZOMBIE_IMAGE_FAIL_HEIGHT)/2)


//Zombie Animation
#define ZOMBIE_IMAGE_JUMP_WIDTH                                         (90)
#define ZOMBIE_IMAGE_JUMP_HEIGHT                                        (144)
#define ZOMBIE_IMAGE_JUMP_GROUND_Y                                      (320 - ZOMBIE_IMAGE_JUMP_HEIGHT - 30)
#define ZOMBIE_IMAGE_JUMP_MAX_Y                                         (ZOMBIE_IMAGE_JUMP_GROUND_Y)
#define ZOMBIE_IMAGE_JUMP_MIN_Y                                         (ZOMBIE_IMAGE_JUMP_MAX_Y - 50)
#define ZOMBIE_IMAGE_JUMP_Y_STEP                                        (20)

#define ZOMBIE_IMAGE_FLAG_WIDTH                                         (106)
#define ZOMBIE_IMAGE_FLAG_HEIGHT                                        (46)
#define ZOMBIE_IMAGE_FLAG_POS_X                                         (23)
#define ZOMBIE_IMAGE_FLAG_POS_Y                                         (10)

#define ZOMBIE_IMAGE_LIGHT_WIDTH                                        (24)
#define ZOMBIE_IMAGE_LIGHT_HEIGHT                                       (60)
#define ZOMBIE_IMAGE_LEFT_LIGHT_POS_X                                   (160.0f)
#define ZOMBIE_IMAGE_LEFT_LIGHT_POS_Y                                   (150.0f)
#define ZOMBIE_IMAGE_RIGHT_LIGHT_POS_X                                  (410.0f)
#define ZOMBIE_IMAGE_RIGHT_LIGHT_POS_Y                                  (150.0f)

#define ZOMBIE_IMAGE_HELP_WIDTH                                         (76)
#define ZOMBIE_IMAGE_HELP_HEIGHT                                        (62)
#define ZOMBIE_IMAGE_HELP1_POS_X                                        (90)
#define ZOMBIE_IMAGE_HELP1_POS_Y                                        (130)
#define ZOMBIE_IMAGE_HELP2_POS_X                                        (90)
#define ZOMBIE_IMAGE_HELP2_POS_Y                                        (235)
#define ZOMBIE_IMAGE_HELP3_POS_X                                        (315)
#define ZOMBIE_IMAGE_HELP3_POS_Y                                        (215)
#define ZOMBIE_IMAGE_HELP4_POS_X                                        (480 - ZOMBIE_IMAGE_HELP_WIDTH - ZOMBIE_BUTTON_FLASHING_WIDTH)
#define ZOMBIE_IMAGE_HELP4_POS_Y                                        (20)

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MAX_ZOMBIE_LEVEL            30
#define MMI_LEVEL_ZOMBIEGAME 	    MMI_LEVEL_23
#define ZOMBIEGAME_UPDATE_PERIOD    5
#define ZOMBIEGAME_ENGINE_FPS       20
#define ZOMBIE_PLAYSCENE_OFFSET_Y  (45)
#define ZOMBIE_FLAG_ANIM_DURATION  (50)

#if defined(__LCM_QVGA_240_320_MMI__)
#define SIZE_SCALE_RATIO 0.675f
#define WIDTH_SCALE_RATIO 0.6666f
#define HEIGHT_SCALE_RATIO 0.75f

#define ZOMBIE_IMAGE_CLOUD_WIDTH                                        (267)
#define ZOMBIE_IMAGE_CLOUD_HEIGHT                                       (80)
#define ZOMBIE_IMAGE_CLOUD_INIT_POS_X                                   (-ZOMBIE_IMAGE_CLOUD_WIDTH)
#define ZOMBIE_IMAGE_CLOUD_POS_Y                                        (0)

#endif

#if defined(__LCM_WQVGA_240_400_MMI__)
#define SIZE_SCALE_RATIO 0.78f
#define WIDTH_SCALE_RATIO 0.8333f
#define HEIGHT_SCALE_RATIO 0.75f

#define ZOMBIE_IMAGE_CLOUD_WIDTH                                        (304)
#define ZOMBIE_IMAGE_CLOUD_HEIGHT                                       (80)
#define ZOMBIE_IMAGE_CLOUD_INIT_POS_X                                   (-ZOMBIE_IMAGE_CLOUD_WIDTH)
#define ZOMBIE_IMAGE_CLOUD_POS_Y                                        (0)

#endif

#if defined(__LCM_HVGA_320_480_MMI__)
#define SIZE_SCALE_RATIO 1.0f
#define WIDTH_SCALE_RATIO 1.0f
#define HEIGHT_SCALE_RATIO 1.0f

#define ZOMBIE_IMAGE_CLOUD_WIDTH                                        (406)
#define ZOMBIE_IMAGE_CLOUD_HEIGHT                                       (116)
#define ZOMBIE_IMAGE_CLOUD_INIT_POS_X                                   (-ZOMBIE_IMAGE_CLOUD_WIDTH)
#define ZOMBIE_IMAGE_CLOUD_POS_Y                                        (0)

#endif

/*=============================================================*/
// Enumeration definition
/*=============================================================*/

enum
{
    eZOMBIE_SCENE_MAIN = 0, 
    eZOMBIE_SCENE_LEVEL, 
    eZOMBIE_SCENE_GAME,
    eZOMBIE_SCENE_END,
    eZOMBIE_SCENE_MAX,
} ;
typedef pgl_u16 eZombieSceneType;

enum
{
    eZOMBIE_ANIM_ZOMBIE_1,
    eZOMBIE_ANIM_ZOMBIE_2,
    eZOMBIE_ANIM_ZOMBIE_3,
    eZOMBIE_ANIM_ZOMBIE_4,
    eZOMBIE_ANIM_ZOMBIE_MAX
};
typedef pgl_u16 eZOMBIE_ZOMBIE_NUM;

enum
{
    eZOMBIE_ANIM_ZOMBIE_GROUND,
    eZOMBIE_ANIM_ZOMBIE_JUMP,
    eZOMBIE_ANIM_ZOMBIE_DOWN,    
};
typedef pgl_u16 eZOMBIE_ANIM_TYPE;


/*=============================================================*/
// Data type definition
/*=============================================================*/

#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
typedef struct
{
    IWidget *pBgImgWdg;
    IWidget *pCloudImgWdg;
    IWidget *pFlashBtnWdg;    
}ZombieGameWdgList;

typedef struct ZombieGameWndData_t_
{
    ZombieGameWdgList tWdgList;
} ZombieGameWndData_t;
#endif

typedef struct
{
#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
    APPLET_BASE_ELEMENTS;
    AudioEnvSrvVolLevel_e eCurVolume;
	pgl_u8 				nFlagAnimIdx;
#endif
	SceneHandleID 		sceneId[eZOMBIE_SCENE_MAX];
	pgl_u8 		u8CurLevID;
	pgl_u8 		u8PassedLevID;                                                //Should come from .cfg....

	hActor actorLevelBox[MAX_ZOMBIE_LEVEL];  
	//pgl_boolean   sg_Zombie_LevisPass[MAX_ZOMBIE_LEVEL];
    EngineHandleID engineID;
	hActorCosHandler bWinhandle;// = PGL_COSHANDLER_NULL;
	hGuiActor 	actorOption[eZOMBIE_GUI_BUTTON_MAX];
	pgl_u8		u8BoxCNT;// =0;
	pgl_boolean bOnPlatform;
	pgl_boolean bPass;
    eZOMBIE_ANIM_TYPE     bZombieAnimStatus[eZOMBIE_ANIM_ZOMBIE_MAX];
    pgl_float   fZombieYPos[eZOMBIE_ANIM_ZOMBIE_MAX];
    hActor  hZombieActor;
    hActor  hPlatformActor;
    hGuiActor hHelpActor;
	
	hTexRes texResID[ZOMBIE_MAX_TEXTURE_NUM];// = {0};
	boolean bSuspendMode;
    boolean bDraw;
    boolean bSound;
} ZombieGameAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
MAE_Ret ZombieGameConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret ZombieGameDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameTouchCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean ZombieGameGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);
boolean ZombieGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#endif /* __MMI_ZOMBIEGAME_PRIV_H__ */
