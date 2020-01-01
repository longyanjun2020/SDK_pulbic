//------------------------------------------------------------------------------
//
//  File        : component_scl.h
//  Description : Header file of SCL configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_SCL_H_
#define _COMPONENT_SCL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

#include "drv_scl_hvsp_io_st.h"
#include "drv_scl_dma_io_st.h"
#include "drv_scl_os.h"
#include "drv_scl_hvsp_st.h"
#include "drv_scl_dma_st.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_SCL0_MAX_NUM         (SCL0_COMP_USAGE_NUM)
#define COMPONENT_SCL1_MAX_NUM         (SCL1_COMP_USAGE_NUM)

#define SCL_COMP_BUF_SIZE_YUV420(W, H) (W * H * 3 / 2)
#define SCL_COMP_BUF_SIZE_YUV422(W, H) (W * H * 2)

#if (SUPPORT_MFE_SHAREBUFFER)
#define SCL_COMP_RECORD_BUF_COUNT      (3)
#define SCL_COMP_PREVW_BUF_COUNT       (2)
#else
#define SCL_COMP_RECORD_BUF_COUNT      (2)
#define SCL_COMP_PREVW_BUF_COUNT       (2)
#endif

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum
{
    SCL_COMP_PARAM_IN_RECT = 0,
    SCL_COMP_PARAM_OUT_RECT,
    SCL_COMP_PARAM_BUF_COUNT,
    SCL_COMP_PARAM_BUF_SIZE,
    SCL_COMP_PARAM_MCNR_EN,
    SCL_COMP_PARAM_CIIR_EN,
    SCL_COMP_PARAM_LDC_EN,
    SCL_COMP_PARAM_LINE_BIAS,
    SCL_COMP_PARAM_BUF_BIAS,
    SCL_COMP_PARAM_MAX
} SCL_COMP_PARAM;

typedef enum
{
    SCL_COMP_TYPE_ID_SCL0 = 0,
    SCL_COMP_TYPE_ID_SCL1,
    SCL_COMP_TYPE_ID_NUM
} SCL_COMP_TYPE_ID;

typedef enum
{
    SCL0_COMP_PRM_CAM = 0,
    SCL0_COMP_SCD_CAM,
    SCL0_COMP_USAGE_NUM
} SCL0_COMP_USAGE;

typedef enum
{
    SCL1_COMP_PRM_CAM = 0,
    SCL1_COMP_SCD_CAM,
    SCL1_COMP_USAGE_NUM
} SCL1_COMP_USAGE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct
{
    bool                        bEn;          ///< OSD enable
    DrvSclHvspOsdLocType_e      enOSD_loc;    ///< OSD locate
    bool                        bOSDBypass;   ///< OSD bypass
    bool                        bWTMBypass;   ///< WTM bypass
} OSDConfigInfo;

typedef struct _SCL_COMP_RECT
{
    MMP_ULONG                   ulX;
    MMP_ULONG                   ulY;
    MMP_ULONG                   ulW;
    MMP_ULONG                   ulH;
} SCL_COMP_RECT;

typedef struct _MMP_COMPONENT_HANDLER_SCL0
{
    MMP_BOOL                    bYUV601;
    u16                         u16BufNumber;
    MMP_BOOL                    bCropEn;
    DrvSclHvspIoWindowConfig_t  stCropWin;
    MMP_BOOL                    bLineOffsetEn;
    u16                         u16LineOffset;
    DrvSclDmaClientType_e       enClient;
    DrvSclDmaIoBufferModeType_e enBufferMd;
    DrvSclDmaIoColorType_e      enColor;
    DrvSclDmaIoMemType_e        enMem;
    DrvSclHvspIoSrcType_e       enSrc;
    OSDConfigInfo               stOsdInfo;
    SCL_COMP_RECT               stInRect;
    SCL_COMP_RECT               stOutRect;
    u16                         u16DropFrameCnt;
    u16                         u16LineBias;
    MMP_BOOL                    bMCNR;
    MMP_BOOL                    bCIIR;
    MMP_BOOL                    bLDC;
} MMP_COMPONENT_HANDLER_SCL0;

typedef struct _MMP_COMPONENT_HANDLER_SCL1
{
    MMP_BOOL                    bYUV601;
    u16                         u16BufNumber;
    MMP_BOOL                    bLineOffsetEn;
    u16                         u16LineOffset;
    DrvSclDmaClientType_e       enClient;
    DrvSclDmaIoBufferModeType_e enBufferMd;
    DrvSclDmaIoColorType_e      enColor;
    DrvSclDmaIoMemType_e        enMem;
    DrvSclHvspIoSrcType_e       enSrc;
    SCL_COMP_RECT               stInRect;
    SCL_COMP_RECT               stOutRect;
    u16                         u16DropFrameCnt;
    u16                         u16LineBias;
} MMP_COMPONENT_HANDLER_SCL1;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_SCL0[];
extern MMP_COMPONENT_BASE Component_SCL1[];

extern MMP_COMPONENT_MEMORY_INFO Component_SCL0_Memory[];
extern MMP_COMPONENT_MEMORY_INFO Component_SCL1_Memory[];
extern MMP_COMPONENT_HANDLER_SCL0 Component_SCL0_Handler[];
extern MMP_COMPONENT_HANDLER_SCL1 Component_SCL1_Handler[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

void SCL0_SetCurComponent(u16 CompID);
void SCL1_SetCurComponent(u16 CompID);
void SCL_SetCMDQUse(bool bCMDQUse);
bool SCL0_GetMCNREn(u16 CompID); 
bool SCL0_GetCIIREn(u16 CompID);
bool SCL0_GetLDCEn(u16 CompID);

MMP_ERR Component_SCL0_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_SCL1_SetParam(void *handler, int type, void* pParam);

#endif // _COMPONENT_SCL_H_

