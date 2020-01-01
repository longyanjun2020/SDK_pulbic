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

#ifndef __DRV_GOP_H__
#define __DRV_GOP_H__

#if defined(__GNUC__)
#include "vm_types.ht"
#endif

//=============================================================================
// Defines
//=============================================================================
#define DRV_GOP_VERSION                        0x0100


//=============================================================================
// enum
//=============================================================================

typedef enum
{
    E_DRV_GOP_ID_0,
    E_DRV_GOP_ID_1,
    E_DRV_GOP_ID_2,
    E_DRV_GOP_ID_3,
    E_DRV_GOP_ID_4,
    E_DRV_GOP_ID_NUM,
} DrvGopIdNum_e;

typedef enum
{
    E_DRV_GOP_ID_00     = 0x00,
    E_DRV_GOP_ID_01     = 0x01,
    E_DRV_GOP_ID_0_ST   = 0x02,
    E_DRV_GOP_ID_10     = 0x10,
    E_DRV_GOP_ID_11     = 0x11,
    E_DRV_GOP_ID_1_ST   = 0x12,
    E_DRV_GOP_ID_20     = 0x20,
    E_DRV_GOP_ID_21     = 0x21,
    E_DRV_GOP_ID_2_ST   = 0x22,
    E_DRV_GOP_ID_30     = 0x30,
    E_DRV_GOP_ID_31     = 0x31,
    E_DRV_GOP_ID_3_ST   = 0x32,
    E_DRV_GOP_ID_40     = 0x40,
    E_DRV_GOP_ID_41     = 0x41,
    E_DRV_GOP_ID_4_ST   = 0x42,
} DrvGopIdType_e;

typedef enum
{
    E_DRV_GOP_OUT_FMT_RGB,
    E_DRV_GOP_OUT_FMT_YUV,
    E_DRV_GOP_OUT_FMT_NUM,
} DrvGopOutFmtType_e;

typedef enum
{
    E_DRV_GOP_DISPLAY_MD_INTERLACE,
    E_DRV_GOP_DISPLAY_MD_PROGRESS,
    E_DRV_GOP_DISPLAY_MD_NUM,
} DrvGopDisplayModeType_e;


typedef enum
{
    E_DRV_GOP_DEST_OP,
    E_DRV_GOP_DEST_NUM,
} DrvGopDestType_e;

typedef enum
{
    E_DRV_GOP_STRETCH_RATIO_1 = 1,
    E_DRV_GOP_STRETCH_RATIO_2 = 2,
    E_DRV_GOP_STRETCH_RATIO_4 = 4,
    E_DRV_GOP_STRETCH_RATIO_8 = 8,
} DrvGopStretchRatioType_e;

//------------------------------------------------------------------------------
// GWin
//------------------------------------------------------------------------------
typedef enum
{
    E_DRV_GOP_GWIN_ID_1,
    E_DRV_GOP_GWIN_ID_2,
    E_DRV_GOP_GWIN_ID_3,
    E_DRV_GOP_GWIN_ID_4,
    E_DRV_GOP_GWIN_ID_NUM,
} DrvGopGwinIdType_e;

typedef enum
{
    E_DRV_GOP_GWIN_SRC_FMT_RGB1555    = 0x00,
    E_DRV_GOP_GWIN_SRC_FMT_RGB565     = 0x01,
    E_DRV_GOP_GWIN_SRC_FMT_ARGB4444   = 0x02,
    E_DRV_GOP_GWIN_SRC_FMT_2266       = 0x03,
    E_DRV_GOP_GWIN_SRC_FMT_I8_PALETTE = 0x04,
    E_DRV_GOP_GWIN_SRC_FMT_ARGB8888   = 0x05,
    E_DRV_GOP_GWIN_SRC_FMT_ARGB1555   = 0x06,
    E_DRV_GOP_GWIN_SRC_FMT_ABGR8888   = 0x07,
    E_DRV_GOP_GWIN_SRC_FMT_UV7Y8      = 0x08,
    E_DRV_GOP_GWIN_SRC_FMT_UV8Y8      = 0x09,
    E_DRV_GOP_GWIN_SRC_FMT_RGBA5551   = 0x0A,
    E_DRV_GOP_GWIN_SRC_FMT_RGBA4444   = 0x0B,
    E_DRV_GOP_GWIN_SRC_FMT_NUM        = 0x0C,
} DrvGopGwinSrcFmtType_e;

typedef enum
{
    E_DRV_GOP_GWIN_ALPHA_CONSTANT,
    E_DRV_GOP_GWIN_ALPHA_PIXEL,
    E_DRV_GOP_GWIN_ALPHA_NUM,
} DrvGopGwinAlphaType_e;

typedef enum
{
    E_DRV_GOP_NONE = 0x0000,
    E_DRV_GOP_H_MIRROR = 0x0001,
    E_DRV_GOP_V_MIRROR = 0x0002,
    E_DRV_GOP_BOTH = E_DRV_GOP_H_MIRROR | E_DRV_GOP_V_MIRROR,
} DrvGopMirrorType_e;
/**
* Used to setup the error type of hvsp device
*/
typedef enum
{
    E_DRV_GOP_ERR_OK    =  0, ///< No Error
    E_DRV_GOP_ERR_FAULT = -1, ///< Fault
    E_DRV_GOP_ERR_INVAL = -2, ///< Invalid value
} DrvGopErrType_e;

//=============================================================================
// struct
//=============================================================================

typedef struct
{
    u16 u16X;
    u16 u16Y;
    u16 u16Width;
    u16 u16Height;
} DrvGopWindowConfig_t;

typedef struct
{
    DrvGopGwinIdType_e     eGwinId;
    DrvGopGwinSrcFmtType_e eSrcFmt;
    DrvGopWindowConfig_t   tDisplayWin;
    u32 u32BaseAddr;
    u16 u16Base_XOffset;
    u32 u32Base_YOffset;
} DrvGopGwinConfig_t;

typedef struct
{
    DrvGopOutFmtType_e      eOutFmt;
    DrvGopDisplayModeType_e eDisplyMode;
    DrvGopWindowConfig_t    tOsdDisplayWindow;
    u8  u8GWinNum;
    DrvGopGwinConfig_t *pstGwinCfg;
    DrvGopStretchRatioType_e eStretchHRatio;
} DrvGopModeConfig_t;

typedef struct
{
    DrvGopGwinAlphaType_e eAlphaType;
    u8 u8ConstantAlpahValue;
} DrvGopGwinAlphaConfig_t;

typedef struct
{
    bool bEn;
    u8 u8R;
    u8 u8G;
    u8 u8B;
} DrvGopColorKeyConfig_t;

typedef struct
{
    u16 u16Size;
    u8 *pu8Palette_A;
    u8 *pu8Palette_R;
    u8 *pu8Palette_G;
    u8 *pu8Palette_B;
} DrvGopGwinPaletteConfig_t;
//=============================================================================

//=============================================================================
#ifndef __DRV_GOP_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif

INTERFACE bool DrvGopSetModeConfig(DrvGopIdNum_e eGopId, DrvGopModeConfig_t *pGopParamCfg);
INTERFACE bool DrvGopUpdateBase(DrvGopIdNum_e eGopId, DrvGopGwinIdType_e eGwinId, u32 u32BaseAddr);
INTERFACE bool DrvGopSetOutFormat(DrvGopIdNum_e eGopId, DrvGopOutFmtType_e eFmt);
INTERFACE bool DrvGopSetAlphaBlending(DrvGopIdNum_e eGopId, DrvGopGwinIdType_e eGwinId, DrvGopGwinAlphaConfig_t tAlphaCfg);
INTERFACE bool DrvGopSetColorKey(DrvGopIdNum_e eGopId, DrvGopColorKeyConfig_t tColorKeyCfg);
INTERFACE bool DrvGopSetPipeDelay(DrvGopIdNum_e eGopId, u8 u8Delay);
INTERFACE bool DrvGopSetPaletteRiu(DrvGopIdNum_e eGopId, DrvGopGwinPaletteConfig_t tPaletteCfg);
INTERFACE bool DrvGopSetPaletteRiuOneMem(DrvGopIdNum_e eGopId, u8 u8Idx, u8 u8A, u8 u8R, u8 u8G, u8 u8B);
INTERFACE bool DrvGopSetEnableGwin(DrvGopIdNum_e eGopId,  DrvGopGwinIdType_e eGwinId, bool bEn);
INTERFACE bool DrvGopSetScalerEnableGop(DrvGopIdNum_e eGopId,  DrvGopGwinIdType_e eGwinId, bool bEn);
INTERFACE bool DrvGopSetGwinSize(DrvGopIdNum_e eGopId, DrvGopGwinIdType_e eGwinId, DrvGopWindowConfig_t tWinCfg, DrvGopGwinSrcFmtType_e eSrcFmt);
INTERFACE bool DrvGopSetStretchWindowSize(DrvGopIdNum_e eGopId, DrvGopWindowConfig_t tWinCfg);
INTERFACE bool DrvGopSetStretchWindowRatio(DrvGopIdNum_e eGopId, u32 u32HRatio, u32 u32VRatio);
INTERFACE bool DrvGopSetSwapUV(DrvGopIdNum_e eGopId, bool bSwap);
INTERFACE bool DrvGopSetSwapYC(DrvGopIdNum_e eGopId, bool bSwap);
INTERFACE bool DrvGopSetSwapRB(DrvGopIdNum_e eGopId, bool bSwap);
INTERFACE bool DrvGopGetEnableGwin(DrvGopIdNum_e eGopId,  DrvGopGwinIdType_e eGwinId, bool *bEn);
INTERFACE bool DrvGopGetScalerEnableGop(DrvGopIdNum_e eGopId,  DrvGopGwinIdType_e eGwinId, bool *bEn);
INTERFACE bool DrvGopGetAlpha(DrvGopIdNum_e eGopId, DrvGopGwinIdType_e eGwinId, DrvGopGwinAlphaConfig_t *pstAlphaCfg);
INTERFACE bool DrvGopGetColorKey(DrvGopIdNum_e eGopId, DrvGopColorKeyConfig_t *pstColorKeyCfg);
INTERFACE void DrvGopSetMirrorMode(DrvGopIdNum_e eGopNum, DrvGopMirrorType_e eMirrorType, DrvGopWindowConfig_t tGwincfg);
INTERFACE bool DrvGopGetSrcFmt(DrvGopIdNum_e eGopNum, DrvGopGwinSrcFmtType_e *eGwinSrcFmt ,  DrvGopGwinIdType_e eGwinId);
INTERFACE bool DrvGopGetMutiWinSize(DrvGopIdNum_e eGopNum, DrvGopWindowConfig_t *tGwinCfg , DrvGopGwinIdType_e eGwinId );
INTERFACE bool DrvGopGetBackgroundWinSize(DrvGopIdNum_e eGopNum, DrvGopWindowConfig_t *tDraWinCfg);
INTERFACE u8 DrvGopGetGwinNum(DrvGopIdNum_e eGopId);
INTERFACE u32 DrvGOPRegisterRead(u32 u32Addr);
INTERFACE u32 DrvGopFindNewBaseAddr(u32 u32OldBaseAddr, DrvGopMirrorType_e eMirrorType, DrvGopGwinConfig_t tGwincfg);
#undef INTERFACE
#endif //
/** @} */ // end of hvsp_group
