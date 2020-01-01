//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvHVD.h
/// @brief  HVD Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_HVD_DEF_H_
#define _DRV_HVD_DEF_H_

#include "drvHVD_Common.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

// HW capability
#define HVD_HW_SVD  1
#define HVD_HW_HVD  2
//#if defined(CHIP_T2)
//#define HVD_HW_VERSION      HVD_HW_SVD
//#else
#define HVD_HW_VERSION      HVD_HW_HVD
//#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// Feature switch
//#if defined(UDMA_FPGA_ENVI)
//    #define HVD_ENABLE_MUTEX_PROTECT    0
//    #define HVD_ENABLE_MIU_RST_PROTECT     0
//    #define HVD_ENABLE_AUTO_SET_REG_BASE    0
//    #define HVD_ENABLE_MSOS_SYSTEM_CALL     0
//    #define HVD_ENABLE_PATCH_ISFRAMERDY     0
//    #define HVD_ENABLE_STOP_ACCESS_OVER_256     1
//    #define HVD_ENABLE_AUTO_AVI_NULL_PACKET     0
//    #define HVD_ENABLE_MSOS_MIU1_BASE     0
//    #define HVD_ENABLE_BDMA_2_BITSTREAMBUF     0
//    #define HVD_ENABLE_EMBEDDED_FW_BINARY       1
//    #define HVD_ENABLE_BDMA_FW_FLASH_2_SDRAM     0
//    #define HVD_ENABLE_CHECK_STATE_BEFORE_SET_CMD   0
//    #define HVD_ENABLE_WAIT_CMD_FINISHED   0
//    #define HVD_ENABLE_TIME_MEASURE     0
//    #define HVD_ENABLE_RV_FEATURE   0
//#elif defined(REDLION_LINUX_KERNEL_ENVI)
//    #define HVD_ENABLE_MUTEX_PROTECT    0
//    #define HVD_ENABLE_MIU_RST_PROTECT     1
//    #define HVD_ENABLE_AUTO_SET_REG_BASE    0
//    #define HVD_ENABLE_MSOS_SYSTEM_CALL     0
//    #define HVD_ENABLE_PATCH_ISFRAMERDY     0
//    #define HVD_ENABLE_STOP_ACCESS_OVER_256     0
//    #define HVD_ENABLE_AUTO_AVI_NULL_PACKET     0
//    #define HVD_ENABLE_MSOS_MIU1_BASE     0
//    #define HVD_ENABLE_BDMA_2_BITSTREAMBUF     0
//    #define HVD_ENABLE_EMBEDDED_FW_BINARY       1
//    #define HVD_ENABLE_BDMA_FW_FLASH_2_SDRAM     0
//    #define HVD_ENABLE_CHECK_STATE_BEFORE_SET_CMD   0
//    #define HVD_ENABLE_WAIT_CMD_FINISHED   0
//    #define HVD_ENABLE_TIME_MEASURE     0
//    #define HVD_ENABLE_REINIT_FAILED        1
//    #define HVD_ENABLE_RV_FEATURE   0
//#else
    #define HVD_ENABLE_MUTEX_PROTECT    1
    #define HVD_ENABLE_MIU_RST_PROTECT     1
    #if 1//defined( MSOS_TYPE_LINUX)
        #define HVD_ENABLE_AUTO_SET_REG_BASE    1
    #else
        #define HVD_ENABLE_AUTO_SET_REG_BASE    0
    #endif
    #if 0//defined( MSOS_TYPE_LINUX) || defined( MSOS_TYPE_ECOS) //|| defined( MSOS_TYPE_NOS)
        #define HVD_ENABLE_PATCH_ISFRAMERDY     0
        #define HVD_ENABLE_MSOS_SYSTEM_CALL     1
    #else
        #define HVD_ENABLE_PATCH_ISFRAMERDY     1
        #define HVD_ENABLE_MSOS_SYSTEM_CALL     1
    #endif
    #if 0//defined( MSOS_TYPE_NOS) && (defined( CHIP_T3 ) || defined( CHIP_T8 ) || defined(CHIP_J2))
        #define HVD_ENABLE_STOP_ACCESS_OVER_256     1
        #define HVD_ENABLE_BDMA_2_BITSTREAMBUF     1
    #else
        #define HVD_ENABLE_STOP_ACCESS_OVER_256     0
        #define HVD_ENABLE_BDMA_2_BITSTREAMBUF     0
    #endif

    #define HVD_ENABLE_AUTO_AVI_NULL_PACKET     1

    #if 0//defined(CHIP_JANUS)
    #define HVD_ENABLE_MSOS_MIU1_BASE   0
    #else
    #define HVD_ENABLE_MSOS_MIU1_BASE   1
    #endif

    #if 0//defined( FW_EXTERNAL_BIN )
        #define HVD_ENABLE_EMBEDDED_FW_BINARY       0
        #define HVD_ENABLE_BDMA_FW_FLASH_2_SDRAM     1
    #else   // defined( FW_EMBEDDED_ASC )
        #define HVD_ENABLE_EMBEDDED_FW_BINARY       1
        #define HVD_ENABLE_BDMA_FW_FLASH_2_SDRAM     0
    #endif

    #define HVD_ENABLE_CHECK_STATE_BEFORE_SET_CMD   0
    #define HVD_ENABLE_WAIT_CMD_FINISHED   0
    #define HVD_ENABLE_TIME_MEASURE     0
    #define HVD_ENABLE_REINIT_FAILED        0

    #if 1//defined(CHIP_T2) || defined(CHIP_U3) || defined(CHIP_T3) || defined(CHIP_T4) || defined(CHIP_T7)
        #define HVD_ENABLE_RV_FEATURE   0
    #else
        #define HVD_ENABLE_RV_FEATURE   1
    #endif

//#endif

#if defined(REDLION_LINUX_KERNEL_ENVI)
    #include "drvHVD_redlion.h"
#endif

#if (HVD_ENABLE_MUTEX_PROTECT) || ( HVD_ENABLE_MSOS_SYSTEM_CALL )
    #include "osalHVD.h"
#endif

#if HVD_ENABLE_MSOS_MIU1_BASE
    #include "halCHIP.h"
#endif

#if HVD_ENABLE_BDMA_2_BITSTREAMBUF
    #include "drvBDMA.h"
    #define HVD_dmacpy( DESTADDR, SRCADDR , LEN)   MDrv_BDMA_CopyHnd((MS_PHYADDR)(SRCADDR), (MS_PHYADDR)(DESTADDR), (LEN), E_BDMA_SDRAM2SDRAM1, BDMA_OPCFG_DEF)
    #define HVD_BDMAcpy(DESTADDR, SRCADDR, LEN , Flag)   MDrv_BDMA_CopyHnd((MS_PHYADDR)(SRCADDR), (MS_PHYADDR)(DESTADDR), (LEN), (Flag), BDMA_OPCFG_DEF)
#endif

#if HVD_ENABLE_BDMA_FW_FLASH_2_SDRAM
    #include "drvSERFLASH.h"
    #define HVD_FLASHcpy(DESTADDR, SRCADDR, LEN , Flag)   MDrv_SERFLASH_CopyHnd((MS_PHYADDR)(SRCADDR), (MS_PHYADDR)(DESTADDR), (LEN), (Flag), SPIDMA_OPCFG_DEF)
#endif

// debug switch
// DEBUG
#define HVD_MSG_MUST(format, args...)  HVD_UART_PRINTF( E_HVD_UART_CTRL_MUST ,format, ##args)
#define HVD_MSG_ERR(format, args...)  HVD_UART_PRINTF( E_HVD_UART_CTRL_ERR ,format, ##args)
#define HVD_MSG_INFO(format, args...)  HVD_UART_PRINTF( E_HVD_UART_CTRL_INFO , format, ##args)
#define HVD_MSG_DEG(format, args...)  HVD_UART_PRINTF( E_HVD_UART_CTRL_DBG , format, ##args)
#define HVD_MSG_TRACE()  HVD_UART_PRINTF( E_HVD_UART_CTRL_TRACE , "HVD TRACE:%s ; %s ; %d \n" , __FILE__ , __FUNCTION__, __LINE__)
#define HVD_FW_DEG(format, args...)     HVD_UART_PRINTF( E_HVD_UART_CTRL_FW , format, ##args)

// Configs
#define HVD_FW_IDLE_THRESHOLD     5000 // VPU ticks
#define HVD_BBU_ST_ADDR_IN_BITSTREAMBUF     0x400

#define HVD_DRV_CMD_WAIT_FINISH_TIMEOUT     100

#define H265_RBSP_BUF_LEN       1024

// Util or Functions
#define HVD_MAX(a,b) (((a)>(b)) ? (a) : (b))
#define HVD_MIN(a,b) (((a)<(b)) ? (a) : (b))
#define HVD_MAX3(x,y,z) (((x)>(y) ? (x):(y)) > (z) ? ((x)>(y) ? (x):(y)):(z))
#define HVD_LWORD(x)    (MS_U16)((x)&0xffff)
#define HVD_HWORD(x)    (MS_U16)(((x)>>16)&0xffff)
#define HVD_U32_MAX     0xffffffffUL
#define HVD_RV_BROKENBYUS_MASK    0x00800000

#ifdef MSOS_TYPE_LINUX
    #if HVD_ENABLE_MSOS_SYSTEM_CALL
        #define HVD_VA2PA(x )  (x)//(MS_U32)(MS_VA2PA( (void*)(x))) // fixme
    #else
        #define HVD_VA2PA(x )  (x)//(MS_U32)(MS_VA2PA( (void*)(x))) // fixme
    #endif
#else
#define HVD_VA2PA(x)        (x)
#endif

#if defined(REDLION_LINUX_KERNEL_ENVI)
#define HVD_PA2VA(x )   (MS_U32)MDrv_SYS_PA2NonCacheSeg((void*)(x))
#else
#define HVD_PA2VA(x )   (MS_U32)MS_PA2KSEG1((MS_U32)(x))
#endif

// Memory alignment
#define MEMALIGN(N, UNIT)       ((((N)+(UNIT)-1)/(UNIT))*(UNIT))

#if 0//def memset
#define HVD_memset(x , y , z)   memset(x, y, z)
#else
#define HVD_memset( pDstAddr, u8value, u32Size)          \
    do {                                                                               \
        MS_U32 i = 0;                                                           \
        volatile MS_U8 *Dest = (volatile MS_U8 *)(pDstAddr) ;                           \
        for (i = 0; i < (u32Size); i++)                                       \
        {                                                                               \
            Dest[i] = (u8value);                                                 \
        }                                                                               \
    }while(0)
#endif

#if 0//def memcpy
#define HVD_memcpy(x , y , z)   memcpy(x, y, z)
#else

#if 0
#define HVD_memcpy(  pDstAddr, pSrcAddr, u32Size)           \
    do {                                                                               \
        MS_U32 i = 0;                                                               \
        volatile MS_U8 *Dest = (volatile MS_U8 *)(pDstAddr );                     \
        volatile MS_U8 *Src = ( volatile MS_U8 *)(pSrcAddr) ;                         \
        for (i = 0; i < (u32Size); i++)                                     \
        {                                                                           \
            Dest[i] = Src[i];                                                      \
        }                                                                               \
    }while(0)
#else
#define HVD_memcpy(  pDstAddr, pSrcAddr, u32Size) \
    do { \
        register unsigned long u32I=0; \
        register unsigned long u32Dst = (unsigned long)pDstAddr; \
        void * pSrc = (void *)pSrcAddr; \
        MS_U32 _u32memsize = u32Size; \
        if( (u32Dst % 4) || ((unsigned long)pSrc % 4) ) \
        { \
            for( u32I=0; u32I< (unsigned long)(_u32memsize); u32I++) \
            { \
                ((volatile unsigned char *)u32Dst)[u32I] = ((volatile unsigned char *)pSrc)[u32I]; \
            } \
        } \
        else \
        { \
            for( u32I=0; u32I < ((unsigned long)(u32Size)/4); u32I++) \
            { \
                ((volatile unsigned long *)u32Dst)[u32I] = ((volatile unsigned long *)pSrc)[u32I]; \
            } \
            if((_u32memsize)%4) \
            { \
                u32Dst += u32I*4; \
                pSrc = (void *)((unsigned long)pSrc + u32I*4); \
                for( u32I=0; u32I<((unsigned long)(_u32memsize)%4); u32I++) \
                { \
                    ((volatile unsigned char *)u32Dst)[u32I] = ((volatile unsigned char *)pSrc)[u32I]; \
                } \
            } \
        } \
    }while(0)
#endif

#endif



#if HVD_ENABLE_MSOS_SYSTEM_CALL
#define HVD_Delay_ms(x)     MsOS_DelayTask(x)
#define HVD_SYSTEM_DELAY_MS_TYPE       2
#elif defined(REDLION_LINUX_KERNEL_ENVI)
#define HVD_Delay_ms(x)     msleep(x)
//#define HVD_Delay_ms(x)     MHal_H264_Delay_ms(x)
#define HVD_SYSTEM_DELAY_MS_TYPE       3
#else
#define HVD_Delay_ms(x)                                 \
    do {                                                            \
        volatile MS_U32 ticks=0;                                         \
        while( ticks < ( ((MS_U32)(x)) <<13) )      \
        {                                                               \
            ticks++;                                                \
        }                                                               \
    } while(0)
#define HVD_SYSTEM_DELAY_MS_TYPE       0
#endif  // HVD_ENABLE_MSOS_SYSTEM_CALL


#define HVD_DumpMemory( addr,  size ,  ascii , NonCacheMask)       \
        do{                                                                                     \
            MS_U32 i = 0;                                                                          \
            MS_U32 j = 0;                                                                           \
            MS_U8* temp = (MS_U8*)addr;                                                 \
            MS_U8 string[17] ;                                                                      \
            HVD_MSG_DEG("HVD Dump Memory addr: 0x%x ; size: 0x%x \r\n", addr, size);    \
            temp = (MS_U8*)(((MS_U32)temp) | NonCacheMask);              \
            HVD_memset(string , 0 , sizeof(string));                                                        \
            for (j = 0; j < (size >> 4); j++)                                                               \
            {                                                                                                               \
                if (ascii)                                                                                              \
                {                                                                                                           \
                    for (i = 0; i < 16; i++)                                                                        \
                    {                                                                                                           \
                        if (*(temp + i) >= 30 && *(temp + i) <= 126)                                        \
                            string[i] = *(temp + i);                                                                    \
                        else                                                                                                    \
                            string[i] = '.';                                                                                    \
                    }                                                                                                         \
                    HVD_MSG_DEG("0x%08x  %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x  %s\n"  \
                           , j << 4 , *temp, *(temp + 1), *(temp + 2), *(temp + 3), *(temp + 4), *(temp + 5), *(temp + 6), *(temp + 7), *(temp + 8), *(temp + 9), *(temp + 10), *(temp + 11), *(temp + 12), *(temp + 13), *(temp + 14), *(temp + 15) , string); \
                }                                                                       \
                else                                                                                                            \
                {                                                                                                                   \
                    HVD_MSG_DEG("0x%08x  %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n"  \
                           , j << 4 , *temp, *(temp + 1), *(temp + 2), *(temp + 3), *(temp + 4), *(temp + 5), *(temp + 6), *(temp + 7), *(temp + 8), *(temp + 9), *(temp + 10), *(temp + 11), *(temp + 12), *(temp + 13), *(temp + 14), *(temp + 15));  \
                }                                       \
                temp += 16;                                                         \
            }                                           \
            HVD_MSG_DEG("0x%08x  " , j << 4);                                        \
            HVD_memset(string , 0 , sizeof(string));                            \
            for (i = 0; i < (size & 0x0f); i++)                                 \
            {                                                                                   \
                if (*(temp + i) >= 30 && *(temp + i) <= 126)                        \
                    string[i] = *(temp + i);                                                    \
                else                                                                                    \
                    string[i] = '.';                                                                    \
                HVD_MSG_DEG("%02x ", *(MS_U8*)(temp + i));                                              \
            }                                                               \
            if (ascii)                                                                                      \
            {                                                                                                       \
                for (; i < 16  ; i++)                                                                           \
                    HVD_MSG_DEG("   ");                                                                                  \
                HVD_MSG_DEG(" %s\n" , string);                                                                       \
            }                                                                       \
            else                                                                                                        \
                HVD_MSG_DEG("\n");                                                                                       \
        }while(0)


#if HVD_ENABLE_MSOS_SYSTEM_CALL
    #define HVD_GetSysTime_ms()    MsOS_GetSystemTime()
    #define HVD_SYSTEM_CLOCK_TYPE       1
#elif defined(REDLION_LINUX_KERNEL_ENVI)
    #define HVD_GetSysTime_ms()    MHal_H264_GetSyetemTime()
    #define HVD_SYSTEM_CLOCK_TYPE       2
#else
    #define HVD_GetSysTime_ms()    1
    #define HVD_SYSTEM_CLOCK_TYPE       0
#endif  // MsOS_GetSystemTime


#if defined(REDLION_LINUX_KERNEL_ENVI)
#define HVD_SYSTEM_UART_TYPE       2
#define HVD_UART_PRINTF( u32type, format , args...)      \
    do{                                                             \
        if( u32UartCtrl & u32type )                            \
        {                                                                   \
            printk( format , ##args  );                           \
        }                                                                   \
    }while(0)
#elif  defined( MSOS_TYPE_ECOS)
#define HVD_SYSTEM_UART_TYPE       3
#define HVD_UART_PRINTF( u32type, format , args...)      \
    do{                                                             \
        if( u32UartCtrl & u32type )                            \
        {                                                                   \
            diag_printf( format , ##args  );                           \
        }                                                                   \
    }while(0)
#elif  defined( __RTK_OS__ )
#define HVD_SYSTEM_UART_TYPE       4
#define HVD_UART_PRINTF( u32type, format , args...)      \
    do{                                                             \
        if( u32UartCtrl & u32type )                            \
        {                                                                   \
            UartSendTrace( format , ##args  );                           \
        }                                                                   \
    }while(0)
#else
#define HVD_SYSTEM_UART_TYPE       1
#define HVD_UART_PRINTF( u32type, format , args...)      \
    do{                                                             \
        if( u32UartCtrl & u32type )                            \
        {                                                                   \
            printf( format , ##args  );                           \
        }                                                                   \
    }while(0)
#endif

#if HVD_ENABLE_MSOS_SYSTEM_CALL
    #include "asmCPU.h"
    #define HAL_MEMORY_BARRIER()     MAsm_CPU_Sync()
    #define HVD_MEMORY_BARRIER_TYPE       3
#else
    #if defined (__mips__)
        #define HAL_MEMORY_BARRIER() __asm__ volatile ("sync;")
        #define HVD_MEMORY_BARRIER_TYPE       1
    #elif defined (__aeon__)
        #ifdef __AEONR2__
            #define HAL_MEMORY_BARRIER() __asm__ volatile ("b.syncwritebuffer;")
            #define HVD_MEMORY_BARRIER_TYPE       22
        #else
            #if defined( CHIP_T2 )
                #define HAL_MEMORY_BARRIER() __asm__ volatile ("l.msync;")
                #define HVD_MEMORY_BARRIER_TYPE       21
            #else
                #define HAL_MEMORY_BARRIER() __asm__ volatile ("l.syncwritebuffer;")
                #define HVD_MEMORY_BARRIER_TYPE       23
            #endif
        #endif
    #else
        #define HAL_MEMORY_BARRIER()
        #define HVD_MEMORY_BARRIER_TYPE       0
    #endif
#endif

#if defined(UDMA_FPGA_ENVI)
#define HVD_UDMA_memcpy( pDstAddr, pSrcAddr, u32Size  )
#endif

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef void (*HVD_ISRCallBack)(void);

typedef enum
{
    E_HVD_RETURN_FAIL=0,
    E_HVD_RETURN_SUCCESS,
    E_HVD_RETURN_INVALID_PARAMETER,
    E_HVD_RETURN_ILLEGAL_ACCESS,
    E_HVD_RETURN_HARDWARE_BREAKDOWN,
    E_HVD_RETURN_OUTOF_MEMORY,
    E_HVD_RETURN_UNSUPPORTED,
    E_HVD_RETURN_TIMEOUT,
    E_HVD_RETURN_NOTREADY,
    E_HVD_RETURN_MEMORY_OVERWIRTE,
    E_HVD_RETURN_ES_FULL,
    E_HVD_RETURN_RE_INIT,
    E_HVD_RETURN_NOT_RUNNING,
} HVD_Return;

typedef enum
{
// share memory
    E_HVD_GDATA_SHARE_MEM=0x1000,
    // switch
    //E_HVD_GDATA_SEMAPHORE,
    E_HVD_GDATA_DISP_INFO_ADDR=(0x0100+E_HVD_GDATA_SHARE_MEM),
    // report
    E_HVD_GDATA_PTS=(0x0200+E_HVD_GDATA_SHARE_MEM),
    E_HVD_GDATA_U64PTS,
    E_HVD_GDATA_DECODE_CNT,
    E_HVD_GDATA_DATA_ERROR_CNT,
    E_HVD_GDATA_DEC_ERROR_CNT,
    E_HVD_GDATA_ERROR_CODE,
    E_HVD_GDATA_VPU_IDLE_CNT,
    E_HVD_GDATA_DISP_FRM_INFO,
    E_HVD_GDATA_DEC_FRM_INFO,
    E_HVD_GDATA_ES_LEVEL,
    E_HVD_GDATA_PTS_STC_DIFF,

    // user data
    E_HVD_GDATA_USERDATA_WPTR,
    E_HVD_GDATA_USERDATA_IDX_TBL_ADDR,
    E_HVD_GDATA_USERDATA_PACKET_TBL_ADDR,
    E_HVD_GDATA_USERDATA_PACKET_SIZE,
    E_HVD_GDATA_USERDATA_IDX_TBL_SIZE,
    E_HVD_GDATA_USERDATA_PACKET_TBL_SIZE,
    // report - modes
    E_HVD_GDATA_IS_SHOW_ERR_FRM,
    E_HVD_GDATA_IS_REPEAT_LAST_FIELD,
    E_HVD_GDATA_IS_ERR_CONCEAL,
    E_HVD_GDATA_IS_SYNC_ON,
    E_HVD_GDATA_IS_PLAYBACK_FINISH,
    E_HVD_GDATA_SYNC_MODE,
    E_HVD_GDATA_SKIP_MODE,
    E_HVD_GDATA_DROP_MODE,
    E_HVD_GDATA_DISPLAY_DURATION,
    E_HVD_GDATA_FRC_MODE,
    E_HVD_GDATA_NEXT_PTS,
    E_HVD_GDATA_DISP_Q_SIZE,
    E_HVD_GDATA_DISP_Q_PTR,
    E_HVD_GDATA_NEXT_DISP_FRM_INFO,
    E_HVD_GDATA_REAL_FRAMERATE,
    E_HVD_GDATA_IS_ORI_INTERLACE_MODE,
    E_HVD_GDATA_FRM_PACKING_SEI_DATA,
    E_HVD_GDATA_TYPE_FRAME_MBS_ONLY_FLAG,
    E_HVD_GDATA_FB_USAGE_MEM,

    // internal control
    E_HVD_GDATA_IS_1ST_FRM_RDY=(0x0300+E_HVD_GDATA_SHARE_MEM),
    E_HVD_GDATA_IS_I_FRM_FOUND,
    E_HVD_GDATA_IS_SYNC_START,
    E_HVD_GDATA_IS_SYNC_REACH,
    E_HVD_GDATA_FW_VERSION_ID,
    E_HVD_GDATA_FW_IF_VERSION_ID,
    E_HVD_GDATA_BBU_Q_NUMB,
    E_HVD_GDATA_DEC_Q_NUMB,
    E_HVD_GDATA_DISP_Q_NUMB,
    E_HVD_GDATA_PTS_Q_NUMB,
    E_HVD_GDATA_FW_INIT_DONE,
    E_HVD_GDATA_FW_FLUSH_STATUS,
    E_HVD_GDATA_TS_SEAMLESS_STATUS,

    // debug
    E_HVD_GDATA_SKIP_CNT=(0x0400+E_HVD_GDATA_SHARE_MEM),
    E_HVD_GDATA_GOP_CNT,
    E_HVD_GDATA_DISP_CNT,
    E_HVD_GDATA_DROP_CNT,
    E_HVD_GDATA_DISP_STC,
    E_HVD_GDATA_VSYNC_CNT,
    E_HVD_GDATA_MAIN_LOOP_CNT,
    // AVC
    E_HVD_GDATA_AVC_LEVEL_IDC =(0x0500+E_HVD_GDATA_SHARE_MEM),
    E_HVD_GDATA_AVC_LOW_DELAY,
    E_HVD_GDATA_AVC_VUI_DISP_INFO,
    //E_HVD_GDATA_AVC_SPS_ADDR,

// SRAM
    E_HVD_GDATA_SRAM=0x2000,
    //E_HVD_GDATA_AVC_NAL_CNT,

// Mailbox or Reg
    E_HVD_GDATA_MBOX=0x3000,
    E_HVD_GDATA_FW_STATE,       // HVD RISC MBOX 0 (esp. FW init done)
    E_HVD_GDATA_IS_DISP_INFO_UNCOPYED,   // HVD RISC MBOX 0 (rdy only)
    E_HVD_GDATA_IS_DISP_INFO_CHANGE,   // HVD RISC MBOX 0 (rdy only)
    E_HVD_GDATA_HVD_ISR_STATUS,   // HVD RISC MBOX 1 (value only)
    E_HVD_GDATA_VPU_ISR_STATUS,   // VPU RISC MBOX 1 (value only)
    E_HVD_GDATA_IS_FRAME_SHOWED,    // HVD HI mbox 0 ( showed: rdy cleared ; not show: rdy enable )
    E_HVD_GDATA_ES_READ_PTR,    //
    E_HVD_GDATA_ES_WRITE_PTR,    //
    E_HVD_GDATA_BBU_READ_PTR,    //
    E_HVD_GDATA_BBU_WRITE_PTR,    //
    E_HVD_GDATA_BBU_WRITE_PTR_FIRED,    //
    E_HVD_GDATA_VPU_PC_CNT,    //

// FW def
    E_HVD_GDATA_FW_DEF=0x4000,
    E_HVD_GDATA_FW_MAX_DUMMY_FIFO,  // AVC: 256Bytes AVS: 2kB RM:???
    E_HVD_GDATA_FW_AVC_MAX_VIDEO_DELAY,
    E_HVD_GDATA_FW_BBU_TOTAL_TBL_ENTRY,
    E_HVD_GDATA_FW_BBU_TBL_ENTRY_NUMB,
    E_HVD_GDATA_FW_PTS_TOTAL_ENTRY_NUMB,
    E_HVD_GDATA_FW_DUMMY_WRITE_ADDR,
    E_HVD_GDATA_FW_DS_BUF_ADDR,
    E_HVD_GDATA_FW_DS_BUF_SIZE,
    E_HVD_GDATA_FW_DS_VECTOR_DEPTH,
    E_HVD_GDATA_FW_DS_INFO_ADDR,
    E_HVD_GDATA_FW_DS_IS_ENABLED,
// BBU size
// default pitch number
//
} HVD_GetData;

typedef enum
{
// share memory
    E_HVD_SDATA_SHARE_MEM=0x1000,
    // switch
    E_HVD_SDATA_FRAMEBUF_ADDR = (0x0100+E_HVD_SDATA_SHARE_MEM),
    E_HVD_SDATA_FRAMEBUF_SIZE,
    E_HVD_SDATA_ERROR_CODE,
    E_HVD_SDATA_DISP_INFO_TH,
    E_HVD_SDATA_FW_FLUSH_STATUS,
    // display info
    //E_HVD_SDATA_HOR_SIZE=(0x0200|E_HVD_SDATA_SHARE_MEM),
    // report
    //E_HVD_SDATA_PTS=0x0200,
    // internal control
    //E_HVD_SDATA_IDLE_CNT=0x0300,
    // debug
    //E_HVD_SDATA_SKIP_CNT=0x0400,
    // RM
    E_HVD_SDATA_RM_PICTURE_SIZES= ( 0x0500 |E_HVD_SDATA_SHARE_MEM  ),
// SRAM
    //E_HVD_SDATA_AVC_NAL_CNT=0x2000,
// Mailbox or Reg
    E_HVD_SDATA_MAILBOX=0x3000,
    E_HVD_SDATA_FW_CODE_TYPE=(0x0000|E_HVD_SDATA_MAILBOX),
    E_HVD_SDATA_TRIGGER_DISP,    // HVD HI mbox 0 ( 0: off ; rdy enable,1: on  )
    E_HVD_SDATA_GET_DISP_INFO_DONE,   // HVD RISC MBOX 1 ( clear rdy )
    E_HVD_SDATA_GET_DISP_INFO_START,   // HVD RISC MBOX 0 ( clear rdy )
// FW def
    E_HVD_SDATA_FW_DEF=0x4000,
    E_HVD_SDATA_VIRTUAL_BOX_WIDTH,
    E_HVD_SDATA_VIRTUAL_BOX_HEIGHT,
    //modify the state of the frame in DispQueue
    E_HVD_SDATA_DISPQ_STATUS_VIEW,
    E_HVD_SDATA_DISPQ_STATUS_DISP,
    E_HVD_SDATA_DISPQ_STATUS_FREE,
} HVD_SetData;

typedef enum
{
    E_HVD_UART_CTRL_DISABLE= BIT(4),
    E_HVD_UART_CTRL_ERR= BIT(0),
    E_HVD_UART_CTRL_INFO = BIT(1),
    E_HVD_UART_CTRL_DBG= BIT(2),
    E_HVD_UART_CTRL_FW= BIT(3),
    E_HVD_UART_CTRL_MUST= BIT(4),
    E_HVD_UART_CTRL_TRACE= BIT(5),
} HVD_Uart_Ctrl;

typedef enum
{
    E_HVD_INIT_HW_MASK = BMASK(2:0),        ///< HW Type
        E_HVD_INIT_HW_AVC = BITS(2:0, 0),   ///< HW deflaut: AVC 0X000
        E_HVD_INIT_HW_AVS = BITS(2:0, 1),   ///< HW: AVS 0X001
        E_HVD_INIT_HW_RM  = BITS(2:0, 2),   ///< HW: RM 0X010
        E_HVD_INIT_HW_MJPEG = BITS(2:0, 3), ///< HW: MJPEG 0x11
        E_HVD_INIT_HW_VP8 = BITS(2:0, 4),   ///< HW: VP8 0X100
        E_HVD_INIT_HW_VP6 = BITS(2:0, 5),   ///< HW: VP6 0x101
        E_HVD_INIT_HW_HEVC = BITS(2:0, 6),  ///< HW: HEVC 0x110
    E_HVD_INIT_MAIN_MASK = BMASK(4:3),                  ///< main type
        E_HVD_INIT_MAIN_FILE_RAW     = BITS(4:3, 0),    ///< main type: default: 0X00
        E_HVD_INIT_MAIN_FILE_TS      = BITS(4:3, 1),    ///< main type: 0X01
        E_HVD_INIT_MAIN_LIVE_STREAM  = BITS(4:3, 2),    ///< main type: 0X10
    E_HVD_INIT_INPUT_MASK = BMASK(5:5),       ///< process path for filling BBU table:  file mode. use drive; TSP: use tsp mode
        E_HVD_INIT_INPUT_TSP = BITS(5:5, 0),   ///< tsp input( default)
        E_HVD_INIT_INPUT_DRV = BITS(5:5, 1),  ///< driver input
    E_HVD_INIT_START_CODE_MASK = BMASK(6:6),               ///< AVC FILE MODE ONLY: mkv, mp4 container use.
        E_HVD_INIT_START_CODE_REMAINED  = BITS(6:6, 0),   ///< start code remained.(Defualt)
        E_HVD_INIT_START_CODE_REMOVED   = BITS(6:6, 1),   ///< start code removed.
    E_HVD_INIT_UTOPIA_ENVI = BIT(7),        ///< check MIU sel and set it
    E_HVD_INIT_DBG_FW      = BIT(8),        ///< check FW is debug version or not
    E_HVD_INIT_DUAL_ES_MASK = BMASK(9:9),                   ///< Dual ES buffer iput.
        E_HVD_INIT_DUAL_ES_DISABLE    = BITS(9:9, 0),       ///< Disable Dual ES buffer input.
        E_HVD_INIT_DUAL_ES_ENABLE     = BITS(9:9, 1),       ///< Enable Dual ES buffer input.
    //E_HVD_INIT_ENABLE_ISR_DISP =  BIT( 8)  ,      ///< enable display ISR. ISR occurs at every Vsync.
} HVD_Init_Mode_Flag;

typedef enum
{
    E_HVD_PLAY_NORMAL,
    E_HVD_PLAY_PAUSE,
    E_HVD_PLAY_STEP_DISPLAY,
} HVD_Play_Type;

typedef enum
{
    E_HVD_ESB_LEVEL_NORMAL = 0,
    E_HVD_ESB_LEVEL_UNDER = BIT(0),
    E_HVD_ESB_LEVEL_OVER = BIT(1),
} HVD_ESBuf_Level;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: HVD_FWInputSourceType
/// @brief \b Enum \b Description:  The type of fw binary input source
//-----------------------------------------------------------------------------
typedef enum
{
    E_HVD_FW_INPUT_SOURCE_NONE,       ///< No input fw.
    E_HVD_FW_INPUT_SOURCE_DRAM,       ///< input source from DRAM.
    E_HVD_FW_INPUT_SOURCE_FLASH,      ///< input source from FLASH.
} HVD_FWInputSourceType;

//-----------------------------------------------------------------------------
/// @brief \b Enum \b Name: HVD_FB_Reduction_Type
/// @brief \b Enum \b Description:  The type of frame buffer reduction type
//-----------------------------------------------------------------------------
typedef enum
{
    E_HVD_FB_REDUCTION_TYPE_NONE = 0,        ///< FB reduction disable
    E_HVD_FB_REDUCTION_TYPE_1_2 = 1,         ///< FB reduction 1/2
    E_HVD_FB_REDUCTION_TYPE_1_4 = 2,         ///< FB reduction 1/4
} HVD_FBReductionType;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Mem_Map
/// @brief \b Struct \b Description:  Store the HVD driver config
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32  u32MIU1BaseAddr;        //!< the physical memory start address of MIU 1 base address. 0: default value.
    MS_U32  u32FWBinaryVAddr;                //!<  virtual address of input FW binary in DRAM
    MS_U32  u32FWBinaryAddr;                //!< the physical memory start address in Flash memory of FW code source.
    MS_U32  u32FWBinarySize;                //!< the FW code size
    MS_U32 u32VLCBinaryVAddr;           ///< VLC table binary data buffer start address
    MS_U32 u32VLCBinaryAddr;            ///< VLC table binary data buffer start address
    MS_U32 u32VLCBinarySize;            ///<VLC table binary data buffer size
    MS_U32  u32CodeBufVAddr;        //!< the virtual memory start address of code buffer
    MS_U32  u32CodeBufAddr;         //!< the physical memory start address of code buffer
    MS_U32  u32CodeBufSize;             //!< the code buffer size
    MS_U32  u32FrameBufVAddr;           //!< the virtual memory start address of frame buffer
    MS_U32  u32FrameBufAddr;            //!< the physical memory start address of frame buffer
    MS_U32  u32FrameBufSize;                //!< the frame buffer size
    MS_U32  u32BitstreamBufVAddr;           //!< the virtual memory start address of bit stream buffer
    MS_U32  u32BitstreamBufAddr;                //!< the physical memory start address of bit stream buffer
    MS_U32  u32BitstreamBufSize;            //!< the bit stream buffer size
    MS_U32  u32DrvProcessBufVAddr;       //!< the virtual memory start address of driver process buffer
    MS_U32  u32DrvProcessBufAddr;       //!< the physical memory start address of driver process buffer
    MS_U32  u32DrvProcessBufSize;        //!< the driver process buffer size
    MS_U32  u32DynSacalingBufVAddr;       //!< the virtual memory start address of dynamic scaling buffer
    MS_U32  u32DynSacalingBufAddr;       //!< the physical memory start address of dynamic scaling buffer
    MS_U32  u32DynSacalingBufSize;        //!< the dynamic scaling buffer size
    HVD_FWInputSourceType eFWSourceType;             //!< the input FW source type.
} HVD_Mem_Map;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Nal_Entry
/// @brief \b Struct \b Description:  Store the information of one nal entry
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32  u32NalID;       ///< the ID nunber of this nal
    MS_U32  u32NalAddr;     ///< the offset of this nal from bit stream buffer start address. unit: byte
    MS_U32  u32NalSize;     ///< the size of this nal. unit: byte
    MS_U32  u32NalPTS;      ///< the time stamp of this nal. unit: ms
    MS_BOOL  bRVBrokenPacket;      ///< the RV only
} HVD_Nal_Entry;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: RV_FileInfo
/// @brief \b Struct \b Description:  RV file information
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U16 RV_Version;      ///< Real Video Bitstream version
    MS_U16 ulNumSizes;      ///< Real Video Number sizes
    MS_U16 ulPicSizes_w[8]; ///< Real Video file width
    MS_U16 ulPicSizes_h[8]; ///< Real Video file height
} RV_FileInfo;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_FB_Reduction_Mode
/// @brief \b Struct \b Description:  Set up frame buffer reduction mode
//-----------------------------------------------------------------------------
typedef struct
{
    HVD_FBReductionType eLumaFBReductionMode;     ///< Luma frame buffer reduction mode.
    HVD_FBReductionType eChromaFBReductionMode;   ///< Chroma frame buffer reduction mode.
    MS_U8				u8EnableAutoMode;	  	  /// 0: Disable, 1: Enable
} HVD_FBReductionMode;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Init_Params
/// @brief \b Struct \b Description:  Store the initialization settings
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32ModeFlag;     ///< init mode flag, use HVD_INIT_* to setup HVD.
    MS_U32 u32FrameRate;     ///< frame rate.
    MS_U32 u32FrameRateBase;     ///< frame rate base. The value of u32FrameRate /u32FrameRateBase must be frames per sec.
    MS_U8   u8MinFrmGap;    ///< set the min frame gap.
    MS_U8   u8SyncType;         ///< HVD_Sync_Type. sync type of current playback.
    MS_U16 u16Pitch;   ///< not zero: specify the pitch. 0: use default value.
    MS_U32 u32MaxDecTick;   ///< not zero: specify the max decode tick. 0: use default value.
    MS_BOOL bSyncEachFrm;   ///< TRUE: sync STC at each frame. FALSE: not sync each frame.
    MS_BOOL bAutoFreeES;   ///< TRUE: auto free ES buffer when ES buffer is full. FALSE: not do the auto free.
    MS_BOOL bAutoPowerSaving;   ///< TRUE: auto power saving. FALSE: not do the auto power saving.
    MS_BOOL bDynamicScaling;   ///< TRUE: enable Dynamic Scaling. FALSE: disable Dynamic Scaling.
    MS_BOOL bFastDisplay;   ///< TRUE: enable Fast Display. FALSE: disable Fast Display.
    MS_BOOL bUserData;   ///< TRUE: enable processing User data. FALSE: disable processing User data.
    MS_U8 u8TurboInit;       ///< HVD_TurboInitLevel. set the turbo init mode.
    MS_U8 u8TimeUnit;   ///< HVD_Time_Unit_Type.set the type of input/output time unit.
    MS_U16 u16DecoderClock;      ///< HVD decoder clock speed. 0: default value. non-zero: any nearist clock.
    MS_U16 u16ChipECONum;    ///< Chip revision, ECO number.
    RV_FileInfo* pRVFileInfo;           ///< pointer to RV file info
    HVD_FBReductionMode stFBReduction; ///< HVD Frame buffer reduction type
} HVD_Init_Params;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_BBU_Info
/// @brief \b Struct \b Description:  Store the packet information
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32Staddr;     ///< Packet offset from bitstream buffer base address. unit: byte.
    MS_U32 u32Length;    ///< Packet size. unit: byte.
    MS_U32 u32TimeStamp;    ///< Packet time stamp. unit: ms.
    MS_U32 u32ID_L;    ///< Packet ID low part.
    MS_U32 u32ID_H;    ///< Packet ID high part.
    MS_U32 u32OriPktAddr;    ///< Original packet offset from bitstream buffer base address. unit: byte.
    MS_BOOL  bRVBrokenPacket;      ///< the RV only
} HVD_BBU_Info;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Alive_Status
/// @brief \b Struct \b Description:  Store the decoder living information
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32DecCnt;
    MS_U32 u32SkipCnt;
    MS_U32 u32IdleCnt;
    MS_U32 u32MainLoopCnt;
} HVD_Alive_Status;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_DISP_INFO_THRESHOLD
/// @brief \b Struct \b Description:  Store the disp information threshold.
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U32 u32FrmrateUpBound;       //Framerate filter upper bound
    MS_U32 u32FrmrateLowBound;      //Framerate filter lower bound
    MS_U32 u32MvopUpBound;          //mvop filter upper bound
    MS_U32 u32MvopLowBound;         //mvop filter lower bound
} HVD_Disp_Info_TH;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Settings
/// @brief \b Struct \b Description:  Store the settings of user requirment
//-----------------------------------------------------------------------------
typedef struct
{
// TODO: currently only DTV settings. Need to add more settings for MM.
// Mode
    HVD_Disp_Info_TH DispInfoTH;
    MS_U32  u32IsrEvent;
    MS_BOOL bEnISR;

    MS_U8 u8SkipMode;                   // HVD_Skip_Decode_Type
    MS_U8 bIsShowErrFrm;
    MS_U8 u8FrcMode;              //HVD_FrmRateConv_Mode

    MS_BOOL bIsErrConceal;
    MS_BOOL bAutoFreeES;
    MS_BOOL bDisDeblocking;
    MS_BOOL bDisQuarterPixel;

    MS_U8 bIsSyncOn;
    MS_U32 u32SyncTolerance;
    MS_U32 u32SyncRepeatTH;
    MS_U32 u32SyncVideoDelay;
    MS_U32 u32SyncFreeRunTH;
    MS_U32 u32MiuBurstLevel;
} HVD_Settings;





//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_CC_Info
/// @brief \b Struct \b Description:  HVD Close Caption Infomation.
//-----------------------------------------------------------------------------
typedef struct
{
    MS_U8 u8UserDataMode;
    MS_U8 u8ParsingStatus;
    MS_BOOL b708Enable;
    MS_BOOL b608InfoEnhance;
    MS_BOOL bBufMiu1[2];
    MS_BOOL bOverFlow[2];
    MS_U32 u32RingBufStartPAddr[2];//physical address
    MS_U32 u32RingBufLen[2];
    MS_U32 volatile u32RingBufVacancy[2];
    MS_U32 volatile u32RingBufRPAddr[2], u32RingBufWPAddr[2];//physical address
    MS_U32 volatile u32FWUsrDataRIdx, u32FWUsrDataWIdx;
    MS_U32 u32PktLen708;
    MS_U32 u32PktHdrAddr708;
    MS_U8 u8CC608buf[512];
    MS_U8 u8CC708buf[512];
} HVD_CC_Info;

typedef struct
{
    MS_U16 u16TmpRef;
    MS_U16 u16PicStruct;
    MS_U32 u32Pts;
    MS_U8  u8UsrDataCnt;
} HVD_CC_608EnhanceInfo;



//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Drv_Ctrl
/// @brief \b Struct \b Description:  HVD driver internal control.
//-----------------------------------------------------------------------------
typedef struct
{
// init stage
    HVD_Mem_Map MemMap;         ///< HVD memory config
    HVD_Init_Params InitParams;         ///< HVD init settings
    MS_BOOL bNoDrvProccBuf;
    MS_BOOL bAutoRmLastZeroByte;
    MS_BOOL bCannotAccessMIU256;
    MS_U32  u32CmdTimeout;          ///< HVD FW command timeout

// reset stage
    MS_U32  u32CtrlMode;            ///< HVD run-time control flag
    MS_U32  u32DummyWriteBuf;       ///< For dummy write MIU action.
    //MS_U32  u32CPUNonCacheMask;         ///< CPU non-cache mask
    MS_U32  u32NULLPacketSize;      ///< to store the size of AVI null packet pattern
    MS_U32  u32NULLPacketAddr;      ///< to store the start address of AVI null packet pattern from bitstream buffer base.
    MS_U32  u32RV_FlushPacketSize;      ///< to store the size of rm flush packet pattern
    MS_U32  u32RV_FlushPacketAddr;      ///< to store the start address of rm flush packet pattern from bitstream buffer base.
    MS_U32  u32StepDecodeCnt;
    //MS_U32  u32LastBBUPTS;
    //MS_U32  u32DummyDataSize;           ///< buffer size of dummy data.
    //MS_U32  u32RestSizeofPushDummy;
    //MS_U32  u32AddrPushDummy;
    MS_U32  u32LastESRptr;
    MS_U32  u32BBUTblInBitstreamBufAddr;
    MS_U32  u32BBUPacketCnt;
    MS_U32  u32BBUWptr_Fired;
    MS_U32  u32LastErrCode;
    //MS_BOOL bPushingDummy;
    MS_BOOL bIsDispInfoChg;
    HVD_Nal_Entry  LastNal;
    HVD_Alive_Status LivingStatus;

// recovery stage
    MS_BOOL bStepDecoding;
    HVD_Settings Settings;

    MS_U8 bTurboFWMode; //TRUE:not reload FW more than once if pre-decoder is the same.

    MS_U32 u32UsrDataRd;
    MS_U32 u32UsrDataWr;

    HVD_CC_Info CloseCaptionInfo;

    MS_U32 u32FlushRstPtr;  ///< flush rst ptr: 0: init, 1:after flush and before push packet

} HVD_Drv_Ctrl;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_ISR_Ctrl
/// @brief \b Struct \b Description:  HVD driver ISR control.
//-----------------------------------------------------------------------------
typedef struct
{
    MS_BOOL bRegISR;
    MS_BOOL bInISR;
    MS_U32  u32ISRInfo;
    HVD_ISRCallBack pfnISRCallBack;
    MS_BOOL bIsHvdIsr;
} HVD_ISR_Ctrl;

//-----------------------------------------------------------------------------
/// @brief \b Struct \b Name: HVD_Pre_Ctrl
/// @brief \b Struct \b Description:  HVD driver pre-setting control.
//-----------------------------------------------------------------------------
typedef struct
{
    MS_BOOL bOnePendingBuffer;
    MS_BOOL bFrameRateHandling;
    MS_U32  u32PreSetFrameRate;
    MS_BOOL bCorrectErrFrameRate;
    MS_U32  u32CorrectFrameRate;
    MS_U32  u32RegBase;
} HVD_Pre_Ctrl;

typedef void(*P_SC_ISR_Proc)(MS_U8 u8SCID);


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
extern MS_U32 u32UartCtrl;
extern MS_U32 u32InitSysTimeBase;

#endif // _DRV_HVD_DEF_H_

