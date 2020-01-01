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
#define  GBL_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  GBL_GET_B(reg)         MMPH_HIF_RegGetB(reg)

#define  LCD_GET_W(reg)         MMPH_HIF_RegGetW(reg)
#define  LCD_GET_B(reg)         MMPH_HIF_RegGetB(reg)
#define  LCD_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  LCD_SET_W(reg, val)    MMPH_HIF_RegSetW(reg, val)
#define  LCD_SET_D(reg, val)    MMPH_HIF_RegSetL(reg, val)


#define Delayms(t) 				LCD_WAIT(t)

#define SECONDARY_DISPLAY 		(0)

#define ENABLE_LCD_ILI9486L_LOG (0)


#if (LCD_IF == LCD_IF_PARALLEL)
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
#define ENABLE_LCD_ILI9486L_ROTATE_90 (1) // panel rotates 90 degrees, it might be removed when LCD FLM is workable and image is rotated 90 degrees by DSP
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define ENABLE_LCD_ILI9486L_ROTATE_90 (0) // panel rotates 90 degrees, it might be removed when LCD FLM is workable and image is rotated 90 degrees by DSP             
#endif
static MMPF_PANEL_ATTR m_PanelAttr = {
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
        480,320,
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        320, 480,             
#endif
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
        LCD_PHASE1,
        LCD_POLARITY1,
        LCD_MCU_80SYS,
        0,
        1,
        5,
        LCD_RGB_ORDER_RGB,
        {0}};
#elif (LCD_IF == LCD_IF_RGB)
static MMPF_PANEL_ATTR m_PanelAttr = {
        320, 480,
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

static void LcdILI9486LInitIndexCmd(MMP_UBYTE ubController)
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
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
    m_PanelAttr.usPanelW      = 480;
    m_PanelAttr.usPanelH      = 320;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    m_PanelAttr.usPanelW      = 320;
    m_PanelAttr.usPanelH      = 480;             
#endif

#if (LCD_IF == LCD_IF_PARALLEL)
	m_PanelAttr.ubDevType 	= LCD_TYPE_PLCD;
#elif (LCD_IF == LCD_IF_RGB)
	m_PanelAttr.ubDevType     = LCD_TYPE_RGBLCD;
#endif
	m_PanelAttr.ubController 	= LCD_PRM_CONTROLER;
	m_PanelAttr.ulBgColor 	= 0;
    #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    m_PanelAttr.ubRatio         = LCD_RATIO_16_9;
    #else
    m_PanelAttr.ubRatio         = LCD_RATIO_4_3;
    #endif

#if (LCD_IF == LCD_IF_PARALLEL)
	m_PanelAttr.pInitSeq 		= NULL;
	m_PanelAttr.pIdxCmdSeq 	= LcdILI9486LInitIndexCmd;

	m_PanelAttr.ubBusWidth 	= LCD_BUS_WIDTH_16;
	m_PanelAttr.ubPhase 		= LCD_PHASE1;
	m_PanelAttr.ubPolarity 	= LCD_POLARITY1;
	m_PanelAttr.ubMCUSystem 	= LCD_MCU_80SYS;
	m_PanelAttr.usRsLeadCsCnt = 0;
	m_PanelAttr.usCsLeadRwCnt = 1;
	m_PanelAttr.usRwCycCnt 	= 9;
	m_PanelAttr.ubRgbOrder 	= LCD_RGB_ORDER_BGR;

	m_PanelAttr.ubRgbFmt      = 0x0A/*RGB_D24BIT_BGR565*/;
#elif (LCD_IF == LCD_IF_RGB)
	m_PanelAttr.pInitSeq      = NULL;
	m_PanelAttr.pIdxCmdSeq    = NULL;
    // RGB interface
	m_PanelAttr.bPartialDisp  = MMP_FALSE;
	m_PanelAttr.ubDclkPor     = LCD_SIG_POLARITY_H;
	m_PanelAttr.ubHsyncPor    = LCD_SIG_POLARITY_L;
	m_PanelAttr.ubVsyncPor    = LCD_SIG_POLARITY_L;
	m_PanelAttr.ubRgbFmt      = 0x02/*RGB_D24BIT_RGB565*/;

	m_PanelAttr.usDotClkRatio = 30;      // Stand for [(Lcd Freq / Dot Clock Freq) - 1]
	m_PanelAttr.usHBPorch     = 7;          // Unit:pixel, Ragne:0~1023
	m_PanelAttr.usHBlanking   = 10;        // Unit:pixel, Range:0~1023
	m_PanelAttr.usHSyncW      = 2;           // Unit:pixel, Range:0~255
	m_PanelAttr.usVBPorch     = 1;          // Unit:line,  Range:0~1023
	m_PanelAttr.usVBlanking   = 5;        // Unit:line,  Range:0~1023
	m_PanelAttr.usVSyncW      = 0;           // Unit:line,  Range:0~255
	m_PanelAttr.usPRT2HdotClk = 2;      // Unit:Dot Clock, Range:0~255

	m_PanelAttr.bDeltaRBG = MMP_FALSE;
	m_PanelAttr.bDummyRBG = MMP_FALSE;
	m_PanelAttr.ubEvenLnOrder = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder  = LCD_SPI_PIX_ORDER_RGB;

    // RGB SPI interface
	m_PanelAttr.usSpi2MciRatio    = 0x0F;     // Stand for [(MCI Freq / SPI Clock Freq) - 1]
	m_PanelAttr.usCsSetupCyc      = 0x0B;     // Unit:MCI Clock, Range:0~15       //tcss - tslw = 60(min) - 15 (min) = 45ns
	m_PanelAttr.usCsHoldCyc       = 0x0B;     // Unit:MCI Clock, Range:0~15       //tcsh  = 65(min) ns
	m_PanelAttr.usCsHighWidth     = 0xFF;     // Unit:MCI Clock, Range:0~255      //tchw  = 40(min) ns
	m_PanelAttr.usSPIRegBitCnt    = SPI_PANEL_9BITS;
    ///////
#endif
	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
	m_PanelAttr.usWinW        = 480;
	m_PanelAttr.usWinH        = 320;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
	m_PanelAttr.usWinW 		= 320;
	m_PanelAttr.usWinH 		= 480;             
#endif
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 	= 0x01500000;

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
//DSPY_DECL;
    extern MMPF_PANEL_ATTR m_PanelAttr;

    //MMP_SHORT i, j;
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9486L ...\r\n");

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

	{
	// VCI = 2.8V
	// ************* Reset LCD Driver **************** //
	//  LCD_nRESET = 1;
	//  Delayms(1); // Delay 1ms
	//  LCD_nRESET = 0;
	//  Delayms(10); // Delay 10ms // This delay time is necessary
	//  LCD_nRESET = 1;
	//  Delayms(120); // Delay 100 ms
	// ************* Start Initial Sequence ********** //
		MAINLCD_CMD(0xF2);
	        MAINLCD_DATA(0x18);
	        MAINLCD_DATA(0xA3);
	        MAINLCD_DATA(0x12);
	        MAINLCD_DATA(0x02);
	        MAINLCD_DATA(0xB2);
	        MAINLCD_DATA(0x12);
	        MAINLCD_DATA(0xFF);
	        MAINLCD_DATA(0x10);
	        MAINLCD_DATA(0x00);
		MAINLCD_CMD(0xF8);
	        MAINLCD_DATA(0x21);
	        MAINLCD_DATA(0x04);
		MAINLCD_CMD(0xF9);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x08);
		MAINLCD_CMD(0xF1);
	        MAINLCD_DATA(0x36);
	        MAINLCD_DATA(0x04);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x3C);
	        MAINLCD_DATA(0x0F);
	        MAINLCD_DATA(0x8F);

		MAINLCD_CMD(0xC0);
	        MAINLCD_DATA(0x19);
	        MAINLCD_DATA(0x1A);
		MAINLCD_CMD(0xC1);
		    MAINLCD_DATA(0x44);
		MAINLCD_CMD(0xC2);
		    MAINLCD_DATA(0x11);
		MAINLCD_CMD(0xC5);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x20);
	        MAINLCD_DATA(0x80);
		MAINLCD_CMD(0xB1);
	        MAINLCD_DATA(0xB0);
	        MAINLCD_DATA(0x11);
		MAINLCD_CMD(0xB4);
		    MAINLCD_DATA(0x02);
		MAINLCD_CMD(0xB0);
		    MAINLCD_DATA(0x00);
		MAINLCD_CMD(0xB6);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x02);
	        MAINLCD_DATA(0x3B);
		MAINLCD_CMD(0xB7);
		    MAINLCD_DATA(0x07);
		MAINLCD_CMD(0xE0);
	        MAINLCD_DATA(0x1F);
	        MAINLCD_DATA(0x25);
	        MAINLCD_DATA(0x22);
	        MAINLCD_DATA(0x0A);
	        MAINLCD_DATA(0x05);
	        MAINLCD_DATA(0x07);
	        MAINLCD_DATA(0x50);
	        MAINLCD_DATA(0xA8);
	        MAINLCD_DATA(0x40);
	        MAINLCD_DATA(0x0D);
	        MAINLCD_DATA(0x19);
	        MAINLCD_DATA(0x07);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x00);
		MAINLCD_CMD(0xE1);
	        MAINLCD_DATA(0x1F);
	        MAINLCD_DATA(0x3F);
	        MAINLCD_DATA(0x3F);
	        MAINLCD_DATA(0x08);
	        MAINLCD_DATA(0x06);
	        MAINLCD_DATA(0x02);
	        MAINLCD_DATA(0x3F);
	        MAINLCD_DATA(0x75);
	        MAINLCD_DATA(0x2E);
	        MAINLCD_DATA(0x08);
	        MAINLCD_DATA(0x0B);
	        MAINLCD_DATA(0x05);
	        MAINLCD_DATA(0x1D);
	        MAINLCD_DATA(0x1A);
	        MAINLCD_DATA(0x00);
	#if (ENABLE_LCD_ILI9486L_ROTATE_90) // panel rotate 90 degree
	    MAINLCD_CMD(0x2A);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x01);
	        MAINLCD_DATA(0xDF);
	    MAINLCD_CMD(0x2B);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x00);
	        MAINLCD_DATA(0x01);
	        MAINLCD_DATA(0x3F);
		MAINLCD_CMD(0x36);
		    MAINLCD_DATA(0xE8);//0xC8
	#else
		MAINLCD_CMD(0x36);
		    MAINLCD_DATA(0x9C);
	#endif
		MAINLCD_CMD(0x3A);
		    MAINLCD_DATA(0x55);
		MAINLCD_CMD(0x11);
		MMPF_OS_Sleep_MS(120);
		MAINLCD_CMD(0x29);
		//MAINLCD_CMD(0x2C);
	}
#elif (LCD_IF == LCD_IF_RGB)
    extern MMPF_PANEL_ATTR m_PanelAttr;

    MMP_SHORT i, j;
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9486L RGB...\r\n");
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
            MMPF_OS_Sleep_MS(10);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(120);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
        }
    #endif

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

       Write_COMMAND16i(0xF1);
           Write_DATA16i(0x36);
           Write_DATA16i(0x04);
           Write_DATA16i(0x00);
           Write_DATA16i(0x3C);
           Write_DATA16i(0x0F);
           Write_DATA16i(0x8F);
       Write_COMMAND16i(0xF2);
           Write_DATA16i(0x18);
           Write_DATA16i(0xA3);
           Write_DATA16i(0x12);
           Write_DATA16i(0x02);
           Write_DATA16i(0xB2);
           Write_DATA16i(0x12);
           Write_DATA16i(0xFF);
           Write_DATA16i(0x10);
           Write_DATA16i(0x00);
       Write_COMMAND16i(0xF8);
           Write_DATA16i(0x21);
           Write_DATA16i(0x04);
       Write_COMMAND16i(0xF9);
           Write_DATA16i(0x00);
           Write_DATA16i(0x08);


       Write_COMMAND16i(0xC0);
           Write_DATA16i(0x0B);
           Write_DATA16i(0x0B);
       Write_COMMAND16i(0xC1);
           Write_DATA16i(0x42);
       Write_COMMAND16i(0xC2);
           Write_DATA16i(0x11);
       Write_COMMAND16i(0xC5);
           Write_DATA16i(0x00);
           Write_DATA16i(0x00);
           Write_DATA16i(0x80);
       Write_COMMAND16i(0xB1);
           Write_DATA16i(0xB0);
           Write_DATA16i(0x11);
       Write_COMMAND16i(0xB4);
           Write_DATA16i(0x02);
       Write_COMMAND16i(0xB6);
           Write_DATA16i(0x22);//0x62 0x22  bit6 RCM 0:DE mode   1:SYCmode
           Write_DATA16i(0x22);
           Write_DATA16i(0x3B);

       Write_COMMAND16i(0xB7);
           Write_DATA16i(0xC6);
       Write_COMMAND16i(0xE0);
           Write_DATA16i(0x00);
           Write_DATA16i(0x1D);
           Write_DATA16i(0x19);
           Write_DATA16i(0x0C);
           Write_DATA16i(0x0F);
           Write_DATA16i(0x0A);
           Write_DATA16i(0x45);
           Write_DATA16i(0x95);
           Write_DATA16i(0x38);
           Write_DATA16i(0x0A);
           Write_DATA16i(0x12);
           Write_DATA16i(0x03);
           Write_DATA16i(0x09);
           Write_DATA16i(0x06);
           Write_DATA16i(0x00);
       Write_COMMAND16i(0xE1);
           Write_DATA16i(0x0F);
           Write_DATA16i(0x3A);
           Write_DATA16i(0x36);
           Write_DATA16i(0x0C);
           Write_DATA16i(0x0D);
           Write_DATA16i(0x05);
           Write_DATA16i(0x4E);
           Write_DATA16i(0x0A);
           Write_DATA16i(0x38);
           Write_DATA16i(0x05);
           Write_DATA16i(0x0F);
           Write_DATA16i(0x03);
           Write_DATA16i(0x25);
           Write_DATA16i(0x22);
           Write_DATA16i(0x0F);

       Write_COMMAND16i(0x36);
           Write_DATA16i(0x08);//0x48

       Write_COMMAND16i(0x3A);
           Write_DATA16i(0x55);//8&16Bit 0x55, 18Bit 0x66
       Write_COMMAND16i(0x11);
       MMPF_OS_Sleep_MS(120);
       Write_COMMAND16i(0x29);
       Write_COMMAND16i(0x2C);


#endif
 }
void RTNA_LCD_RGB_Test(void)
{
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
#if (ENABLE_LCD_ILI9486L_LOG)
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

