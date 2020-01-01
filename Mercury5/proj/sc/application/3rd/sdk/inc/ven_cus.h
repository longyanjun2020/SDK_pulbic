/**
 *
 * @file    ven_cus.h
 * @brief   This file implement the vendor customized data API
 *
 * @author  Code.Lin
 * @version $Id$
 *
 */
#ifndef __VEN_CUS_H_
#define __VEN_CUS_H_


#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_CUS_RET_SUCCESS = 0,
    VEN_CUS_RET_FAILED,
    VEN_CUS_RET_BAD_PARAMETERS,
    VEN_CUS_RET_NOT_ENOUGH_MEMORY,
};
typedef u32 ven_cus_ret_t;

typedef struct
{
	u8 nIndex;      // cus index
    u32 offset;     ///< offset from the start address of vendor customized data
    u32 len;        ///< Data length in bytes
    u32 *pOutData;  ///< Pointer to output data. SDK will copy customized data to this pointer.
} ven_cus_param_t;

typedef struct
{
	u8 nIndex;
	u32 nSize;
}ven_third_size_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
/**
 *  ven_cus_getVenData
 *  @brief    Get vendor specific customized data
 *            Note: This function supports synchronous only
 *
 *  @param  pCusParam     [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq      [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CUS_RET_SUCCESS if success
 *          VEN_CUS_RET_FAILED if failed
 *          VEN_CUS_RET_BAD_PARAMETERS if wrong input parameter
 *
 */
ven_cus_ret_t ven_cus_getVenData(ven_cus_param_t *pCusParam, ven_req_data_t *ptVenReq);


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
/**
 *  ven_cus_getThirdData
 *  @brief    Get 3rd specific customized data
 *            Note: This function supports synchronous only
 *
 *  @param  pCusParam     [in]Handle returned from ven_codec_openMedia()
 *  @param  ptVenReq      [in]The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                            It is up to the user to free the memory allocated for the vendor request data.
 *
 *  @retval VEN_CUS_RET_SUCCESS if success
 *          VEN_CUS_RET_FAILED if failed
 *          VEN_CUS_RET_BAD_PARAMETERS if wrong input parameter
 *
 */
ven_cus_ret_t ven_cus_getThirdData(ven_cus_param_t *pCusParam, ven_req_data_t *ptVenReq);

ven_cus_ret_t ven_cus_getThirdDataSize(ven_third_size_t *pThirdParam, ven_req_data_t *ptVenReq);
#endif /*__VEN_CUS_H_*/

