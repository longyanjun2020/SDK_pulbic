
#ifndef __MDL_AUD_DMA_TYPES_H__
#define __MDL_AUD_DMA_TYPES_H__

//#include "mdl_aud_dma_api.h"
#include "mdl_aud_forward.h"

/**
 *  @brief The structure defines the set DMA writer buffer command
 */
struct MdlAudDmaRecSetBufAddr_t_
{
    u8  *pnBufAddr;
    u32  nBufSize;
};

/**
 *  @brief The structure defines the set DMA writer buffer threshold command
 */
struct MdlAudDmaRecSetBufThreshold_t_
{
    u32  nOverrun;
    u32  nUnderrun;
};

/**
 *  @brief The structure defines the set DMA writer init command
 */
struct MdlAudDmaRecSetSamplingRate_t_
{
    u32  nSamplingRate;
};

/**
 * \brief Audio callback
 */
typedef void (*MdlAudDmaCbFn_t)(void);

/**
 *  @brief The structure defines the register DMA writer callback command
 */
struct MdlAudDmaRecRegCallback_t_
{
    MdlAudDmaCbFn_t  tFullCb;
    MdlAudDmaCbFn_t  tOverrunCb;
    MdlAudDmaCbFn_t  tUnderrunCb;
};

/**
 *  @brief The structure defines the get buffer info command
 */
struct MdlAudDmaRecGetBufInfo_t_
{
    u32  *pnDataSize;
    bool *pbOverrun;
    bool *pbUnderrun;
};

/**
 *  @brief The structure defines the read buffer data command
 */
struct MdlAudDmaRecReadData_t_
{
    u8  *pnDestAddr;
    u32  nDataSize;
    u32 *pnActualSize;
};

/**
 *  @brief The structure defines the set DMA reader buffer command
 */
struct MdlAudDmaPlaySetBufAddr_t_
{
    u8  *pnBufAddr;
    u32  nBufSize;
};

/**
 *  @brief The structure defines the set DMA reader buffer threshold command
 */
struct MdlAudDmaPlaySetBufThreshold_t_
{
    u32  nOverrun;
    u32  nUnderrun;
};

/**
 *  @brief The structure defines the set DMA reader init command
 */
struct MdlAudDmaPlaySetSamplingRate_t_
{
    u32  nSamplingRate;
};

/**
 *  @brief The structure defines the register DMA reader callback command
 */
struct MdlAudDmaPlayRegCallback_t_
{
    MdlAudDmaCbFn_t  tEmptyCb;
    MdlAudDmaCbFn_t  tOverrunCb;
    MdlAudDmaCbFn_t  tUnderrunCb;
};

/**
 *  @brief The structure defines the get buffer info command
 */
struct MdlAudDmaPlayGetBufInfo_t_
{
    u32  *pnDataSize;
    bool *pbOverrun;
    bool *pbUnderrun;
};

/**
 *  @brief The structure defines the write buffer data command
 */
struct MdlAudDmaPlayWriteData_t_
{
    u8  *pnSrcAddr;
    u32  nDataSize;
    u32 *pnActualSize;
};
#endif // __MDL_AUD_DMA_TYPES_H__
