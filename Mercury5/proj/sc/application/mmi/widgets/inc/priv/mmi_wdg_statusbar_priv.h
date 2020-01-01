/**
 * @file    mmi_wdg_statusbar_priv.h
 * @brief   The document describes internal declartion of StatusBar Widget
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mmi_wdg_statusbar_priv.h 34408 2009-06-25 09:59:29Z otto.wu $
 */

#ifndef __MMI_WDG_STATUSBAR_PRIV_H__
#define __MMI_WDG_STATUSBAR_PRIV_H__

#include "mmi_wdg_statusbar.h"
#include "mae_abscontainerbase.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_statusbarsrv.h"
#include "mmi_mae_imagemodel.h"

enum
{
	eIBitmapType = 0,
	eIImageType
};
typedef u8 u8StatBar_ImgType;

#define MAKE_IMGID(_a,_b) _a
enum StatbarImgResId_tag
{
#include "mmi_wdg_statusbar_imgid.h"
	SB_IMG_ID_SUM,
	SB_IMG_ID_END = SB_IMG_ID_SUM - 1,
};

#ifdef __DUAL_LCD__
enum SubStatbarImgResId_tag
{
#include "mmi_wdg_substatusbar_imgid.h"
	SUB_SB_IMG_ID_SUM,
	SUB_SB_IMG_ID_END = SUB_SB_IMG_ID_SUM - 1,
};
#endif
#undef MAKE_IMGID

#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__NCCQQ_MMI__))
enum
{
    SB_ALARMGROUP_NONE = 0,
    SB_ALARMGROUP_ALARM,
    SB_ALARMGROUP_BLOCKCALL,
    SB_ALARMGROUP_MISSEDCALL,
    SB_ALARMGROUP_QQ,
};
typedef u8 eAlarmGroup;

#define STATUSBAR_ALARM_ICON_ENABLE         (1 << SB_ALARMGROUP_ALARM)
#if (!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__))
#define STATUSBAR_BLOCKCALL_ICON_ENABLE     (1 << SB_ALARMGROUP_BLOCKCALL) // __MMI_CALLLOG_SUPPORT_BKLOG__
#endif // End of __MMI_CALLLOG_SUPPORT_BKLOG__
#ifdef __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
#define STATUSBAR_MISSCALL_ICON_ENABLE      (1 << SB_ALARMGROUP_MISSEDCALL) // __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
#endif // End of __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
#ifdef __NCCQQ_MMI__
#define STATUSBAR_QQ_ICON_ENABLE            (1 << SB_ALARMGROUP_QQ) // __NCCQQ_MMI__
#endif // End of __NCCQQ_MMI__

#define STATUSBARWDG_SETBIT(queue,mask){\
                                          queue |= mask; \
                                      }

#define STATUSBARWDG_REMOVEBIT(queue, mask) {\
                                             if(queue & mask) \
                                             { \
                                                 queue ^= mask; \
                                             } \
                                         }
#endif // End of __MMI_CALLLOG_SUPPORT_BKLOG__ || __MMI_STATUSBAR_SUPPORT_MISSED_CALL__ || __NCCQQ_MMI__

#ifdef __WLAN_MMI__
enum
{
	SB_NTYPE_ICON_FLAG_GPRS_SIM1 = 0,
    SB_NTYPE_ICON_FLAG_GPRS_SIM1_TRAFFIC,
	SB_NTYPE_ICON_FLAG_EGPRS_SIM1,
    SB_NTYPE_ICON_FLAG_EGPRS_SIM1_TRAFFIC,
	SB_NTYPE_ICON_FLAG_UMTS_SIM1,
    SB_NTYPE_ICON_FLAG_UMTS_SIM1_TRAFFIC,
	SB_NTYPE_ICON_FLAG_HSDPA_SIM1,
    SB_NTYPE_ICON_FLAG_HSDPA_SIM1_TRAFFIC,
	SB_NTYPE_ICON_FLAG_GPRS_SIM2,
    SB_NTYPE_ICON_FLAG_GPRS_SIM2_TRAFFIC,
	SB_NTYPE_ICON_FLAG_EGPRS_SIM2,
    SB_NTYPE_ICON_FLAG_EGPRS_SIM2_TRAFFIC,
	SB_NTYPE_ICON_FLAG_UMTS_SIM2,
    SB_NTYPE_ICON_FLAG_UMTS_SIM2_TRAFFIC,
	SB_NTYPE_ICON_FLAG_HSDPA_SIM2,
    SB_NTYPE_ICON_FLAG_HSDPA_SIM2_TRAFFIC,
	SB_NTYPE_ICON_FLAG_WIFI_ON,
	SB_NTYPE_ICON_FLAG_WIFI_CONNECTED,
	SB_NTYPE_ICON_FLAG_WIFI_TRAFFIC,
	SB_NTYPE_ICON_FLAG_CONNECT_LIMITED,
};

enum
{
	SB_NTYPE_ICON_GPRS_SIM1 = (1<<SB_NTYPE_ICON_FLAG_GPRS_SIM1),
    SB_NTYPE_ICON_GPRS_SIM1_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_GPRS_SIM1_TRAFFIC),
	SB_NTYPE_ICON_EGPRS_SIM1 = (1<<SB_NTYPE_ICON_FLAG_EGPRS_SIM1),
    SB_NTYPE_ICON_EGPRS_SIM1_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_EGPRS_SIM1_TRAFFIC),
	SB_NTYPE_ICON_UMTS_SIM1 = (1<<SB_NTYPE_ICON_FLAG_UMTS_SIM1),
    SB_NTYPE_ICON_UMTS_SIM1_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_UMTS_SIM1_TRAFFIC),
	SB_NTYPE_ICON_HSDPA_SIM1 = (1<<SB_NTYPE_ICON_FLAG_HSDPA_SIM1),
    SB_NTYPE_ICON_HSDPA_SIM1_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_HSDPA_SIM1_TRAFFIC),
	SB_NTYPE_ICON_GPRS_SIM2 = (1<<SB_NTYPE_ICON_FLAG_GPRS_SIM2),
    SB_NTYPE_ICON_GPRS_SIM2_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_GPRS_SIM2_TRAFFIC),
	SB_NTYPE_ICON_EGPRS_SIM2 = (1<<SB_NTYPE_ICON_FLAG_EGPRS_SIM2),
    SB_NTYPE_ICON_EGPRS_SIM2_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_EGPRS_SIM2_TRAFFIC),
	SB_NTYPE_ICON_UMTS_SIM2 = (1<<SB_NTYPE_ICON_FLAG_UMTS_SIM2),
    SB_NTYPE_ICON_UMTS_SIM2_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_UMTS_SIM2_TRAFFIC),
	SB_NTYPE_ICON_HSDPA_SIM2 = (1<<SB_NTYPE_ICON_FLAG_HSDPA_SIM2),
    SB_NTYPE_ICON_HSDPA_SIM2_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_HSDPA_SIM2_TRAFFIC),
	SB_NTYPE_ICON_WIFI_ON = (1<<SB_NTYPE_ICON_FLAG_WIFI_ON),
	SB_NTYPE_ICON_WIFI_CONNECTED = (1<<SB_NTYPE_ICON_FLAG_WIFI_CONNECTED),
	SB_NTYPE_ICON_WIFI_TRAFFIC = (1<<SB_NTYPE_ICON_FLAG_WIFI_TRAFFIC),
	SB_NTYPE_ICON_WIFI_CONNECT_LIMITED = (1<<SB_NTYPE_ICON_FLAG_CONNECT_LIMITED),
	SB_NTYPE_ICON_WIFI_MASK = (SB_NTYPE_ICON_WIFI_CONNECTED | SB_NTYPE_ICON_WIFI_CONNECT_LIMITED | SB_NTYPE_ICON_WIFI_ON),
};
#endif

#ifdef __MMI_STATUSBAR_AUTO_ARRANGE__
enum
{
	eLeftSegment = 0,
	eRightSegment,
	eTotalSegment
};
typedef u8 eIconPosSide;
#endif  //__MMI_STATUSBAR_AUTO_ARRANGE__

//Charging Animation Timer
#define STATUSBAR_CHARGING_TIMER 250
#define STATUSBAR_WAP_TRANS_TIMER 250

#define INHERIT_StatusImgData(IName) \
    INHERIT_IBase(IName)

DEFINE_INTERFACE(StatusImgData);

typedef struct
{
    DECLARE_FUNCTBL(StatusImgData);	// function table pointer
    u32		RefCnt; //Reference count

#if ! (defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__))
    //Image Models for Widgets
    IImageModel    *pCompItfMdl[STATUSBAR_COMP_BMPWDG_SUM];
#endif
    u32                aCurImgId[STATUSBAR_COMP_BMPWDG_SUM];
    IImage             *pCustomImg[STATUSBAR_CUSTOM_ICON_NUM];
}_MAE_StatusImgData;

typedef struct
{
    AbsContainerBase_t ACntrBase;
    IVectorModel* pIStatusModel;
    IWidget *pCompWdg[STATUSBAR_COMP_WDG_SUM];

    boolean bWAPTrans;
    boolean bCharging;
    boolean bInitState;     //Workaround solution fore reference count
    _MAE_StatusImgData *pImgData;
    ModelListener_t StatusModelListener;
    u16 nWAPTransCounter;   //StatusBar_Batt_e
    u16 nChargingCounter;   //StatusBar_Batt_e
#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__NCCQQ_MMI__))
    u16	nAlarmGroupStatus;  // For alarm group icon status
    u16	nAlign;	            // just for alignment.
#endif
	boolean bforceReloadImg;    //while _StatusbarWidget_ReloadRC, force StatusBarWidget_ChangeImage do reload the image.
	boolean bBGEnable;			//Record the flag and using it while _StatusbarWidget_ReloadR
#ifdef __NCCQQ_MMI__
    StatusBar_QQSrvStatus_e eQQSrvStatus;
#endif // End of __NCCQQ_MMI__
#ifdef __WLAN_MMI__
 	u16 nNTypeIconStatus;
#endif

#ifdef __MMI_STATUSBAR_AUTO_ARRANGE__
    u32  aWidthProportion[eTotalSegment];
    u8   aIconPriority[STATUSBAR_COMP_WDG_SUM];
    u8   nIconCountLeft, nIconCountRight;
#endif  //__MMI_STATUSBAR_AUTO_ARRANGE__

}_MAE_StatusBarWidget;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret StatusBarWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ static boolean StatusBarWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret _WdgStatusBarConstructor(_MAE_StatusBarWidget *pThis);
void _WdgStatusBarDestructor(_MAE_StatusBarWidget *pThis);
static MAE_Ret StatusBarWidget_QueryInterface(IWidget *pSt, MAE_IId iId, void **ppObj, IBase *pOwner);
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_Init(IAbsContainer * pIAbsContainer);
__SLDPM_FREE__ static void StatusBarWidget_StatusModelListener(void *pUsrData, ListModelEvent_t *pVectorMdlEvent);
#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__MMI_STATUSBAR_SUPPORT_UNREAD_MESSAGE__) || defined(__MMI_STATUSBAR_SUPPORT_UNREAD_MESSAGE_BY_IMSI__) || defined(__NCCQQ_MMI__))
__SLDPM_FREE__ static void StatusBarWidget_SetCompWdgVisibility(_MAE_StatusBarWidget *pThis, u32 WdgID, boolean bVisible);
#endif
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_ChangeImage(_MAE_StatusBarWidget *pThis, u32 ImgID, u32 WdgID, u8StatBar_ImgType u8ImgType);
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleBattStatus(_MAE_StatusBarWidget *pThis, u16* pData, u16 nIndex);
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleRSSIStatus(_MAE_StatusBarWidget *pThis, u16* pData );
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleNTypeStatus(_MAE_StatusBarWidget *pThis, u16* pData );
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleCCSSStatus(_MAE_StatusBarWidget *pThis, u16* pData );
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleWAPMsgStatus(_MAE_StatusBarWidget *pThis, u16* pData, u32 WdgID);
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleBackgroundStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#ifdef __NCCQQ_MMI__
static MAE_Ret StatusBarWidget_HandleQQStatus(_MAE_StatusBarWidget *pThis, u16* pData, u32 WdgID );
#endif
#ifdef __DUAL_SIM_MMI__
static MAE_Ret StatusBarWidget_HandleSIMStatus(_MAE_StatusBarWidget *pThis, u16* pData );
#endif
//#ifdef __UI_STYLE_MMI_IFONE__
#ifndef  __LCM_QQVGA_MMI__
static MAE_Ret StatusBarWidget_HandleVibrateStatus(_MAE_StatusBarWidget *pThis, u16* pData);
static MAE_Ret StatusBarWidget_HandleMediaStatus(_MAE_StatusBarWidget *pThis, u16* pData);
static MAE_Ret StatusBarWidget_HandleTimeInfo(_MAE_StatusBarWidget *pThis, StatusBar_Time_t* pData);
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleOtherStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#endif
#ifdef __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleProfileModeStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#else
__SLDPM_FREE__ static MAE_Ret StatusBarWidget_HandleSoundModeStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#endif // __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
static MAE_Ret StatusBarWidget_HandleBTStatus(_MAE_StatusBarWidget *pThis, u16* pData);
static MAE_Ret StatusBarWidget_HandleAlarmStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#ifdef __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
static MAE_Ret StatusBarWidget_HandleMissCallStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#endif
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)
static MAE_Ret StatusBarWidget_HandleBlockCallStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#endif
#ifdef __WLAN_MMI__
static MAE_Ret StatusBarWidget_HandleWiFiStatus(_MAE_StatusBarWidget *pThis, u16* pData);
#endif
//#endif
static MAE_Ret StatusBarWidget_HandleCustomIcon(_MAE_StatusBarWidget *pThis, StatusBar_Custom_Icon_t* pData);
static MAE_Ret StatusBarWidget_SetWAPAnimationFrame(_MAE_StatusBarWidget *pThis);
static MAE_Ret StatusBarWidget_LoadImgData(_MAE_StatusImgData *pThis);
#if ! (defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__))
static MAE_Ret StatusBarWidget_CreateModels(_MAE_StatusImgData *pThis);
static MAE_Ret StatusBarWidget_ReplaceInterfaceModels(_MAE_StatusBarWidget *pThis);
#endif
__SLDPM_FREE__ static u32 StatusImgData_AddRef(StatusImgData *pStatusImgData);
static u32 StatusImgData_Release(StatusImgData *pStatusImgData);
static u32 StatusImgData_QueryInterface(StatusImgData *pStatusImgData, MAE_IId iId, void **ppObj, IBase* pOwner);
#if ((!defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_CALLLOG_SUPPORT_BKLOG__)) || defined(__MMI_STATUSBAR_SUPPORT_MISSED_CALL__) || defined(__NCCQQ_MMI__))
static void StatusBarWidget_SetAlarmGroupWdgVisible(_MAE_StatusBarWidget *pThis, u32 u32WdgID, u32 ImgID);
#endif
static void _StatusbarWidget_ReloadRC(_MAE_StatusBarWidget *pThis, DisplayMode_e nDispMode);
#ifdef __MMI_STATUSBAR_AUTO_ARRANGE__
static void _StatusBarWidget_InitIconPriority(_MAE_StatusBarWidget *pThis);
static MAE_Ret _StatusBarWidget_SetDefaultIconPriority(_MAE_StatusBarWidget *pThis, u32 nWdgId, u8 nPriority, eIconPosSide nSide);
static void _StatusBarWidget_SortIconPos(_MAE_StatusBarWidget *pThis);
#endif  //__MMI_STATUSBAR_AUTO_ARRANGE__

#endif /* __MMI_WDG_STATUSBAR_PRIV_H__ */
