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
* @file    mmi_big2_priv.h
* @version
* @brief   BIG2 applet private header file
*
*/
#ifndef __MMI_BIG2_PRIV_H__
#define __MMI_BIG2_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_big2_id.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_vtm.h"
#include "mmi_srv_header.h"
#include "mmi_mae_shell.h"
#include "mmi_clstbl.h"

#ifdef __NATIVE_GAME_MMI_BIG2__
#include "Big2_resource.h"
#include "mmi_Big2_rs.h"
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
#define NATIVEGAME_BIG2_TIMER_TICK						300
#define START_PLAY_POSITION 0

/**********************************************************for common structure**********************************************************/

enum
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
    MMI_AUDIO_PLAY_ONCE,
    MMI_AUDIO_PLAY_LOOP
};


/**********************************************************for Big2 game structure**********************************************************/
#define GAME_4_CARD_SINGLE_VALUE		(1)
#define GAME_4_CARD_PAIR_VALUE			(2)
#define GAME_4_CARD_TRIPLE_VALUE		(3)
#define GAME_4_CARD_STRAIGHT_VALUE		(5)
#define GAME_4_CARD_FULLHOUSE_VALUE		(6)
#define GAME_4_CARD_IRON_VALUE			(8)
#define GAME_4_CARD_FLUSH_VALUE			(10)

#define GAME_4_MAX_PLAY_ENTITY			300

#define GAME_4_INIT_SCORE		200

enum
{
    GAME_4_WAIT_PLAY_TICK	=   3,
    GAME_4_WAIT_PASS_TICK	=   3,
    GAME_4_WAIT_SHOW_TICK	=   3
};

#define GAME_4_TRASH_TALK_NUM	3

#define GAME_4_MELODY_NUMBER	6

typedef enum
{
    GAME_4_MELODY_CAT,
    GAME_4_MELODY_DOG,
    GAME_4_MELODY_PIG,
    GAME_4_MELODY_PLAYER,
    GAME_4_MELODY_DEAL,
    GAME_4_MELODY_CHIP,
} Big2MelodyType_e;


typedef struct
{
    u32 playValue;
    u32 leftValue;
    u8 type;
    u8 num;
    u8 card[5];
    u8 leftCard[13];
} Big2PlayEntity_t;

typedef enum
{
    GAME_4_BUTTON_PLAY,
    GAME_4_BUTTON_PASS,
    GAME_4_BUTTON_NEXTGAME,
} Big2ButtonType_e;

typedef enum
{
    GAME_4_STATE_WAIT_PLAY,
    GAME_4_STATE_PLAY,
    GAME_4_STATE_WAIT_SHOW_WIN,
    GAME_4_STATE_SHOW_WIN,
} Big2State_e;

typedef enum
{
    GAME_4_CARD_PLAY_NONE,
    GAME_4_CARD_PLAY_SINGLE,
    GAME_4_CARD_PLAY_PAIR,
    GAME_4_CARD_PLAY_TRIPLE,
    GAME_4_CARD_PLAY_STRAIGHT,
    GAME_4_CARD_PLAY_FULLHOUSE,
    GAME_4_CARD_PLAY_IRON,
    GAME_4_CARD_PLAY_FLUSH,
} Big2CardPlay_e;

typedef struct
{
    u8 num;
    u8 card[4];
    u8 symbol[4];
} Big2CardGroup_t;

typedef struct
{
    u8 num;
    u8 selectNum;
    u8 card[13];
    u8 selected[13];
} Big2CardInHand_s;

typedef struct
{
    u32 value;
    u8 card[5];
    u8 num;
    u8 player;
    u8 type;
} Big2CardPlay_t;

typedef struct
{
    Big2CardInHand_s cardInHand[4];
    Big2CardPlay_t tCardPlay;
    u32 nBackColor;
    s16 score[4];
    s16 oldScore[4];
    boolean bRefresh;
    boolean bCanPlay;
    u8 nState;
    u8 nWaitTime;
    u8 nWinner;
    u8 nCurrentPlayer;
    boolean bIsFinished;
    boolean bIsFirstPlay;
    u32 nTempVolLevel;
    boolean bIsSuspend;
    boolean bSoundOn;
    SetRingToneVolume_e	eSetVolumn;
} Big2Data_t;


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
}Big2WndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
} Big2OptionMenuWndData_t;

typedef struct
{
    IWidget *pPMLIMenuWdg;
    IWidget *pIPhoneMenuWidget;
    IWidget *pIConnectMenuWidget;
    IWidget *pITabWidget;
    IWidget *pITitleWidget;
}Big2SettingsViewWdgList_t;

typedef struct
{
    MAE_WChar           *pMelodyURL; //MAE_WChar using for play ringer URL
    IWidget             *pVolWdg;
    MenuItemId_e        eMenuItemID;
    CFGItemID_e         eCFGItemID;
    SetRingToneVolume_e eVolLevel;
} Big2Volume_t;

typedef struct
{
    MenuItemId_e        eMenuItemID;
} Big2Sound_t;

typedef struct
{
    IWidget *pIVolumeWdg;
}Big2VolumeViewWdgList_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    //for get and set configuration items.
    Big2WndData_t *pWdgList;
    MenuItemId_e eCITMenuItemID;
} Big2AppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean Big2StartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean Big2KeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret Big2Destructor(IApplet *pApplet, u32 evt, u32 nParam1, u32 nParam2);
boolean Big2TouchScreenCB(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean Big2SuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean Big2ResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret Big2WndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

u32 Big2RGB(u8 nRed, u8 nGreen, u8 nBlue);
void Big2DrawBitmap(Big2AppData_t *pThis, u32 pic, u16 x, u16 y);
void Big2GraphicText(Big2AppData_t *pThis, u32 x1, u32 y1, u32 x2, u32 y2, const u16 *pText, u32 FontType, u32 FontCat, u32 FontColor, u32 BackColor);
void Big2Draw(Big2AppData_t *pThis);
void Big2DrawFoe(Big2AppData_t *pThis, u8 index);
void Big2DrawButton(Big2AppData_t *pThis, u8 type);
u8 Big2FindAvail(Big2PlayEntity_t *pTempPlayEntity, u8 type, u32 compareValue, u8 cardNum, u8 * cards, u8 getLeftValue);
u32 Big2PlayMelody(Big2AppData_t *pThis, u8 type, u32 loop);
void Big2SortCard(u8 *cards, u8 num);
void Big2Shuffle(void);
void Big2DrawUserCard(Big2AppData_t *pThis, u8 index);
void Big2CheckWin(Big2AppData_t *pThis, u8 index, u8 play);
void Big2DrawResult(Big2AppData_t *pThis);
void Big2DrawPlayCard(Big2AppData_t *pThis);
u32 Big2GetCardValue(u8 type, u8 *card);
u8 Big2DecideCardType(u32 *ret);
u32 Big2CountCardValue(u8 num, u8 *cards);
u8 Big2CheckPlayReasonable(u32 oldValue, u32 leftValue, u32 playValue, u8 oldNum, u8 leftNum, u8 *oldCard, u8 *leftCard, u8 type, u8 playType);
u8 Big2FoePlay(Big2AppData_t *pThis, u8 index);
void Big2CheckPlay(Big2AppData_t *pThis);
void Big2PlayCard(Big2AppData_t *pThis);
void Big2TouchEvent(Big2AppData_t *pThis, s32 x, s32 y, MAE_EventId EventType);
void Big2Start(Big2AppData_t *pThis);
void Big2TickCallBack(void *pUser);
MAE_Ret Big2PlayAudio(Big2AppData_t *pThis, u32 realId, u32 loop);
boolean Big2AudioInit(Big2AppData_t *pThis);
void Big2VolumePlaySound(Big2AppData_t *pThis);
void Big2OptionMenuSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret Big2CreateMainOptionMenuWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndMainOptionMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2DestroyMainOptionMenuWnd(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2OptionMenuBackHdl(Big2AppData_t *pThis, u32 nParam1, u32 nParam2);
MAE_Ret Big2CreateSettingsWnd(Big2AppData_t *pThis, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndVolumeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndCreateVolume(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndDestroyVolume(void *pCusHandle, void *pWndData);
MAE_Ret Big2CreateVolumeView(HWIN hWin, Big2VolumeViewWdgList_t *pWdgList);
void Big2VolumeViewModelListener(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nCurrentLevel,IWidget *pWidget);
void Big2VolumeViewInterruptCb(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
void Big2SetVolume(Big2AppData_t *pThis, u32 nVolumeLevel);
MAE_Ret Big2CreateSoundWnd(Big2AppData_t *pThis, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndSoundHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret Big2WndSettingsHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void Big2SoundSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void Big2RestoreVolume(Big2AppData_t *pThis);
MAE_Ret Big2SaveVolume(Big2AppData_t *pThis);
void Big2SetSoundOff(Big2AppData_t *pThis);
void Big2RestoreSound(Big2AppData_t *pThis);
#endif /* __MMI_BIG2_PRIV_H__ */
