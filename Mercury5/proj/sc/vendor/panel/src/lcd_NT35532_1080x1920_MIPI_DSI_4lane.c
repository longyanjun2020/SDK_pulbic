//==============================================================================
//
//  File        : lcd_NT35532_1080x1920_MIPI_DSI_4lane.c
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

#define PANEL_WIDTH                 (1080)
#define PANEL_HEIGHT                (1920)

#define  RGB888_SYNC_PULSE_MODE  0
#define  RGB888_SYNC_EVENT_MODE  1
#define  RGB888_BURST_MODE  2
#define  RGB565_SYNC_PULSE_MODE  3
#define  RGB565_SYNC_EVENT_MODE  4
#define  RGB565_BURST_MODE  5
#define  RGB666_BURST_MODE  6
#define  VDO_MODE      (RGB888_SYNC_PULSE_MODE)

#define MIPI_PANEL_RW_SETTING_DEBUG	(0)
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
#if 1
    0x14,//0x07, // HS_TRAIL		// > 60+4ui = 64.857698577860164 ->  6.675764
    0x0a,//0x07, // HS_PRPR			// 40+4ui < x < 85+6ui ns = 44.857698577860164 <x< 92.28654786679025 -> 4.617176<x<9.498999000000001
    0x14,//0x0e, // HS_ZERO		// >105+6ui = 112.2865478667902 -> 11.557587
    0x07, // CLK_HS_PRPR		// 38<x<95ns = 56UI/8UI = 7
    0x0d, // CLK_HS_EXIT		// >100ns = 104UI/8UI = 13
    0x08, // CLK_TRAIL		// >60ns = 64UI/8UI = 8
    0x20, // CLK_ZERO		// +CLK_HS_PRPR > 300ns = 296UI/8UI = 37
    0x18, // CLK_HS_POST	// >60+128ui = 215.4463544915252 -> 192UI/8UI = 24
    0x0a, // DA_HS_EXIT		// 100ns---->10
    0x00, // CONT_DET		//don`t care
    0x10,//0x06, // LPX				//50ns~70ns
    0x50,//0x1e, // TA_GET			//5*lpx=250ns
    0x18,//0x09, // TA_SURE			//1~2lpx=75ns
    0x40,//0x18, // TA_GO			//4*lpx=200ns
#else
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
    0x06, // LPX				//50ns~70ns
    0x1e, // TA_GET			//5*lpx=250ns
    0x09, // TA_SURE			//1~2lpx=75ns
    0x18, // TA_GO			//4*lpx=200ns
#endif
    0,
    0,
    0,
    0,

    #if  (VDO_MODE == RGB888_SYNC_PULSE_MODE) //vbp 8
     //HACT ,  	HPW ,  	HBP  ,  	HFP ,     	VACT ,     	VPW,    	VBP,    	VFP,   	BLLP,   		fps,    lane number,   DSI format,                        	DSI Mode
    1080,       155/*8*/,     66/*16*/,     72,      1920,       2,      8,       15,      0,       60/*60*/,     4,        DSI_FORMAT_RGB888,          DSI_SYNC_PULSE_MODE,
    #elif  (VDO_MODE == RGB888_BURST_MODE)
    720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB888,          DSI_BURST_MODE,
    #elif  (VDO_MODE == RGB666_BURST_MODE)
    720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                  DSI_FORMAT_RGB666,          DSI_BURST_MODE,
    #elif  (VDO_MODE == RGB565_BURST_MODE)
    720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB565,          DSI_BURST_MODE,
    #endif
    DSI_TOP_BGR_ORDER,
    {0},
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
#if 1

static struct LCM_setting_table lcm_initialization_setting[] = {

    {0xFF, 1 , { 0x00 }},
    {0x36, 1 , { 0x00 }},//REGW 0XB0,0X00
    {0xB0, 1 , { 0x00 }},//REGW 0XBA,0X03
    {0xBA, 1 , { 0x03 }},//REGW 0XBA,0X03
    {0xD3, 1 , { 0x08 }},//REGW 0XD3,0X08
    {0xD4, 1 , { 0x0E }},//REGW 0XD4,0X0E
    {0xD5, 1 , { 0x0F }},//REGW 0XD5,0X0F
    {0xD6, 1 , { 0x48 }},//REGW 0XD6,0X48
    {0xD7, 1 , { 0x00 }},//REGW 0XD7,0X00
    {0xD9, 1 , { 0x00 }},//REGW 0XD9,0X00

    {0xFF, 1 , { 0xEE }},//REGW 0XFF,0XEE
    {0xFB, 1 , { 0x01 }},//REGW 0XFB,0X01
    {0x40, 1 , { 0x00 }},//REGW 0X40,0X00
    {0x41, 1 , { 0x00 }},//REGW 0X41,0X00
    {0x42, 1 , { 0x00 }},//REGW 0X42,0X00

    {0xFF, 1 , { 0x01 }},
    {0x6E, 1 , { 0x80 }},
    {0x68, 1 , { 0x13 }},
    {0xFB, 1 , { 0x01 }},
    {0xFF, 1 , { 0x02 }},
    {0xFB, 1 , { 0x01 }},
    {0xFF, 1 , { 0x05 }},
    {0xFB, 1 , { 0x01 }},
    {0xD7, 1 , { 0x31 }},
    {0xD8, 1 , { 0x7E }},
    {REGFLAG_DELAY, 100, {}},
    //Command1
    {0xFF, 1 , { 0x00 }},
    {0xFB, 1 , { 0x01 }},
    {0xBA, 1 , { 0x03 }},
    {0x36, 1 , { 0x00 }},
    {0xB0, 1 , { 0x00 }},
    {0xD3, 1 , { 0x08 }},
    {0xD4, 1 , { 0x0E }},
    {0xD5, 1 , { 0x0F }},
    {0xD6, 1 , { 0x48 }},
    {0xD7, 1 , { 0x00 }},
    {0xD9, 1 , { 0x00 }},
    {0xFB, 1 , { 0x01 }},
    {0xFF, 1 , { 0xEE }},
    {0x02, 1 , { 0x00 }},
    {0x40, 1 , { 0x00 }},
    {0x02, 1 , { 0x00 }},
    {0x41, 1 , { 0x00 }},
    {0x02, 1 , { 0x00 }},
    {0x42, 1 , { 0x00 }},
    {0xFB, 1 , { 0x01 }},
    //Command2 Page0
    {0xFF, 1 , { 0x01 }},
    {0xFB, 1 , { 0x01 }},
    {0xFB, 1 , { 0x01 }},
    {0x01, 1 , { 0x55 }},
    {0x04, 1 , { 0x0C }},
    {0x05, 1 , { 0x3A }},
    {0x06, 1 , { 0x50 }},
    {0x07, 1 , { 0xD0 }},
    {0x0A, 1 , { 0x0F }},
    {0x0C, 1 , { 0x06 }},
    {0x0D, 1 , { 0x6B }},
    {0x0E, 1 , { 0x6B }},
    {0x0F, 1 , { 0x70 }},
    {0x10, 1 , { 0x63 }},
    {0x11, 1 , { 0x3C }},
    {0x12, 1 , { 0x5C }},

    {0x13,	1,	{0x4b}}, //VOCM 55
    {0x14,	1,	{0x55}}, //VCOM 55

    {0x15,	1,	{0x60}},
    {0x16,	1,	{0x15}},
    {0x17,	1,	{0x15}},

    {0x5B,	1,	{0xCA}},
    {0x5C,	1,	{0x00}},
    {0x5D,	1,	{0x00}},
    {0x5F,	1,	{0x1B}},

    {0x60,	1,	{0xD5}},
    {0x61,	1,	{0xF7}},
    {0x6C,	1,	{0xAB}},
    {0x6D,	1,	{0x44}},

    //Command2 Page4
    {0xFF, 1 , { 0x05 }},
    {0xFB, 1 , { 0x01 }},
    {0xFB, 1 , { 0x01 }},
    {0x00, 1 , { 0x3F }},
    {0x01, 1 , { 0x3F }},
    {0x02, 1 , { 0x3F }},
    {0x03, 1 , { 0x3F }},
    {0x04, 1 , { 0x38 }},
    {0x05, 1 , { 0x3F }},
    {0x06, 1 , { 0x3F }},
    {0x07, 1 , { 0x19 }},
    {0x08, 1 , { 0x1B }},
    {0x09, 1 , { 0x3F }},
    {0x0A, 1 , { 0x1D }},
    {0x0B, 1 , { 0x17 }},
    {0x0C, 1 , { 0x3F }},
    {0x0D, 1 , { 0x02 }},
    {0x0E, 1 , { 0x08 }},
    {0x0F, 1 , { 0x0C }},
    {0x10, 1 , { 0x3F }},
    {0x11, 1 , { 0x10 }},
    {0x12, 1 , { 0x3F }},
    {0x13, 1 , { 0x3F }},
    {0x14, 1 , { 0x3F }},
    {0x15, 1 , { 0x3F }},
    {0x16, 1 , { 0x3F }},
    {0x17, 1 , { 0x3F }},
    {0x18, 1 , { 0x38 }},
    {0x19, 1 , { 0x18 }},
    {0x1A, 1 , { 0x1A }},
    {0x1B, 1 , { 0x3F }},
    {0x1C, 1 , { 0x3F }},
    {0x1D, 1 , { 0x1C }},
    {0x1E, 1 , { 0x16 }},
    {0x1F, 1 , { 0x3F }},
    {0x20, 1 , { 0x3F }},
    {0x21, 1 , { 0x02 }},
    {0x22, 1 , { 0x06 }},
    {0x23, 1 , { 0x0A }},
    {0x24, 1 , { 0x3F }},
    {0x25, 1 , { 0x0E }},
    {0x26, 1 , { 0x3F }},
    {0x27, 1 , { 0x3F }},
    {0x54, 1 , { 0x06 }},
    {0x55, 1 , { 0x05 }},
    {0x56, 1 , { 0x1A }},
    {0x58, 1 , { 0x19 }},
    {0x59, 1 , { 0x36 }},
    {0x5A, 1 , { 0x1B }},
    {0x5B, 1 , { 0x01 }},
    {0x5C, 1 , { 0x32 }},
    {0x5E, 1 , { 0x21 }},
    {0x5F, 1 , { 0x22 }},
    {0x60, 1 , { 0x2B }},
    {0x61, 1 , { 0x2C }},
    {0x62, 1 , { 0x18 }},
    {0x63, 1 , { 0x01 }},
    {0x64, 1 , { 0x32 }},
    {0x65, 1 , { 0x00 }},
    {0x66, 1 , { 0x44 }},
    {0x67, 1 , { 0x11 }},
    {0x68, 1 , { 0x01 }},
    {0x69, 1 , { 0x01 }},
    {0x6A, 1 , { 0x04 }},
    {0x6B, 1 , { 0x22 }},
    {0x6C, 1 , { 0x08 }},
    {0x6D, 1 , { 0x08 }},
    {0x78, 1 , { 0x00 }},
    {0x79, 1 , { 0x00 }},
    {0x7E, 1 , { 0x00 }},
    {0x7F, 1 , { 0x00 }},
    {0x80, 1 , { 0x00 }},
    {0x81, 1 , { 0x00 }},
    {0x8D, 1 , { 0x00 }},
    {0x8E, 1 , { 0x00 }},
    {0x8F, 1 , { 0xC0 }},
    {0x90, 1 , { 0x73 }},
    {0x91, 1 , { 0x10 }},
    {0x92, 1 , { 0x09 }},
    {0x96, 1 , { 0x11 }},

    {0x97, 1 , { 0x14 }},
    {0x98, 1 , { 0x00 }},
    {0x99, 1 , { 0x00 }},
    {0x9A, 1 , { 0x00 }},
    {0x9B, 1 , { 0x61 }},
    {0x9C, 1 , { 0x15 }},
    {0x9D, 1 , { 0x30 }},
    {0x9F, 1 , { 0x0F }},
    {0xA2, 1 , { 0xB0 }},
    {0xA7, 1 , { 0x0A }},
    {0xA9, 1 , { 0x00 }},
    {0xAA, 1 , { 0x70 }},
    {0xAB, 1 , { 0xDA }},
    {0xAC, 1 , { 0xFF }},
    {0xAE, 1 , { 0xF4 }},
    {0xAF, 1 , { 0x40 }},
    {0xB0, 1 , { 0x7F }},
    {0xB1, 1 , { 0x16 }},
    {0xB2, 1 , { 0x53 }},
    {0xB3, 1 , { 0x00 }},
    {0xB4, 1 , { 0x2A }},
    {0xB5, 1 , { 0x3A }},
    {0xB6, 1 , { 0xF0 }},
    {0xBC, 1 , { 0x85 }},
    {0xBD, 1 , { 0xF8 }},
    {0xBE, 1 , { 0x3B }},
    {0xBF, 1 , { 0x13 }},
    {0xC0, 1 , { 0x77 }},
    {0xC1, 1 , { 0x77 }},
    {0xC2, 1 , { 0x77 }},
    {0xC3, 1 , { 0x77 }},
    {0xC4, 1 , { 0x77 }},
    {0xC5, 1 , { 0x77 }},
    {0xC6, 1 , { 0x77 }},
    {0xC7, 1 , { 0x77 }},
    {0xC8, 1 , { 0xAA }},
    {0xC9, 1 , { 0x2A }},
    {0xCA, 1 , { 0x00 }},
    {0xCB, 1 , { 0xAA }},
    {0xCC, 1 , { 0x92 }},
    {0xCD, 1 , { 0x00 }},
    {0xCE, 1 , { 0x18 }},
    {0xCF, 1 , { 0x88 }},
    {0xD0, 1 , { 0xAA }},
    {0xD1, 1 , { 0x00 }},
    {0xD2, 1 , { 0x00 }},
    {0xD3, 1 , { 0x00 }},
    {0xD6, 1 , { 0x02 }},
    {0xED, 1 , { 0x00 }},
    {0xEE, 1 , { 0x00 }},
    {0xEF, 1 , { 0x70 }},
    {0xFA, 1 , { 0x03 }},
    {0xFF, 1 , { 0x00 }},
    //Command2 Page0
    {0xFF, 1 , { 0x01 }},
    {0xFB, 1 , { 0x01 }},
    //GAMMA RED+
    {0x75, 1 , { 0x00 }},
    {0x76, 1 , { 0x00 }},
    {0x77, 1 , { 0x00 }},
    {0x78, 1 , { 0x1D }},
    {0x79, 1 , { 0x00 }},
    {0x7A, 1 , { 0x43 }},
    {0x7B, 1 , { 0x00 }},
    {0x7C, 1 , { 0x5F }},
    {0x7D, 1 , { 0x00 }},
    {0x7E, 1 , { 0x76 }},
    {0x7F, 1 , { 0x00 }},
    {0x80, 1 , { 0x8A }},
    {0x81, 1 , { 0x00 }},
    {0x82, 1 , { 0x9C }},
    {0x83, 1 , { 0x00 }},
    {0x84, 1 , { 0xAC }},
    {0x85, 1 , { 0x00 }},
    {0x86, 1 , { 0xBB }},
    {0x87, 1 , { 0x00 }},
    {0x88, 1 , { 0xEC }},
    {0x89, 1 , { 0x01 }},
    {0x8A, 1 , { 0x13 }},
    {0x8B, 1 , { 0x01 }},
    {0x8C, 1 , { 0x51 }},
    {0x8D, 1 , { 0x01 }},
    {0x8E, 1 , { 0x82 }},
    {0x8F, 1 , { 0x01 }},
    {0x90, 1 , { 0xCE }},
    {0x91, 1 , { 0x02 }},
    {0x92, 1 , { 0x09 }},
    {0x93, 1 , { 0x02 }},
    {0x94, 1 , { 0x0B }},
    {0x95, 1 , { 0x02 }},
    {0x96, 1 , { 0x41 }},
    {0x97, 1 , { 0x02 }},
    {0x98, 1 , { 0x7A }},
    {0x99, 1 , { 0x02 }},
    {0x9A, 1 , { 0x9F }},
    {0x9B, 1 , { 0x02 }},
    {0x9C, 1 , { 0xD2 }},
    {0x9D, 1 , { 0x02 }},
    {0x9E, 1 , { 0xF2 }},
    {0x9F, 1 , { 0x03 }},
    {0xA0, 1 , { 0x22 }},
    {0xA2, 1 , { 0x03 }},
    {0xA3, 1 , { 0x30 }},
    {0xA4, 1 , { 0x03 }},
    {0xA5, 1 , { 0x3F }},
    {0xA6, 1 , { 0x03 }},
    {0xA7, 1 , { 0x50 }},
    {0xA9, 1 , { 0x03 }},
    {0xAA, 1 , { 0x63 }},
    {0xAB, 1 , { 0x03 }},
    {0xAC, 1 , { 0x79 }},
    {0xAD, 1 , { 0x03 }},
    {0xAE, 1 , { 0x97 }},
    {0xAF, 1 , { 0x03 }},
    {0xB0, 1 , { 0xC2 }},
    {0xB1, 1 , { 0x03 }},
    {0xB2, 1 , { 0xCD }},
    //GAMMA RED-
    {0xB3, 1 , { 0x00 }},
    {0xB4, 1 , { 0x00 }},
    {0xB5, 1 , { 0x00 }},
    {0xB6, 1 , { 0x1D }},
    {0xB7, 1 , { 0x00 }},
    {0xB8, 1 , { 0x43 }},
    {0xB9, 1 , { 0x00 }},
    {0xBA, 1 , { 0x5F }},
    {0xBB, 1 , { 0x00 }},
    {0xBC, 1 , { 0x76 }},
    {0xBD, 1 , { 0x00 }},
    {0xBE, 1 , { 0x8A }},
    {0xBF, 1 , { 0x00 }},
    {0xC0, 1 , { 0x9C }},
    {0xC1, 1 , { 0x00 }},
    {0xC2, 1 , { 0xAC }},
    {0xC3, 1 , { 0x00 }},
    {0xC4, 1 , { 0xBB }},
    {0xC5, 1 , { 0x00 }},
    {0xC6, 1 , { 0xEC }},
    {0xC7, 1 , { 0x01 }},
    {0xC8, 1 , { 0x13 }},
    {0xC9, 1 , { 0x01 }},
    {0xCA, 1 , { 0x51 }},
    {0xCB, 1 , { 0x01 }},
    {0xCC, 1 , { 0x82 }},
    {0xCD, 1 , { 0x01 }},
    {0xCE, 1 , { 0xCE }},
    {0xCF, 1 , { 0x02 }},
    {0xD0, 1 , { 0x09 }},
    {0xD1, 1 , { 0x02 }},
    {0xD2, 1 , { 0x0B }},
    {0xD3, 1 , { 0x02 }},
    {0xD4, 1 , { 0x41 }},
    {0xD5, 1 , { 0x02 }},
    {0xD6, 1 , { 0x7A }},
    {0xD7, 1 , { 0x02 }},
    {0xD8, 1 , { 0x9F }},
    {0xD9, 1 , { 0x02 }},
    {0xDA, 1 , { 0xD2 }},
    {0xDB, 1 , { 0x02 }},
    {0xDC, 1 , { 0xF2 }},
    {0xDD, 1 , { 0x03 }},
    {0xDE, 1 , { 0x22 }},
    {0xDF, 1 , { 0x03 }},
    {0xE0, 1 , { 0x30 }},
    {0xE1, 1 , { 0x03 }},
    {0xE2, 1 , { 0x3F }},
    {0xE3, 1 , { 0x03 }},
    {0xE4, 1 , { 0x50 }},
    {0xE5, 1 , { 0x03 }},
    {0xE6, 1 , { 0x63 }},
    {0xE7, 1 , { 0x03 }},
    {0xE8, 1 , { 0x79 }},
    {0xE9, 1 , { 0x03 }},
    {0xEA, 1 , { 0x97 }},
    {0xEB, 1 , { 0x03 }},
    {0xEC, 1 , { 0xC2 }},
    {0xED, 1 , { 0x03 }},
    {0xEE, 1 , { 0xCD }},
    //GAMMA Green+
    {0xEF, 1 , { 0x00 }},
    {0xF0, 1 , { 0x00 }},
    {0xF1, 1 , { 0x00 }},
    {0xF2, 1 , { 0x1D }},
    {0xF3, 1 , { 0x00 }},
    {0xF4, 1 , { 0x43 }},
    {0xF5, 1 , { 0x00 }},
    {0xF6, 1 , { 0x5F }},
    {0xF7, 1 , { 0x00 }},
    {0xF8, 1 , { 0x76 }},
    {0xF9, 1 , { 0x00 }},
    {0xFA, 1 , { 0x8A }},
    //Command2 Page1
    {0xFF, 1 , { 0x02 }},
    {0xFB, 1 , { 0x01 }},
    {0x00, 1 , { 0x00 }},
    {0x01, 1 , { 0x9C }},
    {0x02, 1 , { 0x00 }},
    {0x03, 1 , { 0xAC }},
    {0x04, 1 , { 0x00 }},
    {0x05, 1 , { 0xBB }},
    {0x06, 1 , { 0x00 }},
    {0x07, 1 , { 0xEC }},
    {0x08, 1 , { 0x01 }},
    {0x09, 1 , { 0x13 }},
    {0x0A, 1 , { 0x01 }},
    {0x0B, 1 , { 0x51 }},
    {0x0C, 1 , { 0x01 }},
    {0x0D, 1 , { 0x82 }},
    {0x0E, 1 , { 0x01 }},
    {0x0F, 1 , { 0xCE }},
    {0x10, 1 , { 0x02 }},
    {0x11, 1 , { 0x09 }},
    {0x12, 1 , { 0x02 }},
    {0x13, 1 , { 0x0B }},
    {0x14, 1 , { 0x02 }},
    {0x15, 1 , { 0x41 }},
    {0x16, 1 , { 0x02 }},
    {0x17, 1 , { 0x7A }},
    {0x18, 1 , { 0x02 }},
    {0x19, 1 , { 0x9F }},
    {0x1A, 1 , { 0x02 }},
    {0x1B, 1 , { 0xD2 }},
    {0x1C, 1 , { 0x02 }},
    {0x1D, 1 , { 0xF2 }},
    {0x1E, 1 , { 0x03 }},
    {0x1F, 1 , { 0x22 }},
    {0x20, 1 , { 0x03 }},
    {0x21, 1 , { 0x30 }},
    {0x22, 1 , { 0x03 }},
    {0x23, 1 , { 0x3F }},
    {0x24, 1 , { 0x03 }},
    {0x25, 1 , { 0x50 }},
    {0x26, 1 , { 0x03 }},
    {0x27, 1 , { 0x63 }},
    {0x28, 1 , { 0x03 }},
    {0x29, 1 , { 0x79 }},
    {0x2A, 1 , { 0x03 }},
    {0x2B, 1 , { 0x97 }},
    {0x2D, 1 , { 0x03 }},
    {0x2F, 1 , { 0xC2 }},
    {0x30, 1 , { 0x03 }},
    {0x31, 1 , { 0xCD }},
    //GAMMA Green-
    {0x32, 1 , { 0x00 }},
    {0x33, 1 , { 0x00 }},
    {0x34, 1 , { 0x00 }},
    {0x35, 1 , { 0x1D }},
    {0x36, 1 , { 0x00 }},
    {0x37, 1 , { 0x43 }},
    {0x38, 1 , { 0x00 }},
    {0x39, 1 , { 0x5F }},
    {0x3A, 1 , { 0x00 }},
    {0x3B, 1 , { 0x76 }},
    {0x3D, 1 , { 0x00 }},
    {0x3F, 1 , { 0x8A }},
    {0x40, 1 , { 0x00 }},
    {0x41, 1 , { 0x9C }},
    {0x42, 1 , { 0x00 }},
    {0x43, 1 , { 0xAC }},
    {0x44, 1 , { 0x00 }},
    {0x45, 1 , { 0xBB }},
    {0x46, 1 , { 0x00 }},
    {0x47, 1 , { 0xEC }},
    {0x48, 1 , { 0x01 }},
    {0x49, 1 , { 0x13 }},
    {0x4A, 1 , { 0x01 }},
    {0x4B, 1 , { 0x51 }},
    {0x4C, 1 , { 0x01 }},
    {0x4D, 1 , { 0x82 }},
    {0x4E, 1 , { 0x01 }},
    {0x4F, 1 , { 0xCE }},
    {0x50, 1 , { 0x02 }},
    {0x51, 1 , { 0x09 }},
    {0x52, 1 , { 0x02 }},
    {0x53, 1 , { 0x0B }},
    {0x54, 1 , { 0x02 }},
    {0x55, 1 , { 0x41 }},
    {0x56, 1 , { 0x02 }},
    {0x58, 1 , { 0x7A }},
    {0x59, 1 , { 0x02 }},
    {0x5A, 1 , { 0x9F }},
    {0x5B, 1 , { 0x02 }},
    {0x5C, 1 , { 0xD2 }},
    {0x5D, 1 , { 0x02 }},
    {0x5E, 1 , { 0xF2 }},
    {0x5F, 1 , { 0x03 }},
    {0x60, 1 , { 0x22 }},
    {0x61, 1 , { 0x03 }},
    {0x62, 1 , { 0x30 }},
    {0x63, 1 , { 0x03 }},
    {0x64, 1 , { 0x3F }},
    {0x65, 1 , { 0x03 }},
    {0x66, 1 , { 0x50 }},
    {0x67, 1 , { 0x03 }},
    {0x68, 1 , { 0x63 }},
    {0x69, 1 , { 0x03 }},
    {0x6A, 1 , { 0x79 }},
    {0x6B, 1 , { 0x03 }},
    {0x6C, 1 , { 0x97 }},
    {0x6D, 1 , { 0x03 }},
    {0x6E, 1 , { 0xC2 }},
    {0x6F, 1 , { 0x03 }},
    {0x70, 1 , { 0xCD }},
    //GAMMA Blue+
    {0x71, 1 , { 0x00 }},
    {0x72, 1 , { 0x00 }},
    {0x73, 1 , { 0x00 }},
    {0x74, 1 , { 0x1D }},
    {0x75, 1 , { 0x00 }},
    {0x76, 1 , { 0x43 }},
    {0x77, 1 , { 0x00 }},
    {0x78, 1 , { 0x5F }},
    {0x79, 1 , { 0x00 }},
    {0x7A, 1 , { 0x76 }},
    {0x7B, 1 , { 0x00 }},
    {0x7C, 1 , { 0x8A }},
    {0x7D, 1 , { 0x00 }},
    {0x7E, 1 , { 0x9C }},
    {0x7F, 1 , { 0x00 }},
    {0x80, 1 , { 0xAC }},
    {0x81, 1 , { 0x00 }},
    {0x82, 1 , { 0xBB }},
    {0x83, 1 , { 0x00 }},
    {0x84, 1 , { 0xEC }},
    {0x85, 1 , { 0x01 }},
    {0x86, 1 , { 0x13 }},
    {0x87, 1 , { 0x01 }},
    {0x88, 1 , { 0x51 }},
    {0x89, 1 , { 0x01 }},
    {0x8A, 1 , { 0x82 }},
    {0x8B, 1 , { 0x01 }},
    {0x8C, 1 , { 0xCE }},
    {0x8D, 1 , { 0x02 }},
    {0x8E, 1 , { 0x09 }},
    {0x8F, 1 , { 0x02 }},
    {0x90, 1 , { 0x0B }},
    {0x91, 1 , { 0x02 }},
    {0x92, 1 , { 0x41 }},
    {0x93, 1 , { 0x02 }},
    {0x94, 1 , { 0x7A }},
    {0x95, 1 , { 0x02 }},
    {0x96, 1 , { 0x9F }},
    {0x97, 1 , { 0x02 }},
    {0x98, 1 , { 0xD2 }},
    {0x99, 1 , { 0x02 }},
    {0x9A, 1 , { 0xF2 }},
    {0x9B, 1 , { 0x03 }},
    {0x9C, 1 , { 0x22 }},
    {0x9D, 1 , { 0x03 }},
    {0x9E, 1 , { 0x30 }},
    {0x9F, 1 , { 0x03 }},
    {0xA0, 1 , { 0x3F }},
    {0xA2, 1 , { 0x03 }},
    {0xA3, 1 , { 0x50 }},
    {0xA4, 1 , { 0x03 }},
    {0xA5, 1 , { 0x63 }},
    {0xA6, 1 , { 0x03 }},
    {0xA7, 1 , { 0x79 }},
    {0xA9, 1 , { 0x03 }},
    {0xAA, 1 , { 0x97 }},
    {0xAB, 1 , { 0x03 }},
    {0xAC, 1 , { 0xC2 }},
    {0xAD, 1 , { 0x03 }},
    {0xAE, 1 , { 0xCD }},
    //GAMMA Blue-
    {0xAF, 1 , { 0x00 }},
    {0xB0, 1 , { 0x00 }},
    {0xB1, 1 , { 0x00 }},
    {0xB2, 1 , { 0x1D }},
    {0xB3, 1 , { 0x00 }},
    {0xB4, 1 , { 0x43 }},
    {0xB5, 1 , { 0x00 }},
    {0xB6, 1 , { 0x5F }},
    {0xB7, 1 , { 0x00 }},
    {0xB8, 1 , { 0x76 }},
    {0xB9, 1 , { 0x00 }},
    {0xBA, 1 , { 0x8A }},
    {0xBB, 1 , { 0x00 }},
    {0xBC, 1 , { 0x9C }},
    {0xBD, 1 , { 0x00 }},
    {0xBE, 1 , { 0xAC }},
    {0xBF, 1 , { 0x00 }},
    {0xC0, 1 , { 0xBB }},
    {0xC1, 1 , { 0x00 }},
    {0xC2, 1 , { 0xEC }},
    {0xC3, 1 , { 0x01 }},
    {0xC4, 1 , { 0x13 }},
    {0xC5, 1 , { 0x01 }},
    {0xC6, 1 , { 0x51 }},
    {0xC7, 1 , { 0x01 }},
    {0xC8, 1 , { 0x82 }},
    {0xC9, 1 , { 0x01 }},
    {0xCA, 1 , { 0xCE }},
    {0xCB, 1 , { 0x02 }},
    {0xCC, 1 , { 0x09 }},
    {0xCD, 1 , { 0x02 }},
    {0xCE, 1 , { 0x0B }},
    {0xCF, 1 , { 0x02 }},
    {0xD0, 1 , { 0x41 }},
    {0xD1, 1 , { 0x02 }},
    {0xD2, 1 , { 0x7A }},
    {0xD3, 1 , { 0x02 }},
    {0xD4, 1 , { 0x9F }},
    {0xD5, 1 , { 0x02 }},
    {0xD6, 1 , { 0xD2 }},
    {0xD7, 1 , { 0x02 }},
    {0xD8, 1 , { 0xF2 }},
    {0xD9, 1 , { 0x03 }},
    {0xDA, 1 , { 0x22 }},
    {0xDB, 1 , { 0x03 }},
    {0xDC, 1 , { 0x30 }},
    {0xDD, 1 , { 0x03 }},
    {0xDE, 1 , { 0x3F }},
    {0xDF, 1 , { 0x03 }},
    {0xE0, 1 , { 0x50 }},
    {0xE1, 1 , { 0x03 }},
    {0xE2, 1 , { 0x63 }},
    {0xE3, 1 , { 0x03 }},
    {0xE4, 1 , { 0x79 }},
    {0xE5, 1 , { 0x03 }},
    {0xE6, 1 , { 0x97 }},
    {0xE7, 1 , { 0x03 }},
    {0xE8, 1 , { 0xC2 }},
    {0xE9, 1 , { 0x03 }},
    {0xEA, 1 , { 0xCD }},
#if RUN_TEST_PATTERN
    {0xFF, 1 , { 0x00 }},
    {0xFF, 1 , { 0x05 }},
    {0xEA, 1 , { 0xFF }},
    {0xEB, 1 , { 0x00 }},
    {0xEC, 1 , { 0x11 }},
#else
    {0xFF, 1 , { 0x00 }},
    {0x36, 1 , { 0x08 }},
    {0x11, 0 , {}},
    {REGFLAG_DELAY, 150, {}},
    {0x29, 0 , {}},		// Display on
    {REGFLAG_DELAY, 50, {}},
#endif
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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for lcd_NT35532_1080x1920_MIPI_DSI_4lane ...\r\n");

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
