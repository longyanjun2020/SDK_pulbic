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
 *  @file mdrv_hvsp_io_st.h
 *  @brief hvsp Driver struct parameter interface
 */

/**
* \ingroup hvsp_group
* @{
*/

#ifndef __DRV_SCL_HVSP_IO_H__
#define __DRV_SCL_HVSP_IO_H__

//=============================================================================
// Defines
//=============================================================================
#define DRV_SCLHVSP_VERSION                        0x0100


//=============================================================================
// enum
//=============================================================================

typedef enum
{
    E_DRV_SCLHVSP_ID_1,
    E_DRV_SCLHVSP_ID_2,
    E_DRV_SCLHVSP_ID_3,
    E_DRV_SCLHVSP_ID_NUM,
} DrvSclHvspIdType_e;


/**
* Used to setup the input source of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_SRC_ISP,       ///< input source: ISP
    E_DRV_SCLHVSP_SRC_BT656,     ///< input source: BT656
    E_DRV_SCLHVSP_SRC_DRAM,      ///< input source: DRAM
    E_DRV_SCLHVSP_SRC_HVSP,      ///< input source: HVSP1
    E_DRV_SCLHVSP_SRC_PAT_TGEN,  ///< input source: PATGEN
    E_DRV_SCLHVSP_SRC_NUM,       ///< The max number of input source
} DrvSclHvspSrcType_e;

/**
* Used to setup the color format of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_COLOR_RGB,     ///< color format:RGB
    E_DRV_SCLHVSP_COLOR_YUV444,  ///< color format:YUV444
    E_DRV_SCLHVSP_COLOR_YUV422,  ///< color format:YUV422
    E_DRV_SCLHVSP_COLOR_YUV420,  ///< color format:YUV420
    E_DRV_SCLHVSP_COLOR_NUM,     ///< The max number of color format
} DrvSclHvspColorType_e;

/**
* Used to setup the IPR/W status of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_MCNR_YCM_R  = 0x1,    ///< IP only read
    E_DRV_SCLHVSP_MCNR_YCM_W  = 0x2,    ///< IP only write
    E_DRV_SCLHVSP_MCNR_YCM_RW = 0x3,    ///< IP R/W
    E_DRV_SCLHVSP_MCNR_CIIR_R = 0x4,    ///< IP only read
    E_DRV_SCLHVSP_MCNR_CIIR_W = 0x8,    ///< IP only write
    E_DRV_SCLHVSP_MCNR_CIIR_RW = 0xC,    ///< IP R/W
    E_DRV_SCLHVSP_MCNR_NON = 0x10,    ///< IP none open
} DrvSclHvspMcnrType_e;

/**
* Used to setup the OSD locate of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_OSD_LOC_AFTER  = 0,    ///< after hvsp
    E_DRV_SCLHVSP_OSD_LOC_BEFORE = 1,    ///< before hvsp
} DrvSclHvspOsdLocType_e;

/**
* Used to setup the FB locate of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_FBMG_SET_LDCPATH_ON      = 0x1,
    E_DRV_SCLHVSP_FBMG_SET_LDCPATH_OFF     = 0x2,
    E_DRV_SCLHVSP_FBMG_SET_DNR_Read_ON     = 0x4,
    E_DRV_SCLHVSP_FBMG_SET_DNR_Read_OFF    = 0x8,
    E_DRV_SCLHVSP_FBMG_SET_DNR_Write_ON    = 0x10,
    E_DRV_SCLHVSP_FBMG_SET_DNR_Write_OFF   = 0x20,
    E_DRV_SCLHVSP_FBMG_SET_DNR_BUFFER_1    = 0x40,
    E_DRV_SCLHVSP_FBMG_SET_DNR_BUFFER_2    = 0x80,
    E_DRV_SCLHVSP_FBMG_SET_UNLOCK          = 0x100,
    E_DRV_SCLHVSP_FBMG_SET_DNR_COMDE_ON    = 0x200,
    E_DRV_SCLHVSP_FBMG_SET_DNR_COMDE_OFF   = 0x400,
    E_DRV_SCLHVSP_FBMG_SET_DNR_COMDE_265OFF   = 0x800,
    E_DRV_SCLHVSP_FBMG_SET_PRVCROP_ON      = 0x1000,
    E_DRV_SCLHVSP_FBMG_SET_PRVCROP_OFF     = 0x2000,
    E_DRV_SCLHVSP_FBMG_SET_CIIR_ON      = 0x4000,
    E_DRV_SCLHVSP_FBMG_SET_CIIR_OFF     = 0x8000,
} DrvSclHvspFbmgSetType_e;

/**
* Used to setup the error type of hvsp device
*/
typedef enum
{
    E_DRV_SCLHVSP_ERR_OK    =  0, ///< No Error
    E_DRV_SCLHVSP_ERR_FAULT = -1, ///< Fault
    E_DRV_SCLHVSP_ERR_INVAL = -2, ///< Invalid value
    E_DRV_SCLHVSP_ERR_MULTI = -3, ///< MultiInstance Fault
}DrvSclHvspErrType_e;
//=============================================================================
// struct
//=============================================================================
/**
* Used to get HVSP drvier version
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    u32   u32Version;      ///< version
    u32   VerChk_Size;     ///< VerChk Size
} __attribute__ ((__packed__))DrvSclHvspVersionConfig_t;

/**
* Used to setup the crop size of hvsp device
*/
typedef struct
{
    u16 u16X;        ///< crop frame start x point
    u16 u16Y;        ///< crop frame start y point
    u16 u16Width;    ///< crop width size
    u16 u16Height;   ///< crop height size
} __attribute__ ((__packed__))DrvSclHvspWindowConfig_t;

/**
* Used to setup the HVSP timing gen of hvsp device
*/
typedef struct
{
    bool  bInterlace;      ///< is interlace or progressive
    u16 u16Htotal;       ///< Htt
    u16 u16Vtotal;       ///< Vtt
    u16 u16Vfrequency;   ///< Vfreq
} DrvSclHvspTimingConfig_t;


//=============================================================================
// struct for DrvSclHvspInputConfig_t
/**
* Used to setup the input mux ,input capture window of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    DrvSclHvspSrcType_e        enSrcType;    ///< Input source type
    DrvSclHvspColorType_e      enColor;      ///< color type
    DrvSclHvspWindowConfig_t   stCaptureWin; ///< Input Source Size(input src is scl capture win
    DrvSclHvspTimingConfig_t    stTimingCfg;  ///< Input Timing
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__))DrvSclHvspInputConfig_t;


// struct for for DrvSclHvspOutputConfig_t
/**
* Used to setup the output config of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    DrvSclHvspColorType_e         enColor;      ///< color type
    DrvSclHvspWindowConfig_t      stDisplayWin; ///< display window size
    DrvSclHvspTimingConfig_t      stTimingCfg;  ///< output timing
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspOutputConfig_t;

/**
* Used to set CLK mux of hvsp device
*/
typedef struct
{
#if 0 //RTK_ToDo CLK
    struct clk* idclk;  ///< idclk
    struct clk* fclk1;  ///< fclk (SC1 SC2
    struct clk* fclk2;  ///< fclk (SC3
    struct clk* odclk;  ///< odclk (display Lpll
#endif
} DrvSclHvspClkConfig_t;

// sturct DrvSclHvspScalingConfig_t
/**
* Used to setup the crop and HVSP123 scaling configuration of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    u16              u16Src_Width;   ///< post crop IN width
    u16              u16Src_Height;  ///< post crop IN height
    u16              u16Dsp_Width;   ///< after HVSP width
    u16              u16Dsp_Height;  ///< after HVSP height
    bool               bCropEn;        ///< Is post crop En
    DrvSclHvspWindowConfig_t stCropWin;      ///< post crop size
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspScalingConfig_t;

//struct DrvSclHvspReqMemConfig_t
/**
* Used to allocate the buffer and setup framebuffer configuration of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    u16              u16Vsize;   ///< framebuffer height
    u16              u16Pitch;   ///< framebuffer width
    u32               u32MemSize; ///< height*width *2(YUV422) *2(2frame)
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspReqMemConfig_t;

//struct DrvSclHvspMiscConfig_t
/**
* Used to setup the register of hvsp device
*/
typedef struct
{
    u8   u8Cmd;      ///< register value
    u32   u32Size;    ///< number
    u32   u32Addr;    ///< bank&addr
} DrvSclHvspMiscConfig_t;

//struct DrvSclHvspPostCropConfig_t
/**
* Used to setup the post crop of hvsp device if need
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    bool  bCropEn;     ///< post crop En
    u16 u16X;        ///< crop frame start x point
    u16 u16Y;        ///< crop frame start y point
    u16 u16Width;    ///< crop frame width
    u16 u16Height;   ///< crop frame height
    bool  bFmCntEn;    ///< Is use CMDQ to set
    u8  u8FmCnt;     ///< when frame count
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspPostCropConfig_t;

//struct DrvSclHvspScInformConfig_t
/**
* Used to get resolution information of hvsp device
*/
typedef struct
{
    u16 u16X;            ///< x vs input src
    u16 u16Y;            ///< y vs input src
    u16 u16Width;        ///< display width
    u16 u16Height;       ///< display height
    u16 u16crop2inWidth; ///< framebuffer width
    u16 u16crop2inHeight;///< framebuffer height
    u16 u16crop2OutWidth; ///< after crop width
    u16 u16crop2OutHeight;///< after crop height
} DrvSclHvspScInformConfig_t;

//struct DrvSclHvspPrivateIdConfig_t
/**
* Used to get private ID of hvsp device
*/
typedef struct
{
    s32 s32Id;  ///< private ID
} DrvSclHvspPrivateIdConfig_t;

//struct DrvSclHvspPriMaskConfig_t
/**
* Used to set MASK of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    bool bMask; ///<Mask or not
    u8 u8idx; ///< mask id
    DrvSclHvspWindowConfig_t stMaskWin;      ///< Mask info
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspPriMaskConfig_t;
/**
* Used to set MASK trigger of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    bool bEn; ///<Mask enable
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspPriMaskTriggerConfig_t;

//struct DrvSclHvspOsdConfig_t
/**
* Used to set OSD of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    bool              bEn;          ///< OSD enable
    DrvSclHvspOsdLocType_e enOSD_loc;    ///< OSD locate
    bool              bOSDBypass;   ///< OSD bypass
    bool              bWTMBypass;   ///<WTM bypass
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspOsdConfig_t;

//struct DrvSclHvspSetFbManageConfig_t
/**
* Used to set OSD of hvsp device
*/
typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    DrvSclHvspFbmgSetType_e  enSet;
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< VerChk Size
} __attribute__ ((__packed__)) DrvSclHvspSetFbManageConfig_t;


/**
* Used to set CB function of Poll*/

typedef void (*PollCB) (void *);

typedef struct
{
    u32   VerChk_Version ; ///< VerChk version
    PollCB *pCBFunc;
    u32   VerChk_Size; ///< VerChk Size
}__attribute__ ((__packed__)) DrvSclHvspPollConfig_t;
//=============================================================================

//=============================================================================
#ifndef __DRV_SCL_HVSP_IO_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif
INTERFACE DrvSclHvspErrType_e DrvSclHvspInit(void);
INTERFACE DrvSclHvspErrType_e DrvSclHvspExit(void);
INTERFACE s32                 DrvSclHvspOpen(DrvSclHvspIdType_e enSclHvspId);
INTERFACE DrvSclHvspErrType_e DrvSclHvspRelease(s32 s32Handler);
INTERFACE DrvSclHvspErrType_e DrvSclHvspPoll(s32 s32Handler, DrvSclHvspPollConfig_t *pstIoPollCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSuspend(s32 s32Handler);
INTERFACE DrvSclHvspErrType_e DrvSclHvspResume(s32 s32Handler);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetInputConfig(s32 s32Handler, DrvSclHvspInputConfig_t *pstIoInCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetOutputConfig(s32 s32Handler, DrvSclHvspOutputConfig_t *pstIoOutCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetScalingConfig(s32 s32Handler, DrvSclHvspScalingConfig_t *pstIOSclCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspReqmemConfig(s32 s32Handler, DrvSclHvspReqMemConfig_t*pstReqMemCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetMiscConfig(s32 s32Handler, DrvSclHvspMiscConfig_t *pstIOMiscCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetPostCropConfig(s32 s32Handler, DrvSclHvspPostCropConfig_t *pstIOPostCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspGetPrivateIdConfig(s32 s32Handler, DrvSclHvspPrivateIdConfig_t *pstIOCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspGetInformConfig(s32 s32Handler, DrvSclHvspScInformConfig_t *pstIOInfoCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspReleaseMemConfig(s32 s32Handler);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetOsdConfig(s32 s32Handler, DrvSclHvspOsdConfig_t *pstIOOSDCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetPriMaskConfig(s32 s32Handler, DrvSclHvspPriMaskConfig_t *pstIOPriMaskCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspPirMaskTrigerConfig(s32 s32Handler, DrvSclHvspPriMaskTriggerConfig_t *pstIOPriMaskTrigCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspSetFbConfig(s32 s32Handler, DrvSclHvspSetFbManageConfig_t *pstIOFbMgCfg);
INTERFACE DrvSclHvspErrType_e DrvSclHvspGetVersion(s32 s32Hander, DrvSclHvspVersionConfig_t *pstIOVersionCfg);

#undef INTERFACE
#endif //
/** @} */ // end of hvsp_group
