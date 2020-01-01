#ifndef _SOCKMGR_OS_PORT_ITF_H_
#define _SOCKMGR_OS_PORT_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"

#ifndef RES_MGR_STANDALONE_DEBUG
#include "osdefs.hc"
#include "sys_MsWrapper_cus_os_sem.h"
#endif/* RES_MGR_STANDALONE_DEBUG */

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/


#define SOCKMGR_MEMSET	GRM_MEMSET
#define SOCKMGR_MALLOC	GRM_MALLOC
#define SOCKMGR_MFREE	GRM_MFREE
#define SOCKMGR_MEMMOVE GRM_MEMMOVE
#define SOCKMGR_MEMCPY	GRM_MEMCPY
#define SOCKMGR_MEMCMP	GRM_MEMCMP
#define SOCKMGR_TRACE	GRM_TRACE
#define SOCKMGR_ASSERT  GRM_ASSERT
#define SOCKMGR_FATAL   GRM_FATAL

#ifdef RES_MGR_STANDALONE_DEBUG
#define SOCKMGR_SOCKET_LOCK_INIT
#define SOCKMGR_SOCKET_LOCK
#define SOCKMGR_SOCKET_UNLOCK

#define SOCKMGR_SOCKET_CMD_LOCK_INIT
#define SOCKMGR_SOCKET_CMD_LOCK
#define SOCKMGR_SOCKET_CMD_UNLOCK
#else

#define SOCKMGR_SOCKET_LOCK_INIT    \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_LOCK_INIT");   \
        MsInitSem(SOCKETMGR_SOCKET_SEM, 1); \
    }while(FALSE)

#define SOCKMGR_SOCKET_LOCK \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_LOCK");    \
        MsConsumeSem(SOCKETMGR_SOCKET_SEM);    \
    }while(FALSE)

#define SOCKMGR_SOCKET_UNLOCK   \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_UNLOCK");  \
        MsProduceSem(SOCKETMGR_SOCKET_SEM); \
    }while(FALSE)

#define SOCKMGR_SOCKET_CMD_LOCK_INIT    \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_CMD_LOCK_INIT");  \
        MsInitSem(SOCKETMGR_CMD_SEM, 1);    \
    }while(FALSE)

#define SOCKMGR_SOCKET_CMD_LOCK \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_CMD_LOCK");    \
        MsConsumeSem(SOCKETMGR_CMD_SEM);    \
    }while(FALSE)

#define SOCKMGR_SOCKET_CMD_UNLOCK   \
    do  \
    {   \
        SOCKMGR_TRACE(SOCKMGR_DUMP_FLAG, "SOCKMGR_SOCKET_CMD_UNLOCK");    \
        MsProduceSem(SOCKETMGR_CMD_SEM);    \
    }while(FALSE)

#endif/* __SDK_SIMULATION__ */

/*=============================================================*/
// Function Declarations
/*=============================================================*/

bool SockMgr_StartCbTimer
( 
  SockMgr_TimeId_t *psTimerId, 
  void (*pfCB)(SockMgr_TimeId_t sTimerId, u32 UserData),
  u32 UserData,
  u32 trigger,
  u32 interval
);

bool SockMgr_StartPeriodicTimer
(
  SockMgr_TimeId_t sTimerId,
  SockMgr_MailBox_t sMailBox,
  u32 uInterval
);

u32 SockMgr_StopTimer
(
  SockMgr_TimeId_t sTimerId
);

SockMgr_TaskId_t SockMgr_GetCurTaskId
(
  void
);

#endif/* _SOCKMGR_OS_PORT_ITF_H_ */
