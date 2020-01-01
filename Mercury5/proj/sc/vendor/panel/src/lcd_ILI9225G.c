//==============================================================================
//
//  File        : lcd_ILI9486L.c
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

#define SECONDARY_DISPLAY 		(0)

#define ENABLE_LCD_ILI9225G_LOG (0)




static MMPF_PANEL_ATTR m_PanelAttr = {
        176, 220,
        LCD_TYPE_PLCD,
        LCD_PRM_CONTROLER,
        0,
        #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
        LCD_RATIO_16_9,
        #else
        LCD_RATIO_4_3,
        #endif
        NULL, NULL,
        LCD_BUS_WIDTH_16,
    LCD_BGR565,			//ubBusCfg
        LCD_PHASE1,
        LCD_POLARITY1,
        LCD_MCU_80SYS,
        30,
        20,
        50,
        LCD_RGB_ORDER_RGB,

    // RGB interface
    MMP_FALSE,				//bPartialDisp
    LCD_SIG_POLARITY_L,     // DCLK Polarity
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
    LCD_SIG_POLARITY_H,     // V-Sync Polarity
    0x02/*RGB_D24BIT_RGB565*/,	//ubRgbFmt
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

    {0}
};


//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

    m_PanelAttr.usPanelW      = 176;
    m_PanelAttr.usPanelH      = 220;


	m_PanelAttr.ubDevType 	= LCD_TYPE_PLCD;

	m_PanelAttr.ubController 	= LCD_PRM_CONTROLER;
	m_PanelAttr.ulBgColor 	= 0;
    #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    m_PanelAttr.ubRatio         = LCD_RATIO_16_9;
    #else
    m_PanelAttr.ubRatio         = LCD_RATIO_4_3;
    #endif

	m_PanelAttr.pInitSeq 		= NULL;
	m_PanelAttr.pIdxCmdSeq 	= 	NULL;;

	m_PanelAttr.ubBusWidth 	= LCD_BUS_WIDTH_16;
	m_PanelAttr.ubPhase 		= LCD_PHASE1;
	m_PanelAttr.ubPolarity 	= LCD_POLARITY1;
	m_PanelAttr.ubMCUSystem 	= LCD_MCU_80SYS;
	m_PanelAttr.usRsLeadCsCnt = 30;
	m_PanelAttr.usCsLeadRwCnt = 20;
	m_PanelAttr.usRwCycCnt 	= 50;
	m_PanelAttr.ubRgbOrder 	= LCD_RGB_ORDER_BGR;

	m_PanelAttr.ubRgbFmt      = 0x0A/*RGB_D24BIT_BGR565*/;

	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;

	m_PanelAttr.usWinW 		= 176;
	m_PanelAttr.usWinH 		= 220;

#endif
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 	= 0x01500000;

	MMPF_LCD_InitPanel(&m_PanelAttr);

}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)


	m_PanelAttr.usPanelW 		= 240;
	m_PanelAttr.usPanelH 		= 320;
	m_PanelAttr.ubDevType 	= LCD_TYPE_PLCD;
	m_PanelAttr.ubController 	= LCD_SCD_CONTROLER;
	m_PanelAttr.ulBgColor 	= 0;
	
	m_PanelAttr.pInitSeq 		= NULL;
	m_PanelAttr.pIdxCmdSeq 	= NULL;

	m_PanelAttr.ubBusWidth 	= LCD_BUS_WIDTH_16;
	m_PanelAttr.ubPhase 		= LCD_PHASE1;
	m_PanelAttr.ubPolarity 	= LCD_POLARITY1;
	m_PanelAttr.ubMCUSystem 	= LCD_MCU_80SYS;
	m_PanelAttr.usRsLeadCsCnt = 0;
	m_PanelAttr.usCsLeadRwCnt = 1;
	m_PanelAttr.usRwCycCnt 	= 7;
	m_PanelAttr.ubRgbOrder 	= LCD_RGB_ORDER_RGB;

	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_OSD;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
	m_PanelAttr.usWinW 		= 320;
	m_PanelAttr.usWinH 		= 480;
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 	= 0x02500000;


	MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

void RTNA_LCD_Init(void)
{
//DSPY_DECL;
    extern MMPF_PANEL_ATTR m_PanelAttr;

    //MMP_SHORT i, j;
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9225G ...\r\n");

/* LCD Power On (ex: LCD_CE pin connects to A83's PCGPIO30 (GPIO62)) */
#if defined(LCD_GPIO_ENABLE)
	if (LCD_GPIO_ENABLE != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(LCD_GPIO_ENABLE, MMP_TRUE, MMP_TRUE);
		MMPF_OS_Sleep_MS(100);
		//RTNA_DBG_Str(0, "dbg-set LCD_CE to output mode\r\n");

		MMPF_PIO_SetData(LCD_GPIO_ENABLE, LCD_GPIO_ENABLE_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(10);
		//RTNA_DBG_Str(0, "dbg-set LCD_CE to high\r\n");
	}
#endif

/* LCD HW Reset (ex: LCD_RST pin connects to A83's PCGPIO29 (GPIO61)) */
#if defined(LCD_GPIO_RESET)
	if (LCD_GPIO_RESET != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(LCD_GPIO_RESET, MMP_TRUE, MMP_TRUE);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to output mode\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(1);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(10);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(120);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
	}
#endif

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();   
#else
	RTNA_LCD_InitMainLCD();
#endif
	MAINLCD_CMD(0x00d0);        MAINLCD_DATA(0X0003);
	MAINLCD_CMD(0x00eb);        MAINLCD_DATA(0X0b00);
	MAINLCD_CMD(0x00ec);        MAINLCD_DATA(0X004f);


	MAINLCD_CMD(0x0001);        MAINLCD_DATA(0X011C);
	MAINLCD_CMD(0x0002);        MAINLCD_DATA(0X0100);
	MAINLCD_CMD(0x0003);        MAINLCD_DATA(0X1030);
	MAINLCD_CMD(0x0008);        MAINLCD_DATA(0X0808);
	MAINLCD_CMD(0x000C);        MAINLCD_DATA(0x0000);
	MAINLCD_CMD(0x000F);        MAINLCD_DATA(0x0c01);

	MMPF_OS_Sleep_MS(0X50);
	MAINLCD_CMD(0x0010);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0011);        MAINLCD_DATA(0X1B41);
	MMPF_OS_Sleep_MS(0X50);
	MAINLCD_CMD(0x0012);        MAINLCD_DATA(0X200E);
	MAINLCD_CMD(0x0013);        MAINLCD_DATA(0X0064);
	MAINLCD_CMD(0x0014);        MAINLCD_DATA(0X4b50);

	MAINLCD_CMD(0x0030);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0031);        MAINLCD_DATA(0X00DB);
	MAINLCD_CMD(0x0032);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0033);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0034);        MAINLCD_DATA(0X00DB);
	MAINLCD_CMD(0x0035);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0036);        MAINLCD_DATA(0X00AF);
	MAINLCD_CMD(0x0037);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0038);        MAINLCD_DATA(0X00DB);
	MAINLCD_CMD(0x0039);        MAINLCD_DATA(0X0000);

	MAINLCD_CMD(0x0050);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0051);        MAINLCD_DATA(0X0502);
	MAINLCD_CMD(0x0052);        MAINLCD_DATA(0X0a04);
	MAINLCD_CMD(0x0053);        MAINLCD_DATA(0X0406);
	MAINLCD_CMD(0x0054);        MAINLCD_DATA(0X040a);
	MAINLCD_CMD(0x0055);        MAINLCD_DATA(0X0205);
	MAINLCD_CMD(0x0056);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0057);        MAINLCD_DATA(0X0604);
	MAINLCD_CMD(0x0058);        MAINLCD_DATA(0X0700);
	MAINLCD_CMD(0x0059);        MAINLCD_DATA(0X0007);
	MMPF_OS_Sleep_MS(0X50);
	MAINLCD_CMD(0x0020);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0021);        MAINLCD_DATA(0X0000);
	MAINLCD_CMD(0x0007);        MAINLCD_DATA(0X1017);
	MMPF_OS_Sleep_MS(0X96);
	MAINLCD_CMD(0x0022);
}
void RTNA_LCD_RGB_Test(void)
{
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);

#if (ENABLE_LCD_ILI9225G_LOG)
	RTNA_DBG_Str(0, "dbg-ILI9486L-RTNA_LCD_RGB_Test\r\n");
	RTNA_LCD_Backlight(MMP_TRUE);
	RTNA_DBG_Str(0, "dbg-ILI9486L LCD backlight On\r\n");
	MMPF_OS_Sleep_MS(2000);
	RTNA_LCD_Backlight(MMP_FALSE);
	RTNA_DBG_Str(0, "dbg-ILI9486L LCD backlight Off\r\n");
	MMPF_OS_Sleep_MS(2000);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
#if 0
	DSPY_DECL;
	MMP_USHORT value = 0x04 << 8;

	RTNA_DBG_Str(0, "RTNA_LCD_Direction, dir:");
	RTNA_DBG_Short(0, dir);
	RTNA_DBG_Str(0, "\r\n");

	switch (dir)
	{
		case LCD_DIR_DOWNLEFT_UPRIGHT: // 1
			return;
			break;

		case LCD_DIR_UPRIGHT_DOWNLEFT: // 2
			return;
			break;

		case LCD_DIR_DOWNRIGHT_UPLEFT: // 3
		#if (LCD_RGB_MODE == STRIP_RGB)
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE, RGB_DUMMY_MODE_ENABLE |
											RGB_DELTA_MODE_ENABLE |
											SPI_ODD_LINE_RGB |
											SPI_EVEN_LINE_RGB);
		#else
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE,	RGB_DELTA_MODE_ENABLE | SPI_ODD_LINE_RBG | SPI_EVEN_LINE_BGR);
		#endif
			value |= (0x0C | 0x00);
			break;

		case LCD_DIR_UPLEFT_DOWNRIGHT: // 0
		#if (LCD_RGB_MODE == STRIP_RGB)
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE, RGB_DUMMY_MODE_ENABLE |
											RGB_DELTA_MODE_ENABLE |
											SPI_ODD_LINE_RGB |
											SPI_EVEN_LINE_RGB);
		#else
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE, RGB_DELTA_MODE_ENABLE | SPI_ODD_LINE_RGB | SPI_EVEN_LINE_GBR);
		#endif
			value |= (0x0C | 0x03);
			break;

		default:
			return;
			break;
    }

	MMPF_LCD_Write16BitCmd(&m_PanelAttr, value);
#endif
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{

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

