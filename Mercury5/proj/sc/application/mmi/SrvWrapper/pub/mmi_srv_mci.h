/**
* @file mmi_srv_mci.h
*
*/
#ifndef __MMI_SRV_MCI_H__
#define __MMI_SRV_MCI_H__



#include "mmi_srv_client_commondefine.h"
#include "mmi_messagecontentsrv.h"


/** SrvMciOpenMessage
* @brief    To read a SMS message of the phone
*           [Note]The data will alloc and copy to ppMsgCnt; Remember to Free ppMsgCnt by AP self
*           [Note]The data will create ppObjCnt in service; Remember to release ppObjCnt by AP self
*
* @param[in]    nMsgId              The message id.
* @param[out]   ppMsgCnt            The pointer address of the message text content.
* @param[out]   ppObjCnt            The pointer address of the object vector model in the message content.
* @param[out]   ppExtObjData        The pointer address of the message extended object data.
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If shell wants to terminate service, ignore request.
*
* +pRequester for vecotrmodel creating
*/
MAE_Ret SrvMciOpenMessage(u32 nMsgId, u16 **ppMsgCnt, IVectorModel **ppObjCnt, u8 **ppExtObjData);

/**
* SrvMciSaveEdtMessageSync
* @brief    To save a edited SMS
* @param[in]    pMsgCnt             The pointer of the message text content.
* @param[in]    nDataLen            The data length of the message content.
* @param[out]   pSmsHdr             The pointer of the message header.
* @param[in]    pMsgRecipLst        The pointer of the message recipient list information.
* @param[in]    eDualMode           The id of the SIM module
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvMciSaveEdtMessageSync(u16 *pMsgCnt,
                                 u16 nDataLen,
                                 SMI_MsgHdr_t *pSmsHdr,
                                 SMI_SmEncoding_t encoding,
                                 u16 nPort,
                                 mmiGsmLockShiftTable_e tLockShift,
                                 mmiGsmSingleShiftTable_e tSingleShift,
                                 SMS_MsgRecipLst *pMsgRecipLst,
                                 MAE_DualMode_t eDualMode);

/**
* SrvMciGetMessageSmscInfo
* @brief    To get the SMSC address of the SIM

* @param[out]   pMsgSmscInfo        The pointer of the SIM SMSC infomation.
* @param[in]    eDualMode           The id of the SIM module
*
* @return MAE_RET_SUCCESS           If successful.
*/
MAE_Ret SrvMciGetMessageSmscInfo(SMI_MsgSmscInfo_t *pMsgSmscInfo, MAE_DualMode_t eDualMode);

/**
* SrvMciGetMsgRecipAddr
* @brief    To get the recipient address of the SIM

* @param[in]    nMsgId              The id of the message.
* @param[out]   pMsgRecipLst        The pointer of the message recipient information
*
* @return MAE_RET_SUCCESS           If successful.
*/
MAE_Ret SrvMciGetMsgRecipAddr(u16 nMsgId, SMS_MsgRecipLst *pMsgRecipLst);

/**
* SrvMciGetMsgLstInfo
* @brief    To get the message list information for message center list.
*           [Note]The memo string will alloc and copy to ppMemo; Remember to Free ppMemo by AP self
*
* @param[in]    nMsgId          The id of the message.
* @param[out]   pRecipAddr          The pointer of the first sender/recipient information
* @param[out]   bMultiRecip         If there are more than one recipient address
* @param[out]   ppMemo              The pointer of the Memo string
* @param[out]   pbMoreMemo          If the output memo string has been cut
* @param[out]   pu8IMSI             If the output imsi
*
* @return MAE_RET_SUCCESS           If successful.
*/
MAE_Ret SrvMciGetMsgLstInfo(u16 nMsgId,
                            SMS_MsgRecipAddr *pRecipAddr,
                            boolean *pbMultiRecip,
                            MAE_WChar **ppMemo,
                            boolean *pbMoreMemo,
                            u8 *pu8IMSI);

/**
* SrvMciModifyMsgSimIndexInfo
* @brief    To update the SIM index information for the SIM SMS.

* @param[in]    nMsgId              The id of the message.
* @param[in]    pSimIndexInfo       The pointer of the message's SIM index information
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM         If nMsgId < 0.
*/
MAE_Ret SrvMciModifyMsgSimIndexInfo(u16 nMsgId, u8 *p8SimIndexInfo);

/**
* SrvMciOpenMessageFromSimMsgBuf
* @brief    To decoding a SIM SMS message
*           [Note]The data will alloc and copy to ppu16MsgCnt; Remember to Free ppu16MsgCnt by AP self
*           [Note]The data will create ppObjCnt in service; Remember to release ppObjCnt by AP self
*
* @param[out]   ppu16MsgCnt             The pointer address of the message text content.
* @param[out]   ppObjCnt                The pointer address of the object vector model in the message content.
* @param[in]    pSimMsgRowData          The pointer of the SIM message raw data.
* @param[in]    nSimMsgRowDataLen       The data length of the SIM message raw data.
* @param[out]   ppExtObjData        The pointer address of the message extended object data.
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If shell wants to terminate service, ignore request.
*
* +pRequestre : for vectormoel creating
*/
MAE_Ret SrvMciOpenMessageFromSimMsgBuf(u16 **ppu16MsgCnt,
                                       IVectorModel **ppObjCnt,
                                       u8 *pSimMsgRowData,
                                       u32 nSimMsgRowDataLen,
                                       u8 **ppExtObjData);

/**
* SrvMciModifyMsgResentPduIdx
* @brief    To modify the resent PDU index of the SMS

* @param[in]    nMsgId                  The id of the message.
* @param[in]    nResentPduIdx           The PDU index of the message
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM             If nMsgId < 0.
*/
MAE_Ret SrvMciModifyMsgResentPduIdx(u16 nMsgId, u8 nResentPduIdx);

/**
* SrvMciGetMsgResentPduIdx
* @brief    To get the resent PDU index of the SMS
*
* @param[in]    nMsgId              The id of the message.
* @param[out]   pResentPduIdx       The PDU index pointer of the message
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM             If nMsgId < 0.
*/
MAE_Ret SrvMciGetMsgResentPduIdx(u16 nMsgId, u8 *pResentPduIdx);

/**
* SrvMciGetMsgPduNum
* @brief    To get the PDU max number of the SMS
*
* @param[in]    nMsgId              The id of the message.
* @param[out]   pMsgTotalPduNum     The PDU max number pointer of the message
* @param[out]   pMsgPartNum         The number pointer of the message
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM         If nMsgId < 0.
*/
MAE_Ret SrvMciGetMsgPduNum(u16 nMsgId, u8 *pMsgTotalPduNum, u8 *pMsgPartNum);

/**
* mmi_MCI_BackupMessage
* @brief    To backup the message to the backup tool
*           [Note]The data will alloc and copy to ppMsgCnt; Remember to Free ppMsgCnt by AP self
*
* @param[in]    nMsgId              The message id.
* @param[out]   pSmHdrInfo          The pointer of the message pdu header information.
* @param[out]   pMsgRecipLst        The pointer of the message recipient information.
* @param[out]   ppMsgCnt            The pointer address of the message text content.
*
* @return MAE_RET_SUCCESS           If successful.
* @return MAE_RET_NOT_SUPPORTED     If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM         If nMsgId < 0.
*/
MAE_Ret SrvMciBackupMessage(MCI_BackupSMS_t *pBackupData);


/**
* SrvMciBackupMessageFromSimMsgBuf
* @brief    To backup the SIM message buffer to the backup tool
*           [Note]The data will alloc and copy to ppMsgCnt; Remember to Free ppMsgCnt by AP self
*
* @param[out]   pSmHdrInfo              The pointer of the message pdu header information.
* @param[out]   ppMsgCnt                The pointer address of the message text content.
* @param[in]    pSimMsgRowData          The pointer of the SIM message raw data.
* @param[in]    nSimMsgRowDataLen       The data length of the SIM message raw data.
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvMciBackupMessageFromSimMsgBuf(MCI_BackupSMS_t *pBackupSIMData,
                                         u8 *pSimMsgRowData,
                                         u32 nSimMsgRowDataLen);

/**
* SrvMciOpenPortMessage
* @brief    To read a port message of the phone
*           [Note]The data will alloc and copy to ppMsgCnt; Remember to Free ppMsgCnt by AP self
*
* @param[in]    nMsgId                  The message id.
* @param[out]   ppMsgCnt                The pointer address of the message text content.
* @param[out]   pEncoding               The pointer of the message encoding type.
*
* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_NOT_SUPPORTED         If shell wants to terminate service, ignore request.
* @return MAE_RET_BAD_PARAM             If nMsgId < 0.
*/
MAE_Ret SrvMciOpenPortMessage(u16 nMsgId, u16 **ppMsgCnt, SMI_SmEncoding_t *pEncoding);


/**
 * SrvMciModifyIMSI
* @brief    modify IMSI for phone SMS
*
* @param[in]    nMsgId                  The id of the message.
* @param[in]    pIMSI                   The pointer of the imsi
* @param[in]    nIMSILen                The length of the imsi

* @return MAE_RET_SUCCESS               If successful.
* @return MAE_RET_FAILED                If an error happen.
*/
MAE_Ret SrvMciModifyIMSI(u16 nMsgId, u8 *pIMSI, u16 nIMSILen);

MAE_Ret SrvMciBackupPhoneSMS(MCI_VenBackupSMS_t *pBackupData);
MAE_Ret SrvMciBackupSIMSMS(MCI_VenBackupSMS_t *pBackupData, u8 *pSimMsgRowData, u32 nSimMsgRowDataLen);
MAE_Ret SrvMciRestoreSMS(MCI_VenBackupSMS_t *pBackupData);
#endif /* __MMI_SRV_MCI_H__ */
