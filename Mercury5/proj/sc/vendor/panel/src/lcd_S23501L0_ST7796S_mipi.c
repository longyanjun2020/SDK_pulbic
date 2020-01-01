//==============================================================================
//
//  File        : lcd_mipi_dsi_template.c
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



//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)        (lcm_util.set_reset_pin((v)))

#define PANEL_WIDTH                 (320)//(800)//pm16
#define PANEL_HEIGHT                (480)//(480)

#define  RGB888_SYNC_PULSE_MODE       0
#define  RGB888_SYNC_EVENT_MODE         1
#define  RGB888_BURST_MODE          2
#define  RGB565_SYNC_PULSE_MODE       3
#define  RGB565_SYNC_EVENT_MODE       4
#define  RGB565_BURST_MODE          5
#define  RGB666_BURST_MODE          6
#define  VDO_MODE      (RGB888_SYNC_PULSE_MODE)

#define MIPI_PANEL_RW_SETTING_DEBUG	(1)
#define RUN_TEST_PATTERN			(0)
#define HX8394_TST_MODE				(0)
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

#define SECONDARY_DISPLAY 			(0)


typedef unsigned char u8;
typedef int i32;
typedef unsigned int u32;
#define NULL 0


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
    LCD_BUS_WIDTH_24,
    LCD_RGB888,
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
    0x00/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

    {0}
};
/*{
    unsigned char LPX;
    unsigned char HS_PRPR;
    unsigned char HS_ZERO;
    unsigned char HS_TRAIL;
} DSI_PHY_TIMCON0_REG, *PDSI_PHY_TIMCON0_REG;
*/
static LCM_PARAMS  m_MIPI_DSI_LCM=
{
#if 0
#if 1
        0x05, // HS_TRAIL       60+4UI ~ MAX
        0x03, // HS_PRPR        40+4UI ~ 85+6UI
        0x05, // HS_ZERO        105+6UI ~ MAX
        0x0A, // CLK_HS_PRPR    38ns ~ 95ns
        0x0E, // CLK_HS_EXIT    100ns ~ max
        0x03, // CLK_TRAIL      60ns ~ max
        0x0b, // CLK_ZERO       300ns -CLK_HS_PRPR
        0x0A, // CLK_HS_POST    60+52UI ~ max
        0x05, // DA_HS_EXIT     100ns ~ max
        0x00, // CONT_DET
        0x0A, // LPX            50ns ~ MAX  ===>62.5ns
        0x1a, // TA_GET         5LPX
        0x16, // TA_SURE        1LPX ~ 2LPX
        0x32, // TA_GO          4LPX
#else
        0x3a,//0x05, // HS_TRAIL       60+4UI ~ MAX
        0x06,//0x03, // HS_PRPR        40+4UI ~ 85+6UI
        0x6a,//0x05, // HS_ZERO        105+6UI ~ MAX
        0x06,//0x0A, // CLK_HS_PRPR    38ns ~ 95ns
        0x2f,//0x0E, // CLK_HS_EXIT    100ns ~ max
        0x2f,//0x03, // CLK_TRAIL      60ns ~ max
        0x2e,//0x0b, // CLK_ZERO       300ns -CLK_HS_PRPR
        0x3a,//0x0A, // CLK_HS_POST    60+52UI ~ max
        0x39,//0x05, // DA_HS_EXIT     100ns ~ max
        0x00,//0x00, // CONT_DET
        0x10,//0x0A, // LPX            50ns ~ MAX  ===>62.5ns
        0x50,//0x1a, // TA_GET         5LPX
        0x20,//0x16, // TA_SURE        1LPX ~ 2LPX
        0x40,//0x32, // TA_GO          4LPX
#endif
#else
        0x04,//0x05, // HS_TRAIL       60+4UI ~ MAX
        0x03,//0x03, // HS_PRPR        40+4UI ~ 85+6UI
        0x06,//0x05, // HS_ZERO        105+6UI ~ MAX
        0x03,//0x0A, // CLK_HS_PRPR    38ns ~ 95ns
        0x0A,//0x0E, // CLK_HS_EXIT    100ns ~ max
        0x06,//0x03, // CLK_TRAIL      60ns ~ max
        0x0F,//0x0b, // CLK_ZERO       300ns -CLK_HS_PRPR
        0x0a,//0x0A, // CLK_HS_POST    60+52UI ~ max
        0x0A,//0x05, // DA_HS_EXIT     100ns ~ max
        0x00,//0x00, // CONT_DET
        0x03,//0x0A, // LPX            50ns ~ MAX  ===>62.5ns
        0x0f,//0x1a, // TA_GET         5LPX
        0x04,//0x16, // TA_SURE        1LPX ~ 2LPX
        0x0c,//0x32, // TA_GO          4LPX
 #endif
        0,
        0,
        0,
        0,


        #if  (VDO_MODE == RGB888_SYNC_PULSE_MODE)
         //HACT ,  	  HPW ,   HBP  ,     HFP ,      VACT ,    VPW,      VBP,      VFP,    BLLP,    fps,    lane number,       DSI format,                 DSI Mode
        320,		  10,	  100,		 76,	    480, 	  4,	    48, 	  18,	  0,	   60,	   1,				  DSI_FORMAT_RGB888,		  DSI_SYNC_PULSE_MODE,
//        320,		  10,	  100,		 80,	    480, 	  4,	    25, 	  18,	  0,	   60,	   1,				  DSI_FORMAT_RGB888,		  DSI_SYNC_PULSE_MODE,
        #elif  (VDO_MODE == RGB888_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB888,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB666_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                  DSI_FORMAT_RGB666,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB565_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB565,          DSI_BURST_MODE
        #endif
        DSI_TOP_BGR_ORDER,
        8
};




//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

unsigned char DisplayOn[]        ={   1, 0x29};
unsigned char AllPixelOn[]       ={   1, 0x23}; //turn to white display, debug used
unsigned char AllPixelOFF[]      ={  1, 0x22}; //turn to white display, debug used
unsigned char SleepOut[]         ={   1, 0x11};
unsigned char INVOFF[]           ={   1, 0x21};
unsigned char ADDRESS_MODE[]     ={   2, 0x36, 0x02}; // Horizontal flip

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
#if 0
static struct LCM_setting_table lcm_initialization_setting[] = {
    //=================================================
    //	Main LDI Power ON Sequence
    //=================================================

    {REGFLAG_DELAY, 120, {}},

    {0x11,0,{}},

    {REGFLAG_DELAY, 120, {}},

    //{0x30,4,{0x00, 0x10, 0x01, 0xE0}},

    //{0x33,6,{0x00,0x00,0x02,0x00,0x00,0x00}},

    {0x36,1,{0x48}},

    //{0x37,2,{0x00, 0x10}},

    {0x3A,1,{0x77}},

    {0xF0,1,{0xC3}},

    {0xF0,1,{0x96}},

    {0xB4,1,{0x01}},

    //{0xB5,4,{0x03, 0x04, 0x00, 0x10}},
    //{0xB5,4,{0xff, 0xff, 0x00, 0xff}},

    {0xC1,1,{0x1D}},

    {0xC2,1,{0xA7}},

    {0xC5,1,{0x23}},

    {0xE8,8,{0x40,0x8A,0x00,0x00,0x29,0x19,0xA5,0x33}},

    {0xE0,14,{0xF0,0x03,0x0A,0x12,0x15,0x1D,0x42,0x44,0x50,0x28,0x16,0x15,0x20,0x21}},

    {0xE1,14,{0xF0,0x03,0x0A,0x12,0x15,0x1C,0x42,0x44,0x52,0x28,0x16,0x15,0x20,0x23}},

    {0xF0,1,{0x3C}},

    {0xF0,1,{0x69}},

    {0x29,0,{}},
    {REGFLAG_DELAY, 100, {}},

    {0x2A,4,{0x00, 0x00, 0x01, 0x3F}},
    {0x2B,4,{0x00, 0x00, 0x01, 0xDF}},

    {0x2C,0,{}},
    {REGFLAG_DELAY, 100, {}},
} ;

#else
static struct LCM_setting_table lcm_initialization_setting[] =
{
    {REGFLAG_DELAY, 120, {}},
    //*************LCDDriverInitial**********//
    {0X11,0,{0x00}},
    {REGFLAG_DELAY, 120, {}},

    {0xf0,1,{0xc3}},
    {0xf0,1,{0x96}},

    {0x36,1,{0x48}},
    {0x3A,1,{0x77}},// 77 24BIT/PIX

    {0x2A,4,{0x00,0x00,0x01,0x3F}},     //column address set
    {0x2B,4,{0x00,0x00,0x01,0xDF}},     //row address set
    {0xB4,1,{0x01}},                    //display inversion ctrl
    {0xB1,2,{0xa0,0x10}},               // 55fps                      aaaaaaaaaaaaa

    {0xb6,3,{0x80,0x02,0x3b}},

    {0xB5,4,{0x12,0x30,0x00,0x64}},     //VFP VBP 00 HBP ctrl
    {0xB7,1,{0xc6}},                    //enter mode set    xxxxxxxxxxxxxx

    {0xB9,1,{0x02}},//24bit設置，不�?4bit不需要用著寄存器

    #if 0
    {0xe8,8,{0x40,0x8A,0x00,0x00,0x25,0x19,0x3F,0x33}},     //display output ctrl adjust
    #else
    //{0xE8,8,{0x40,0x8A,0x00,0x00,0x29,0x19,0xA5,0x33}},         //ccccccccccccccccccccc
    {0xE8,8,{0x40,0x8A,0x00,0x00,0x28,0x19,0xA5,0x33}},         //ccccccccccccccccccccc
    #endif

    {0xc0,2,{0x80,0x25}},   //power ctrl1     aaaaaaaaaaaaa
    {0xb9,2,{0x02,0xc0}},   //no comment      aaaaaaaaaaaaa

#if 1
    {0xc1,1,{0x20}},    //power ctrl2
    {0xc2,1,{0xAF}},    //power ctrl3   source driving&gamma driving current
    {0xc5,1,{0x28}},    //vcom ctrl
#else
    {0xC1,1,{0x1D}},        //                  bbbbbbbbbbbbbbb
    {0xC2,1,{0xA7}},
    {0xC5,1,{0x23}},
#endif

    {0x35,1,{0x00}},    //teon                bbbbbbbbbbbbb

    {0xe0,14,{0x00,0x03,0x07,0x07,0x07,0x23,0x2b,0x33,0x46,0x1a,0x19,0x19,0x27,0x2F}},
    {0xe1,14,{0x00,0x03,0x06,0x07,0x04,0x22,0x2f,0x54,0x49,0x1b,0x17,0x15,0x25,0x2d}},

    {0xf0,1,{0x3c}},
    {0xf0,1,{0x69}},

    //{0X21,0,{0x00}},    //display inversion on        cccccccccc
    //{REGFLAG_DELAY, 120, {}},

    {0X29,0,{0x00}},
    {REGFLAG_DELAY, 100, {}},

    //{0x2C,0,{}},  //ram write         aaaaaaaaaaaa
    //{REGFLAG_DELAY, 100, {}},
    {REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif

static struct LCM_setting_table lcm_test_pattern_setting[] = {
    {0xFF	, 1 , {0x00}},
    {0xFF	, 1 , {0x05}},
    {0xEA	, 1 , {0xFF}},
    {0xEB	, 1 , {0x00}},
    {0xEC	, 1 , {0x11}},

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

            #if MIPI_PANEL_RW_SETTING_DEBUG//send to panel by mipi
            {
                unsigned char *paraList2=&table[i].para_list;
                int k;
                UartSendTrace("\r\n{0x%x , %d , ", cmd, table[i].count);
                UartSendTrace("{");
                for(k=0; k< table[i].count;k++) {
                    UartSendTrace("0x%x", *paraList2);
                    paraList2 ++;
                    if(k!=(table[i].count - 1))
                        UartSendTrace(",   ");
                }
                UartSendTrace("}},\r\n");
            }
            #endif

                if((table[i].count+1) <=2){
                    Hal_DSI_WriteShortPacket((table[i].count+1), cmd, table[i].para_list);
                    #if defined(MIPI_PANEL_RW_SETTING_DEBUG)&&(MIPI_PANEL_RW_SETTING_DEBUG)
                    Hal_DSI_ReadLongPacket(table[i].count,cmd);
                    #endif
                }
                else{
                    Hal_DSI_WriteLongPacket((table[i].count+1), cmd,  table[i].para_list);
                    #if defined(MIPI_PANEL_RW_SETTING_DEBUG)&&(MIPI_PANEL_RW_SETTING_DEBUG)
                    Hal_DSI_ReadLongPacket(table[i].count,cmd);
                    #endif
                }
            break;
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

static void lcm_init_debug(void)
{
   //push_table(lcm_initialization_setting_lei, sizeof(lcm_initialization_setting_lei) / sizeof(struct LCM_setting_table), 1);
}

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
    RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - OTA7001A 480x854\r\n");


    m_PanelAttr.usDotClkRatio 	= 4;

    m_PanelAttr.usHBPorch 		= 16;
    m_PanelAttr.usHBlanking 	= 96;
    m_PanelAttr.usHSyncW 		= 8;
    m_PanelAttr.usVBPorch 		= 8;
    m_PanelAttr.usVBlanking 	= 25;
    m_PanelAttr.usVSyncW 		= 2;

    m_PanelAttr.usPRT2HdotClk 	= 2;

    m_PanelAttr.bDeltaRBG 		= MMP_FALSE;
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
void SendDSIPacket(unsigned char *paraList)
{
    unsigned char count=paraList[0];
    unsigned char *paraList1=&paraList[1];

#if MIPI_PANEL_RW_SETTING_DEBUG
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

void RTNA_LCD_Init(void)
{
    RTNA_DBG_Str(0, "\r\n####### RTNA_LCD_Init for lcd_S23501L0_ST7796S_mipi ...\r\n\r\n");
#if 0
    MMP_BOOL	err;
    MMP_ULONG fd, fs, fp;
    char file[] = "SD:\\lcd_porch_test.txt";
#endif
    //Reset PIN
    MMPF_PIO_Enable(DRV_IO_SPI0_GPIO4,MMP_TRUE);
    MMPF_PIO_EnableOutputMode(DRV_IO_SPI0_GPIO4, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(DRV_IO_SPI0_GPIO4, MMP_TRUE, MMP_TRUE);
    Delay_ms(50);
    MMPF_PIO_SetData(DRV_IO_SPI0_GPIO4, MMP_FALSE, MMP_TRUE);
    Delay_ms(100);
    MMPF_PIO_SetData(DRV_IO_SPI0_GPIO4, MMP_TRUE, MMP_TRUE);
    Delay_ms(50);
#if 0
    err = AHC_FS_FileOpen(file, AHC_StrLen(file), "rb", AHC_StrLen("rb"), &fd);
    err = AHC_FS_FileGetSize(fd, &fs);
    err = AHC_FS_FileRead(fd, (unsigned char*)fb, fs, (MMP_ULONG*)&fp);
    RTNA_DBG_Str(0, "fs = %d, fb:%s\r\n",fs,fb);
    AHC_FS_FileClose(fd) ;
#endif

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

    lcm_init();

#if	!RUN_TEST_PATTERN	//Built in test pattern mode
    Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_Config_VDO_Timing(&m_MIPI_DSI_LCM);
    Hal_DSI_Switch_Mode(m_MIPI_DSI_LCM.vdo_mode);
#endif
    MMPF_PIO_Enable(DRV_IO_PM_GPIO0, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(DRV_IO_PM_GPIO0, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(DRV_IO_PM_GPIO0, MMP_TRUE, MMP_TRUE);
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
    .name			= "ST7796S",
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
