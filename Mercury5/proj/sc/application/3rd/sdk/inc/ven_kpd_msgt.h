#ifndef __VEN_KPD_MSGT_H__
#define __VEN_KPD_MSGT_H__

#include "ven_kpd.h"
#include "ven_common_def.h"

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 SdkHandle; // Handle of 3rd task
} iVen_kpd_subscribe_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 SdkHandle; // Handle of 3rd task
} iVen_kpd_reset_backlight_req_t;

#endif //__VEN_KPD_MSGT_H__

