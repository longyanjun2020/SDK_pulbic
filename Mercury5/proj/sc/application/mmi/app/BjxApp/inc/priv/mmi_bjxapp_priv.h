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
* @file mmi_bjxapp_priv.h
*
* Class Id: CLSID_BJXAPP
*
* @version $Id$
*/
#ifndef __MMI_BJXAPP_PRIV_H__
#define __MMI_BJXAPP_PRIV_H__

#include "bjxapp_resource.h"
#ifdef __TOUCH_SCREEN_MMI__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_bjxapp.h"
#include "mmi_bjxapp_view_id.h"

#include "mmi_baseapplet.h"
#include "mmi_bjxapp_id.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_BJXAP_ALPHABET_NUMBER (27)
#define MMI_BJXAP_ROW_NUM  RS_BJX_SURNAME_NUM_ROW
#define MMI_BJXAP_COL_NUM  RS_BJX_SURNAME_NUM_COL

#define isAbc(alphabet) (((alphabet) <= MMI_BJX_EN_Z_UC) && ((alphabet) >= MMI_BJX_EN_A_UC))
#define transAlphabetToIdx(alphabet) ((alphabet) - MMI_BJX_EN_A_UC + 1)

#define ArraySize(X) (sizeof(X) / sizeof(X[0]))

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    MAE_WChar   u16DisplayChar;
    u16         u16Idx;
    u16         u16Visible;
    u16         u16Alphabet;
} BjxAppItemData_t;

typedef struct
{
    u16 KeyCode;
    u8 nMinIdx;
    u8 nMaxIdx;
} BjxAppKeyInfo_t;

typedef enum
{
    BJXAPP_MODE_ALPHABET,
    BJXAPP_MODE_SURNAME
} BjxAppMode_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;

    WidgetHandler_t SurnameHandler;
    WidgetHandler_t AlphabetHandler;

    ArrayClass_t *pSurnameArray;
    VectorClass_t *pAlphabetVector;
    IWidget *pSurnameGridWdg;
    IWidget *pAlphabetGridWdg;
    u16 SurnameCurrentIdx;
    u16 AlphabetCurrentIdx;

    IWidget *pSurnameTextWdg;
    IWidget *pAlphabetTextWdg;
    IWidget *pAlphbetBGCnt;
    
    // used for checking memory overwrite of tResponseInfo , pr0203355
    u32 u32UserDataAdr;
    u32 u32ListenerCBAdr;
    u32 u32RspCBAdr;
    // end
    
    MmiPhbBookType_e         s32Booktype;
    MmiPhbGroup_e             s32PhbGroup;
    boolean bIsSetFocusIdxBySurname;
    BjxAppMode_e eMode;
#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)    
    boolean bIsConvert;
    MAE_WChar u16FocusChar;  
#endif  
    BjxAppFindContactIdCbInfo_t tResponseInfo; // TODO: AP owner need to handle the response callback for Find Content Id later 

} BjxAppData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean BjxAppStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BjxAppKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret BjxAppDestructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);

/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret _BjxAppWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _BjxAppWndConvert(void *pCusHandle, void *pWndData);
MAE_Ret _BjxAppWndDestroyMain(void *pCusHandle, void *pWndData);

MAE_Ret _BjxAppWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

static void _BjxAppInit(BjxAppData_t* pThis, u32 nEvt, u32 nParam1, u32 nParam2);
static void _BjxAppMainKeyPressCB(BjxAppData_t* pThis, u32 nEvt, u32 nParam1, u32 nParam2);
static void _BjxAppFreeObjects(BjxAppData_t *pThis);
static MAE_Ret _BjxAppUpdateThemeColor(BjxAppData_t *pThis);

static void _BjxAppAlphabet(BjxAppData_t* pThis);
static void _BjxAppAlphabetHandlerFree(void *pData);
static void _BjxAppAlphabetItemDrawNotify(void *pUsrData, ItemInfo_st *pstItemInfo);
static boolean _BjxAppAlphabetHandler(void *pData, MAEEvent_t evt, u32 Param1, u32 Param2);
static void _BjxAppAlphabetViewFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
static void _BjxAppAlphabetViewFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

static void _BjxAppSurname(BjxAppData_t* pThis);
static void _BjxAppSurnameHandlerFree(void *pData);
static void _BjxAppSurnameItemDrawNotify(void *pUsrData, ItemInfo_st *pstItemInfo);
static boolean _BjxAppSurnameHandler(void *pData, MAEEvent_t evt, u32 Param1, u32 Param2);
static void _BjxAppSurnameViewFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
static void _BjxAppSurnameViewFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);

static boolean _BjxAppGridMove(BjxAppData_t *pThis, IWidget *pWdg, u16 *pCurrentIdx, u32 MoveDirection);
static boolean _BjxAppSetFocusIteminGrid(BjxAppData_t *pThis, IWidget *pWdg, u32 Idx);
static void _BjxAppGridItemDrawNotify(void *pUsrData, ItemInfo_st *pstItemInfo, IWidget *pWdg);
MAE_Ret BjxAppSetTheArray(BjxAppData_t *pThis);
static void _BjxAppFreeVectorItem(void *pData, void *pOwner);

#endif // __TOUCH_SCREEN_MMI__
#endif /* __MMI_BJXAPP_PRIV_H__ */
