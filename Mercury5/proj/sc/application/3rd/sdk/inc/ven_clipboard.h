/**
 *
 * @file    ven_clipboard.h
 * @brief   This file defines the clipboard related request vendor API
 *
 * @author  Jorena.Ku
 * @version $Id: ven_clipboard.h 15719 2008-10-30 07:39:51Z jorena.ku $
 *
 */
#ifndef __VEN_CLIPBOARD_DEFINE_H_
#define __VEN_CLIPBOARD_DEFINE_H_


#include "ven_sdk.h"

enum
{
    VEN_CLIPBOARD_RET_SUCCESS           = 0, ///< operation completed successfully
    VEN_CLIPBOARD_RET_BAD_PARAM         = 1, ///< invalid input parameters
    VEN_CLIPBOARD_RET_FAILED            = 2, ///< WHAT? every code here is failed
    VEN_CLIPBOARD_RET_OUT_OF_MEMORY     = 3, ///< memory is not enough to complete the operation
};
typedef u32 ven_clipboard_ret_t;

enum
{
    VEN_CLIPBOARD_DISABLED = 0,
    VEN_CLIPBOARD_ENABLED
};
typedef u8 ven_clipboard_setting_t;

ven_clipboard_ret_t ven_clipboard_getSetting(ven_clipboard_setting_t *pSetting, ven_req_data_t *ptVenReq);
ven_clipboard_ret_t ven_clipboard_copyText(u16* pStr, u32 nStrLen, ven_req_data_t *ptVenReq);
ven_clipboard_ret_t ven_clipboard_getCopyText(u16** ppStr, u32 *pnStrLen, ven_req_data_t *ptVenReq);
ven_clipboard_ret_t ven_clipboard_hasCopyText(bool* pHasCopyText, ven_req_data_t *ptVenReq);



#endif //__VEN_CLIPBOARD_DEFINE_H_
