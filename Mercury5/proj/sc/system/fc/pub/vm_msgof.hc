/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright MStar S.A. (c) 2007
*/

/****************************************************************************/
/*  File    : vm_msgofs.hc                                                  */
/*--------------------------------------------------------------------------*/
/*  Description:  OPEN-MMI Message offset                                   */
/*                                                                          */
/*                                                                          */
/*  History :                                                               */
/*--------------------------------------------------------------------------*/
/*   Date   | Author     | Err  |  Modification                             */
/*----------+------------+------+-------------------------------------------*/
/****************************************************************************/

#ifndef __VM_MSGOF_HC__
#define __VM_MSGOF_HC__

/* WARNING: In mae_msgdispatcher#3.h, some hard code are reference to those
 * message base definition here. Beware of changing both side if you want to
 * change some message base definition.
 */

#include "vm_types.ht"

/****************************************************************************/
/*      VM offset definition                                                */
/****************************************************************************/
/****************************************************************************/
/*
** =========================================================================
**     VM MESSAGE OFFSET DEFINITIONS
**
**     +--------+--------+
**     |                 |
**     +--------+--------+
**        ^        ^
**        |        +-------- Msg ID (0  .. 255)
**        +----------------- Base   (256.. 65535)
** =========================================================================
*/
/*** Base defined for message   VM <-> CUS ***/
#define VM_SIM_BASE         (u16) (0x2000)
#define VM_SMS_BASE         (u16) (0x2100)
#define VM_SS_BASE          (u16) (0x2200)
#define VM_CC_BASE          (u16) (0x2300)
#define VM_MM_BASE          (u16) (0x2400)
#define VM_RR_BASE          (u16) (0x2500)
#define VM_RTC_BASE         (u16) (0x2600)
#define VM_GPIO_BASE        (u16) (0x2700)
#define VM_BUS_BASE         (u16) (0x2800)
#define VM_BAT_BASE         (u16) (0x2900)
#define VM_DBG_BASE         (u16) (0x2A00)
#define VM_IR_BASE          (u16) (0x2B00)
#define VM_KBD_BASE         (u16) (0x2C00)
#define VM_DAT_BASE         (u16) (0x2D00)
#define VM_OS_TIMER_BASE    (u16) (0x2E00)
#define VM_SYS_BASE         (u16) (0x2F00)
#define VM_IP_BASE          (u16) (0x3000)
#define VM_HWL_BASE         (u16) (0x3100)
#define VM_V24_BASE         (u16) (0x3200)
#define VM_USB_BASE         (u16) (0x3300)
#define VM_OBX_BASE         (u16) (0x3400)
#define VM_FCM_BASE         (u16) (0x3500)
#define VM_SYS_RTK_BASE     (u16) (0x3600)
#define VM_WBT_BASE         (u16) (0x3700)
#define VM_MDL_BASE         (u16) (0x3800)
#define CUS_MMT_BASE        VM_MDL_BASE                  //0x3800
#define VM_ATI_BASE         VM_MDL_BASE + (u16) (0x0200) //0x3A00
#define API_ATI_BASE        VM_MDL_BASE + (u16) (0x0400) //0x3C00
#ifdef __LOWER_LAYER_RESET__
#define VM_CE_BASE          VM_MDL_BASE + (u16) (0x0500) //0x3D00
#endif
#define VM_PM_BASE          VM_MDL_BASE + (u16) (0x0600) //0x3E00
#define VM_CALLBACK_TIMER_BASE (u16) (0x3EE0)
#define VM_CALLBACK_TIMER_END (u16) (0x3F00)



/*** Base defined for message   CUS <-> CUS ***/
#define VM_CUS_BASE         (u16) (0x4000)                     // 0x4000
#define VM_CUS_BASE2        (u16) (VM_CUS_BASE+0x4100)         // 0x8100

#define VM_CUS1_BASE        (u16) (VM_CUS_BASE+0x0000)
#define VM_CUS2_BASE        (u16) (VM_CUS_BASE+0x0300)
#define VM_CUS3_BASE        (u16) (VM_CUS_BASE+0x0600)
#define VM_CUS4_BASE        (u16) (VM_CUS_BASE+0x0900)
#define VM_CUS5_BASE        (u16) (VM_CUS_BASE+0x0B00)
#define VM_CUS6_BASE        (u16) (VM_CUS_BASE+0x0D00)
#define VM_CUS6_BASE_END    (u16) (VM_CUS_BASE+0x0DFF)
#define VM_UNUSE_START      (u16) (VM_CUS_BASE+0x0F00)
#define VM_UNUSE_END        (u16) (VM_CUS_BASE+0x0FFF)         // 0x40FFF

/* WARNING: (VM_CUS_BASE+0x1000) to VM_CUS_BASE+0x1000) are reserved
 * for system task in msgofs.hc. Do not overlap this section.
 */

#define VM_CUS7_BASE        (u16) (VM_CUS_BASE2+0x0F00)         // 0x9000
#define VM_CUS8_BASE        (u16) (VM_CUS_BASE2+0x1100)
#define VM_CUS9_BASE        (u16) (VM_CUS_BASE2+0x1300)
#define VM_CUS10_BASE       (u16) (VM_CUS_BASE2+0x1500)
#define VM_CUS11_BASE       (u16) (VM_CUS_BASE2+0x1600)
#define VM_CUS12_BASE       (u16) (VM_CUS_BASE2+0x1700)
#define VM_CUS13_BASE       (u16) (VM_CUS_BASE2+0x1800)
#define VM_CUS14_BASE       (u16) (VM_CUS_BASE2+0x1900)
#define VM_CUS15_BASE       (u16) (VM_CUS_BASE2+0x1A00)
#define VM_CUS16_BASE       (u16) (VM_CUS_BASE2+0x1B00)
#define VM_CUS17_BASE       (u16) (VM_CUS_BASE2+0x1C00)
#define VM_CUS18_BASE       (u16) (VM_CUS_BASE2+0x1D00)
#define VM_CUS19_BASE       (u16) (VM_CUS_BASE2+0x1E00)
#define VM_CUS20_BASE       (u16) (VM_CUS_BASE2+0x1F00)         // 0xA000
#define VM_CUS21_BASE       (u16) (VM_CUS_BASE2+0x2000)
#define VM_CUS22_BASE       (u16) (VM_CUS_BASE2+0x2100)
#define VM_CUS23_BASE       (u16) (VM_CUS_BASE2+0x2200)
#define VM_CUS24_BASE       (u16) (VM_CUS_BASE2+0x2300)
#define VM_CUS25_BASE       (u16) (VM_CUS_BASE2+0x2400)
#define VM_CUS26_BASE       (u16) (VM_CUS_BASE2+0x2500)
#define VM_CUS27_BASE       (u16) (VM_CUS_BASE2+0x2600)
#define VM_CUS28_BASE       (u16) (VM_CUS_BASE2+0x2700)
#define VM_CUS29_BASE       (u16) (VM_CUS_BASE2+0x2800)
#define VM_CUS30_BASE       (u16) (VM_CUS_BASE2+0x2900)
#define VM_CUS31_BASE       (u16) (VM_CUS_BASE2+0x2A00)
#define VM_CUS32_BASE       (u16) (VM_CUS_BASE2+0x2B00)
#define VM_CUS33_BASE       (u16) (VM_CUS_BASE2+0x2C00)
#define VM_CUS34_BASE       (u16) (VM_CUS_BASE2+0x2D00)
#define VM_CUS35_BASE       (u16) (VM_CUS_BASE2+0x2E00)
#define VM_CUS36_BASE       (u16) (VM_CUS_BASE2+0x2F00)         // 0xB000
#if defined(__3G__)
#define VM_3G_IP_BASE       (u16) (VM_CUS_BASE2+0x3000)
#define VM_3G_CM_BASE      (u16) (VM_CUS_BASE2+0x3100)
#define VM_3G_MUX_BASE     (u16) (VM_CUS_BASE2+0x3200)
#else //__3G__
#define VM_CUS37_BASE       (u16) (VM_CUS_BASE2+0x3000)
#define VM_CUS38_BASE       (u16) (VM_CUS_BASE2+0x3100)
#define VM_CUS39_BASE       (u16) (VM_CUS_BASE2+0x3200)
#endif  //__3G__
#define VM_CUS40_BASE       (u16) (VM_CUS_BASE2+0x3300)
#define VM_CUS41_BASE       (u16) (VM_CUS_BASE2+0x3400)
#define VM_CUS42_BASE       (u16) (VM_CUS_BASE2+0x3500)
#define VM_CUS43_BASE       (u16) (VM_CUS_BASE2+0x3600)
#define VM_CUS44_BASE       (u16) (VM_CUS_BASE2+0x3700)
#define VM_CUS45_BASE       (u16) (VM_CUS_BASE2+0x3800)
#define VM_CUS46_BASE       (u16) (VM_CUS_BASE2+0x3900)
#define VM_CUS47_BASE       (u16) (VM_CUS_BASE2+0x3A00)

#define VM_VENSDK_TIMER_BASE (u16)(VM_CUS_BASE2+0x3C00)         // For Vendor SDK timer ID, reserve 32 timers

/*** GPRS Base defined for message   WM <-> CUS ***/
#define VM_SM_BASE          (u16) (VM_CUS_BASE2+0x3D00)         // 0xBE00
#define VM_SNDCP_BASE       (u16) (VM_CUS_BASE2+0x3E00)         // 0xBF00
#define VM_PPS_BASE         (u16) (VM_CUS_BASE2+0x3F00)         // 0xC000

#define VM_CUS48_BASE       (u16) (VM_CUS_BASE2+0x4000)
#define VM_CUS49_BASE       (u16) (VM_CUS_BASE2+0x4100)
#define VM_CUS50_BASE       (u16) (VM_CUS_BASE2+0x4200)
#if defined(__3G__)
#define VM_3G_CL_BASE       (u16) (VM_CUS_BASE2+0x4300)
#define VM_3G_MDLUT_BASE   (u16) (VM_CUS_BASE2+0x4400)
#define VM_3G_PPP_BASE     (u16) (VM_CUS_BASE2+0x4500)
#else //#if defined(__3G__)
#define VM_CUS51_BASE       (u16) (VM_CUS_BASE2+0x4300)
#define VM_CUS52_BASE       (u16) (VM_CUS_BASE2+0x4400)
#define VM_CUS53_BASE       (u16) (VM_CUS_BASE2+0x4500)
#endif //#if defined(__3G__)
#define VM_CUS54_BASE       (u16) (VM_CUS_BASE2+0x4600)
#define VM_CUS55_BASE       (u16) (VM_CUS_BASE2+0x4700)
#define VM_CUS56_BASE       (u16) (VM_CUS_BASE2+0x4800)
#define VM_CUS57_BASE       (u16) (VM_CUS_BASE2+0x4900)
#define VM_CUS58_BASE       (u16) (VM_CUS_BASE2+0x4A00)
#define VM_CUS59_BASE       (u16) (VM_CUS_BASE2+0x4B00)
#define VM_CUS60_BASE       (u16) (VM_CUS_BASE2+0x4C00)
#define VM_CUS61_BASE       (u16) (VM_CUS_BASE2+0x4D00)
#define VM_3G324M_BASE      (u16) (VM_CUS_BASE2+0x4E00)
#define VM_CUS63_BASE       (u16) (VM_CUS_BASE2+0x4F00)         // 0xD000
#define VM_CUS64_BASE       (u16) (VM_CUS_BASE2+0x5000)
#define VM_CUS65_BASE       (u16) (VM_CUS_BASE2+0x5100)
#define VM_CUS66_BASE       (u16) (VM_CUS_BASE2+0x5200)
#define VM_CUS67_BASE       (u16) (VM_CUS_BASE2+0x5300)         // 0xD400
#define VM_CUS68_BASE       (u16) (VM_CUS_BASE2+0x5400)         // 0xD500
#define VM_CUS69_BASE       (u16) (VM_CUS_BASE2+0x5500)         // 0xD600, added for GSS/G3D
#define VM_CUS70_BASE       (u16) (VM_CUS_BASE2+0x5600)
#define VM_CUS71_BASE       (u16) (VM_CUS_BASE2+0x5700)
#define VM_CUS72_BASE       (u16) (VM_CUS_BASE2+0x5800)
#define VM_CUS73_BASE       (u16) (VM_CUS_BASE2+0x5900)
#define VM_CUS74_BASE       (u16) (VM_CUS_BASE2+0x5A00)

#if defined(__FT_AUTO_TEST__)
#define VM_AUTOTEST_BASE    (u16) (0x3F00)
#endif

#define VM_VENSDK_BASE      (u16) (VM_CUS_BASE2+0x5B00)         // 0xDC00 For Vendor SDK
#define VM_VENSDK1_BASE     (u16) (VM_CUS_BASE2+0x5C00)         // 0xDD00 For Vendor SDK
#define VM_VENSDK2_BASE     (u16) (VM_CUS_BASE2+0x5D00)         // 0xDE00 For Vendor SDK
#define VM_VENSDK3_BASE     (u16) (VM_CUS_BASE2+0x5E00)         // 0xDF00 For Vendor SDK
#define VM_VENSDK4_BASE     (u16) (VM_CUS_BASE2+0x5F00)         // 0xE000 For Vendor SDK
#define VM_VENSDK5_BASE     (u16) (VM_CUS_BASE2+0x6000)         // 0xE100 For Vendor SDK
#define VM_VENSDK6_BASE     (u16) (VM_CUS_BASE2+0x6100)         // 0xE200 For Vendor SDK
#define VM_VENSDK7_BASE     (u16) (VM_CUS_BASE2+0x6200)         // 0xE300 For Vendor SDK

#define VM_RIL_BASE         (u16) (VM_CUS_BASE2+0x6300)         // 0xE400
#define VM_CUS79_BASE       (u16) (VM_CUS_BASE2+0x6700)         // 0xE800 For Vendor SDK
#define VM_RTSP_BASE       VM_CUS79_BASE
#define VM_LLC_BASE             (u16)  (VM_CUS_BASE2+0x6800)        //  for LLC to VML

/* Warning: Customer base cannot exceed VM_LAST_BASE value
 * Warning: VM_LAST_BASE must be increased if add more and more task
 * Warning : 0xB100 has been registerd by VM_MDL_TIMER_BASE, if new task
             msg base exceed 0xB100, the msg id would overlape eahc other
 */
#define VM_LAST_BASE        (u16) (VM_CUS_BASE2+0x6900)         // 0xEA00




#ifdef __MSTAR_DUAL_SIM__

#if defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && (defined(__MSTAR_DUAL_SIM_DUP_GLOB__) || defined(__TRACE_C__)) && !defined(__SDK_SIMULATION__)

	#ifdef __TRACE_C__
	  	#define EXT_VMMSGOFS
		#ifdef __EXTRA_MDL_TASK__
	  	#define INIT_VMMSGOFS(X,Y,Z) ={X,Y,Z}
		#else
	  	#define INIT_VMMSGOFS(X,Y) ={X,Y}
		#endif
	#else
	  	#define EXT_VMMSGOFS extern
		#ifdef __EXTRA_MDL_TASK__
	  	#define INIT_VMMSGOFS(X,Y,Z)
		#else
	  	#define INIT_VMMSGOFS(X,Y)
		#endif
	#endif

	#ifdef __EXTRA_MDL_TASK__
	EXT_VMMSGOFS const u16 MdlTimerBase[MS_NUM_OF_MODULES]  INIT_VMMSGOFS(VM_MDL_BASE ,0xDA00, 0xDC00);
	EXT_VMMSGOFS const u16 AtiTimerBase[MS_NUM_OF_MODULES]  INIT_VMMSGOFS(VM_ATI_BASE ,0xDB00, 0xDD00);
	#else
	EXT_VMMSGOFS const u16 MdlTimerBase[MS_NUM_OF_MODULES]  INIT_VMMSGOFS(VM_MDL_BASE ,0xDA00);
	EXT_VMMSGOFS const u16 AtiTimerBase[MS_NUM_OF_MODULES]  INIT_VMMSGOFS(VM_ATI_BASE ,0xDB00);
	#endif

	#define VM_MDL_TIMER_BASE MdlTimerBase[Rtk_CurrentModule]
	#define VM_ATI_TIMER_BASE AtiTimerBase[Rtk_CurrentModule]

#else

	#ifdef __DUPLICATE_TASK__
	#define VM_MDL_TIMER_BASE   (u16) (0xDA00)
	#define VM_ATI_TIMER_BASE   (u16) (0xDB00)
	#else
	#define VM_MDL_TIMER_BASE   VM_MDL_BASE
	#define VM_ATI_TIMER_BASE   VM_ATI_BASE
	#endif

#endif  /* end of #if defined(__MSTAR_DUAL_SIM_REDUCE_CODE__) && (defined(__MSTAR_DUAL_SIM_DUP_GLOB__) */

#endif  /* end if __MSTAR_DUAL_SIM__ */

#define VM_UNSUBSCRIB_BASE  (u16) (0xFFFF)


#endif  /* __VM_MSGOF_HC__ */
