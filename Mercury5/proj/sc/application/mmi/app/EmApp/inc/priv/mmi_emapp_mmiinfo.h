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
* @file mmi_emapp_mmiinfo.h
*
* @version $Id: mmi_em_mmiinfo.h 25438 2009-03-11 13:59:32Z sho.ding $
*/
#ifndef __MMI_EMAPP_MMIINFO_H__
#define __MMI_EMAPP_MMIINFO_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define PC_RAI_HEADER_LEN 6
#define POWER_ON_OFF_CAUSE_BUFFER (10240)
/*=============================================================*/
// Global function definition
/*=============================================================*/
u32 em_request_software_version               (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_user_software_version          (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_device_info                    (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_uart_share                     (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_track_patch_mechanism          (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_imei                           (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_standby                        (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_antf                           (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_antf_radio_menu                (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_antf_set_radio_menu            (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_dump_rai_info                  (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_response_dump_rai            (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
u32 em_exit_dump_rai                          (EmAppData_t *pThis, u32 param1);
u32 em_request_memory_status_info             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_power_onoff_casuse             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

u32 em_request_query_auto_test_status         (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_query_station_status           (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_debug_info                     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_rssi_smooth_algorithm_onoff    (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

#ifdef __VT_3G324M__ //VT engineer test mode
u32 em_request_vt_log (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
#endif

#ifdef __FEATURE_POWER_CONSUMPTION_LOG__
u32 em_request_power_consumption_log    (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
#endif//__FEATURE_POWER_CONSUMPTION_LOG__

EmAppResRet_e em_response_sms_crash_no  (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
EmAppResRet_e em_response_query_auto_test_status(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
u32 em_request_sms_crash_no             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);

u32 em_request_query_library_version    (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

#define PC_RAI_HEADER_LEN 6
#define POWER_ON_OFF_CAUSE_BUFFER (10240)

#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI__)
u32 em_request_send_mms_settings        (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_send_mms_settings(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_send_mms_settings           (EmAppData_t *pThis, u32 param1);
#endif

#ifdef __SDK_MMI_VENDOR_ENTRY__
#ifdef __SDK_MMI_TEST__
u32 em_request_sdk_v2_test              (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#else
u32 em_request_launch_vendor            (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif /* __SDK_MMI_TEST__ */
#endif /* __SDK_MMI_VENDOR_ENTRY__ */

#ifdef __WAP_MMI__
u32 em_request_wap_test                 (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif /* __WAP_MMI__ */


#ifdef __JAVA_MMI__
u32 em_request_java_test                (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif /* __JAVA_MMI__ */


#ifdef __WAP_MMI_CDWAP__
u32 em_request_view_httpheader(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_view_httpheader(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_request_edit_useragent(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_edit_useragent(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif /* __WAP_MMI_CDWAP__ */
#ifdef __ENABLE_EGPRS_STATS__
u32 em_request_EgprsStatFlush(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif
u32 em_request_new_auto_test_enable(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_new_auto_test_disable(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#ifdef __SUPPORT_HIDDEN_PARTITION__
u32 em_request_hidden_partition_enable(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_hidden_partition_disable(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif
#ifdef __STREAMING_MODULE__
u32 em_request_video_stream_load(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#ifdef __SUPPORT_HTTP_MEMORY_STREAMING__
u32 em_request_video_stream_mode(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_video_select_mode(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif
u32 em_request_video_stream_edit(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_video_stream_edit(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_video_stream_edit(EmAppData_t *pThis, u32 param1);
#ifdef __RTSP_STREAMING__
u32 em_request_rtsp_mdlsim_play(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_rtsp_mdlsim_play(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_rtsp_mdlsim_play(EmAppData_t *pThis, u32 param1);
#endif //__RTSP_STREAMING__
#endif
u32 em_request_turn_on_off_ramdump(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

u32 em_request_IQ_dump_filter_setting(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_turn_on_off_IQ_dump(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#ifdef __NOSIM_CAMP_ON_TEST_NETWORK__
u32 em_prefer_network_radio_menu(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_turn_on_off_prefer_network(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif
#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__
u32 em_request_get_high_speed_task(EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
#endif

#endif//__MMI_EMAPP_MMIINFO_H__

