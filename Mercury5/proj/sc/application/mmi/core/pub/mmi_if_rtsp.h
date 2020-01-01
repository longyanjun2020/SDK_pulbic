/**
 * @file    mmi_if_rtsp.h
 * @brief   The file handles the rtsp event with rtsp task
 *
 */
#ifndef __MMI_IF_RTSP_H__
#define __MMI_IF_RTSP_H__


#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

typedef struct
{
    void *pData;
    u32 nDataSize;
	u32 nDataPos;
}RtspDownloadDataInd_t;

void mmi_rtsp_user_extend_rsp_if(IBase *pRecipient, vm_msg_t *pMessage);
void mmi_rtsp_msg_parser(IBase* pRecipient, vm_msg_t *pData);


#endif /* __MMI_IF_RTSP_H__ */
