#ifndef __MMI_REQ_WLAN_H__
#define __MMI_REQ_WLAN_H__

#ifdef __WLAN_MMI__
/*=============================================================*/
/* Include Files                                               */
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_wlansrv.h"

/*=============================================================*/
/* Function Declarations                                       */
/*=============================================================*/
void                mmi_set_WLANSRVPtr(void *pWLANSRV);
WLANSRV_ErrCode_e   mmi_wlan_init(void);
WLANSRV_ErrCode_e   mmi_wlan_register_event_req(void);
WLANSRV_ErrCode_e   mmi_wlan_unregister_event_req(void);
WLANSRV_ErrCode_e   mmi_wlan_power_onoff_req(WLANSRV_PowerAction_e eAction);
WLANSRV_ErrCode_e   mmi_wlan_reset_req(void);
WLANSRV_ErrCode_e   mmi_wlan_power_saving_req(void);
WLANSRV_ErrCode_e   mmi_wlan_scan_req(WLANSRV_ScanAction_e eAction);
WLANSRV_ErrCode_e   mmi_wlan_get_scan_result_req(void);
WLANSRV_ErrCode_e   mmi_wlan_get_bss_req(void);
WLANSRV_ErrCode_e   mmi_wlan_connect_req(WLANSRV_ConnectAction_e eAction, WLANSRV_ConnectParam_t *ptConnectParam);
WLANSRV_ErrCode_e   mmi_wlan_init_fifo_req(WLANSRV_PowerAction_e eAction);
WLANSRV_ErrCode_e   mmi_wlan_delete_fifo_req(void);
WLANSRV_ErrCode_e   mmi_wlan_set_configuration(u8 *pu8MACAddr, u8 u8HostPlatform, WLANSRV_PowerAction_e eAction);
WLANSRV_ErrCode_e   mmi_wlan_set_btstatus(u32 u32BTStatus);
WLANSRV_ErrCode_e   mmi_wlan_get_auq_ver_req(void);
WLANSRV_ErrCode_e   mmi_wlan_set_gsmstatus(u32 u32GSMStatus);


#endif /* __WLAN_MMI__ */
#endif /* __MMI_REQ_WLAN_H__ */
