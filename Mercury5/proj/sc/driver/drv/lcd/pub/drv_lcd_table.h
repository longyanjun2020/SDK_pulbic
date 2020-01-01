/****************************************************************************\
  @file     lcd_drv_table.h
  @brief    header file of LCD driver
  @date     2007/10/31
  @version  1.00
  @author
  @warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __LCD_DRV_TABLE_H__
#define __LCD_DRV_TABLE_H__

#include "drv_lcd.h"

typedef struct
{
  u8 *pTbl;
  u32 size;
} dev_Disptable_t;

typedef struct
{
    u16 CID;
    u16 padding;
    u8 *info_string;
    dev_LcdConfig_t *config;
} lcm_info_t;

u16  LCD_GetDeviceID_GI0(u16);
void LCD_Init_GI1(u8 reInit);
void LCD_SleepModeOn_GI2(void);
void LCD_SleepModeCancel_GI3(void);
void LCD_PowerOff_GI4(void);
void LCD_SetDisplayRange_GI6(u16 x, u16 y, u16 width, u16 height);
void LCD_DrawLogo_noGI(void);
void DrvLcdTbl_getDisplayTblAddr(dev_Disptable_t *pTb);
lcm_info_t const *DrvLcdTbl_GetInfo(void);
void DrvLcd_Search_DISP_TABLE(bool bCopyInMem);
#ifdef __CUS_LCM_TABLE_DRV_MEM__
void DrvLcd_GetWholeLcmTable(void);
#endif

void LCD_SetPanelSel(u8 panel_sel);


#endif//ndef __LCD_DRV__TABLE_H__

