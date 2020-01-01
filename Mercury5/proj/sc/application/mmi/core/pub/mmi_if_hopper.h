/**
 * @file    mmi_if_hopper.h
 * @brief   The file handles the Hopper messages
 * @author  eddie.chen
 *
 * @version $Id $
 */

#ifndef __MMI_IF_HOPPER_H__
#define __MMI_IF_HOPPER_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

void mmi_hopper_msg_parser(IBase *pRecipient, struct vm_msg *pData);

#endif /* __MMI_IF_HOPPER_H__ */
