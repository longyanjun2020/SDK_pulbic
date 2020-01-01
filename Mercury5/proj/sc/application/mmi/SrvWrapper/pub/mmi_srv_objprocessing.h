/**
* @file    mmi_srv_objprocessing.h
* @brief
*
*/

#ifndef __MMI_SRV_OBJPROCESSING_H__
#define __MMI_SRV_OBJPROCESSING_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_objprocessingsrv.h"

//#define OBJPROCESSINGSRV_EVT_GETPREVIEWDATADONE               (CLSID_OBJPROCESSINGSRV << 16 | 1)
typedef void (* SrvObjProcessingGetPreviewDataDone_CB)(void *pThis,
                                                            OPSrv_LaunchFor_e eCurrentOP,
                                                            OPSrvRsltInfo_t *pRsltInfo);

//#define OBJPROCESSINGSRV_EVT_SRVSTOPPED               (CLSID_OBJPROCESSINGSRV << 16 | 28)
typedef void (* SrvObjProcessingSrvStopped_CB)(void *pThis);


/** SrvObjProcessingSetxxxCB
* @brief  Add a CB to ObjProcessing obex.
*
* @param[in]      pfnCallBack             the function which will be called to notify the detection of specific event.
*/
void SrvObjProcessingSetGetPreviewDataDoneCB(SrvObjProcessingGetPreviewDataDone_CB pfnCallBack);

void SrvObjProcessingSetSrvStoppedCB(SrvObjProcessingSrvStopped_CB pfnCallBack);


/** SrvObjProcessingStartProcessing
* @brief  It is used for AP to start the obj processing.
*
* @param[in]      eLaunchType             Define the operation type that the OPSRV is launcher
* @param[out]     pReqInfo                Info of obj processing pointer to return
*
* @retval MAE_RET_SUCCESS                 If successful.
*/
MAE_Ret SrvObjProcessingStartProcessing(OPSrv_LaunchFor_e eLaunchType, OPSrvReqInfo_u *pReqInfo);

/** SrvObjProcessingStopProcessing
* @brief  It is used for AP to stop the obj processing.
*
* @retval MAE_RET_SUCCESS                 If successful.
* @retval OPSRV_RET_SRVBUSY               If the service is serving for other request.
*/
MAE_Ret SrvObjProcessingStopProcessing(void);

/** SrvObjProcessingGetStatus
* @brief  The interface is used to get obj processing status.
*
* @param[out]   pStatus                   Status of obj processing pointer to return
*/
void SrvObjProcessingGetStatus(OPSrvStatus_t *pStatus);


#endif //__MMI_SRV_OBJPROCESSING_H__
/*-----------------------------------------------------*/
