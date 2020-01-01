/**
* @file mmi_srv_moi.h
*
*/
#ifndef __MMI_SRV_MOI_H__
#define __MMI_SRV_MOI_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_messageorganizationsrv.h"


//Specific Service ListenerCallBackfunction define
typedef void (* SrvMoiSmsIndCB)(void *pThis, SMI_MsgHdr_t *pSmHdr, boolean bNew); //MOI_EVT_SmsInd .MOI_Notify_Mask_SmsInd
typedef void (* SrvMoiTelNoSmsIndCB)(void *pThis, SMI_MsgHdr_t *pSmHdr, u32 nTelno_crc32id); //MOI_EVT_TelNoSmsInd.MOI_Notify_Mask_SmsInd
typedef void (* SrvMoiPortSmsIndCB)(void *pThis, SMI_MsgHdr_t *pSmHdr, u32 nPort); //MOI_EVT_PortSmsInd.MOI_Notify_Mask_SmsInd
typedef void (* SrvMoiSrIndCB)(void *pThis, SMI_MsgSrHdr_t *pSmHdr, u32  nStatus); //MOI_EVT_SrInd. MOI_Notify_Mask_CbInd
typedef void (* SrvMoiCbIndCB)(void *pThis, MOI_CbData_t *pCBData, SMI_SmEncoding_t eEncoding); //MOI_EVT_CbInd. MOI_Notify_Mask_SrInd

// MOI_EVT_WapPushInd no use

/**
 SrvMoiSetSMSIndCB
@brief  The interface of Service Client is use to set CB to listen the MT normal sms ind

@param[in]      pfnCallBack         SrvMoiSmsIndCB Call back function point
*/
void SrvMoiSetSMSIndCB(SrvMoiSmsIndCB pfnCallBack);

/**
 SrvMoiSetTelNoSMSIndCB
@brief  The interface of Service Client is use to set CB to listen the MT telno sms ind

@param[in]      pfnCallBack         SrvMoiTelNoSmsIndCB Call back function point
*/
void SrvMoiSetTelNoSMSIndCB(SrvMoiTelNoSmsIndCB pfnCallBack);

/**
 SrvMoiSetPortSMSIndCB
@brief  The interface of Service Client is use to set CB to listen the MT port sms ind

@param[in]      pfnCallBack         SrvMoiPortSmsIndCB Call back function point
*/
void SrvMoiSetPortSMSIndCB(SrvMoiPortSmsIndCB pfnCallBack);

/**
 SrvMoiSetCbIndCB
@brief  The interface of Service Client is use to set CB to listen the new CB ind

@param[in]      pfnCallBack         SrvMoiCbIndCB Call back function point
*/
void SrvMoiSetCbIndCB(SrvMoiCbIndCB pfnCallBack);

/**
 SrvMoiSetCbIndCB
@brief  The interface of Service Client is use to set CB to listen the status report ind

@param[in]      pfnCallBack         SrvMoiSrIndCB Call back function point
*/
void SrvMoiSetSRIndCB(SrvMoiSrIndCB pfnCallBack);

/**
* SrvMoiSMS_MT_IND
* @brief    To receive the SMS raw data indication and post the MT information to listened AP/Srv.
* @param[in]    pSmsInd             The pointer of the message indication information "MOI_SmsInd_t".
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If MOI has been released.
*/
MAE_Ret SrvMoiSMS_MT_IND(MOI_SmsInd_t *pSmsInd);

/**
* SrvMoiSMS_CB_IND
* @brief    To receive the CB raw data indication and post the CB information to listened AP/Srv
* @param[in]    pCbInd              The pointer of the CB indication information "MOI_CbInd_t".
*/
void SrvMoiSMS_CB_IND(MOI_CbInd_t *pCbInd);

/**
* SrvMoiSMS_SR_IND
* @brief    To receive the SMS status report raw data indication and post this information to listened AP/Srv
* @param[in]    pSrInd              The pointer of the status report indication information "MOI_SrInd_t".
*/
void SrvMoiSMS_SR_IND(MOI_SrInd_t *pSrInd);

/**
* SrvMoiSMS_WapPush_IND
* @brief    To receive the WAP push raw data indication and post this information to listened AP/Srv
* @param[in]    pWapPushInd         The pointer of the WAP push indication information "MOI_SmsInd_t".
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If MOI has been released / Not support SMS-SUBMIT for WAP push.
*/
MAE_Ret SrvMoiSMS_WapPush_IND(MOI_SmsInd_t *pWapPushInd);

/**
* SrvMoiSMS_PortMT_IND
* @brief    To receive the port SMS raw data indication and post this information to listened AP/Srv
* @param[in]    pSmInd                  The pointer of the message indication information "MOI_SmsInd_t".
* @param[in]    nPort                   The message port.
*
* @return MAE_RET_SUCCESS               If successful.
* event :MOI_EVT_PortSmsInd
*/
MAE_Ret SrvMoiSMS_PortMT_IND(MOI_SmsInd_t *pSmInd, u16 nPort);

/**
* SrvMoiRetrvWapPushData
* @brief    To retrieve the WAP push data for CD Kernel
* @param[in]    pSmHdr              The pointer of the message header.
* @param[out]   pWapPushCnt         The pointer of the WAP push raw data except for the WAP push header.
* @param[out]   pWapPushCntLen      The pointer of the WAP push raw data length except for the WAP push header.
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If MOI has been released.
*/
MAE_Ret SrvMoiRetrvWapPushData(SMI_MsgHdr_t *pSmHdr, u8 *pWapPushCnt, u32 *pWapPushCntLen);

/**
* SrvMoiAddSMS.
* @param[in]    pSmsInd                 sms raw data
* @param[in]    bCheckExitPackage
    TRUE: Need to check if exit other package of the same message in the same location
    FALSE: Don't need to check. Using a new message id.
* @param[out]peMsgLoc    message location
* @param[out]pMsgId    message Id
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If MOI has been released.
*
* event : MOI_EVT_SmsInd, or MOI_EVT_TelNoSmsInd
* */
MAE_Ret SrvMoiAddSMS(MOI_SmsInd_t *pSmsInd,
                     boolean bCheckExitPackage,
                     SMI_MsgLocation_e *peMsgLoc,
                     SMI_MsgID_t *pMsgId);

/**
* SrvMoiAppendSMS
* Add a SMS.
* @param[in]    pSmInd      sms raw data
* @param[in]    eMsgLoc     message location
* @param[in]    nMsgId       message Id
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If MOI has been released.
* event : MOI_EVT_SmsInd, or  MOI_EVT_TelNoSmsInd
* */
MAE_Ret SrvMoiAppendSMS(MOI_SmsInd_t *pSmInd, SMI_MsgLocation_e eMsgLoc, SMI_MsgID_t nMsgId);

#endif /* __MMI_SRV_MOI_H__ */
