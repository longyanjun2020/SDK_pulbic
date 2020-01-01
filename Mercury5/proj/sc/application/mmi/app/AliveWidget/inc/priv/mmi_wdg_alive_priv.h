/**
 * @file    mmi_wdg_alive_priv.h
 * @brief   This file defines the interface of alivewidget.

 */

#ifndef __MMI_WDG_ALIVE_PRIV_H__
#define __MMI_WDG_ALIVE_PRIV_H__

#if defined(__GADGETS_MMI__) ||defined(__3D_UI_IDLE_GADGETBAR__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_abscontainerbase.h"
#include "mmi_wdg_image.h"
#include "mae_widget_common.h"
#include "mmi_mae_clock_types.h"

#include "mmi_common_alivewidget.h"
#include "mmi_common_util.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"
#include "mmi_alivewidget_rs.h"
/*=============================================================*/
// type and define
/*=============================================================*/
#define PI                       3.14159265
#define ANGLE_ARC   PI / 180

#define ALIVEWIDGET_INVALID_INIT_STATE(eState) (AliveWidget_State_Begin == eState || AliveWidget_State_End == eState || AliveWidget_State_Touch_Click == eState || AliveWidget_State_Touch_Move == eState || AliveWidget_State_Touch_FallDown == eState)

typedef struct
{
	u8  hour;			///< Hour, value range is 0~23
	u8  minute;			///< Minute, value range is 0~59
	u8  second;			///< Second, value range is 0~59 (Not use)
}AliveWidget_DateTime_t;

typedef struct
{
	// For Time information
	AliveWidget_DateTime_t stClockTime;
	IClock     	   *pIClock;
	ClockListener_t IClockListener;

	u8 minLength;
	u8 hourLength;
	u8 nBrushSize;
	u32 handColor;
} AliveWidget_Clock_Info;

enum
{
	E_SMALL_BOUNDARY = 0,
	E_LARGE_BOUNDARY
};
typedef u8 AliveWidget_Boundary_e;

typedef struct
{
	AbsContainerBase_t AbsCntrBase;
	IWidget *pImageWdg; /* Image widget */
	IWidget *pImageDlgWdg;	/* Pet dialog widget */
	IWidget *pTextWdg;	/* Text widget */
	AliveWidgetID_e eID;
	AliveWidget_State_e eCurrentState;
	AliveWidget_Behavior_t stBehavior;
	WPos_t	stAliveWidgetPos;
	WPos_t	stImagePos;
	WPos_t	stImageDlgPos;
	WPos_t	stTextPos;
	IEVTCENTERSRV *pIEvtCenterSrv;
	IALIVEWDGSRV *pIAliveWdgSrv;
	ITouchSrv *pITouchSrv;
	ICFGSrv         *pICFGSrv;
	ICORESRV	    *pICoreSrv;
	IBattery    *pIBattery;
	ModelListener_t BattModelListener;
	IAbsContainer * pParentAbsContainer;
	IDataModel	*pIAliveWdgSrvModel;	//get data model from AliveWdgSrv;
	ModelListener_t AliveWdgSrvMdlListener; //handle  model changes.
	boolean bTouchMoveStatus;
	boolean bTouchDragPosChanged;
	WPos_t stMoveStartPos;
        WPos_t stAliveWidgetStartPos;
        WPos_t stMoveStartPosFirst;
       boolean bActivte;
       boolean bBacklightOn;
       boolean bRequestBacklight;
	AliveWidget_Clock_Info *ptClockInfo;
	u8 nMoveCount;
	WidgetSize_t stWidgetSize;
    u16 u16BoundaryY;
	boolean bUpdateMovingPos;
} AliveWidget_t;


/*=============================================================*/
// functions
/*=============================================================*/
static MAE_Ret AliveWidgetBaseStrucCtor(AliveWidget_t *pThis);
static void AliveWidgetStructDtor(AliveWidget_t *pThis);
boolean AliveWidget_HandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 param1, u32 param2);
void AliveWidget_GetPreferredSize(IAbsContainer *pIAbsContainer, WidgetSize_t *pSize);
void AliveWidget_SetParent(IAbsContainer *pIAbsContainer, IContainer *pParentContainer);
static boolean AliveWidget_SetProperty(AliveWidget_t *pThis, u32 param1, u32 param2);
static boolean AliveWidget_GetProperty(AliveWidget_t *pThis, u32 param1, u32 param2);
void AliveWidget_Draw(AliveWidget_t *pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static void _AliveWidget_ModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
static void _AliveWidget_CreateTimer(AliveWidget_t* pThis, s32 nTimePeriod, PfnMAE_Notify fnCallBack);
static void _AliveWidget_CancelTimer(AliveWidget_t* pThis, PfnMAE_Notify fnCallBack);
static void _AliveWidget_Timer_CallBack_AutoChangeState(void *pHandler);
static void _AliveWidget_Timer_CallBack_Moving(void *pHandler);
static void _AliveWidget_Timer_CallBack_SwitchSamePriorityStates(void *pHandler);
static void _AliveWidget_Init(AliveWidget_t *pThis);
static AliveWidget_State_e _AliveWidget_GetNextState(AliveWidget_t *pThis, AliveWidget_State_e eCurrentState, AliveWidget_InputEvent_e eInputEvent);
static MAE_Ret _AliveWidget_GetStateBehavior(AliveWidget_t *pThis, AliveWidget_State_e eState, AliveWidget_Behavior_t *pstBehavior);
static MAE_Ret _AliveWidget_GetAliveWidgetInfo(AliveWidget_t *pThis, AliveWidget_Init_State_Info_t *pstInitStateInfo);
static void _AliveWidget_SaveCurrentState(AliveWidget_t *pThis);
static boolean _AliveWidget_HandleTouchEvent(AliveWidget_t *pThis, MAE_EventId evt, u32 param1, u32 param2);
static boolean _AliveWidget_AllowToChangeState(AliveWidget_t *pThis, AliveWidget_State_e eNewState, AliveWidget_State_e eOldState);
static void _AliveWidget_ChangeToNewState(AliveWidget_t *pThis, AliveWidget_State_e eNewState);
static void _AliveWidget_UpdateDrawData(AliveWidget_t *pThis);
static void _AliveWidget_MovingToNextPosition(AliveWidget_t *pThis);
static void _AliveWidget_TouchUpdatePosition(AliveWidget_t *pThis, s32 x, s32 y);
static boolean _AliveWidget_TouchEventInsideContainer(AliveWidget_t *pThis, s32 x, s32 y, boolean bUpdatePos);
static void _AliveWidget_UpdateWidgetsPosition(AliveWidget_t *pThis);
static boolean _AliveWidget_LaunchApp(AliveWidget_t *pThis);
static void _AliveWidget_Notify(AliveWidget_t *pThis, u32 MdlEvt, u32 dwParam);
static void _ALiveWidget_ClockListener(void *pUsrData, MAEClkItemId_t id, void *pItemData);
static void _ALiveWidget_FreeClockInfo(AliveWidget_t* pThis);
static void _ALiveWidget_DrawClock(AliveWidget_t* pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static boolean _AliveWidget_IsPositionOutOfBoundary(AliveWidget_t *pThis, AliveWidget_Boundary_e bSmallBoundary);
static boolean _AliveWidget_IsNeedToSwitchSamePriorityState(AliveWidget_t *pThis);
static void _AliveWidget_AdjustPositionToInsideBoundary(AliveWidget_t *pThis, AliveWidget_Boundary_e bSmallBoundary);
static void _AliveWidget_ActivateVisible(AliveWidget_t *pThis);
static void _AliveWidget_SaveClockPos(AliveWidget_t *pThis);
static void _AliveWidget_BattModelListener(void *pUsrData, ModelEvent_t *pMdlEvent);
static boolean _Alivewidget_IsLowBattery(AliveWidget_t *pThis);
static boolean _Alivewidget_IsChargingBattery(AliveWidget_t *pThis);
static boolean _AliveWidget_IsPositionInShortcut(AliveWidget_t *pThis, MAE_EventId evt, s32 param1, s32 param2) ;
static void _Alivewidget_ReloadRC(AliveWidget_t *pThis, DisplayMode_e nDispMode);
#endif 
#endif //__MMI_WDG_ALIVE_PRIV_H__
/*=============================================================*/
// end of file
