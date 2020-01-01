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
* @file   a2dp_io_itf.h
* @version
* @brief
*
*/

#ifndef __A2DP_IO_ITF_H__
#define __A2DP_IO_ITF_H__

#include <stdint.h>

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define A2DP_MAX_DMA1_BUFSIZE   (1024*32)
#define A2DP_MAX_DMA2_BUFSIZE   (1024*64)

/*
 * A2DP I/O error codes
 */
#define A2DP_IO_ERR_SUCCESS          0   /* No error */
#define A2DP_IO_ERR_ALLOC_FAILED    -1   /* Not enough memory */
#define A2DP_IO_ERR_DRV_FAILED      -2   /* Driver generic error */

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/
s32 a2dp_io_open(int channel, u32 sample_rate, u32 out_sample_rate);
s32 a2dp_io_write(u8 *pBuffer, u32 u32Len);
s32 a2dp_io_read(u8 *pBuffer, u32 u32Len, u32 *pnActualSize);
s32 a2dp_io_play(void);
s32 a2dp_io_stop(void);
s32 a2dp_io_pause(void);
s32 a2dp_io_resume(void);
s32 a2dp_io_reset(void);
s32 a2dp_io_bufinfo(u32 *pnDataSize, u32 DmaChoose);
s32 a2dp_io_close(void);

#endif
