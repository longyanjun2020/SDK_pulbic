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
//*-----------------------------------------------------------------------------
//* FILE
//*      mmi_fishfurygame_actors.h
//*
//*
//* HISTORY
//*      2012.01.05       Andy Wang         Initial Version
//*
//*-----------------------------------------------------------------------------*/

/**
* @file    mmi_fishfurygame_actors.h
* @version
* @brief   FishFuryGame applet actor info header file
*
*/

#ifndef __MMI_FISHFURYGAME_ACTORS__
#define __MMI_FISHFURYGAME_ACTORS__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_headers.h"
#ifdef FISHFURYGAME_ON_MAE_PLATFORM
#include "FishFuryGame_resource.h"
#endif
/*------------------------------------------------------------------------------
Macro define
-------------------------------------------------------------------------------*/
#define HIGHSCORE_TEX_WIDTH         (96.0f)
#define HIGHSCORE_TEX_HEIGHT        (30.0f)

#define SCORE_TEX_WIDTH             (64.0f)
#define SCORE_TEX_HEIGHT            (32.0f)

#define NUMBER_TEX_WIDTH            (22.0f)
#define NUMBER_TEX_HEIGHT           (22.0f)

#define HELP_ICON_WIDTH             (36.0f)
#define HELP_ICON_HEIGHT            (36.0f)
#define HELP_WIDTH             (340.0f)
#define HELP_HEIGHT            (228.0f)
#define HELP_POS_X                  (70.0f)
#define HELP_POS_Y                  (46.0f)
#define MAIN_HELP_POS_X             (72.0f)
#define MAIN_HELP_POS_Y             (275.0f)


#define GAMEOVER_ICON_WIDTH         (340.0f)
#define GAMEOVER_ICON_HEIGHT        (228.0f)
#define GAMEOVER_POS_X              (70.0f)
#define GAMEOVER_POS_Y              (46.0f)

#define MENU_ICON_WIDTH             (54.0f)
#define MENU_ICON_HEIGHT            (54.0f)

#define GAMEOVER_MENU_POS_X         (123.0f)
#define GAMEOVER_MENU_POS_Y         (198.0f)
#define MENU_POS_X                  (40.0f)
#define MENU_POS_Y                  (31.0f)
#define MENU_ICON_SIZE              (64.0f)
#define MENU_X_SHIFT                (20.0f)
#define MENU_Y_SHIFT                (20.0f)

#define REPLAY_ICON_WIDTH           (54.0f)
#define REPLAY_ICON_HEIGHT          (54.0f)
#define REPLAY_POS_X                (213.0f)
#define REPLAY_POS_Y                (198.0f)

#define NEXT_ICON_WIDTH             (54.0f)
#define NEXT_ICON_HEIGHT            (54.0f)
#define NEXT_POS_X                  (303.0f)
#define NEXT_POS_Y                  (198.0f)

#define MENU_RETURN_POS_X           (20.0f)
#define MENU_RETURN_POS_Y           (275.0f)
#define MENU_RETURN_SIZE            (36.0f)

#define PLAYSCENE_PAUSE_ICON_SIZE   (36.0f)
#define PAUSE_POS_X                 (20.0f)
#define PAUSE_POS_Y                 (9.0f)

#define SCOREWORD_POS_X     (370.0f)
#define SCOREWORD_POS_Y     (10.0f)
#define SCOREWORD_W         (38.0f)
#define SCOREWORD_H         (14.0f)
#define SCORE_POS_X             (370.0f)
#define SCORE_POS_Y             (30.0f)
#define SCORE_W                     (18.0f)
#define SCORE_H                     (18.0f)
#define SCORE_SPACE                     (20.0f)

#define HIGHSCOREWORD_POS_X     (370.0f)
#define HIGHSCOREWORD_POS_Y     (60.0f)
#define HIGHSCOREWORD_W         (64.0f)
#define HIGHSCOREWORD_H         (14.0f)
#define HIGHSCORE_POS_X             (370.0f)
#define HIGHSCORE_POS_Y             (80.0f)
#define HIGHSCORE_W                     (18.0f)
#define HIGHSCORE_H                     (18.0f)
#define HIGHSCORE_SPACE                     (20.0f)

#define PAUSE_ICON_SIZE             (50.0f)
#define PAUSE_PLAY_ICON_POS_X       (30.0f)
#define PAUSE_PLAY_ICON_POS_Y       (22.0f)
#define PAUSE_SOUND_ICON_POS_X      (30.0f)
#define PAUSE_SOUND_ICON_POS_Y      (82.0f)
#define PAUSE_MENU_ICON_POS_X       (30.0f)
#define PAUSE_MENU_ICON_POS_Y       (142.0f)
#define PAUSE_REPLAY_ICON_POS_X     (30.0f)
#define PAUSE_REPLAY_ICON_POS_Y     (202.0f)

#define PLAY_SCENE_GROUND_POS_Y     (270.0f)


/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
enum
{
    eFISHFURY_ACTOR_FISH_1 = 0,
    eFISHFURY_ACTOR_FISH_2,
    eFISHFURY_ACTOR_FISH_3,
    eFISHFURY_ACTOR_FISH_4,
    eFISHFURY_ACTOR_FISH_5,
    eFISHFURY_ACTOR_FISH_6,
    eFISHFURY_ACTOR_BIRD_1,
    eFISHFURY_ACTOR_BIRD_2,
    eFISHFURY_ACTOR_BIRD_3,
    eFISHFURY_ACTOR_BIRD_4,
    eFISHFURY_ACTOR_BIRD_5,
    eFISHFURY_ACTOR_BIRD_6,
    eFISHFURY_ACTOR_BIRD_7,
    eFISHFURY_ACTOR_BIRD_8,
    eFISHFURY_ACTOR_WOOD,
    eFISHFURY_ACTOR_ICE,
    eFISHFURY_ACTOR_ROCK,
    eFISHFURY_ACTOR_EGG,
    eFISHFURY_ACTOR_EGG_EXPLOSION,
    eFISHFURY_ACTOR_POOF,
    eFISHFURY_ACTOR_BALL,
    eFISHFURY_ACTOR_BOX,
    eFISHFURY_ACTOR_SEGEMNT,
    eFISHFURY_ACTOR_NODE_MAX,
};
typedef mgl_u16 eFISHFURY_ACTOR_TYPE;

enum
{
    //BG...
    eFISHFURY_GUI_START_BG = eFISHFURY_ACTOR_NODE_MAX,
    eFISHFURY_GUI_MENU_BG,
    eFISHFURY_GUI_PLAY_NULL_BG,
    eFISHFURY_GUI_PLAY_BG,
    eFISHFURY_GUI_GAMEOVER,
    eFISHFURY_GUI_BUTTON_HELP,
    eFISHFURY_GUI_BUTTON_HELP_PRESS,
    eFISHFURY_GUI_BUTTON_REPLAY_PRESS,
    eFISHFURY_GUI_BUTTON_REPLAY,
    eFISHFURY_GUI_BUTTON_NEXT_PRESS,
    eFISHFURY_GUI_BUTTON_NEXT,
    eFISHFURY_GUI_BUTTON_MENU_PRESS,
    eFISHFURY_GUI_BUTTON_MENU,
    eFISHFURY_GUI_BUTTON_STOP_PRESS,
    eFISHFURY_GUI_BUTTON_STOP,
    eFISHFURY_GUI_BUTTON_SOUND_CLOSE,
    eFISHFURY_GUI_BUTTON_SOUND,
    eFISHFURY_GUI_BUTTON_RESUME_PRESS,
    eFISHFURY_GUI_BUTTON_RESUME,
    eFISHFURY_GUI_BUTTON_PLAY_PRESS,
    eFISHFURY_GUI_BUTTON_PLAY,
    eFISHFURY_GUI_BUTTON_CONFIRM_PRESS,
    eFISHFURY_GUI_BUTTON_CONFIRM,
    eFISHFURY_GUI_BUTTON_BACK_PRESS,
    eFISHFURY_GUI_BUTTON_BACK,
    eFISHFURY_GUI_SCORE_0,
    eFISHFURY_GUI_SCORE_1,
    eFISHFURY_GUI_SCORE_2,
    eFISHFURY_GUI_SCORE_3,
    eFISHFURY_GUI_SCORE_4,
    eFISHFURY_GUI_SCORE_5,
    eFISHFURY_GUI_SCORE_6,
    eFISHFURY_GUI_SCORE_7,
    eFISHFURY_GUI_SCORE_8,
    eFISHFURY_GUI_SCORE_9,
    eFISHFURY_GUI_SCORE,
    eFISHFURY_GUI_HIGHSCORE,
    eFISHFURY_GUI_HELP_1,
    eFISHFURY_GUI_HELP_2,
    eFISHFURY_GUI_HELP_3,
    eFISHFURY_GUI_HELP_4,
    eFISHFURY_GUI_HELP_5,
    eFISHFURY_GUI_MENU_LOCK,
    eFISHFURY_GUI_MENU_NUMBER,
    eFISHFURY_GUI_MENU_NUMBER_PRESS,
    eFISHFURY_GUI_MENU_NUMBER_0,
    eFISHFURY_GUI_MENU_NUMBER_1,
    eFISHFURY_GUI_MENU_NUMBER_2,
    eFISHFURY_GUI_MENU_NUMBER_3,
    eFISHFURY_GUI_MENU_NUMBER_4,
    eFISHFURY_GUI_MENU_NUMBER_5,
    eFISHFURY_GUI_MENU_NUMBER_6,
    eFISHFURY_GUI_MENU_NUMBER_7,
    eFISHFURY_GUI_MENU_NUMBER_8,
    eFISHFURY_GUI_MENU_NUMBER_9,
    eFISHFURY_GUI_MENU_PAGE_WHITE,
    eFISHFURY_GUI_MENU_PAGE_BLACK,
    eFISHFURY_GUI_SLINGSHOT,
    eFISHFURY_GUI_SLINGSHOT_LINE1,
    eFISHFURY_GUI_SLINGSHOT_LINE2,
    eFISHFURY_GUI_SCENE_MAX,
};
typedef mgl_u16 eFISHFURY_GUI_TYPE;

#define     MAX_TEXTURE_NUM     eFISHFURY_GUI_SCENE_MAX

#ifdef FISHFURYGAME_ON_MAE_PLATFORM
static const u32 TEX_RESOURCE [MAX_TEXTURE_NUM] = 
{
    IMG_FISHFURY_FISH_1,
    IMG_FISHFURY_FISH_2, 
    IMG_FISHFURY_FISH_3,
    IMG_FISHFURY_FISH_4,
    IMG_FISHFURY_FISH_5, 
    IMG_FISHFURY_FISH_6,
    IMG_FISHFURY_BIRD_1,
    IMG_FISHFURY_BIRD_4,
    IMG_FISHFURY_BIRD_3, 
    IMG_FISHFURY_BIRD_2,
    IMG_FISHFURY_BIRD_5,
    IMG_FISHFURY_BIRD_6,
    IMG_FISHFURY_BIRD_7,
    IMG_FISHFURY_BIRD_8,
    IMG_FISHFURY_WOOD,
    IMG_FISHFURY_ICE,
    IMG_FISHFURY_STONE,
    IMG_FISHFURY_EGG, 
    IMG_FISHFURY_EGG_EXPLOSION, 
    IMG_FISHFURY_POOF, 
    IMG_FISHFURY_BEACH_BALL,
    IMG_FISHFURY_BOX,
    IMG_NULL_ID,
    IMG_FISHFURY_START_BG,
    IMG_FISHFURY_MENU_BG,
    IMG_NULL_ID, 
    IMG_FISHFURY_PLAY_BG,
    IMG_FISHFURY_GAME_OVER,
    IMG_FISHFURY_BTN_HELP_UNPRESS,
    IMG_FISHFURY_BTN_HELP_PRESS,
    IMG_FISHFURY_BTN_REPLAY_PRESS,
    IMG_FISHFURY_BTN_REPLAY_UNPRESS,    
    IMG_FISHFURY_BTN_NEXT_PRESS,
    IMG_FISHFURY_BTN_NEXT_UNPRESS,    
    IMG_FISHFURY_BTN_MENU_PRESS,    
    IMG_FISHFURY_BTN_MENU_UNPRESS,    
    IMG_FISHFURY_BTN_STOP_PRESS,    
    IMG_FISHFURY_BTN_STOP_UNPRESS,    
    IMG_FISHFURY_BTN_SOUND_CLOSE,    
    IMG_FISHFURY_BTN_SOUND_OPEN,    
    IMG_FISHFURY_BTN_RESUME_PRESS,    
    IMG_FISHFURY_BTN_RESUME_UNPRESS,
    IMG_FISHFURY_BTN_PLAY_PRESS,
    IMG_FISHFURY_BTN_PLAY_UNPRESS,    
    IMG_FISHFURY_BTN_CONFIRM_PRESS,
    IMG_FISHFURY_BTN_CONFIRM_UNPRESS,    
    IMG_FISHFURY_BTN_BACK_PRESS,
    IMG_FISHFURY_BTN_BACK_UNPRESS,
    IMG_FISHFURY_SCORE_0,
    IMG_FISHFURY_SCORE_1,
    IMG_FISHFURY_SCORE_2,
    IMG_FISHFURY_SCORE_3,
    IMG_FISHFURY_SCORE_4,
    IMG_FISHFURY_SCORE_5,
    IMG_FISHFURY_SCORE_6,
    IMG_FISHFURY_SCORE_7,
    IMG_FISHFURY_SCORE_8,
    IMG_FISHFURY_SCORE_9,
    IMG_FISHFURY_SCORE,    
    IMG_FISHFURY_HIGHSCORE,
    IMG_FISHFURY_HELP_1,
    IMG_FISHFURY_HELP_2,
    IMG_FISHFURY_HELP_3,
    IMG_FISHFURY_HELP_4,
    IMG_FISHFURY_HELP_5,
    IMG_FISHFURY_MENU_LOCK,
    IMG_FISHFURY_MENU_NUMBER,
    IMG_FISHFURY_MENU_NUMBER_PRESS,
    IMG_FISHFURY_MENU_NUMBER_0,
    IMG_FISHFURY_MENU_NUMBER_1,
    IMG_FISHFURY_MENU_NUMBER_2,
    IMG_FISHFURY_MENU_NUMBER_3,
    IMG_FISHFURY_MENU_NUMBER_4,
    IMG_FISHFURY_MENU_NUMBER_5,
    IMG_FISHFURY_MENU_NUMBER_6,
    IMG_FISHFURY_MENU_NUMBER_7,
    IMG_FISHFURY_MENU_NUMBER_8,
    IMG_FISHFURY_MENU_NUMBER_9,
    IMG_FISHFURY_MENU_PAGE_WHITE,
    IMG_FISHFURY_MENU_PAGE_BLACK,
    IMG_FISHFURY_SLINGSHOT,
    IMG_NULL_ID,
    IMG_NULL_ID    
};

#else

static char* TEX_RESOURCE [MAX_TEXTURE_NUM] =
{
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_1.png",                     
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_2.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_3.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_4.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_5.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_FISH_6.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_1.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_4.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_3.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_2.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_5.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_6.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_7.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_BIRD_8.png",                 
    "./Games/FishfuryGame/image/IMG_FISHFURY_WOOD.png",                   
    "./Games/FishfuryGame/image/IMG_FISHFURY_ICE.png",                    
    "./Games/FishfuryGame/image/IMG_FISHFURY_STONE.png",                  
    "./Games/FishfuryGame/image/IMG_FISHFURY_EGG.png",                    
    "./Games/FishfuryGame/image/IMG_FISHFURY_EGG_EXPLOSION.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_POOF.png",                   
    "./Games/FishfuryGame/image/IMG_FISHFURY_BEACH_BALL.png",             
    "./Games/FishfuryGame/image/IMG_FISHFURY_BOX.png",                    
    "",
#if defined(__LCM_QVGA_240_320_MMI__)
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_START_BG.jpg",               
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_MENU_BG.jpg",                
    "",                         
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_PLAY_BG.jpg",
#endif
#if defined(__LCM_WQVGA_240_400_MMI__)
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_START_BG.jpg",               
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_MENU_BG.jpg",                
    "",                         
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_PLAY_BG.jpg",
#endif
#if defined(__LCM_HVGA_320_480_MMI__)
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_START_BG.jpg",               
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_MENU_BG.jpg",                
    "",                         
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_PLAY_BG.jpg",
#endif          
    "./Games/FishfuryGame/image/IMG_FISHFURY_GAME_OVER.png",              
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_HELP_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_HELP_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_REPLAY_PRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_REPLAY_UNPRESS.png",     
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_NEXT_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_NEXT_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_MENU_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_MENU_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_STOP_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_STOP_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_SOUND_CLOSE.png",        
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_SOUND_OPEN.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_RESUME_PRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_RESUME_UNPRESS.png",     
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_PLAY_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_PLAY_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_CONFIRM_PRESS.png",      
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_CONFIRM_UNPRESS.png",    
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_BACK_PRESS.png",         
    "./Games/FishfuryGame/image/IMG_FISHFURY_BTN_BACK_UNPRESS.png",       
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_0.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_1.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_2.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_3.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_4.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_5.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_6.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_7.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_8.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE_9.png",                
    "./Games/FishfuryGame/image/IMG_FISHFURY_SCORE.png",                  
    "./Games/FishfuryGame/image/IMG_FISHFURY_HIGHSCORE.png",
#if defined(__LCM_QVGA_240_320_MMI__)
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_HELP_1.png",                 
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_HELP_2.png",                 
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_HELP_3.png",                 
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_HELP_4.png",                 
    "./Games/FishfuryGame/image/QVGA/IMG_FISHFURY_HELP_5.png",                 
#endif
#if defined(__LCM_WQVGA_240_400_MMI__)
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_HELP_1.png",                 
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_HELP_2.png",                 
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_HELP_3.png",                 
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_HELP_4.png",                 
    "./Games/FishfuryGame/image/WQVGA/IMG_FISHFURY_HELP_5.png",                 
#endif
#if defined(__LCM_HVGA_320_480_MMI__)
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_HELP_1.png",                 
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_HELP_2.png",                 
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_HELP_3.png",                 
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_HELP_4.png",                 
    "./Games/FishfuryGame/image/HVGA/IMG_FISHFURY_HELP_5.png",                 
#endif    
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_LOCK.png",              
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER.png",            
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_PRESS.png",      
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_0.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_1.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_2.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_3.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_4.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_5.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_6.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_7.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_8.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_NUMBER_9.png",          
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_PAGE_WHITE.png",        
    "./Games/FishfuryGame/image/IMG_FISHFURY_MENU_PAGE_BLACK.png",        
    "./Games/FishfuryGame/image/IMG_FISHFURY_SLINGSHOT.png",              
    "",                         
    ""
};
#endif

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_void FishFury_Prepare_AllResID(void *pApplet);
hTexRes FishFury_Get_TexResID(void *pApplet, pgl_u8 idx);
hActor FishFury_Add_Actor(void *pUserData, SceneHandleID SceneID, eFISHFURY_ACTOR_TYPE  NodeType, pgl_float NodePosX, pgl_float NodePosY, pgl_float NodeWidth, pgl_float NodeHeight, PglActorTouchesCBFunc_t *pActorTouchCB);
pgl_void FishFury_Add_AddSeg(void *pUserData, SceneHandleID SceneID);
hGuiActor FishFury_AddGUINode(SceneHandleID SceneID, ePgl_Layer_Type elayer, eFISHFURY_GUI_TYPE  NodeType, 
                                  mgl_float GuiPosX, mgl_float GuiPosY, mgl_float GuiWidth, mgl_float GuiHeight,
                                  GuiActorTouchesCBFunc_t  *pGUITouchCB);
#endif
