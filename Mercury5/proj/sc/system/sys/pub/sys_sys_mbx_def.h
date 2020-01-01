
/****************************************************************************/
/*  File    : sys_sys_mbx_def.h                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : define mailbox number                                         */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Historical :                                                            */
/****************************************************************************/

#ifndef __SYS_SYS_MBX_DEF_H__
#define __SYS_SYS_MBX_DEF_H__




#include "sys_rtk_config.h"
#include "vm_osdef.hc"
#include "vm_types.ht"  /* __MSTAR_DUAL_SIM_REDUCE_CODE__ */



/****************************************************************************/
/*  OS tasks and Mailbox Definition                                         */
/****************************************************************************/
/****************************************************************************/

#define VM_OS_MAX_TASK      10

/*** Customer task identifiers ***/
#define VM_OS_CUST_TASK1    1
#define VM_OS_CUST_TASK2    2
#define VM_OS_CUST_TASK3    3
#define VM_OS_CUST_TASK4    4
#define VM_OS_CUST_TASK5    5
#define VM_OS_CUST_TASK6    6
#define VM_OS_CUST_TASK7    7
#define VM_OS_CUST_TASK8    8
#define VM_OS_CUST_TASK9    9
#define VM_OS_CUST_TASK10   10
#define VM_OS_CUST_TASK11   11
#define VM_OS_CUST_TASK12   12
#define VM_OS_CUST_TASK13   13
#define VM_OS_CUST_TASK14   14
#define VM_OS_CUST_TASK42   42
#define VM_OS_CUST_TASK54   54





/*
 ** =========================================================================
 **     MAILBOXES DEFINITION
 ** =========================================================================
 */

/* !!!!!!!!!!! DO NOT CHANGE ANYTHING STARTING FROM HERE !!!!!!!!!!!! */

/* No matter __MSTAR_DUAL_SIM__ is defined or not, we always define the
 * following Mailbox ID(10~18, 40~49). The main reason is that dual-SIM L1C
 * refer to these ID's too many times. As long as we are using dual-SIM L1C
 * (in both dual-SIM and mono-SIM case), it does not make sense to wrap all
 * of them in L1C.
 */


/*** MailBox Identifiers ***/
#define VM_MBX_HWL          0 /* Core MailBox Identifiers */
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM1         1
#else
#define VM_MBX_SIM          1
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_CC1          2
#define VM_MBX_SS1          3
#define VM_MBX_SMS1         4
#define VM_MBX_MM1          5
#define VM_MBX_GMM1         VM_MBX_MM1
#define VM_MBX_RR1          6
#define VM_MBX_SPV1         7
#define VM_MBX_DATA         8

#define VM_MBX_STORAGE      9
#define VM_MBX_IR           9
#define VM_MBX_DIP			9 //check

#define VM_MBX_CC2          10
#define VM_MBX_SS2          11
#define VM_MBX_SMS2         12
#define VM_MBX_MM2          13
#define VM_MBX_GMM2         VM_MBX_MM2
#define VM_MBX_RR2          14
#define VM_MBX_SPV2         15
#define VM_MBX_SM2          16
#define VM_MBX_SNDCP2       17
#define VM_MBX_MDL2         18
#define VM_MBX_IP1          19
#define VM_MBX_BAT          20
#define VM_MBX_LAPD1        21
#define VM_MBX_MSR1         22
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM1_HAND    23
#else
#define VM_MBX_SIM_HAND     23
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_OBX          24
#define VM_MBX_MDL1         25
#define VM_MBX_SM1          26
#define VM_MBX_PPS1         27
#define VM_MBX_SNDCP1       28
#define VM_MBX_LLC1         29
#define VM_MBX_RLD1         30
#define VM_MBX_RLU1         31
#define VM_MBX_PM           32
#define VM_MBX_V24          33
#define VM_MBX_HAC          34
#define VM_MBX_ABB          35
#define VM_MBX_TIMER        36
#define VM_MBX_DSR          37

#define VM_MBX_MDL_EXT      38

#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM2         40
#define VM_MBX_SIM2_HAND    41
#endif //__MSTAR_DUAL_SIM_SIM_DUO__

#define VM_MBX_PPS2         42
#define VM_MBX_IP2          43
#define VM_MBX_CE           44 			// __LOWER_LAYER_RESET__
#define VM_MBX_MSR2         45
#define VM_MBX_LLC2         46
#define VM_MBX_RLD2         47
#define VM_MBX_RLU2         48
#define VM_MBX_LAPD2        49




#define HWL_MBX         VM_MBX_HWL        /*  0 */
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM1_MBX        VM_MBX_SIM1        /*  1 */
#else
#define SIM_MBX         VM_MBX_SIM        /*  1 */
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define CC1_MBX         VM_MBX_CC1        /*  2 */
#define SS1_MBX         VM_MBX_SS1        /*  3 */
#define SMS1_MBX        VM_MBX_SMS1       /*  4 */
#define MM1_MBX         VM_MBX_MM1        /*  5 */
#define GMM1_MBX        MM1_MBX
#define RR1_MBX         VM_MBX_RR1        /*  6 */
#define SPV1_MBX        VM_MBX_SPV1       /*  7 */
#define L1C1_MBX        SPV1_MBX
#define DATA_MBX        VM_MBX_DATA       /*  8 */
#define IR_MBX          VM_MBX_IR         /*  9 */
#define STO_MBX         VM_MBX_STORAGE    /*  9 */
#define CC2_MBX         VM_MBX_CC2        /* 10 */
#define SS2_MBX         VM_MBX_SS2        /* 11 */
#define SMS2_MBX        VM_MBX_SMS2       /* 12 */
#define MM2_MBX         VM_MBX_MM2        /* 13 */
#define GMM2_MBX        MM2_MBX
#define RR2_MBX         VM_MBX_RR2        /* 14 */
#define SPV2_MBX        VM_MBX_SPV2       /* 15 */
#define L1C2_MBX        SPV2_MBX
#define SM2_MBX         VM_MBX_SM2        /* 16 */
#define SNDCP2_MBX      VM_MBX_SNDCP2     /* 17 */
#define MDL2_MBX        VM_MBX_MDL2       /* 18 */
#define IP1_MBX         VM_MBX_IP1        /* 19 */
#define BAT_MBX         VM_MBX_BAT        /* 20 */
#define LAPD1_MBX       VM_MBX_LAPD1      /* 21 */
#define MSR1_MBX        VM_MBX_MSR1       /* 22 */
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM1_HAND_MBX   VM_MBX_SIM1_HAND  /* 23 */
#else
#define SIM_HAND_MBX    VM_MBX_SIM_HAND   /* 23 */
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define OBX_MBX         VM_MBX_OBX        /* 24 */
#define MDL1_MBX        VM_MBX_MDL1       /* 25 */
#define SM1_MBX         VM_MBX_SM1        /* 26 */
#define PPS1_MBX        VM_MBX_PPS1       /* 27 */
#define SNDCP1_MBX      VM_MBX_SNDCP1     /* 28 */
#define LLC1_MBX        VM_MBX_LLC1       /* 29 */
#define RLD1_MBX        VM_MBX_RLD1       /* 30 */
#define RLU1_MBX        VM_MBX_RLU1       /* 31 */
#define PM_MBX          VM_MBX_PM         /* 32 */
#define V24_MBX         VM_MBX_V24        /* 33 */ // SOL : virtual mailbox used by FCM
#define HACTIM_MBX      VM_MBX_HAC        /* 34 */
#define ABB_MBX         VM_MBX_ABB        /* 35 */
#define TIMER_MBX       VM_MBX_TIMER      /* 36 */
#define DSR_MBX         VM_MBX_DSR        /* 37 */

#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM2_MBX        VM_MBX_SIM2       /* 40 */
#define SIM2_HAND_MBX   VM_MBX_SIM2_HAND  /* 41 */
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define PPS2_MBX        VM_MBX_PPS2       /* 42 */
#define IP2_MBX         VM_MBX_IP2        /* 43 */
#define CE_MBX          VM_MBX_CE         /* 44 */
#define MSR2_MBX        VM_MBX_MSR2       /* 45 */
#define LLC2_MBX        VM_MBX_LLC2       /* 46 */
#define RLD2_MBX        VM_MBX_RLD2       /* 47 */
#define RLU2_MBX        VM_MBX_RLU2       /* 48 */
#define LAPD2_MBX       VM_MBX_LAPD2      /* 49 */
#define MDL_EXT_MBX     VM_MBX_MDL_EXT    /* 50 */

//#if defined(__DIP__)
#define DIP_CTL_MBX     VM_MBX_DIP
//#endif

#define __LAST_MBX      59 /* WARNING: must be updated if mailboxes are added */




#if defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && defined(__MSTAR_DUAL_SIM_DUP_GLOB__)

/* For general cases, determine the mailbox by current module ID. */
#define VM_MBX_CC           ((Rtk_CurrentModule==0)?VM_MBX_CC1:VM_MBX_CC2)
#define VM_MBX_SS           ((Rtk_CurrentModule==0)?VM_MBX_SS1:VM_MBX_SS2)
#define VM_MBX_SMS          ((Rtk_CurrentModule==0)?VM_MBX_SMS1:VM_MBX_SMS2)
#define VM_MBX_MM           ((Rtk_CurrentModule==0)?VM_MBX_MM1:VM_MBX_MM2)
#define VM_MBX_GMM          ((Rtk_CurrentModule==0)?VM_MBX_GMM1:VM_MBX_GMM2)
#define VM_MBX_RR           ((Rtk_CurrentModule==0)?VM_MBX_RR1:VM_MBX_RR2)
#define VM_MBX_SPV          ((Rtk_CurrentModule==0)?VM_MBX_SPV1:VM_MBX_SPV2)
#if defined( __MDL_EXT__)
#define VM_MBX_MDL          ((Rtk_CurrentModule==0)?VM_MBX_MDL1:((Rtk_CurrentModule==1)?VM_MBX_MDL2:VM_MBX_MDL_EXT))
#else
#define VM_MBX_MDL          ((Rtk_CurrentModule==0)?VM_MBX_MDL1:VM_MBX_MDL2)
#endif
#define VM_MBX_SM           ((Rtk_CurrentModule==0)?VM_MBX_SM1:VM_MBX_SM2)
#define VM_MBX_SNDCP        ((Rtk_CurrentModule==0)?VM_MBX_SNDCP1:VM_MBX_SNDCP2)
#define VM_MBX_PPS          ((Rtk_CurrentModule==0)?VM_MBX_PPS1:VM_MBX_PPS1)
#if defined(__WLAN_IP_SUPPORT__)
#define VM_MBX_IP           ((Rtk_CurrentModule==2)?VM_MBX_IP2:VM_MBX_IP1)
#else
#define VM_MBX_IP            VM_MBX_IP1
#endif
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM          ((Rtk_CurrentModule==0)?VM_MBX_SIM1:VM_MBX_SIM2)
#endif //__MSTAR_DUAL_SIM_SIM_DUO__

/* For general cases, determine the mailbox by current module ID. */
#define CC_MBX          ((Rtk_CurrentModule==0)?CC1_MBX:CC2_MBX)
#define SS_MBX          ((Rtk_CurrentModule==0)?SS1_MBX:SS2_MBX)
#define SMS_MBX         ((Rtk_CurrentModule==0)?SMS1_MBX:SMS2_MBX)
#define MM_MBX          ((Rtk_CurrentModule==0)?MM1_MBX:MM2_MBX)
#define GMM_MBX         ((Rtk_CurrentModule==0)?GMM1_MBX:GMM2_MBX)
#define RR_MBX          ((Rtk_CurrentModule==0)?RR1_MBX:RR2_MBX)
#define LAPD_MBX        ((Rtk_CurrentModule==0)?LAPD1_MBX:LAPD2_MBX)
#define SPV_MBX         ((Rtk_CurrentModule==0)?SPV1_MBX:SPV2_MBX)
#define L1C_MBX         ((Rtk_CurrentModule==0)?L1C1_MBX:L1C2_MBX)
#define MSR_MBX         ((Rtk_CurrentModule==0)?MSR1_MBX:MSR2_MBX)
#define SM_MBX          ((Rtk_CurrentModule==0)?SM1_MBX:SM2_MBX)
#define SNDCP_MBX       ((Rtk_CurrentModule==0)?SNDCP1_MBX:SNDCP2_MBX)
#define LLC_MBX         ((Rtk_CurrentModule==0)?LLC1_MBX:LLC2_MBX)
#define RLD_MBX         ((Rtk_CurrentModule==0)?RLD1_MBX:RLD2_MBX)
#define RLU_MBX         ((Rtk_CurrentModule==0)?RLU1_MBX:RLU2_MBX)
#if defined(__MDL_EXT__)
#define MDL_MBX         ((Rtk_CurrentModule==0)?MDL1_MBX:((Rtk_CurrentModule==1)?MDL2_MBX:MDL_EXT_MBX))
#else
#define MDL_MBX         ((Rtk_CurrentModule==0)?MDL1_MBX:MDL2_MBX)
#endif

/*#define PPS_MBX         ((Rtk_CurrentModule==0)?PPS1_MBX:PPS2_MBX)*/
/* #define IP_MBX          ((Rtk_CurrentModule==0)?IP1_MBX:IP2_MBX)*/
#if defined(__WLAN_IP_SUPPORT__)
#ifdef  __DUPLICATE_IP_TASK__
#define IP_MBX              IP2_MBX
#else
#define IP_MBX              ((Rtk_CurrentModule==2)?IP2_MBX:IP1_MBX)
#endif
#else
#define IP_MBX              IP1_MBX
#endif

#define PPS_MBX            PPS1_MBX
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM_MBX         ((Rtk_CurrentModule==0)?SIM1_MBX:SIM2_MBX)
#define SIM_HAND_MBX    ((Rtk_CurrentModule==0)?SIM1_HAND_MBX:SIM2_HAND_MBX)
#endif //__MSTAR_DUAL_SIM_SIM_DUO__

#else //__MSTAR_DUAL_SIM_REDUCE_CODE__ && __MSTAR_DUAL_SIM_DUP_GLOB__

#ifdef __DUPLICATE_TASK__
#define VM_MBX_CC           VM_MBX_CC2
#define VM_MBX_SS           VM_MBX_SS2
#define VM_MBX_SMS          VM_MBX_SMS2
#define VM_MBX_MM           VM_MBX_MM2
#define VM_MBX_GMM          VM_MBX_GMM2
#define VM_MBX_RR           VM_MBX_RR2
#define VM_MBX_SPV          VM_MBX_SPV2
#define VM_MBX_MDL          VM_MBX_MDL2
#define VM_MBX_SM           VM_MBX_SM2
#define VM_MBX_SNDCP        VM_MBX_SNDCP2
#define VM_MBX_PPS          VM_MBX_PPS2
#define VM_MBX_IP           VM_MBX_IP2
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM          VM_MBX_SIM2
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#else
#define VM_MBX_CC           VM_MBX_CC1
#define VM_MBX_SS           VM_MBX_SS1
#define VM_MBX_SMS          VM_MBX_SMS1
#define VM_MBX_MM           VM_MBX_MM1
#define VM_MBX_GMM          VM_MBX_GMM1
#define VM_MBX_RR           VM_MBX_RR1
#define VM_MBX_SPV          VM_MBX_SPV1
#define VM_MBX_MDL          VM_MBX_MDL1
#define VM_MBX_SM           VM_MBX_SM1
#define VM_MBX_SNDCP        VM_MBX_SNDCP1
#define VM_MBX_PPS          VM_MBX_PPS1
#define VM_MBX_IP           VM_MBX_IP1
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define VM_MBX_SIM          VM_MBX_SIM1
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#endif //__DUPLICATE_TASK__

#ifdef __DUPLICATE_TASK__
#define CC_MBX          CC2_MBX
#define SS_MBX          SS2_MBX
#define SMS_MBX         SMS2_MBX
#define MM_MBX          MM2_MBX
#define GMM_MBX         GMM2_MBX
#define RR_MBX          RR2_MBX
#define LAPD_MBX        LAPD2_MBX
#define SPV_MBX         SPV2_MBX
#define L1C_MBX         L1C2_MBX
#define MSR_MBX         MSR2_MBX
#define SM_MBX          SM2_MBX
#define SNDCP_MBX       SNDCP2_MBX
#define LLC_MBX         LLC2_MBX
#define RLD_MBX         RLD2_MBX
#define RLU_MBX         RLU2_MBX
#define MDL_MBX         MDL2_MBX
#define PPS_MBX         PPS2_MBX
#define IP_MBX          IP2_MBX
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM_MBX         SIM2_MBX
#define SIM_HAND_MBX    SIM2_HAND_MBX
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#else
#define CC_MBX          CC1_MBX
#define SS_MBX          SS1_MBX
#define SMS_MBX         SMS1_MBX
#define MM_MBX          MM1_MBX
#define GMM_MBX         GMM1_MBX
#define RR_MBX          RR1_MBX
#define LAPD_MBX        LAPD1_MBX
#define SPV_MBX         SPV1_MBX
#define L1C_MBX         L1C1_MBX
#define MSR_MBX         MSR1_MBX
#define SM_MBX          SM1_MBX
#define SNDCP_MBX       SNDCP1_MBX
#define LLC_MBX         LLC1_MBX
#define RLD_MBX         RLD1_MBX
#define RLU_MBX         RLU1_MBX
#define MDL_MBX         MDL1_MBX
#define PPS_MBX         PPS1_MBX
#if defined (__WLAN_IP_SUPPORT__) && !defined(__SDK_SIMULATION__)
#ifdef  __DUPLICATE_IP_TASK__
#define IP_MBX              IP2_MBX
#else
#define IP_MBX              ((Rtk_CurrentModule==2)?IP2_MBX:IP1_MBX)
#endif
#else
#define IP_MBX          IP1_MBX
#endif

#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define SIM_MBX         SIM1_MBX
#define SIM_HAND_MBX    SIM1_HAND_MBX
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#endif

#endif //__MSTAR_DUAL_SIM_REDUCE_CODE__ && __MSTAR_DUAL_SIM_DUP_GLOB__


#if defined(__MSTAR_DUAL_SIM_REDUCE_CODE__)
/* For the initial value in variable declaration, use special mailbox since we can determine it at this time.
   Determine the real mailbox, by current module ID, before sending out the message later. */
#define DUAL_MBX_BASE        0xff00
#define DUAL_CC_MBX          DUAL_MBX_BASE
#define DUAL_SS_MBX          DUAL_MBX_BASE+1
#define DUAL_SMS_MBX         DUAL_MBX_BASE+2
#define DUAL_MM_MBX          DUAL_MBX_BASE+3
#define DUAL_GMM_MBX         DUAL_MBX_BASE+4
#define DUAL_RR_MBX          DUAL_MBX_BASE+5
#define DUAL_LAPD_MBX        DUAL_MBX_BASE+6
#define DUAL_SPV_MBX         DUAL_MBX_BASE+7
#define DUAL_L1C_MBX         DUAL_MBX_BASE+8
#define DUAL_MSR_MBX         DUAL_MBX_BASE+9
#define DUAL_SM_MBX          DUAL_MBX_BASE+10
#define DUAL_SNDCP_MBX       DUAL_MBX_BASE+11
#define DUAL_LLC_MBX         DUAL_MBX_BASE+12
#define DUAL_RLD_MBX         DUAL_MBX_BASE+13
#define DUAL_RLU_MBX         DUAL_MBX_BASE+14
#define DUAL_MDL_MBX         DUAL_MBX_BASE+15
#define DUAL_PPS_MBX         DUAL_MBX_BASE+16
#define DUAL_IP_MBX          DUAL_MBX_BASE+17
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define DUAL_SIM_MBX         DUAL_MBX_BASE+18
#define DUAL_SIM_HAND_MBX    DUAL_MBX_BASE+19
#endif //__MSTAR_DUAL_SIM_SIM_DUO__
#define DUAL_MBX_NUM    20

extern const u16 DualMbxTab[DUAL_MBX_NUM][2];
/* For Simulator build, the definition is moved to middleware\vml\inc\ase_mmt.hv. */

#else
/*
    For simulator, keep the original design.
 */
#define DUAL_CC_MBX          CC_MBX
#define DUAL_SS_MBX          SS_MBX
#define DUAL_SMS_MBX         SMS_MBX
#define DUAL_MM_MBX          MM_MBX
#define DUAL_GMM_MBX         GMM_MBX
#define DUAL_RR_MBX          RR_MBX
#define DUAL_LAPD_MBX        LAPD_MBX
#define DUAL_SPV_MBX         LAPD_MBX
#define DUAL_L1C_MBX         LAPD_MBX
#define DUAL_MSR_MBX         MSR_MBX
#define DUAL_SM_MBX          SM_MBX
#define DUAL_SNDCP_MBX       SNDCP_MBX
#define DUAL_LLC_MBX         LLC_MBX
#define DUAL_RLD_MBX         RLD_MBX
#define DUAL_RLU_MBX         RLU_MBX
#define DUAL_MDL_MBX         MDL_MBX
#define DUAL_PPS_MBX         PPS_MBX
#define DUAL_IP_MBX          IP_MBX
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#define DUAL_SIM_MBX         SIM_MBX
#define DUAL_SIM_HAND_MBX    SIM_HAND_MBX
#endif //__MSTAR_DUAL_SIM_SIM_DUO__

#endif //__MSTAR_DUAL_SIM_REDUCE_CODE__



#define DEV_MBX         CUS2_MBX


#define VM_MBX_UNSUBSCRIB   0xFFFF



#define VM_MBX_CUS1         RTK_FIRST_CUSTOMER_MAILBOXID /* previously used as BAT_MBX     Custom MailBox Identifiers */
#define VM_MBX_CUS2         (VM_MBX_CUS1+1)              /* previously used as DEV_MBX */
#define VM_MBX_CUS3         (VM_MBX_CUS1+2)              /* previously used as MMI_MBX */
#define VM_MBX_CUS4         (VM_MBX_CUS1+3)
#define VM_MBX_CUS5         (VM_MBX_CUS1+4)
#define VM_MBX_CUS6         (VM_MBX_CUS1+5)
#define VM_MBX_CUS7         (VM_MBX_CUS1+6)
#define VM_MBX_CUS8         (VM_MBX_CUS1+7)
#define VM_MBX_CUS9         (VM_MBX_CUS1+8)
#define VM_MBX_CUS10        (VM_MBX_CUS1+9)
#define VM_MBX_CUS11        (VM_MBX_CUS1+10)
#define VM_MBX_CUS12        (VM_MBX_CUS1+11)
#define VM_MBX_CUS13        (VM_MBX_CUS1+12)
#define VM_MBX_CUS14        (VM_MBX_CUS1+13)
#define VM_MBX_CUS15        (VM_MBX_CUS1+14)
#define VM_MBX_CUS16        (VM_MBX_CUS1+15)
#define VM_MBX_CUS17        (VM_MBX_CUS1+16)
#define VM_MBX_CUS18        (VM_MBX_CUS1+17)
#define VM_MBX_CUS19        (VM_MBX_CUS1+18)
#define VM_MBX_CUS20        (VM_MBX_CUS1+19)
#define VM_MBX_CUS21        (VM_MBX_CUS1+20)
#define VM_MBX_CUS22        (VM_MBX_CUS1+21)
#define VM_MBX_CUS23        (VM_MBX_CUS1+22)
#define VM_MBX_CUS24        (VM_MBX_CUS1+23)
#define VM_MBX_CUS25        (VM_MBX_CUS1+24)
#define VM_MBX_CUS26        (VM_MBX_CUS1+25)
#define VM_MBX_CUS27        (VM_MBX_CUS1+26)
#define VM_MBX_CUS28        (VM_MBX_CUS1+27)
#define VM_MBX_CUS29        (VM_MBX_CUS1+28)
#define VM_MBX_CUS30        (VM_MBX_CUS1+29)
#define VM_MBX_CUS31        (VM_MBX_CUS1+30)
#define VM_MBX_CUS32        (VM_MBX_CUS1+31)
#define VM_MBX_CUS33        (VM_MBX_CUS1+32)
#define VM_MBX_CUS34        (VM_MBX_CUS1+33)
#define VM_MBX_CUS35        (VM_MBX_CUS1+34)
#define VM_MBX_CUS36        (VM_MBX_CUS1+35)
#define VM_MBX_CUS37        (VM_MBX_CUS1+36)
#define VM_MBX_CUS38        (VM_MBX_CUS1+37)
#define VM_MBX_CUS39        (VM_MBX_CUS1+38)
#define VM_MBX_CUS40        (VM_MBX_CUS1+39)
#define VM_MBX_CUS41        (VM_MBX_CUS1+40)
#define VM_MBX_CUS42        (VM_MBX_CUS1+41)
#define VM_MBX_CUS43        (VM_MBX_CUS1+42)
#define VM_MBX_CUS44        (VM_MBX_CUS1+43)
#define VM_MBX_CUS45        (VM_MBX_CUS1+44)
#define VM_MBX_CUS46        (VM_MBX_CUS1+45)
#define VM_MBX_CUS47        (VM_MBX_CUS1+46)
#define VM_MBX_CUS48        (VM_MBX_CUS1+47)
#define VM_MBX_CUS49        (VM_MBX_CUS1+48)
#define VM_MBX_CUS50        (VM_MBX_CUS1+49)
#define VM_MBX_CUS51        (VM_MBX_CUS1+50)
#define VM_MBX_CUS52        (VM_MBX_CUS1+51)
#define VM_MBX_CUS53        (VM_MBX_CUS1+52)
#define VM_MBX_CUS54        (VM_MBX_CUS1+53)
#define VM_MBX_CUS55        (VM_MBX_CUS1+54)
#define VM_MBX_CUS56        (VM_MBX_CUS1+55)
#define VM_MBX_CUS57        (VM_MBX_CUS1+56)
#define VM_MBX_CUS58        (VM_MBX_CUS1+57)
#define VM_MBX_CUS59        (VM_MBX_CUS1+58)
#define VM_MBX_CUS60        (VM_MBX_CUS1+59)
#define VM_MBX_CUS61        (VM_MBX_CUS1+60)
#define VM_MBX_CUS62        (VM_MBX_CUS1+61)
#define VM_MBX_CUS63        (VM_MBX_CUS1+62)
#define VM_MBX_CUS64        (VM_MBX_CUS1+63)
#define VM_MBX_CUS65        (VM_MBX_CUS1+64)
#define VM_MBX_CUS66        (VM_MBX_CUS1+65)
#define VM_MBX_CUS67        (VM_MBX_CUS1+66)
#define VM_MBX_CUS68        (VM_MBX_CUS1+67)
#define VM_MBX_CUS69        (VM_MBX_CUS1+68)
#define VM_MBX_CUS70        (VM_MBX_CUS1+69)
#define VM_MBX_CUS71        (VM_MBX_CUS1+70)
#define VM_MBX_CUS72        (VM_MBX_CUS1+71)
#define VM_MBX_CUS73        (VM_MBX_CUS1+72)
#define VM_MBX_CUS74        (VM_MBX_CUS1+73)
#define VM_MBX_CUS75        (VM_MBX_CUS1+74)
#define VM_MBX_CUS76        (VM_MBX_CUS1+75)
#define VM_MBX_CUS77        (VM_MBX_CUS1+76)
#define VM_MBX_CUS78        (VM_MBX_CUS1+77)
#define VM_MBX_CUS79        (VM_MBX_CUS1+78)
#define VM_MBX_CUS80        (VM_MBX_CUS1+79)
#define VM_MBX_CUS81        (VM_MBX_CUS1+80)
#define VM_MBX_CUS82        (VM_MBX_CUS1+81)
#define VM_MBX_CUS83        (VM_MBX_CUS1+82)
#define VM_MBX_CUS84        (VM_MBX_CUS1+83)
#define VM_MBX_CUS85        (VM_MBX_CUS1+84)
#define VM_MBX_CUS86        (VM_MBX_CUS1+85)
#define VM_MBX_CUS87        (VM_MBX_CUS1+86)
#define VM_MBX_CUS88        (VM_MBX_CUS1+87)
#define VM_MBX_CUS89        (VM_MBX_CUS1+88)
#define VM_MBX_CUS90        (VM_MBX_CUS1+89)
#define VM_MBX_CUS91        (VM_MBX_CUS1+90)
#define VM_MBX_CUS92        (VM_MBX_CUS1+91)
#define VM_MBX_CUS93        (VM_MBX_CUS1+92)
#define VM_MBX_CUS94        (VM_MBX_CUS1+93)
#define VM_MBX_CUS95        (VM_MBX_CUS1+94)
#define VM_MBX_CUS96        (VM_MBX_CUS1+95)
#define VM_MBX_CUS97        (VM_MBX_CUS1+96)
#define VM_MBX_CUS98        (VM_MBX_CUS1+97)




                                          /* PB */ /* DUO */
#define CUS1_MBX        VM_MBX_CUS1       /* 40 */ /* 50  */
#define CUS2_MBX        VM_MBX_CUS2       /* 41 */ /* 51  */
#define CUS3_MBX        VM_MBX_CUS3       /* 42 */ /* 52  */
#define CUS4_MBX        VM_MBX_CUS4       /* 43 */ /* 53  */
#define CUS5_MBX        VM_MBX_CUS5       /* 44 */ /* 54  */
#define CUS6_MBX        VM_MBX_CUS6       /* 45 */ /* 55  */
#define CUS7_MBX        VM_MBX_CUS7       /* 46 */ /* 56  */
#define CUS8_MBX        VM_MBX_CUS8       /* 47 */ /* 57  */
#define CUS9_MBX        VM_MBX_CUS9       /* 48 */ /* 58  */
#define CUS10_MBX       VM_MBX_CUS10      /* 49 */ /* 59  */
#define CUS11_MBX       VM_MBX_CUS11      /* 50 */ /* 60  */
#define CUS12_MBX       VM_MBX_CUS12      /* 51 */ /* 61  */
#define CUS13_MBX       VM_MBX_CUS13      /* 52 */ /* 62  */
#define CUS14_MBX       VM_MBX_CUS14      /* 53 */ /* 63  */
#define CUS15_MBX       VM_MBX_CUS15      /* 54 */ /* 64  */
#define CUS16_MBX       VM_MBX_CUS16      /* 55 */ /* 65  */
#define CUS17_MBX       VM_MBX_CUS17      /* 56 */ /* 66  */
#define CUS18_MBX       VM_MBX_CUS18      /* 57 */ /* 67  */
#define CUS19_MBX       VM_MBX_CUS19      /* 58 */ /* 68  */
#define CUS20_MBX       VM_MBX_CUS20      /* 59 */ /* 69  */
#define CUS21_MBX       VM_MBX_CUS21      /* 60 */ /* 70  */
#define CUS22_MBX       VM_MBX_CUS22      /* 61 */ /* 71  */
#define CUS23_MBX       VM_MBX_CUS23      /* 62 */ /* 72  */
#define CUS24_MBX       VM_MBX_CUS24      /* 63 */ /* 73  */
#define CUS25_MBX       VM_MBX_CUS25      /* 64 */ /* 74  */
#define CUS26_MBX       VM_MBX_CUS26      /* 65 */ /* 75  */
#define CUS27_MBX       VM_MBX_CUS27      /* 66 */ /* 76  */
#define CUS28_MBX       VM_MBX_CUS28      /* 67 */ /* 77  */
#define CUS29_MBX       VM_MBX_CUS29      /* 68 */ /* 78  */
#define CUS30_MBX       VM_MBX_CUS30      /* 69 */ /* 79  */
#define CUS31_MBX       VM_MBX_CUS31      /* 70 */ /* 80  */
#define CUS32_MBX       VM_MBX_CUS32      /* 71 */ /* 81  */
#define CUS33_MBX       VM_MBX_CUS33      /* 72 */ /* 82  */
#define CUS34_MBX       VM_MBX_CUS34      /* 73 */ /* 83  */
#define CUS35_MBX       VM_MBX_CUS35      /* 74 */ /* 84  */
#define CUS36_MBX       VM_MBX_CUS36      /* 75 */ /* 85  */
#define CUS37_MBX       VM_MBX_CUS37      /* 76 */ /* 86  */
#define CUS38_MBX       VM_MBX_CUS38      /* 77 */ /* 87  */
#define CUS39_MBX       VM_MBX_CUS39      /* 78 */ /* 88  */
#define CUS40_MBX       VM_MBX_CUS40      /* 79 */ /* 89  */
#define CUS41_MBX       VM_MBX_CUS41      /* 80 */ /* 90  */
#define CUS42_MBX       VM_MBX_CUS42      /* 81 */ /* 91  */
#define CUS43_MBX       VM_MBX_CUS43      /* 82 */ /* 92  */
#define CUS44_MBX       VM_MBX_CUS44      /* 83 */ /* 93  */
#define CUS45_MBX       VM_MBX_CUS45      /* 84 */ /* 94  */
#define CUS46_MBX       VM_MBX_CUS46      /* 85 */ /* 95  */
#define CUS47_MBX       VM_MBX_CUS47      /* 86 */ /* 96  */
#define CUS48_MBX       VM_MBX_CUS48      /* 87 */ /* 97  */
#define CUS49_MBX       VM_MBX_CUS49      /* 88 */ /* 98  */
#define CUS50_MBX       VM_MBX_CUS50      /* 89 */ /* 99  */
#define CUS51_MBX       VM_MBX_CUS51      /* 90 */ /* 100  */
#define CUS52_MBX       VM_MBX_CUS52      /* 91 */ /* 101  */
#define CUS53_MBX       VM_MBX_CUS53      /* 92 */ /* 102  */
#define CUS54_MBX       VM_MBX_CUS54      /* 93 */ /* 103  */
#define CUS55_MBX       VM_MBX_CUS55      /* 94 */ /* 104  */
#define CUS56_MBX       VM_MBX_CUS56      /* 95 */ /* 105  */
#define CUS57_MBX       VM_MBX_CUS57      /* 96 */ /* 106  */
#define CUS58_MBX       VM_MBX_CUS58      /* 97 */ /* 107  */
#define CUS59_MBX       VM_MBX_CUS59      /* 98 */ /* 108  */
#define CUS60_MBX       VM_MBX_CUS60      /* 99 */ /* 109  */
#define CUS61_MBX       VM_MBX_CUS61      /* 100 */ /* 110  */
#define CUS62_MBX       VM_MBX_CUS62      /* 101 */ /* 111  */
#define CUS63_MBX       VM_MBX_CUS63      /* 102 */ /* 112  */
#define CUS64_MBX       VM_MBX_CUS64      /* 103 */ /* 113  */
#define CUS65_MBX       VM_MBX_CUS65      /* 104 */ /* 114  */
#define CUS66_MBX       VM_MBX_CUS66      /* 105 */ /* 115  */
#define CUS67_MBX       VM_MBX_CUS67      /* 106 */ /* 116  */
#define CUS68_MBX       VM_MBX_CUS68      /* 107 */ /* 117  */
#define CUS69_MBX       VM_MBX_CUS69      /* 108 */ /* 118  */
#define CUS70_MBX       VM_MBX_CUS70      /* 109 */ /* 119  */
#define CUS71_MBX       VM_MBX_CUS71      /* 110 */ /* 120  */
#define CUS72_MBX       VM_MBX_CUS72      /* 111 */ /* 121  */
#define CUS73_MBX       VM_MBX_CUS73      /* 112 */ /* 122  */
#define CUS74_MBX       VM_MBX_CUS74      /* 113 */ /* 123  */
#define CUS75_MBX       VM_MBX_CUS75      /* 114 */ /* 124  */
#define CUS76_MBX       VM_MBX_CUS76      /* 115 */ /* 125  */
#define CUS77_MBX       VM_MBX_CUS77      /* 116 */ /* 126  */
#define CUS78_MBX       VM_MBX_CUS78      /* 117 */ /* 127  */
#define CUS79_MBX       VM_MBX_CUS79      /* 118 */ /* 128  */
#define CUS80_MBX       VM_MBX_CUS80      /* 119 */ /* 129  */
#define CUS81_MBX       VM_MBX_CUS81      /* 120 */ /* 130  */
#define CUS82_MBX       VM_MBX_CUS82      /* 121 */ /* 131  */
#define CUS83_MBX       VM_MBX_CUS83      /* 122 */ /* 132  */
#define CUS84_MBX       VM_MBX_CUS84      /* 123 */ /* 133  */
#define CUS85_MBX       VM_MBX_CUS85      /* 124 */ /* 134  */
#define CUS86_MBX       VM_MBX_CUS86      /* 125 */ /* 135  */
#define CUS87_MBX       VM_MBX_CUS87      /* 126 */ /* 136  */
#define CUS88_MBX       VM_MBX_CUS88      /* 127 */ /* 137  */
#define CUS89_MBX       VM_MBX_CUS89      /* 128 */ /* 138  */
#define CUS90_MBX       VM_MBX_CUS90      /* 129 */ /* 139  */
#define CUS91_MBX       VM_MBX_CUS91      /* 130 */ /* 140  */
#define CUS92_MBX       VM_MBX_CUS92      /* 131 */ /* 141  */
#define CUS93_MBX       VM_MBX_CUS93      /* 132 */ /* 142  */
#define CUS94_MBX       VM_MBX_CUS94      /* 133 */ /* 143  */
#define CUS95_MBX       VM_MBX_CUS95      /* 134 */ /* 144  */
#define CUS96_MBX       VM_MBX_CUS96      /* 135 */ /* 145  */
#define CUS97_MBX       VM_MBX_CUS97      /* 136 */ /* 146  */
#define CUS98_MBX       VM_MBX_CUS98      /* 137 */ /* 147  */

/****************************************************************************/
/*  Customer Mailbox Definition                                             */
/****************************************************************************/


#define DEV_ACC_MBX                VM_MBX_CUS1  /* DEV_TASK is CUS1 */
#define BTUART_MBX                 VM_MBX_CUS1
#define CUS_MBX_BAT                VM_MBX_CUS1
#define CUS_MBX_MIDI               VM_MBX_CUS1
#define CUS_MBX_EMA                VM_MBX_CUS2
#define CUS_MBX_DEV                VM_MBX_CUS2

#if defined(__MML_ON_VML__)
#define CUS_MBX_MMI                VM_MBX_MDL
#else
#define CUS_MBX_MMI                VM_MBX_CUS3
#define CUS_MBX_MMIEXT             VM_MBX_CUS15
#endif

#define CUS_MBX_RTSP                VM_MBX_CUS79

#define VM_MBX_MMI                 VM_MBX_CUS3
#define VM_MBX_RIL                 VM_MBX_CUS4

#if defined(__USE_MRL__)
#define CUS_MBX_RIL                VM_MBX_CUS4
#endif

#define CUS_JAVA_TASK              VM_MBX_CUS5

#ifdef __JAVA__
#define CUS_MBX_JAVA               VM_MBX_CUS5
#endif /* __JAVA__ */


#ifdef __SDK_SIMULATION__  /* Main task for Aplix solution */
#define JAP_TASK_MBX_MAIN          VM_MBX_CUS5
#else
#define JAP_TASK_MBX_KVE           VM_MBX_CUS5
#endif

#if defined(__BLUETOOTH_DRV__)||defined(__MMI_BT__)
#define CUS_MBX_BT                 VM_MBX_CUS6
#endif /* __BLUETOOTH__ */

#define CUS_MBX_GTR                VM_MBX_CUS6

#define CUS_MBX_MSERV              VM_MBX_CUS7

#define CUS_MBX_VOC                VM_MBX_CUS8
#define CUS_MBX_FMR                VM_MBX_CUS8

#define CUS_MBX_DSR                VM_MBX_CUS9
#define CUS_MBX_MTGS               VM_MBX_CUS9 //stack 30
#define CUS_MBX_GPD                VM_MBX_CUS10
#define CUS_MBX_VFS                VM_MBX_CUS11

#define CUS_MBX_LBS                VM_MBX_CUS12

#ifdef __SDK_SIMULATION__
#define JAP_TASK_MBX_KVE           VM_MBX_CUS12
#else
#define JAP_TASK_MBX_MAIN          VM_MBX_CUS12
#endif

#define CUS_MBX_WAP                VM_MBX_CUS13

#ifdef __NCCQQ_MMI__
#define CUS_MBX_QQ                  VM_MBX_CUS67
#endif // #ifdef __NCCQQ_MMI__


#define CUS_MBX_GRM                VM_MBX_CUS16

#define CUS_MBX_FILEMGR            VM_MBX_CUS17
#define CUS_MBX_HOPPER             VM_MBX_CUS58

#ifdef __EMA_ENHANCEMENT__
#define CUS_MBX_EFS                VM_MBX_CUS18
#else
#define CUS_MBX_EFS                CUS_MBX_EMA
#endif

#ifdef __VFS_TEST_CASE__
#define CUS_MBX_FMGRTEST           VM_MBX_CUS19
#endif

#define CUS_MBX_TST                VM_MBX_CUS20

#define MDLAUD_READDATA_MBX       VM_MBX_CUS21
#define MDLAUD_MAP_MBX            VM_MBX_CUS22
#define MDLAUD_PLAYCTL_MBX        VM_MBX_CUS23
//#define MDLAUD_MAR_MBX            VM_MBX_CUS24
//#define MDLAUD_WRITEDATA_MBX      VM_MBX_CUS25
#define MDLAUD_GETINFO_MBX        VM_MBX_CUS45
#define MDLAUD_MIDCONV_MBX        VM_MBX_CUS46 //use getinfo for test emporarily

#define CUS_MBX_MDWCOMM	VM_MBX_CUS50

#define CUS_MBX_AVP               VM_MBX_CUS35   /* avp video player*/

#define CUS_MBX_EFAT              VM_MBX_CUS40   /* EFAT*/
#define CUS_MBX_CUSIDLE           VM_MBX_CUS54   /* Custom Idle*/

#define CUS_MBX_GPD2              VM_MBX_CUS60

#if defined(__WLAN__)
#define CUS_MBX_WIFI           	  VM_MBX_CUS37
#define CUS_MBX_WIFI2             VM_MBX_CUS38
#define CUS_MBX_SUPPLICANT        VM_MBX_CUS39
#endif

#if defined(__3G__)
#define CUS_MBX_3G_IP             VM_MBX_CUS75
#define CUS_MBX_3G_CM             VM_MBX_CUS76
#define CUS_MBX_3G_MUX            VM_MBX_CUS77
#define CUS_MBX_3G_CL             VM_MBX_CUS51
#define CUS_MBX_3G_MDLUT          VM_MBX_CUS52
#define CUS_MBX_3G_PPP            VM_MBX_CUS78
#endif  //#ifdef __3G__

#define CUS_MBX_MTMGR              VM_MBX_CUS59
#define CUS_MBX_60                 VM_MBX_CUS60
#define CUS_MBX_61                 VM_MBX_CUS61
#define CUS_MBX_VT                 VM_MBX_CUS62
#define CUS_MBX_63                 VM_MBX_CUS63
#define CUS_MBX_USB_MSG            VM_MBX_CUS64
#define CUS_MBX_65                 VM_MBX_CUS65
#define CUS_MBX_66                 VM_MBX_CUS66
#define CUS_MBX_67                 VM_MBX_CUS67
#define CUS_MBX_68                 VM_MBX_CUS68
#define CUS_MBX_GSS                VM_MBX_CUS69
#define CUS_MBX_EFAT2              VM_MBX_CUS70

#ifdef __RFID__
#define RFID_DRV_MBX		VM_MBX_CUS53
#define RFID_MDL_MBX		VM_MBX_CUS56
#endif	//__RFID__

#if defined(__GPS_DUALSTAR_DRV__)
#define GPS_COMM_MBX               VM_MBX_CUS71
#define GPS_HOST_MBX               VM_MBX_CUS72
#define GPS_MDL_MBX                VM_MBX_CUS73
#else
#define CUS_MBX_71                 VM_MBX_CUS71
#define CUS_MBX_72                 VM_MBX_CUS72
#define CUS_MBX_73                 VM_MBX_CUS73
#endif

#define CUS_MBX_74                 VM_MBX_CUS74
#define CUS_MBX_75                 VM_MBX_CUS75
#define CUS_MBX_76                 VM_MBX_CUS76
#define CUS_MBX_77                 VM_MBX_CUS77
#define CUS_MBX_78                 VM_MBX_CUS78


#endif /* __SYS_SYS_MBX_DEF_H__ */
