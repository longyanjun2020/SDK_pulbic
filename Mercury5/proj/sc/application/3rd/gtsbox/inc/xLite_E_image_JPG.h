#ifndef __XLITE_E_IMAGE_JPG_H__
#define __XLITE_E_IMAGE_JPG_H__


#include "xLite_E_internal.h"

/*!
 * @file xlite_E_image_JPG.h
 * @brief jpg图形资源操作
 */


#if xlite_E_addon_jpg == 1

xl_int32 xlite_E_image_load_jpeg(xlite_himage* himage_ptr,const xl_uint8* buffer,xl_uint32 buffer_length,xl_int32 *w,xl_int32 *h);

xl_void xlite_E_draw_rgb565(xlite_graphics* g, const xlite_rect* t_rect,xlite_himage s_img,xl_int32 s_x,xl_int32 s_y);

#endif


#endif


