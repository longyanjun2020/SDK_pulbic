/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : Hardware decoder system configuration
--
--------------------------------------------------------------------------------
--
--  Version control information, please leave untouched.
--
--  $RCSfile: deccfg.h,v $
--  $Revision: 1.6 $
--  $Date: 2007/11/22 12:15:58 $
--
------------------------------------------------------------------------------*/

#ifndef __DEC_X170_CFG_H__
#define __DEC_X170_CFG_H__

#include "drv_mfd_mstar_fpga.h"

/* predefined values of HW system parameters. DO NOT ALTER! */
#define DEC_X170_OUTPUT_PICTURE_LITTLE_ENDIAN       1
#define DEC_X170_OUTPUT_PICTURE_BIG_ENDIAN          0

#define DEC_X170_INPUT_STREAM_LITTLE_ENDIAN        1
#define DEC_X170_INPUT_STREAM_BIG_ENDIAN           0

#define DEC_X170_INPUT_DATA_LITTLE_ENDIAN          1
#define DEC_X170_INPUT_DATA_BIG_ENDIAN             0

#define DEC_X170_BUS_BURST_LENGTH_UNDEFINED        0
#define DEC_X170_BUS_BURST_LENGTH_4                4
#define DEC_X170_BUS_BURST_LENGTH_8                8
#define DEC_X170_BUS_BURST_LENGTH_16               16

#define DEC_X170_ASIC_SERVICE_PRIORITY_DEFAULT      0
#define DEC_X170_ASIC_SERVICE_PRIORITY_WR_1         1
#define DEC_X170_ASIC_SERVICE_PRIORITY_WR_2         2
#define DEC_X170_ASIC_SERVICE_PRIORITY_RD_1         3
#define DEC_X170_ASIC_SERVICE_PRIORITY_RD_2         4

#define DEC_X170_OUTPUT_FORMAT_RASTER_SCAN          0
#define DEC_X170_OUTPUT_FORMAT_TILED                1

/* end of predefined values */

/* now what we use */

#ifndef DEC_X170_USING_IRQ
/* Control IRQ generation by decoder hardware */
#define DEC_X170_USING_IRQ                1
#endif

#ifndef DEC_X170_ASIC_SERVICE_PRIORITY
/* hardware intgernal prioriy scheme. better left unchanged */
#define DEC_X170_ASIC_SERVICE_PRIORITY    DEC_X170_ASIC_SERVICE_PRIORITY_DEFAULT
#endif

#ifndef DEC_X170_BUS_BURST_LENGTH
/* how long are the hardware data bursts; better left unchanged    */
#define DEC_X170_BUS_BURST_LENGTH        DEC_X170_BUS_BURST_LENGTH_16
#endif

#ifndef DEC_X170_INPUT_STREAM_ENDIAN
/* this should match the system endianess, so that Decoder reads      */
/* the input stream in the right order                                */
#define DEC_X170_INPUT_STREAM_ENDIAN    DEC_X170_INPUT_STREAM_LITTLE_ENDIAN
#endif

#ifndef DEC_X170_OUTPUT_PICTURE_ENDIAN
/* this should match the system endianess, so that Decoder writes     */
/* the output pixel data in the right order                           */
#define DEC_X170_OUTPUT_PICTURE_ENDIAN    DEC_X170_OUTPUT_PICTURE_LITTLE_ENDIAN
#endif

#ifndef DEC_X170_LATENCY_COMPENSATION
/* compensation for bus latency; values up to 63 */
#define DEC_X170_LATENCY_COMPENSATION    0
#endif

#ifndef DEC_X170_INTERNAL_CLOCK_GATING
/* clock is gated from decoder structures that are not used */
#define DEC_X170_INTERNAL_CLOCK_GATING    0
#endif

#ifndef DEC_X170_OUTPUT_FORMAT
/* Decoder output picture format in external memory: Raster-scan or     */
/*macroblock tiled i.e. macroblock data written in consecutive addresses */
#define DEC_X170_OUTPUT_FORMAT            DEC_X170_OUTPUT_FORMAT_RASTER_SCAN
#endif

#ifndef DEC_X170_DATA_DISCARD_ENABLE
#define DEC_X170_DATA_DISCARD_ENABLE     0
#endif

/* Decoder output data swap for 32bit words*/
#ifndef DEC_X170_OUTPUT_SWAP_32_ENABLE
#define DEC_X170_OUTPUT_SWAP_32_ENABLE   0
#endif

/* Decoder input data swap(excluding stream data) for 32bit words*/
#ifndef DEC_X170_INPUT_DATA_SWAP_32_ENABLE
#define DEC_X170_INPUT_DATA_SWAP_32_ENABLE   0
#endif

/* Decoder input stream swap for 32bit words */
#ifndef DEC_X170_INPUT_STREAM_SWAP_32_ENABLE
#define DEC_X170_INPUT_STREAM_SWAP_32_ENABLE   0
#endif

/* Decoder input data endian */
#ifndef DEC_X170_INPUT_DATA_ENDIAN
#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_BIG_ENDIAN
#endif

/* Check validity of values */

/* data discard and tiled mode can not be on simultaneously */
#if (DEC_X170_DATA_DISCARD_ENABLE && (DEC_X170_OUTPUT_FORMAT == DEC_X170_OUTPUT_FORMAT_TILED))
#error "Bad value specified: DEC_X170_DATA_DISCARD_ENABLE && (DEC_X170_OUTPUT_FORMAT == DEC_X170_OUTPUT_FORMAT_TILED)"
#endif

#if (DEC_X170_OUTPUT_PICTURE_ENDIAN > 1)
#error "Bad value specified for DEC_X170_OUTPUT_PICTURE_ENDIAN"
#endif

#if (DEC_X170_OUTPUT_FORMAT > 1)
#error "Bad value specified for DEC_X170_OUTPUT_FORMAT"
#endif

#if (DEC_X170_BUS_BURST_LENGTH > 31)
#error "Bad value specified for DEC_X170_AMBA_BURST_LENGTH"
#endif

#if (DEC_X170_ASIC_SERVICE_PRIORITY > 4)
#error "Bad value specified for DEC_X170_ASIC_SERVICE_PRIORITY"
#endif

#if (DEC_X170_LATENCY_COMPENSATION > 63)
#error "Bad value specified for DEC_X170_LATENCY_COMPENSATION"
#endif

#if (DEC_X170_OUTPUT_SWAP_32_ENABLE > 1)
#error "Bad value specified for DEC_X170_OUTPUT_SWAP_32_ENABLE"
#endif

#if (DEC_X170_INPUT_DATA_SWAP_32_ENABLE > 1)
#error "Bad value specified for DEC_X170_INPUT_DATA_SWAP_32_ENABLE"
#endif

#if (DEC_X170_INPUT_STREAM_SWAP_32_ENABLE > 1)
#error "Bad value specified for DEC_X170_INPUT_STREAM_SWAP_32_ENABLE"
#endif

#if (DEC_X170_OUTPUT_SWAP_32_ENABLE > 1)
#error "Bad value specified for DEC_X170_INPUT_DATA_ENDIAN"
#endif

#if (DEC_X170_DATA_DISCARD_ENABLE > 1)
#error "Bad value specified for DEC_X170_DATA_DISCARD_ENABLE"
#endif

/* Common defines for the decoder */

/* Number registers for the decoder */
#define DEC_X170_REGISTERS          50

/* Max amount of stream */
#define DEC_X170_MAX_STREAM         ((1<<24)-1)

#ifndef DEC_X170_TIMEOUT_LENGTH
#define DEC_X170_TIMEOUT_LENGTH     -1
#endif

#define DEC_X170_HW_TIMEOUT_INT_ENA  1

/* Check validity of the stream addresses */

#define X170_CHECK_BUS_ADDRESS(d)   ((d) < 64 ? 1 : 0)
#define X170_CHECK_VIRTUAL_ADDRESS(d)   (((void*)(d) < (void*)64) ? 1 : 0)

#endif /* __DEC_X170_CFG_H__ */
