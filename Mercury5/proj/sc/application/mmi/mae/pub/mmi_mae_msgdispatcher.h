/**
 * @file mmi_mae_msgdispatcher.h
 *
 * This header file defines the enums for dispatching system messages.
 *
 * @version $Id: mmi_mae_msgdispatcher.h 1485 2009-07-30 10:17:06Z code.lin $
 */

#ifndef __MMI_MAE_MSGDISPATCHER_H__
#define __MMI_MAE_MSGDISPATCHER_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"

///< incomplete struct definition for rtk messages
struct vm_msg;

#define VM_FIRST_BASE (u16) (0x2000)

typedef enum
{
    MAE_MSG_BASE_MM		= 0x24, ///< VM_MM_BASE			(u16) (0x2400)
    MAE_MSG_BASE_RTC		= 0x26, ///< VM_RTC_BASE		(u16) (0x2600)
    MAE_MSG_BASE_GPIO	= 0x27, ///< VM_GPIO_BASE		(u16) (0x2700)
    MAE_MSG_BASE_BUS		= 0x28, ///< VM_BUS_BASE		(u16) (0x2800)
    MAE_MSG_BASE_BAT		= 0x29, ///< VM_BAT_BASE		(u16) (0x2900)
    MAE_MSG_BASE_DBG		= 0x2A, ///< VM_DBG_BASE		(u16) (0x2A00)
    MAE_MSG_BASE_IR		= 0x2B, ///< VM_IR_BASE			(u16) (0x2B00)
    MAE_MSG_BASE_KBD		= 0x2C, ///< VM_KBD_BASE		(u16) (0x2C00)
    MAE_MSG_BASE_DAT		= 0x2D, ///< VM_DAT_BASE		(u16) (0x2D00)
    MAE_MSG_BASE_OS_TIMER	= 0x2E, ///< VM_OS_TIMER_BASE	(u16) (0x2E00)
    MAE_MSG_BASE_SYS		= 0x2F, ///< VM_SYS_BASE		(u16) (0x2F00)
    MAE_MSG_BASE_IP		= 0x30, ///< VM_IP_BASE			(u16) (0x3000)
    MAE_MSG_BASE_HWL	= 0x31, ///< VM_HWL_BASE		(u16) (0x3100)
    MAE_MSG_BASE_V24		= 0x32, ///< VM_V24_BASE		(u16) (0x3200)
    MAE_MSG_BASE_USB		= 0x33, ///< VM_USB_BASE		(u16) (0x3300)
    MAE_MSG_BASE_OBX		= 0x34, ///< VM_OBX_BASE		(u16) (0x3400)
    MAE_MSG_BASE_FCM		= 0x35, ///< VM_FCM_BASE		(u16) (0x3500)
    MAE_MSG_BASE_RTK		= 0x36, ///< VM_SYS_RTK_BASE	(u16) (0x3600)
    MAE_MSG_BASE_WBT		= 0x37, ///< VM_WBT_BASE		(u16) (0x3700)
    MAE_MSG_BASE_MDL		= 0x38, ///< VM_MDL_BASE		(u16) (0x3800)
    MAE_MSG_BASE_VM_ATI	= 0x3A, ///< VM_ATI_BASE		VM_MDL_BASE + (u16) (0x0200) // 0x3A00
#ifdef __3G_RIL_MMI__
    MAE_MSG_BASE_API_ATI	= 0x4A, ///< API_ATI_BASE		CUS_RIL_BASE + (u16) (0x0180) // 0x4A00
#else
    MAE_MSG_BASE_API_ATI	= 0x3C, ///< API_ATI_BASE		VM_MDL_BASE	+ (u16) (0x0400) // 0x3C00
#endif
#if defined(__FT_AUTO_TEST__)
	MAE_MSG_BASE_AUTOTEST	= 0x3F, ///< #define VM_AUTOTEST_BASE		(u16) (0x3F00)
#endif
    MAE_MSG_BASE_MEDIA	= 0x40, ///< VM_DEVMSG_MEDIA	(u16) (VM_CUS1_BASE + 0x0000)
    MAE_MSG_BASE_ACC		= 0x41, ///< DEV_ACC_BASE		(u16) (0x4000 + 0x0100)
    MAE_MSG_BASE_DEV		= 0x43, ///< CUS_DEV_BASE		(u16) (0x4300)
    MAE_MSG_BASE_MMI		= 0x46, ///< VM_CUS3_BASE		(u16) (0x4600)
    MAE_MSG_BASE_BT		= 0x4D, ///< VM_CUS6_BASE		(u16) (0x4D00)
    MAE_MSG_BASE_MSERV       = 0x90, ///< VM_CUS7_BASE           (u16) (0x9000)
#ifdef __NCCQQ_MMI__
    MAE_MSG_BASE_QQ      = 0xD4, ///< VM_CUS67_BASE         (u16) (0xD400)
#endif // #ifdef __NCCQQ_MMI__
    //MAE_MSG_BASE_GMM       = 0x5C, ///< #define VM_GMM_BASE    (u16) (0x5C00)
    MAE_MSG_BASE_EMAIL       = 0xB7, ///< VM_CUS43_BASE         (u16) (0xB700)
    MAE_MSG_BASE_VENSDK      = 0xDC, ///< VM_VENSDK_BASE         (u16) (0xDC00)
    MAE_MSG_BASE_VENSDK1     = 0xDD, ///< VM_VENSDK1_BASE         (u16) (0xDD00)
    MAE_MSG_BASE_VENSDK2     = 0xDE, ///< VM_VENSDK2_BASE         (u16) (0xDE00)
    MAE_MSG_BASE_VENSDK3     = 0xDF, ///< VM_VENSDK3_BASE         (u16) (0xDF00)
    MAE_MSG_BASE_VENSDK4     = 0xE0, ///< VM_VENSDK4_BASE         (u16) (0xE000)
    MAE_MSG_BASE_VENSDK5     = 0xE1, ///< VM_VENSDK5_BASE         (u16) (0xE100)
    MAE_MSG_BASE_VENSDK6     = 0xE2, ///< VM_VENSDK6_BASE         (u16) (0xE200)
    MAE_MSG_BASE_VENSDK7     = 0xE3, ///< VM_VENSDK7_BASE         (u16) (0xE300)
    MAE_MSG_BASE_CB         = 0xE4, ///< VM_MRL_CB_BASE    (u16) (0xE430)
    MAE_MSG_BASE_CPHS		= 0xE4, ///< VM_MRL_CPHS_BASE  (u16) (0xE450)
    MAE_MSG_BASE_GPRS		= 0xE4, ///< VM_MRL_GPRS_BASE		(u16) (0xE470)
    MAE_MSG_BASE_CC		= 0xE4, ///< VM_MRL_CC_BASE			(u16) (0xE4C0)
    MAE_MSG_BASE_PHB		= 0xE5, ///< VM_MRL_PHB_BASE			(u16) (0xE520)
    MAE_MSG_BASE_PWON		= 0xE5, ///< VM_MRL_PWON_BASE			(u16) (0xE550)    
    MAE_MSG_BASE_RR		= 0xE5, ///< VM_MRL_RR_BASE			(u16) (0xE570)
    MAE_MSG_BASE_SEC		= 0xE5, ///< VM_MRL_SEC_BASE		(u16) (0xE5A0)
    MAE_MSG_BASE_SMS		= 0xE5, ///< VM_MRL_SMS_BASE		(u16) (0xE5C0)
    MAE_MSG_BASE_SIM		= 0xE6, ///< VM_MRL_SIM_BASE		(u16) (0xE600)
    MAE_MSG_BASE_SS		= 0xE6, ///< VM_MRL_SS_BASE			(u16) (0xE630)
    MAE_MSG_BASE_STK		= 0xE6, ///< VM_MRL_STLK_BASE		(u16) (0xE660)
    MAE_MSG_BASE_WCUS_PHB         = 0xE6, ///< VM_MRL_WCUS_PHB_BASE            (u16) (0xE6C0)
    MAE_MSG_BASE_WCUS_SMS         = 0xE6, ///< VM_MRL_WCUS_SMS_BASE            (u16) (0xE6E0)
    MAE_MSG_BASE_WCUS_CALLLOG         = 0xE7, ///< VM_MRL_WCUS_CALLLOG_BASE            (u16) (0xE700)
    MAE_MSG_BASE_RTSP     = 0xE8, ///< VM_RTSP_BASE         (u16) (0xE800)
    MAE_MSG_BASE_SM          = 0xBE, ///< #define VM_SM_BASE     (u16) (0xBE00)
    MAE_MSG_BASE_SNDCP       = 0xBF, ///< #define VM_SNDCP_BASE  (u16) (0xBF00)
    MAE_MSG_BASE_PPS         = 0xC0, ///< #define VM_PPS_BASE    (u16) (0xC000)
#ifdef __VT_3G324M__
	MAE_MSG_BASE_324M		 = 0xCF, ///< #define VM_3G324M_BASE	(u16) (0xC900)
	MAE_MSG_BASE_CM 		 = 0xB2, ///< #define VM_3G_CM_BASE    (u16) (0xB200)
#endif //__VT_3G324M__
    MAE_MSG_BASE_MMIEXT      = 0x9A, ///< #define VM_CUS14_BASE  (u16) (0x9A00)
    MAX_MAE_MSG_BASE
} MAE_MsgBase_e;

/**
 * The function prototype of system message handlers.
 */
typedef void (*PfnInterface)(IBASE *pRecipient, struct vm_msg *pMessage);

/**
 * The function prototype for hooking system messages.
 */
typedef boolean (*PfnHookHandler)(IBASE *pRecipient, struct vm_msg *pMessage);

/**
 * This structure stores the message id and its corresponding handler. It can be used to
 * construct a table for handling messages of a specific group.
 */
typedef struct
{
	u32 nMsgId; ///< message id
	PfnInterface pfnHandler; ///< interface function
} MAE_MsgHandler_t;

#endif /* __MAE_MSGDISPATCHER_H__ */
