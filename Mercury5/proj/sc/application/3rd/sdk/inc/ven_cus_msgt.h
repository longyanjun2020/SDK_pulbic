/**
 * @file ven_cus_msgt.h
 *
 * This file defines the implement the vendor customized data API
 *
 * @version $Id: ven_cus_msgt.h 45468 2009-11-13 05:13:00Z Mobile_CM $
 *
 */

#ifndef __VEN_CUS_MSGT_H__
#define __VEN_CUS_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_cus.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_CUS_GET_VEN_DATA_REQ                              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : Vendor task to MMI                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the purpose to get vendor */
/*              specific data                                               */
/*                                                                          */
/*  Structure : iVen_codec_open_media_req_t                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_cus_param_t *pCusParam;
    ven_cus_ret_t *pRetCode;
} iVen_cus_get_ven_data_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_cus_param_t *pCusParam;
    ven_cus_ret_t *pRetCode;
} iVen_cus_get_ven_third_data_req_t;

typedef struct
{
    iVen_AsyncReq_BodyBase_t ReqBase;
    ven_third_size_t *pThirdParam;
    ven_cus_ret_t *pRetCode;
} iVen_cus_get_ven_third_Size_req_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__
#endif /* __VEN_CUS_MSGT_H__ */
