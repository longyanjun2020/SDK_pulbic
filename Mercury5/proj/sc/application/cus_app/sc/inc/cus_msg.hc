/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 2001
*/

/****************************************************************************/
/*  File    : cus_msgofs.hc                                                 */
/*--------------------------------------------------------------------------*/
/*  Description:  Customer Message offset                                   */
/*                                                                          */
/*                                                                          */
/*  History :                                                               */
/*--------------------------------------------------------------------------*/
/*   Date   | Author     | Err  |  Modification                             */
/*----------+------------+------+-------------------------------------------*/

/*----------+------------+------+-------------------------------------------*/
/****************************************************************************/

#ifndef __CUS_MSG_HC__
#define __CUS_MSG_HC__



#include "vm_msgof.hc"



/****************************************************************************/
/*      Customer offset definition                                          */
/****************************************************************************/
/****************************************************************************/

/*** DEV task Message ***/
#define CUS_DEV_BASE         (u16) (VM_CUS2_BASE + 0x0000)  /* (u16) (0x3500) */

/*** MMI task Message ***/
#define CUS_MMI_BASE         (u16) (VM_CUS3_BASE + 0x0000)  /* (u16) (0x3A00) */
#define CUS_MML_BASE         (u16) (VM_CUS3_BASE + 0x0100)  /* (u16) (0x3B00) */
#define CUS_MMK_BASE         (u16) (VM_CUS3_BASE + 0x0200)  /* (u16) (0x3C00) */

/*** MSERV task Message ***/
#define CUS_MSERV_BASE       (u16) (VM_CUS7_BASE + 0x0000)  /* (u16) (0x3F00) */

/*** EMAIL task Message ***/
#ifdef __EMAIL_MMI__
#define CUS_EMAIL_BASE       (u16) (VM_CUS43_BASE + 0x0000)
#endif /* __EMAIL_MMI__ */

#ifdef __WAP__
#define CUS_WAP_BASE        (u16) (VM_CUS13_BASE + 0x0000)  /* (u16) (0x4900) */
#endif /* __WAP__ */

#define CUS_HTTP_BASE        (u16) (VM_CUS13_BASE + 0x0050)  /* (u16) (0x4950) */

#ifdef __NCCQQ_MMI__
#define CUS_QQ_BASE         (u16)(VM_CUS67_BASE + 0x0000)
#endif // #ifdef __NCCQQ_MMI__
/*** JAVA task Message ***/
#ifdef __JAVA__
#define CUS_JAVA_BASE        (u16) (VM_CUS5_BASE + 0x0000)  /* (u16) (0x4300) */
#elif defined(__DALVIK__)
#define CUS_JAVA_BASE        (u16) (VM_CUS5_BASE + 0x0000)  /* (u16) (0x4300) */
#endif /* __JAVA__ */

#ifdef __MAP_MMI_LBS__
#define CUS_LBS_BASE        (u16) (VM_CUS12_BASE + 0x0000)  /* (u16) (0x4800) */
#endif

#define CUS_RESMGR_BASE         (u16) (VM_CUS16_BASE + 0x0000)

#define CUS_EFAT_BASE       (u16) (VM_CUS40_BASE+0x0000)

#if defined(__USE_MRL__)
#define CUS_MRL_BASE         (u16) (VM_CUS9_BASE + 0x0000)  /* (u16) (0x5300) */
#define CUS_MRL_PHB_BASE     (u16) (CUS_MRL_BASE)
#define CUS_MRL_PHB_BASE_1   (u16) (CUS_MRL_BASE + 0x10)
#define CUS_MRL_CPHS_BASE    (u16) (CUS_MRL_BASE + 0x20)
#define CUS_MRL_CPHS_BASE_1  (u16) (CUS_MRL_BASE + 0x30)
#define CUS_MRL_PS_BASE	     (u16) (CUS_MRL_BASE + 0x40)
#define CUS_MRL_PS_BASE_1	(u16) (CUS_MRL_BASE + 0x50)
#define CUS_MRL_PS_BASE_2	(u16) (CUS_MRL_BASE + 0x60)
#define CUS_MRL_PS_BASE_3	(u16) (CUS_MRL_BASE + 0x70)
#define CUS_MRL_PS_BASE_4	(u16) (CUS_MRL_BASE + 0x80)
#define CUS_MRL_GPRS_BASE		(u16) (CUS_MRL_BASE + 0x40)
#define CUS_MRL_GPRS_BASE_1	(u16) (CUS_MRL_BASE + 0x50)
#define CUS_MRL_GPRS_BASE_2	(u16) (CUS_MRL_BASE + 0x60)
#define CUS_MRL_GPRS_BASE_3	(u16) (CUS_MRL_BASE + 0x70)
#define CUS_MRL_GPRS_BASE_4	(u16) (CUS_MRL_BASE + 0x80)
#endif

/* The constant value for "ModuleID" in the vm_msgHeader_t */
#define DUO_MODULE_1       (0)
#define DUO_MODULE_2       (1)
#define DUO_MODULE_ALL     (2)
#define DUO_MODULE_NONE    (0xFF)
#define DUO_MODULE_NUM     (2)


#if defined(__QUAD_SIM_DUAL_STANDBY__)
#define PS_MODULE_1       (0)
#define PS_MODULE_2       (1)
#define PS_MODULE_3       (2)
#define PS_MODULE_4       (3)
#define PS_MODULE_NONE    (0xFF)
#define PS_MODULE_NUM     (4)
#endif

#endif  /* __CUS_MSG_HC__ */
