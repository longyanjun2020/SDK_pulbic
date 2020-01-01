#ifndef __XLITE_H_IMAGE_565_H__
#define __XLITE_H_IMAGE_565_H__


#include "xLite_E_internal.h"

xl_void xlite_H_image_565_draw(xlite_raster* r,xlite_himage t_img,const xlite_rect* t_rect,xlite_himage s_img,xl_int32 s_x,xl_int32 s_y);

xlite_himage xlite_H_image_565_create_from_image(xlite_himage s_img);


#endif