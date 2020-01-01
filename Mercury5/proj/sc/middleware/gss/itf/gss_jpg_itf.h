/**
 * \file gss_jpg_itf.h
 * \brief jpg hig level driver	for V2751
*/

#ifndef __GSS_JPG_ITF_H__
#define __GSS_JPG_ITF_H__

#include "vm_types.ht"
#include "gss_cisi_drv.h"

typedef struct GSSJPGDECPICTURE_T {
	u32 *in_buffer_ptr;
	u32 in_buffer_size;
	u8 *out_buffer_ptr;
	u16 out_pict_width;
	u16 out_pict_height;
	bool clipping;
    u16 clip_x;
	u16 clip_y;
	u16 clip_width;
	u16 clip_height;
	GssMCUShape_t MCUShape;
	EncrustMode_t encrust_mode;
	FlipMode_t flip_mode;
	RotationAngle_t rotation_angle;
	ShrinkRatio_t shrink_ratio;
	GssPixelFormat_t pixel_format;
	CisiCscCoefs_t *csc_coefs;
} GssJpgDecPicture_t;

typedef struct GSSJPGENCPICTURE_T {
	u32 *in_buffer_ptr;
	u32 in_buffer_width;
	u32 in_buffer_height;
	u32 *out_buffer_ptr;
	u32 out_buffer_max_size;
	GssPixelFormat_t pixel_format;
	GssJpgR2BMode_t R2B_mode;
} GssJpgEncPicture_t;

#define JPG_INVALID_PARAM 		-1
#define JPG_TIMEOUT 			-2
#define JPG_SIZE_ERROR 			-3
#define JPG_CFG_ERROR 			-4
#define JPG_MISDATA_ERROR 		-5
#define JPG_OK 					1

void gss_jpg_Initialize(void);
s32 gss_jpg_DecodeJpeg(GssJpgDecPicture_t *pict);
s32 gss_jpg_DecodeMJpeg(GssJpgDecPicture_t *pict);
s32 gss_jpg_OpenEncodeJpeg(GssJpgEncPicture_t *pict);
s32 gss_jpg_StartEncodeJpeg(u32 *final_size);
s32 gss_jpg_EncodeMJpeg(GssJpgEncPicture_t *pict);
s32 gss_jpg_Configure(u32 configstartadd, u32 configfilesize);

#endif // __GSS_JPG_ITF_H__
