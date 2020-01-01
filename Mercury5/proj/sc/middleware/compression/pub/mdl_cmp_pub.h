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
* @file    mdl_cmp_pub.h
* @version
* @brief   This file defines compress prototype and data structure
*
*/

#ifndef __PRIVATE_MDL_COMPRESS_PUB_H__
#define __PRIVATE_MDL_COMPRESS_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"



/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef struct CompressHeaderSmall_s {
	unsigned short     orignal_imageSize;    /* original image size (bytes)*/
	unsigned short     compressedSize;       /* compressed image size (bytes)*/
	unsigned char      comType;              /* compress algorithm type */
} CompressHeaderSmall_t;


typedef enum
{
    CMP_FLZF_TYPE = 0x6698,
    CMP_LZF_TYPE = 0x6699,
    CMP_ZLIB_TYPE = 0x6700,
    CMP_LZMA2_TYPE = 0x6701,
    CMP_MAX_TYPE
} cmp_CompressType_t;


typedef enum
{
    LZMA_NORMAL = 0,
    LZMA_BOOT   = 1 << 0,
    LZMA_BOOT2  = 1 << 1,
    LZMA_DICT   = 1 << 2,
    LZMA_DICT2  = 1 << 3,
} LZMA_SOURCE_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @brief Get decompresse data (Normally, this api is for allocting destination memory size)
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return u32           : The data decompressed length.
 */
u32 MdlCmpCheckSize(u8 *pComData, u32 sourcelen);


/**
 * @brief Get decompresse data for Small data compression (Normally, this api is for allocting destination memory size)
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return u32           : The data decompressed length.
 */
u32 MdlCmpCheckSizeSmall(u8 *pComData, u32 sourcelen);


/**
 * @brief Decompress api which compressed by MSComprs.exe
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return TRUE          : decompress success.
 * @return FAIL          : decompress fail.
 */
bool MdlCmpDecompress(u8 *pComData, u32 sourcelen, u8 *pComDstBuffer, u32 totalProcessLen, u32 parameter);

/**
 * @brief Decompress api which compressed by MSComprs.exe
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return TRUE          : decompress success.
 * @return FAIL          : decompress fail.
 */
bool MdlCmpDecompressMae(u8 *pComData, u32 sourcelen, u8 *pComDstBuffer, u32 totalProcessLen, u32 parameter);

/**
 * @brief Decompress api which compressed by MSComprs.exe (for Small data compression)
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return TRUE          : decompress success.
 * @return FAIL          : decompress fail.
 */
bool MdlCmpDecompressSmall(u8 *pComData, u32 sourcelen, u8 *pComDstBuffer, u32 totalProcessLen, u32 parameter);


/**
 * @brief Decompress by index api which compressed by MSComprs.exe
 *
 * @param index          : Decompress index (block)
 * @param pComData       : Compressed data (source)
 *
 * @return TRUE          : decompress success.
 * @return FAIL          : decompress fail.
 */
bool MdlCmpDecompressByIndex(u32 index,u8 *pComData, u8 *pComDstBuffer, u32 totalProcessLen, u32 parameter);

/**
 * @brief Compress api which compressed by MSComprs.exe
 *
 * @param type            : Compresse type (source)
 * @param pSrcData        : Compresse data (source data)
 * @param sourcelen       : Compresse data length (source length)
 * @param pDstBuffer      : Compressed buffer (destination data)
 * @param dstLen          : Compressed buffer length
 *                          (destination length, fill compress result length when return TRUE)
 * @return TRUE           : Compress success.
 * @return FAIL           : Compress fail.
 */
bool MdlCmpcompress(cmp_CompressType_t type, u8 *pSrcData, u32 sourcelen, u8 *pDstBuffer, u32 *dstLen);


/**
 * @brief Compress api which compressed by MSComprs.exe (for Small data compression)
 *
 * @param type            : Compresse type (source)
 * @param pSrcData        : Compresse data (source data)
 * @param sourcelen       : Compresse data length (source length)
 * @param pDstBuffer      : Compressed buffer (destination data)
 * @param dstLen          : Compressed buffer length
 *                          (destination length, fill compress result length when return TRUE)
 * @return TRUE           : Compress success.
 * @return FAIL           : Compress fail.
 */
bool MdlCmpcompressSmall(cmp_CompressType_t type, u8 *pSrcData, u32 sourcelen, u8 *pDstBuffer, u32 *dstLen);


/**
 * @brief Dump error pattern
 *
 * @param pSrc            : Source pointer
 * @param nSrcLen         : Source length
 * @param pDst            : Destination pointer
 * @param pDstLen         : Destination length pointer
 * @param nErrNo          : Error code
 */
void MdlDumpDecompressError(u8 *pSrc, u32 nSrcLen, u8 *pDst, u32 *pDstLen, s32 nErrNo);

#endif /* __PRIVATE_MDL_COMPRESS_PUB_H__ */


