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
* @file    MML_CommTask.h
* @version
* @brief
*
*/

#ifndef __MML_COMMTASK_H__
#define __MML_COMMTASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "MML_Manager.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerManager
    @brief      Common task message types
*/
typedef union
{
    MmlAudioUCParam_t     tAudioUCParam;     ///< Audio use case parameters
    MmlVideoUCParam_t     tVideoUCParam;     ///< Video use case parameters
    MmlImageUCParam_t     tImageUCParam;     ///< Image use case parameters
    MmlGameUCParam_t      tGameUCParam;      ///< Game use case parameters
    MmlUsbUCParam_t       tUsbUCParam;       ///< Usb use case parameters
    MmlCameraUCParam_t    tCameraUCParam;    ///< Camera use case parameters
    MmlTvUCParam_t        tTvUCParam;        ///< Tv use case parameters
    MmlRadioUCParam_t     tRadioUCParam;     ///< Radio use case parameters
    MmlGpsUCParam_t       tGpsUCParam;       ///< Gps use case parameters
    MmlWlanUCParam_t      tWlanUCParam;      ///< Wlan use case parameters
    MmlVideoSdkUCParam_t     tVideoSdkUCParam;     ///< Video SDK use case parameters
    MmlRfidUCParam_t      tRfidUCParam;      ///< Rfid use case parameters
} vm_msgBody_t;

#include "vm_msgt.ht"

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
void MdwCommTaskInit(void);
void MdwCommTaskParseMsg(void *pMessage);

#ifdef __cplusplus
}
#endif

#endif //__MML_COMMTASK_H__

