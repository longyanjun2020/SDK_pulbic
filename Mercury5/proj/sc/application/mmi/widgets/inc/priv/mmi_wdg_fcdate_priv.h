/**
* @file mmi_wdg_fcdate_priv.h
* @brief This file defines the data structure of FCDateWidget
*
* @version $Id: mmi_wdg_fcdate_priv.h 36107 2009-07-20 13:05:10Z collin.chiang $
*/
 
#ifndef __MMI_WDG_FC_DATE_PRIV_H__
#define __MMI_WDG_FC_DATE_PRIV_H__ 
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_abscontainerbase.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_wdg_fcdate.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum {
	FCD_MOVE_IND_LEFT,
	FCD_MOVE_IND_RIGHT,	
} _FCDMoveInd_e;



typedef enum {
	 FCD_DATE_FORMAT_NUMBER_MIN 
	,FCD_DATE_FORMAT_NUMBER_0 = FCD_DATE_FORMAT_NUMBER_MIN 
	,FCD_DATE_FORMAT_NUMBER_1
	,FCD_DATE_FORMAT_NUMBER_2
	,FCD_DATE_FORMAT_NUMBER_3
	,FCD_DATE_FORMAT_NUMBER_4
	,FCD_DATE_FORMAT_NUMBER_5
	,FCD_DATE_FORMAT_NUMBER_6
	,FCD_DATE_FORMAT_NUMBER_7
	,FCD_DATE_FORMAT_NUMBER_8
	,FCD_DATE_FORMAT_NUMBER_9
	,FCD_DATE_FORMAT_NUMBER_MAX = FCD_DATE_FORMAT_NUMBER_9,
} _FCDateFormatNumber_e;


typedef enum {
	 FCD_DATE_FORMAT_MONTH_MIN = 1
	,FCD_DATE_FORMAT_MONTH_1 = FCD_DATE_FORMAT_MONTH_MIN 
	,FCD_DATE_FORMAT_MONTH_2
	,FCD_DATE_FORMAT_MONTH_3
	,FCD_DATE_FORMAT_MONTH_4
	,FCD_DATE_FORMAT_MONTH_5
	,FCD_DATE_FORMAT_MONTH_6
	,FCD_DATE_FORMAT_MONTH_7
	,FCD_DATE_FORMAT_MONTH_8
	,FCD_DATE_FORMAT_MONTH_9
	,FCD_DATE_FORMAT_MONTH_10
	,FCD_DATE_FORMAT_MONTH_11
	,FCD_DATE_FORMAT_MONTH_12
	,FCD_DATE_FORMAT_MONTH_MAX = FCD_DATE_FORMAT_MONTH_12,
} _FCDateFormatMonth_e;

enum
{
	FCT_TIME_FORMAT_AM = 0,
	FCT_TIME_FORMAT_PM,
};

/**
* Flag 
*/
#define INPUT_KEY_INFO_NON_INPUT								(0)
#define INPUT_KEY_INFO_NON_ZERO_NUMBER_INPUT					(1<<1)
#define INPUT_KEY_INFO_ZERO_NUMBER_INPUT						(1<<2)

#define FCDWDG_RESET_INPUT_KEY_INFO(_pFCDWDG) \
	 ((_pFCDWDG)->InputKeyCnt=0)
#define FCDWDG_SET_INPUT_KEY_INFO(_pFCDWDG,_n) \
	((_pFCDWDG)->InputKeyCnt=_n)
#define FCDWDG_GET_INPUT_KEY_INFO(_pFCDWDG) \
	((_pFCDWDG)->InputKeyCnt)



/**
* Flags in Config
*/
typedef enum
{
	FCDWDG_FLAG_YEAR4_SCROLLING = 0 ,
	FCDWDG_FLAG_YEAR3_SCROLLING		,
	FCDWDG_FLAG_YEAR2_SCROLLING		,
	FCDWDG_FLAG_YEAR1_SCROLLING		,
	FCDWDG_FLAG_MONTH_SCROLLING		,
	FCDWDG_FLAG_DAY2_SCROLLING		,
	FCDWDG_FLAG_DAY1_SCROLLING
}FCDWDG_FLAG;
enum
{
	FCDWDG_WDG_RELOAD_FLAG_START = 0,
	FCDWDG_WDG_RELOAD_FLAG_MINYEAR = FCDWDG_WDG_RELOAD_FLAG_START,   ///< textAlign
	FCDWDG_WDG_RELOAD_FLAG_MAXYEAR,	///< textLayout
	FCDWDG_WDG_RELOAD_FLAG_END
};
/**
* Flag Mask
*/
#define FCDWDG_MASK_YEAR4_SCROLLING			(1<<FCDWDG_FLAG_YEAR4_SCROLLING)
#define FCDWDG_MASK_YEAR3_SCROLLING			(1<<FCDWDG_FLAG_YEAR3_SCROLLING)
#define FCDWDG_MASK_YEAR2_SCROLLING			(1<<FCDWDG_FLAG_YEAR2_SCROLLING)
#define FCDWDG_MASK_YEAR1_SCROLLING			(1<<FCDWDG_FLAG_YEAR1_SCROLLING)
#define FCDWDG_MASK_MONTH_SCROLLING			(1<<FCDWDG_FLAG_MONTH_SCROLLING)
#define FCDWDG_MASK_DAY2_SCROLLING			(1<<FCDWDG_FLAG_DAY2_SCROLLING)
#define FCDWDG_MASK_DAY1_SCROLLING			(1<<FCDWDG_FLAG_DAY1_SCROLLING)

#define FCDWDG_WDG_RELOAD_MASK_MINYEAR      (1<<FCDWDG_WDG_RELOAD_FLAG_MINYEAR)
#define FCDWDG_WDG_RELOAD_MASK_MAXYEAR      (1<<FCDWDG_WDG_RELOAD_FLAG_MAXYEAR)
/**
* Macro to get flag value
*/
#define FCDWDG_IS_YEAR4_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_YEAR4_SCROLLING)>>FCDWDG_FLAG_YEAR4_SCROLLING)
	
#define FCDWDG_IS_YEAR3_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_YEAR3_SCROLLING)>>FCDWDG_FLAG_YEAR3_SCROLLING)

#define FCDWDG_IS_YEAR2_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_YEAR2_SCROLLING)>>FCDWDG_FLAG_YEAR2_SCROLLING)
	
#define FCDWDG_IS_YEAR1_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_YEAR1_SCROLLING)>>FCDWDG_FLAG_YEAR1_SCROLLING)

#define FCDWDG_IS_MONTH_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_MONTH_SCROLLING)>>FCDWDG_FLAG_MONTH_SCROLLING)

#define FCDWDG_IS_DAY2_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_DAY2_SCROLLING)>>FCDWDG_FLAG_DAY2_SCROLLING)
	
#define FCDWDG_IS_DAY1_SCROLLING(_pThis) \
	(boolean)(((_pThis)->nScrollingFlag&FCDWDG_MASK_DAY1_SCROLLING)>>FCDWDG_FLAG_DAY1_SCROLLING)

#define FCDWDG_WDG_MINYEAR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FCDWDG_WDG_RELOAD_MASK_MINYEAR)>>FCDWDG_WDG_RELOAD_FLAG_MINYEAR)
#define FCDWDG_WDG_MAXYEAR_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&FCDWDG_WDG_RELOAD_MASK_MAXYEAR)>>FCDWDG_WDG_RELOAD_FLAG_MAXYEAR)
/**
* Macro to Set flag value
*/
#define FCDWDG_SET_SCROLLING(_pThis, _idx, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~(u32)(1<<_idx)))|(((u8)_b)<<(_idx))	
#define FCDWDG_SET_YEAR4_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_YEAR4_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_YEAR4_SCROLLING)	
#define FCDWDG_SET_YEAR3_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_YEAR3_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_YEAR3_SCROLLING)
#define FCDWDG_SET_YEAR2_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_YEAR2_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_YEAR2_SCROLLING)
#define FCDWDG_SET_YEAR1_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_YEAR1_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_YEAR1_SCROLLING)
#define FCDWDG_SET_MONTH_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_MONTH_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_MONTH_SCROLLING)
#define FCDWDG_SET_DAY2_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_DAY2_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_DAY2_SCROLLING)
#define FCDWDG_SET_DAY1_SCROLLING(_pThis, _b) \
	(_pThis)->nScrollingFlag = ((_pThis)->nScrollingFlag&(~FCDWDG_MASK_DAY1_SCROLLING))|(((u8)_b)<<FCDWDG_FLAG_DAY1_SCROLLING)

#define FCDWDG_WDG_MINYEAR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FCDWDG_WDG_RELOAD_MASK_MINYEAR))|(((u32)_b)<<FCDWDG_WDG_RELOAD_FLAG_MINYEAR)
#define FCDWDG_WDG_MAXYEAR_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~FCDWDG_WDG_RELOAD_MASK_MAXYEAR))|(((u32)_b)<<FCDWDG_WDG_RELOAD_FLAG_MAXYEAR)

//#define DEFAULT_FONT_TYPE FONT_TYPE_NORMAL      ///<  FONT_TYPE 0 ==> Normal type
//#define DEFAULT_FONT_CATE FONT_CAT_NORMAL      ///<  default font size

#define FCDWDG_KEY_IN_MONTH_TIMER 1500
#define FCDWDG_VALID_DISPLAY_DATE_TIMER 1000


typedef struct{
	s8 *pStrAMPM;
	boolean bAM;
	u8 Hour;
	u8 Minute;
}FCT_TimeFormat_t;


typedef struct{	
	ModelListener_t RingListMdlLsn;
	WidgetHandler_t RingListWdgHdlData;
	IWidget *pIRingListWdg;
	IBase *pOwner;
}FCT_DateWdgInfo_t;


typedef struct
{
    AbsContainerBase_t ACntrBase;
	IWidget *pIMageWdg_Ind;

	FCT_DateWdgInfo_t stTimeWdgInfo[FCD_IND_SUM];
	u16 nMaxYear;            ///< max year value for current date format
	u16 nMinYear;	        ///< min year value for current date format	

	u8 nFCDisplay[FCD_IND_SUM];
	u8 InputKeyCnt;
	u8 nScrollingFlag;
	u8 bEnableValidTimer;
	u8 bSyncDisplayTimetoRingList;//When function validate display time, and display time is not valid.
								  //This flag will set to 1, and we start to sync valid display time to ring list.
	_FCDIndType_e FCDInd;
	u32 nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
}_FCDateWidget_t;

/*------------------------------------------------------------------------------------------
* New function and Event handler
------------------------------------------------------------------------------------------*/
MAE_Ret FCDateWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean FCDateWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* Non-interface functions
------------------------------------------------------------------------------------------*/
MAE_Ret _WdgFCDateConstructor(_FCDateWidget_t *pThis);
void _WdgFCDateDestructor(_FCDateWidget_t *pThis);

static MAE_Ret _FCDateWidget_Create_ChildObjects(_FCDateWidget_t *pThis);
static void _FCDateWidget_ChecktoResetMonthData(_FCDateWidget_t *pThis);
static void _FCDateWidget_ShowIndicator(_FCDateWidget_t *pThis, IWidget *pIndImgWdg ,_FCDIndType_e FCDIndType);
static void _FCDateWidget_SwitchIndicator(_FCDateWidget_t *pThis, IWidget *pIndImgWdg ,_FCDMoveInd_e FCDMoveInd);
static void _FCDateWidget_AddMinuteDatetoVctmodel(_FCDateWidget_t *pThis, IVectorModel *pRingListVctMdl);
void _FCDateRingListWidget_FreeVcrMdl(void *pData, IBase *pOwner);
void _FCDateWidget_FreeModel(void *pData, IBase *pOwner);
static void _FCDateWidget_SetDATEToFCDWdg(_FCDateWidget_t *pThis, MAE_DateTime_t *pDateTime);
static void _FCDateWidget_UpdateFCDisplayDatetoModel(_FCDateWidget_t *pThis);
static void _FCDateWidget_SyncFCTDisplayTimetoRingList(_FCDateWidget_t *pThis);
void _FCDateWidget_VaildDispalayDateCB(void *pObj);
static void _FCDateWidget_ValidateDisplayDate(_FCDateWidget_t *pThis);
static boolean _FCDateWidget_IsValidDate(_FCDateWidget_t *pThis, u16 *pYear, u16 *pMonth, u16 *pDay);
void _FCDateRingListWidget_CancelVaildateDisplayTimer(_FCDateWidget_t *pThis);
void _FCDateRingListWidget_ViewMdlLsn(void *pUsrData, ModelEvent_t *pMdlEvent);
static boolean _FCDateWidget_RingListWdgHdlEvent(void *pUsr, MAE_EventId evt, u32 P1, u32 P2);
static void _FCDateWidget_RingListWdgHdlFree(void *pData);

static boolean _FCDateWidget_SetProperty(_FCDateWidget_t *pThis, u32 P1,  u32 P2);
static boolean _FCDateWidget_GetProperty(_FCDateWidget_t *pThis, u32 P1,  u32 P2);
static boolean _FCDateWidget_HandleKey(_FCDateWidget_t *pThis, u32 P1,  u32 P2);
static void _FCDateWidget_ReloadRC(_FCDateWidget_t *pThis, DisplayMode_e nDispMode);

#endif /* __MMI_WDG_FC_DATE_PRIV_H__ */
