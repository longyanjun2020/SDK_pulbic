#ifndef __VEN_WLAN_MSGT_H__
#define __VEN_WLAN_MSGT_H__

#include "ven_wlan.h"
#include "ven_comdef_priv.h"

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
	bool *pbIsWlanConnted;
	ven_wlan_connected_device_info_t *psConnectDeviceInfo;
    ven_wlan_ret_t *pRetCode; //output: only useful if the ReqBase.bSync is TRUE
} iVen_wlan_get_cur_connected_device_info_req_t;

#endif
