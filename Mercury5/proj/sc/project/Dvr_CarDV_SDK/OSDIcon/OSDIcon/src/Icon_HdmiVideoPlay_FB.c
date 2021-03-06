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
* Source file: Icon_HdmiVideoPlay_FB
* Dimensions:  20 * 19
* NumColors:   2
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

static GUI_CONST_STORAGE GUI_COLOR ColorsIcon_HdmiVideoPlay_FB[] = {
     0x101010,0xC3C3C3
};

static GUI_CONST_STORAGE GUI_LOGPALETTE PalIcon_HdmiVideoPlay_FB = {
  2,	/* number of entries */
  1, 	/* Has transparency */
  &ColorsIcon_HdmiVideoPlay_FB[0]
};

static GUI_CONST_STORAGE unsigned char acIcon_HdmiVideoPlay_FB[] = {
  ________, ________, ________,
  ________, _X______, __X_____,
  ________, XX______, _XX_____,
  _______X, XX______, XXX_____,
  ______XX, XX_____X, XXX_____,
  _____XXX, XX____XX, XXX_____,
  ____XXXX, XX___XXX, XXX_____,
  ___XXXXX, XX__XXXX, XXX_____,
  __XXXXXX, XX_XXXXX, XXX_____,
  _XXXXXXX, XXXXXXXX, XXX_____,
  __XXXXXX, XX_XXXXX, XXX_____,
  ___XXXXX, XX__XXXX, XXX_____,
  ____XXXX, XX___XXX, XXX_____,
  _____XXX, XX____XX, XXX_____,
  ______XX, XX_____X, XXX_____,
  _______X, XX______, XXX_____,
  ________, XX______, _XX_____,
  ________, _X______, __X_____,
  ________, ________, ________
};

GUI_CONST_STORAGE GUI_BITMAP bmIcon_HdmiVideoPlay_FB = {
  20, /* XSize */
  19, /* YSize */
  3, /* BytesPerLine */
  1, /* BitsPerPixel */
  acIcon_HdmiVideoPlay_FB,  /* Pointer to picture data (indices) */
  &PalIcon_HdmiVideoPlay_FB  /* Pointer to palette */
};

/* *** End of file *** */
