#ifndef __SOCKETCMD_CTRLHANDLER_H__
#define __SOCKETCMD_CTRLHANDLER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "ResMgr_Ctrl.h"
#include "SocketCmdCtrlHandlerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct
{
    SockMgr_Bearer_e eBearer;
    SockMgr_Bearer_StatusChange_e eStatusChange;
}SockMgrUpdateBearerStatusReq_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif/* __SOCKETCMD_CTRLHANDLER_H__ */
