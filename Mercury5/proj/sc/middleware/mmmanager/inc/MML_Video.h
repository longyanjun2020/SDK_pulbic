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
* @file    MML_Video.h
* @version
* @brief
*
*/

#ifndef __MML_VIDEO_H__
#define __MML_VIDEO_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup MMLayerVideo Video
    Video Playback and Recording
    @{
*/
    /** @defgroup MMLayerVideoPlayback Video Playback
        Video Playback
        @{
    */
    /** @} */

    /** @defgroup MMLayerVideoRecording Video Recording
        Video Recording
        @{
    */
    /** @} */

    /** @defgroup MMLayerVideoTelephony Video Telephony
        Video Telephony
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlvideo_types.h" // Lib release stage1's workaround

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MmlErrCode_e MmlVideoNotifyCallbackDispatch
(
    MmlMultimediaGroup_t            *pGroup,
    u32                             nEvent,
    void                            *pNotifyPayload
);
/**
    This sync API is ONLY exported to ResMgr to get the capability from middleware.ResMgr SHOULD
    not further exported to upper layer.In normal case, AP should get the capability via command
    with ID "MML_UCID_VIDEO_GET_PLAYBACK_CAPABILITY" and response(Stephen Wong 2011 07 18).
*/
void MmlVideoGetVideoCapability
(
    MmlVideoPlaybackCapability_t *pCapability
);
#ifdef __cplusplus
}
#endif

#endif //__MML_VIDEO_H__
