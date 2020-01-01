//==============================================================================
//
//  File        : lcd_chimei_wvga.c
//  Description : SONY 240x320 LCD Panel Control Function
//  Author      : Philip Lin
//  Revision    : 1.1
//
//==============================================================================



//==============================================================================
//
//                              MACRO for different environment
//
//==============================================================================

#ifdef BUILD_CE
#undef BUILD_FW
#endif

#ifdef BUILD_FW

#include "lib_retina.h"
#include "mmpf_reg_display.h"
#include "mmpf_reg_gbl.h"

#define  LCD_DECL               //AITPS_LCD   pLCD  = AITC_BASE_LCD
#define  LCD_WAIT(cnt)          RTNA_WAIT_MS(cnt)
#define  LCD_CMD(idx, cmd)      RTNA_LCD_BurstCmd(idx, cmd)

#define  GBL_SET_B(reg, val)    //(pGBL->##reg) = (val)
#define  GBL_GET_B(reg)         //(pGBL->##reg)

#define  LCD_GET_W(reg)         //(pLCD->##reg)
#define  LCD_GET_B(reg)         //(pLCD->##reg)
#define  LCD_SET_B(reg, val)    //(pLCD->##reg) = (val)
#define  LCD_SET_W(reg, val)    //(pLCD->##reg) = (val)
#define  LCD_SET_D(reg, val)    //(pLCD->##reg) = (val)
#define  MEM_SET_W(addr, val)   *(MMP_USHORT*)(addr) = (val);

#define  PIP_FB0                g_PIP_fb0   // refer to BSP\lib_retina.c

#else

#include "ait_utility.h"
#include "mmp_lib.h"

#include "mmph_hif.h"
//#include "mmp_reg_display.h"
//#include "mmp_reg_gbl.h"
#include "mmpd_system.h"

#define  LCD_DECL
#define  LCD_WAIT(cnt)          
#define  LCD_CMD(idx, cmd)      MMPD_LCD_SendIndexCommand(idx, cmd)

#define  GBL_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  GBL_GET_B(reg)         MMPH_HIF_RegGetB(reg)

#define  LCD_GET_W(reg)         MMPH_HIF_RegGetW(reg)
#define  LCD_GET_B(reg)         MMPH_HIF_RegGetB(reg)
#define  LCD_SET_B(reg, val)    MMPH_HIF_RegSetB(reg, val)
#define  LCD_SET_W(reg, val)    MMPH_HIF_RegSetW(reg, val)
#define  LCD_SET_D(reg, val)    MMPH_HIF_RegSetL(reg, val)
#define  MEM_SET_W(addr, val)   MMPH_HIF_MemSetW(addr, val)

#endif

#define LCD_SDI_PAD_0 (0)
#define LCD_SDI_PAD_1 (1)

#define UPS051_MODE (0)
#define UPS052_MODE (1)

#define RESOL_320X240 (0)
#define RESOL_360X240 (1)

#define A030DW01_MODE UPS052_MODE
#define A030DW01_RESOL RESOL_360X240
#define USE_LCD_SDI_PAD LCD_SDI_PAD_1

//==============================================================================
//
//                              CONSTANTS & VARIABLES
//
//==============================================================================

//[GLOBAL] LCD configuration
#if (A030DW01_MODE == UPS051_MODE)
MMP_USHORT  g_PANL_w  = 320;
#endif

#if (A030DW01_MODE == UPS052_MODE)
#if (A030DW01_RESOL == RESOL_320X240)
MMP_USHORT  g_PANL_w  = 320;
#endif
#if (A030DW01_RESOL == RESOL_360X240)
MMP_USHORT  g_PANL_w  = 360;
#endif
#endif

MMP_USHORT  g_PIP_w   = 320;

MMP_USHORT  g_PIP_bpp = 2; // byte per pixel
//[GLOBAL]

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
}


//=====================================================================//
void RTNA_LCD_RGB_Test(void)
{
#if 1
    int     x, y;
    MMP_USHORT  lcd_pat[] = {0xF800, 0x07E0, 0x001F, 0xFFFF};
    //MMP_USHORT  lcd_pat[] = {0x07E0, 0xF800, 0xFFFF,  0x001F};
    //MMP_USHORT  lcd_pat[] = {0x001F, 0x001F, 0x001F, 0x001F};

    LCD_DECL;

    LCD_SET_W( DSPY_WIN_PRIO,       (ICON_WIN  << WIN_1_SHFT) |
                                    (OVLY_WIN  << WIN_2_SHFT) |
                                    (PIP_WIN   << WIN_3_SHFT) |
                                    (MAIN_WIN  << WIN_4_SHFT) );


#if (SECONDARY_DISPLAY == 1) 
    LCD_SET_D( DSPY_SCD_BG_COLR,    0x00000000 );

    LCD_SET_W( DSPY_SCD_CTL,         LCD_FRAME_TX_SETADDR_EN |
                                    SCD_SRC_RGB565 | 
                                    SCD_565_2_888_STUFF_0);

    LCD_SET_D( DSPY_SCD_WIN_ADDR_ST,   PIP_FB0 );
    LCD_SET_D( DSPY_SCD_WIN_OFST_ST,     0 );
    LCD_SET_W( DSPY_SCD_WIN_W,           g_PIP_w );
    LCD_SET_W( DSPY_SCD_WIN_H,           g_PIP_h );
    LCD_SET_W( DSPY_SCD_WIN_X,           0 );
    LCD_SET_W( DSPY_SCD_WIN_Y,           0 );
    LCD_SET_D( DSPY_SCD_WIN_PIXL_CNT,    g_PIP_w * g_PIP_h);
#else
    LCD_SET_D( DSPY_BG_COLR,    0xFFFFFFFF );

    LCD_SET_W( DSPY_PIP_FMT,         WIN_16BPP);
    //LCD_SET_D( DSPY_PIP_TP_COLR,     0x00000000 );

    LCD_SET_D( DSPY_PIP_0_ADDR_ST,   PIP_FB0 );
    LCD_SET_D( DSPY_PIP_OFST_ST,     0 );
    LCD_SET_W( DSPY_PIP_OFST_PIXL,   g_PIP_bpp );                        // byte unit
    LCD_SET_W( DSPY_PIP_OFST_ROW,    g_PIP_w * g_PIP_bpp );              // byte unit
    LCD_SET_W( DSPY_PIP_W,           g_PIP_w );
    LCD_SET_W( DSPY_PIP_H,           g_PIP_h );
    LCD_SET_W( DSPY_PIP_X,           0 );
    LCD_SET_W( DSPY_PIP_Y,           0 );
    LCD_SET_D( DSPY_PIP_PIXL_CNT,    g_PIP_w * g_PIP_h);
#endif


    //[Jerry]
    // When PIP format is YUV (422,420) it's forced to be scaling path
    // Scaling bypass only controls the N/M and LPF, all regsiter should
    // be correct when using YUV format

    // LCD Scaling Setting
    LCD_SET_W( DSPY_SIN_W,           g_PIP_w );
    LCD_SET_W( DSPY_SIN_H,           g_PIP_h );
    LCD_SET_D( DSPY_SOUT_GRAB_PIXL_CNT,   g_PIP_w * g_PIP_h );
    LCD_SET_W( DSPY_SOUT_GRAB_H_ST,  1 );
    LCD_SET_W( DSPY_SOUT_GRAB_H_ED,  g_PIP_w );
    LCD_SET_W( DSPY_SOUT_GRAB_V_ST,  1 );
    LCD_SET_W( DSPY_SOUT_GRAB_V_ED,  g_PIP_h );


    // Display different pattern for HOST and FW
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
/*
    for (y = 0; y < g_PIP_h; y++) {
    	// Red block
        for (x = 0; x < g_PIP_w; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[0]);
        }
    }
*/   
/*
    for (y = 0; y < 80; y++) {
    	// Red block
        for (x = 0; x < 800; x++) {
            MEM_SET_W((PIP_FB0 + g_PIP_bpp*(g_PIP_w*y+x)), lcd_pat[0]);
        }
    } 
*/    
    
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
/*
    // Draw first 3 even line as Yellow color
    for (y = 0; y < 15; y += 5) {
    	for (x = 0; x < g_PIP_w/2; x++) {
        	MEM_SET_W( (PIP_FB0 + (g_PIP_bpp*(g_PIP_w*y + x))), 0xFFE0 );
    	}
    }
*/    

	#endif

#if (SECONDARY_DISPLAY == 1) 
#else
    LCD_SET_W( DSPY_PIP_CTL,         WIN_EN );
#endif

#endif

    return;
}

void RTNA_LCD_InitMainLCD(void)
{
    return;	
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