/**
 * @file    mmi_btsrv_util.h
 * @brief   The file is contain some utilities for BTSRV.
 * @author  cosmo.sung@mstarsemi.com
 * 
 * @version $Id: 
 */

#ifndef __MMI_BTSRV_UTIL_H__
#define __MMI_BTSRV_UTIL_H__
#include "mmi_btsrv.h"
#include "mmi_btsrv_def.h"
#include "mmi_mae_applet.h"

/* The functions to pack the different param data(BTSRV_IndMsg_t) for BTNotifyApp */
MAE_Ret _BTSRV_PackBTNotifyAudioStatusMsg(BTSRV_IndicationType_e eType, BTSRV_DevInfo_t *ptDevInfo, BTSRV_Link_Status_e  eConnectStatus, BTSRV_AudioDevLinkStatus_t *ptDevLinkStatus, BTSRV_IndMsg_t **pOutIndMsg);

MAE_Ret _BTSRV_PackBTNotifyDeviceInfoMsg( BTSRV_IndicationType_e eType, BTSRV_DevInfo_t *ptDevInfo, BTSRV_IndMsg_t **pOutIndMsg);

MAE_Ret _BTSRV_PackBTNotifyBaseMsg( BTSRV_IndicationType_e eType, BTSRV_IndMsg_t** pOutIndMsg);

MAE_Ret _BTSRV_PackBTNotifyWarningMsg(BTSRV_IndicationType_e eType, u32 u32WarningMsgID, BTSRV_IndMsg_t** pOutIndMsg);

MAE_Ret _BTSRV_PackBTNotifyAcceptRecvFileMsg(BTSRV_IndicationType_e eType, BTSRV_DevInfo_t *ptDevInfo, boolean  bisConflict, BTSRV_IndMsg_t **pOutIndMsg);

MAE_Ret _BTSRV_PackBTNotifyA2dpStreamingMsg(BTSRV_IndicationType_e eType, BTSRV_DevInfo_t *ptDevInfo, boolean bIsDisableA2dpStream, BTSRV_IndMsg_t** pOutIndMsg);


/* Launch BTNotifyApp to show dialog or interact with the user */
MAE_Ret _BTSRV_LaunchBTNotifyApp(IBase *pOwner, IApplet **ppIApplet, BTSRV_IndMsg_t *pIndMsg);

/* Check if a device is a BT audio device by its CoD(Class Of Device)*/
boolean	mmi_BTSrv_IsAudioDevice(u32 CoD);

/* Check if a device supports a certain service */
boolean mmi_BTSrv_IsSupportService(u32 u32DevSdpData, BTSRV_SdpService_e eSdpServiceType);

/* Check if two addresses are the same */
boolean _BTSRV_IsSameAddr(u8 *Addr1, u8 *Addr2);

/* The function to free the param after "post event" */
void _BTSRV_EventParamsFree(IBase *pIssuer, u32 nParam1, u32 nParam2);

void _BTSRV_RecvInfoForDlgResultFree(IBase *pIssuer, u32 nParam1, u32 nParam2);

void _BTSRV_PrintDeviceAddr(u8 *pAddr);

void _BTSRV_PrintFilePath(MAE_WChar *pwPath);

#endif // __MMI_BTSRV_UTIL_H__
