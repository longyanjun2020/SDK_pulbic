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
* @file    mdl_cmp.h
* @version
* @brief   This file defines compress prototype and data structure
*
*/

#ifndef __PRIVATE_MDL_COMPRESS_H__
#define __PRIVATE_MDL_COMPRESS_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"


/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Macro definition
/*=============================================================*/



/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct CompressHeader_s {
	unsigned long     orignal_imageSize;    /* original image size (bytes)*/
	unsigned long     compressedSize;       /* compressed image size (bytes)*/
	unsigned long     comType;              /* compress algorithm type */
	unsigned long     reserved;             /* reserved*/
} CompressHeader_t;


typedef enum
{
    CMP_SMALL_FLZF_TYPE,
    CMP_SMALL_LZF_TYPE,
    CMP_SMALL_ZLIB_TYPE,
    CMP_SMALL_LZMA2_TYPE,
    CMP_SMALL_MAX_TYPE
} cmp_CompressSmallType_t;


typedef enum
{
    CMP_LARGE_DATA,
    CMP_SMALL_DATA,
    CMP_PAGE_DATA,
    CMP_MAE_DATA,
} cmp_CompressData_t;


/*=============================================================*/
// Local function definition
/*=============================================================*/

#endif /* __PRIVATE_MDL_COMPRESS_H__ */


