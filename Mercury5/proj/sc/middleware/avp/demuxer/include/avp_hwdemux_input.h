////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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


#ifndef HWDEMUX_INPUT_H
#define HWDEMUX_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  HWDemux_Init(const void *pArg);
int HWDemux_GetStreamingData(void *hdl, char *base);
void HWDemux_DeInit(void);
void HWDemux_Start(void);
void HWDemux_Stop(void);
void HWDemux_IOSeek(int offset);
int  HWDemux_GetExtraRbufSize(void);

int HWDemux_SetService(void *pPayload, uint8_t payloadLen);
int HWDemux_SetServiceProvider(void *pPayload, uint8_t payloadLen);
int HWDemux_ScanFrequency(void *pPayload, uint8_t payloadLen);

int HWDemux_GetSignalStrength(void);
int HWDemux_GetSignalQuality(void);
int HWDemux_GetLockStatus(void);

int streaming_hwdemux_input_plugin(void);
int streamingapp_hwdemux_input_plugin(void);

#ifdef __cplusplus
}
#endif


#endif /* HWDEMUX_INPUT_H */
