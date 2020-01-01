#ifndef __MS_SOCKMGR_INIT_H__
#define __MS_SOCKMGR_INIT_H__

#include "ResMgr_CmdMgrStgrItf.h"
#include "ResMgr_CmdMgrItf.h"
#include "SockMgrComMediaMgrItf.h"
#include "ms_socket_traffic_manager.h"
#include "sys_sys_bootinit.h" 

__ONCE_CALL_ON_BOOT__ void Mserv_InitSockMgr(u8 (*puVmlClientIDs)[E_SOCKMGR_COMMEDIA_NUM]);
CmdMgrHdl_t Mserv_Get_SocketCmdMgr(void);
__SLDPM_FREE__ CmdMgrStgrHdl_t Mser_Get_SocketTaskStgr(void);
MservSocketDataTrafficMgrHdl_t Mserv_Get_SocketDataTrafficMgr(void);
void Mser_UnInitSockMgr(void);

#endif/* __MS_SOCKMGR_INIT_H__ */
