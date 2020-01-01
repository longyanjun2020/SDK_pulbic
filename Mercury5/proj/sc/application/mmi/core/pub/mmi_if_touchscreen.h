/**
* @file    mmi_if_touchscreen.h
* @brief   The file handles the touch screen events
*
* @version $Id: mmi_if_touchscreen.h 28068 2009-04-10 15:47:23Z zinc.chen $
*/
#ifndef __MMI_IF_TOUCHSCREEN_H__
#define __MMI_IF_TOUCHSCREEN_H__

#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_if_def.h"

void mmi_touchscreen_msg_parser(IBase* pRecipient, struct vm_msg *pData);

boolean mmi_ts_coresrv_hook_msg_parser(IBase *pRecipient, struct vm_msg *pMessage);

#ifdef  __TOUCH_SCREEN_FWUPDATE_MMI__
typedef enum
{
    MMI_TOUCH_SCREEN_FW_UPDATE_SUCCESS,
    MMI_TOUCH_SCREEN_FW_UPDATE_FAIL,
    MMI_TOUCH_SCREEN_FW_UPDATE_START,
    MMI_TOUCH_SCREEN_FW_UPDATE_DATA,
    MMI_TOUCH_SCREEN_FW_UPDATE_END,
    MMI_TOUCH_SCREEN_FW_UPDATE_ERASE_FAIL,
    MMI_TOUCH_SCREEN_FW_UPDATE_WRITE_FAIL,
    MMI_TOUCH_SCREEN_FW_UPDATE_VERIFY_FAIL,
    MMI_TOUCH_SCREEN_FW_UPDATE_INVALID_FIRMWARE,
    MMI_TOUCH_SCREEN_FW_UPDATE_INVALID_FIRMWARE_VERSION,
}MmiTsFwUpdate_e;

typedef void (*fwupdateCB)(void* pRecipient, u32 nTsRet, u16 nFirmwarId);
void mmi_ts_fwupdate_req( u8 *data, u16 size, fwupdateCB CB);
void mmi_touchscreen_msg_parser_for_em(IBase *pRecipient, struct vm_msg *pData);
#endif

#endif //__TOUCH_SCREEN_MMI__
#endif // __MMI_IF_TOUCHSCREEN_H__
