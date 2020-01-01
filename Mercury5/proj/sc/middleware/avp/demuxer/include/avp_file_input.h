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


#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  File_Init(const void *pArg);
int File_GetStreamingData(void *hdl, char *base);
void File_DeInit(void);
void File_Start(void);
void File_Stop(void);
void File_IOSeek(int offset);
int  File_GetExtraRbufSize(void);

int  File_SetService(void *pPayload, uint8_t payloadLen);
int  File_SetServiceProvider(void *pPayload, uint8_t payloadLen);
int  File_ScanFrequency(void *pPayload, uint8_t payloadLen);


int File_GetSignalStrength(void);
int File_GetSignalQuality(void);
int File_GetLockStatus(void);


int streaming_file_input_plugin(void);
int streamingapp_file_input_plugin(void);

#ifdef __cplusplus
}
#endif


#endif /* FILE_INPUT_H */
