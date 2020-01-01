////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef DRV_MFD_MAIN_SHARE_H
#define DRV_MFD_MAIN_SHARE_H

#include "drv_mfd_basetype.h"
#include "drv_mfd_mstar_fpga.h"
#include "drv_mfd_mvc_decoder.h"
#include "hal_mfd.h"

#ifdef INPUT_FROM_FILE
extern MY_FILE input_file;
extern MY_FILE output_file;
#endif

#ifdef _SIM_OUTPUT_
extern MY_FILE reg_file;
extern MY_FILE input_txt_file;
extern MY_FILE output_txt_file;
#endif

#ifdef SDL_OUTPUT
#include <sdl.h>
struct sdl_inst {
    SDL_Surface *screen;  //output via SDL
    SDL_Overlay *video;
    SDL_Rect dest;
};
extern struct sdl_inst sdl_out;
extern SDL_Event event;
#endif

#ifdef _HANTRO_PROFILE_
extern u32 dec_time[N_AVGS];
extern u32 max_time[N_AVGS];
extern u32 max_time_frame[N_AVGS];
extern u32 total_time;
extern u32 total_high;
extern u32 mb_dec_time[N_AVGS];
extern u32 mb_max_time[N_AVGS];
extern u32 max_time_mb[N_AVGS];
extern u32 max_time_mb_frame[N_AVGS];
extern u32 mb_total_time;
extern u32 mb_total_high;
#endif

#ifdef _HANTRO_SYS_PROFILE_
#include <time.h>
clock_t cpu_time = 0;
clock_t cpu_time_a1 = 0;
clock_t elapsed = 0;
#endif

/* macro to get smaller of two values */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int MVC_API vidInitDecoder_hantro_h264(int *handle, VID_SETUP *setup, uint8_t *decbuf, int *p_decbuf_size);
int MVC_API vidInitDecoder_hantro_mpeg2(int *handle, VID_SETUP *setup, uint8_t *decbuf, int *p_decbuf_size);
int MVC_API vidInitDecoder_hantro_mpeg4(int *handle, VID_SETUP *setup, uint8_t *decbuf, int *p_decbuf_size);

int MVC_API vidDecFrame_hantro_h264(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidDecFrame_hantro_mpeg2(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidDecFrame_hantro_mpeg4(int handle, VID_SETUP *setup, VID_PICTURE *pic);

int MVC_API vidGetLastFrame_hantro_h264(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidGetLastFrame_hantro_mpeg2(int handle, VID_SETUP *setup, VID_PICTURE *pic);
int MVC_API vidGetLastFrame_hantro_mpeg4(int handle, VID_SETUP *setup, VID_PICTURE *pic);


void report_performance(char* infile_name);
//#ifdef CYG_HWR_M3_BIG2
//void M4VD_ISR_Enable(unsigned char y);
//#endif
void M4VD_U03_StuffingEn(void);

/* The implementation of the following functions is system */
/* dependent and is not introduced here */
void allocInputBuffer(const u8 ** stream_virtual_address,
                      u32 * stream_bus_address,
                      u32 * streamLen);
void updateStreamBuffer(const u8 ** stream_virtual_address,
                        u32 * stream_bus_address,
                        u32 * bufferLen);
void displayOnScreen(u32 * outputPicture,
                     u32 pictureWidth,
                     u32 pictureHeight);

#ifdef SDL_OUTPUT
void init_output(struct sdl_inst* sdl, int width, int height);
#endif

#endif //DRV_MFD_MAIN_SHARE_H
