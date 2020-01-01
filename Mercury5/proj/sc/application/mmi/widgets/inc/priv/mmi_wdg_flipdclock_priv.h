/**
* @file    mmi_wdg_flipdclock_priv.h
* @brief   The document describes internal declartion of flipdclock Widget
* @author  Ryan.Chou
* @version $Id: mmi_wdg_flipdclock_priv.h  2010-12-3 Lin.wang $
*/
#ifdef __UI_STYLE_FLIPDCLOCK__
#ifndef __MMI_WDG_FLIPDCLOCK_PRIV_H__
#define __MMI_WDG_FLIPDCLOCK_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_abscontainer_priv.h"
#include "mmi_wdg_layout.h"
#include "mmi_mae_clock.h"
#include "mmi_cfgsrv.h"
#include "mmi_log.h"
#include "mmi_wdg_text.h"
#include "mmi_wdg_image.h"
#include "mmi_coresrv.h"
#include "mmi_mae_clock_types.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#ifndef BREAKIF
#define BREAKIF(a)    {if(MAE_RET_SUCCESS != a) break;}
#endif

#define FLIP_ANIMATION_STEP 13//8
#define FLIP_ANIMATION_DELAY  3

enum
{
	FLIPDCLOCK_HOUR,
	FLIPDCLOCK_MIN,
	FLIPDCLOCK_NUM
};

typedef struct {
	AbsContainer_t	AbsCntrBase;			///< Using AbsContainer_t as base structure.
	ModelListener_t	MdlListener;

	IWidget                    *pAMPMTxtWdg;
	// Hour
	IWidget         *pHourFlipImgWdg;
	IWidget			*pHourLeftTopImgWdg;
	IWidget			*pHourLeftBtmImgWdg;
	IWidget			*pHourRightTopImgWdg;
	IWidget			*pHourRightBtmImgWdg;

    IImage                     *pHourLTImg;
	IImage                     *pHourLBImg;
	IImage                     *pHourRTImg;
	IImage                     *pHourRBImg;


	// Minute
	IWidget                     *pMinFlipImgWdg;
	IWidget                     *pMinLeftTopImgWdg;
	IWidget                     *pMinLeftBtmImgWdg;
	IWidget                     *pMinRightTopImgWdg;
	IWidget                     *pMinRightBtmImgWdg;

	IImage                     *pMinLTImg;
	IImage                     *pMinLBImg;
	IImage                     *pMinRTImg;
	IImage                     *pMinRBImg;

	IClock                      *pIClock;
	ClockListener_t             tClockListener;

	ICORESRV	                *pICoreSrv;

    boolean                     bAnimation;
    u8                         nCurStepHR;
    u8                         nCurStepMIN;
    boolean                     bEnableFlipAnim;
} FlipDClockWidget_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/

//new function
MAE_Ret FlipDClockWidget_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret FlipDClockWidget_Ctor(FlipDClockWidget_t *pThis);
void FlipDClockWidget_Dtor(FlipDClockWidget_t * pThis);

/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/
//add reference function => use the function in container base

//release function
u32 FlipDClockWidget_Release(IAbsContainer *pIAbsContainer);
//setsize function
void FlipDClockWidget_SetSize(IAbsContainer *pIAbsContainer, WidgetSize_t *pSize);

//query interface function => use the function in PropContainer

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
boolean FlipDClockWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IPropContainer interface
------------------------------------------------------------------------------------------*/

//add function => use the function in container base

//delete function => use the function in container base

//container move function
MAE_Ret FlipDClockWidget_Move(IAbsContainer *pIAbsContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);

//get widget function => use the function in container base

//invalidate function => use the function in PropContainer

//locate function => use the function in container base

//Set the proportion function => use the function in PropContainer

//Get the proportion function => use the function in PropContainer

//Set the padding function => use the function in PropContainer

//Get the padding function => use the function in PropContainer


/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/

//set model function
MAE_Ret FlipDClockWidget_SetModel(IAbsContainer *pIAbsContainer, IModel *pIModel, IBase* pOwner);

//Get preferred size function => use the function in PropContainer

//other functions for IWidget interface are used in container base
boolean FlipDClockWidget_DefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

#endif //__MMI_WDG_FLIPDCLOCK_PRIV_H__
#endif //__UI_STYLE_FLIPDCLOCK__
/*=============================================================*/
// end of file

