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
* @file    mmi_labyrinthgame_priv.h
* @version
* @brief   LabyrinthGame applet private header file
*
*/

#ifndef __MMI_LABYRINTHGAME_PRIV_H__
#define __MMI_LABYRINTHGAME_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_labyrinthgame.h"

#include "melody_data.h"
#include "mmi_srv_audio.h"

#include "LabyrinthGame_resource.h"

#include "mgl_Egl.h"
#include "mgl_Core_Types.h"

#include "mgl_Scene_Camera.h"

#ifdef __G_SENSOR_MMI__
#include "mmi_mae_sensormgr.h"
#endif

#include "mmi_srv_cfg.h"
#include "mmi_common_cfg.h"
#include "mmi_layout.h"  // for MAIN_LCD_WIDTH, MAIN_LCD_HEIGHT definition

#define DRAW_3D_BALL 0
#define EN_AUDIO 1

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
enum 
{
    LABYRINTHGAME_WND_DESKTOP = WND_ID_APP_BASE,
};

enum
{
    LABYRINTHGAME_BG_IMAGEWIDGET = APP_WDG_START,
};

#define MENU_CUBE_NUM 16
#define MENU_INIT_Z 45.0f
#define MENU_ALPHA 1.0f
#define MENU_ROTATE_STEP 10.0f;
#define MENU_Z_MAX 80.0f
#define MENU_Z_STEP 10.0f
#define MENU_TIMER_INTERVAL 5

#define STAGE_NUM 24

#define MENU_EXIT 9999

typedef struct
{
    IWidget *pOwner;
    s32 nodeID;

    int MenuCubeNum;
    Vertex3D MenuPos[MENU_CUBE_NUM];
    Vertex3D MenuSize[MENU_CUBE_NUM];
    mgl_u32 MenuFrontImg[MENU_CUBE_NUM];
    int MenuStartInd;
    int MenuEndInd;
    int MenuSelectInd;
    int MenuNowInd;
    
    mgl_float MenuRotateX;
    mgl_float MenuRotateY;
    boolean ZSelect[MENU_CUBE_NUM];
    mgl_float ZShift[MENU_CUBE_NUM];
    mgl_float XAngle[MENU_CUBE_NUM];
    mgl_float XTargetAngle;
    
    boolean bStop;
    boolean bStopTimer;
    mgl_float StopCount;
    boolean bSound;
    boolean bVibrate;
    boolean bShowGround;
    boolean bUseGSensor;

    mgl_float pressX;
    mgl_float pressY;

    int StageNum;
    u8 StageOpen;
    int StageSelectInd;
    Vertex3D StagePos[STAGE_NUM];
    mgl_float StagePosShiftY;

    Vertex3D BestScorePos[STAGE_NUM];
    u16 BestScore[STAGE_NUM];
    mgl_float BestScoreShiftY;

    boolean bDraw;
}Menu_t;

#define BALL_SPACE  30
#define BALL_VCS    (90 / BALL_SPACE) * (360 / BALL_SPACE) * 4
#define RADIOUS_PI  MGL_PI / 180.0f

#define SLOWDOWN_CO -0.3f
#define ROTATE_CO 15.0f
#define KEY_PRESS_CO 5.0f
#define ROTATE_THRESHOLD 1.0f
#define ALPHA_STEP 0.04f
#define GSENSOR_TOLERANCE 50

#if defined(__LCM_HVGA_320_480_MMI__)
#define RETURN_X 440.0f
#define RETURN_Y 280.0f
#define TOLERANCE 4.0f
#define SOUND_THRESHOLD 12.0f
#define POINT_SIZE 26.0f
#define BUTTON_SIZE 32.0f
#define TRAP_SIZE 34.0f
#define TRAP_BOTTOM_SIZE 32.0f
#define LOCK_W 40.0f
#define LOCK_H 40.0f
#define DIGIT_W 19.0f
#define DIGIT_H 38.0f
#define LOGO_W 233
#define LOGO_H 310
#define RETURN_W 40.0f
#define RETURN_H 40.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 70.0f
#define STAGE_TIME_X 174.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.9983f
#define SLOWDOWN_STEP_X 0.06f
#define SLOWDOWN_STEP_Y 0.06f
#define GRATIVITY_STEP 0.04f
#define ACCELERATION_STEP_X 0.15f
#define ACCELERATION_STEP_Y 0.15f
#define ACCELERATION_X_MAX 8.0f
#define ACCELERATION_Y_MAX 8.0f
#define VELOCITY_X_MAX 31.0f
#define VELOCITY_Y_MAX 31.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 187.0f
#define LEVEL_Y 186.0f
#define LEVEL_W 70.0f
#define LEVEL_H 38.0f
#define LEVEL_FROM 76.0f
#define LEVEL_TO 136.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 320.0f/240.0f
#define Y_COEF 480.0f/400.0f
#define BEST_SCORE_SHIFT_Y -600
#define STAGE_SHIFT_Y -150
#elif defined(__LCM_LANDSCAPE_HVGA_MMI__)
#define RETURN_X 440.0f
#define RETURN_Y 280.0f
#define TOLERANCE 4.0f
#define SOUND_THRESHOLD 12.0f
#define POINT_SIZE 26.0f
#define BUTTON_SIZE 32.0f
#define TRAP_SIZE 34.0f
#define TRAP_BOTTOM_SIZE 32.0f
#define LOCK_W 40.0f
#define LOCK_H 40.0f
#define DIGIT_W 19.0f
#define DIGIT_H 38.0f
#define LOGO_W 243
#define LOGO_H 310
#define RETURN_W 40.0f
#define RETURN_H 40.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 70.0f
#define STAGE_TIME_X 194.0f
#define STAGE_TIME_Y -3.0f
#define SHIFT_RATE 0.9977f
#define SLOWDOWN_STEP_X 0.06f
#define SLOWDOWN_STEP_Y 0.06f
#define GRATIVITY_STEP 0.04f
#define ACCELERATION_STEP_X 0.15f
#define ACCELERATION_STEP_Y 0.15f
#define ACCELERATION_X_MAX 8.0f
#define ACCELERATION_Y_MAX 8.0f
#define VELOCITY_X_MAX 31.0f
#define VELOCITY_Y_MAX 31.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 0.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 187.0f
#define LEVEL_Y 186.0f
#define LEVEL_W 70.0f
#define LEVEL_H 38.0f
#define LEVEL_FROM 76.0f
#define LEVEL_TO 136.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 480.0f/400.0f
#define Y_COEF 320.0f/240.0f
#define BEST_SCORE_SHIFT_Y -600
#define STAGE_SHIFT_Y -150
#elif defined(__LCM_WQVGA_240_400_MMI__)
#define RETURN_X 370.0f
#define RETURN_Y 210.0f
#define TOLERANCE 3.0f
#define SOUND_THRESHOLD 9.0f
#define POINT_SIZE 20.0f
#define BUTTON_SIZE 24.0f
#define TRAP_SIZE 26.0f
#define TRAP_BOTTOM_SIZE 24.0f
#define LOCK_W 30.0f
#define LOCK_H 30.0f
#define DIGIT_W 15.0f
#define DIGIT_H 30.0f
#define LOGO_W 186
#define LOGO_H 224
#define RETURN_W 30.0f
#define RETURN_H 30.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 70.0f
#define STAGE_TIME_X 145.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.998f
#define SLOWDOWN_STEP_X 0.04f
#define SLOWDOWN_STEP_Y 0.04f
#define GRATIVITY_STEP 0.03f
#define ACCELERATION_STEP_X 0.1f
#define ACCELERATION_STEP_Y 0.1f
#define ACCELERATION_X_MAX 5.0f
#define ACCELERATION_Y_MAX 5.0f
#define VELOCITY_X_MAX 21.0f
#define VELOCITY_Y_MAX 21.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 140.0f
#define LEVEL_Y 155.0f
#define LEVEL_W 70.0f
#define LEVEL_H 30.0f
#define LEVEL_FROM 45.0f
#define LEVEL_TO 105.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 1.0f
#define Y_COEF 1.0f
#define BEST_SCORE_SHIFT_Y -700
#define STAGE_SHIFT_Y -250
#elif defined(__LCM_LANDSCAPE_WQVGA_240_400_MMI__)
#define RETURN_X 370.0f
#define RETURN_Y 210.0f
#define TOLERANCE 3.0f
#define SOUND_THRESHOLD 9.0f
#define POINT_SIZE 20.0f
#define BUTTON_SIZE 24.0f
#define TRAP_SIZE 26.0f
#define TRAP_BOTTOM_SIZE 24.0f
#define LOCK_W 30.0f
#define LOCK_H 30.0f
#define DIGIT_W 15.0f
#define DIGIT_H 30.0f
#define LOGO_W 186
#define LOGO_H 224
#define RETURN_W 30.0f
#define RETURN_H 30.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 70.0f
#define STAGE_TIME_X 160.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.9968f
#define SLOWDOWN_STEP_X 0.04f
#define SLOWDOWN_STEP_Y 0.04f
#define GRATIVITY_STEP 0.03f
#define ACCELERATION_STEP_X 0.1f
#define ACCELERATION_STEP_Y 0.1f
#define ACCELERATION_X_MAX 5.0f
#define ACCELERATION_Y_MAX 5.0f
#define VELOCITY_X_MAX 21.0f
#define VELOCITY_Y_MAX 21.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 140.0f
#define LEVEL_Y 155.0f
#define LEVEL_W 70.0f
#define LEVEL_H 30.0f
#define LEVEL_FROM 45.0f
#define LEVEL_TO 105.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 1.0f
#define Y_COEF 1.0f
#define BEST_SCORE_SHIFT_Y -700
#define STAGE_SHIFT_Y -250
#elif defined(__LCM_QVGA_MMI__)
#define RETURN_X 290.0f
#define RETURN_Y 210.0f
#define TOLERANCE 3.0f
#define SOUND_THRESHOLD 9.0f
#define POINT_SIZE 20.0f
#define BUTTON_SIZE 24.0f
#define TRAP_SIZE 26.0f
#define TRAP_BOTTOM_SIZE 24.0f
#define LOCK_W 30.0f
#define LOCK_H 30.0f
#define DIGIT_W 15.0f
#define DIGIT_H 30.0f
#define LOGO_W 186
#define LOGO_H 224
#define RETURN_W 30.0f
#define RETURN_H 30.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 60.0f
#define STAGE_TIME_X 118.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.9976f
#define SLOWDOWN_STEP_X 0.04f
#define SLOWDOWN_STEP_Y 0.04f
#define GRATIVITY_STEP 0.03f
#define ACCELERATION_STEP_X 0.1f
#define ACCELERATION_STEP_Y 0.1f
#define ACCELERATION_X_MAX 5.0f
#define ACCELERATION_Y_MAX 5.0f
#define VELOCITY_X_MAX 21.0f
#define VELOCITY_Y_MAX 21.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 110.0f
#define LEVEL_Y 155.0f
#define LEVEL_W 70.0f
#define LEVEL_H 30.0f
#define LEVEL_FROM 45.0f
#define LEVEL_TO 105.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 1.0f
#define Y_COEF 320.0f/400.0f
#define BEST_SCORE_SHIFT_Y -700
#define STAGE_SHIFT_Y -250
#elif defined(__LCM_LANDSCAPE_QVGA_MMI__)
#define RETURN_X 290.0f
#define RETURN_Y 210.0f
#define TOLERANCE 3.0f
#define SOUND_THRESHOLD 9.0f
#define POINT_SIZE 20.0f
#define BUTTON_SIZE 24.0f
#define TRAP_SIZE 26.0f
#define TRAP_BOTTOM_SIZE 24.0f
#define LOCK_W 30.0f
#define LOCK_H 30.0f
#define DIGIT_W 15.0f
#define DIGIT_H 30.0f
#define LOGO_W 186
#define LOGO_H 224
#define RETURN_W 30.0f
#define RETURN_H 30.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 60.0f
#define STAGE_TIME_X 124.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.9968f
#define SLOWDOWN_STEP_X 0.04f
#define SLOWDOWN_STEP_Y 0.04f
#define GRATIVITY_STEP 0.03f
#define ACCELERATION_STEP_X 0.1f
#define ACCELERATION_STEP_Y 0.1f
#define ACCELERATION_X_MAX 5.0f
#define ACCELERATION_Y_MAX 5.0f
#define VELOCITY_X_MAX 21.0f
#define VELOCITY_Y_MAX 21.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 110.0f
#define LEVEL_Y 155.0f
#define LEVEL_W 70.0f
#define LEVEL_H 30.0f
#define LEVEL_FROM 45.0f
#define LEVEL_TO 105.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 320.0f/400.0f
#define Y_COEF 1.0f
#define BEST_SCORE_SHIFT_Y -700
#define STAGE_SHIFT_Y -250
#else
#define RETURN_X 370.0f
#define RETURN_Y 210.0f
#define TOLERANCE 3.0f
#define SOUND_THRESHOLD 9.0f
#define POINT_SIZE 20.0f
#define BUTTON_SIZE 24.0f
#define TRAP_SIZE 26.0f
#define TRAP_BOTTOM_SIZE 24.0f
#define LOCK_W 30.0f
#define LOCK_H 30.0f
#define DIGIT_W 15.0f
#define DIGIT_H 30.0f
#define LOGO_W 186
#define LOGO_H 224
#define RETURN_W 30.0f
#define RETURN_H 30.0f
#define BEST_W 44.0f
#define BEST_H 20.0f
#define BEST_SHIFT 70.0f
#define STAGE_TIME_X 145.0f
#define STAGE_TIME_Y -5.0f
#define SHIFT_RATE 0.998f
#define SLOWDOWN_STEP_X 0.04f
#define SLOWDOWN_STEP_Y 0.04f
#define GRATIVITY_STEP 0.03f
#define ACCELERATION_STEP_X 0.1f
#define ACCELERATION_STEP_Y 0.1f
#define ACCELERATION_X_MAX 5.0f
#define ACCELERATION_Y_MAX 5.0f
#define VELOCITY_X_MAX 21.0f
#define VELOCITY_Y_MAX 21.0f
#define REBOUND_MIN SOUND_THRESHOLD
#define TRAP_SHIFT_X_MAX 1.0f
#define TRAP_SHIFT_Y_MAX TRAP_SHIFT_X_MAX
#define LEVEL_X 140.0f
#define LEVEL_Y 155.0f
#define LEVEL_W 70.0f
#define LEVEL_H 30.0f
#define LEVEL_FROM 45.0f
#define LEVEL_TO 105.0f
#define LEVEL_BG_W 54.0f
#define LEVEL_BG_H 54.0f
#define X_COEF 1.0f
#define Y_COEF 1.0f
#define BEST_SCORE_SHIFT_Y -700
#define STAGE_SHIFT_Y -250
#endif
#define POINT_RADIOUS POINT_SIZE / 2
#define TRAP_RADIOUS TRAP_SIZE / 2
#define BUTTON_RADIOUS TRAP_SIZE / 2
#define STAGE_TIME_Z 23.0f
#define STAGE_TIME_SECOND 26
#define TRAP_NUM 14
#define TRAP_MOVE_MAX 9
#define TRAP_MOVE_X 1.0f
#define TRAP_MOVE_Y 1.0f
#define BOUNDARY_NUM 8
#define TRANSPORT_NUM 8
#define PLANE_Z 0.0f
#define BALL_Z 20.0f
#define BALL_STEP_Z -1.0f
#define BALL_END_Z PLANE_Z/*-5.0f*/
#define START_Z 3.0f
#define END_APPEAR_Z 10.0f
#define TRAP_Z 5.0f
#define TRAP_BOTTOM_Z 3.0f
#define BOUNDARY_Z 0.0f

#define FLOAT_MAX 10000.0f
#define FLOAT_MIN 0.0f

#define LABYRINTH_TIMER_INTERVAL 5


#if DRAW_3D_BALL
typedef struct	
{
    Vertex3D    SpherePos[2][BALL_VCS];
    Vertex2D    SphereTC[2][BALL_VCS];
    Color4f SphereColor[2][BALL_VCS];
} LabyrinthBall_t;
#endif

typedef struct
{
    APPLET_BASE_ELEMENTS;

    s32 nodeID;
    u16 u16SceneHandleId;

#if DRAW_3D_BALL
    LabyrinthBall_t  LabyrinthBall;
#endif
    Vertex3D LabyrinthBallPos;
    mgl_float LabyrinthBallRotateX;
    mgl_float LabyrinthBallRotateY;

    boolean bLockAccelerationXNeg, bLockAccelerationXPos;
    boolean bLockAccelerationYNeg, bLockAccelerationYPos;
    mgl_float LabyrinthBallAccelerationX;
    mgl_float LabyrinthBallAccelerationY;
    mgl_float LabyrinthBallVelocityX;
    mgl_float LabyrinthBallVelocityY;

    u16 LastGSensorX;
    u16 LastGSensorY;

    Vertex2D PressMovePoint;

    Vertex2D StartPoint;
    mgl_float StartPointAlpha;
    Vertex2D BreakWallPoint;
    mgl_float BreakWallPointAlpha;
    Vertex2D EndPoint;
    mgl_float EndPointAlpha;
    int EndAppearNum;
    int EndAppearInd;
    Vertex2D EndAppearPoint[9];
    mgl_float EndAppearPointAlpha[9];
    int EndPointCount;
    mgl_float EndPointMaxHeight;
    Vertex2D TrapPoint[TRAP_NUM];
    Vertex2D TrapPointShift;
    int TrapMoveNum;
    Vertex2D TrapMoveMax[TRAP_MOVE_MAX];
    Vertex2D TrapMove[TRAP_MOVE_MAX];
    boolean bTrapDirX[TRAP_MOVE_MAX];
    boolean bTrapDirY[TRAP_MOVE_MAX];
    Vertex2D BoundaryPoint[BOUNDARY_NUM+5][2];
    int TransportNum;
    Vertex2D TransportPoint[TRANSPORT_NUM];
    mgl_float TransportPointAlpha[TRANSPORT_NUM];
    mgl_float LevelAlpha;
    Vertex3D LevelPoint;
    boolean bDrawLevel;
    int StageNum;
    int StageTime;
    u32 StageTimeBase;
    int SuspendTime;
    u32 SuspendTimeBase;
    int TrapNum;
    int BoundaryNum;

    boolean bBreakWallPointHit;
    boolean bTransportHit;
    boolean bTrapHit;
    int TrapHitInd;
    boolean bEndHit;

    Menu_t menu;

    boolean bDrawReturn;
    boolean bStop;
	boolean bWin;

    CameraId CameraID;
    Vertex3D CameraEye;
    Vertex3D CameraAt;
    Vertex3D CameraOriginalEye;
    Vertex3D CameraOriginalAt;
    Vertex3D CameraUp;

    boolean bSuspendMode;
    boolean bDraw;
    boolean bMove;
    boolean bExit;
    boolean bPause;
#ifdef __G_SENSOR_MMI__
    ISensorMgr *pISensorMgr;
#endif
    boolean bUpdateWindow;

    int MoveCount;

    u32 P1, P2;

    IWidget *pBgImgWdg;
    IWidget *pLogoImgWdg;
}LabyrinthApp_t;

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret LabyrinthGameConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret LabyrinthGameDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameIsFOCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
//void	FruitSliceGameTimeoutCb(void* pUserData);

boolean LabyrinthGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean LabyrinthGameGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);

MAE_Ret WndLabyrinthDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret WndLabyrinthCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret LabyrinthApp_Ctor (LabyrinthApp_t *pThis);
MAE_Ret LabyrinthApp_Dtor (LabyrinthApp_t *pThis);
boolean LabyrinthApp_DefHandleEvent (LabyrinthApp_t *pWdg, u32 evt, u32 P1, u32 P2);
void    LabyrinthApp_Draw (LabyrinthApp_t *pWdg);

MAE_Ret LabyrinthApp_Pause(LabyrinthApp_t *pThis);
MAE_Ret LabyrinthApp_Play(LabyrinthApp_t *pThis, boolean bForcePlay);
MAE_Ret LabyrinthApp_Replay(LabyrinthApp_t *pThis);

u32 Labyrinth_GetBgImageID(LabyrinthApp_t *pThis);

mgl_u32 GetDigitImageID(int num);
void ClockwiseRotate(s32 nodeID);
void ClockwiseRotateEnd(void);
void InitMenu(Menu_t *pMenu, IWidget* pOwner, s32 nodeID, int stage_num);
void DrawMenu(void *pUser, void *pUserData);
void DrawLabyrinth(void *pUser, void *pUserData);
int Menu_DefHandleEvent(Menu_t *pMenu, MAE_EventId evt, u32 P1, u32 P2);
void DrawMenuAll(void *pUser, void *pUserData);
void _LabyrinthDrawAll(LabyrinthApp_t *pThis);
void _Labyrinth_CalInput(LabyrinthApp_t *pThis);

#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
