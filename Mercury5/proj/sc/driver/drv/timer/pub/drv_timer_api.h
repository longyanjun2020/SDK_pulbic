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
* @file    drv_timer_api.h
* @version
* @brief   Timer/WDT driver header file.
*
*/

#ifndef __DRV_TIMER_API_H__
#define __DRV_TIMER_API_H__

#include "drv_timer_forward.h"
#include "halex_rtk_timer.h"

typedef void (*PfnTimerIntcISR)(void);


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define DRV_RTK_TICK_TIME        HAL_RTK_TICK_TIME
#define DRV_RTK_TICK_TIME_REAL   HAL_RTK_TICK_TIME_REAL
#define DRV_RTK_MS_TO_TICK(MsT)  HAL_RTK_MS_TO_TICK(MsT)
#define DRV_RTK_MS_TO_TICK_64(MsT)  HAL_RTK_MS_TO_TICK_64(MsT)
#define DRV_RTK_S_TO_TICK(SecT)  HAL_RTK_S_TO_TICK(SecT)
#define DRV_RTK_MN_TO_TICK(MnT)  HAL_RTK_MN_TO_TICK(MnT)
/* In order to avoid the phenomenon of overflow */
//#define DRV_RTK_AO_S_TO_TICK(SecT)  HAL_RTK_AO_S_TO_TICK(SecT)

#define DRV_RTK_TICK_TO_MS(T) HAL_RTK_TICK_TO_MS(T)
//#define VM_RTK_TICK_TO_MS(T) ((u32)(((T)* 303955) >> 16))
#define DRV_RTK_TICK_TO_S(T)  HAL_RTK_TICK_TO_S(T)

///#define DRV_RTK_FRAME_TO_TICK(F) HAL_RTK_FRAME_TO_TICK(F)
//#define DRV_RTK_TICK_TO_FRAME(T) HAL_RTK_TICK_TO_FRAME(T)

#define DRV_RTK_MAXTIMER_VALUE   HAL_RTK_MAXTIMER_VALUE


/*=============================================================*/
// Global function definition
/*=============================================================*/
DrvTimerErrorCode_e DrvSysTimerInit(void);

DrvTimerErrorCode_e DrvWDTimer0Enable(bool en);
DrvTimerErrorCode_e DrvWDTimer1Enable(bool en);
DrvTimerErrorCode_e DrvWDTimer0IntEnable(bool en);
DrvTimerErrorCode_e DrvWDTimer1IntEnable(bool en);
DrvTimerErrorCode_e DrvWDTimer0IsEnable(bool* en);
DrvTimerErrorCode_e DrvWDTimer1IsEnable(bool* en);
DrvTimerErrorCode_e DrvWDTimer0Ack(void);
DrvTimerErrorCode_e DrvWDTimer1Ack(void);
DrvTimerErrorCode_e DrvWDTimer0SetTimeoutTicks(u32 tick);
DrvTimerErrorCode_e DrvWDTimer1SetTimeoutTicks(u32 tick);
DrvTimerErrorCode_e DrvWDTimer0GetTimeoutTicks(u32* tick);
DrvTimerErrorCode_e DrvWDTimer1GetTimeoutTicks(u32* tick);
DrvTimerErrorCode_e DrvWDTimer0IsTimeout(bool* flag);
DrvTimerErrorCode_e DrvWDTimer1IsTimeout(bool* flag);
DrvTimerErrorCode_e DrvWDTimer0ClearTimeout(void);
DrvTimerErrorCode_e DrvWDTimer1ClearTimeout(void);
DrvTimerErrorCode_e DrvWDTimer0GetStatus(u32* status);
DrvTimerErrorCode_e DrvWDTimer1GetStatus(u32* status);

#if defined(__CHIPDRV_DBB_WDT___)
DrvTimerErrorCode_e DrvWDTDbbIntEnable(bool en);

/**
* @brief        To register dbb watchdog timer ISR
*
* @param[in]    pfnDbbWDTimerISR    DBB WatchDog Timer Isr
* @retval       none
*/
void DrvDbbWDTimerIsrReg(PfnTimerIntcISR pfnDbbWDTimerISR);

/**
* @brief        To release(disconnect) dbb watchdog timer ISR
*
* @retval       none
*/
void DrvDbbWDTimerIsrRel(void);

#endif //__CHIPDRV_DBB_WDT___

#ifdef __CHIPDRV_MM_TIMER___
/**
* @brief        To register MM timer ISR
*
* @param[in]    pfnMMTimerISR    MM Timer Isr
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimerIsrReg(DrvMMTimerId_e mmTimerId, PfnTimerIntcISR pfnMMTimerISR);

/**
* @brief        To Init MM timer Irq
*
* @param[in]    pfnMMTimerISR    MM Timer Isr
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimerIrqInit(void);

/**
* @brief        To Enable MM timer0
*
* @param[in]    bIsEnable        TRUE/FALSE to enable/disable MM Timer0.
* @param[in]    bIsPeriodic      TRUE/FALSE to period/non-periond MM Timer0.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer0Enable(bool bIsEnable, bool bIsPeriodic);

/**
* @brief        To Enable MM timer1
*
* @param[in]    bIsEnable        TRUE/FALSE to enable/disable MM Timer1.
* @param[in]    bIsPeriodic      TRUE/FALSE to period/non-periond MM Timer1.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer1Enable(bool bIsEnable, bool bIsPeriodic);

/**
* @brief        To Set MM timer0 timeout
*
* @param[in]    nMs        millisecond for timer0 timeout.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer0TimeoutMs(u32 nMs);

/**
* @brief        To Set MM timer1 timeout
*
* @param[in]    nMs        millisecond for timer1 timeout.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer1TimeoutMs(u32 nMs);

/**
* @brief        To Mask/Unmask MM timer0
*
* @param[in]    bIsMask        TRUE/FALSE to mask/unmask MM Timer0.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer0IntMask(bool bIsMask);

/**
* @brief        To Mask/Unmask MM timer1
*
* @param[in]    bIsMask        TRUE/FALSE to mask/unmask MM Timer1.
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer1IntMask(bool bIsMask);

/**
* @brief        To Know timeout status of MM timer 0
*
* @param[out]   bIsTimeOut        TRUE: timerout, FALSE: not timeout..
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer0IsTimeout(bool *bIsTimeOut);

/**
* @brief        To Know timeout status of MM timer 1
*
* @param[out]   bIsTimeOut        TRUE: timerout, FALSE: not timeout..
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer1IsTimeout(bool *bIsTimeOut);

/**
* @brief        To Clear MM timer0 timeout status
*
* @void
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer0Clear(void);

/**
* @brief        To Clear MM timer1 timeout status
*
* @void
* @retval       DRV_TIMER_SUCCESS
*/
DrvTimerErrorCode_e DrvMMTimer1Clear(void);

#endif // __CHIPDRV_MM_TIMER___

u32 DrvTimerGetOstickMaxCount(void);
u32 DrvTimerGetStdaTimerMaxCount(void);
u32 DrvTimerGetTimsoftMaxCount(void);
u32 DrvTimerStdaTimerUs2Tick(u32 us);
u32 DrvTimerStdaTimerTick2Us(u32 tick);
u32 DrvTimerMs2Ostick(u32 ms);
u32 DrvTimerOstick2Ms(u32 tick);
void DrvTimerStdaTimerStart(void);
u32 DrvTimerStdaTimerGetTick(void);
u32 DrvTimerStdaTimerGetTimeoutLength(void);
void DrvTimerUdelay(u32 us);
void DrvTimerUdelayCond(s32 cond, u32 us);
u32 DrvTimerGetGlobalTimerMaxCount(void);
u32 DrvTimerGlobalTimerMs2Tick(u32 ms);
u32 DrvTimerGlobalTimerTick2Ms(u32 tick);
u64 DrvTimerGlobalTimerTick2MsEx(u64 tick);
u64 DrvTimerGlobalTimerMs2TickEx(u64 ms);
void DrvTimerGlobalTimerStart(void);
u32 DrvTimerGlobalTimerGetTick(void);
u32 DrvTimerGlobalTimerGetTimeoutLength();
void DrvTimerGlobalTimerIntClear();
void DrvTimerGlobalTimerIntEnable();
void DrvTimerGlobalTimerIntDisable();
u32 DrvTimerGlobalTimerIntFlag();
void DrvTimerGlobalTimerIsrReg(PfnTimerIntcISR pfnTimeSoftTimerISR);
void DrvTimerGlobalTimerIsrMask(void);
void DrvTimerGlobalTimerIsrUnMask(void);
void DrvTimerGlobalTimerIsrRel(void);
void DrvTimerTimsoft32kStop(void);
void DrvTimerTimsoft32kStart(u32 tick);
void DrvTimerTimsoftMaskUnmask(bool IsUnmask);
u32 DrvTimerTimsoft32kGetTick(void);
u32 DrvTimerTimsoft32kGetLength(void);
void DrvTimerOstickStop(void);
void DrvTimerOstickRun(u32 tick);
u32 DrvTimerOstickGetTimeoutLength(void);
u32 DrvTimerOstickGetCount(void);
void DrvTimerOstickHoldEnable(void);
void DrvTimerOstickHoldDisable(void);
void DrvTimerOstickIntClear(void);
void DrvTimerOstickIntEnable(void);
void DrvTimerOstickIntDisable(void);
u32 DrvTimerOstickIntFlag(void);
u64 DrvTimerHwToUserTickGlobal(u64 x);
u64 DrvTimerUserToHwTickGlobal(u64 x);
u32 DrvTimerUserToHwTickOstick(u32 x);
u32 DrvTimerHwToUserTickOstick(u32 x);

void DrvTimerTimsoftIntClear(void);
void DrvTimerTimsoftIntEnable(void);
void DrvTimesoftIntDisable(void);
void DrvTimerWDTimerIntClear(void);
void DrvTimerWDTimerIntEnable(void);
void DrvTimerWDTimerIntDisable(void);
u32 DrvTimerSysTimerIntRawStatus(void);
u32 DrvTimerSysTimerIntStatus(void);
void DrvTimerTimsoft32kStartFast(u32 tick);
u32 DrvTimerGetWDTimerMaxTick(void);

extern void DrvOsTimerAck (void);
extern void DrvOsTimerClear (void);

/**
* @brief        To register ostick timer ISR
*
* @param[in]    pfnOstickTimerISR    Ostick Timer Isr
* @retval       none
*/
void DrvOsTickTimerIsrReg(PfnTimerIntcISR pfnOstickTimerISR);

/**
* @brief        To release(disconnect) ostick timer ISR
*
* @retval       none
*/
void DrvOsTickTimerIsrRel(void);

/**
* @brief        To register timesoft timer ISR (only available for some chip)
*
* @param[in]    pfnTimeSoftTimerISR    TimeSoft Timer Isr
* @retval       none
*/
void DrvTimeSoftTimerIsrReg(PfnTimerIntcISR pfnTimeSoftTimerISR);

/**
* @brief        To release(disconnect) timesoft timer ISR
*
* @retval       none
*/
void DrvTimeSoftTimerIsrRel(void);


/**
* @brief        To register watchdog timer ISR
*
* @param[in]    pfnWDTimerISR    WatchDog Timer Isr
* @retval       none
*/
void DrvWDTimerIsrReg(PfnTimerIntcISR pfnWDTimerISR);

/**
* @brief        To release(disconnect) watchdog timer ISR
*
* @retval       none
*/
void DrvWDTimerIsrRel(void);


#endif /* __DRV_TIMER_API_H__ */
