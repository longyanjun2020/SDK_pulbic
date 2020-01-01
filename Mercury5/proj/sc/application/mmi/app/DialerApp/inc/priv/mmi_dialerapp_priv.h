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
* @file    mmi_dialerapp_priv.h
* @version
* @brief   DialerApp applet private header file
*
*/

#ifndef __MMI_DIALERAPP_PRIV_H__
#define __MMI_DIALERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_dialerapp.h"
#include "mmi_srv_header.h"
#include "mmi_common_dialog.h"
#include "mmi_common_vtm.h"
#include "mmi_launcher_calllog.h"
#include "mmi_launcher_cc.h"
#ifdef __APP_VIDEO_TELEPHONY__
#include "mmi_launcher_videotelephony.h"
#endif
#include "mmi_launcher_em.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_security.h"
#include "mmi_launcher_shortcut.h"
#include "mmi_launcher_ussd.h"
#include "mmi_launcher_javafactory.h"
#include "mmi_dialerapp_id.h"
#include "dialerapp_resource.h"

#ifdef __APP_MMI_3D_DIALER__
#include "mgl_Core_Types.h"
#include "mgl_Texture_ImgMgr.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define DIALERAPP_DIALINGVIEW_COLOR MAKE_RGB    (2, 187, 240)
#define DIALERAPP_MAX_INPUT_BYTE                160 //Maximum allowable input bytes (80 characters)
#define DIALERAPP_SHORTCUTTEXT_PRETEXT_LENGTH    4    /* [#: ] + 0 */

#ifdef __FEATURE_VECTOR_FONT__

#ifdef __APP_MMI_SMALLROM__
#define DIALERAPP_ONE_LINE_CHAR_LENGTH ((u32)(FONTBASE_IsVectorFontExist()? (15*2):(9*3)))
#else
#define DIALERAPP_ONE_LINE_CHAR_LENGTH ((u32)(FONTBASE_IsVectorFontExist()? (15*2):(9*2)))
#endif
#else

#ifdef __APP_MMI_SMALLROM__
#define DIALERAPP_ONE_LINE_CHAR_LENGTH ( 9*3)
#else
#define DIALERAPP_ONE_LINE_CHAR_LENGTH ( 9*2)
#endif

#endif //__FEATURE_VECTOR_FONT__

#ifdef __APP_MMI_3D_DIALER__
#define DIALERAPP_3D_TRANSITION_TYPE_CUBE 0
#define DIALERAPP_3D_TRANSITION_TYPE_BOX 1
#endif //__APP_MMI_3D_DIALER__

// [3DUI][TODO] for support auto rotate
#ifdef __APP_MMI_DIALER_BOX_TRANSITION__
#define RS_DIALERAPP_BOX_DIALER_PLANE1_START_POS_WIDTH      DIALERAPP_BOX_DIALER_PLANE1_START_POS_WIDTH
#define RS_DIALERAPP_BOX_DIALER_PLANE1_START_POS_HEIGHT     DIALERAPP_BOX_DIALER_PLANE1_START_POS_HEIGHT
#define RS_DIALERAPP_BOX_DIALER_PLANE1_START_POS_X	        DIALERAPP_BOX_DIALER_PLANE1_START_POS_X
#define RS_DIALERAPP_BOX_DIALER_PLANE1_START_POS_Y	        DIALERAPP_BOX_DIALER_PLANE1_START_POS_Y
#define RS_DIALERAPP_BOX_DIALER_PLANE1_START_POS_Z	        DIALERAPP_BOX_DIALER_PLANE1_START_POS_Z
#define RS_DIALERAPP_BOX_DIALER_PLANE2_START_POS_X	        DIALERAPP_BOX_DIALER_PLANE2_START_POS_X
#define RS_DIALERAPP_BOX_DIALER_PLANE2_START_POS_Y	        DIALERAPP_BOX_DIALER_PLANE2_START_POS_Y
#define RS_DIALERAPP_BOX_DIALER_PLANE2_START_POS_Z	        DIALERAPP_BOX_DIALER_PLANE2_START_POS_Z
#define RS_DIALERAPP_BOX_DIALER_PLANE2_START_POS_WIDTH	    DIALERAPP_BOX_DIALER_PLANE2_START_POS_WIDTH
#define RS_DIALERAPP_BOX_DIALER_PLANE2_START_POS_HEIGHT	    DIALERAPP_BOX_DIALER_PLANE2_START_POS_HEIGHT
#define RS_DIALERAPP_BOX_DIALER_PLANE3_START_POS_HEIGHT	    DIALERAPP_BOX_DIALER_PLANE3_START_POS_HEIGHT
#define RS_DIALERAPP_BOX_DIALER_PLANE4_START_POS_WIDTH	    DIALERAPP_BOX_DIALER_PLANE4_START_POS_WIDTH
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_WIDTH	    DIALERAPP_BOX_DIALER_FLOWER_START_POS_WIDTH
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_HEIGHT	    DIALERAPP_BOX_DIALER_FLOWER_START_POS_HEIGHT
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_X	        DIALERAPP_BOX_DIALER_FLOWER_START_POS_X
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_Y	        DIALERAPP_BOX_DIALER_FLOWER_START_POS_Y
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_Z	        DIALERAPP_BOX_DIALER_FLOWER_START_POS_Z
#define RS_DIALERAPP_BOX_DIALER_NUMBER_START_POS_WIDTH	    DIALERAPP_BOX_DIALER_NUMBER_START_POS_WIDTH
#define RS_DIALERAPP_BOX_DIALER_NUMBER_START_POS_HEIGHT	    DIALERAPP_BOX_DIALER_NUMBER_START_POS_HEIGHT
#define RS_DIALERAPP_BOX_DIALER_NUMBER_START_POS_X	        DIALERAPP_BOX_DIALER_NUMBER_START_POS_X
#define RS_DIALERAPP_BOX_DIALER_NUMBER_START_POS_Y	        DIALERAPP_BOX_DIALER_NUMBER_START_POS_Y
#define RS_DIALERAPP_BOX_DIALER_NUMBER_START_POS_Z	        DIALERAPP_BOX_DIALER_NUMBER_START_POS_Z
#define RS_DIALERAPP_BOX_DIALER_PLANE_START_POS_DY	        DIALERAPP_BOX_DIALER_PLANE_START_POS_DY
#define RS_DIALERAPP_BOX_DIALER_FLOWER_START_POS_DY	        DIALERAPP_BOX_DIALER_FLOWER_START_POS_DY
#define RS_DIALERAPP_BOX_DIALER_PLANE_NUM	                DIALERAPP_BOX_DIALER_PLANE_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE1_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE1_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE2_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE2_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE3_1_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE3_1_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE3_2_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE3_2_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE3_3_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE3_3_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE3_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE3_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE4_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE4_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE5_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE5_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE6_FRAME_NUM	        DIALERAPP_BOX_DIALER_PHASE6_FRAME_NUM
#define RS_DIALERAPP_BOX_DIALER_PHASE0_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE0_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE1_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE1_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE2_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE2_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE3_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE3_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE4_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE4_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE5_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE5_FRAME_TOTALNUM
#define RS_DIALERAPP_BOX_DIALER_PHASE6_FRAME_TOTALNUM	    DIALERAPP_BOX_DIALER_PHASE6_FRAME_TOTALNUM
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/
#ifdef __SMART_DIALER__
typedef enum
{
	MMI_DIALER_AP_SIM_BOTH 		= 0,
	MMI_DIALER_AP_SIM_NO_SIM1	= 1,
	MMI_DIALER_AP_SIM_NO_SIM2 	= 2,
	MMI_DIALER_AP_SIM_NO_SIM 	= 3,
}DialerApp_Sim_Type_e;
#endif

typedef enum
{
    DIALERAPP_BASE_STATUSBAR,
    DIALERAPP_BASE_SOFTKEY
}DialerApp_BaseWdg_ID_e;

typedef enum
{
    DIALERAPP_MSG_SMS,
    DIALERAPP_MSG_MMS
}DialerApp_Msg_Type_e;


typedef enum
{
#ifndef __DIALAPP_SMALLROM__
	DIALERAPP_TS_TOUCHGRID3,
#endif
    DIALERAPP_TS_TOUCHGRID1,
    DIALERAPP_TS_TOUCHGRID2
}DialerApp_TS_Grid_e;

typedef enum
{
    DIALERAPP_AP_NORMAL,
    DIALERAPP_AP_EMBEDDED_DIALINGVIEW
}DialerApp_AP_Type_e;

typedef enum
{
  DIALERAPP_CALL_TYPE_EMERGENCYCall =0,
  DIALERAPP_CALL_TYPE_NORMALCall,
#ifdef __APP_VIDEO_TELEPHONY__
  DIALERAPP_CALL_TYPE_VIDEOCall,
#endif
#ifdef __IP_CALL_MMI__
  DIALERAPP_CALL_TYPE_IPCall,
#endif
}DIALERAPP_CALL_TYPE_e;

#ifdef __WLAN_MMI__
typedef enum
{
    DIALERAPP_LAUNCH_WLAN_NONE,
    DIALERAPP_LAUNCH_WLAN_ALL_TEST,
    DIALERAPP_LAUNCH_WLAN_RX_TEST,
	DIALERAPP_LAUNCH_WLAN_TX_TEST,
    DIALERAPP_LAUNCH_WLAN_END,
}DialerApp_Wlan_Test_e;
#endif

#ifdef __APP_MMI_3D_DIALER__

typedef enum
{
	DIALERAPP_ANIM_NONE,
	DIALERAPP_ANIM_FLYIN,
	DIALERAPP_ANIM_PRESS,
	DIALERAPP_ANIM_RELEASE,
}DialerApp_Anim_Phase_e;

typedef struct {
    Vertex3D    tPos;
    Vertex3D    tSize;
	Vertex3D	aGridPos_End;
	Vertex3D	aGridPos_Mid;
	Vertex3D	aGridPos_Init;
    IBitmap     *pTextureBitmap;
} DialerAppButtonInfo_t;

#endif

enum
{
    DIALER_APP_FID_FIRST_KEY = 0
   ,DIALER_APP_FID_CALL_NUM = 1
};
typedef u32 MMI_DIALER_APP_FID_E;

typedef struct
{
	MMI_DIALER_APP_FID_E	u32DialerAppFid;
	MAE_WChar	CallNumber[CCSRV_MAX_CALL_NUMBER+1];
} DialerAppNumerInfo_t;

typedef struct
{
    IWidget *pMainContainer;
    IWidget *pInputWidget;
    IWidget *pShortcutWidget;
#ifdef __SMART_DIALER__
    IWidget *pContactImageWdg;
    IWidget *pContactInfoWdg;
    IWidget *pContactMenuWdg;
    IWidget *pContactNumberWdg;    
#endif
#ifdef __TOUCH_SCREEN_MMI__
    IWidget *pGridWdg1;
    IWidget *pButtonWdg1;
    IWidget *pGridWdg2;
    IWidget *pButtonWdg2;
#ifdef __DIALAPP_SMALLROM__
	IWidget *pDialButtonAbsContainer;
	IWidget *pDialButtonBgImageWdg;
#endif	// __DIALAPP_SMALLROM__
#ifndef __DIALAPP_SMALLROM__
	IWidget *pGridWdg3;
	IWidget *pButtonWdg3;
#endif
#endif
#ifdef __UI_STYLE_MMI_IFONE__
    IWidget *pTabWdg;
#endif
}DialerWndDialingWdgList_t;

typedef struct
{
    DialerWndDialingWdgList_t tWdgList;

} DialerWndDialingData_t;


typedef struct
{
    APPLET_BASE_ELEMENTS;
    DialerApp_AP_Type_e eIdleAPType;
    SetRingToneVolume_e eVolumeLevel;
    u32 nFirstKeyCode;
    u32 nCurrentTextLength;
    u32 nKeycode;
    boolean bShortcutDisplay;
    boolean bDialWithFirstKey;
    boolean bEnableOptionMenu;
    boolean bExit;
    boolean bLaunchEmbeddedAP;
    MAE_WChar *pEmergencyQueue;
    MAE_WChar *pstrCurrentInput;
#ifdef __TOUCH_SCREEN_MMI__
    DialerApp_TS_Grid_e eTouchGrid;
    boolean bLongPressed;
    u32 nLongpressKeyCode;
	boolean bDigitInput;
#endif
#ifdef __IP_CALL_MMI__
    boolean bShortPress;
#endif
#ifdef __SMART_DIALER__
    MenuWdgList_t tWdgList;
    WidgetHandler_t	tContactImageWidgetHandler;
    WidgetHandler_t	tContactInfoWidgetHandler;
    WidgetHandler_t	tContactNumberWidgetHandler;
    WidgetHandler_t	tInputWidgetHandler;
    WidgetHandler_t	tMenuWidgetHandler;
    MmiPhbBookType_e s32PhbBookType;
    u8 u8SimCondition;
    u16 u16FocusItem;
    u16 u16SearchedNum;
    boolean bIsSearchResult;
    boolean bIsNumberUpdated;
    MmiPhbSearchResult_t *patSearchResult;
    IImage *pContactImg;
    IImage *pContactMasterImg;
    IImage *pContactSlaveImg;
    SmartSearchType_t tSearchType;
    SmartSearchType_t tSearchTypeTemp;
#ifdef __APP_MMI_PRIVATEPROTECT__
	SecurityLockStatus_e ePHBLockStatus;
#endif	
#endif

#if defined(__SMART_DIALER__)
    /* PR0199310 */
	boolean bDialerUsePhbSortingTable;
    /* end of PR0199310 */
#endif

    boolean bDialWithCallNum;
    MAE_WChar *pstrCallNum;
#ifdef __APP_MMI_3D_DIALER__
	DialerApp_Anim_Phase_e eAnimatPhase;
	s32	AnimationCounter;
	bool bScrInvalide;

#ifdef __APP_MMI_DIALER_CUBE_TRANSITION__
	s32	AnimationCount[GROUP_NUMBER];
#else //APP_MMI_DIALER_BOX_TRANSITION
    IBitmap *pBoxTextureBitmap[DIALERAPP_BOX_DIALER_PLANE_NUM];
#endif

	u16	SceneHandleId;
	u32	Anim1NodeId;
	u32	Anim2NodeId;
	u32 DialerButtonId;
	DialerAppButtonInfo_t *pDialerButton;
    CubeSingleTexture *pCube;
    PlaneTexture *pPlaneTex;

    s32 nFlyinFrame;
#endif

#if defined (__DROPDOWN_STATUSPAGE__)
    IWidget *pStatusPageWidget;
    boolean bToShowStatusPageAfterResume;
	boolean bShowAirplanceModeWaitingDlg;
#endif // __DROPDOWN_STATUSPAGE__

//#if defined(__TOUCH_SCREEN_MMI__)
//	boolean bNotToSetTimer;
//#endif

#ifdef __PROGRAM_TEMP_IMEI_MMI__
	u8 szIMEICode[MMI_MM_IMEI_LENGTH+1];
	boolean bSetIMEIProcessing;
#endif
} DialerAppData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret DialerConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret DialerDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerKeyLongPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerKeyReleaseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#if defined(__TOUCH_SCREEN_MMI__)
boolean DialerTouchEventCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
MAE_Ret DialerWndDailingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndCreateDialing(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndSetDialing(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndShowDialing(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndDestroyDialing(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndSendHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndCreateSend(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndDestroySend(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndSetSend(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndCreateOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret DialerWndSetOption(void *pCusHandle, void *pWndData);
MAE_Ret DialerWndDestroyOption(void *pCusHandle, void *pWndData);
void DialerProfileChangeCb(void *pUserData, ProfileID_e eProfileID);
#ifdef __MMS_MMI_CDMMS__
void DialerSendViaMenuHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
void DialerOptionMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void DialerSilentModeDialogTimerCb(void* pUserData);
#ifdef __TOUCH_SCREEN_MMI__
void DialerTSLongPressCb(void* pUserData);
void DialerTSLongPressCb2(void* pUserData);
//void DialerGrid1FocusChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
//void DialerGrid2FocusChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void DialerButtonWdg1ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void DialerButtonWdg2ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void DialerGrid1FocusSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
void DialerGrid2FocusSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
void DialerButtonWdgInvalidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
#endif
void DialerInputTextChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
#if defined(__TOUCH_SCREEN_MMI__) && defined(__SMART_DIALER__)
void DialerInputTextFocusChangeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);
#endif
#ifndef __DIALAPP_SMALLROM__
void DialerButtonWdg3ValidCb(void *pApplet,void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid,IWidget *pWidget);
void DialerGrid3FocusSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
#endif

#ifdef __SMART_DIALER__
void DialerWndCreateSettingOptionLev2Cb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void DialerSearchSettingMenuHandleCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void DialerSearchMenuSoftkeyActCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void DialerSearchMenuOnFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
#endif //__SMART_DIALER__

#ifdef __APP_MMI_3D_DIALER__
boolean DialerHookDrawCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean DialerGetInvalidateRect(IApplet *pApplet, u32 u32DisplayInfo, u32 param1, u32 param2);
void Dialer3DAnimateTimer(void * pUser);
#endif

#endif /* __MMI_DIALERAPP_PRIV_H__ */
