/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      CutRopeAPI.h
*
*
* HISTORY
*      2011.08.31       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __CUTROPEAPI_INC__
#define __CUTROPEAPI_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
//#include "WinMain.h"
#include "mmi_baseapplet.h"
#include "mae_widgetbase.h"
#include "mgl_Core_Types.h"
#include "cutrope_resource.h"
#include "cutrope.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Layout
-------------------------------------------------------------------------------*/
#if defined(__LCM_HVGA_320_480_MMI__)
#define XRATIO (320.0f/240.0f)
#define YRATIO (480.0f/400.0f)
#define RATIO (410.0f/400.0f)
#define RATIO2 (440.0f/400.0f)
#define XRATIO2 (440.0f/400.0f)
#define YRATIO2 (440.0f/400.0f)
#define XSHIFT (30.0f)
#elif defined(__LCM_WQVGA_240_400_MMI__)
#define XRATIO (1.0f)
#define YRATIO (380.0f/400.0f)
#define RATIO (1.0f)
#define RATIO2 (1.0f)
#define XRATIO2 (1.0f)
#define YRATIO2 (1.0f)
#define XSHIFT (0.0f)
#elif defined(__LCM_QVGA_MMI__)
#define XRATIO (1.0f)
#define YRATIO (320.0f/400.0f)
#define RATIO (380.0f/400.0f)
#define RATIO2 (1.0f)
#define XRATIO2 (1.0f)
#define YRATIO2 (320.0f/400.0f)
#define XSHIFT (0.0f)
#else
#define XRATIO (1.0f)
#define YRATIO (1.0f)
#define RATIO (1.0f)
#define RATIO2 (1.0f)
#define XRATIO2 (1.0f)
#define YRATIO2 (1.0f)
#define XSHIFT (0.0f)
#endif
#define CROPE_SEGMENT_GAP   (10.0f*RATIO)
#define FLOOR_X (-200.0f*XRATIO)
#define FLOOR_Y (-200.0f*YRATIO)
#define FLOOR_WIDTH (1600.0f*XRATIO)
#define FLOOR_HEIGHT (10.0f*YRATIO)

#define BALL_Y_UP_THRESHOLD (50.0f*YRATIO)
#define BALL_Y_THRESHOLD (MAIN_LCD_HEIGHT)
#define BALL_X_STEP (2.0f*XRATIO)
#define BALL_Y_STEP (5.0f*YRATIO)

#define PLAY_X (60.0f*XRATIO)
#define PLAY_Y (200.0f*YRATIO)
#define PLAY_W (120.0f*XRATIO)
#define PLAY_H (60.0f*YRATIO)
#define HELP_X (60.0f*XRATIO)
#define HELP_Y (260.0f*YRATIO)
#define HELP_W (120.0f*XRATIO)
#define HELP_H (60.0f*YRATIO)
#define SOUND_X (200.0f*XRATIO)
#define SOUND_Y (40.0f*YRATIO)
#define SOUND_W (35.0f*XRATIO)
#define SOUND_H (35.0f*YRATIO)

#define COMP1_X (0.0f*XRATIO)
#define COMP1_Y (2.0f*YRATIO)
#define COMP1_W (100.0f*XRATIO)
#define COMP1_H (45.0f*YRATIO)
#define COMP1STAGE_X (45.0f*XRATIO)
#define COMP1STAGE_Y (10.0f*XRATIO)
#define COMP1STAGE_W (12.0f*XRATIO)
#define COMP1STAGE_H (24.0f*XRATIO)
#define COMP1STAGE_S (14.0f*XRATIO)
#define COMP2_X (140.0f*XRATIO)
#define COMP2_Y (2.0f*YRATIO)
#define COMP2_W (100.0f*XRATIO)
#define COMP2_H (45.0f*YRATIO)
#define COMP2TIME_X (165.0f*XRATIO)
#define COMP2TIME_Y (10.0f*XRATIO)
#define COMP2TIME_W (10.0f*XRATIO)
#define COMP2TIME_H (28.0f*XRATIO)
#define COMP2TIME_S (12.0f*XRATIO)
#define PAUSE_X (205.0f*XRATIO)
#define PAUSE_Y (365.0f*YRATIO)
#define PAUSE_W (30.0f*XRATIO)
#define PAUSE_H (30.0f*YRATIO)
#define STOPSCREEN_X (0.0f*XRATIO)
#define STOPSCREEN_Y (175.0f*YRATIO)
#define STOPSCREEN_W (240.0f*XRATIO)
#define STOPSCREEN_H (50.0f*YRATIO)
#define PAUSEAGAIN_X (20.0f*XRATIO)
#define PAUSEAGAIN_Y (185.0f*YRATIO)
#define PAUSEAGAIN_W (30.0f*XRATIO)
#define PAUSEAGAIN_H (30.0f*YRATIO)
#define PAUSEMENU_X (105.0f*XRATIO)
#define PAUSEMENU_Y (185.0f*YRATIO)
#define PAUSEMENU_W (30.0f*XRATIO)
#define PAUSEMENU_H (30.0f*YRATIO)
#define PAUSERESUME_X (190.0f*XRATIO)
#define PAUSERESUME_Y (185.0f*YRATIO)
#define PAUSERESUME_W (30.0f*XRATIO)
#define PAUSERESUME_H (30.0f*YRATIO)
#define STARSCORE_X (37.0f*XRATIO)
#define STARSCORE_Y (30.0f*YRATIO)
#define STARSCORE_W (12.0f*XRATIO)
#define STARSCORE_H (12.0f*YRATIO)
#define STARSCORE_SPACE (17.5f*XRATIO)

#define AGAIN_X (30.0f*XRATIO)
#define AGAIN_Y (290.0f*YRATIO)
#define AGAIN_W (50.0f*XRATIO)
#define AGAIN_H (50.0f*YRATIO)
#define NEXT_X (95.0f*XRATIO)
#define NEXT_Y (290.0f*YRATIO)
#define NEXT_W (50.0f*XRATIO)
#define NEXT_H (50.0f*YRATIO)
#define MENU_X (160.0f*XRATIO)
#define MENU_Y (290.0f*YRATIO)
#define MENU_W (50.0f*XRATIO)
#define MENU_H (50.0f*YRATIO)
#define RATE_X (20.0f*XRATIO)
#define RATE_Y (20.0f*YRATIO)
#define RATE_W (200.0f*XRATIO)
#define RATE_H (140.0f*YRATIO)
#define RATESTAR_X (50.0f*XRATIO)
#define RATESTAR_Y (140.0f*YRATIO)
#define RATESTAR_W (40.0f*XRATIO)
#define RATESTAR_H (40.0f*YRATIO)
#define RATESTAR_SPACE (45.0f*XRATIO)
#define TIMEICON_X (30.0f*XRATIO)
#define TIMEICON_Y (220.0f*YRATIO)
#define TIMEICON_W (80.0f*XRATIO)
#define TIMEICON_H (40.0f*YRATIO)
#define TIME_X (115.0f*XRATIO)
#define TIME_Y (220.0f*YRATIO)
#define TIME_W (18.0f*XRATIO)
#define TIME_H (40.0f*YRATIO)
#define TIME_SPACE (20.0f*XRATIO)

#define BACK_X (175.0f*XRATIO)
#define BACK_Y (320.0f*YRATIO)
#define BACK_W (55.0f*XRATIO)
#define BACK_H (55.0f*YRATIO)
#define STAGE_W (40.0f*XRATIO)
#define STAGE_H (40.0f*YRATIO)
#define STAGE_X1 (40.0f*XRATIO)
#define STAGE_X2 (100.0f*XRATIO)
#define STAGE_X3 (160.0f*XRATIO)
#define STAGE_Y1 (50.0f*YRATIO)
#define STAGE_Y2 (150.0f*YRATIO)
#define STAGE_Y3 (250.0f*YRATIO)
#define STAGEICON_W (50.0f*XRATIO)
#define STAGEICON_H (50.0f*YRATIO)
#define STAGEICON_X1 (35.0f*XRATIO)
#define STAGEICON_X2 (95.0f*XRATIO)
#define STAGEICON_X3 (155.0f*XRATIO)
#define STAGEICON_Y1 (45.0f*YRATIO)
#define STAGEICON_Y2 (145.0f*YRATIO)
#define STAGEICON_Y3 (245.0f*YRATIO)
#define STAGESTAR_SHIFT_X (-2.0f*XRATIO)
#define STAGESTAR_SHIFT_Y (42.0f*YRATIO)
#define STAGESTAR_W (13.0f*XRATIO)
#define STAGESTAR_H (13.0f*YRATIO)
#define STAGESTAR_SPACE (15.0f*XRATIO)
#define BALL_CLOSE_THRESHOLD_X (100.0f*XRATIO)
#define BALL_CLOSE_THRESHOLD_Y (100.0f*YRATIO)

#define THEME_X (48.0f*XRATIO)
#define THEME_Y (98.0f*YRATIO)
#define THEME_W (144.0f*XRATIO)
#define THEME_WS (180.0f*XRATIO)
#define THEME_H (163.0f*YRATIO)
#define THEME_X_SHIFT (15.0f*XRATIO)
#define THEME_X_THRESHOLD (50.0f*XRATIO)
#define TOTAL_X (80.0f*XRATIO)
#define TOTAL_Y (8.0f*YRATIO)
#define TOTAL_W (80.0f*XRATIO)
#define TOTAL_H (34.0f*YRATIO)
#define TOTALSTAR_X (165.0f*XRATIO)
#define TOTALSTAR_Y (10.0f*YRATIO)
#define TOTALSTAR_W (15.0f*XRATIO)
#define TOTALSTAR_H (30.0f*YRATIO)
#define TOTALSTAR_S (17.0f*YRATIO)
#define STAR_X (215.0f*XRATIO)
#define STAR_Y (15.0f*YRATIO)
#define STAR_W (20.0f*XRATIO)
#define STAR_H (20.0f*YRATIO)

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/
static const u32 TEX_RESOURCE [] = 
{
    img_startgame_candy,
    img_cutrope_force2,
    img_cutrope_force1,
    img_cutrope_bubble1,
    img_cutrope_bubble2,
    img_cutrope_bubble3,
    img_startgame_component3,
    img_cutrope_monster_1,
    img_cutrope_monster_2,
    img_cutrope_monster_3,
    img_cutrope_monster_4,
    img_cutrope_monster_5,
    img_cutrope_monster_6,
    img_cutrope_monster_7,
    img_cutrope_monster_8,
    img_cutrope_monster_9,
    img_cutrope_bubble,
    img_cutrope_airbubble1,
    img_cutrope_airbubble2,
    img_startgame_star,
    img_optionsmenu_star,
    img_cutrope_theme1,
    img_cutrope_thorn,    
    img_menu_score0,
    img_menu_score1,
    IMG_CUTROPE_SLICE,
    img_cutrope_play,
    img_cutrope_play_press,
    img_cutrope_button_sound,
    img_cutrope_button_sound_close,
    img_cutrope_button_stop,
    img_cutrope_button_replay,
    img_cutrope_button_replay_press,
    img_cutrope_button_menu,
    img_cutrope_button_menu_press,
    IMG_SCORE_NOTBAD,
    IMG_SCORE_GOOD,
    IMG_SCORE_VERYNICE,
    IMG_SCORE_PERFECT,
    img_cutrope_button_back,
    img_cutrope_button_back_press,
    img_cutrope_button_next,
    img_cutrope_button_next_press,
    IMG_CUTROPE_IDLE,
    img_cutrope_theme2,
    img_cutrope_theme3,
    img_cutrope_theme4,
    img_cutrope_button_time,
    img_startgame_0,
    img_startgame_1,
    img_startgame_2,
    img_startgame_3,
    img_startgame_4,
    img_startgame_5,
    img_startgame_6,
    img_startgame_7,
    img_startgame_8,
    img_startgame_9,
    img_startgame_10,
    img_startgame_11,
    img_startgame_12,
    img_menu_icon1,
    img_menu_icon0,
    img_menu_1,
    img_menu_2,
    img_menu_3,
    img_menu_4,
    img_menu_5,
    img_menu_6,
    img_menu_7,
    img_menu_8,
    img_menu_9,
    img_cutrope_stopscreen,
    img_cutrope_optionsmenu,
    img_cutrope_help,
    img_cutrope_help_press,
    img_cutrope_helpBG,
    img_optionsmenu_button_theme1,
    img_optionsmenu_button_theme2,
    img_optionsmenu_button_theme3,
    img_optionsmenu_button_theme4,
    img_optionsmenu_total,
    img_startgame_component1,
    img_startgame_component2,
    img_optionsmenu_button_themelock,
    img_cutrope_stone,
    img_cutrope_force22,
    img_cutrope_force11,
    img_cutrope_button_resume,
    img_cutrope_button_resume_press,
};

boolean CutRopeAPI_CheckInside(u32 p1, u32 p2, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawPlaneTex(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_u32 imgID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawPlay(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawHelp(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawSound(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawComp1(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawComp2(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawPause(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawAgain(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawMenu(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawRate(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawResume(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawNext(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_DrawPrevious(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h);
void CutRope_Draw3Num(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h, mgl_float space, int num);
void CutRope_DrawStar(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h, mgl_float space, int starscore);
void CutRope_DrawStage(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h, mgl_float space, int stage);
void CutRope_DrawTime(CutRopeApp_t *pThis, mgl_u32 nodeID, mgl_float x, mgl_float y, mgl_float w, mgl_float h, mgl_float space);

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
void CutRopeAPI_UpdateAnim(CutRopeApp_t *pThis, s32 nfps);

void CutRopeAPI_CreateSpace(CutRopeApp_t *pThis, s32 iterations, Vertex2D scr_CenterPos, Vertex2D space_gravity);
void CutRopeAPI_ResetSpace(CutRopeApp_t *pThis, s32 iterations, Vertex2D scr_CenterPos, Vertex2D space_gravity);
void CutRopeAPI_ReleaseSpace(CutRopeApp_t *pThis);

void CutRopeAPI_DrawShape(CutRopeApp_t *pThis, CRopeDrawData *pDrawData);

hCRopeNode CutRopeAPI_CreateRopeNode(CutRopeApp_t *pThis, CRopeNodeData *pCRopeNode);
void CutRopeAPI_ReleaseRopeNode(CutRopeApp_t *pThis, hCRopeNode hCpNode);

hCRope CutRopeAPI_CreateRope(CutRopeApp_t *pThis, hCRopeNode hNodeA, hCRopeNode hNodeB, mgl_float nLength);
void CutRopeAPI_ReleaseRope(CutRopeApp_t *pThis, hCRope hRope);

hCRopeNode CutRopeAPI_CutRope_Picking(CutRopeApp_t *pThis, s32 nTSx, s32 nTSy);
void CutRopeAPI_CutRope_ReleasePick(CutRopeApp_t *pThis);

void CutRopeAPI_CutRope_SetCut_Start(CutRopeApp_t *pThis, s32 nTSx_S, s32 nTSy_S);
void CutRopeAPI_CutRope_SetCut_End(CutRopeApp_t *pThis, s32 nTSx_E, s32 nTSy_E);

hCRopeCosHandler CutRopeAPI_CreateCollisionHandler(CutRopeApp_t *pThis, eCROPE_COLLISION_TYPE CollisionA, eCROPE_COLLISION_TYPE CollisionB, CRopeCollisionFunc CollFunc);

void CutRopeAPI_ReleaseCollisionHandler(CutRopeApp_t *pThis, hCRopeCosHandler handler);

void CutRopeAPI_MergeBallandBubble(CutRopeApp_t *pThis, hCRopeNode hNodeBall);
void CutRopeAPI_SetRopeNodeCollisionStatus(CutRopeApp_t *pThis, hCRopeNode hNodeRange, eCROPE_NODE_COLLISION_STATUS eStatus);
void CutRopeAPI_AddStarScore(CutRopeApp_t *pThis);
#endif
