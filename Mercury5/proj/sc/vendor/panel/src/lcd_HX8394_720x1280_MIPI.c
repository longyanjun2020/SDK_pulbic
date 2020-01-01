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

#include "Customer_config.h" // CarDV
#include "lib_retina.h"
#include "lcd_common.h"
#include "mmpf_pio.h"
#include "Mipi_SSD2828.h"
#include "halPnl.h"

#define PANEL_WIDTH                 (720)//(800)//pm16
#define PANEL_HEIGHT                (1280)//(480)
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define Delayms(t) 					LCD_WAIT(t)

#define SECONDARY_DISPLAY 			(0)

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	// Panel basic setting
	PANEL_WIDTH, PANEL_HEIGHT,
	LCD_TYPE_RGBLCD,
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


#define Delay_us(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.udelay(n))
#define Delay_ms(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.mdelay(n))

#define LCD_YSIZE_TFT  (720)
#define LCD_XSIZE_TFT  (1280)	

#if 0
#define LCD_HBPD		(5)
#define LCD_HFPD		(25)
#define LCD_HSPW		(5)
#define LCD_VBPD		(10)
#define LCD_VFPD		(30)
#define LCD_VSPW		(20)
#else

    #define SSD2828_LCD_HBPD		(40)
    #define SSD2828_LCD_HFPD		(20)
    #define SSD2828_LCD_HSPW		(5)
    #define SSD2828_LCD_VBPD		(20)
    #define SSD2828_LCD_VFPD		(50)
    #define SSD2828_LCD_VSPW		(40)

    #define LCD_HBPD		(20) //20
    #define LCD_HBLANK		(LCD_HBPD+8) //8
    #define LCD_HSPW		(5)
    #define LCD_VBPD		(20) //20
    #define LCD_VBLANK		(LCD_VBPD+20) //30
    #define LCD_VSPW		(40)
#endif
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



char HX8394ExtCmd[]   ={    0xB9,   3,
                            0xFF,   0x83,   0x94};

char HX8394Tab0[]     ={    0xB1,   10,
                            0x48,   0x11,   0x71,   0x09,   0x32,
                            0x54,   0x71,   0x71,   0x4e,   0x43 };

char HX8394Tab1[]     ={    0xBA,  6, 
                            0x61,   0x03,   0x68,   0x6B,   0xB2,   0xC0};

char HX8394Tab2[]     ={    0xD4,  1,
                            0x02};

char HX8394Tab3[]     ={    0xB2,   6,
                            0x65,   0x80,   0x64,   0x05,   0x07,   0x2F};

char HX8394Tab4[]     ={    0xB4,   21,
                            0x26,   0x76,   0x26,   0x76,   0x26,   0x26,   
                            0x05,   0x10,   0x86,   0x75,   0x00,   0x3F,   
                            0x26,   0x76,   0x26,   0x76,   0x26,   0x26,   
                            0x05,   0x10,   0x86};

char HX8394Tab5[]     ={    0xD3,  33, 
                            0x00,   0x00,   0x04,   0x04,   0x01,   0x01,   
                            0x10,   0x00,   0x32,   0x10,   0x00,   0x00,
                            0x00,   0x32,   0x15,   0x04,   0x05,   0x04,
                            0x32,   0x15,   0x14,   0x05,   0x14,   0x37,
                            0x33,   0x04,   0x04,   0x37,   0x00,   0x00,
                            0x47,   0x05,   0x40};

char HX8394Tab6[]     ={    0xD5, 44,
                            0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
                            0x18,0x18,0x18,0x18,0x18,0x25,0x24,0x27,0x26,
                            0x18,0x18,0x11,0x10,0x15,0x14,0x13,0x12,0x17,
                            0x16,0x01,0x00,0x05,0x04,0x03,0x02,0x07,0x06,
                            0x21,0x20,0x23,0x22,0x18,0x18,0x18,0x18};

char HX8394Tab7[]     ={    0xD6,44,
                            0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
                            0x18,0x18,0x18,0x18,0x18,0x22,0x23,0x20,0x21,
                            0x18,0x18,0x12,0x13,0x16,0x17,0x10,0x11,0x14,
                            0x15,0x06,0x07,0x02,0x03,0x04,0x05,0x00,0x01,
                            0x26,0x27,0x24,0x25,0x18,0x18,0x18,0x18};

char HX8394Tab8[]     ={    0xE0,58,
                            0x00,0x04,0x11,0x1B,0x1E,0x22,0x27,0x26,0x51,
                            0x60,0x70,0x6F,0x7A,0x8C,0x94,0x9A,0xA9,0xAC,
                            0xA9,0xB9,0xC8,0x64,0x62,0x67,0x69,0x6A,0x7F,
                            0x7F,0x7F,0x00,0x04,0x11,0x1B,0x1E,0x22,0x27,
                            0x26,0x51,0x60,0x70,0x6F,0x7A,0x8C,0x94,0x9A,
                            0xA9,0xAC,0xA9,0xB9,0xC8,0x64,0x62,0x67,0x69,
                            0x6A,0x7F,0x7F,0x7F};

char HX8394Tab9[]     ={    0xCC,1,
                            0x03};

char HX8394Tab10[]     ={   0xC0,2,
                            0x1F,0x31};

char HX8394Tab11[]     ={   0xB6,2,
                            0x43,0x43};

char HX8394Tab12[]     ={   0xBD,1,
                            0x01};

char HX8394Tab13[]     ={   0xB1,1,
                            0x00};

char HX8394Tab14[]     ={   0xBD,1,
                            0x00};

char HX8394Tab15[]     ={   0xBF, 7 ,
                            0x40,0x81,0x50,0x00,0x1A,0xFC,0x01};
char HX8394Tab16[]     ={   0xB2,12,
                            0x65,0x80,0x64,0x05,0x07,0x2F,0x00,0x00,0x00,
                            0x00,0xC0,0x18};

char DisplayOn[]        ={   0x29, 0}; 
char AllPixelOn[]       ={   0x23, 0}; //turn to white display, debug used
char AllPixelOFF[]      ={   0x22, 0}; //turn to white display, debug used
char SleepOut[]         ={   0x11, 0};
char INVOFF[]           ={   0x21, 0};
char ADDRESS_MODE[]     ={   0x36, 1,
                             0x02}; // Horizontal flip
void PowerOn_Panel(void) 
{
    //unsigned short ret_val;
    //SSD2828_Read_Status();
    SSD2828_Send_Write_Dsi_Packet(ADDRESS_MODE);
    SSD2828_Send_Write_Dsi_Packet(HX8394ExtCmd);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab0);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab1);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab2);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab3);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab4);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab5);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab6);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab7);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab8);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab9);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab10);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab11);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab12);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab13);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab14);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab15);
    SSD2828_Send_Write_Dsi_Packet(SleepOut);     // panel sleep out
    Delay_ms(200);
    SSD2828_Send_Write_Dsi_Packet(HX8394Tab16);
    //SSD2828_Send_Write_Dsi_Packet(INVOFF);        // not included in initial sequence

    SSD2828_Send_Write_Dsi_Packet(DisplayOn);     // display on
    Delay_ms(200);	
}

void RTNA_Init_MIPI_DSI(void)
{
	unsigned short cfg;
    // 0xC1 MRSR = Maximum Return Size Register 
 	SPI_init_gpio();
    #if 0
	Set_RST(0);// ( rGPFDAT &= (~(1<<3))) ;
	Delay_ms(50);
	Set_RST(1);//  ( rGPFDAT |= (1<<3) ) ;
	Delay_ms(50);
    #endif
	Delay_ms(10);
 
    SPI_2828_WrReg(0xD4, 0xFA); // special command for read register back used
    //SSD2828_Send_Read_Dsi_Packet(HX8394_READ_DSPY_IDENT_INFO, 1);
    //SSD2828_Read_Status();
    #if 0
    SPI_2828_WrReg(SSD2828_DAR1, 0x3f09);	    //0x1402 HZ zero/prepare delay
    SPI_2828_WrReg(SSD2828_DAR7, 0x05);	    //0x10
    SPI_2828_WrReg(SSD2828_DAR2, 0x7070);	    //0x2803 clk zero/prepare delay
    SPI_2828_WrReg(SSD2828_DAR3, 0x0416);	    //0x0416 clk pre/post delay
    #endif
    //SPI_2828_WrReg(SSD2828_ACR4, );	    //Clock delay sel
    SPI_2828_WrReg(0xb1,( SSD2828_LCD_VSPW<<8)| SSD2828_LCD_HSPW);	//Vertical sync and horizontal sync active period 
	SPI_2828_WrReg(0xb2,( SSD2828_LCD_VBPD<<8)| SSD2828_LCD_HBPD);	//Vertical and horizontal back porch period  
	SPI_2828_WrReg(0xb3,( SSD2828_LCD_VFPD<<8)| SSD2828_LCD_HFPD);	//Vertical and horizontal front porch period 
	SPI_2828_WrReg(0xb4, 720);		//Horizontal active period 
	SPI_2828_WrReg(0xb5, 1280);		//Vertical active period
    //SPI_2828_WrReg(0xb6, 0x2007);				//Video mode and video pixel format 888
    cfg =0;
    cfg &= ~VICR6_VSYNC_ACT_HIGH;
    cfg &= ~VICR6_HSYNC_ACT_HIGH;
    cfg |= VICR6_DATA_LATCH_RISE_EDGE; //VICR6_DATA_LATCH_RISE_EDGE
    cfg |= VICR6_VIDEO_BURST_MODE;
    cfg |= VICR6_VIDEO_DATA_FORMAT_16BPP; 
	SPI_2828_WrReg(0xb6, cfg);  // 0x2008 //pm16 note:2004无显示,0008横向*2显示		//Video mode and video pixel format       565	
	/*
        Bit 15      VS_P    Vsync pulse active low/high
        Bit 14      HS_P    Hsync pulse active low/high
        Bit 13      PCLK_P  PCLK launch at falling/rising edge
        Bit 7       NVB     Non video data burst mode control
        Bit 3-2     VM      00 - Non burst mode with sync pulse
                            01 -  Non burst mode with sync event
                            10 -  Burst mode
                            11 -  Reserved
        Bit 1-0     VPF     00- 16bpp, 01- 18bpp packed, 10-18bpp, loosely packed, 11- 24bpp
    */
    SPI_2828_WrReg(0xde, SSD2828_LANE_CFG_2_LANE);//panmdf16				//MIPI lane select 
	//SPI_2828_WrReg(0xDD, (LCD_HFPD<<8)|LCD_VFPD);
	//SPI_2828_WrReg(0xd6, 0x0004);				//Color order and endianess	BGR
	SPI_2828_WrReg(0xd6, 0x0005);				//
	//SPI_2828_WrReg(0xb9, 0x0000);				//PLL enable 
    SPI_2828_WrReg(0xba, 0xC015); /*801c*/ //pm16?
	SPI_2828_WrReg(0xbb, 0x0008);				//LP clock divider p.38
	//SPI_2828_WrReg(0xc4, 0x0001);				//BTA setting
    SPI_2828_WrReg(0xb9, 0x0001);				//PLL enable 
	SPI_2828_WrReg(0xb7, 0x0150);				//Generic mode, LP mode
	SPI_2828_WrReg(0xb8, 0x0000);				//VC register
	
    //SPI_2828_WrReg(0xc4, 0x0005);				//BTA setting
	SPI_2828_WrReg(0xc4, 0x0005);				//BTA setting     
    PowerOn_Panel();

  	SPI_2828_WrReg(0xb7, 0x032B);		//0x030B | 0x0020  //Generic mode, HS video mode
    return; 
}

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - OTA7001A 480x854\r\n");


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

    m_PanelAttr.usHBPorch 		= LCD_HBPD;
	m_PanelAttr.usHBlanking 	= LCD_HBLANK;
	m_PanelAttr.usHSyncW 		= LCD_HSPW;
	m_PanelAttr.usVBPorch 		= LCD_VBPD;
	m_PanelAttr.usVBlanking 	= LCD_VBLANK;
	m_PanelAttr.usVSyncW 		= LCD_VSPW;

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
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for HX8394_720X1280_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif

#if 1 //ENABLE_MIPI_PANEL
    RTNA_Init_MIPI_DSI();
	//lcm_init();
#endif
}


//============================================================================//
void RTNA_LCD_RGB_Test(void)
{
#if (ENABLE_LCD_TEST_PATTERN)
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

