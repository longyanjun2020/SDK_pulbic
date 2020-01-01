#ifndef __MS_SOCKET_TRAFFIC_MANAGER_H__
#define __MS_SOCKET_TRAFFIC_MANAGER_H__

#include "ms_socket_cmn.h"
#include "ms_socket_traffic_checker.h"
#include "sys_sys_bootinit.h" 

typedef void* MservSocketDataTrafficMgrHdl_t;
typedef void (*Mserv_DataTrafficManager_NotifyCB)(MservSocketBearerInfo_t *psBearerInfo, MservSocketTrafficStatus_t sStatus, void *pvUserData);


__ONCE_CALL_ON_BOOT__ MservSocketDataTrafficMgrHdl_t Mserv_DataTrafficManagerFactory_Create(void);
void Mserv_DataTrafficManagerFactory_Destroy(MservSocketDataTrafficMgrHdl_t hDataTrafficMgr);
Mserv_DataTrafficCheckerHdl_t Mserv_DataTrafficManager_GetDataTrafficChecker(MservSocketDataTrafficMgrHdl_t hDataTrafficMgr, MservSocketBearerInfo_t *psBearerInfo);

bool Mserv_DataTrafficManager_AddObserver(MservSocketDataTrafficMgrHdl_t hDataTrafficMgr,u32 uAppId, bool bFromVendor, void *pvUserData, Mserv_DataTrafficManager_NotifyCB pfnNotifyCb);
bool Mserv_DataTrafficManager_RemoveObserver(MservSocketDataTrafficMgrHdl_t hDataTrafficMgr,u32 uAppId, bool bFromVendor, void **ppvUserData);
void Mserv_DataTrafficManager_NotifyAll(MservSocketDataTrafficMgrHdl_t hDataTrafficMgr, MservSocketBearerInfo_t *psBearerInfo ,MservSocketTrafficStatus_t sStatus);

#endif/* __MS_SOCKET_TRAFFIC_MANAGER_H__ */
