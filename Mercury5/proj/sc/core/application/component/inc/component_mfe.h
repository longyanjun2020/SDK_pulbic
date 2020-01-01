//------------------------------------------------------------------------------
//
//  File        : component_mfe.h
//  Description : Header file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_MFE_H_
#define _COMPONENT_MFE_H_

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

#define MAX_MFE_COMP_NUM    MFE_COMP_USAGE_NUM

 // For input buffer alignment
#define MFE_COMP_W_ALIGN_BASE_YUV422    (16)
#define MFE_COMP_H_ALIGN_BASE_YUV422    (16)
#define MFE_COMP_W_ALIGN_BASE_NV12      (32)
#define MFE_COMP_H_ALIGN_BASE_NV12      (16)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    MFE_COMP_PRM_RECD = 0,
    MFE_COMP_SCD_RECD,
    MFE_COMP_TRD_RECD,
    MFE_COMP_UVC_RECD,
    MFE_COMP_PRM_STREAM,
    MFE_COMP_SCD_STREAM,
    MFE_COMP_USAGE_NUM
} MFE_COMP_USAGE;

typedef enum // Sync with VIDENC_PROFILE
{
    MFE_COMP_PROFILE_NONE = 0,
    MFE_COMP_PROFILE_BASELINE,
    MFE_COMP_PROFILE_MAIN,
    MFE_COMP_PROFILE_HIGH
} MFE_COMP_PROFILE;

typedef enum // Sync with VIDENC_PIXFMT
{
    MFE_COMP_PIXFMT_NV12 = 0,
    MFE_COMP_PIXFMT_NV21,
    MFE_COMP_PIXFMT_YUYV,
    MFE_COMP_PIXFMT_YVYU,
    MFE_COMP_PIXFMT_NUM
} MFE_COMP_PIXFMT;

typedef enum // Sync with VIDENC_STREAMTYPE
{
    MFE_COMP_STREAMTYPE_PRM_RECD = 0,
    MFE_COMP_STREAMTYPE_PRM_EMERG,
    MFE_COMP_STREAMTYPE_UVC_RECD,
    MFE_COMP_STREAMTYPE_UVC_EMERG,
    MFE_COMP_STREAMTYPE_SCD_RECD,
    MFE_COMP_STREAMTYPE_SCD_EMERG,
    MFE_COMP_STREAMTYPE_TRD_RECD,
    MFE_COMP_STREAMTYPE_TRD_EMERG,
    MFE_COMP_STREAMTYPE_WIFI_PRM,
    MFE_COMP_STREAMTYPE_WIFI_SCD,
    MFE_COMP_STREAMTYPE_REFIXTAIL,
    MFE_COMP_STREAMTYPE_MAX
} MFE_COMP_STREAMTYPE;

typedef enum
{
    MFE_COMP_PARAM_ENC_ID = 0,
    MFE_COMP_PARAM_STRM_TYPE,
    MFE_COMP_PARAM_BITRATE,
    MFE_COMP_PARAM_P_FRM_CNT,
    MFE_COMP_PARAM_PROFILE,
    MFE_COMP_PARAM_PIX_FMT,
    MFE_COMP_PARAM_RESOLUTION,
    MFE_COMP_PARAM_SNR_FPS,
    MFE_COMP_PARAM_ENC_FPS,
    MFE_COMP_PARAM_MGR_FPS,
    MFE_COMP_PARAM_BUF_COUNT,
    MFE_COMP_PARAM_BUF_SIZE,
    MFE_COMP_PARAM_NEARRING_THD,
    MFE_COMP_PARAM_LINE_OFFSET,
    MFE_COMP_PARAM_MAX
} MFE_COMP_PARAM;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MFE_COMP_ENC_RESOL
{
    MMP_ULONG           ulEncW;
    MMP_ULONG           ulEncH;
    MMP_ULONG           ulEncBufW;
    MMP_ULONG           ulEncBufH;
} MFE_COMP_ENC_RESOL;

typedef struct _MFE_COMP_FPS
{
    MMP_ULONG           usTimeIncre;
    MMP_ULONG           usTimeResol;
} MFE_COMP_FPS;

typedef struct _MFE_COMP_QP_CTRL
{
    MMP_UBYTE           ubIFrameLowB;
    MMP_UBYTE           ubIFrameHighB;
    MMP_UBYTE           ubPFrameLowB;
    MMP_UBYTE           ubPFrameHighB;
    MMP_UBYTE           ubIMBLowB;
    MMP_UBYTE           ubIMBHighB;
    MMP_UBYTE           ubPMBLowB;
    MMP_UBYTE           ubPMBHighB;
} MFE_COMP_QP_CTRL;

typedef struct _MMP_COMPONENT_HANDLER_MFE
{
    MMP_UBYTE               ubUseType;
    MMP_UBYTE               ubEncID;
    MMP_USHORT              usStreamType;
    MMP_ULONG               ulBitrate;
    MMP_ULONG               ulPframeNum;
    MFE_COMP_PROFILE        eProfile;
    MFE_COMP_PIXFMT         ePixFmt;
    MFE_COMP_ENC_RESOL      stEncWH;
    MFE_COMP_FPS            stSnrFps;
    MFE_COMP_FPS            stEncFps;
    MFE_COMP_FPS            stMgrFps;
    MMP_BOOL                bEncodeEn;
    MMP_USHORT              usLineOffset;
    MFE_COMP_QP_CTRL        stQpCtl;
} MMP_COMPONENT_HANDLER_MFE;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_MFE[];

extern MMP_COMPONENT_MEMORY_INFO Component_MFE_Memory[];
extern MMP_COMPONENT_HANDLER_MFE Component_MFE_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_MFE_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MFE_GetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_MFE_H_

