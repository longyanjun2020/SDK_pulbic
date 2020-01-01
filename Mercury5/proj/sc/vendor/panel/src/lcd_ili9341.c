//==============================================================================
//
//  File        : lcd_ili9341.c
//  Description : ILI9341 LCD Panel Control Function
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

#define LCD_ILI9341_WIDTH           (240)
#define LCD_ILI9341_HEIGHT          (320)

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	// Panel basic setting
	LCD_ILI9341_WIDTH, LCD_ILI9341_HEIGHT,
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
	0x00/*RGB_D24BIT_RGB888*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

	{0}
};

#define ENABLE_LCD_ILI9341_LOG      (0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN 	(1)
#else
#define ENABLE_LCD_TEST_PATTERN 	(0)
#endif

typedef enum _LCDDIR{ //For compiler
	UPLEFT_DOWNRIGHT = 0,
	DOWNLEFT_UPRIGHT,
	UPRIGHT_DOWNLEFT,
	DOWNRIGHT_UPLEFT
}LCDDIR;

#define Write_COMMAND16i(index)     MMPF_LCD_Write16BitCmd(&m_PanelAttr, index)
#define Write_DATA16i(command)      MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | command)

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

	m_PanelAttr.usDotClkRatio 	= 18;

	m_PanelAttr.usHBPorch 		= 7;
	m_PanelAttr.usHBlanking 	= 10;
	m_PanelAttr.usHSyncW 		= 2;
	m_PanelAttr.usVBPorch 		= 1;
	m_PanelAttr.usVBlanking 	= 5;
	m_PanelAttr.usVSyncW 		= 2;
	m_PanelAttr.usPRT2HdotClk 	= 2;

	m_PanelAttr.bDeltaRBG 		= MMP_TRUE;
	m_PanelAttr.bDummyRBG 		= MMP_FALSE;
	m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

    // RGB SPI interface
	m_PanelAttr.usSpi2MciRatio 	= 0x0F;
	m_PanelAttr.usCsSetupCyc 	= 0x0B;
	m_PanelAttr.usCsHoldCyc 	= 0x0B;
	m_PanelAttr.usCsHighWidth 	= 0xFF;
	m_PanelAttr.usSPIRegBitCnt  = SPI_PANEL_9BITS;

	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
	m_PanelAttr.usWinW 			= LCD_ILI9341_WIDTH;
	m_PanelAttr.usWinH 			= LCD_ILI9341_HEIGHT;

	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 		= 0x03000000;

	MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)

#endif
}

void RTNA_LCD_Init(void)
{
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9341 ...\r\n");

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif

	Write_COMMAND16i(0x01);
	RTNA_WAIT_MS(50);

    Write_COMMAND16i(0xCF);
    Write_DATA16i (0x00);
    Write_DATA16i (0xAA);
    Write_DATA16i (0x30);
    Write_COMMAND16i(0xED);
    Write_DATA16i (0x64);
    Write_DATA16i (0x03);
    Write_DATA16i (0x12);
    Write_DATA16i (0x81);
    Write_COMMAND16i(0xE8);
    Write_DATA16i (0x85);
    Write_DATA16i (0x00);
    Write_DATA16i (0x78);
    Write_COMMAND16i(0xCB);
    Write_DATA16i (0x39);
    Write_DATA16i (0x2C);
    Write_DATA16i (0x00);
    Write_DATA16i (0x34);
    Write_DATA16i (0x02);
    Write_COMMAND16i(0xF7);
    Write_DATA16i (0x20);
    Write_COMMAND16i(0xEA);
    Write_DATA16i (0x00);
    Write_DATA16i (0x00);
    Write_COMMAND16i(0xC0); //Power control
    Write_DATA16i (0x1D); //VRH[5:0]
    Write_COMMAND16i(0xC1); //Power control
    Write_DATA16i (0x13); //SAP[2:0];BT[3:0]
    Write_COMMAND16i(0xC5); //VCM control
    Write_DATA16i (0x30);
    Write_DATA16i (0x3F);
    Write_COMMAND16i(0xC7); //VCM control
    Write_DATA16i (0xB5);
    Write_COMMAND16i(0x3A); // Memory Access Control
    Write_DATA16i (0x55);//Write_DATA16i (0x55);//
    Write_COMMAND16i(0x36); // Memory Access Control
    Write_DATA16i (0x40);

    //[
    Write_COMMAND16i(0xB0); // Display Function Control
    Write_DATA16i (0xE0);//sync mode
    //Write_DATA16i (0xC0);//DE mode
    //]
    Write_COMMAND16i(0xB1);
    Write_DATA16i (0x00);
    Write_DATA16i (0x17);
    //[add

    Write_COMMAND16i(0xB5); // Display Function Control
    Write_DATA16i (0x02);//0x02  VFP
    Write_DATA16i (0x02);//0x02  VBP

    Write_DATA16i (0x09);//0x09
    Write_DATA16i (0x15);//0x15

    Write_COMMAND16i(0xF6); // Display Function Control
    Write_DATA16i (0x01);
    Write_DATA16i (0x00);
    Write_DATA16i (0x07);//Write_DATA16i (0x07);
    //]
    Write_COMMAND16i(0xB6); // Display Function Control
    Write_DATA16i (0x32);
    Write_DATA16i (0x02);

    Write_COMMAND16i(0xF2); // 3Gamma Function Disable
    Write_DATA16i (0x00);
    Write_COMMAND16i(0x26); //Gamma curve selected
    Write_DATA16i (0x01);
    Write_COMMAND16i(0xE0); //Set Gamma
    Write_DATA16i (0x0F);
    Write_DATA16i (0x12);
    Write_DATA16i (0x19);
    Write_DATA16i (0x0B);
    Write_DATA16i (0x0A);
    Write_DATA16i (0x18);
    Write_DATA16i (0x46);
    Write_DATA16i (0xB8);
    Write_DATA16i (0x34);
    Write_DATA16i (0x07);
    Write_DATA16i (0x0A);
    Write_DATA16i (0x00);
    Write_DATA16i (0x00);
    Write_DATA16i (0x07);
    Write_DATA16i (0x00);
    Write_COMMAND16i(0xE1); //Set Gamma
    Write_DATA16i (0x00);
    Write_DATA16i (0x23);
    Write_DATA16i (0x26);
    Write_DATA16i (0x04);
    Write_DATA16i (0x10);
    Write_DATA16i (0x07);
    Write_DATA16i (0x39);
    Write_DATA16i (0x47);
    Write_DATA16i (0x4B);
    Write_DATA16i (0x08);
    Write_DATA16i (0x15);
    Write_DATA16i (0x0F);
    Write_DATA16i (0x3F);
    Write_DATA16i (0x38);
    Write_DATA16i (0x0F);

    Write_COMMAND16i(0x21); 
    Write_COMMAND16i(0x11); //Exit Sleep
    LCD_WAIT(120);
    Write_COMMAND16i(0x29); //Display on
}

void RTNA_LCD_RGB_Test(void)
{
#if (ENABLE_LCD_TEST_PATTERN)
	#if defined(LCD_GPIO_BACK_LIGHT)
		/* Force turn-on LCD backlight */
		if (LCD_GPIO_BACK_LIGHT != MMP_GPIO_MAX)
		{
			MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
			RTNA_DBG_Str(0, "dbg-set LCD_BL to output mode\r\n");

			MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
			Delayms(20);
			RTNA_DBG_Str(0, "dbg-set LCD_BL to low\r\n");

			MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
			Delayms(20);
			RTNA_DBG_Str(0, "dbg-set LCD_BL to high\r\n");
		}
	#endif

	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
//TODO
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
//TODO
}

void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value)
{
//TODO
}

void RTNA_LCD_AdjustBrightness(MMP_UBYTE level)
{
//TODO
}

void RTNA_LCD_AdjustBrightness_R(MMP_UBYTE level)
{
//TODO
}

void RTNA_LCD_AdjustBrightness_B(MMP_UBYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast(MMP_UBYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast_R(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast_B(MMP_BYTE level)
{
//TODO
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

