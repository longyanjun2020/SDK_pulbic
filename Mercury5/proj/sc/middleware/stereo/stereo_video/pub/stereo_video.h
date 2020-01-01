#ifndef STEREO_VIDEO_H
#define STEREO_VIDEO_H

#include <stdint.h>

int get_stereo_video_depth(void);
void set_stereo_video_depth(int depth);
int get_stereo_video_lean(void);
void set_stereo_video_lean(int lean);

int convert_stereo_video(uint16_t* dst_buf, uint16_t* src_buf, int x, int y, int width, int height, int stride, int rotate_mode);
int convert_3DLR(uint16_t *dst_buf, uint16_t *src_l, uint16_t *src_r, int x, int y, int width, int height, int stride, int rotate_mode);

#ifdef WIN32
int convert_stereo_video_win32(uint32_t *outbuf, uint8_t *src_y, uint8_t *src_u, uint8_t *src_v,
                               int width, int height, int stride_y, int stride_uv);
int convert_3DLR_win32(uint32_t *outbuf, uint8_t *src_y, uint8_t *src_u, uint8_t *src_v,
                       int width, int height, int stride_y, int stride_uv);
#endif
#endif //STEREO_VIDEO_H
