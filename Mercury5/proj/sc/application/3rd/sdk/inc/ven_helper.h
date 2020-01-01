#ifndef __VEN_HELPER_H__
#define __VEN_HELPER_H__

/***************************************************************************/
/*  File : ven_helper.h                                                    */
/*-------------------------------------------------------------------------*/
/*  Scope: This file defines helper function for vender req/rsp functions. */
/*         Private function for SDK internal use                           */
/*                                                                         */
/***************************************************************************/

#include "ven_common_def.h"
#include "ven_prim_msg.h"
#include "vm_msgt.ht"

enum
{
    IVEN_HELPER_RET_SUCCESS         = 0,
    IVEN_HELPER_RET_BAD_PARAM       = 1,
    IVEN_HELPER_RET_OUT_MOMORY      = 2,
    IVEN_HELPER_RET_FAILED          = 3
};

typedef u8 iven_helper_ret_t;

//iven_helper_ret_t iven_malloc_req_message(ven_req_data_t *pReqData, vm_msg_t **ppMsg, s16 BodyLength, s16 TypeMsg);
vm_msg_t* ven_helper_malloc_req_message(ven_req_data_t *pReqData, s16 BodyLength, s16 TypeMsg, u16 MbxDst);
iven_helper_ret_t ven_helper_SyncAPI_InitSem(u32 Handle, u32 *pSemID);
iven_helper_ret_t ven_helper_SyncAPI_FreeSem(u32 Handle, u32 SemID);
iven_helper_ret_t ven_helper_UISyncAPI_InitSem(u32 Handle, u32 *pSemID);
iven_helper_ret_t ven_helper_UISyncAPI_FreeSem(u32 Handle, u32 SemID);
void ven_helper_VoteCpuSpeedHigh(iVen_App_ID  AP_ID, u8 bHigh);
iVen_Handle_t* ven_helper_getHandleByAppId(ven_app_id_t appId);

#endif //__VEN_HELPER_H__
