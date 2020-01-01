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
* @file    mmi_bmiapp_priv.h
* @version
* @brief   BMI applet private header file
*
*/
#ifndef __MMI_PACMAN_PRIV_H__
#define __MMI_PACMAN_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_pacman_id.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_header.h"
#include "mmi_mae_shell.h"
#include "mmi_clstbl.h"

#ifdef __NATIVE_GAME_MMI_PACMAN__
#include "PacMan_resource.h"
#include "mmi_PacMan_rs.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
#define NATIVEGAME_DIALOG_TIMER                         1000
#define NATIVEGAME_PACMAN_TIMER_TICK					200

/**********************************************************for common structure**********************************************************/

enum e_Dialog_Type
{
  DIALOG_E_START=0x00,
  DIALOG_E_CONFIRM=0x00,
  DIALOG_E_INFO,
  DIALOG_E_WARNING,
  DIALOG_E_WAITING,
  DIALOG_E_TOTAL,
};

enum
{
	KER_NONE,
	KER_UP,
	KER_DOWN,
	KER_LEFT,
	KER_RIGHT
};

enum
{
    MMI_AUDIO_PLAY_ONCE,
    MMI_AUDIO_PLAY_LOOP
};


/**********************************************************for PacMan game structure**********************************************************/
#define GAME_3_ENEMY_NUMBER	4
#define GAME_3_POWERDOT_NUMBER	4
#define GAME_3_MAX_LEVEL	10
#define GAME_3_INIT_LIFE	3
#define GAME_3_BONUS_NUMBER	5

#define GAME_3_GHOST_TIME	50

#define GAME_3_BASE_ENEMY_SCORE		100 //0
#define GAME_3_DOT_SCORE			10 //0
#define GAME_3_POWERDOT_SCORE		100 //0

#define GAME_3_INIT_WAIT_TIME	21

enum
{
	GAME_3_FRUIT_NUMBER	    =   5,
	GAME_3_FRUIT_WAIT_TIME	=   10,
	GAME_3_FRUIT_LIVE_TIME	=   20,
};

#define GAME_3_MELODY_NUMBER	7

typedef enum
{
	GAME_3_SUSPEND_NONE = 0,
	GAME_3_SUSPEND_WAIT_START,
	GAME_3_SUSPEND_ATTACKED,
	GAME_3_SUSPEND_END,
	GAME_3_SUSPEND_NEXT_LEVEL,
} PacManSuspend_e;

typedef enum
{
	GAME_3_ENEMY_NORMAL,
	GAME_3_ENEMY_WEAK,
	GAME_3_ENEMY_GHOST,
} PacManEnemyStatus_e;

typedef enum
{
	GAME_3_FRUIT_NONE,
	GAME_3_FRUIT_APPLE,
	GAME_3_FRUIT_ORANGE,
	GAME_3_FRUIT_CHERRY,
	GAME_3_FRUIT_GRENEADE,
	GAME_3_FRUIT_STRAWBERRY,
} PacManFruitType_e;

typedef enum
{
	GAME_3_MELODY_BEGIN,
	GAME_3_MELODY_EXTRAPAC,
	GAME_3_MELODY_INTERM,
	GAME_3_MELODY_KILLED,
	GAME_3_MELODY_GHOST,
	GAME_3_MELODY_EATFRUIT,
	GAME_3_MELODY_PACCHOMP,
} PacManMelodyType_e;

typedef struct
{
	u32 direction;
	u32 nextDirection;
	u8 posX;
	u8 posY;
	u8 oldPosX;
	u8 oldPosY;
} PacManPos_t;

typedef struct
{
	u32 direction;
	u32 nextDirection;
	u32 leftTime;
	u32 sleepTime;
	u8 status;
	u8 posX;
	u8 posY;
	u8 oldPosX;
	u8 oldPosY;
} PacManEnemy_t;

typedef struct
{
    PacManMelodyType_e eMelodyName;
    PacManEnemy_t tEnemy[GAME_3_ENEMY_NUMBER];
    PacManPos_t tGenie;
    u32 nScore;
    u32 nPowerTime;
    u32 nDots;
    boolean bInit;
    u8 nFlash;
    u8 nLife;
    u8 nLevel;
    boolean bIsPause;
    boolean bRefresh;
    u8 nSuspendStatus;
    u8 nWaitTime;
    u8 nEatEnemyNum;
    u8 nFruitTime;
    u8 nFruitType;
    u32 nMelodyTicks;
    u8 nMelodyType;
    u32 nTempVolLevel;
    boolean bSoundOn;
    SetRingToneVolume_e	eSetVolumn;
} PacManData_t;

typedef struct
{
	u8	coordinate[GAME_3_BLOCK_Y][GAME_3_BLOCK_X];

}PacManMap_t;

typedef struct
{
	u16 posX;
	u16 posY;
} PacManSimplePos_t;

typedef struct
{
    IWidget *pBmpWdg;
    IWidget *pTextWdg;
    IWidget *pPenSwitchIconWdg;
    IWidget *pStrokeSwitchIconWdg;
    IWidget *pColorSwitchIconWdg;
    IWidget *pTxtBtnWdg;
    IWidget *pEraserSwitchIconWdg;
    IWidget *pStrokeGridWdg;
    IWidget *pColorGridWdg;

	IDisplay *pDisplay;
	IBitmap	*pBitmapImg;
	IBitmap *pIBmpSrc;

}PacManWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
} PacManOptionMenuWndData_t;

typedef struct
{
    InputVtmWdgList_t   tWdgList;
    boolean             bSKShown;       //Check if softkey is shown.
} PacManEditChannelNameWndData_t;

typedef struct
{
    IWidget *pPMLIMenuWdg;
    IWidget *pIPhoneMenuWidget;
    IWidget *pIConnectMenuWidget;
    IWidget *pITabWidget;
    IWidget *pITitleWidget;
}PacManSettingsViewWdgList_t;

typedef struct
{
    MAE_WChar           *pMelodyURL; //MAE_WChar using for play ringer URL
    IWidget             *pVolWdg;
    MenuItemId_e        eMenuItemID;
    SetRingToneVolume_e eVolLevel;
} PacManVolume_t;

typedef struct
{
    MenuItemId_e        eMenuItemID;
} PacManSound_t;

typedef struct
{
    IWidget *pIVolumeWdg;
}PacManVolumeViewWdgList_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

	//for get and set configuration items.
	PacManWndData_t *pWdgList;
	MenuItemId_e    eCITMenuItemID;
	ModelListener_t	ViewModelListener;
	SetRingToneVolume_e	eVolumn;
	u8 bActionControl;
    u8 bSoftkeyChange;
} PacManAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean PacManStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PacManKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret PacManConstructor(IApplet *pApplet, u32 evt, u32 nParam1, u32 nParam2);
MAE_Ret PacManDestructor(IApplet *pApplet, u32 evt, u32 nParam1, u32 nParam2);
MAE_Ret PacManWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void PacManDrawAllMap(PacManAppData_t *pThis);
void PacManDraw(PacManAppData_t *pThis);
static u32 PacManRGB(u8 nRed, u8 nGreen, u8 nBlue);
void PacManDrawPoint(PacManAppData_t *pThis, u32 u32clr, u16 x, u16 y);
void PacManDrawBitmap(PacManAppData_t *pThis, u32 pic, u16 x, u16 y);
void PacManDrawPartialMap(PacManAppData_t *pThis);
void PacManCountMove(void);
void PacManDrawRole(PacManAppData_t *pThis);
void PacManCountStatus(PacManAppData_t *pThis);
void PacManDrawStatus(PacManAppData_t *pThis);
void PacManDrawBlock(PacManAppData_t *pThis, u16 x, u16 y, u8 data);
void PacManGraphicText(PacManAppData_t *pThis, u32 x1, u32 y1, u32 x2, u32 y2, const u16 *pText, u32 FontType, u32 FontCat, u32 nFontColor, u32 nBackColor);
u32 PacManEnemyDirection(u8 i);
u32 PacManFind(u8 i);
u32 PacManShortestPath(u8 *tempBuf, u16 x1, u16 y1, u16 x2, u16 y2);
u32 PacManRandDirection(u8 i);
u32 PacManPlayMelody(PacManAppData_t *pThis, u8 type, u32 loop);
MAE_Ret PacManPlayAudio(PacManAppData_t *pThis, u32 realId, u32 loop);
boolean PacManAudioInit(PacManAppData_t *pThis);
void PacManVolumePlaySound(PacManAppData_t *pThis);
void PacManAudioExit(PacManAppData_t *pThis);
u8 PacManGetMapData(u8 *buf, u16 x, u16 y);
void PacManSetMapData(u8 *buf, u16 x, u16 y, u8 data);
void PacManTickCallBack(void *pUser);
void PacManStart(PacManAppData_t *pThis);
void PacManResume(PacManAppData_t *pThis);
void PacManPause(PacManAppData_t *pThis);
void PacManOptionMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret PacManCreateMainOptionMenuWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndMainOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManDestroyMainOptionMenuWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManOptionMenuBackHdl(PacManAppData_t *pThis, u32 nParam1, u32 nParam2);
MAE_Ret PacManCreateSettingsWnd(PacManAppData_t *pThis, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndVolumeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndCreateVolume(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndDestroyVolume(void *pCusHandle, void *pWndData);
MAE_Ret PacManCreateVolumeView(HWIN hWin, PacManVolumeViewWdgList_t *pWdgList);
void PacManVolumeViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel,IWidget *pWidget);
void PacManSetVolume(PacManAppData_t *pThis, u32 nVolumeLevel);
MAE_Ret PacManCreateSoundWnd(PacManAppData_t *pThis, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndSoundHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret PacManWndSettingsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void PacManSoundSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void PacManVolumeViewInterruptCb(void *pData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void PacManRestoreVolume(PacManAppData_t *pThis);
MAE_Ret PacManSaveVolume(PacManAppData_t *pThis);
void PacManSetSoundOff(PacManAppData_t *pThis);
void PacManRestoreSound(PacManAppData_t *pThis);
boolean PacManSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PacManResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

#endif /* __MMI_BMIAPP_PRIV_H__ */

