//==============================================================================
//
//  File        : lcd_480x272.c
//  Description : AUO 4"3 800x480 DE only RGB LCD Panel Control Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "Customer_config.h" // CarDV
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

#define Delayms(t) 					LCD_WAIT(t)

#define SECONDARY_DISPLAY 			(0)

#define PANEL_WIDTH                 (800)
#define PANEL_HEIGHT                (480)



typedef unsigned char u8;
typedef int i32;
typedef unsigned int u32;
#define NULL 0

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
	LCD_BUS_WIDTH_24,
	LCD_BGR565_SWAP,//LCD_RGB888,
    LCD_PHASE0,         //ubPhase
    LCD_POLARITY0,      //ubPolarity
    LCD_MCU_80SYS,      //ubMCUSystem
    0,                  //usRsLeadCsCnt
    0,                  //usCsLeadRwCnt
    0,                  //usRwCycCnt
    LCD_RGB_ORDER_RGB,  //ubRgbOrder

    // RGB interface
    MMP_FALSE,              //bPartialDisp
    LCD_SIG_POLARITY_H,//LCD_SIG_POLARITY_L,     // DCLK Polarity
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
    LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x02, /*RGB_D24BIT_RGB565*/
    LCD_TOP_CLK_MPLL_108M,  //ulClkSelect
    0x0,  //usDotClkRatio
    0x0,  //ulDotClkFreq

    {0}
};

#define ENABLE_LCD_LOG              (1)

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

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - ParallelRGB565 480x272\r\n");

    m_PanelAttr.ulDotClkFreq    = 28000000;

	// RGB interface
    m_PanelAttr.usHBPorch       = 384;
    m_PanelAttr.usHBlanking     = 512;
    m_PanelAttr.usHSyncW        = 10;
    m_PanelAttr.usVBPorch       = 15;
    m_PanelAttr.usVBlanking     = 198;
    m_PanelAttr.usVSyncW        = 5;
    m_PanelAttr.usPRT2HdotClk   = 2;

    m_PanelAttr.bDeltaRBG       = MMP_FALSE;
    m_PanelAttr.bDummyRBG       = MMP_FALSE;

    m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RBG;
    m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RBG;

    // Window setting (For drawing test pattern)
    m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_PIP;
    m_PanelAttr.usWinStX        = 0;
    m_PanelAttr.usWinStY        = 0;
    m_PanelAttr.usWinW          = PANEL_WIDTH;
    m_PanelAttr.usWinH          = PANEL_HEIGHT;
    m_PanelAttr.usWinBPP        = 2;
    m_PanelAttr.usWinFmt        = LCD_WIN_FMT_16BPP;
    m_PanelAttr.ulWinAddr       = 0x03000000;

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
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ParallelRGB565 480x854 @@\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
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

