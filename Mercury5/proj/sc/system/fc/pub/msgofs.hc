/****************************************************************************/
/*  File    : msgofs.hc                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : GSM project message offset definition                         */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __MSGOFS_HC__
#define __MSGOFS_HC__


#include "stdcomp.h"


/*
** =========================================================================
**     MESSAGE OFFSET DEFINITIONS
**
**     +--------+--------+
**     |                 |
**     +--------+--------+
**        ^        ^
**        |        +-------- Msg sub ID (0 .. 255)
**        +----------------- Module ID  (service provider)
** =========================================================================
*/
#include "vm_msgof.hc"                 /*--- Base defined for message exchanged between CUS <--> WM ---*/

#define ABB_BASE        (u16) (0x5000) /*--- Base defined for message exchanged between  WM <--> WM ---*/
#define SYS_BASE        VM_SYS_BASE
#define SYS_RTK_BASE    VM_SYS_RTK_BASE
#define RR_BASE         (u16) (0x5200)
#define MM_BASE         (u16) (0x5300)
#define GMM_BASE        MM_BASE
#define CC_BASE         (u16) (0x5400)
#define SMS_BASE        (u16) (0x5500)
#define SIM_BASE        (u16) (0x5600)
#define DL_BASE         (u16) (0x5700)
#define L1C_BASE        (u16) (0x5800)   /* for L1C-Prot communication   */
#ifdef VM_HWL_BASE /* since PACK 3+ */
#define HWL_BASE        VM_HWL_BASE
#else /* in PACK 2 and PACK 3 */
#define HWL_BASE        (u16) (0x5900)
#endif /* VM_HWL_BASE */
#define AT_BASE         (u16) (0x5A00)
#define DAT_BASE        (u16) (0x5B00)
#define IRLAP_BASE      (u16) (0x5D00)
#define IRLMP_BASE      (u16) (0x5E00)
#define IP_BASE         (u16) (0x5F00)
#define RTK_BASE        (u16) (0x6000)  /* for RTK internal communication */
#define XMOD_BASE       (u16) (0x6100)
#define DWL_BASE        (u16) (0x6200)
#define USB_BASE        (u16) (0x6300)  /* For USB notification mechanism */        
#define OBX_BASE        (u16) (0x6400)
                                        /*-------------*/
#define V24_BASE        VM_V24_BASE   
#define SS_BASE         VM_SS_BASE
#define FCM_BASE        VM_FCM_BASE
#define WBT_BASE        VM_WBT_BASE
#define TRC_BASE        (u16) (0x6A00)

// GPRS data Base
#define SM_BASE         (u16) (0x7100)
#define LLC_BASE        (u16) (0x7200)
#define SNDCP_BASE      (u16) (0x7300)
#define RLU_BASE        (u16) (0x7400)
#define RLD_BASE        (u16) (0x7500)
#define PPS_BASE        (u16) (0x7600)


#define AUDIO_MSG_BASE    (0x7700)
#define AUDIO_BASE        ((u16) AUDIO_MSG_BASE)

#define TIMER_TEMPID_BASE 0x7800

#ifdef __MSTAR_DUAL_SIM__
#define CE_BASE		(u16)(0x7900)

#if defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && (defined(__MSTAR_DUAL_SIM_DUP_GLOB__) || defined(__TRACE_C__))

//extern    volatile u8      Rtk_CurrentTask;

#ifdef __TRACE_C__
  #define EXT_MSGOFS
  #define INIT_MSGOFS(X,Y) ={X,Y}
#else
  #define EXT_MSGOFS extern
  #define INIT_MSGOFS(X,Y)
#endif

#define DUO_TIMER_OFFSET 0x3000
#define SMS_DUO_TIMER_OFFSET DUO_TIMER_OFFSET

EXT_MSGOFS const u16 RrTimerBase[MS_NUM_OF_MODULES]  INIT_MSGOFS(RR_BASE ,(RR_BASE  + DUO_TIMER_OFFSET));
EXT_MSGOFS const u16 MmTimerBase[MS_NUM_OF_MODULES]  INIT_MSGOFS(MM_BASE ,(MM_BASE  + DUO_TIMER_OFFSET));
EXT_MSGOFS const u16 CcTimerBase[MS_NUM_OF_MODULES]  INIT_MSGOFS(CC_BASE ,(CC_BASE  + DUO_TIMER_OFFSET));
EXT_MSGOFS const u16 DlTimerBase[MS_NUM_OF_MODULES]  INIT_MSGOFS(DL_BASE ,(DL_BASE  + DUO_TIMER_OFFSET));
EXT_MSGOFS const u16 L1cTimerBase[MS_NUM_OF_MODULES] INIT_MSGOFS(L1C_BASE,(L1C_BASE  + DUO_TIMER_OFFSET));
EXT_MSGOFS const u16 SsTimerBase[MS_NUM_OF_MODULES]  INIT_MSGOFS(SS_BASE ,0xD900);

#define RR_TIMER_BASE    RrTimerBase [Rtk_CurrentModule]
#define MM_TIMER_BASE    MmTimerBase [Rtk_CurrentModule]
#define GMM_TIMER_BASE   MM_TIMER_BASE
#define CC_TIMER_BASE    CcTimerBase [Rtk_CurrentModule]
#define SMS_TIMER_BASE   SMS_BASE
#define DL_TIMER_BASE    DlTimerBase [Rtk_CurrentModule]
#define L1C_TIMER_BASE   L1cTimerBase[Rtk_CurrentModule]
#define SS_TIMER_BASE    SsTimerBase [Rtk_CurrentModule]
#ifdef __DUPLICATE_IP_TASK__
#define IP_TIMER_BASE    IP_BASE + DUO_TIMER_OFFSET
#else
#define IP_TIMER_BASE    IP_BASE
#endif

#else

#ifdef __DUPLICATE_TASK__
#define DUO_TIMER_OFFSET 0x3000

#define RR_TIMER_BASE    RR_BASE  + DUO_TIMER_OFFSET           // 0x8200
#define MM_TIMER_BASE    MM_BASE  + DUO_TIMER_OFFSET           // 0x8300
#define GMM_TIMER_BASE   MM_TIMER_BASE
#define CC_TIMER_BASE    CC_BASE  + DUO_TIMER_OFFSET           // 0x8400
#define SMS_TIMER_BASE   SMS_BASE + DUO_TIMER_OFFSET           // 0x8500
#define DL_TIMER_BASE    DL_BASE  + DUO_TIMER_OFFSET           // 0x8700
#define L1C_TIMER_BASE   L1C_BASE + DUO_TIMER_OFFSET           // 0x8800
#define SS_TIMER_BASE    (u16) (0xD900) 
#define IP_TIMER_BASE    IP_BASE + DUO_TIMER_OFFSET             // 0x8F00
#else
#define RR_TIMER_BASE    RR_BASE
#define MM_TIMER_BASE    MM_BASE
#define GMM_TIMER_BASE   MM_TIMER_BASE
#define CC_TIMER_BASE    CC_BASE
#define SMS_TIMER_BASE   SMS_BASE
#define DL_TIMER_BASE    DL_BASE
#define L1C_TIMER_BASE   L1C_BASE
#define SS_TIMER_BASE    SS_BASE
#define IP_TIMER_BASE     IP_BASE
#endif

#endif /* defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) */
#endif

#define INTERN_L1C_BASE (u16) (0x0600)   /* for L1C intern communication */
#define DUMP_BASE       (u16) (0xE000)


////////////////// RR stuff ////////////////////////////////////////////////

/*
** =========================================================================
**     MSG SUB ID Definition for RR (use in ph_prim.hc and rr_prim.hc)
**
**     +-+-+-+-+-+-+-+-+
**     |D| MOD | MsgID |
**     +-+-+-+-+-+-+-+-+
**      ^   ^      ^
**      |   |      +------- Message Identity (0 .. 15)
**      |   +-------------- SUB_BASE of RR Module which sends or receives
**      |                    this message
**      +------------------ Direction (message "from RR" or "to RR")
** =========================================================================
*/
/*
** Direction
*/
#define FROM_EL            (u16) (0x0000)
#define TO_EL              (u16) (0x0080)

/*
** RR Modules
*/
#define RRX_SUB_BASE_MASK  (u16) (0x0070)
#define NO_RR_SUB_BASE     (u16) (0x0000)
#define RRM_SUB_BASE       (u16) (0x0010)
#define RRS_SUB_BASE       (u16) (0x0020)
#define RRD_SUB_BASE       (u16) (0x0030)
#define RRT_SUB_BASE       (u16) (0x0040)
#define RRP_SUB_BASE       (u16) (0x0050)
#define RRC_SUB_BASE       (u16) (0x0060)

/* 
** MM Modules
*/
#define MMX_MSG_TYPE_MASK  0x001F
#define MMX_SUB_BASE_MASK  (u16) (0x0060)
#define MMS_SUB_BASE       (u16) (0x0000)
#define MMC_SUB_BASE       (u16) (0x0020)
#define MMP_SUB_BASE       (u16) (0x0040)


#endif /* __MSGOFS_HC__ */


