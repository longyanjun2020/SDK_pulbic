//------------------------------------------------------------------------------
//
//  File        : component_jpe.h
//  Description : Header file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_JPE_H_
#define _COMPONENT_JPE_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_JPE_COMP_NUM                JPE_COMP_USAGE_NUM

#define MAX_JPE_COMP_OUTBUF_NUM         (16)

#define JPE_COMP_W_ALIGN_BASE_YUV422    (16)
#define JPE_COMP_H_ALIGN_BASE_YUV422    (8)
#define JPE_COMP_W_ALIGN_BASE_NV12      (16)
#define JPE_COMP_H_ALIGN_BASE_NV12      (16)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum // Ref with MMP_JPEG_ENC_TYPE
{
    JPE_COMP_PRM_MJPEG = 0,
    JPE_COMP_SCD_MJPEG,
    JPE_COMP_TRD_MJPEG,
    JPE_COMP_PRM_PRIMARY,
    JPE_COMP_SCD_PRIMARY,
    JPE_COMP_TRD_PRIMARY,
    JPE_COMP_PRM_THUMB,
    JPE_COMP_SCD_THUMB,
    JPE_COMP_TRD_THUMB,
    JPE_COMP_PRM_VR_THUMB,
    JPE_COMP_SCD_VR_THUMB,
    JPE_COMP_TRD_VR_THUMB,
    JPE_COMP_USAGE_NUM
} JPE_COMP_USAGE;

typedef enum
{
    JPE_COMP_UI_MODE_VR = 0,
    JPE_COMP_UI_MODE_DSC,
    JPE_COMP_UI_MODE_BROWSER,
    JPE_COMP_UI_MODE_NUM
} JPE_COMP_UI_MODE;

typedef enum
{
    JPE_COMP_SINGLE_SHOT = 0,
    JPE_COMP_CONTINUOUS_SHOT,
    JPE_COMP_MJPEG_MODE,
    JPE_COMP_SHOT_MODE_NUM
} JPE_COMP_SHOT_MODE;

typedef enum // Sync with MMP_JPEG_ENC_RAW_FMT
{
    JPE_COMP_FMT_YUYV = 0x0,
    JPE_COMP_FMT_YVYU = 0x1,
    JPE_COMP_FMT_NV12 = 0x3,
    JPE_COMP_FMT_NV21 = 0x4,
} JPE_COMP_COLOR_FMT;

typedef enum
{
    JPE_COMP_PARAM_RES = 0,
    JPE_COMP_PARAM_UI_MODE,
    JPE_COMP_PARAM_FMT,
    JPE_COMP_PARAM_SHOT_MODE,
    JPE_COMP_PARAM_SHOT_NUM,
    JPE_COMP_PARAM_INIT_QF,
    JPE_COMP_PARAM_BUF_COUNT,
    JPE_COMP_PARAM_BUF_SIZE,
    JPE_COMP_PARAM_BUF_RING_THD,
    JPE_COMP_PARAM_MAX
} JPE_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _JPE_COMP_RESOL
{
    MMP_ULONG       ulEncW;
    MMP_ULONG       ulEncH;
    MMP_ULONG       ulEncBufW;
    MMP_ULONG       ulEncBufH;
} JPE_COMP_RESOL;

typedef struct _MMP_COMPONENT_HANDLER_JPE
{
    MMP_UBYTE       ubUseType;
    MMP_UBYTE       ubUiMode;
    MMP_USHORT      usInstID;
    MMP_UBYTE       ubRawFormat;
    MMP_UBYTE       ubShotMode;
    MMP_ULONG       ulShotNum;
    MMP_USHORT      usInitQFactor;
    JPE_COMP_RESOL  stEncWH;
} MMP_COMPONENT_HANDLER_JPE;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_JPE[];

extern MMP_COMPONENT_HANDLER_JPE Component_JPE_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_JPE_Memory[];

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR Component_JPE_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPE_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_JPE_H_

