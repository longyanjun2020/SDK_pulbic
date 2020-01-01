/**
 * @file mmi_rfid_util.h
 *
 * $Id: mmi_rfid_util.h 2009-03-25 austin.chou $
 */

#ifndef __MMI_RFID_UTIL_H__
#define __MMI_RFID_UTIL_H__

#include "mae_common_def.h"
#include "mmi_rfid_def.h"
#include "mmi_mae_rfidreader.h"

//for other includes
#include "mmi_rfid_receive.h"
#include "mmi_rfid_upload.h"

#define DEFAULT_TAG_PERMISSION_AMOUNT	(20)

extern PorkGlobe_t	PorkGlobe;
extern BizGlobe_t BizGlobe;

#define HI_BYTE(value)             ( (u8)( (value)>>8 ) )
#define LO_BYTE(value)             ( (u8)( (value) & 0x00FF ) )

u16 mmi_rfid_CRC16(MmiCRCType_e type, u16 len, u8 *buf);
boolean	pork_check_encrytion(void);
void	pork_upload_buf_init(u8 reqType);
u8	pork_upload_buf_add_frame(u8 len, u8 operation, u8 type, u8 *data);
u16	pork_upload_buf_end(void* pOwner);
u16	pork_upload_buf_get_len(void);
u8*	pork_upload_buf_get_ptr(void);
u8	pork_receive_buf_init(void* pOwner);
void	pork_receive_buf_get_header(RcvHeader_t *pHeader);
u8	pork_receive_buf_get_frame(u8 frameId, RcvFrame_t *pFrame);
RtnAction_e pork_check_return_code(void);
void	rfid_mmi_para_init(void *pOwner, boolean bResetInit);
u8	pork_bcd_to_u8(u8 bcd);
u8 pork_u8_to_bcd(u8 binary);
void	pork_key_press_check(void* pOwner);
void	pork_pause_background_upload(void* pOwner);
void	pork_resume_background_upload(void* pOwner);
void	pork_get_server_ip(u8* defaultServer, u16* defaultPort, u8* backupServer);
void	pork_set_randomkey(u8* newKey);
s32	pork_get_idle_time(void);
//u16	pork_GetRandomKey_BufferFilled(void* pOwner);
void	pork_scan_result_notify(boolean bSuccess);
u16	rfid_mmi_encrypt_buf(u8* buf, u16 len);
u16	rfid_mmi_decrypt_buf(u8* buf, u16 len);
u8	pork_band_epc_tran(u8 *pBuf, u8 *pEPCcode);
boolean rfid_mmi_get_random_key(u8 *key);
void	rfid_trace_raw_data(u8 *pData, u16 len);
boolean	pork_is_test_service_on(void);
MAERet_t	rfid_mmi_get_time(u8 *destTimeBuf);
MAERet_t	rfid_mmi_set_time(u8 *destTimeBuf);
u32	pork_get_pedigree_str(u8 *pedigree, u8 *EPC, MAE_WChar *destStr, u8 maxLen);

boolean Biz_Check_UpdateStatus(void);
void Biz_Set_UpdateStatus(boolean bstatus);

u16 Biz_Get_NetWorkStatus(void);
u16 Biz_Get_ServerCode(void);
void	Biz_Set_User_CardData(CardType_et cardType, u8 *EPC, u8 *TID, u8 *UID, u8 *manNumber, u8 *password);

#endif // #ifndef __MMI_RFID_UTIL_H__
