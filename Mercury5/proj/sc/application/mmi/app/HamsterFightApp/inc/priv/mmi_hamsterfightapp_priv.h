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
* @file    mmi_hamsterfightapp_priv.h
* @version
* @brief   HAMSTERFIGHT applet private header file
*
*/
#ifndef __MMI_HAMSTERFIGHTAPP_PRIV_H__
#define __MMI_HAMSTERFIGHTAPP_PRIV_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_hamsterfightapp_id.h"
#include "hamsterfightapp_resource.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_common_rai_id.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define HF_COUNT_DOWN_LAST_INTERVAL             800
#define HF_ANIMAL_APPEARANCE_INTERVAL           1800
#define HF_GAME_CYCLE_INTERVAL                  40
#define HF_HAMMER_CYCLE_INTERVAL                20
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct
{
    IWidget *pMenuButtonWdg;
    IWidget *pMenuSelectLeftBtnWdg;
    IWidget *pMenuSelectRightBtnWdg;
    HFMenuWdgList_e eMenuBtnName;
} HFMenuWdgList_t;

typedef struct
{
    IWidget *pGameBackBtnWdg;
    IWidget *pGameBGImgWdg;
    IWidget *pAnimalMotionWdg;
    IWidget *pGrassShelterImgWdg;
    IWidget *pHammerMotionImgWdg;
    IWidget *pHitSignImgWdg;
    IWidget *pComboNumberImgWdg_1;
    IWidget *pComboNumberImgWdg_10;
    IWidget *pGameMultiSignImgWdg;
    IWidget *pSparkImgWdg[3];
    IWidget *pHPImgWdg[5];
    IWidget *pCountDownMotionImgWdg;
    IWidget *pLevelNumberImgWdg;
    IWidget *pSmallHamsterSignImgWdg;
    IWidget *pHamsterNumberImgWdg_1;
    IWidget *pHamsterNumberImgWdg_10;
    IWidget *pWinGameImgWdg;
    IWidget *pLoseGameImgWdg;
} HFGameWdgList_t;

typedef enum
{
    COUNTDOWN_PROCESS,
    GAME_PROCESS,
    LOSE_PROCESS,
    WIN_PROCESS
} HFProcessState_e;

typedef struct
{
    u16      u16HFGameLevel;
    u16      u16RemainingHP;
    u16      u16ComboNumber;
    u16      u16RemainingHamsterNumber;
    u16      u16CountDownMotionNumber;
    u16      u16WinGameMotionNumber;
    u16      u16LoseGameMotionNumber;
//    u32      u32CountDownMotionImgID[5];
    u32      u32CountDownMotionImgID;
    u32      u32LevelNumberImgID;
    u32      u32AnimalMotionImgID;
    u32      u32GrassShelterImgID;
    u32      u32ComboNumberImg_1_ID;
    u32      u32ComboNumberImg_10_ID;
    u32      u32HPImgID;
    u32      u32HamsterNumberImg_1_ID;
    u32      u32HamsterNumberImg_10_ID;
    u16      u16HamsterNumberTobeHit;
    boolean  bISHamster;
    boolean  bISAnimalBeHit;
    u16      u16HammerOnHoleNumber;
    boolean  bIsAnimalMotionHighest;
    u16      u16AnimalMotionNumber;
    u16      u16AnimalMotionLevel;
    u16      u16Animal_Rand_Pos_Index;
    u16      u16AnimalPosX;
    u16      u16AnimalPosY;
    u16      u16GrassShelterPosX;
    u16      u16GrassShelterPosY;
    u16      u16HammerEffectNumber;
    HFProcessState_e eProcessState;
    HFGameWdgList_t tGameWdg;
} HFGameWndData_t;

typedef struct
{
    IWidget *pOptionsFadeoutWdg;
    IWidget *pOptionsTxtSoundWdg;
    IWidget *pOptionsImgFrameWdg;
    IWidget *pOptionsSoundSwitchBtnWdg;
    IWidget *pOptionsTxtStartCameraWdg;
    IWidget *pOptionsCameraBtnWdg;
    IWidget *pOptionsTxtChangePicWdg;
    IWidget *pOptionsChangePicImgWdg;
//    IWidget *pOptionsTxtNoticeWdg;
    IWidget *pOptionsBackBtnWdg;
	IWidget *pOptionsImgDefaultPic;
	IWidget *pOptionsTxtDefaultPic;
	IWidget *pOptionsBtnBackDefault;
}HFOptionsWndData_t;

typedef struct
{
    IWidget *pHelpFadeoutWdg;
    IWidget *pHelpTxtContentWdg;
    IWidget *pHelpTxtNoticeWdg;
    IWidget *pHelpTxtRuleWdg;
    IWidget *pHelpImgHitWdg;
    IWidget *pHelpImgMultiSignWdg;
    IWidget *pHelpImgGetHPWdg;
    IWidget *pHelpBackBtnWdg;
} HFHelpWdgList_t;

typedef struct
{
	APPLET_BASE_ELEMENTS;
    boolean bIsSoundOn;
    MAE_LANG_CODE_e eLangCode;

    MAE_WChar *pImageURL;
    IImage * pIImage;
} HFAppData_t;
/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean HFStartCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean HFKeyPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret HFTSPressCB(IApplet *pApplet, MAEEvent_t nEvt, u32 param1, u32 param2);
boolean HFSuspendCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean HFResumeCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret HFDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
/*=============================================================*/
// Local function definition
/*=============================================================*/
void _HFGetImagePtrFromUrl(HFAppData_t *pThis);
void _HFStartCameraButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _HFGetFileByBrowseCb(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
static void _HFLaunchFileMgrToGetImage(HFAppData_t *pThis);
void _HFWdgImageLinkImageClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pWidget);

MAE_Ret _HFCreateMenuWnd(void* pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _HFMenuWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData,u32 nWndInitParam);

MAE_Ret _HFCreateOptionsWnd(void* pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _HFOptionsWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData,u32 nWndInitParam);

MAE_Ret _HFCreateHelpWnd(void* pCusHandle, void *pWndData,u32 nWndInitParam);
MAE_Ret _HFHelpWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData,u32 nWndInitParam);

MAE_Ret _HFCreateGameWnd(void* pCusHandle, void *pWndData,u32 nWndInitParam);
MAE_Ret _HFGameWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData,u32 nWndInitParam);

MAE_Ret _HFPlayNewGame(void* pCusHandle);
MAE_Ret _HFPlayContinueGame(void* pCusHandle);

void _HFCreateCountDownMotionTimerCB(void *pData);
void _HFChooseAnimalTimerCB(void *pData);
void _HFCreateAnimalActionTimerCB(void *pData);
void _HFCreateHammerEffectTimerCB(void* pData);
void _HFCreateLoseGameTimerCB(void *pData);
void _HFCreateWinGameTimerCB(void *pData);

MAE_Ret _HFCreateHP(void* pCusHandle);
MAE_Ret _HFCreateGetHP(void* pCusHandle);
MAE_Ret _HFCreateComboNumber(void* pCusHandle);
MAE_Ret _HFCreateHamsterNumber(void* pCusHandle);
void _HFPressActions(IApplet *pApplet);

void _HFSetGameRecordToConfig(HFGameWndData_t *pGameData);
void _HFSetInitialGameRecordToConfig(HFGameWndData_t *pGameData);
void _HFGetGameRecordFromConfig(HFGameWndData_t *pGameData);
MAE_Ret _HFGameWdgConstruct(void* pCusHandle);
MAE_Ret _HFGameWdgDestroy(void* pCusHandle);
void _HFCreateTimer(HFAppData_t *pThis);
void _HFCancelTimer(HFAppData_t *pThis);

void _HFOptionsSoundButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _HFMenuButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _HFSelectButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _HFReturnButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

#endif /* __MMI_HAMSTERFIGHTAPP_PRIV_H__ */
