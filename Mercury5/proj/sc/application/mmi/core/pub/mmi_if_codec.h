/**
 * @file    mmi_if_gss.h
 *
 * @brief   This file implements the parser of codec message.
 * @author	steve.lee@mstarsemi.com	
 *
 * @version $Id: mmi_if_codec.h 28068 2009-04-10 15:47:23Z zinc.chen $
 */
 
 
#ifndef __MMI_IF_GSS_H__
#define __MMI_IF_GSS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_codec_dec_cnf_if(IBase* pRecipient, struct vm_msg *pMsg);
void mmi_codec_rotate_cnf_if(IBase* pRecipient, struct vm_msg *pMsg);
void mmi_codec_msg_parser(IBase* pRecipient, struct vm_msg *pMsg);

#endif /* __MMI_IF_RTC_H__ */
