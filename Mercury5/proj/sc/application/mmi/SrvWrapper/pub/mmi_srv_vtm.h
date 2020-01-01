/**
* @file    mmi_srv_vtm.h
* @brief
*
*/

#ifdef __VT_3G324M__

#ifndef __MMI_SRV_VTM_H__
#define __MMI_SRV_VTM_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_vtmsrv.h"

/** SrvVtmOpenSessionReq
@brief Open a session of video telephony activity. Resource Manager will inform App of interrupt happenend/ ended via this command
*/
void SrvVtmCloseSessionReq(void);

/** SrvVtmOpenSessionReq
@brief Close a session of video telephony activity.
*/
void SrvVtmCloseSessionReq(void);

/** SrvVtmOpenReq
@brief   The interface is use to open video telephony.

@param[in]      pStartVideoTelephonySetting      Pointer to the user specified data for open video telephony.
@param[in]      pfnCallBack             			Pointer to the callback function.
*/
MediaSrvErrCode_e SrvVtmOpenReq(VtmSrvOpenVideoTelephony_t *pOpenVideoTelephony, VtmSrvCnfCb pfnCallBack);

/** SrvVtmStartReq
@brief  The interface is use to start video telephony.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
MediaSrvErrCode_e  SrvVtmStartReq(VtmSrvCnfCb pfnCallBack);

/** SrvVtmStopReq
@brief  The interface is use to stop video telephony.
@param[in]      pfnCallBack             Pointer to the callback funtion.
*/
MediaSrvErrCode_e  SrvVtmStopReq(VtmSrvCnfCb pfnCallBack);

/** SrvVtmCloseReq
@brief  The interface is use to close video telephony.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
MediaSrvErrCode_e  SrvVtmCloseReq(VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetZoomLevelReq
@brief  The interface is use to set video telephony zoom level.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetZoomLevelReq(VtmSrvCameraZoomLevel_e eZoomLevel, boolean bAspectRatioEnable, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetScreenModeReq
@brief  The interface is use to set video telephony screen mode.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetScreenModeReq(VtmSrvScreenMode_e eScreenMode, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetInputSourceReq
@brief  The interface is use to set video telephony input source.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetInputSourceReq(VtmSrvInputSource_t *pInputSource, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetBrightnessReq
@brief  The interface is use to set video telephony brightness level.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetBrightnessReq(u16 nLevel, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetContrastReq
@brief  The interface is use to set video telephony contrast level.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetContrastReq(u16 nLevel, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetRemotePictureReq
@brief  The interface is use to set video telephony remote picture.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetRemotePictureReq(VtmSrvRemotePicture_t *pRemotePicture, VtmSrvCnfCb pfnCallBack);

/** SrvVtmSetBlankPreviewReq
@brief  The interface is use to enable/disable blank preview.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSetBlankPreviewReq(boolean bEnable, VtmSrvCnfCb pfnCallBack);

/** SrvVtmStartRecordReq
@brief  The interface is use to start record video telephony.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmStartRecordReq(VtmSrvStartRecord_t *pStartRecord, VtmSrvCnfCb pfnCallBack);

/** SrvVtmStopRecordReq
@brief  The interface is use to stop record video telephony.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmStopRecordReq(VtmSrvCnfCb pfnCallBack);

/** SrvVtmSaveRecordFileReq
@brief  The interface is use to save record file.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmSaveRecordFileReq(VtmSrvGetFilenameCb pfnCallBack);

/** SrvVtmDiscardRecordFileReq
@brief  The interface is use to discard record file.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmDiscardRecordFileReq(VtmSrvCnfCb pfnCallBack);

/** SrvVtmAbortSavingFileReq
@brief  The interface is use to abort saving file.
@param[in]      pfnCallBack             Pointer to the callback function.
*/
void SrvVtmAbortSavingFileReq(VtmSrvCnfCb pfnCallBack);

void SrvVtmSetInterruptNotifyCb(MediaSrvInterruptNotifyCb pfnVtmSrvCb, u32 nCusData);
void SrvVtmSetNotifyCb(VtmSrvNotifyCb pfnVtmSrvCb, u32 nCusData);

#endif /*__MMI_SRV_VTM_H__*/

#endif //#ifdef __VT_3G324M__
