//------------------------------------------------------------------------------
//
//  File        : component_dip.c
//  Description : Source file of dip component configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"
#include "aitu_calendar.h"
#include "component_dip.h"
#include "dip_ctl.h"
#include "sys_MsWrapper_cus_os_mem.h"

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================
static void Component_DIP_StoreBufferDone(MMP_ULONG param1, MMP_ULONG param2);
MMP_ERR Component_DIP_InitDevice(void *handler);
MMP_ERR Component_DIP_UnInitDevice(void *handler);
MMP_ERR Component_DIP_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_DIP_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_DIP_Move_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_DIP_Rotate_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_DIP_Scale_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_DIP_OSDB_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_DIP_CC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_DIP_S_AllocateMemory_LineOffset(void *handler);
MMP_ERR Component_DIP_S_Close_NoBufRelease(void *handler);
MMP_ERR Component_DIP_S_UpdateBuffer_Combination(void *handler);

MMP_ERR ComponentPort_DIP_Close(void *handler);

//==============================================================================
//
//                              MACRO
//
//==============================================================================

#define COMPONENT_DIP_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_DIP_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define DIP_COMP_COLOR_MAP(x) (\
                                x == DIP_COMP_COLOR_FMT_YUV420_UV           ?   DIP_CTL_COLOR_YUV420_UV : \
                                x == DIP_COMP_COLOR_FMT_YUV420_VU           ?   DIP_CTL_COLOR_YUV420_VU : \
                                x == DIP_COMP_COLOR_FMT_YUV420_T16X32_UV    ?   DIP_CTL_COLOR_YUV420_T16X32_UV : \
                                x == DIP_COMP_COLOR_FMT_YUV420_T16X32_VU    ?   DIP_CTL_COLOR_YUV420_T16X32_VU : \
                                x == DIP_COMP_COLOR_FMT_YUV422_YUYV         ?   DIP_CTL_COLOR_YUV422_YUYV : \
                                x == DIP_COMP_COLOR_FMT_YUV422_YVYU         ?   DIP_CTL_COLOR_YUV422_YVYU : \
                                x == DIP_COMP_COLOR_FMT_YUV422_UYVY         ?   DIP_CTL_COLOR_YUV422_UYVY : \
                                x == DIP_COMP_COLOR_FMT_YUV422_VYUY         ?   DIP_CTL_COLOR_YUV422_VYUY : \
                                DIP_CTL_COLOR_UNSUPPORT)

#define DIP_COMP_ROT_DEG_MAP(x) (\
                                x == DIP_COMP_ROTATE_0      ?   DIP_CTL_ROTATE_0 : \
                                x == DIP_COMP_ROTATE_90     ?   DIP_CTL_ROTATE_90 : \
                                x == DIP_COMP_ROTATE_180    ?   DIP_CTL_ROTATE_180 : \
                                x == DIP_COMP_ROTATE_270    ?   DIP_CTL_ROTATE_270 : \
                                DIP_CTL_ROTATE_UNSUPPORT)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_BOOL bComponent_RearCam_2In1 = MMP_FALSE;
static MMP_BYTE g_byBufferUpdated[3][2] = {0};

/* Move */
MMP_COMPONENT_BUFFER_INFO Component_DIP_Move_BufInfo[COMPONENT_DIP_MOVE_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_Move_InPort[COMPONENT_DIP_MOVE_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_Move_OutPort[COMPONENT_DIP_MOVE_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DIP_Move_MemoryInfo[COMPONENT_DIP_MOVE_MAX_NUM];
MMP_COMPONENT_HANDLER_DIP Component_DIP_Move_DevInfo[COMPONENT_DIP_MOVE_MAX_NUM];

/* Scale */
MMP_COMPONENT_BUFFER_INFO Component_DIP_Scale_BufInfo[COMPONENT_DIP_S_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_Scale_InPort[COMPONENT_DIP_S_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_Scale_OutPort[COMPONENT_DIP_S_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DIP_Scale_MemoryInfo[COMPONENT_DIP_S_MAX_NUM];
MMP_COMPONENT_HANDLER_DIP Component_DIP_Scale_DevInfo[COMPONENT_DIP_S_MAX_NUM];

/* Rotate */
MMP_COMPONENT_BUFFER_INFO Component_DIP_R_BufInfo[COMPONENT_DIP_R_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_R_InPort[COMPONENT_DIP_R_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_R_OutPort[COMPONENT_DIP_R_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DIP_R_MemoryInfo[COMPONENT_DIP_R_MAX_NUM];
MMP_COMPONENT_HANDLER_DIP Component_DIP_R_DevInfo[COMPONENT_DIP_R_MAX_NUM];

/* Color Convert */
MMP_COMPONENT_BUFFER_INFO Component_DIP_CC_BufInfo[COMPONENT_DIP_CC_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_CC_InPort[COMPONENT_DIP_CC_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_CC_OutPort[COMPONENT_DIP_CC_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DIP_CC_MemoryInfo[COMPONENT_DIP_CC_MAX_NUM];
MMP_COMPONENT_HANDLER_DIP Component_DIP_CC_DevInfo[COMPONENT_DIP_CC_MAX_NUM];

/* OSDB */
MMP_COMPONENT_BUFFER_INFO Component_DIP_OSDB_BufInfo[COMPONENT_DIP_OSDB_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_OSDB_InPort[COMPONENT_DIP_OSDB_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_DIP_OSDB_OutPort[COMPONENT_DIP_OSDB_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_DIP_OSDB_MemoryInfo[COMPONENT_DIP_OSDB_MAX_NUM];
MMP_COMPONENT_HANDLER_DIP Component_DIP_OSDB_DevInfo[COMPONENT_DIP_OSDB_MAX_NUM];

MMP_COMPONENT_BASE Component_DIP_Move[COMPONENT_DIP_MOVE_MAX_NUM] =
{
    {
        "DIP_M0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Move_MemoryInfo[0],      // MemoryInfo
        Component_DIP_Move_BufInfo[0],          // BufferInfo
        &Component_DIP_Move_InPort[0],          // pInPort
        Component_DIP_Move_OutPort[0],          // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Move_EmptyBuffer,        // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Move_DevInfo[0]          // DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_DIP_Scale[COMPONENT_DIP_S_MAX_NUM] =
{
    {
        "DIP_S0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[0],     // MemoryInfo
        Component_DIP_Scale_BufInfo[0],         // BufferInfo
        &Component_DIP_Scale_InPort[0],         // pInPort
        Component_DIP_Scale_OutPort[0],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[0]         // DeviceInfo
    },
    {
        "DIP_S1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[1],     // MemoryInfo
        Component_DIP_Scale_BufInfo[1],         // BufferInfo
        &Component_DIP_Scale_InPort[1],         // pInPort
        Component_DIP_Scale_OutPort[1],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[1]         // DeviceInfo
    },
    {
        "DIP_S2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[2],     // MemoryInfo
        Component_DIP_Scale_BufInfo[2],         // BufferInfo
        &Component_DIP_Scale_InPort[2],         // pInPort
        Component_DIP_Scale_OutPort[2],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[2]         // DeviceInfo
    },
    {
        "DIP_S3",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[3],     // MemoryInfo
        Component_DIP_Scale_BufInfo[3],         // BufferInfo
        &Component_DIP_Scale_InPort[3],         // pInPort
        Component_DIP_Scale_OutPort[3],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[3]         // DeviceInfo
    },
    {
        "DIP_S4",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[4],     // MemoryInfo
        Component_DIP_Scale_BufInfo[4],         // BufferInfo
        &Component_DIP_Scale_InPort[4],         // pInPort
        Component_DIP_Scale_OutPort[4],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[4]         // DeviceInfo
    },
    {
        "DIP_S5",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[5],     // MemoryInfo
        Component_DIP_Scale_BufInfo[5],         // BufferInfo
        &Component_DIP_Scale_InPort[5],         // pInPort
        Component_DIP_Scale_OutPort[5],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[5]         // DeviceInfo
    },
    {
        "DIP_S6",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[6],     // MemoryInfo
        Component_DIP_Scale_BufInfo[6],         // BufferInfo
        &Component_DIP_Scale_InPort[6],         // pInPort
        Component_DIP_Scale_OutPort[6],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[6]         // DeviceInfo
    },
    {
        "DIP_S7",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[7],     // MemoryInfo
        Component_DIP_Scale_BufInfo[7],         // BufferInfo
        &Component_DIP_Scale_InPort[7],         // pInPort
        Component_DIP_Scale_OutPort[7],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[7]         // DeviceInfo
    },
    {
        "DIP_S8",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[8],     // MemoryInfo
        Component_DIP_Scale_BufInfo[8],         // BufferInfo
        &Component_DIP_Scale_InPort[8],         // pInPort
        Component_DIP_Scale_OutPort[8],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[8]         // DeviceInfo
    },
    {
        "DIP_S9",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[9],     // MemoryInfo
        Component_DIP_Scale_BufInfo[9],         // BufferInfo
        &Component_DIP_Scale_InPort[9],         // pInPort
        Component_DIP_Scale_OutPort[9],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[9]         // DeviceInfo
    },
    {
        "DIP_S10",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[10],    // MemoryInfo
        Component_DIP_Scale_BufInfo[10],        // BufferInfo
        &Component_DIP_Scale_InPort[10],        // pInPort
        Component_DIP_Scale_OutPort[10],        // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        &Component_DIP_S_AllocateMemory_LineOffset, // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        &Component_DIP_S_Close_NoBufRelease,    // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        &Component_DIP_S_UpdateBuffer_Combination,  // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[10]        // DeviceInfo
    },
    {
        "DIP_S11",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[11],    // MemoryInfo
        Component_DIP_Scale_BufInfo[11],        // BufferInfo
        &Component_DIP_Scale_InPort[11],        // pInPort
        Component_DIP_Scale_OutPort[11],        // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        &Component_DIP_S_AllocateMemory_LineOffset, // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        &Component_DIP_S_Close_NoBufRelease,    // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        &Component_DIP_S_UpdateBuffer_Combination,  // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[11]        // DeviceInfo
    },
    {
        "DIP_S12",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[12],    // MemoryInfo
        Component_DIP_Scale_BufInfo[12],        // BufferInfo
        &Component_DIP_Scale_InPort[12],        // pInPort
        Component_DIP_Scale_OutPort[12],        // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        &Component_DIP_S_AllocateMemory_LineOffset, // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        &Component_DIP_S_Close_NoBufRelease,    // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        &Component_DIP_S_UpdateBuffer_Combination,  // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[12]         // DeviceInfo
    },
    {
        "DIP_S13",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[13],    // MemoryInfo
        Component_DIP_Scale_BufInfo[13],        // BufferInfo
        &Component_DIP_Scale_InPort[13],        // pInPort
        Component_DIP_Scale_OutPort[13],        // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        &Component_DIP_S_AllocateMemory_LineOffset, // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        &Component_DIP_S_Close_NoBufRelease,    // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        &Component_DIP_S_UpdateBuffer_Combination,  // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[13]        // DeviceInfo
    },
    {
        "DIP_S14",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[14],     // MemoryInfo
        Component_DIP_Scale_BufInfo[14],         // BufferInfo
        &Component_DIP_Scale_InPort[14],         // pInPort
        Component_DIP_Scale_OutPort[14],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[14]         // DeviceInfo
    },
    {
        "DIP_S15",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_Scale_MemoryInfo[15],     // MemoryInfo
        Component_DIP_Scale_BufInfo[15],         // BufferInfo
        &Component_DIP_Scale_InPort[15],         // pInPort
        Component_DIP_Scale_OutPort[15],         // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Scale_EmptyBuffer,       // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_Scale_DevInfo[15]         // DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_DIP_Rotate[COMPONENT_DIP_R_MAX_NUM] =
{
    {
        "DIP_R0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_R_MemoryInfo[0],         // MemoryInfo
        Component_DIP_R_BufInfo[0],             // BufferInfo
        &Component_DIP_R_InPort[0],             // pInPort
        Component_DIP_R_OutPort[0],             // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Rotate_EmptyBuffer,      // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_R_DevInfo[0]             // DeviceInfo
    },
    {
        "DIP_R1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_R_MemoryInfo[1],         // MemoryInfo
        Component_DIP_R_BufInfo[1],             // BufferInfo
        &Component_DIP_R_InPort[1],             // pInPort
        Component_DIP_R_OutPort[1],             // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Rotate_EmptyBuffer,      // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_R_DevInfo[1]             // DeviceInfo
    },
    {
        "DIP_R2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_R_MemoryInfo[2],         // MemoryInfo
        Component_DIP_R_BufInfo[2],             // BufferInfo
        &Component_DIP_R_InPort[2],             // pInPort
        Component_DIP_R_OutPort[2],             // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_Rotate_EmptyBuffer,      // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_R_DevInfo[2]             // DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_DIP_ColorConvert[COMPONENT_DIP_CC_MAX_NUM] =
{
    {
        "DIP_CC0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_CC_MemoryInfo[0],        // MemoryInfo
        Component_DIP_CC_BufInfo[0],            // BufferInfo
        &Component_DIP_CC_InPort[0],            // pInPort
        Component_DIP_CC_OutPort[0],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_CC_EmptyBuffer,          // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_CC_DevInfo[0]            // DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_DIP_OSDB[COMPONENT_DIP_OSDB_MAX_NUM] =
{
    {
        "DIP_OSDB0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_DIP_OSDB_MemoryInfo[0],      // MemoryInfo
        Component_DIP_OSDB_BufInfo[0],          // BufferInfo
        &Component_DIP_OSDB_InPort[0],          // pInPort
        Component_DIP_OSDB_OutPort[0],          // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        &Component_DIP_InitDevice,              // pfInit
        NULL,                                   // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        &Component_DIP_UnInitDevice,            // pfUnInit
        NULL,                                   // pfClose
        Component_DIP_SetParam,                 // pfSetParameter
        Component_DIP_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        &Component_DIP_OSDB_EmptyBuffer,        // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_DIP_OSDB_DevInfo[0]          // DeviceInfo
    },
};

MMP_COMPONENT_PORT_INFO ComponentPort_DipS[COMPONENT_DIP_S_MAX_NUM] =
{
    {   // Port0
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[0],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port1
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[1],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port2
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[2],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port3
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[3],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port4
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[4],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port5
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[5],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port6
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[6],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port7
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[7],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port8
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[8],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port9
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[9],     // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port10
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[10],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port11
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[11],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port12
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[12],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port13
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[13],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port14
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[14],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port15
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_Scale_MemoryInfo[15],    // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
};

MMP_COMPONENT_PORT_INFO ComponentPort_DipR[COMPONENT_DIP_R_MAX_NUM] =
{
    {   // Port0
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_R_BufInfo[0],            // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port1
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_R_BufInfo[1],            // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
    {   // Port2
        PORT_INVALID,                           // State;
        NULL,                                   // pfOpen
        ComponentPort_DIP_Close,                // pfClose
        NULL,                                   // pfInit
        NULL,                                   // pfUnInit
        &Component_DIP_R_BufInfo[2],            // bufInfo
        NULL,                                   // pCurComponent
        NULL,                                   // PrevComponent
        NULL,                                   // NextComponent
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____Component_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : Component_DIP_S_AllocateMemory_LineOffset
//  Description : This function will assign memory of component to "Out" component
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_S_AllocateMemory_LineOffset(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDIP  =  (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_UBYTE                   byDipOutCompIdx = pDIP->fdAttr.scale.byOutCompIdx;
    MMP_COMPONENT_BASE          *pComp_Out = &Component_DIP_Scale[byDipOutCompIdx];
    MMP_COMPONENT_HANDLER_DIP   *pDIP_Out  = (MMP_COMPONENT_HANDLER_DIP *)pComp_Out->DeviceInfo;
    MMP_COMPONENT_BUFFER_INFO   *pBuf_Out = pComp_Out->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem_Out = pComp_Out->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_ULONG                   ulStartPoint_ShiftPixels = 0;
    MMP_ULONG                   ulStartAddr_ShiftBytes   = 0;
    MMP_ULONG                   i = 0;

    memcpy(pBuf, pBuf_Out, sizeof(MMP_COMPONENT_BUFFER_INFO));
    memcpy(pMem, pMem_Out, sizeof(MMP_COMPONENT_MEMORY_INFO));

    pDIP->inFormat  = pDIP_Out->inFormat;
    pDIP->outFormat = pDIP_Out->outFormat;

    ulStartPoint_ShiftPixels = (pDIP->stOutRect.ulY * pDIP->stOutRect.ulLineOffset) + pDIP->stOutRect.ulX;
    //UartSendTrace("ulStartPoint_ShiftPixels: %d * %d + %d\r\n", pDIP_2In1->stOutRect.ulY, pDIP_2In1->stOutRect.ulLineOffset, pDIP_2In1->stOutRect.ulX);

    ulStartAddr_ShiftBytes = (pDIP_Out->outFormat <= DIP_COMP_COLOR_FMT_YUV420_T16X32_VU) ?
                ((ulStartPoint_ShiftPixels) * 1) : ((ulStartPoint_ShiftPixels) * 2);

    for (i = 0; i < pMem_Out->ubBufNum; i++) {

        pBuf[i].ulBufAddr     = pBuf_Out[i].ulBufAddr + ulStartAddr_ShiftBytes;
        //pBuf_2In1[i].u64BufMiuAddr = pBuf[i].u64BufMiuAddr;
        //pBuf[i].u64BufPhyAddr = pBuf_Out[i].u64BufPhyAddr + ulStartAddr_ShiftBytes;

        //pBuf[i].bufctl.frm.ubBufUsage = 0;
        //pBuf[i].bufctl.frm.bBufUsing[0] = MMP_FALSE;
        //pBuf[i].ulTime = 0;
        //pBuf_2In1[i].ulSize = pBuf[i].ulSize;

        // For Out component, if data format is YUV420, set UV buffer address here because pComp_Out->pfEmptyBuffer will be not run.
        if (pDIP_Out->outFormat <= DIP_COMP_COLOR_FMT_YUV420_T16X32_VU) {
            pBuf_Out[i].ulBufAddr1 = pBuf_Out[i].ulBufAddr + pDIP_Out->stOutRect.ulW * pDIP_Out->stOutRect.ulH;
            pBuf_Out[i].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf_Out[i].ulBufAddr1);
            pBuf_Out[i].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf_Out[i].u64BufPhyAddr1);
        }

        //UartSendTrace("Alloc [%s] Addr[%x] (0x%x, 0x%x) Size[%d]\r\n", pComp->name, pBuf[i].ulBufAddr, pBuf[i].u64BufMiuAddr, pBuf[i].u64BufPhyAddr, pMem->ulBufSize);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_S_Close_NoBufRelease
//  Description : This function will set ubBufNum as 0 to avoid memory release.
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_S_Close_NoBufRelease(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    // Note: Please make sure in Component_Close_Script(), MMP_CompCtl_CloseComponent() is in front of MMP_CompCtl_FreeMemory().
    pMem->ubBufNum = 0;

    if (strcmp("DIP_S10", pComp->name) == 0) {
        //byBufferUpdateCase = 0;
        //byBufferUpdatePart = 0;
        g_byBufferUpdated[0][0] = 0;
    }
    else if (strcmp("DIP_S11", pComp->name) == 0) {
        //byBufferUpdateCase = 0;
        //byBufferUpdatePart = 1;
        g_byBufferUpdated[0][1] = 0;
    }
    else if (strcmp("DIP_S12", pComp->name) == 0) {
        //byBufferUpdateCase = 1;
        //byBufferUpdatePart = 0;
        g_byBufferUpdated[1][0] = 0;
    }
    else if (strcmp("DIP_S13", pComp->name) == 0) {
        //byBufferUpdateCase = 1;
        //byBufferUpdatePart = 1;
        g_byBufferUpdated[1][1] = 0;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_UpdateBuffer
//  Description : It will be called in run time to notice "Out" component Buffer done.
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_S_UpdateBuffer_Combination(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDIP =  (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_UBYTE byDipOutCompIdx;
    MMP_UBYTE byBufferUpdateCase;
    MMP_UBYTE byBufferUpdatePart;

    if (strcmp("DIP_S10", pComp->name) == 0) {
        byBufferUpdateCase = 0;
        byBufferUpdatePart = 0;
    }
    else if (strcmp("DIP_S11", pComp->name) == 0) {
        byBufferUpdateCase = 0;
        byBufferUpdatePart = 1;
    }
    else if (strcmp("DIP_S12", pComp->name) == 0) {
        byBufferUpdateCase = 1;
        byBufferUpdatePart = 0;
    }
    else if (strcmp("DIP_S13", pComp->name) == 0) {
        byBufferUpdateCase = 1;
        byBufferUpdatePart = 1;
    }
    else {
        UartSendTrace(FG_RED("Error!! Component_DIP_S_AllocateMemory_LineOffset(): Un-support component [%s]!!"), pComp->name);
        return MMP_ERR_NONE;
    }

    byDipOutCompIdx = pDIP->fdAttr.scale.byOutCompIdx;
    g_byBufferUpdated[byBufferUpdateCase][byBufferUpdatePart]++;

    #if 0 //debug
    {
        MMP_COMPONENT_BASE          *pComp_Out = &Component_DIP_Scale[byDipOutCompIdx];
        //MMP_COMPONENT_HANDLER_DIP   *pDIP_Out  = &Component_DIP_Scale_Handler[byDipOutCompIdx];
        MMP_COMPONENT_BUFFER_INFO   *pBuf_Out = pComp_Out->BufferInfo;
        MMP_COMPONENT_MEMORY_INFO   *pMem_Out = pComp_Out->MemoryInfo;

        UartSendTrace("Update [%s]: %d, %d (%d, %d)\r\n", pComp->name, pMem_Out->memctl.frm.ubWBufIndex,
                pMem_Out->memctl.frm.ubRBufIndex, pBuf_Out[pMem_Out->memctl.frm.ubWBufIndex].bufctl.frm.ubBufUsage, pBuf_Out[pMem_Out->memctl.frm.ubRBufIndex].bufctl.frm.ubBufUsage);
    }
    #endif

    //if ( 1 ) {
    if ( g_byBufferUpdated[byBufferUpdateCase][0] > 0 && g_byBufferUpdated[byBufferUpdateCase][1] > 0 ) {
        g_byBufferUpdated[byBufferUpdateCase][0] = 0;
        g_byBufferUpdated[byBufferUpdateCase][1] = 0;
        Component_DIP_StoreBufferDone( &Component_DIP_Scale[byDipOutCompIdx], NULL); // Trigger to preview / record "out buffer"
    }

    if ((g_byBufferUpdated[byBufferUpdateCase][0] > 2 && g_byBufferUpdated[byBufferUpdateCase][1] == 0) ||
        (g_byBufferUpdated[byBufferUpdateCase][1] > 2 && g_byBufferUpdated[byBufferUpdateCase][0] == 0)) {
        UartSendTrace(FG_YELLOW("RearCam_2In1 did not be updated in time!! (%d, %d)\r\n"), g_byBufferUpdated[byBufferUpdateCase][0], g_byBufferUpdated[byBufferUpdateCase][1]);
        Component_DIP_StoreBufferDone( &Component_DIP_Scale[byDipOutCompIdx], NULL); // Trigger to preview / record "out buffer"
        g_byBufferUpdated[byBufferUpdateCase][0] = 0;
        g_byBufferUpdated[byBufferUpdateCase][1] = 0;
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_UnInitDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    pComp->bByPass = MMP_FALSE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_S_SetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_S_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDipDev = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_COMPONENT_HANDLER_DIP   *pDIP = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pDIPMem = NULL;

    if (strcmp("DIP_S0", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[0];
        pDIPMem = &Component_DIP_Scale_Memory[0];
    }
    else if (strcmp("DIP_S1", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[1];
        pDIPMem = &Component_DIP_Scale_Memory[1];
    }
    else if (strcmp("DIP_S2", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[2];
        pDIPMem = &Component_DIP_Scale_Memory[2];
    }
    else if (strcmp("DIP_S3", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[3];
        pDIPMem = &Component_DIP_Scale_Memory[3];
    }
    else if (strcmp("DIP_S4", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[4];
        pDIPMem = &Component_DIP_Scale_Memory[4];
    }
    else if (strcmp("DIP_S5", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[5];
        pDIPMem = &Component_DIP_Scale_Memory[5];
    }
    else if (strcmp("DIP_S6", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[6];
        pDIPMem = &Component_DIP_Scale_Memory[6];
    }
    else if (strcmp("DIP_S7", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[7];
        pDIPMem = &Component_DIP_Scale_Memory[7];
    }
    else if (strcmp("DIP_S8", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[8];
        pDIPMem = &Component_DIP_Scale_Memory[8];
    }
    else if (strcmp("DIP_S9", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[9];
        pDIPMem = &Component_DIP_Scale_Memory[9];
    }
    else if (strcmp("DIP_S10", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[10];
        pDIPMem = &Component_DIP_Scale_Memory[10];
    }
    else if (strcmp("DIP_S11", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[11];
        pDIPMem = &Component_DIP_Scale_Memory[11];
    }
    else if (strcmp("DIP_S12", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[12];
        pDIPMem = &Component_DIP_Scale_Memory[12];
    }
    else if (strcmp("DIP_S13", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[13];
        pDIPMem = &Component_DIP_Scale_Memory[13];
    }
    else if (strcmp("DIP_S14", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[14];
        pDIPMem = &Component_DIP_Scale_Memory[14];
    }
    else if (strcmp("DIP_S15", pComp->name) == 0) {
        pDIP    = &Component_DIP_Scale_Handler[15];
        pDIPMem = &Component_DIP_Scale_Memory[15];
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case DIP_COMP_PARAM_SCL_IN_RES:
        memcpy(&pDIP->stInRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stInRect.ulX, pDIP->stInRect.ulY, pDIP->stInRect.ulW, pDIP->stInRect.ulH);
        if (pDIP->stInRect.ulW == 0 || pDIP->stInRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] In Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_SCL_CROP_RES:
        memcpy(&pDIP->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        memcpy(&pDipDev->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT)); // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Crop Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stCropRect.ulX, pDIP->stCropRect.ulY, pDIP->stCropRect.ulW, pDIP->stCropRect.ulH);
        if (pDIP->stCropRect.ulW == 0 || pDIP->stCropRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] Crop Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_SCL_OUT_RES:
        memcpy(&pDIP->stOutRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stOutRect.ulX, pDIP->stOutRect.ulY, pDIP->stOutRect.ulW, pDIP->stOutRect.ulH);
        if (pDIP->stOutRect.ulW == 0 || pDIP->stOutRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] Out Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_SCL_IN_FMT:
        pDIP->inFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Fmt %d\r\n", pComp->name, pDIP->inFormat);
        break;
    case DIP_COMP_PARAM_SCL_OUT_FMT:
        pDIP->outFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Fmt %d\r\n", pComp->name, pDIP->outFormat);
        break;
    case DIP_COMP_PARAM_SCL_BUF_COUNT:
        pDIPMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Count %d\r\n", pComp->name, pDIPMem->ubBufNum);
        break;
    case DIP_COMP_PARAM_SCL_BUF_SIZE:
        pDIPMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Size %d\r\n", pComp->name, pDIPMem->ulBufSize);
        break;
    case DIP_COMP_PARAM_SCL_OSDB_EN:
        pDIP->fdAttr.scale.bOsdb = *(MMP_BOOL*)pParam;
        pDipDev->fdAttr.scale.bOsdb = *(MMP_BOOL*)pParam; // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update OSDB Enable %d\r\n", pComp->name, pDipDev->fdAttr.scale.bOsdb);
        break;
    case DIP_COMP_PARAM_SCL_MIRROR_EN:
        pDIP->fdAttr.scale.bMirror = *(MMP_BOOL*)pParam;
        pDipDev->fdAttr.scale.bMirror = *(MMP_BOOL*)pParam; // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Mirror Enable %d\r\n", pComp->name, pDIP->fdAttr.scale.bMirror);
        break;
    case DIP_COMP_PARAM_SCL_FLIP_EN:
        pDIP->fdAttr.scale.bFlip = *(MMP_BOOL*)pParam;
        pDipDev->fdAttr.scale.bFlip = *(MMP_BOOL*)pParam; // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Flip Enable %d\r\n", pComp->name, pDIP->fdAttr.scale.bFlip);
        break;
    case DIP_COMP_PARAM_SCL_BYPASS:
        pComp->bByPass = *(MMP_BOOL*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Bypass %d\r\n", pComp->name, pComp->bByPass);
        break;
    case DIP_COMP_PARAM_SCL_LINE_BIAS:
        pDIP->usLineBias = *(MMP_USHORT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Line Bias %d\r\n", pComp->name, pDIP->usLineBias);
        break;
    case DIP_COMP_PARAM_SCL_BUF_BIAS:
        pDIPMem->ulBufBias = *(MMP_ULONG*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Bias %d\r\n", pComp->name, pDIPMem->ulBufBias);
        break;
    case DIP_COMP_PARAM_SCL_OUT_COMP_IDX:
        pDIP->fdAttr.scale.byOutCompIdx = *(MMP_UBYTE*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Component Index %d\r\n", pComp->name, pDIP->fdAttr.scale.byOutCompIdx);
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_S_GetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_S_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP       *pDipDev = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;

    if ((strcmp("DIP_S0", pComp->name) == 0) ||
        (strcmp("DIP_S1", pComp->name) == 0) ||
        (strcmp("DIP_S2", pComp->name) == 0) ||
        (strcmp("DIP_S3", pComp->name) == 0) ||
        (strcmp("DIP_S4", pComp->name) == 0) ||
        (strcmp("DIP_S5", pComp->name) == 0) ||
        (strcmp("DIP_S6", pComp->name) == 0) ||
        (strcmp("DIP_S7", pComp->name) == 0) ||
        (strcmp("DIP_S8", pComp->name) == 0) ||
        (strcmp("DIP_S9", pComp->name) == 0) ||
        (strcmp("DIP_S10", pComp->name) == 0) ||
        (strcmp("DIP_S11", pComp->name) == 0) ||
        (strcmp("DIP_S12", pComp->name) == 0) ||
        (strcmp("DIP_S13", pComp->name) == 0) ||
        (strcmp("DIP_S14", pComp->name) == 0) ||
        (strcmp("DIP_S15", pComp->name) == 0)) {
        // NOP
    }
    else {
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case DIP_COMP_PARAM_SCL_RBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubRBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_SCL_WBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_SCL_IN_RES:
        memcpy((DIP_COMP_RECT*)pParam, &pDipDev->stInRect, sizeof(DIP_COMP_RECT));
        break;
    case DIP_COMP_PARAM_SCL_CROP_RES:
        memcpy((DIP_COMP_RECT*)pParam, &pDipDev->stCropRect, sizeof(DIP_COMP_RECT));
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_R_SetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_R_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDipDev = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_COMPONENT_HANDLER_DIP   *pDIP = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pDIPMem = NULL;

    if (strcmp("DIP_R0", pComp->name) == 0) {
        pDIP    = &Component_DIP_R_Handler[0];
        pDIPMem = &Component_DIP_R_Memory[0];
    }
    else if (strcmp("DIP_R1", pComp->name) == 0) {
        pDIP    = &Component_DIP_R_Handler[1];
        pDIPMem = &Component_DIP_R_Memory[1];
    }
    else if (strcmp("DIP_R2", pComp->name) == 0) {
        pDIP    = &Component_DIP_R_Handler[2];
        pDIPMem = &Component_DIP_R_Memory[2];
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case DIP_COMP_PARAM_ROT_IN_RES:
        memcpy(&pDIP->stInRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stInRect.ulX, pDIP->stInRect.ulY, pDIP->stInRect.ulW, pDIP->stInRect.ulH);
        if (pDIP->stInRect.ulW == 0 || pDIP->stInRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] In Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_ROT_CROP_RES:
        memcpy(&pDIP->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        memcpy(&pDipDev->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT)); // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Crop Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stCropRect.ulX, pDIP->stCropRect.ulY, pDIP->stCropRect.ulW, pDIP->stCropRect.ulH);
        if (pDIP->stCropRect.ulW == 0 || pDIP->stCropRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] Crop Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_ROT_OUT_RES:
        memcpy(&pDIP->stOutRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stOutRect.ulX, pDIP->stOutRect.ulY, pDIP->stOutRect.ulW, pDIP->stOutRect.ulH);
        if (pDIP->stOutRect.ulW == 0 || pDIP->stOutRect.ulH == 0) {
            COMPONENT_DIP_DBG_ERR(1, "[%s] Out Resolution Wrong\r\n", pComp->name);
        }
        break;
    case DIP_COMP_PARAM_ROT_IN_FMT:
        pDIP->inFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Fmt %d\r\n", pComp->name, pDIP->inFormat);
        break;
    case DIP_COMP_PARAM_ROT_OUT_FMT:
        pDIP->outFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Fmt %d\r\n", pComp->name, pDIP->outFormat);
        break;
    case DIP_COMP_PARAM_ROT_BUF_COUNT:
        pDIPMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Count %d\r\n", pComp->name, pDIPMem->ubBufNum);
        break;
    case DIP_COMP_PARAM_ROT_BUF_SIZE:
        pDIPMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Size %d\r\n", pComp->name, pDIPMem->ulBufSize);
        break;
    case DIP_COMP_PARAM_ROT_BYPASS:
        pComp->bByPass = *(MMP_BOOL*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Bypass %d\r\n", pComp->name, pComp->bByPass);
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_R_GetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_R_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP       *pDipDev = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;

    if ((strcmp("DIP_R0", pComp->name) == 0) ||
        (strcmp("DIP_R1", pComp->name) == 0) ||
        (strcmp("DIP_R2", pComp->name) == 0)) {
        // NOP
    }
    else {
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case DIP_COMP_PARAM_ROT_RBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubRBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_ROT_WBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_ROT_IN_RES:
        memcpy((DIP_COMP_RECT*)pParam, &pDipDev->stInRect, sizeof(DIP_COMP_RECT));
        break;
    case DIP_COMP_PARAM_ROT_CROP_RES:
        memcpy((DIP_COMP_RECT*)pParam, &pDipDev->stCropRect, sizeof(DIP_COMP_RECT));
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_OSDB_SetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_OSDB_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDipDev = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    MMP_COMPONENT_HANDLER_DIP   *pDIP = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pDIPMem = NULL;

    if (strcmp("DIP_OSDB0", pComp->name) == 0) {
        pDIP    = &Component_DIP_OSDB_Handler[0];
        pDIPMem = &Component_DIP_OSDB_Memory[0];
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case DIP_COMP_PARAM_OSDB_EN:
        pDIP->fdAttr.osdb.bOsdb = *(MMP_BOOL*)pParam;
        pDipDev->fdAttr.osdb.bOsdb = *(MMP_BOOL*)pParam; // For RunTime Change
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update OSDB Enable %d\r\n", pComp->name, pDipDev->fdAttr.osdb.bOsdb);
        break;
    case DIP_COMP_PARAM_OSDB_IN_RES:
        memcpy(&pDIP->stInRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stInRect.ulX, pDIP->stInRect.ulY, pDIP->stInRect.ulW, pDIP->stInRect.ulH);
        break;
    case DIP_COMP_PARAM_OSDB_CROP_RES:
        memcpy(&pDIP->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Crop Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stCropRect.ulX, pDIP->stCropRect.ulY, pDIP->stCropRect.ulW, pDIP->stCropRect.ulH);
        break;
    case DIP_COMP_PARAM_OSDB_OUT_RES:
        memcpy(&pDIP->stOutRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stOutRect.ulX, pDIP->stOutRect.ulY, pDIP->stOutRect.ulW, pDIP->stOutRect.ulH);
        break;
    case DIP_COMP_PARAM_OSDB_IN_FMT:
        pDIP->inFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Fmt %d\r\n", pComp->name, pDIP->inFormat);
        break;
    case DIP_COMP_PARAM_OSDB_OUT_FMT:
        pDIP->outFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Fmt %d\r\n", pComp->name, pDIP->outFormat);
        break;
    case DIP_COMP_PARAM_OSDB_BUF_COUNT:
        pDIPMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Count %d\r\n", pComp->name, pDIPMem->ubBufNum);
        break;
    case DIP_COMP_PARAM_OSDB_BUF_SIZE:
        pDIPMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Size %d\r\n", pComp->name, pDIPMem->ulBufSize);
        break;
    case DIP_COMP_PARAM_OSDB_BYPASS:
        pComp->bByPass = *(MMP_BOOL*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Bypass %d\r\n", pComp->name, pComp->bByPass);
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_OSDB_GetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_OSDB_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;

    if ((strcmp("DIP_OSDB0", pComp->name) == 0)) {
        // NOP
    }
    else {
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case DIP_COMP_PARAM_OSDB_RBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubRBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_OSDB_WBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr;
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_CC_SetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_CC_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_DIP   *pDIP = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pDIPMem = NULL;

    if (strcmp("DIP_CC0", pComp->name) == 0) {
        pDIP    = &Component_DIP_CC_Handler[0];
        pDIPMem = &Component_DIP_CC_Memory[0];
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case DIP_COMP_PARAM_CC_IN_RES:
        memcpy(&pDIP->stInRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stInRect.ulX, pDIP->stInRect.ulY, pDIP->stInRect.ulW, pDIP->stInRect.ulH);
        break;
    case DIP_COMP_PARAM_CC_CROP_RES:
        memcpy(&pDIP->stCropRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Crop Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stCropRect.ulX, pDIP->stCropRect.ulY, pDIP->stCropRect.ulW, pDIP->stCropRect.ulH);
        break;
    case DIP_COMP_PARAM_CC_OUT_RES:
        memcpy(&pDIP->stOutRect, (DIP_COMP_RECT*)pParam, sizeof(DIP_COMP_RECT));
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pDIP->stOutRect.ulX, pDIP->stOutRect.ulY, pDIP->stOutRect.ulW, pDIP->stOutRect.ulH);
        break;
    case DIP_COMP_PARAM_CC_IN_FMT:
        pDIP->inFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update In Fmt %d\r\n", pComp->name, pDIP->inFormat);
        break;
    case DIP_COMP_PARAM_CC_OUT_FMT:
        pDIP->outFormat = *(DIP_COMP_COLOR_FMT*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Out Fmt %d\r\n", pComp->name, pDIP->outFormat);
        break;
    case DIP_COMP_PARAM_CC_BUF_COUNT:
        pDIPMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Count %d\r\n", pComp->name, pDIPMem->ubBufNum);
        break;
    case DIP_COMP_PARAM_CC_BUF_SIZE:
        pDIPMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Buf Size %d\r\n", pComp->name, pDIPMem->ulBufSize);
        break;
    case DIP_COMP_PARAM_CC_BYPASS:
        pComp->bByPass = *(MMP_BOOL*)pParam;
        COMPONENT_DIP_DBG_MSG(1, "[%s] Update Bypass %d\r\n", pComp->name, pComp->bByPass);
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_CC_GetParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_DIP_CC_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;

    if ((strcmp("DIP_CC0", pComp->name) == 0)) {
        // NOP
    }
    else {
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case DIP_COMP_PARAM_CC_RBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubRBufIndex].ulBufAddr;
        break;
    case DIP_COMP_PARAM_CC_WBUF_ADDR:
        *(MMP_ULONG*)pParam = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr;
        break;
    default:
        COMPONENT_DIP_DBG_ERR(1, "[%s] UnSupport DIP Param Type\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if ((strcmp("DIP_S0", pComp->name) == 0) ||
        (strcmp("DIP_S1", pComp->name) == 0) ||
        (strcmp("DIP_S2", pComp->name) == 0) ||
        (strcmp("DIP_S3", pComp->name) == 0) ||
        (strcmp("DIP_S4", pComp->name) == 0) ||
        (strcmp("DIP_S5", pComp->name) == 0) ||
        (strcmp("DIP_S6", pComp->name) == 0) ||
        (strcmp("DIP_S7", pComp->name) == 0) ||
        (strcmp("DIP_S8", pComp->name) == 0) ||
        (strcmp("DIP_S9", pComp->name) == 0) ||
        (strcmp("DIP_S10", pComp->name) == 0) ||
        (strcmp("DIP_S11", pComp->name) == 0) ||
        (strcmp("DIP_S12", pComp->name) == 0) ||
        (strcmp("DIP_S13", pComp->name) == 0) ||
        (strcmp("DIP_S14", pComp->name) == 0) ||
        (strcmp("DIP_S15", pComp->name) == 0)) {
        return Component_DIP_S_SetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_R0", pComp->name) == 0) ||
        (strcmp("DIP_R1", pComp->name) == 0) ||
        (strcmp("DIP_R2", pComp->name) == 0)) {
        return Component_DIP_R_SetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_OSDB0", pComp->name) == 0)) {
        return Component_DIP_OSDB_SetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_CC0", pComp->name) == 0)) {
        return Component_DIP_CC_SetParam(handler, type, pParam);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if ((strcmp("DIP_S0", pComp->name) == 0) ||
        (strcmp("DIP_S1", pComp->name) == 0) ||
        (strcmp("DIP_S2", pComp->name) == 0) ||
        (strcmp("DIP_S3", pComp->name) == 0) ||
        (strcmp("DIP_S4", pComp->name) == 0) ||
        (strcmp("DIP_S5", pComp->name) == 0) ||
        (strcmp("DIP_S6", pComp->name) == 0) ||
        (strcmp("DIP_S7", pComp->name) == 0) ||
        (strcmp("DIP_S8", pComp->name) == 0) ||
        (strcmp("DIP_S9", pComp->name) == 0) ||
        (strcmp("DIP_S10", pComp->name) == 0) ||
        (strcmp("DIP_S11", pComp->name) == 0) ||
        (strcmp("DIP_S12", pComp->name) == 0) ||
        (strcmp("DIP_S13", pComp->name) == 0) ||
        (strcmp("DIP_S14", pComp->name) == 0) ||
        (strcmp("DIP_S15", pComp->name) == 0)) {
        return Component_DIP_S_GetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_R0", pComp->name) == 0) ||
        (strcmp("DIP_R1", pComp->name) == 0) ||
        (strcmp("DIP_R2", pComp->name) == 0)) {
        return Component_DIP_R_GetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_OSDB0", pComp->name) == 0)) {
        return Component_DIP_OSDB_GetParam(handler, type, pParam);
    }
    if ((strcmp("DIP_CC0", pComp->name) == 0)) {
        return Component_DIP_CC_GetParam(handler, type, pParam);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_EmptyBufferDone
//  Description :
//------------------------------------------------------------------------------
static void Component_DIP_StoreBufferDone(MMP_ULONG param1, MMP_ULONG param2)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)param1;

    MMP_CompCtl_StoreBufferDone(pComp, 0, NULL);
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_CallBack
//  Description :
//------------------------------------------------------------------------------
static void Component_DIP_CallBack(void* param1, void* param2)
{
    Component_DIP_StoreBufferDone((MMP_ULONG)param1, (MMP_ULONG)param2);
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_Move_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_Move_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_ULONG                       nOffsetY = 0, nOffsetC = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_DIP       *pDip = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    DIP_COMP_RECT                   *pInRect;
    DIP_COMP_RECT                   *pCropRect;
    DIP_COMP_RECT                   *pOutRect;
    DIPCTL_ATTR_t                   DipCtlAttr;
    DIPCTL_BUF_ATTR_t               tSrcBufAttr, tDestBufAttr;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pInRect      = &pDip->stInRect;
    pCropRect    = &pDip->stCropRect;
    pOutRect     = &pDip->stOutRect;

    tSrcBufAttr.nWidth          = pCropRect->ulW;
    tSrcBufAttr.nHeight         = pCropRect->ulH;
    tSrcBufAttr.nLineOffset     = pInRect->ulW;
    tSrcBufAttr.eColorFormat    = DIP_COMP_COLOR_MAP(pDip->inFormat);

    tDestBufAttr.nWidth         = pOutRect->ulW;
    tDestBufAttr.nHeight        = pOutRect->ulH;
    tDestBufAttr.nLineOffset    = pOutRect->ulW;
    tDestBufAttr.eColorFormat   = DIP_COMP_COLOR_MAP(pDip->outFormat);

    switch (pDip->inFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetC = (pCropRect->ulY * pInRect->ulW) / 2 + pCropRect->ulX;
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = pComp->pInPort->bufInfo.ulBufAddr1 + nOffsetC + pComp->pInPort->bufInfo.ulBufBias*3/2;
            break;
        default:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetY *= 2; // YUV422
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = 0;
            break;
    }

    switch (pDip->outFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetC = pOutRect->ulW * pOutRect->ulH;
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + nOffsetC;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 + pMem->ulBufBias*3/2;
            break;
        default:
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = 0;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = 0;
            break;
    }

    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr2       = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr2   = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr2   = 0;

    pBuf[pMem->memctl.frm.ubWBufIndex].ulTime = pComp->pInPort->bufInfo.ulTime;

    memcpy(&DipCtlAttr.tSrcBufAttr, &tSrcBufAttr, sizeof(DIPCTL_BUF_ATTR_t));
    memcpy(&DipCtlAttr.tDestBufAttr, &tDestBufAttr, sizeof(DIPCTL_BUF_ATTR_t));

    DipCtlAttr.bMirror  = pDip->fdAttr.move.bMirror;
    DipCtlAttr.bFlip    = pDip->fdAttr.move.bFlip;
    DipCtlAttr.bOsdb    = pDip->fdAttr.move.bOsdb;

    if (dip_mdl_img_scaling(&DipCtlAttr, Component_DIP_CallBack, (void*)pComp) == DIP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] Move Fail\r\n", pComp->name);
        return MMP_COMPONENT_ERR_CALL;
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_Rotate_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_Rotate_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_ULONG                       nOffsetY = 0, nOffsetC = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BASE              *pPrevComp = (MMP_COMPONENT_BASE *)pComp->pInPort->PrevComponent;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_DIP       *pDip = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    DIP_COMP_RECT                   *pInRect;
    DIP_COMP_RECT                   *pCropRect;
    DIP_COMP_RECT                   *pOutRect;
    DIPCTL_ATTR_t                   DipCtlAttr;
    DIPCTL_BUF_ATTR_t               tSrcBufAttr, tDestBufAttr;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pInRect      = &pDip->stInRect;
    pCropRect    = &pDip->stCropRect;
    pOutRect     = &pDip->stOutRect;

    tSrcBufAttr.nWidth          = pCropRect->ulW;
    tSrcBufAttr.nHeight         = pCropRect->ulH;
    tSrcBufAttr.nLineOffset     = pInRect->ulW;
    tSrcBufAttr.eColorFormat    = DIP_COMP_COLOR_MAP(pDip->inFormat);

    tDestBufAttr.nWidth         = pOutRect->ulW;
    tDestBufAttr.nHeight        = pOutRect->ulH;
    tDestBufAttr.nLineOffset    = pOutRect->ulW;
    tDestBufAttr.eColorFormat   = DIP_COMP_COLOR_MAP(pDip->outFormat);

    switch (pDip->inFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetC = (pCropRect->ulY * pInRect->ulW) / 2 + pCropRect->ulX;
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = pComp->pInPort->bufInfo.ulBufAddr1 + nOffsetC + pComp->pInPort->bufInfo.ulBufBias*3/2;
            break;
        default:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetY *= 2; // YUV422
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = 0;
            break;
    }

    switch (pDip->outFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetC = pOutRect->ulW * pOutRect->ulH;
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + nOffsetC;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 + pMem->ulBufBias*3/2;
            break;
        default:
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = 0;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = 0;
            break;
    }

    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr2       = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr2   = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr2   = 0;

    pBuf[pMem->memctl.frm.ubWBufIndex].ulTime = pComp->pInPort->bufInfo.ulTime;

    memcpy(&DipCtlAttr.tSrcBufAttr, &tSrcBufAttr, sizeof(DIPCTL_BUF_ATTR_t));
    memcpy(&DipCtlAttr.tDestBufAttr, &tDestBufAttr, sizeof(DIPCTL_BUF_ATTR_t));

    DipCtlAttr.bMirror  = 0; // not support rotate + mirror
    DipCtlAttr.bFlip    = 0; // not support rotate + flip
    DipCtlAttr.bOsdb    = 0; // not support rotate + osdb
    DipCtlAttr.eRotDegree = DIP_COMP_ROT_DEG_MAP(pDip->fdAttr.rotate.RotDegree);

    if (dip_mdl_img_rotate(&DipCtlAttr, Component_DIP_CallBack, (void*)pComp) == DIP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] Rotate Fail\r\n", pComp->name);
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        return MMP_COMPONENT_ERR_CALL;
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_Scale_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_Scale_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_ULONG                       nOffsetY = 0, nOffsetC = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_DIP       *pDip =  (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    DIP_COMP_RECT                   *pInRect;
    DIP_COMP_RECT                   *pCropRect;
    DIP_COMP_RECT                   *pOutRect;
    DIPCTL_ATTR_t                   DipCtlAttr;
    DIPCTL_BUF_ATTR_t               tSrcBufAttr, tDestBufAttr;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pInRect      = &pDip->stInRect;
    pCropRect    = &pDip->stCropRect;
    pOutRect     = &pDip->stOutRect;

    tSrcBufAttr.nWidth          = pCropRect->ulW;
    tSrcBufAttr.nHeight         = pCropRect->ulH;
    tSrcBufAttr.nLineOffset     = pInRect->ulW;
    tSrcBufAttr.eColorFormat    = DIP_COMP_COLOR_MAP(pDip->inFormat);

    tDestBufAttr.nWidth         = pOutRect->ulW;
    tDestBufAttr.nHeight        = pOutRect->ulH;
    tDestBufAttr.nLineOffset    = pOutRect->ulLineOffset; //pOutRect->ulW;
    tDestBufAttr.eColorFormat   = DIP_COMP_COLOR_MAP(pDip->outFormat);

    switch (pDip->inFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetC = (pCropRect->ulY * pInRect->ulW) / 2 + pCropRect->ulX;
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = pComp->pInPort->bufInfo.ulBufAddr1 + nOffsetC + pComp->pInPort->bufInfo.ulBufBias*3/2;
            break;
        default:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetY *= 2; // YUV422
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = 0;
            break;
    }

    switch (pDip->outFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            if ( pOutRect->ulLineOffset > pOutRect->ulW ) {
                nOffsetC = pOutRect->ulLineOffset * pOutRect->ulH;
            }
            else {
                nOffsetC = pOutRect->ulW * pOutRect->ulH;
            }
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + nOffsetC;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 + pMem->ulBufBias*3/2;
            break;
        default:
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = 0;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = 0;
            break;
    }

    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr2       = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr2   = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr2   = 0;

    pBuf[pMem->memctl.frm.ubWBufIndex].ulTime = pComp->pInPort->bufInfo.ulTime;

    if (pDip->fdAttr.scale.bOsdb) {
        memcpy(&(pBuf[pMem->memctl.frm.ubWBufIndex].stDateTime), MMPF_Icon_GetDateTimeAttr(1/*MMP_STICKER_ID_1*/), sizeof(AUTL_DATETIME));
    }

    memcpy(&DipCtlAttr.tSrcBufAttr, &tSrcBufAttr, sizeof(DIPCTL_BUF_ATTR_t));
    memcpy(&DipCtlAttr.tDestBufAttr, &tDestBufAttr, sizeof(DIPCTL_BUF_ATTR_t));

    DipCtlAttr.bMirror  = pDip->fdAttr.scale.bMirror;
    DipCtlAttr.bFlip    = pDip->fdAttr.scale.bFlip;
    DipCtlAttr.bOsdb    = pDip->fdAttr.scale.bOsdb;

    if (dip_mdl_img_scaling(&DipCtlAttr, Component_DIP_CallBack, (void*)pComp) == DIP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] Scale Fail\r\n", pComp->name);
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        return MMP_COMPONENT_ERR_CALL;
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_OSDB_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_OSDB_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_ULONG                       nOffsetY = 0, nOffsetC = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_DIP       *pDip = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    DIP_COMP_RECT                   *pInRect;
    DIP_COMP_RECT                   *pCropRect;
    DIP_COMP_RECT                   *pOutRect;
    DIPCTL_ATTR_t                   DipCtlAttr;
    DIPCTL_BUF_ATTR_t               tSrcBufAttr, tDestBufAttr;
    DIP_ERR_CODE_e                  eDipErr = DIP_ERR_NONE;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pInRect      = &pDip->stInRect;
    pCropRect    = &pDip->stCropRect;
    pOutRect     = &pDip->stOutRect;

    tSrcBufAttr.nWidth          = pCropRect->ulW;
    tSrcBufAttr.nHeight         = pCropRect->ulH;
    tSrcBufAttr.nLineOffset     = pInRect->ulW;
    tSrcBufAttr.eColorFormat    = DIP_COMP_COLOR_MAP(pDip->inFormat);

    tDestBufAttr.nWidth         = pOutRect->ulW;
    tDestBufAttr.nHeight        = pOutRect->ulH;
    tDestBufAttr.nLineOffset    = pOutRect->ulW;
    tDestBufAttr.eColorFormat   = DIP_COMP_COLOR_MAP(pDip->outFormat);

    switch (pDip->inFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetC = (pCropRect->ulY * pInRect->ulW) / 2 + pCropRect->ulX;
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = pComp->pInPort->bufInfo.ulBufAddr1 + nOffsetC + pComp->pInPort->bufInfo.ulBufBias*3/2;
            break;
        default:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetY *= 2; // YUV422
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = 0;
            break;
    }

    switch (pDip->outFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetC = pOutRect->ulW * pOutRect->ulH;
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + nOffsetC;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 + pMem->ulBufBias*3/2;
            break;
        default:
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = 0;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = 0;
            break;
    }

    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr2       = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr2   = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr2   = 0;

    pBuf[pMem->memctl.frm.ubWBufIndex].ulTime = pComp->pInPort->bufInfo.ulTime;

    if (pDip->fdAttr.osdb.bOsdb) {
        memcpy(&(pBuf[pMem->memctl.frm.ubWBufIndex].stDateTime), MMPF_Icon_GetDateTimeAttr(1/*MMP_STICKER_ID_1*/), sizeof(AUTL_DATETIME));
    }

    memcpy(&DipCtlAttr.tSrcBufAttr, &tSrcBufAttr, sizeof(DIPCTL_BUF_ATTR_t));
    memcpy(&DipCtlAttr.tDestBufAttr, &tDestBufAttr, sizeof(DIPCTL_BUF_ATTR_t));

    DipCtlAttr.bMirror  = 0; //pDip->bMirror;
    DipCtlAttr.bFlip    = 0; //pDip->bFlip;
    DipCtlAttr.bOsdb    = pDip->fdAttr.osdb.bOsdb;

    if (dip_mdl_img_osdb(&DipCtlAttr, Component_DIP_CallBack, (void*)pComp) == DIP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] OSDB Fail\r\n", pComp->name);
        return MMP_COMPONENT_ERR_CALL;
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_DIP_CC_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_DIP_CC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_ULONG                       nOffsetY = 0, nOffsetC = 0;
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_DIP       *pDip = (MMP_COMPONENT_HANDLER_DIP *)pComp->DeviceInfo;
    DIP_COMP_RECT                   *pInRect;
    DIP_COMP_RECT                   *pCropRect;
    DIP_COMP_RECT                   *pOutRect;
    DIPCTL_ATTR_t                   DipCtlAttr;
    DIPCTL_BUF_ATTR_t               tSrcBufAttr, tDestBufAttr;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pInRect      = &pDip->stInRect;
    pCropRect    = &pDip->stCropRect;
    pOutRect     = &pDip->stOutRect;

    tSrcBufAttr.nWidth          = pCropRect->ulW;
    tSrcBufAttr.nHeight         = pCropRect->ulH;
    tSrcBufAttr.nLineOffset     = pInRect->ulW;
    tSrcBufAttr.eColorFormat    = DIP_COMP_COLOR_MAP(pDip->inFormat);

    tDestBufAttr.nWidth         = pOutRect->ulW;
    tDestBufAttr.nHeight        = pOutRect->ulH;
    tDestBufAttr.nLineOffset    = pOutRect->ulW;
    tDestBufAttr.eColorFormat   = DIP_COMP_COLOR_MAP(pDip->outFormat);

    switch (pDip->inFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetC = (pCropRect->ulY * pInRect->ulW) / 2 + pCropRect->ulX;
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY + pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = pComp->pInPort->bufInfo.ulBufAddr1 + nOffsetC + pComp->pInPort->bufInfo.ulBufBias*3/2;
            break;
        default:
            nOffsetY = (pCropRect->ulY * pInRect->ulW) + pCropRect->ulX;
            nOffsetY *= 2; // YUV422
            tSrcBufAttr.nBaseAddrY = pComp->pInPort->bufInfo.ulBufAddr + nOffsetY +pComp->pInPort->bufInfo.ulBufBias;
            tSrcBufAttr.nBaseAddrC = 0;
            break;
    }

    switch (pDip->outFormat) {
        case DIP_COMP_COLOR_FMT_YUV420_UV:
        case DIP_COMP_COLOR_FMT_YUV420_VU:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_UV:
        case DIP_COMP_COLOR_FMT_YUV420_T16X32_VU:
            nOffsetC = pOutRect->ulW * pOutRect->ulH;
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + nOffsetC;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 + pMem->ulBufBias*3/2;
            break;
        default:
            pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1 = 0;
            tDestBufAttr.nBaseAddrY = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr + pMem->ulBufBias;
            tDestBufAttr.nBaseAddrC = 0;
            break;
    }

    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1   = (MMP_ULONG)MsVA2PA((void*)pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr1   = HalUtilPHY2MIUAddr((MMP_ULONG)pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr1);
    pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr2       = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufPhyAddr2   = 0;
    pBuf[pMem->memctl.frm.ubWBufIndex].u64BufMiuAddr2   = 0;

    pBuf[pMem->memctl.frm.ubWBufIndex].ulTime = pComp->pInPort->bufInfo.ulTime;

    memcpy(&DipCtlAttr.tSrcBufAttr, &tSrcBufAttr, sizeof(DIPCTL_BUF_ATTR_t));
    memcpy(&DipCtlAttr.tDestBufAttr, &tDestBufAttr, sizeof(DIPCTL_BUF_ATTR_t));

    DipCtlAttr.bMirror  = pDip->fdAttr.cc.bMirror;
    DipCtlAttr.bFlip    = pDip->fdAttr.cc.bFlip;
    DipCtlAttr.bOsdb    = 0;//pDip->fdAttr.cc.bOsdb;

    if (dip_mdl_img_color_convert(&DipCtlAttr, Component_DIP_CallBack, (void*)pComp) == DIP_ERR_NONE) {
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_DIP_DBG_ERR(1, "[%s] CC Fail\r\n", pComp->name);
        return MMP_COMPONENT_ERR_CALL;
    }
}

#if 0
void ____Port_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : ComponentPort_DIP_Close
//  Description :
//------------------------------------------------------------------------------
MMP_ERR ComponentPort_DIP_Close(void *handler)
{
    MMP_ULONG                   ulIdx = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pComp == NULL) {
        COMPONENT_DIP_DBG_ERR(1, FG_RED("Component is NULL\r\n"));
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    pMem->memctl.frm.ubWBufIndex = 0;
    pMem->memctl.frm.ubRBufIndex = 0;

    if (pMem->ubBufNum) {
        for (ulIdx = 0; ulIdx < pMem->ubBufNum; ulIdx++) {
            pBuf[ulIdx].bufctl.frm.ubBufUsage = 0;
            memset(&pBuf[ulIdx].bufctl.frm.bBufUsing[0], 0x00, pComp->ubOutputPortNum);
            pBuf[ulIdx].ulTime = 0xFFFF0000;
        }
    }

    COMPONENT_DIP_DBG_MSG(0, FG_YELLOW("[%s] PortClose for Flush!\r\n"), pComp->name);

    return MMP_ERR_NONE;
}

#if 0
void ____Customized_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : Component_RearCam_2In1_Enable
//  Description :
//------------------------------------------------------------------------------
void Component_RearCam_2In1_Enable( MMP_BOOL bEnable )
{
    bComponent_RearCam_2In1 = bEnable;
}

//------------------------------------------------------------------------------
//  Function    : Component_RearCam_2In1_Status
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL Component_RearCam_2In1_Status( void )
{
    return bComponent_RearCam_2In1;
}


