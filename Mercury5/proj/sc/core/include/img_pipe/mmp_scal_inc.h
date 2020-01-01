//==============================================================================
//
//  File        : mmp_scal_inc.h
//  Description : INCLUDE File for the Firmware Scaler Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_SCAL_INC_H_
#define _MMP_SCAL_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_SCAL_NM_VALUE			(0x0FFF) // Ref:SCAL_NM_MAX
#define MAX_BAYERSCAL_NM_VALUE		(0x03FF) // Ref:BAYER_SCAL_NM_MAX
#define MAX_WINSCAL_NM_VALUE		(0x007F) // Ref:DSPY_SCAL_NM_MAX

#define SCALER_MODE_BILINEAR		(0)
#define SCALER_MODE_BICUBIC			(1)

#define SCALER_DIR_X                (0)
#define SCALER_DIR_Y                (1)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_SCAL_PIPEID
{
    MMP_SCAL_PIPE_0 = 0,
    MMP_SCAL_PIPE_1,
    MMP_SCAL_PIPE_2,
    MMP_SCAL_PIPE_3,
    MMP_SCAL_PIPE_4,
    MMP_SCAL_PIPE_NUM,
    MMP_SCAL_PIPE_UNDEF
} MMP_SCAL_PIPEID;

typedef enum _MMP_SCAL_USER_DEF_TYPE
{
    MMP_SCAL_USER_DEF_TYPE_IN_OUT,
    MMP_SCAL_USER_DEF_TYPE_OUT
} MMP_SCAL_USER_DEF_TYPE;

typedef enum _MMP_SCAL_SOURCE 
{
    MMP_SCAL_SOURCE_ISP = 0,
    MMP_SCAL_SOURCE_JPG,
    MMP_SCAL_SOURCE_GRA,
    MMP_SCAL_SOURCE_LDC,
    MMP_SCAL_SOURCE_MAX
} MMP_SCAL_SOURCE;

typedef enum _MMP_SCAL_COLORMODE
{
    MMP_SCAL_COLOR_RGB565 = 0,
    MMP_SCAL_COLOR_RGB888,
    MMP_SCAL_COLOR_YUV444,
    MMP_SCAL_COLOR_YUV422
} MMP_SCAL_COLORMODE;

typedef enum _MMP_SCAL_COLRMTX_MODE 
{
	MMP_SCAL_COLRMTX_YUV_FULLRANGE = 0,     /* FULLRANGE means YUV (0~255) */
    MMP_SCAL_COLRMTX_FULLRANGE_TO_BT601,    /* BT601 means Y (16~235) UV (16~240) */
    MMP_SCAL_COLRMTX_FULLRANGE_TO_RGB,      /* RGB means RGB (0~255) */
    MMP_SCAL_COLRMTX_BT601_TO_FULLRANGE,
    MMP_SCAL_COLRMTX_MAX
} MMP_SCAL_COLRMTX_MODE;

typedef enum _MMP_SCAL_FIT_MODE
{
    MMP_SCAL_FITMODE_OUT = 0,
    MMP_SCAL_FITMODE_IN,
    MMP_SCAL_FITMODE_OPTIMAL,
    MMP_SCAL_FITMODE_NUM
} MMP_SCAL_FIT_MODE;

typedef enum _MMP_SCAL_SCALER_TYPE
{
    MMP_SCAL_TYPE_SCALER = 0,
    MMP_SCAL_TYPE_WINSCALER,
    MMP_SCAL_TYPE_NUM
} MMP_SCAL_SCALER_TYPE;

typedef enum _MMP_SCAL_GRAB_STAGE 
{
	MMP_SCAL_GRAB_STAGE_LPF = 1,
	MMP_SCAL_GRAB_STAGE_SCA,
	MMP_SCAL_GRAB_STAGE_OUT
} MMP_SCAL_GRAB_STAGE;

typedef enum _MMP_SCAL_EVENT 
{
    MMP_SCAL_EVENT_FRM_ST 	= 0,
    MMP_SCAL_EVENT_FRM_END,
    MMP_SCAL_EVENT_INPUT_END,
    MMP_SCAL_EVENT_MAX
} MMP_SCAL_EVENT;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_SCAL_FIT_RANGE {
    MMP_SCAL_FIT_MODE  		fitmode;
    MMP_SCAL_SCALER_TYPE	scalerType;
    MMP_BOOL	bUseLpfGrab;		// For PTZ operation
    MMP_BOOL	ubChoseLit;         // RetryCondition->[0:1]/[TargetRes<NewRes:TargetRes>NewRes]
    
    MMP_ULONG 	ulFitResol;
    MMP_ULONG  	ulInWidth;
    MMP_ULONG 	ulInHeight;
    MMP_ULONG  	ulOutWidth;
    MMP_ULONG 	ulOutHeight;

    MMP_ULONG 	ulInGrabX;
    MMP_ULONG	ulInGrabY;
    MMP_ULONG 	ulInGrabW;
    MMP_ULONG	ulInGrabH;
    
    MMP_ULONG 	ulDummyInPixelX;
    MMP_ULONG	ulDummyInPixelY;
    MMP_ULONG	ulDummyOutPixelX;	// Used in bayer scaler
    MMP_ULONG	ulDummyOutPixelY;	// Used in bayer scaler
   
    MMP_ULONG	ulInputRatioH;
    MMP_ULONG	ulInputRatioV;
    MMP_ULONG	ulOutputRatioH;
    MMP_ULONG	ulOutputRatioV;
} MMP_SCAL_FIT_RANGE;

typedef struct _MMP_SCAL_GRAB_CTRL {
    MMP_ULONG	ulOutStX;
    MMP_ULONG 	ulOutStY;
    MMP_ULONG	ulOutEdX;
    MMP_ULONG 	ulOutEdY;

    MMP_ULONG 	ulScaleN;
    MMP_ULONG 	ulScaleM;
    MMP_ULONG	ulScaleXN;
    MMP_ULONG 	ulScaleXM;
    MMP_ULONG  	ulScaleYN;
    MMP_ULONG 	ulScaleYM; 
} MMP_SCAL_GRAB_CTRL;

typedef void ScalCallBackFunc(void *argu);

#endif // _MMP_SCAL_INC_H_
