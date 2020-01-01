//==============================================================================
//
//  File        : lcd_HST430BL_480x272.c
//  Description : HST 4"3 480x272 DE only RGB LCD Panel Control Function
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
#include "halPnl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define Delayms(t) 					LCD_WAIT(t)

#define SECONDARY_DISPLAY 			(0)

#define PANEL_WIDTH                 480
#define PANEL_HEIGHT                854

#define LSCE_GPIO_PIN   (MMP_GPIO124)
#define LSCK_GPIO_PIN   (MMP_GPIO122)
#define LSDA_GPIO_PIN   (MMP_GPIO123)
#define LSDR_GPIO_PIN   (MMP_GPIO62)

#define Delay_us(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.udelay(n))
#define Delay_ms(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.mdelay(n))

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
	LCD_SIG_POLARITY_H,     // DCLK Polarity
	LCD_SIG_POLARITY_L,     // H-Sync Polarity
	LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x02/*RGB_D24BIT_RGB565*/,	//ubRgbFmt
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

	{0}
};

#define ENABLE_LCD_LOG       		(0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN 	(1)
#else
#define ENABLE_LCD_TEST_PATTERN 	(0)
#endif

#if (ENABLE_LCD_LOG)
#define LCD_DBG_LEVEL               (0)
#else
#define LCD_DBG_LEVEL               (3)
#endif

static void Set_RST(unsigned long index)
{
	if(index) MMPF_PIO_SetData(LSDR_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x8000;
	else      MMPF_PIO_SetData(LSDR_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x8000;	
}

static void Set_2805_CS(unsigned long index)
{
	if(index) MMPF_PIO_SetData(LSCE_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x8000;
	else       MMPF_PIO_SetData(LSCE_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x8000;	
}

static void Set_SCL(unsigned long index)
{
	if(index) MMPF_PIO_SetData(LSCK_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x2000;
	else       MMPF_PIO_SetData(LSCK_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x2000;	
}

static void Set_SDI(unsigned long index)
{
	if(index) MMPF_PIO_SetData(LSDA_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x1000;
	else      MMPF_PIO_SetData(LSDA_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x1000;	
}


static void SPI_Init(void)
{
	
	
	MMPF_PIO_EnableOutputMode(LSCE_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSCK_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSDA_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSDR_GPIO_PIN, MMP_TRUE, MMP_TRUE);

	Set_RST(0);
	Delay_ms(100);
	Set_RST(1);

	Set_2805_CS(1);
	//Set_CSX(1);
	Set_SCL(1);	
	Set_SDI(1);
	
}

static void SPI_3W_wrByte(unsigned char cmd)
{
	unsigned long kk;	


	Set_SCL(0);
	for(kk=0;kk<8;kk++)
	{
		if(cmd&0x80) Set_SDI(1);
		else         Set_SDI(0);
    	cmd<<=1;
		Set_SCL(0);	Delay_us(5);
	
		Set_SCL(1);	Delay_us(5);
	//	cmd = cmd<<1;	
	}
}

static void SPI_9608_wrAddr(unsigned short addr)
{
	Set_2805_CS(0);
	//SPI_3W_wrByte(0x20);
	//SPI_3W_wrByte(addr>>8);

	//SPI_3W_wrByte(0x00);
	Set_SCL(0);
    Set_SDI(0);
    Delay_us(5);
    Set_SCL(1);	
    Delay_us(5);
	SPI_3W_wrByte(addr);
	Set_2805_CS(1);	
}

static void SPI_9608_wrPara(unsigned char value)
{
	Set_2805_CS(0);
	//SPI_3W_wrByte(0x40);	//Write D[7]~D[0]
	Set_SCL(0);
    Set_SDI(1);
    Delay_us(5);
    Set_SCL(1);	
    Delay_us(5);
	SPI_3W_wrByte(value);
	Set_2805_CS(1);
}

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - lcd_HST430BL_480x854~~~\r\n");

	m_PanelAttr.usDotClkRatio 	= 5;//10;   // 166MHz / Divder

	// RGB interface
	m_PanelAttr.usHBPorch 		= 48;
	m_PanelAttr.usHBlanking 	= 88;
	m_PanelAttr.usHSyncW 		= 48;
	m_PanelAttr.usVBPorch 		= 12;
	m_PanelAttr.usVBlanking 	= 32;
	m_PanelAttr.usVSyncW 		= 3;
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

void RTNA_LCD_Init(void)
{
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ParallelRGB565 480x854 @@\r\n");

	/* LCD Power On */                                                                                                
#if defined(LCD_GPIO_ENABLE)
	if (LCD_GPIO_ENABLE != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(LCD_GPIO_ENABLE, MMP_TRUE, MMP_TRUE);
		MMPF_OS_Sleep_MS(100);
		RTNA_DBG_Str(0, "dbg-set LCD_CE to output mode\r\n");

		MMPF_PIO_SetData(LCD_GPIO_ENABLE, LCD_GPIO_ENABLE_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(10);
		RTNA_DBG_Str(0, "dbg-set LCD_CE to high\r\n");
	}
#endif
	//if (LCD_GPIO_ENABLE != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(MMP_GPIO60, MMP_TRUE, MMP_TRUE);
		MMPF_OS_Sleep_MS(100);
		RTNA_DBG_Str(0, "dbg-set LCD_CE to output mode\r\n");

		MMPF_PIO_SetData(MMP_GPIO60, LCD_GPIO_ENABLE_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(10);
		RTNA_DBG_Str(0, "dbg-set LCD_CE to high\r\n");
	}

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif
	SPI_Init();
	Delay_ms(10);
    RTNA_DBG_Str(0, "TEST======================================================2=LCD\r\n");
    //**********
SPI_9608_wrAddr(0xFF);SPI_9608_wrPara(0xFF);
SPI_9608_wrPara(0x98);SPI_9608_wrPara(0x06);
SPI_9608_wrPara(0x04);SPI_9608_wrPara(0x00);     // Change to Page 0
Delay_us(10);
SPI_9608_wrAddr(0x28);SPI_9608_wrPara(0x00);                 // Sleep-Out
Delay_us(120);
SPI_9608_wrAddr(0x10);SPI_9608_wrPara(0x00);                 // Display on
Delay_us(10);

//********************************************************************//
//****************************** Page 1 Command 
//********************************************************************//
SPI_9608_wrAddr(0xFF);SPI_9608_wrPara(0xFF);
SPI_9608_wrPara(0x98);SPI_9608_wrPara(0x06);
SPI_9608_wrPara(0x04);SPI_9608_wrPara(0x01);     // Change to Page 1
Delay_us(10);
SPI_9608_wrAddr(0x08);SPI_9608_wrPara(0x10);                 // output SDA
Delay_us(10);
SPI_9608_wrAddr(0x21);SPI_9608_wrPara(0x01);                 // DE = 1 Active
Delay_us(10);
SPI_9608_wrAddr(0x30);SPI_9608_wrPara(0x01);                 // 480 X 854
Delay_us(10);
SPI_9608_wrAddr(0x31);SPI_9608_wrPara(0x00);                 // 2 dot
Delay_us(10);
SPI_9608_wrAddr(0x40);SPI_9608_wrPara(0x16);                // BT  
Delay_us(10);
SPI_9608_wrAddr(0x41);SPI_9608_wrPara(0x33);                 // DVDDH DVDDL clamp 
Delay_us(10);
SPI_9608_wrAddr(0x42);SPI_9608_wrPara(0x03);                 // VGH/VGL 
Delay_us(10);
SPI_9608_wrAddr(0x43);SPI_9608_wrPara(0x09);                  // VGH_CLAMP 0FF ;
Delay_us(10);
SPI_9608_wrAddr(0x44);SPI_9608_wrPara(0x07);                  // VGL_CLAMP OFF ; 
Delay_us(10);
SPI_9608_wrAddr(0x45);SPI_9608_wrPara(0x16);                  // VGL_REG  -11V 
Delay_us(10);
SPI_9608_wrAddr(0x50);SPI_9608_wrPara(0x78);                    
Delay_us(10);
SPI_9608_wrAddr(0x51);SPI_9608_wrPara(0x78);                    
Delay_us(10);
SPI_9608_wrAddr(0x52);SPI_9608_wrPara(0x00);                    //Flicker
Delay_us(10);
SPI_9608_wrAddr(0x53);SPI_9608_wrPara(0x4A);                    //Flicker
Delay_us(10);
SPI_9608_wrAddr(0x57);SPI_9608_wrPara(0x50);                    //Low voltage detect
Delay_us(10);
SPI_9608_wrAddr(0x60);SPI_9608_wrPara(0x07);                  // SDTI
Delay_us(10);
SPI_9608_wrAddr(0x61);SPI_9608_wrPara(0x00);                 // CRTI
Delay_us(10);
SPI_9608_wrAddr(0x62);SPI_9608_wrPara(0x08);                  // EQTI
Delay_us(10);
SPI_9608_wrAddr(0x63);SPI_9608_wrPara(0x00);                 // PCTI
Delay_us(10);
//++++++++++++++++++ Gamma Setting ++++++++++++++++++//

SPI_9608_wrAddr(0xA0);SPI_9608_wrPara(0x00);   // Gamma 255 
Delay_us(10);
SPI_9608_wrAddr(0xA1);SPI_9608_wrPara(0x09);   // Gamma 251 
Delay_us(10);
SPI_9608_wrAddr(0xA2);SPI_9608_wrPara(0x0F);   // Gamma 247
Delay_us(10);
SPI_9608_wrAddr(0xA3);SPI_9608_wrPara(0x0B);   // Gamma 239
Delay_us(10);
SPI_9608_wrAddr(0xA4);SPI_9608_wrPara(0x06);   // Gamma 231
Delay_us(10);
SPI_9608_wrAddr(0xA5);SPI_9608_wrPara(0x09);   // Gamma 203
Delay_us(10);
SPI_9608_wrAddr(0xA6);SPI_9608_wrPara(0x07);   // Gamma 175
Delay_us(10);
SPI_9608_wrAddr(0xA7);SPI_9608_wrPara(0x05);   // Gamma 147
Delay_us(10);
SPI_9608_wrAddr(0xA8);SPI_9608_wrPara(0x08);   // Gamma 108
Delay_us(10);
SPI_9608_wrAddr(0xA9);SPI_9608_wrPara(0x0C);   // Gamma 80
Delay_us(10);
SPI_9608_wrAddr(0xAA);SPI_9608_wrPara(0x12);   // Gamma 52
Delay_us(10);
SPI_9608_wrAddr(0xAB);SPI_9608_wrPara(0x08);   // Gamma 24
Delay_us(10);
SPI_9608_wrAddr(0xAC);SPI_9608_wrPara(0x0D);   // Gamma 16
Delay_us(10);
SPI_9608_wrAddr(0xAD);SPI_9608_wrPara(0x17);   // Gamma 8
Delay_us(10);
SPI_9608_wrAddr(0xAE);SPI_9608_wrPara(0x0E);   // Gamma 4
Delay_us(10);
SPI_9608_wrAddr(0xAF);SPI_9608_wrPara(0x00);   // Gamma 0
Delay_us(10);
///==============Nagitive
SPI_9608_wrAddr(0xC0);SPI_9608_wrPara(0x00);   // Gamma 255 
Delay_us(10);
SPI_9608_wrAddr(0xC1);SPI_9608_wrPara(0x08);   // Gamma 251
Delay_us(10);
SPI_9608_wrAddr(0xC2);SPI_9608_wrPara(0x0E);   // Gamma 247
Delay_us(10);
SPI_9608_wrAddr(0xC3);SPI_9608_wrPara(0x0B);   // Gamma 239
Delay_us(10);
SPI_9608_wrAddr(0xC4);SPI_9608_wrPara(0x05);   // Gamma 231
Delay_us(10);
SPI_9608_wrAddr(0xC5);SPI_9608_wrPara(0x09);   // Gamma 203
Delay_us(10);
SPI_9608_wrAddr(0xC6);SPI_9608_wrPara(0x07);   // Gamma 175
Delay_us(10);
SPI_9608_wrAddr(0xC7);SPI_9608_wrPara(0x04);   // Gamma 147
Delay_us(10);
SPI_9608_wrAddr(0xC8);SPI_9608_wrPara(0x08);   // Gamma 108
Delay_us(10);
SPI_9608_wrAddr(0xC9);SPI_9608_wrPara(0x0C);   // Gamma 80
Delay_us(10);
SPI_9608_wrAddr(0xCA);SPI_9608_wrPara(0x11);   // Gamma 52
Delay_us(10);
SPI_9608_wrAddr(0xCB);SPI_9608_wrPara(0x07);   // Gamma 24
Delay_us(10);
SPI_9608_wrAddr(0xCC);SPI_9608_wrPara(0x0D);   // Gamma 16
Delay_us(10);
SPI_9608_wrAddr(0xCD);SPI_9608_wrPara(0x17);   // Gamma 8
Delay_us(10);
SPI_9608_wrAddr(0xCE);SPI_9608_wrPara(0x0E);   // Gamma 4
Delay_us(10);
SPI_9608_wrAddr(0xCF);SPI_9608_wrPara(0x00);   // Gamma 0
Delay_us(10);



//****************************************************************************//
//****************************** Page 6 Command ******************************//
//****************************************************************************//
SPI_9608_wrAddr(0xFF);SPI_9608_wrPara(0xFF);
SPI_9608_wrPara(0x98);SPI_9608_wrPara(0x06);
SPI_9608_wrPara(0x04);SPI_9608_wrPara(0x06);      // Change to Page 6
Delay_us(10);
SPI_9608_wrAddr(0x00);SPI_9608_wrPara(0x21); 
Delay_us(10);
SPI_9608_wrAddr(0x01);SPI_9608_wrPara(0x0A); 
Delay_us(10);
SPI_9608_wrAddr(0x02);SPI_9608_wrPara(0x00);    
Delay_us(10);
SPI_9608_wrAddr(0x03);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x04);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x05);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x06);SPI_9608_wrPara(0x80);     
Delay_us(10);
SPI_9608_wrAddr(0x07);SPI_9608_wrPara(0x06); 
Delay_us(10);
SPI_9608_wrAddr(0x08);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x09);SPI_9608_wrPara(0x80);     
Delay_us(10);
SPI_9608_wrAddr(0x0A);SPI_9608_wrPara(0x00);     
Delay_us(10);
SPI_9608_wrAddr(0x0B);SPI_9608_wrPara(0x00);     
Delay_us(10);
SPI_9608_wrAddr(0x0C);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x0D);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x0E);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x0F);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x10);SPI_9608_wrPara(0xF0); 
Delay_us(10);
SPI_9608_wrAddr(0x11);SPI_9608_wrPara(0xF4); 
Delay_us(10);
SPI_9608_wrAddr(0x12);SPI_9608_wrPara(0x04); 
Delay_us(10);
SPI_9608_wrAddr(0x13);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x14);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x15);SPI_9608_wrPara(0xC0); 
Delay_us(10);
SPI_9608_wrAddr(0x16);SPI_9608_wrPara(0x08); 
Delay_us(10);
SPI_9608_wrAddr(0x17);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x18);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x19);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x1A);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x1B);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x1C);SPI_9608_wrPara(0x00); 
Delay_us(10);
SPI_9608_wrAddr(0x1D);SPI_9608_wrPara(0x00); 
Delay_us(10);

SPI_9608_wrAddr(0x20);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x21);SPI_9608_wrPara(0x23); 
Delay_us(10);
SPI_9608_wrAddr(0x22);SPI_9608_wrPara(0x45); 
Delay_us(10);
SPI_9608_wrAddr(0x23);SPI_9608_wrPara(0x67); 
Delay_us(10);
SPI_9608_wrAddr(0x24);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x25);SPI_9608_wrPara(0x23); 
Delay_us(10);
SPI_9608_wrAddr(0x26);SPI_9608_wrPara(0x45); 
Delay_us(10);
SPI_9608_wrAddr(0x27);SPI_9608_wrPara(0x67); 
Delay_us(10);

SPI_9608_wrAddr(0x30);SPI_9608_wrPara(0x01); 
Delay_us(10);
SPI_9608_wrAddr(0x31);SPI_9608_wrPara(0x11); 	//GOUT1
Delay_us(10);
SPI_9608_wrAddr(0x32);SPI_9608_wrPara(0x00); 	//GOUT2
Delay_us(10);
SPI_9608_wrAddr(0x33);SPI_9608_wrPara(0xEE); 	//GOUT3
Delay_us(10);
SPI_9608_wrAddr(0x34);SPI_9608_wrPara(0xFF); 	//GOUT4
Delay_us(10);
SPI_9608_wrAddr(0x35);SPI_9608_wrPara(0xBB); 	//GOUT5
Delay_us(10);
SPI_9608_wrAddr(0x36);SPI_9608_wrPara(0xCA); 	//GOUT6
Delay_us(10);
SPI_9608_wrAddr(0x37);SPI_9608_wrPara(0xDD); 	//GOUT7
Delay_us(10);
SPI_9608_wrAddr(0x38);SPI_9608_wrPara(0xAC); 	//GOUT8
Delay_us(10);
SPI_9608_wrAddr(0x39);SPI_9608_wrPara(0x76); 	//GOUT9
Delay_us(10);	
SPI_9608_wrAddr(0x3A);SPI_9608_wrPara(0x67); 	//GOUT10
Delay_us(10);
SPI_9608_wrAddr(0x3B);SPI_9608_wrPara(0x22); 	//GOUT11
Delay_us(10);
SPI_9608_wrAddr(0x3C);SPI_9608_wrPara(0x22); 	//GOUT12
Delay_us(10);
SPI_9608_wrAddr(0x3D);SPI_9608_wrPara(0x22); 	//GOUT13
Delay_us(10);
SPI_9608_wrAddr(0x3E);SPI_9608_wrPara(0x22); 	//GOUT14
Delay_us(10);
SPI_9608_wrAddr(0x3F);SPI_9608_wrPara(0x22); 
Delay_us(10);
SPI_9608_wrAddr(0x40);SPI_9608_wrPara(0x22); 
Delay_us(10);

SPI_9608_wrAddr(0x52);SPI_9608_wrPara(0x10); 
Delay_us(10);
SPI_9608_wrAddr(0x53);SPI_9608_wrPara(0x10);        //12:VGLO tie VGL_REG; 10: VGLO tie VGL
Delay_us(10);

//****************************************************************************//
//****************************** Page 7 Command ******************************//
//****************************************************************************//
SPI_9608_wrAddr(0xFF);SPI_9608_wrPara(0xFF);
SPI_9608_wrPara(0x98);SPI_9608_wrPara(0x06);
SPI_9608_wrPara(0x04);SPI_9608_wrPara(0x07);      // Change to Page 7
Delay_us(10);
SPI_9608_wrAddr(0x17);SPI_9608_wrPara(0x22);   // VGL_REG ON
Delay_us(10);
SPI_9608_wrAddr(0x02);SPI_9608_wrPara(0x77);   // 
Delay_us(10);
SPI_9608_wrAddr(0x06);SPI_9608_wrPara(0x13);   //
Delay_us(10);
SPI_9608_wrAddr(0xE1);SPI_9608_wrPara(0x79);   // 
Delay_us(10);
//****************************************************************************//

SPI_9608_wrAddr(0xFF);SPI_9608_wrPara(0xFF);
SPI_9608_wrPara(0x98);SPI_9608_wrPara(0x06);
SPI_9608_wrPara(0x04);SPI_9608_wrPara(0x00);      // Change to Page 0
Delay_us(10);
SPI_9608_wrAddr(0x36);SPI_9608_wrPara(0x08);                  // ¡MA¡P????I??E?
Delay_us(120);
SPI_9608_wrAddr(0x11);SPI_9608_wrPara(0x00);                  // Sleep-Out
Delay_us(120);
SPI_9608_wrAddr(0x29);SPI_9608_wrPara(0x00);                  // Display on
Delay_us(10);
SPI_9608_wrAddr(0x35);SPI_9608_wrPara(0x00);                  // TE ON

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

