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


#ifndef ISDBT_S_INPUT_H
#define ISDBT_S_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  ISDBT_S_Init(const void *pArg);
int ISDBT_S_GetStreamingData(void *hdl, char *base);
void ISDBT_S_DeInit(void);
void ISDBT_S_Start(void);
void ISDBT_S_Stop(void);
void ISDBT_S_IOSeek(int offset);
int  ISDBT_S_GetExtraRbufSize(void);

int  ISDBT_S_SetService(void *pPayload, uint8_t payloadLen);
int  ISDBT_S_SetServiceProvider(void *pPayload, uint8_t payloadLen);
int  ISDBT_S_ScanFrequency(void *pPayload, uint8_t payloadLen);


int ISDBT_S_GetSignalStrength(void);
int ISDBT_S_GetSignalQuality(void);
int ISDBT_S_GetLockStatus(void);

int streaming_isdbt_s_input_plugin(void);
int streamingapp_isdbt_s_input_plugin(void);

#ifdef __cplusplus
}
#endif


#endif /* ISDBT_S_INPUT_H */
