//------------------------------------------------------------------------------
//
//  File        : component_jpemgr.c
//  Description : Source file of JPE merger component configuration
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
#include "component_jpemgr.h"
#include "mmpf_jpeg_enc.h"
#include "mmpf_ringbuf.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_JPEMGR_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_JPEMGR_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_JPEMGR_InitDevice(void *handler);
MMP_ERR Component_JPEMGR_UnInitDevice(void *handler);
MMP_ERR Component_JPEMGR_OpenDevice(void *handler);
MMP_ERR Component_JPEMGR_CloseDevice(void *handler);
MMP_ERR Component_JPEMGR_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_JPEMGR_AllocateBuffer(void *handler);
MMP_ERR Component_JPEMGR_FreeBuffer(void *handler);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_JPEMGR_BufInfo[MAX_JPEMGR_COMP_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_JPEMGR_InPort[MAX_JPEMGR_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_JPEMGR_OutPort[MAX_JPEMGR_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_JPEMGR_MemoryInfo[MAX_JPEMGR_COMP_NUM];
MMP_COMPONENT_HANDLER_JPE_MGR Component_JPEMGR_DeviceInfo[MAX_JPEMGR_COMP_NUM];

MMP_COMPONENT_BASE Component_JPEMGR[MAX_JPEMGR_COMP_NUM] =
{
    {
        "JPEMGR0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[0],        // MemoryInfo
        Component_JPEMGR_BufInfo[0],            // BufferInfo
        &Component_JPEMGR_InPort[0],            // pInPort
        Component_JPEMGR_OutPort[0],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[0]         // DeviceInfo
    },
    {
        "JPEMGR1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[1],        // MemoryInfo
        Component_JPEMGR_BufInfo[1],            // BufferInfo
        &Component_JPEMGR_InPort[1],            // pInPort
        Component_JPEMGR_OutPort[1],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[1]         // DeviceInfo
    },
    {
        "JPEMGR2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[2],        // MemoryInfo
        Component_JPEMGR_BufInfo[2],            // BufferInfo
        &Component_JPEMGR_InPort[2],            // pInPort
        Component_JPEMGR_OutPort[2],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[2]         // DeviceInfo
    },
    {
        "JPEMGR3",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[3],        // MemoryInfo
        Component_JPEMGR_BufInfo[3],            // BufferInfo
        &Component_JPEMGR_InPort[3],            // pInPort
        Component_JPEMGR_OutPort[3],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[3]         // DeviceInfo
    },
    {
        "JPEMGR4",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[4],        // MemoryInfo
        Component_JPEMGR_BufInfo[4],            // BufferInfo
        &Component_JPEMGR_InPort[4],            // pInPort
        Component_JPEMGR_OutPort[4],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[4]         // DeviceInfo
    },
    {
        "JPEMGR5",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[5],        // MemoryInfo
        Component_JPEMGR_BufInfo[5],            // BufferInfo
        &Component_JPEMGR_InPort[5],            // pInPort
        Component_JPEMGR_OutPort[5],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[5]         // DeviceInfo
    },
    {
        "JPEMGR6",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[6],        // MemoryInfo
        Component_JPEMGR_BufInfo[6],            // BufferInfo
        &Component_JPEMGR_InPort[6],            // pInPort
        Component_JPEMGR_OutPort[6],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[6]         // DeviceInfo
    },
    {
        "JPEMGR7",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[7],        // MemoryInfo
        Component_JPEMGR_BufInfo[7],            // BufferInfo
        &Component_JPEMGR_InPort[7],            // pInPort
        Component_JPEMGR_OutPort[7],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[7]         // DeviceInfo
    },
    {
        "JPEMGR8",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[8],        // MemoryInfo
        Component_JPEMGR_BufInfo[8],            // BufferInfo
        &Component_JPEMGR_InPort[8],            // pInPort
        Component_JPEMGR_OutPort[8],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[8]         // DeviceInfo
    },
    {
        "JPEMGR9",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[9],        // MemoryInfo
        Component_JPEMGR_BufInfo[9],            // BufferInfo
        &Component_JPEMGR_InPort[9],            // pInPort
        Component_JPEMGR_OutPort[9],            // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[9]         // DeviceInfo
    },
    {
        "JPEMGR10",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[10],       // MemoryInfo
        Component_JPEMGR_BufInfo[10],           // BufferInfo
        &Component_JPEMGR_InPort[10],           // pInPort
        Component_JPEMGR_OutPort[10],           // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[10]        // DeviceInfo
    },
    {
        "JPEMGR11",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPEMGR_MemoryInfo[11],       // MemoryInfo
        Component_JPEMGR_BufInfo[11],           // BufferInfo
        &Component_JPEMGR_InPort[11],           // pInPort
        Component_JPEMGR_OutPort[11],           // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_JPEMGR_InitDevice,            // pfInit
        Component_JPEMGR_OpenDevice,            // pfOpen
        Component_JPEMGR_AllocateBuffer,        // pfAllocateMemory
        Component_JPEMGR_FreeBuffer,            // pfFreeMemory
        Component_JPEMGR_UnInitDevice,          // pfUnInit
        Component_JPEMGR_CloseDevice,           // pfClose
        NULL,                                   // pfSetParameter
        NULL,                                   // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_JPEMGR_EmptyBuffer,           // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPEMGR_DeviceInfo[11]        // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE_MGR   *pMgrDev = pComp->DeviceInfo;

    if (pMgrDev->ubUseType == JPEMGR_COMP_PRM_MJPEG) {
        MMPF_FRAME_RING_BUF_HANDLE pRing = MMPF_StreamRing_GetFrameRing(VIDEO1_RING_STREAM);
        MMPF_FrameRing_LinkMgrComponent(pRing, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_SCD_MJPEG) {
        MMPF_FRAME_RING_BUF_HANDLE pRing = MMPF_StreamRing_GetFrameRing(VIDEO2_RING_STREAM);
        MMPF_FrameRing_LinkMgrComponent(pRing, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_TRD_MJPEG) {
        //MMPF_FRAME_RING_BUF_HANDLE pRing = MMPF_StreamRing_GetFrameRing(VIDEO2_RING_STREAM);
        //MMPF_FrameRing_LinkMgrComponent(pRing, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_PRM_PRIMARY ||
             pMgrDev->ubUseType == JPEMGR_COMP_PRM_THUMB) {

        MMPF_Ring2_LinkMgrComponent(MMP_JPEG_ENC_CAM_SEL_PRM, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_SCD_PRIMARY ||
             pMgrDev->ubUseType == JPEMGR_COMP_SCD_THUMB) {

        MMPF_Ring2_LinkMgrComponent(MMP_JPEG_ENC_CAM_SEL_SCD, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_TRD_PRIMARY ||
             pMgrDev->ubUseType == JPEMGR_COMP_TRD_THUMB) {

        MMPF_Ring2_LinkMgrComponent(MMP_JPEG_ENC_CAM_SEL_TRD, pComp);
    }
    else if (pMgrDev->ubUseType == JPEMGR_COMP_PRM_VR_THUMB ||
             pMgrDev->ubUseType == JPEMGR_COMP_SCD_VR_THUMB ||
             pMgrDev->ubUseType == JPEMGR_COMP_TRD_VR_THUMB) {
        // TBD
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_CloseDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    JPE_MGR_COMP_EMPTY_BUF_INFO *pInfo = (JPE_MGR_COMP_EMPTY_BUF_INFO *)BufInfo;
    //MMP_COMPONENT_BUFFER_INFO *InBufinfo = &pComp->pInPort->bufInfo;

    // TBD Sync write pointer ?
    //pContainer->ulVidCompBufWritePtr    = InBufinfo->bufctl.ring.ulWL;
    //pContainer->ulVidCompBufWriteWrap   = InBufinfo->bufctl.ring.ulWH;

    COMPONENT_JPEMGR_DBG_MSG(0, "JPEMGR_EmptyBuffer Id %d Type %d DoneMode %d Size %d\r\n",
                             pInfo->usEncId,
                             pInfo->usEncType,
                             pInfo->usEncDoneMode,
                             pInfo->ulTotalSize);

    return MMPF_JPGENC_MGR_ProcessBitstream(    pInfo->usEncId,
                                                pInfo->usEncType,
                                                pInfo->usEncDoneMode,
                                                pInfo->ulTotalSize,
                                                pInfo->ulEncBufAddr,
                                                pComp);
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_AllocateBuffer(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPEMGR_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPEMGR_FreeBuffer(void *handler)
{
    return MMP_ERR_NONE;
}
