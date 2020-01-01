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
* @file mmi_emapp_voiceinfo.h
*
* @version $Id:$
*/

#ifndef __MMI_EMAPP_VOICEINFO_H__
#define __MMI_EMAPP_VOICEINFO_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/
#ifdef __EM_AUDIO__
u32 em_request_audio_input_gain(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_audio_input_gain(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
EmAppResRet_e em_response_audio_mic_gain(EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);

u32 em_request_audio_mic_gain(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_tone_generator(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_audio_radio_menu(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_audio_set_radio_menu(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);

#ifdef __APP_MMI_EM_AUDIO_APPTOSD__
u32 em_request_audio_saveapptosd(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_request_audio_loadappfromsd(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#endif

u32 em_exit_audio_tone_generator(EmAppData_t *pThis, u32 param1);
u32 em_request_get_amp_offset_gain(EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
#else
u32 em_request_audio_input_gain                 (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_response_audio_input_gain      (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);

u32 em_request_audio_output_gain                (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_response_audio_output_gain     (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);

u32 em_request_audio_command                    (EmAppData_t *pThis, u32 param1, u32 param2,u32 Output);
EmAppResRet_e em_response_audio_command         (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo,u32 Output);

u32 em_request_receiver_test                    (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
u32 em_exit_receiver_test                       (EmAppData_t *pThis, u32 param1);
#endif

#endif//__MMI_EMAPP_VOICEINFO_H__
