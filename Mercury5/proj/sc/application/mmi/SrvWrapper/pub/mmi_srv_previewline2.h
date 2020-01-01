/**
* @file    mmi_srv_previewline2.h
* @brief
*
*/

#ifndef __MMI_SRV_PREVIEWLINE2_H__
#define __MMI_SRV_PREVIEWLINE2_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_previewline2srv.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
/** SrvPreviewLine2Init
* @brief  The interface is used to set initial data to previewline2 service
*
* @param[in]    pstLine2PrvInitData		   The place to holder initial data.
*
* @retval MAE_RET_SUCCESS                  Success
* @retval MAE_RET_FAILED                   Can not get CFG Info
*/
MAE_Ret SrvPreviewLine2Init(Line2PrvInitData_t *pstLine2PrvInitData);

/** SrvPreviewLine2Update
* @brief  The interface is used to fill string in text buffer which is created by client AP
*
* @param[in]     pstLine2PrvData            The place to holder preview data(Previewbuffer and buffer size).
*/
void SrvPreviewLine2Update(Line2PrvData_t *pstLine2PrvData);

/** SrvPreviewLine2UpdateNextandSave
* @brief  The interface is used to set setting to next value(ex. ON->OFF, OFF->ON)  and fill corresponding string in text buffer which is created by client AP
*
* @param[in]     pstLine2PrvData            The place to holder preview data(Previewbuffer and buffer size).
*/
void SrvPreviewLine2UpdateNextandSave(Line2PrvData_t *pstLine2PrvData);


#endif // __MMI_SRV_PREVIEWLINE2_H__

