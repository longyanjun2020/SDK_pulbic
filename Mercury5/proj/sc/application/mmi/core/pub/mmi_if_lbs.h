/**
 * @file    mmi_if_lbs.c
 *
 * @brief   This file implements the functions defined in mmi_if_lbs.h 
 *          which are used parse the confirmations from lbs task and send events to mapview AP.
 * @author	william.wang@mstarsemi.com
 *
 * @version $Id: mmi_if_lbs.c 14013 2008-12-11 16:23:04Z william.wang $
 */

#ifdef __MAP_MMI_LBS__
#ifndef __MMI_IF_LBS_H__
#define __MMI_IF_LBS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_lbs_msg_parser(IBase* pRecipient, vm_msg_t *pData);
void mmi_lbs_common_if(IBase* pRecipient, vm_msg_t *pData);

#endif /* __MMI_IF_LBS_H__ */
#endif /* __MAP_MMI_LBS__ */
