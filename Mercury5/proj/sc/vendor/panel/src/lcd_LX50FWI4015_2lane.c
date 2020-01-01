//==============================================================================

//==============================================================================
//
//  File        : lcd_LX50FWI4015_2lane.c
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

#define PANEL_WIDTH                 (480)
#define PANEL_HEIGHT                (854)

#define  RGB888_SYNC_PULSE_MODE  0
#define  RGB888_SYNC_EVENT_MODE  1
#define  RGB888_BURST_MODE  2
#define  RGB565_SYNC_PULSE_MODE  3
#define  RGB565_SYNC_EVENT_MODE  4
#define  RGB565_BURST_MODE  5
#define  RGB666_BURST_MODE  6
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
        LCD_PHASE0,		//ubPhase
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

static LCM_PARAMS  m_MIPI_DSI_LCM=
{
        0x07, // HS_TRAIL		// > 60+4ui = 64.857698577860164 ->  6.675764
        0x07, // HS_PRPR			// 40+4ui < x < 85+6ui ns = 44.857698577860164 <x< 92.28654786679025 -> 4.617176<x<9.498999000000001
        0x0e, // HS_ZERO		// >105+6ui = 112.2865478667902 -> 11.557587
        0x07, // CLK_HS_PRPR		// 38<x<95ns = 56UI/8UI = 7
        0x0d, // CLK_HS_EXIT		// >100ns = 104UI/8UI = 13
        0x08, // CLK_TRAIL		// >60ns = 64UI/8UI = 8
        0x20, // CLK_ZERO		// +CLK_HS_PRPR > 300ns = 296UI/8UI = 37
        0x18, // CLK_HS_POST	// >60+128ui = 215.4463544915252 -> 192UI/8UI = 24
        0x0a, // DA_HS_EXIT		// 100ns---->10
        0x00, // CONT_DET		//don`t care
        0x40, // LPX				//50ns~70ns
        0x1e, // TA_GET			//5*lpx=250ns
        0x09, // TA_SURE			//1~2lpx=75ns
        0x18, // TA_GO			//4*lpx=200ns
        0,
        0,
        0,
        0,

#if  (VDO_MODE == RGB888_SYNC_PULSE_MODE) //vbp 8
        //HACT ,  	HPW ,  	HBP  ,  	HFP ,     	VACT ,     	VPW,    	VBP,    	VFP,   	BLLP,   		fps,    lane number,   DSI format,                        	DSI Mode
        480,            32,         50,         150,        854,            2,              16,       6,            0,              60,     2,                  DSI_FORMAT_RGB888,          DSI_SYNC_PULSE_MODE,
#endif
        DSI_TOP_BGR_ORDER,
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
static struct LCM_setting_table lcm_initialization_setting[] = {

        {0xF0,  2 ,{0x5A,0x5A}},
        {0xF1,  2 ,{0xA5,0xA5}},
        {0xB4,  11 ,{0x03,0x03,0x03,0x06,0x04,0x0C,0x0E,0x10,0x12,0x08,0x0A}},
        {0xB3,  11 ,{0x03,0x03,0x03,0x07,0x05,0x0D,0x0F,0x11,0x13,0x09,0x0B}},
        {0xB0,  12 ,{0x54,0x32,0x23,0x45,0x44,0x44,0x44,0x44,0x60,0x00,0x60,0x1C}},
        {0xB1,  8 ,{0x32,0x84,0x02,0x83,0x12,0x00,0x70,0x1C}},
        {0xB2,  5 ,{0x73,0x09,0x08,0x89,0x48}},
        {0xB6,  3 ,{0x60,0x60,0x05}},
        {0xB7,  1 ,{0x41}},
        {0xC1,  6 ,{0x10,0x0E,0x02,0x14,0x14,0x08}},
        {0xC2,  1 ,{0x82}},
        {0xC3,  2 ,{0x2A,0x11}},
        {0xD0,  3 ,{0x17,0x10,0x00}},
        {0xC6,  7 ,{0x08,0x15,0xFF,0x10,0x16,0x80,0x60}},
        {0xC7,  1 ,{0x04}},
        {0xC9,  2 ,{ 0x37,0x93}},

        {REGFLAG_DELAY, 120, {}},//delay 120;
        //{0xC8,  38 ,{0x7D,0x69,0x5A,0x4D,0x49,0x3A,0x3E,0x2A,0x45,0x47,0x48,0x69,0x57,0x5F,0x52,0x4D,0x40,0x2C,0x07,0x7D,0x69,0x5A,0x4D,0x49,0x3A,0x3E,0x2A,0x45,0x47,0x48,0x69,0x57,0x5F,0x52,0x4D,0x40,0x2C,0x07}}
        {0xC8,  38 ,{0x7F,0x66,0x57,0x49,0x45,0x34,0x38,0x22,0x3C,0x3C,0x3D,0x5C,0x4B,0x54,0x46,0x40,0x2F,0x14,0x00,0x7F,0x66,0x57,0x49,0x45,0x34,0x38,0x22,0x3C,0x3C,0x3D,0x5C,0x4B,0x54,0x46,0x40,0x2F,0x14,0x00}},
        {REGFLAG_DELAY, 120, {}},//delay 120;
        {0x11, 1 , {0x00}},
        {REGFLAG_DELAY, 120, {}},//delay 120;
        {0x29, 1 , {0x00}},

        //{REGFLAG_DELAY, 200, {}},//delay 20;
        {REGFLAG_END_OF_TABLE, 0x00, {}}
};

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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for lcd_LX50FWI4015_2lane ...\r\n");

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
    //Hal_DSI_LPLL(&m_MIPI_DSI_LCM);

#if	!RUN_TEST_PATTERN	//Built in test pattern mode
    Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_Config_VDO_Timing(&m_MIPI_DSI_LCM);
    Hal_DSI_Switch_Mode(m_MIPI_DSI_LCM.vdo_mode);
#endif
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
        .name			= "NT35532",
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

