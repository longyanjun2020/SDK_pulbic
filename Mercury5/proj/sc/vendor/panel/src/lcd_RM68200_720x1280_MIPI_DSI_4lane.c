//==============================================================================
//
//  File        : lcd_OTA7001A_800x480.c
//  Description : 800x480 Sync or DE mode RGB LCD Panel Control Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================


#include "lcd_common.h"
#include "hal_mipi_dsi.h"
#include "lcm_drv.h"
#include "sys_sys.h"
#include "halPnl.h"

typedef unsigned char u8;
typedef int i32;
typedef unsigned int u32;
#define NULL 0


//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)        (lcm_util.set_reset_pin((v)))

#define PANEL_WIDTH                 (720)//(800)//pm16
#define PANEL_HEIGHT                (1280)//(480)

#define  RGB888_SYNC_PULSE_MODE  0
#define  RGB888_SYNC_EVENT_MODE  1
#define  RGB888_BURST_MODE  2
#define  RGB565_SYNC_PULSE_MODE  3
#define  RGB565_SYNC_EVENT_MODE  4
#define  RGB565_BURST_MODE  5
#define  RGB666_BURST_MODE  6
#define  VDO_MODE      (RGB888_SYNC_PULSE_MODE)


#define SECONDARY_DISPLAY           (0)

#define HX8394_TST_MODE             (0)

#define ENABLE_LCD_LOG              (0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN     (1)
#else
#define ENABLE_LCD_TEST_PATTERN     (1)
#endif

#if (ENABLE_LCD_LOG)
#define LCD_DBG_LEVEL               (0)
#else
#define LCD_DBG_LEVEL               (3)
#endif



#define Delay_ms(n) SYS_UDELAY(n*1000)

#define LCD_YSIZE_TFT  (720)
#define LCD_XSIZE_TFT  (1280)



static MMPF_PANEL_ATTR m_PanelAttr =
{
    // Panel basic setting
    PANEL_WIDTH, PANEL_HEIGHT,
    LCD_TYPE_MIPIDSI,
    LCD_PRM_CONTROLER,
    0,

    // CarDV
#if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    LCD_RATIO_16_9,
#else
    LCD_RATIO_4_3,
#endif

    // Panel initial sequence
    NULL,

    // Index/Cmd sequence
    NULL,

    // MCU interface
    LCD_BUS_WIDTH_8,    //ubBusWidth
    LCD_BGR565,            //ubBusCfg
    LCD_PHASE0,            //ubPhase
    LCD_POLARITY0,        //ubPolarity
    LCD_MCU_80SYS,        //ubMCUSystem
    0,                    //usRsLeadCsCnt
    0,                    //usCsLeadRwCnt
    0,                    //usRwCycCnt
    LCD_RGB_ORDER_RGB,    //ubRgbOrder

    // RGB interface
    MMP_FALSE,                //bPartialDisp
    LCD_SIG_POLARITY_L,     // DCLK Polarity LCD_SIG_POLARITY_L
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
    LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,    //ulClkSelect

    {0}
};

static LCM_PARAMS  m_MIPI_DSI_LCM=
{
        0x05, // HS_TRAIL
        0x03, // HS_PRPR
        0x05, // HS_ZERO
        0x0A,// CLK_HS_PRPR
        0xE, // CLK_HS_EXIT
        0x03, // CLK_TRAIL
        0x0b, // CLK_ZERO
        0x0A,// CLK_HS_POST
        0x05, // DA_HS_EXIT
        0x00,// CONT_DET
        0x10, // LPX
        0x1a,// TA_GET
        0x18,// TA_SURE
        0x32,// TA_GO
        0,
        0,
        0,
        0,
        #if  (VDO_MODE == RGB888_SYNC_PULSE_MODE)
         //HACT ,               HPW ,  HBP  ,  HFP ,     VACT ,     VPW,    VBP,    VFP,   BLLP,   fps,    lane number,   DSI format,                        DSI Mode
        PANEL_WIDTH,          2,     40,      60,          PANEL_HEIGHT,       4,        16,       16,       0,       60,     4,                 DSI_FORMAT_RGB888,          DSI_SYNC_PULSE_MODE,
        #endif
        .rgbOrder = DSI_TOP_BGR_ORDER,
        .u8ClkExtSkew =5,       /// clock skew setting, range 1~15,  0: use default setting
        .bClkMode=0,            /// 0: continuous-clock,
                                /// 1:non-continuous clock (HS enter LP period when VBlanking and HBlank)
        .bNonContClkAutoMode=1, /// 0:auto calculation HSTX LP period when non-continuous clock is on,
                                /// 1: manually config HSTX LP period
        .u16HSLPeriod=0,        /// range:0~2^14, take effect when bClkMode=1 and bNonContClkAutoMode=1
};




//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

/*
    Note :
    Data ID will depends on the following rule.

        count of parameters > 1    => Data ID = 0x39
        count of parameters = 1    => Data ID = 0x15
        count of parameters = 0    => Data ID = 0x05
    Structure Format :
    {DCS command, count of parameters, {parameter list}}
    {REGFLAG_DELAY, milliseconds of time, {}},
    ...
    Setting ending by predefined flag

    {REGFLAG_END_OF_TABLE, 0x00, {}}
    */
static struct LCM_setting_table lcm_initialization_setting[] = {
        {0xFE, 1, {0x01}},
        {0x27, 1, {0x0A}},
        {0x29, 1, {0x0A}},
        {0x2B, 1, {0xE5}},
        {0x24, 1, {0xC0}},
        {0x25, 1, {0x53}},
        {0x26, 1, {0x00}},
        {0x16, 1, {0x52}}, //wrong
        {0x2F, 1, {0x54}},
        {0x34, 1, {0x57}},
        {0x1B, 1, {0x00}},
        {0x12, 1, {0x0A}},
        {0x1A, 1, {0x06}},
        {0x46, 1, {0x4D}},
        {0x52, 1, {0x90}},
        {0x53, 1, {0x00}},
        {0x54, 1, {0x90}},
        {0x55, 1, {0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x03}},
        {0x00, 1, {0x05}},
        {0x01, 1, {0x16}},
        {0x02, 1, {0x09}},
        {0x03, 1, {0x0D}},
        {0x04, 1, {0x00}},
        {0x05, 1, {0x00}},
        {0x06, 1, {0x50}},
        {0x07, 1, {0x05}},
        {0x08, 1, {0x16}},
        {0x09, 1, {0x0B}},
        {0x0A, 1, {0x0F}},
        {0x0B, 1, {0x00}},
        {0x0C, 1, {0x00}},
        {0x0D, 1, {0x50}},
        {0x0E, 1, {0x03}},
        {0x0F, 1, {0x04}},
        {0x10, 1, {0x05}},
        {0x11, 1, {0x06}},
        {0x12, 1, {0x00}},
        {0x13, 1, {0x54}},
        {0x14, 1, {0x00}},
        {0x15, 1, {0xC5}},
        {0x16, 1, {0x08}},
        {0x17, 1, {0x07}},
        {0x18, 1, {0x08}},
        {0x19, 1, {0x09}},
        {0x1A, 1, {0x0A}},
        {0x1B, 1, {0x00}},
        {0x1C, 1, {0x54}},
        {0x1D, 1, {0x00}},
        {0x1E, 1, {0x85}},
        {0x1F, 1, {0x08}},
        {0x20, 1, {0x00}},
        {0x21, 1, {0x00}},
        {0x22, 1, {0x03}},
        {0x23, 1, {0x1F}},
        {0x24, 1, {0x00}},
        {0x25, 1, {0x28}},
        {0x26, 1, {0x00}},
        {0x27, 1, {0x1F}},
        {0x28, 1, {0x00}},
        {0x29, 1, {0x28}},
        {0x2A, 1, {0x00}},
        {0x2B, 1, {0x00}},
        {0x2D, 1, {0x00}},
        {0x2F, 1, {0x00}},
        {0x30, 1, {0x00}},
        {0x31, 1, {0x00}},
        {0x32, 1, {0x00}},
        {0x33, 1, {0x00}},
        {0x34, 1, {0x00}},
        {0x35, 1, {0x00}},
        {0x36, 1, {0x00}},
        {0x37, 1, {0x00}},
        {0x38, 1, {0x00}},
        {0x39, 1, {0x00}},
        {0x3A, 1, {0x00}},
        {0x3B, 1, {0x00}},
        {0x3D, 1, {0x00}},
        {0x3F, 1, {0x00}},
        {0x40, 1, {0x00}},
        {0x3F, 1, {0x00}},
        {0x41, 1, {0x00}},
        {0x42, 1, {0x00}},
        {0x43, 1, {0x00}},
        {0x44, 1, {0x00}},
        {0x45, 1, {0x00}},
        {0x46, 1, {0x00}},
        {0x47, 1, {0x00}},
        {0x48, 1, {0x00}},
        {0x49, 1, {0x00}},
        {0x4A, 1, {0x00}},
        {0x4B, 1, {0x00}},
        {0x4C, 1, {0x00}},
        {0x4D, 1, {0x00}},
        {0x4E, 1, {0x00}},
        {0x4F, 1, {0x00}},
        {0x50, 1, {0x00}},
        {0x51, 1, {0x00}},
        {0x52, 1, {0x00}},
        {0x53, 1, {0x00}},
        {0x54, 1, {0x00}},
        {0x55, 1, {0x00}},
        {0x56, 1, {0x00}},
        {0x58, 1, {0x00}},
        {0x59, 1, {0x00}},
        {0x5A, 1, {0x00}},
        {0x5B, 1, {0x00}},
        {0x5C, 1, {0x00}},
        {0x5D, 1, {0x00}},
        {0x5E, 1, {0x00}},
        {0x5F, 1, {0x00}},
        {0x60, 1, {0x00}},
        {0x61, 1, {0x00}},
        {0x62, 1, {0x00}},
        {0x63, 1, {0x00}},
        {0x64, 1, {0x00}},
        {0x65, 1, {0x00}},
        {0x66, 1, {0x00}},
        {0x67, 1, {0x00}},
        {0x68, 1, {0x00}},
        {0x69, 1, {0x00}},
        {0x6A, 1, {0x00}},
        {0x6B, 1, {0x00}},
        {0x6C, 1, {0x00}},
        {0x6D, 1, {0x00}},
        {0x6E, 1, {0x00}},
        {0x6F, 1, {0x00}},
        {0x70, 1, {0x00}},
        {0x71, 1, {0x00}},
        {0x72, 1, {0x00}},
        {0x73, 1, {0x00}},
        {0x74, 1, {0x04}},
        {0x75, 1, {0x04}},
        {0x76, 1, {0x04}},
        {0x77, 1, {0x04}},
        {0x78, 1, {0x00}},
        {0x79, 1, {0x00}},
        {0x7A, 1, {0x00}},
        {0x7B, 1, {0x00}},
        {0x7C, 1, {0x00}},
        {0x7D, 1, {0x00}},
        {0x7E, 1, {0x86}},
        {0x7F, 1, {0x02}},
        {0x80, 1, {0x0E}},
        {0x81, 1, {0x0C}},
        {0x82, 1, {0x0A}},
        {0x83, 1, {0x08}},
        {0x84, 1, {0x3F}},
        {0x85, 1, {0x3F}},
        {0x86, 1, {0x3F}},
        {0x87, 1, {0x3F}},
        {0x88, 1, {0x3F}},
        {0x89, 1, {0x3F}},
        {0x8A, 1, {0x3F}},
        {0x8B, 1, {0x3F}},
        {0x8C, 1, {0x3F}},
        {0x8D, 1, {0x3F}},
        {0x8E, 1, {0x3F}},
        {0x8F, 1, {0x3F}},
        {0x90, 1, {0x00}},
        {0x91, 1, {0x04}},
        {0x92, 1, {0x3F}},
        {0x93, 1, {0x3F}},
        {0x94, 1, {0x3F}},
        {0x95, 1, {0x3F}},
        {0x96, 1, {0x05}},
        {0x97, 1, {0x01}},
        {0x98, 1, {0x3F}},
        {0x99, 1, {0x3F}},
        {0x9A, 1, {0x3F}},
        {0x9B, 1, {0x3F}},
        {0x9C, 1, {0x3F}},
        {0x9D, 1, {0x3F}},
        {0x9E, 1, {0x3F}},
        {0x9F, 1, {0x3F}},
        {0xA0, 1, {0x3F}},
        {0xA2, 1, {0x3F}},
        {0xA3, 1, {0x3F}},
        {0xA4, 1, {0x3F}},
        {0xA5, 1, {0x09}},
        {0xA6, 1, {0x0B}},
        {0xA7, 1, {0x0D}},
        {0xA9, 1, {0x0F}},
        {REGFLAG_DELAY, 10, {}},
        {0xAA, 1, {0x03}}, // wrong
        {REGFLAG_DELAY, 10, {}},
        {0xAB, 1, {0x07}}, //wrong
        {REGFLAG_DELAY, 10, {}},
        {0xAC, 1, {0x01}},
        {0xAD, 1, {0x05}},
        {0xAE, 1, {0x0D}},
        {0xAF, 1, {0x0F}},
        {0xB0, 1, {0x09}},
        {0xB1, 1, {0x0B}},
        {0xB2, 1, {0x3F}},
        {0xB3, 1, {0x3F}},
        {0xB4, 1, {0x3F}},
        {0xB5, 1, {0x3F}},
        {0xB6, 1, {0x3F}},
        {0xB7, 1, {0x3F}},
        {0xB8, 1, {0x3F}},
        {0xB9, 1, {0x3F}},
        {0xBA, 1, {0x3F}},
        {0xBB, 1, {0x3F}},
        {0xBC, 1, {0x3F}},
        {0xBD, 1, {0x3F}},
        {0xBE, 1, {0x07}},
        {0xBF, 1, {0x03}},
        {0xC0, 1, {0x3F}},
        {0xC1, 1, {0x3F}},
        {0xC2, 1, {0x3F}},
        {0xC3, 1, {0x3F}},
        {0xC4, 1, {0x02}},
        {0xC5, 1, {0x06}},
        {0xC6, 1, {0x3F}},
        {0xC7, 1, {0x3F}},
        {0xC8, 1, {0x3F}},
        {0xC9, 1, {0x3F}},
        {0xCA, 1, {0x3F}},
        {0xCB, 1, {0x3F}},
        {0xCC, 1, {0x3F}},
        {0xCD, 1, {0x3F}},
        {0xCE, 1, {0x3F}},
        {0xCF, 1, {0x3F}},
        {0xD0, 1, {0x3F}},
        {0xD1, 1, {0x3F}},
        {0xD2, 1, {0x0A}},
        {0xD3, 1, {0x08}},
        {0xD4, 1, {0x0E}},
        {0xD5, 1, {0x0C}},
        {0xD6, 1, {0x04}},
        {0xD7, 1, {0x00}},
        {0xDC, 1, {0x02}},
        {0xDE, 1, {0x10}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x04}},
        {0x60, 1, {0x00}},
        {0x61, 1, {0x0C}},
        {0x62, 1, {0x14}},
        {0x63, 1, {0x0F}},
        {0x64, 1, {0x08}},
        {0x65, 1, {0x15}},
        {0x66, 1, {0x0F}},
        {0x67, 1, {0x0B}},
        {0x68, 1, {0x17}},
        {0x69, 1, {0x0D}},
        {0x6A, 1, {0x10}},
        {0x6B, 1, {0x09}},
        {0x6C, 1, {0x0F}},
        {0x6D, 1, {0x11}},
        {0x6E, 1, {0x0B}},
        {0x6F, 1, {0x00}},
        {0x70, 1, {0x00}},
        {0x71, 1, {0x0C}},
        {0x72, 1, {0x14}},
        {0x73, 1, {0x0F}},
        {0x74, 1, {0x08}},
        {0x75, 1, {0x15}},
        {0x76, 1, {0x0F}},
        {0x77, 1, {0x0B}},
        {0x78, 1, {0x17}},
        {0x79, 1, {0x0D}},
        {0x7A, 1, {0x10}},
        {0x7B, 1, {0x09}},
        {0x7C, 1, {0x0F}},
        {0x7D, 1, {0x11}},
        {0x7E, 1, {0x0B}},
        {0x7F, 1, {0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x0E}},
        {0x01, 1, {0x75}},
        {0x49, 1, {0x56}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x00}},
        {0x58, 1, {0xA9}},
        {0x11, 0,{0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0x29, 0,{0x00}},
        {REGFLAG_DELAY, 200, {}},
         {REGFLAG_END_OF_TABLE, 0x00, {}}
} ;

static struct LCM_setting_table lcm_test_pattern_setting[] = {
        {0xFE, 1, {0x01}},
        {0x27, 1, {0x0A}},
        {0x29, 1, {0x0A}},
        {0x2B, 1, {0xE5}},
        {0x24, 1, {0xC0}},
        {0x25, 1, {0x53}},
        {0x26, 1, {0x00}},
        {0x16, 1, {0x52}}, //wrong
        {0x2F, 1, {0x54}},
        {0x34, 1, {0x57}},
        {0x1B, 1, {0x00}},
        {0x12, 1, {0x0A}},
        {0x1A, 1, {0x06}},
        {0x46, 1, {0x4D}},
        {0x52, 1, {0x90}},
        {0x53, 1, {0x00}},
        {0x54, 1, {0x90}},
        {0x55, 1, {0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x03}},
        {0x00, 1, {0x05}},
        {0x01, 1, {0x16}},
        {0x02, 1, {0x09}},
        {0x03, 1, {0x0D}},
        {0x04, 1, {0x00}},
        {0x05, 1, {0x00}},
        {0x06, 1, {0x50}},
        {0x07, 1, {0x05}},
        {0x08, 1, {0x16}},
        {0x09, 1, {0x0B}},
        {0x0A, 1, {0x0F}},
        {0x0B, 1, {0x00}},
        {0x0C, 1, {0x00}},
        {0x0D, 1, {0x50}},
        {0x0E, 1, {0x03}},
        {0x0F, 1, {0x04}},
        {0x10, 1, {0x05}},
        {0x11, 1, {0x06}},
        {0x12, 1, {0x00}},
        {0x13, 1, {0x54}},
        {0x14, 1, {0x00}},
        {0x15, 1, {0xC5}},
        {0x16, 1, {0x08}},
        {0x17, 1, {0x07}},
        {0x18, 1, {0x08}},
        {0x19, 1, {0x09}},
        {0x1A, 1, {0x0A}},
        {0x1B, 1, {0x00}},
        {0x1C, 1, {0x54}},
        {0x1D, 1, {0x00}},
        {0x1E, 1, {0x85}},
        {0x1F, 1, {0x08}},
        {0x20, 1, {0x00}},
        {0x21, 1, {0x00}},
        {0x22, 1, {0x03}},
        {0x23, 1, {0x1F}},
        {0x24, 1, {0x00}},
        {0x25, 1, {0x28}},
        {0x26, 1, {0x00}},
        {0x27, 1, {0x1F}},
        {0x28, 1, {0x00}},
        {0x29, 1, {0x28}},
        {0x2A, 1, {0x00}},
        {0x2B, 1, {0x00}},
        {0x2D, 1, {0x00}},
        {0x2F, 1, {0x00}},
        {0x30, 1, {0x00}},
        {0x31, 1, {0x00}},
        {0x32, 1, {0x00}},
        {0x33, 1, {0x00}},
        {0x34, 1, {0x00}},
        {0x35, 1, {0x00}},
        {0x36, 1, {0x00}},
        {0x37, 1, {0x00}},
        {0x38, 1, {0x00}},
        {0x39, 1, {0x00}},
        {0x3A, 1, {0x00}},
        {0x3B, 1, {0x00}},
        {0x3D, 1, {0x00}},
        {0x3F, 1, {0x00}},
        {0x40, 1, {0x00}},
        {0x3F, 1, {0x00}},
        {0x41, 1, {0x00}},
        {0x42, 1, {0x00}},
        {0x43, 1, {0x00}},
        {0x44, 1, {0x00}},
        {0x45, 1, {0x00}},
        {0x46, 1, {0x00}},
        {0x47, 1, {0x00}},
        {0x48, 1, {0x00}},
        {0x49, 1, {0x00}},
        {0x4A, 1, {0x00}},
        {0x4B, 1, {0x00}},
        {0x4C, 1, {0x00}},
        {0x4D, 1, {0x00}},
        {0x4E, 1, {0x00}},
        {0x4F, 1, {0x00}},
        {0x50, 1, {0x00}},
        {0x51, 1, {0x00}},
        {0x52, 1, {0x00}},
        {0x53, 1, {0x00}},
        {0x54, 1, {0x00}},
        {0x55, 1, {0x00}},
        {0x56, 1, {0x00}},
        {0x58, 1, {0x00}},
        {0x59, 1, {0x00}},
        {0x5A, 1, {0x00}},
        {0x5B, 1, {0x00}},
        {0x5C, 1, {0x00}},
        {0x5D, 1, {0x00}},
        {0x5E, 1, {0x00}},
        {0x5F, 1, {0x00}},
        {0x60, 1, {0x00}},
        {0x61, 1, {0x00}},
        {0x62, 1, {0x00}},
        {0x63, 1, {0x00}},
        {0x64, 1, {0x00}},
        {0x65, 1, {0x00}},
        {0x66, 1, {0x00}},
        {0x67, 1, {0x00}},
        {0x68, 1, {0x00}},
        {0x69, 1, {0x00}},
        {0x6A, 1, {0x00}},
        {0x6B, 1, {0x00}},
        {0x6C, 1, {0x00}},
        {0x6D, 1, {0x00}},
        {0x6E, 1, {0x00}},
        {0x6F, 1, {0x00}},
        {0x70, 1, {0x00}},
        {0x71, 1, {0x00}},
        {0x72, 1, {0x00}},
        {0x73, 1, {0x00}},
        {0x74, 1, {0x04}},
        {0x75, 1, {0x04}},
        {0x76, 1, {0x04}},
        {0x77, 1, {0x04}},
        {0x78, 1, {0x00}},
        {0x79, 1, {0x00}},
        {0x7A, 1, {0x00}},
        {0x7B, 1, {0x00}},
        {0x7C, 1, {0x00}},
        {0x7D, 1, {0x00}},
        {0x7E, 1, {0x86}},
        {0x7F, 1, {0x02}},
        {0x80, 1, {0x0E}},
        {0x81, 1, {0x0C}},
        {0x82, 1, {0x0A}},
        {0x83, 1, {0x08}},
        {0x84, 1, {0x3F}},
        {0x85, 1, {0x3F}},
        {0x86, 1, {0x3F}},
        {0x87, 1, {0x3F}},
        {0x88, 1, {0x3F}},
        {0x89, 1, {0x3F}},
        {0x8A, 1, {0x3F}},
        {0x8B, 1, {0x3F}},
        {0x8C, 1, {0x3F}},
        {0x8D, 1, {0x3F}},
        {0x8E, 1, {0x3F}},
        {0x8F, 1, {0x3F}},
        {0x90, 1, {0x00}},
        {0x91, 1, {0x04}},
        {0x92, 1, {0x3F}},
        {0x93, 1, {0x3F}},
        {0x94, 1, {0x3F}},
        {0x95, 1, {0x3F}},
        {0x96, 1, {0x05}},
        {0x97, 1, {0x01}},
        {0x98, 1, {0x3F}},
        {0x99, 1, {0x3F}},
        {0x9A, 1, {0x3F}},
        {0x9B, 1, {0x3F}},
        {0x9C, 1, {0x3F}},
        {0x9D, 1, {0x3F}},
        {0x9E, 1, {0x3F}},
        {0x9F, 1, {0x3F}},
        {0xA0, 1, {0x3F}},
        {0xA2, 1, {0x3F}},
        {0xA3, 1, {0x3F}},
        {0xA4, 1, {0x3F}},
        {0xA5, 1, {0x09}},
        {0xA6, 1, {0x0B}},
        {0xA7, 1, {0x0D}},
        {0xA9, 1, {0x0F}},
        {REGFLAG_DELAY, 10, {}},
        {0xAA, 1, {0x03}}, // wrong
        {REGFLAG_DELAY, 10, {}},
        {0xAB, 1, {0x07}}, //wrong
        {REGFLAG_DELAY, 10, {}},
        {0xAC, 1, {0x01}},
        {0xAD, 1, {0x05}},
        {0xAE, 1, {0x0D}},
        {0xAF, 1, {0x0F}},
        {0xB0, 1, {0x09}},
        {0xB1, 1, {0x0B}},
        {0xB2, 1, {0x3F}},
        {0xB3, 1, {0x3F}},
        {0xB4, 1, {0x3F}},
        {0xB5, 1, {0x3F}},
        {0xB6, 1, {0x3F}},
        {0xB7, 1, {0x3F}},
        {0xB8, 1, {0x3F}},
        {0xB9, 1, {0x3F}},
        {0xBA, 1, {0x3F}},
        {0xBB, 1, {0x3F}},
        {0xBC, 1, {0x3F}},
        {0xBD, 1, {0x3F}},
        {0xBE, 1, {0x07}},
        {0xBF, 1, {0x03}},
        {0xC0, 1, {0x3F}},
        {0xC1, 1, {0x3F}},
        {0xC2, 1, {0x3F}},
        {0xC3, 1, {0x3F}},
        {0xC4, 1, {0x02}},
        {0xC5, 1, {0x06}},
        {0xC6, 1, {0x3F}},
        {0xC7, 1, {0x3F}},
        {0xC8, 1, {0x3F}},
        {0xC9, 1, {0x3F}},
        {0xCA, 1, {0x3F}},
        {0xCB, 1, {0x3F}},
        {0xCC, 1, {0x3F}},
        {0xCD, 1, {0x3F}},
        {0xCE, 1, {0x3F}},
        {0xCF, 1, {0x3F}},
        {0xD0, 1, {0x3F}},
        {0xD1, 1, {0x3F}},
        {0xD2, 1, {0x0A}},
        {0xD3, 1, {0x08}},
        {0xD4, 1, {0x0E}},
        {0xD5, 1, {0x0C}},
        {0xD6, 1, {0x04}},
        {0xD7, 1, {0x00}},
        {0xDC, 1, {0x02}},
        {0xDE, 1, {0x10}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x04}},
        {0x60, 1, {0x00}},
        {0x61, 1, {0x0C}},
        {0x62, 1, {0x14}},
        {0x63, 1, {0x0F}},
        {0x64, 1, {0x08}},
        {0x65, 1, {0x15}},
        {0x66, 1, {0x0F}},
        {0x67, 1, {0x0B}},
        {0x68, 1, {0x17}},
        {0x69, 1, {0x0D}},
        {0x6A, 1, {0x10}},
        {0x6B, 1, {0x09}},
        {0x6C, 1, {0x0F}},
        {0x6D, 1, {0x11}},
        {0x6E, 1, {0x0B}},
        {0x6F, 1, {0x00}},
        {0x70, 1, {0x00}},
        {0x71, 1, {0x0C}},
        {0x72, 1, {0x14}},
        {0x73, 1, {0x0F}},
        {0x74, 1, {0x08}},
        {0x75, 1, {0x15}},
        {0x76, 1, {0x0F}},
        {0x77, 1, {0x0B}},
        {0x78, 1, {0x17}},
        {0x79, 1, {0x0D}},
        {0x7A, 1, {0x10}},
        {0x7B, 1, {0x09}},
        {0x7C, 1, {0x0F}},
        {0x7D, 1, {0x11}},
        {0x7E, 1, {0x0B}},
        {0x7F, 1, {0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x0E}},
        {0x01, 1, {0x75}},
        {0x49, 1, {0x56}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x00}},
        {0x58, 1, {0xA9}},
        {0x11, 0,{0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0x29, 0,{0x00}},
        {REGFLAG_DELAY, 200, {}},
        {0xFE, 1, {0x0E}},
        {0x35, 1, {0x80}},
        {REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;
    for(i = 0; i < count; i++) {
        unsigned cmd;
        cmd = table[i].cmd;
        switch (cmd) {
            case REGFLAG_DELAY :
                Delay_ms(table[i].count);
                break;
            case REGFLAG_END_OF_TABLE :
                break;
            default:
                if((table[i].count+1) <=2) {
                    Hal_DSI_WriteShortPacket((table[i].count+1), cmd, table[i].para_list);
                    //Hal_DSI_ReadLongPacket(table[i].count, cmd);
                }
                else {
                    Hal_DSI_WriteLongPacket((table[i].count+1), cmd,  table[i].para_list);
                    //if(table[i].count <=10)
                    //Hal_DSI_ReadLongPacket(table[i].count, cmd);
                }
           }
    }
}

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

  void lcm_init(void)
{
   push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_get_params(LCM_PARAMS *params)
{
    //TBD
}
void SendDSIPacket(unsigned char *paraList)
{
    unsigned char count=paraList[0];
    unsigned char *paraList1=&paraList[1];

    #if 0
    unsigned char *paraList2=&paraList[2];
    int i;
    UartSendTrace("{0x%x,   %d,     ", paraList[1], paraList[0]-1);
     UartSendTrace("{");
    for(i=0; i< (paraList[0]-1);i++) {
         UartSendTrace("0x%x", *paraList2);
         paraList2 ++;
         if(i!=(paraList[0]-2))
             UartSendTrace(",   ");
    }
     UartSendTrace("}},\n");
     #endif

    if(count <=2)
        Hal_DSI_WriteShortPacket(count, paraList1[0], &paraList1[1]);
    else
        Hal_DSI_WriteLongPacket(count, paraList1[0], &paraList1[1] );

}

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
    RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - OTA7001A 480x854\r\n");


    m_PanelAttr.usDotClkRatio     = 4;

    #if 0
    m_PanelAttr.usHBPorch        = 22;
    m_PanelAttr.usHBlanking     = 25;
    m_PanelAttr.usHSyncW        = 5;
    m_PanelAttr.usVBPorch        = 23;
    m_PanelAttr.usVBlanking     = 40;
    m_PanelAttr.usVSyncW        = 5;
    #else
    m_PanelAttr.usHBPorch         = 5;
    m_PanelAttr.usHBlanking     = 30;
    m_PanelAttr.usHSyncW         = 5;
    m_PanelAttr.usVBPorch         = 10;
    m_PanelAttr.usVBlanking     = 330;
    m_PanelAttr.usVSyncW         = 40;

    #endif
    m_PanelAttr.usPRT2HdotClk     = 2;

    m_PanelAttr.bDeltaRBG         = MMP_FALSE; //MMP_FALSE
    m_PanelAttr.bDummyRBG         = MMP_FALSE;

    //m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
    //m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

    // Window setting (For drawing test pattern)
    m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_PIP;
    m_PanelAttr.usWinStX         = 0;
    m_PanelAttr.usWinStY         = 0;
    m_PanelAttr.usWinW             = PANEL_WIDTH;
    m_PanelAttr.usWinH             = PANEL_HEIGHT;
    m_PanelAttr.usWinBPP         = 2;
    m_PanelAttr.usWinFmt         = LCD_WIN_FMT_16BPP;
    m_PanelAttr.ulWinAddr         = 0x03000000;

    // CarDV
    #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    m_PanelAttr.ubRatio         = LCD_RATIO_16_9;
    #else
    m_PanelAttr.ubRatio         = LCD_RATIO_4_3;
    #endif

    MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)
    // TBD
#endif
}


void RTNA_LCD_Init(void)
{
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for RM68200 800X1280_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
#endif

    Hal_DSI_DHY_Init();
    Hal_DSI_PadOutSel(m_MIPI_DSI_LCM.u8LaneNum);

    Hal_DSI_SetLaneNum((DSI_TOTAL_LANE_NUM)m_MIPI_DSI_LCM.u8LaneNum);
    Hal_DSI_Switch_Mode(DSI_CMD_MODE);
    Hal_DSI_clk_HS_mode(1);
    Hal_DSI_Set_RGB_Order(m_MIPI_DSI_LCM.rgbOrder);
    Hal_DSI_LP_LPLL();

    #if 0
    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE0_SEL, 4);
    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE3_SEL, 0);
    Hal_DSI_DHY_Pol(DSI_DATA_LANE1_SEL, 1);
    Hal_DSI_DHY_Pol(DSI_DATA_LANE3_SEL, 1);
    #endif
    lcm_init();


    Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_Config_VDO_Timing(&m_MIPI_DSI_LCM);
    Hal_DSI_Switch_Mode(m_MIPI_DSI_LCM.vdo_mode);

}


//============================================================================//
void RTNA_LCD_RGB_Test(void)
{
#if 0 //(ENABLE_LCD_TEST_PATTERN)
    #if defined(LCD_GPIO_BACK_LIGHT)
        /* Force turn-on LCD backlight */
        if (LCD_GPIO_BACK_LIGHT != MMP_GPIO_MAX)
        {
            MMPF_PIO_PadConfig(LCD_GPIO_BACK_LIGHT, PAD_OUT_DRIVING(0), MMP_TRUE);
            MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
            RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to output mode\r\n");

            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
            Delayms(20);
            RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to low\r\n");

            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
            Delayms(20);
            RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to high\r\n");
        }
    #endif

    MMPF_LCD_DrawTestPattern(&m_PanelAttr);
    Delayms(5000);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
    // TBD
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
    // TBD
}

void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value)
{
    // TBD
}

void RTNA_LCD_AdjustBrightness(MMP_UBYTE level)
{
    // TBD
}

void RTNA_LCD_AdjustBrightness_R(MMP_UBYTE level)
{
    // TBD
}

void RTNA_LCD_AdjustBrightness_B(MMP_UBYTE level)
{
    // TBD
}

void RTNA_LCD_AdjustContrast(MMP_UBYTE level)
{
    // TBD
}

void RTNA_LCD_AdjustContrast_R(MMP_BYTE level)
{
    // TBD
}

void RTNA_LCD_AdjustContrast_B(MMP_BYTE level)
{
    // TBD
}

/*
 * Set Panel Properties
 * Width, Height, Color Depth, Display Type
 */
MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void)
{
    return &m_PanelAttr;
}

/**
    @brief
    @return NONE
*/
void RTNA_LCD_Backlight(MMP_BOOL bEnable)
{
#if 0
#if (USE_PWM_FOR_LCD_BACKLIGHT)
    MMPF_PWM_Initialize();
    MMPF_PWM_OutputPulse(LCD_BACKLIGHT_PWM_UNIT_PIN, bEnable, 6000,50, MMP_TRUE, MMP_FALSE, NULL, 0);
#else
    // (LCD_GPIO_BACK_LIGHT == MMP_GPIOxxx) which can not be used in preprocessor
    #if    defined(LCD_GPIO_BACK_LIGHT)
        if (LCD_GPIO_BACK_LIGHT != MMP_GPIO_MAX)
        {
            MMPF_PIO_PadConfig(LCD_GPIO_BACK_LIGHT, PAD_OUT_DRIVING(0), MMP_TRUE);
            MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
        #ifdef LCD_GPIO_BACK_LIGHT_ACT_LEVEL
            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, ((bEnable) ? (LCD_GPIO_BACK_LIGHT_ACT_LEVEL) : !(LCD_GPIO_BACK_LIGHT_ACT_LEVEL)), MMP_TRUE);
        #else
            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, bEnable, MMP_TRUE);
        #endif
        }
    #endif
#endif
#endif
}

/**
@brief Customer LCD initialize setting(register setting in AIT side) for MAIN LCD.
@retval MMP_TRUE for success, MMP_FALSE for fail
*/
MMP_BOOL MMPC_Display_InitMainLCD(MMP_BOOL bSoftReset)
{
    RTNA_LCD_InitMainLCD();

    return MMP_TRUE;
}

/**
@brief Customer LCD re-initialize setting for MAIN LCD.
@retval MMP_TRUE for success, MMP_FALSE for fail
*/
MMP_BOOL MMPC_Display_ReinitMainLCD(MMP_BOOL bSoftReset)
{
    return MMP_TRUE;
}


LCM_DRIVER lcm_drv =
{
    .name            = "RM68200",
    .set_util_funcs = NULL,
    .get_params     = NULL,
    .init           = lcm_init,
    .suspend        = NULL,
    .resume         = NULL,
    .update         = NULL,
};


const LCM_DRIVER* LCM_GetDriver(void)
{
    return &lcm_drv;

}
