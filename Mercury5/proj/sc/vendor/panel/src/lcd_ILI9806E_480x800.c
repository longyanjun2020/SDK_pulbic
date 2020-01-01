//==============================================================================
//
//  File        : lcd_ILI9806E.c
//  Description : 480x800 LCD Panel Control Function
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
#define  GBL_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  GBL_GET_B(reg)         MMPH_HIF_RegGetB(reg)

#define  LCD_GET_W(reg)         MMPH_HIF_RegGetW(reg)
#define  LCD_GET_B(reg)         MMPH_HIF_RegGetB(reg)
#define  LCD_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  LCD_SET_W(reg, val)    MMPH_HIF_RegSetW(reg, val)
#define  LCD_SET_D(reg, val)    MMPH_HIF_RegSetL(reg, val)

#define Delayms(t) 				MMPF_OS_Sleep_MS(t)
#define W_C(d)                  Write_COMMAND16i(d)
#define W_D(d)                  Write_DATA16i(d)

#define SECONDARY_DISPLAY       (0)

#define ENABLE_LCD_ILI9806E_LOG  (1)

#define PANEL_WIDTH                 480
#define PANEL_HEIGHT                800

#if (LCD_IF == LCD_IF_PARALLEL)
static MMPF_PANEL_ATTR m_PanelAttr = {
        };
#elif (LCD_IF == LCD_IF_RGB)
static MMPF_PANEL_ATTR m_PanelAttr = {
        PANEL_WIDTH, PANEL_HEIGHT,

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
        0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect
        {0}};
#endif
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
void Write_COMMAND16i(MMP_USHORT d)
{
    DSPY_DECL;
    DSPY_WR_W(DSPY_LCD_TX_0, d);
    DSPY_WR_B(DSPY_CTL_0, LCD_IDX_RDY);
    while(DSPY_RD_B(DSPY_CTL_0) & LCD_IDX_RDY);
}

void Write_DATA16i(MMP_USHORT d)
{
    DSPY_DECL;
    DSPY_WR_W(DSPY_LCD_TX_0, d | 0x0100);
    DSPY_WR_B(DSPY_CTL_0, LCD_IDX_RDY);
    while(DSPY_RD_B(DSPY_CTL_0) & LCD_IDX_RDY);
}

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

#if (LCD_IF == LCD_IF_PARALLEL)

#elif (LCD_IF == LCD_IF_RGB)
	m_PanelAttr.usDotClkRatio 	= 5;    // DCLK = 166MHz / usDotClkRatio
	m_PanelAttr.usHBPorch 		= 48;
	m_PanelAttr.usHBlanking 	= 88;
	m_PanelAttr.usHSyncW 		= 48;
	m_PanelAttr.usVBPorch 		= 12;
	m_PanelAttr.usVBlanking 	= 32;
	m_PanelAttr.usVSyncW 		= 3;
	m_PanelAttr.usPRT2HdotClk = 2;      // Unit:Dot Clock, Range:0~255

	m_PanelAttr.bDeltaRBG = MMP_FALSE;
	m_PanelAttr.bDummyRBG = MMP_FALSE;
	m_PanelAttr.ubEvenLnOrder = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder  = LCD_SPI_PIX_ORDER_RGB;

    // RGB SPI interface
	m_PanelAttr.usSpi2MciRatio 	= 0x80;
	m_PanelAttr.usCsSetupCyc 	= 0x0F;
	m_PanelAttr.usCsHoldCyc 	= 0x0F;
	m_PanelAttr.usCsHighWidth 	= 0xFF;
	m_PanelAttr.usSPIRegBitCnt  = SPI_PANEL_9BITS;
    ///////
#endif
	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
	m_PanelAttr.usWinW          = PANEL_WIDTH;
	m_PanelAttr.usWinH          = PANEL_HEIGHT;
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 		= 0x01500000;

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
#if (LCD_IF == LCD_IF_PARALLEL)
#elif (LCD_IF == LCD_IF_RGB)
    extern MMPF_PANEL_ATTR m_PanelAttr;

    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9806E RGB...\r\n");
    /* LCD Power On */
    #if 0//defined(LCD_GPIO_ENABLE)
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

    /* LCD HW Reset (LCD_RST pin connects to A83's PCGPIO29 (GPIO61)) */
    #if defined(LCD_GPIO_RESET)
        if (LCD_GPIO_RESET != MMP_GPIO_MAX)
        {
            MMPF_PIO_EnableOutputMode(LCD_GPIO_RESET, MMP_TRUE, MMP_TRUE);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to output mode\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(2);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(11);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(120);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
        }
    #endif

   #if (SECONDARY_DISPLAY == 1)
       RTNA_LCD_Init2ndLCD();
   #else
       RTNA_LCD_InitMainLCD();
   #endif

   //****************************************************************************//
   //****************************** Page 1 Command ******************************//
   //****************************************************************************//
   W_C(0XFF); W_D(0XFF); W_D(0X98); W_D(0X06); W_D(0X04); W_D(0X01);	 // Change to Page 1
   
   W_C(0X08); W_D(0X10);				 // output SDA
   W_C(0X21); W_D(0X01);				 // DE = 1 Active
   W_C(0X22); W_D(0X08);				 // BGR
   W_C(0X30); W_D(0X02);				 // 480 X 800
   W_C(0X31); W_D(0X00);				 // 2-dot Inversion
   
   
   W_C(0X40); W_D(0X16);				// BT  +2.5/-3 pump for DDVDH-L
   W_C(0X41); W_D(0X33);				 // DVDDH DVDDL clamp  
   W_C(0X42); W_D(0X11);				// VGH/VGL 
   W_C(0X43); W_D(0X05);				//	
   W_C(0X44); W_D(0X0B);				 // VGH/VGL 
   W_C(0X45); W_D(0X1B);				// VGH/VGL=1B 
   W_C(0X50); W_D(0X78);				 // VGMP  78 
   W_C(0X51); W_D(0X78);				 // VGMN  78
   W_C(0X52); W_D(0X00);				   //Flicker
   W_C(0X53); W_D(0X40);				   //Flicker  
   W_C(0X54); W_D(0X00);				   //Flicker
   W_C(0X55); W_D(0X40);				   //Flicker 
   W_C(0X57); W_D(0X50);				 
   W_C(0X60); W_D(0X07);				 // SDTI
   W_C(0X61); W_D(0X00);			   // CRTI
   W_C(0X62); W_D(0X07);				// EQTI
   W_C(0X63); W_D(0X00);			  // PCTI
   
   
   
   //++++++++++++++++++ Gamma Setting ++++++++++++++++++//
   
   W_C(0XA0); W_D(0X00);  // Gamma 255	
   W_C(0XA1); W_D(0X0b);  // Gamma 251	
   W_C(0XA2); W_D(0X12);  // Gamma 247 
   W_C(0XA3); W_D(0X0c);  // Gamma 239
   W_C(0XA4); W_D(0X05);  // Gamma 231	
   W_C(0XA5); W_D(0X0c);  // Gamma 203	 
   W_C(0XA6); W_D(0X07);  // Gamma 175	
   W_C(0XA7); W_D(0X16);  // Gamma 147	
   W_C(0XA8); W_D(0X06);  // Gamma 108	 
   W_C(0XA9); W_D(0X0a);  // Gamma 80 
   W_C(0XAA); W_D(0X0F);  // Gamma 52	
   W_C(0XAB); W_D(0X06);  // Gamma 24
   W_C(0XAC); W_D(0X0e);  // Gamma 16	
   W_C(0XAD); W_D(0X1a);  // Gamma 8   
   W_C(0XAE); W_D(0X12);  // Gamma 4   
   W_C(0XAF); W_D(0X00);  // Gamma 0
   
   ///==============Nagitive
   W_C(0XC0); W_D(0X00);  // Gamma 255	
   W_C(0XC1); W_D(0X0b);  // Gamma 251	
   W_C(0XC2); W_D(0X12);  // Gamma 247 
   W_C(0XC3); W_D(0X0c);  // Gamma 239
   W_C(0XC4); W_D(0X05);  // Gamma 231	
   W_C(0XC5); W_D(0X0c);  // Gamma 203	 
   W_C(0XC6); W_D(0X07);  // Gamma 175	
   W_C(0XC7); W_D(0X16);  // Gamma 147	
   W_C(0XC8); W_D(0X06);  // Gamma 108	 
   W_C(0XC9); W_D(0X0a);  // Gamma 80 
   W_C(0XCA); W_D(0X0F);  // Gamma 52	
   W_C(0XCB); W_D(0X06);  // Gamma 24
   W_C(0XCC); W_D(0X0e);  // Gamma 16	
   W_C(0XCD); W_D(0X1a);  // Gamma 8   
   W_C(0XCE); W_D(0X12);  // Gamma 4   
   W_C(0XCF); W_D(0X00);  // Gamma 0
   
   
   //****************************************************************************//
   //****************************** Page 6 Command ******************************//
   //****************************************************************************//
   W_C(0XFF); W_D(0XFF); W_D(0X98); W_D(0X06); W_D(0X04); W_D(0X06);	 // Change to Page 6
   
   W_C(0X00); W_D(0XA0);  //1
   W_C(0X01); W_D(0X05);  //2
   W_C(0X02); W_D(0X00);  //3  
   W_C(0X03); W_D(0X00);  //4
   W_C(0X04); W_D(0X01);  //5
   W_C(0X05); W_D(0X01);  //6
   W_C(0X06); W_D(0X88);  //7  
   W_C(0X07); W_D(0X04);  //8
   W_C(0X08); W_D(0X01);
   W_C(0X09); W_D(0X90);	
   W_C(0X0A); W_D(0X04);	
   W_C(0X0B); W_D(0X01);	
   W_C(0X0C); W_D(0X01);
   W_C(0X0D); W_D(0X01);
   W_C(0X0E); W_D(0X00);
   W_C(0X0F); W_D(0X00);
   W_C(0X10); W_D(0X55);
   W_C(0X11); W_D(0X50);
   W_C(0X12); W_D(0X01);
   W_C(0X13); W_D(0X85);
   W_C(0X14); W_D(0X85);
   W_C(0X15); W_D(0XC0);
   W_C(0X16); W_D(0X0B);
   W_C(0X17); W_D(0X00);
   W_C(0X18); W_D(0X00);
   W_C(0X19); W_D(0X00);
   W_C(0X1A); W_D(0X00);
   W_C(0X1B); W_D(0X00);
   W_C(0X1C); W_D(0X00);
   W_C(0X1D); W_D(0X00);
   
   
   W_C(0X20); W_D(0X01);
   W_C(0X21); W_D(0X23);
   W_C(0X22); W_D(0X45);
   W_C(0X23); W_D(0X67);
   W_C(0X24); W_D(0X01);
   W_C(0X25); W_D(0X23);
   W_C(0X26); W_D(0X45);
   W_C(0X27); W_D(0X67);
   
   
   W_C(0X30); W_D(0X02);
   W_C(0X31); W_D(0X22);
   W_C(0X32); W_D(0X11);
   W_C(0X33); W_D(0XAA);
   W_C(0X34); W_D(0XBB);
   W_C(0X35); W_D(0X66);
   W_C(0X36); W_D(0X00);
   W_C(0X37); W_D(0X22);
   W_C(0X38); W_D(0X22);
   W_C(0X39); W_D(0X22);
   W_C(0X3A); W_D(0X22);
   W_C(0X3B); W_D(0X22);
   W_C(0X3C); W_D(0X22);
   W_C(0X3D); W_D(0X22);
   W_C(0X3E); W_D(0X22);
   W_C(0X3F); W_D(0X22);
   W_C(0X40); W_D(0X22);
   W_C(0X52); W_D(0X10);
   W_C(0X53); W_D(0X10);
   
   
   //****************************************************************************//
   //****************************** Page 7 Command ******************************//
   //****************************************************************************//
   
   W_C(0XFF); W_D(0XFF); W_D(0X98); W_D(0X06); W_D(0X04); W_D(0X07);	 // Change to Page 7
   
   W_C(0X17); W_D(0X22);
   W_C(0X02); W_D(0X77);
   W_C(0XE1); W_D(0X79);
   
   
   
   //****************************************************************************//
   //****************************** Page 0 Command ******************************//
   //****************************************************************************//
   
   W_C(0XFF); W_D(0XFF); W_D(0X98); W_D(0X06); W_D(0X04); W_D(0X00);	 // Change to Page 0
   W_C(0X3A); W_D(0X77);				 // 0X77=24BIT
   W_C(0X36); W_D(0X03);				 // ·´É¨
   W_C(0X21); W_D(0X00);
   W_C(0X11); W_D(0X00);				 // Sleep-Out
   Delayms(150);
   W_C(0X29); W_D(0X00);				 // Display On
   Delayms(10);

#endif

    if(LCD_GPIO_BACK_LIGHT != MMP_GPIO_MAX)
    {
        MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_FALSE); // 1. Set LCD_GPIO_BACK_LIGHT output enable
        RTNA_DBG_Str(0, "dbg-set LCD_BL to output mode\r\n");

        MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 2. LCD_GPIO_BACK_LIGHT pull low
        Delayms(20);
        RTNA_DBG_Str(0, "dbg-set LCD_BL to low\r\n");

        MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 3. LCD_GPIO_BACK_LIGHT pull high
        Delayms(20);
        RTNA_DBG_Str(0, "dbg-set LCD_BL to high\r\n");
    }

}
void RTNA_LCD_RGB_Test(void)
{
#if (ENABLE_LCD_ILI9806E_LOG)
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
	RTNA_DBG_Str(0, "dbg-ILI9806E-RTNA_LCD_RGB_Test\r\n");
	RTNA_LCD_Backlight(MMP_TRUE);
	RTNA_DBG_Str(0, "dbg-ILI9806E LCD backlight On\r\n");
	MMPF_OS_Sleep_MS(5000);
	RTNA_LCD_Backlight(MMP_FALSE);
	RTNA_DBG_Str(0, "dbg-ILI9806E LCD backlight Off\r\n");
	MMPF_OS_Sleep_MS(1000);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{

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

