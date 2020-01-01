////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file     hal_scl_util.h
* @version
* @Platform I3
* @brief    This file defines the HAL SCL utility interface
*
*/

#ifndef __HAL_GOP_H__
#define __HAL_GOP_H__

//=============================================================================
// Defines
//=============================================================================


//=============================================================================
// enum
//=============================================================================
typedef enum
{
    E_HAL_GOP_ID_0,
    E_HAL_GOP_ID_1,
    E_HAL_GOP_ID_2,
    E_HAL_GOP_ID_3,
    E_HAL_GOP_ID_4,
    E_HAL_GOP_ID_NUM,
} HalGopIdNum_e;

typedef enum
{
    E_HAL_GOP_GWIN_ID_1,
    E_HAL_GOP_GWIN_ID_2,
    E_HAL_GOP_GWIN_ID_3,
    E_HAL_GOP_GWIN_ID_4,
    E_HAL_GOP_GWIN_ID_NUM,
} HalGopGwinIdType_e;

typedef enum
{
    E_HAL_GOP_ID_00     = 0x00,
    E_HAL_GOP_ID_01     = 0x01,
    E_HAL_GOP_ID_0_ST   = 0x02,
    E_HAL_GOP_ID_10     = 0x10,
    E_HAL_GOP_ID_11     = 0x11,
    E_HAL_GOP_ID_1_ST   = 0x12,
    E_HAL_GOP_ID_20     = 0x20,
    E_HAL_GOP_ID_21     = 0x21,
    E_HAL_GOP_ID_2_ST   = 0x22,
    E_HAL_GOP_ID_30     = 0x30,
    E_HAL_GOP_ID_31     = 0x31,
    E_HAL_GOP_ID_3_ST   = 0x32,
    E_HAL_GOP_ID_40     = 0x40,
    E_HAL_GOP_ID_41     = 0x41,
    E_HAL_GOP_ID_4_ST   = 0x42,
} HalGopIdType_e;

typedef enum
{
    E_HAL_GOP_DISPLAY_MODE_INTERLACE = 0x00,
    E_HAL_GOP_DISPLAY_MODE_PROGRESS  = 0x01,
} HalGopDisplayModeType_t;

typedef enum
{
    E_HAL_GOP_OUT_FMT_RGB = 0x00,
    E_HAL_GOP_OUT_FMT_YUV = 0x01,
} HalGopOutFormatType_e;

typedef enum
{
    E_HAL_GOP_GWIN_SRC_RGB1555    = 0x00,
    E_HAL_GOP_GWIN_SRC_RGB565     = 0x01,
    E_HAL_GOP_GWIN_SRC_ARGB4444   = 0x02,
    E_HAL_GOP_GWIN_SRC_2266       = 0x03,
    E_HAL_GOP_GWIN_SRC_I8_PALETTE = 0x04,
    E_HAL_GOP_GWIN_SRC_ARGB8888   = 0x05,
    E_HAL_GOP_GWIN_SRC_ARGB1555   = 0x06,
    E_HAL_GOP_GWIN_SRC_ABGR8888   = 0x07,
    E_HAL_GOP_GWIN_SRC_UV7Y8      = 0x08,
    E_HAL_GOP_GWIN_SRC_UV8Y8      = 0x09,
    E_HAL_GOP_GWIN_SRC_RGBA5551   = 0x0A,
    E_HAL_GOP_GWIN_SRC_RGBA4444   = 0x0B,
    E_HAL_GOP_GWIN_SRC_NUM
} HalGopGwinSrcFormat_e;

typedef enum
{
	E_HAL_GOP_NONE = 0x00,
    E_HAL_GOP_H_MIRROR = 0x01,
    E_HAL_GOP_V_MIRROR = 0x02,
    E_HAL_GOP_BOTH = E_HAL_GOP_H_MIRROR | E_HAL_GOP_V_MIRROR,
} HalGopMirrorType_e;

typedef enum
{
    GOP_OK,    
    GOP_ERR_NO_INT,         //GOP no interrupt 
    GOP_ERR_GWIN_OUT_OF_SCREEN, //Gwin location out of strech window range
    GOP_ERR_SCREEN_TOO_SMALL, //Gwin size larger than strech window size 
    GOP_ERR_NOT_SUPPORT_MULTI_GWIN,  //Current GOP not support multiple GWin
    GOP_ERR_MULTI_GWIN_OVERLAY,   //Multiple GWIN overlayed
    GOP_ERR_MULTI_GWIN_FMT_CONFLICT, //Multiple GWIN Bpp not the same   
    GOP_ERR_UNKNOWN_GOP_ID,	//Unknown GOP ID
    GOP_ERR_UNKNOWN_COLOR_ORDER,
    GOP_ERR_SCALE_RATIO
} GOPStatus_e;

//=============================================================================
// struct
//=============================================================================

typedef struct
{
    u16 u16X;
    u16 u16Y;
    u16 u16Width;
    u16 u16Height;
} HalGopWindowType_t;

typedef struct
{
    HalGopDisplayModeType_t eDisplayMode;
    HalGopOutFormatType_e eOutFormat;
    HalGopWindowType_t tStretchWindow;
    u32 u32StretchHRatio;
} HalGopParamConfig_t;

typedef struct
{
    HalGopGwinSrcFormat_e eSrcFmt;
    HalGopWindowType_t tDispWindow;
    u32 u32BaseAddr;
    u16 u16Base_XOffset;
    u32 u32Base_YOffset;
} HalGopGwinParamConfig_t;

//=============================================================================

//=============================================================================

#ifndef __HAL_GOP_C__
#define INTERFACE extern
#else
#define INTERFACE
#endif
INTERFACE bool HalGopTransGwinId(HalGopIdNum_e eGopId, HalGopIdType_e *pHalId);
INTERFACE HalGopIdType_e HalGopGetTransId(HalGopIdNum_e eGopIdx);

INTERFACE void HalGopUpdateBase(HalGopIdType_e eGopId, u32 u32BaseAddr, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopUpdateParam(HalGopIdType_e eGopId, HalGopParamConfig_t tParamCfg);
INTERFACE GOPStatus_e HalGopUpdateGwinParam(HalGopIdType_e eGopId, HalGopGwinParamConfig_t tParamCfg, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopSetStretchWindowSize(HalGopIdType_e eGopId, HalGopWindowType_t tGwinCfg);
INTERFACE GOPStatus_e HalGopSetStretchWindowRatio(HalGopIdType_e eGopId, u32 u32HRatio, u32 u32VRatio);
INTERFACE void HalGopSetGwinSize(HalGopIdType_e eGopId, HalGopWindowType_t tGwinCfg, HalGopGwinSrcFormat_e eSrcFmt, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopSetOutFormat(HalGopIdType_e eGopId, bool bYUVOutput);
INTERFACE void HalGopSetConstantAlpha(HalGopIdType_e eGopId, bool bEn, u8 Alpha, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopSetColorKey(HalGopIdType_e eGopId, bool bEn, u8 u8R, u8 u8G, u8 u8B);
INTERFACE void HalGopSetPipeDelay(HalGopIdType_e eGopId, u8 delay);
INTERFACE void HalGopSetPaletteRiu(HalGopIdType_e eGopId, u8 u8Index, u8 u8A, u8 u8R, u8 u8G, u8 u8B);
INTERFACE void HalGopSetEnableGwin(HalGopIdType_e eGopId, bool bEn, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopSetScalerEnableGop(HalGopIdType_e eGopId, bool bEn);
INTERFACE GOPStatus_e HalGopSetSwapUV(HalGopIdNum_e eGopId, bool bSwap);
INTERFACE GOPStatus_e HalGopSetSwapYC(HalGopIdNum_e eGopId, bool bSwap);
INTERFACE GOPStatus_e HalGopSetSwapRB(HalGopIdNum_e eGopId, bool bSwap);
INTERFACE void HalGopGetEnableGwin(HalGopIdType_e eGopId, bool *bEn, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopGetScalerEnableGop(HalGopIdType_e eGopId, bool *bEn);
INTERFACE void HalGopGetColorKey(HalGopIdType_e eGopId, bool *bEn, u8 *u8R, u8  *u8G, u8  *u8B);
INTERFACE void HalGopSetAlphaBlending(HalGopIdType_e eGopId, bool bConstantAlpha, u8 Alpha, HalGopGwinIdType_e eGwinId);
INTERFACE void HalGopGetAlpha(HalGopIdType_e eGopId, bool *pbConstantAlpha, u8 *pu8ConstantAlphaValue, HalGopGwinIdType_e eGwinId);
INTERFACE bool HalGopGetSrcFmt(HalGopIdNum_e eGopNum, HalGopGwinSrcFormat_e *eGwinSrcFmt ,  HalGopGwinIdType_e eGwinId);
INTERFACE bool HalGopGetGWinSize(HalGopIdNum_e eGopNum, void *GwinCfg , HalGopGwinIdType_e eGwinId );
INTERFACE u8 HalGopGetGwinNum(HalGopIdNum_e eGopId);
INTERFACE bool HalGopGetStrechWinSize(HalGopIdNum_e eGopNum, void *StWinCfg );
//Extend API
INTERFACE void HalGopSetMirrorMode(HalGopIdNum_e eGopNum, HalGopMirrorType_e eMirrorType, u16 u16Width, u16 u16Height);
u32 HalGOPRegisterRead(u32 u32Addr);
#undef INTERFACE
#endif /* __HAL_GOP_H__ */
