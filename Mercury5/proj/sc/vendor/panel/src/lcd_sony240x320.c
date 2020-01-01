//==============================================================================
//
//  File        : lcd_sony240x320.h
//  Description : SONY 240x320 LCD Panel Control Function
//  Author      : Philip Lin
//  Revision    : 1.1
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lcd_common.h"
#include "lcd_sony240x320.h"
#include "halPnl.h"


//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define SECONDARY_DISPLAY		(0)

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	240,
	320,
	LCD_TYPE_PLCD,
	LCD_PRM_CONTROLER,
	0,
	LCD_RATIO_4_3,

	NULL,
	NULL,

	LCD_BUS_WIDTH_16,
	LCD_PHASE1,
	LCD_POLARITY1,
    LCD_MCU_80SYS,		//ubMCUSystem
    0,					//usRsLeadCsCnt
	1,
	7,
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

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

static void LcdSony240x320InitIndexCmd(MMP_UBYTE ubController)
{
	DSPY_DECL;
	
	if (ubController == LCD_PRM_CONTROLER)
	{
		#ifdef LCD_ROTATE_180
	    DSPY_WR_W(LCD_AUTO_TX_0,        0x00000200);
	    DSPY_WR_W(LCD_AUTO_TX_1,               239);
	    DSPY_WR_W(LCD_AUTO_TX_2,        0x00000201);
	    DSPY_WR_W(LCD_AUTO_TX_3,               319);
		#else
	    DSPY_WR_W(DSPY_LCD_TX_0,        0x00000200);
	    DSPY_WR_W(DSPY_LCD_TX_1,                 0);
	    DSPY_WR_W(DSPY_LCD_TX_2,        0x00000201);
	    DSPY_WR_W(DSPY_LCD_TX_3,                 0);
		#endif

	    DSPY_WR_W(DSPY_LCD_TX_4,        0x00000202 );
	    DSPY_WR_W(DSPY_LCD_AUTO_CFG,    LCD_TX_TYPE_IDX(0) |
	                                     LCD_TX_TYPE_CMD(1) |
	                                     LCD_TX_TYPE_IDX(2) |
	                                     LCD_TX_TYPE_CMD(3) |
	                                     LCD_TX_TYPE_IDX(4) |
	                                     0);
	                                     
	    DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 5 );
    }
    else
    {
    	//TBD
	}
}

void RTNA_LCD_InitMainLCD(void)
{
	MMPF_PANEL_ATTR panelAttr;

	panelAttr.usPanelW 		= 240;
	panelAttr.usPanelH 		= 320;
	panelAttr.ubDevType 	= LCD_TYPE_PLCD;
	panelAttr.ubController	= LCD_PRM_CONTROLER;
	panelAttr.ulBgColor		= 0;
	panelAttr.ubRatio		= LCD_RATIO_4_3;
	
	panelAttr.pInitSeq		= LcdSony240x320InitSeq;
	panelAttr.pIdxCmdSeq    = LcdSony240x320InitIndexCmd;
	
	panelAttr.ubBusWidth	= LCD_BUS_WIDTH_16;
	panelAttr.ubPhase		= LCD_PHASE1;
	panelAttr.ubPolarity	= LCD_POLARITY1;
	panelAttr.ubMCUSystem	= LCD_MCU_80SYS;
	panelAttr.usRsLeadCsCnt	= 0;
	panelAttr.usCsLeadRwCnt	= 1;
	panelAttr.usRwCycCnt	= 7;
	panelAttr.ubRgbOrder	= LCD_RGB_ORDER_RGB;
	
	panelAttr.ubDispWinId	= LCD_DISP_WIN_PIP;
	panelAttr.usWinStX		= 0;
	panelAttr.usWinStY		= 0;
	panelAttr.usWinW		= 240;
	panelAttr.usWinH		= 320;
	panelAttr.usWinBPP		= 2;
	panelAttr.usWinFmt		= LCD_WIN_FMT_16BPP;
	panelAttr.ulWinAddr		= 0x01500000;
	
	m_PanelAttr = panelAttr;

	MMPF_LCD_InitPanel(&panelAttr);
}

void RTNA_LCD_Init2ndLCD(void)
{
	MMPF_PANEL_ATTR panelAttr;

	panelAttr.usPanelW 		= 240;
	panelAttr.usPanelH 		= 320;
	panelAttr.ubDevType 	= LCD_TYPE_PLCD;
	panelAttr.ubController	= LCD_SCD_CONTROLER;
	panelAttr.ulBgColor		= 0;
	
	panelAttr.pInitSeq		= LcdSony240x320InitSeq;
	panelAttr.pIdxCmdSeq    = LcdSony240x320InitIndexCmd;
	
	panelAttr.ubBusWidth	= LCD_BUS_WIDTH_16;
	panelAttr.ubPhase		= LCD_PHASE1;
	panelAttr.ubPolarity	= LCD_POLARITY1;
	panelAttr.ubMCUSystem	= LCD_MCU_80SYS;
	panelAttr.usRsLeadCsCnt	= 0;
	panelAttr.usCsLeadRwCnt	= 1;
	panelAttr.usRwCycCnt	= 7;
	panelAttr.ubRgbOrder	= LCD_RGB_ORDER_RGB;
	
	panelAttr.ubDispWinId	= LCD_DISP_WIN_OSD;
	panelAttr.usWinStX		= 0;
	panelAttr.usWinStY		= 0;
	panelAttr.usWinW		= 240;
	panelAttr.usWinH		= 320;
	panelAttr.usWinBPP		= 2;
	panelAttr.usWinFmt		= LCD_WIN_FMT_16BPP;
	panelAttr.ulWinAddr		= 0x01500000;
	
	m_PanelAttr = panelAttr;
	
	MMPF_LCD_InitPanel(&panelAttr);
}

void RTNA_LCD_Init(void)
{
    #if (SECONDARY_DISPLAY == 1)  
    RTNA_LCD_Init2ndLCD();   
    #else 
    RTNA_LCD_InitMainLCD();
    #endif
}

void RTNA_LCD_RGB_Test(void)
{
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
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

MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void)
{
	return &m_PanelAttr;
}

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

