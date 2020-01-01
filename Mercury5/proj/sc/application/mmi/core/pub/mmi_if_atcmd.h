/**
 * @file    mmi_if_atcmd.h
 *
 * @brief   This file implements the parser of atcmd message.
 * @author	steve.lee@mstarsemi.com	
 *
 * @version $Id: mmi_if_atcmd.h 38442 2009-08-24 09:24:24Z steve.lee $
 */
 
 
#ifndef __MMI_IF_ATCMD_H__
#define __MMI_IF_ATCMD_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

__SLDPM_FREE__ void mmi_atcmd_msg_parser(IBase* pRecipient, struct vm_msg *pMsg);

#endif /* __MMI_IF_ATCMD_H__ */

