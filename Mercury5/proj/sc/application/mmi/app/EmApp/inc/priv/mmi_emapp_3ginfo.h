////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_emapp_3ginfo.h
*
*/
#ifndef __MMI_EMAPP_3GINFO_H__
#define __MMI_EMAPP_3GINFO_H__

#ifdef __3G_RIL_MMI__

/*----- struct for input window --------------------------------------------------*/
enum
{
    EM_3G_ENG_VIEW_BEGIN = APP_WDG_START,
    EM_3G_ENG_TEXT_1,
    EM_3G_ENG_TEXT_2,
    EM_3G_ENG_INPUT_1,
    EM_3G_ENG_INPUT_2
} Em3gCellLockInputView_e;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pTextWdg1;
    IWidget *pTextWdg2;
    IWidget *pInputWdg1;
    IWidget *pInputWdg2;    
} EmApp3gCellLockWndWdgList_t;

/*----- function prototypes --------------------------------------------------*/
u32 em_request_3g_modem_imei(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_3g_modem_imei_rsp(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_3g_modem_version         (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_3g_modem_version_rsp   (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_request_3g_modem_imsi(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

u32 em_request_3g_modem_unlock_cell(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_3g_modem_unlock_cell_rsp(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_3g_modem_unlock_ARFCN(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_3g_modem_unlock_ARFCN_rsp(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_3g_modem_full_freq_scan(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_3g_modem_full_freq_scan_rsp(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_base_software_version(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_request_base_software_rsp(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_3g_custom_command(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

u32 em_request_3g_silent_reboot(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_3g_silent_reboot_enter(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

u32 em_set_lockcell(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_set_sd_limit(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

#if defined (__UPGRADE_GENIE_OVER_SHMCONN__)    // this is for update TTPCom modem GENIE log filter
u32 em_set_genie_filter(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
#endif // __UPGRADE_GENIE_OVER_SHMCONN__

u32 em_request_3g_antf_trace_enter(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_3g_dbb_antf_off(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

#endif //__3G_RIL_MMI__


#endif //__MMI_EMAPP_3GINFO_H__
