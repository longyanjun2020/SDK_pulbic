////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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

/**
* @file    mdl_aud_wav_api.h
* @version
* @brief   header file
*
*/

#ifndef __MDL_AUD_WAV_API_H__
#define __MDL_AUD_WAV_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "mdl_aud_forward.h"

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
WAVEFORM* MdlAudGetWaveFormat(CWaveFile *wavFile);
DATA* MdlAudGetWaveData(CWaveFile *wavFile);
u32 MdlAudGetData(CWaveFile *wavFile);
bool MdlAudCheckID(u8* idPar,u8 A, u8 B, u8 C, u8 D);
s32 MdlAudReadWave(CWaveFile *wavFile);
s32 MdlAudReadRIFF(CWaveFile *wavFile);
s32 MdlAudReadFMT(CWaveFile *wavFile);
s32 MdlAudReadDATA(CWaveFile *wavFile);

#endif	//__MDL_AUD_WAV_API_H__
