//------------------------------------------------------------------------------
//
//  File        : component_display.c
//  Description : Source file of display component configuration
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
#include "lcd_common.h"
#include "component_display.h"

#include "halPnl.h"
#include "hal_mipi_dsi.h"
#include "hal_int_ctrl_pub.h"
#include "drv_pnl.h"
#include "drv_dec_scl_hvsp_st.h"
#include "drv_dec_scl_hvsp.h"
#include "drv_scl_pq_define.h"
#include "drv_scl_pq.h"
#include "drv_scl_dbg.h"
#include "drv_scl_os.h"
#include "drv_scl_vip_m_st.h"
#include "drv_dec_scl_vip_m.h"
#include "drvMVOP.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define DROP_FRAME_CNT  (5)

#define COMPONENT_DISP_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_DISP_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _Dspy_Status
{
    MMP_BOOL bIsMVOPInit;   // Display pipeline front-end
    MMP_BOOL bIsPQInit;
    MMP_BOOL bIsHVSPInit;
    MMP_BOOL bIsPanelInit;
} Dspy_Status;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_ERR Component_Display_InitDevice(void *handler);
MMP_ERR Component_Display_UnInitDevice(void *handler);
MMP_ERR Component_Display_OpenDevice(void *handler);
MMP_ERR Component_Display_CloseDevice(void *handler);
MMP_ERR Component_Display_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_Display_SetParameter(void *handler, int type, void* pParam);
MMP_ERR Component_Display_GetParameter(void *handler, int type, void* pParam);

MMP_COMPONENT_BUFFER_INFO Component_Display_BufInfo;
MMP_COMPONENT_PORT_INFO Component_Display_InPort;
MMP_COMPONENT_PORT_INFO Component_Display_OutPort[MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DISP_MemoryInfo;
MMP_COMPONENT_HANDLER_DISPLAY Component_DISP_DeviceInfo;

MMP_COMPONENT_BASE Component_Display =
{
    "DISP",
    MMP_COMPONENT_STATE_INVALID,            // ulState
    MMP_TRUE,                               // bRegistered
    MMP_FALSE,                              // bByPass
    0,                                      // ubOutputPortNum
    &Component_DISP_MemoryInfo,             // MemoryInfo
    NULL,                                   // BufferInfo
    &Component_Display_InPort,              // pInPort
    NULL,                                   // pOutPort
    {
        &MMP_CompCtl_UpdateBuffer_Frm,
        &MMP_CompCtl_EmptyBuffer_Frm,
        &MMP_CompCtl_EmptyOrderBuffer_Frm,
        &MMP_CompCtl_EmptyBufferDone_Frm,
    },
    Component_Display_InitDevice,           // pfInit
    Component_Display_OpenDevice,           // pfOpen
    NULL,                                   // pfAllocateMemory
    NULL,                                   // pfFreeMemory
    Component_Display_UnInitDevice,         // pfUnInit
    Component_Display_CloseDevice,          // pfClose
    Component_Display_SetParameter,         // pfSetParameter
    Component_Display_GetParameter,         // pfGetParameter
    NULL,                                   // pfUpdateBuffer
    Component_Display_EmptyBuffer,          // pfEmptyBuffer
    NULL,                                   // pfEmptyBufferDone
    NULL,                                   // pfGetBufferInfo
    &Component_DISP_DeviceInfo              // DeviceInfo
};

static Dspy_Status m_stDspyStatus;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_Display_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_InitDevice(void *handler)
{
    MVOP_DrvStatus stMVOPSts;

    // Init display pipeline
    if (m_stDspyStatus.bIsMVOPInit != 1) {
       MDrv_MVOP_GetStatus(&stMVOPSts);
       if (stMVOPSts.bIsInit == 0) {
            MDrv_MVOP_Init();
            MDrv_MVOP_SetFrequency(E_MVOP_144MHZ);
       }
       m_stDspyStatus.bIsMVOPInit = 1;
    }

    // Init PQ setting
    if (m_stDspyStatus.bIsPQInit != 1) {
        MDrv_PQ_DesideSrcType(PQ_DSPY_WINDOW, PQ_INPUT_SOURCE_DRAM);
        MDrv_PQ_LoadSettings(PQ_DSPY_WINDOW);

        MDrvDecSclOSDBLocConfig(MDRV_DEC_OSDB_LOC_PASS_VIP);
        Drv_DEC_HVSP_Init(NULL);
        m_stDspyStatus.bIsPQInit = 1;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Display_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Display_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DISPLAY   *pDisp = (MMP_COMPONENT_HANDLER_DISPLAY *)pComp->DeviceInfo;
    DISPLAY_COMP_RECT               *pInRect;
    DISPLAY_COMP_RECT               *pOutRect;
    DISPLAY_COMP_RECT               *pCropRect;
    DISPLAY_COMP_RECT               *pBkColRect;
    DISPLAY_COMP_SCL_CFG            *pSclCfg;
    MVOP_InputCfg                   stInputCfg;
    ST_DEC_HVSP_SCALING_CONFIG      stScaleCfg;
    u16                             u16PnlWidth = 0;
    u16                             u16PnlHeight = 0;
    MVOP_DrvStatus                  stMvopStatus;

    pInRect     = &pDisp->stInRect;
    pOutRect    = &pDisp->stOutRect;
    pCropRect   = &pDisp->stCropRect;
    pBkColRect  = &pDisp->stBkColRect;
    pSclCfg     = &pDisp->stSclCfg;

    // Set HVSP setting first
    stScaleCfg.u16Src_Width  = pCropRect->ulW;
    stScaleCfg.u16Src_Height = pCropRect->ulH;
    stScaleCfg.u16Dsp_Width  = pOutRect->ulW;
    stScaleCfg.u16Dsp_Height = pOutRect->ulH;
    stScaleCfg.bScl_H_Bypass = pSclCfg->bSclHBypass;
    stScaleCfg.bScl_V_Bypass = pSclCfg->bSclVBypass;

    Drv_DEC_HVSP_SetScaling(E_DEC_HVSP_ID_1, stScaleCfg, NULL);

    if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV420) {
        stInputCfg.bYUV_RGB_SEL = 1;
        stInputCfg.bYUV422      = 0;
        stInputCfg.b422pack     = 0;
        stInputCfg.bDramRdContd = 1;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV422) {
        stInputCfg.bYUV_RGB_SEL = 1;
        stInputCfg.bYUV422      = 1;
        stInputCfg.b422pack     = 1;
        stInputCfg.bDramRdContd = 1;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV420_TILE) {
        stInputCfg.bYUV_RGB_SEL = 1;
        stInputCfg.bYUV422      = 0;
        stInputCfg.bDramRdContd = 0;
        stInputCfg.b422pack     = 0;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_RGB565) {
        stInputCfg.bYUV_RGB_SEL = 0;
    }

    stInputCfg.u16HSize     = pCropRect->ulW;
    stInputCfg.u16VSize     = pCropRect->ulH;
    stInputCfg.u16StripSize = pInRect->ulW;

    if (m_stDspyStatus.bIsMVOPInit == 1) {
        if ((pCropRect->ulW  < pInRect->ulW) || (pCropRect->ulH < pInRect->ulH)) {
            stInputCfg.u16CropX         = pCropRect->ulX;
            stInputCfg.u16CropY         = pCropRect->ulY;
            stInputCfg.u16CropWidth     = pCropRect->ulW;
            stInputCfg.u16CropHeight    = pCropRect->ulH;
            MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &stInputCfg);
            MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &stInputCfg);
        }
        else {
            MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &stInputCfg);
        }
    }

    u16PnlWidth = DrvLCDGePanelWidth();
    u16PnlHeight = DrvLCDGePanelHeight();

    if (DrvLCDGeCurPanelType() != LCD_TYPE_MIPIDSI) {
        if ((u16PnlWidth > pOutRect->ulW) || (u16PnlHeight > pOutRect->ulH)) {
            DrvLCDEnableBG(0);
            DrvLCDSetBGRegion(pBkColRect->ulX, pBkColRect->ulY, pBkColRect->ulW, pBkColRect->ulH, u16PnlWidth);
            DrvLCDEnableBG(1);
        }
    }

    DrvLCD_RGB_EN(1);

    if (DrvLCDGeCurPanelType() == LCD_TYPE_MIPIDSI) {
        COMPONENT_DISP_DBG_MSG(1, "[Component display] DSI clock enable\n");
        if (!Hal_DSI_GetDSIClkSt())
            Hal_DSI_EnableClk();
    }

    if (m_stDspyStatus.bIsMVOPInit == 1) {

        MDrv_MVOP_Enable(1);
        MDrv_MVOP_GetStatus(&stMvopStatus);

        if (stMvopStatus.bIsBlackBG == 0) {
            MDrv_MVOP_SetBlackBG(1);
        }
    }

    *(volatile unsigned short *)0x1F207148 = 0x24;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Display_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_CloseDevice(void *handler)
{
    MS_U8 status=0;
    MDrv_MVOP_SetBlackBG(1);
    return MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : Component_Display_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DISPLAY   *pDisp = (MMP_COMPONENT_HANDLER_DISPLAY *)pComp->DeviceInfo;
    MMP_BOOL                        bProgressive = MMP_TRUE;
    MMP_BOOL                        b422pack = MMP_FALSE;
    MS_U32                          u32YAddr = 0;
    MS_U32                          u32UVAddr = 0;
    MS_U32                          u32GetYAddr = 0;
    MS_U32                          u32GetUVAddr = 0;
    DISPLAY_COMP_RECT               *pInRect;
    MMP_COMPONENT_BUFFER_INFO       CustBufInfo;
    MVOP_DrvStatus                  stMvopStatus;

    pInRect = &pDisp->stInRect;

    if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV420) {
        u32YAddr    = pComp->pInPort->bufInfo.u64BufPhyAddr;
        u32UVAddr   = u32YAddr + pInRect->ulW*pInRect->ulH;
        b422pack    = 0;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV422) {
        u32YAddr    = pComp->pInPort->bufInfo.u64BufPhyAddr;
        u32UVAddr   = u32YAddr + pInRect->ulW*pInRect->ulH;
        b422pack    = 1;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_YUV420_TILE) {
        u32YAddr    = pComp->pInPort->bufInfo.u64BufPhyAddr;
        u32UVAddr   = u32YAddr + pInRect->ulW*pInRect->ulH;
        b422pack    = 0;
    }
    else if (pDisp->eColorFormat == MMP_DISPLAY_COLOR_RGB565) {
        // TBD
    }

    #if 1
    MDrv_MVOP_SetBaseAdd((MS_U32)u32YAddr,
                         (MS_U32)u32UVAddr,
                         (MS_BOOL)bProgressive,
                         (MS_BOOL)b422pack);
    #else

    DrvLCDLoadAddress(u32YAddr, u32UVAddr, pInRect->ulW, bProgressive, b422pack);

    #endif
    MDrv_MVOP_GetStatus(&stMvopStatus);

    if (stMvopStatus.bIsBlackBG == 1) {
        do {
            MDrv_MVOP_GetBaseAdd(&u32GetYAddr, &u32GetUVAddr);
            //UartSendTrace(" u32GetYAddr %x %x",u32GetYAddr,u32YAddr);
        } while ((u32GetYAddr != u32YAddr) || (u32GetUVAddr != u32UVAddr));

        MDrv_MVOP_SetBlackBG(0);
    }

    DrvLCDRefresh();

    CustBufInfo.ulBufAddr = u32UVAddr;

    MMP_CompCtl_StoreBufferDone((void *)pComp, 0, &CustBufInfo);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Display_SetParameter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_SetParameter(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DISPLAY   *pDisp = &Component_Display_Handler[0];;
    MMP_COMPONENT_MEMORY_INFO       *pDispMem = &Component_Display_Memory[0];
    DISPLAY_COMP_RECT               *pDispRect = NULL;
    DISPLAY_COMP_SCL_CFG            *pDispSclCfg = NULL;

    switch(type) {
    case DISPLAY_COMP_PARAM_IN_RECT:
        pDispRect = &pDisp->stInRect;
        memcpy(pDispRect, (DISPLAY_COMP_RECT*)pParam, sizeof(DISPLAY_COMP_RECT));
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update InRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pDispRect->ulX, pDispRect->ulY, pDispRect->ulW, pDispRect->ulH);
        break;
    case DISPLAY_COMP_PARAM_CROP_RECT:
        pDispRect = &pDisp->stCropRect;
        memcpy(pDispRect, (DISPLAY_COMP_RECT*)pParam, sizeof(DISPLAY_COMP_RECT));
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update CropRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pDispRect->ulX, pDispRect->ulY, pDispRect->ulW, pDispRect->ulH);
        break;
    case DISPLAY_COMP_PARAM_OUT_RECT:
        pDispRect = &pDisp->stOutRect;
        memcpy(pDispRect, (DISPLAY_COMP_RECT*)pParam, sizeof(DISPLAY_COMP_RECT));
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update OutRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pDispRect->ulX, pDispRect->ulY, pDispRect->ulW, pDispRect->ulH);
        break;
    case DISPLAY_COMP_PARAM_BK_COLOR_RECT:
        pDispRect = &pDisp->stBkColRect;
        memcpy(pDispRect, (DISPLAY_COMP_RECT*)pParam, sizeof(DISPLAY_COMP_RECT));
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update BkColRect [%d][%d][%d][%d]\r\n",
                              pComp->name, pDispRect->ulX, pDispRect->ulY, pDispRect->ulW, pDispRect->ulH);
        break;
    case DISPLAY_COMP_PARAM_COLOR_FORMAT:
        pDisp->eColorFormat = *(MMP_DISPLAY_COLORMODE*)pParam;
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update ColorFormat [%d]\r\n", pComp->name, pDisp->eColorFormat);
        break;
    case DISPLAY_COMP_PARAM_BUF_COUNT:
        pDispMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pDispMem->ubBufNum);
        break;
    case DISPLAY_COMP_PARAM_BUF_SIZE:
        pDispMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pDispMem->ulBufSize);
        break;
    case DISPLAY_COMP_PARAM_SCL_CFG:
        pDispSclCfg = &pDisp->stSclCfg;
        memcpy(pDispSclCfg, (DISPLAY_COMP_SCL_CFG*)pParam, sizeof(DISPLAY_COMP_SCL_CFG));
        COMPONENT_DISP_DBG_MSG(1, "[%s] Update Scl Cfg [%d][%d]\r\n",
                               pComp->name, pDispSclCfg->bSclHBypass, pDispSclCfg->bSclVBypass);
        break;
    default:
        COMPONENT_DISP_DBG_ERR(1, "[%s] UnSupport DISP Param Type\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Display_GetParameter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Display_GetParameter(void *handler, int type, void* pParam)
{
    // TBD
    return MMP_ERR_NONE;
}
