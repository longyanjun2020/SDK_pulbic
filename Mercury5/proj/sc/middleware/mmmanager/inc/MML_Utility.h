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
* @file    MML_Utility.h
* @version
* @brief
*
*/

#ifndef __MML_UTILITY_H__
#define __MML_UTILITY_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlutility_api.h" // Lib release stage1's workaround
#if defined (__SDK_SIMULATION__)
#include "bsp.h"
#endif
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MML_RING_HEAD_SIGNATURE         (0x1C2D3E4F)
#define MML_RING_TAIL_SIGNATURE         (0xB6C7D8E9)

#define MML_RGB565_RED                  (0xF800)
#define MML_RGB565_GREEN                (0x07E0)
#define MML_RGB565_BLUE		            (0x001F)
#define MML_RGB565_WHITE		        (0xFFFF)
#define MML_CHAR_WIDTH		            (11)                /* Character width, including border line */
#define MML_CHAR_HEIGHT		            (24)                /* Character height */
#define MML_CHAR_SPACE_WIDTH	        (1)                 /* Border line width */
#define MML_DRAW_WIDTH		            (MML_CHAR_WIDTH)
#define MML_DRAW_HEIGHT	                (MML_CHAR_HEIGHT)

/* Font size in bytes = Width*(Height-Space)/8-bits */
#define MML_FONT_DATA_SIZE_PER_CHAR     ((MML_CHAR_HEIGHT)*((MML_CHAR_WIDTH)-(MML_CHAR_SPACE_WIDTH))/8)
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    FLASH_TYPE_NAND = 0,
    FLASH_TYPE_NOR,
	FLASH_TYPE_SPI

} MmlFlashType_e;

typedef enum
{
    EMI_MODE_SINGLE = 0,
    EMI_MODE_PAGE,
    EMI_MODE_BURST_WRITE,
    EMI_MODE_BURST_READ = 4,
    EMI_MODE_BURST_RW = 6
} MmlEmiMode_e;

typedef struct
{
	MmlFlashType_e	eFlashType;
	MmlEmiMode_e    ePsram_OpMode ;
	MmlEmiMode_e    eNor_OpMode ;
}MmlMcpOpMode;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#if !defined(__SDK_SIMULATION__)
void MmlDisplayColorDraw
(
    u16     nColor
);

void MmlDisplayTextDraw
(
    u16     nForeGroundColor,
    u16     nBackgroundColor,
    u8      *pAsciiString
);
#endif

MmlUtilityResult_e MmlFileGetFileNameUtility
(
    MmlFileGetFileNameType_e eGetFileType,
    MmlFileNameInfo_t *pFileNameType,
    MmlFilenameFormat_e eFilenameFormat,
    u16* dest,
    u32 nBytes
);

void MmlAssertWrap(u32 nValue);
void *MmlMemcpyWrap(void *pDst, void *pSrc, u32 nSize);
void MmlGetMcpTypeWrap(MmlMcpOpMode *pMcpOpMode);
void MmlDelayWrap(u32 nDelay);
void MmlEnableDMC_CLKGating(u8 bEnable);
#if defined (__SDK_SIMULATION__)
void MmlGetChipTypeWrap(SysPlatformChipType_e *pPlatformChipType);
#endif
#ifdef __cplusplus
}
#endif

#endif //__MML_UTILITY_H__
