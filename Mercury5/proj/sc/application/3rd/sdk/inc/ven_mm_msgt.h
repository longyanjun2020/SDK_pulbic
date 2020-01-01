#ifndef __VEN_MM_MSGT_H__
#define __VEN_MM_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_mm.h"
#include "ven_comdef_priv.h"

typedef enum
{
    ///< Only support VEN_MM_EVT_SignalStrengthInd now
    VEN_MM_EVT_NITZInd = 0
   ,VEN_MM_EVT_SignalStrengthInd
   ,VEN_MM_EVT_NetworkKLostInd
   ,VEN_MM_EVT_EmergencyCallOnlyInd
   ,VEN_MM_EVT_GPRSRegStatusInd
   ,VEN_MM_EVT_NetworkRegInd
   ,VEN_MM_EVT_NetworkTypeInd
   ,VEN_MM_EVT_LineServiceInd
}VEN_MM_Event_Type_e;

/****************************************************************************/
/*  Message :       I_VEN_MM_REGISTER_LISTENER_REQ                          */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to            */
/*              send a sms.                                                 */
/*  Structure : iVen_mm_register_listener_req_t                             */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    u32 nEventMask;
    void *pCBFunc;
    u32 UserData;
    u32 *pRetCode; // for sync
}iVen_mm_register_listener_req_t;

typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    VEN_MM_Event_Type_e nEventType;
    union
    {
        iVen_mm_signalStrength_listener_rsp tSignalStrengthData;
    }RspData;
}iVen_mm_register_listener_rsp_t;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif
