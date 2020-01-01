#ifndef _SOCKMGR_TRACK_POOL_ITF_H_
#define _SOCKMGR_TRACK_POOL_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrDSPortItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef enum
{
	SOCKMGR_TRACK_POOL__SOCKET_E,
	SOCKMGR_TRACK_POOL__DATALINK_E,
	SOCKMGR_TRACK_POOL__SOCKET_CMD_E,
	SOCKMGR_TRACK_POOL__CONNECTION_E,
	SOCKMGR_TRACK_POOL__NUM,
}SockMgr_Pool_e;


/*=============================================================*/
// Function Declarations
/*=============================================================*/

void SockMgr_TrackPool_Init(void) ;
void SockMgr_TrackPool_UnInit(void) ;
SockMgr_CtnrHdl_t SockMgr_TrackPool_GetPool(SockMgr_Pool_e ePool);

#endif/* _SOCKMGR_TRACK_POOL_ITF_H_ */
