//------------------------------------------------------------------------------
//
//  File        : component_mfe.c
//  Description : Source file of MFE component configuration
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
#include "component_mfe.h"
#include "mmpd_3gpmgr.h"
#include "mmpf_mp4venc.h"
#include "mmpf_h264enc.h"
#include "libcamera.h"
#include "libcamera_io.h"
#include "drv_pm_chip.h"
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_MFE_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_MFE_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_MFE_InitDevice(void *handler);
MMP_ERR Component_MFE_UnInitDevice(void *handler);
MMP_ERR Component_MFE_OpenDevice(void *handler);
MMP_ERR Component_MFE_CloseDevice(void *handler);
MMP_ERR Component_MFE_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MFE_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_MFE_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_MFE_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo);
MMP_ERR Component_MFE_AllocateBuffer(void *handler);
MMP_ERR Component_MFE_FreeBuffer(void *handler);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_MFE_BufInfo[MAX_MFE_COMP_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_MFE_InPort[MAX_MFE_COMP_NUM];
MMP_COMPONENT_PORT_INFO Component_MFE_OutPort[MAX_MFE_COMP_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_MFE_MemoryInfo[MAX_MFE_COMP_NUM];
MMP_COMPONENT_HANDLER_MFE Component_MFE_DeviceInfo[MAX_MFE_COMP_NUM];

MMP_COMPONENT_BASE Component_MFE[MAX_MFE_COMP_NUM] =
{
    {
        "MFE0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[0],           // MemoryInfo
        Component_MFE_BufInfo[0],               // BufferInfo
        &Component_MFE_InPort[0],               // pInPort
        Component_MFE_OutPort[0],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[0]            // DeviceInfo
    },
    {
        "MFE1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[1],           // MemoryInfo
        Component_MFE_BufInfo[1],               // BufferInfo
        &Component_MFE_InPort[1],               // pInPort
        Component_MFE_OutPort[1],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[1]            // DeviceInfo
    },
    {
        "MFE2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[2],           // MemoryInfo
        Component_MFE_BufInfo[2],               // BufferInfo
        &Component_MFE_InPort[2],               // pInPort
        Component_MFE_OutPort[2],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[2]            // DeviceInfo
    },
    {
        "MFE3",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[3],           // MemoryInfo
        Component_MFE_BufInfo[3],               // BufferInfo
        &Component_MFE_InPort[3],               // pInPort
        Component_MFE_OutPort[3],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[3]            // DeviceInfo
    },
    {
        "MFE4",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[4],           // MemoryInfo
        Component_MFE_BufInfo[4],               // BufferInfo
        &Component_MFE_InPort[4],               // pInPort
        Component_MFE_OutPort[4],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[4]            // DeviceInfo
    },
    {
        "MFE5",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_MFE_MemoryInfo[5],           // MemoryInfo
        Component_MFE_BufInfo[5],               // BufferInfo
        &Component_MFE_InPort[5],               // pInPort
        Component_MFE_OutPort[5],               // pOutPort
#if (H264E_COMPRESS_BUF_NEAR_RING_EN)
        {
            &MMP_CompCtl_UpdateBuffer_NearRing,
            &MMP_CompCtl_EmptyBuffer_NearRing,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_NearRing,
        },
#else
        {
            &MMP_CompCtl_UpdateBuffer_Ring,
            &MMP_CompCtl_EmptyBuffer_Ring,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Ring,
        },
#endif
        Component_MFE_InitDevice,               // pfInit
        Component_MFE_OpenDevice,               // pfOpen
        Component_MFE_AllocateBuffer,           // pfAllocateMemory
        Component_MFE_FreeBuffer,               // pfFreeMemory
        Component_MFE_UnInitDevice,             // pfUnInit
        Component_MFE_CloseDevice,              // pfClose
        Component_MFE_SetParam,                 // pfSetParameter
        Component_MFE_GetParam,                 // pfGetParameter
        Component_MFE_UpdateBuffer,             // pfUpdateBuffer
        Component_MFE_EmptyBuffer,              // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_MFE_DeviceInfo[5]            // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_MFE_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_UnInitDevice(void *handler)
{
    MMP_COMPONENT_BASE      	*pComp  = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE   *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;

    //COMPONENT_MFE_DBG_ERR(1, "[%s] [%s] \r\n",__FUNCTION__ ,pComp->name);
    if (pMfeDev->ubUseType == MFE_COMP_UVC_RECD)
    	MMPF_USBH_SetUSBRecordBuffer(handler, MMP_TRUE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_OpenDeviceNonEncode
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_MFE_OpenDeviceNonEncode(void *handler)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE       *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_ERR                         eRetErr = MMP_ERR_NONE;

    eRetErr = MMPS_3GPRECD_AllocUVCEncMemory(pComp, pMfeDev->usStreamType);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Alloc UVC Enc Memory Fail\r\n", pComp->name);
        return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
    }

    eRetErr = MMPF_H264ENC_SetUVCCompressBuf(pBuf[0].ulBufAddr, pMem->ulBufSize); // Put at here for correct ubEncID
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set CompressBuf Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    MMPF_VIDMGR_SetCompBufRingMode(pMfeDev->usStreamType, MMP_FALSE, pMem->ulNearRingThd);

    MMPF_USBH_SetUSBRecordBuffer(handler, MMP_FALSE);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE       *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;
    MFE_COMP_ENC_RESOL              *pEncWH  = &pMfeDev->stEncWH;
    MFE_COMP_FPS                    *pSnrFps = &pMfeDev->stSnrFps;
    MFE_COMP_FPS                    *pEncFps = &pMfeDev->stEncFps;
    MFE_COMP_FPS                    *pMgrFps = &pMfeDev->stMgrFps;
    MMP_COMPONENT_BUFFER_INFO       *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO       *pMem = pComp->MemoryInfo;
    MMP_ULONG                       ulTgtFrmSize = 0;
    MMP_ULONG                       ulFps = 0;
    MMP_ULONG                       ulVidFullRange = 1;
    MMP_ULONG                       ulTimingInfoPres = 1;
    MMP_ULONG64                     u64Size = 0;
    MMP_ERR                         eRetErr = MMP_ERR_NONE;
    MMP_BOOL                        bEncCapable = MMP_FALSE;
    MS_CAM20_COLORTRANS_TYPE        colorType;
    VIDENC_QP_BOUND_CTL             stFrmQPBoundCtl;
    VIDENC_QP_BOUND_CTL             stMBQPBoundCtl;

    if (pMfeDev->ubUseType == MFE_COMP_UVC_RECD) {
        return Component_MFE_OpenDeviceNonEncode(handler);
    }

    ulFps = (pSnrFps->usTimeResol + pSnrFps->usTimeIncre - 1) / pSnrFps->usTimeIncre;

    bEncCapable = MMPF_VIDENC_CheckCapability((pEncWH->ulEncBufW >>4) * (pEncWH->ulEncBufH >> 4), ulFps);
    if (bEncCapable != MMP_TRUE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Check Capability Fail\r\n", pComp->name);
        return MMP_MP4VE_ERR_CAPABILITY;
    }

    // For sync live stream audio pointer
    //MMPF_AUDIO_WaitForSync(); // TBD

    if (!MMPF_VIDENC_IsModuleInit()) {
        eRetErr = MMPF_VIDENC_InitModule();
        if (eRetErr != MMP_ERR_NONE) {
            COMPONENT_MFE_DBG_ERR(1, "[%s] Module Init Fail\r\n", pComp->name);
            return eRetErr;
        }
    }

    eRetErr = MMPS_3GPRECD_AllocH264Memory((MMP_ULONG *)&pMfeDev->ubEncID, pComp, pMfeDev->usStreamType);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Alloc Enc Memory Fail\r\n", pComp->name);
        return MMP_3GPRECD_ERR_MEM_EXHAUSTED;
    }

    eRetErr = MMPD_H264ENC_SetBitstreamBuf(pMfeDev->ubEncID, pBuf[0].ulBufAddr, pMem->ulBufSize); // Put at here for correct ubEncID
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set BitStreamBuf Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    eRetErr = MMPF_VIDENC_SetVideoRes(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), pEncWH->ulEncW, pEncWH->ulEncH, pEncWH->ulEncBufW, pEncWH->ulEncBufH);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set Resolution Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    eRetErr = MMPF_VIDENC_SetVideoProfile(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), pMfeDev->eProfile);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set Profile Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    // EROY TBD
#if (SUPPORT_MFE_SHAREBUFFER)
    eRetErr = MMPF_VIDENC_SetMfeResrc(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), pMfeDev->ePixFmt, -1, -1);
#else
    eRetErr = MMPF_VIDENC_SetMfeResrc(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), pMfeDev->ePixFmt, -1, 0);
#endif
    eRetErr |= MMPF_VIDENC_SetMfeMotion(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), 32, 16, 2, 0xFF, 0);
    eRetErr |= MMPF_VIDENC_SetMfeSplit(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), 0, 0);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set Resrc/Motion/Split Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    pMfeDev->usStreamType = MMPF_H264ENC_GetStreamTypeFromId(pMfeDev->ubEncID);

    MMPF_VIDMGR_SetCompBufRingMode(pMfeDev->usStreamType, MMP_TRUE, pMem->ulNearRingThd);

    MMPF_VIDMGR_SetGOP(pMfeDev->usStreamType, pMfeDev->ulPframeNum, 0);
    eRetErr = MMPF_VIDENC_SetVideoGOP(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID), pMfeDev->ulPframeNum, 0);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set GOP Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    u64Size = (MMP_ULONG64)pMfeDev->ulBitrate * (MMP_ULONG64)pMgrFps->usTimeIncre;
    ulTgtFrmSize = (MMP_ULONG)(u64Size / (pMgrFps->usTimeResol * 8));

    stFrmQPBoundCtl.ubQPBound[I_FRAME][BD_LOW]  = pMfeDev->stQpCtl.ubIFrameLowB;
    stFrmQPBoundCtl.ubQPBound[I_FRAME][BD_HIGH] = pMfeDev->stQpCtl.ubIFrameHighB;
    stFrmQPBoundCtl.ubQPBound[P_FRAME][BD_LOW]  = pMfeDev->stQpCtl.ubPFrameLowB;
    stFrmQPBoundCtl.ubQPBound[P_FRAME][BD_HIGH] = pMfeDev->stQpCtl.ubPFrameHighB;

    stMBQPBoundCtl.ubQPBound[I_FRAME][BD_LOW]   = pMfeDev->stQpCtl.ubIMBLowB;
    stMBQPBoundCtl.ubQPBound[I_FRAME][BD_HIGH]  = pMfeDev->stQpCtl.ubIMBHighB;
    stMBQPBoundCtl.ubQPBound[P_FRAME][BD_LOW]   = pMfeDev->stQpCtl.ubPMBLowB;
    stMBQPBoundCtl.ubQPBound[P_FRAME][BD_HIGH]  = pMfeDev->stQpCtl.ubPMBHighB;

    eRetErr = MMPF_VIDENC_SetQualityEx(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID),
                                       ulTgtFrmSize,
                                       (MMP_ULONG)pMfeDev->ulBitrate,
                                       &stFrmQPBoundCtl,
                                       &stMBQPBoundCtl);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set Quality Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    eRetErr = MMPF_VIDENC_SetSnrFrameRate(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID),
                                          pMfeDev->usStreamType,
                                          pSnrFps->usTimeIncre,
                                          pSnrFps->usTimeResol);

    eRetErr |= MMPF_VIDENC_SetEncFrameRate(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID),
                                           pEncFps->usTimeIncre,
                                           pEncFps->usTimeResol);

    eRetErr |= MMPF_VIDMGR_SetFrameRate(pMfeDev->usStreamType,
                                        pMgrFps->usTimeIncre,
                                        pMgrFps->usTimeResol);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set Frame Rate Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    MS_CAM20_GetCOLORTRANS(0, &colorType);
    if (DrvPM_GetChipID() == CHIP_ID_M5) {
        if (colorType.stManual.paraAPI.Y_OFST == 64) {
            ulVidFullRange = 0;
        }
        else {
            ulVidFullRange = 1;
        }
    }
    else if (DrvPM_GetChipID() == CHIP_ID_M5U){
        ulVidFullRange = 0;
    }
    else {
        COMPONENT_MFE_DBG_ERR(1, "MFE Strange ID: %x\n", DrvPM_GetChipID());
        if (colorType.stManual.paraAPI.Y_OFST == 64) {
                ulVidFullRange = 0;
        }
        else {
                ulVidFullRange = 1;
        }
    }
    eRetErr = MMPF_VIDENC_SetMfeVUIInfo(MMPF_H264ENC_GetHandle(pMfeDev->ubEncID),
                                        1, 1, ulVidFullRange, 1, 5, 1, ulTimingInfoPres);
    if (eRetErr != MMP_ERR_NONE) {
        COMPONENT_MFE_DBG_ERR(1, "[%s] Set VUI Err\r\n", pComp->name);
        return MMP_3GPRECD_ERR_UNSUPPORTED_PARAMETERS;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_CloseDevice(void *handler)
{
    //MMP_COMPONENT_BASE      *pComp  = (MMP_COMPONENT_BASE *)handler;
    //COMPONENT_MFE_DBG_ERR(1, "[%s] [%s] \r\n",__FUNCTION__ ,pComp->name);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE   *pMfeDev    = &Component_MFE_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pMfeMem    = &Component_MFE_Memory[0];
    MFE_COMP_ENC_RESOL          *pMfeResol  = &pMfeDev->stEncWH;
    MFE_COMP_FPS                *pMfeSnrFps = &pMfeDev->stSnrFps;
    MFE_COMP_FPS                *pMfeEncFps = &pMfeDev->stEncFps;
    MFE_COMP_FPS                *pMfeMgrFps = &pMfeDev->stMgrFps;

    if (strcmp("MFE0", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[0];
        pMfeMem = &Component_MFE_Memory[0];
    }
    else if (strcmp("MFE1", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[1];
        pMfeMem = &Component_MFE_Memory[1];
    }
    else if (strcmp("MFE2", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[2];
        pMfeMem = &Component_MFE_Memory[2];
    }
    else if (strcmp("MFE3", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[3];
        pMfeMem = &Component_MFE_Memory[3];
    }
    else if (strcmp("MFE4", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[4];
        pMfeMem = &Component_MFE_Memory[4];
    }
    else if (strcmp("MFE5", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[5];
        pMfeMem = &Component_MFE_Memory[5];
    }
    else {
        COMPONENT_MFE_DBG_ERR(1, "[%s] UnSupport MFE Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    pMfeResol  = &pMfeDev->stEncWH;
    pMfeSnrFps = &pMfeDev->stSnrFps;
    pMfeEncFps = &pMfeDev->stEncFps;
    pMfeMgrFps = &pMfeDev->stMgrFps;

    switch(type) {
    case MFE_COMP_PARAM_STRM_TYPE:
        pMfeDev->usStreamType = *(MMP_USHORT*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update StrmType [%d]\r\n", pComp->name, pMfeDev->usStreamType);
        break;
    case MFE_COMP_PARAM_BITRATE:
        pMfeDev->ulBitrate = *(MMP_ULONG*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Bitrate [%d]\r\n", pComp->name, pMfeDev->ulBitrate);
        break;
    case MFE_COMP_PARAM_P_FRM_CNT:
        pMfeDev->ulPframeNum = *(MMP_ULONG*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update P-Frm [%d]\r\n", pComp->name, pMfeDev->ulPframeNum);
        break;
    case MFE_COMP_PARAM_PROFILE:
        pMfeDev->eProfile = *(MFE_COMP_PROFILE*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Profile [%d]\r\n", pComp->name, pMfeDev->eProfile);
        break;
    case MFE_COMP_PARAM_PIX_FMT:
        pMfeDev->ePixFmt = *(MFE_COMP_PIXFMT*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update PixFmt [%d]\r\n", pComp->name, pMfeDev->ePixFmt);
        break;
    case MFE_COMP_PARAM_RESOLUTION:
        memcpy(pMfeResol, (MFE_COMP_ENC_RESOL*)pParam, sizeof(MFE_COMP_ENC_RESOL));
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Enc Resol [%d][%d][%d][%d]\r\n", pComp->name,
                              pMfeResol->ulEncW, pMfeResol->ulEncH, pMfeResol->ulEncBufW, pMfeResol->ulEncBufH);
        break;
    case MFE_COMP_PARAM_SNR_FPS:
        memcpy(pMfeSnrFps, (MFE_COMP_FPS*)pParam, sizeof(MFE_COMP_FPS));
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update SnrFps [%d][%d]\r\n", pComp->name, pMfeSnrFps->usTimeIncre, pMfeSnrFps->usTimeResol);
        break;
    case MFE_COMP_PARAM_ENC_FPS:
        memcpy(pMfeEncFps, (MFE_COMP_FPS*)pParam, sizeof(MFE_COMP_FPS));
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update EncFps [%d][%d]\r\n", pComp->name, pMfeEncFps->usTimeIncre, pMfeEncFps->usTimeResol);
        break;
    case MFE_COMP_PARAM_MGR_FPS:
        memcpy(pMfeMgrFps, (MFE_COMP_FPS*)pParam, sizeof(MFE_COMP_FPS));
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update MgrFps [%d][%d]\r\n", pComp->name, pMfeMgrFps->usTimeIncre, pMfeMgrFps->usTimeResol);
        break;
    case MFE_COMP_PARAM_BUF_COUNT:
        pMfeMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pMfeMem->ubBufNum);
        break;
    case MFE_COMP_PARAM_BUF_SIZE:
        pMfeMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Buf Size [%d]\r\n", pComp->name, pMfeMem->ulBufSize);
        break;
    case MFE_COMP_PARAM_NEARRING_THD:
        pMfeMem->ulNearRingThd = *(MMP_ULONG*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Near-Ring Thd [%d]\r\n", pComp->name, pMfeMem->ulNearRingThd);
        break;
    case MFE_COMP_PARAM_LINE_OFFSET:
        pMfeDev->usLineOffset = *(MMP_USHORT*)pParam;
        COMPONENT_MFE_DBG_MSG(1, "[%s] Update Line Offset [%d]\r\n", pComp->name, pMfeDev->usLineOffset);
        break;
    default:
        COMPONENT_MFE_DBG_ERR(1, "[%s] SetParamr UnSupport Type\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_GetStaticParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_MFE_GetStaticParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp   = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE   *pMfeDev = &Component_MFE_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pMfeMem = pComp->MemoryInfo;

    if (strcmp("MFE0", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[0];
    }
    else if (strcmp("MFE1", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[1];
    }
    else if (strcmp("MFE2", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[2];
    }
    else if (strcmp("MFE3", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[3];
    }
    else if (strcmp("MFE4", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[4];
    }
    else if (strcmp("MFE5", pComp->name) == 0) {
        pMfeDev = &Component_MFE_Handler[5];
    }
    else {
        COMPONENT_MFE_DBG_ERR(1, "[%s] UnSupport MFE Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case MFE_COMP_PARAM_ENC_ID:
        *(MMP_UBYTE*)pParam = pMfeDev->ubEncID;
        break;
    case MFE_COMP_PARAM_STRM_TYPE:
        *(MMP_USHORT*)pParam = pMfeDev->usStreamType;
        break;
    case MFE_COMP_PARAM_BITRATE:
        *(MMP_ULONG*)pParam = pMfeDev->ulBitrate;
        break;
    case MFE_COMP_PARAM_P_FRM_CNT:
        *(MMP_ULONG*)pParam = pMfeDev->ulPframeNum;
        break;
    case MFE_COMP_PARAM_PROFILE:
        *(MFE_COMP_PROFILE*)pParam = pMfeDev->eProfile;
        break;
    case MFE_COMP_PARAM_PIX_FMT:
        *(MFE_COMP_PIXFMT*)pParam = pMfeDev->ePixFmt;
        break;
    case MFE_COMP_PARAM_RESOLUTION:
        memcpy(pParam, &pMfeDev->stEncWH, sizeof(MFE_COMP_ENC_RESOL));
        break;
    case MFE_COMP_PARAM_SNR_FPS:
        memcpy(pParam, &pMfeDev->stSnrFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_ENC_FPS:
        memcpy(pParam, &pMfeDev->stEncFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_MGR_FPS:
        memcpy(pParam, &pMfeDev->stMgrFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_BUF_COUNT:
        *(MMP_UBYTE*)pParam = pMfeMem->ubBufNum;
        break;
    case MFE_COMP_PARAM_BUF_SIZE:
        *(MMP_ULONG*)pParam = pMfeMem->ulBufSize;
        break;
    case MFE_COMP_PARAM_NEARRING_THD:
        *(MMP_ULONG*)pParam = pMfeMem->ulNearRingThd;
        break;
    case MFE_COMP_PARAM_LINE_OFFSET:
        *(MMP_USHORT*)pParam = pMfeDev->usLineOffset;
        break;
    default:
        COMPONENT_MFE_DBG_ERR(1, "MFE_GetParamr UnSupport Type\r\n");
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_GetRunTimeParam
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_MFE_GetRunTimeParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp   = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE   *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMfeMem = pComp->MemoryInfo;

    if (strcmp("MFE0", pComp->name) == 0 ||
        strcmp("MFE1", pComp->name) == 0 ||
        strcmp("MFE2", pComp->name) == 0 ||
        strcmp("MFE3", pComp->name) == 0 ||
        strcmp("MFE4", pComp->name) == 0 ||
        strcmp("MFE5", pComp->name) == 0) {
        // NOP
    }
    else {
        COMPONENT_MFE_DBG_ERR(1, "[%s] UnSupport MFE Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case MFE_COMP_PARAM_ENC_ID:
        *(MMP_UBYTE*)pParam = pMfeDev->ubEncID;
        break;
    case MFE_COMP_PARAM_STRM_TYPE:
        *(MMP_USHORT*)pParam = pMfeDev->usStreamType;
        break;
    case MFE_COMP_PARAM_BITRATE:
        *(MMP_ULONG*)pParam = pMfeDev->ulBitrate;
        break;
    case MFE_COMP_PARAM_P_FRM_CNT:
        *(MMP_ULONG*)pParam = pMfeDev->ulPframeNum;
        break;
    case MFE_COMP_PARAM_PROFILE:
        *(MFE_COMP_PROFILE*)pParam = pMfeDev->eProfile;
        break;
    case MFE_COMP_PARAM_PIX_FMT:
        *(MFE_COMP_PIXFMT*)pParam = pMfeDev->ePixFmt;
        break;
    case MFE_COMP_PARAM_RESOLUTION:
        memcpy(pParam, &pMfeDev->stEncWH, sizeof(MFE_COMP_ENC_RESOL));
        break;
    case MFE_COMP_PARAM_SNR_FPS:
        memcpy(pParam, &pMfeDev->stSnrFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_ENC_FPS:
        memcpy(pParam, &pMfeDev->stEncFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_MGR_FPS:
        memcpy(pParam, &pMfeDev->stMgrFps, sizeof(MFE_COMP_FPS));
        break;
    case MFE_COMP_PARAM_BUF_COUNT:
        *(MMP_UBYTE*)pParam = pMfeMem->ubBufNum;
        break;
    case MFE_COMP_PARAM_BUF_SIZE:
        *(MMP_ULONG*)pParam = pMfeMem->ulBufSize;
        break;
    case MFE_COMP_PARAM_NEARRING_THD:
        *(MMP_ULONG*)pParam = pMfeMem->ulNearRingThd;
        break;
    case MFE_COMP_PARAM_LINE_OFFSET:
        *(MMP_USHORT*)pParam = pMfeDev->usLineOffset;
        break;
    default:
        COMPONENT_MFE_DBG_ERR(1, "MFE_GetParamr UnSupport Type\r\n");
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if (pComp->ulState != MMP_COMPONENT_STATE_IDLE) {
        return Component_MFE_GetStaticParam(handler, type, pParam);
    }
    else {
        return Component_MFE_GetRunTimeParam(handler, type, pParam);
    }
}

static u32 _GetTime(void)
{
    CamOsTimespec_t tTime;

    CamOsGetMonotonicTime(&tTime);

    return ((tTime.nSec*1000000+ tTime.nNanoSec/1000));
}

static void Component_mfe_CalculateFPS(void)
{
    int AverageFrameNu = 100;
    static int u32ISRCount = 0;
    static int u32Tmr1, u32Tmr2, u32Duration;

    if(u32ISRCount == 0) {
        u32Tmr1 = _GetTime();
    }

    if(u32ISRCount == AverageFrameNu) {
        u32Tmr2 = _GetTime();
        u32Duration = (u32Tmr2 - u32Tmr1)/AverageFrameNu;
        UartSendTrace("MFE0 frame duration = %d micro sec, FPS = %d / 1000\r\n\r\n", u32Duration, 1000*1000*1000/u32Duration);
        u32ISRCount = 0;
    }
    else {
        u32ISRCount++;
    }
}


//------------------------------------------------------------------------------
//  Function    : Component_MFE_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE       *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;
    MFE_COMP_ENC_RESOL              *pEncWH = &pMfeDev->stEncWH;
    MMP_ULONG                       ulInAddr = pComp->pInPort->bufInfo.ulBufAddr;
    //MMP_ULONG                     ulInTime = pComp->pInPort->bufInfo.ulTime;
    MMP_ULONG                       ulFrmType = COMP_BUF_INVALID_FRM_TYPE;
    VIDENC_INPUT_ATTR               stEncInputAttr;
    MMP_ERR                         eRetErr = MMP_ERR_NONE;
    #if (SUPPORT_MFE_SHAREBUFFER)
    MMP_ULONG                       ulPreCompAddr[COMP_MAX_OUTBUF_NUM];
    MMP_ULONG                       ulPreCompBufNum = 0;
    MMP_ULONG                       i = 0;
    #endif

    if ((pMfeDev->usStreamType == VIDENC_STREAM_PRM_RECD)) {
        if(GetCheckFPSEnable(0))
            Component_mfe_CalculateFPS();
    }

    if (pMfeDev->bEncodeEn == MMP_FALSE) {
        ulFrmType = (pComp->pInPort->bufInfo.ulFrmType == COMP_BUF_FRM_TYPE_H264_I) ?
                    (VIDENC_I_FRAME) : (VIDENC_P_FRAME);

        eRetErr = MMPF_VIDENC_InputFrameDirectOut(pMfeDev->usStreamType,
                                                  ulInAddr,
                                                  ulSize,
                                                  MMPF_VIDMGR_GetTimeCounter(),
                                                  ulFrmType);
        if (MMP_COMPONENT_ADV_RDIDX == eRetErr) {
            MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        }
    }
    else {
        // Fill Input Frame Information
        stEncInputAttr.pComp          = pComp;
        stEncInputAttr.usStreamType   = pMfeDev->usStreamType;
        stEncInputAttr.ulInstId       = pMfeDev->ubEncID;
        stEncInputAttr.ulBufAddr      = ulInAddr;
        stEncInputAttr.ulBufWidth     = pEncWH->ulEncBufW;
        stEncInputAttr.ulBufHeight    = pEncWH->ulEncBufH;
        stEncInputAttr.ulBufFmt422    = (pMfeDev->ePixFmt == MFE_COMP_PIXFMT_YUYV || pMfeDev->ePixFmt == MFE_COMP_PIXFMT_YVYU) ? (1) : (0);
        stEncInputAttr.ulBufTime      = MMPF_VIDMGR_GetTimeCounter(); // ulInTime;
    #if (SUPPORT_MFE_SHAREBUFFER)
        stEncInputAttr.usLineBias     = pComp->pInPort->bufInfo.ulBufBias / pEncWH->ulEncBufW;

        MMP_CompCtl_GetBufferInfo((void *)pComp->pInPort->PrevComponent, &ulPreCompBufNum, ulPreCompAddr);

        for (i = 0; i < ulPreCompBufNum; i++) {
        #if (COMPONENT_SUPPORT_ORDER == 0)
            if (ulInAddr == ulPreCompAddr[i]) { // Find Current Buffer Index

                if (i == 0) {
                    stEncInputAttr.ulGenBufAddr = ulPreCompAddr[ulPreCompBufNum - 1];
                }
                else {
                    stEncInputAttr.ulGenBufAddr = ulPreCompAddr[i - 1];
                }

                if (i == (ulPreCompBufNum -1)) {
                    stEncInputAttr.ulRefBufAddr = ulPreCompAddr[0];
                }
                else {
                    stEncInputAttr.ulRefBufAddr = ulPreCompAddr[i + 1];
                }
                break;
            }
        #else
            if (ulInAddr == ulPreCompAddr[i]) {
                stEncInputAttr.ulGenBufAddr = ulPreCompAddr[i]; // Share Gen with current
                if (i == 0) {
                    stEncInputAttr.ulRefBufAddr = ulPreCompAddr[ulPreCompBufNum - 1];
                }
                else {
                    stEncInputAttr.ulRefBufAddr = ulPreCompAddr[i - 1];
                }
                break;
            }
        #endif
        }
    #else
        stEncInputAttr.usLineBias = 0;
    #endif

        eRetErr = MMPF_VIDENC_InputFrameReady(pMfeDev->ubEncID, stEncInputAttr);
        if (MMP_COMPONENT_ADV_RDIDX == eRetErr) {
            MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        }
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_UpdateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *pvBufInfo)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pMem->MemMode == MMP_COMPONENT_MEMORY_RING ||
        pMem->MemMode == MMP_COMPONENT_MEMORY_NEARRING) {

        pMem->memctl.ring.ulWL = ALIGN32(pMem->memctl.ring.ulWL);
        if (pMem->MemMode == MMP_COMPONENT_MEMORY_NEARRING) { // Match the write pointer with read pointer.
            if ((pMem->memctl.ring.ulWL + pMem->ulNearRingThd) >= pMem->ulBufSize) {
                 pMem->memctl.ring.ulWL = 0;
                 pMem->memctl.ring.ulWH++;
            }
        }
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_AllocateBuffer(void *handler)
{
#if 0 // Move to Open Component
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_MFE   *pDev = pComp->DeviceInfo;

    MMPD_H264ENC_SetBitstreamBuf(pDev->ubEncID, pBuf[0].ulBufAddr, pMem->ulBufSize);
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_MFE_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_MFE_FreeBuffer(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MFE   *pMfeDev = (MMP_COMPONENT_HANDLER_MFE *)pComp->DeviceInfo;

    if (pMfeDev->ubUseType == MFE_COMP_UVC_RECD) {
        return MMPS_3GPRECD_FreeUVCEncMemory(pMfeDev->usStreamType);
    }
    else {
        return MMPS_3GPRECD_FreeH264Memory(pMfeDev->ubEncID);
    }
}
