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
 *  @file drv_scl_hvsp_io_st.h
 *  @brief SclHvsp Driver struct parameter interface
 */

/**
* \ingroup sclhvsp_group
* @{
*/

#ifndef __DRV_SCL_HVSP_IO_ST_H__
#define __DRV_SCL_HVSP_IO_ST_H__

#include "cam_os_wrapper.h"

//=============================================================================
// Defines
//=============================================================================
#define DRV_SCLHVSP_VERSION                        0x0100


//=============================================================================
// enum
//=============================================================================

/// @cond
/**
* The ID type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_ID_1,      ///< ID_1
    E_DRV_SCLHVSP_IO_ID_2,      ///< ID_2
    E_DRV_SCLHVSP_IO_ID_3,      ///< ID_3
    E_DRV_SCLHVSP_IO_ID_NUM,    ///< The max number of ID
} DrvSclHvspIoIdType_e;
/// @endcond

/**
* The input source type of SlcHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_SRC_ISP,       ///< input source: ISP
    E_DRV_SCLHVSP_IO_SRC_BT656,     ///< input source: BT656
    E_DRV_SCLHVSP_IO_SRC_DRAM,      ///< input source: DRAM
    E_DRV_SCLHVSP_IO_SRC_HVSP,      ///< input source: HVSP1
    E_DRV_SCLHVSP_IO_SRC_PAT_TGEN,  ///< input source: PATGEN
    E_DRV_SCLHVSP_IO_SRC_NUM,       ///< The max number of input source
} DrvSclHvspIoSrcType_e;

/**
* Thecolor format type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_COLOR_RGB,     ///< color format:RGB
    E_DRV_SCLHVSP_IO_COLOR_YUV444,  ///< color format:YUV444
    E_DRV_SCLHVSP_IO_COLOR_YUV422,  ///< color format:YUV422
    E_DRV_SCLHVSP_IO_COLOR_YUV420,  ///< color format:YUV420
    E_DRV_SCLHVSP_IO_COLOR_NUM,     ///< The max number of color format
} DrvSclHvspIoColorType_e;

/**
* The R/W status of MCNR for SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_MCNR_YCM_R   = 0x01,    ///< IP only read
    E_DRV_SCLHVSP_IO_MCNR_YCM_W   = 0x02,    ///< IP only write
    E_DRV_SCLHVSP_IO_MCNR_YCM_RW  = 0x03,    ///< IP R/W
    E_DRV_SCLHVSP_IO_MCNR_CIIR_R  = 0x04,    ///< IP only read
    E_DRV_SCLHVSP_IO_MCNR_CIIR_W  = 0x08,    ///< IP only write
    E_DRV_SCLHVSP_IO_MCNR_CIIR_RW = 0x0C,    ///< IP R/W
    E_DRV_SCLHVSP_IO_MCNR_NON     = 0x10,   ///< IP none open
} DrvSclHvspIoMcnrType_e;

/**
* The OSD location type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_OSD_LOC_AFTER  = 0,    ///< after hvsp
    E_DRV_SCLHVSP_IO_OSD_LOC_BEFORE = 1,    ///< before hvsp
} DrvSclHvspIoOsdLocType_e;

/**
*  The FB control option of SclHvsp in debug mode
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_FBMG_SET_LDCPATH_ON        = 0x0001,   ///< LDC On
    E_DRV_SCLHVSP_IO_FBMG_SET_LDCPATH_OFF       = 0x0002,   ///< LDC off
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_Read_ON       = 0x0004,   ///< DNR Read On
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_Read_OFF      = 0x0008,   ///< DNR Read Off
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_Write_ON      = 0x0010,   ///< DNR Write On
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_Write_OFF     = 0x0020,   ///< DNR Write Off
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_BUFFER_1      = 0x0040,   ///< DNR allocated 1 buffer
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_BUFFER_2      = 0x0080,   ///< DNR allocated 2 buffers
    E_DRV_SCLHVSP_IO_FBMG_SET_UNLOCK            = 0x0100,   ///< Disable Debug mode to
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_COMDE_ON      = 0x0200,   ///< DNR compress on
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_COMDE_OFF     = 0x0400,   ///< DNR compress off
    E_DRV_SCLHVSP_IO_FBMG_SET_DNR_COMDE_265OFF  = 0x0800,   ///< DNR compress off for H265
    E_DRV_SCLHVSP_IO_FBMG_SET_PRVCROP_ON        = 0x1000,   ///< Delay frame On for crop
    E_DRV_SCLHVSP_IO_FBMG_SET_PRVCROP_OFF       = 0x2000,   ///< Delay frame off for crop
    E_DRV_SCLHVSP_IO_FBMG_SET_CIIR_ON           = 0x4000,   ///< CIIR On
    E_DRV_SCLHVSP_IO_FBMG_SET_CIIR_OFF          = 0x8000,   ///< CIIR Off
	E_DRV_SCLHVSP_IO_FBMG_SET_LOCK              = 0x10000,  ///< Enable Debug mode to
} DrvSclHvspIoFbmgSetType_e;

/// @cond
/**
* The error type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_ERR_OK    =  0, ///< No Error
    E_DRV_SCLHVSP_IO_ERR_FAULT = -1, ///< Fault
    E_DRV_SCLHVSP_IO_ERR_INVAL = -2, ///< Invalid value
    E_DRV_SCLHVSP_IO_ERR_MULTI = -3, ///< MultiInstance Fault
}DrvSclHvspIoErrType_e;
/// @endcond

/**
* The Rotate type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_ROTATE_0,      ///< Rotate degree 0
    E_DRV_SCLHVSP_IO_ROTATE_90,     ///< Rotate degree 90
    E_DRV_SCLHVSP_IO_ROTATE_180,    ///< Rotate degree 180
    E_DRV_SCLHVSP_IO_ROTATE_270,    ///< Rotate degree 270
    E_DRV_SCLHVSP_IO_ROTATE_NUM,    ///< The max number of rotate type
}DrvSclHvspIoRotateType_e;

/**
* The output type of SclHvsp
*/
typedef enum
{
    E_DRV_SCLHVSP_IO_OUT_HVSP,      ///< output type: HVSP
    E_DRV_SCLHVSP_IO_OUT_EXTERNAL,  ///< output type: external
    E_DRV_SCLHVSP_IO_OUT_NUM,       ///< The max number of output type.
}DrvSclHvspIoOutputType_e;
//=============================================================================
// struct
//=============================================================================
/**
*  The Version of SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    u32   u32Version;      ///< version
    u32   VerChk_Size;     ///< structure size for version checking
} __attribute__ ((__packed__))DrvSclHvspIoVersionConfig_t;

/**
* The rectangle configuration for Crop Window, Capture Window, Display Window of SclHvsp
*/
typedef struct
{
    u16 u16X;        ///< horizontal starting position
    u16 u16Y;        ///< vertical starting position
    u16 u16Width;    ///< horizontal size
    u16 u16Height;   ///< vertical size
} __attribute__ ((__packed__))DrvSclHvspIoWindowConfig_t;

/**
* The timing configuration of SclHvsp
*/
typedef struct
{
    bool  bInterlace;   ///< be interlace or progressive
    u16 u16Htotal;      ///< horizontal total
    u16 u16Vtotal;      ///< vertical total
    u16 u16Vfrequency;  ///< vertical frequency
} DrvSclHvspIoTimingConfig_t;


/**
*  The input source configuration of SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclHvspIoSrcType_e        enSrcType;     ///< Input source type
    DrvSclHvspIoColorType_e      enColor;       ///< Input color type
    DrvSclHvspIoWindowConfig_t   stCaptureWin;  ///< Input Source Size(input src is scl capture win
    DrvSclHvspIoTimingConfig_t    stTimingCfg;  ///< Input Timing configuration
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__))DrvSclHvspIoInputConfig_t;


// struct for for DrvSclHvspIoOutputConfig_t
/**
* The output configuration of SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ;                    ///< structure version
    DrvSclHvspIoColorType_e     enColor;      ///< Output color type
    DrvSclHvspIoWindowConfig_t  stDisplayWin; ///< Output display size
    DrvSclHvspIoTimingConfig_t  stTimingCfg;  ///< Output timing
    DrvSclHvspIoOutputType_e    enOutput;     ///< Output type
    u32   VerChk_Size;                        ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoOutputConfig_t;

/// @cond
/*
* Used to set CLK mux of SclHvsp
*/
typedef struct
{
    void* idclk;  ///< idclk
    void* fclk1;  ///< fclk (SC1 SC2
    void* fclk2;  ///< fclk (SC3
    void* odclk;  ///< odclk (display Lpll
} DrvSclHvspIoClkConfig_t;
/// @endcond

/**
*  The scaling configuration of SclHvsp
*/
typedef struct
{
    u32  VerChk_Version ;   ///< structure version
    u16  u16Src_Width;      ///< horizontal size of input source
    u16  u16Src_Height;     ///< vertical size of input source
    u16  u16Dsp_Width;      ///< horizontal size of output display
    u16  u16Dsp_Height;     ///< vertifcal size of output display
    bool bCropEn;           ///< the control flag of Crop on/off
    DrvSclHvspIoWindowConfig_t stCropWin;   ///< crop configuration
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoScalingConfig_t;

/**
* The configuration of memory allocated for SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ;  ///< structure version
    u16   u16Vsize;         ///< vertical size of framebuffer
    u16   u16Pitch;         ///< horizontal size of framebuffer
    u32   u32MemSize;       ///< total size of allocated memory, height*width *2(YUV422) *2(2frame)
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;      ///< structure size for version checking
    u32   u32Channel;
} __attribute__ ((__packed__)) DrvSclHvspIoReqMemConfig_t;

/**
* The configuration of R/W registers for SclHvsp
*/
typedef struct
{
    u8    u8Cmd;      ///< register value
    u32   u32Size;    ///< number
    u32   u32Addr;    ///< bank&addr
} DrvSclHvspIoMiscConfig_t;

/**
* Used to setup the post crop of SclHvsp  if need
*/
typedef struct
{
    u32  VerChk_Version ;   ///< structure version
    bool bCropEn;           ///< post crop En
    u16  u16X;              ///< crop frame start x point
    u16  u16Y;              ///< crop frame start y point
    u16  u16Width;          ///< crop frame width
    u16  u16Height;         ///< crop frame height
    bool bFmCntEn;          ///< Is use CMDQ to set
    u8   u8FmCnt;           ///< when frame count
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoPostCropConfig_t;

/**
*  The setting information of SclHvsp
*/
typedef struct
{
    u16 u16X;               ///< horizotnal starting position of input source
    u16 u16Y;               ///< vertical starting position of input source
    u16 u16Width;           ///< horizontal size of output display
    u16 u16Height;          ///< vertical size of oputput display
    u16 u16crop2inWidth;    ///< framebuffer width
    u16 u16crop2inHeight;   ///< framebuffer height
    u16 u16crop2OutWidth;   ///< horizotnal size of after crop
    u16 u16crop2OutHeight;  ///< vertical size after crop
} DrvSclHvspIoScInformConfig_t;


/**
* The private id of multi-instance for SclHvsp
*/
typedef struct
{
    s32 s32Id;  ///< private ID
} DrvSclHvspIoPrivateIdConfig_t;

/**
* The configuration of PrivateMask for SclHvsp
*/
typedef struct
{
    u32  VerChk_Version ;                   ///< structure version
    bool bMask;                             ///< PrivateMask On/Off
    u8   u8idx;                             ///< PrivateMask id
    DrvSclHvspIoWindowConfig_t stMaskWin;   ///< the rectangel of PrivateMask
    u32   VerChk_Size;                      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoPriMaskConfig_t;

/**
* The configuration of PrivateMask Trigger for SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ;   ///< structure version
    bool  bEn;               ///< PrivateMask enable/disable
    u32   VerChk_Size;      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoPriMaskTriggerConfig_t;

/**
* The configuration of OSD for SclHvsp
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    bool              bEn;              ///< OSD enable/disable
    DrvSclHvspIoOsdLocType_e enOSD_loc; ///< OSD location
    bool              bOSDBypass;       ///< OSD bypass
    bool              bWTMBypass;       ///< WTM bypass
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoOsdConfig_t;


/**
* The configuration of fb management controller for SclHvsp in debug mode
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    DrvSclHvspIoFbmgSetType_e  enSet; ///< FB control option
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclHvspIoSetFbManageConfig_t;


/// @cond
/**
* Used to set CB function of Poll
*/

typedef void (*PollCB) (void *);

typedef struct
{
    u8   u8retval;           ///< return
    u8   u8pollval;          ///< get
    u32  u32Timeout;         ///< u32Timeout
    PollCB *pCBFunc;
}__attribute__ ((__packed__)) DrvSclHvspIoPollConfig_t;
///@endcond

/**
* The configuration of rotate for SCLHVSP
*/
typedef struct
{
    u32   VerChk_Version ;                  ///< structure version
    DrvSclHvspIoRotateType_e enRotateType;  ///< rotate type
    bool  bEn;                              ///< enable/disable
    u32   VerChk_Size;                      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclHvspIoRotateConfig_t;

/**
*  The lock configuration of multi-instance for SCLHVSP
*/
typedef struct
{
    u32   VerChk_Version ;  ///< structure version
    s32 *ps32IdBuf;         ///< buffer ID
    u8 u8BufSize;           ///< buffer size
    u32   VerChk_Size;      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclHvspIoLockConfig_t;

///@cond
/**
* The configuration of rotate for SCLHVSP
*/
typedef struct
{
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetInputConfig)(s32 s32Handler, DrvSclHvspIoInputConfig_t *pstIoInCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetOutputConfig)(s32 s32Handler, DrvSclHvspIoOutputConfig_t *pstIoOutCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetScalingConfig)(s32 s32Handler, DrvSclHvspIoScalingConfig_t *pstIOSclCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoReqmemConfig)(s32 s32Handler, DrvSclHvspIoReqMemConfig_t*pstReqMemCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetMiscConfig)(s32 s32Handler, DrvSclHvspIoMiscConfig_t *pstIOMiscCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetPostCropConfig)(s32 s32Handler, DrvSclHvspIoPostCropConfig_t *pstIOPostCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoGetPrivateIdConfig)(s32 s32Handler, DrvSclHvspIoPrivateIdConfig_t *pstIOCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoGetInformConfig)(s32 s32Handler, DrvSclHvspIoScInformConfig_t *pstIOInfoCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoReleaseMemConfig)(s32 s32Handler, u32 ulchannel);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetOsdConfig)(s32 s32Handler, DrvSclHvspIoOsdConfig_t *pstIOOSDCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetPriMaskConfig)(s32 s32Handler, DrvSclHvspIoPriMaskConfig_t *pstIOPriMaskCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoPirMaskTrigerConfig)(s32 s32Handler, DrvSclHvspIoPriMaskTriggerConfig_t *pstIOPriMaskTrigCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetFbConfig)(s32 s32Handler, DrvSclHvspIoSetFbManageConfig_t *pstIOFbMgCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoGetVersion)(s32 s32Hander, DrvSclHvspIoVersionConfig_t *pstIOVersionCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetRotateConfig)(s32 s32Handler, DrvSclHvspIoRotateConfig_t *pstIoRotateCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetLockConfig)(s32 s32Handler, DrvSclHvspIoLockConfig_t *pstIoLockCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetUnlockConfig)(s32 s32Handler, DrvSclHvspIoLockConfig_t *pstIoLockCfg);
    DrvSclHvspIoErrType_e (*DrvSclHvspIoSetCiirConfig)(s32 s32Handler, bool en);
}DrvSclHvspIoFunctionConfig_t;
///@endcond

//=============================================================================

#endif //
/** @} */ // end of sclhvsp_group
