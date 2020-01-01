//==============================================================================
//
//  File        : lcd_NT35510.c
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



#define SECONDARY_DISPLAY 		(0)

#define ENABLE_LCD_NT35510_LOG (1)


static MMPF_PANEL_ATTR m_PanelAttr = {
        480, 800,
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
        LCD_BUS_WIDTH_8,
        LCD_PHASE0,
        LCD_POLARITY0,
        LCD_MCU_80SYS,
        0,
        0,
        0,
        LCD_RGB_ORDER_BGR,
        MMP_FALSE,
        LCD_SIG_POLARITY_H,
        LCD_SIG_POLARITY_L,
        LCD_SIG_POLARITY_L,
        0x02/*RGB_D24BIT_RGB565*/,
        {0}};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
void write_command(MMP_USHORT reg)
{
    //MMP_UBYTE  i;
    MMP_USHORT  regH, regL;
    //MMP_USHORT data;
    DSPY_DECL;

    regH = reg >> 8;
    regL = reg & 0x00ff;
    DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 2);

    DSPY_WR_W(DSPY_LCD_TX_0,         regH|0x2000);
    DSPY_WR_W(DSPY_LCD_TX_1,         regL);
    DSPY_WR_B(DSPY_CTL_0, LCD_IDX_RDY);
    while(DSPY_RD_B(DSPY_CTL_0) & LCD_IDX_RDY);
}

void write_data(MMP_USHORT data)
{
    DSPY_DECL;
    DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 1);
    DSPY_WR_W(DSPY_LCD_TX_0,         data|0x4000);
    DSPY_WR_B(DSPY_CTL_0, LCD_CMD_RDY);
    while(DSPY_RD_B(DSPY_CTL_0) & LCD_CMD_RDY);
}



void RTNA_LCD_InitMainLCD(void)
{
    #if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");
    m_PanelAttr.usPanelW      = 480;
    m_PanelAttr.usPanelH      = 800;

	m_PanelAttr.ubDevType     = LCD_TYPE_RGBLCD;

	m_PanelAttr.ubController 	= LCD_PRM_CONTROLER;
	m_PanelAttr.ulBgColor 	= 0;
    #if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    m_PanelAttr.ubRatio         = LCD_RATIO_16_9;
    #else
    m_PanelAttr.ubRatio         = LCD_RATIO_4_3;
    #endif


	m_PanelAttr.pInitSeq      = NULL;
	m_PanelAttr.pIdxCmdSeq    = NULL;
    // RGB interface
	m_PanelAttr.bPartialDisp  = MMP_FALSE;
	m_PanelAttr.ubDclkPor     = LCD_SIG_POLARITY_H;
	m_PanelAttr.ubHsyncPor    = LCD_SIG_POLARITY_L;
	m_PanelAttr.ubVsyncPor    = LCD_SIG_POLARITY_L;
	m_PanelAttr.ubRgbFmt      = 0x02/*RGB_D24BIT_RGB565*/;


	m_PanelAttr.usDotClkRatio = 6; //30;      // Stand for [(Lcd Freq / Dot Clock Freq) - 1]
	m_PanelAttr.usHBPorch     = 7;          // Unit:pixel, Ragne:0~1023
	m_PanelAttr.usHBlanking   = 10;        // Unit:pixel, Range:0~1023
	m_PanelAttr.usHSyncW      = 2;           // Unit:pixel, Range:0~255, origin:2
	m_PanelAttr.usVBPorch     = 5;           // Unit:line,  Range:0~1023, origin:1
	m_PanelAttr.usVBlanking   = 20;        // Unit:line,  Range:0~1023, origin:5
	m_PanelAttr.usVSyncW      = 0;           // Unit:line,  Range:0~255, origin:0
	m_PanelAttr.usPRT2HdotClk = 2;      // Unit:Dot Clock, Range:0~255
	m_PanelAttr.bDeltaRBG = MMP_FALSE;
	m_PanelAttr.bDummyRBG = MMP_FALSE;
	m_PanelAttr.ubEvenLnOrder = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder  = LCD_SPI_PIX_ORDER_RGB;

    // RGB SPI interface
	m_PanelAttr.usSpi2MciRatio    = 0xEF;     // Stand for [(MCI Freq / SPI Clock Freq) - 1]
	m_PanelAttr.usCsSetupCyc      = 0x0F;     // Unit:MCI Clock, Range:0~15       //tcss  = 20(min) ns
	m_PanelAttr.usCsHoldCyc       = 0x0F;     // Unit:MCI Clock, Range:0~15       //tcsh  = 50(min) ns
	m_PanelAttr.usCsHighWidth     = 0xFF;     // Unit:MCI Clock, Range:0~255      //tchw  = 45(min) ns
	m_PanelAttr.usSPIRegBitCnt    = SPI_PANEL_16BITS;
    ///////

	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
	m_PanelAttr.usWinW        = 480;
	m_PanelAttr.usWinH        = 800;
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
    //DSPY_DECL;
    //MMP_SHORT i, j;
    //MMP_SHORT retval;
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for NT35510 RGB...\r\n");

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
            MMPF_OS_Sleep_MS(20);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(20);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

            MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
            MMPF_OS_Sleep_MS(20);
            RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
        }
    #endif

        {
            MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_FALSE); // 1. Set LCD_GPIO_BACK_LIGHT output enable
            RTNA_DBG_Str(0, "dbg-set LCD_BL to output mode\r\n");

            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 2. LCD_GPIO_BACK_LIGHT pull low
            MMPF_OS_Sleep_MS(20);
            RTNA_DBG_Str(0, "dbg-set LCD_BL to low\r\n");

            MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 3. LCD_GPIO_BACK_LIGHT pull high
            MMPF_OS_Sleep_MS(20);
            RTNA_DBG_Str(0, "dbg-set LCD_BL to high\r\n");
        }
   #if (SECONDARY_DISPLAY == 1)
       RTNA_LCD_Init2ndLCD();
   #else
       RTNA_LCD_InitMainLCD();
   #endif

    write_command(0x0100);
		MMPF_OS_Sleep_MS(10);
    write_command(0xF000); write_data(0x55);
    write_command(0xF001); write_data(0xAA);
    write_command(0xF002); write_data(0x52);
    write_command(0xF003); write_data(0x08);
    write_command(0xF004); write_data(0x01);
    write_command(0xB600); write_data(0x34);   //# AVDD: manual, 6V (0x44: 2.5xVCI0)
    write_command(0xB601); write_data(0x34);
    write_command(0xB602); write_data(0x34);
    write_command(0xB000); write_data(0x0C);   //#Default žé05  6v
    write_command(0xB001); write_data(0x0C);
    write_command(0xB002); write_data(0x0C);
    write_command(0xB700); write_data(0x24);   //# AVEE: manual, -6V (0x34: -2.5xVCI)
    write_command(0xB701); write_data(0x24);
    write_command(0xB702); write_data(0x24);
    write_command(0xB100); write_data(0x0C);   //#Default žé05  -6v
    write_command(0xB101); write_data(0x0C);
    write_command(0xB102); write_data(0x0C);
    write_command(0xB800); write_data(0x34);    //#Power Control for VCL
    write_command(0xB200); write_data(0x00);  //#-2.5v
    write_command(0xB900); write_data(0x34);   //# VGH: Clamp Enable, 2*AVDD-AVEE, 11V(0x00);
    write_command(0xB901); write_data(0x34);
    write_command(0xB902); write_data(0x34);
    write_command(0xB300); write_data(0x08);
    write_command(0xB301); write_data(0x08);
    write_command(0xB302); write_data(0x08);
    write_command(0xBA00); write_data(0x14);    //# VGL(LVGL):
    write_command(0xBA01); write_data(0x14);
    write_command(0xBA02); write_data(0x14);
    write_command(0xB500); write_data(0x08);    //# VGL_REG(VGLO):-10V
    write_command(0xB501); write_data(0x08);
    write_command(0xB502); write_data(0x08);
    write_command(0xBC00); write_data(0x00);
    write_command(0xBC01); write_data(0xA0);//80
    write_command(0xBC02); write_data(0x00);
    write_command(0xBD00); write_data(0x00);    //# VGMN/VGSN  -4.8v
    write_command(0xBD01); write_data(0xA0);//80
    write_command(0xBD02); write_data(0x00);
    write_command(0xBE00); write_data(0x00);    //# VCOM=-0.1
    write_command(0xBE01); write_data(0x40); //2f
    write_command(0xD100); write_data(0x00);    //#R+
    write_command(0xD101); write_data(0x14);
    write_command(0xD102); write_data(0x00);
    write_command(0xD103); write_data(0x3a);
    write_command(0xD104); write_data(0x00);
    write_command(0xD105); write_data(0x66);
    write_command(0xD106); write_data(0x00);
    write_command(0xD107); write_data(0x86);
    write_command(0xD108); write_data(0x00);
    write_command(0xD109); write_data(0x9d);
    write_command(0xD10A); write_data(0x00);
    write_command(0xD10B); write_data(0xc3);
    write_command(0xD10C); write_data(0x00);
    write_command(0xD10D); write_data(0xe7);
    write_command(0xD10E); write_data(0x01);
    write_command(0xD10F); write_data(0x19);
    write_command(0xD110); write_data(0x01);
    write_command(0xD111); write_data(0x41);
    write_command(0xD112); write_data(0x01);
    write_command(0xD113); write_data(0x81);
    write_command(0xD114); write_data(0x01);
    write_command(0xD115); write_data(0xB4);
    write_command(0xD116); write_data(0x02);
    write_command(0xD117); write_data(0x03);
    write_command(0xD118); write_data(0x02);
    write_command(0xD119); write_data(0x41);
    write_command(0xD11A); write_data(0x02);
    write_command(0xD11B); write_data(0x43);
    write_command(0xD11C); write_data(0x02);
    write_command(0xD11D); write_data(0x7c);
    write_command(0xD11E); write_data(0x02);
    write_command(0xD11F); write_data(0xB8);
    write_command(0xD120); write_data(0x02);
    write_command(0xD121); write_data(0xDd);
    write_command(0xD122); write_data(0x03);
    write_command(0xD123); write_data(0x0b);
    write_command(0xD124); write_data(0x03);
    write_command(0xD125); write_data(0x2a);
    write_command(0xD126); write_data(0x03);
    write_command(0xD127); write_data(0x55);
    write_command(0xD128); write_data(0x03);
    write_command(0xD129); write_data(0x71);
    write_command(0xD12A); write_data(0x03);
    write_command(0xD12B); write_data(0x92);
    write_command(0xD12C); write_data(0x03);
    write_command(0xD12D); write_data(0xab);
    write_command(0xD12E); write_data(0x03);
    write_command(0xD12F); write_data(0xbe);
    write_command(0xD130); write_data(0x03);
    write_command(0xD131); write_data(0xC0);
    write_command(0xD132); write_data(0x03);
    write_command(0xD133); write_data(0xC0);
    write_command(0xD200); write_data(0x00);
    write_command(0xD201); write_data(0x14);
    write_command(0xD202); write_data(0x00);
    write_command(0xD203); write_data(0x3a);
    write_command(0xD204); write_data(0x00);
    write_command(0xD205); write_data(0x66);
    write_command(0xD206); write_data(0x00);
    write_command(0xD207); write_data(0x86);
    write_command(0xD208); write_data(0x00);
    write_command(0xD209); write_data(0x9d);
    write_command(0xD20A); write_data(0x00);
    write_command(0xD20B); write_data(0xc3);
    write_command(0xD20C); write_data(0x00);
    write_command(0xD20D); write_data(0xe7);
    write_command(0xD20E); write_data(0x01);
    write_command(0xD20F); write_data(0x19);
    write_command(0xD210); write_data(0x01);
    write_command(0xD211); write_data(0x41);
    write_command(0xD212); write_data(0x01);
    write_command(0xD213); write_data(0x81);
    write_command(0xD214); write_data(0x01);
    write_command(0xD215); write_data(0xB4);
    write_command(0xD216); write_data(0x02);
    write_command(0xD217); write_data(0x03);
    write_command(0xD218); write_data(0x02);
    write_command(0xD219); write_data(0x41);
    write_command(0xD21A); write_data(0x02);
    write_command(0xD21B); write_data(0x43);
    write_command(0xD21C); write_data(0x02);
    write_command(0xD21D); write_data(0x7c);
    write_command(0xD21E); write_data(0x02);
    write_command(0xD21F); write_data(0xB8);
    write_command(0xD220); write_data(0x02);
    write_command(0xD221); write_data(0xDd);
    write_command(0xD222); write_data(0x03);
    write_command(0xD223); write_data(0x0b);
    write_command(0xD224); write_data(0x03);
    write_command(0xD225); write_data(0x2a);
    write_command(0xD226); write_data(0x03);
    write_command(0xD227); write_data(0x55);
    write_command(0xD228); write_data(0x03);
    write_command(0xD229); write_data(0x71);
    write_command(0xD22A); write_data(0x03);
    write_command(0xD22B); write_data(0x92);
    write_command(0xD22C); write_data(0x03);
    write_command(0xD22D); write_data(0xab);
    write_command(0xD22E); write_data(0x03);
    write_command(0xD22F); write_data(0xbe);
    write_command(0xD230); write_data(0x03);
    write_command(0xD231); write_data(0xC0);
    write_command(0xD232); write_data(0x03);
    write_command(0xD233); write_data(0xC0);

    //#B+
    write_command(0xD300); write_data(0x00);
    write_command(0xD301); write_data(0x14);
    write_command(0xD302); write_data(0x00);
    write_command(0xD303); write_data(0x3a);
    write_command(0xD304); write_data(0x00);
    write_command(0xD305); write_data(0x66);
    write_command(0xD306); write_data(0x00);
    write_command(0xD307); write_data(0x86);
    write_command(0xD308); write_data(0x00);
    write_command(0xD309); write_data(0x9d);
    write_command(0xD30A); write_data(0x00);
    write_command(0xD30B); write_data(0xc3);
    write_command(0xD30C); write_data(0x00);
    write_command(0xD30D); write_data(0xe7);
    write_command(0xD30E); write_data(0x01);
    write_command(0xD30F); write_data(0x19);
    write_command(0xD310); write_data(0x01);
    write_command(0xD311); write_data(0x41);
    write_command(0xD312); write_data(0x01);
    write_command(0xD313); write_data(0x81);
    write_command(0xD314); write_data(0x01);
    write_command(0xD315); write_data(0xB4);
    write_command(0xD316); write_data(0x02);
    write_command(0xD317); write_data(0x03);
    write_command(0xD318); write_data(0x02);
    write_command(0xD319); write_data(0x41);
    write_command(0xD31A); write_data(0x02);
    write_command(0xD31B); write_data(0x43);
    write_command(0xD31C); write_data(0x02);
    write_command(0xD31D); write_data(0x7c);
    write_command(0xD31E); write_data(0x02);
    write_command(0xD31F); write_data(0xB8);
    write_command(0xD320); write_data(0x02);
    write_command(0xD321); write_data(0xDd);
    write_command(0xD322); write_data(0x03);
    write_command(0xD323); write_data(0x0b);
    write_command(0xD324); write_data(0x03);
    write_command(0xD325); write_data(0x2a);
    write_command(0xD326); write_data(0x03);
    write_command(0xD327); write_data(0x55);
    write_command(0xD328); write_data(0x03);
    write_command(0xD329); write_data(0x71);
    write_command(0xD32A); write_data(0x03);
    write_command(0xD32B); write_data(0x92);
    write_command(0xD32C); write_data(0x03);
    write_command(0xD32D); write_data(0xab);
    write_command(0xD32E); write_data(0x03);
    write_command(0xD32F); write_data(0xbe);
    write_command(0xD330); write_data(0x03);
    write_command(0xD331); write_data(0xC0);
    write_command(0xD332); write_data(0x03);
    write_command(0xD333); write_data(0xC0);
//    MMPF_OS_Sleep_MS(500);

    write_command(0xD400); write_data(0x00);
    write_command(0xD401); write_data(0x14);
    write_command(0xD402); write_data(0x00);
    write_command(0xD403); write_data(0x3a);
    write_command(0xD404); write_data(0x00);
    write_command(0xD405); write_data(0x66);
    write_command(0xD406); write_data(0x00);
    write_command(0xD407); write_data(0x86);
    write_command(0xD408); write_data(0x00);
    write_command(0xD409); write_data(0x9d);
    write_command(0xD40A); write_data(0x00);
    write_command(0xD40B); write_data(0xc3);
    write_command(0xD40C); write_data(0x00);
    write_command(0xD40D); write_data(0xe7);
    write_command(0xD40E); write_data(0x01);
    write_command(0xD40F); write_data(0x19);
    write_command(0xD410); write_data(0x01);
    write_command(0xD411); write_data(0x41);
    write_command(0xD412); write_data(0x01);
    write_command(0xD413); write_data(0x81);
    write_command(0xD414); write_data(0x01);
    write_command(0xD415); write_data(0xB4);
    write_command(0xD416); write_data(0x02);
    write_command(0xD417); write_data(0x03);
    write_command(0xD418); write_data(0x02);
    write_command(0xD419); write_data(0x41);
    write_command(0xD41A); write_data(0x02);
    write_command(0xD41B); write_data(0x43);
    write_command(0xD41C); write_data(0x02);
    write_command(0xD41D); write_data(0x7c);
    write_command(0xD41E); write_data(0x02);
    write_command(0xD41F); write_data(0xB8);
    write_command(0xD420); write_data(0x02);
    write_command(0xD421); write_data(0xDd);
    write_command(0xD422); write_data(0x03);
    write_command(0xD423); write_data(0x0b);
    write_command(0xD424); write_data(0x03);
    write_command(0xD425); write_data(0x2a);
    write_command(0xD426); write_data(0x03);
    write_command(0xD427); write_data(0x55);
    write_command(0xD428); write_data(0x03);
    write_command(0xD429); write_data(0x71);
    write_command(0xD42A); write_data(0x03);
    write_command(0xD42B); write_data(0x92);
    write_command(0xD42C); write_data(0x03);
    write_command(0xD42D); write_data(0xab);
    write_command(0xD42E); write_data(0x03);
    write_command(0xD42F); write_data(0xbe);
    write_command(0xD430); write_data(0x03);
    write_command(0xD431); write_data(0xC0);
    write_command(0xD432); write_data(0x03);
    write_command(0xD433); write_data(0xC0);

    //#G-
    write_command(0xD500); write_data(0x00);
    write_command(0xD501); write_data(0x14);
    write_command(0xD502); write_data(0x00);
    write_command(0xD503); write_data(0x3a);
    write_command(0xD504); write_data(0x00);
    write_command(0xD505); write_data(0x66);
    write_command(0xD506); write_data(0x00);
    write_command(0xD507); write_data(0x86);
    write_command(0xD508); write_data(0x00);
    write_command(0xD509); write_data(0x9d);
    write_command(0xD50A); write_data(0x00);
    write_command(0xD50B); write_data(0xc3);
    write_command(0xD50C); write_data(0x00);
    write_command(0xD50D); write_data(0xe7);
    write_command(0xD50E); write_data(0x01);
    write_command(0xD50F); write_data(0x19);
    write_command(0xD510); write_data(0x01);
    write_command(0xD511); write_data(0x41);
    write_command(0xD512); write_data(0x01);
    write_command(0xD513); write_data(0x81);
    write_command(0xD514); write_data(0x01);
    write_command(0xD515); write_data(0xB4);
    write_command(0xD516); write_data(0x02);
    write_command(0xD517); write_data(0x03);
    write_command(0xD518); write_data(0x02);
    write_command(0xD519); write_data(0x41);
    write_command(0xD51A); write_data(0x02);
    write_command(0xD51B); write_data(0x43);
    write_command(0xD51C); write_data(0x02);
    write_command(0xD51D); write_data(0x7c);
    write_command(0xD51E); write_data(0x02);
    write_command(0xD51F); write_data(0xB8);
    write_command(0xD520); write_data(0x02);
    write_command(0xD521); write_data(0xDd);
    write_command(0xD522); write_data(0x03);
    write_command(0xD523); write_data(0x0b);
    write_command(0xD524); write_data(0x03);
    write_command(0xD525); write_data(0x2a);
    write_command(0xD526); write_data(0x03);
    write_command(0xD527); write_data(0x55);
    write_command(0xD528); write_data(0x03);
    write_command(0xD529); write_data(0x71);
    write_command(0xD52A); write_data(0x03);
    write_command(0xD52B); write_data(0x92);
    write_command(0xD52C); write_data(0x03);
    write_command(0xD52D); write_data(0xab);
    write_command(0xD52E); write_data(0x03);
    write_command(0xD52F); write_data(0xbe);
    write_command(0xD530); write_data(0x03);
    write_command(0xD531); write_data(0xC0);
    write_command(0xD532); write_data(0x03);
    write_command(0xD533); write_data(0xC0);

    //#B-
    write_command(0xD600); write_data(0x00);
    write_command(0xD601); write_data(0x14);
    write_command(0xD602); write_data(0x00);
    write_command(0xD603); write_data(0x3a);
    write_command(0xD604); write_data(0x00);
    write_command(0xD605); write_data(0x66);
    write_command(0xD606); write_data(0x00);
    write_command(0xD607); write_data(0x86);
    write_command(0xD608); write_data(0x00);
    write_command(0xD609); write_data(0x9d);
    write_command(0xD60A); write_data(0x00);
    write_command(0xD60B); write_data(0xc3);
    write_command(0xD60C); write_data(0x00);
    write_command(0xD60D); write_data(0xe7);
    write_command(0xD60E); write_data(0x01);
    write_command(0xD60F); write_data(0x19);
    write_command(0xD610); write_data(0x01);
    write_command(0xD611); write_data(0x41);
    write_command(0xD612); write_data(0x01);
    write_command(0xD613); write_data(0x81);
    write_command(0xD614); write_data(0x01);
    write_command(0xD615); write_data(0xB4);
    write_command(0xD616); write_data(0x02);
    write_command(0xD617); write_data(0x03);
    write_command(0xD618); write_data(0x02);
    write_command(0xD619); write_data(0x41);
    write_command(0xD61A); write_data(0x02);
    write_command(0xD61B); write_data(0x43);
    write_command(0xD61C); write_data(0x02);
    write_command(0xD61D); write_data(0x7c);
    write_command(0xD61E); write_data(0x02);
    write_command(0xD61F); write_data(0xB8);
    write_command(0xD620); write_data(0x02);
    write_command(0xD621); write_data(0xDd);
    write_command(0xD622); write_data(0x03);
    write_command(0xD623); write_data(0x0b);
    write_command(0xD624); write_data(0x03);
    write_command(0xD625); write_data(0x2a);
    write_command(0xD626); write_data(0x03);
    write_command(0xD627); write_data(0x55);
    write_command(0xD628); write_data(0x03);
    write_command(0xD629); write_data(0x71);
    write_command(0xD62A); write_data(0x03);
    write_command(0xD62B); write_data(0x92);
    write_command(0xD62C); write_data(0x03);
    write_command(0xD62D); write_data(0xab);
    write_command(0xD62E); write_data(0x03);
    write_command(0xD62F); write_data(0xbe);
    write_command(0xD630); write_data(0x03);
    write_command(0xD631); write_data(0xC0);
    write_command(0xD632); write_data(0x03);
    write_command(0xD633); write_data(0xC0);

    //#Enable Page0
    write_command(0xF000); write_data(0x55);
    write_command(0xF001); write_data(0xAA);
    write_command(0xF002); write_data(0x52);
    write_command(0xF003); write_data(0x08);
    write_command(0xF004); write_data(0x00);

    //# RGB I/F Setting
    write_command(0xB000); write_data(0x03); //0x00,
    write_command(0xB001); write_data(0x05);
    write_command(0xB002); write_data(0x02);
    write_command(0xB003); write_data(0x05);
    write_command(0xB004); write_data(0x02);

    //## SDT:
    write_command(0xB600); write_data(0x05);

    //## Gate EQ:
    write_command(0xB700); write_data(0x70);
    write_command(0xB701); write_data(0x70);

    //## Source EQ:
    write_command(0xB800); write_data(0x01);
    write_command(0xB801); write_data(0x05);
    write_command(0xB802); write_data(0x05);
    write_command(0xB803); write_data(0x05);

    //# Inversion: Column inversion (NVT)
    write_command(0xBC00); write_data(0x00);
    write_command(0xBC01); write_data(0x00);
    write_command(0xBC02); write_data(0x00);

    //# BOE's Setting (default)
    write_command(0xCC00); write_data(0x03);
    write_command(0xCC01); write_data(0x50);
    write_command(0xCC02); write_data(0x50);

    //# Display Timing:
    write_command(0xBD00); write_data(0x01); //
    write_command(0xBD01); write_data(0x00);
    write_command(0xBD02); write_data(0x07);
    write_command(0xBD03); write_data(0x31);
    write_command(0xBD04); write_data(0x00);

    write_command(0xFF00); write_data(0xAA);
    write_command(0xFF01); write_data(0x55);
    write_command(0xFF02); write_data(0x25);
    write_command(0xFF03); write_data(0x01);
    write_command(0x3a00); write_data(0x55);
	write_command(0x3600); write_data(0x00);

//    write_command(0x3500); write_data(0x01);
    write_command(0x1100);
		MMPF_OS_Sleep_MS(10);

    write_command(0x2900);
		MMPF_OS_Sleep_MS(10);
}

void RTNA_LCD_RGB_Test(void)
{
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
#if (ENABLE_LCD_NT35510_LOG)
	RTNA_DBG_Str(0, "dbg-NT35510-RTNA_LCD_RGB_Test\r\n");
	RTNA_LCD_Backlight(MMP_TRUE);
	RTNA_DBG_Str(0, "dbg-NT35510 LCD backlight On\r\n");
	MMPF_OS_Sleep_MS(200);
	RTNA_LCD_Backlight(MMP_FALSE);
	RTNA_DBG_Str(0, "dbg-NT35510 LCD backlight Off\r\n");
	MMPF_OS_Sleep_MS(200);
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
    write_command(reg); write_data(value);
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

