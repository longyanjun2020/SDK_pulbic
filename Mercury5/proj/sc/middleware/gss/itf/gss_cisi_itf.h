/**
 * \file gss_cisi_itf.h
 * \brief Camera Interface high level driver	for V2751
*/

#ifndef __GSS_CISI_ITF_H__
#define __GSS_CISI_ITF_H__

#include "gss_cisi_drv.h"

#define CISI_YUV_422 	0x0 // CISI receives YUV in 4 :2 :2 format
#define CISI_YCRCB_422 	0x1// CISI receives YCbCr in 4 :2 :2 format
#define CISI_RGB_565 	0x2 // CISI receives RGB in 5 :6 :5 format
#define CISI_RGB_444 	0x3 // CISI receives RGB in 4:4:4 format
#define CISI_RGB_332	0x4 // CISI receives RGB in 3:3:2 format

#define CISI_ORDER_RGB   	0x0 // applied to all formats, from camera or display ram 
#define CISI_ORDER_BGR   	0x1 // applied to all formats, from camera or display ram     
#define CISI_ORDER_RBG   	0x2// only applied to RGB 3:3:2 and 4:4:4
#define CISI_ORDER_GBR   	0x3 // only applied to RGB 3:3:2 and 4:4:4
#define CISI_ORDER_BRG   	0x4 // only applied to RGB 3:3:2 and 4:4:4
#define CISI_ORDER_GRB   	0x5 // only applied to RGB 3:3:2 and 4:4:4
#define CISI_ORDER_RG2G1B   0x6	// (only RGB 5:6:5 from camera)
#define CISI_ORDER_BG2G1G   0x7  // (only RGB 5:6:5 from camera)
#define CISI_ORDER_G1RBG2   0x8  // (only RGB 5:6:5 from camera)
#define CISI_ORDER_G1BRG2   0x9  // (only RGB 5:6:5 from camera)
#define CISI_ORDER_G2RBG1   0xA  // (only RGB 5:6:5 from camera)
#define CISI_ORDER_G2BRG1   0xB  // (only RGB 5:6:5 from camera)

#define CISI_RGB_POS_C1C2C3X   	0      //(only RGB 4:4:4 from camera)
#define CISI_RGB_POS_C1C2XC3	1
#define CISI_RGB_POS_C1XC2C3	2
#define CISI_RGB_POS_XC1C2C3	3

#define CISI_ALREADY_OPEN -1
#define CISI_WRONG_PARAM -2
#define CISI_OK 				1


typedef struct CISIWIN_T {
	u16 x_pos;
	u16 y_pos;
	u16 height;
	u16 width;
} CisiWindow_t;

typedef struct CISIINPUTPARAM_T {
	u32 *dst_addr;
	CisiWindow_t input_window;
	CisiWindow_t clip_window;
	FrameSample_t frame_sample; 
	CaptMode_t capture_mode;
	ShrinkAlgo_t algo;
	ShrinkRatio_t ratio;
	CisiFlow_t flow;
	CisiBusItf_t busItf;
	CisiCscCoefs_t*csc;
} CisiInputParam_t;

s32 gss_cisi_Initialize(CisiInterface_s *cisi_itf);
s32 gss_cisi_Open(CisiInputParam_t *param);
s32 gss_cisi_Start(s32 session_id);
s32 gss_cisi_Stop(s32 session_id);
s32 gss_cisi_IsFinished(s32 session_id);
s32 gss_cisi_Close(s32 session_id);

#endif // __GSS_CISI_ITF_H__
