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
* @file    srv_resmgr_mml_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MML_TYPES_H__
#define __SRV_RESMGR_MML_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

#include "vm_types.ht"
#include "srv_resmgr_mml_forward.h"

/** @ingroup    MMLayerManager
    @brief      Multimedia capability 1.0\n
                MUST be synced with E2p_stck.ho
*/
struct MmlMultimediaCapability_t_
{
    u32    MccVersion;
    u32    MccReserved[4];
    u32    MccAudioRecording;
    u32    MccAudioPlayback;
    u32    MccVideoRecording;
    u32    MccVideoPlayback;
    u32    MccMaxRomSizeEmu;
};

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MML_TYPES_H__

