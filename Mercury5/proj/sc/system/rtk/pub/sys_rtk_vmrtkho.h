/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/

/****************************************************************************/
/*  File    : vm_rtk.ho                                                     */
/*--------------------------------------------------------------------------*/
/*  Description:  OS API                                                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_RTK_VMRTKHO_H__
#define __SYS_RTK_VMRTKHO_H__

#include "vm_types.ht"

#ifndef __SDK_SIMULATION__
#include "drv_timer_types.h"
#include "drv_timer_api.h"
#endif
/****************************************************************************/
/*  OS constants                                                            */
/****************************************************************************/
/****************************************************************************/

/* Return values */
#define VM_RTK_OK                               10

/****************************************************************************/
/*  OS structure                                                            */
/****************************************************************************/
/****************************************************************************/


/*****************************************/
/*     Queue structure                   */
/*****************************************/
#ifdef __SDK_SIMULATION__

struct vm_rtkEnvelop_t;

typedef struct
{
    struct vm_rtkEnvelop_t  *osEnvelopFirst;
    struct vm_rtkEnvelop_t  *osEnvelopLast;
} vm_rtkQueue_t;

typedef enum
{
    VM_RTK_STK_POOL_GRP,
    VM_RTK_CUS_POOL_GRP
}	vm_rtkPoolGroup_e;


/****************************************************************************/
/*  OS functions                                                            */
/****************************************************************************/
/****************************************************************************/

/*****************************************/
/*      Timer management                 */
/*****************************************/

/* Starts timer counting.             */
s32 vm_rtkStartTimer(u32 TimerId, s32 bCyclic, u16 MBoxNo, u32 TimerValue);


/* Stops the timer identified by TimerId.                               */
u32 vm_rtkStopTimer(u32 TimerId);

/* Check if a Timer is Active */
s32 vm_rtkIsTimerActive(u32 TimerId);

#endif

/****************************************************************************/
/*  OS macro                                                                */
/****************************************************************************/
/****************************************************************************/

#ifndef __SDK_SIMULATION__
#define VM_RTK_TICK_TIME        DRV_RTK_TICK_TIME
#define VM_RTK_TICK_TIME_REAL   DRV_RTK_TICK_TIME_REAL
#define VM_RTK_MS_TO_TICK(MsT)  DRV_RTK_MS_TO_TICK(MsT)
#define VM_RTK_MS_TO_TICK_64(MsT)  DRV_RTK_MS_TO_TICK_64(MsT)
#define VM_RTK_S_TO_TICK(SecT)  DRV_RTK_S_TO_TICK(SecT)
#define VM_RTK_MN_TO_TICK(MnT)  DRV_RTK_MN_TO_TICK(MnT)
/* In order to avoid the phenomenon of overflow */
//#define VM_RTK_AO_S_TO_TICK(SecT)  DRV_RTK_AO_S_TO_TICK(SecT)

#define VM_RTK_TICK_TO_MS(T) DRV_RTK_TICK_TO_MS(T)
//#define VM_RTK_TICK_TO_MS(T) ((u32)(((T)* 303955) >> 16))
#define VM_RTK_TICK_TO_S(T)  DRV_RTK_TICK_TO_S(T)

//#define VM_RTK_FRAME_TO_TICK(F) DRV_RTK_FRAME_TO_TICK(F)
//#define VM_RTK_TICK_TO_FRAME(T) DRV_RTK_TICK_TO_FRAME(T)

#define VM_RTK_MAXTIMER_VALUE   DRV_RTK_MAXTIMER_VALUE

#else //__SDK_SIMULATION__
#define VM_RTK_TICK_TIME        15
#define VM_RTK_TICK_TIME_REAL   (15.0)
#define VM_RTK_MS_TO_TICK(MsT)  ((u32)((MsT) >= VM_RTK_TICK_TIME) ? (((MsT)+(VM_RTK_TICK_TIME-1) )/VM_RTK_TICK_TIME) : 1)
#define VM_RTK_S_TO_TICK(SecT)  VM_RTK_MS_TO_TICK((SecT*60))
#define VM_RTK_MN_TO_TICK(MnT)  VM_RTK_MS_TO_TICK((MnT*3600))
/* In order to avoid the phenomenon of overflow */
#define VM_RTK_AO_S_TO_TICK(SecT)  ((u32)((((u64)SecT)* 55189) >> 8))

#define VM_RTK_TICK_TO_S(T)  ((u32)((T)* VM_RTK_TICK_TIME)/1000)
#define VM_RTK_TICK_TO_MS(T) ((u32)((T)* VM_RTK_TICK_TIME))

#define VM_RTK_FRAME_TO_TICK(_x)   ((_x & 0x3) ? ((_x >> 2)+1) : (_x >> 2))
#define VM_RTK_TICK_TO_FRAME(T)    ((T*VM_RTK_TICK_TIME)>>2)

#define VM_RTK_MAXTIMER_VALUE      -1L

#endif //__SDK_SIMULATION__


#endif  /* __SYS_RTK_VMRTKHO_H__ */


