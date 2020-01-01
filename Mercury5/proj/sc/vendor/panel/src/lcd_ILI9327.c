//==============================================================================
//
//  File        : lcd_ILI9327L.c
//  Description : 240x432 LCD Panel Control Function
//  Author      : Jacy Lab
//  Revision    : 1.0 cccc
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

#define Delayms(t) 	LCD_WAIT(t)
#define PANEL_W 	(400)	// cooper FIXME
#define PANEL_H 	(240) 	// cooper FIXME
#define BG_COLOR 	(0x0)
#define ENABLE_LCD_ILI9327L_LOG (0x0)

//MMPF_PANEL_ATTR panelAttr;

static MMPF_PANEL_ATTR m_PanelAttr = {
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
        PANEL_W, PANEL_H,
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
        240, 432,//432,
#endif

        LCD_TYPE_RGBLCD,
        LCD_PRM_CONTROLER,
        0,
 	    LCD_RATIO_16_9,
        NULL,		// Panel initial sequence
        NULL,   	// Index/Cmd sequence
        LCD_BUS_WIDTH_16,
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
void Write_COMMAND16i(MMP_USHORT d)
{
    LCD_SET_W(0x80002810, d);
    LCD_SET_B(0x80002800, LCD_IDX_RDY);
    while(LCD_GET_B(0x80002800) & LCD_IDX_RDY);
}

void Write_DATA16i(MMP_USHORT d)
{
    LCD_SET_W(0x80002810, d | 0x0100);
    LCD_SET_B(0x80002800, LCD_IDX_RDY);
    while(LCD_GET_B(0x80002800) & LCD_IDX_RDY);
}

void RTNA_LCD_InitMainLCD(void)
{

    RTNA_DBG_Str(0, "### RTNA_LCD_InitMainLCD -\r\n");

    //	MMPF_PANEL_ATTR panelAttr;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
    m_PanelAttr.usPanelW      = PANEL_W;
    m_PanelAttr.usPanelH      = PANEL_H;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    m_PanelAttr.usPanelW      = 240;
    m_PanelAttr.usPanelH      = 432;//432;
#endif    
    m_PanelAttr.ubDevType		= LCD_TYPE_RGBLCD;                                                                          
    m_PanelAttr.ubController 	= LCD_PRM_CONTROLER;                                                                        
    m_PanelAttr.ulBgColor 		= BG_COLOR;                                                                            
    m_PanelAttr.ubRatio		    = LCD_RATIO_16_9;

    m_PanelAttr.pInitSeq		= NULL;                                                                          
    m_PanelAttr.pIdxCmdSeq		= NULL;                                                                                     

    // RGB interface                                                                                                  
    m_PanelAttr.bPartialDisp	= MMP_FALSE;                                                                          
    m_PanelAttr.ubDclkPor       = LCD_SIG_POLARITY_L;
    m_PanelAttr.ubHsyncPor		= LCD_SIG_POLARITY_L;                                                                       
    m_PanelAttr.ubVsyncPor		= LCD_SIG_POLARITY_L;                                                                       
    m_PanelAttr.ubRgbFmt		= 0x02/*RGB_D24BIT_RGB565*/;           

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
    m_PanelAttr.usDotClkRatio 	= 16;	// Stand for [(Lcd Freq / Dot Clock Freq) - 1]                                   

    m_PanelAttr.usHBPorch     	= 25;//25;	// Unit:pixel, Ragne:0~1023                                                   
    m_PanelAttr.usHBlanking   	= 33;	// Unit:pixel, Range:0~1023                                                    
    m_PanelAttr.usHSyncW      	= 2;	// Unit:pixel, Range:0~255                                                   

    m_PanelAttr.usVBPorch     	= 1;	// Unit:line,  Range:0~1023                                                   
    m_PanelAttr.usVBlanking   	= 0;	// Unit:line,  Range:0~1023                                                     
    m_PanelAttr.usVSyncW      	= 0;	// Unit:line,  Range:0~255                                                   

    m_PanelAttr.usPRT2HdotClk 	= 2;	// Unit:Dot Clock, Range:0~255                                                    
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    m_PanelAttr.usDotClkRatio 	= 30;//16;	// Stand for [(Lcd Freq / Dot Clock Freq) - 1]

    m_PanelAttr.usHBPorch     	= 1;//25;//25;	// Unit:pixel, Ragne:0~1023
    m_PanelAttr.usHBlanking   	= 15;//33;	// Unit:pixel, Range:0~1023
    m_PanelAttr.usHSyncW      	= 2;	// Unit:pixel, Range:0~255                                                   

    m_PanelAttr.usVBPorch     	= 1;	// Unit:line,  Range:0~1023                                                   
    m_PanelAttr.usVBlanking   	= 5;//0;	// Unit:line,  Range:0~1023
    m_PanelAttr.usVSyncW      	= 0;	// Unit:line,  Range:0~255                                                   

    m_PanelAttr.usPRT2HdotClk 	= 2;	// Unit:Dot Clock, Range:0~255                                                    
#endif    
    //	panelAttr.usPartStX;                                                                                              
    //	panelAttr.usPartEndX;                                                                                             
    //	panelAttr.usPartStY;                                                                                              
    //	panelAttr.usPartEndY;                                                                                             

    m_PanelAttr.bDeltaRBG 		= MMP_FALSE;                                                                                    
    m_PanelAttr.bDummyRBG 		= MMP_FALSE;                                                                                    
    m_PanelAttr.ubEvenLnOrder 	= LCD_SPI_PIX_ORDER_RGB;                                                                    
    m_PanelAttr.ubOddLnOrder  	= LCD_SPI_PIX_ORDER_RGB;                                                                    

    // RGB SPI interface                                                                                              
    m_PanelAttr.usSpi2MciRatio	= 0x0F;	// Stand for [(MCI Freq / SPI Clock Freq) - 1]                              
    m_PanelAttr.usCsSetupCyc      	= 0x0B;	// Unit:MCI Clock, Range:0~15  //tcss - tslw = 60(min) - 15 (min) = 45ns    
    m_PanelAttr.usCsHoldCyc       	= 0x0B;	// Unit:MCI Clock, Range:0~15  //tcsh  = 65(min) ns                         
    m_PanelAttr.usCsHighWidth     	= 0xFF;	// Unit:MCI Clock, Range:0~255 //tchw  = 40(min) ns                         
    m_PanelAttr.usSPIRegBitCnt    	= SPI_PANEL_9BITS;                                                                      
    ///////                                                                                                           
    m_PanelAttr.ubDispWinId 	= LCD_DISP_WIN_PIP;                                                                         
    m_PanelAttr.usWinStX 		= 0;                                                                                          
    m_PanelAttr.usWinStY 		= 0;
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) 
    m_PanelAttr.usWinW        = PANEL_W;
    m_PanelAttr.usWinH        = PANEL_H;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    m_PanelAttr.usWinW      = 240;
    m_PanelAttr.usWinH      = 432;//432;
#endif    
    m_PanelAttr.usWinBPP 		= 2;                                                                                          
    m_PanelAttr.usWinFmt 		= LCD_WIN_FMT_16BPP;                                                                          
    m_PanelAttr.ulWinAddr 		= 0x01500000;                                                                                 

    //	m_PanelAttr = panelAttr;                                                                                            

    MMPF_LCD_InitPanel(&m_PanelAttr);                                                                                     
}                                                                                                                     
                                                                          
void RTNA_LCD_Init(void)                                                                                              
{                                                                                                                     
                                                                                                                      
#if (LCD_IF == LCD_IF_RGB)                                                                                            
//	extern MMPF_PANEL_ATTR m_PanelAttr;                                                                               
                                                                          
	RTNA_DBG_Str(0, "### RTNA_LCD_Init for ILI9327L RGB...\r\n");                                                     

#if 1
	/* LCD Power On */                                                                                                
//#define LCD_GPIO_ENABLE 49	// cooper for Jacylab      
	/* LCD Power On (ex: LCD_CE pin connects to A83's PCGPIO30 (GPIO62)) */
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
#endif

#if 0
/* LCD HW Reset (ex: LCD_RST pin connects to A83's PCGPIO29 (GPIO61)) */
#if defined(LCD_GPIO_RESET)
//	if (LCD_GPIO_RESET != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(3, MMP_TRUE, MMP_TRUE);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to output mode\r\n");

		MMPF_PIO_SetData(3, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(1);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");

		MMPF_PIO_SetData(3, LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(10);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to low\r\n");

		MMPF_PIO_SetData(3, !LCD_GPIO_RESET_ACT_LEVEL, MMP_TRUE);
		MMPF_OS_Sleep_MS(120);
		//RTNA_DBG_Str(0, "dbg-set LCD_RST to high\r\n");
	}
#endif
#endif

	// ************* Back Light Controll **************** //
	MMPF_PIO_EnableOutputMode(LCD_GPIO_BACK_LIGHT, MMP_TRUE, MMP_FALSE); // 1. Set LCD_GPIO_BACK_LIGHT output enable
	Delayms(20);
	//RTNA_DBG_Str(0, "dbg-set LCD_BL to output mode\r\n");

	MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, !LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 2. LCD_GPIO_BACK_LIGHT pull low
	Delayms(20);
	  //RTNA_DBG_Str(0, "dbg-set LCD_BL to low\r\n");

	MMPF_PIO_SetData(LCD_GPIO_BACK_LIGHT, LCD_GPIO_BACK_LIGHT_ACT_LEVEL, MMP_FALSE); // 3. LCD_GPIO_BACK_LIGHT pull high
	Delayms(20);
	//RTNA_DBG_Str(0, "dbg-set LCD_BL to high\r\n");
 
    
	RTNA_LCD_InitMainLCD();

	// ************* Reset LCD Driver **************** //
	Write_COMMAND16i(0x01);
	MMPF_OS_Sleep_MS(1);
	Write_COMMAND16i(0x01);
	MMPF_OS_Sleep_MS(10);
	Write_COMMAND16i(0x01);
	MMPF_OS_Sleep_MS(50);
	// ************* Start Initial Sequence ********** //

	// ??????? Not define in Data Sheet  
	Write_COMMAND16i(0xE9);
	        Write_DATA16i(0x20);

	// Exit Sleep Mode //
	Write_COMMAND16i(0x11);
	MMPF_OS_Sleep_MS(100);
	    
	// Enter Normal Mode //)    	        
	Write_COMMAND16i(0x13);
	MMPF_OS_Sleep_MS(120);

	// VCOM Control //
	Write_COMMAND16i(0xD1);
	        Write_DATA16i(0x00);
	        Write_DATA16i(0x6B);	//(0x40);	//(0x6B);
	        Write_DATA16i(0x19);	//(0x0F);	//(0x19);
					        		
	// Power Setting //
	Write_COMMAND16i(0xD0);
	        Write_DATA16i(0x07);
	        Write_DATA16i(0x01);	//(0x04);	//(0x01);
	        Write_DATA16i(0x04);	//(0x8C);	//(0x04);
	        
	// Set Address Mode - Rotation //)    	        
	Write_COMMAND16i(0x36);
		Write_DATA16i(0xE8);
		    
	// Display Timing Setting //
	Write_COMMAND16i(0xC1);
		Write_DATA16i(0x10);
		Write_DATA16i(0x10);
		Write_DATA16i(0x02);
		Write_DATA16i(0x02);

	// Panel Driving Setting //
	Write_COMMAND16i(0xC0);	// Set Default Gamma
		Write_DATA16i(0x00);	//(0x10);
		Write_DATA16i(0x35);
		Write_DATA16i(0x00);
		Write_DATA16i(0x00);
		Write_DATA16i(0x01);
		Write_DATA16i(0x02);

	// Frame Rate Control //
	Write_COMMAND16i(0xC5);
		Write_DATA16i(0x04);	//(0x03);

	// Power Setting for Normal Mode //
    	Write_COMMAND16i(0xD2);
	        Write_DATA16i(0x01);
	        Write_DATA16i(0x44);	//(0x22);
#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
    // Set Column Address //      
    Write_COMMAND16i(0x2A);
        Write_DATA16i(0);
        Write_DATA16i(0);
        Write_DATA16i((432-1)>>8);
        Write_DATA16i((432-1)&0xFF);

    // Set Page Address //      
    Write_COMMAND16i(0x2B);
        Write_DATA16i(0);
        Write_DATA16i(0);
        Write_DATA16i((240-1)>>8);
        Write_DATA16i((240-1)&0xFF);
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    Write_COMMAND16i(0x36);//lucas
        Write_DATA16i(0x9C);//lucas
#endif
#if 1
        // Set Pixel Format //            
	Write_COMMAND16i(0x3A);
		Write_DATA16i(0x55);
		
	// Display Mode And Frame Memory Mode Setting //    
	Write_COMMAND16i(0xB4);
		Write_DATA16i(0x10);

	// Interface Control //
	Write_COMMAND16i(0xC6);
		Write_DATA16i(0x03);
#endif
			
	// Gamma Setting //	    
	Write_COMMAND16i(0xC8);
	        Write_DATA16i(0x04);	//(0x00);
	        Write_DATA16i(0x67);	//(0x30);
	        Write_DATA16i(0x35);	//(0x33);
	        Write_DATA16i(0x04);	//(0x00);
	        Write_DATA16i(0x08);	//(0x0F);
	        Write_DATA16i(0x06);	//(0x02);
	        Write_DATA16i(0x24);	//(0x44);
	        Write_DATA16i(0x01);	//(0x74);
	        Write_DATA16i(0x37);	//(0x77);
	        Write_DATA16i(0x40);	//(0x00);
	        Write_DATA16i(0x03);	//(0x02);
	        Write_DATA16i(0x10);	//(0x0F);
	        Write_DATA16i(0x08);	//(0x08);
	        Write_DATA16i(0x80);	//(0x80);
	        Write_DATA16i(0x00);	//(0x00);

	Write_COMMAND16i(0XC9); //Set Gamma 
	        Write_DATA16i(0x0D); 
	        Write_DATA16i(0x09); 
	        Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x0B); 
		Write_DATA16i(0x0B); 
		Write_DATA16i(0x0D); 
		Write_DATA16i(0x0D); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00);  
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01);  
		Write_DATA16i(0x01); 
		Write_DATA16i(0x04); 
		Write_DATA16i(0x0D); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x09); 
		Write_DATA16i(0x0B); 
		Write_DATA16i(0x0B); 
		Write_DATA16i(0x0D); 
		Write_DATA16i(0x0D); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x0E); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x00); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01);  
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x01); 
		Write_DATA16i(0x04); 
		Write_DATA16i(0x04); 

	// Enable 3 Gamma //
	Write_COMMAND16i(0xEA);
		Write_DATA16i(0x80);

	// Invert Mode //
//	Write_COMMAND16i(0x20);			// Exit	    
//		Write_COMMAND16i(0x21);	    	// Enter     
	        			
	// Set Display On //				
	Write_COMMAND16i(0x29);

#endif
}
 
void RTNA_LCD_RGB_Test(void)
{
	MMPF_LCD_DrawTestPattern(&m_PanelAttr);      
	
#if (ENABLE_LCD_ILI9327L_LOG)
	RTNA_DBG_Str(0, "dbg-ILI9327L-RTNA_LCD_RGB_Test\r\n");
	RTNA_LCD_Backlight(MMP_TRUE);
	RTNA_DBG_Str(0, "dbg-ILI9327L LCD backlight On\r\n");
	MMPF_OS_Sleep_MS(20);
	RTNA_LCD_Backlight(MMP_FALSE);
	RTNA_DBG_Str(0, "dbg-ILI9327L LCD backlight Off\r\n");
	MMPF_OS_Sleep_MS(20);
#endif
}

void RTNA_LCD_Direction(LCD_DIR dir)
{
	DSPY_DECL;

	DSPY_WR_B(DSPY_RGB2_DELTA_MODE, RGB_DUMMY_MODE_ENABLE |
					RGB_DELTA_MODE_ENABLE |
					SPI_ODD_LINE_RGB |
					SPI_EVEN_LINE_RGB);

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
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE,	RGB_DELTA_MODE_ENABLE | 
							SPI_ODD_LINE_RBG | 
							SPI_EVEN_LINE_BGR);
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
			DSPY_WR_B(DSPY_RGB2_DELTA_MODE, RGB_DELTA_MODE_ENABLE | 
							SPI_ODD_LINE_RGB | 
							SPI_EVEN_LINE_GBR);
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

