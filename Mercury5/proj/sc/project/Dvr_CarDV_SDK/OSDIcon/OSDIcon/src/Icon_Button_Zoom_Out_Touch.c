/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*
* C-file generated by
*
*        �C/GUI-BitmapConvert V5.04.
*        Compiled Jan  8 2010, 16:46:31
*          (c) 2002-2005  Micrium, Inc.
  www.micrium.com

  (c) 1998-2005  Segger
  Microcontroller Systeme GmbH
  www.segger.com
*
**********************************************************************
*
* Source file: Icon_Button_Zoom_Out_Touch
* Dimensions:  36 * 32
* NumColors:   48
*
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/*   Palette
The following are the entries of the palette table.
Every entry is a 32-bit value (of which 24 bits are actually used)
the lower   8 bits represent the Red component,
the middle  8 bits represent the Green component,
the highest 8 bits (of the 24 bits used) represent the Blue component
as follows:   0xBBGGRR
*/

static GUI_CONST_STORAGE GUI_COLOR ColorsIcon_Button_Zoom_Out_Touch[] = {
     0xFE00FE,0x00B4FF,0x640000,0x630000
    ,0x620000,0x610000,0x5F0000,0x5E0000
    ,0x5C0000,0x5B0000,0x590000,0x560000
    ,0x540000,0x520000,0x500000,0x4D0000
    ,0x4A0000,0x470000,0x440000,0x410000
    ,0x3F0000,0x3C0000,0x3A0000,0x370000
    ,0x350000,0x340000,0x330000,0x320000
    ,0x310000,0x731818,0x863838,0x4D2020
    ,0x4C2020,0x512828,0x904848,0xA26565
    ,0x988080,0xDDC7C7,0xBEAEAE,0xE7D7D7
    ,0xF3EBEB,0xE0D9D9,0xF7F2F2,0xF0EDED
    ,0xFEFEFE,0x030303,0x000000,0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalIcon_Button_Zoom_Out_Touch = {
  48,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsIcon_Button_Zoom_Out_Touch[0]
};

static GUI_CONST_STORAGE unsigned char acIcon_Button_Zoom_Out_Touch[] = {
  0x00, 0x00, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x00, 0x00,
  0x00, 0x28, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2A, 0x00,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x2D, 0x2E, 0x2C, 0x2C, 0x2D, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2C, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D, 0x2D, 0x2E, 0x2D, 0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D, 0x2D, 0x2E, 0x2D, 0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2C, 0x2C, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x2D, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2E, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2C, 0x2D, 0x2E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2C, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2E, 0x2D, 0x2C, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2C, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2D, 0x2D, 0x2D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x2C, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2C,
  0x00, 0x29, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x2B, 0x00,
  0x00, 0x00, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x00, 0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmIcon_Button_Zoom_Out_Touch = {
  36, /* XSize */
  32, /* YSize */
  36, /* BytesPerLine */
  8, /* BitsPerPixel */
  acIcon_Button_Zoom_Out_Touch,  /* Pointer to picture data (indices) */
  &PalIcon_Button_Zoom_Out_Touch  /* Pointer to palette */
};

/* *** End of file *** */
