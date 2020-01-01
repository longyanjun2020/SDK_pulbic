#ifndef __VEN_GPS_MSGT_H__
#define __VEN_GPS_MSGT_H__

#ifndef __SDK_API_WAP_MMS_ONLY__

#include "ven_gps.h"
#include "ven_msg.h"
#include "ven_comdef_priv.h"

/****************************************************************************/
/*  Message :       I_VEN_GPS_DATA_IND                                      */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  From/to   : MMI to Vendor task                                          */
/*                                                                          */
/*  Scope     : The structure of the message with the indication of GPS     */
/*              data                                                        */
/*                                                                          */
/*  Structure : iVen_gps_data_ind_t                                         */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Field             |    Type   |  Description                            */
/*--------------------+-----------+-----------------------------------------*/
/*                    |           |                                         */
/****************************************************************************/
typedef struct
{
    iVen_AsyncRsp_BodyBase_t RspBase;
    ven_gpsData_t gpsData;
    ven_gpsDataCbFuncPtr_t pFnCb;
} iVen_gps_data_ind_t;

#endif //#ifndef __SDK_API_WAP_MMS_ONLY__

#endif //__VEN_GPS_MSGT_H__

