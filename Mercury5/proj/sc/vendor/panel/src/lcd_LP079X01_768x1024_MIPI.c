//==============================================================================
//
//  File        : lcd_OTA7001A_800x480.c
//  Description : 800x480 Sync or DE mode RGB LCD Panel Control Function
//  Author      : 
//  Revision    : 1.0
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
#include "Mipi_SSD2828.h"
#include "halPnl.h"

#define PANEL_WIDTH                 (768/*480*/)//(800)//pm16
#define PANEL_HEIGHT                (1024/*854*/)//(480)
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define Delayms(t) 					LCD_WAIT(t)

#define SECONDARY_DISPLAY 			(0)

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	// Panel basic setting
	PANEL_WIDTH, PANEL_HEIGHT,
	LCD_TYPE_RGBLCD,
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
    LCD_SIG_POLARITY_L,     // DCLK Polarity
    LCD_SIG_POLARITY_L,     // H-Sync Polarity
	LCD_SIG_POLARITY_L,     // V-Sync Polarity
	0x02/*RGB_D24BIT_RGB565*/,
    LCD_TOP_CLK_MPLL_108M,	//ulClkSelect

	{0}
};

#define ENABLE_LCD_LOG       		(0)

#if defined(FAT_BOOT)
#define ENABLE_LCD_TEST_PATTERN 	(0)
#else
#define ENABLE_LCD_TEST_PATTERN 	(0)
#endif

#if (ENABLE_LCD_LOG)
#define LCD_DBG_LEVEL               (0)
#else
#define LCD_DBG_LEVEL               (3)
#endif

#define LCD_XSIZE_TFT  (768)  //pm16
#define LCD_YSIZE_TFT  (1024)
#if 0	
/*old setting*/
#define LCD_VBPD		(0x1e) //0x78
#define LCD_VFPD		(0x24) //0x3C
#define LCD_VSPW		(0x32)
#define LCD_HBPD		(0x38) //0x50
#define LCD_HFPD		(0x3c) //0x24
#define LCD_HSPW		(0x40)
#else
/*new but not final*/
#define LCD_VBPD		(0x77) //0x78 (120 =56+64)
#define LCD_VFPD		(0x3D) //0x3C (60)
#define LCD_VSPW		(0x40) //0x40 (64)
#define LCD_HBPD		(0x18) //0x18 //0x50 (80 = 30+50)
#define LCD_HFPD		(0x5c) //0x5c //0x24 (36)
#define LCD_HSPW		(0x32)
#endif

#define Delay_us(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.udelay(n))
#define Delay_ms(n)   MMPF_OS_Sleep_MS(n)	//(lcm_util.mdelay(n))

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
void RTNA_Init_MIPI_DSI(void)
{
	unsigned short regval;
    unsigned short cfg;
 	SPI_init_gpio();
	Delay_ms(10);

    #if 0
	Set_RST(0);// ( rGPFDAT &= (~(1<<3))) ;
	Delay_ms(50);
	Set_RST(1);//  ( rGPFDAT |= (1<<3) ) ;
	Delay_ms(10);
    #endif

    SPI_2828_WrReg(0xD4,0xFA);   
                  
    SPI_2828_WrReg(0xb1,(LCD_HSPW<<8)|LCD_VSPW);	//Vertical sync and horizontal sync active period 
	SPI_2828_WrReg(0xb2,(LCD_HBPD<<8)|LCD_VBPD);	//Vertical and horizontal back porch period  
	SPI_2828_WrReg(0xb3,(LCD_HFPD<<8)|LCD_VFPD);	//Vertical and horizontal front porch period 
	SPI_2828_WrReg(0xb4, 768);		//Horizontal active period 
	SPI_2828_WrReg(0xb5, 1024);		//Vertical active period
    //SPI_2828_WrReg(0xb6, 0x2007);				//Video mode and video pixel format 888
    cfg =0;
    cfg &= ~VICR6_VSYNC_ACT_HIGH;
    cfg &= ~VICR6_HSYNC_ACT_HIGH;
    cfg |= VICR6_DATA_LATCH_RISE_EDGE;
    cfg |= VICR6_VIDEO_BURST_MODE;
    cfg |= VICR6_VIDEO_DATA_FORMAT_16BPP;
	SPI_2828_WrReg(0xb6, cfg); /*0008 2004*/ //pm16 note:200 //Video mode and video pixel format       565	
	SPI_2828_WrReg(0xde, SSD2828_LANE_CFG_4_LANE);//panmdf16				//MIPI lane select 
	//SPI_2828_WrReg(0xDD, (LCD_HFPD<<8)|LCD_VFPD);
	//SPI_2828_WrReg(0xd6, 0x0004);				//Color order and endianess	BGR
	SPI_2828_WrReg(0xd6, 0x0005);				//Color order and endianess	RGB
	//SPI_2828_WrReg(0xbb, 0x0002); //08				//LP clock divider p.38
	//SPI_2828_WrReg(0xb9, 0x0000);				//PLL enable 
	SPI_2828_WrReg(0xba, 0xC015);               /*801c*///pm16? //0xC015
	//SPI_2828_WrReg(0xb7, 0x0000);				//Generic mode, LP mode
	SPI_2828_WrReg(0xc4, 0x0001);				//BTA setting
    SPI_2828_WrReg(0xb9, 0x0001);				//PLL enable 
	SPI_2828_WrReg(0xb7, 0x0150);				//Generic mode, LP mode
	SPI_2828_WrReg(0xb8, 0x0000);				//VC register
	SPI_2828_WrReg(0xb7, 0x030B | 0x0020 );		//Generic mode, HS video mode
}

#if 0
void Init_MIPI_Bridge(void)
{
	unsigned short regval;
    unsigned short cfg;
 	SPI_init_gpio();
	Delay_ms(10);

    #if 0
	Set_RST(0);// ( rGPFDAT &= (~(1<<3))) ;
	Delay_ms(50);
	Set_RST(1);//  ( rGPFDAT |= (1<<3) ) ;
	Delay_ms(10);
    #endif

	//Initial code 1: SSD2828 initialization
	//RGB interface configuration 
	SPI_2828_WrReg(0xb1,(LCD_HSPW<<8)|LCD_VSPW);	//Vertical sync and horizontal sync active period 
	SPI_2828_WrReg(0xb2,(LCD_HBPD<<8)|LCD_VBPD);	//Vertical and horizontal back porch period  
	SPI_2828_WrReg(0xb3,(LCD_HFPD<<8)|LCD_VFPD);	//Vertical and horizontal front porch period 
	SPI_2828_WrReg(0xb4, LCD_XSIZE_TFT);		//Horizontal active period 
	SPI_2828_WrReg(0xb5, LCD_YSIZE_TFT);		//Vertical active period
	//SPI_2828_WrReg(0xb6, 0x2007);				//Video mode and video pixel format 888
	SPI_2828_WrReg(0xb6, 0x2008/*0008 2004*/);//pm16 note:2004无显示,0008横向*2显示		//Video mode and video pixel format       565	
	//MIPI lane configuration
	//00 - 1 lane mode 
	//01 - 2 lane mode 
	//10 - 3 lane mode 
	//11 - 4 lane mode 
	SPI_2828_WrReg(0xde, 0x0003);//panmdf16				//MIPI lane select 
	//SPI_2828_WrReg(0xDD, (LCD_HFPD<<8)|LCD_VFPD);
	//SPI_2828_WrReg(0xd6, 0x0004);				//Color order and endianess	BGR
	SPI_2828_WrReg(0xd6, 0x0005);				//Color order and endianess	RGB
	SPI_2828_WrReg(0xb9, 0x0000);				//Disable PLL
	SPI_2828_WrReg(0xba, 0xC015/*801c*/);//pm16?
	SPI_2828_WrReg(0xbb, 0x0008); //08				//LP clock divider p.38
	SPI_2828_WrReg(0xb9, 0x0000);				//PLL enable 
	
	SPI_2828_WrReg(0xc4, 0x0001);				//BTA setting
	//CABC brightness setting 
	//SPI_2828_WrReg(0xe9, 0xff2f);	//pm16			//CABC control
	//SPI_2828_WrReg(0xeb, 0x0100);				//CABC control
	//Communicate with LCD driver through MIPI 
	/*SPI_2828_WrReg(0xb7, 0x0342);	//pm165			//DCS mode 0342
	SPI_2828_WrReg(0xb8, 0x0000);				//VC registe
	SPI_2828_WrReg(0xbc, 0x0000);				//Packet size 
	SPI_2828_WrCmd(0x11);					//LCD driver exit sleep mode
	Delay_ms(100);	
	SPI_2828_WrCmd(0x29);	*/				//Set LCD driver display on 
//	PLL configuration 
	//SPI_2828_WrReg(0xba, 0x8334);				//PLL setting,8028 0x34--52*24/3=416M
	//SPI_2828_WrReg(0xba, 0x8346/*22*/);	//pm16	//PLL setting,8028    0x27--39*24/3=312M
	
	/*SPI_2828_WrReg(0xbb, 0x0006);				//LP clock divider
	SPI_2828_WrReg(0xb9, 0x0001);				//PLL enable 
	SPI_2828_WrReg(0xb8, 0x0000);*/	//pm16			//VC register 
//	SPI_2828_WrReg(0xb7, 0x030B);				//Generic mode, HS video mode
	
	//Delay_ms(100/*55*/);          //pm16
	//SPI_2828_WrReg(0xb7, 0x030B|0x0020);//pm16
	//Initial code 2: LCD driver initialization
	//MIPI lane and PLL configuration
	SPI_2828_WrReg(0xb9, 0x0001);				//PLL enable 
	SPI_2828_WrReg(0xb7, 0x0150);				//Generic mode, LP mode
	SPI_2828_WrReg(0xb8, 0x0000);				//VC register
    
	//Send command and data through MIPI 
	//------------------------------------------------------------------------------------------	
	//----------communicate with lcd driver through mipi----------------------------------------
	
	/*GP_COMMAD_PA(4);
	SPI_WriteData(0xBF);
	SPI_WriteData(0x91);
	SPI_WriteData(0x61);
	SPI_WriteData(0xF2); 

	GP_COMMAD_PA(3);
	SPI_WriteData(0xB3);
	SPI_WriteData(0x00);
	SPI_WriteData(0x77);

	GP_COMMAD_PA(3);
	SPI_WriteData(0xB4);
	SPI_WriteData(0x00);
	SPI_WriteData(0x77);

	GP_COMMAD_PA(7);
	SPI_WriteData(0xB8);
	SPI_WriteData(0x00);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0xA0);
	SPI_WriteData(0x01);

	GP_COMMAD_PA(4);
	SPI_WriteData(0xBA);
	SPI_WriteData(0x3E);
	SPI_WriteData(0x23);
	SPI_WriteData(0x00);


	GP_COMMAD_PA(2);
	SPI_WriteData(0xC3);
	SPI_WriteData(0x04);


	GP_COMMAD_PA(3);
	SPI_WriteData(0xC4);
	SPI_WriteData(0x30);
	SPI_WriteData(0x6A);

	GP_COMMAD_PA(39);
	SPI_WriteData(0xC8);
	SPI_WriteData(0x7E);
	SPI_WriteData(0x68);
	SPI_WriteData(0x57);
	SPI_WriteData(0x49);
	SPI_WriteData(0x43);
	SPI_WriteData(0x33);
	SPI_WriteData(0x35);
	SPI_WriteData(0x1C);
	SPI_WriteData(0x33);
	SPI_WriteData(0x2F);
	SPI_WriteData(0x2B);
	SPI_WriteData(0x43);
	SPI_WriteData(0x2C);
	SPI_WriteData(0x31);
	SPI_WriteData(0x20);
	SPI_WriteData(0x22);
	SPI_WriteData(0x1E);
	SPI_WriteData(0x1D);
	SPI_WriteData(0x03);
	SPI_WriteData(0x7E);
	SPI_WriteData(0x68);
	SPI_WriteData(0x57);
	SPI_WriteData(0x49);
	SPI_WriteData(0x43);
	SPI_WriteData(0x33);
	SPI_WriteData(0x35);
	SPI_WriteData(0x1C);
	SPI_WriteData(0x33);
	SPI_WriteData(0x2F);
	SPI_WriteData(0x2B);
	SPI_WriteData(0x43);
	SPI_WriteData(0x2C);
	SPI_WriteData(0x31);
	SPI_WriteData(0x20);
	SPI_WriteData(0x22);
	SPI_WriteData(0x1E);
	SPI_WriteData(0x1D);
	SPI_WriteData(0x03);

	GP_COMMAD_PA(10);
	SPI_WriteData(0xC7);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0x31);
	SPI_WriteData(0x05);
	SPI_WriteData(0x65);
	SPI_WriteData(0x2B);
	SPI_WriteData(0x12);
	SPI_WriteData(0xA5);
	SPI_WriteData(0xA5);

	GP_COMMAD_PA(17);
	SPI_WriteData(0xD4);
	SPI_WriteData(0x1E);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x17);
	SPI_WriteData(0x37);
	SPI_WriteData(0x06);
	SPI_WriteData(0x04);
	SPI_WriteData(0x0A);
	SPI_WriteData(0x08);
	SPI_WriteData(0x00);
	SPI_WriteData(0x02);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);

	GP_COMMAD_PA(17);
	SPI_WriteData(0xD5);
	SPI_WriteData(0x1E);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x17);
	SPI_WriteData(0x37);
	SPI_WriteData(0x07);
	SPI_WriteData(0x05);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x09);
	SPI_WriteData(0x01);
	SPI_WriteData(0x03);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);

	GP_COMMAD_PA(17);
	SPI_WriteData(0xD6);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x13);
	SPI_WriteData(0x17);
	SPI_WriteData(0x17);
	SPI_WriteData(0x07);
	SPI_WriteData(0x09);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x05);
	SPI_WriteData(0x03);
	SPI_WriteData(0x01);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);

	GP_COMMAD_PA(17);
	SPI_WriteData(0xD7);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1E);
	SPI_WriteData(0x17);
	SPI_WriteData(0x17);
	SPI_WriteData(0x06);
	SPI_WriteData(0x08);
	SPI_WriteData(0x0A);
	SPI_WriteData(0x04);
	SPI_WriteData(0x02);
	SPI_WriteData(0x00);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x1F);

	GP_COMMAD_PA(21);
	SPI_WriteData(0xD8);
	SPI_WriteData(0x20);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x30);
	SPI_WriteData(0x03);
	SPI_WriteData(0x30);
	SPI_WriteData(0x01);
	SPI_WriteData(0x02);
	SPI_WriteData(0x00);
	SPI_WriteData(0x01);
	SPI_WriteData(0x02);
	SPI_WriteData(0x06);
	SPI_WriteData(0x70);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x73);
	SPI_WriteData(0x07);
	SPI_WriteData(0x06);
	SPI_WriteData(0x70);
	SPI_WriteData(0x08);

	GP_COMMAD_PA(21);
	SPI_WriteData(0xD9);
	SPI_WriteData(0x00);
	SPI_WriteData(0x0A);
	SPI_WriteData(0x0A);
	SPI_WriteData(0x80);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x06);
	SPI_WriteData(0x7B);
	SPI_WriteData(0x00);
	SPI_WriteData(0x80);
	SPI_WriteData(0x00);
	SPI_WriteData(0x33);
	SPI_WriteData(0x6A);
	SPI_WriteData(0x1F);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x03);
	SPI_WriteData(0x7B);

	GP_COMMAD_PA(2);
	SPI_WriteData(0x35);
	SPI_WriteData(0x00);

	GP_COMMAD_PA(2);
	SPI_WriteData(0x11);
	SPI_WriteData(0x00);   
	Delay_us(5);

	GP_COMMAD_PA(2);
	SPI_WriteData(0x29);
	SPI_WriteData(0x00);   
	Delay_us(1);*/
                  
	//------------------------------------------------------------------------------------------	
	 
	//Cmd code 3: Access video mode 
	//RGB interface configuration 
	/*SPI_2828_WrReg(0xb1,(LCD_HSPW<<8)|LCD_VSPW);//pm16	//Vertical sync and horizontal sync active period 
	SPI_2828_WrReg(0xb2,(LCD_HBPD<<8)|LCD_VBPD);	//Vertical and horizontal back porch period  
	SPI_2828_WrReg(0xb3,(LCD_HFPD<<8)|LCD_VFPD);	//Vertical and horizontal front porch period 
	SPI_2828_WrReg(0xb4, LCD_XSIZE_TFT);		//Horizontal active period 
	SPI_2828_WrReg(0xb5, LCD_YSIZE_TFT);		//Vertical active period
	//SPI_2828_WrReg(0xb6, 0x0007);		//2007		//Video mode and video pixel format 	888
	SPI_2828_WrReg(0xb6, 0x2004);		//2007		//Video mode and video pixel format 	565
	//MIPI lane configuration
	//00 - 1 lane mode 
	//01 - 2 lane mode 
	//10 - 3 lane mode 
	//11 - 4 lane mode
	SPI_2828_WrReg(0xde, 0x0001);				//MIPI lane select, 2chl
	SPI_2828_WrReg(0xd6, 0x0005);				//Color order and endianess
	SPI_2828_WrReg(0xb9, 0x0000);				//Disable PLL
	SPI_2828_WrReg(0xc4, 0x0001);				//BTA setting
	//CABC brightness setting 
	SPI_2828_WrReg(0xe9, 0xff2f);				//CABC control
	SPI_2828_WrReg(0xeb, 0x0100);				//CABC control
	
	Delay_ms(22);
	//PLL configuration
	//FR: bit15~14
	//00 – 62.5 < OUT f  < 125 
	//01 – 126 < OUT f  < 250 
	//10 – 251 < OUT f  < 500  
	//11 – 501 < OUT f  < 1000 
	
	//MS: bit12~8
	//Fpre = fin/MS
	
	//NS: bit7~0
	//Fout = Fpre*NS
	
	SPI_2828_WrReg(0xba, 0x8324);				//PLL setting,8028    
	SPI_2828_WrReg(0xbb, 0x0006);				//LP clock divider,分频f/（1+1）,750MHZ/2 = 
	SPI_2828_WrReg(0xb9, 0x0001);				//PLL enable 
	SPI_2828_WrReg(0xb8, 0x0000);				//VC register */
	
    #if 0
	    SPI_2828_WrReg(0xb7, 0x0342);	//pm165			//DCS mode 0342
	    SPI_2828_WrReg(0xb8, 0x0000);				//VC registe
	    SPI_2828_WrReg(0xbc, 0x0000);				//Packet size 
        #if 0
	        SPI_2828_WrCmd(0x11);					//LCD driver exit sleep mode
	        Delay_ms(100);	
	        SPI_2828_WrCmd(0x29);					//Set LCD driver display on 
	        Delay_ms(100);
        #endif
    #endif
	SPI_2828_WrReg(0xb7, 0x030B | 0x0020 );		//Generic mode, HS video mode	
}
#endif
void RTNA_LCD_InitMainLCD(void)
{
#if (SECONDARY_DISPLAY == 0)
	RTNA_DBG_Str(LCD_DBG_LEVEL, "### RTNA_LCD_InitMainLCD - OTA7001A 480x854\r\n");

	m_PanelAttr.usDotClkRatio 	= 5;    // 4

	#if 1
    #if 0
	m_PanelAttr.usHBPorch		= 28; 
	m_PanelAttr.usHBlanking     = 58;
	m_PanelAttr.usHSyncW		= 32;
	m_PanelAttr.usVBPorch		= 30;
	m_PanelAttr.usVBlanking 	= 66;
	m_PanelAttr.usVSyncW		= 50;	
    #else
    /*not final*/
    m_PanelAttr.usHBPorch		= 20; 
	m_PanelAttr.usHBlanking     = 24;
	m_PanelAttr.usHSyncW		= 6;
	m_PanelAttr.usVBPorch		= 24;
	m_PanelAttr.usVBlanking 	= 32;
	m_PanelAttr.usVSyncW		= 6;	
    #endif
	#else
	m_PanelAttr.usHBPorch 		= 8;
	m_PanelAttr.usHBlanking 	= 20;
	m_PanelAttr.usHSyncW 		= 8;
	m_PanelAttr.usVBPorch 		= 14;
	m_PanelAttr.usVBlanking     = 20;
	m_PanelAttr.usVSyncW 		= 2;
	#endif
	m_PanelAttr.usPRT2HdotClk 	= 2;

	m_PanelAttr.bDeltaRBG 		= MMP_FALSE;
	m_PanelAttr.bDummyRBG 		= MMP_FALSE;

	//m_PanelAttr.ubEvenLnOrder   = LCD_SPI_PIX_ORDER_RGB;
	//m_PanelAttr.ubOddLnOrder    = LCD_SPI_PIX_ORDER_RGB;

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

void RTNA_LCD_Init(void)
{
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for LP079X01_768X1024_MIPI ...\r\n");

#if (SECONDARY_DISPLAY == 1)
	RTNA_LCD_Init2ndLCD();
#else
	RTNA_LCD_InitMainLCD();
#endif

#if 1//ENABLE_MIPI_PANEL
       RTNA_Init_MIPI_DSI();
	//lcm_init();
#endif
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

