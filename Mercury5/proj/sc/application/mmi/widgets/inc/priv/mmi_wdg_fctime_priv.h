/**
* @file mmi_wdg_fctime_priv.h
* @brief This file defines the data structure of FCTimeWidget
*
* @version $Id: mmi_wdg_fctime_priv.h 30795 2009-05-14 03:06:34Z eric.chen $
*/

#ifndef __MMI_WDG_FCTIME_PRIV_H__
#define __MMI_WDG_FCTIME_PRIV_H__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_fctime.h"
#include "mae_abscontainerbase.h"
#include "mmi_mae_vectormodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum {
	FCT_TIME_FORMAT_12,
	FCT_TIME_FORMAT_24,
} _FCTTimeFormat_e;

typedef enum {
	FCT_MOVE_IND_LEFT,
	FCT_MOVE_IND_RIGHT,
} _FCTMoveInd_e;

//typedef enum {
//	FCT_RING_LIST_HOUR,
//	FCT_RING_LIST_MINUTE2,
//	FCT_RING_LIST_MINUTE1,
//	FCT_RING_LIST_AMPM,
//} _FCTRingListType_e;



typedef enum {
	FCT_TIME_FORMAT_24HOUR_MIN
	,FCT_TIME_FORMAT_24HOUR_00 = FCT_TIME_FORMAT_24HOUR_MIN
	,FCT_TIME_FORMAT_24HOUR_01
	,FCT_TIME_FORMAT_24HOUR_02
	,FCT_TIME_FORMAT_24HOUR_03
	,FCT_TIME_FORMAT_24HOUR_04
	,FCT_TIME_FORMAT_24HOUR_05
	,FCT_TIME_FORMAT_24HOUR_06
	,FCT_TIME_FORMAT_24HOUR_07
	,FCT_TIME_FORMAT_24HOUR_08
	,FCT_TIME_FORMAT_24HOUR_09
	,FCT_TIME_FORMAT_24HOUR_10
	,FCT_TIME_FORMAT_24HOUR_11
	,FCT_TIME_FORMAT_24HOUR_12
	,FCT_TIME_FORMAT_24HOUR_13
	,FCT_TIME_FORMAT_24HOUR_14
    ,FCT_TIME_FORMAT_24HOUR_15
    ,FCT_TIME_FORMAT_24HOUR_16
    ,FCT_TIME_FORMAT_24HOUR_17
    ,FCT_TIME_FORMAT_24HOUR_18
    ,FCT_TIME_FORMAT_24HOUR_19
	,FCT_TIME_FORMAT_24HOUR_20
	,FCT_TIME_FORMAT_24HOUR_21
	,FCT_TIME_FORMAT_24HOUR_22
	,FCT_TIME_FORMAT_24HOUR_23
	,FCT_TIME_FORMAT_24HOUR_MAX = FCT_TIME_FORMAT_24HOUR_23,
} _FCTTimeFormat24Hour_e;

typedef enum {
	FCT_TIME_FORMAT_12HOUR_MIN
	,FCT_TIME_FORMAT_12HOUR_01 = FCT_TIME_FORMAT_12HOUR_MIN
	,FCT_TIME_FORMAT_12HOUR_02
	,FCT_TIME_FORMAT_12HOUR_03
	,FCT_TIME_FORMAT_12HOUR_04
	,FCT_TIME_FORMAT_12HOUR_05
	,FCT_TIME_FORMAT_12HOUR_06
	,FCT_TIME_FORMAT_12HOUR_07
	,FCT_TIME_FORMAT_12HOUR_08
	,FCT_TIME_FORMAT_12HOUR_09
	,FCT_TIME_FORMAT_12HOUR_10
	,FCT_TIME_FORMAT_12HOUR_11
	,FCT_TIME_FORMAT_12HOUR_12
	,FCT_TIME_FORMAT_12HOUR_MAX = FCT_TIME_FORMAT_12HOUR_12,
} _FCTTimeFormat12Hour_e;

typedef enum {
	FCT_TIME_FORMAT_NUMBER_MIN
	,FCT_TIME_FORMAT_NUMBER_0 = FCT_TIME_FORMAT_NUMBER_MIN
	,FCT_TIME_FORMAT_NUMBER_1
	,FCT_TIME_FORMAT_NUMBER_2
	,FCT_TIME_FORMAT_NUMBER_3
	,FCT_TIME_FORMAT_NUMBER_4
	,FCT_TIME_FORMAT_NUMBER_5
	,FCT_TIME_FORMAT_NUMBER_6
	,FCT_TIME_FORMAT_NUMBER_7
	,FCT_TIME_FORMAT_NUMBER_8
	,FCT_TIME_FORMAT_NUMBER_9
	,FCT_TIME_FORMAT_NUMBER_MAX = FCT_TIME_FORMAT_NUMBER_9,
} _FCTTimeFormatNumber_e;


/*
enum TimeFields_e
{
	HOUR = 0,
	MINUTE
	//SECOND
};
*/

enum
{
	FCT_TIME_FORMAT_AM = 0,
	FCT_TIME_FORMAT_PM,
};


#define FCTWDG_RESET_INPUT_KEY_COUNTER(_pFCTWdg) \
	 ((_pFCTWdg)->InputKeyCnt=0)

#define FCTWDG_SET_INPUT_KEY_COUNTER(_pFCTWdg,_n) \
	((_pFCTWdg)->InputKeyCnt=_n)
#define FCTWDG_GET_INPUT_KEY_COUNTER(_pFCTWdg) \
	((_pFCTWdg)->InputKeyCnt)


//#define DEFAULT_FONT_TYPE FONT_TYPE_NORMAL      ///<  FONT_TYPE 0 ==> Normal type
//#define DEFAULT_FONT_CATE FONT_CAT_NORMAL      ///<  default font size

#define FCT_12HR_MAX_HOUR    12 ///< the max value of HOUR field of 12 Hour time format
#define FCT_12HR_MIN_HOUR    1   ///< the min value of HOUR field of 12 Hour time format

#define FCT_24HR_MAX_HOUR    23  ///< the max value of HOUR field of 24 Hour time format
#define FCT_24HR_MIN_HOUR    0   ///< the min value of HOUR field of 24 Hour time format



typedef struct{
	s8 *pStrAMPM;
	boolean bAM;
	u8 Hour;
	u8 Minute;
}FCT_TimeFormat_t;


typedef u8 FCTTimeWdgId_e;
//-----------------------------------


typedef struct{
	ModelListener_t RingListMdlLsn;
	WidgetHandler_t RingListWdgHdlData;
	IWidget *pIRingListWdg;
	IBase *pOwner;
	u8 nFCDisplayNum;
}FCT_TimeWdgInfo_t;







typedef struct
{
    AbsContainerBase_t ACntrBase;


	FCT_TimeWdgInfo_t *pTimeWdgsInfo;
	const FCT_TimeDispInfo_t *pTimeDispInfo;

	IWidget *pIMageWdg_Ind;

	boolean bShowAMPM;				 ///< should the widget show AM/PM
	boolean bAM;					 ///< current time period

	u8 u8WdgNum;
	u8 InputKeyCnt;

	u8 nMaxHour;            ///< max hour value for current time format
	u8 nMinHour;	        ///< min hour value for current time format
    _FCTIndType_e FCTInd;

}_FCTimeWidget_t;
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret FCTimeWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean FCTimeWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
void _WdgFCTimeDestructor(_FCTimeWidget_t *pThis);
MAE_Ret _WdgFCTimeConstructor(_FCTimeWidget_t *pThis);

static MAE_Ret _FCTimeWidget_Create_ChildObjects(_FCTimeWidget_t *pThis);
static void _FCTimeWidget_ShowIndicator(_FCTimeWidget_t *pThis, IWidget *pIndImgWdg ,_FCTIndType_e FCTIndType);
static void _FCTimeWidget_SwitchIndicator(_FCTimeWidget_t *pThis, IWidget *pIndImgWdg ,_FCTMoveInd_e FCTMoveInd);
static void _FCTimeWidget_Get12FormatTimeInfo(_FCTimeWidget_t *pThis, MAE_DateTime_t *pDateTime ,FCT_TimeFormat_t *pTimeFormat);
static void _FCTimeWidget_AddMinuteDatetoVctmodel(_FCTimeWidget_t *pThis, IVectorModel *pRingListVctMdl);
void _FCTimeRingListWidget_FreeVcrMdl(void *pData, IBase *pOwner);
void _FCTimeWidget_FreeModel(void *pData, IBase *pOwner);
void _FCTimeRingListWidget_ViewModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
static boolean _FCTimeWidget_RingListWdgHandleEvent(void *pUsr, MAE_EventId evt, u32 P1, u32 P2);
static void _FCTimeWidget_RingListWdgHdlFree(void *pData);
MAE_Ret _FCTimeWidget_FindWdgIdxbyWdgInstance(_FCTimeWidget_t *pThis, IWidget *pIRingListWidget, s32 *pWdgIdx);
MAE_Ret _FCTimeWidget_FindWdgIdxbyIndType(_FCTimeWidget_t *pThis, _FCTIndType_e eFCTIndType, s32 *pWdgIdx);
static void _FCTimeWidget_SetTimeToFCTWdg(_FCTimeWidget_t *pThis, MAE_DateTime_t *pDateTime);
static void _FCTimeWidget_UpdateFCDisplayTimetoModel(_FCTimeWidget_t *pThis);
static void _FCTimeWidget_SyncFCTDisplayTimetoRingList(_FCTimeWidget_t *pThis);

static boolean _FCTimeWidget_SetProperty(_FCTimeWidget_t *pThis, u32 P1, u32 P2);
static boolean _FCTimeWidget_GetProperty(_FCTimeWidget_t *pThis, u32 P1, u32 P2);
static boolean _FCTimeWidget_HandleKey(_FCTimeWidget_t *pThis, u32 P1, u32 P2);
static void _FCTimeWidget_ReloadRC(_FCTimeWidget_t *pThis, DisplayMode_e nDispMode);

#endif /* __MMI_WDG_FCTIME_PRIV_H__ */
