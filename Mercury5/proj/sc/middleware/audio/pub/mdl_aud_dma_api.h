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
* @file    mdl_aud_dma_api.h
* @version
* @brief   Abscontainer middleware audio header file
*
*/

#ifndef __MDL_AUD_DMA_API_H__
#define __MDL_AUD_DMA_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
// #include mdl_audio.h" is replaced by the following three header
//#include "hal_audio.h"
#include "vm_audio_api.h"
#include "mdl_audio_pub_api.h"

#include "mdl_aud_pub_api.h"
#include "mdl_aud_forward.h"
#include "mdl_aud_dma_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * \brief Audio callback
 */
//typedef void (*MdlAudDmaCbFn_t)(void);

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/**
 * @brief This function is used to Reset DMA
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaResetReq(void);

/**
 * @brief This function is used to set DMA writer buffer address
 *
 * @param  pnBufAddr                    : Buffer address
 * @param  nBufSize                     : Buffer size
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecSetBufAddrReq(u8 *pnBufAddr, u32 nBufSize);

/**
 * @brief This function is used to set DMA writer buffer threshold
 *
 * @param  nOverrun                     : Overrun threshold
 * @param  nUnderrun                    : Underrun threshold
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecSetBufThresholdReq(u32 nOverrun, u32 nUnderrun);

/**
 * @brief This function is used to initialize DMA writer
 *
 * @param  eSamplingRate                : Sampling rate
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecSetSamplingRateReq(u32 nSamplingRate);

/**
 * @brief This function is used to register callback function for DMA writer
 *
 * @param  tFullCb                      : Buffer full callback
 * @param  tOverrunCb                   : Overrun callback
 * @param  tUnderrunCb                  : Underrun callback
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecRegCallbackReq(MdlAudDmaCbFn_t tFullCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);

/**
 * @brief This function is used to get information of DMA writer
 *
 * @param  pnDataSize                   : Available Data size in the buffer
 * @param  pbOverrun                    : Is buffer overrun?
 * @param  pbUnderrun                   : Is buffer underrun?
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecGetBufInfoReq(u32 *pnDataSize, bool *pbOverrun, bool *pbUnderrun);

/**
 * @brief This function is used to control DMA interrupt
 *
 * @param  bFull                        : Enable / disable full interrupt
 * @param  bOverrun                     : Enable / disable overrun interrupt
 * @param  bUnderrun                    : Enable / disable underrun interrupt
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecCtrlIntReq(bool bFull, bool bOverrun, bool bUnderrun);

/**
 * @brief This function is used to read data from DMA buffer
 *
 * @param  pnDestAddr                   : Destination address
 * @param  nDataSize                    : Data size which user want to read
 * @param  pnActualSize                 : [out] data size which user actually read
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecReadDataReq(u8 *pnDestAddr, u32 nDataSize, u32 *pnActualSize);

/**
 * @brief This function is used to read data from DMA buffer (Asynchronous API)
 *
 * @param  pnDestAddr                   : Destination address
 * @param  nDataSize                    : Data size which user want to read
 * @param  pnActualSize                 : [out] Data size which user actually read
 * @param  ptAudCb                      : Callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecReadDataAsyncReq(u8 *pnDestAddr, u32 nDataSize, u32 *pnActualSize, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to start recordng
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecStartReq(void);

/**
 * @brief This function is used to stop recordng
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecStopReq(void);

/**
 * @brief This function is used to pause recordng
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecPauseReq(void);

/**
 * @brief This function is used to resume recordng
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaRecResumeReq(void);

/**
 * @brief This function is used to set DMA reader buffer address
 *
 * @param  pnBufAddr                    : Buffer address
 * @param  nBufSize                     : Buffer size
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlaySetBufAddrReq(u8 *pnBufAddr, u32 nBufSize);

/**
 * @brief This function is used to set DMA reader buffer threshold
 *
 * @param  nOverrun                     : Overrun threshold
 * @param  nUnderrun                    : Underrun threshold
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlaySetBufThresholdReq(u32 nOverrun, u32 nUnderrun);

/**
 * @brief This function is used to initialize DMA reader
 *
 * @param  eSamplingRate                : Sampling rate
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlaySetSamplingRateReq(u32 nSamplingRate);

/**
 * @brief This function is used to register callback function for DMA reader
 *
 * @param  tEmptyCb                     : Buffer empty callback
 * @param  tOverrunCb                   : Overrun callback
 * @param  tUnderrunCb                  : Underrun callback
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayRegCallbackReq(MdlAudDmaCbFn_t tEmptyCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);

/**
 * @brief This function is used to get information of DMA reader
 *
 * @param  pnDataSize                   : Data written in buffer
 * @param  pbOverrun                    : Is buffer overrun?
 * @param  pbUnderrun                   : Is buffer underrun?
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayGetBufInfoReq(u32 *pnDataSize, bool *pbOverrun, bool *pbUnderrun);

/**
 * @brief This function is used to control DMA interrupt
 *
 * @param  bEmpty                       : Enable / disable empty interrupt
 * @param  bOverrun                     : Enable / disable overrun interrupt
 * @param  bUnderrun                    : Enable / disable underrun interrupt
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayCtrlIntReq(bool bEmpty, bool bOverrun, bool bUnderrun);

/**
 * @brief This function is used to write data to DMA buffer
 *
 * @param  pnSrcAddr                    : Source address
 * @param  nDataSize                    : Data size which user want to write
 * @param  pnActualSize                 : [out] Data size which user actually write
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayWriteDataReq(u8 *pnSrcAddr, u32 nDataSize, u32 *pnActualSize);

/**
 * @brief This function is used to write data to DMA buffer (Asynchronous API)
 *
 * @param  pnSrcAddr                    : Source address
 * @param  nDataSize                    : Data size which user want to write
 * @param  pnActualSize                 : [out] Data size which user actually write
 * @param  ptAudCb                      : Callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayWriteDataAsyncReq(u8 *pnSrcAddr, u32 nDataSize, u32 *pnActualSize, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to start playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayStartReq(void);

/**
 * @brief This function is used to stop playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayStopReq(void);

/**
 * @brief This function is used to pause playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayPauseReq(void);

/**
 * @brief This function is used to resume playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayResumeReq(void);

/**
 * @brief This function is used to pause playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayPowerSavingPauseReq(void);

/**
 * @brief This function is used to resume playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPlayPowerSavingResumeReq(void);

/**
 * @brief  This function is used to set fade-out.
 *
 * @param                               : None
 *
 * @return DRV_AUDIO_RET_OK             : Request success
 * @return DRV_AUDIO_RET_PARAM_ERROR    : Incorrect parameter setting
 * @return DRV_AUDIO_RET_WRONG_STATE    : Wrong state
 * @return DRV_AUDIO_RET_FAIL           : Request fail
 */
MdlAudRet_e MdlAudDmaPlaySetFadeOutReq(void);

/**
 * @brief  This function is used to set fade-in.
 *
 * @param                               : None
 *
 * @return DRV_AUDIO_RET_OK             : Request success
 * @return DRV_AUDIO_RET_PARAM_ERROR    : Incorrect parameter setting
 * @return DRV_AUDIO_RET_WRONG_STATE    : Wrong state
 * @return DRV_AUDIO_RET_FAIL           : Request fail
 */
MdlAudRet_e MdlAudDmaPlaySetFadeInReq(void);

/**
 * @brief This function is used to Reset DMA
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2ResetReq(void);

/**
 * @brief This function is used to set DMA2 reader buffer address
 *
 * @param  pnBufAddr                    : Buffer address
 * @param  nBufSize                     : Buffer size
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlaySetBufAddrReq(u8 *pnBufAddr, u32 nBufSize);

/**
 * @brief This function is used to set DMA2 reader buffer threshold
 *
 * @param  nOverrun                     : Overrun threshold
 * @param  nUnderrun                    : Underrun threshold
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlaySetBufThresholdReq(u32 nOverrun, u32 nUnderrun);

/**
 * @brief This function is used to initialize DMA2 reader
 *
 * @param  eSamplingRate                : Sampling rate
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlaySetSamplingRateReq(u32 nSamplingRate);

/**
 * @brief This function is used to register callback function for DMA2 reader
 *
 * @param  tEmptyCb                     : Buffer empty callback
 * @param  tOverrunCb                   : Overrun callback
 * @param  tUnderrunCb                  : Underrun callback
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayRegCallbackReq(MdlAudDmaCbFn_t tEmptyCb, MdlAudDmaCbFn_t tOverrunCb, MdlAudDmaCbFn_t tUnderrunCb);

/**
 * @brief This function is used to get information of DMA2 reader
 *
 * @param  pnDataSize                   : Data written in buffer
 * @param  pbOverrun                    : Is buffer overrun?
 * @param  pbUnderrun                   : Is buffer underrun?
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayGetBufInfoReq(u32 *pnDataSize, bool *pbOverrun, bool *pbUnderrun);

/**
 * @brief This function is used to control DMA2 interrupt
 *
 * @param  bEmpty                       : Enable / disable empty interrupt
 * @param  bOverrun                     : Enable / disable overrun interrupt
 * @param  bUnderrun                    : Enable / disable underrun interrupt
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayCtrlIntReq(bool bEmpty, bool bOverrun, bool bUnderrun);

/**
 * @brief This function is used to write data to DMA2 buffer
 *
 * @param  pnSrcAddr                    : Source address
 * @param  nDataSize                    : Data size which user want to write
 * @param  pnActualSize                 : [out] Data size which user actually write
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayWriteDataReq(u8 *pnSrcAddr, u32 nDataSize, u32 *pnActualSize);

/**
 * @brief This function is used to write data to DMA2 buffer (Asynchronous API)
 *
 * @param  pnSrcAddr                    : Source address
 * @param  nDataSize                    : Data size which user want to write
 * @param  pnActualSize                 : [out] Data size which user actually write
 * @param  ptAudCb                      : Callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayWriteDataAsyncReq(u8 *pnSrcAddr, u32 nDataSize, u32 *pnActualSize, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to start playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayStartReq(void);

/**
 * @brief This function is used to stop playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayStopReq(void);

/**
 * @brief This function is used to pause playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayPauseReq(void);

/**
 * @brief This function is used to resume playing
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDma2PlayResumeReq(void);

/**
 * @brief This function is used to
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudDmaPowerSavingResetReq(void);

#endif //__MDL_AUD_DMA_API_H__

