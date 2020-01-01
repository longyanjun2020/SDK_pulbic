//==============================================================================
//
//  File        : lcd_ILI8961.c
//  Description : 320x240 LCD Panel Control Function
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
#include "drv_bus_spi.h"
#include "drv_mspi.h"
#include "halPnl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define Delayms(t)                  0//LCD_WAIT(t)

#define DELTA_RGB                   (0)
#define STRIP_RGB                   (1) // TBD??
#define LCD_RGB_MODE                (DELTA_RGB)

#define SECONDARY_DISPLAY           (0)

#define LCD_ILI8961_WIDTH           (320)
#define LCD_ILI8961_HEIGHT          (240)

#define Delay_us(n)   0
#define Delay_ms(n)   0

static MMPF_PANEL_ATTR m_PanelAttr =
{
    // Panel basic setting
    LCD_ILI8961_WIDTH, LCD_ILI8961_HEIGHT,
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
    LCD_BUS_WIDTH_8,    //ubBusWidth
    LCD_RGB565,//LCD_RGB565,//LCD_BGR565,
    LCD_PHASE0,         //ubPhase
    LCD_POLARITY0,      //ubPolarity
    LCD_MCU_80SYS,      //ubMCUSystem
    0,                  //usRsLeadCsCnt
    0,                  //usCsLeadRwCnt
    0,                  //usRwCycCnt
    LCD_RGB_ORDER_RGB,  //ubRgbOrder

    // RGB interface
    MMP_FALSE,              //bPartialDisp
    LCD_SIG_POLARITY_H,     // DCLK Polarity
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
    LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x00/*RGB_D24BIT_RGB888*/,
    LCD_TOP_CLK_MPLL_108M,  //ulClkSelect

    {0}
};

#define ENABLE_LCD_ILI8961_LOG      (0)
#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN     (1)
#else
#define ENABLE_LCD_TEST_PATTERN     (0)
#endif

#define LCD_BRIGETNESS_DEFAULT      (1)

#define LCD_CONTRAST_DEFAULT        (1)

#define LCD_VCOM_DEFAULT            (0)

#define LCD_GAMMA_AUTO              (1) // 0: Manual set gamma by R17h~R1Ah, 1: Auto set to gamma2.2


//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
    RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD ILI8961----\r\n");

    m_PanelAttr.usDotClkRatio   = 4;//4;

    m_PanelAttr.ulDotClkFreq    = 20000000;

    m_PanelAttr.ubDclkPor       = LCD_SIG_POLARITY_H;
    m_PanelAttr.ubHsyncPor      = LCD_SIG_POLARITY_L;
    m_PanelAttr.ubVsyncPor      = LCD_SIG_POLARITY_L;

    #if (LCD_RGB_MODE == STRIP_RGB)
    m_PanelAttr.usHBPorch       = 0x3C;
    m_PanelAttr.usHBlanking     = 0x47;
    #else
    m_PanelAttr.usHBPorch       = 24;
    m_PanelAttr.usHBlanking     = 0x46;
    #endif
    m_PanelAttr.usHSyncW        = 0;
    m_PanelAttr.usVBPorch       = 21;
    m_PanelAttr.usVBlanking     = 22;
    m_PanelAttr.usVSyncW        = 0;
    m_PanelAttr.usPRT2HdotClk   = 2;

    #if (LCD_RGB_MODE == STRIP_RGB)
    m_PanelAttr.bDeltaRBG       = MMP_FALSE; // TBD??
    m_PanelAttr.bDummyRBG       = MMP_TRUE; // TBD??
    #else
    m_PanelAttr.bDeltaRBG       = MMP_TRUE;
    m_PanelAttr.bDummyRBG       = MMP_FALSE;
    #endif

    // The order maybe changed by RTNA_LCD_Direction
    //#if (LCD_RGB_MODE == STRIP_RGB)
    m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RBG;
    m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;//LCD_SPI_PIX_ORDER_GRB;
    /*#else
    m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_GBR;
    m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
    #endif*/

    m_PanelAttr.usSpi2MciRatio  = 0x80;
    m_PanelAttr.usCsSetupCyc    = 0x0F;
    m_PanelAttr.usCsHoldCyc     = 0x0F;
    m_PanelAttr.usCsHighWidth   = 0xFF;
    m_PanelAttr.usSPIRegBitCnt  = 0x00;//SPI_PANEL_16BITS;

    m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_PIP;
    m_PanelAttr.usWinStX        = 0;
    m_PanelAttr.usWinStY        = 0;
    m_PanelAttr.usWinW          = LCD_ILI8961_WIDTH;
    m_PanelAttr.usWinH          = LCD_ILI8961_HEIGHT;
    m_PanelAttr.usWinBPP        = 2;
    m_PanelAttr.usWinFmt        = LCD_WIN_FMT_16BPP;
    m_PanelAttr.ulWinAddr       = 0x03000000;

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
    m_PanelAttr.usPanelW        = LCD_ILI8961_WIDTH;
    m_PanelAttr.usPanelH        = LCD_ILI8961_HEIGHT;
    m_PanelAttr.ubDevType       = LCD_TYPE_RGBLCD;
    m_PanelAttr.ubController    = LCD_SCD_CONTROLER;

    m_PanelAttr.pInitSeq        = NULL;
    m_PanelAttr.pIdxCmdSeq      = NULL;

    m_PanelAttr.bPartialDisp    = MMP_FALSE;
    m_PanelAttr.ubHsyncPor      = LCD_SIG_POLARITY_L;
    m_PanelAttr.ubVsyncPor      = LCD_SIG_POLARITY_L;
    m_PanelAttr.ubRgbFmt        = 0x00/*RGB_D24BIT_RGB888*/;

    m_PanelAttr.usDotClkRatio   = 7;
    m_PanelAttr.usHBPorch       = 0x3F;
    m_PanelAttr.usHBlanking     = 0x46;
    m_PanelAttr.usHSyncW        = 0;
    m_PanelAttr.usVBPorch       = 13;
    m_PanelAttr.usVBlanking     = 22;
    m_PanelAttr.usVSyncW        = 0;
    m_PanelAttr.usPRT2HdotClk   = 2;

    m_PanelAttr.bDeltaRBG       = MMP_TRUE;
    m_PanelAttr.bDummyRBG       = MMP_TRUE;
    m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
    m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

    m_PanelAttr.usSpi2MciRatio  = 0x80;
    m_PanelAttr.usCsSetupCyc    = 0x0F;
    m_PanelAttr.usCsHoldCyc     = 0x0F;
    m_PanelAttr.usCsHighWidth   = 0xFF;

    m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_OSD;
    m_PanelAttr.usWinStX        = 0;
    m_PanelAttr.usWinStY        = 0;
    m_PanelAttr.usWinW          = LCD_ILI8961_WIDTH;
    m_PanelAttr.usWinH          = LCD_ILI8961_HEIGHT;
    m_PanelAttr.usWinBPP        = 2;
    m_PanelAttr.usWinFmt        = LCD_WIN_FMT_16BPP;
    m_PanelAttr.ulWinAddr       = 0x02500000;

    MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

MSpiSettings_t gtSetting;
MSpiChannel_e geSPIHandle;
#define SPI_writedat SPI_writecom

static void  SPI_INIT(void)
{
     MSpiErrorCode_e eRtn;

    gtSetting.eChannel = MSPI_CH0;
    gtSetting.eMSpiMode = 0;
    gtSetting.ePadSelect = MSPI_PAD2;
    gtSetting.eRWMethod = MSPI_RW_METHOD_POLLING;
    gtSetting.nMspiClk = 200000;

    if(MSPI_PROC_DONE != (eRtn = DrvMSpiOpen(&geSPIHandle,&gtSetting)))
        UartSendTrace(" MSpi Open err  %d \n", eRtn);
}

static void SPI_writecom(u8 u8data)
{
    DrvMSpiWrite(geSPIHandle,u8data,1);
}
static void MMPF_LCD_Write16BitCmd(MMPF_PANEL_ATTR* pAttr, u16 usData)
{
    u8 aWriteBuf[2];
    aWriteBuf[0] = usData >> 8;
    aWriteBuf[1] = usData & 0x00ff;
    DrvMSpiWrite(geSPIHandle,aWriteBuf,2);
}

void RTNA_LCD_Init(void)
{
    //RTNA_DBG_Str(0, "### ---->>>> RTNA_LCD_Init for ...\r\n");

#if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
#else
    RTNA_LCD_InitMainLCD();
#endif
    SPI_INIT();

    //Delay_ms(10);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x051E);
    Delayms(80);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x055D);
    Delayms(80);

    // Normal operation
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x2B01);           // STB(R2Bh[0]): Standby (Power saving) mode control
                                                            // 0: Standby Mode. (default)
                                                            // 1: Normal operation.
    Delayms(80);

#if (LCD_RGB_MODE == STRIP_RGB)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0418);           // 8-bit Dummy RGB
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x2F71);           // Stripe color filter.
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0695);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0746);
#else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x040B);           // 8-bit RGB
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x2F61);           // Delta color filter. (default)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0695);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0746);
#endif

#if (LCD_BRIGETNESS_DEFAULT)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0300 | 0x40);    // Brightness(R03h[7:0]): RGB brightness level control
#else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0300 | 80);      // Brightness(R03h[7:0]): RGB brightness level control
#endif
#if (LCD_CONTRAST_DEFAULT)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0D00 | 0x40);    // CONTRAST(R0Dh[7:0]): RGB contrast level setting, the gain changes (1/64) bit.
#else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0D00 | 75);      // CONTRAST(R0Dh[7:0]): RGB contrast level setting, the gain changes (1/64) bit.
#endif
#if (LCD_VCOM_DEFAULT)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x019C);           // VCDC(R01h[5:0]): VCOM vlotage DC level selection (20mV/step)
#else
    //MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x019F);             // VCDC(R01h[5:0]): VCOM vlotage DC level selection (20mV/step)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x019B);           // VCDC(R01h[5:0]): VCOM vlotage DC level selection (20mV/step) // new setting from Mio, TBD
#endif
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0336);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0B81);

#if (LCD_GAMMA_AUTO)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1604);           // GON_EN(R16h[2]): Gamma op enable Function
                                                            // 0: Manual set gamma by R17h~R1Ah
                                                            // 1: Auto set to gamma2.2. (default)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1757);           // [6:4]: L016_SEL (101)
                                                            // [2:0]: L008_SEL (111)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1875);           // [6:4]: L050_SEL (111)
                                                            // [2:0]: L032_SEL (101)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1944);           // [6:4]: L096_SEL (100)
                                                            // [2:0]: L072_SEL (100)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1A54);           // [6:4]: L120_SEL (101)
                                                            // [2:0]: L110_SEL (100)
#else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1600);           // GON_EN(R16h[2]): Gamma op enable Function
                                                            // 0: Manual set gamma by R17h~R1Ah
                                                            // 1: Auto set to gamma2.2. (default)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1777);           // [6:4]: L016_SEL (101)
                                                            // [2:0]: L008_SEL (111)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1877);           // [6:4]: L050_SEL (111)
                                                            // [2:0]: L032_SEL (101)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1933);           // [6:4]: L096_SEL (100)
                                                            // [2:0]: L072_SEL (100)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x1A43);           // [6:4]: L120_SEL (101)
                                                            // [2:0]: L110_SEL (100)
#endif

    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x9580);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xAF04);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xA522);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xA612);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xA706);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB301);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0xB506);

}

//============================================================================//
#if (ENABLE_LCD_ILI8961_LOG)
#include "Customer_config.h"
#include "mmpf_pio.h"
#endif

void RTNA_LCD_BLACK_LIGHT(MMP_BOOL enable)
{
    if(enable)
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0340);
  else
    MMPF_LCD_Write16BitCmd(&m_PanelAttr,0x0300);
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
#if 0
    DSPY_DECL;
    MMP_UBYTE value;

#if (ENABLE_LCD_ILI8961_LOG)
    RTNA_DBG_Str(0, "### RTNA_LCD_Direction, dir:");
    RTNA_DBG_Short(0, dir);
    RTNA_DBG_Str(0, "\r\n");

    RTNA_DBG_Str(0, "pDSPY->DSPY_RGB_DELTA_MODE at ");
    RTNA_DBG_Long(0, (MMP_ULONG)&(pDSPY->DSPY_RGB_DELTA_MODE));
    RTNA_DBG_Str(0, "\r\n");
    RTNA_DBG_Str(0, "pDSPY->DSPY_RGB_DELTA_MODE = ");
    RTNA_DBG_Long(0, *(AIT_REG_B *)((MMP_ULONG)&(pDSPY->DSPY_RGB_DELTA_MODE)));
    RTNA_DBG_Str(0, "\r\n");
#endif

    switch(dir)
    {
        case LCD_DIR_DOWNLEFT_UPRIGHT:
            // not support;
            break;

        case LCD_DIR_UPRIGHT_DOWNLEFT:
            // not support;
            break;

        case LCD_DIR_DOWNRIGHT_UPLEFT:
        #if (ENABLE_LCD_ILI8961_LOG)
            RTNA_DBG_Str(0, "LCD_DIR_DOWNRIGHT_UPLEFT -\r\n");
        #endif

            value = 0x0C;
        #if (LCD_RGB_MODE == STRIP_RGB)
            DSPY_WR_B(DSPY_RGB_DELTA_MODE, RGB_DUMMY_MODE_ENABLE |
                                           RGB_DELTA_MODE_ENABLE |
                                           SPI_ODD_LINE_RGB |
                                           SPI_EVEN_LINE_RGB);
        #else
            DSPY_WR_B(DSPY_RGB_DELTA_MODE, RGB_DELTA_MODE_ENABLE |
                                           SPI_ODD_LINE_RBG |
                                           SPI_EVEN_LINE_BGR);
            m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RBG;
            m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_BGR;
        #endif

        #if (ENABLE_LCD_ILI8961_LOG)
            RTNA_DBG_Str(0, "pDSPY->DSPY_RGB_DELTA_MODE at ");
            RTNA_DBG_Long(0, (MMP_ULONG) &(pDSPY->DSPY_RGB_DELTA_MODE));
            RTNA_DBG_Str(0, "\r\n");
            RTNA_DBG_Str(0, "pDSPY->DSPY_RGB_DELTA_MODE = ");
            RTNA_DBG_Long(0, *(AIT_REG_B *)((MMP_ULONG)&(pDSPY->DSPY_RGB_DELTA_MODE)));
            RTNA_DBG_Str(0, "\r\n");
        #endif
            break;

        case LCD_DIR_UPLEFT_DOWNRIGHT:
        #if (ENABLE_LCD_ILI8961_LOG)
            RTNA_DBG_Str(0, "LCD_DIR_UPLEFT_DOWNRIGHT -\r\n");
        #endif

            value = 0x0C | 0x03;
        #if (LCD_RGB_MODE == STRIP_RGB)
            DSPY_WR_B(DSPY_RGB_DELTA_MODE, RGB_DUMMY_MODE_ENABLE |
                                           RGB_DELTA_MODE_ENABLE |
                                           SPI_ODD_LINE_RGB |
                                           SPI_EVEN_LINE_RGB);
        #else
            DSPY_WR_B(DSPY_RGB_DELTA_MODE, RGB_DELTA_MODE_ENABLE |
                                           SPI_ODD_LINE_RGB |
                                           SPI_EVEN_LINE_GBR);
            m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;
            m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_GBR;
        #endif
            break;

        default:
            break;
    }

#if (ENABLE_LCD_ILI8961_LOG)
    RTNA_DBG_Str(0, "New pDSPY->DSPY_RGB_DELTA_MODE = ");
    RTNA_DBG_Long(0, *(AIT_REG_B *)((MMP_ULONG)&(pDSPY->DSPY_RGB_DELTA_MODE)));
    RTNA_DBG_Str(0, "\r\n");
#endif

    MMPF_LCD_Write16BitCmd(&m_PanelAttr, (0x04 << 8) | value);
#endif
}

void RTNA_LCD_AdjustBrightness(MMP_UBYTE level)
{
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0300 | level);   // Brightness(R03h[7:0]): RGB brightness level control
}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
    MMP_SHORT Tempvalue;

    Tempvalue = (((reg & 0xFF) << 8) + value);
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, Tempvalue);
}

void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value)
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
    MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0D00 | level);   // CONTRAST(R0Dh[7:0]): RGB contrast level setting, the gain changes (1/64) bit.
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
#if (USE_PWM_FOR_LCD_BACKLIGHT)
        MMPF_PWM_Initialize();
        MMPF_PWM_OutputPulse(LCD_BACKLIGHT_PWM_UNIT_PIN, bEnable, 6000,50, MMP_TRUE, MMP_FALSE, NULL, 0);
#else
        // (LCD_GPIO_BACK_LIGHT == MMP_GPIOxxx) which can not be used in preprocessor
    #if defined(LCD_GPIO_BACK_LIGHT) && defined(LCD_GPIO_BACK_LIGHT_ACT_LEVEL)
                MMPF_PIO_Enable(LCD_GPIO_BACK_LIGHT,MMP_TRUE);
                MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
        #ifdef LCD_GPIO_BACK_LIGHT_ACT_LEVEL
                MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, ((bEnable) ? (LCD_GPIO_BACK_LIGHT_ACT_LEVEL) : !(LCD_GPIO_BACK_LIGHT_ACT_LEVEL)), MMP_TRUE);
        #else
                MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, bEnable, MMP_TRUE);
        #endif
    #endif
        RTNA_DBG_Str(0, "### RTNA_LCD_Backlight \r\n");
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

