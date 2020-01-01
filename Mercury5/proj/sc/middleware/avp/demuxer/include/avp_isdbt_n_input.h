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


#ifndef ISDBT_N_INPUT_H
#define ISDBT_N_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  ISDBT_N_Init(const void *pArg);
int  ISDBT_N_GetStreamingData(char *pBuf, int freesize);
void ISDBT_N_DeInit(void);
void ISDBT_N_Start(void);
void ISDBT_N_Stop(void);
void ISDBT_N_IOSeek(int offset);
int  ISDBT_N_GetExtraRbufSize(void);

int  ISDBT_N_SetService(void *pPayload, uint8_t payloadLen);
int  ISDBT_N_SetServiceProvider(void *pPayload, uint8_t payloadLen);
int  ISDBT_N_ScanFrequency(void *pPayload, uint8_t payloadLen);


int ISDBT_N_GetSignalStrength(void);
int ISDBT_N_GetSignalQuality(void);
int ISDBT_N_GetLockStatus(void);

int streaming_isdbt_n_input_plugin(void);
int streamingapp_isdbt_n_input_plugin(void);

#ifdef __cplusplus
}
#endif


#endif /* ISDBT_N_INPUT_H */
