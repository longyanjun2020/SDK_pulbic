/**
 * @file    mmi_if_tts.h
 * @brief   This file defines the interface to parse messages from tts task.
 * @author  mstarsemi.com
 *
 */
#ifndef __MMI_IF_TTS_H__
#define __MMI_IF_TTS_H__

#ifdef __TTS__

#include "mmi_mae_common_def.h"
#include "tts_itf.h"

void mmi_tts_msg_parser(IBase* pRecipient, vm_msg_t *pData);
void mmi_tts_user_extend_msg_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __TTS__ */

#endif /* __MMI_IF_TTS_H__ */
