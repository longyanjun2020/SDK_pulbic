//------------------------------------------------------------------------------
//
//  File        : component_mgr.c
//  Description : Source file of mgr component configuration
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
#include "component_mgr.h"
#include "mmpd_3gpmgr.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_MGR_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_MGR_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_MGR_InitDevice(void *handler);
MMP_ERR Component_MGR_UnInitDevice(void *handler);
MMP_ERR Component_MGR_OpenDevice(void *handler);
MMP_ERR Component_MGR_CloseDevice(void *handler);
MMP_ERR Component_MGR_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MGR_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MGR_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_MGR_AllocateBuffer(void *handler);
MMP_ERR Component_MGR_FreeBuffer(void *handler);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_MGR_BufInfo[MAX_MGR_COMP_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_MGR_InPort[MAX_MGR_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_MGR_OutPort[MAX_MGR_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_MGR_MemoryInfo[MAX_MGR_COMP_NUM];
MMP_COMPONENT_HANDLER_MGR Component_MGR_DeviceInfo[MAX_MGR_COMP_NUM];

MMP_COMPONENT_BASE Component_MGR[MAX_MGR_COMP_NUM] =
{
    {
        "MGR0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[0],           // MemoryInfo
        Component_MGR_BufInfo[0],               // BufferInfo
        &Component_MGR_InPort[0],               // pInPort
        Component_MGR_OutPort[0],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[0]            // DeviceInfo
    },
    {
        "MGR1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[1],           // MemoryInfo
        Component_MGR_BufInfo[1],               // BufferInfo
        &Component_MGR_InPort[1],               // pInPort
        Component_MGR_OutPort[1],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[1]            // DeviceInfo
    },
    {
        "MGR2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[2],           // MemoryInfo
        Component_MGR_BufInfo[2],               // BufferInfo
        &Component_MGR_InPort[2],               // pInPort
        Component_MGR_OutPort[2],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[2]            // DeviceInfo
    },
    {
        "MGR3",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[3],           // MemoryInfo
        Component_MGR_BufInfo[3],               // BufferInfo
        &Component_MGR_InPort[3],               // pInPort
        Component_MGR_OutPort[3],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[3]            // DeviceInfo
    },
    {
        "MGR4",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[4],           // MemoryInfo
        Component_MGR_BufInfo[4],               // BufferInfo
        &Component_MGR_InPort[4],               // pInPort
        Component_MGR_OutPort[4],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[4]            // DeviceInfo
    },
    {
        "MGR5",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MGR_MemoryInfo[5],           // MemoryInfo
        Component_MGR_BufInfo[5],               // BufferInfo
        &Component_MGR_InPort[5],               // pInPort
        Component_MGR_OutPort[5],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
        Component_MGR_InitDevice,               // pfInit
        Component_MGR_OpenDevice,               // pfOpen
        Component_MGR_AllocateBuffer,           // pfAllocateMemory
        Component_MGR_FreeBuffer,               // pfFreeMemory
        Component_MGR_UnInitDevice,             // pfUnInit
        Component_MGR_CloseDevice,              // pfClose
        Component_MGR_SetParam,                 // pfSetParameter
        Component_MGR_GetParam,                 // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MGR_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MGR_DeviceInfo[5]            // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_MGR_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_OpenDevice(void *pHandle)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)pHandle;
    MMP_COMPONENT_HANDLER_MGR   *pMgrDev = pComp->DeviceInfo;
    MMPF_VID_MGR_INFO           *pContainer = NULL;

    switch (pMgrDev->usStreamType) {
        case VIDENC_STREAM_PRM_RECD:
            pContainer = MMPF_VIDMGR_GetMerger(VIDENC_STREAM_PRM_RECD);
            pMgrDev->pContainer = pContainer;
            pContainer->pCompHandle = pHandle;
            break;
        case VIDENC_STREAM_SCD_RECD:
            pContainer = MMPF_VIDMGR_GetMerger(VIDENC_STREAM_SCD_RECD);
            pMgrDev->pContainer = pContainer;
            pContainer->pCompHandle = pHandle;
            break;
        #if (SUPPORT_H264_WIFI_STREAM)
        case VIDENC_STREAM_WIFI_PRM:
            pContainer = MMPF_VIDMGR_GetMerger(VIDENC_STREAM_WIFI_PRM);
            pMgrDev->pContainer = pContainer;
            pContainer->pCompHandle = pHandle;
            break;
        case VIDENC_STREAM_WIFI_SCD:
            pContainer = MMPF_VIDMGR_GetMerger(VIDENC_STREAM_WIFI_SCD);
            pMgrDev->pContainer = pContainer;
            pContainer->pCompHandle = pHandle;
            break;
        #endif
        case VIDENC_STREAM_UVC_RECD:
            pContainer = MMPF_VIDMGR_GetMerger(VIDENC_STREAM_UVC_RECD);
            pMgrDev->pContainer = pContainer;
            pContainer->pCompHandle = pHandle;
            break;
        default:
            COMPONENT_MGR_DBG_ERR(1, "MGR device open fail\r\n");
            break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_CloseDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MGR   *pMgrDev    = &Component_MGR_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pMgrMem    = &Component_MGR_Memory[0];

    if (strcmp("MGR0", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[0];
        pMgrMem = &Component_MGR_Memory[0];
    }
    else if (strcmp("MGR1", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[1];
        pMgrMem = &Component_MGR_Memory[1];
    }
    else if (strcmp("MGR2", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[2];
        pMgrMem = &Component_MGR_Memory[2];
    }
    else if (strcmp("MGR3", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[3];
        pMgrMem = &Component_MGR_Memory[3];
    }
    else if (strcmp("MGR4", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[4];
        pMgrMem = &Component_MGR_Memory[4];
    }
    else if (strcmp("MGR5", pComp->name) == 0) {
        pMgrDev = &Component_MGR_Handler[5];
        pMgrMem = &Component_MGR_Memory[5];
    }
    else {
        COMPONENT_MGR_DBG_ERR(1, "[%s] UnSupport MGR Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case MGR_COMP_PARAM_MULTI_TRACK:
        pMgrDev->bMultiTrack = *(MMP_BOOL*)pParam;
        COMPONENT_MGR_DBG_MSG(1, "[%s] Update Multi-Track [%d]\r\n", pComp->name, pMgrDev->bMultiTrack);
        break;
    case MGR_COMP_PARAM_BUF_COUNT:
        pMgrMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_MGR_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pMgrMem->ubBufNum);
        break;
    case MGR_COMP_PARAM_BUF_SIZE:
        pMgrMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_MGR_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pMgrMem->ulBufSize);
        break;
    default:
        COMPONENT_MGR_DBG_ERR(1, "[%s] SetParamr UnSupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_GetParam(void *handler, int type, void* pParam)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MGR       *pMgrDev = pComp->DeviceInfo;
    MMP_COMPONENT_BASE              *pPrevComp = (MMP_COMPONENT_BASE *)pComp->pInPort->PrevComponent;
    MGR_COMP_EMPTY_BUF_INFO         *pInfo = (MGR_COMP_EMPTY_BUF_INFO *)pvBufInfo;
    //MMP_COMPONENT_BUFFER_INFO       *InBufinfo = &pComp->pInPort->bufInfo;
    MMPF_VID_MGR_INFO               *pContainer = pMgrDev->pContainer;

    pContainer->ulVidCompBufAddr        = pComp->pInPort->bufInfo.ulBufAddr;
    pContainer->ulVidCompBufSize        = pPrevComp->MemoryInfo->ulBufSize;
    //pContainer->ulVidCompBufWritePtr    = InBufinfo->bufctl.ring.ulWL;
    //pContainer->ulVidCompBufWriteWrap   = InBufinfo->bufctl.ring.ulWH;

    // Keep size to frame queue.
    MMPF_VIDMGR_KeepSizeToFrameQueue(ulSize, pInfo->ulFrameTime, (VIDENC_FRAME_TYPE)pInfo->ulFrameType, pContainer);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_AllocateBuffer(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_MGR   *pMgrDev = pComp->DeviceInfo;
    MMPD_3GPMGR_REPACKBUF       stRepackBuf = {0};

    stRepackBuf.ulAvRepackStartAddr   = pBuf[0].ulBufAddr;
    stRepackBuf.ulAvRepackSize        = pMem->ulBufSize;
    stRepackBuf.ulVideoSizeTableAddr  = 0;
    stRepackBuf.ulVideoSizeTableSize  = 0;
    stRepackBuf.ulVideoTimeTableAddr  = 0;
    stRepackBuf.ulVideoTimeTableSize  = 0;

    MMPD_3GPMGR_SetRepackMiscBuf(pMgrDev->usStreamType, &stRepackBuf);

    if (pMgrDev->bEncodeEn == MMP_FALSE) {
        return MMPS_3GPRECD_AllocUVCMGRMemory(pMgrDev->usStreamType, pMgrDev->bMultiTrack);
    }
    else {
        return MMPS_3GPRECD_AllocMGRMemory(pMgrDev->usStreamType, pMgrDev->bMultiTrack);
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_MGR_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MGR_FreeBuffer(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MGR   *pMgrDev = pComp->DeviceInfo;
    
    if (pMgrDev->bEncodeEn == MMP_FALSE) {
        return MMPS_3GPRECD_FreeUVCMGRMemory(pMgrDev->usStreamType);
    }
    else {
        return MMPS_3GPRECD_FreeMGRMemory(pMgrDev->usStreamType);
    }
}
