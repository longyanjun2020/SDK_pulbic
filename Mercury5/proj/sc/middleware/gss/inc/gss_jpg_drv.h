/**
 * \file gss_jpg_drv.h
 * \brief JPG low level driver prototypes for V2751
*/

#ifndef __GSS_JPG_DRV_H__
#define __GSS_JPG_DRV_H__

#include "vm_types.ht"
#include "gss_cisi_drv.h"

typedef enum   {
	YCRCB = 0, // YCbCr 4:2:2
	RGB565 = 2, // RGB 5:6:5
	RGB444 = 3, // RGB 4:4:4
	RGB332 = 4 // RGB 3:3:2
} GssPixelFormat_t;

typedef enum   {
	FROM_RAM = 0, // 
	FROM_R2B_BUFFER = 1 // 
} GssJpgR2BMode_t;


/**
 * \brief Shape of the MCU output by the decoder IP
 */
typedef enum   {
	_1_BLOCK_PER_COMPONENT = 0, // one block of each component in MCU ( YCrCb or YUV 4:4:4 or  RGB 8:8:8 format)
	_2_Y_FOR_1_C = 1, // 2 blocks of luminance and 1 block of each chrominance component (YUV or YCrCb 4:2:2)
	_4_Y_FOR_1_C_4_1_1 = 2, // 4 blocks of luminance and 1 block of each chrominance component (YUV or YCrCb 4:1:1)
	_4_Y_FOR_1_C_4_2_0= 3 // 4 blocks of luminance and 1 block of each chrominance component (YUV or YCrCb 4:2:0)
} GssMCUShape_t;


void gss_jpg_Init(void);
void gss_jpg_Start(void);
void gss_jpg_ConfigurationMode(bool enable);
void gss_jpg_Reset(void);
void gss_jpg_LowPowerMode(bool enableLowPower);
void gss_jpg_SetInputPict(u16 width, u16 height, u32 address);
void gss_jpg_SetOutputPictAddr(u32 address);
void gss_jpg_SetConfigParam(u32 start,  u32 size);
void gss_jpg_SetInputJpegParam(u32 start,  u32 size);
void gss_jpg_SetOutputJpegParam(u32 start,  u32 max_size);
u32 gss_jpg_GetJpegSize(void);
void gss_jpg_SetPixelFormat(GssPixelFormat_t format);
void gss_jpg_SetR2BMode(GssJpgR2BMode_t mode);
void gss_jpg_SetColorSpaceConversionParams(CisiCscCoefs_t  *params);
void gss_jpg_EnableColorSpaceConversion(bool enable);
void gss_jpg_SetMCUShape(GssMCUShape_t shape);
void gss_jpg_SetShrinkRatio(ShrinkRatio_t ratio);
void gss_jpg_OperationMode(bool encode, bool mjpeg);
void gss_jpg_SetClipSize(u16 width, u16 height);
void gss_jpg_SetClipPos(u16 x_clip, u16 y_clip);
void gss_jpg_EnableClipping(bool enable);
void gss_jpg_SetFlipAndRotate(FlipMode_t flip, RotationAngle_t rotation_angle);
void gss_jpg_SetIncrustMode(EncrustMode_t encrust_mode);


#endif // __GSS_JPG_DRV_H__

