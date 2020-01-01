///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//
// @file   drv_gop_io.h
// @brief  GOP Driver Interface
// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *  @file drv_gop_io.h
 *  @brief GOP Driver IOCTL parameter interface
 */

/**
* \ingroup gop_group
* @{
*/

#ifndef __DRV_GOP_IO_H__
#define __DRV_GOP_IO_H__

//=============================================================================
// Defines
//=============================================================================

#define DRV_GOP_IO_PALETTE_ENTRY_NUM 256

//=============================================================================
// enum
//=============================================================================
/**
* Used to setup the id type of gop device
*/
typedef enum
{
    E_DRV_GOP_IO_ID_0,
    E_DRV_GOP_IO_ID_1,
    E_DRV_GOP_IO_ID_2,
    E_DRV_GOP_IO_ID_3,
    E_DRV_GOP_IO_ID_4,
    E_DRV_GOP_IO_ID_NUM,
} DrvGopIoIdType_e;

/**
* Used to setup the erro type of gop device
*/
typedef enum
{
    E_DRV_GOP_IO_ERR_SUCCESS  =  0,     ///< No Error
    E_DRV_GOP_IO_ERR_FAULT = -1,     ///< Fault
    E_DRV_GOP_IO_ERR_INVAL = -2,     ///< Invalid Value
    E_DRV_GOP_IO_ERR_NOMEM = -3,     ///< No Assign Memory
} DrvGopIoErrType_e;

/**
* Used to setup output format of gop device
*/
typedef enum
{
    E_DRV_GOP_IO_OUT_FMT_RGB,
    E_DRV_GOP_IO_OUT_FMT_YUV,
    E_DRV_GOP_IO_OUT_FMT_NUM,
} DrvGopIoOutFmtType_e;

typedef enum
{
    E_DRV_GOP_IO_DISPLAY_MD_INTERLACE,
    E_DRV_GOP_IO_DISPLAY_MD_PROGRESS,
    E_DRV_GOP_IO_DISPLAY_MD_NUM,
} DrvGopIoDisplayModeType_e;

/**
* Used to setup the stretch H ratio for gop
*/
typedef enum
{
    E_DRV_GOP_IO_STRETCH_H_RATIO_1 = 1,
    E_DRV_GOP_IO_STRETCH_H_RATIO_2 = 2,
    E_DRV_GOP_IO_STRETCH_H_RATIO_4 = 4,
    E_DRV_GOP_IO_STRETCH_H_RATIO_8 = 8,
} DrvGopIoStretchHorizonRatio_e;

/**
* Used to set gwin color format of gop
*/
typedef enum
{
    E_DRV_GOP_IO_GWIN_SRC_FMT_RGB1555    = 0x00,
    E_DRV_GOP_IO_GWIN_SRC_FMT_RGB565     = 0x01,
    E_DRV_GOP_IO_GWIN_SRC_FMT_ARGB4444   = 0x02,
    E_DRV_GOP_IO_GWIN_SRC_FMT_2266       = 0x03,
    E_DRV_GOP_IO_GWIN_SRC_FMT_I8_PALETTE = 0x04,
    E_DRV_GOP_IO_GWIN_SRC_FMT_ARGB8888   = 0x05,
    E_DRV_GOP_IO_GWIN_SRC_FMT_ARGB1555   = 0x06,
    E_DRV_GOP_IO_GWIN_SRC_FMT_ABGR8888   = 0x07,
    E_DRV_GOP_IO_GWIN_SRC_FMT_UV7Y8      = 0x08,
    E_DRV_GOP_IO_GWIN_SRC_FMT_UV8Y8      = 0x09,
    E_DRV_GOP_IO_GWIN_SRC_FMT_RGBA5551   = 0x0A,
    E_DRV_GOP_IO_GWIN_SRC_FMT_RGBA4444   = 0x0B,
    E_DRV_GOP_IO_GWIN_SRC_FMT_NUM        = 0x0C,
} DrvGopIoGwinSrcFmtType_e;

/**
* Used to setup the mode of alpha blending for gop
*/
typedef enum
{
    E_DRV_GOP_IO_GWIN_ALPHA_CONSTANT,
    E_DRV_GOP_IO_GWIN_ALPHA_PIXEL,
    E_DRV_GOP_IO_GWIN_ALPHA_NUM,
} DrvGopIoGwinAlphaType_e;

/**
* Used to setup the buffer number for gop
*/
typedef enum
{
    E_DRV_GOP_IO_FB_SINGLE_BUFFER = 1,
    E_DRV_GOP_IO_FB_DOUBLE_BUFFER = 2,
    E_DRV_GOP_IO_FB_TRIPLE_BUFFER = 3,
    E_DRV_GOP_IO_FB_FOURTH_BUFFER = 4,
    E_DRV_GOP_IO_FB_FIFTH_BUFFER = 5,
} DrvGopIoBufferNum_e;

/**
* Used to setup the gwin number for gop
*/
typedef enum
{
    E_DRV_GOP_IO_GWIN_ID_1,
    E_DRV_GOP_IO_GWIN_ID_2,    
    E_DRV_GOP_IO_GWIN_ID_3,  
    E_DRV_GOP_IO_GWIN_ID_4,  
    E_DRV_GOP_IO_GWIN_ID_NUM,
} DrvGopIoGwinIdType_e;


//=============================================================================
// struct
//=============================================================================


/**
* Used to set or get gwin parameters
*/
typedef struct
{
    u16 u16XStart; ///< window coordinate, x offset
    u16 u16YStart; ///< window coordinate, y offset
    u16 u16Width;  ///< window width
    u16 u16Height; ///< window height
} DrvGopIoWindowConfig_t;

/**
* Used to set or get gop alpha blending settings
*/
typedef struct
{
    DrvGopIoGwinAlphaType_e eAlphaType; ///< set alpha type: pixel alpha or constant alpha
    u8 u8Alpha;         ///< constant alpha value, availble for setting constant alpha
} DrvGopIoAlphaConfig_t;

typedef struct
{
    u16 u16DisplayWidth;  ///< window display width
    u16 u16DisplayHeight; ///< window display height
    DrvGopIoStretchHorizonRatio_e eStretchHRatio; //stretch H ratio
} DrvGopIoSetModeConfig_t;



/**
* Used to set or get gop colorkey settings
*/
typedef struct
{
    bool bEn; ///< colorkey enable or disable
    u8 u8R; ///< parameter for red color in colorkey
    u8 u8G; ///< parameter for green color in colorkey
    u8 u8B; ///< parameter for blue color in colorkey
} DrvGopIoColorKeyConfig_t;


/**
* Used to set palette parameters
*/
typedef union
{
    /// RGBA8888
    struct
    {
        u8 u8B; ///< parameter for blue color in palette
        u8 u8G; ///< parameter for green color in palette
        u8 u8R; ///< parameter for red color in palette
        u8 u8A; ///< parameter for alpha in palette
    } BGRA;
} DrvGopIoPaletteEntry_t;

//=============================================================================

//=============================================================================
#ifndef __DRV_GOP_IO_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE DrvGopIoErrType_e DrvGopIoInit(void);
INTERFACE DrvGopIoErrType_e DrvGopIoSetGopParam(DrvGopIoIdType_e eGopId, DrvGopIoSetModeConfig_t tParCfg);
INTERFACE DrvGopIoErrType_e DrvGopIoSetEnGop(DrvGopIoIdType_e eGopId, bool bEn);
INTERFACE DrvGopIoErrType_e DrvGopIoSetAlphaBld(DrvGopIoIdType_e eGopId, DrvGopIoGwinIdType_e eGwinId, DrvGopIoAlphaConfig_t tAlphaCfg);
INTERFACE DrvGopIoErrType_e DrvGopIoSetColorKey(DrvGopIoIdType_e eGopId, DrvGopIoColorKeyConfig_t tColorKeyCfg);
INTERFACE DrvGopIoErrType_e DrvGopIoSetPanDisplay(DrvGopIoIdType_e eGopId, u16 u16Yoffset);
INTERFACE DrvGopIoErrType_e DrvGopIoSetPalette(DrvGopIoIdType_e eGopId, u16 u16Size, DrvGopIoPaletteEntry_t *tPal);
INTERFACE DrvGopIoErrType_e DrvGopIoSetGwinSize(DrvGopIoIdType_e eGopId, DrvGopIoGwinIdType_e eGwinId, DrvGopIoWindowConfig_t tWinCfg);
INTERFACE DrvGopIoErrType_e DrvGopIoGetMemMap(DrvGopIoIdType_e eGopId, u32 *u32pVirAddr);
INTERFACE DrvGopIoErrType_e DrvGopIoGetEnGop(DrvGopIoIdType_e eGopId, bool *bEn);
INTERFACE DrvGopIoErrType_e DrvGopIoGetAlphaBld(DrvGopIoIdType_e eGopId, DrvGopIoGwinIdType_e enGwinId, DrvGopIoAlphaConfig_t *tAlphaCfg);
INTERFACE DrvGopIoErrType_e DrvGopIoGetColorKey(DrvGopIoIdType_e eGopId, DrvGopIoColorKeyConfig_t *tColorKeyCfg);

#undef INTERFACE

#endif //

/** @} */ // end of gop_group
