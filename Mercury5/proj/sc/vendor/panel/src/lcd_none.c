//==============================================================================
//
//  File        : lcd_none.c
//
//==============================================================================



//==============================================================================
//
//                              MACRO for different environment
//
//==============================================================================

#include "lcd_common.h"

#ifdef BUILD_FW

#include "reg_retina.h"
#include "lib_retina.h"

#include "mmpf_reg_display.h"
#include "mmpf_reg_gbl.h"

#define  LCD_DECL               //AITPS_LCD   pLCD  = AITC_BASE_LCD
#define  GBL_DECL               //AITPS_GBL   pGBL  = AITC_BASE_GBL
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
//#define  LCD_WAIT(cnt)          
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

//#include "mmps_vidplay.h"
//#include "mmps_audio.h"

#define LCD_SDI_PAD_0 (0)
#define LCD_SDI_PAD_1 (1)

#define USE_LCD_SDI_PAD LCD_SDI_PAD_1

#define ENABLE_LCD_ILI9242_LOG (0)

typedef enum _LCDDIR{ //For compiler
	UPLEFT_DOWNRIGHT = 0,
	DOWNLEFT_UPRIGHT,
	UPRIGHT_DOWNLEFT,
	DOWNRIGHT_UPLEFT
}LCDDIR;

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMPF_PANEL_ATTR m_PanelAttr = 
{
	320, 
	240, 
	LCD_TYPE_MAX,   
	LCD_PRM_CONTROLER, 
	0,
	
	NULL, 
	NULL,
	
	LCD_BUS_WIDTH_8, 
	LCD_PHASE0, 
	LCD_POLARITY0, 
	LCD_MCU_80SYS, 
	0, 
	0, 
	0, 
	LCD_RGB_ORDER_RGB,
		
	MMP_FALSE, 
	LCD_SIG_POLARITY_L, 
	LCD_SIG_POLARITY_L, 
	0x00/*RGB_D24BIT_RGB888*/,
	{0}
};


//==============================================================================
//
//                              CONSTANTS & VARIABLES
//
//==============================================================================

//[GLOBAL] LCD configuration
MMP_USHORT  g_PANL_w  = 320;


MMP_USHORT  g_PIP_w   = 320;

MMP_USHORT  g_PIP_bpp = 2; // byte per pixel

void RTNA_LCD_InitMainLCD(void);
void RTNA_LCD_Init(void)
{
    RTNA_LCD_InitMainLCD();
}

void RTNA_LCD_RGB_Test(void){return;}
void RTNA_LCD_InitMainLCD(void)
{
   
}
void RTNA_LCD_AdjustBrightness(MMP_UBYTE level){return;}
void RTNA_LCD_AdjustContrast(MMP_UBYTE level){return;}
void RTNA_LCD_AdjustContrast_R(MMP_BYTE level){return;}
void RTNA_LCD_AdjustBrightness_R(MMP_UBYTE level){return;}
void RTNA_LCD_AdjustContrast_B(MMP_BYTE level){return;}
void RTNA_LCD_AdjustBrightness_B(MMP_UBYTE level){return;}
void RTNA_LCD_Direction(LCD_DIR dir){return;}
void RTNA_LCD_SetReg(MMP_ULONG reg, MMP_UBYTE value){return;}
void RTNA_LCD_GetReg(MMP_ULONG reg, MMP_ULONG *value){return;}
void RTNA_LCD_Show_Image(MMP_USHORT *psrc_buf){return;}
void RTNA_LCD_ReduceHblank(MMP_BYTE enable){return;}


void RTNA_LCD_DispAll(MMP_UBYTE* map){return;}
void RTNA_LCD_DisplayOn(void){}
void RTNA_LCD_SetDisplayOnOff(MMP_UBYTE OnOff){return;}
void RTNA_LCD_SOFT_Reset(void){}
void RTNA_LCD_DispALL(MMP_UBYTE* map){return;}

#include "disp_drv.h"

DISP_PROP	this_p = {720, 480, 16, DISP_NTSC};

DISP_PROP* RTNA_GetDisplayProp()
{
	return &this_p;	
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

#if 0
void RTNA_LCD_AdjustBrightness(MMP_UBYTE level)
{
	//MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0300 | level); 	// Brightness(R03h[7:0]): RGB brightness level control
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
	//MMPF_LCD_Write16BitCmd(&m_PanelAttr, 0x0D00 | level); 	// CONTRAST(R0Dh[7:0]): RGB contrast level setting, the gain changes (1/64) bit.
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
#endif
