//------------------------------------------------------------------------------
//
//  File        : component_jpd.c
//  Description : Source file of JPD component configuration
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
#include "component_jpd.h"
#include "mmpf_jpeg_dec.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_JPD_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_JPD_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_JPD_InitDevice(void *handler);
MMP_ERR Component_JPD_UnInitDevice(void *handler);
MMP_ERR Component_JPD_OpenDevice(void *handler);
MMP_ERR Component_JPD_CloseDevice(void *handler);
MMP_ERR Component_JPD_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPD_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPD_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_JPD_AllocateBuffer(void *handler);
MMP_ERR Component_JPD_FreeBuffer(void *handler);
MMP_ERR Component_JPD_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_JPD_BufInfo[MAX_JPD_COMP_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_JPD_InPort[MAX_JPD_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_JPD_OutPort[MAX_JPD_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_JPD_MemoryInfo[MAX_JPD_COMP_NUM];
MMP_COMPONENT_HANDLER_JPD Component_JPD_DeviceInfo[MAX_JPD_COMP_NUM];

MMP_COMPONENT_BASE Component_JPD[MAX_JPD_COMP_NUM] =
{
    {
        "JPD0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPD_MemoryInfo[0],           // MemoryInfo
        Component_JPD_BufInfo[0],               // BufferInfo
        &Component_JPD_InPort[0],               // pInPort
        Component_JPD_OutPort[0],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPD_InitDevice,               // pfInit
        Component_JPD_OpenDevice,               // pfOpen
        Component_JPD_AllocateBuffer,           // pfAllocateMemory
        Component_JPD_FreeBuffer,               // pfFreeMemory
        Component_JPD_UnInitDevice,             // pfUnInit
        Component_JPD_CloseDevice,              // pfClose
        Component_JPD_SetParam,                 // pfSetParameter
        Component_JPD_GetParam,                 // pfGetParameter
        Component_JPD_UpdateBuffer,             // pfUpdateBuffer
        Component_JPD_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPD_DeviceInfo[0]            // DeviceInfo
    },
    {
        "JPD1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPD_MemoryInfo[1],           // MemoryInfo
        Component_JPD_BufInfo[1],               // BufferInfo
        &Component_JPD_InPort[1],               // pInPort
        Component_JPD_OutPort[1],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPD_InitDevice,               // pfInit
        Component_JPD_OpenDevice,               // pfOpen
        Component_JPD_AllocateBuffer,           // pfAllocateMemory
        Component_JPD_FreeBuffer,               // pfFreeMemory
        Component_JPD_UnInitDevice,             // pfUnInit
        Component_JPD_CloseDevice,              // pfClose
        Component_JPD_SetParam,                 // pfSetParameter
        Component_JPD_GetParam,                 // pfGetParameter
        Component_JPD_UpdateBuffer,             // pfUpdateBuffer
        Component_JPD_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPD_DeviceInfo[1]            // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_JPD_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_OpenDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_CloseDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO   *pJPDMem    = &Component_JPD_Memory[0];
    MMP_COMPONENT_HANDLER_JPD   *pJpdDev    = &Component_JPD_Handler[0];
    JPD_COMP_RESOL              *pJPDRect   = &pJpdDev->stResol;

    if (strcmp("JPD0", pComp->name) == 0) {
        pJpdDev = &Component_JPD_Handler[0];
        pJPDMem = &Component_JPD_Memory[0];
    }
    else if (strcmp("JPD1", pComp->name) == 0) {
        pJpdDev = &Component_JPD_Handler[1];
        pJPDMem = &Component_JPD_Memory[1];
    }
    else {
        COMPONENT_JPD_DBG_ERR(1, "[%s] UnSupport JPD Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case JPD_COMP_PARAM_RES:
        memcpy(pJPDRect, (JPD_COMP_RESOL*)pParam, sizeof(JPD_COMP_RESOL));
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Res [%d][%d][%d][%d]\r\n",
                              pComp->name, pJPDRect->ulStartX, pJPDRect->ulStartY, pJPDRect->ulWidth, pJPDRect->ulHeight);
        break;
    case JPD_COMP_PARAM_DEC_SRC:
        pJpdDev->ubDecSrc = *(MMP_UBYTE*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Image Source [%d]\r\n", pComp->name, pJpdDev->ubDecSrc);
        break;
    case JPD_COMP_PARAM_DEC_IMG_TYPE:
        pJpdDev->ubDecImgType = *(MMP_UBYTE*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Image Type [%d]\r\n", pComp->name, pJpdDev->ubDecImgType);
        break;
    case JPD_COMP_PARAM_BUF_COUNT:
        pJPDMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pJPDMem->ubBufNum);
        break;
    case JPD_COMP_PARAM_BUF_SIZE:
        pJPDMem->ulBufSize= *(MMP_ULONG*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pJPDMem->ulBufSize);
        break;
    case JPD_COMP_PARAM_MEM_MODE_IN_ADDR:
        pComp->pInPort->bufInfo.ulBufAddr = *(MMP_ULONG*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Mem In Addr [%x]\r\n", pComp->name, pComp->pInPort->bufInfo.ulBufAddr);
        break;
    case JPD_COMP_PARAM_MEM_MODE_IN_SIZE:
        pComp->pInPort->bufInfo.ulSize = *(MMP_ULONG*)pParam;
        COMPONENT_JPD_DBG_MSG(1, "[%s] Update Mem In Size [%x]\r\n", pComp->name, pComp->pInPort->bufInfo.ulSize);
        break;
    default:
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_GetParam(void *handler, int type, void* pParam)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_JPD   *pJpdDev = (MMP_COMPONENT_HANDLER_JPD *)pComp->DeviceInfo;
    MMPF_JPEGD_INPUT_ATTR       stJpgDecAttr;

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    /* Config JPEG Decode Module */
    stJpgDecAttr.ubCompType         = pJpdDev->ubUseType;
    stJpgDecAttr.ubDecSrc           = pJpdDev->ubDecSrc;
    stJpgDecAttr.ubDecImgType       = pJpdDev->ubDecImgType;

    if (stJpgDecAttr.ubDecSrc == JPD_COMP_DEC_SRC_MJPEG) {
        stJpgDecAttr.ulSrcBufAddr   = pComp->pInPort->bufInfo.ulBufAddr;
        stJpgDecAttr.ulSrcBufSize   = pComp->pInPort->bufInfo.ulSize;
        stJpgDecAttr.ulInputBufAddr = pComp->pInPort->bufInfo.ulBufAddr;
        stJpgDecAttr.ulInputBufSize = pComp->pInPort->bufInfo.ulSize;
    }
    else if (stJpgDecAttr.ubDecSrc == JPD_COMP_DEC_SRC_MEMORY) {
        stJpgDecAttr.ulSrcBufAddr   = pComp->pInPort->bufInfo.ulBufAddr; // TBD. Memory mode may not have previous component
        stJpgDecAttr.ulSrcBufSize   = pComp->pInPort->bufInfo.ulSize;
        stJpgDecAttr.ulInputBufAddr = pComp->pInPort->bufInfo.ulBufAddr;
        stJpgDecAttr.ulInputBufSize = pComp->pInPort->bufInfo.ulSize;
    }
    else if (stJpgDecAttr.ubDecSrc == JPD_COMP_DEC_SRC_FILE) {
        stJpgDecAttr.ulSrcBufAddr   = 0;
        stJpgDecAttr.ulSrcBufSize   = 0;
        stJpgDecAttr.ulInputBufAddr = 0;
        stJpgDecAttr.ulInputBufSize = 0;
    }

    stJpgDecAttr.ulOutputBufAddr    = pBuf[pMem->memctl.frm.ubWBufIndex].ulBufAddr;
    stJpgDecAttr.ulOutputBufSize    = pMem->ulBufSize;
    stJpgDecAttr.pfDecCBFunc        = NULL; // TBD
    stJpgDecAttr.pDecCBFuncArg      = (void*)&(pJpdDev->ubUseType);

    if (MMP_COMPONENT_ADV_RDIDX == MMPF_JPEGD_InputFrameReady(stJpgDecAttr.ubCompType, stJpgDecAttr)) {
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_UpdateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_AllocateBuffer(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPD   *pJpdDev = (MMP_COMPONENT_HANDLER_JPD *)pComp->DeviceInfo;

    if (pJpdDev->ubUseType == JPD_COMP_MJPEG_DEC)
        return MMPS_DSC_AllocDecIntBuf(pJpdDev->ubUseType);
    else
        return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_FreeBuffer(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPD   *pJpdDev = (MMP_COMPONENT_HANDLER_JPD *)pComp->DeviceInfo;

    if (pJpdDev->ubUseType == JPD_COMP_MJPEG_DEC)
        return MMPS_DSC_FreeDecIntBuf(pJpdDev->ubUseType);
    else
        return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_TriggerEmptyBuf
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_TriggerEmptyBuf(MMP_UBYTE ubUseType)
{
    return Component_JPD_EmptyBuffer(&Component_JPD[ubUseType], 0, NULL);
}

//------------------------------------------------------------------------------
//  Function    : Component_JPD_TriggerEmptyBufEx
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPD_TriggerEmptyBufEx(MMP_UBYTE ubUseType, MMP_ULONG ulSrcAddr, MMP_ULONG ulSrcSize)
{
    MMP_COMPONENT_BASE *pComp = &Component_JPD[ubUseType];

    pComp->pInPort->bufInfo.ulBufAddr = ulSrcAddr;
    pComp->pInPort->bufInfo.ulSize    = ulSrcSize;

    return Component_JPD_EmptyBuffer(&Component_JPD[ubUseType], 0, NULL);
}
