//------------------------------------------------------------------------------
//
//  File        : component_dip.h
//  Description : Header file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_DIP_H_
#define _COMPONENT_DIP_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO
//
//==============================================================================

#define COMPONENT_DIP_S_MAX_NUM         (16) // Ref:DIP_S_COMP_VR_USAGE_NUM
#define COMPONENT_DIP_R_MAX_NUM         (3) // Ref:DIP_R_COMP_VR_USAGE_NUM
#define COMPONENT_DIP_OSDB_MAX_NUM      (1)
#define COMPONENT_DIP_MOVE_MAX_NUM      (1)
#define COMPONENT_DIP_CC_MAX_NUM        (1)

#define DIP_R_COMP_ALIGN_BASE           (32)
#define DIP_R_COMP_ALIGN_CHECK(W)       ((W) & (DIP_R_COMP_ALIGN_BASE - 1))

#define DIP_S_COMP_WIDTH_ALIGN_BASE     (16)
#define DIP_S_COMP_WIDTH_ALIGN_CHECK(W) ((W) & (DIP_S_COMP_WIDTH_ALIGN_BASE - 1))

#define DIP_S_COMP_WIDTH_MAX_RATIO      (6000)
#define DIP_S_COMP_HEIGHT_MAX_RATIO     (4000)

#define DIP_COMP_BUF_SIZE_YUV420(W, H)  (W) * (H) * 3 / 2
#define DIP_COMP_BUF_SIZE_YUV422(W, H)  (W) * (H) * 2

#if (SUPPORT_MFE_SHAREBUFFER)
#define DIP_COMP_RECORD_BUF_COUNT      (3)
#define DIP_COMP_PREVW_BUF_COUNT       (2)
#else
#define DIP_COMP_RECORD_BUF_COUNT      (2)
#define DIP_COMP_PREVW_BUF_COUNT       (2)
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    DIP_COMP_COLOR_FMT_YUV420_UV = 0,
    DIP_COMP_COLOR_FMT_YUV420_VU,
    DIP_COMP_COLOR_FMT_YUV420_T16X32_UV,
    DIP_COMP_COLOR_FMT_YUV420_T16X32_VU,
    DIP_COMP_COLOR_FMT_YUV422_YUYV,
    DIP_COMP_COLOR_FMT_YUV422_YVYU,
    DIP_COMP_COLOR_FMT_YUV422_UYVY,
    DIP_COMP_COLOR_FMT_YUV422_VYUY,
    DIP_COMP_COLOR_FMT_UNSUPPORT
} DIP_COMP_COLOR_FMT;

typedef enum
{
    DIP_COMP_TYPE_ID_ROT = 0,
    DIP_COMP_TYPE_ID_SCL,
    DIP_COMP_TYPE_ID_OSDB,
    DIP_COMP_TYPE_ID_CC,
    DIP_COMP_TYPE_ID_MOVE,
    DIP_COMP_TYPE_ID_NUM
} DIP_COMP_TYPE_ID;

typedef enum
{
    DIP_COMP_MIRROR_DIS = 0,
    DIP_COMP_MIRROR_EN
} DIP_COMP_MIRROR_TYPE;

typedef enum
{
    DIP_COMP_ROTATE_0 = 0,
    DIP_COMP_ROTATE_90,
    DIP_COMP_ROTATE_180,
    DIP_COMP_ROTATE_270,
    DIP_COMP_ROTATE_UNSUPPORT
} DIP_R_COMP_ROT_DEG;

typedef enum
{
    DIP_COMP_PARAM_SCL_IN_RES = 0,
    DIP_COMP_PARAM_SCL_CROP_RES,
    DIP_COMP_PARAM_SCL_OUT_RES,
    DIP_COMP_PARAM_SCL_IN_FMT,
    DIP_COMP_PARAM_SCL_OUT_FMT,
    DIP_COMP_PARAM_SCL_BUF_COUNT,
    DIP_COMP_PARAM_SCL_BUF_SIZE,
    DIP_COMP_PARAM_SCL_RBUF_ADDR,
    DIP_COMP_PARAM_SCL_WBUF_ADDR,
    DIP_COMP_PARAM_SCL_OSDB_EN,
    DIP_COMP_PARAM_SCL_MIRROR_EN,
    DIP_COMP_PARAM_SCL_FLIP_EN,
    DIP_COMP_PARAM_SCL_BYPASS,
    DIP_COMP_PARAM_SCL_LINE_BIAS,
    DIP_COMP_PARAM_SCL_BUF_BIAS,
    DIP_COMP_PARAM_SCL_OUT_COMP_IDX,
    DIP_S_COMP_PARAM_MAX
} DIP_S_COMP_PARAM;

typedef enum
{
    DIP_COMP_PARAM_ROT_IN_RES = 0,
    DIP_COMP_PARAM_ROT_CROP_RES,
    DIP_COMP_PARAM_ROT_OUT_RES,
    DIP_COMP_PARAM_ROT_IN_FMT,
    DIP_COMP_PARAM_ROT_OUT_FMT,
    DIP_COMP_PARAM_ROT_BUF_COUNT,
    DIP_COMP_PARAM_ROT_BUF_SIZE,
    DIP_COMP_PARAM_ROT_RBUF_ADDR,
    DIP_COMP_PARAM_ROT_WBUF_ADDR,
    DIP_COMP_PARAM_ROT_BYPASS,
    DIP_R_COMP_PARAM_MAX
} DIP_R_COMP_PARAM;

typedef enum
{
    DIP_COMP_PARAM_OSDB_EN = 0,
    DIP_COMP_PARAM_OSDB_IN_RES,
    DIP_COMP_PARAM_OSDB_CROP_RES,
    DIP_COMP_PARAM_OSDB_OUT_RES,
    DIP_COMP_PARAM_OSDB_IN_FMT,
    DIP_COMP_PARAM_OSDB_OUT_FMT,
    DIP_COMP_PARAM_OSDB_BUF_COUNT,
    DIP_COMP_PARAM_OSDB_BUF_SIZE,
    DIP_COMP_PARAM_OSDB_RBUF_ADDR,
    DIP_COMP_PARAM_OSDB_WBUF_ADDR,
    DIP_COMP_PARAM_OSDB_BYPASS,
    DIP_OSDB_COMP_PARAM_MAX
} DIP_OSDB_COMP_PARAM;

typedef enum
{
    DIP_COMP_PARAM_CC_IN_RES = 0,
    DIP_COMP_PARAM_CC_CROP_RES,
    DIP_COMP_PARAM_CC_OUT_RES,
    DIP_COMP_PARAM_CC_IN_FMT,
    DIP_COMP_PARAM_CC_OUT_FMT,
    DIP_COMP_PARAM_CC_BUF_COUNT,
    DIP_COMP_PARAM_CC_BUF_SIZE,
    DIP_COMP_PARAM_CC_RBUF_ADDR,
    DIP_COMP_PARAM_CC_WBUF_ADDR,
    DIP_COMP_PARAM_CC_BYPASS,
    DIP_CC_COMP_PARAM_MAX
} DIP_CC_COMP_PARAM;

// VR mode component usage
typedef enum
{
    DIP_S_COMP_VR_FCAM_PREVIEW = 0,
    DIP_S_COMP_VR_RCAM_PREVIEW,
    DIP_S_COMP_VR_RCAM_RESCAL_PREV,
    DIP_S_COMP_VR_RCAM_RECD,
    DIP_S_COMP_VR_FCAM_ADAS,
    DIP_S_COMP_VR_FCAM_THUMB,
    DIP_S_COMP_VR_RCAM_THUMB,
    DIP_S_COMP_VR_FCAM_STREAMING,
    DIP_S_COMP_VR_RCAM_STREAMING,
    DIP_S_COMP_VR_SHARE_RECD,
    DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INA,  //DIP_S10
    DIP_S_COMP_VR_RCAM_PREVIEW_2IN1_INB,  //DIP_S11
    DIP_S_COMP_VR_RCAM_RECD_2IN1_INA,     //DIP_S12
    DIP_S_COMP_VR_RCAM_RECD_2IN1_INB,     //DIP_S13
    DIP_S_COMP_VR_FCAM_RECD_2IN2_SRC,     //DIP_S14
    DIP_S_COMP_VR_FCAM_STREAMING_2,       //DIP_S15 (for PCAM 2nd stream)
    DIP_S_COMP_VR_USAGE_NUM
} DIP_S_COMP_VR_USAGE;

typedef enum
{
    DIP_R_COMP_VR_FCAM_PREVIEW = 0,
    DIP_R_COMP_VR_RCAM_PREVIEW,
    DIP_R_COMP_VR_USAGE_NUM
} DIP_R_COMP_VR_USAGE;

typedef enum
{
    DIP_OSDB_COMP_VR_RCAM_RECD = 0,
    DIP_OSDB_COMP_VR_USAGE_NUM
} DIP_OSDB_COMP_VR_USAGE;

// DSC mode component usage
typedef enum
{
    DIP_S_COMP_DSC_FCAM_PREVIEW = 0,
    DIP_S_COMP_DSC_RCAM_PREVIEW,
    DIP_S_COMP_DSC_RCAM_RESCAL_PREV,
    DIP_S_COMP_DSC_RCAM_CAPTURE,
    DIP_S_COMP_DSC_THUMB_PRE_SCL,   // For Encode Thumbnail
    DIP_S_COMP_DSC_THUMB_MID_SCL,
    DIP_S_COMP_DSC_THUMB_POST_SCL,
    DIP_S_COMP_DSC_FCAM_STREAMING,
    DIP_S_COMP_DSC_RCAM_STREAMING,
    DIP_S_COMP_DSC_FCAM_CAPT_2IN2,          //DIP_S9
    DIP_S_COMP_DSC_RESERVE10,               //DIP_S10
    DIP_S_COMP_DSC_RESERVE11,               //DIP_S11
    DIP_S_COMP_DSC_RESERVE12,               //DIP_S12
    DIP_S_COMP_DSC_RESERVE13,               //DIP_S13
    DIP_S_COMP_DSC_FCAM_THUMB_2IN2,         //DIP_S14
    DIP_S_COMP_DSC_USAGE_NUM
} DIP_S_COMP_DSC_USAGE;

typedef enum
{
    DIP_R_COMP_DSC_FCAM_PREVIEW = 0,
    DIP_R_COMP_DSC_RCAM_PREVIEW,
    DIP_R_COMP_DSC_USAGE_NUM
} DIP_R_COMP_DSC_USAGE;

typedef enum
{
    DIP_OSDB_COMP_DSC_RCAM_CAPTURE = 0,
    DIP_OSDB_COMP_DSC_USAGE_NUM
} DIP_OSDB_COMP_DSC_USAGE;

// Movie playback component usage
typedef enum
{
    DIP_S_COMP_MOVIE_PB = 0,
    DIP_S_COMP_MOVIE_PB_RE_SCAL,
    DIP_S_COMP_MOVIE_PB_USAGE_NUM
} DIP_S_COMP_MOVIE_PB_USAGE;

typedef enum
{
    DIP_R_COMP_MOVIE_PB = 0,
    DIP_R_COMP_MOVIE_PB_USAGE_NUM
} DIP_R_COMP_MOVIE_PB_USAGE;

// JPEG playback component usage
typedef enum
{
    DIP_S_COMP_JPEG_PB = 0,
    DIP_S_COMP_JPEG_PB_RE_SCAL,
    DIP_S_COMP_JPEG_PB_USAGE_NUM
} DIP_S_COMP_JPEG_PB_USAGE;

typedef enum
{
    DIP_R_COMP_JPEG_PB = 0,
    DIP_R_COMP_JPEG_PB_USAGE_NUM
} DIP_R_COMP_JPEG_PB_USAGE;

// Browser thumbnail component usage
typedef enum
{
    DIP_S_COMP_THUMB_SCL_PRE = 0,
    DIP_S_COMP_THUMB_SCL,
    DIP_S_COMP_THUMB_SCL_POST,
    DIP_S_COMP_THUMB_SCL_USAGE_NUM
} DIP_S_COMP_THUMB_SCL_USAGE;

typedef enum
{
    DIP_R_COMP_THUMB_ROT = 0,
    DIP_R_COMP_THUMB_ROT_USAGE_NUM
} DIP_R_COMP_THUMB_ROT_USAGE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _DIP_COMP_RECT
{
    MMP_ULONG           ulX;    // Unit = pixel
    MMP_ULONG           ulY;    // Unit = line
    MMP_ULONG           ulW;    // Unit = pixel
    MMP_ULONG           ulH;    // Unit = line
    MMP_ULONG           ulLineOffset;    // Unit = pixel
} DIP_COMP_RECT;

typedef struct _MMP_COMPONENT_HANDLER_DIP
{
    DIP_COMP_RECT       stInRect;
    DIP_COMP_RECT       stCropRect;
    DIP_COMP_RECT       stOutRect;
    DIP_COMP_COLOR_FMT  inFormat;
    DIP_COMP_COLOR_FMT  outFormat;
    MMP_USHORT          usLineBias;
    union {
        struct {
            MMP_BOOL bMirror;
            MMP_BOOL bFlip;
            MMP_BOOL bOsdb;
            MMP_UBYTE byOutCompIdx;
        } scale, cc, move, osdb;
        struct {
            DIP_R_COMP_ROT_DEG RotDegree;
        } rotate;
    } fdAttr;
} MMP_COMPONENT_HANDLER_DIP;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_DIP_Move[];
extern MMP_COMPONENT_BASE Component_DIP_Rotate[];
extern MMP_COMPONENT_BASE Component_DIP_Scale[];
extern MMP_COMPONENT_BASE Component_DIP_ColorConvert[];
extern MMP_COMPONENT_BASE Component_DIP_OSDB[];

extern MMP_COMPONENT_HANDLER_DIP Component_DIP_R_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_DIP_R_Memory[];
extern MMP_COMPONENT_HANDLER_DIP Component_DIP_Scale_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_DIP_Scale_Memory[];
extern MMP_COMPONENT_HANDLER_DIP Component_DIP_Move_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_DIP_Move_Memory[];
extern MMP_COMPONENT_HANDLER_DIP Component_DIP_CC_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_DIP_CC_Memory[];
extern MMP_COMPONENT_HANDLER_DIP Component_DIP_OSDB_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_DIP_OSDB_Memory[];

extern MMP_COMPONENT_PORT_INFO ComponentPort_DipR[];
extern MMP_COMPONENT_PORT_INFO ComponentPort_DipS[];

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR Component_DIP_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_DIP_GetParam(void *handler, int type, void* pParam);

void Component_RearCam_2In1_Enable( MMP_BOOL bEnable );
MMP_BOOL Component_RearCam_2In1_Status( void );

#endif // _COMPONENT_DIP_H_

