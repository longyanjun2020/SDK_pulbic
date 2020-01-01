/**
 * \file gss_2dgp_itf.h
 * \brief 2dgp interface for V2751
*/

#ifndef __GSS_2DGP_ITF_H__
#define __GSS_2DGP_ITF_H__

#include "vm_types.ht"

#define GSS_2DGP_OK 1
#define GSS_2DGP_NOK -1

typedef struct {
   u16      width;
   u16      height;
   u32      src_addr;
   u32      dst_addr;
   u16      key_color;
   bool     transparency;
   u8       rop;
   bool     alphablending;
   u8       alphablending_lvl;
   bool     jnj;
   bool     dir;
} gss_2dpg_t;

typedef struct{
   u32 buffer_addr;
   u16 x_start;
   u16 y_start;
   u16 x_end;
   u16 y_end;
   u16 key_color;
   u8  pitch;
} gss_2dpg_line_t;

typedef struct {
   u16 x_clip;
   u16 y_clip;
   u16 clip_width;
   u16 clip_height;
} clip_param_t;

typedef struct {
   u16 width;
   u16 height;
   u32 data_addr;
} pattern_param_t;

typedef enum {
   NONE_OP=0,
   S_ROP_AND,
   S_ROP_OR,
   S_ROP_XOR,
   S_ROP_NOT_SRC,
   S_ROP_NOT_DST,
   S_ROP_NAND,
   S_ROP_NOR,
   S_ROP_NXOR,
   S_ROP_NOT_AND,
   S_ROP_AND_NOT,
   S_ROP_OR_NOT,
   S_ROP_NOT_OR,
   DC_ROP_AND,
   DC_ROP_OR,
   DC_ROP_XOR
} rop_t;

s32 gss_2dgp_DrawPicture16bpp(gss_2dpg_t *param);
s32 gss_2dgp_DrawClipPicture16bpp(gss_2dpg_t *param,clip_param_t clip_param);
s32 gss_2dgp_DrawPicture8bpp(gss_2dpg_t *param);
s32 gss_2dgp_DrawClipPicture8bpp(gss_2dpg_t *param,clip_param_t clip_param);
s32 gss_2dgp_GetArea(gss_2dpg_t *param);
s32 gss_2dgp_GetPoint(gss_2dpg_t *param);
s32 gss_2dgp_SetColorArea(gss_2dpg_t *param);
s32 gss_2dgp_CopyScreenpageBloc(gss_2dpg_t *param);
s32 gss_2dgp_FillPattern(gss_2dpg_t *param,pattern_param_t *pattern);
s32 gss_2dgp_DrawLine(gss_2dpg_line_t *param);

#endif // __GSS_2DGP_ITF_H__
