/****************************************************************************\
  \file     lcd_logo.h
  \brief    power on logo
  \date     2007/11/30
  \version  1.00
  \author
  \warning

--------------------------------------------------------------------------
  Historical :
-----------------------------------------------------------------------------
    Date  | Author  | Err  |  Modification
----------+---------+------+-----------------------------------------------
----------+---------+------+-----------------------------------------------
\****************************************************************************/
#ifndef __LCD_LOGO_H__
#define __LCD_LOGO_H__

/* QCIF 176x220 */
//extern const u16 power_on_logo[];// removde for reducing code size

/* QVGA 240x320 */
//extern const u16 power_on_logo_QVGA[];
#if defined(__CUS_BOOTUP_LOGO__)
extern const u16 power_on_logo_Mstar[];
#else
#if defined(__CUS_BOOTUP_LOGO__)
extern const u16 power_on_logo_Mstar[];
#else
#if defined(__PNG_BOOTUP_LOGO__)
extern const u8 power_on_logo_Mstar[];
#else
extern const u16 power_on_logo_Mstar[];
#endif
#endif
#endif

enum LOGO_STATUS
{
    STATUS_ERROR,
    STATUS_FORMAT_ERROR,
    STATUS_RESOLUTION_ERROR,
    STATUS_ALIGNMENT_ERROR,
    STATUS_INDEX_ERROR,
    STATUS_SUCCESS
};

typedef struct
{
    u16 Status;
    u32 size;
    u32 Width;
    u32 Height;
    u16 *pRaw;
    u32 CusRecordAddr;
    u32 MemFreeAddr;
} BootUpLogo_t;

typedef struct
{
    u16 xStart;
    u16 yStart;
    u16 Width;
    u16 Height;
} BootUpLogoParam_t;

#endif//ndef __LCD_LOGO_H__
