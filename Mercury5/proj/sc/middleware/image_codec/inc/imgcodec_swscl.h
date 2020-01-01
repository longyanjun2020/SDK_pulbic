#ifndef _IMGCODEC_SWSCL_H_
#define _IMGCODEC_SWSCL_H_

#include "imgcodec_common.h"

typedef struct Image_Swscl Image_Swscl_t;

Image_Swscl_t *swscl_open(u32 src_width, u32 src_height,
                          u32 dst_width_rotated, u32 dst_height_rotated,
                          u32 dst_rgb_stride, u8 *dst_rgb_buf,
                          u32 dst_alp_stride, u8 *dst_alp_buf,
                          Image_RotationAngle angle, u8 bMirror, u8 bNoFilter);
void swscl_close(Image_Swscl_t *pSwscl);
s32 swscl_feedLine(Image_Swscl_t *pSwscl, u8 *src_rgb_buf, u8 *src_alp_buf);

#endif

