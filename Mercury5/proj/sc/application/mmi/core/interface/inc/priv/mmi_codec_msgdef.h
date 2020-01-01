/**
* @file mmi_codec_msgdef.h
*
*
* @version $Id: mmi_codec_msgdef.h 10228 2008-05-08 09:35:59Z steve.lee $
*
*/
#ifndef __MMI_CODEC_MSGDEF_H__
#define __MMI_CODEC_MSGDEF_H__

#include "vm_types.ht"
#include "mdl_imgcodec_main.h"

typedef struct 
{
	image_Errmsg       RetCode;
	u32                userData;
	u8                *pBuffer;
	u32                bufferLen;
} mmi_CodecMsgBody_t;
#endif /*__MMI_CODEC_MSGDEF_H__*/
