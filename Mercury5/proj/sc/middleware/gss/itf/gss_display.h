/**
 * \file gss_display.h
 * \brief Graphic sub system display buffer management
*/

#ifndef __GSS_DISPLAY_H__
#define __GSS_DISPLAY_H__

#include "vm_types.ht"

/*
typedef struct GSS_DISPLAYCFG_T  {
	u32 base_addr;
	u32 size; // in bytes
	u16 width;
	u16 height;
	GssCtrlPixelFormat_t pixel_format;
}GssDisplayCfg_t;
*/

//s32 gss_createDisplayBuffer(GssDisplay_t display_num, u16 width, u16 height, GssCtrlPixelFormat_t pixel_format);
//s32 gss_PaintPicture(GssDisplay_t display_num, u16 *buffer,  u16 x_pos, u16 y_pos, u16 width, u16 height);
s32 gss_PaintArea(GssDisplay_t display_num, u16 color,  u16 x_pos, u16 y_pos, u16 width, u16 height);
s32 gss_PrintDisplay(GssDisplay_t display_num);
s32 gss_PrintDisplayArea(GssDisplay_t display_num,  u16 x_pos, u16 y_pos, u16 width, u16 height);

#endif // __GSS_DISPLAY_H__
