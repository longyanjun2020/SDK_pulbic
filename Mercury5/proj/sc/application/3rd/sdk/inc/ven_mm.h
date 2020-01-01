#ifndef __VEN_MM_H_
#define __VEN_MM_H_
/***************************************************************************/
/*  File : ven_mm.h                                                        */
/*-------------------------------------------------------------------------*/
/*  Scope: This file defines the mobilelity related vendor request API,    */
/*         and MMI response API.                                           */
/*                                                                         */
/***************************************************************************/

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_MM_RET_SUCCESS             = 0, ///< operation completed successfully
    VEN_MM_RET_FAILED              = 1, ///< WHAT? every code here is failed
    VEN_MM_RET_NOT_SUPPORT         = 2, ///< not support
    VEN_MM_RET_BAD_PARAM           = 3, ///< invalid input parameters
    VEN_MM_RET_OUT_OF_MEMORY       = 4, ///< memory is not enough to complete the operation
};
typedef u32 ven_mm_ret_t;

// Radio signal strength
typedef struct
{
    u16 Rssi;   //signal strength
    u16 Ber;    //channel bit error rate
} ven_mm_signalStrengthInd_t;

typedef struct
{
    ven_mm_signalStrengthInd_t tSignalStrength;
    ven_common_sim_id_t SimID;
}iVen_mm_signalStrength_listener_rsp;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_mm_register_signalStrengthListener
 *
 *  @brief  This function will help to register signal strength listener.
 *          This function only support sync mode!
 *
 *  @param  nSDKHandle  [in]Vendor handle.
 *  @param  ptVenReq    [in]Vendor req data.
 *
 *  @retval VEN_MM_RET_SUCCESS if success
 *          VEN_MM_RET_FAILED if failed
 *          VEN_MM_RET_BAD_PARAM if input parameter is invalid
 */
ven_mm_ret_t ven_mm_register_signalStrengthListener(u32 nSDKHandle, ven_req_data_t *ptVenReq);
#endif
