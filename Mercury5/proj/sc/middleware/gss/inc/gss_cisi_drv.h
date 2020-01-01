/**
 * \file gss_cisi_drv.h
 * \brief CISI low level driver for V2751
*/

#ifndef __GSS_CISI_DRV_H__
#define __GSS_CISI_DRV_H__

#include "vm_types.ht"

typedef struct CISI_INTERFACE {
	u32 clip1_valid : 1;
	u32 pixel_valid : 1;
	u32 xavcode_use : 1;
	u32 clip2_valid : 1;
	u32 v_sync_pol : 1;
	u32 h_sync_pol : 1;
	u32 v_clk_pol : 1;
	u32 in_color_space_sel : 3;
	u32 rgb_order : 4;
	u32 rgb_pos : 2;
	u32 yuv_order : 2;
	u32 clock_divider;
} CisiInterface_s;

typedef enum {
	ONE_FRAME_EVERY_FRAME = 0,
	ONE_FRAME_EVERY_2_FRAMES,
	ONE_FRAME_EVERY_3_FRAMES,
	ONE_FRAME_EVERY_4_FRAMES,
	ONE_FRAME_EVERY_5_FRAMES,
	ONE_FRAME_EVERY_6_FRAMES
} FrameSample_t;

typedef enum {
	STILL_PICTURE_MODE = 0,
	PREVIEW_MODE = 1,
	JPEG_MODE = 2,
	MOTION_JPEG_MODE = 3
} CaptMode_t;

typedef enum {
	SUB_SAMPLING = 0,
	LINE_AVERAGING = 1
} ShrinkAlgo_t;

typedef enum {
	DIVIDE_BY_1 = 0,
	DIVIDE_BY_2 = 1,
	DIVIDE_BY_4 = 3,
	DIVIDE_BY_8 = 7
} ShrinkRatio_t;

typedef enum {
	INPUT_FROM_CIS = 0,
	INPUT_FROM_GBSI = 1
} CisiFlow_t;

typedef enum {
	NO_ENCRUST = 0, //the data flow is written to a separate display buffer, starting at CISIWRADDRPTRREG
	ENCRUST_IN_MAIN = 1 //the data is encrusted into the main display buffer. In this case, CISIWRADDRPTRREG must store the start address inside the main display, where the encrusted image starts.
} EncrustMode_t;

typedef enum {
	NO_FLIP = 0, //No flip applied to image
	VERTICAL_FLIP = 1 // input image is flipped along a vertical rotation axis, while
} FlipMode_t;

typedef enum {
	NO_ROTATION = 0, //no rotation (captured image stored "as is")
	ROTATION_90 = 1, //input image is rotated by +90?while stored in RAM
	ROTATION_270 = 2, //input image is rotated by -90?(= +270? while stored in RAM
	ROTATION_180 = 3 // input image is rotated by +180?while stored in RAM	 
} RotationAngle_t;

typedef enum {
	YUV_FORMAT = 0, // YUV         output packing
	YCRCB_FORMAT = 1, // YCbCr      output packing
	RGB_565_FORMAT = 2, // RGB5:6:5 output packing
	RGB_332_FORMAT = 3 // RGB3:3:2 output packing
} OutPackFormat_t;

typedef struct  CISIBUSITF_T {
	EncrustMode_t encrust_mode;
	FlipMode_t flip_mode;
	RotationAngle_t rotation_angle;
	OutPackFormat_t out_pack_format_db;
	OutPackFormat_t out_pack_format_jpg;
} CisiBusItf_t;

/**
 * applies also to YCrCb order if  INCOLSPCESEL == ?01?
 */
typedef enum {
	CISI_ORDER_YUYVYUYV =	0,
	CISI_ORDER_YVYUYVYU,
	CISI_ORDER_UYVYUYVY,   
	CISI_ORDER_VYUYVYUY,
} CisiYuvOrder_t;

 
#define GSS_CISICSCDISCOEF1_CSC_DIS_COE_12_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF1_CSC_DIS_COE_12_OFFSET			16	
#define GSS_CISICSCDISCOEF1_CSC_DIS_COE_11_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF1_CSC_DIS_COE_11_OFFSET			0	
#define GSS_CISICSCDISCOEF2_CSC_DIS_COE_14_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF2_CSC_DIS_COE_14_OFFSET			16	
#define GSS_CISICSCDISCOEF2_CSC_DIS_COE_13_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF2_CSC_DIS_COE_13_OFFSET			0	
#define GSS_CISICSCDISCOEF3_CSC_DIS_COE_22_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF3_CSC_DIS_COE_22_OFFSET			16
#define GSS_CISICSCDISCOEF3_CSC_DIS_COE_21_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF3_CSC_DIS_COE_21_OFFSET			0	
#define GSS_CISICSCDISCOEF4_CSC_DIS_COE_24_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF4_CSC_DIS_COE_24_OFFSET			16
#define GSS_CISICSCDISCOEF4_CSC_DIS_COE_23_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF4_CSC_DIS_COE_23_OFFSET			0	
#define GSS_CISICSCDISCOEF5_CSC_DIS_COE_32_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF5_CSC_DIS_COE_32_OFFSET			16
#define GSS_CISICSCDISCOEF5_CSC_DIS_COE_31_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF5_CSC_DIS_COE_31_OFFSET			0	
#define GSS_CISICSCDISCOEF6_CSC_DIS_COE_34_MSK				(0x3FF<<16)	
#define GSS_CISICSCDISCOEF6_CSC_DIS_COE_34_OFFSET			16	
#define GSS_CISICSCDISCOEF6_CSC_DIS_COE_33_MSK				(0x3FF<<0)	
#define GSS_CISICSCDISCOEF6_CSC_DIS_COE_33_OFFSET			0	

typedef struct  CISICSCCOEFS_T {
	u16 coef11;
	u16 coef12;
	u16 coef13;
	u16 coef14;
	u16 coef21;
	u16 coef22;
	u16 coef23;
	u16 coef24;
	u16 coef31;
	u16 coef32;
	u16 coef33;
	u16 coef34;
} CisiCscCoefs_t;

void gss_cisi_Init(CisiInterface_s *cisi_itf);
void gss_cisi_set_yuv_order(CisiYuvOrder_t yuv_order);
CisiYuvOrder_t gss_cisi_get_yuv_order(void);
void gss_cisi_SetInputWindowPos(u16 x_win, u16 y_win);
void gss_cisi_SetInputWindowSize(u16 width, u16 height);
void gss_cisi_SetInputImgSize(u16 width, u16 height);
void gss_cisi_SetTriggerCtrl(FrameSample_t frame_sample, CaptMode_t capture_mode);
void gss_cisi_SetDownSizeCtrl(ShrinkAlgo_t algo, ShrinkRatio_t ratio);
void gss_cisi_SetClipWindowPos(u16 x_win, u16 y_win);
void gss_cisi_SetClipWindowSize(u16 height, u16 width);
void gss_cisi_EnableColorSpaceConversion(bool enable);
void gss_cisi_EnableJpegColorSpaceConversion(bool enable);
void gss_cisi_SetFlowCtrl(CisiFlow_t flow);
void gss_cisi_SetBusItfCtrl(CisiBusItf_t *busItf);
void gss_cisi_SetClk(u8 ratio);
void gss_cisi_SetWriteAddress(u32 address);
void gss_cisi_SetReadAddress(u32 address);
void gss_cisi_SetColorSpaceConversionParams(CisiCscCoefs_t*params);
void gss_cisi_StartCapture(void);
void gss_cisi_StopCapture(void);
bool gss_cisi_IsCaptureInProgress(void);

#endif // __GSS_CISI_DRV_H__

