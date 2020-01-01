/**
* @file mmi_cb_rfidreader.h
*
*
* @version $Id: mmi_cb_rfidreader.h 14013 2008-09-10 14:04:04Z allan.hsu $
*/

#ifdef __RFID__

#ifndef __MMI_CB_RFIDREADER_H__
#define __MMI_CB_RFIDREADER_H__

#include "mmi_mae_rfidreader.h"
#include "srv_resmgr_mmlrfid_types.h"

// Callback functions
#if defined(__SUPPORT_ABL_INTERFACE__)
void RfidReader_Resp_Cb(u16 uSenderId, u32 userValue, MmlRfidResult_e eErrCode, MmlRfidResponse_t *pMML_RfidInfo);

#ifdef __SUPPORT_JSR257__
void RfidReader_Listener_Ind_Cb(u16 uSenderId, u32 uUserValue, MmlRfidNotify_t *pNotifyInfo);
#endif	/* __SUPPORT_JSR257__ */

#else // defined(__SUPPORT_ABL_INTERFACE__)
void RfidReader_Resp_Cb(u16 senderID, u32 userValue, esl_RFID_ErrCode_e errCode, esl_RFID_Info_t *pRFIDInfo);

#ifdef __SUPPORT_JSR257__
void RfidReader_Listener_Ind_Cb(u16 senderID, u32 userValue, esl_RFID_ErrCode_e errCode, esl_RFID_Info_t *pRFIDInfo);
#endif	/* __SUPPORT_JSR257__ */

#endif //defined(__SUPPORT_ABL_INTERFACE__)


#endif // __MMI_CB_RFIDREADER_H__

#endif	//__RFID__
