#ifndef __VMLIND_2_SOCKETCMDPRO_ITF_H__
#define __VMLIND_2_SOCKETCMDPRO_ITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "VmlAdaptor.h"
#include "SocketCmdItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

bool VmlIndCheckValid(const void *cpvMsg);
SocketCmdHdl_t VmlIndGetSocketCmd(const void *cpvMsg);
ResMgr_RspHdl_t VmlInd2SocketCmdRsp_StatusChange(const void *cpvMsg);

#endif /* __VMLIND_2_SOCKETCMDPRO_ITF_H__ */
