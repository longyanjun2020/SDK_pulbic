//------------------------------------------------------------------------------
//
//  File        : component_pip.c
//  Description : Source file of pip component configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"
#include "component_pip.h"
#include "drv_gop.h"
#include "drv_gop_io.h"
#include "lcd_common.h"
#include "halPnl.h"
#include "drv_pnl.h"
#include "sys_sys.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

MMP_ERR Component_PIP_InitDevice(void *handler);
MMP_ERR Component_PIP_UnInitDevice(void * handler);
MMP_ERR Component_PIP_Open(void * handler);
MMP_ERR Component_PIP_Close(void * handler);
MMP_ERR Component_PIP_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_PIP_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_PIP_EmptyBuffer(void * handler,MMP_ULONG ulSize,void * BufInfo);

//==============================================================================
//
//                              MACRO
//
//==============================================================================

#define COMPONENT_PIP_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_PIP_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define GET_GWIN_COLOR_FMT(c) (\
                            c == PIP_COMP_COLOR_FMT_RGB565      ? E_DRV_GOP_GWIN_SRC_FMT_RGB565   :   \
                            c == PIP_COMP_COLOR_FMT_BGR565      ? E_DRV_GOP_GWIN_SRC_FMT_RGB565   :   \
                            c == PIP_COMP_COLOR_FMT_ARGB8888    ? E_DRV_GOP_GWIN_SRC_FMT_ARGB8888 :   \
                            c == PIP_COMP_COLOR_FMT_ABGR8888    ? E_DRV_GOP_GWIN_SRC_FMT_ABGR8888 :   \
                            c == PIP_COMP_COLOR_FMT_YUYV422     ? E_DRV_GOP_GWIN_SRC_FMT_UV8Y8    :   \
                            c == PIP_COMP_COLOR_FMT_YVYU422     ? E_DRV_GOP_GWIN_SRC_FMT_UV8Y8    :   \
                            c == PIP_COMP_COLOR_FMT_UYVY422     ? E_DRV_GOP_GWIN_SRC_FMT_UV8Y8    :   \
                            c == PIP_COMP_COLOR_FMT_VYUY422     ? E_DRV_GOP_GWIN_SRC_FMT_UV8Y8    :   \
                            E_DRV_GOP_GWIN_SRC_FMT_NUM)

#define GET_ALPHA_FMT(a) (\
                            a == PIP_COMP_ALPHA_FMT_GLOBAL      ? E_DRV_GOP_GWIN_ALPHA_CONSTANT: \
                            a == PIP_COMP_ALPHA_FMT_PIXEL       ? E_DRV_GOP_GWIN_ALPHA_PIXEL: \
                            E_DRV_GOP_GWIN_ALPHA_NUM)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if 0
static DrvGopIoPaletteEntry_t _gatGop1Palette[256] =
{
    {{  0,  0, 128, 128}}, {{  0,  0,  0, 180}}, {{  0, 128,  0, 220}}, {{  0, 128, 128,  0}},
    {{128,  0,  0, 255}}, {{128,  0, 128, 255}}, {{128, 128,  0, 255}}, {{192, 192, 192,  0}},
    {{192, 220, 192, 255}}, {{240, 202, 166, 255}}, {{  0, 32, 64, 255}}, {{  0, 32, 96,  0}},
    {{  0, 32, 128, 255}}, {{  0, 32, 160, 255}}, {{  0, 32, 192,  0}}, {{  0, 32, 224,  0}},
    {{  0, 64,  0, 255}}, {{  0, 64, 32, 255}}, {{  0, 64, 64,  0}}, {{  0, 64, 96,  0}},
    {{  0, 64, 128, 255}}, {{  0, 64, 160, 255}}, {{  0, 64, 192,  0}}, {{  0, 64, 224,  0}},
    {{  0, 96,  0, 255}}, {{  0, 96, 32, 255}}, {{  0, 96, 64,  0}}, {{  0, 96, 96,  0}},
    {{  0, 96, 128, 255}}, {{  0, 96, 160, 255}}, {{  0, 96, 192,  0}}, {{  0, 96, 224,  0}},
    {{  0, 128,  0, 255}}, {{  0, 128, 32, 255}}, {{  0, 128, 64,  0}}, {{  0, 128, 96,  0}},
    {{  0, 128, 128, 255}}, {{  0, 128, 160, 255}}, {{  0, 128, 192,  0}}, {{  0, 128, 224,  0}},
    {{  0, 160,  0, 255}}, {{  0, 160, 32, 255}}, {{  0, 160, 64,  0}}, {{  0, 160, 96,  0}},
    {{  0, 160, 128, 255}}, {{  0, 160, 160, 255}}, {{  0, 160, 192,  0}}, {{  0, 160, 224,  0}},
    {{  0, 192,  0, 255}}, {{  0, 192, 32, 255}}, {{  0, 192, 64,  0}}, {{  0, 192, 96,  0}},
    {{  0, 192, 128, 255}}, {{  0, 192, 160, 255}}, {{  0, 192, 192,  0}}, {{  0, 192, 224,  0}},
    {{  0, 224,  0, 255}}, {{  0, 224, 32, 255}}, {{  0, 224, 64,  0}}, {{  0, 224, 96,  0}},
    {{  0, 224, 128, 255}}, {{  0, 224, 160, 255}}, {{  0, 224, 192,  0}}, {{  0, 224, 224,  0}},
    {{ 64,  0,  0, 255}}, {{ 64,  0, 32, 255}}, {{ 64,  0, 64,  0}}, {{ 64,  0, 96,  0}},
    {{ 64,  0, 128, 255}}, {{ 64,  0, 160, 255}}, {{ 64,  0, 192,  0}}, {{ 64,  0, 224,  0}},
    {{ 64, 32,  0, 255}}, {{ 64, 32, 32, 255}}, {{ 64, 32, 64,  0}}, {{ 64, 32, 96,  0}},
    {{ 64, 32, 128, 255}}, {{ 64, 32, 160, 255}}, {{ 64, 32, 192,  0}}, {{ 64, 32, 224,  0}},
    {{ 64, 64,  0, 255}}, {{ 64, 64, 32, 255}}, {{ 64, 64, 64,  0}}, {{ 64, 64, 96,  0}},
    {{ 64, 64, 128, 255}}, {{ 64, 64, 160, 255}}, {{ 64, 64, 192,  0}}, {{ 64, 64, 224,  0}},
    {{ 64, 96,  0, 255}}, {{ 64, 96, 32, 255}}, {{ 64, 96, 64,  0}}, {{ 64, 96, 96,  0}},
    {{ 64, 96, 128, 255}}, {{ 64, 96, 160, 255}}, {{ 64, 96, 192,  0}}, {{ 64, 96, 224,  0}},
    {{ 64, 128,  0, 255}}, {{ 64, 128, 32, 255}}, {{ 64, 128, 64,  0}}, {{ 64, 128, 96,  0}},
    {{ 64, 128, 128, 250}}, {{ 64, 128, 160,  0}}, {{ 64, 128, 192,  0}}, {{ 64, 128, 224,  0}},
    {{ 64, 160,  0, 255}}, {{ 64, 160, 32,  0}}, {{ 64, 160, 64,  0}}, {{ 64, 160, 96,  0}},
    {{ 64, 160, 128, 255}}, {{ 64, 160, 160,  0}}, {{ 64, 160, 192,  0}}, {{ 64, 160, 224,  0}},
    {{ 64, 192,  0, 255}}, {{ 64, 192, 32,  0}}, {{ 64, 192, 64,  0}}, {{ 64, 192, 96,  0}},
    {{ 64, 192, 128, 255}}, {{ 64, 192, 160,  0}}, {{ 64, 192, 192,  0}}, {{ 64, 192, 224,  0}},
    {{ 64, 224,  0, 255}}, {{ 64, 224, 32,  0}}, {{ 64, 224, 64,  0}}, {{ 64, 224, 96,  0}},
    {{ 64, 224, 128, 255}}, {{ 64, 224, 160,  0}}, {{ 64, 224, 192,  0}}, {{ 64, 224, 224,  0}},
    {{128,  0,  0, 255}}, {{128,  0, 32,  0}}, {{128,  0, 64,  0}}, {{128,  0, 96,  0}},
    {{128,  0, 128, 255}}, {{128,  0, 160,  0}}, {{128,  0, 192,  0}}, {{128,  0, 224,  0}},
    {{128, 32,  0, 255}}, {{128, 32, 32,  0}}, {{128, 32, 64,  0}}, {{128, 32, 96,  0}},
    {{128, 32, 128, 255}}, {{128, 32, 160,  0}}, {{128, 32, 192,  0}}, {{128, 32, 224,  0}},
    {{128, 64,  0, 255}}, {{128, 64, 32,  0}}, {{128, 64, 64,  0}}, {{128, 64, 96,  0}},
    {{128, 64, 128, 255}}, {{128, 64, 160,  0}}, {{128, 64, 192,  0}}, {{128, 64, 224,  0}},
    {{128, 96,  0, 255}}, {{128, 96, 32,  0}}, {{128, 96, 64,  0}}, {{128, 96, 96,  0}},
    {{128, 96, 128, 255}}, {{128, 96, 160,  0}}, {{128, 96, 192,  0}}, {{128, 96, 224,  0}},
    {{128, 128,  0, 255}}, {{128, 128, 32,  0}}, {{128, 128, 64,  0}}, {{128, 128, 96,  0}},
    {{128, 128, 128, 255}}, {{128, 128, 160,  0}}, {{128, 128, 192,  0}}, {{128, 128, 224,  0}},
    {{128, 160,  0, 255}}, {{128, 160, 32,  0}}, {{128, 160, 64,  0}}, {{128, 160, 96,  0}},
    {{128, 160, 128, 255}}, {{128, 160, 160,  0}}, {{128, 160, 192,  0}}, {{128, 160, 224,  0}},
    {{128, 192,  0, 255}}, {{128, 192, 32,  0}}, {{128, 192, 64,  0}}, {{128, 192, 96,  0}},
    {{128, 192, 128, 255}}, {{128, 192, 160,  0}}, {{128, 192, 192,  0}}, {{128, 192, 224,  0}},
    {{128, 224,  0, 255}}, {{128, 224, 32,  0}}, {{128, 224, 64,  0}}, {{128, 224, 96,  0}},
    {{128, 224, 128, 255}}, {{128, 224, 160,  0}}, {{128, 224, 192,  0}}, {{128, 224, 224,  0}},
    {{192,  0,  0, 255}}, {{192,  0, 32,  0}}, {{192,  0, 64,  0}}, {{192,  0, 96,  0}},
    {{192,  0, 128, 255}}, {{192,  0, 160,  0}}, {{192,  0, 192,  0}}, {{192,  0, 224,  0}},
    {{192, 32,  0, 255}}, {{192, 32, 32,  0}}, {{192, 32, 64,  0}}, {{192, 32, 96,  0}},
    {{192, 32, 128, 255}}, {{192, 32, 160,  0}}, {{192, 32, 192,  0}}, {{192, 32, 224,  0}},
    {{192, 64,  0, 255}}, {{192, 64, 32,  0}}, {{192, 64, 64,  0}}, {{192, 64, 96,  0}},
    {{192, 64, 128, 255}}, {{192, 64, 160,  0}}, {{192, 64, 192,  0}}, {{192, 64, 224,  0}},
    {{192, 96,  0, 255}}, {{192, 96, 32,  0}}, {{192, 96, 64,  0}}, {{192, 96, 96,  0}},
    {{192, 96, 128, 255}}, {{192, 96, 160,  0}}, {{192, 96, 192,  0}}, {{192, 96, 224,  0}},
    {{192, 128,  0, 255}}, {{192, 128, 32,  0}}, {{192, 128, 64,  0}}, {{192, 128, 96,  0}},
    {{192, 128, 128, 255}}, {{192, 128, 160,  0}}, {{192, 128, 192,  0}}, {{192, 128, 224,  0}},
    {{192, 160,  0, 255}}, {{192, 160, 32,  0}}, {{192, 160, 64,  0}}, {{192, 160, 96,  0}},
    {{192, 160, 128, 255}}, {{192, 160, 160,  0}}, {{192, 160, 192,  0}}, {{192, 160, 224,  0}},
    {{192, 192,  0, 255}}, {{192, 192, 32,  0}}, {{192, 192, 64,  0}}, {{192, 192, 96,  0}},
    {{192, 192, 128, 255}}, {{192, 192, 160,  0}}, {{240, 251, 255,  0}}, {{164, 160, 160,  0}},
    {{128, 128, 128, 255}}, {{  0,  0, 255,  0}}, {{  0, 255,  0,  0}}, {{  0, 255, 255,  0}},
    {{255,  0,  0, 255}}, {{255,  0, 255, 255}}, {{255, 255,  0,  0}}, {{255, 255, 255,  200}}
};
#endif

MMP_COMPONENT_BUFFER_INFO Component_PIP_BufInfo[COMPONENT_PIP_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_PIP_InPort[COMPONENT_PIP_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_PIP_OutPort[COMPONENT_PIP_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_PIP_MemoryInfo[COMPONENT_PIP_MAX_NUM];
MMP_COMPONENT_HANDLER_PIP Component_PIP_DevInfo[COMPONENT_PIP_MAX_NUM];

MMP_COMPONENT_BASE Component_PIP[COMPONENT_PIP_MAX_NUM] =
{
    {
        "PIP0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_PIP_MemoryInfo[0],           // MemoryInfo
        Component_PIP_BufInfo[0],               // BufferInfo
        &Component_PIP_InPort[0],               // pInPort
        Component_PIP_OutPort[0],               // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_PIP_InitDevice,               // pfInit
        Component_PIP_Open,                     // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_PIP_UnInitDevice,             // pfUnInit
        Component_PIP_Close,                    // pfClose
        Component_PIP_SetParam,                 // pfSetParameter
        Component_PIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_PIP_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_PIP_DevInfo[0]               // DeviceInfo
    },
    {
        "PIP1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_PIP_MemoryInfo[1],           // MemoryInfo
        Component_PIP_BufInfo[1],               // BufferInfo
        &Component_PIP_InPort[1],               // pInPort
        Component_PIP_OutPort[1],               // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_PIP_InitDevice,               // pfInit
        Component_PIP_Open,                     // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_PIP_UnInitDevice,             // pfUnInit
        Component_PIP_Close,                    // pfClose
        Component_PIP_SetParam,                 // pfSetParameter
        Component_PIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_PIP_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_PIP_DevInfo[1]               // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_PIP_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_Open
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_Open(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_PIP   *pPIP = (MMP_COMPONENT_HANDLER_PIP *)pComp->DeviceInfo;
    PIP_COMP_RECT               *pBGRect = &pPIP->stBgRect;
    PIP_COMP_RECT               *pFGRect = &pPIP->stFgRect;

    DrvGopGwinAlphaConfig_t     tAlphaCfg;
    DrvGopColorKeyConfig_t      tColorkeyCfg;
    DrvGopWindowConfig_t        tStretchWinRect;
    DrvGopWindowConfig_t        tGwinRect;
    DrvGopModeConfig_t          tGopModeCfg;
    DrvGopGwinConfig_t          tInitCfg0;
    DrvGopMirrorType_e          eMirrorType = E_DRV_GOP_NONE;

    tInitCfg0.eGwinId = E_DRV_GOP_GWIN_ID_1;
    tInitCfg0.eSrcFmt = GET_GWIN_COLOR_FMT(pPIP->ColorFmt);
    tInitCfg0.tDisplayWin.u16Height = pFGRect->ulH;
    tInitCfg0.tDisplayWin.u16Width = pFGRect->ulW;
    tInitCfg0.tDisplayWin.u16X = pFGRect->ulX;
    tInitCfg0.tDisplayWin.u16Y = pFGRect->ulY;
    tInitCfg0.u16Base_XOffset = 0;
    tInitCfg0.u32BaseAddr = 0;
    tInitCfg0.u32Base_YOffset = 0;

    tGopModeCfg.eOutFmt = E_DRV_GOP_OUT_FMT_YUV;
    tGopModeCfg.eDisplyMode = E_DRV_GOP_DISPLAY_MD_PROGRESS;
    tGopModeCfg.pstGwinCfg = &tInitCfg0;
    tGopModeCfg.tOsdDisplayWindow.u16Width = pBGRect->ulW;
    tGopModeCfg.tOsdDisplayWindow.u16Height = pBGRect->ulH;
    tGopModeCfg.tOsdDisplayWindow.u16X = pBGRect->ulX;
    tGopModeCfg.tOsdDisplayWindow.u16Y = pBGRect->ulY;
    tGopModeCfg.eStretchHRatio = E_DRV_GOP_STRETCH_RATIO_1;
    tGopModeCfg.u8GWinNum = 1; //Means only update first GWIN's parameters.
    DrvGopSetModeConfig(E_DRV_GOP_ID_1, &tGopModeCfg);  //set mode will do GOP reset

    // Set out format.
    DrvGopSetOutFormat(E_DRV_GOP_ID_1, tGopModeCfg.eOutFmt);

    // Set Stretch win attr.
    tStretchWinRect.u16X = pBGRect->ulX;
    tStretchWinRect.u16Y = pBGRect->ulY;
    tStretchWinRect.u16Width = pBGRect->ulW;
    tStretchWinRect.u16Height = pBGRect->ulH;
    DrvGopSetStretchWindowSize(E_DRV_GOP_ID_1, tStretchWinRect);

    // Set GWIN attr.
    tGwinRect.u16X = pFGRect->ulX;
    tGwinRect.u16Y = pFGRect->ulY;
    tGwinRect.u16Width = pFGRect->ulW;
    tGwinRect.u16Height = pFGRect->ulH;
    DrvGopSetGwinSize(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, tGwinRect, GET_GWIN_COLOR_FMT(pPIP->ColorFmt));

    // Set alpha attr.
    tAlphaCfg.eAlphaType = GET_ALPHA_FMT(pPIP->AlphaAttr.AlphaFmt);
    tAlphaCfg.u8ConstantAlpahValue = pPIP->AlphaAttr.Weight;
    DrvGopSetAlphaBlending(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, tAlphaCfg);

    // Set transparent color.
    tColorkeyCfg.bEn = MMP_FALSE;
    tColorkeyCfg.u8R = 0;
    tColorkeyCfg.u8G = 0;
    tColorkeyCfg.u8B = 0;
    DrvGopSetColorKey(E_DRV_GOP_ID_1, tColorkeyCfg);

    // Set gop1 palette. CHECK.
    //DrvGopIoSetPalette(E_DRV_GOP_ID_1, sizeof(_gatGop1Palette)/sizeof(_gatGop1Palette[0]), _gatGop1Palette);

    /* Is the GOP output order depends on MVOP ? */
    switch (pPIP->ColorFmt) {
    case PIP_COMP_COLOR_FMT_RGB565:
        DrvGopSetSwapRB(E_DRV_GOP_ID_1, MMP_FALSE);
        break;
    case PIP_COMP_COLOR_FMT_BGR565:
        DrvGopSetSwapRB(E_DRV_GOP_ID_1, MMP_TRUE);
        break;
    case PIP_COMP_COLOR_FMT_ARGB8888:
        DrvGopSetSwapRB(E_DRV_GOP_ID_1, MMP_FALSE);
        break;
    case PIP_COMP_COLOR_FMT_ABGR8888:
        DrvGopSetSwapRB(E_DRV_GOP_ID_1, MMP_FALSE);
        break;
    case PIP_COMP_COLOR_FMT_YUYV422:
        DrvGopSetSwapUV(E_DRV_GOP_ID_1, MMP_TRUE);
        DrvGopSetSwapYC(E_DRV_GOP_ID_1, MMP_FALSE);
        break;
    case PIP_COMP_COLOR_FMT_YVYU422:
        DrvGopSetSwapUV(E_DRV_GOP_ID_1, MMP_FALSE);
        DrvGopSetSwapYC(E_DRV_GOP_ID_1, MMP_FALSE);
        break;
    case PIP_COMP_COLOR_FMT_UYVY422:
        DrvGopSetSwapUV(E_DRV_GOP_ID_1, MMP_TRUE);
        DrvGopSetSwapYC(E_DRV_GOP_ID_1, MMP_TRUE);
        break;
    case PIP_COMP_COLOR_FMT_VYUY422:
        DrvGopSetSwapUV(E_DRV_GOP_ID_1, MMP_FALSE);
        DrvGopSetSwapYC(E_DRV_GOP_ID_1, MMP_TRUE);
        break;
    }

    if (pPIP->bMirror) {
        eMirrorType |= E_DRV_GOP_H_MIRROR;
    }
    if (pPIP->bFlip) {
        eMirrorType |= E_DRV_GOP_V_MIRROR;
    }

    DrvGopSetMirrorMode(E_DRV_GOP_ID_1, eMirrorType, tStretchWinRect);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_Close
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_Close(void *handler)
{
    //DrvGopSetScalerEnableGop(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_FALSE);
    DrvGopSetEnableGwin(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_FALSE);
    SYS_UDELAY(33000) ; //if GWIN disable and GOP reset simultaneously happen, lcd panel will see garbage line
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_PIP   *pPip       = &Component_PIP_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pPipMem    = &Component_PIP_Memory[0];

    if (strcmp("PIP0", pComp->name) == 0) {
        pPip    = &Component_PIP_Handler[0];
        pPipMem = &Component_PIP_Memory[0];
    }
    else if (strcmp("PIP1", pComp->name) == 0) {
        pPip    = &Component_PIP_Handler[1];
        pPipMem = &Component_PIP_Memory[1];
    }
    else {
        COMPONENT_PIP_DBG_ERR(1, "[%s] UnSupport PIP Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case PIP_COMP_PARAM_FG_RECT:
        memcpy(&pPip->stFgRect, (PIP_COMP_RECT*)pParam, sizeof(PIP_COMP_RECT));
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update FG Rect [%d][%d][%d][%d]\r\n",
                              pComp->name, pPip->stFgRect.ulX, pPip->stFgRect.ulY, pPip->stFgRect.ulW, pPip->stFgRect.ulH);
        break;
    case PIP_COMP_PARAM_BG_RECT:
        memcpy(&pPip->stBgRect, (PIP_COMP_RECT*)pParam, sizeof(PIP_COMP_RECT));
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update BG Rect [%d][%d][%d][%d]\r\n",
                              pComp->name, pPip->stBgRect.ulX, pPip->stBgRect.ulY, pPip->stBgRect.ulW, pPip->stBgRect.ulH);
        break;
    case PIP_COMP_PARAM_BUF_COUNT:
        pPipMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pPipMem->ubBufNum);
        break;
    case PIP_COMP_PARAM_BUF_SIZE:
        pPipMem->ulBufSize= *(MMP_ULONG*)pParam;
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update Buf Size [%d] Bytes\r\n", pComp->name, pPipMem->ulBufSize);
        break;
    case PIP_COMP_PARAM_H_MIRROR:
        pPip->bMirror = *(MMP_BOOL*)pParam;
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update H-Mirror [%d]\r\n", pComp->name, pPip->bMirror);
        break;
    case PIP_COMP_PARAM_V_FLIP:
        pPip->bFlip = *(MMP_BOOL*)pParam;
        COMPONENT_PIP_DBG_MSG(1, "[%s] Update V-Flip [%d]\r\n", pComp->name, pPip->bFlip);
        break;
    default:
        COMPONENT_PIP_DBG_ERR(1, "[%s] UnSupport PIP Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_GetParam(void *handler, int type, void* pParam)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_PIP_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_PIP_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_PIP   *pPIP = (MMP_COMPONENT_HANDLER_PIP *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_BOOL                    bGWinEn = MMP_FALSE;
    MMP_BOOL                    bOsdEn = MMP_FALSE;
    MMP_ULONG                   u32OldBaseAddr = (u32)pComp->pInPort->bufInfo.u64BufPhyAddr;
    MMP_ULONG                   u32NewBaseAddr = 0;
    DrvGopMirrorType_e          eMirrorType = E_DRV_GOP_NONE;
    DrvGopGwinConfig_t          tGWinCfg;
    PIP_COMP_RECT               *pBGRect = &pPIP->stBgRect;
    PIP_COMP_RECT               *pFGRect = &pPIP->stFgRect;

    tGWinCfg.eGwinId                = E_DRV_GOP_GWIN_ID_1;
    tGWinCfg.eSrcFmt                = GET_GWIN_COLOR_FMT(pPIP->ColorFmt);
    tGWinCfg.tDisplayWin.u16Height  = pFGRect->ulH;
    tGWinCfg.tDisplayWin.u16Width   = pFGRect->ulW;
    tGWinCfg.tDisplayWin.u16X       = pFGRect->ulX;
    tGWinCfg.tDisplayWin.u16Y       = pFGRect->ulY;
    tGWinCfg.u16Base_XOffset        = 0;
    tGWinCfg.u32BaseAddr            = 0;
    tGWinCfg.u32Base_YOffset        = 0;

    if (pPIP->bMirror) {
        eMirrorType |= E_DRV_GOP_H_MIRROR;
    }
    if (pPIP->bFlip) {
        eMirrorType |= E_DRV_GOP_V_MIRROR;
    }

    u32NewBaseAddr = DrvGopFindNewBaseAddr(u32OldBaseAddr, eMirrorType, tGWinCfg);

    // Update base addr.
    //DrvGopSetEnableGwin(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_FALSE);
    DrvGopUpdateBase(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, u32NewBaseAddr);

    DrvGopGetEnableGwin(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, &bGWinEn);
    if (bGWinEn == MMP_FALSE && pComp->ulState == MMP_COMPONENT_STATE_IDLE && pPIP->g_DropFrame == 0) {
        DrvGopSetEnableGwin(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_TRUE);
    }
    if(pPIP->g_DropFrame > 0)
        pPIP->g_DropFrame --;

    DrvGopGetScalerEnableGop(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, &bOsdEn);
    if (bOsdEn == MMP_FALSE) {
        DrvGopSetScalerEnableGop(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_TRUE);
    }

    /* The function of DrvGopGetScalerEnableGop is the same as DrvGopGetEnableGwin */
    //DrvGopGetScalerEnableGop(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, &bGopEn);
    //if (bGopEn == MMP_FALSE) {
    //  DrvGopSetScalerEnableGop(E_DRV_GOP_ID_1, E_DRV_GOP_GWIN_ID_1, MMP_TRUE);
    //}

    MMP_CompCtl_StoreBufferDone((void*)pComp, 0, NULL);

    return MMP_ERR_NONE;
}
