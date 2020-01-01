#ifndef __XLITE_E_IMAGE_BUFFER_H__
#define __XLITE_E_IMAGE_BUFFER_H__
#include "xlite.h"

//创建一个image_buffer
xlite_himage xlite_H_image_buffer_create(xl_uint16 width, xl_uint16 height);

//用一种颜色清空image_buffer
void xlite_H_image_buffer_clear(xlite_himage image_buffer, xl_uint16 color);

//移除image_buffer
void xlite_H_image_buffer_delete(xlite_himage image_buffer);

//把图画到image_buffer上
void xlite_H_image_buffer_draw(xlite_graphics* g, xlite_himage image_buffer,xl_int16 dx, xl_int16 dy,
	xl_uint16 width, xl_uint16 height, xlite_himage image, xl_int16 sx, xl_int16 sy);

//把image_buffer刷新到屏幕
void xlite_H_image_buffer_flush(xlite_graphics* g, xlite_himage image_buffer, int dx,int dy,
	xl_uint16 width, xl_uint16 height,int sx,int sy);

#endif