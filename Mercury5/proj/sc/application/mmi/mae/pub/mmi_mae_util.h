/**
 * @file mmi_mae_util.h
 *
 * This header file declares the function prototypes for dumping/logging kernel status,
 * and other miscellaneous purposes.
 *
 * @version $Id: mmi_mae_util.h 1538 2009-08-05 10:50:03Z kenny.wu $
 */
#ifndef __MMI_MAE_UTIL_H__
#define __MMI_MAE_UTIL_H__

//
// header files
//
#include "mmi_mae_common_def.h"


//
// definitions and prototypes
//

/// functions for dumping Shell and APM's status information, activity history, and/or
/// state machine objects' transition history to the backtrace buffer or the trace task
void MAE_DumpInfo(void);
void MAE_Backtrace(void);
void MAE_SMO_DumpInfo(MAEClsId_t);

/// function for dumping information of the static media service object
void MAEMedia_ShowClientItemInfo(void);

/// function to enable/disable raising exception for MAE serious errors
void MAE_Option_HaltOnSeriousError(boolean bEnable);


/**
 * @brief Get decompresse data (Normally, this api is for allocting destination memory size)
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 *
 * @return u32           : The data decompressed length.
 */
u32 MAE_GetDecompressSize(u8 *pComData, u32 sourcelen);

/**
 * @brief Decompress api which compressed by MSComprs.exe
 *
 * @param pComData       : Compressed data (source)
 * @param sourcelen      : Compressed data length (source length)
 * @param pComDstBuffer      : Decompressed data  (Destitation)
 * @param totalProcessLen      : Decompressed data length (Destitation length), get from MAE_GetDecompressSize
 *
 * @return TRUE          : decompress success.
 * @return FAIL          : decompress fail.
 */
boolean MAE_Decompress(u8 *pComData, u32 sourcelen, u8 *pComDstBuffer, u32 totalProcessLen);

boolean MAE_DecompressByIndex(u8 *pComData, u32 sourcelen, u8 *pComDstBuffer, u32 totalProcessLen);
#endif // __MAE_UTIL_H__
