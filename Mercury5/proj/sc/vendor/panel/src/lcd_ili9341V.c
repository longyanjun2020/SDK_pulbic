//==============================================================================
//
//  File        : lcd_ILI9341V.c
//  Description : ILI9341V LCD Panel Control Function
//  Author      : 
//  Revision    : 
//
//==============================================================================



//==============================================================================
//
//                              MACRO for different environment
//
//==============================================================================

//AIT_PMP,20100308
#ifdef BUILD_CE
#undef BUILD_FW
#endif


#ifdef BUILD_FW

#include "mmp_lib.h"
#include "reg_retina.h"
#include "lib_retina.h"

#include "mmph_hif.h"
#include "mmph_reg_display.h"

#define  LCD_DECL               //AITPS_LCD   pLCD  = AITC_BASE_LCD
#define  LCD_WAIT(cnt)          RTNA_WAIT_MS(cnt)
#define  LCD_CMD(idx, cmd)      RTNA_LCD_BurstCmd(idx, cmd)
#define  LCD_GET_W(reg)         //(pLCD->##reg)
#define  LCD_SET_B(reg, val)    //(pLCD->##reg) = (val)
#define  LCD_SET_W(reg, val)    //(pLCD->##reg) = (val)
#define  LCD_SET_D(reg, val)    //(pLCD->##reg) = (val)
#define  MEM_SET_W(addr, val)   *(MMP_USHORT*)(addr) = (val);

#define  PIP_FB0                g_PIP_fb0   // refer to BSP\lib_retina.c

#else 

#include "mmp_lib.h"
#include "ait_utility.h"
//#include "ait_bsp.h"

#include "mmph_hif.h"
//#include "mmp_reg_display.h"
//#include "mmp_reg_gbl.h"
#include "mmpf_pio.h"
#include "lib_retina.h"
#include "CarDV_dsc_Key.h"
#define  LCD_DECL
#define  LCD_WAIT(cnt)          MMPF_OS_Sleep_MS(cnt)
#define  LCD_CMD(idx, cmd)      MMPD_LCD_SendIndexCommand(idx, cmd)
#define  LCD_SEND_IDX(idx)		MMPD_LCD_SendIndex(idx)
#define  LCD_SEND_CMD(cmd)		MMPD_LCD_SendCommand(cmd)
#define  LCD_GET_W(reg)         MMPH_HIF_RegGetW(reg)
#define  LCD_GET_B(reg)         MMPH_HIF_RegGetB(reg)

#define  LCD_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  LCD_SET_W(reg, val)    MMPH_HIF_RegSetW(reg, val)
#define  LCD_SET_D(reg, val)    MMPH_HIF_RegSetL(reg, val)
#define  MEM_SET_W(addr, val)   MMPH_HIF_MemSetW(addr, val)

#endif

#define ENABLE_LCD_ILI9341_LOG (0)

typedef enum _LCDDIR{ //For compiler
	UPLEFT_DOWNRIGHT = 0,
	DOWNLEFT_UPRIGHT,
	UPRIGHT_DOWNLEFT,
	DOWNRIGHT_UPLEFT
}LCDDIR;


//==============================================================================
//
//                              CONSTANTS & VARIABLES
//
//==============================================================================

//[GLOBAL] LCD configuration

// #define LCD_ROTATE_180
#if 0
MMP_USHORT  g_PANL_w  = 320; 
MMP_USHORT  g_PANL_h  = 240; 
MMP_USHORT  g_PIP_w   = 320;
MMP_USHORT  g_PIP_h   = 240;
#else
MMP_USHORT  g_PANL_w  = 240; 
MMP_USHORT  g_PANL_h  = 320; 
MMP_USHORT  g_PIP_w   = 240;
MMP_USHORT  g_PIP_h   = 320;
#endif

MMP_USHORT  g_PIP_bpp = 2; // byte per pixel
//[GLOBAL]

void RTNA_LCD_InitMainLCD(void);
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#pragma O0
void RTNA_LCD_WaitCount(unsigned int count)
{
    while(count--);
}
#pragma

void RTNA_LCD_Init(void)
{
    LCD_DECL;
    
	RTNA_LCD_InitMainLCD();

	LCD_SEND_IDX(0x11); //Exit Sleep
	LCD_WAIT(60);

	LCD_SEND_IDX(0xcf); 
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0xD9);
	LCD_SEND_CMD(0x30);

	LCD_SEND_IDX(0xed); 
	LCD_SEND_CMD(0x64);
	LCD_SEND_CMD(0x03);
	LCD_SEND_CMD(0x12);
	LCD_SEND_CMD(0x81);

	LCD_SEND_IDX(0xcb); 
	LCD_SEND_CMD(0x39);
	LCD_SEND_CMD(0x2c);
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x34);
	LCD_SEND_CMD(0x02);

	LCD_SEND_IDX(0xea); 
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x00);

	LCD_SEND_IDX(0xe8); 
	LCD_SEND_CMD(0x85);
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x78);

	LCD_SEND_IDX(0xC0); //Power control
	LCD_SEND_CMD(0x23); //VRH[5:0]

	LCD_SEND_IDX(0xC1); //Power control
	LCD_SEND_CMD(0x12); //SAP[2:0];BT[3:0]

	LCD_SEND_IDX(0xC2);
	LCD_SEND_CMD(0x11);

	LCD_SEND_IDX(0xC5); //VCM control
	LCD_SEND_CMD(0x35);
	LCD_SEND_CMD(0x3F);

	LCD_SEND_IDX(0xc7); 
	LCD_SEND_CMD(0xA0);

	LCD_SEND_IDX(0x3A);
	LCD_SEND_CMD(0x55);//RGB565
	//LCD_SEND_CMD(0x66);//RGB666

	LCD_SEND_IDX(0x36); // Memory Access Control
	LCD_SEND_CMD(0xdc);

	LCD_SEND_IDX(0xB1); // Frame Rate Control
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x18);

	LCD_SEND_IDX(0xB6); // Display Function Control
	LCD_SEND_CMD(0x0a);
	LCD_SEND_CMD(0xa2);

	LCD_SEND_IDX(0xF2); // 3Gamma Function Disable
	LCD_SEND_CMD(0x00);

	LCD_SEND_IDX(0xF7);
	LCD_SEND_CMD(0x20);

	LCD_SEND_IDX(0x26); //Gamma curve selected
	LCD_SEND_CMD(0x01);

	LCD_SEND_IDX(0xE0); //Set Gamma
	LCD_SEND_CMD(0x1f);
	LCD_SEND_CMD(0x24);
	LCD_SEND_CMD(0x23);
	LCD_SEND_CMD(0x0b);
	LCD_SEND_CMD(0x0f);
	LCD_SEND_CMD(0x08);
	LCD_SEND_CMD(0x50);
	LCD_SEND_CMD(0xd8);
	LCD_SEND_CMD(0x3b);
	LCD_SEND_CMD(0x08);
	LCD_SEND_CMD(0x0a);
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x00);

	LCD_SEND_IDX(0XE1); //Set Gamma
	LCD_SEND_CMD(0x00);
	LCD_SEND_CMD(0x1b);
	LCD_SEND_CMD(0x1c);
	LCD_SEND_CMD(0x04);
	LCD_SEND_CMD(0x10);
	LCD_SEND_CMD(0x07);
	LCD_SEND_CMD(0x2f);
	LCD_SEND_CMD(0x27);
	LCD_SEND_CMD(0x44);
	LCD_SEND_CMD(0x07);
	LCD_SEND_CMD(0x15);
	LCD_SEND_CMD(0x0f);
	LCD_SEND_CMD(0x3f);
	LCD_SEND_CMD(0x3f);
	LCD_SEND_CMD(0x1F);

	LCD_SEND_IDX(0x29); //display o
	LCD_SEND_IDX(0x2C);

    LCD_SET_W( DSPY_LCD_TX_0,        0x36 );
    LCD_SET_W( DSPY_LCD_TX_1,        0xDC );
    LCD_SET_W( DSPY_LCD_TX_2,        0x2C );
    
    LCD_SET_W( DSPY_LCD_AUTO_CFG,    LCD_TX_TYPE_IDX(0) |
                                     LCD_TX_TYPE_CMD(1) |
                                     LCD_TX_TYPE_IDX(2));
    LCD_SET_W( DSPY_PLCD_IDX_CMD_NUM, 3 );
    
}

//=====================================================================//
void RTNA_LCD_RGB_Test(void)
{
    int     x, y;
    MMP_USHORT  lcd_pat[] = {0xF800, 0x07E0, 0x001F, 0xFFFF};

    LCD_DECL;

//#ifdef BUILD_HOST
//MMPH_HIF_RegGetW(0x704E);
//MMPH_HIF_RegSetW(0x704E, 0x0000);
//#endif

    LCD_SET_W( DSPY_WIN_PRIO,       (ICON_WIN  << WIN_1_SHFT) |
                                    (OVLY_WIN  << WIN_2_SHFT) |
                                    (PIP_WIN   << WIN_3_SHFT) |
                                    (MAIN_WIN  << WIN_4_SHFT) );

    LCD_SET_D( DSPY_BG_COLR,  	    0x00000000 );
    LCD_SET_W( DSPY_PIP_FMT,        WIN_16BPP);
    LCD_SET_D( DSPY_PIP_TP_COLR,    0x00000000 );
    LCD_SET_D( DSPY_PIP_0_ADDR_ST,  PIP_FB0 );

    LCD_SET_D( DSPY_PIP_OFST_ST,    0 );
    LCD_SET_W( DSPY_PIP_OFST_PIXL,  g_PIP_bpp );                        // byte unit
    LCD_SET_W( DSPY_PIP_OFST_ROW,   g_PIP_w * g_PIP_bpp );              // byte unit
    LCD_SET_W( DSPY_PIP_W,          g_PIP_w );
    LCD_SET_W( DSPY_PIP_H,          g_PIP_h );
    LCD_SET_W( DSPY_PIP_X,          0 );
    LCD_SET_W( DSPY_PIP_Y,          0 );
    LCD_SET_D( DSPY_PIP_PIXL_CNT,   g_PIP_w * g_PIP_h);
	
    // LCD Scaling Setting
    LCD_SET_W( DSPY_SIN_W,              g_PIP_w );
    LCD_SET_W( DSPY_SIN_H,              g_PIP_h );
    LCD_SET_D( DSPY_SOUT_GRAB_PIXL_CNT, g_PIP_w * g_PIP_h );
    LCD_SET_W( DSPY_SOUT_GRAB_H_ST,     1 );
    LCD_SET_W( DSPY_SOUT_GRAB_H_ED,     g_PIP_w );
    LCD_SET_W( DSPY_SOUT_GRAB_V_ST,     1 );
    LCD_SET_W( DSPY_SOUT_GRAB_V_ED,     g_PIP_h );

    // preview
	#ifdef BUILD_FW
	
	// Draw 4 color blocks: Red/Green/Blue/White
    for (y = 0; y < 4; y++) {
        for (x = 0; x < g_PIP_w*g_PIP_h/4; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(y*g_PIP_w*g_PIP_h/4+x)), lcd_pat[y]);
        }
    }
    // Draw first 3 even line as Yellow color
    for (y = 0; y < 15; y += 5) {
    	for (x = 0; x < g_PIP_w; x++) {
        	MEM_SET_W( (PIP_FB0 + (g_PIP_bpp*(g_PIP_w*y + x))), 0xFFE0 );
    	}
    }

	#else
	
	
    for (y = 0; y < g_PIP_h/2; y++) {
    	// Red block
        for (x = 0; x < g_PIP_w/2; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[0]);
        }
        // Green block
        for (x = g_PIP_w/2; x < g_PIP_w; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[1]);
        }
    }
    for (y = g_PIP_h/2; y < g_PIP_h; y++) {
    	// Blue block
        for (x = 0; x < g_PIP_w/2; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[2]);
        }
        // White block
        for (x = g_PIP_w/2; x < g_PIP_w; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[3]);
        }
    }

    // Draw first 3 even line as Yellow color
    for (y = 0; y < 15; y += 5) {
    	for (x = 0; x < g_PIP_w/2; x++) {
        	MEM_SET_W( (PIP_FB0 + (g_PIP_bpp*(g_PIP_w*y + x))), 0xFFE0 );
    	}
    }
	
	#endif
	
	
	//while(1);
#if (SECONDARY_DISPLAY==1) 
    LCD_SET_W( DSPY_CTL_0,         LCD_GET_W(DSPY_CTL_0) | SCD_DSPY_REG_READY); 
	LCD_SET_W( DSPY_SCD_CTL,       LCD_GET_W(DSPY_SCD_CTL) | LCD_FRAME_TX);
	while (LCD_GET_W(DSPY_SCD_CTL) & LCD_FRAME_TX);
#else
    LCD_SET_W( DSPY_PIP_CTL,       WIN_EN );
 
    LCD_SET_W( DSPY_CTL_0,         LCD_GET_W(DSPY_CTL_0) | LCD_FRAME_TX);
	while (LCD_GET_W(DSPY_CTL_0) & LCD_FRAME_TX);
#endif
    
    return;
}

void RTNA_LCD_InitMainLCD(void)
{
//TODO

    // Disable LCD
    LCD_SET_W( DSPY_CTL_0,          0 );


    LCD_SET_W( DSPY_CTL_2,          PRM_DSPY_REG_READY   |
                                    DSPY_PRM_SEL(DSPY_TYPE_PL_LCD) |
                                    DSPY_PRM_EN);
    LCD_SET_W( DSPY_PLCD_CTL,       PLCD_BUS_8BPP    | //Rogers@JWD: PLCD_BUS_16BPP 
                                    PLCD_PH1         |
                                    PLCD_PO1         |
                                    PLCD_TYPE_80     |
                                    LCD_PL1_PL2  );    
/*
#define PLCD_RGB565_B16           0x0000
        #define PLCD_RGB444_B16           0x0001
        #define PLCD_RGB666_B16           0x0002
        #define PLCD_RGB888_B8            0x0003
        #define PLCD_RGB332_B8            0x0004
        #define PLCD_RGB444_B8            0x0005
        #define PLCD_RGB666_B8            0x0006
        #define PLCD_RGB565_B8            0x0007
        #define PLCD_RGB666_B18           0x0008
        #define PLCD_RGB666_B9_9          0x0009
        #define PLCD_RGB666_B2_16         0x000A
        #define PLCD_RGB666_B16_2         0x000B
        #define LCD_RGB24_B16_8             0x000C
        #define LCD_RGB24_B8_16             0x000D
        #define LCD_RGB666_B8_2_7           0x0010
        #define LCD_RBG444_B12_16           0x0020
        #define LCD_RBG444_B12_16_15_14     0x0040
        #define LCD_RGBB9_9_17              0x0080

        #define LCD_RGB666_B9               0x0100
        #define LCD_RGB666_B2_16            0x0200
        #define LCD_RGB666_B16_2            0x0300
        #define LCD_B8_RGB666_12_17         0x0400
        #define LCD_B16_1_8_10_17           0x0800
        #define LCD_B8_10_17                0x1000
        #define LCD_B8_1_8                  0x2000
        #define LCD_B8_RGB565_G_LSB_FIRST   0x4000
*/        

    LCD_SET_W(DSPY_PLCD_FMT, PLCD_RGB565_B8);  //Rogers@JWD: Add
    //LCD_SET_W(DSPY_PLCD_FMT, PLCD_RGB666_B8);
    //LCD_SET_W(DSPY_PLCD_FMT, PLCD_RGB666_B8|LCD_RGB666_B8_2_7);
     
    
//[???]    pLCD->LCD_CLK_CTL
    LCD_SET_W( DSPY_PLCD_RS_CS_CYC,  0 ); 
    LCD_SET_W( DSPY_PLCD_CS_RW_CYC,  1); 
    LCD_SET_W( DSPY_PLCD_RW_CYC   ,  4); 

//#ifdef BUILD_HOST
//MMPH_HIF_RegGetW(0x704C);
//MMPH_HIF_RegSetW(0x704C, 0x0000);
//#endif

    LCD_SET_W(DSPY_CTL_4,           LCD_OUT_RGB       |
                                    LCD_OUT_SEL_LCD1  |
                                    LCD_BG_COLR_888);

//#ifdef BUILD_HOST
//MMPH_HIF_RegGetW(0x704C);
//#endif


    LCD_SET_W( DSPY_W,          	g_PANL_w );
    LCD_SET_W( DSPY_H,          	g_PANL_h );
    LCD_SET_D( DSPY_PIXL_CNT,		g_PANL_w * g_PANL_h );
//#ifdef BUILD_HOST
//MMPH_HIF_RegGetL(0x7048);
//MMPH_HIF_RegSetL(0x7048, 0x00000000);
//#endif
//#ifdef BUILD_HOST
//MMPH_HIF_RegGetL(0x7048);
//#endif


    //[Jerry]
    // When PIP format is YUV (422,420) it's forced to be scaling path
    // Scaling bypass only controls the N/M and LPF, all regsiter should
    // be correct when using YUV format

    // LCD Scaling Setting
    LCD_SET_W( DSPY_SCAL_IN_THR,     16 );
    LCD_SET_W( DSPY_SCAL_CTL,       DSPY_SCAL_BYPASS );
    LCD_SET_W( DSPY_SOUT_CTL,       DSPY_SOUT_RGB_EN );
    LCD_SET_W( DSPY_SEDGE_CTL,      DSPY_SEDGE_BYPASS );

    // COMS frame count ?
    // Bypass LUT ?

    LCD_SET_B(DSPY_RGB_SHARE_P_LCD_BUS,      P_LCD_ONLY);    //Rogers@JWD: Add 
    
    // ====== Panel initial sequence ======
    LCD_SET_W( DSPY_PLCD_CTL,        LCD_GET_W(DSPY_PLCD_CTL) & ~PLCD_CMD_BURST );
//    LCD_SET_W( LCD_PANL_CTL,        LCD_GET_W(LCD_PANL_CTL) & ~LCD_PANL_CMD_BURST);

    // Enable auto transfer set address
    LCD_SET_W( DSPY_CTL_0,          LCD_FRAME_TX_SETADDR_EN |
                                    LCD_AUTO_TX_SETADDR_EN );
}

void RTNA_LCD_AdjustBrightness(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast_R(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustBrightness_R(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustContrast_B(MMP_BYTE level)
{
//TODO
}

void RTNA_LCD_AdjustBrightness_B(MMP_BYTE level)
{
//TODO
}

MMP_USHORT m_LCD_Direct = 0xDC;

void RTNA_LCD_Direction(LCDDIR dir)
{
	//LCD_SEND_IDX(0x36);

	switch(dir)
    {
        case DOWNLEFT_UPRIGHT:
        	//LCD_SEND_CMD(0xD9);
            //m_LCD_Direct = 0x98;
            LCD_SET_W( DSPY_LCD_TX_1,        0xDC );
            break;
        case UPRIGHT_DOWNLEFT:
	        //LCD_SEND_CMD(0xD9);
            //m_LCD_Direct = 0x4C;  
            LCD_SET_W( DSPY_LCD_TX_1,        0xDC );
            break;
        case DOWNRIGHT_UPLEFT:
        	//LCD_SEND_CMD(0x99);
            //m_LCD_Direct = 0x98;//0xDC
            LCD_SET_W( DSPY_LCD_TX_1,        0x08 );
            break;
        case UPLEFT_DOWNRIGHT:
        default:
        	//LCD_SEND_CMD(0xD9);
            //m_LCD_Direct = 0xDC;//0x08
            LCD_SET_W( DSPY_LCD_TX_1,        0xDC );
            break;
    }
    //LCD_SEND_IDX(0x2C);
    
//#define  LCD_SEND_IDX(idx)		MMPD_LCD_SendIndex(idx)
//#define  LCD_SEND_CMD(cmd)		MMPD_LCD_SendCommand(cmd)

}

void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value)
{
//TODO
}

void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value)
{
//TODO
}

#include "disp_drv.h"

/* Set Display property
 * Width, Height, Color Depth, Display Type */
DISP_PROP	this_p = {240, 320, 24, DISP_LCDV};

DISP_PROP* RTNA_GetDisplayProp()
{
	return &this_p;	
}


