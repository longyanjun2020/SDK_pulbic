//------------------------------------------------------------------------------
//
//  File        : component_cfg.c
//  Description : Component configuration
//  Author      : CZ
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_cfg.h"
#include "mmp_component_ctl.h"

#include "component_raws.h"
#include "component_dip.h"
#include "component_scl.h"
#include "component_display.h"
#include "component_jpe.h"
#include "component_aud.h"
#include "component_pip.h"
#include "lcd_common.h"

#include "cust_component_cfg.h"
#include "sys_sys_isw_cli.h"
#include "sys_sys_isw_uart.h"
#include "drv_gop.h"
#include "drv_bus_axi.h"

//==============================================================================
//
//                              INTERNAL 
//
//==============================================================================

static MMP_ERR _component_ut(CLI_t* ptCli, char* p);
static MMP_ERR _component_dip_ut_2(CLI_t* ptCli, char* p);
static MMP_ERR _component_jpe_ut(CLI_t* ptCli, char* p);

//==============================================================================
//
//                              COMPONENT_SCRIPT_CFG 
//
//==============================================================================

#if 0
void _____Component_Script_____(){}
#endif

COMPONENT_CFG Component_Config_DIP_UT[5] =
{
    {
        &Component_DIP_Move[0],
        DEVICE_DIP_MOVE,
        NULL,
        1,
        {&Component_DIP_Rotate[0],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_DIP_Rotate[0],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Move[0],
        1,
        {&Component_DIP_Rotate[1],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_DIP_Rotate[1],
        DEVICE_DIP_ROTATE,
        &Component_DIP_Rotate[0],
        1,
        {&Component_DIP_Scale[0],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_DIP_Scale[0],
        DEVICE_DIP_SCALE,
        &Component_DIP_Rotate[1],
        1,
        {&Component_DIP_ColorConvert[0],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_DIP_ColorConvert[0],
        DEVICE_DIP_CC,
        &Component_DIP_Scale[0],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    }
};

COMPONENT_CFG Component_Config_JPE_UT[5] =
{
    {
        &Component_DIP_Move[0],
        DEVICE_DIP_MOVE,
        NULL,
        1,
        {&Component_DIP_Scale[0],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_DIP_Scale[0],
        DEVICE_DIP_SCALE,
        &Component_DIP_Move[0],
        1,
        {&Component_JPE[3],NULL,NULL,NULL,NULL},
        {MMP_TRUE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    },
    {
        &Component_JPE[3],
        DEVICE_JPE,
        &Component_DIP_Scale[0],
        0,
        {NULL,NULL,NULL,NULL,NULL},
        {MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE,MMP_FALSE}
    }
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____Script_Function_____(){}
#endif

/* Unit test */
extern const u8 rect_pattern_yuv422_yuyv[32*64*2];
extern const unsigned short icon_star_rgb565[32*64];

CUSTOMER_COMP_SCRIPT UtScriptCfg[5] =
{
    {COMPO_SCRIPT_UNIT_TEST, "DIP_UT", MMP_FALSE, Component_Config_DIP_UT, 5, 0, 2, 3, 0, 0}
};

CUSTOMER_COMP_SCRIPT JPEUtScriptCfg[2] =
{
    {COMPO_SCRIPT_UNIT_TEST, "JPE_UT", MMP_FALSE, Component_Config_JPE_UT, 3, 0, 0, 3},
};

CliParseToken_t g_atCompMenuTbl[] =
{
#if defined(__VER_DIP__)
    {"dip", "", "", _component_ut, NULL},
    {"dip2", "", "", _component_dip_ut_2, NULL},
#endif
    {"jpe", "", "", _component_jpe_ut, NULL},
    PARSE_TOKEN_DELIMITER
};

//==============================================================================
//
//                              Function
//
//==============================================================================

/* Unit test*/
static MMP_ERR OpenScript2(MMP_ULONG ulScriptNum);

static MMP_ERR _component_ut(CLI_t* ptCli, char* p)
{
    MMP_ULONG ulScriptNum = 0;

    CliTokenPopNum(ptCli, &ulScriptNum, 0);
    OpenScript2(ulScriptNum);
    
    return MMP_ERR_NONE;
}

static MMP_ERR OpenScript2(MMP_ULONG ulScriptNum)
{
#if 0
    CUSTOMER_COMP_SCRIPT *cfg = &UtScriptCfg[ulScriptNum];
    COMPONENT_CFG *Comp_Cfg = cfg->ScriptCfg;
    MMP_COMPONENT_BASE* pComp = NULL;
    MMP_UBYTE ubNum = cfg->ubNum;
    MMP_UBYTE i = 0;

    // Init and open script.
    for (i = 0 ; i < ubNum; i++) {
        Component_Update_Script(Comp_Cfg, i, cfg->ubUpdIdx[i]);
    }
    Component_Initial_Script(cfg->ScriptCfg, ubNum);
    Component_Open_Script(cfg->ScriptCfg,  ubNum);

    // Fill buffer by a 32x63 yuv422 image.
    pComp = Comp_Cfg[0].Component; // first component in this pipe.
    UartSendTrace("img buffer phy addr: 0x%08X. miu addr: 0x%08X\r\n", (MMP_ULONG)pComp->BufferInfo[0].u64BufPhyAddr, (MMP_ULONG)pComp->BufferInfo[0].u64BufMiuAddr);
    memcpy((void*)pComp->BufferInfo[0].ulBufAddr, &rect_pattern_yuv422_yuyv[0], 32*64*2);

    // Call MMP_CompCtl_EmptyBuffer explicity to start the pipe.
    MMP_CompCtl_EmptyBuffer_Frm(pComp, 0, NULL);
#endif
    return MMP_ERR_NONE;
}

static MMP_ERR _component_dip_ut_2(CLI_t* ptCli, char* p)
{
#if 0
    CUSTOMER_COMP_SCRIPT *cfg = &UtScriptCfg[1];
    COMPONENT_CFG *Comp_Cfg = cfg->ScriptCfg;
    MMP_COMPONENT_BASE* pComp = NULL;
    MMP_UBYTE ubNum = cfg->ubNum;
    MMP_UBYTE i = 0;
    DrvGopWindowConfig_t tGwinCfg;
    DrvGopWindowConfig_t tStretchWinCfg;
    MMP_ULONG ulIconVirAddr = 0, ulIconPhyAddr = 0;
    DrvGopModeConfig_t tGOPModeCfg;
    DrvGopGwinConfig_t tInitCfg0;
    DrvGopGwinAlphaConfig_t tAlphaCfg;

    /* Init GOP4. */
    tGOPModeCfg.eOutFmt = E_DRV_GOP_OUT_FMT_YUV;
    tGOPModeCfg.eDisplyMode = E_DRV_GOP_DISPLAY_MD_PROGRESS;

    tInitCfg0.eGwinId = E_DRV_GOP_GWIN_ID_1;
    tInitCfg0.eSrcFmt = E_DRV_GOP_GWIN_SRC_FMT_RGB565;
    tInitCfg0.tDisplayWin.u16Height = 32;
    tInitCfg0.tDisplayWin.u16Width = 64;
    tInitCfg0.tDisplayWin.u16X = 0;
    tInitCfg0.tDisplayWin.u16Y = 0;
    tInitCfg0.u16Base_XOffset = 0;
    tInitCfg0.u32BaseAddr = 0;
    tInitCfg0.u32Base_YOffset = 0;
    tGOPModeCfg.pstGwinCfg = &tInitCfg0;
    tGOPModeCfg.tOsdDisplayWindow.u16Width = 32;
    tGOPModeCfg.tOsdDisplayWindow.u16Height = 64;
    tGOPModeCfg.tOsdDisplayWindow.u16X = 0;
    tGOPModeCfg.tOsdDisplayWindow.u16Y = 0;
    tGOPModeCfg.eStretchHRatio = E_DRV_GOP_STRETCH_RATIO_1;
    tGOPModeCfg.u8GWinNum = DrvGopGetGwinNum(E_DRV_GOP_ID_4);
    DrvGopSetModeConfig(E_DRV_GOP_ID_4, &tGOPModeCfg);

    // Set out format.
    DrvGopSetOutFormat(E_DRV_GOP_ID_4, E_DRV_GOP_OUT_FMT_YUV);
    tStretchWinCfg.u16X = 0;
    tStretchWinCfg.u16Y = 0;
    tStretchWinCfg.u16Width = 32;
    tStretchWinCfg.u16Height = 64;
    DrvGopSetStretchWindowSize(E_DRV_GOP_ID_4, tStretchWinCfg);

    tGwinCfg.u16X = 0;
    tGwinCfg.u16Y = 0;
    tGwinCfg.u16Width = 32;
    tGwinCfg.u16Height = 64;
    DrvGopSetGwinSize(E_DRV_GOP_ID_4, E_DRV_GOP_GWIN_ID_1, tGwinCfg, E_DRV_GOP_GWIN_SRC_FMT_RGB565);

    tAlphaCfg.eAlphaType=E_DRV_GOP_GWIN_ALPHA_CONSTANT;
    tAlphaCfg.u8ConstantAlpahValue = 0;
    DrvGopSetAlphaBlending(E_DRV_GOP_ID_4, E_DRV_GOP_GWIN_ID_1, tAlphaCfg);

    // TBD
    //ulIconVirAddr = (MMP_ULONG)MsAllocateNonCacheMemExt(32*64*2, 4);
    //ulIconPhyAddr = (MMP_ULONG)MsVA2PA((void*)ulIconVirAddr);
    memcpy((void*)ulIconPhyAddr, &icon_star_rgb565[0], 32*64*2);
    UartSendTrace("icon viraddr: 0x%08X, icon phyaddr: 0x%08X\r\n", ulIconVirAddr, ulIconPhyAddr);
    DrvChipFlushMiuPipe();
    DrvGopUpdateBase(E_DRV_GOP_ID_4, E_DRV_GOP_GWIN_ID_1, ulIconPhyAddr);
    DrvGopSetPipeDelay(E_DRV_GOP_ID_4, 33);
    DrvGopSetEnableGwin(E_DRV_GOP_ID_4,  E_DRV_GOP_GWIN_ID_1, MMP_TRUE);
    
    // Init and open script.
    for (i = 0 ; i < ubNum; i++) {
        Component_Update_Script(Comp_Cfg, i, cfg->ubUpdIdx[i]);
    }
    Component_Initial_Script(cfg->ScriptCfg, ubNum);
    Component_Open_Script(cfg->ScriptCfg,  ubNum);

    // Fill buffer by a 32x63 yuv422 image.
    pComp = Comp_Cfg[0].Component; // first component in this pipe.
    UartSendTrace("img buffer phy addr: 0x%08X. miu addr: 0x%08X\r\n", (MMP_ULONG)pComp->BufferInfo[0].u64BufPhyAddr, (MMP_ULONG)pComp->BufferInfo[0].u64BufMiuAddr);
    memcpy((void*)pComp->BufferInfo[0].ulBufAddr, &rect_pattern_yuv422_yuyv[0], 32*64*2);

    // Call MMP_CompCtl_EmptyBuffer explicity to start the pipe.
    MMP_CompCtl_EmptyBuffer_Frm(pComp, 0, NULL);
#endif
    return MMP_ERR_NONE;
}

static MMP_ERR _component_jpe_ut(CLI_t* ptCli, char* p)
{
#if 0
    CUSTOMER_COMP_SCRIPT *cfg = &JPEUtScriptCfg[0];
    COMPONENT_CFG *Comp_Cfg = cfg->ScriptCfg;
    MMP_COMPONENT_BASE* pComp = NULL;
    MMP_UBYTE ubNum = cfg->ubNum;
    MMP_UBYTE i = 0;

    // Init and open script.
    for (i = 0 ; i < ubNum; i++) {
        Component_Update_Script(Comp_Cfg, i, cfg->ubUpdIdx[i]);
    }
    Component_Initial_Script(cfg->ScriptCfg, ubNum);
    Component_Open_Script(cfg->ScriptCfg,  ubNum);

    // Fill buffer by a 32x63 yuv422 image.
    pComp = Comp_Cfg[0].Component; // first component in this pipe.
    UartSendTrace("img buffer phy addr: 0x%08X. miu addr: 0x%08X\r\n", (MMP_ULONG)pComp->BufferInfo[0].u64BufPhyAddr, (MMP_ULONG)pComp->BufferInfo[0].u64BufMiuAddr);
    memcpy((void*)pComp->BufferInfo[0].ulBufAddr, &rect_pattern_yuv422_yuyv[0], 32*64*2);

    // Call MMP_CompCtl_EmptyBuffer explicity to start the pipe.
    MMP_CompCtl_EmptyBuffer_Frm(pComp, 0, NULL);
#endif
    return MMP_ERR_NONE;
}
