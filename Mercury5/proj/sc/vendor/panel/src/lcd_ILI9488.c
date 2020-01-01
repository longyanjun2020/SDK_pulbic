//==============================================================================
//
//  File        : lcd_ILI9488.c
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
#define  GBL_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  GBL_GET_B(reg)         MMPH_HIF_RegGetB(reg)

#define  LCD_GET_W(reg)         MMPH_HIF_RegGetW(reg)
#define  LCD_GET_B(reg)         MMPH_HIF_RegGetB(reg)
#define  LCD_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  LCD_SET_W(reg, val)    MMPH_HIF_RegSetW(reg, val)
#define  LCD_SET_D(reg, val)    MMPH_HIF_RegSetL(reg, val)


#define Delayms(t) 				LCD_WAIT(t)

#define SECONDARY_DISPLAY       (0)

#define ENABLE_LCD_ILI9488_LOG  (0)


#if (LCD_IF == LCD_IF_PARALLEL)
static MMPF_PANEL_ATTR m_PanelAttr = {
        };
#elif (LCD_IF == LCD_IF_RGB)
static MMPF_PANEL_ATTR m_PanelAttr = {
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
        480, 320,
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        320, 480,             
#endif
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

#if (LCD_IF == LCD_IF_PARALLEL)
void LCD_ILI9488_CMD(MMP_USHORT d)
{
    MAINLCD_CMD(d);
}

void LCD_ILI9488_INDEX(MMP_USHORT d)
{
    MAINLCD_DATA(d);
}

#elif (LCD_IF == LCD_IF_RGB)
void LCD_ILI9488_CMD(MMP_USHORT d)
{
    Write_COMMAND16i(d);
}

void LCD_ILI9488_INDEX(MMP_USHORT d)
{
    Write_DATA16i(d);
}
#endif


static void LcdILI9488InitIndexCmd(MMP_UBYTE ubController)
{
    DSPY_DECL;

    if (ubController == LCD_PRM_CONTROLER)
    {
        DSPY_WR_W(DSPY_LCD_TX_0,         0x2C);
        DSPY_WR_W(DSPY_LCD_AUTO_CFG,     LCD_TX_TYPE_IDX(0));
        DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 1);
    }
    else
    {
//        DSPY_WR_W(DSPY_SCD_LCD_TX_0,     0x2C);
//        DSPY_WR_W(DSPY_SCD_LCD_AUTO_CFG, LCD_TX_TYPE_IDX(0));
//        DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 1);
    }
}


void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

#if (LCD_IF == LCD_IF_PARALLEL)

#elif (LCD_IF == LCD_IF_RGB)
	m_PanelAttr.usDotClkRatio = 18;      // Stand for [(Lcd Freq / Dot Clock Freq) - 1]
	m_PanelAttr.usHBPorch     = 10;          // Unit:pixel, Ragne:0~1023
	m_PanelAttr.usHBlanking   = 20;        // Unit:pixel, Range:0~1023
	m_PanelAttr.usHSyncW      = 2;           // Unit:pixel, Range:0~255
	m_PanelAttr.usVBPorch     = 5;          // Unit:line,  Range:0~1023
	m_PanelAttr.usVBlanking   = 10;        // Unit:line,  Range:0~1023
	m_PanelAttr.usVSyncW      = 0;           // Unit:line,  Range:0~255
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
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
	m_PanelAttr.usWinW          = 480;
	m_PanelAttr.usWinH          = 320;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
	m_PanelAttr.usWinW          = 320;//480;
	m_PanelAttr.usWinH          = 480;//320;             
#endif
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 		= 0x01500000;

	MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
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
#if (LCD_IF == LCD_IF_PARALLEL)
#elif (LCD_IF == LCD_IF_RGB)
    extern MMPF_PANEL_ATTR m_PanelAttr;

    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9488 RGB...\r\n");
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
    // VCI = 2.8V
    // ************* Reset LCD Driver **************** //
    //  LCD_nRESET = 1;
    //  Delayms(1); // Delay 1ms
    //  LCD_nRESET = 0;
    //  Delayms(10); // Delay 10ms // This delay time is necessary
    //  LCD_nRESET = 1;
    //  Delayms(120); // Delay 100 ms
    // ************* Start Initial Sequence ********** //

//BS 20160323 >> ADD init Code >>    
#if 1
	LCD_ILI9488_CMD(0xE0); //P-Gamma
	LCD_ILI9488_INDEX(0x00);
	LCD_ILI9488_INDEX(0x03);
	LCD_ILI9488_INDEX(0x0C);
	LCD_ILI9488_INDEX(0x09);
	LCD_ILI9488_INDEX(0x17);
	LCD_ILI9488_INDEX(0x09);
	LCD_ILI9488_INDEX(0x3E);
	LCD_ILI9488_INDEX(0x89);
	LCD_ILI9488_INDEX(0x49);
	LCD_ILI9488_INDEX(0x08);
	LCD_ILI9488_INDEX(0x0D);
	LCD_ILI9488_INDEX(0x0A);
	LCD_ILI9488_INDEX(0x13);
	LCD_ILI9488_INDEX(0x15);
	LCD_ILI9488_INDEX(0x0F);
	LCD_ILI9488_CMD(0XE1); //N-Gamma
	LCD_ILI9488_INDEX(0x00);
	LCD_ILI9488_INDEX(0x11);
	LCD_ILI9488_INDEX(0x15);
	LCD_ILI9488_INDEX(0x03);
	LCD_ILI9488_INDEX(0x0F);
	LCD_ILI9488_INDEX(0x05);
	LCD_ILI9488_INDEX(0x2D);
	LCD_ILI9488_INDEX(0x34);
	LCD_ILI9488_INDEX(0x41);
	LCD_ILI9488_INDEX(0x02);
	LCD_ILI9488_INDEX(0x0B);
	LCD_ILI9488_INDEX(0x0A);
	LCD_ILI9488_INDEX(0x33);
	LCD_ILI9488_INDEX(0x37);
	LCD_ILI9488_INDEX(0x0F);
	LCD_ILI9488_CMD(0XC0); //Power Control 1
	LCD_ILI9488_INDEX(0x17); //Vreg1out
	LCD_ILI9488_INDEX(0x15); //Verg2out
	LCD_ILI9488_CMD(0xC1); //Power Control 2
	LCD_ILI9488_INDEX(0x41); //VGH,VGL
	LCD_ILI9488_CMD(0xC5); //Power Control 3
	LCD_ILI9488_INDEX(0x00);
	LCD_ILI9488_INDEX(0x12); //Vcom
	LCD_ILI9488_INDEX(0x80);
	LCD_ILI9488_CMD(0x36); //Memory Access
	LCD_ILI9488_INDEX(0x48);
	LCD_ILI9488_CMD(0x3A); // Interface Pixel Format
	LCD_ILI9488_INDEX(0x66);
	LCD_ILI9488_CMD(0XB0); // Interface Mode Control
	LCD_ILI9488_INDEX(0x00);
	LCD_ILI9488_CMD(0xB1); //Frame rate
	LCD_ILI9488_INDEX(0xA0); //60Hz
	LCD_ILI9488_CMD(0xB4); //Display Inversion Control
	LCD_ILI9488_INDEX(0x02); 
	LCD_ILI9488_CMD(0XB6); //RGB/MCU Interface Control
	LCD_ILI9488_INDEX(0x22); //MCU
	LCD_ILI9488_INDEX(0x02); //Source,Gate scan dieection

	LCD_ILI9488_CMD(0XE9); // Set Image Function
	LCD_ILI9488_INDEX(0x00); // Disable 24 bit data input

	LCD_ILI9488_CMD(0xF7);
	LCD_ILI9488_INDEX(0xA9);
	LCD_ILI9488_INDEX(0x51);
	LCD_ILI9488_INDEX(0x2C);
	LCD_ILI9488_INDEX(0x82);
//BS 20130323 ADD >>
#if (VERTICAL_LCD == 0) // panel rotate 90 degree
   LCD_ILI9488_CMD(0x2A);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x01);
       LCD_ILI9488_INDEX(0xDF);
   LCD_ILI9488_CMD(0x2B);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x01);
       LCD_ILI9488_INDEX(0x3F);
   LCD_ILI9488_CMD(0x36);
       LCD_ILI9488_INDEX(0xE8);//0xC8 //0xE8
//           LCD_ILI9488_CMD(0x36);
//            LCD_ILI9488_INDEX(0x08);
   #else
   LCD_ILI9488_CMD(0x36);
       LCD_ILI9488_INDEX(0x4C);
   #endif
//BS 20130323 ADD << 
   

	LCD_ILI9488_CMD(0x11); //Sleep out
	MMPF_OS_Sleep_MS(120);
	LCD_ILI9488_CMD(0x29);
		
#else // origin
   LCD_ILI9488_CMD(0xE0); 
   LCD_ILI9488_INDEX(0x00); 
   LCD_ILI9488_INDEX(0x07); 
   LCD_ILI9488_INDEX(0x0f); 
   LCD_ILI9488_INDEX(0x07); 
   LCD_ILI9488_INDEX(0x15); 
   LCD_ILI9488_INDEX(0x09); 
   LCD_ILI9488_INDEX(0x3c); 
   LCD_ILI9488_INDEX(0x99); 
   LCD_ILI9488_INDEX(0x4b); 
   LCD_ILI9488_INDEX(0x09); 
   LCD_ILI9488_INDEX(0x10); 
   LCD_ILI9488_INDEX(0x0d); 
   LCD_ILI9488_INDEX(0x1c); 
   LCD_ILI9488_INDEX(0x1e); 
   LCD_ILI9488_INDEX(0x0f);  
	
   LCD_ILI9488_CMD(0xE1); 
   LCD_ILI9488_INDEX(0x00); 
   LCD_ILI9488_INDEX(0x20); 
   LCD_ILI9488_INDEX(0x23); 
   LCD_ILI9488_INDEX(0x02); 
   LCD_ILI9488_INDEX(0x0f); 
   LCD_ILI9488_INDEX(0x06); 
   LCD_ILI9488_INDEX(0x34); 
   LCD_ILI9488_INDEX(0x45); 
   LCD_ILI9488_INDEX(0x43); 
   LCD_ILI9488_INDEX(0x04); 
   LCD_ILI9488_INDEX(0x0a); 
   LCD_ILI9488_INDEX(0x08); 
   LCD_ILI9488_INDEX(0x30); 
   LCD_ILI9488_INDEX(0x37); 
   LCD_ILI9488_INDEX(0x0f); 
   
   LCD_ILI9488_CMD(0xC0); 
   LCD_ILI9488_INDEX(0x10); 
   LCD_ILI9488_INDEX(0x10); 
	
   LCD_ILI9488_CMD(0xC1); 
   LCD_ILI9488_INDEX(0x41); 
   
   LCD_ILI9488_CMD(0xC5); 
   LCD_ILI9488_INDEX(0x00); 
   LCD_ILI9488_INDEX(0x20); 
   LCD_ILI9488_INDEX(0xd0); 
   

   LCD_ILI9488_CMD(0x3A); //Interface Mode Control
   LCD_ILI9488_INDEX(0x50); 
   
   
   LCD_ILI9488_CMD(0XB0);  //Interface Mode Control  
   LCD_ILI9488_INDEX(0x08); 
   LCD_ILI9488_CMD(0xB1);	//Frame rate 60HZ  
   LCD_ILI9488_INDEX(0xA0); 
   LCD_ILI9488_INDEX(0x11); 
   LCD_ILI9488_CMD(0xB4); // jeff.li
   LCD_ILI9488_INDEX(0x02);   
   LCD_ILI9488_CMD(0xB6); //RGB/MCU Interface Control
   LCD_ILI9488_INDEX(0x30); 
   LCD_ILI9488_INDEX(0x42); // jeff.li SS(D5) GS(D6)
   
   LCD_ILI9488_CMD(0XBE);
   LCD_ILI9488_INDEX(0x00);
   LCD_ILI9488_INDEX(0x04);
   
   LCD_ILI9488_CMD(0xE9); 
   LCD_ILI9488_INDEX(0x00);
	
   LCD_ILI9488_CMD(0XF7);	 
   LCD_ILI9488_INDEX(0xA9); 
   LCD_ILI9488_INDEX(0x51); 
   LCD_ILI9488_INDEX(0x2C); 
   LCD_ILI9488_INDEX(0x82);
   
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) // panel rotate 90 degree
   LCD_ILI9488_CMD(0x2A);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x01);
       LCD_ILI9488_INDEX(0xDF);
   LCD_ILI9488_CMD(0x2B);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x00);
       LCD_ILI9488_INDEX(0x01);
       LCD_ILI9488_INDEX(0x3F);
   LCD_ILI9488_CMD(0x36);
       LCD_ILI9488_INDEX(0xE8);//0xC8
//           LCD_ILI9488_CMD(0x36);
//            LCD_ILI9488_INDEX(0x08);
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
   LCD_ILI9488_CMD(0x36);
       LCD_ILI9488_INDEX(0x08);
#endif


   LCD_ILI9488_CMD(0x11); 
   MMPF_OS_Sleep_MS(120); 
   LCD_ILI9488_CMD(0x29); 
#endif
//BS 20160323 << ADD init Code << 

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
#if (ENABLE_LCD_ILI9488_LOG)
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
	RTNA_DBG_Str(0, "dbg-ILI9488-RTNA_LCD_RGB_Test\r\n");
	RTNA_LCD_Backlight(MMP_TRUE);
	RTNA_DBG_Str(0, "dbg-ILI9488 LCD backlight On\r\n");
	MMPF_OS_Sleep_MS(5000);
	RTNA_LCD_Backlight(MMP_FALSE);
	RTNA_DBG_Str(0, "dbg-ILI9488 LCD backlight Off\r\n");
	MMPF_OS_Sleep_MS(1000);
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
	LCD_ILI9488_CMD(reg);
	LCD_ILI9488_INDEX(value);
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

