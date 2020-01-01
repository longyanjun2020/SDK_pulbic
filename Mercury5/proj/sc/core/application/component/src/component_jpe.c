//------------------------------------------------------------------------------
//
//  File        : component_jpe.c
//  Description : Source file of jpe component configuration
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
#include "mmp_vidrec_inc.h"
#include "component_cfg.h"
#include "component_jpe.h"
#include "mmpf_jpeg_enc.h"
#include "mmpf_ringbuf.h"
#include "mmpf_vr_thumb.h"
#include "snr_cfg.h"
#include "mmpf_sensor.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_JPE_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_JPE_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define JPE_COMP_USAGE_TO_MMP_JPEG_ENC_TYPE(c) (\
                            c == JPE_COMP_PRM_MJPEG      ? MMP_JPEG_ENC_TYPE_PRM_MJPEG     :   \
                            c == JPE_COMP_SCD_MJPEG      ? MMP_JPEG_ENC_TYPE_SCD_MJPEG     :   \
                            c == JPE_COMP_TRD_MJPEG      ? MMP_JPEG_ENC_TYPE_TRD_MJPEG     :   \
                            c == JPE_COMP_PRM_PRIMARY    ? MMP_JPEG_ENC_TYPE_PRM_PRIMARY   :   \
                            c == JPE_COMP_SCD_PRIMARY    ? MMP_JPEG_ENC_TYPE_SCD_PRIMARY   :   \
                            c == JPE_COMP_TRD_PRIMARY    ? MMP_JPEG_ENC_TYPE_TRD_PRIMARY   :   \
                            c == JPE_COMP_PRM_THUMB      ? MMP_JPEG_ENC_TYPE_PRM_THUMB     :   \
                            c == JPE_COMP_SCD_THUMB      ? MMP_JPEG_ENC_TYPE_SCD_THUMB     :   \
                            c == JPE_COMP_TRD_THUMB      ? MMP_JPEG_ENC_TYPE_TRD_THUMB     :   \
                            c == JPE_COMP_PRM_VR_THUMB   ? MMP_JPEG_ENC_TYPE_PRM_VR_THUMB  :   \
                            c == JPE_COMP_SCD_VR_THUMB   ? MMP_JPEG_ENC_TYPE_SCD_VR_THUMB  :   \
                            c == JPE_COMP_TRD_VR_THUMB   ? MMP_JPEG_ENC_TYPE_TRD_VR_THUMB  :   \
                            MMP_JPEG_ENC_TYPE_NUM)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_JPE_InitDevice(void *handler);
MMP_ERR Component_JPE_UnInitDevice(void *handler);
MMP_ERR Component_JPE_OpenDevice(void *handler);
MMP_ERR Component_JPE_CloseDevice(void *handler);
MMP_ERR Component_JPE_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPE_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_JPE_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_JPE_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_JPE_AllocateBuffer(void *handler);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_JPE_BufInfo[MAX_JPE_COMP_NUM][MAX_JPE_COMP_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_JPE_InPort[MAX_JPE_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_JPE_OutPort[MAX_JPE_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_JPE_MemoryInfo[MAX_JPE_COMP_NUM];
MMP_COMPONENT_HANDLER_JPE Component_JPE_DevInfo[MAX_JPE_COMP_NUM];

MMP_COMPONENT_BASE Component_JPE[MAX_JPE_COMP_NUM] =
{
    {
        "JPE0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[0],           // MemoryInfo
        Component_JPE_BufInfo[0],               // BufferInfo
        &Component_JPE_InPort[0],               // pInPort
        Component_JPE_OutPort[0],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[0],              // DeviceInfo
    },
    {
        "JPE1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[1],           // MemoryInfo
        Component_JPE_BufInfo[1],               // BufferInfo
        &Component_JPE_InPort[1],               // pInPort
        Component_JPE_OutPort[1],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[1],              // DeviceInfo
    },
    {
        "JPE2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[2],           // MemoryInfo
        Component_JPE_BufInfo[2],               // BufferInfo
        &Component_JPE_InPort[2],               // pInPort
        Component_JPE_OutPort[2],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[2],              // DeviceInfo
    },
    {
        "JPE3",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[3],           // MemoryInfo
        Component_JPE_BufInfo[3],               // BufferInfo
        &Component_JPE_InPort[3],               // pInPort
        Component_JPE_OutPort[3],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[3],              // DeviceInfo
    },
    {
        "JPE4",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[4],           // MemoryInfo
        Component_JPE_BufInfo[4],               // BufferInfo
        &Component_JPE_InPort[4],               // pInPort
        Component_JPE_OutPort[4],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[4],              // DeviceInfo
    },
    {
        "JPE5",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[5],           // MemoryInfo
        Component_JPE_BufInfo[5],               // BufferInfo
        &Component_JPE_InPort[5],               // pInPort
        Component_JPE_OutPort[5],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[5],              // DeviceInfo
    },
    {
        "JPE6",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[6],           // MemoryInfo
        Component_JPE_BufInfo[6],               // BufferInfo
        &Component_JPE_InPort[6],               // pInPort
        Component_JPE_OutPort[6],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[6],              // DeviceInfo
    },
    {
        "JPE7",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[7],           // MemoryInfo
        Component_JPE_BufInfo[7],               // BufferInfo
        &Component_JPE_InPort[7],               // pInPort
        Component_JPE_OutPort[7],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[7],              // DeviceInfo
    },
    {
        "JPE8",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[8],           // MemoryInfo
        Component_JPE_BufInfo[8],               // BufferInfo
        &Component_JPE_InPort[8],               // pInPort
        Component_JPE_OutPort[8],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[8],              // DeviceInfo
    },
    {
        "JPE9",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[9],           // MemoryInfo
        Component_JPE_BufInfo[9],               // BufferInfo
        &Component_JPE_InPort[9],               // pInPort
        Component_JPE_OutPort[9],               // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[9],              // DeviceInfo
    },
    {
        "JPE10",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[10],          // MemoryInfo
        Component_JPE_BufInfo[10],              // BufferInfo
        &Component_JPE_InPort[10],              // pInPort
        Component_JPE_OutPort[10],              // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[10],             // DeviceInfo
    },
    {
        "JPE11",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_JPE_MemoryInfo[11],          // MemoryInfo
        Component_JPE_BufInfo[11],              // BufferInfo
        &Component_JPE_InPort[11],              // pInPort
        Component_JPE_OutPort[11],              // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_JPE_InitDevice,               // pfInit
        Component_JPE_OpenDevice,               // pfOpen
        Component_JPE_AllocateBuffer,           // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_JPE_UnInitDevice,             // pfUnInit
        Component_JPE_CloseDevice,              // pfClose
        Component_JPE_SetParam,                 // pfSetParameter
        Component_JPE_GetParam,                 // pfGetParameter
        Component_JPE_UpdateBuffer,             // pfUpdateBuffer
        Component_JPE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_JPE_DevInfo[11],             // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_JPE_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpeDev = (MMP_COMPONENT_HANDLER_JPE *)pComp->DeviceInfo;
    JPE_COMP_RESOL              *pEncWH = &pJpeDev->stEncWH;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    MMP_ULONG                   ulEncId = 0;
    MMP_UBYTE                   ubCamSel = 0;
    MMP_USHORT                  usEncDoneMode = 0;

    if (!MMPF_JPGENC_IsModuleInit()) {
        eRetErr = MMPF_JPGENC_InitModule();
        if (eRetErr != MMP_ERR_NONE) {
            COMPONENT_JPE_DBG_ERR(1, "[%s] Module Init Fail\r\n", pComp->name);
            return eRetErr;
        }
    }

    if (MMPF_JPGENC_InitInstance(&ulEncId, pComp) != MMP_ERR_NONE) {
        COMPONENT_JPE_DBG_ERR(1, "[%s] Instance Init Fail\r\n", pComp->name);
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_JPE_DBG_MSG(0, "[%s] Instance %d Init OK\r\n", pComp->name, ulEncId);
    }

    pJpeDev->usInstID = (MMP_USHORT)ulEncId;

    switch(pJpeDev->ubUseType) {
    case JPE_COMP_PRM_MJPEG:
    case JPE_COMP_PRM_PRIMARY:
    case JPE_COMP_PRM_THUMB:
    case JPE_COMP_PRM_VR_THUMB:
        ubCamSel = MMP_JPEG_ENC_CAM_SEL_PRM;
        break;
    case JPE_COMP_SCD_MJPEG:
    case JPE_COMP_SCD_PRIMARY:
    case JPE_COMP_SCD_THUMB:
    case JPE_COMP_SCD_VR_THUMB:
        ubCamSel = MMP_JPEG_ENC_CAM_SEL_SCD;
        break;
    case JPE_COMP_TRD_MJPEG:
    case JPE_COMP_TRD_PRIMARY:
    case JPE_COMP_TRD_THUMB:
    case JPE_COMP_TRD_VR_THUMB:
        ubCamSel = MMP_JPEG_ENC_CAM_SEL_TRD;
        break;
    default:
        ubCamSel = MMP_JPEG_ENC_CAM_SEL_PRM;
        break;
    }

    switch(pJpeDev->ubUseType) {
    case JPE_COMP_PRM_MJPEG:
    case JPE_COMP_SCD_MJPEG:
    case JPE_COMP_TRD_MJPEG:
        MMPS_DSC_GetMjpegEncDoneMode(&usEncDoneMode);
        break;
    case JPE_COMP_PRM_PRIMARY:
    case JPE_COMP_SCD_PRIMARY:
    case JPE_COMP_TRD_PRIMARY:
        if (pJpeDev->ubShotMode == JPE_COMP_CONTINUOUS_SHOT)
            usEncDoneMode = MMP_JPEG_ENC_DONE_CONTINUOUS_SHOT;
        else
            usEncDoneMode = MMP_JPEG_ENC_DONE_NONE; //MMP_JPEG_ENC_DONE_SIZE_CTL; TBD
        break;
    case JPE_COMP_PRM_THUMB:
    case JPE_COMP_SCD_THUMB:
    case JPE_COMP_TRD_THUMB:
        usEncDoneMode = MMP_JPEG_ENC_DONE_NONE;
        break;
    case JPE_COMP_PRM_VR_THUMB:
    case JPE_COMP_SCD_VR_THUMB:
    case JPE_COMP_TRD_VR_THUMB:
        usEncDoneMode = MMP_JPEG_ENC_DONE_NONE;
        break;
    default:
        COMPONENT_JPE_DBG_ERR(1, "[JPE] UnSupport Use Type\r\n");
        break;
    }

    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_W, pEncWH->ulEncW);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_H, pEncWH->ulEncH);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_BUF_W, pEncWH->ulEncBufW);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_BUF_H, pEncWH->ulEncBufH);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_INPUT_FMT, pJpeDev->ubRawFormat);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_MAX_SHOT_NUM, pJpeDev->ulShotNum);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_CAM_SEL, ubCamSel);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_DONE_FLOW, usEncDoneMode);
    MMPF_JPGENC_SetParameter(MMPF_JPGENC_GetInstance(ulEncId), MMP_JPEG_ENC_ATTR_ENC_COMP_TYPE, JPE_COMP_USAGE_TO_MMP_JPEG_ENC_TYPE(pJpeDev->ubUseType));

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_CloseDevice(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpeDev = (MMP_COMPONENT_HANDLER_JPE *)pComp->DeviceInfo;

    if ((pComp == NULL) || (pJpeDev == NULL)) {
        COMPONENT_JPE_DBG_ERR(1, "[JPE] CloseDevice Err\r\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (MMPF_JPGENC_DeInitInstance(pJpeDev->usInstID) != MMP_ERR_NONE) {
        COMPONENT_JPE_DBG_ERR(1, "[JPE] DeInitInst %d Fail\r\n", pJpeDev->usInstID);
        return MMP_ERR_NONE;
    }
    else {
        COMPONENT_JPE_DBG_MSG(0, "[JPE] DeInitInst %d OK\r\n", pJpeDev->usInstID);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpe       = &Component_JPE_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pJpeMem    = &Component_JPE_Memory[0];

    if (strcmp("JPE0", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[0];
        pJpeMem = &Component_JPE_Memory[0];
    }
    else if (strcmp("JPE1", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[1];
        pJpeMem = &Component_JPE_Memory[1];
    }
    else if (strcmp("JPE2", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[2];
        pJpeMem = &Component_JPE_Memory[2];
    }
    else if (strcmp("JPE3", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[3];
        pJpeMem = &Component_JPE_Memory[3];
    }
    else if (strcmp("JPE4", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[4];
        pJpeMem = &Component_JPE_Memory[4];
    }
    else if (strcmp("JPE5", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[5];
        pJpeMem = &Component_JPE_Memory[5];
    }
    else if (strcmp("JPE6", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[6];
        pJpeMem = &Component_JPE_Memory[6];
    }
    else if (strcmp("JPE7", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[7];
        pJpeMem = &Component_JPE_Memory[7];
    }
    else if (strcmp("JPE8", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[8];
        pJpeMem = &Component_JPE_Memory[8];
    }
    else if (strcmp("JPE9", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[9];
        pJpeMem = &Component_JPE_Memory[9];
    }
    else if (strcmp("JPE10", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[10];
        pJpeMem = &Component_JPE_Memory[10];
    }
    else if (strcmp("JPE11", pComp->name) == 0) {
        pJpe    = &Component_JPE_Handler[11];
        pJpeMem = &Component_JPE_Memory[11];
    }
    else {
        COMPONENT_JPE_DBG_ERR(1, "[%s] UnSupport JPE Comp Name [%d]\r\n", pComp->name, type);
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case JPE_COMP_PARAM_RES:
        memcpy(&pJpe->stEncWH, (JPE_COMP_RESOL*)pParam, sizeof(JPE_COMP_RESOL));
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update JPE Res [%d][%d][%d][%d]\r\n",
                              pComp->name,
                              pJpe->stEncWH.ulEncW, pJpe->stEncWH.ulEncH,
                              pJpe->stEncWH.ulEncBufW, pJpe->stEncWH.ulEncBufH);
        break;
    case JPE_COMP_PARAM_UI_MODE:
        pJpe->ubUiMode = *(MMP_UBYTE*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update UI Mode [%d]\r\n", pComp->name, pJpe->ubUiMode);
        break;
    case JPE_COMP_PARAM_FMT:
        pJpe->ubRawFormat = *(MMP_UBYTE*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Raw Fmt [%d]\r\n", pComp->name, pJpe->ubRawFormat);
        break;
    case JPE_COMP_PARAM_SHOT_MODE:
        pJpe->ubShotMode = *(MMP_UBYTE*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Shot Mode [%d]\r\n", pComp->name, pJpe->ubShotMode);
        break;
    case JPE_COMP_PARAM_SHOT_NUM:
        pJpe->ulShotNum = *(MMP_ULONG*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Shot Num [%d]\r\n", pComp->name, pJpe->ulShotNum);
        break;
    case JPE_COMP_PARAM_INIT_QF:
        pJpe->usInitQFactor = *(MMP_USHORT*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Init Q-Factor [%d]\r\n", pComp->name, pJpe->usInitQFactor);
        break;
    case JPE_COMP_PARAM_BUF_COUNT:
        pJpeMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pJpeMem->ubBufNum);
        break;
    case JPE_COMP_PARAM_BUF_SIZE:
        pJpeMem->ulBufSize= *(MMP_ULONG*)pParam;
        COMPONENT_JPE_DBG_MSG(1, "[%s] Update Buf Size [%d] Bytes\r\n", pComp->name, pJpeMem->ulBufSize);
        break;
    default:
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_GetStaticParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_JPE_GetStaticParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp   = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpeDev = &Component_JPE_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pJpeMem = &Component_JPE_Memory[0];

    if (strcmp("JPE0", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[0];
        pJpeMem = &Component_JPE_Memory[0];
    }
    else if (strcmp("JPE1", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[1];
        pJpeMem = &Component_JPE_Memory[1];
    }
    else if (strcmp("JPE2", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[2];
        pJpeMem = &Component_JPE_Memory[2];
    }
    else if (strcmp("JPE3", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[3];
        pJpeMem = &Component_JPE_Memory[3];
    }
    else if (strcmp("JPE4", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[4];
        pJpeMem = &Component_JPE_Memory[4];
    }
    else if (strcmp("JPE5", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[5];
        pJpeMem = &Component_JPE_Memory[5];
    }
    else if (strcmp("JPE6", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[6];
        pJpeMem = &Component_JPE_Memory[6];
    }
    else if (strcmp("JPE7", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[7];
        pJpeMem = &Component_JPE_Memory[7];
    }
    else if (strcmp("JPE8", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[8];
        pJpeMem = &Component_JPE_Memory[8];
    }
    else if (strcmp("JPE9", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[9];
        pJpeMem = &Component_JPE_Memory[9];
    }
    else if (strcmp("JPE10", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[10];
        pJpeMem = &Component_JPE_Memory[10];
    }
    else if (strcmp("JPE11", pComp->name) == 0) {
        pJpeDev = &Component_JPE_Handler[11];
        pJpeMem = &Component_JPE_Memory[11];
    }
    else {
        COMPONENT_JPE_DBG_ERR(1, "[%s] UnSupport JPE Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case JPE_COMP_PARAM_RES:
        memcpy(pParam, &pJpeDev->stEncWH, sizeof(JPE_COMP_RESOL));
        break;
    case JPE_COMP_PARAM_UI_MODE:
        *(MMP_UBYTE*)pParam = pJpeDev->ubUiMode;
        break;
    case JPE_COMP_PARAM_FMT:
        *(MMP_UBYTE*)pParam = pJpeDev->ubRawFormat;
        break;
    case JPE_COMP_PARAM_SHOT_MODE:
        *(MMP_UBYTE*)pParam = pJpeDev->ubShotMode;
        break;
    case JPE_COMP_PARAM_SHOT_NUM:
        *(MMP_ULONG*)pParam = pJpeDev->ulShotNum;
        break;
    case JPE_COMP_PARAM_INIT_QF:
        *(MMP_USHORT*)pParam = pJpeDev->usInitQFactor;
        break;
    case JPE_COMP_PARAM_BUF_COUNT:
        *(MMP_UBYTE*)pParam = pJpeMem->ubBufNum;
        break;
    case JPE_COMP_PARAM_BUF_SIZE:
        *(MMP_ULONG*)pParam = pJpeMem->ulBufSize;
        break;
    case JPE_COMP_PARAM_BUF_RING_THD:
        *(MMP_ULONG*)pParam = pJpeMem->ulNearRingThd;
        break;
    default:
        COMPONENT_JPE_DBG_ERR(1, "JPE_GetParamr UnSupport Type\r\n");
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_GetRunTimeParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_JPE_GetRunTimeParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp   = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpeDev = (MMP_COMPONENT_HANDLER_JPE *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO   *pJpeMem = pComp->MemoryInfo;

    if ((strcmp("JPE0", pComp->name) == 0) ||
        (strcmp("JPE1", pComp->name) == 0) ||
        (strcmp("JPE2", pComp->name) == 0) ||
        (strcmp("JPE3", pComp->name) == 0) ||
        (strcmp("JPE4", pComp->name) == 0) ||
        (strcmp("JPE5", pComp->name) == 0) ||
        (strcmp("JPE6", pComp->name) == 0) ||
        (strcmp("JPE7", pComp->name) == 0) ||
        (strcmp("JPE8", pComp->name) == 0) ||
        (strcmp("JPE9", pComp->name) == 0) ||
        (strcmp("JPE10", pComp->name) == 0) ||
        (strcmp("JPE11", pComp->name) == 0)) {
    }
    else {
        COMPONENT_JPE_DBG_ERR(1, "[%s] UnSupport JPE Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case JPE_COMP_PARAM_RES:
        memcpy(pParam, &pJpeDev->stEncWH, sizeof(JPE_COMP_RESOL));
        break;
    case JPE_COMP_PARAM_UI_MODE:
        *(MMP_UBYTE*)pParam = pJpeDev->ubUiMode;
        break;
    case JPE_COMP_PARAM_FMT:
        *(MMP_UBYTE*)pParam = pJpeDev->ubRawFormat;
        break;
    case JPE_COMP_PARAM_SHOT_MODE:
        *(MMP_UBYTE*)pParam = pJpeDev->ubShotMode;
        break;
    case JPE_COMP_PARAM_SHOT_NUM:
        *(MMP_ULONG*)pParam = pJpeDev->ulShotNum;
        break;
    case JPE_COMP_PARAM_INIT_QF:
        *(MMP_USHORT*)pParam = pJpeDev->usInitQFactor;
        break;
    case JPE_COMP_PARAM_BUF_COUNT:
        *(MMP_UBYTE*)pParam = pJpeMem->ubBufNum;
        break;
    case JPE_COMP_PARAM_BUF_SIZE:
        *(MMP_ULONG*)pParam = pJpeMem->ulBufSize;
        break;
    case JPE_COMP_PARAM_BUF_RING_THD:
        *(MMP_ULONG*)pParam = pJpeMem->ulNearRingThd;
        break;
    default:
        COMPONENT_JPE_DBG_ERR(1, "JPE_GetParamr UnSupport Type\r\n");
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if (pComp->ulState != MMP_COMPONENT_STATE_IDLE) {
        return Component_JPE_GetStaticParam(handler, type, pParam);
    }
    else {
        return Component_JPE_GetRunTimeParam(handler, type, pParam);
    }
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_JPE   *pJpeDev = (MMP_COMPONENT_HANDLER_JPE *)pComp->DeviceInfo;
    JPGENC_INPUT_ATTR           stJpgEncAttr;
    MMP_UBYTE                   ubClosePortIdx = PORT_SCRIPT_INVALID;

    /* Config Script Index */
    if (pJpeDev->ubUseType == JPE_COMP_PRM_PRIMARY) {
        if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_VR) {
            ubClosePortIdx = PORT_SCRIPT_VR_PRM_BAYER_CAPTURE;
        }
        else {
            if(MMP_GetANACamType() == ANA_CAM_2I2O){
                ubClosePortIdx = PORT_SCRIPT_DSC_PRM_CAPTURE_RAW1;
            }else{
                ubClosePortIdx = PORT_SCRIPT_DSC_PRM_CAPTURE;
            }
        }
    }
    else if (pJpeDev->ubUseType == JPE_COMP_SCD_PRIMARY) {
        if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_VR) {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                ubClosePortIdx = PORT_SCRIPT_VR_SCD_BAYER_CAPTURE;
            else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))
                ubClosePortIdx = PORT_SCRIPT_VR_SCD_ANADEC_CAPTURE;
            else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264))
                ubClosePortIdx = PORT_SCRIPT_VR_USBH_CAPTURE;
            else if (CAM_CHECK_USB(USB_CAM_AIT))
                ubClosePortIdx = PORT_SCRIPT_VR_USBH_CAPTURE;
        }
        else {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                ubClosePortIdx = PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE;
            else
                ubClosePortIdx = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE;
        }
    }
    else if (pJpeDev->ubUseType == JPE_COMP_TRD_PRIMARY) {
        // TBD
    }
    else if (pJpeDev->ubUseType == JPE_COMP_PRM_THUMB) {
        if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_VR)
            ubClosePortIdx = PORT_SCRIPT_INVALID;
        else if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_DSC){
            if(MMP_GetANACamType() == ANA_CAM_2I2O)
                ubClosePortIdx = PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB_RAW1;
            else
                ubClosePortIdx = PORT_SCRIPT_DSC_PRM_CAPTURE_THUMB;
        }
        else if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_BROWSER)
            ubClosePortIdx = PORT_SCRIPT_INVALID;
    }
    else if (pJpeDev->ubUseType == JPE_COMP_SCD_THUMB) {
        if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_VR)
            ubClosePortIdx = PORT_SCRIPT_INVALID;
        else if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_DSC) {
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                ubClosePortIdx = PORT_SCRIPT_DSC_SCD_BAYER_CAPTURE_THUMB;
            else
                ubClosePortIdx = PORT_SCRIPT_DSC_SCD_ANADEC_CAPTURE_THUMB;
        }
        else if (pJpeDev->ubUiMode == JPE_COMP_UI_MODE_BROWSER)
            ubClosePortIdx = PORT_SCRIPT_INVALID;
    }
    else if (pJpeDev->ubUseType == JPE_COMP_TRD_THUMB) {
        // TBD
    }
    else if (pJpeDev->ubUseType == JPE_COMP_PRM_VR_THUMB) {
        if(MMP_GetANACamType() == ANA_CAM_2I2O)
            ubClosePortIdx = PORT_SCRIPT_VR_PRM_ANADEC_THUMB_RAW1;
        else
            ubClosePortIdx = PORT_SCRIPT_VR_PRM_BAYER_THUMB;
    }
    else if (pJpeDev->ubUseType == JPE_COMP_SCD_VR_THUMB) {
        if (MMPF_VIDMGR_IsShareRecdEn()) {
            ubClosePortIdx = PORT_SCRIPT_VR_SHARE_THUMB;
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            ubClosePortIdx = PORT_SCRIPT_VR_SCD_BAYER_THUMB;
        }
        else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            ubClosePortIdx = PORT_SCRIPT_VR_SCD_ANADEC_THUMB;
        }
        else if (CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) {
            ubClosePortIdx = PORT_SCRIPT_VR_USBH_THUMB;
        }
        else if (CAM_CHECK_USB(USB_CAM_AIT)) {
            ubClosePortIdx = PORT_SCRIPT_VR_USBH_THUMB;
        }
    }
    else if (pJpeDev->ubUseType == JPE_COMP_TRD_VR_THUMB) {
        // TBD
    }
    else {
        COMPONENT_JPE_DBG_MSG(1, "JPE_EmptyBuffer TBD\r\n");
    }

    /* Config JPEG Module */
    stJpgEncAttr.pComp          = (void*)pComp;
    stJpgEncAttr.usEncId        = pJpeDev->usInstID;
    stJpgEncAttr.ulInBufAddr    = (MMP_ULONG)pComp->pInPort->bufInfo.ulBufAddr;
    stJpgEncAttr.ulInBufSize    = pComp->pInPort->bufInfo.ulSize;
    stJpgEncAttr.usInitQFactor  = pJpeDev->usInitQFactor;
    stJpgEncAttr.pfEncCBFunc    = NULL; // TBD
    stJpgEncAttr.pEncCBFuncArg  = (void*)&(pJpeDev->ubUseType);
    stJpgEncAttr.stDateTime     = pComp->pInPort->bufInfo.stDateTime;
    stJpgEncAttr.ulBufBias      = pComp->pInPort->bufInfo.ulBufBias;

    if (MMP_COMPONENT_ADV_RDIDX == MMPF_JPGENC_InputFrameReady(stJpgEncAttr.usEncId, stJpgEncAttr)) {
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
    }

    /* Close Port */
    if (ubClosePortIdx != PORT_SCRIPT_INVALID) {
        if (pJpeDev->ubShotMode == JPE_COMP_SINGLE_SHOT) {
            ClosePortScript(ubClosePortIdx);
        }
        else if (pJpeDev->ubShotMode == JPE_COMP_CONTINUOUS_SHOT) {
            if (MMPF_JPGENC_CheckMaxShotExceed(pJpeDev->usInstID)) {
                ClosePortScript(ubClosePortIdx);
            }
        }
        else if (pJpeDev->ubShotMode == JPE_COMP_MJPEG_MODE) {
            // TBD : Control Stop by MMPS_DSC
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_UpdateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pMem->MemMode == MMP_COMPONENT_MEMORY_RING ||
        pMem->MemMode == MMP_COMPONENT_MEMORY_NEARRING) {
        pMem->memctl.ring.ulWL = ALIGN32(pMem->memctl.ring.ulWL);
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_JPE_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_JPE_AllocateBuffer(void *handler)
{
#define JPE_ADDR_ALIGNMENT 32

    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_JPE   *pDev = pComp->DeviceInfo;
    MMP_UBYTE                   i = 0;
    MMP_UBYTE                   ubRingBufType = VIDENC_THUMB_RING_BUF_PRM;

    if (pDev->ubUseType == JPE_COMP_PRM_MJPEG) {
        MMPF_StreamRing_ConfigBuffer(VIDEO1_RING_STREAM, pBuf[0].ulBufAddr, pMem->ulBufSize, JPE_ADDR_ALIGNMENT, MMP_TRUE);
    }
    else if (pDev->ubUseType == JPE_COMP_SCD_MJPEG) {
        MMPF_StreamRing_ConfigBuffer(VIDEO2_RING_STREAM, pBuf[0].ulBufAddr, pMem->ulBufSize, JPE_ADDR_ALIGNMENT, MMP_TRUE);
    }
    else if (pDev->ubUseType == JPE_COMP_TRD_MJPEG) {
        //MMPF_StreamRing_ConfigBuffer(VIDEO2_RING_STREAM, pBuf[0].ulBufAddr, pMem->ulBufSize, JPE_ADDR_ALIGNMENT, MMP_TRUE);
    }
    else if (pDev->ubUseType == JPE_COMP_PRM_PRIMARY ||
             pDev->ubUseType == JPE_COMP_PRM_THUMB) {

        if (pDev->ubShotMode == JPE_COMP_SINGLE_SHOT)
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_PRM, pBuf[0].ulBufAddr, pMem->ulBufSize, 0, JPE_ADDR_ALIGNMENT, 0);
        else
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_PRM, pBuf[0].ulBufAddr, pMem->ulBufSize, pMem->ulNearRingThd, JPE_ADDR_ALIGNMENT, 20/*m_ulContiShotInterval, Interval:ms*/);
    }
    else if (pDev->ubUseType == JPE_COMP_SCD_PRIMARY ||
             pDev->ubUseType == JPE_COMP_SCD_THUMB) {

        if (pDev->ubShotMode == JPE_COMP_SINGLE_SHOT)
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_SCD, pBuf[0].ulBufAddr, pMem->ulBufSize, 0, JPE_ADDR_ALIGNMENT, 0);
        else
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_SCD, pBuf[0].ulBufAddr, pMem->ulBufSize, pMem->ulNearRingThd, JPE_ADDR_ALIGNMENT, 20/*m_ulContiShotInterval, Interval:ms*/);
    }
    else if (pDev->ubUseType == JPE_COMP_TRD_PRIMARY ||
             pDev->ubUseType == JPE_COMP_TRD_THUMB) {

        if (pDev->ubShotMode == JPE_COMP_SINGLE_SHOT)
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_TRD, pBuf[0].ulBufAddr, pMem->ulBufSize, 0, JPE_ADDR_ALIGNMENT, 0);
        else
            MMPF_Ring2_InitBuf(MMP_JPEG_ENC_CAM_SEL_TRD, pBuf[0].ulBufAddr, pMem->ulBufSize, pMem->ulNearRingThd, JPE_ADDR_ALIGNMENT, 20/*m_ulContiShotInterval, Interval:ms*/);
    }
#if (SUPPORT_VR_THUMBNAIL)
    else if (pDev->ubUseType == JPE_COMP_PRM_VR_THUMB) {

        ubRingBufType = VIDENC_THUMB_RING_BUF_PRM;

        for (i = 0; i < MMPF_VIDENC_GetVRThumbRingBufNum(ubRingBufType); i++) {
            gstVRThumbAttr[ubRingBufType][i].ulAddr     = (MMP_ULONG)pBuf[i].ulBufAddr;
            gstVRThumbAttr[ubRingBufType][i].ulSize     = 0;
            gstVRThumbAttr[ubRingBufType][i].ulProgCnt  = INVALID_THUMB_PROG_CNT;
            gstVRThumbAttr[ubRingBufType][i].ulFrmQIdx  = 0;

            COMPONENT_JPE_DBG_MSG(0, "VRThumb PrmRing [%d] Addr = 0x%X\r\n", i, gstVRThumbAttr[ubRingBufType][i].ulAddr);
        }
    }
    else if (pDev->ubUseType == JPE_COMP_SCD_VR_THUMB) {

        ubRingBufType = VIDENC_THUMB_RING_BUF_SCD;

        for (i = 0; i < MMPF_VIDENC_GetVRThumbRingBufNum(ubRingBufType); i++) {
            gstVRThumbAttr[ubRingBufType][i].ulAddr     = (MMP_ULONG)pBuf[i].ulBufAddr;
            gstVRThumbAttr[ubRingBufType][i].ulSize     = 0;
            gstVRThumbAttr[ubRingBufType][i].ulProgCnt  = INVALID_THUMB_PROG_CNT;
            gstVRThumbAttr[ubRingBufType][i].ulFrmQIdx  = 0;

            COMPONENT_JPE_DBG_MSG(0, "VRThumb ScdRing [%d] Addr = 0x%X\r\n", i, gstVRThumbAttr[ubRingBufType][i].ulAddr);
        }
    }
    else if (pDev->ubUseType == JPE_COMP_TRD_VR_THUMB) {

        ubRingBufType = VIDENC_THUMB_RING_BUF_TRD;

        for (i = 0; i < MMPF_VIDENC_GetVRThumbRingBufNum(ubRingBufType); i++) {
            gstVRThumbAttr[ubRingBufType][i].ulAddr     = (MMP_ULONG)pBuf[i].ulBufAddr;
            gstVRThumbAttr[ubRingBufType][i].ulSize     = 0;
            gstVRThumbAttr[ubRingBufType][i].ulProgCnt  = INVALID_THUMB_PROG_CNT;
            gstVRThumbAttr[ubRingBufType][i].ulFrmQIdx  = 0;

            COMPONENT_JPE_DBG_MSG(0, "VRThumb ScdRing [%d] Addr = 0x%X\r\n", i, gstVRThumbAttr[ubRingBufType][i].ulAddr);
        }
    }
#endif

    return MMP_ERR_NONE;
}
