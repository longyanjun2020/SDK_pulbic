//==============================================================================
//
//  File        : lcd_OTA5182A.c
//  Description : OTA5182A LCD Panel Control Function
//  Author      : Philip Lin
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

#define Delayms(t)				LCD_WAIT(t)

#define OTA5182_VERSION 		(4)

#define SECONDARY_DISPLAY		(0)

#define PANEL_WIDTH             (320)
#define PANEL_HEIGHT            (240)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN (1)
#else
#define ENABLE_LCD_TEST_PATTERN (0)
#endif

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	PANEL_WIDTH, 
	PANEL_HEIGHT, 
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

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
    #if defined(_5182A_C3_)
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_InitMainLCD - OTA5182A-C3\r\n"));
    #elif defined(_5182A_C2_)
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_InitMainLCD - OTA5182A-C2\r\n"));
    #else
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_InitMainLCD - OTA5182A\r\n"));
    #endif
        
	m_PanelAttr.usDotClkRatio	= 11;  // 7;
	#ifdef _5182A_C3_
	m_PanelAttr.usHBPorch		= 0x3C;
	#else
	m_PanelAttr.usHBPorch		= 0x3F;
	#endif
	m_PanelAttr.usHBlanking	    = 0x46;
	m_PanelAttr.usHSyncW		= 0;
	#ifdef _5182A_C3_
	m_PanelAttr.usVBPorch		= 22;
	m_PanelAttr.usVBlanking	    = 32;
	#else
	m_PanelAttr.usVBPorch		= 13;
	m_PanelAttr.usVBlanking	    = 22;
	#endif
	m_PanelAttr.usVSyncW		= 0;
	m_PanelAttr.usPRT2HdotClk	= 2;
	
	m_PanelAttr.bDeltaRBG		= MMP_TRUE;
	m_PanelAttr.bDummyRBG		= MMP_TRUE;
	m_PanelAttr.ubEvenLnOrder	= LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder	= LCD_SPI_PIX_ORDER_RGB;
	
	m_PanelAttr.usSpi2MciRatio  = 0x80;
	m_PanelAttr.usCsSetupCyc	= 0x0F;
	m_PanelAttr.usCsHoldCyc	    = 0x0F;
	m_PanelAttr.usCsHighWidth	= 0xFF;
	m_PanelAttr.usSPIRegBitCnt  = SPI_PANEL_16BITS;

	m_PanelAttr.ubDispWinId	    = LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX		= 0;
	m_PanelAttr.usWinStY		= 0;
	m_PanelAttr.usWinW		    = 160;
	m_PanelAttr.usWinH		    = 240;
	m_PanelAttr.usWinBPP		= 2;
	m_PanelAttr.usWinFmt		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr		= 0x03000000;
	
	MMPF_LCD_InitPanel(&m_PanelAttr);
}

void RTNA_LCD_Init2ndLCD(void)
{
#if SECONDARY_DISPLAY
    #if defined(_5182A_C3_)
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_Init2ndLCD - OTA5182A-C3\r\n"));
    #elif defined(_5182A_C2_)
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_Init2ndLCD - OTA5182A-C2\r\n"));
    #else
    RTNA_DBG_Str(0, FG_GREEN("### RTNA_LCD_Init2ndLCD - OTA5182A\r\n"));
    #endif

	m_PanelAttr.ubController	= LCD_SCD_CONTROLER;
	
	m_PanelAttr.usDotClkRatio	= 7;
	#ifdef _5182A_C3_
	m_PanelAttr.usHBPorch		= 0x3C;
	#else
	m_PanelAttr.usHBPorch		= 0x3F;
	#endif
	m_PanelAttr.usHBlanking	    = 0x46;
	m_PanelAttr.usHSyncW		= 0;
	#ifdef _5182A_C3_
	m_PanelAttr.usVBPorch		= 22;
	m_PanelAttr.usVBlanking	    = 32;
	#else
	m_PanelAttr.usVBPorch		= 13;
	m_PanelAttr.usVBlanking	    = 22;
	#endif
	m_PanelAttr.usVSyncW		= 0;
	m_PanelAttr.usPRT2HdotClk	= 2;
	
	m_PanelAttr.bDeltaRBG		= MMP_TRUE;
	m_PanelAttr.bDummyRBG		= MMP_TRUE;
	m_PanelAttr.ubEvenLnOrder	= LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder	= LCD_SPI_PIX_ORDER_RGB;
	
	m_PanelAttr.usSpi2MciRatio  = 0x80;
	m_PanelAttr.usCsSetupCyc	= 0x0F;
	m_PanelAttr.usCsHoldCyc	    = 0x0F;
	m_PanelAttr.usCsHighWidth	= 0xFF;
	m_PanelAttr.usSPIRegBitCnt  = SPI_PANEL_16BITS;

	m_PanelAttr.ubDispWinId	    = LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX		= 0;
	m_PanelAttr.usWinStY		= 0;
	m_PanelAttr.usWinW		    = 160;
	m_PanelAttr.usWinH		    = 240;
	m_PanelAttr.usWinBPP		= 2;
	m_PanelAttr.usWinFmt		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr		= 0x03000000;
	
	MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

void RTNA_LCD_Init(void)
{
    #if (SECONDARY_DISPLAY == 1)  
    RTNA_LCD_Init2ndLCD();   
    #else 
    RTNA_LCD_InitMainLCD();
    #endif
  	
  	#if defined(_5182A_C2_)
  	/*MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000f); 
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005); 
	Delayms(80); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000f); 
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x5040); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xE013); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x3008); 	// Contrast   bit0~3 (0x0 : 0,   0x8 : 1.0 0xf :1.875
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x7034); 	// Brightness bit0~6 (0x00:-256, 0x40:0,   0x7f:+252)
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x6001);	// 24.54Mhz H:320
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x8010);	// Horizontal Data Start Delay -1
	Delayms(50);*/
#ifdef _5182A_C2_V071	
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000D);   
	Delayms(10); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0005); 
	Delayms(20); 	
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000f);   	
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xc004);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x5043);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x1064);   
	//MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xf546);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x9050);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x8010);
    ///MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x3009); //Contrast
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x4003); 
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x5068); 
    //MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x7043); //Brightness
    //MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x7038);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xC005); 
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xE003);  	
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x6001); 
#else
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000D);   
	Delayms(10); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0005); 
	Delayms(20); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000f);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xc004);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x5043);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x1064);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xf546);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x9050);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x8010);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x6001);
#endif
	#elif defined(_5182A_C3_)
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000d); 
	Delayms(50);  
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005); 
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005); 
	Delayms(100); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000d);
	Delayms(200);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0601); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0600);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x4003);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xa008); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x5068); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xe007); 
	Delayms(50);
  	#else//_5182A_C2_
	#if 0 //Org: Issue: Mesh and Shake
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000D);   
	Delayms(10); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005); 
	Delayms(20); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000F);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC004);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x5043);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1064);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xF546);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x9050);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x8010);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x6001);
	#endif
    #if 1 //New:
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005);   
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000F);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0005); 
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x000F);   
	Delayms(50);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x3009);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x4003);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x5068);   //Fix Issue: Mesh and Shake
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x7043);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xC005);   //Fix Issue: Mesh and Shake
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xE003);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x8010);    //Fix Issue: yellow color.
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x6001);
	#endif
	
	#endif//_5182A_C2_	
}

void RTNA_LCD_BLACK_LIGHT(MMP_BOOL enable)
{
  if(enable)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x7040);
  else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x7000);
}

void RTNA_LCD_RGB_Test(void)
{
#if (ENABLE_LCD_TEST_PATTERN)
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
	if (dir)
		MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x4003);
 	else
		MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x4000);	// Rotate 180
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
	MMP_SHORT Tempvalue;

	#if ((OTA5182_VERSION == 2) || (OTA5182_VERSION == 4))
	Tempvalue = ((reg << 12) + value );	
	#elif ((OTA5182_VERSION == 3))
	Tempvalue = (((reg & 0xff)<< 8) + value );	
	#endif

#if defined(ALL_FW) 
       printc("RTNA_LCD_SetReg: 0x%X\r\n", Tempvalue);
#else
       RTNA_DBG_Str(0, FG_GREEN("RTNA_LCD_SetReg: "));
       RTNA_DBG_Long(0, Tempvalue);
       RTNA_DBG_Str(0, FG_GREEN("\r\n"));
#endif    
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, Tempvalue);	
}

void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value)
{
#if 0
	DSPY_DECL;

    //Not work.  TBD
    DSPY_WR_W(DSPY_LCD_TX_0, (((reg & 0x0F) << 12) | (1<<11)) );
    DSPY_WR_B(DSPY_CTL_0, LCD_PANEL_READ_EN | LCD_IDX_RDY);
    while(DSPY_RD_B(DSPY_CTL_0) & LCD_IDX_RDY); 

    *value = DSPY_RD_B(DSPY_PLCD_READ_PORT);
#endif
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
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, ((0x0A << 10) | (level & 0x3F)));
}

void RTNA_LCD_AdjustContrast_B(MMP_BYTE level)
{
	MMPF_LCD_Write16BitCmd(&m_PanelAttr, ((0x0B << 10) | (level & 0x3F)));
}

MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void)
{
	return &m_PanelAttr;
}

void RTNA_LCD_SOFT_Reset(void)
{

#if( OTA5182_VERSION == 4 )

    // GiantPlus C2 version
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000D);   
	Delayms(10); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0005); 
	Delayms(20); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000f);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xc004);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x5043);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x1064);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xf546);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x9050);

	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x8010);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x6001);    

    return;
#endif

#if( OTA5182_VERSION == 5 )
    // GiantPlus C1 version
    // C1 version is for mass production
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000D);   
	Delayms(10); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0005); 
	Delayms(20); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x000f);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x507C);   
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xF546);   

	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x8010);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x6001); 
    return;
#endif



	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xf546); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x9060); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x5000); 
	Delayms(50); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x8010);	// Horizontal Data Start Delay 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x3008);
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x2003);    // Disable Dithering mode 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x7040); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xC005); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0xE013); 
	MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x6001); 

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

