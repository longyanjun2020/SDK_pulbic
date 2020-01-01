#ifndef __DRV_DIP__
#define __DRV_DIP__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "hal_dip_pub.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

/*=============================================================*/
// Macro
/*=============================================================*/

#define DRV_DIP_OPEN0() drv_dip_open(0)

/*=============================================================*/
// Public function
/*=============================================================*/

s32 drv_dip_init(void);
HDIP drv_dip_open(u8 dip_id);
s32 drv_dip_close(HDIP hDip);
s32 drv_dip_set_wh(HDIP hDip, u32 nSrcWidth, u32 nSrcHeight, u32 nDestWidth, u32 nDestHeight);
s32 drv_dip_set_line_offset(HDIP hDip, u32 nSrcLineOffset, u32 nDestLineOffset);
s32 drv_dip_set_scale_wh(HDIP hDip, u32 nSrcWidth, u32 nSrcHeight, u32 nDestWidth, u32 nDestHeight);
s32 drv_dip_set_scale_en(HDIP hDip, BOOL bHScaleEn, BOOL bVScaleEn);
s32 drv_dip_set_color_format(HDIP hDip, DIPCOLORFORMAT_e eSrcFormat, DIPCOLORFORMAT_e eDestFormat);
s32 drv_dip_set_base_addr(HDIP hDip, u32 nSrcAddrY, u32 nSrcAddrC, u32 nDestAddrY, u32 nDestAddrC);
s32 drv_dip_set_ring_buffer_num(HDIP hDip, u32 nSrcBufNum, u32 nDestBufNum);
s32 drv_dip_set_frame_offset(HDIP hDip, u32 nSrcFrameOffsetY, u32 nSrcFrameOffsetC, u32 nDestFrameOffsetY, u32 nDestFrameOffsetC);
s32 drv_dip_set_rotate_degree(HDIP hDip, DIPROTATE_e eRotate);
s32 drv_dip_set_osdb_en(HDIP hDip, BOOL bEn);
s32 drv_dip_set_h_mirror_en(HDIP hDip, BOOL bEn);
s32 drv_dip_set_v_flip_en(HDIP hDip, BOOL bEn);
s32 drv_dip_set_src_yc_swap(HDIP hDip, BOOL bEn);
s32 drv_dip_set_src_uv_swap(HDIP hDip, BOOL bEn);
s32 drv_dip_set_dest_yc_swap(HDIP hDip, BOOL bEn);
s32 drv_dip_set_dest_uv_swap(HDIP hDip, BOOL bEn);
s32 drv_dip_get_src_rect(HDIP hDip, u32 *nSrcWidth, u32 *nSrcHeight, u32 *nSrcLineOffset);
s32 drv_dip_get_dest_rect(HDIP hDip, u32 *nDestWidth, u32 *nDestHeight, u32 *nDestLineOffset);
s32 drv_dip_get_scale_in_rect(HDIP hDip, u32 *nScaleInWidth, u32 *nScaleInHeight);
s32 drv_dip_get_scale_out_rect(HDIP hDip, u32 *nScaleOutWidth, u32 *nScaleOutHeight);
s32 drv_dip_get_src_color_format(HDIP hDip, DIPCOLORFORMAT_e *eSrcColorFormat);
s32 drv_dip_get_dest_color_format(HDIP hDip, DIPCOLORFORMAT_e *eDestColorFormat);
s32 drv_dip_get_rotate_enable(HDIP hDip, BOOL *bEnable);
s32 drv_dip_get_rotate_degree(HDIP hDip, DIPROTATE_e *eRotateDegree);
s32 drv_dip_get_osdb_enable(HDIP hDip, BOOL *bEnable);
s32 drv_dip_get_scale_enable(HDIP hDip, BOOL *bHScaleEn, BOOL *bVScaleEn);
s32 drv_dip_get_src_base_addr(HDIP hDip, u32 *nSrcBaseAddrY, u32 *nSrcBaseAddrC);
s32 drv_dip_get_dest_base_addr(HDIP hDip, u32 *nDestBaseAddrY, u32 *nDestBaseAddrC);
s32 drv_dip_trigger(HDIP hDip, void (*pfnCallback)(void*, void*), void* pParam);

#endif //__DRV_DIP__
