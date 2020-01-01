#ifndef RENDER_C_API_H
#define RENDER_C_API_H

#include "avp_mvc_types.h"
#include "avp_mvc_decoder.h"
#include "avp_global_buffer.h"
#include "avp_sdlo_api.h"
#include <assert.h>
#include <sdl.h>

#define QUEUE_SIZE 128

#if defined(__cplusplus)
extern "C" {
#endif
int  std_render_thread_start(VID_SETUP *setup, struct sdl_inst sdl_out);
void std_render_packet_inqueue(int handle, VID_PICTURE *decPicture);
void std_wait_available_packet(int handle);
void std_wait_render_finish(int handle);
#if defined(__cplusplus)
}
#endif

struct CRENDER
{
  struct sdl_inst sdl_out;
  VID_SETUP* vidSetup;
  VID_PICTURE* decPicture;
  SDL_Event event; 
 
};

#endif
