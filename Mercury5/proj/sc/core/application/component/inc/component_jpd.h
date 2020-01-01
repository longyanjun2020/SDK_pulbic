//------------------------------------------------------------------------------
//
//  File        : component_jpd.h
//  Description : Header file of JPD configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_JPD_H_
#define _COMPONENT_JPD_H_

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

#define MAX_JPD_COMP_NUM                JPD_COMP_USAGE_NUM

#define JPD_COMP_BUF_SIZE_YUV422(W, H)  (W) * (H) * 2

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    JPD_COMP_STILL_DEC = 0,
    JPD_COMP_MJPEG_DEC,
    JPD_COMP_USAGE_NUM
} JPD_COMP_USAGE;

typedef enum
{
    JPD_COMP_PARAM_RES = 0,
    JPD_COMP_PARAM_DEC_SRC,
    JPD_COMP_PARAM_DEC_IMG_TYPE,
    JPD_COMP_PARAM_BUF_COUNT,
    JPD_COMP_PARAM_BUF_SIZE,
    JPD_COMP_PARAM_MEM_MODE_IN_ADDR,
    JPD_COMP_PARAM_MEM_MODE_IN_SIZE,
    JPD_COMP_PARAM_MAX
} JPD_COMP_PARAM;

typedef enum // Sync with MMPF_JPEGD_IMG_TYPE
{
    JPD_COMP_IMG_TYPE_PRIMARY = 0,
    JPD_COMP_IMG_TYPE_THUMB,
#if (DSC_SUPPORT_BASELINE_MP_FILE)
    JPD_COMP_IMG_TYPE_LARGETHUMB,
#endif
    JPD_COMP_IMG_TYPE_NUM
} JPD_COMP_IMG_TYPE;

typedef enum // Sync with MMPF_JPEGD_DEC_SRC
{
    JPD_COMP_DEC_SRC_MJPEG = 0,       ///< JPEG decode MJPEG Data
    JPD_COMP_DEC_SRC_FILE,            ///< JPEG decode files
    JPD_COMP_DEC_SRC_MEMORY,          ///< JPEG decode in memory
    JPD_COMP_DEC_SRC_NONE = 0xFF
} JPD_COMP_DEC_SRC;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _JPD_COMP_RESOL
{
    MMP_ULONG       ulStartX;
    MMP_ULONG       ulStartY;
    MMP_ULONG       ulWidth;
    MMP_ULONG       ulHeight;
} JPD_COMP_RESOL;

typedef struct _MMP_COMPONENT_HANDLER_JPD
{
    MMP_UBYTE       ubUseType;
    JPD_COMP_RESOL  stResol;
    MMP_UBYTE       ubDecSrc;               ///< Decode Source Type
    MMP_UBYTE       ubDecImgType;           ///< Decode Image Type
} MMP_COMPONENT_HANDLER_JPD;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_JPD[];

extern MMP_COMPONENT_HANDLER_JPD Component_JPD_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_JPD_Memory[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

MMP_ERR Component_JPD_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPD_GetParam(void *handler, int type, void* pParam);

MMP_ERR Component_JPD_TriggerEmptyBuf(MMP_UBYTE ubUseType);

#endif // _COMPONENT_JPD_H_

