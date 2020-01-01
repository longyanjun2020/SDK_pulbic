/**
* @file    mmi_srv_cl.h
* @brief
*
*/

#ifndef __MMI_SRV_CL_H__
#define __MMI_SRV_CL_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_clsrv.h"

/**
* @brief: Get Cell Location Name by number
* @param[in]  codestr  Pointer to the search number buffer
* @param[in]  msgidOut Pointer to the _CLSRV_TEXTID_TAG
* @return     caller location
*/
MAE_WChar * SrvClGetZoneName(s8* codestr, u32 * msgidOut);


/**
* @brief: Get Cell Location by number Ex
* @param[in]  codestr  Pointer to the search number buffer
* @param[out] pStringOut String of Cell Location Name
* @return		MAE_RET_SUCCESS		success
* @return		MAE_RET_FAILED			not found
* @return		MAE_RET_NO_FILE		can not find file
* @return		MAE_RET_NOT_SUPPORTED	not support
*/
MAE_Ret SrvClGetZoneNameEx(s8* pCodeStr, MAE_WChar** pStringOut);


/**
* @brief: Get Cl service database file status
* @param[out]  pStatus  Pointer to the status of service setting
*
* @return		MAE_RET_SUCCESS				success
* @return		MAE_RET_BAD_PARAM			param is not valid
* @return		MAE_RET_NOT_SUPPORTED	not support
*/
MAE_Ret SrvClGetDbFileStatus(ClSrvStatus_t *pStatus);

#endif /*__MMI_SRV_CL_H__*/

