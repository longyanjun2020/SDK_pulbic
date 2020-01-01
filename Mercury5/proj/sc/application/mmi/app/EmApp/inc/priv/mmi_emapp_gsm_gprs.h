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
* @file mmi_emapp_gsm_gprs.h
*
* @version $Id: mmi_em_gsm_gprs.h 15895 2008-11-04 15:17:49Z eric.chen $
*/

#ifndef __MMI_EMAPP_GSM_GPRS_H__
#define __MMI_EMAPP_GSM_GPRS_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_emapp_priv.h"

//Request
u32 em_request_gsmoff                  (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_gprs_attach             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_gprs_detach             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_apn              (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_pdp_addr         (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosreq_prece     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosreq_delay     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosreq_relia     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosreq_peak      (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosreq_mean      (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosmin_prece     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosmin_delay     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosmin_relia     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosmin_peak      (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qosmin_mean      (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_send_datalen     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_send_num_repeat  (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_class                   (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
// u32 em_request_class_cgprs             (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//
// u32 em_request_class_cgsm               (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_gprs_state              (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_send_reset       (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//Sync
u32 em_request_config_pdp_type         (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//Sync
u32 em_request_config_dcomp            (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//Sync
u32 em_request_config_hcomp            (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//Sync
u32 em_request_config_addpdpctx        (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
u32 em_request_config_qos_reset        (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//ASync
u32 em_request_pdp_act                 (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//ASync
u32 em_request_config_qos_send_cmd     (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//ASync
u32 em_request_setband                 (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);//ASync
u32 em_request_query_audio_setting     (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);//ASync
u32 em_request_set_audio_setting       (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);//ASync

u32 em_request_wgsend                   (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);//ASync.
#ifdef __FT_AUTO_TEST__
u32 em_request_ft_auto_test_run_test	(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_ft_auto_test_enter_number(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif


//Response
EmAppResRet_e em_response_gsmoff                 (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_gprs_attach            (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_gprs_detach            (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_apn             (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_pdp_addr        (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosreq_prece    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosreq_delay    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosreq_relia    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosreq_peak     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosreq_mean     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosmin_prece    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosmin_delay    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosmin_relia    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosmin_peak     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_qosmin_mean     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_send_datalen    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_config_send_num_repeat (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_class                  (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
EmAppResRet_e em_response_gprs_state             (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
EmAppResRet_e em_response_config_addpdpctx       (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);
EmAppResRet_e em_response_config_qos_reset       (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);//ASync
EmAppResRet_e em_response_pdp_act                (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);//ASync
EmAppResRet_e em_response_config_qos_send_cmd    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);//ASync
EmAppResRet_e em_response_setband                (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);//ASync
EmAppResRet_e em_response_query_audio_setting    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);//ASync
EmAppResRet_e em_response_set_audio_setting      (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);//ASync
EmAppResRet_e em_response_wgsend                 (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);//ASync
#ifdef __FT_AUTO_TEST__
EmAppResRet_e em_response_ft_auto_test_enter_number(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
#endif

//Exit
u32 em_exit_gsmoff                  (EmAppData_t *pThis, u32);
u32 em_exit_gprs_attach             (EmAppData_t *pThis, u32);
u32 em_exit_gprs_detach             (EmAppData_t *pThis, u32);
u32 em_exit_class                   (EmAppData_t *pThis, u32);
u32 em_exit_gprs_state              (EmAppData_t *pThis, u32);
u32 em_exit_config_addpdpctx        (EmAppData_t *pThis, u32);
u32 em_exit_config_qos_reset        (EmAppData_t *pThis, u32);//ASync
u32 em_exit_pdp_act                 (EmAppData_t *pThis, u32);//ASync
u32 em_exit_config_qos_send_cmd     (EmAppData_t *pThis, u32);//ASync
u32 em_exit_setband                 (EmAppData_t *pThis, u32);//ASync
u32 em_exit_query_audio_setting     (EmAppData_t *pThis, u32);//ASync
u32 em_exit_set_audio_setting       (EmAppData_t *pThis, u32);//ASync
u32 em_exit_wgsend                  (EmAppData_t *pThis, u32);//ASync

#endif//__MMI_EMAPP_GSM_GPRS_H__


