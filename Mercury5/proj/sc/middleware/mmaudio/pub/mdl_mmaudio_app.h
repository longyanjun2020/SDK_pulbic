////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012  MStar Semiconductor, Inc.
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
* @file    mdl_aud_app.h
* @version
* @brief   API for Audio Post Process 
*
*/

#ifndef __MDL_AUD_APP_H__
#define __MDL_AUD_APP_H__

/*=============================================================*/
// Include files
/*=============================================================*/


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/** \addtogroup AudMdlApi
* @{
*/


typedef enum
{
    MDL_AudioPP_OK = 0,
    MDL_AudioPP_TASK_CRATE_FAIL,
    MDL_AudioPP_TASK_DESTORY_FAIL,

} MdlAudioPPErrCode_e;



/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/


MdlAudioPPErrCode_e MdlAudioPPTaskCreate(void);

MdlAudioPPErrCode_e MdlAudioPPTaskDestory(void);

void MdlAudioPPSendStartMsg(u16 MbxSrc);

void MdlAudioPPSendStopMsg(u16 MbxSrc);

u32 MdlAudioPPQueryLatencyMs(void);



/** @}*/

#endif //__MDL_AUD_PUB_API_H__

