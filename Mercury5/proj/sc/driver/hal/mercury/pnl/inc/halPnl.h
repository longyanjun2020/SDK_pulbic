////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/**
* @file     hal_scl_util.h
* @version
* @Platform I3
* @brief    This file defines the HAL SCL utility interface
*
*/

#ifndef __HALPNL_H__
#define __HALPNL_H__

typedef unsigned char   u8;
typedef signed   char   s8;
typedef          char   ascii;
typedef unsigned short  u16;
typedef          short  s16;
typedef unsigned int    u32;
typedef          int    s32;
typedef unsigned long long u64;
typedef      long long s64;
typedef unsigned char   bool;

typedef enum _LCD_PIX_ORDER {
    LCD_PIX_ORDER_RGB,
    LCD_PIX_ORDER_RBG,
    LCD_PIX_ORDER_GRB,
    LCD_PIX_ORDER_GBR,
    LCD_PIX_ORDER_BRG,
    LCD_PIX_ORDER_BGR
} LCD_PIX_ORDER;

typedef enum _LCD_TOP_CLK_SEL {
    LCD_TOP_CLK_LPLL,
    LCD_TOP_CLK_MPLL_160M,
    LCD_TOP_CLK_MPLL_144M,
    LCD_TOP_CLK_MPLL_108M,
    LCD_TOP_CLK_MPLL_216M,
    LCD_TOP_CLK_MPLL_240M
} E_LCD_TOP_CLK_SEL;


typedef enum
{
    HAL_LCD_FRM_END_INT,
	HAL_LCD_IDX_RDY_INT	,
	HAL_LCD_CMD_RDY_INT 	,
	HAL_LCD_RGB_VSYNC_INT 	,
	HAL_LCD_RGB_FRM_CNT_HIT_INT ,
	HAL_LCD_BUSY_INT 		,
	HAL_LCD_RGB_HSYNC_INT 		,
	HAL_LCD_RGB_LINE_MATCH_1_INT 			,
	HAL_LCD_RGB_LINE_MATCH_2_INT 			,
	HAL_LCD_FLM_INT_INT 			,
	HAL_LCD_RGB_UNFLOW_INT
}HALLCD_INT_STATUS;

#if 0
/* LCD Bus Width */
typedef enum _LCD_DATABUS_CFG {
    LCD_RGB888,
    LCD_RGB666,
    LCD_RGB565,
    LCD_RGB666_LOOSE_PACKED_MSB_ALIGN,
    LCD_RGB666_LOOSE_PACKED_LSB_ALIGN,
    LCD_RGB332,
    LCD_BGR888,
    LCD_BGR666,
    LCD_BGR565,
    LCD_BGR666_LOOSE_PACKED_MSB_ALIGN,
    LCD_BGR666_LOOSE_PACKED_LSB_ALIGN,
    LCD_BGR332,

    LCD_RGB888_SWAP,    //R7...R0, G7...G0, B7...B0
    LCD_RGB666_SWAP,
    LCD_RGB565_SWAP,
    LCD_RGB666_LOOSE_PACKED_MSB_ALIGN_SWAP,
    LCD_RGB666_LOOSE_PACKED_LSB_ALIGN_SWAP,
    LCD_RGB332_SWAP,
    LCD_BGR888_SWAP,
    LCD_BGR666_SWAP,
    LCD_BGR565_SWAP,
    LCD_BGR666_LOOSE_PACKED_MSB_ALIGN_SWAP,
    LCD_BGR666_LOOSE_PACKED_LSB_ALIGN_SWAP,
    LCD_BGR332_SWAP,
} LCD_DATABUS_CFG;
#endif

 void HalLCDSWRest(void );
 bool HalLCDQuerryPnlF(LCD_TYPE pnlType);
 LCD_BUS_WIDTH  HalLCDGeBusWidth(void);
 LCD_TYPE  HalLCDGeCurPanelType(void );
 u16  HalLCDGePanelWidth(void );
 u16  HalLCDGePanelHeight( void);

 void HalLCDOpenClk(E_LCD_TOP_CLK_SEL eTOP_LCD_CLK_SEL);
void HalLCDSetWidth(u16 u16Width);
void HalLCDSetHeight(u16 u16Height);
void HalLCDSetPixelCnt(u32 u32Cnt);

void  HalLCDSetBGRegion(u16 XOffset, u16 YOffset, u16 u16Width, u16 u16Height, u16 u16OutWidth);
void  HalLCDEnableBG(bool bEnBG);

void HalLCDShareBusSwitch(LCD_TYPE bPanelType);
void  HalLCD_SetOutPanelType(LCD_TYPE ubDevType);

u32 HalLCDSetRGB_CLK(u32 Frequency);
void  HalLCDSetRGBBus(LCD_DATABUS_CFG buscfg );
void  HalLCD_RGB_EN(bool uEnable);
void HalLCDSetRGB_V_Timing(u16 u8V_B_PORCH, u16 u8V_SYNC_W, u16 u8V_BLK);
void  HalLCDSetRGB_H_Timing(u16 u8V_B_PORCH, u16 u8V_SYNC_W, u16 u8V_BLK);
u64 HalLCDGetLpll_Idx(void);
void HalLCDSetRGB_V_Pol(bool bVPOL);
void HalLCDSetRGB_H_Pol(bool bHPOL);
void HalLCDSetRGB_DCLK_Pol(bool bDCLK_POL);
void HalLCD_DeltaRGB_EN(bool bEnable);
void HalLCD_DummyRGB_EN(bool bEnable);
void HalLCDSetRGB_LnOrder(LCD_PIX_ORDER EvenLnOrder, LCD_PIX_ORDER OddLnOrder);

void HalPLCD_Update(void);
void HalPLCD_Ctl(void);
void HalPLCD_SendCmd(void);
void HalPLCD_SendIndex(void);
void HalPLCD_AutoConfigIDXCmd(u32 u32Val, u8 u8TXNum, bool bIdxCmd);
void HalPLCD_SetMCUType(LCD_MCU_SYS McuSys);
void HalPLCD_SetCycleCnt(u16 RSLeadCs, u16 CSLeadRW, u16 RW_Cnt);
void HalPLCD_SetBUS( LCD_BUS_WIDTH busWidth,  LCD_PIX_ORDER Order, PLCD_DATABUS_CFG databus);
void HalPLCD_SetPHA( bool bPHA);
void HalPLCD_SetPOR( bool bPOR);
void HalPLCD_Set_IDX_CMD_NUM( u8 u8Num);
void HalLCDSetRGB_MVOP_Timing(u16 u16MVOPOffsetLine, u16 u16MVOPVsyncLine);

u32 HalLCDRegisterRead(u32 u32Addr);
void HalLCDRegisterWrite(u32 u32Addr, u16  u16value);
void HalLCDRegisterWriteBit(u32 u32Addr, bool bitValue, u16  u16bitfield);

#endif /*__HALPNL_H__*/
