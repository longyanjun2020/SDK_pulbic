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
* @file    mmi_puzzleapp_priv.h
* @version
* @brief   PUZZLE applet private header file
*
*/
#ifndef __MMI_PUZZLEAPP_PRIV_H__
#define __MMI_PUZZLEAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_mae_common_def.h"
#include "puzzleapp_resource.h"
#include "mmi_common_rai_id.h"

/*==================s===========================================*/
// Extern definition
/*=============================================================*/
#define MAX_GATE_LENGTH 30
#define MAX_GATE 10
#define MAX_STEP 10
#define LIMIT_TIME 2000
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    PUZZLE_SET_EASY = 3,
    PUZZLE_SET_MIDDLE, 
    PUZZLE_SET_HARD,
}PuzzleSetting_e;


typedef struct
{
	IWidget *pStartBgImage;
	IWidget *pStartBtn;
	IWidget *pExitBtn;
	IWidget *pSettingBtn;
} PuzzleStartWndData_t;

typedef struct
{
    IWidget *pShowPicBgImage;
    IWidget *pShowPicImage;
	IWidget *pShowPicText;
	IWidget *pShowPicExitBtn;
} PuzzleShowPicWndData_t;

typedef struct
{
	IWidget *pPlayBgImage;
	IWidget *pPlayPrevBtn;
    IWidget *pPlayShowBtn;
	IWidget *pPlaySetBtn;
	IWidget *pPlayNextBtn;
	IWidget *pPlayImage;
    IWidget *pPlayGateText;
    IWidget *pPlayStepText;
    IWidget *pPlaySucceedText;
    IWidget *pPlayBackBtn;
    IWidget *pPlaySoundsetBtn;
	IBitmap	  *pBitmap;
} PuzzlePlayWndData_t;

typedef struct
{
    IWidget *pSetBgImage;
    IWidget *pSetEasyBtn;
    IWidget *pSetMiddleBtn;
    IWidget *pSetHardBtn;
	IWidget *pSetExitBtn;
}PuzzleSettingWndData_t;


typedef struct
{
    APPLET_BASE_ELEMENTS;
    u32 matchnum;
    u32 x1;
    u32 y1;
    s32 PressPos;
    u32 ReleasePos;
    u32 BmpWidth;
    u32 BmpHeight;
    u32 level;
    u32 number;
    u32 gate;
    u32 step;
    s32 id;
    u32 rand[25];
    u32    nImageID[10];
    boolean  bSound;
    IBitmap           *pMidBmp[25];
    IWidget           *BmpWidget[25];
}PuzzleAppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/

boolean PuzzleStartCB(IApplet * pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret PuzzleConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret PuzzleDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PuzzleKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _StartWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PuzzleCreateStartWnd(void    *pCusHandle,void    *pWndData,u32     nWndInitParam);
void StartWndPlayButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void StartWndSettingButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PlayWndShowPicButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void StartWndExitButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PlayWndBackClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PlayWndSucceedCb(void *pApplet, void *pUserData);
MAE_Ret _PlayWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PuzzleCreatePlayWnd(void    *pCusHandle,void    *pWndData,u32     nWndInitParam);
MAE_Ret _PuzzleCreateSettingWnd(void    *pCusHandle,void    *pWndData,u32     nWndInitParam);
MAE_Ret _SettingWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
void Random(u32 a[], u32 n);
boolean PuzzleTSPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean PuzzleTSReleaseCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
u32 match ( void *pApplet , s8 num);
boolean PuzzleTSMoveCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _ShowPicWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PuzzleCreateShowPicWnd(void    *pCusHandle,   void    *pWndData,   u32     nWndInitParam);
void PlayWndPlaySoundsetBtnClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PlayWndPrevClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void PlayWndNextClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _UpdatePlayWnd(void    *pCusHandle,   void    *pWndData);
void SettingWndEasyButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void SettingWndMiddleButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void SettingWndHardButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
//void InitBitmapWdg(void *pApplet,u32 n);
#endif /* __MMI_PUZZLEAPP_PRIV_H__ */

