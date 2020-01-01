////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef DRM_H
#define DRM_H

typedef enum MMP_KEY_e_
{
    KEY_KMV = 0,
    KEY_RMVB,
} MMP_KEY_e;

void KMV_GetE2P(uint8_t *KMVE2P);
int MMP_GetKey(uint8_t *key_ptr, MMP_KEY_e key_index);

#endif /* DRM_H */
