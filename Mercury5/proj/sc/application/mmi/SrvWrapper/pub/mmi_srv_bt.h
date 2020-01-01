/**
* @file    mmi_srv_bt.h
* @brief   
*          
*/

#ifndef __MMI_SRV_BT_H__
#define __MMI_SRV_BT_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_btsrv.h"

#ifdef __BLUETOOTH_MMI__
//Specific Service ListenerCallBack API

// BTSRV_MASK_CHIP_RESET
typedef void (*SrvBtChipResetCB)(void *pThis); //BTSRV_EVT_ChipResetInd

// BTSRV_MASK_TRANS_STATUS
typedef void (*SrvBtSendFileCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult); //BTSRV_EVT_SendFileInd
typedef void (*SrvBtTransProgressCB)(void *pThis, u32 nTransFileSize, u32 nTotalFileSize); //BTSRV_EVT_TransProgressInd
typedef void (*SrvBtTransInteractiveCB)(void *pThis); //BTSRV_EVT_TransInteractiveInd
typedef void (*SrvBtRecvReqCB)(void *pThis, MAE_WChar *pwName); //BTSRV_EVT_RecvReqInd
typedef void (*SrvBtRecvFileCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult); //BTSRV_EVT_RecvFileInd
typedef void (*SrvBtImportFileCB)(void *pThis, BTSRV_TRANS_RESULT_e eResult); //BTSRV_EVT_ImportFileInd

// BTSRV_MASK_Audio_Call
typedef void (*SrvBtAtchupCB)(void *pThis); //BTSRV_EVT_ATCHUP
typedef void (*SrvBtAtaCB)(void *pThis); //BTSRV_EVT_ATA
typedef void (*SrvBtAtchldCB)(void *pThis, u32 value); //BTSRV_EVT_ATCHLD
typedef void (*SrvBtAudioVolumeCB)(void *pThis, s8 nVolLevel); //BTSRV_EVT_AudioVolumeInd
typedef void (*SrvBtAudioCallCnfCB)(void *pThis, BTSRV_StatusCode_e eResult, BTSRV_AudioCallType_e eType); //BTSRV_EVT_AudioCallCnf
typedef void (*SrvBtAudioCallIndCB)(void *pThis, BTSRV_StatusCode_e eResult, BTSRV_AudioCallType_e eType); //BTSRV_EVT_AudioCallInd

// BTSRV_MASK_Audio_Link
typedef void (*SrvBtAudioLinkCB)(void *pThis, u8 nItem, BTSRV_Link_Status_e eLinkStatus); //BTSRV_EVT_AudioLinkCnf, BTSRV_EVT_AudioLinkInd
typedef void (*SrvBtAudioLinkConnReqCB)(void *pThis, u8 nItem); //BTSRV_EVT_AudioLinkConnInd
typedef void (*SrvBtAudioLinkStatusChangeCB)(void *pThis, u8 nItem, BTSRV_AudioDevLinkAction_e eLinkAction, BTSRV_PROFILE_e eLinkProfile, BTSRV_StatusCode_e eBtStatus, BTSRV_AudioDevLinkStatus_e eCurrentLinkStatus, BTSRV_AudioDevNotifyAttr_e eAttributes);

// BTSRV_MASK_Other
typedef void (*SrvBtPhonePowerOffCB)(void *pThis); //BTSRV_EVT_PhonePowerOffCnf
typedef void (*SrvBtPowerOnOffCB)(void *pThis, BTSRV_StatusCode_e eResult, BTSRV_PowerAction_e eOnOffStatus); //BTSRV_EVT_PowerOnOffCnf
typedef void (*SrvBtAclLinkCnfCB)(void *pThis, BTSRV_StatusCode_e eResult, BTSRV_ACLLink_t *pACLLink); //MAE_EVT_BT_ACL_LINK_CNF
typedef void (*SrvBtAclLinkIndCB)(void *pThis, BT_ACLLinkAction_e eBTLinkAction); //MAE_EVT_BT_ACL_LINK_IND
typedef void (*SrvBtReadyCB)(void *pThis); //BTSRV_EVT_Ready
typedef void (*SrvBtPairDoneCB)(void *pThis, BTSRV_StatusCode_e eResult); //BTSRV_EVT_PairDoneInd
typedef void (*SrvBtInquiryIndCB)(void *pThis, BTSRV_DevInfo_t *pBTDevInfo); //BTSRV_EVT_InquiryInd
typedef void (*SrvBtInquiryCnfCB)(void *pThis, BTSRV_StatusCode_e eResult, u32 nNum); //BTSRV_EVT_InquiryCnf
typedef void (*SrvBtPinCodeCB)(void *pThis, BTSRV_DevInfo_t *pPairDevInfo, BTSRV_StatusCode_e eResult); //BTSRV_EVT_PinCodeInd
typedef void (*SrvBtPairReqCB)(void *pThis, MAE_WChar *pwName); //BTSRV_EVT_PairReqInd
#ifdef __BLUETOOTH_A2DP_MMI__
typedef void (*SrvBtA2dpStreamingStatusChangeCB)(void *pThis, BTSRV_A2dpStreamingStatus_e); //BTSRV_EVT_A2dpStatusInd
#endif // __BLUETOOTH_A2DP_MMI__
typedef void (*SrvBtRegAvrcpCb)(void *pThis, BTSRV_AvrcpActionType_e eAvrcpAction);
typedef void (*SrvBtDeleteDeviceCB)(void *pThis, boolean bIsSuccess, BTSRV_DevInfo_t *pDevInfo); //BTSRV_EVT_DeleteDeviceCnf

/** SrvBtSetxxxCB
@brief  Add a CB to BT.

@param[in]      pfnCallBack             the function which will be called to notify the detection of specific event.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
*/
MAE_Ret SrvBtSetChipResetCB(SrvBtChipResetCB pfnCallBack);

MAE_Ret SrvBtSetSendFileCB(SrvBtSendFileCB pfnCallBack);

MAE_Ret SrvBtSetTransProgressCB(SrvBtTransProgressCB pfnCallBack);

MAE_Ret SrvBtSetTransInteractiveCB(SrvBtTransInteractiveCB pfnCallBack);

MAE_Ret SrvBtSetRecvReqCB(SrvBtRecvReqCB pfnCallBack);

MAE_Ret SrvBtSetRecvFileCB(SrvBtRecvFileCB pfnCallBack);

MAE_Ret SrvBtSetImportFileCB(SrvBtImportFileCB pfnCallBack);

MAE_Ret SrvBtSetAtchupCB(SrvBtAtchupCB pfnCallBack);

MAE_Ret SrvBtSetAtaCB(SrvBtAtaCB pfnCallBack);

MAE_Ret SrvBtSetAtchldCB(SrvBtAtchldCB pfnCallBack);

MAE_Ret SrvBtSetAudioVolumeCB(SrvBtAudioVolumeCB pfnCallBack);

MAE_Ret SrvBtSetAudioCallIndCB(SrvBtAudioCallIndCB pfnCallBack);

MAE_Ret SrvBtSetAclLinkIndCB(SrvBtAclLinkIndCB pfnCallBack);

MAE_Ret SrvBtSetReadyCB(SrvBtReadyCB pfnCallBack);

MAE_Ret SrvBtSetPairDoneCB(SrvBtPairDoneCB pfnCallBack);

MAE_Ret SrvBtSetInquiryIndCB(SrvBtInquiryIndCB pfnCallBack);

MAE_Ret SrvBtSetPinCodeCB(SrvBtPinCodeCB pfnCallBack);

MAE_Ret SrvBtSetAudioLinkIndCB(SrvBtAudioLinkCB pfnCallBack);

MAE_Ret SrvBtSetAudioLinkStatusChangeCB(SrvBtAudioLinkStatusChangeCB pfnCallBack);

MAE_Ret SrvBtSetAudioLinkConnReqCB(SrvBtAudioLinkConnReqCB pfnCallBack);

MAE_Ret SrvBtSetPairReqCB(SrvBtPairReqCB pfnCallBack);

#ifdef __BLUETOOTH_A2DP_MMI__
MAE_Ret SrvBtSetA2dpStreamingStatusChangeCB(SrvBtA2dpStreamingStatusChangeCB pfnCallBack);
#endif // __BLUETOOTH_A2DP_MMI__

/** SrvBtPowerOnOffReq
@brief   The external interface is provided to power on/off BT chip

@param[in]      eAction                 Power on/off
@param[in]      eCause                  Power on/off cause
@param[in]      pfnCallBack             SrvBtPowerOnOffCB Call back function point.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAILED                  If an error happen. 
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
*/
MAE_Ret SrvBtPowerOnOffReq(BTSRV_PowerAction_e eAction,
                           BTSRV_POWER_ONOFF_CAUSE_e eCause,
                           SrvBtPowerOnOffCB pfnCallBack);

/** SrvBtInquiryReq
@brief  The external interface is provided to send inquiry request

@param[in]      eAction                 Inquiry start/stop.
@param[in]      pfnCallBack             SrvBtInquiryCnfCB Call back function point.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAILED                  BT srv mode is not active and inquiry is stop. 
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT srv mode is not active and inquiry is start.
*/
MAE_Ret SrvBtInquiryReq(BTSRV_InquiryAction_e eAction, SrvBtInquiryCnfCB pfnCallBack);

/** SrvBtPairReq
@brief  The external interface is provided to send pair request

@param[in]      pDev                    Device information
@param[in]      eAction                 Connect/Disconnect
@param[in]      pfnCallBack             SrvBtInquiryCnfCB Call back function point.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
*/
MAE_Ret SrvBtPairReq(BTSRV_DevInfo_t *pDev, BTSRV_ACLLinkAction_e eAction, SrvBtAclLinkCnfCB pfnCallBack);

/** SrvBtPinCodeRsp
@brief  The external interface is provided to send pin code respond

@param[in]      pPinCode                pin code

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_FAILED                  BT srv mode is not active. 
@retval MAE_RET_BAD_PARAM               If input parameter error. 
*/
MAE_Ret SrvBtPinCodeRsp(MAE_WChar *pPinCode);

/** SrvBtDeleteDeviceReq
@brief  The API is used to delete a Bluetooth device. 
Using this API, AP can not make sure if the device is deleted in BT driver's database.

@param[in]      nItem                   The device index.

@retval MAE_RET_SUCCESS                 If the request is sent successful. (This does not mean the deletion is successful)
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BAD_PARAM               If input parameter is incorrect.
@retval MAE_RET_BUSY                    BT Srv mode is not in idle mode.
@retval MAE_RET_FAILED                  BT Srv does not allow deleting the device. e.g. BT Srv is creating audio link with the device.
*/
MAE_Ret SrvBtDeleteDeviceReq(u8 nItem);

/** SrvBtDeleteDeviceReqAsync
@brief  The API is used to delete a Bluetooth device. 
Using this API, AP can make sure if the device is deleted in BT driver's database successfully through the callback function.

@param[in]      nItem                   The device index.
@param[out]     pfnCallBack             The callback function to get the device deletion result.

@retval MAE_RET_SUCCESS                 If the request is sent successful. (This does not mean the deletion is successful)
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated.
@retval MAE_RET_BAD_PARAM               If input parameter is incorrect.
@retval MAE_RET_BUSY                    BT Srv mode is not in idle mode.
@retval MAE_RET_FAILED                  BT Srv does not allow deleting the device. e.g. BT Srv is creating audio link with the device.
*/
MAE_Ret SrvBtDeleteDeviceReqAsync(u8 nItem, SrvBtDeleteDeviceCB pfnCallBack);

/** SrvBtSetLocalNameReq
@brief  The external interface is provided to set local name request

@param[in]      pName                   the set name

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT srv mode is busy.
*/
MAE_Ret SrvBtSetLocalNameReq(MAE_WChar *pName);

/** SrvBtSetDiscoveryReq
@brief  The external interface is provided to set discovery request

@param[in]      eDiscoverable           discoverable/hide

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT srv mode is busy.
*/
MAE_Ret SrvBtSetDiscoveryReq(BTSRV_Discoverable_e eDiscoverable);


/** SrvBtSetAudioLinkCnfCB
@brief  1. If want to receive AudioLink Cnf CB after calling SrvBtAudioLinkReq(), need to call this API first.
        2. If want to receive AudioLink Cnf CB, and don't want to call AudioLink Req. 

@param[in]      pfnCallBack             SrvBtAudioLinkCB Call back function point.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
*/
MAE_Ret SrvBtSetAudioLinkCnfCB(SrvBtAudioLinkCB pfnCallBack);

/** SrvBtAudioLinkReq
@brief  The external interface is provided to send audio link request
        If want to receive AudioLink Cnf CB, need to call SrvBtSetAudioLinkCnfCB() first.

@param[in]      eLink                   Audio link. Please reference to BTSRV_AudioLink_e.
@param[in]      nItem                   The device index.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BAD_PARAM               nItem is out of PairDeviceNum. 
*/
MAE_Ret SrvBtAudioLinkReq(BTSRV_AudioLink_e eLink, u8 nItem);

/** SrvBtAudioLinkReqByProfile
@brief  The external interface is provided to send audio link request
        If want to receive AudioLink Cnf CB, need to call SrvBtSetAudioLinkCnfCB() first.

@param[in]      eLink                   Audio link. Please reference to BTSRV_AudioLink_e.
@param[in]      nItem                   The device index.
@param[in]      eProfile                The type of profile to connect. (only BTSRV_A2DP_PROFILE/BTSRV_HF_PROFILE/BTSRV_HS_PROFILE are supported.)

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BAD_PARAM               nItem is out of PairDeviceNum. 
*/
MAE_Ret SrvBtAudioLinkReqByProfile(BTSRV_AudioDevLinkAction_e eLink, u8 u8DevIdx, BTSRV_PROFILE_e eProfile);

/** SrvBtAudioCallReq
@brief   The external interface is provided to send audio call request

@param[in]      eCall                   Audio call type. Please reference to BTSRV_AudioCallType_e.
@param[in]      pfnCallBack             SrvBtAudioCallCnfCB Call back function point.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_FAILED                  If an error happen. 
*/
MAE_Ret SrvBtAudioCallReq(BTSRV_AudioCallType_e eCall, SrvBtAudioCallCnfCB pfnCallBack);

/** SrvBtGetActiveMode
@brief  Get BT service mode.

@retval BT srv mode           
*/
BTSRV_Mode_e SrvBtGetActiveMode(void);

/** SrvBtGetPairDeviceNum
@brief  Get the number of paired device list

@retval pair device number
*/
u8 SrvBtGetPairDeviceNum(void);

/** SrvBtGetPairDeviceInfo
@brief  Get the record of BT paired device information

@param[in]      u8Item                  The device index.

@retval Pair device information
*/
BTSRV_DevInfo_t * SrvBtGetPairDeviceInfo(u8 u8Item);

/** SrvBtGetPowerOnOffStataus
@brief  To get the record of BT power on/off status

@retval BT power status.
*/
BTSRV_PowerAction_e SrvBtGetPowerOnOffStataus(void);

/** SrvBtGetLocalName
@brief  Get the local name

@retval local name
*/
MAE_WChar * SrvBtGetLocalName(void);

/** SrvBtGetDiscoveryStatus
@brief  Get the discovery status.

@retval Discovery status           
*/
BTSRV_Discoverable_e SrvBtGetDiscoveryStatus(void);

/** SrvBtGetAudioStatus
@brief  Get the record of audio headset status

@retval Audio status
*/
BTSRV_AudioLink_e SrvBtGetAudioStatus(void);

/** SrvBtSetPairDeviceInfo
@brief  Set the paired device information.

@param[in]      nItem   The paired device index.
@param[in]      pInfo   information data

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_FAILED                  If nItem is out of PairDeviceNum. 
*/
MAE_Ret SrvBtSetPairDeviceInfo(u8 nItem, BTSRV_DevInfo_t *pInfo);

/** SrvBtAudioRingStart
@brief  Audio ring start.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_FAILED                  If BTSRV_DISCONNECT. 
*/
MAE_Ret SrvBtAudioRingStart(void);

/** SrvBtAudioRingStartWithCallerID
@brief  Audio ring start with caller ID.

@retval MAE_RET_SUCCESS                      If successful.
@retval MAE_RET_NOT_SUPPORTED          BT Srv is already terminated. 
@retval MAE_RET_FAILED                          If BTSRV_DISCONNECT. 
*/
MAE_Ret SrvBtAudioRingStartWithCallerID(u8 *pCallerID);

/** SrvBtAudioRingStop
@brief  Audio ring stop.
*/
void SrvBtAudioRingStop(void);

/** SrvBtGetPairListIndexByAddr
@brief  Get pair list index by address.

@param[in]      pAddr                   Address.

@retval pair list index
*/
u8 SrvBtGetPairListIndexByAddr(u8 *pAddr);

/** SrvBtAudioMuteReq
@brief  Set audio mute on/off request.

@param[in]      eMute                   Set mute On/Off

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT srv mode is busy.
*/
MAE_Ret SrvBtAudioMuteReq(BTSRV_AudioMuteType_e eMute);

/** SrvBtAudioCallStatus
@brief  Set audio call status.

@param[in]      eStatus                 Audio call status. Please reference to BTSRV_AudioCallStatus_e.
@param[in]      pCallerID               Caller ID.
@param[in]      nType                   Type.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT srv mode is busy.
*/
MAE_Ret SrvBtAudioCallStatus(BTSRV_AudioCallStatus_e eStatus, u8 *pCallerID, u8 nType);

/** SrvBtAudioVolumeReq
@brief  Set audio volumn level request.

@param[in]      eVolume                 Volume. Please reference to AudioSrvToneVolLevel_e.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
*/
MAE_Ret SrvBtAudioVolumeReq(AudioSrvToneVolLevel_e eVolume);

/** SrvBtStart
@brief  BT start
*/
void SrvBtStart(void);

/** SrvBtPhonePowerOffReq
@brief  Phone power off request.

@param[in]      pfnCallBack             SrvBtPhonePowerOffCB Call back function point.
*/
void SrvBtPhonePowerOffReq(SrvBtPhonePowerOffCB pfnCallBack);

/** SrvBtIsBusy
@brief  To know if BT is busy or not.

@retval MAE_RET_BUSY                    btsrv is busy.
@retval MAE_RET_SUCCESS                 btsrv is on idle. 
*/
MAE_Ret SrvBtIsBusy(void);

/** SrvBtIsReceivingFile
@brief  To know if BT is receiving file or not.

@retval TRUE                            If it is receiving file.
@retval FALSE                           If it is not receiving file. 
*/
boolean SrvBtIsReceivingFile(void);

/** SrvBtIsSendingFile
@brief  To know if BT is sending file or not.

@retval TRUE                            If it is sending file.
@retval FALSE                           If it is not sending file. 
*/
boolean SrvBtIsSendingFile(void);

/** SrvBtAbortTransFile
@brief  Abort trans file.
*/
void SrvBtAbortTransFile(void);

/** SrvBtDisconObexLink
@brief  If this file  is last one in the sending list, calling this function to disconnect with ObexLink. (Correct PR#0150551)
*/
void SrvBtDisconObexLink(void);

/** SrvBtIsUsed
@brief  To know if BT is in used or not.    

@param[in]     pAddr                    Address.

@retval TRUE                            If BT is used.
@retval FALSE                           If BT is not used.
*/
boolean SrvBtIsUsed(u8 *pAddr);

/** SrvBtIsConnectDevice (Deprecated. Use SrvBtGetBtHeadsetStatus instead)
@brief  To know if BT is connected to device or not.

@retval TRUE                            If BT is connected to device.
@retval FALSE                           If BT is not connected to device.
*/
boolean SrvBtIsConnectDevice(void);

/** SrvBtGetBtHeadsetStatus
@brief  To get the status of BT headset
@param[out]      peHeadsetStatus        The status of BT headset
*/
MAE_Ret SrvBtGetBtHeadsetStatus(BTSRV_HeadsetStatus_e *peHeadsetStatus);

/** SrvBtSendFileReq
@brief  BT send file request.

@param[in]      pAddr                   Paired device address.          
@param[in]      pwFileName              File name to be sent.
*/
MAE_Ret SrvBtSendFileReq(u8 *pAddr, MAE_WChar *pwFileName);

/** SrvBtSetInteractiveMode
@brief  Set BT interactive mode. In this mode, other APs can be notified when receiving file indicator is received. 
        Therefore, they have the chance to accept/deny the request

@param[in]      bIsActive             
*/
void SrvBtSetInteractiveMode(boolean bIsActive);

/** SrvBtInteractiveCnf
@brief  In interactive mode, other APs accept/deny receiving a file

@param[in]      bIsAccept               TRUE/FALSE.
*/
void SrvBtInteractiveCnf(boolean bIsAccept);

/** SrvBtGetReceiveFolder
@brief  Get current receive folder

@retval receive folder path.
*/
MAE_WChar *SrvBtGetReceiveFolder(void);

/** SrvBtInteractiveCnf
@brief  Set receive folder path.

@param[in]      pPath                   Receive folder path.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_NOT_SUPPORTED           BT Srv is already terminated. 
@retval MAE_RET_BUSY                    BT Srv is not in active mode. 
*/
MAE_Ret SrvBtSetReceiveFolderReq(MAE_WChar *pPath);

/** SrvBtIsOPPActive
@brief  To see if BTobex is sending or receiving or not.

@retval TRUE                            if BTobex is sending or receiving
@retval FALSE                           if BTobex is not sending nor receiving
*/
boolean SrvBtIsOPPActive(void);

/** SrvBtIsA2DPActive
@brief  To see if BT A2DP is playing media

@retval TRUE                            if A2DP is running
@retval FALSE                           if A2DP is stopped (still connected)
*/
boolean SrvBtIsA2DPActive(void);

/**
SrvBtSetBtAvrcpCb
@brief  Register a call back to listen AVRCP action type.

@param[in]      eAvrcpRegType           Pointer to a FOREGROUND/BACKGROUND channel.
@param[in]      pIReqCB                 Pointer to a request callback function.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
@return MAE_RET_NOT_SUPPORTED 		If AVRCP does not support.
*/
MAE_Ret SrvBtSetBtAvrcpCb(BTSRV_AvrcpRegType_e eAvrcpRegType, SrvBtRegAvrcpCb pfnCallBack);

/**
SrvBtCnfBTAvrcp
@brief  Confirm avrcp opertion is successful or not.

@param[in]      eAvrcpActionType        operation needed to confirm.
@param[in]      bIsSuccess              operation success or not.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvBtAvrcpCmdCnf(BTSRV_AvrcpActionType_e eAvrcpActionType, boolean bIsSuccess);

#endif /* __BLUETOOTH_MMI__ */

#endif /*__MMI_SRV_BT_H__*/
