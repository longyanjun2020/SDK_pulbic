//==============================================================================
//
//  File        : lcd_st7789s.h
//  Description : 320 x 240 LCD Panel Control Function
//  Author      : 
//  Revision    : 1.1
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

#define SECONDARY_DISPLAY		(0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN (1)
#else
#define ENABLE_LCD_TEST_PATTERN (0)
#endif

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
#define PANEL_WIDTH             (320)
#define PANEL_HEIGHT			(240)
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define PANEL_WIDTH             (240)
#define PANEL_HEIGHT			(320)            
#endif

//==============================================================================
//
//
//
//==============================================================================
static void Lcdst7789sInitIndexCmd(MMP_UBYTE ubController);
static void Lcdst7789sInitSeq(void);

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	PANEL_WIDTH,
	PANEL_HEIGHT,
	LCD_TYPE_PLCD_FLM,
	LCD_PRM_CONTROLER,
	0,
#if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
	LCD_RATIO_16_9,
#else
	LCD_RATIO_4_3,
#endif

	Lcdst7789sInitSeq,
	Lcdst7789sInitIndexCmd,

    LCD_BUS_WIDTH_8,	//ubBusWidth
    LCD_BGR565,			//ubBusCfg
	LCD_PHASE1,
	LCD_POLARITY1,
    LCD_MCU_80SYS,		//ubMCUSystem
	1,
	1,
	10,
    LCD_RGB_ORDER_RGB,	//ubRgbOrder

    // RGB interface
    MMP_FALSE,				//bPartialDisp
	LCD_SIG_POLARITY_H,
	LCD_SIG_POLARITY_L,
	LCD_SIG_POLARITY_L,
	0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect
	{0}
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

static void Lcdst7789sInitIndexCmd(MMP_UBYTE ubController)
{
	DSPY_DECL;

	if (ubController == LCD_PRM_CONTROLER)
	{
		DSPY_WR_W(DSPY_LCD_TX_0,         0x2C);
		DSPY_WR_W(DSPY_LCD_AUTO_CFG,     LCD_TX_TYPE_IDX(0));
		DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 1);
	}
}

static void Lcdst7789sInitSeq(void)
{
#if defined(FAT_BOOT) || defined (MBOOT_FW)
	RTNA_DBG_Str(0, "### RTNA_LCD_Lcdst7789s InitSeq ...\r\n");

    #if defined(LCD_GPIO_RESET)
	if (LCD_GPIO_RESET != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(LCD_GPIO_RESET, MMP_TRUE, MMP_TRUE);
		RTNA_DBG_Str(0, "dbg-set LCD_RST to output mode\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		LCD_WAIT(2);
		RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		LCD_WAIT(10);
		RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

		MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		LCD_WAIT(50);
		RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
	}
    #endif

    // ============ CR On =============
    MAINLCD_CMD(0x11);  
	LCD_WAIT(120);
//-------------Display and color format setting----	
	MAINLCD_CMD(0x36);
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
    MAINLCD_DATA(0xA8); //   0x68
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    MAINLCD_DATA(0x00);
#endif
	MAINLCD_CMD(0x3a);
    MAINLCD_DATA(0x55);    
 //----------ST7789S Frame rate setting----   
	MAINLCD_CMD(0xb2);
    MAINLCD_DATA(0x08);    
    MAINLCD_DATA(0x08);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x22);    
    MAINLCD_DATA(0x22);    

	MAINLCD_CMD(0xb7);
    MAINLCD_DATA(0x35);    
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
	MAINLCD_CMD(0x2A);
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x01);    
    MAINLCD_DATA(0x3F);    

	MAINLCD_CMD(0x2B);
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0xEF);   
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
	MAINLCD_CMD(0x2A);
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0xEF);    

	MAINLCD_CMD(0x2B);
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x01);    
    MAINLCD_DATA(0x3F); 
#endif
//----------ST7789S Power setting--------
	MAINLCD_CMD(0xbb);
    MAINLCD_DATA(0x27);    

	MAINLCD_CMD(0xc0);
    MAINLCD_DATA(0x2c);    

	MAINLCD_CMD(0xc2);
    MAINLCD_DATA(0x01);    

	MAINLCD_CMD(0xc3);
    MAINLCD_DATA(0x0b);    

	MAINLCD_CMD(0xc4);
    MAINLCD_DATA(0x20);    

	MAINLCD_CMD(0xc6);
    MAINLCD_DATA(0x0f);    

	MAINLCD_CMD(0xd0);
    MAINLCD_DATA(0xa4);    
    MAINLCD_DATA(0xa1);    
     MAINLCD_CMD(0x35);
     MAINLCD_DATA(0x00);	
//-----------ST7789S gamma setting--------
	MAINLCD_CMD(0xe0);
    MAINLCD_DATA(0xd0);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x02);    
    MAINLCD_DATA(0x07);    
    MAINLCD_DATA(0x07);    
    MAINLCD_DATA(0x19);    
    MAINLCD_DATA(0x2e);    
    MAINLCD_DATA(0x54);    
    MAINLCD_DATA(0x41);    
    MAINLCD_DATA(0x2d);    
    MAINLCD_DATA(0x17);    
    MAINLCD_DATA(0x18);    
    MAINLCD_DATA(0x14);    
    MAINLCD_DATA(0x18);  
	
	MAINLCD_CMD(0xe1);
    MAINLCD_DATA(0xd0);    
    MAINLCD_DATA(0x00);    
    MAINLCD_DATA(0x02);    
    MAINLCD_DATA(0x07);    
    MAINLCD_DATA(0x04);    
    MAINLCD_DATA(0x24);    
    MAINLCD_DATA(0x2c);    
    MAINLCD_DATA(0x44);    
    MAINLCD_DATA(0x42);    
    MAINLCD_DATA(0x1c);    
    MAINLCD_DATA(0x1a);    
    MAINLCD_DATA(0x17);    
    MAINLCD_DATA(0x15);    
    MAINLCD_DATA(0x18);  

	MAINLCD_CMD(0x29);
	LCD_WAIT(100);

	MAINLCD_CMD(0x2c);
	LCD_WAIT(100);
	#endif
}

void RTNA_LCD_InitMainLCD(void)
{
	m_PanelAttr.ubDispWinId		= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX		= 0;
	m_PanelAttr.usWinStY		= 0;
	m_PanelAttr.usWinW			= PANEL_WIDTH;
	m_PanelAttr.usWinH			= PANEL_HEIGHT;
	m_PanelAttr.usWinBPP		= 2;
	m_PanelAttr.usWinFmt		= LCD_WIN_FMT_8BPP;
	m_PanelAttr.ulWinAddr		= 0x03000000;
	#ifdef FLM_GPIO_NUM
	m_PanelAttr.ulFLMGPIO		= FLM_GPIO_NUM;
	#else
	m_PanelAttr.ulFLMGPIO		= MMP_GPIO_MAX;
	#endif
	m_PanelAttr.ubPlcdFmt     	= PLCD_RGB565_BUS8;

	MMPF_LCD_InitPanel(&m_PanelAttr);
}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)

#endif

}

void RTNA_LCD_Init(void)
{
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ST7789S 320x240 ...\r\n");

    #if (SECONDARY_DISPLAY == 1)  
    RTNA_LCD_Init2ndLCD();   
    #else 
    RTNA_LCD_InitMainLCD();
    #endif
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
#if 0
    	{
    		int i, j;
    		
    		for (j = 0; j <80; j++) {
    			for (i = 0; i < 320; i++) {
    				MAINLCD_DATA(0xF8);
    				MAINLCD_DATA(0x00);
    			}
    		}

    		for (; j < 160; j++) {
    			for (i = 0; i < 320; i++) {
    				MAINLCD_DATA(0x07);
    				MAINLCD_DATA(0xE0);
    			}
    		}
    		
    		for (; j < 240; j++) {
    			for (i = 0; i < 320; i++) {
    				MAINLCD_DATA(0x00);
    				MAINLCD_DATA(0x1F);
    			}
    		}
    	}
		RTNA_DBG_Str(0, "wait panel draw \r\n");
		Delayms(10000);
        #endif	
		MMPF_LCD_DrawTestPattern(&m_PanelAttr);
#endif	
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
	DSPY_DECL;
	MMP_UBYTE value;

	switch(dir)
	{
		case LCD_DIR_DOWNLEFT_UPRIGHT:
			// not support;
			break;

		case LCD_DIR_UPRIGHT_DOWNLEFT:
			// not support;
			break;

		case LCD_DIR_DOWNRIGHT_UPLEFT:
		    RTNA_DBG_Str(0, FG_BLUE("LCD-ROTATE\r\n"));
			value = 0x00;
			break;

		case LCD_DIR_UPLEFT_DOWNRIGHT:
		    RTNA_DBG_Str(0, FG_BLUE("LCD-NORMAL\r\n"));
			value = 0xC0;
			break;

		default:
			break;
	}

#if (defined(FAT_BOOT) || defined(MBOOT_FW))
//	MAINLCD_CMD(0x36);
//	MAINLCD_DATA(value);
#else
    {
        OS_CRITICAL_INIT();
        OS_ENTER_CRITICAL();
        while (DSPY_RD_W(DSPY_CTL_0) & LCD_FRAME_TX);
    	MAINLCD_CMD(0x36);
    	MAINLCD_DATA(value);
    	MAINLCD_CMD(0x2C);
    	OS_EXIT_CRITICAL();
    }
#endif
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


