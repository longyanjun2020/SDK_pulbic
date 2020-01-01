//==============================================================================
//
//  File        : lcd_mipi_dsi_template.c
//  Description :
//  Author      :
//  Revision    : 1.1 (2018/08/07)
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

#define  RGB888_SYNC_PULSE_MODE     0
#define  RGB888_SYNC_EVENT_MODE     1
#define  RGB888_BURST_MODE          2
#define  RGB565_SYNC_PULSE_MODE     3
#define  RGB565_SYNC_EVENT_MODE     4
#define  RGB565_BURST_MODE          5
#define  RGB666_BURST_MODE          6
#define  VDO_MODE                   (RGB888_SYNC_PULSE_MODE)


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



#define Delay_ms(n)                 SYS_UDELAY(n*1000)

#define LCD_YSIZE_TFT               (720)
#define LCD_XSIZE_TFT               (1280)



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
    LCD_BGR565,         //ubBusCfg
    LCD_PHASE0,         //ubPhase
    LCD_POLARITY0,      //ubPolarity
    LCD_MCU_80SYS,      //ubMCUSystem
    0,                  //usRsLeadCsCnt
    0,                  //usCsLeadRwCnt
    0,                  //usRwCycCnt
    LCD_RGB_ORDER_RGB,  //ubRgbOrder

    // RGB interface
    MMP_FALSE,              //bPartialDisp
    LCD_SIG_POLARITY_L,     // DCLK Polarity
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
        0x03, // LPX
        0x1a,// TA_GET
        0x16,// TA_SURE
        0x32,// TA_GO
        0,
        0,
        0,
        0,

        #if  (VDO_MODE == RGB888_SYNC_PULSE_MODE)
         //HACT ,    HPW ,  HBP  ,      HFP ,       VACT ,     VPW,     VBP,     VFP,   BLLP,       fps,    lane number,        DSI format,                 DSI Mode
        .HACT=720,    24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB888,          DSI_SYNC_PULSE_MODE
        #elif  (VDO_MODE == RGB888_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB888,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB666_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                  DSI_FORMAT_RGB666,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB565_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB565,          DSI_BURST_MODE
        #endif
        .rgbOrder = DSI_TOP_BGR_ORDER,
        .u8ClkExtSkew =4,       /// clock skew setting, range 1~15,  0: use default setting
        .bClkMode=0,            /// 0: continuous-clock,
                                /// 1:non-continuous clock (HS enter LP period when VBlanking and HBlank)
        .bNonContClkAutoMode=0, /// 0:auto calculation HSTX LP period when non-continuous clock is on,
                                /// 1: manually config HSTX LP period
        .u16HSLPeriod=0,        /// range:0~2^14, take effect when bClkMode=1 and bNonContClkAutoMode=1
};




//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================




unsigned char DisplayOn[]        ={     1, 0x29};
unsigned char AllPixelOn[]       ={     1, 0x23}; //turn to white display, debug used
unsigned char AllPixelOFF[]      ={     1, 0x22}; //turn to white display, debug used
unsigned char SleepOut[]         ={     1, 0x11};
unsigned char INVOFF[]           ={     1, 0x21};
unsigned char ADDRESS_MODE[]     ={     2, 0x36, 0x02}; // Horizontal flip
/*
    Note :
    Data ID will depends on the following rule.

    count of parameters > 1	=> Data ID = 0x39
    count of parameters = 1	=> Data ID = 0x15
    count of parameters = 0	=> Data ID = 0x05
    Structure Format :
    {DCS command, count of parameters, {parameter list}}
    {REGFLAG_DELAY, milliseconds of time, {}},
    Setting ending by predefined flag

    {REGFLAG_END_OF_TABLE, 0x00, {}}
    */
static struct LCM_setting_table lcm_initialization_setting[] = {
        {0xb9,   3,     {0xff,   0x83,   0x94}},  //ExtCmd
        {0xb1,   10,    {  0x48,   0x11,   0x71,   0x9,   0x32,   0x54,   0x71,   0x71,   0x4e,   0x43}},
        {0xba,   6,     {   0x61,   0x3,   0x68,   0x6b,   0xb2,   0xc0}},
        {0xd4,   1,     {0x2}},
        {0xb2,   11,    {   0x65,   0x80,   0x64,   0x05,   0x07,     0x2f,   0x00,   0x00,   0x00,   0x00,   0xc8}},
        {0xb4,   21,    {   0x26,   0x76,   0x26,   0x76,   0x26,     0x26,   0x05,   0x10,   0x86,   0x75,
                                  0x00,   0x3f,   0x26,   0x76,   0x26 ,    0x76,   0x26,   0x26,   0x05,   0x10,
                                  0x86}},
        {0xd3,   33,    {   0x0,   0x0,   0x4,   0x4,   0x1,   0x1,   0x10,   0x0,   0x32,   0x10,   0x0,   0x0,   0x0,   0x32,   0x15,   0x4,        //GIP0
                              0x5,   0x4,   0x32,   0x15,   0x14,   0x5,   0x14,   0x37,   0x33,   0x4,   0x4,   0x37,   0x0,   0x0,   0x47,   0x5,   0x40}},
        {0xd5,   44,    {  0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x25,   //GIP1
                                0x24,   0x27,   0x26,   0x18,   0x18,   0x11,   0x10,   0x15,   0x14,   0x13,   0x12,   0x17,   0x16,   0x1,   0x0,   0x5,
                                0x4,   0x3,   0x2,   0x7,   0x6,   0x21,   0x20,   0x23,   0x22,   0x18,   0x18,   0x18,   0x18}},
        {0xd6,   44,    {0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x22,    //GIP2
                                0x23,   0x20,   0x21,   0x18,   0x18,   0x12,   0x13,   0x16,   0x17,   0x10,   0x11,   0x14,   0x15,   0x6,   0x7,   0x2,   0x3,
                                0x4,   0x5,   0x0,   0x1,   0x26,   0x27,   0x24,   0x25,   0x18,   0x18,   0x18,   0x18}},
        {0xe0,   58,    {0x0,   0x4,   0x11,   0x1b,   0x1e,   0x22,   0x27,   0x26,   0x51,   0x60,   0x70,   0x6f,   0x7a,   0x8c,   0x94,   0x9a,
                                0xa9,   0xac,   0xa9,   0xb9,   0xc8,   0x64,   0x62,   0x67,   0x69,   0x6a,   0x7f,   0x7f,   0x7f,   0x0,   0x4,   0x11,
                                0x1b,   0x1e,   0x22,   0x27,   0x26,   0x51,   0x60,   0x70,   0x6f,   0x7a,   0x8c,   0x94,   0x9a,   0xa9,   0xac,   0xa9,
                                0xb9,   0xc8,   0x64,   0x62,   0x67,   0x69,   0x6a,   0x7f,   0x7f,   0x7f}},
        {0xcc,   1,     {0x3}},
        {0xc0,   2,     {0x1f,   0x31}},
        {0xb6,   2,     {0x43,   0x43}},
        {0xbd,   1,     {0x1}},
        {0xb1,   1,     {0x0}},
        {0xbd,   1,     {0x0}},
        {0xbf,   7,     {0x40,   0x81,   0x50,   0x0,   0x1a,   0xfc,   0x1}},
        {0x11,   0,     {}},
        {REGFLAG_DELAY, 200, {}},
        {0xb2,   12,     {0x65,   0x80,   0x64,   0x5,   0x7,   0x2f,   0x0,   0x0,   0x0,   0x0,   0xc0,   0x18}},
        {0x29,   0,     {}},  //DisplayOn
        {REGFLAG_DELAY, 200, {}},
        {REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_test_pattern_setting[] = {
        {0xb9,   3,     {0xff,   0x83,   0x94}},  //ExtCmd
        {0xb1,   10,    {  0x48,   0x11,   0x71,   0x9,   0x32,   0x54,   0x71,   0x71,   0x4e,   0x43}},
        {0xba,   6,     {   0x61,   0x3,   0x68,   0x6b,   0xb2,   0xc0}},
        {0xd4,   1,     {0x2}},
        {0xb2,   11,    {   0x65,   0x80,   0x64,   0x05,   0x07,     0x2f,   0x00,   0x00,   0x00,   0x00,   0x00}},
        {0xb4,   21,    {   0x26,   0x76,   0x26,   0x76,   0x26,     0x26,   0x05,   0x10,   0x86,   0x75,
                                  0x00,   0x3f,   0x26,   0x76,   0x26 ,    0x76,   0x26,   0x26,   0x05,   0x10,
                                  0x86}},
        {0xd3,   33,    {   0x0,   0x0,   0x4,   0x4,   0x1,   0x1,   0x10,   0x0,   0x32,   0x10,   0x0,   0x0,   0x0,   0x32,   0x15,   0x4,
                              0x5,   0x4,   0x32,   0x15,   0x14,   0x5,   0x14,   0x37,   0x33,   0x4,   0x4,   0x37,   0x0,   0x0,   0x47,   0x5,   0x40}},
        {0xd5,   44,    {  0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x25,
                                0x24,   0x27,   0x26,   0x18,   0x18,   0x11,   0x10,   0x15,   0x14,   0x13,   0x12,   0x17,   0x16,   0x1,   0x0,   0x5,
                                0x4,   0x3,   0x2,   0x7,   0x6,   0x21,   0x20,   0x23,   0x22,   0x18,   0x18,   0x18,   0x18}},
        {0xd6,   44,    {0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x18,   0x22,
                                0x23,   0x20,   0x21,   0x18,   0x18,   0x12,   0x13,   0x16,   0x17,   0x10,   0x11,   0x14,   0x15,   0x6,   0x7,   0x2,   0x3,
                                0x4,   0x5,   0x0,   0x1,   0x26,   0x27,   0x24,   0x25,   0x18,   0x18,   0x18,   0x18}},
        {0xe0,   58,    {0x0,   0x4,   0x11,   0x1b,   0x1e,   0x22,   0x27,   0x26,   0x51,   0x60,   0x70,   0x6f,   0x7a,   0x8c,   0x94,   0x9a,
                                0xa9,   0xac,   0xa9,   0xb9,   0xc8,   0x64,   0x62,   0x67,   0x69,   0x6a,   0x7f,   0x7f,   0x7f,   0x0,   0x4,   0x11,
                                0x1b,   0x1e,   0x22,   0x27,   0x26,   0x51,   0x60,   0x70,   0x6f,   0x7a,   0x8c,   0x94,   0x9a,   0xa9,   0xac,   0xa9,
                                0xb9,   0xc8,   0x64,   0x62,   0x67,   0x69,   0x6a,   0x7f,   0x7f,   0x7f}},
        {0xcc,   1,     {0x3}},
        {0xc0,   2,     {0x1f,   0x31}},
        {0xb6,   2,     {0x43,   0x43}},
        {0xbd,   1,     {0x1}},
        {0xb1,   1,     {0x0}},
        {0xbd,   1,     {0x0}},
        {0xbf,   7,     {0x40,   0x81,   0x50,   0x0,   0x1a,   0xfc,   0x1}},

        {0xb2,   11,     {0x65,   0x80,   0x64,   0x5,   0x7,   0x2f,   0x0,   0x0,   0x0,   0x0,   0xc8}},
        {0x11,   0,     {}},
        {REGFLAG_DELAY, 200, {}},
        {0x29,   0,     {}},  //DisplayOn
        {REGFLAG_DELAY, 200, {}},
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
                if((table[i].count+1) <=2)
                    Hal_DSI_WriteShortPacket((table[i].count+1), cmd, table[i].para_list);
                else
                    Hal_DSI_WriteLongPacket((table[i].count+1), cmd,  table[i].para_list);

           }
    }
}


static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}

static void lcm_init(void)
{
   push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);

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


    m_PanelAttr.usDotClkRatio   = 4;

    #if 0
    m_PanelAttr.usHBPorch       = 22;
    m_PanelAttr.usHBlanking     = 25;
    m_PanelAttr.usHSyncW        = 5;
    m_PanelAttr.usVBPorch       = 23;
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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for HX8394_720X1280_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
#endif

    Hal_DSI_DHY_Init();
    Hal_DSI_PadOutSel(m_MIPI_DSI_LCM.LANE_NUM);
    Hal_DSI_SetLaneNum((DSI_TOTAL_LANE_NUM)m_MIPI_DSI_LCM.LANE_NUM);
    Hal_DSI_Switch_Mode(DSI_CMD_MODE);
    Hal_DSI_clk_HS_mode(1);
    Hal_DSI_Set_RGB_Order(m_MIPI_DSI_LCM.rgbOrder);
    Hal_DSI_LP_LPLL();

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
    #if	defined(LCD_GPIO_BACK_LIGHT)
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
    .name	        = "HX8394",
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
