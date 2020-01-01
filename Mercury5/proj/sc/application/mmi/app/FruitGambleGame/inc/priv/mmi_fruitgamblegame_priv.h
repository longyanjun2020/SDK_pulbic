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
* @file    mmi_fruitgamblegame_priv.h
* @version
* @brief   fruit gamble game private header file
*
*/
#ifndef __MMI_FRUITGAMBLEGAME_PRIV_H__
#define __MMI_FRUITGAMBLEGAME_PRIV_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_fruitgamblegame_id.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_header.h"
#include "mmi_mae_shell.h"
#include "mmi_clstbl.h"

#ifdef __NATIVE_GAME_MMI_FRUIT__
#include "FruitGambleGame_resource.h"
#include "mmi_FruitGambleGame_rs.h"
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
#define GAME_FRUITGAMBLE_SPLASH_TIMER 1000
#define GAME_FRUITGAMBLE_IDLE_TIMER 1000
#define GAME_FRUITGAMBLE_QUICK_RUN_TIMER 100
#define GAME_FRUITGAMBLE_SLOW_RUN_TIMER 400
#define GAME_FRUITGAMBLE_SHOW_RESULT_TIMER COMMON_DIALOG_AUTOCLOSE_TIME
#define GAME_FRUITGAMBLE_GUESS_TIMER 200

#define GAME_FRUITGAMBLE_START_STEP 5
#define GAME_FRUITGAMBLE_QUICK_RUN_STEP 24    // GAME_FRUITGAMBLE_NUM_PLAY_ITEM*2
#define GAME_FRUITGAMBLE_RUN_STEP 1
#define GAME_FRUITGAMBLE_IDLE_STEP 5
#define GAME_FRUITGAMBLE_TRANS_TO_SLOW_STEP 5
#define GAME_FRUITGAMBLE_GUESS_RUN_STEP 10

#define GAME_FRUITGAMBLE_NUM_PLAY_ITEM 24

#define GAME_FRUITGAMBLE_GUESS_WIN_RATIO 2

#define GAME_FRUITGAMBLE_NUM_FIRST_ITEM 0
#define GAME_FRUITGAMBLE_NUM_LAST_ITEM 7
#define GAME_FRUITGAMBLE_MAX_BET 9
#define GAME_FRUITGAMBLE_MIN_BET 0
#define GAME_FRUITGAMBLE_SIZE_TMP_STR 20

#define GAME_FRUITGAMBLE_RESULT_NONE 100

#define GAME_FRUITGAMBLE_PROB_MAX 100
#define	GAME_FRUITGAMBLE_ITEM_ONEMORE_PROB 5											  // 5                     
#define	GAME_FRUITGAMBLE_ITEM_SKELETON_PROB (GAME_FRUITGAMBLE_ITEM_ONEMORE_PROB + 5)      // 5~10
#define GAME_FRUITGAMBLE_ITEM_APPLE_PROB (GAME_FRUITGAMBLE_ITEM_SKELETON_PROB + 20)       // 10~30
#define	GAME_FRUITGAMBLE_ITEM_ORANGE_PROB (GAME_FRUITGAMBLE_ITEM_APPLE_PROB + 17)         // 30~47
#define	GAME_FRUITGAMBLE_ITEM_SUIKA_PROB (GAME_FRUITGAMBLE_ITEM_ORANGE_PROB + 15)         // 47~62
#define	GAME_FRUITGAMBLE_ITEM_MELON_PROB (GAME_FRUITGAMBLE_ITEM_SUIKA_PROB + 13)          // 62~75
#define	GAME_FRUITGAMBLE_ITEM_DINGDONG_PROB (GAME_FRUITGAMBLE_ITEM_MELON_PROB + 10)       // 75~85
#define	GAME_FRUITGAMBLE_ITEM_STAR_PROB (GAME_FRUITGAMBLE_ITEM_DINGDONG_PROB + 7)         // 85~92
#define	GAME_FRUITGAMBLE_ITEM_SEVEN_PROB (GAME_FRUITGAMBLE_ITEM_STAR_PROB + 5)            // 92~97
#define	GAME_FRUITGAMBLE_ITEM_BAR_PROB (GAME_FRUITGAMBLE_ITEM_SEVEN_PROB + 3)             // 97~100

#define GAME_FRUITGAMBLE_WIN_STR L"$"
#define GAME_FRUITGAMBLE_BET_STR L"$"

// storage related

#define GAME_FRUITGAMBLE_RECORDS_DISPLAY_NUM_PER_PAGE 8

enum
{
	GAME_FRUITGAMBLE_APPLE = 0,
	GAME_FRUITGAMBLE_ORANGE,
	GAME_FRUITGAMBLE_DINGDONG,
	GAME_FRUITGAMBLE_MELON,
	GAME_FRUITGAMBLE_SUIKA,
	GAME_FRUITGAMBLE_STAR,
	GAME_FRUITGAMBLE_SEVEN,
	GAME_FRUITGAMBLE_BAR,
	GAME_FRUITGAMBLE_SKELETON,
	GAME_FRUITGAMBLE_ONEMORE
};

enum
{
    GAME_FRUITGAMBLE_NONE = 0,
    GAME_FRUITGAMBLE_TRIGGER_SPLASH,
    GAME_FRUITGAMBLE_RUN,
    GAME_FRUITGAMBLE_IDLE_START,
    GAME_FRUITGAMBLE_SHOW_RESULT,
    GAME_FRUITGAMBLE_GUESS_BIG_SMALL_UPDATE

}FruitGambleGameSuspendStatus_e;

#define GAME_FRUITGAMBLE_NUM_ALL_ITEM 10
#define GAME_FRUITGAMBLE_INIT_MONEY 50
#define GAME_FRUITGAMBLE_RESULT_NONE 100

#define GAME_FRUITGAMBLE_WIN_RATIO_APPLE 1
#define	GAME_FRUITGAMBLE_WIN_RATIO_ORANGE 2
#define	GAME_FRUITGAMBLE_WIN_RATIO_DINGDONG 3
#define	GAME_FRUITGAMBLE_WIN_RATIO_SUIKA 4
#define	GAME_FRUITGAMBLE_WIN_RATIO_MELON 4
#define	GAME_FRUITGAMBLE_WIN_RATIO_STAR 6
#define	GAME_FRUITGAMBLE_WIN_RATIO_SEVEN 8
#define	GAME_FRUITGAMBLE_WIN_RATIO_BAR 20

typedef struct
{
	IModel		*pIModel;
} Mmi_GameFruitGamble_Button_Tbl_t;

typedef struct
{
    IWidget *pSplashAbsContainer;
    IWidget *pSplashImageWdg;
    IWidget *pSplashTextWdg;
}FruitGambleGameSplashWndWdgList_t;

typedef struct
{
    IWidget *pPlayAbsContainer;
    IWidget *pTabletImageWdg;
    IWidget *pSelectFrameImageWdg;
    IWidget *pFocusImageWdg;
    IWidget *pPlayYourMoneyTextWdg;
    IWidget *pPlayInputBarTextWdg;
    IWidget *pPlayInputSevenTextWdg;
    IWidget *pPlayInputStarTextWdg;
    IWidget *pPlayInputSuikaTextWdg;
    IWidget *pPlayInputMelonTextWdg;
    IWidget *pPlayInputDingdongTextWdg;
    IWidget *pPlayInputOrangeTextWdg;
    IWidget *pPlayInputAppleTextWdg;
    IWidget *pPlayInputBarButtonWdg;
    IWidget *pPlayInputSevenButtonWdg;
    IWidget *pPlayInputStarButtonWdg;
    IWidget *pPlayInputSuikaButtonWdg;
    IWidget *pPlayInputMelonButtonWdg;
    IWidget *pPlayInputDingdongButtonWdg;
    IWidget *pPlayInputOrangeButtonWdg;
    IWidget *pPlayInputAppleButtonWdg;
}FruitGambleGamePlayWndWdgList_t;

typedef struct
{
    IWidget *pResultAbsContainer;
    IWidget *pResultFadeoutWdg;
    IWidget *pResultImageWdg;
    IWidget *pResultTextWdg;
}FruitGambleGameResultWndWdgList_t;

typedef struct
{
    IWidget *pGuessAbsContainer;
    IWidget *pGuessBGImageWdg;
    IWidget *pGuessFrameImageWdg;
    IWidget *pGuessFadeoutWdg;
    IWidget *pGuessTextWdg;
}FruitGambleGameGuessWndWdgList_t;

typedef struct
{
	u16		nXPos; //Use datatype u16, because the MAX Xpos is 278. 
	u16		nYPos;  //Use datatype u16, because Ypos is 294.
	u32		nImgId;
} FruitGambleItemPos_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;

    u8              nItemBet[GAME_FRUITGAMBLE_NUM_ALL_ITEM];
    s8              nItemResultType;
    s8              nItemChgToSlow;
    s8              nItemResult;
    s8              nStopCounter;
    s8              nNeedQuickRunCounter;
    s8              nRunCounter;
    s16             nCurSelectItem;
    s16             nLastSelectItem;
    s16				  nCurPlayItem;
    s16             nLastPlayItem;
    s32             nMoney;
    s32             nWinMoney;
	
    boolean         bIsCalFinalStep;
    boolean         bIsBig;
    boolean         bIsBusy;
    boolean         bIsResultBig;
    boolean         bIsSelectBig;
    boolean         bIsRunning;

#ifdef __TOUCH_SCREEN_MMI__
	Mmi_GameFruitGamble_Button_Tbl_t atButtonTbl[GAME_FRUITGAMBLE_NUM_ALL_ITEM];
	ModelListener_t	atButtonMdl[GAME_FRUITGAMBLE_NUM_ALL_ITEM];
#endif
} FruitGambleGameAppData_t;
/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean FruitGambleGameStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitGambleGameKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitGambleGameTouchScreenCB(IApplet* pData, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean FruitGambleGameSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitGambleGameResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FruitGambleGameStopCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

MAE_Ret FruitGambleGameSplashWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void FruitGambleGameTriggerSplashEndCB(void *data);
MAE_Ret FruitGambleGamePlayWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FruitGambleGameDrawTextWidgetByInt(FruitGambleGameAppData_t *pThis, IWidget *pIWidget, u32 u32WidgetID, s32 s32Int);
void  FruitGambleGameTriggerIdleStartCB(FruitGambleGameAppData_t *pThis);

#ifdef __TOUCH_SCREEN_MMI__
void FruitGambleGameButtonMdl(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif

void FruitGambleDrawSeletTextWidget(FruitGambleGameAppData_t *pThis);
void FruitGambleSetResetKey(FruitGambleGameAppData_t *pThis);
void FruitGambleGameDataReset(FruitGambleGameAppData_t *pThis);
void FruitGambleDrawSelectByIntTextWidget(FruitGambleGameAppData_t *pThis, u8 i);
void FruitGambleRunInit(FruitGambleGameAppData_t *pThis);
void FruitGambleRun(FruitGambleGameAppData_t *pThis);
void FruitGambleRunRandomResult(FruitGambleGameAppData_t *pThis);
MAE_Ret  FruitGambleResultWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret FruitGambleDrawImageWidget(FruitGambleGameAppData_t *pThis, IWidget *pIImageWidget, u32 widgetID, u32 imageID);
void FruitGambleShowResult(FruitGambleGameAppData_t *pThis);
MAE_Ret  FruitGambleGuessBigSmallWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void  FruitGambleGuessBigSmallUpdate(FruitGambleGameAppData_t *pThis);
void  FruitGambleGuessBigSmallSelect(FruitGambleGameAppData_t *pThis);
#endif /* __MMI_FRUITGAMBLEGAME_PRIV_H__ */
