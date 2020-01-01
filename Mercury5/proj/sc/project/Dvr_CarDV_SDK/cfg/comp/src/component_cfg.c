//------------------------------------------------------------------------------
//
//  File        : component_cfg.c
//  Description : Component configuration
//  Author      : CZ
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_cfg.h"
#include "mmp_component_ctl.h"

#include "component_raws.h"
#include "component_dip.h"
#include "component_scl.h"
#include "component_display.h"
#include "component_mfe.h"
#include "component_mgr.h"
#include "component_jpe.h"
#include "component_jpemgr.h"
#include "component_jpd.h"
#include "component_aud.h"
#include "component_pip.h"
#include "component_hvd.h"
#include "component_HvdTimerCtl.h"
#include "component_adas.h"
#include "component_huvc.h"
#include "component_uvc.h"
#include "component_memhost.h"
#include "component_uvc.h"

#include "Config_SDK.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if 0
void _____SCL_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_SCL0 Component_SCL0_Handler[] =
{
    {
        MMP_TRUE,                       // bYUV601
        3,                              // u16BufNumber
        MMP_FALSE,                      // bCropEn
        {                               // stCropWin
            1,
            1,
            1920,
            1080
        },
        MMP_FALSE,                      // bLineOffsetEn
        0,                              // u16LineOffset
        E_DRV_SCLDMA_1_FRM_W,           // enClient
        E_DRV_SCLDMA_IO_BUFFER_MD_RING, // enBufferMd
        E_DRV_SCLDMA_IO_COLOR_YUV420,   // enColor
        E_DRV_SCLDMA_IO_MEM_FRM,        // enMem
        E_DRV_SCLHVSP_IO_SRC_ISP,       // enSrc
        {                               // stOsdInfo
            0,
            E_DRV_SCLHVSP_IO_OSD_LOC_AFTER,
            0,
            0
        },
        {0, 0, 0, 0},                   // stInRect
        {0, 0, 0, 0},                   // stOutRect
        10,                             // u16DropFrameCnt
        MFE_SHARE_BUF_LINE_BIAS,        // u16MFEOffset
        1,                              // bMCNR //M5 c2390 LIHDR should disable MCNR
        1,                              // bCIIR
        1,                              // bLDC
    },
    {
        MMP_TRUE,
        3,
        MMP_FALSE,
        {
            1,
            1,
            1920,
            1080
        },
        MMP_FALSE,
        0,
        E_DRV_SCLDMA_1_FRM_W,
        E_DRV_SCLDMA_IO_BUFFER_MD_RING,
        E_DRV_SCLDMA_IO_COLOR_YUV420,
        E_DRV_SCLDMA_IO_MEM_FRM,
        E_DRV_SCLHVSP_IO_SRC_ISP,
        {
            0,
            E_DRV_SCLHVSP_IO_OSD_LOC_AFTER,
            0,
            0
        },
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        10,
        MFE_SHARE_BUF_LINE_BIAS,
        1,                                 //M5 c2390 LIHDR should disable MCNR
        1,
        1,
    },
};

MMP_COMPONENT_MEMORY_INFO Component_SCL0_Memory[] =
{
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_CUSTOMER,  // MemMode
        0,                              // ulNearRingThd
    },
    {
        1,
        {
            {
                0,
                0
            },
        },
        0,
        0,
        MMP_COMPONENT_MEMORY_CUSTOMER,
        0,
    },
};

MMP_COMPONENT_HANDLER_SCL1 Component_SCL1_Handler[] =
{
    {
        MMP_TRUE,                       // bYUV601
        3,                              // u16BufNumber
        MMP_FALSE,                      // bLineOffsetEn
        0,                              // u16LineOffset
        E_DRV_SCLDMA_2_FRM_W,           // enClient
        E_DRV_SCLDMA_IO_BUFFER_MD_RING, // enBufferMd
        E_DRV_SCLDMA_IO_COLOR_YUV420,   // enColor
        E_DRV_SCLDMA_IO_MEM_FRM,        // enMem
        E_DRV_SCLHVSP_IO_SRC_HVSP,      // enSrc
        {0, 0, 0, 0},                   // stInRect
        {0, 0, 0, 0},                   // stOutRect
        5,                              // u16DropFrameCnt
        0,                              // u16MFEOffset
    },
    {
        MMP_TRUE,
        3,
        MMP_FALSE,
        0,
        E_DRV_SCLDMA_2_FRM_W,
        E_DRV_SCLDMA_IO_BUFFER_MD_RING,
        E_DRV_SCLDMA_IO_COLOR_YUV420,
        E_DRV_SCLDMA_IO_MEM_FRM,
        E_DRV_SCLHVSP_IO_SRC_HVSP,
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        5,
        0,
    }
};

MMP_COMPONENT_MEMORY_INFO Component_SCL1_Memory[] =
{
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_CUSTOMER,  // MemMode
        0,                              // ulNearRingThd
    },
    {
        1,
        {
            {
                0,
                0
            },
        },
        0,
        0,
        MMP_COMPONENT_MEMORY_CUSTOMER,
        0,
    }
};

#if 0
void _____Display_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DISPLAY Component_Display_Handler[] =
{
    {
        MMP_SCAL_FITMODE_OPTIMAL,       // eFitMode
        {0, 0, 480, 864},               // stInRect
        {0, 0, 480, 864},               // stCropRect
        {0, 0, 480, 854},               // stOutRect
        {0, 0, 480, 854},               // stBkColRect
        MMP_FALSE,                      // bMirror
        MMP_DISPLAY_COLOR_YUV420,       // eColorFormat
        {0, 0},                         // stSclCfg
    },
};

MMP_COMPONENT_MEMORY_INFO Component_Display_Memory[] =
{
    {
        0,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0,                      // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____DIP_R_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DIP Component_DIP_R_Handler[COMPONENT_DIP_R_MAX_NUM] =
{
    {
        {0, 0, 0, 0},                   // stInRect
        {0, 0, 0, 0},                   // stCropRect
        {0, 0, 0, 0},                   // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // outFormat
        0,                              // usLineBias
        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
        DIP_COMP_ROTATE_90              // RotDegree
        #else
        DIP_COMP_ROTATE_270             // RotDegree
        #endif
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
        DIP_COMP_ROTATE_90
        #else
        DIP_COMP_ROTATE_270
        #endif
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        #if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90)
        DIP_COMP_ROTATE_90
        #else
        DIP_COMP_ROTATE_270
        #endif
    },
};

MMP_COMPONENT_MEMORY_INFO Component_DIP_R_Memory[COMPONENT_DIP_R_MAX_NUM] =
{
    {
        2,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____DIP_M_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DIP Component_DIP_Move_Handler[COMPONENT_DIP_MOVE_MAX_NUM] =
{
    {
        {0, 0, 32, 64},                 // stInRect
        {0, 0, 32, 64},                 // stCropRect
        {0, 0, 32, 64},                 // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_FALSE                       // bOsdb
    }
};

MMP_COMPONENT_MEMORY_INFO Component_DIP_Move_Memory[COMPONENT_DIP_MOVE_MAX_NUM] =
{
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        32*64*2,                        // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    }
};

#if 0
void _____DIP_S_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DIP Component_DIP_Scale_Handler[COMPONENT_DIP_S_MAX_NUM] =
{
    {   /* 0 */
        {0, 0, 0, 0, 0},                // stInRect
        {0, 0, 0, 0, 0},                // stCropRect
        {0, 0, 0, 0, 0},                // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_FALSE,                      // bOsdb
        0                               // byOutCompIdx
    },
    {   /* 1 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 2 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 3 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 4 */
        {0, 0, 1920, 1080, 1920},
        {0, 0, 1920, 1080, 1920},
        {0, 0, 512, 288, 512},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 5 */
        {0, 0, 720, 480, 720},
        {0, 0, 720, 480, 720},
        {0, 0, 512, 288, 512},
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        DIP_COMP_COLOR_FMT_YUV422_YUYV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 6 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 7 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 8 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 9 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 10 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 11 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 12 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 13 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 14 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
    {   /* 15 */
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        DIP_COMP_COLOR_FMT_YUV420_UV,
        DIP_COMP_COLOR_FMT_YUV420_UV,
        0,
        MMP_FALSE,
        MMP_FALSE,
        MMP_FALSE,
        0
    },
};

MMP_COMPONENT_MEMORY_INFO Component_DIP_Scale_Memory[COMPONENT_DIP_S_MAX_NUM] =
{
    {   /* 0 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 1 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 2 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 3 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 4 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 5 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 6 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 7 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 8 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 9 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 10 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 11 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 12 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 13 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 14 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {   /* 15 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____DIP_CC_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DIP Component_DIP_CC_Handler[] =
{
    {
        {0, 0, 720, 480},               // stInRect
        {0, 0, 720, 480},               // stCropRect
        {0, 0, 720, 480},               // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV420_UV,   // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_FALSE                       // bOsdb
    },
    {
        {0, 0, 512, 288},               // stInRect
        {0, 0, 512, 288},               // stCropRect
        {0, 0, 512, 288},               // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV420_UV,   // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_FALSE                       // bOsdb
    },
    {
        {0, 0, 1920, 1088},             // stInRect
        {0, 0, 1920, 1088},             // stCropRect
        {0, 0, 1920, 1088},             // stOutRect
        DIP_COMP_COLOR_FMT_YUV420_UV,   // inFormat
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_FALSE                       // bOsdb
    },
};

MMP_COMPONENT_MEMORY_INFO Component_DIP_CC_Memory[] =
{
    {
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        720*480*3/2,                    // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        512*288*3/2,                    // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        1920*1088*2,                    // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____DIP_OSDB_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_DIP Component_DIP_OSDB_Handler[COMPONENT_DIP_OSDB_MAX_NUM] =
{
    {
        {0, 0, 720, 480},               // stInRect
        {0, 0, 720, 480},               // stCropRect
        {0, 0, 720, 480},               // stOutRect
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // inFormat
        DIP_COMP_COLOR_FMT_YUV422_YUYV, // outFormat
        0,                              // usLineBias
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        MMP_TRUE                        // bOsdb
    },
};

MMP_COMPONENT_MEMORY_INFO Component_DIP_OSDB_Memory[COMPONENT_DIP_OSDB_MAX_NUM] =
{
    {
        2,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        720*480*2,                      // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____PIP_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_PIP Component_PIP_Handler[] =
{
    {
        {0, 0, 0, 0},                   // stBgRect
        {0, 0, 0, 0},                   // stFgRect
        PIP_COMP_COLOR_FMT_YUYV422,     // ColorFmt
        {                               // AlphaAttr
            PIP_COMP_ALPHA_FMT_GLOBAL,
            0xFF
        },
        MMP_FALSE,                      // bMirror
        MMP_FALSE,                      // bFlip
        0,                              //g_DropFrame
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        PIP_COMP_COLOR_FMT_YUYV422,
        {
            PIP_COMP_ALPHA_FMT_GLOBAL,
            0xFF
        },
        MMP_FALSE,
        MMP_FALSE,
        0,                              //g_DropFrame
    },
};

MMP_COMPONENT_MEMORY_INFO Component_PIP_Memory[] =
{
    {
        0,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            {
                0,                      // ubWBufIndex
                0                       // ubRBufIndex
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0,                              // ulNearRingThd
    },
};

#if 0
void _____MFE_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_MFE Component_MFE_Handler[] =
{
    {
        MFE_COMP_PRM_RECD,              // ubUseType
        0,                              // ubEncID
        MFE_COMP_STREAMTYPE_PRM_RECD,   // usStreamType
        16000000,                       // ulBitrate
        14,                             // ulPframeNum
        MFE_COMP_PROFILE_MAIN,          // eProfile
        MFE_COMP_PIXFMT_NV12,           // ePixFmt
        {1920, 1080, 1920, 1088},       // stEncWH
        {1001, 30000}, // 29.97FPS      // stSnrFps
        {1001, 30000}, // 29.97FPS      // stEncFps
        {1001, 30000}, // 29.97FPS      // stMgrFps
        MMP_TRUE,                       // bEncodeEn
        MFE_SHARE_BUF_LINE_BIAS,        // usLineOffset
        {                               // stQpCtl
            20, 38,                     // I frame Min, Max QP.
            22, 42,                     // P frame Min, Max QP.
            18, 40,                     // I MB Min, Max QP.
            20, 42                      // P MB Min, Max QP.
        },
    },
    {
        MFE_COMP_SCD_RECD,
        0,
        MFE_COMP_STREAMTYPE_SCD_RECD,
        5000000,
        14,
        MFE_COMP_PROFILE_MAIN,
        MFE_COMP_PIXFMT_NV12,
        {720, 480, 720, 480},
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        MMP_TRUE,
        MFE_SHARE_BUF_LINE_BIAS,
        {
            20, 38,
            22, 42,
            18, 40,
            20, 42
        },
    },
    {
        MFE_COMP_TRD_RECD,
        0,
        MFE_COMP_STREAMTYPE_TRD_RECD,
        5000000,
        14,
        MFE_COMP_PROFILE_MAIN,
        MFE_COMP_PIXFMT_NV12,
        {720, 480, 720, 480},
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        MMP_TRUE,
        MFE_SHARE_BUF_LINE_BIAS,
        {
            20, 38,
            22, 42,
            18, 40,
            20, 42
        },
    },
    {
        MFE_COMP_UVC_RECD,
        0,
        MFE_COMP_STREAMTYPE_UVC_RECD,
        12000000,
        14,
        MFE_COMP_PROFILE_MAIN,
        MFE_COMP_PIXFMT_NV12,
        {1920, 1080, 1920, 1080},
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        MMP_FALSE,
        MFE_SHARE_BUF_LINE_BIAS,
        {
            20, 38,
            22, 42,
            18, 40,
            20, 42
        },
    },
    {
        MFE_COMP_PRM_STREAM,
        0,
        MFE_COMP_STREAMTYPE_WIFI_PRM,
        12000000,
        14,
        MFE_COMP_PROFILE_MAIN,
        MFE_COMP_PIXFMT_NV12,
        {1920, 1080, 1920, 1088},
        {1001, 30000}, // 29.97FPS
        {1001, 30000}, // 29.97FPS
        {1001, 30000}, // 29.97FPS
        MMP_TRUE,
        MFE_SHARE_BUF_LINE_BIAS,
        {
            20, 38,
            22, 42,
            18, 40,
            20, 42
        },
    },
    {
        MFE_COMP_SCD_STREAM,
        0,
        MFE_COMP_STREAMTYPE_WIFI_SCD,
        3000000,
        14,
        MFE_COMP_PROFILE_MAIN,
        MFE_COMP_PIXFMT_NV12,
        {640, 360, 640, 368},
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        {1200, 30000}, // 25FPS
        MMP_TRUE,
        MFE_SHARE_BUF_LINE_BIAS,
        {
            20, 38,
            22, 42,
            18, 40,
            20, 42
        },
    },
};

MMP_COMPONENT_MEMORY_INFO Component_MFE_Memory[] =
{
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x800000,                       // ulBufSize : Ref:m_VidRecdConfigs.ulVideoCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        512*1024,                       // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x600000,                       // ulBufSize : Ref:m_VidRecdConfigs.ul2ndVideoCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024,                       // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x600000,                       // ulBufSize : Ref:m_VidRecdConfigs.ul2ndVideoCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024,                       // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x600000,                       // ulBufSize : Ref:m_VidRecdConfigs.ulUVCVidCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024,                       // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x800000,                       // ulBufSize : Ref:m_VidRecdConfigs.ulWifiVideoCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        512*1024,                       // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x100000,                       // ulBufSize : Ref:m_VidRecdConfigs.ulWifiVideoCompBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024,                       // ulNearRingThd
    },
};

#if 0
void _____Merger_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_MGR Component_MGR_Handler[] =
{
    {
        MGR_COMP_PRM_RECD,              // ubUseType
        VIDENC_STREAM_PRM_RECD,         // usStreamType
        NULL,                           // pContainer
        MMP_FALSE,                      // bMultiTrack
        MMP_TRUE,                       // bEncodeEn
    },
    {
        MGR_COMP_SCD_RECD,
        VIDENC_STREAM_SCD_RECD,
        NULL,
        MMP_FALSE,
        MMP_TRUE,
    },
    {
        MGR_COMP_TRD_RECD,
        VIDENC_STREAM_TRD_RECD,
        NULL,
        MMP_FALSE,
        MMP_TRUE,
    },
    {
        MGR_COMP_UVC_RECD,
        VIDENC_STREAM_UVC_RECD,
        NULL,
        MMP_FALSE,
        MMP_FALSE,
    },
    {
        MGR_COMP_PRM_STREAM,
        VIDENC_STREAM_WIFI_PRM,
        NULL,
        MMP_FALSE,
        MMP_TRUE,
    },
    {
        MGR_COMP_SCD_STREAM,
        VIDENC_STREAM_WIFI_SCD,
        NULL,
        MMP_FALSE,
        MMP_TRUE,
    },
};

MMP_COMPONENT_MEMORY_INFO Component_MGR_Memory[] =
{
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x100000,                       // ulBufSize: for repack buffer
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x80000,                        // ulBufSize: for repack buffer, if bMultiTrack = 1, set 0.
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x80000,                        // ulBufSize: for repack buffer, if bMultiTrack = 1, set 0.
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0x80000,                        // ulBufSize: for repack buffer, if bMultiTrack = 1, set 0.
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize: streaming mode don't need repack buffer
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize: streaming mode don't need repack buffer
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____JPE_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_JPE Component_JPE_Handler[JPE_COMP_USAGE_NUM] =
{
    {   /* 0 */
        JPE_COMP_PRM_MJPEG,             // ubUseType
        JPE_COMP_UI_MODE_VR,            // ubUiMode
        0,                              // usInstID
        JPE_COMP_FMT_NV12,              // ubRawFormat
        JPE_COMP_SINGLE_SHOT,           // ubShotMode
        1,                              // ulShotNum
        22,                             // usInitQFactor
        {640, 480, 640, 480},           // stEncWH
    },
    {   /* 1 */
        JPE_COMP_SCD_MJPEG,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        22,
        {640, 480, 640, 480},
    },
    {   /* 2 */
        JPE_COMP_TRD_MJPEG,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        22,
        {640, 480, 640, 480},
    },
    {   /* 3 */
        JPE_COMP_PRM_PRIMARY,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        20,
        {1920, 1080, 1920, 1088},
    },
    {   /* 4 */
        JPE_COMP_SCD_PRIMARY,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        20,
        {720, 480, 720, 480},
    },
    {   /* 5 */
        JPE_COMP_TRD_PRIMARY,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        20,
        {720, 480, 720, 480},
    },
    {   /* 6 */
        JPE_COMP_PRM_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        25,
        {160, 120, 160, 120},
    },
    {   /* 7 */
        JPE_COMP_SCD_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        25,
        {160, 120, 160, 120},
    },
    {   /* 8 */
        JPE_COMP_TRD_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        1,
        25,
        {160, 120, 160, 120},
    },
    {   /* 9 */
        JPE_COMP_PRM_VR_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        0xFFFFFFFF,
        20,
        {512, 288, 512, 288},
    },
    {   /* 10 */
        JPE_COMP_SCD_VR_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        0xFFFFFFFF,
        20,
        {512, 288, 512, 288},
    },
    {   /* 11 */
        JPE_COMP_TRD_VR_THUMB,
        JPE_COMP_UI_MODE_VR,
        0,
        JPE_COMP_FMT_NV12,
        JPE_COMP_SINGLE_SHOT,
        0xFFFFFFFF,
        20,
        {512, 288, 512, 288},
    },
};

MMP_COMPONENT_MEMORY_INFO Component_JPE_Memory[JPE_COMP_USAGE_NUM] =
{
    {   /* 0 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        1024*1024                        // ulNearRingThd => Jinag Ann: Temporary increase this value to avoid Jpeg out buffer full.(TBD)
    },
    {   /* 1 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 2 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 3 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 4 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 5 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 6 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 7 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 8 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_NEARRING,  // MemMode
        256*1024                        // ulNearRingThd
    },
    {   /* 9 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        512*288,                        // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {   /* 10 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        512*288,                        // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {   /* 11 */
        1,                              // ubBufNum
        {
            {
                0,                      // ulWL
                0,                      // ulWH
                0,                      // ulRL
                0,                      // ulRH
            },
        },
        512*288,                        // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____JPE_Merger_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_JPE_MGR Component_JPEMGR_Handler[] =
{
    {   /* 0 */
        JPEMGR_COMP_PRM_MJPEG,         // ubUseType
        JPE_COMP_SINGLE_SHOT,           // ubShotMode
    },
    {   /* 1 */
        JPEMGR_COMP_SCD_MJPEG,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 2 */
        JPEMGR_COMP_TRD_MJPEG,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 3 */
        JPEMGR_COMP_PRM_PRIMARY,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 4 */
        JPEMGR_COMP_SCD_PRIMARY,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 5 */
        JPEMGR_COMP_TRD_PRIMARY,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 6 */
        JPEMGR_COMP_PRM_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 7 */
        JPEMGR_COMP_SCD_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 8 */
        JPEMGR_COMP_TRD_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 9 */
        JPEMGR_COMP_PRM_VR_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 10 */
        JPEMGR_COMP_SCD_VR_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
    {   /* 11 */
        JPEMGR_COMP_TRD_VR_THUMB,
        JPE_COMP_SINGLE_SHOT,
    },
};

MMP_COMPONENT_MEMORY_INFO Component_JPEMGR_Memory[] =
{
    {   /* 0 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 1 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 2 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 3 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 4 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 5 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 6 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 7 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 8 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 9 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 10 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {   /* 11 */
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____HVD_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_HVD Component_HVD_Handler[] =
{
    {
        0,                              // ulIsUtMode
        0,                              // ulIsInitialDone
        0,                              // ulSize
        0,                              // ulTimestamp
        0,                              // pGetFrmInf
    },
};

MMP_COMPONENT_MEMORY_INFO Component_HVD_Memory[] =
{
    {
        0,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____JPD_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_JPD Component_JPD_Handler[] =
{
    {
        JPD_COMP_STILL_DEC,             // ubUseType
        {0, 0, 0, 0},                   // stResol
        JPD_COMP_DEC_SRC_FILE,          // ubDecSrc
        JPD_COMP_IMG_TYPE_PRIMARY       // ubDecImgType
    },
    {
        JPD_COMP_MJPEG_DEC,
        {0, 0, 1280, 720},
        JPD_COMP_DEC_SRC_MJPEG,
        JPD_COMP_IMG_TYPE_PRIMARY,
    }
};

MMP_COMPONENT_MEMORY_INFO Component_JPD_Memory[] =
{
    {
        1,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        1280*720*2,                     // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____TimerCtl_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_TIMECTL Component_TCL_Handler[] =
{
    {
        0,                              // ulStAddr
        0,                              // ulSize
        0,                              // ulTimestamp
        0,                              // ulSkipStartFrmNum
    },
    {
        0,                              // ulStAddr
        0,                              // ulSize
        0,                              // ulTimestamp
        2,                              // ulSkipStartFrmNum
    },
};

MMP_COMPONENT_MEMORY_INFO Component_TCL_Memory[] =
{
    {
        0,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_INTERNAL,  // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____AUDIO_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_AUD_GAIN AudGain[2] =
{
    {MMP_AUD_GAIN_MIC_PREGAIN_13dB, MMP_AUD_GAIN_MIC_ADC_ANALOG_P6dB, 3},
    {MMP_AUD_GAIN_MIC_PREGAIN_13dB, MMP_AUD_GAIN_MIC_ADC_ANALOG_P6dB, 3},
};

MMP_COMPONENT_HANDLER_AUD Component_AudEnc_Handler[] =
{
    {
        COMPONENT_AUD_DIRECTION_RECORD,         // Audio Operation
        COMPONENT_AUD_RECORD_PATH_SINGLE_LINEIN,// Audio Path
        COMPONENT_AUD_FORMAT_ADPCM,             // Audio Format
        COMPONENT_AUD_ADPCM_32K_22K,            // Audio Option
        &AudGain[0],                            // Audio Gain
        32000,                                  // ulSampleRate
        22000,                                  // ulBitRate
    },
};

MMP_COMPONENT_MEMORY_INFO Component_AudEnc_Memory[] =
{
    {
        2,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0x100000,                       // ulBufSize     //1MB for Compress buffer size
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_RING,      // MemMode
        0                               // ulNearRingThd
    },
};

MMP_COMPONENT_HANDLER_AUD Component_AudDec_Handler[] =
{
    {
        COMPONENT_AUD_PLAYBACK_PATH_SINGLE_LINEOUT,// Audio Path
        COMPONENT_AUD_FORMAT_ADPCM,             // Audio Format
        COMPONENT_AUD_ADPCM_32K_22K,            // Audio Option
        &AudGain[1],                            // Audio Gain
        32000,                                  // ulSampleRate
        22000,                                  // ulBitRate
    },
};

MMP_COMPONENT_MEMORY_INFO Component_AudDec_Memory[] =
{
    {
        2,                              // ubBufNum
        0,                              // ubWBufIndex
        0,                              // ubRBufIndex
        0x100000,                       // ulBufSize     //1MB for Compress buffer size
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_RING,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____RAW_Store_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_RAW Component_RAWS_Handler[] =
{
    {
        720,                            // usWidth
        288,                            // usHeight
        1,                              // ubSnrSel
        RAWS_COMP_SIG_TYPE_INTERLACE,   // ubSigType
        5,                              // usDropFrameCnt
    },
    {
        720,
        288,
        1,
        RAWS_COMP_SIG_TYPE_INTERLACE,
        3,
    },
    {
        720,
        288,
        1,
        RAWS_COMP_SIG_TYPE_INTERLACE,
        3,
    },
};

MMP_COMPONENT_MEMORY_INFO Component_RAWS_Memory[] =
{
    {
        2,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0,                          // ubRBufIndex
        },
        720*288*2,                      // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0,                          // ubRBufIndex
        },
        720*288*2,                      // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        2,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0,                          // ubRBufIndex
        },
        720*288*2,                      // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____ADAS_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_ADAS Component_Adas_Handler[] =
{
    {
        COMMON_LDWS_EN_ON,              // bLdwsEnable
        COMMON_FCWS_EN_ON,              // bFcwsEnable
        COMMON_SAG_EN_ON,               // bSagEnable
    },
};

MMP_COMPONENT_MEMORY_INFO Component_Adas_Memory[] =
{
    {
        1,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        LDWS_WIDTH*LDWS_HEIGHT*1,       // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____MDTC_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_MDTC Component_Mdtc_Handler[] =
{
    {
        MMP_FALSE,                      // bParkingMode
        MOTION_DTC_SENSITIVITY_MID,     // uiMotionDtcSensitivity
        VMD_REC_TIME_5SEC,              // uiVMDRecTime
    },
};

MMP_COMPONENT_MEMORY_INFO Component_Mdtc_Memory[] =
{
     {
        1,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        MDTC_WIDTH*MDTC_HEIGHT*1,       // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____HUVC_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_HUVC Component_HUVC_Handler[] =
{
    {
        HUVC_COMP_USB_MODE_ISO,         // ubUsbMode
        0,                              // uFrameDropThreshold
        {                               // stEncWH
            1280,                       // ulW
            720                         // ulH
        }
    },
};

MMP_COMPONENT_MEMORY_INFO Component_HUVC_Memory[] =
{
    {
        3,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0x20000,                        // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____UVC_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_UVC Component_UVC_Handler[] =
{
    {
        {1920, 1088},                   // stResol
        UVC_COMP_FORMAT_YUV422,         // eColorFormat
    },
    {
        {720, 480},                     // stResol
        UVC_COMP_FORMAT_YUV422,         // eColorFormat
    },
};

MMP_COMPONENT_MEMORY_INFO Component_UVC_Memory[] =
{
    {
        0,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};

#if 0
void _____MEM_Host_Configuration_____(){}
#endif

MMP_COMPONENT_HANDLER_MEMHOST Component_MemHost_Handler[] =
{
    {
        MEMHOST_COMP_BROWSER_THUMB,     // ubUseType
        MMP_TRUE                        // bEnableHandler
    },
    {
        MEMHOST_COMP_FCAM_VR_THUMB,
        MMP_TRUE
    },
    {
        MEMHOST_COMP_RCAM_VR_THUMB,
        MMP_TRUE
    },
};

MMP_COMPONENT_MEMORY_INFO Component_MemHost_Memory[] =
{
    {
        0,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
    {
        0,                              // ubBufNum
        {
            0,                          // ubWBufIndex
            0                           // ubRBufIndex
        },
        0,                              // ulBufSize
        0,                              // ulBufBias
        MMP_COMPONENT_MEMORY_AUTO,      // MemMode
        0                               // ulNearRingThd
    },
};
