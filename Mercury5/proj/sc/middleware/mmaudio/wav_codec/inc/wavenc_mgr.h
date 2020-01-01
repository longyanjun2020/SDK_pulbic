///////////////////////////////////////////////////////////////////////////////
// File   : wavencc_mgr.h
// Author : MStar Semiconductor Inc.(CA.Wang)
// Brief  : Manage all wav encorder IPs.
///////////////////////////////////////////////////////////////////////////////
#ifndef __WAVENC_MGR_H__
#define __WAVENC_MGR_H__


//=============================================================================
// Include Files
//=============================================================================
#include "wavenc_mgr_datatype.h"

// include encorders
#if defined(ENABLE_WAVENC_IMAADPCM)
#include "ima_adpcm_enc.h"
#else
#define IMAADPCM_HEADER_SIZE 0
#endif

#if defined (ENABLE_WAVENC_MSADPCM)
#include "ms_adpcm_enc.h"
#else
#define MSADPCM_HEADER_SIZE 0
#endif


//=============================================================================
// Function Define
//=============================================================================

//======== Print Message Switch========
#define ENABLE_WAVENC_MGR_DBG_PRINTF




//=============================================================================
// Define
//=============================================================================

//----------- Print  --------------
#ifdef ENABLE_WAVENC_MGR_DBG_PRINTF
#ifndef ON_MONTAGE
#define WAVENC_MGR_DBG_MSG       printf
#else
#define WAVENC_MGR_DBG_MSG       printf
#endif
#else
#ifndef ON_MONTAGE
#define WAVENC_MGR_DBG_MSG
#else
#define WAVENC_MGR_DBG_MSG(fmt, args...)
#endif
#endif

#ifdef ENABLE_WAVENC_MGR_DBG_PRINTF
#ifndef ON_MONTAGE
#define WAVENC_MGR_DBG_MSG       printf
#else
#define WAVENC_MGR_DBG_MSG       printf
#endif
#else
#ifndef ON_MONTAGE
#define WAVENC_MGR_DBG_MSG
#else
#define WAVENC_MGR_DBG_MSG(fmt, args...)
#endif
#endif




//=============================================================================
// Mgr Structure/Paramater
//=============================================================================



//=============================================================================
// Extern Function Declare
//=============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

//#if defined(ENABLE_WAVENC_IMAADPCM)

//-----------------------------------------------------------------------------
//                      IMA-ADPCM 3 BITs Encoder
//-----------------------------------------------------------------------------
S32 wavenc_imaadpcm3bit_open( void *pInst,
                                          S32 S32dtx_enable,
                                          U32 *u32samplebuffer_addr,
                                          U32 *u32bits_per_sample,
                                          U32 *u32sample_rate,
                                          U32 *u32frame_length,
                                          U32 *u32channels,
                                          U32 *u32para);
S32 wavenc_imaadpcm3bit_data( void *pInst,
                                         S32 *out_size,
                                         U32 *u32rectotaltime,
                                         U32 *u32rectotalsize,
                                         S32 s32first_frame );
S32 wavenc_imaadpcm3bit_timestamp( void *pInst,
                                                 U32 *pu32Pos );

void wavenc_imaadpcm3bit_engineclock( void *pInst,
                                                    U8 onoff );
S32 wavenc_imaadpcm3bit_close( void *pInst );
S32 wavenc_imaadpcm3bit_write_close(void *pinst ,S32 *seek_offt, S32 *wsize, U8** wsrcptr);

//-----------------------------------------------------------------------------
//                      IMA-ADPCM 4 BITs Encoder
//-----------------------------------------------------------------------------
S32 wavenc_imaadpcm4bit_open_append( void *pInst,
                                          S32 S32dtx_enable,
                                          U32 *u32samplebuffer_addr,
                                          U32 *u32bits_per_sample,
                                          U32 *u32sample_rate,
                                          U32 *u32frame_length,
                                          U32 *u32channels,
                                          U32 *u32para);
S32 wavenc_imaadpcm4bit_open( void *pInst,
                                          S32 S32dtx_enable,
                                          U32 *u32samplebuffer_addr,
                                          U32 *u32bits_per_sample,
                                          U32 *u32sample_rate,
                                          U32 *u32frame_length,
                                          U32 *u32channels,
                                          U32 *u32para);

S32 wavenc_imaadpcm4bit_data_append_begin( void *pInst,
                                         S32 *out_size,
                                         U32 *u32rectotaltime,
                                         U32 *u32rectotalsize,
                                         S32 s32first_frame );

S32 wavenc_imaadpcm4bit_data_append_continue( void *pInst,
                                         S32 *out_size,
                                         U32 *u32rectotaltime,
                                         U32 *u32rectotalsize,
                                         S32 s32first_frame );

S32 wavenc_imaadpcm4bit_data( void *pInst,
                                         S32 *out_size,
                                         U32 *u32rectotaltime,
                                         U32 *u32rectotalsize,
                                         S32 s32first_frame );
S32 wavenc_imaadpcm4bit_timestamp( void *pInst,
                                                 U32 *pu32Pos );

void wavenc_imaadpcm4bit_engineclock( void *pInst,
                                                    U8 onoff );
S32 wavenc_imaadpcm4bit_close( void *pInst );
S32 wavenc_imaadpcm4bit_write_close(void *pinst ,S32 *seek_offt, S32 *wsize, U8** wsrcptr);

//#endif


//#if defined(ENABLE_WAVENC_MSADPCM)

//-----------------------------------------------------------------------------
//                      MS-ADPCM 4 BITs Encoder
//-----------------------------------------------------------------------------
S32 wavenc_msadpcm4bit_open( void *pInst,
                                          S32 S32dtx_enable,
                                          U32 *u32samplebuffer_addr,
                                          U32 *u32bits_per_sample,
                                          U32 *u32sample_rate,
                                          U32 *u32frame_length,
                                          U32 *u32channels,
                                          U32 *u32para);
S32 wavenc_msadpcm4bit_data( void *pInst,
                                         S32 *out_size,
                                         U32 *u32rectotaltime,
                                         U32 *u32rectotalsize,
                                         S32 s32first_frame );
S32 wavenc_msadpcm4bit_timestamp( void *pInst,
                                                 U32 *pu32Pos );

void wavenc_msadpcm4bit_engineclock( void *pInst,
                                                    U8 onoff );
S32 wavenc_msadpcm4bit_close( void *pInst );
S32 wavenc_msadpcm4bit_write_close(void *pinst ,S32 *seek_offt, S32 *wsize, U8** wsrcptr);

//#endif

#ifdef __cplusplus
}
#endif



#endif


