//==============================================================================
//
//  File        : lcd_HST430BL_480x272.c
//  Description : HST 4"3 480x272 DE only RGB LCD Panel Control Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "Customer_config.h" // CarDV
//#include "lib_retina.h"
#include "lcd_common.h"
//#include "mmpf_pio.h"
#include "drv_bus_spi.h"
#include "drv_mspi.h"
#include "halpnl.h"
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define Delayms(t) 					LCD_WAIT(t)

#define SECONDARY_DISPLAY 			(0)

#define PANEL_WIDTH                 480
#define PANEL_HEIGHT                854

#define _SUPPORT_SW_SPI    0
#if 0
#define LSCE_GPIO_PIN   (MMP_GPIO124)
#define LSCK_GPIO_PIN   (MMP_GPIO122)
#define LSDA_GPIO_PIN   (MMP_GPIO123)

#define LSDR_GPIO_PIN   (MMP_GPIO31)//(MMP_GPIO28)
#else

#define LSCE_GPIO_PIN   (0)
#define LSCK_GPIO_PIN   (0)
#define LSDA_GPIO_PIN   (0)

#define LSDR_GPIO_PIN   (0)//(MMP_GPIO28)

#if 0
#define LSCE_GPIO_PIN   (MMP_GPIO62)//CS40
#define LSCK_GPIO_PIN   (MMP_GPIO124)//SCL39
#define LSDA_GPIO_PIN   (MMP_GPIO123)//SDI38
#define LSDR_GPIO_PIN   (MMP_GPIO122)//RES37
#endif
#endif
/*#define LSCE_GPIO_PIN   (MMP_GPIO124)//CS39
#define LSCK_GPIO_PIN   (MMP_GPIO122))//SCL37
#define LSDA_GPIO_PIN   (MMP_GPIO123))//SDI38
#define LSDR_GPIO_PIN   (MMP_GPIO62))//RES40*/

#define Delay_us(n)   (0) //MMPF_OS_Sleep_MS(n)	//(lcm_util.udelay(n))
#define Delay_ms(n)   (0) //MMPF_OS_Sleep_MS(n)	//(lcm_util.mdelay(n))


typedef unsigned char u8;
typedef int i32;
typedef unsigned int u32;
#define NULL 0

static MMPF_PANEL_ATTR m_PanelAttr =
{
	// Panel basic setting
	PANEL_WIDTH, PANEL_HEIGHT,
	LCD_TYPE_CCIR601,
	LCD_PRM_CONTROLER,
	0,

	// CarDV
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
	LCD_YUV422_D16BIT_UY0_VY1,	//ubBusCfg
    LCD_PHASE0,			//ubPhase
    LCD_POLARITY0,		//ubPolarity
    LCD_MCU_80SYS,		//ubMCUSystem
    0,					//usRsLeadCsCnt
    0,					//usCsLeadRwCnt
    0,					//usRwCycCnt
    LCD_RGB_ORDER_RGB,	//ubRgbOrder

	// RGB interface
    MMP_FALSE,				//bPartialDisp
	LCD_SIG_POLARITY_L,     // DCLK Polarity
	LCD_SIG_POLARITY_L,     // H-Sync Polarity
	LCD_SIG_POLARITY_L,     // V-Sync Polarity
    0x02/*RGB_D24BIT_RGB565*/,	//ubRgbFmt
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

	{0}
};

#define ENABLE_LCD_LOG       		(1)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN 	(1)
#else
#define ENABLE_LCD_TEST_PATTERN 	(0)
#endif

#if (ENABLE_LCD_LOG)
#define LCD_DBG_LEVEL               (0)
#else
#define LCD_DBG_LEVEL               (3)
#endif

static void Set_RST(unsigned long index)
{
    #if 0
	if(index) MMPF_PIO_SetData(LSDR_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x8000;
	else      MMPF_PIO_SetData(LSDR_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x8000;
    #endif
}

static void Set_CS(unsigned long index)
{
    #if 0
	if(index) MMPF_PIO_SetData(LSCE_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x8000;
	else       MMPF_PIO_SetData(LSCE_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x8000;
    #endif
}

static void Set_SCL(unsigned long index)
{
    #if 0
	if(index) MMPF_PIO_SetData(LSCK_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x2000;
	else       MMPF_PIO_SetData(LSCK_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x2000;
    #endif
}

static void Set_SDI(unsigned long index)
{
    #if 0
	if(index) MMPF_PIO_SetData(LSDA_GPIO_PIN, GPIO_HIGH, MMP_TRUE);//rGPEDAT |= 0x1000;
	else      MMPF_PIO_SetData(LSDA_GPIO_PIN, GPIO_LOW, MMP_TRUE);//rGPEDAT &= ~0x1000;
    #endif
}


static void SPI_Init(void)
{

	#if 0
	MMPF_PIO_EnableOutputMode(LSCE_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSCK_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSDA_GPIO_PIN, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(LSDR_GPIO_PIN, MMP_TRUE, MMP_TRUE);

	Set_RST(0);
	Delay_ms(100);
	Set_RST(1);

	Set_CS(1);
	//Set_CSX(1);
	Set_SCL(1);
	Set_SDI(1);
	#endif
}

static void SPI_3W_wrByte(unsigned char cmd)
{
	unsigned long kk;


	Set_SCL(0);
	for(kk=0;kk<8;kk++)
	{
		if(cmd&0x80) Set_SDI(1);
		else         Set_SDI(0);
		cmd<<=1;
		Set_SCL(0);	Delay_us(5);

		Set_SCL(1);	Delay_us(5);
	//	cmd = cmd<<1;
	}
}

/*static void write_spicom(unsigned short addr)
{
	Set_CS(0);
	Set_SCL(0);
    Set_SDI(0);
    Delay_us(5);
    Set_SCL(1);
    Delay_us(5);
	SPI_3W_wrByte(addr);
	Set_CS(1);
}

static void write_spidat(unsigned char value)
{
	Set_CS(0);
	Set_SCL(0);
    Set_SDI(1);
    Delay_us(5);
    Set_SCL(1);
    Delay_us(5);
	SPI_3W_wrByte(value);
	Set_CS(1);
}*/
#if _SUPPORT_SW_SPI
static void SPI_writedat(unsigned int value)
{
	unsigned int i;

	Set_CS(1);
	Delay_us(1);
	Set_CS(0);
	Set_SDI(1);
	Set_SCL(0);
	Delay_us(1);
	for(i=0;i<16;i++)
	{
		Delay_us(10);
		Set_SCL(0);
		if(value & 0x8000)
			Set_SDI(1);
		else
			Set_SDI(0);
		Delay_us(3);
		Set_SCL(1);
		value <<= 1;
	}

	Set_CS(1);
	Delay_us(5);
}

static void SPI_writecom(unsigned int value)
{
	unsigned int i;
	Set_CS(1);
	Delay_us(1);
	Set_CS(0);
	Set_SDI(1);
	Set_SCL(0);

	Delay_us(1);

	for(i=0;i<16;i++)
	{
		Delay_us(10);
		Set_SCL(0);
		if(value & 0x8000)
			Set_SDI(1);
		else
			Set_SDI(0);

		Delay_us(3);
		Set_SCL(1);
		value <<= 1;

	}

	Set_CS(1);
	Delay_us(5);
}
#else

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

static void SPI_writecom(u16 u16data)
{
	u8 aWriteBuf[2];
	aWriteBuf[0] = u16data >> 8;
	aWriteBuf[1] = u16data & 0x00ff;
	DrvMSpiWrite(geSPIHandle,aWriteBuf,2);
}
#endif
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	//RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD CCIR 601 \r\n");

	m_PanelAttr.ulDotClkFreq 	= 28000000;
	m_PanelAttr.ubBusCfg		= LCD_YUV422_D16BIT_UY0_VY1;//LCD_TYPE_RGBLCD & LCD_TYPE_CCIR601 need to setting only.
	m_PanelAttr.ubRgbOrder		= LCD_RGB_ORDER_RGB;//LCD_TYPE_PLCD  & LCD_TYPE_PLCD_FLM need to setting only.

	// RGB interface
	m_PanelAttr.usHBPorch 		= 4; //Horizontal back porch must larger than 4 in CCIR601 mode
	m_PanelAttr.usHBlanking 	= 25;
	m_PanelAttr.usHSyncW 		= 3;
	m_PanelAttr.usVBPorch 		= 16;
	m_PanelAttr.usVBlanking 	= 96;
	m_PanelAttr.usVSyncW 		= 3;
	m_PanelAttr.usPRT2HdotClk 	= 2;

	m_PanelAttr.bDeltaRBG 		= MMP_FALSE;
	m_PanelAttr.bDummyRBG 		= MMP_FALSE;

	m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
	m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

	// Window setting (For drawing test pattern)
	m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;
	m_PanelAttr.usWinStX 		= 0;
	m_PanelAttr.usWinStY 		= 0;
	m_PanelAttr.usWinW 			= PANEL_WIDTH;
	m_PanelAttr.usWinH 			= PANEL_HEIGHT;
	m_PanelAttr.usWinBPP 		= 2;
	m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;
	m_PanelAttr.ulWinAddr 		= 0x03000000;

	// CarDV
	#if ((16 == LCD_MODEL_RATIO_X) && (9 == LCD_MODEL_RATIO_Y))
	m_PanelAttr.ubRatio 		= LCD_RATIO_16_9;
	#else
	m_PanelAttr.ubRatio 		= LCD_RATIO_4_3;
	#endif

	MMPF_LCD_InitPanel(&m_PanelAttr);
#endif
}

void RTNA_LCD_Init2ndLCD(void)
{
#if (SECONDARY_DISPLAY == 1)
    // TBD
#endif
}



static void Lcd_init(void)
{

    SPI_INIT();
#if 1
	/**************************************************
	IC Name: RM68172
	Panel Maker/Size: IVO498
	Panel Product No.:
	Version: C050SWY8-1
	Date: V0_140930
	**************************************************/
	SPI_writecom(0x2001); SPI_writecom(0x0000);SPI_writedat(0x4000);

	SPI_writecom(0x20F0);SPI_writecom(0x0000); SPI_writedat(0x4055);
	SPI_writecom(0x20F0);SPI_writecom(0x0001); SPI_writedat(0x40AA);
	SPI_writecom(0x20F0);SPI_writecom(0x0002); SPI_writedat(0x4052);
	SPI_writecom(0x20F0);SPI_writecom(0x0003); SPI_writedat(0x4008);
	SPI_writecom(0x20F0);SPI_writecom(0x0004); SPI_writedat(0x4002);

	SPI_writecom(0x20F6);SPI_writecom(0x0000); SPI_writedat(0x4060);
	SPI_writecom(0x20F6);SPI_writecom(0x0001); SPI_writedat(0x4040);

	SPI_writecom(0x20FE);SPI_writecom(0x0000); SPI_writedat(0x4001);
	SPI_writecom(0x20FE);SPI_writecom(0x0001); SPI_writedat(0x4080);
	SPI_writecom(0x20FE);SPI_writecom(0x0002); SPI_writedat(0x4009);
	//SPI_writecom(0x20FE);SPI_writecom(0x0003); SPI_writedat(0x4009);
		SPI_writecom(0x20FE);SPI_writecom(0x0003); SPI_writedat(0x4018);
			SPI_writecom(0x20FE);SPI_writecom(0x0004); SPI_writedat(0x40a0);

	//sunxi_lcd_delay_ms(200);

	SPI_writecom(0x20F0);SPI_writecom(0x0000); SPI_writedat(0x4055);
	SPI_writecom(0x20F0);SPI_writecom(0x0001); SPI_writedat(0x40AA);
	SPI_writecom(0x20F0);SPI_writecom(0x0002); SPI_writedat(0x4052);
	SPI_writecom(0x20F0);SPI_writecom(0x0003); SPI_writedat(0x4008);
	SPI_writecom(0x20F0);SPI_writecom(0x0004); SPI_writedat(0x4001);

	SPI_writecom(0x20B0);SPI_writecom(0x0000); SPI_writedat(0x400A);
	//PCKP fetch polarity: 0: data latch at rising edge of PCLK
	//1: data latch at falling edge of PCLK
	SPI_writecom(0x20B1);SPI_writecom(0x0000); SPI_writedat(0x400A);

	SPI_writecom(0x20B5);SPI_writecom(0x0000); SPI_writedat(0x4008);

	SPI_writecom(0x20B6);SPI_writecom(0x0000); SPI_writedat(0x4054);

	SPI_writecom(0x20B7);SPI_writecom(0x0000); SPI_writedat(0x4044);

	SPI_writecom(0x20B8);SPI_writecom(0x0000); SPI_writedat(0x4024);

	SPI_writecom(0x20B9);SPI_writecom(0x0000); SPI_writedat(0x4034);

	SPI_writecom(0x20BA);SPI_writecom(0x0000); SPI_writedat(0x4014);

       #if 1
	SPI_writecom(0x20BC);SPI_writecom(0x0000); SPI_writedat(0x4000);
       #else
        //zigZag mode test used
	SPI_writecom(0x20BC);SPI_writecom(0x0000); SPI_writedat(0x4005);
	SPI_writecom(0x20C7);SPI_writecom(0x0000); SPI_writedat(0x4000);

       #endif
	SPI_writecom(0x20BC);SPI_writecom(0x0001); SPI_writedat(0x4098);//A8
	SPI_writecom(0x20BC);SPI_writecom(0x0002); SPI_writedat(0x4013);

	SPI_writecom(0x20BD);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20BD);SPI_writecom(0x0001); SPI_writedat(0x4090);
	SPI_writecom(0x20BD);SPI_writecom(0x0002); SPI_writedat(0x401A);

	SPI_writecom(0x20BE);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20BE);SPI_writecom(0x0001); SPI_writedat(0x401A);

	SPI_writecom(0x20D1);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D1);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D1);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D1);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D1);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D1);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D1);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D1);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D1);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D1);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D1);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D1);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D1);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D1);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D1);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D1);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D1);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D1);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D1);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D1);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D1);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D1);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D1);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D1);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D1);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D1);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D1);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D1);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D1);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D1);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D1);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D1);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D1);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D1);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D1);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D1);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D1);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	SPI_writecom(0x20D2);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D2);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D2);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D2);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D2);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D2);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D2);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D2);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D2);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D2);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D2);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D2);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D2);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D2);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D2);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D2);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D2);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D2);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D2);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D2);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D2);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D2);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D2);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D2);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D2);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D2);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D2);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D2);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D2);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D2);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D2);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D2);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D2);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D2);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D2);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D2);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D2);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	SPI_writecom(0x20D3);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D3);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D3);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D3);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D3);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D3);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D3);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D3);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D3);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D3);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D3);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D3);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D3);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D3);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D3);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D3);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D3);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D3);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D3);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D3);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D3);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D3);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D3);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D3);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D3);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D3);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D3);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D3);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D3);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D3);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D3);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D3);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D3);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D3);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D3);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D3);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D3);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	SPI_writecom(0x20D4);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D4);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D4);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D4);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D4);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D4);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D4);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D4);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D4);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D4);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D4);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D4);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D4);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D4);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D4);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D4);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D4);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D4);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D4);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D4);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D4);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D4);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D4);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D4);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D4);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D4);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D4);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D4);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D4);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D4);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D4);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D4);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D4);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D4);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D4);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D4);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D4);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	SPI_writecom(0x20D5);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D5);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D5);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D5);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D5);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D5);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D5);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D5);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D5);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D5);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D5);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D5);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D5);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D5);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D5);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D5);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D5);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D5);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D5);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D5);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D5);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D5);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D5);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D5);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D5);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D5);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D5);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D5);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D5);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D5);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D5);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D5);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D5);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D5);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D5);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D5);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D5);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	SPI_writecom(0x20D6);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0003); SPI_writedat(0x4017);
	SPI_writecom(0x20D6);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0005); SPI_writedat(0x403E);
	SPI_writecom(0x20D6);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0007); SPI_writedat(0x405E);
	SPI_writecom(0x20D6);SPI_writecom(0x0008); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x0009); SPI_writedat(0x407B);
	SPI_writecom(0x20D6);SPI_writecom(0x000A); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x000B); SPI_writedat(0x40A9);
	SPI_writecom(0x20D6);SPI_writecom(0x000C); SPI_writedat(0x4000);
	SPI_writecom(0x20D6);SPI_writecom(0x000D); SPI_writedat(0x40CE);
	SPI_writecom(0x20D6);SPI_writecom(0x000E); SPI_writedat(0x4001);
	SPI_writecom(0x20D6);SPI_writecom(0x000F); SPI_writedat(0x400A);
	SPI_writecom(0x20D6);SPI_writecom(0x0010); SPI_writedat(0x4001);
	SPI_writecom(0x20D6);SPI_writecom(0x0011); SPI_writedat(0x4037);
	SPI_writecom(0x20D6);SPI_writecom(0x0012); SPI_writedat(0x4001);
	SPI_writecom(0x20D6);SPI_writecom(0x0013); SPI_writedat(0x407C);
	SPI_writecom(0x20D6);SPI_writecom(0x0014); SPI_writedat(0x4001);
	SPI_writecom(0x20D6);SPI_writecom(0x0015); SPI_writedat(0x40B0);
	SPI_writecom(0x20D6);SPI_writecom(0x0016); SPI_writedat(0x4001);
	SPI_writecom(0x20D6);SPI_writecom(0x0017); SPI_writedat(0x40FF);
	SPI_writecom(0x20D6);SPI_writecom(0x0018); SPI_writedat(0x4002);
	SPI_writecom(0x20D6);SPI_writecom(0x0019); SPI_writedat(0x403D);
	SPI_writecom(0x20D6);SPI_writecom(0x001A); SPI_writedat(0x4002);
	SPI_writecom(0x20D6);SPI_writecom(0x001B); SPI_writedat(0x403F);
	SPI_writecom(0x20D6);SPI_writecom(0x001C); SPI_writedat(0x4002);
	SPI_writecom(0x20D6);SPI_writecom(0x001D); SPI_writedat(0x407C);
	SPI_writecom(0x20D6);SPI_writecom(0x001E); SPI_writedat(0x4002);
	SPI_writecom(0x20D6);SPI_writecom(0x001F); SPI_writedat(0x40C4);
	SPI_writecom(0x20D6);SPI_writecom(0x0020); SPI_writedat(0x4002);
	SPI_writecom(0x20D6);SPI_writecom(0x0021); SPI_writedat(0x40F6);
	SPI_writecom(0x20D6);SPI_writecom(0x0022); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0023); SPI_writedat(0x403A);
	SPI_writecom(0x20D6);SPI_writecom(0x0024); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0025); SPI_writedat(0x4068);
	SPI_writecom(0x20D6);SPI_writecom(0x0026); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0027); SPI_writedat(0x40A0);
	SPI_writecom(0x20D6);SPI_writecom(0x0028); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0029); SPI_writedat(0x40BF);
	SPI_writecom(0x20D6);SPI_writecom(0x002A); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x002B); SPI_writedat(0x40E0);
	SPI_writecom(0x20D6);SPI_writecom(0x002C); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x002D); SPI_writedat(0x40EC);
	SPI_writecom(0x20D6);SPI_writecom(0x002E); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x002F); SPI_writedat(0x40F5);
	SPI_writecom(0x20D6);SPI_writecom(0x0030); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0031); SPI_writedat(0x40FA);
	SPI_writecom(0x20D6);SPI_writecom(0x0032); SPI_writedat(0x4003);
	SPI_writecom(0x20D6);SPI_writecom(0x0033); SPI_writedat(0x40FF);

	//sunxi_lcd_delay_ms(200);

	SPI_writecom(0x20F0);SPI_writecom(0x0000); SPI_writedat(0x4055);
	SPI_writecom(0x20F0);SPI_writecom(0x0001); SPI_writedat(0x40AA);
	SPI_writecom(0x20F0);SPI_writecom(0x0002); SPI_writedat(0x4052);
	SPI_writecom(0x20F0);SPI_writecom(0x0003); SPI_writedat(0x4008);
	SPI_writecom(0x20F0);SPI_writecom(0x0004); SPI_writedat(0x4003);

	SPI_writecom(0x20B0);SPI_writecom(0x0000); SPI_writedat(0x4005);
	SPI_writecom(0x20B0);SPI_writecom(0x0001); SPI_writedat(0x4017);
	SPI_writecom(0x20B0);SPI_writecom(0x0002); SPI_writedat(0x40F9);
	SPI_writecom(0x20B0);SPI_writecom(0x0003); SPI_writedat(0x4053);
	SPI_writecom(0x20B0);SPI_writecom(0x0004); SPI_writedat(0x4053);
	SPI_writecom(0x20B0);SPI_writecom(0x0005); SPI_writedat(0x4000);
	SPI_writecom(0x20B0);SPI_writecom(0x0006); SPI_writedat(0x4030);

	SPI_writecom(0x20B1);SPI_writecom(0x0000); SPI_writedat(0x4005);
	SPI_writecom(0x20B1);SPI_writecom(0x0001); SPI_writedat(0x4017);
	SPI_writecom(0x20B1);SPI_writecom(0x0002); SPI_writedat(0x40FB);
	SPI_writecom(0x20B1);SPI_writecom(0x0003); SPI_writedat(0x4055);
	SPI_writecom(0x20B1);SPI_writecom(0x0004); SPI_writedat(0x4053);
	SPI_writecom(0x20B1);SPI_writecom(0x0005); SPI_writedat(0x4000);
	SPI_writecom(0x20B1);SPI_writecom(0x0006); SPI_writedat(0x4030);

	SPI_writecom(0x20B2);SPI_writecom(0x0000); SPI_writedat(0x40FB);
	SPI_writecom(0x20B2);SPI_writecom(0x0001); SPI_writedat(0x40FC);
	SPI_writecom(0x20B2);SPI_writecom(0x0002); SPI_writedat(0x40FD);
	SPI_writecom(0x20B2);SPI_writecom(0x0003); SPI_writedat(0x40FE);
	SPI_writecom(0x20B2);SPI_writecom(0x0004); SPI_writedat(0x40F0);
	SPI_writecom(0x20B2);SPI_writecom(0x0005); SPI_writedat(0x4053);
	SPI_writecom(0x20B2);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20B2);SPI_writecom(0x0007); SPI_writedat(0x40C5);
	SPI_writecom(0x20B2);SPI_writecom(0x0008); SPI_writedat(0x4008);

	SPI_writecom(0x20B3);SPI_writecom(0x0000); SPI_writedat(0x405B);
	SPI_writecom(0x20B3);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20B3);SPI_writecom(0x0002); SPI_writedat(0x40FB);
	SPI_writecom(0x20B3);SPI_writecom(0x0003); SPI_writedat(0x405A);
	SPI_writecom(0x20B3);SPI_writecom(0x0004); SPI_writedat(0x405A);
	SPI_writecom(0x20B3);SPI_writecom(0x0005); SPI_writedat(0x400C);

	SPI_writecom(0x20B4);SPI_writecom(0x0000); SPI_writedat(0x40FF);
	SPI_writecom(0x20B4);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20B4);SPI_writecom(0x0002); SPI_writedat(0x4001);
	SPI_writecom(0x20B4);SPI_writecom(0x0003); SPI_writedat(0x4002);
	SPI_writecom(0x20B4);SPI_writecom(0x0004); SPI_writedat(0x40C0);
	SPI_writecom(0x20B4);SPI_writecom(0x0005); SPI_writedat(0x4040);
	SPI_writecom(0x20B4);SPI_writecom(0x0006); SPI_writedat(0x4005);
	SPI_writecom(0x20B4);SPI_writecom(0x0007); SPI_writedat(0x4008);
	SPI_writecom(0x20B4);SPI_writecom(0x0008); SPI_writedat(0x4053);

	SPI_writecom(0x20B5);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20B5);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20B5);SPI_writecom(0x0002); SPI_writedat(0x40FF);
	SPI_writecom(0x20B5);SPI_writecom(0x0003); SPI_writedat(0x4083);
	SPI_writecom(0x20B5);SPI_writecom(0x0004); SPI_writedat(0x405F);
	SPI_writecom(0x20B5);SPI_writecom(0x0005); SPI_writedat(0x405E);
	SPI_writecom(0x20B5);SPI_writecom(0x0006); SPI_writedat(0x4050);
	SPI_writecom(0x20B5);SPI_writecom(0x0007); SPI_writedat(0x4050);
	SPI_writecom(0x20B5);SPI_writecom(0x0008); SPI_writedat(0x4033);
	SPI_writecom(0x20B5);SPI_writecom(0x0009); SPI_writedat(0x4033);
	SPI_writecom(0x20B5);SPI_writecom(0x000A); SPI_writedat(0x4055);

	SPI_writecom(0x20B6);SPI_writecom(0x0000); SPI_writedat(0x40BC);
	SPI_writecom(0x20B6);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20B6);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20B6);SPI_writecom(0x0003); SPI_writedat(0x4000);
	SPI_writecom(0x20B6);SPI_writecom(0x0004); SPI_writedat(0x402A);
	SPI_writecom(0x20B6);SPI_writecom(0x0005); SPI_writedat(0x4080);
	SPI_writecom(0x20B6);SPI_writecom(0x0006); SPI_writedat(0x4000);

	SPI_writecom(0x20B7);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0001); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0002); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0003); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0004); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0005); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0006); SPI_writedat(0x4000);
	SPI_writecom(0x20B7);SPI_writecom(0x0007); SPI_writedat(0x4000);

	SPI_writecom(0x20B8);SPI_writecom(0x0000); SPI_writedat(0x4011);
	SPI_writecom(0x20B8);SPI_writecom(0x0001); SPI_writedat(0x4060);
	SPI_writecom(0x20B8);SPI_writecom(0x0002); SPI_writedat(0x4000);

	SPI_writecom(0x20B9);SPI_writecom(0x0000); SPI_writedat(0x4090);

	SPI_writecom(0x20BA);SPI_writecom(0x0000); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x0001); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x0002); SPI_writedat(0x4008);
	SPI_writecom(0x20BA);SPI_writecom(0x0003); SPI_writedat(0x40AC);
	SPI_writecom(0x20BA);SPI_writecom(0x0004); SPI_writedat(0x40E2);
	SPI_writecom(0x20BA);SPI_writecom(0x0005); SPI_writedat(0x4064);
	SPI_writecom(0x20BA);SPI_writecom(0x0006); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x0007); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x0008); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x0009); SPI_writedat(0x4044);
	SPI_writecom(0x20BA);SPI_writecom(0x000A); SPI_writedat(0x4047);
	SPI_writecom(0x20BA);SPI_writecom(0x000B); SPI_writedat(0x403F);
	SPI_writecom(0x20BA);SPI_writecom(0x000C); SPI_writedat(0x40DB);
	SPI_writecom(0x20BA);SPI_writecom(0x000D); SPI_writedat(0x4091);
	SPI_writecom(0x20BA);SPI_writecom(0x000E); SPI_writedat(0x4054);
	SPI_writecom(0x20BA);SPI_writecom(0x000F); SPI_writedat(0x4044);

	SPI_writecom(0x20BB);SPI_writecom(0x0000); SPI_writedat(0x4044);
	SPI_writecom(0x20BB);SPI_writecom(0x0001); SPI_writedat(0x4043);
	SPI_writecom(0x20BB);SPI_writecom(0x0002); SPI_writedat(0x4079);
	SPI_writecom(0x20BB);SPI_writecom(0x0003); SPI_writedat(0x40FD);
	SPI_writecom(0x20BB);SPI_writecom(0x0004); SPI_writedat(0x40B5);
	SPI_writecom(0x20BB);SPI_writecom(0x0005); SPI_writedat(0x4014);
	SPI_writecom(0x20BB);SPI_writecom(0x0006); SPI_writedat(0x4044);
	SPI_writecom(0x20BB);SPI_writecom(0x0007); SPI_writedat(0x4044);
	SPI_writecom(0x20BB);SPI_writecom(0x0008); SPI_writedat(0x4044);
	SPI_writecom(0x20BB);SPI_writecom(0x0009); SPI_writedat(0x4044);
	SPI_writecom(0x20BB);SPI_writecom(0x000A); SPI_writedat(0x4040);
	SPI_writecom(0x20BB);SPI_writecom(0x000B); SPI_writedat(0x404A);
	SPI_writecom(0x20BB);SPI_writecom(0x000C); SPI_writedat(0x40CE);
	SPI_writecom(0x20BB);SPI_writecom(0x000D); SPI_writedat(0x4086);
	SPI_writecom(0x20BB);SPI_writecom(0x000E); SPI_writedat(0x4024);
	SPI_writecom(0x20BB);SPI_writecom(0x000F); SPI_writedat(0x4044);


	SPI_writecom(0x20BC);SPI_writecom(0x0000); SPI_writedat(0x40E0);
	SPI_writecom(0x20BC);SPI_writecom(0x0001); SPI_writedat(0x401F);
	SPI_writecom(0x20BC);SPI_writecom(0x0002); SPI_writedat(0x40F8);
	SPI_writecom(0x20BC);SPI_writecom(0x0003); SPI_writedat(0x4007);

	SPI_writecom(0x20BD);SPI_writecom(0x0000); SPI_writedat(0x40E0);
	SPI_writecom(0x20BD);SPI_writecom(0x0001); SPI_writedat(0x401F);
	SPI_writecom(0x20BD);SPI_writecom(0x0002); SPI_writedat(0x40F8);
	SPI_writecom(0x20BD);SPI_writecom(0x0003); SPI_writedat(0x4007);

	//sunxi_lcd_delay_ms(200);

	SPI_writecom(0x20F0);SPI_writecom(0x0000); SPI_writedat(0x4055);
	SPI_writecom(0x20F0);SPI_writecom(0x0001); SPI_writedat(0x40AA);
	SPI_writecom(0x20F0);SPI_writecom(0x0002); SPI_writedat(0x4052);
	SPI_writecom(0x20F0);SPI_writecom(0x0003); SPI_writedat(0x4008);
	SPI_writecom(0x20F0);SPI_writecom(0x0004); SPI_writedat(0x4000);

	SPI_writecom(0x20B0);SPI_writecom(0x0000); SPI_writedat(0x4000);
	SPI_writecom(0x20B0);SPI_writecom(0x0001); SPI_writedat(0x4010);

	//SPI_writecom(0x20B4);SPI_writecom(0x0000); SPI_writedat(0x4010);

	SPI_writecom(0x20B5);SPI_writecom(0x0000); SPI_writedat(0x406B);

	SPI_writecom(0x20BC);SPI_writecom(0x0000); SPI_writedat(0x4000);

	SPI_writecom(0x2035);SPI_writecom(0x0000); SPI_writedat(0x4000);

	SPI_writecom(0x2036);SPI_writecom(0x0000); SPI_writedat(0x4003);

	SPI_writecom(0x2011);SPI_writecom(0x0000); SPI_writedat(0x4000);

	Delay_us(120);

	SPI_writecom(0x2029);SPI_writecom(0x0000); SPI_writedat(0x4000);

	Delay_us(100);

#endif

}

void RTNA_LCD_Init(void)
{
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ParallelRGB565 480x854 @@\r\n");

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

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif
	SPI_Init();
	Delay_ms(10);
    RTNA_DBG_Str(0, "S5000L19-G =LCD\r\n");
    //****************************************************************************//
    //****************************** Page 1 Command ******************************//
    //****************************************************************************//
    Lcd_init();
}

//============================================================================//
void RTNA_LCD_RGB_Test(void)
{
#if (ENABLE_LCD_TEST_PATTERN)
	#if defined(LCD_GPIO_BACK_LIGHT)
		/* Force turn-on LCD backlight */
		if (LCD_GPIO_BACK_LIGHT != MMP_GPIO_MAX)
		{
            MMPF_PIO_PadConfig(LCD_GPIO_BACK_LIGHT, PAD_OUT_DRIVING(0), MMP_TRUE);
			MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_TRUE);
			RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to output mode\r\n");

			MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
			Delayms(20);
			RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to low\r\n");

			MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_TRUE);
			Delayms(20);
			RTNA_DBG_Str(LCD_DBG_LEVEL, "dbg-set LCD_BL to high\r\n");
		}
	#endif

	MMPF_LCD_DrawTestPattern(&m_PanelAttr);
    Delayms(5000);
#endif
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
