/**
* @file mmi_media_msgdef.h
*
*
* @version $Id: mmi_media_msgdef.h 36778 2009-07-29 10:50:17Z stone.shih $
*
*/
#ifndef __MMI_MEDIA_MSGDEF_H__
#define __MMI_MEDIA_MSGDEF_H__


#include "mmi_mae_common_def.h"
#include "ABL_Aud.h"
#include "ABL_Vdo.h"
#include "MediaRspItf.h"

typedef enum
{
	FunctionCB,
	NotificationCB
} MAEMediaMsgType_t;


typedef struct 
{
	MAEMediaMsgType_t MsgType;
	s32 errCode;
	union {
		ABL_AudInfo_t *pAudioInfo;
		ABL_AudNotifyInfo_t  *pAudNotificayInfo;
		ABL_VdoInfo_t *pVideoInfo;
		ABL_VdoNotifyInfo_t  *pVdoNotificayInfo;
		MediaInterruptInfo_t *pResMgrNotifyInfo;
		u8*  pFileName;
	} msgInfo;
	u32 userData;
} mmi_mediaMsgBody_t ;
#endif /*__MMI_MEDIA_MSGDEF_H__*/
