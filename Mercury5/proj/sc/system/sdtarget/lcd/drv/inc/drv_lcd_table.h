
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
void DrvLcd_GetWholeLcmTable(void);


#endif//ndef __LCD_DRV__TABLE_H__


