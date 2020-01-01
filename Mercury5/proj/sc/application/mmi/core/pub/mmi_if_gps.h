/**
 * @file    mmi_if_gps.c
 *
 * @brief   This file implements the functions defined in mmi_if_gps.h 
 *          which are used parse the confirmations from gps driver and send events to gps AP.
 * @author	william.wang@mstarsemi.com
 *
 * @version $Id: mmi_if_gps.c 14013 2008-12-11 16:23:04Z william.wang $
 */

#ifndef __MMI_IF_GPS_H__
#define __MMI_IF_GPS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_gps_msg_parser(IBase* pRecipient, struct vm_msg*pData);
void mmi_gps_common_if(IBase* pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_GPS_H__ */
