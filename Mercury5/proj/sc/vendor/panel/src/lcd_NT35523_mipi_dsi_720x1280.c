//==============================================================================
//
//  File        : lcd_NT35523_mipi_dsi_720x1280.c
//  Description :
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "Config_SDK.h"
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

#define PANEL_WIDTH                 (720)
#define PANEL_HEIGHT                (1280)

#define  RGB888_SYNC_PULSE_MODE  0
#define  RGB888_SYNC_EVENT_MODE  1
#define  RGB888_BURST_MODE  2
#define  RGB565_SYNC_PULSE_MODE  3
#define  RGB565_SYNC_EVENT_MODE  4
#define  RGB565_BURST_MODE  5
#define  RGB666_BURST_MODE  6
#define  VDO_MODE      (RGB888_SYNC_PULSE_MODE)


#define SECONDARY_DISPLAY 			(0)

#define ENABLE_LCD_LOG       		(0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN 	(1)
#else
#define ENABLE_LCD_TEST_PATTERN 	(1)
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
    LCD_BUS_WIDTH_8,	//ubBusWidth
    LCD_BGR565,			//ubBusCfg
    LCD_PHASE0,			//ubPhase
    LCD_POLARITY0,		//ubPolarity
    LCD_MCU_80SYS,		//ubMCUSystem
    0,					//usRsLeadCsCnt
    0,					//usCsLeadRwCnt
    0,					//usRwCycCnt
    LCD_RGB_ORDER_RGB,	//ubRgbOrder

    // RGB interface
    MMP_FALSE,				//bPartialDisp
    LCD_SIG_POLARITY_L,     // DCLK Polarity LCD_SIG_POLARITY_L
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
    LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

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
         //HACT ,  HPW ,  HBP  ,  HFP ,     VACT ,     VPW,    VBP,    VFP,   BLLP,   fps,    lane number,   DSI format,                        DSI Mode
        720,          1,      11,      50,          1280,       1,        22,      32,      0,       50,     4,                 DSI_FORMAT_RGB888,          DSI_SYNC_PULSE_MODE
        #elif  (VDO_MODE == RGB888_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     4,                 DSI_FORMAT_RGB888,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB666_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     4,                 DSI_FORMAT_RGB666,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB565_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     4,                 DSI_FORMAT_RGB565,          DSI_BURST_MODE
        #endif
        {0},
};




//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#define HX8394_READ_DSPY_IDENT_INFO    (0x04)
#define HX8394_READ_DSPY_STATUS        (0x09)
#define HX8394_GET_POWER_MOD           (0x0A)
#define HX8394_GET_DSPY_MOD            (0x0D)
#define HX8394_EXIT_SLEEP_MOD          (0x11)
#define HX8394_ALL_PIXEL_ON            (0x23)
#define HX8394_SET_DSPY_ON             (0x29)


unsigned char DisplayOn[]        ={   1, 0x29};
unsigned char AllPixelOn[]       ={   1, 0x23}; //turn to white display, debug used
unsigned char AllPixelOFF[]      ={  1, 0x22}; //turn to white display, debug used
unsigned char SleepOut[]         ={   1, 0x11};
unsigned char INVOFF[]           ={   1, 0x21};
unsigned char ADDRESS_MODE[]     ={   2, 0x36,
                             0x02}; // Horizontal flip
/*
    Note :
    Data ID will depends on the following rule.

        count of parameters > 1	=> Data ID = 0x39
        count of parameters = 1	=> Data ID = 0x15
        count of parameters = 0	=> Data ID = 0x05
    Structure Format :
    {DCS command, count of parameters, {parameter list}}
    {REGFLAG_DELAY, milliseconds of time, {}},
    ...
    Setting ending by predefined flag

    {REGFLAG_END_OF_TABLE, 0x00, {}}
    */
static struct LCM_setting_table lcm_initialization_setting[] =
{
    //HWRST 20
    //DELAY 120

    //ccmon

    /////////////////For NT50198B control
    {0xF0,5,{0x55,0xAA,0x52,0x08,0x01}},
    {0xC0,1,{0x01}},
    //{0xB5,2,{0x08,0x08}},
    //3line
    //{0xFF,4,{0xAA,0x55,0xA5,0x80}},
    //{0x6F,1,{0x0C}},
    //{0xF7,1,{0x10}},

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x00}},
    {0xC0,9,{0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x02}},
    {0xC8,1,{0x80}},

    {0xB1,2,{0xE8,0x21}},
    {0xB5,2,{0x05,0x00}},
    {0xBB,2,{0x93,0x93}},
    {0xBC,2,{0x0F,0x00}},
    {0xBD,4,{0x11,0x30,0x10,0x10}},

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x01}},
    {0xD7,2,{0x00,0xFF}},
    {0xB7,2,{0x00,0x4C}},
    //{0xB7,2,{0x00,0x48}},

    {0xCE,1,{0x00}},
    //{0xCA,1,{0x07}},
    {0xCA,1,{0x03}},

    {0xB3,2,{0x23,0x23}},
    {0xB4,2,{0x23,0x23}},
    {0xC3,2,{0x5A,0x5A}},
    {0xC4,2,{0x5A,0x5A}},
    {0xC2,2,{0x5A,0x5A}},
    {0xB9,2,{0x44,0x44}},
    {0xBA,2,{0x24,0x24}},
    {0xBC,2,{0x50,0x00}},
    {0xBD,2,{0x50,0x00}},
    {0xBE,2,{0x00,0x71}},
    {0xBF,2,{0x00,0x71}},//A0
    //ID CODE
    {0xC7,3,{0x82,0x12,0x08}},

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x02}},
    {0xB0,1,{0x40}},
    {0xD1,16,{0x00,0x00,0x00,0x1B,0x00,0x40,0x00,0x5B,0x00,0x71,0x00,0x97,0x00,0xB5,0x00,0xE6}},
    {0xD2,16,{0x01,0x0D,0x01,0x4B,0x01,0x7C,0x01,0xC8,0x02,0x03,0x02,0x05,0x02,0x3A,0x02,0x72}},
    {0xD3,16,{0x02,0x95,0x02,0xC5,0x02,0xE7,0x03,0x15,0x03,0x32,0x03,0x57,0x03,0x71,0x03,0x95}},
    {0xD4,4,{0x03,0xB0,0x03,0xB3}},

    /*
    {0xF0,5,{0x55,0xAA,0x52,0x08,0x02}},
    {0xB0,1,{0x42}},
    {0xD1,16,{0x00,0x00,0x00,0x64,0x00,0xC8,0x01,0x2C,0x01,0x90,0x01,0xF4,0x02,0x26,0x02,0x58}},
    {0xD2,16,{0x02,0x8A,0x02,0xBC,0x02,0xEE,0x03,0x20,0x03,0x52,0x03,0x84,0x03,0xB6,0x03,0xFF}},
    {0xD3,16,{0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF,0x03,0xFF}},
    {0xD4,4,{0x03,0xBC,0x03,0xBE}},
    */

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x03}},
    {0xB0,4,{0x00,0x00,0x00,0x00}},
    {0xB1,4,{0x00,0x00,0x00,0x00}},
    {0xB2,7,{0x00,0x00,0x0A,0x06,0x00,0xF0,0x5B}},
    {0xB3,7,{0x00,0x00,0x09,0x06,0x00,0xF0,0x5B}},
    {0xB6,10,{0xF0,0x05,0x06,0x03,0x00,0x00,0x00,0x00,0x10,0x10}},
    {0xB7,10,{0xF0,0x05,0x07,0x03,0x00,0x00,0x00,0x00,0x10,0x10}},
    {0xBC,7,{0xC5,0x03,0x00,0x08,0x00,0xF0,0x5B}},
    {0xC4,2,{0x00,0x00}},

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x05}},
    {0xB0,4,{0x33,0x04,0x00,0x01}},
    {0xB1,2,{0x40,0x00}},
    {0xB2,3,{0x03,0x02,0x22}},
    {0xB3,4,{0x83,0x23,0x42,0x9A}},


    {0xB4,4,{0xC5,0x35,0x77,0x53}},
    {0xB5,7,{0x4C,0xE5,0x31,0x33,0x33,0xA3,0x0A}},
    {0xB6,6,{0x00,0x00,0xD5,0x31,0x77,0x53}},
    {0xB9,5,{0x00,0x00,0x00,0x05,0x00}},
    {0xC0,5,{0x35,0x33,0x33,0x50,0x05}},
    {0xC6,4,{0x00,0x00,0x00,0x00}},

    {0xCE,2,{0xF0,0x1F}},

    {0xD2,5,{0x00,0x25,0x02,0x00,0x00}},
    {0xE7,2,{0xE8,0xFF}},
    {0xE8,2,{0xFF,0xFF}},
    {0xE9,1,{0x00}},
    {0xEA,1,{0xAA}},
    {0xEB,1,{0xAA}},
    {0xEC,1,{0xAA}},
    {0xEE,1,{0xAA}},

    {0xF0,5,{0x55,0xAA,0x52,0x08,0x06}},
    {0xB0,5,{0x7D,0x4A,0x7D,0x7D,0x7D}},
    {0xB1,5,{0x7D,0x7D,0x42,0x5d,0x7D}},
    {0xB2,5,{0x7D,0x63,0x61,0x7D,0x7D}},
    {0xB3,5,{0x5f,0x72,0x7d,0x7D,0x7D}},
    {0xB4,2,{0x7D,0x7D}},
    {0xB5,5,{0x7D,0x48,0x7D,0x7D,0x7D}},
    {0xB6,5,{0x7D,0x7D,0x40,0x5c,0x7D}},
    {0xB7,5,{0x7D,0x62,0x60,0x7D,0x7D}},
    {0xB8,5,{0x5e,0x72,0x7d,0x7D,0x7D}},
    {0xB9,2,{0x7D,0x7D}},

    {0xFF,4,{0xAA,0x55,0xA5,0x80}},
    {0xF3,1,{0xC0}},
    {0xFF,4,{0xAA,0x55,0xA5,0x80}},


    {0x35,1,{0x00}},

    //{0xF0,5,{0x55,0xAA,0x52,0x08,0x00}},
    //{0xEE,4,{0x87,0x78,0x02,0x40}},
    //{0xEF,4,{0x00,0x02,0x20,0xFF}},
    //{0xEF,4,{0x00,0x07,0xFF,0xFF}},


    {0x11, 1, {0x00}},
    {REGFLAG_DELAY, 120, {}},
    {0x29, 1, {0x00}},
    {REGFLAG_DELAY, 20, {}},


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

    m_PanelAttr.usDotClkRatio 	= 4;

    #if 0
    m_PanelAttr.usHBPorch		= 22;
    m_PanelAttr.usHBlanking     = 25;
    m_PanelAttr.usHSyncW		= 5;
    m_PanelAttr.usVBPorch		= 23;
    m_PanelAttr.usVBlanking 	= 40;
    m_PanelAttr.usVSyncW		= 5;
    #else
    m_PanelAttr.usHBPorch 		= 5;
    m_PanelAttr.usHBlanking 	= 30;
    m_PanelAttr.usHSyncW 		= 5;
    m_PanelAttr.usVBPorch 		= 10;
    m_PanelAttr.usVBlanking 	= 330;
    m_PanelAttr.usVSyncW 		= 40;

    #endif
    m_PanelAttr.usPRT2HdotClk 	= 2;

    m_PanelAttr.bDeltaRBG 		= MMP_FALSE; //MMP_FALSE
    m_PanelAttr.bDummyRBG 		= MMP_FALSE;

    //m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
    //m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

    // Window setting (For drawing test pattern)
    m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
    m_PanelAttr.usWinStX 		= 0;
    m_PanelAttr.usWinStY 		= 0;
    m_PanelAttr.usWinW 			= PANEL_WIDTH;
    m_PanelAttr.usWinH 			= PANEL_HEIGHT;
    m_PanelAttr.usWinBPP 		= 2;
    m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
    m_PanelAttr.ulWinAddr 		= 0x03000000;

    // CarDV
    #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    m_PanelAttr.ubRatio 		= LCD_RATIO_16_9;
    #else
    m_PanelAttr.ubRatio 		= LCD_RATIO_4_3;
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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for NT35523B_720X1280_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
#endif

    Hal_DSI_DHY_Init();
    //Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_PadOutSel(m_MIPI_DSI_LCM.u8LaneNum);
    Hal_DSI_SetLaneNum((DSI_TOTAL_LANE_NUM)m_MIPI_DSI_LCM.u8LaneNum);
    Hal_DSI_Switch_Mode(DSI_CMD_MODE);
    Hal_DSI_clk_HS_mode(1);

    lcm_init();

    Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_Config_VDO_Timing(&m_MIPI_DSI_LCM);
    Hal_DSI_Switch_Mode(m_MIPI_DSI_LCM.vdo_mode);
}


//============================================================================//
void RTNA_LCD_RGB_Test(void)
{
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
#if (USE_PWM_FOR_LCD_BACKLIGHT)
        MMPF_PWM_Initialize();
        MMPF_PWM_OutputPulse(LCD_BACKLIGHT_PWM_UNIT_PIN, bEnable, 6000,50, MMP_TRUE, MMP_FALSE, NULL, 0);
#else
        // (LCD_GPIO_BACK_LIGHT == MMP_GPIOxxx) which can not be used in preprocessor
    #if	defined(LCD_GPIO_BACK_LIGHT) && defined(LCD_GPIO_BACK_LIGHT_ACT_LEVEL)
                MMPF_PIO_Enable(LCD_GPIO_BACK_LIGHT,MMP_TRUE);
                MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
        #ifdef LCD_GPIO_BACK_LIGHT_ACT_LEVEL
                MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, ((bEnable) ? (LCD_GPIO_BACK_LIGHT_ACT_LEVEL) : !(LCD_GPIO_BACK_LIGHT_ACT_LEVEL)), MMP_TRUE);
        #else
                MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, bEnable, MMP_TRUE);
        #endif
    #endif
        RTNA_DBG_Str(0, "### RTNA_LCD_Backlight \r\n");
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
        .name			= "NT35523B",
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
