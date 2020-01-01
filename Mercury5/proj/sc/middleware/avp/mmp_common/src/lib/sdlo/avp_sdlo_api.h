#ifndef SDLO_API_H
#define SDLO_API_H

#include <stdint.h>
#include "avp_sdl.h"
#include "avp_ms_io.h"

struct sdl_inst {
    SDL_Surface *screen;
    SDL_Overlay *video;
    SDL_Rect dest;
#ifdef SUPPORT_SUBTITLE
    SDL_Surface *sVideo;
#endif
};

void sdlo_init_output(struct sdl_inst *sdl, int width, int height);

void sdlo_output_frame(struct sdl_inst *sdl,
                      uint8_t *y, uint8_t *u, uint8_t *v,
                      int width, int height,
                      int stride_y, int stride_uv,
                      int active_x, int active_y);

void sdlo_update_title(struct sdl_inst *sdl,
                       const ms_fnchar *filename,
                       int media_time,
                       int total_duration);

void sdlo_close(void);

void sdlo_update_screen(struct sdl_inst *sdl);

#endif
