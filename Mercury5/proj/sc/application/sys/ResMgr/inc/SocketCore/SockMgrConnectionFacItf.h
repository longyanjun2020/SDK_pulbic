#ifndef __SOCKMGR_CONNECTIONFACITF_H__
#define __SOCKMGR_CONNECTIONFACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ConnHdl_t SockMgr_ConnectionFactory_CreateConnection
(
  ResMgr_AppId_e eOwnerId,
  SockMgr_Bearer_e eBearer
);

void SockMgr_ConnectionFactory_DestroyConnection
( 
  SockMgr_ConnHdl_t hConn
);

#endif/* __SOCKMGR_CONNECTIONFACITF_H__ */
