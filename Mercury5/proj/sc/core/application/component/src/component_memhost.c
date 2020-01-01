//------------------------------------------------------------------------------
//
//  File        : component_memhost.c
//  Description : Source file of memhost component configuration
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
#include "component_cfg.h"
#include "component_memhost.h"
#include "mmp_vidrec_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_MEMHOST_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_MEMHOST_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_MEMHOST_OpenDevice(void *handler);
MMP_ERR Component_MEMHOST_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MEMHOST_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MEMHOST_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_MEMHOST_BufInfo[MAX_MEMHOST_COMP_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_MEMHOST_InPort[MAX_MEMHOST_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_MEMHOST_OutPort[MAX_MEMHOST_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_MEMHOST_MemoryInfo[MAX_MEMHOST_COMP_NUM];
MMP_COMPONENT_HANDLER_MEMHOST Component_MEMHOST_DevInfo[MAX_MEMHOST_COMP_NUM];

MMP_COMPONENT_BASE Component_MemHost[MAX_MEMHOST_COMP_NUM] =
{
    {
        "MEMHOST0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MEMHOST_MemoryInfo[0],       // MemoryInfo
        Component_MEMHOST_BufInfo[0],           // BufferInfo
        &Component_MEMHOST_InPort[0],           // pInPort
        NULL,                                   // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        NULL,                                   // pfInit
        Component_MEMHOST_OpenDevice,           // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        NULL,                                   // pfUnInit
        NULL,                                   // pfClose
        Component_MEMHOST_SetParam,             // pfSetParameter
        Component_MEMHOST_GetParam,             // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MEMHOST_EmptyBuffer,          // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MEMHOST_DevInfo[0],          // DeviceInfo
    },
    {
        "MEMHOST1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MEMHOST_MemoryInfo[1],       // MemoryInfo
        Component_MEMHOST_BufInfo[1],           // BufferInfo
        &Component_MEMHOST_InPort[1],           // pInPort
        NULL,                                   // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        NULL,                                   // pfInit
        Component_MEMHOST_OpenDevice,           // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        NULL,                                   // pfUnInit
        NULL,                                   // pfClose
        Component_MEMHOST_SetParam,             // pfSetParameter
        Component_MEMHOST_GetParam,             // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MEMHOST_EmptyBuffer,          // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MEMHOST_DevInfo[1],          // DeviceInfo
    },
    {
        "MEMHOST2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MEMHOST_MemoryInfo[2],       // MemoryInfo
        Component_MEMHOST_BufInfo[2],           // BufferInfo
        &Component_MEMHOST_InPort[2],           // pInPort
        NULL,                                   // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        NULL,                                   // pfInit
        Component_MEMHOST_OpenDevice,           // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        NULL,                                   // pfUnInit
        NULL,                                   // pfClose
        Component_MEMHOST_SetParam,             // pfSetParameter
        Component_MEMHOST_GetParam,             // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_MEMHOST_EmptyBuffer,          // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MEMHOST_DevInfo[2],          // DeviceInfo
    }
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_MEMHOST_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MEMHOST_OpenDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MEMHOST_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MEMHOST_SetParam(void *handler, int type, void* pParam)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MEMHOST_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MEMHOST_GetParam(void *handler, int type, void* pParam)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MEMHOST_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MEMHOST_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MEMHOST   *pMemHost = (MMP_COMPONENT_HANDLER_MEMHOST *)pComp->DeviceInfo;

    COMPONENT_MEMHOST_DBG_MSG(  0, "[%s] Input Buf Addr: 0x%x Size %d ArgSize %d\r\n",
                                pComp->name,
                                pComp->pInPort->bufInfo.ulBufAddr,
                                pComp->pInPort->bufInfo.ulSize,
                                ulSize);

    if (pMemHost->ubUseType == MEMHOST_COMP_BROWSER_THUMB) {
        MMPS_VIDPLAY_SetTumbnaiInfo( pComp->pInPort->bufInfo.ulBufAddr,  pComp->pInPort->bufInfo.ulSize);
    }
    else if (pMemHost->ubUseType == MEMHOST_COMP_FCAM_VR_THUMB) {
        MMPF_VIDENC_UpdateVRThumbInfo(VIDENC_THUMB_RING_BUF_PRM, pComp->pInPort->bufInfo.ulBufAddr, ulSize);
    }
    else if (pMemHost->ubUseType == MEMHOST_COMP_RCAM_VR_THUMB) {
        MMPF_VIDENC_UpdateVRThumbInfo(VIDENC_THUMB_RING_BUF_SCD, pComp->pInPort->bufInfo.ulBufAddr, ulSize);
    }

    MMP_CompCtl_StoreBufferDone(pComp, 0, NULL);

    return MMP_ERR_NONE;
}
