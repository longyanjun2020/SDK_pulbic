/*
** gal.h: graphic absract layer header file.
**
** Copyright (C) 2007-2008 SKY-MOBI AS.  All rights reserved.
**
** This file is part of the simple gui library.
** It may not be redistributed under any circumstances.
*/

#ifndef _SGL_GAL_H
#define _SGL_GAL_H

#include "sgl_types.h"
#include "mrporting.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef struct _screendevice
{
	mr_screeninfo scrInfo;
}* GAL_GC;

extern struct _screendevice scrdev;

/**
 * \brief Normal colors.
 */
#define COLOR_transparent	0x00000000
#define COLOR_darkred		0x00800000
#define COLOR_darkgreen		0x00008000
#define COLOR_darkyellow	0x00808000
#define COLOR_darkblue		0x00000080
#define COLOR_darkmagenta	0x00800080
#define COLOR_darkcyan		0x00008080
#define COLOR_lightgray		0x00c0c0c0
#define COLOR_darkgray		0x00808080
#define COLOR_red			0x00ff0000
#define COLOR_green			0x0000ff00
#define COLOR_yellow			0x00ffff00
#define COLOR_blue			0x000000f0
#define COLOR_magenta		0x00ff00ff
#define COLOR_cyan			0x0000ffff
#define COLOR_lightwhite		0x00ffffff
#define COLOR_black			0x00000000

/**
 * \brief The phisical graphic context handle.
 */
#define PHYSICALGC	(&scrdev)

/**
 * \brief Intialize the graphic abstract layer.
 */
void GAL_Initialize (VOID);

/**
 * \brief Terminate the graphic abstract layer.
 */
void GAL_Terminate (VOID);
/*********************add xuyitao********************/
void GALP_drawLine(int16 x1, int16 y1, int16 x2, int16 y2, Uint32 pixel);
void GALP_drawRect(int16 x, int16 y, int16 w, int16 h, Uint32 pixel);
void GALP_drawPointEx(int16 x, int16 y, Uint32 pixel);
void GALP_refreshScreen(int16 x, int16 y, uint16 w, uint16 h);
int32 mrc_drawText(char* pcText, int16 x, int16 y, uint8 r,uint8 g,uint8 b, int is_unicode, uint16 font);
int mrc_textWidthHeight(char* pcText, int is_unicode, uint16 font, int32* w, int32* h);
char* sgl_malloc(int size);
int32 sgl_mem_free(void* mem);
int32 mrc_drawTextEx(char* pcText, int16 x, int16 y, mr_screenRectSt rect, mr_colourSt colorst, int flag, uint16 font);
void SGLTimerCb(U16 id);
void SGL_CreateTime(void);
void SGL_DestoryTime(void);
void SGL_StartTime(uint16 time);
void SGL_StopTime(void);
int32 SGL_event(int32 code, int32 param0, int32 param1);
int32 GAL_DrawIcon(u32 type,int16 x, int16 y,int16 h,int16 is_select); //x,y为显示的右上角




//export function

int32 mr_resumeSGLDraw(void);
int32 mr_suspendSGLDraw(void);
void mythroad_text_cb(int32 hText,u32 code);
void mythroad_dialog_cb(int32 hText,u32 code);
void mythroad_menu_cb(int32 hMenu,u32 code, u32 index);

/**********************end xuyitao********************/
/**
 * \brief Get the bytes per pixel.
 */
#define GAL_BytesPerPixel(gc) \
	DIV((gc)->scrInfo.bit + 7 , 8)

/**
 * \brief Get the bits per pixel.
 */
#define GAL_BitsPerPixel(gc) \
	((gc)->scrInfo.bit)

/**
 * \brief Get the screen width.
 */
#define GAL_Width(gc) \
	((gc)->scrInfo.width)

/**
 * \brief Get the screen height.
 */
#define GAL_Height(gc) \
	((gc)->scrInfo.height)

/**
 * \brief Get supported colors.
 */
#define GAL_Colors(gc) \
	(((gc)->scrInfo.bit >= 24)? (1 << 24): (1 << (gc)->scrInfo.bit))


/**
 * \brief Fill the box with a specific color.
 */
#define GAL_FillBox(gc, x, y, w, h, pixel) \
	GALP_drawRect((int16)(x), (int16)(y), (int16)(w), (int16)(h), pixel)

/**
 * \brief Draw a horizontal line.
 */
#define GAL_DrawHLine(gc, x, y, w, pixel) \
	GALP_drawLine((int16)(x), (int16)(y), (int16)((x)+(w)-1), (int16)(y), pixel)

/**
 * \brief Draw a vertical line.
 */
#define GAL_DrawVLine(gc, x, y, h, pixel) \
	GALP_drawLine((int16)(x), (int16)(y), (int16)(x), (int16)((y)+(h)-1), pixel)

/**
 * \brief Draw a pixel.
 */
#define GAL_DrawPixel(gc, x, y, pixel) \
	GALP_drawPointEx((int16)(x), (int16)(y),pixel)

/**
 * \brief Daw a normal line.
 */
#define GAL_Line(gc, x1, y1, x2, y2, pixel) \
	GALP_drawLine((int16)(x1), (int16)(y1), (int16)(x2), (int16)(y2), pixel)

/**
 * \brief Draw a rectangle.
 */
void GAL_Rectangle(GAL_GC gc, int x, int y, int w, int h, Uint32 pixel);

/**
 * \brief Draw a rectangle with a specific width.
 */
void GAL_Rectangle2(GAL_GC gc, int x, int y, int w, int h, int line, Uint32 pixel);

/**
 * \brief Flush all the screen.
 */
#define GAL_Flush(gc) \
	GALP_refreshScreen(0, 0, (uint16)(gc->scrInfo.width), (uint16)(gc->scrInfo.height))

/**
 * \brief Flush a region of the screen.
 */
#define GAL_FlushRegion(gc,  x,  y,  w, h) \
	GALP_refreshScreen((int16)(x), (int16)(y), (uint16)(w), (uint16)(h))

//from application.c
HWND Show_DialogWin(void* pDialogData);
VOID Refresh_DialogWin(HWND hWnd);
HWND Show_TextWin(void* pTextData);
VOID Refresh_TextWin(HWND hWnd);
HWND Show_MenuWin(void* pMenuData);
HWND Show_NetworkProfileWin(void* pProfiles);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _SGL_GAL_H */

