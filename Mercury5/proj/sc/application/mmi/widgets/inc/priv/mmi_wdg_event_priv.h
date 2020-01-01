/**
 * @file	mmi_wdg_event_priv.h
 * @version	$Id: mmi_wdg_event_priv.h 13288 2008-08-14 11:48:55Z lena.lin $
 * @brief	
 *
 */
#ifndef __MMI_WDG_EVENT_PRIV_H__
#define __MMI_WDG_EVENT_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_event.h"
#include "mmi_wdg_image_text_image.h"
#include "mae_abscontainerbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
	EVENTWDG_STYLE_SINGLE = 0,
	EVENTWDG_STYLE_GROUP,
	EVENTWDG_STYLE_FOCUS,
	EVENTWDG_STYLE_TOTAL
};

typedef struct {
	AbsContainerBase_t AbsCntrBase;	///< Using AbsContainer_t as base structure.
	ModelListener_t MdlLsn;		///< Model listener for listening the data model change.
	IWidget *pSummaryWdg;		///< An ImageText widget to display event summary.
	IWidget *pDurationWdg;		///< An Bitmap widget to display duration bar.
	boolean bAlarmExist;		///< An boolean to indicate this event has alarm or not
	u32 nOverlapCount;			///< An u32 variable to indicate how many event is overlap on this time slot
	u32 nEventUID;
	RGBColor_t tBGColor[EVENTWDG_STYLE_TOTAL];
	RGBColor_t tBorderColor[EVENTWDG_STYLE_TOTAL];
	EvtTime_t tStartTime;
	EvtTime_t tEndTime;
	u8 nBorderPixelSize[EVENTWDG_STYLE_TOTAL];
} _EventWidget_t;

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret EventWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean EventWdg_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret _WdgEventConstructor(_EventWidget_t *pThis);
void _WdgEventDestructor(_EventWidget_t *pThis);

MAE_Ret EventWidget_SetModel(_EventWidget_t *pThis, IModel *pIModel, IBase *pOwner);
void EventWidget_SetSize(_EventWidget_t *pThis, WidgetSize_t *pSize);

#endif //__MMI_WDG_EVENT_PRIV_H__
/*=============================================================*/
// end of file
