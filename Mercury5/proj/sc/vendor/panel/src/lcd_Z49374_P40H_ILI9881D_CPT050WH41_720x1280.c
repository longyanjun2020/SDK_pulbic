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
#include "halPnl.h"
#include "sys_sys.h"
#include "Config_SDK_EVB_C_TV_Decoder.h" // 2018-3-23
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


#define SECONDARY_DISPLAY 			(0)

#define HX8394_TST_MODE    (0)

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
    LCD_BUS_WIDTH_8,
    LCD_BGR565,			//ubBusCfg
    LCD_PHASE0,
    LCD_POLARITY0,
    LCD_MCU_80SYS,
    0,
    0,
    0,
    LCD_RGB_ORDER_RGB,

    // RGB interface
    MMP_FALSE,
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
         //HACT ,  HPW ,  HBP  ,  HFP ,     VACT ,     VPW,    VBP,      VFP,   BLLP,   fps,    lane number,   DSI format,                        DSI Mode
    //  720,	   2,	  20,	  50,	    1280, 	    2,		30, 	  60,	  0,	   60,	   4,			DSI_FORMAT_RGB888,		  DSI_SYNC_PULSE_MODE
          720,	   2,	  50,	  50,	    1280, 	    2,		60, 	  60,	  0,	   40,	   4,			DSI_FORMAT_RGB888,		  DSI_SYNC_PULSE_MODE
        //720,	   2,	  40,	  60,		1280,		2,		40, 	  60,	  0,	   60,	   4,			DSI_FORMAT_RGB888,		  DSI_SYNC_PULSE_MODE
        #elif  (VDO_MODE == RGB888_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB888,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB666_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                  DSI_FORMAT_RGB666,          DSI_BURST_MODE
        #elif  (VDO_MODE == RGB565_BURST_MODE)
        720,          24,     48,      48,          1280,       2,        5,       9,       0,       60,     2,                 DSI_FORMAT_RGB565,          DSI_BURST_MODE
        #endif
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
static struct LCM_setting_table lcm_initialization_setting[] = {
    {0xFF,3,{0x98,81,03}},

    //GIP_1
    {0x01,1,{0x00}},
    {0x02,1,{0x00}},
    {0x03,1,{0x55}},
    {0x04,1,{0x13}},
    {0x05,1,{0x00}},
    {0x06,1,{0x05}},
    {0x07,1,{0x01}},
    {0x08,1,{0x00}},
    {0x09,1,{0x34}},
    {0x0a,1,{0x01}},
    {0x0b,1,{0x01}},
    {0x0c,1,{0x32}},
    {0x0d,1,{0x00}},
    {0x0e,1,{0x00}},
    {0x0f,1,{0x19}},
    {0x10,1,{0x19}},
    {0x11,1,{0x00}},
    {0x12,1,{0x00}},
    {0x13,1,{0x00}},
    {0x14,1,{0x00}},
    {0x15,1,{0x08}},
    {0x16,1,{0x08}},
    {0x17,1,{0x00}},
    {0x18,1,{0x08}},
    {0x19,1,{0x00}},
    {0x1a,1,{0x00}},
    {0x1b,1,{0x00}},
    {0x1c,1,{0x00}},
    {0x1d,1,{0x00}},
    {0x1e,1,{0x40}},
    {0x1f,1,{0x40}},
    {0x20,1,{0x02}},
    {0x21,1,{0x05}},
    {0x22,1,{0x02}},
    {0x23,1,{0x00}},
    {0x24,1,{0x87}},
    {0x25,1,{0x87}},
    {0x26,1,{0x00}},
    {0x27,1,{0x00}},
    {0x28,1,{0x3B}},
    {0x29,1,{0x03}},
    {0x2a,1,{0x00}},
    {0x2b,1,{0x00}},
    {0x2c,1,{0x00}},
    {0x2d,1,{0x00}},
    {0x2e,1,{0x00}},
    {0x2f,1,{0x00}},
    {0x30,1,{0x00}},
    {0x31,1,{0x00}},
    {0x32,1,{0x00}},
    {0x33,1,{0x00}},
    {0x34,1,{0x04}},
    {0x35,1,{0x00}},
    {0x36,1,{0x00}},
    {0x37,1,{0x00}},
    {0x38,1,{0x01}},
    {0x39,1,{0x35}},
    {0x3A,1,{0x01}},
    {0x3B,1,{0x40}},
    {0x3C,1,{0x00}},
    {0x3D,1,{0x01}},
    {0x3E,1,{0x00}},
    {0x3F,1,{0x00}},
    {0x40,1,{0x35}},
    {0x41,1,{0x88}},
    {0x42,1,{0x00}},
    {0x43,1,{0x00}},
    {0x44,1,{0x1F}},

    //GIP_2
    {0x50,1,{0x01}},
    {0x51,1,{0x23}},
    {0x52,1,{0x45}},
    {0x53,1,{0x67}},
    {0x54,1,{0x89}},
    {0x55,1,{0xAB}},
    {0x56,1,{0x01}},
    {0x57,1,{0x23}},
    {0x58,1,{0x45}},
    {0x59,1,{0x67}},
    {0x5A,1,{0x89}},
    {0x5B,1,{0xAB}},
    {0x5C,1,{0xCD}},
    {0x5D,1,{0xEF}},

    //GIP_3
    {0x5e,1,{0x13}},
    {0x5f,1,{0x06}},	//STV_06
    {0x60,1,{0x0C}},	//CK1_0C
    {0x61,1,{0x0D}},	//CK2_0D
    {0x62,1,{0x0E}},	//CK1B_0E
    {0x63,1,{0x0F}},   //CK2B_0F
    {0x64,1,{0x02}},
    {0x65,1,{0x02}},
    {0x66,1,{0x02}},   //GOUT8 VGL 02
    {0x67,1,{0x02}},   //GOUT9 VGL 02
    {0x68,1,{0x02}},
    {0x69,1,{0x02}},
    {0x6a,1,{0x02}},
    {0x6b,1,{0x02}},   //GOUT13 VGL 02
    {0x6c,1,{0x02}},   //GOUT14 VGL 02
    {0x6d,1,{0x02}},   //GOUT15 VGL 02
    {0x6e,1,{0x05}},   //GOUT16  VGH 05
    {0x6f,1,{0x05}},   //GOUT17  VGH 05
    {0x70,1,{0x05}},   //GOUT18  VGH 05
    {0x71,1,{0x02}},
    {0x72,1,{0x01}},	//GOUT20  FWE 01
    {0x73,1,{0x00}},	//GOUT21  BWE 00
    {0x74,1,{0x08}},	//GOUT22  RSTE 08
    {0x75,1,{0x08}},
    {0x76,1,{0x0C}},
    {0x77,1,{0x0D}},
    {0x78,1,{0x0E}},
    {0x79,1,{0x0F}},
    {0x7a,1,{0x02}},
    {0x7b,1,{0x02}},
    {0x7c,1,{0x02}},
    {0x7d,1,{0x02}},
    {0x7e,1,{0x02}},
    {0x7f,1,{0x02}},
    {0x80,1,{0x02}},
    {0x81,1,{0x02}},
    {0x82,1,{0x02}},
    {0x83,1,{0x02}},
    {0x84,1,{0x05}},
    {0x85,1,{0x05}},
    {0x86,1,{0x05}},
    {0x87,1,{0x02}},
    {0x88,1,{0x01}},
    {0x89,1,{0x00}},
    {0x8A,1,{0x06}},

    {0xFF,3,{0x98,0x81,0x04}},
    {0x68,1,{0xDB}},	 //nonoverlap 18ns (VGH and VGL)
    {0x6D,1,{0x08}},	 //gvdd_isc[2:0]=0 (0.2uA) 可減少VREG1擾動
    {0x70,1,{0x00}},	 //VGH_MOD and VGH_DC CLKDIV disable
    {0x71,1,{0x00}},	 //VGL CLKDIV disable
    {0x66,1,{0xFE}},	 //VGH 4X
    {0x6F,1,{0x05}},	 //GIP EQ_EN
    {0x82,1,{0x14}},	 //VREF_VGH_MOD_CLPSEL 15V
    {0x84,1,{0x14}},	 //VREF_VGH_CLPSEL 15V
    {0x85,1,{0x14}},	 //VREF_VGL_CLPSEL -12V
    {0x32,1,{0xAC}},	 //開啟負channel的power saving
    {0x8C,1,{0x80}},	 //sleep out Vcom disable以避免Vcom source不同步enable導致玻璃微亮
    {0x3C,1,{0xF5}},	 //開啟Sample & Hold Function
    {0x3A,1,{0x24}},	 //PS_EN OFF
    {0xB5,1,{0x02}},	 //GAMMA OP
    {0x31,1,{0x25}},	 //SOURCE OP
    {0x88,1,{0x33}},	//VSP/VSN LVD Disable
    //{0x2F,1,{0x01}},	//自检模式

    {0xFF,3,{0x98,0x81,0x01}},
    {0x22,1,{0x0A}},
    {0x31,1,{0x00}},
    {0x50,1,{0x78}},	  //vreg1  4.8V
    {0x51,1,{0x78}},	  //vreg2 -4.8V
    {0x53,1,{0x94}},	  //VCOM1
    {0x55,1,{0x94}},	  //VCOM2
    {0x60,1,{0x28}},
    {0x61,1,{0x00}},
    {0x62,1,{0x0D}},
    {0x63,1,{0x00}},

    {0xA0,1,{0x00}},
    {0xA1,1,{0x1F}},
    {0xA2,1,{0x2E}},
    {0xA3,1,{0x13}},
    {0xA4,1,{0x15}},
    {0xA5,1,{0x28}},
    {0xA6,1,{0x1C}},
    {0xA7,1,{0x1D}},
    {0xA8,1,{0x92}},
    {0xA9,1,{0x1B}},
    {0xAA,1,{0x28}},
    {0xAB,1,{0x8A}},
    {0xAC,1,{0x1C}},
    {0xAD,1,{0x1A}},
    {0xAE,1,{0x4E}},
    {0xAF,1,{0x23}},
    {0xB0,1,{0x28}},
    {0xB1,1,{0x5B}},
    {0xB2,1,{0x6A}},
    {0xB3,1,{0x39}},

    {0xC0,1,{0x00}},
    {0xC1,1,{0x1F}},
    {0xC2,1,{0x2E}},
    {0xC3,1,{0x13}},
    {0xC4,1,{0x15}},
    {0xC5,1,{0x28}},
    {0xC6,1,{0x1C}},
    {0xC7,1,{0x1D}},
    {0xC8,1,{0x92}},
    {0xC9,1,{0x1B}},
    {0xCA,1,{0x28}},
    {0xCB,1,{0x8A}},
    {0xCC,1,{0x1C}},
    {0xCD,1,{0x1A}},
    {0xCE,1,{0x4E}},
    {0xCF,1,{0x23}},
    {0xD0,1,{0x28}},
    {0xD1,1,{0x5B}},
    {0xD2,1,{0x6A}},
    {0xD3,1,{0x39}},

    //CMD_Page 0
    {0xFF,3,{0x98,0x81,0x00}},
    {0x11,00,{0x00}},
    {REGFLAG_DELAY, 120, {}},
    {0x29,00,{0x00}},
    //{0x35,00,{0x00}},
    //{0x36,1,{0x03}},//反扫
    {REGFLAG_END_OF_TABLE, 0x00, {}}

} ;

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
    RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD -  720x1280\r\n");


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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9881D_720X1280_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
#endif
    #if 0
    Hal_DSI_DHY_Pol(DSI_DATA_LANE0_SEL, 1);
    Hal_DSI_DHY_Pol(DSI_DATA_LANE1_SEL, 1);
    Hal_DSI_DHY_Pol(DSI_DATA_LANE2_SEL, 1);
    Hal_DSI_DHY_Pol(DSI_DATA_LANE3_SEL, 1);
    Hal_DSI_DHY_Pol(DSI_CLK_LANE_SEL, 1);

    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE0_SEL, 4); //0
    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE1_SEL, 3); //1
    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE2_SEL, 1);	//3
    Hal_DSI_DHY_LaneSel(DSI_DATA_LANE3_SEL, 0); //4
    Hal_DSI_DHY_LaneSel(DSI_CLK_LANE_SEL, 2);   //2
    #endif
    Hal_DSI_DHY_Init();
    //Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_PadOutSel(m_MIPI_DSI_LCM.u8LaneNum);
    Hal_DSI_SetLaneNum((DSI_TOTAL_LANE_NUM)m_MIPI_DSI_LCM.u8LaneNum);
    Hal_DSI_Switch_Mode(DSI_CMD_MODE);
    Hal_DSI_clk_HS_mode(1);

    //Reset PIN
    MMPF_PIO_Enable(DRV_IO_FUART_GPIO1,MMP_TRUE);
    MMPF_PIO_EnableOutputMode(DRV_IO_FUART_GPIO1, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(DRV_IO_FUART_GPIO1, MMP_TRUE, MMP_TRUE);
    Delay_ms(50);
    MMPF_PIO_SetData(DRV_IO_FUART_GPIO1, MMP_FALSE, MMP_TRUE);
    Delay_ms(100);
    MMPF_PIO_SetData(DRV_IO_FUART_GPIO1, MMP_TRUE, MMP_TRUE);
    Delay_ms(50);

    lcm_init();

    //Hal_DSI_clk_HS_mode(1);
    Hal_DSI_PHY_TIMCONFIG(&m_MIPI_DSI_LCM);
    Hal_DSI_Config_VDO_Timing(&m_MIPI_DSI_LCM);
    Hal_DSI_Switch_Mode(m_MIPI_DSI_LCM.vdo_mode);


    MMPF_PIO_Enable(91, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(91, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(91, MMP_TRUE, MMP_TRUE);
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
    .name			= "NT35521SH",
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
