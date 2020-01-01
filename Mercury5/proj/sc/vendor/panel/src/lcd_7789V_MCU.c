//==============================================================================
//
//  File        : lcd_ILI9341V_MCU.c
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

#include "Config_SDK.h"
#include "lcd_common.h"
#include "drv_bus_spi.h"
#include "drv_mspi.h"
#include "halPnl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define SECONDARY_DISPLAY       (0)

#define ENABLE_LCD_TEST_PATTERN (0)

#define PANEL_WIDTH             (240)
#define PANEL_HEIGHT            (240)

//==============================================================================
//
//
//
//==============================================================================
static void Lcdst7796vInitIndexCmd(MMP_UBYTE ubController);
static void Lcdst7796vInitSeq(void);
void RTNA_LCD_RGB_Test();
//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMPF_PANEL_ATTR m_PanelAttr =
{
    PANEL_WIDTH,
    PANEL_HEIGHT,
    LCD_TYPE_PLCD,
    LCD_PRM_CONTROLER,
    0,
#if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
    LCD_RATIO_16_9,
#else
    LCD_RATIO_4_3,
#endif

    Lcdst7796vInitSeq,
    Lcdst7796vInitIndexCmd,

    LCD_BUS_WIDTH_8,//LCD_BUS_WIDTH_8,
    LCD_RGB888,     //dummy
    LCD_PHASE1,
    LCD_POLARITY1,
    LCD_MCU_80SYS,
    1,
    3,
    6,
    LCD_RGB_ORDER_RGB,//LCD_RGB_ORDER_RGB

    MMP_FALSE,
    LCD_SIG_POLARITY_H,
    LCD_SIG_POLARITY_L,
    LCD_SIG_POLARITY_L,
    0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_216M,  //ulClkSelect
    0x0,                    //usDotClkRatio
    6750000,                //ulDotClkFreq
    {0}
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
static void WriteCmd(MMP_UBYTE ubData)
{
    DrvPLCD_ConfigIDXCmd(ubData, 1, 1);
    DrvPLCD_SendIndex();
}

static void WriteData(MMP_UBYTE ubData)
{
    DrvPLCD_ConfigIDXCmd(ubData, 2, 0);
    DrvPLCD_SendCmd();
}

static void Sleep(MMP_ULONG ms)
{
    MMP_ULONG ulStartTick;
    MMP_ULONG ulCurTick;
    MMPF_OS_GetTime(&ulStartTick);
    ulCurTick = ulStartTick;
    while (ulCurTick - ulStartTick < ms) {
        MMPF_OS_GetTime(&ulCurTick);
    }
}

static void Lcdst7796vInitIndexCmd(MMP_UBYTE ubController)
{
#if 0
    DSPY_DECL;

    if (ubController == LCD_PRM_CONTROLER)
    {
        DSPY_WR_W(DSPY_LCD_TX_0,         0x2C);
        DSPY_WR_W(DSPY_LCD_AUTO_CFG,     LCD_TX_TYPE_IDX(0));
        DSPY_WR_W(DSPY_PLCD_IDX_CMD_NUM, 1);
    }
#endif
#if 1
    DrvPLCD_SetIDXCmdNum(1);
    DrvPLCD_ConfigIDXCmd(0x2C, 1, 1);
    #endif
}

static void Lcdst7796vInitSeq(void)
{
#if 1
    RTNA_DBG_Str(0, "### RTNA_LCD_Lcd ST7789V InitSeq ...\r\n");

    #if defined(LCD_GPIO_RESET)
    if (LCD_GPIO_RESET != MMP_GPIO_MAX)
    {
        MMPF_PIO_Enable(LCD_GPIO_RESET,MMP_TRUE);
        MMPF_PIO_EnableOutputMode(LCD_GPIO_RESET, MMP_TRUE, MMP_TRUE);
        RTNA_DBG_Str(0, "dbg-set LCD_RST to output mode\r\n");

        MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
        Sleep(20);
        RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

        MMPF_PIO_SetData(LCD_GPIO_RESET, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
        Sleep(100);
        RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

        MMPF_PIO_SetData(LCD_GPIO_RESET, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
        Sleep(50);
        RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
    }
    #endif
#if 1


WriteCmd( 0xB2);
WriteData(0x0C);   //porch setting
WriteData( 0x0C);
WriteData( 0x00);
WriteData( 0x33);
WriteData( 0x33);

WriteCmd(  0xB7);
WriteData( 0x02);   //64;VGH&VGL,12V&-8V

WriteCmd(  0xC2);
WriteData( 0x01);

WriteCmd(  0xBB);
WriteData( 0x28);   // 0x35 0x3C 28;VCOM

WriteCmd(  0xC3);
WriteData( 0x13);  //0x19 0x27

WriteCmd(  0xC4);
WriteData( 0x20);  //0x3F

WriteCmd(  0xC5);
WriteData( 0x20);   //vcom shift.0V  20

WriteCmd( 0xD0);
WriteData( 0xA4);
WriteData( 0xA2);   //AVDD&AVCL,6.8v&-4.8v

WriteCmd(  0xD2);
WriteData( 0x4C);

WriteCmd(  0xE8);
WriteData( 0x83);   //Booster CLK Select

WriteCmd(  0xE9);
WriteData( 0x09);   //EQ
WriteData( 0x09);
WriteData( 0x08);

WriteCmd(  0x36);
WriteData( 0x00);   //ACCESS

WriteCmd(  0x35);
WriteData( 0x00);   //TEWrite

WriteCmd(  0x3A);
WriteData( 0x05);   //16bit


WriteCmd( 0xC6);
WriteData( 0x0F);   //0x09orig [DB7-5] 0forDotInv,1forColumnInv ,0xEF  蹈楹


WriteCmd( 0xE0);
WriteData( 0xD0);   //V0[7-4] & V63[3-0]
WriteData( 0x06);   //V62[5-0]
WriteData( 0x0C);   //V61[5-0]
WriteData( 0x09);   //V59[4-0]
WriteData( 0x09);   //V57[4-0]
WriteData( 0x25);   //J1[5-4] & V50[3-0]
WriteData( 0x2E);   //V43[6-0]
WriteData( 0x33);   //V27[6-4] & V36[2-0]
WriteData( 0x45);   //V20[6-0]
WriteData( 0x36);   //J0[5-4] & V13[3-0]
WriteData( 0x12);   //V6[4-0]
WriteData( 0x12);   //V4[4-0]
WriteData( 0x2E);   //V2[5-0]
WriteData( 0x34);   //V1[5-0]

WriteCmd( 0xE1);
WriteData( 0xD0);   //V0[7-4] & V63[3-0]
WriteData( 0x06);   //V62[5-0]
WriteData( 0x0C);   //V61[5-0]
WriteData( 0x09);   //V59[4-0]
WriteData( 0x09);   //V57[4-0]
WriteData( 0x25);   //J1[5-4] & V50[3-0]
WriteData( 0x2E);   //V43[6-0]
WriteData( 0x33);   //V27[6-4] & V36[2-0]
WriteData( 0x45);   //V20[6-0]
WriteData( 0x36);   //J0[5-4] & V13[3-0]
WriteData( 0x12);   //V6[4-0]
WriteData( 0x12);   //V4[4-0]
WriteData( 0x2E);   //V2[5-0]
WriteData( 0x34);   //V1[5-0]

WriteCmd( 0x21);

WriteCmd( 0xD6);
WriteData( 0xA1);

#if 1
WriteCmd( 0x2A);     //Column Address Set
WriteData( 0x00);
WriteData( 0x00);   //0
WriteData( 0x01);
WriteData( 0x40);   //239

WriteCmd( 0x2B);     //Row Address Set
WriteData( 0x00);
WriteData( 0x00);   //0
WriteData( 0x01);
WriteData( 0x40);   //239
#endif


WriteCmd( 0x11);
Sleep(120);

WriteCmd( 0x29);


//WriteCmd( 0x2c);


#else

WriteCmd( 0xB2);
WriteData( 0x0C);   //porch setting
WriteData( 0x0C);
WriteData( 0x00);
WriteData( 0x33);
WriteData( 0x33);

WriteCmd( 0xB7);
WriteData( 0x02);   //64;VGH&VGL,12V&-8V

WriteCmd( 0xC2);
WriteData( 0x01);

WriteCmd( 0xBB);
WriteData( 0x28);   // 0x35 0x3C 28;VCOM

WriteCmd( 0xC3);
WriteData( 0x13);  //0x19 0x27

WriteCmd( 0xC4);
WriteData( 0x20);  //0x3F

WriteCmd( 0xC5);
WriteData( 0x20);   //vcom shift.0V  20

WriteCmd( 0xD0);
WriteData( 0xA4);
WriteData( 0xA2);   //AVDD&AVCL,6.8v&-4.8v

WriteCmd( 0xD2);
WriteData( 0x4C);

WriteCmd( 0xE8);
WriteData( 0x83);   //Booster CLK Select

WriteCmd( 0xE9);
WriteData( 0x09);   //EQ
WriteData( 0x09);
WriteData( 0x08);

WriteCmd( 0x36);
WriteData( 0x00);   //ACCESS

WriteCmd( 0x35);
WriteData( 0x00);   //TEWrite

WriteCmd( 0x3A);
WriteData( 0x05);   //18bit

WriteCmd( 0xC6);
WriteData( 0x0F);   //0x09orig [DB7-5] 0forDotInv,1forColumnInv ,0xEF  ??

WriteCmd( 0xE0);
WriteData( 0xD0);   //V0[7-4] & V63[3-0]
WriteData( 0x06);   //V62[5-0]
WriteData( 0x0C);   //V61[5-0]
WriteData( 0x09);   //V59[4-0]
WriteData( 0x09);   //V57[4-0]
WriteData( 0x25);   //J1[5-4] & V50[3-0]
WriteData( 0x2E);   //V43[6-0]
WriteData( 0x33);   //V27[6-4] & V36[2-0]
WriteData( 0x45);   //V20[6-0]
WriteData( 0x36);   //J0[5-4] & V13[3-0]
WriteData( 0x12);   //V6[4-0]
WriteData( 0x12);   //V4[4-0]
WriteData( 0x2E);   //V2[5-0]
WriteData( 0x34);   //V1[5-0]

WriteCmd( 0xE1);
WriteData( 0xD0);   //V0[7-4] & V63[3-0]
WriteData( 0x06);   //V62[5-0]
WriteData( 0x0C);   //V61[5-0]
WriteData( 0x09);   //V59[4-0]
WriteData( 0x09);   //V57[4-0]
WriteData( 0x25);   //J1[5-4] & V50[3-0]
WriteData( 0x2E);   //V43[6-0]
WriteData( 0x33);   //V27[6-4] & V36[2-0]
WriteData( 0x45);   //V20[6-0]
WriteData( 0x36);   //J0[5-4] & V13[3-0]
WriteData( 0x12);   //V6[4-0]
WriteData( 0x12);   //V4[4-0]
WriteData( 0x2E);   //V2[5-0]
WriteData( 0x34);   //V1[5-0]

WriteCmd( 0x21);

WriteCmd( 0xD6);
WriteData( 0xA1);

WriteCmd( 0x11);
Sleep(120);

WriteCmd( 0x29);
#endif


#endif
}

void RTNA_LCD_InitMainLCD(void)
{
    m_PanelAttr.ubDispWinId     = LCD_DISP_WIN_PIP;
    m_PanelAttr.usWinStX        = 0;
    m_PanelAttr.usWinStY        = 0;
    m_PanelAttr.usWinW          = PANEL_WIDTH;
    m_PanelAttr.usWinH          = PANEL_HEIGHT;
    m_PanelAttr.usWinBPP        = 2;
    m_PanelAttr.usWinFmt        = LCD_WIN_FMT_8BPP;
    m_PanelAttr.ulWinAddr       = 0x03000000;//0x03000000;
    #ifdef FLM_GPIO_NUM
    //m_PanelAttr.ulFLMGPIO     = FLM_GPIO_NUM;
    #else
    //m_PanelAttr.ulFLMGPIO     = MMP_GPIO_MAX;
    #endif
    m_PanelAttr.ubPlcdFmt       = PLCD_RGB565_BUS8_CFG;//PLCD_RGB565_BUS8;//PLCD_RGB565_BUS16;

    MMPF_LCD_InitPanel(&m_PanelAttr);
}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)

#endif

}

void RTNA_LCD_Init(void)
{
    RTNA_DBG_Str(0, "### RTNA_LCD_Init for ST7789V 240x240 ...\r\n");

    #if (SECONDARY_DISPLAY == 1)
    RTNA_LCD_Init2ndLCD();
    #else
    RTNA_LCD_InitMainLCD();
    #endif
}

void RTNA_LCD_RGB_Test(void)
{
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
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

MMPF_PANEL_ATTR* RTNA_LCD_GetAttr(void)
{
    return &m_PanelAttr;
}

