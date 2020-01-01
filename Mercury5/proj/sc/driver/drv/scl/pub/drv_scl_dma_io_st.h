///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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


/**
 *  @file drv_scl_dma_io_st.h
 *  @brief SCLDMA Driver IOCTL parameter interface
 */

 /**
 * \ingroup scldma_group
 * @{
 */

#ifndef __DRV_SCL_DMA_IO_ST_H__
#define __DRV_SCL_DMA_IO_ST_H__

#include "cam_os_wrapper.h"

//=============================================================================
// Defines
//=============================================================================
// library information
//1.0.1:for clean SCLDMA.
//1.1.1:for add buffer queue handler and swring mode.
//1.1.3:refine for 1.1.1 scl test OK,stabilize not yet.
#define DRV_SCLDMA_VERSION             0x0113 ///< H:Major L:minor H3:Many Change H2:adjust Struct L1:add struct L0:adjust driver
#define DRV_SCLDMA_QUEUE_OFFSET   sizeof(DrvScldmaIoFrameBufferConfig_t)///<Buffer Queue Size For OMX

//=============================================================================
// enum
//=============================================================================
/// @cond
/**
* The ID type of SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_ID_1,
    E_DRV_SCLDMA_IO_ID_2,
    E_DRV_SCLDMA_IO_ID_3,
    E_DRV_SCLDMA_IO_ID_4,
    E_DRV_SCLDMA_IO_ID_NUM,

    E_DRV_SCLDMA_IO_ID_IPW  = E_DRV_SCLDMA_IO_ID_1,
    E_DRV_SCLDMA_IO_ID_IPW2 = E_DRV_SCLDMA_IO_ID_2,
    E_DRV_SCLDMA_IO_ID_DIPR = E_DRV_SCLDMA_IO_ID_3,
    E_DRV_SCLDMA_IO_ID_IPM2 = E_DRV_SCLDMA_IO_ID_4,
}DrvSclDmaIoIdType_e;
/// @endcond

/**
* The color format of DMA buffer for  SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_COLOR_YUV422,       ///< color format: 422Pack
    E_DRV_SCLDMA_IO_COLOR_YUV420,       ///< color format: YCSep420
    E_DRV_SCLDMA_IO_COLOR_YCSep422,     ///< color format: YC422
    E_DRV_SCLDMA_IO_COLOR_YUVSep422,    ///< color format: YUVSep422
    E_DRV_SCLDMA_IO_COLOR_YUVSep420,    ///< color format: YUVSep420
    E_DRV_SCLDMA_IO_COLOR_NUM,          ///< The max number of color format
}DrvSclDmaIoColorType_e;

/**
* The memory type of DMA buffer for SCLDMA
*/
typedef enum
{
     E_DRV_SCLDMA_IO_MEM_FRM =0,  ///< memory type: FRM
     E_DRV_SCLDMA_IO_MEM_SNP =1,  ///< memory type: SNP
     E_DRV_SCLDMA_IO_MEM_FRM2 =2, ///< memory type: SNP
     E_DRV_SCLDMA_IO_MEM_IMI =3,  ///< memory type: IMI
     E_DRV_SCLDMA_IO_MEM_NUM =4,  ///< The max number of memory type
}DrvSclDmaIoMemType_e;

/**
* The buffer mode of DMA for SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_BUFFER_MD_RING,   ///< buffer mode: RING
    E_DRV_SCLDMA_IO_BUFFER_MD_SINGLE, ///< bufer mode : single
    E_DRV_SCLDMA_IO_BUFFER_MD_SWRING, ///< bufer mode : sw control ring mode
    E_DRV_SCLDMA_IO_BUFFER_MD_NUM,    ///< The max number of buffer mode
}DrvSclDmaIoBufferModeType_e;

/**
* The flag type of actived buffer for SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_ACTIVE_BUFFER_OMX      = 0x10,  ///< active buffer type: OMX,if OMX need to update Rp
    E_DRV_SCLDMA_IO_ACTIVE_BUFFER_OFF      = 0x20,  ///< acitve buffer type: OFF,if hw dma trig off
    E_DRV_SCLDMA_IO_ACTIVE_BUFFER_RINGFULL = 0x40,  ///< active buffer type: RINGFULL,if without update Rp
}DrvSclDmaIoActiveBufferType_e;

/**
* The buffer queued type of DMA for SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_BUFFER_QUEUE_TYPE_PEEKQUEUE,    ///< buffer queue type: user only to get information
    E_DRV_SCLDMA_IO_BUFFER_QUEUE_TYPE_DEQUEUE,      ///< buffer queue type: user can set Read information
    E_DRV_SCLDMA_IO_BUFFER_QUEUE_TYPE_ENQUEUE,      ///< TODO : buffer queue type: user can set Write information(not use)
    E_DRV_SCLDMA_IO_BUFFER_QUEUE_TYPE_NUM,          ///< buffer type: totally
}DrvSclDmaIoUsedBufferQueueType_e;

/// @cond
/**
* The error type of SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_ERR_OK    =  0,     ///< No Error
    E_DRV_SCLDMA_IO_ERR_FAULT = -1,     ///< Fault
    E_DRV_SCLDMA_IO_ERR_INVAL = -2,     ///< Invalid Value
    E_DRV_SCLDMA_IO_ERR_MULTI = -3,     ///< MultiInstance Fault
	E_DRV_SCLDMA_IO_ERR_TIMEOUT = -4,   ///< Timeout Fault
}DrvSclDmaIoErrType_e;
/// @endcond

/**
* The external input type of SCLDMA
*/
typedef enum
{
    E_DRV_SCLDMA_IO_EXTERNAL_INPUT_BT656,   ///< External input: BT656
    E_DRV_SCLDMA_IO_EXTERNAL_INPUT_BT601,   ///< External input: BT601
    E_DRV_SCLDMA_IO_EXTERNAL_INPUT_HVSP,    ///< External input: HVSP
    E_DRV_SCLDMA6_IO_EXTERNAL_INPUT_NUM,    ///< The max number of exteranl input type
}DrvSclDmaIoExternalInputType_e;
//=============================================================================
// struct
//=============================================================================

/**
*  The version of SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    u32   u32Version;      ///< version
    u32   VerChk_Size;     ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoVersionConfig_t;


//=============================================================================
/**
* The flag of used buffer for SCLDMA
*/
typedef struct
{
    u8  btsBase_0   : 1;  ///< base0 flag
    u8  btsBase_1   : 1;  ///< base1 flag
    u8  btsBase_2   : 1;  ///< base2 flag
    u8  btsBase_3   : 1;  ///< Base3 flag
    u8  btsReserved : 4;  ///< reserved
}DrvSclDmaIoBufferFlagBit_t;


/**
* The configuration of DMA buffer for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    union
    {
        u8  u8Flag;
        DrvSclDmaIoBufferFlagBit_t bvFlag;   ///< buffer flag
    };

    DrvSclDmaIoMemType_e   enMemType;         ///< memory type
    DrvSclDmaIoColorType_e enColorType;       ///< color type
    DrvSclDmaIoBufferModeType_e enBufMDType;  ///< buffer mode

    u16      u16BufNum;     ///< number of buffer
    u32       u32Base_Y[4]; ///< base address of Y
    u32       u32Base_C[4]; ///< base address of CbCr (Cb)
    u32       u32Base_V[4]; ///< base address of Cr
    u16      u16Width;      ///< width of buffer
    u16      u16Height;     ///< height of buffer
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoBufferConfig_t;

/**
* The triger setting of DMA buffer for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    bool       bEn;                     ///< enable/disable trigger
    DrvSclDmaIoMemType_e   enMemType;   ///< memory type
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoTriggerConfig_t;

/**
* The actived configuration of dma buffer for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    DrvSclDmaIoMemType_e   enMemType;   ///< memory type
    u8   u8ActiveBuffer;                ///< ID of ActiveBuffer
    u8   u8ISPcount;                    ///< ISP counter
    u64  u64FRMDoneTime;               ///< Time of FRMDone
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
}__attribute__ ((__packed__))DrvSclDmaIoActiveBufferConfig_t;


/// @cond
typedef void ( *pDrvSclDmaIoPollCb ) (void);        ///< DrvSclDmaIoPoll callback function

/**
* The frame buffer configuration for SCLDMA
*/
typedef struct
{
    u8   u8retval;           ///< return
    u8   u8pollval;          ///< get
    u32  u32Timeout;         ///< u32Timeout
    pDrvSclDmaIoPollCb pfnCb ; ///< callback function
}__attribute__ ((__packed__))DrvSclDmaIoPollConfig_t;
/// @endcond

/**
* The frame buffer configuration for SCLDMA
*/
typedef struct
{
    u8   u8FrameAddrIdx;       ///< ID of Frame address
    u32   u32FrameAddr;         ///< Frame Address
    u8   u8ISPcount;           ///< ISP counter
    u16   u16FrameWidth;         ///< Frame Width
    u16   u16FrameHeight;        ///< Frame Height
    u64   u64FRMDoneTime;  ///< Time of FRMDone
}__attribute__ ((__packed__))DrvScldmaIoFrameBufferConfig_t;


/**
* The queued buffer configuration for SCLDMA
*/
typedef struct
{
    u32 VerChk_Version ;                          ///< structure version
    DrvSclDmaIoMemType_e   enMemType;             ///< memory type
    DrvSclDmaIoUsedBufferQueueType_e  enUsedType; ///< queued buffer type
    DrvScldmaIoFrameBufferConfig_t stRead;        ///< frame buffer configuration
    u8  u8InQueueCount;                           ///< counter of queue
    u8  u8EnqueueIdx;                             ///< index of end queue
    u32 VerChk_Size;                              ///< structure size for version checking
}__attribute__ ((__packed__))DrvSclDmaIoBufferQueueConfig_t;

/**
* The private Id of multi-instance for SCLDMA
*/
typedef struct
{
    s32 s32Id;  ///< private ID
}DrvSclDmaIoPrivateIdConfig_t;

/**
*  The lock configuration of multi-instance for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ;  ///< structure version
    s32 *ps32IdBuf;         ///< buffer ID
    u8 u8BufSize;           ///< buffer size
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoLockConfig_t;

/**
*  The information of DMA buffer for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclDmaIoMemType_e   enMemType;           ///< memory type
    u16 u16DMAH;                                ///< horizontal size of DMA buffer
    u16 u16DMAV;                                ///< vertical size of DMA buffer
    DrvSclDmaIoColorType_e enColorType;         ///< color type
    DrvSclDmaIoBufferModeType_e enBufMDType;    ///< buffer mode
    u16   u16BufNum;                            ///< number of buffer
    u32   u32Base_Y[4];                         ///< base address of Y
    u32   u32Base_C[4];                         ///< base address of CbCr
    u32   u32Base_V[4];                         ///< base address of CbCr
    u32   VerChk_Size;                          ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoGetInformationConfig_t;


/**
*  The external input configuration of DMA buffer for SCLDMA
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclDmaIoExternalInputType_e  enInput;    ///< external input type
    u32   VerChk_Size;                          ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclDmaIoExternalInputConfig_t;


/**
*  The information external input configuration of DMA buffer for SCLDMA
*/
typedef struct
{
    DrvSclDmaIoExternalInputType_e  enInput;    ///< External input type
    u16 u16Width;                               ///< horizontal size of external input
    u16 u16Height;                              ///< vertical size of external input
    bool bStabel;                               ///< signal status of external input
}__attribute__ ((__packed__)) DrvSclDmaIoExternalInputInformConfig_t;

typedef struct
{
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetInBufferConfig)(s32 s32Handler, DrvSclDmaIoBufferConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetInTriggerConfig)(s32 s32Handler, DrvSclDmaIoTriggerConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetOutBufferConfig)(s32 s32Handler, DrvSclDmaIoBufferConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetOutTriggerConfig)(s32 s32Handler, DrvSclDmaIoTriggerConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoGetInformationConfig)(s32 s32Handler, DrvSclDmaIoGetInformationConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoGetInActiveBufferConfig)(s32 s32Handler, DrvSclDmaIoActiveBufferConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoGetOutActiveBufferConfig)(s32 s32Handler, DrvSclDmaIoActiveBufferConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoBufferQueueHandleConfig)(s32 s32Handler, DrvSclDmaIoBufferQueueConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoGetPrivateIdConfig)(s32 s32Handler, DrvSclDmaIoPrivateIdConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetLockConfig)(s32 s32Handler, DrvSclDmaIoLockConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetUnlockConfig)(s32 s32Handler, DrvSclDmaIoLockConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoGetVersion)(s32 s32Handler, DrvSclDmaIoVersionConfig_t *pstIoInCfg);
    DrvSclDmaIoErrType_e (*DrvSclDmaIoSetExternalInputConfig)(s32 s32Handler, DrvSclDmaIoExternalInputConfig_t *pstIoInCfg);
}DrvSclDmaIoFunctionConfig_t;

//=============================================================================

#endif //

/** @} */ // end of scldma_group
