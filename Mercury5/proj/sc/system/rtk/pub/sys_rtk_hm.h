/******************************************************************/
/*  File    : RTKMACRO.H                                          */
/*-------------------------------------------------------------   */
/*  Scope   :  Internal RTK definitions                           */
/*                                                                */
/*  Contents:                                                     */
/*                                                                */
/*  Changes    :                                                  */
/******************************************************************/

#ifndef __SYS_RTK_HM_H__
#define __SYS_RTK_HM_H__

/** for heap instrumentation **/
#ifdef __RTK_DIAGNOSE__

#define RTK_DEFINE_RTC()
#define RTK_SET_TIME(time)    time = 0
#define RTK_SET_DATE(date)    date = 0
#define RTK_GET_TIME(time)    time
#define RTK_GET_DATE(date)    date

#endif // __RTK_DIAGNOSE__


/******** Macro ************/
#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
#endif   // __SDK_SIMULATION__

#define RTK_GETLR(Lr)	Lr = __return_address()

// Use reduced disable/enable API in kernel
#if !defined(__RTK_OVER_R2__) && !defined(__SDK_SIMULATION__)
#ifdef __FIXME__
#define RTK2_ENABLE_K(itmask) RTK2_ENABLE_K_R((int)itmask)
#define RTK2_DISABLE_K (rtk_ItMask_t) RTK2_DISABLE_K_R
#endif
#endif

#ifdef __SDK_SIMULATION__
#ifdef __cplusplus
}
#endif //__cplusplus
#endif // __SDK_SIMULATION__

#define LOW_U8(w)		((u8 *)(&w))[0]
#define HIGH_U8(w)		((u8 *)(&w))[1]

#define LOW_U16(w) 		((u16 *)(&w))[0]
#define HIGH_U16(w)		((u16 *)(&w))[1]

#define ALIGN8(P)                ( (u32) ((char *)(P) + 7) & ~7)

#ifdef __RTK_MEMORY_ALIGN8__
#define ALIGN_MEM(P)    ALIGN8(P)
#else
#define ALIGN_MEM(P)    ALIGN(P)
#endif
#define SIZE_POOL(a,b)  (ALIGN_MEM(a) + LEN_rtk_MemOverhead_t) * (b)


#define RTK_ASSERT(_condition,_reason) {	\
    if (!(_condition)) _ERROR((_RTK|FATAL , _reason));		\
}

#define RTK_CUSTOMER_TASKID(_taskNumber)  (RTK_FIRST_CUSTOMER_TASKID + _taskNumber - 1)

#endif    /* __SYS_RTK_HM_H__ */

