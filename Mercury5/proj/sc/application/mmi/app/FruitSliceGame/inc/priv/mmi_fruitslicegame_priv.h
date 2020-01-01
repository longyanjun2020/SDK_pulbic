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
* @file    mmi_fruitslicegame_priv.h
* @version
* @brief   FruitSliceGame applet private header file
*
*/

#ifndef __MMI_FRUITSLICEGAME_PRIV_H__
#define __MMI_FRUITSLICEGAME_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_fruitslicegame.h"

#include "melody_data.h"
#include "mmi_srv_audio.h"

#include "FruitSliceGame_resource.h"

#include "mgl_Egl.h"
#include "mgl_Core_Types.h"

#include "mmi_layout.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
enum 
{
	FRUITSLICEGAME_WND_DESKTOP = WND_ID_APP_BASE,
};

enum
{
	FRUITSLICEGAME_BG_IMAGEWIDGET = APP_WDG_START,
};

typedef enum
{
    FRUITSLICE_ANIM_NONE,
    FRUITSLICE_ANIM_LOADING,
    FRUITSLICE_ANIM_MENU,
    FRUITSLICE_ANIM_OPTION,
    FRUITSLICE_ANIM_HELP,
    FRUITSLICE_ANIM_MAIN,
    FRUITSLICE_ANIM_RESULT,
    FRUITSLICE_ANIM_EXPLOSION
} FruitSlice_Anim_e;

#define FRUITSLICE_VARIOUS_COLOR_SPEED			2.0f		//Various color speed of comet.
#define FRUITSLICE_LENGTH_THREAD				10		
#define FRUITSLICE_LENGTH_THREAD_DELTA			0.8f/(float)FRUITSLICE_LENGTH_THREAD

#ifdef __G3D_MMI__
#define FRUITSLICE_FRUIT_MAX                    10
#else
#define FRUITSLICE_FRUIT_MAX                    8
#endif
#define FRUITSLICE_BOMB_MAX                     3
#define FRUITSLICE_STEAMER_MAX                  1
#define FRUITSLICE_SPRITES_MAX                  (FRUITSLICE_FRUIT_MAX+FRUITSLICE_BOMB_MAX+FRUITSLICE_STEAMER_MAX)
#define FRUITSLICE_MISS_MAX                     3

#define FRUITSLICE_STEAMER_FRUIT_MAX            FRUITSLICE_FRUIT_MAX

typedef enum
{
    FRUITSLICE_NODE_BG,
    FRUITSLICE_NODE_SCENE,
    FRUITSLICE_NODE_FRUIT,
    FRUITSLICE_NODE_SLICE = FRUITSLICE_SPRITES_MAX+FRUITSLICE_NODE_FRUIT,
    FRUITSLICE_NODE_MAX_NUM,
} FruitSlice_Node_e;

typedef enum
{
    FRUITSLICE_TYPE_BANANA,
    FRUITSLICE_TYPE_BLUE_APPLE,
    FRUITSLICE_TYPE_RED_APPLE,
    FRUITSLICE_TYPE_CANTALOUPE,
    FRUITSLICE_TYPE_CUCUMBER,
    FRUITSLICE_TYPE_GREEN_PEPPER,
    FRUITSLICE_TYPE_RED_PEPPER,
    FRUITSLICE_TYPE_KIWI,
    FRUITSLICE_TYPE_LAI,
    FRUITSLICE_TYPE_LEMON,
    FRUITSLICE_TYPE_ORANGE,
    FRUITSLICE_TYPE_PAPAYA,
    FRUITSLICE_TYPE_PEACH,
    FRUITSLICE_TYPE_PEARS,
    FRUITSLICE_TYPE_STRAWBERRY,
    FRUITSLICE_TYPE_TOMATO,
    FRUITSLICE_TYPE_WATERMELON,
    FRUITSLICE_TYPE_STEAMER,
    FRUITSLICE_TYPE_BOMB,
    FRUITSLICE_TYPE_MAX,
} FruitSlice_Type_e;

typedef enum
{
    FRUITSLICE_CTRL_HELP,
    FRUITSLICE_CTRL_STARTGAME,
    FRUITSLICE_CTRL_OPTION,
    FRUITSLICE_CTRL_TIME_ATTACK,
    FRUITSLICE_CTRL_STEAMER,
    FRUITSLICE_CTRL_OPTION_BACK,
    FRUITSLICE_CTRL_MAINMENU,
    FRUITSLICE_CTRL_RETRY,
    FRUITSLICE_CTRL_HELP_BACK,
    FRUITSLICE_CTRL_MAX,
} FruitSlice_Ctrl_e;

typedef enum
{
    FRUITSLICE_STATUS_NONE,
    FRUITSLICE_STATUS_READY,    
    FRUITSLICE_STATUS_MOTION,
    FRUITSLICE_STATUS_SLICE,
    FRUITSLICE_STATUS_MISS,
    FRUITSLICE_STATUS_MAX,
} FruitSlice_Status_e;

typedef enum
{
    FRUITSLICE_FUNC_CTRLFRUIT,
    FRUITSLICE_FUNC_GAMEFRUIT,
} FruitSlice_Func_e;

typedef enum
{
    FRUITSLICE_BODY_ALL,    
    FRUITSLICE_BODY_UP,
    FRUITSLICE_BODY_DN,
    FRUITSLICE_BODY_MAX,
} FruitSlice_Body_e;

typedef enum
{
    FRUITSLICE_GAME_SCORE,
    FRUITSLICE_GAME_TIMEATTACK,
    FRUITSLICE_GAME_STEAMER
} FruitSlice_Game_e;

#define FRUITSLICE_BUTTON_NONE 0xFF

typedef enum
{
    FRUITSLICE_BUTTON_STATE_PLAY,
    FRUITSLICE_BUTTON_STATE_REPLAY,
    FRUITSLICE_BUTTON_STATE_PAUSE,
    FRUITSLICE_BUTTON_STATE_QUIT,
    FRUITSLICE_BUTTON_STATE_PREV,
    FRUITSLICE_BUTTON_STATE_NEXT,
    FRUITSLICE_BUTTON_STATE_MENU_MUSIC,
    FRUITSLICE_BUTTON_STATE_MENU_VOLUME,
    FRUITSLICE_BUTTON_STATE_PAUSE_MUSIC,
    FRUITSLICE_BUTTON_STATE_PAUSE_VOLUME,
    FRUITSLICE_BUTTON_STATE_NUM
} FruitSlice_Button_State_e;

typedef enum
{
    FRUITSLICE_NUMTYPE_SCORE,
    FRUITSLICE_NUMTYPE_DIGIT,
    FRUITSLICE_NUMTYPE_BIGDIGIT,
} FruitSlice_NumType_e;

typedef struct 
{
    u32 eButton;
    u32 nImageID;
    u32 nDisableImageID;
    Vertex3D tPos;
    Vertex2D tSize;
} FruitSlice_Button_t;

typedef struct
{
    u32 nDockImage;
    Vertex3D        fDockPos;
    Vertex2D        fDockSize;
} FruitSlice_Ctrl_t;

// fire
#define FRUIT_FIRE_NUM      20
#define FRUIT_FIRE_SIZE     48
typedef struct
{
    Color4f     s_color[FRUIT_FIRE_NUM];
    Vertex3D	s_pos[FRUIT_FIRE_NUM];
    Vertex3D    s_vec[FRUIT_FIRE_NUM];
    Vertex2D    s_size[FRUIT_FIRE_NUM];
    mgl_float   s_rotate[FRUIT_FIRE_NUM];
    mgl_float   s_decade[FRUIT_FIRE_NUM];
} FruitSlice_Fire_t;

// explosion
#define FRUIT_EXPLOSION_NUM 8
typedef struct  
{
    boolean s_active[FRUIT_EXPLOSION_NUM];
    u32 s_step[FRUIT_EXPLOSION_NUM];
    mgl_float s_ratio[FRUIT_EXPLOSION_NUM];
    mgl_float s_maxratio[FRUIT_EXPLOSION_NUM];
    mgl_float s_width[FRUIT_EXPLOSION_NUM];
    Vertex2D s_upvec[FRUIT_EXPLOSION_NUM];
    Vertex2D s_downvec[FRUIT_EXPLOSION_NUM];
    mgl_float s_rotate[FRUIT_EXPLOSION_NUM];
} FruitSlice_Explosion_t;

typedef struct
{
    boolean bBomb;
    Vertex3D ExplosionCenter;
    FruitSlice_Explosion_t t_Explosion;
} FruitSlice_Bomb_t;

typedef enum
{
    FRUITSLICE_JUICE1,
    FRUITSLICE_JUICE2,
    FRUITSLICE_JUICE3,
    FRUITSLICE_JUICE_NUM
} FruitSlice_Juice_e;

typedef struct FruitSlice_Info_tag
{
    mgl_u32         nNodeID;
    FruitSlice_Func_e    eFruitFunc;
    FruitSlice_Type_e    eFruitType;
    FruitSlice_Status_e     eMotionSuatus;
    mgl_float	    fTheta;
    mgl_float	    fAngle[FRUITSLICE_BODY_MAX];
    mgl_float       fSize_W[FRUITSLICE_BODY_MAX];
    mgl_float       fSize_H[FRUITSLICE_BODY_MAX];
    mgl_float       fAlpha; 
    mgl_float       fSpeed;
    Vertex3D        glvPos[FRUITSLICE_BODY_MAX]; 
    Vertex3D        glvVelocity[FRUITSLICE_BODY_MAX];
    Vertex3D        glvAcceleration[FRUITSLICE_BODY_MAX];
    u16             nMissStep;
    u32             nDockImage;
    Vertex3D        fDockPos;
    Vertex2D        fDockSize;
    mgl_float       nRotateDock;
    FruitSlice_Fire_t t_Fire;
    mgl_float       fSliceAngle;
    FruitSlice_Juice_e eJuice;
    mgl_float       fFootPrintRatio;
} FruitSlice_Info_t;

typedef struct FruitSliceScore_tag
{
    u32 nScore;
} FruitSliceScore_t;

typedef enum
{
    FRUITSLICE_THROW_ANYTIME,
    FRUITSLICE_THROW_WAIT,
    FRUITSLICE_THROW_TOGETHER
} FruitSlice_Throw_e;

typedef enum
{
    FRUITSLICE_LEVEL_0,
    FRUITSLICE_LEVEL_1,
    FRUITSLICE_LEVEL_2,
    FRUITSLICE_LEVEL_3,
    FRUITSLICE_LEVEL_4,
    FRUITSLICE_LEVEL_5,
    FRUITSLICE_LEVEL_6,
    FRUITSLICE_LEVEL_NUM,
} FruitSlice_Level_e;

typedef struct FruitSliceLevelConfig_tag
{
    u32 nActiveFruit;
    u32 nFruitTime;
    u32 nActiveBomb;
    u32 nBombTime;
    u32 nThrowCount;
    u32 nWaitCount;
} FruitSliceLevelConfig_t;

typedef struct FruitSliceLevel_tag
{
    FruitSlice_Level_e eGameLevel;
    FruitSliceLevelConfig_t tConfig;
    //
    FruitSlice_Throw_e eThrow;
    u32 nThrowStep;
} FruitSliceLevel_t;

typedef enum
{
    FruitSlice_TimerState_Idle = 0,
    FruitSlice_TimerState_Counting,
    FruitSlice_TimerState_Pause,
    FruitSlice_TimerState_Timeout
} FruitSlice_TimerState_e;

typedef struct FruitSliceTimer_tag
{
    FruitSlice_TimerState_e eTimerState;
    u32 nDuration;
    u32 nCountingSeconds;
    u32 nCountingMilliSeconds;
    u32 nStartSecond;
    u32 nPauseSecond;
    u32 nLastSecond;
} FruitSliceTimer_t;

typedef enum
{
    FRUITSLICE_HELP_DOC_MENU = 0,
    FRUITSLICE_HELP_DOC_STEAMER,
    FRUITSLICE_HELP_DOC_CLASSIC,
    FRUITSLICE_HELP_DOC_TIMEATTACK,
    FRUITSLICE_HELP_DOC_NUM
} FruitSlice_Help_e;

typedef enum
{
    FRUITSLICE_WAV_SLICE = 0,
    FRUITSLICE_WAV_SPURT,
    FRUITSLICE_WAV_BUTTON,
    FRUITSLICE_WAV_THROW,
    FRUITSLICE_WAV_BOMB,
    FRUITSLICE_WAV_MISS,
    FRUITSLICE_WAV_COUNTDOWN,
    FRUITSLICE_WAV_TIMEUP,
    FRUITSLICE_WAV_LOADING,
    FRUITSLICE_WAV_MENU,
} FruitSlice_Sound_e;

typedef struct FruitSlice_Instruction_tag
{
    boolean bEnable;
    u32 nStep;
    mgl_float fAlpha;
    Vertex3D fPos;
    Vertex3D fFromPos;
    Vertex3D fToPos;
} FruitSlice_Instruction_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    mgl_boolean	    bTouched;
    mgl_boolean	    bSlice;
    mgl_boolean     bHasSlice;
    mgl_u16         u16SceneHandleId;
    mgl_u32         nodeID[FRUITSLICE_NODE_MAX_NUM];
    mgl_s32		    nTS_CurrentX, nTS_CurrentY;
    mgl_float	    fTS_X, fTS_Y;
    mgl_float       slice_slope;
    mgl_float       slice_angle;
    Vertex3D	    f_SlicePos;
    Vertex3D	    Slices[FRUITSLICE_LENGTH_THREAD];
    Vertex3D	    p_LineCoords[FRUITSLICE_LENGTH_THREAD];		//Pointer of Slice Coords array.
    Color4f		    p_LineColors[FRUITSLICE_LENGTH_THREAD];		//Pointer of Slice Color array.

    Vertex3D  	    p_SliceVertice[FRUITSLICE_LENGTH_THREAD<<1];
    Vertex2D  	    p_SliceTex[FRUITSLICE_LENGTH_THREAD<<1];

    FruitSlice_Info_t     t_FruitInfo[FRUITSLICE_SPRITES_MAX];
    FruitSliceLevel_t   t_FruitLevel;
    u32 nLoadingStep;
    mgl_float       fSpeedRatio;

    FruitSlice_Bomb_t t_Bomb;

    boolean bViewturn;
    u32 nWidth;
    u32 nHeight;

    //
    FruitSlice_Instruction_t t_Instruction;

    boolean bSuspendMode;
    boolean bDraw;
    boolean bExit;
    boolean bPause;
    boolean bVolume;
    boolean bMusic;
    boolean bPlayAudio;
    boolean bWaitAudio;
    u32 nWaitSound;
    u32 nPressed;
    FruitSlice_Anim_e u16Amin_type;
    FruitSlice_Game_e eGameMode;
    boolean bEnableSteamer;
    u32 nSteamerStep;
    boolean bWaitRelease;
    // count down
    u32 nCountDown;
    FruitSliceTimer_t t_Timer;
    // score
    boolean         bUpdateScore;
    u32             nScore;
    u32             nShowScore;
    u8              nMiss;
    boolean bGameOver;
    u16 nGameOverStep;
    // combo
    u32 nMaxCombo;
    u32 nCombo;
    u32 nSliceTime;
    u32 nShowCombo;
    u32 nComboStep;
    // help
    FruitSlice_Help_e eHelp;
    //
#ifdef __FEATURE_MGLS__
    IWidget *pBgImgWdg;
#endif
}FruitSliceApp_t;
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret FruitSliceGameConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret FruitSliceGameDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameIsFOCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameTSCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
//void	FruitSliceGameTimeoutCb(void* pUserData);

boolean FruitSliceGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameIsFullOpaque(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitSliceGameGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);

MAE_Ret WndFruitSliceDesktopHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret WndFruitSliceCreate(void *pCusHandle, void *pWndData, u32 nWndInitParam);

MAE_Ret FruitSliceWdg_Ctor (FruitSliceApp_t *pThis);
MAE_Ret FruitSliceWdg_Dtor (FruitSliceApp_t *pThis);
boolean FruitSliceWdg_DefHandleEvent (FruitSliceApp_t *pWdg, u32 evt, u32 P1, u32 P2);
void    FruitSliceWdg_Draw (FruitSliceApp_t *pWdg);

MAE_Ret FruitSliceWdg_Pause(FruitSliceApp_t *pThis);
MAE_Ret FruitSliceWdg_Play(FruitSliceApp_t *pThis, boolean bForcePlay);
MAE_Ret FruitSliceWdg_Replay(FruitSliceApp_t *pThis);

MAE_Ret FruitSliceWdg_PlayMusic(FruitSliceApp_t *pThis, FruitSlice_Anim_e eAnim, boolean bResume);
u32 FruitSlice_GetBgImageID(FruitSliceApp_t *pThis);

#endif /* __MMI_MGLDEMOAPP_PRIV_H__ */
