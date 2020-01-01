#ifndef __MAE_GSS_CB_H__
#define __MAE_GSS_CB_H__
#include "mmi_mae_shell.h"
#include "mmi_mae_common_def.h"
#include "vm_msgof.hc"
#include "ABL_Gss.h"

typedef struct
{
	IBase *pRecipent;
	ABL_GssInfo_t errCode;
	u8 *pOutBuf;
	u32 nBufSize;
}MMICodecEncodeCb_t;


void mmi_codec_dec_cb(u16 senderID, u32 userValue, ABL_GssErrCode_e status, ABL_GssInfoExt_t *pGssInfo);
void mmi_codec_rotate_cb(u16 senderID, u32 userValue, ABL_GssErrCode_e errCode, ABL_GssInfo_t *pGssInfo);
void mmi_codec_encode_cb(u16 senderID, u32 userValue, ABL_GssErrCode_e errCode, ABL_GssInfo_t *pGssInfo);

#endif /* __MAE_GSS_CB_H__ */

