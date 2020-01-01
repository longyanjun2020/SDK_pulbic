/**
* @file PlatformDefines.h
*
* This header file defines the definitions of platform dependent
* types and macros
*/

#ifndef __PLATFORMDEFINES_H__
#define __PLATFORMDEFINES_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
//#define RES_MGR_STANDALONE_DEBUG
//#define RES_MGR_STANDALONE_DEBUG__TEST_INVALID_CASES

#if defined(RES_MGR_STANDALONE_DEBUG)

#include "string.h"
#include "assert.h"
#include "memory.h"
#include "stdlib.h"
#include "stdio.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#else ////#if defined(RES_MGR_STANDALONE_DEBUG)

#include "vm_types.ht"
#include "vm_audio_api.h"
#include "string.h"
#include "cus_os.hc"

#if defined(__SDK_SIMULATION__)
#include "assert.h"
#endif
#include "sys_vm_dbg.ho"
#include "sys_rtk_vmrtkho.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
#endif //#if defined(RES_MGR_STANDALONE_DEBUG)

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#if defined(RES_MGR_STANDALONE_DEBUG)

#define GRM_MALLOC(_X_)                     calloc(1, _X_)
#define GRM_MFREE(_X_)                      free((void*)_X_)
#define GRM_MEMSET                          memset
#define GRM_MEMCPY                          memcpy
#define GRM_MEMCMP                          memcmp
#define GRM_MEMMOVE                         memmove
#define GRM_MS_OK                           0
#define GRM_SENDMSG(_X_, _Y_)
#define GRM_SENDMSG_THD(_X_, _Y_)           GRM_MS_OK
#define GRM_MBOX_STATUS(_W_, _X_, _Y_, _Z_)
#define FALSE                               0
#define TRUE                                1

typedef unsigned long int                   Primitive; /* 32 bits */
typedef unsigned _int8                      u8;
typedef unsigned _int16                     u16;
typedef unsigned _int32                     u32;
typedef unsigned _int64                     u64;
typedef          char                       ascii;
typedef _int8                               s8;
typedef _int16                              s16;
typedef _int32                              s32;
typedef _int64                              s64;
typedef unsigned char                       bool;
#define _GRM_IMG
#define _GRM                                0
#define _GRM_UT                             0
#define GRM_SYNC_LOCK_INIT
#define GRM_SYNC_LOCK
#define GRM_SYNC_UNLOCK

#define GRM_REENTRY_LOCK_INIT
#define GRM_REENTRY_LOCK
#define GRM_REENTRY_UNLOCK

#define GRM_GSS_SYNC_LOCK_INIT
#define GRM_GSS_SYNC_LOCK
#define GRM_GSS_SYNC_UNLOCK

#define GRM_GSS_REENTRY_LOCK_INIT
#define GRM_GSS_REENTRY_LOCK
#define GRM_GSS_REENTRY_UNLOCK

#define GRM_CTRL_SYNC_LOCK_INIT
#define GRM_CTRL_SYNC_LOCK
#define GRM_CTRL_SYNC_UNLOCK

#define GRM_CTRL_REENTRY_LOCK_INIT
#define GRM_CTRL_REENTRY_LOCK
#define GRM_CTRL_REENTRY_UNLOCK

#define GRM_TASK_SYNC_LOCK_INIT
#define GRM_TASK_SYNC_LOCK
#define GRM_TASK_SYNC_UNLOCK

#define GRM_RINGBUFF_LOCK_INIT
#define GRM_RINGBUFF_SEM                    1

//#define GRM_TRACE(_level_, _format_, ...)   Win32_Trace(_level_, "[TRACE] %s (%d): " _format_, __FILE__, __LINE__, ##__VA_ARGS__)
#define GRM_TRACE(_level_, _format_, ...)   \
    Win32_Trace(_level_, _format_, ##__VA_ARGS__);   \
    printf(_format_ "\n", ##__VA_ARGS__)

#define GRM_ERROR(_level_, _format_, ...)   \
    Win32_Trace(_level_, _format_, ##__VA_ARGS__);   \
    printf(_format_ "\n", ##__VA_ARGS__)

extern void Win32_Trace(u32 level, char *strFormat, ...);

#define GRM_SLEEP(_COUNT_)
#define GRM_GET_TICK()              (0)
#define __G1__
#define __BLUETOOTH_A2DP_MMI__
#define __DISTORTED_VOICE_MMI__
#define __CAMERA_QRCODE_MMI__
#define __CAMERA_STICKER_MMI__
#define __ATV_MMI__
#define __GPS__
#else ////#if defined(RES_MGR_STANDALONE_DEBUG)

#define GRM_MALLOC                          MsCallocateMem
#define GRM_MFREE(_X_)                      MsReleaseMemory(_X_)
#define GRM_MEMSET                          memset
#define GRM_MEMCPY                          memcpy
#define GRM_MEMCMP                          memcmp
#define GRM_MEMMOVE                         memmove
#define GRM_MS_OK                           MS_OK
#define GRM_SENDMSG(_X_, _Y_)               MsSend(_X_, _Y_)
#define GRM_SENDMSG_THD(_X_, _Y_)           MsSendWithThreshold(_X_, _Y_)
#define GRM_MBOX_STATUS(_W_, _X_, _Y_, _Z_) MsMboxStatus(_W_, _X_, _Y_, _Z_)

#define _GRM_IMG                            (_SYS | LEVEL_29)
#define _GRM                                (_SYS | LEVEL_30)
#define _GRM_UT                             (_SYS | LEVEL_31)

#define GRM_TRACE                           vm_dbgTrace
#define GRM_ERROR                           vm_dbgError

#define GRM_SYNC_LOCK_INIT                  MsInitSem(RESMGR_SYNC_SEM, 1);
#define GRM_SYNC_LOCK                       MsConsumeSem(RESMGR_SYNC_SEM);
#define GRM_SYNC_UNLOCK                     MsProduceSem(RESMGR_SYNC_SEM);

#define GRM_REENTRY_LOCK_INIT               MsInitSem(RESMGR_REENTRY_SEM, 1);
#define GRM_REENTRY_LOCK                    MsConsumeSem(RESMGR_REENTRY_SEM);
#define GRM_REENTRY_UNLOCK                  MsProduceSem(RESMGR_REENTRY_SEM);

#define GRM_GSS_SYNC_LOCK_INIT              MsInitSem(RESMGR_GSS_SYNC_SEM, 1);
#define GRM_GSS_SYNC_LOCK                   MsConsumeSem(RESMGR_GSS_SYNC_SEM);
#define GRM_GSS_SYNC_UNLOCK                 MsProduceSem(RESMGR_GSS_SYNC_SEM);

#define GRM_GSS_REENTRY_LOCK_INIT           MsInitSem(RESMGR_GSS_REENTRY_SEM, 1);
#define GRM_GSS_REENTRY_LOCK                MsConsumeSem(RESMGR_GSS_REENTRY_SEM);
#define GRM_GSS_REENTRY_UNLOCK              MsProduceSem(RESMGR_GSS_REENTRY_SEM);

#define GRM_CTRL_SYNC_LOCK_INIT             MsInitSem(RESMGR_CTRL_SYNC_SEM, 1);
#define GRM_CTRL_SYNC_LOCK                  MsConsumeSem(RESMGR_CTRL_SYNC_SEM);
#define GRM_CTRL_SYNC_UNLOCK                MsProduceSem(RESMGR_CTRL_SYNC_SEM);

#define GRM_CTRL_REENTRY_LOCK_INIT          MsInitSem(RESMGR_CTRL_REENTRY_SEM, 1);
#define GRM_CTRL_REENTRY_LOCK               MsConsumeSem(RESMGR_CTRL_REENTRY_SEM);
#define GRM_CTRL_REENTRY_UNLOCK             MsProduceSem(RESMGR_CTRL_REENTRY_SEM);

#define GRM_TASK_SYNC_LOCK_INIT             MsInitSem(RESMGR_TASK_SYNC_SEM, 1);
#define GRM_TASK_SYNC_LOCK                  MsConsumeSem(RESMGR_TASK_SYNC_SEM);
#define GRM_TASK_SYNC_UNLOCK                MsProduceSem(RESMGR_TASK_SYNC_SEM);

#define GRM_RINGBUFF_LOCK_INIT              MsInitSem(RESMGR_RINGBUFF_SEM, 1);
#define GRM_RINGBUFF_SEM                    RESMGR_RINGBUFF_SEM

#define GRM_SLEEP(_COUNT_)                  MsSleep(_COUNT_)
#define GRM_GET_TICK                        MsGetOsTick

#endif //#if defined(RES_MGR_STANDALONE_DEBUG)

#if !defined(__SDK_SIMULATION__)
#ifndef __PLATFORM_DEBUG__
#define GRM_ASSERT(_e_)                     if(_e_){}
#define GRM_FATAL(_level_, _format_, ...)   vm_dbgError((_level_) | FATAL, _format_, ##__VA_ARGS__)
#else
#define GRM_ASSERT                          CUS_ASSERT
#define GRM_FATAL(_level_, _format_, ...)   vm_dbgError((_level_) | FATAL, _format_, ##__VA_ARGS__)
#endif
#else
#define GRM_ASSERT                          assert
#define GRM_FATAL                           assert(0); //vm_dbgError
#endif

/// static assert macro for const value checking at build time
/// The _const_e_ should be a constant expression that can be converted to a boolean.
/// If _const_e_ is false, the "'STATIC_ASSERTION_AT_FALSE_EXP' : redefinition; different subscripts" is showed and the compilation fails with an error.
/// If _const_e_ is true, the STATIC_ASSERT declaration has no effect.
#define GRM_STATIC_ASSERT(_const_e_)   \
    extern char STATIC_ASSERTION_AT_FALSE_EXP[1]; \
    extern char STATIC_ASSERTION_AT_FALSE_EXP[(_const_e_)?1:2]

#define GRM_RET_IF_NULL(p, str) \
    {\
        if(NULL == (p))\
        {\
            GRM_ASSERT(0);\
            return;\
        }\
    }

#define GRM_RET_VAL_IF_NULL(p, v, str) \
    {\
        if(NULL == (p))\
        {\
            GRM_ASSERT(0);\
            return (v);\
        }\
    }

#define GRM_RET_IF_FAIL(a, str) \
    {\
        if(ABL_CMN_OK != (a))\
        {\
            GRM_ASSERT(0);\
            return;\
        }\
    }

#define GRM_RET_VAL_IF_FAIL(a, str) \
    {\
        if(ABL_CMN_OK != (a))\
        {\
            GRM_ASSERT(0);\
            return (a);\
        }\
    }

#define GRM_RET_IF_NEQ(p, str) \
    {\
        if(0 == (p))\
        {\
            GRM_ERROR(_GRM, str);\
            return;\
        }\
    }

#define GRM_RET_VAL_IF_NEQ(p, v, str) \
    {\
        if(0 == (p))\
        {\
            GRM_ERROR(_GRM, str);\
            return (v);\
        }\
    }

#if defined(__SDK_SIMULATION__)
#define GRM_ENABLE_UNIT_TEST
#define GRM_ENABLE_DEBUG_INFO
#endif

#if defined(GRM_ENABLE_DEBUG_INFO)
#define FSM_ENABLE_DEBUG_INFO
#endif

/*The meaning of __SLDPM_FREE etc are in mmi_common_def.h*/
#if defined(__TARGET__) && defined(__arm)
#define __SLDPM_FREE__  __attribute__((section(".sldpm_free")))
#define __SLDPM_AUDIO_SECTION__  __attribute__((section(".audio_section")))
#define __SLDPM_AUDIO_PLAY_SECTION__  __attribute__((section(".audio_play_section")))
#define __SLDPM_AUDIO_STOP_SECTION__  __attribute__((section(".audio_stop_section")))
#define __SLDPM_AUDIO_RODATA_SECTION__  __attribute__((section(".audio_rodata_section")))
#define __SLDPM_BT_RODATA_SECTION__  __attribute__((section(".bt_rodata_section")))
#define __SLDPM_BT_SECTION__  __attribute__((section(".bt_section")))
#define __SLDPM_BT_SEARCH_SECTION__  __attribute__((section(".bt_search_section")))
#define __SLDPM_CALENDAR_SECTION__  __attribute__((section(".calendar_section")))
#define __SLDPM_CALLLOG_SECTION__  __attribute__((section(".callog_section")))
#define __SLDPM_CAM_SECTION__  __attribute__((section(".cam_section")))
#define __SLDPM_CAM_SESSION_SECTION__  __attribute__((section(".cam_session_section")))
#define __SLDPM_CAM_RODATA_SECTION__  __attribute__((section(".cam_rodata_section")))
#define __SLDPM_CC_SECTION__  __attribute__((section(".cc_section")))
#define __SLDPM_CC_RODATA_SECTION__  __attribute__((section(".cc_rodata_section")))
#define __SLDPM_CC_IN_SECTION__  __attribute__((section(".cc_in_section")))
#define __SLDPM_CC_OUT_SECTION__  __attribute__((section(".cc_out_section")))
#define __SLDPM_CFG_SECTION__  __attribute__((section(".cfg_section")))
#define __SLDPM_CHECK_SIGNAL_SECTION__  __attribute__((section(".check_singal_section")))
#define __SLDPM_DIALOG_SECTION__  __attribute__((section(".dialog_section")))
#define __SLDPM_FILEMGR_SECTION__  __attribute__((section(".filemgr_section")))
#define __SLDPM_FILEMGR_RODATA_SECTION__  __attribute__((section(".filemgr_rodata_section")))
#define __SLDPM_KMV_SECTION__  __attribute__((section(".kmv_section")))
#define __SLDPM_MISC_SECTION__  __attribute__((section(".misc_section")))
#define __SLDPM_MOI_SECTION__  __attribute__((section(".moi_section")))
#define __SLDPM_MSG_SECTION__  __attribute__((section(".msg_section")))
#define __SLDPM_MMS_SECTION__  __attribute__((section(".mms_section")))
#define __SLDPM_MPLAYER_SECTION__  __attribute__((section(".mplayer_section")))
#define __SLDPM_NETWORK_SECTION__  __attribute__((section(".network_section")))
#define __SLDPM_PHB_SECTION__  __attribute__((section(".phb_section")))
#define __SLDPM_RADIO_SECTION__  __attribute__((section(".radio_section")))
#define __SLDPM_SIM_SECTION__  __attribute__((section(".sim_section")))
#define __SLDPM_SMS_SECTION__  __attribute__((section(".sms_section")))
#define __SLDPM_STGR_SECTION__  __attribute__((section(".stgr_section")))
#define __SLDPM_STK_SECTION__  __attribute__((section(".stk_section")))
#define __SLDPM_USB_SECTION__  __attribute__((section(".usb_section")))
#define __SLDPM_VDO_SESSION_SECTION__  __attribute__((section(".vdo_session_section")))
#define __SLDPM_VOICECALL_SECTION__  __attribute__((section(".voicecall_section")))
#define __SLDPM_VPLAYER_SECTION__  __attribute__((section(".videoplayer_section")))
#define __SLDPM_VTM_SECTION__  __attribute__((section(".vtm_section")))
#define __SLDPM_WAP_SECTION__  __attribute__((section(".wap_section")))
#else
#define __SLDPM_FREE__
#define __SLDPM_AUDIO_SECTION__ 
#define __SLDPM_AUDIO_PLAY_SECTION__ 
#define __SLDPM_AUDIO_STOP_SECTION__  
#define __SLDPM_AUDIO_RODATA_SECTION__  
#define __SLDPM_BT_RODATA_SECTION__  
#define __SLDPM_BT_SECTION__  
#define __SLDPM_BT_SEARCH_SECTION__  
#define __SLDPM_CALLLOG_SECTION__ 
#define __SLDPM_CALENDAR_SECTION__  
#define __SLDPM_CAM_SECTION__  
#define __SLDPM_CAM_SESSION_SECTION__  
#define __SLDPM_CAM_RODATA_SECTION__
#define __SLDPM_CC_SECTION__  
#define __SLDPM_CC_RODATA_SECTION__ 
#define __SLDPM_CC_IN_SECTION__  
#define __SLDPM_CC_OUT_SECTION__ 
#define __SLDPM_CFG_SECTION__   
#define __SLDPM_CHECK_SIGNAL_SECTION__  
#define __SLDPM_DIALOG_SECTION__  
#define __SLDPM_FILEMGR_SECTION__  
#define __SLDPM_FILEMGR_RODATA_SECTION__  
#define __SLDPM_KMV_SECTION__  
#define __SLDPM_MISC_SECTION__ 
#define __SLDPM_MMS_SECTION__  
#define __SLDPM_MOI_SECTION__  
#define __SLDPM_MPLAYER_SECTION__ 
#define __SLDPM_MSG_SECTION__  
#define __SLDPM_NETWORK_SECTION__  
#define __SLDPM_PHB_SECTION__  
#define __SLDPM_RADIO_SECTION__  
#define __SLDPM_SIM_SECTION__  
#define __SLDPM_SMS_SECTION__  
#define __SLDPM_STGR_SECTION__  
#define __SLDPM_STK_SECTION__  
#define __SLDPM_USB_SECTION__  
#define __SLDPM_VDO_SESSION_SECTION__ 
#define __SLDPM_VOICECALL_SECTION__  
#define __SLDPM_VPLAYER_SECTION__ 
#define __SLDPM_VTM_SECTION__  
#define __SLDPM_WAP_SECTION__  
#endif
/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__PLATFORMDEFINES_H__


