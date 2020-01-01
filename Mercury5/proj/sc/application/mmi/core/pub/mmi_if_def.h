/**
 * @file    mmi_if_def.h
 * @brief   The document defines default structures for system message parsers.
 * @author  kenny.wu@mstarsemi.com
 * 
 * @version $Id: mmi_if_def.h 26571 2009-03-24 14:25:53Z steve.lee $
 */

#ifndef __MMI_IF_DEF_H__
#define __MMI_IF_DEF_H__

#include "mmi_mae_msgdispatcher.h"

#define MMI_MSG_HANDLER(_MessageId_, _Handler_) {_MessageId_, _Handler_}
#define MMI_MSG_ID_OFFSET(_MessageId_) ((u16)_MessageId_ & 0x00FF)
#define MMI_GROUP_MSG_ID_DIFF_WITH_BASE_OFFSET(_MessageId_) ((u16)(_MessageId_-VM_RIL_BASE) & 0x00FF)

#endif /* __MMI_IF_DEF_H__ */
