/**
* @file mmi_cb_lbs.h
*
*
* @version $Id: mmi_cb_lbs.h 14013 2008-12-11 16:23:04Z william.wang $
*/

#ifndef __MMI_CB_LBS_H__
#define __MMI_CB_LBS_H__

#ifdef __MAP_MMI_LBS__
#include "mmi_mae_common_def.h"
#include "mmi_if_def.h"
#include "ven_sdk.h"
#include "ven_setting.h"
#include "ven_handle.h"
#include "cus_msg.hc"

typedef enum HTTP_METHOD_Tag
{
    HTTP_UNKNOWN_METHOD = -1,
    HTTP_GET_METHOD = 0,
    HTTP_POST_METHOD,
}HTTP_Method;

typedef struct LBS_REQ_SERVICE_INIT_Tag
{
    ven_common_sim_id_t SimID;
    ven_setting_network_profile_t *pNetworkProfile;
} LBS_REQ_SERVICE_INIT_t;

typedef struct LBS_REQ_SERVICE_ACTION_Tag
{
    HTTP_Method  http_method;
    u16 *http_url;
    u8 *http_message;
}LBS_REQ_SERVICE_ACTION_t;

typedef struct LBS_REQ_Body_tag
{
    union
    {
        LBS_REQ_SERVICE_INIT_t lbs_service_init;
        LBS_REQ_SERVICE_ACTION_t lbs_service_action;
    } reqParams;
} LBS_REQ_Body_t;

void MapView_LBS_Init(void);
bool MapView_LBS_Parser(vm_msg_t *pMessage);
void MapView_LBS_Service_Init_Req(ven_common_sim_id_t SimID, ven_setting_network_profile_t *pNetworkProfile);
void MapView_LBS_Service_Final_Req(void);
void MapView_LBS_Service_Action_Req(HTTP_Method  http_method, u16 *http_url, u8 *http_message);
int  MapView_check_LBS_Cmd(void);
#endif /* __MAP_MMI_LBS */

#endif
