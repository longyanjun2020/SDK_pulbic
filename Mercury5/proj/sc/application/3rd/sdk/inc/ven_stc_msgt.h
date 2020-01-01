/**
 * @file ven_stc_msgt.h
 *
 * @brief This file defines the app state control related message structures
 *
 * @version $Id: ven_stc_msgt.h 33467 2009-06-16 08:26:01Z steve.lee $
 *
 */
#ifndef __VEN_STC_MSGT_H__
#define __VEN_STC_MSGT_H__

#include "ven_stc.h"
#include "ven_comdef_priv.h"

enum
{
    VEN_STC_BACKGROUND = 1,
    VEN_STC_FOREGROUND,
};
typedef u8 IVen_stc_param_t;

typedef struct
{
    iVen_App_ID VenAppId;
    u8 bForceCPUHigh;
    void *pData;
    u32 DataLen;
	bool bSessionOpen;
} iVen_stc_start_req_t;

typedef struct
{
    iVen_App_ID VenAppId;
} iVen_stc_stop_req_t;

typedef struct
{
    iVen_App_ID VenAppId;
} iVen_stc_suspend_req_t;

typedef struct
{
    iVen_App_ID VenAppId;
} iVen_stc_resume_req_t;

typedef struct
{
    iVen_App_ID VenAppId;
    u8 type;
    void *pData;
    u32 DataLen;
} iVen_stc_status_ind_t;

typedef struct
{
    iVen_App_ID VenAppId;
    ven_stc_ret_t ret;
} iVen_stc_rsp_t;

typedef struct
{
    iVen_App_ID VenAppId;
} iVen_stc_notify_stop_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_App_ID VenAppId;
} iVen_stc_notify_start_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_stc_ret_t retCode;
} iVen_stc_start_cnf_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    iVen_App_ID VenAppId;
    ven_stc_status_t status;
    ven_stc_ret_t *pRetCode; // For sync
} iVen_stc_notify_status_change_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_stc_ret_t retCode;
} iVen_stc_status_change_cnf_t;

#endif /* __VEN_STC_MSGT_H__ */


