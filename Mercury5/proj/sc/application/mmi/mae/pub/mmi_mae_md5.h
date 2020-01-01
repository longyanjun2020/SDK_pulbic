/**
 * @file mmi_mae_md5.h
 *
 * @brief This header file defines the interface of MD5 encoder functions.
 *
 * @version $Id: mmi_mae_md5.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MMI_MAE_MD5_H__
#define __MMI_MAE_MD5_H__
#include "mmi_mae_common_def.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/* Structure of MD5 context */
typedef struct
{
  u32 nSeed[4];               ///< seed for next round
  u32 nCount[2];              ///< number of bits, mod 2^64
  u8  nBuffer[64];            ///< data buffer
}MD5Context_t;

/*=============================================================*/
// Functions
/*=============================================================*/

/**
 * MAE_MD5Init(MD5Context_t *pContext)
 *
 * @brief	This function initilizes the given MD5 context.
 *
 * @param[in]   pContext(MD5Context_t*)    Pointer of MD5Context_t
 */
void MAE_MD5Init(MD5Context_t *pContext);

/**
 * MAE_MD5Update(MD5Context_t *pContext, const u8 *pData, u32 nLen)
 *
 * @brief	This function encodes the input data and update the MD5 context
 *
 * @param[in]   pContext(MD5Context_t*)    Pointer of MD5Context_t
 * @param[in]   pData(u8*)                 Pointer of input data ( u8 string )
 * @param[in]   nLen(u32)                   Length of input data
 */
void MAE_MD5Update(MD5Context_t *pContext, const u8 *pData, u32 nLen);

/**
 * MAE_MD5Final(u8 *pDigest, MD5Context_t *pContext)
 *
 * @brief	This function finalizes MD5 encoding and outputs the result
 *
 * @param[out]   pDigest(u8*)               Pointer of output data ( u8 string )
 * @param[in]    pContext(MD5Context_t*)    Pointer of MD5Context_t
 *
 * @note The size of pDigest must >= 16, because the MD5 output is 128 bits.
 */
void MAE_MD5Final(u8 *pDigest, MD5Context_t *pContext);

/**
 * MAE_MD5Encode(u8 *pDigest, const u8 *pData, u32 nLen)
 *
 * @brief	This function encodes input data with MD5 outputs the result
 *
 * @param[out]   pDigest(u8*)               Pointer of output data ( u8 string )
 * @param[in]    pData(u8*)                 Pointer of input data ( u8 string )
 * @param[in]    nLen(u32)                   Size of input data
 *
 * @note The size of pDigest must >= 16, because the MD5 output is 128 bits.
 */
void MAE_MD5Encode(u8 *pDigest, const u8 *pData, u32 nLen);

#endif /* __MAE_MD5_H__ */
