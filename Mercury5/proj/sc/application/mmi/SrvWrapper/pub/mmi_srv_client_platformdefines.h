/**
* @file srv_client_platformdefines.h
*
* This header file defines the definitions of platform dependent
* types and macros
*/

#ifndef __SRV_CLIENT_PLATFORMDEFINES_H__
#define __SRV_CLIENT_PLATFORMDEFINES_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "vm_types.ht"
#include "vm_audio_api.h"
#include "string.h"
#include "cus_os.hc"

#if defined(__SDK_SIMULATION__)
#include "assert.h"
#endif //__SDK_SIMULATION__

#include "sys_vm_dbg.ho"
#include "sys_rtk_vmrtkho.h"
#include "sys_MsWrapper_cus_os_msg.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#define SRV_MALLOC                          MsAllocateMem
#define SRV_MFREE(_X_)                      MsReleaseMemory(_X_)
#define SRV_LINKMEM(_X_)                    MsLinkMemory(_X_)
#define SRV_MEMSET                          memset
#define SRV_MEMCPY                          memcpy
#define SRV_MEMCMP                          memcmp
#define SRV_MEMMOVE                         memmove
#define SRV_SENDMSG(_X_, _Y_)               MsSend(_X_, _Y_)

/*
#define _SRV_IMG                            (_SYS | LEVEL_29)
#define _SRV                                (_SYS | LEVEL_30)
#define _SRV_UT                             (_SYS | LEVEL_31)
*/
#define _SRV                                (_SYS | LEVEL_17)
#define SRV_TRACE                           vm_dbgTrace


#ifndef __MMI_SRV_CORE_DIFFERENT_TASK__
#define SRV_LOCK_INIT                       
#define SRV_LOCK_UNINIT                       
#define SRV_LOCK                            
#define SRV_UNLOCK                          
#else
#error Must define SRV_SEM in cus_os.hc
#define SRV_LOCK_INIT                       MsInitSem(SRV_SEM, 1)
#define SRV_LOCK_UNINIT                       
#define SRV_LOCK                            MsConsumeSem(SRV_SEM)
#define SRV_UNLOCK                          MsProduceSem(SRV_SEM)
#endif/* __MMI_SRV_CORE_DIFFERENT_TASK__ */

/*
#define GRM_SLEEP(_COUNT_)                  MsSleep(_COUNT_)
*/

#ifndef __PLATFORM_DEBUG__
#define SRV_ASSERT(_e_)                     if(_e_){}
#define SRV_FATAL(_level_, _format_, ...)   vm_dbgError((_level_) | FATAL, _format_, ##__VA_ARGS__)

#elif !defined(__SDK_SIMULATION__)
#define SRV_ASSERT                          CUS_ASSERT
#define SRV_FATAL(_level_, _format_, ...)   vm_dbgError((_level_) | FATAL, _format_, ##__VA_ARGS__)
#else
#define SRV_ASSERT                          assert
#endif //__SDK_SIMULATION__


/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__SRV_CLIENT_PLATFORMDEFINES_H__
