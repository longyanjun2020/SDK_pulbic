/* @file mmi_schedulersrv_priv.h
*
* Class Id: CLSID_SCHEDULERSRV
*
* @version $Id:
*/
#ifndef __MMI_SCHEDULERSRV_PRIV_H__
#define __MMI_SCHEDULERSRV_PRIV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_schedulersrv.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_notifier.h"

/*-------------------------------------------------------------------------*/
#define SCHSRV_SAFE_HEADER_PATTERN      (0xA5A5A5A5)

//Notes: currently use scheduler event
//1: Auto Power-On
//1: Clock alarm, Calendar alarm, To-Do alarm and Auto Power-Off
//1: Factory Power-On alarm
//6: FM schedule Play
//6: FM schedule Record
#define SCHSRV_INFO_INIT_SIZE  (16)
#define SCHSRV_INFO_EXPAND_SIZE SCHSRV_INFO_INIT_SIZE
#define SCHSRV_INFO_MAX_EXP_TIMES (2)


#define SCHSRV_INFO_MAX_SIZE (SCHSRV_INFO_INIT_SIZE + SCHSRV_INFO_MAX_EXP_TIMES * SCHSRV_INFO_EXPAND_SIZE)
#define SCHSRV_NOT_FOUND           (0xFFFF)

#define SCHSRV_TEST_ENABLE       (0)

typedef struct SchSrv_Node_tag
{
    boolean bIsAvail;
    u32 nSchedulerId;
    MAE_DateTime_t tUtcDateTime;
    SCHSRV_CALLBACK_ENUM_e eCBEnum;
    SCHSRV_SCHEDULE_TYPE_e eType;
    SCHSRV_PeriodicType nPeriodType;
}SchSrv_Node_t;

typedef struct SchSrv_Info_tag
{
    u32 MarkPattern;
    u16 max;
    SchSrv_Node_t pList[SCHSRV_INFO_INIT_SIZE];
}SchSrv_Info_t;

typedef enum
{
    SCHSRV_RUNSTATE_POWERON, //before idle app is run.
    SCHSRV_RUNSTATE_NORMAL,  //after idle app is run.
}SchSrv_RunState_e;

typedef struct
{
    u16 nNum;
    SCHSRV_CONFIRM_CAUSE_e eCause;
}SchSrv_Confirm_Info_t;

typedef struct SchSrv_t_
{
    DECLARE_FUNCTBL(ISCHEDULERSRV); // function table pointer
    u32 nRefCnt;     // reference count
    IClock *pIClock;
    ClockListener_t IClockListener;
    SchSrv_Info_t *pSchSrvInfo;
    SchSrv_RunState_e eRunState;
    boolean bRegClockListener;
    MAE_Notifier_t *pNotifier;
    SchSrv_Confirm_Info_t tConfirmInfo;
} SchSrv_t;

typedef enum
{
    SCHSRV_SEARCH_ID = 0,
    SCHSRV_GET_AVAILSLOT,
    SCHSRV_GET_SMALLDT,
    SCHSRV_SEARCH_SCHTYPE,
}SCHSRV_SEARCH_TYPE;

typedef struct
{
    SCHSRV_SCHEDULE_TYPE_e eScheduleType;
    MAE_DateTime_t *ptDateTime;
}SchSrv_Search_SchType_Data_t;

extern void _SCHSRV_Init(SchSrv_t *ptSchSrv);
extern MAE_Ret _SCHSRV_New(SchSrv_t *ptSchSrv);
extern void _SCHSRV_Release(SchSrv_t *ptSchSrv);
extern MAE_Ret _SCHSRV_StopRTCAlarm(void);
extern MAE_Ret _SCHSRV_SetRTCAlarm(MAE_DateTime_t *ptUTCDateTime);
extern void _SchSrv_MinuteTick_Callback(void *data, u32 nParam);
extern void _SchSrv_SystemTimeChange_Callback(void *data, u32 nParm);
extern void _SchSrv_ClockListener(void *pUsrData, MAEClkItemId_t id, void *pItemData);
extern MAE_Ret  _SCHSRV_LoadInfo(SchSrv_Info_t** pptInfo);
extern MAE_Ret  _SCHSRV_SaveInfo(SchSrv_Info_t* ptInfo);
extern MAE_Ret _SCHSRV_SetInfo(SchSrv_Info_t *ptInfo, u16 nPosition, SchSrv_Node_t *ptNode);
extern void _SCHSRV_InitInfo(SchSrv_Info_t *ptInfo);
extern void _SCHSRV_ReleaseInfoSlot(SchSrv_Info_t *ptInfo, u16 nPosition);
extern u16 _SCHSRV_SearchInfo(SchSrv_Info_t *ptInfo, SCHSRV_SEARCH_TYPE eType, void *pData);
extern MAE_Ret _SCHSRV_ExpandInfo(SchSrv_Info_t** pptInfo);
extern boolean _SCHSRV_Notify(SchSrv_t *pThis, u16 *pnConfirmNum, MAE_DateTime_t *ptCurUtcTime, SCHSRV_CAUSE_REASON_e eCauseReason);
extern void _SCHSRV_AdjustPeriodicSch(SchSrv_Info_t *ptInfo, MAE_DateTime_t *ptCurUtcDT, SCHSRV_CAUSE_REASON_e eCauseReason);
extern MAE_Ret _SCHSRV_GetNextSchDT(MAE_DateTime_t *ptCurUtcDT, MAE_DateTime_t *ptRefUtcDT, SCHSRV_PeriodicType nPeriod, MAE_DateTime_t *ptNextDT);
extern boolean _SCHSRV_IsInterestedCause(SCHSRV_SCHEDULE_TYPE_e eType, SCHSRV_CAUSE_REASON_e eCauseReason);
extern void _SCHSRV_Dump_DateTime(MAE_DateTime_t *ptDT);
extern void _SCHSRV_Dump_SchSrvInfo(SchSrv_Info_t *pSchSrvInfo);

#if (SCHSRV_TEST_ENABLE == 1)
extern void _SCHSRV_Test_NextPeriod(void);
#endif
/*-------------------------------------------------------------------------*/
#endif /* __MMI_SCHEDULERSRV_PRIV_H__ */
