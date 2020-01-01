#ifndef _SOCKMGR_CONFIG_H_
#define _SOCKMGR_CONFIG_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/// feature for socket manager
#define __SOCKMGR_FEATURE_QUEUING_TIMEOUT__
#define MS_SOCKET_CMD_TIMEOUT_VALUE  (20000)


#define SOCKMGR_DUMP_FLAG    _GRM
#define COMMEDIA_OWNER_NUM   (1)
#define _SOCKMGR_DEBUG_MODE_ (1)

#define SOCKMGR_MAX_SHARE_SOCKET_NUM (7)
#define BEARER_GPRS_MAX_SOCKET_NUM   (SOCKMGR_MAX_SHARE_SOCKET_NUM)
#define BEARER_WIFI_MAX_SOCKET_NUM   (SOCKMGR_MAX_SHARE_SOCKET_NUM)
#define BEARER_WIFI_MAX_DATALINK_NUM (1)
#define BEARER_DUMMY_DATALINK_NUM    (1)
#ifdef __MULTI_DATALINK__
#define BEARER_GPRS_MAX_DATALINK_NUM (2)
#else
#define BEARER_GPRS_MAX_DATALINK_NUM (1)
#endif /// __SMALL_ROM__

#define MSER_MAILBOX (CUS_MBX_MSERV)
#define MSER_DATALINK_TI (0)

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif /* _SOCKMGR_CONFIG_H_ */
