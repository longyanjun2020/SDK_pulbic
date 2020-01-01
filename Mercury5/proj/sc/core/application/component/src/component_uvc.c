//------------------------------------------------------------------------------
//
//  File        : component_uvc.c
//  Description : Source file of UVC component configuration
//  Author      :
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"
#include "component_uvc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_UVC_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_UVC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_ERR Component_UVC_InitDevice(void *handler);
MMP_ERR Component_UVC_UnInitDevice(void *handler);
MMP_ERR Component_UVC_OpenDevice(void *handler);
MMP_ERR Component_UVC_CloseDevice(void *handler);
MMP_ERR Component_UVC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_UVC_SetParameter(void *handler, int type, void* pParam);
MMP_ERR Component_UVC_GetParameter(void *handler, int type, void* pParam);

MMP_COMPONENT_BUFFER_INFO Component_UVC_BufInfo[COMPONENT_UVC_MAX_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_UVC_InPort[COMPONENT_UVC_MAX_NUM];
MMP_COMPONENT_PORT_INFO Component_UVC_OutPort[COMPONENT_UVC_MAX_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_UVC_MemoryInfo[COMPONENT_UVC_MAX_NUM];
MMP_COMPONENT_HANDLER_UVC Component_UVC_DevInfo[COMPONENT_UVC_MAX_NUM];

MMP_COMPONENT_BASE Component_UVC[COMPONENT_UVC_MAX_NUM] =
{
    {
        "UVC0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_UVC_MemoryInfo[0],           // MemoryInfo
        Component_UVC_BufInfo[0],               // BufferInfo
        &Component_UVC_InPort[0],               // pInPort
        Component_UVC_OutPort[0],               // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_UVC_InitDevice,               // pfInit
        Component_UVC_OpenDevice,               // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_UVC_UnInitDevice,             // pfUnInit
        Component_UVC_CloseDevice,              // pfClose
        Component_UVC_SetParameter,             // pfSetParameter
        Component_UVC_GetParameter,             // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_UVC_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_UVC_DevInfo[0]               // DeviceInfo
    },
    {
        "UVC1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_UVC_MemoryInfo[1],           // MemoryInfo
        Component_UVC_BufInfo[1],               // BufferInfo
        &Component_UVC_InPort[1],               // pInPort
        Component_UVC_OutPort[1],               // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_UVC_InitDevice,               // pfInit
        Component_UVC_OpenDevice,               // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_UVC_UnInitDevice,             // pfUnInit
        Component_UVC_CloseDevice,              // pfClose
        Component_UVC_SetParameter,             // pfSetParameter
        Component_UVC_GetParameter,             // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        Component_UVC_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_UVC_DevInfo[1]               // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_UVC_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_OpenDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_CloseDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_UVC       *pUvcDev = (MMP_COMPONENT_HANDLER_UVC *)pComp->DeviceInfo;
    MMP_ULONG                       ulStartAddr = pComp->pInPort->bufInfo.ulBufAddr;

    if (pUvcDev->eColorFormat == UVC_COMP_FORMAT_YUV422) {
        ulStartAddr += pComp->pInPort->bufInfo.ulBufBias;
        usb_uvc_yuv422_tx(ulStartAddr);
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL); // CHECK
    }
    else if (pUvcDev->eColorFormat == UVC_COMP_FORMAT_YUV420) {
        // TBD
    }
    else if (pUvcDev->eColorFormat == UVC_COMP_FORMAT_MJPEG) {
        //usb_uvc_mjpeg_tx();
    }

    //MMP_CompCtl_StoreBufferDone((void *)pComp, 0, NULL);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_SetParameter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_SetParameter(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_UVC       *pUvcDev = &Component_UVC_Handler[0];;
    MMP_COMPONENT_MEMORY_INFO       *pUVCMem = &Component_UVC_Memory[0];
    UVC_COMP_RESOL                  *pUVCResol= NULL;

    switch(type) {
    case UVC_COMP_PARAM_RESOL:
        pUVCResol = &pUvcDev->stResol;
        memcpy(pUVCResol, (UVC_COMP_RESOL*)pParam, sizeof(UVC_COMP_RESOL));
        COMPONENT_UVC_DBG_MSG(1, "[%s] Update Resol [%d][%d]\r\n",
                              pComp->name, pUVCResol->ulW, pUVCResol->ulH);
        break;
    case UVC_COMP_PARAM_FORMAT:
        pUvcDev->eColorFormat = *(UVC_COMP_FORMAT*)pParam;
        COMPONENT_UVC_DBG_MSG(1, "[%s] Update ColorFormat [%d]\r\n", pComp->name, pUvcDev->eColorFormat);
        break;
    case UVC_COMP_PARAM_BUF_COUNT:
        pUVCMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_UVC_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pUVCMem->ubBufNum);
        break;
    case UVC_COMP_PARAM_BUF_SIZE:
        pUVCMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_UVC_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pUVCMem->ulBufSize);
        break;
    default:
        COMPONENT_UVC_DBG_ERR(1, "[%s] UnSupport UVC Param Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_UVC_GetParameter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_UVC_GetParameter(void *handler, int type, void* pParam)
{
    // TBD
    return MMP_ERR_NONE;
}

