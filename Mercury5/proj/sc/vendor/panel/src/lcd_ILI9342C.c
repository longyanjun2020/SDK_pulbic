//==============================================================================
//
//  File        : lcd_ILI9342C.c
//  Description : 320x480 LCD Panel Control Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "Customer_config.h"
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

#define LCD_ILI9342C_WIDTH          (320)
#define LCD_ILI9342C_HEIGHT         (240)

static MMPF_PANEL_ATTR m_PanelAttr = {
	// Panel basic setting
    LCD_ILI9342C_WIDTH, LCD_ILI9342C_HEIGHT,
    LCD_TYPE_RGBLCD,
    LCD_PRM_CONTROLER,
    0,

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
    LCD_SIG_POLARITY_H,
    LCD_SIG_POLARITY_L,
    LCD_SIG_POLARITY_L,
    0x00/*RGB_D24BIT_RGB888*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

    {0}
};

#define ENABLE_LCD_ILI9342C_LOG 	(0)

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

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

	m_PanelAttr.usDotClkRatio   = 14;
	
	m_PanelAttr.usHBPorch       = 7;
	m_PanelAttr.usHBlanking     = 10;
	m_PanelAttr.usHSyncW        = 2;
	m_PanelAttr.usVBPorch       = 2;
	m_PanelAttr.usVBlanking     = 5;
	m_PanelAttr.usVSyncW        = 1;
	m_PanelAttr.usPRT2HdotClk   = 2;

	m_PanelAttr.bDeltaRBG       = MMP_TRUE;
	m_PanelAttr.bDummyRBG       = MMP_FALSE;
	m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

    // RGB SPI interface
	m_PanelAttr.usSpi2MciRatio  = 0x0F;
	m_PanelAttr.usCsSetupCyc    = 0x0B;
	m_PanelAttr.usCsHoldCyc     = 0x0B;
	m_PanelAttr.usCsHighWidth   = 0xFF;
	m_PanelAttr.usSPIRegBitCnt  = SPI_PANEL_9BITS;

	m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX        = 0;
	m_PanelAttr.usWinStY        = 0;
	m_PanelAttr.usWinW          = LCD_ILI9342C_WIDTH;
	m_PanelAttr.usWinH          = LCD_ILI9342C_HEIGHT;

	m_PanelAttr.usWinBPP        = 2;
	m_PanelAttr.usWinFmt        = LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr       = 0x03000000;

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
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9342C ...\r\n");

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC8);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0xFF);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x93);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x42);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x36);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x08);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x3A);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x55);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB4);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x02);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB0);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0xE0);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB5);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x02);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x02);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x09);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x15);
		
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xF6);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x01);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x00);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x07);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB4);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x02);
	
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC0);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC1);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x07);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC5);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0xDA);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xE0);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x00);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x05);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x08);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x02);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x1A);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0C);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x42);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x7A);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x54);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x08);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0D);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0C);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x23);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x25);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xE1);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x00);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x29);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x2F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x03);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x05);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x42);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x55);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x53);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x06);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0C);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x38);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x3A);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x0F);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x11);     //Exit Sleep
	LCD_WAIT(200);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | 0x29);     //Display on
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
    MMP_UBYTE value;
#if 0
    RTNA_DBG_Str(0,"RTNA_LCD_Direction, dir:");
    RTNA_DBG_Short(0,dir);
    RTNA_DBG_Str(0,"\r\n");
#endif

    switch(dir)
    {
        case DOWNLEFT_UPRIGHT:
            value = 0x98;
            break;
        case UPRIGHT_DOWNLEFT:
            value = 0x4C;  
            break;
        case DOWNRIGHT_UPLEFT:
            value = 0x08;//0xDC
            break;
        case UPLEFT_DOWNRIGHT:
        default:
            value = 0xDC;//0x08
            break;
    }

    RTNA_LCD_SetReg(0x36, value);
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, reg);    
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x100 | value);    
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

