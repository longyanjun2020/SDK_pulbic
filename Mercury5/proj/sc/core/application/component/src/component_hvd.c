//------------------------------------------------------------------------------
//
//  File        : component_hvd.c
//  Description : Source file of hvd component configuration
//  Author      : Tunglin
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_component_ctl.h"

#include "component_hvd.h"
#include "mmpd_system.h"
#include "cam_os_wrapper.h"
#include "apiVDEC.h"
#include "MsOS.h"
#include "mmp_vidplay_inc.h"
//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_HVD_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_HVD_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
MMP_ERR Component_HVD_InitDevice (void *handler);
MMP_ERR Component_HVD_OpenDevice (void *handler);
MMP_ERR Component_HVD_CloseDevice (void *handler);
MMP_ERR Component_HVD_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_HVD_EmptyBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_HVD_EmptyBufferDone (void *handler, MMP_ULONG ulSize, void *BufInfo);
// Function of Port:
MMP_ERR ComponentPort_HVD_Close(void *handler);

MMP_COMPONENT_BASE *pCompHVD;

//Code:
MMP_ULONG gulHVDFwRlsPtr;
MMP_ULONG gulHVDFwAlocSize;
//FB:
MMP_ULONG gulHVDFbRlsPtr;
MMP_ULONG gulHVDFbAlocSize;

MMP_ULONG gulDecErrCnt;

MMP_COMPONENT_BUFFER_INFO Component_HVD_BufInfo[COMP_MAX_OUTBUF_NUM] = {0};
MMP_COMPONENT_PORT_INFO Component_HVD_InPort = {0};
MMP_COMPONENT_PORT_INFO Component_HVD_OutPort[5] = {0};
MMP_COMPONENT_MEMORY_INFO Component_HVD_MemoryInfo;
MMP_COMPONENT_HANDLER_HVD Component_HVD_DevInfo;

MMP_COMPONENT_BASE Component_HVD =
{
    "HVD",
    MMP_COMPONENT_STATE_INVALID,            //  ulState
    MMP_TRUE,                               //  bRegistered
    MMP_FALSE,                              //  bByPass
    0,                                      //  ubOutputPortNum
    &Component_HVD_MemoryInfo,              //  MemoryInfo
    &Component_HVD_BufInfo[0],              //  BufferInfo
    NULL,                                   //  pInPort
    &Component_HVD_OutPort[0],              //  pOutPort
    {
        &MMP_CompCtl_UpdateBuffer_Frm,
        &MMP_CompCtl_EmptyBuffer_Frm,
        &MMP_CompCtl_EmptyOrderBuffer_Frm,
        &MMP_CompCtl_EmptyBufferDone_Frm,
    },
    Component_HVD_InitDevice,               //  pfInit
    Component_HVD_OpenDevice,               //  pfOpen
    NULL,                                   //  pfAllocateMemory
    NULL,                                   //  pfFreeMemory
    NULL,                                   //  pfUnInit
    Component_HVD_CloseDevice,              //  pfClose
    NULL,                                   //  pfSetParameter
    NULL,                                   //  pfGetParameter
    Component_HVD_UpdateBuffer,             //  pfUpdateBuffer
    Component_HVD_EmptyBuffer,              //  pfEmptyBuffer
    Component_HVD_EmptyBufferDone,          //  pfEmptyBufferDone  // Out memory port done(eq: Device/component work finish).
    NULL,                                   //  pfGetBufferInfo
    &Component_HVD_DevInfo                  //  DeviceInfo
};

MMP_COMPONENT_PORT_INFO ComponentPort_HVD[MAX_OUTPUT_COMP_NUM] =
{
    { //Port0
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_HVD_Close,                // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.
        &Component_HVD_BufInfo[0],              // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port1
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_HVD_Close,                // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.
        &Component_HVD_BufInfo[0],              // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port2
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_HVD_Close,                // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.
        &Component_HVD_BufInfo[0],              // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port3
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_HVD_Close,                // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.
        &Component_HVD_BufInfo[0],              // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port4
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_HVD_Close,                // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.
        &Component_HVD_BufInfo[0],              // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
};
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
MMP_ERR Component_HVD_InitDevice (void *handler)
{
    //DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    gulDecErrCnt = 0;

    return MMP_ERR_NONE;
}

MMP_ERR Component_HVD_OpenDevice (void *handler)
{
    CamOsRet_e eRet = CAM_OS_OK;
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO *pMem = pComp->MemoryInfo;
    MMP_COMPONENT_HANDLER_HVD *pDevInf = (MMP_COMPONENT_HANDLER_HVD *)pComp->DeviceInfo;
    MMP_ULONG* pHVDFwUserPtr, pHVDFbUserPtr;
    MMP_ULONG64  nHVDFwMiuAddr, nHVDFbMiuAddr;
    MMP_ULONG64  nlHVDFwPhysAddr, nlHVDFbPhysAddr;
    MMP_ULONG  ulR2FwAddr, ulR2FwSz;
    MMP_ULONG  ulR2FbAddr, ulR2FbSz;
    MMP_ULONG  ulEsAddr, ulEsSz, ulBufType;
    MMP_ULONG  ulDynHvdFbSize = 0x00000000, ulVideoCurTrack = 0x00000000;
    MMP_ULONG  ulFrmSize = 0x00000000;
    VDEC_InitParam mInitParam = {0};
    MMP_VIDEO_CONTAINER_INFO *info;

    DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    if (!pDevInf->ulIsUtMode)
    {
        MMPF_VIDPSR_GetCommonInfo(&info);
        MMPS_VIDPLAY_GetCurrentTrack(&ulVideoCurTrack);
        //CODE:
        if (!gulHVDFwRlsPtr) {
            gulHVDFwAlocSize = (COMP_HVD_CODE_BF_SZ)+(COMP_HVD_CODE_AD_ALIGN);
            CAM_OS_RET_CHK(CamOsDirectMemAlloc("HVD_FW",
                                               gulHVDFwAlocSize,
                                               &pHVDFwUserPtr,
                                               &nHVDFwMiuAddr,
                                               &nlHVDFwPhysAddr));
            gulHVDFwRlsPtr = (MMP_ULONG)pHVDFwUserPtr;
        }
        else {
            COMPONENT_HVD_DBG_ERR(1, "NoRls(HVD_FW)\r\n");
            return MMP_ERR_NONE;
        }
        //FB:
        if (!gulHVDFbRlsPtr) {
            ulFrmSize = (info->video_info[ulVideoCurTrack].width * info->video_info[ulVideoCurTrack].height * 3)>>1;
            //R2_FW -> [FB<24M : FB>=24M] / [Dos : NonDos]
            ulDynHvdFbSize = (ulFrmSize & UV_SZ_HW_LIMIT_MASK) ? ((26 * 1024 * 1024) - 0x2000) : COMP_HVD_FB_BF_SZ;
            gulHVDFbAlocSize = (ulDynHvdFbSize)+(COMP_HVD_FB_AD_ALIGN);
            #if (ALOC_NON_CACHE_FB == 0)
            pHVDFbUserPtr = (MS_PHY)MsAllocateMem(gulHVDFbAlocSize);
            #else
            CAM_OS_RET_CHK(CamOsDirectMemAlloc("HVD_FB",
                                               gulHVDFbAlocSize,
                                               &pHVDFbUserPtr,
                                               &nHVDFbMiuAddr,
                                               &nlHVDFbPhysAddr));
            #endif
            gulHVDFbRlsPtr = (MMP_ULONG)pHVDFbUserPtr;
        }
        else {
            COMPONENT_HVD_DBG_ERR(1, "NoRls(HVD_FB\r\n");
            return MMP_ERR_NONE;
        }
        //Assign ES, R2fw and FB buffer address.
        MMPF_3GPPSR_GetVideoInBuffers(&ulEsAddr, &ulEsSz, &ulBufType);

        ulR2FwAddr = ALIGN_X((MMP_ULONG)pHVDFwUserPtr, COMP_HVD_CODE_AD_ALIGN);
        ulR2FbAddr = ALIGN_X((MMP_ULONG)pHVDFbUserPtr, COMP_HVD_FB_AD_ALIGN);
        //if (ulFrmSize & UV_SZ_HW_LIMIT_MASK) { //TBD
        //    MEMSET(ulR2FbAddr, 0x00, ulDynHvdFbSize);
        //}

        mInitParam.eCodecType = E_VDEC_CODEC_TYPE_H264;
        #if (HVD_ENABLE_EMBEDDED_FW_BINARY)
        mInitParam.SysConfig.u32FWBinaryAddr = 0;
        mInitParam.SysConfig.u32FWBinarySize = 0;
        mInitParam.SysConfig.u32CodeBufAddr = MS_VA2PA(ulR2FwAddr);
        mInitParam.SysConfig.u32CodeBufSize = COMP_HVD_CODE_BF_SZ;
        #else
        mInitParam.SysConfig.u32FWBinaryAddr = 0;
        mInitParam.SysConfig.u32FWBinarySize = COMP_HVD_CODE_BF_SZ;
        mInitParam.SysConfig.u32CodeBufAddr = MS_VA2PA(ulR2FwAddr);
        mInitParam.SysConfig.u32CodeBufSize = COMP_HVD_CODE_BF_SZ;
        #endif
        mInitParam.SysConfig.u32FrameBufAddr = MS_VA2PA(ulR2FbAddr);
        mInitParam.SysConfig.u32FrameBufSize = ulDynHvdFbSize;
        mInitParam.SysConfig.u32BitstreamBufAddr = MS_VA2PA(ulEsAddr);
        mInitParam.SysConfig.u32BitstreamBufSize = ulEsSz;
        mInitParam.SysConfig.eDbgMsgLevel = MMPS_VIDPLAY_GetHvdDbgLv();
        mInitParam.SysConfig.eFWSourceType = E_VDEC_FW_SOURCE_NONE;
        mInitParam.VideoInfo.eSrcMode = E_VDEC_SRC_MODE_FILE;
        mInitParam.VideoInfo.eTimeStampType = E_VDEC_TIME_STAMP_PTS;
        mInitParam.VideoInfo.bWithoutNalStCode = FALSE;
        mInitParam.EnableDynaScale = FALSE;
        mInitParam.bDisableDropErrFrame = TRUE;
        mInitParam.bDisableErrConceal = FALSE;
        mInitParam.bRepeatLastField = TRUE;

        MApi_VDEC_EnableESBuffMalloc(TRUE);
        //MApi_VDEC_EnableLastFrameShow(MMP_FALSE);
        pDevInf->ulIsInitialDone = MApi_VDEC_Init(&mInitParam);
        //if (ulFrmSize & UV_SZ_HW_LIMIT_MASK)
        //{
        //    MApi_VDEC_DbgDpbInfo(info->video_info[ulVideoCurTrack].width,
        //                         info->video_info[ulVideoCurTrack].height,
        //                         ulR2FbAddr,
        //                         gulHVDFbAlocSize);
        //}
        MApi_VDEC_SetBlockDisplay(TRUE);
        MApi_VDEC_DispOutsideMode(TRUE);
        MDrv_HVD_PushDispQWithRefNum(TRUE);
        MApi_VDEC_Play();
    }

    return MMP_ERR_NONE;
}

MMP_ERR Component_HVD_CloseDevice (void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_HVD *pDevInf = (MMP_COMPONENT_HANDLER_HVD *)pComp->DeviceInfo;

    DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    MApi_VDEC_Exit();
    CAM_OS_RET_CHK(CamOsDirectMemRelease(gulHVDFwRlsPtr, gulHVDFwAlocSize));
    #if (ALOC_NON_CACHE_FB == 0)
    MsReleaseMemory(gulHVDFbRlsPtr);
    #else
    CAM_OS_RET_CHK(CamOsDirectMemRelease(gulHVDFbRlsPtr, gulHVDFbAlocSize));
    #endif
    gulHVDFwRlsPtr = gulHVDFbRlsPtr = 0;
    pDevInf->ulIsInitialDone = 0;

    return MMP_ERR_NONE;
}

MMP_ERR Component_HVD_UpdateBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
#if 0
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_HVD *pDevInf = (MMP_COMPONENT_HANDLER_HVD *)pComp->DeviceInfo;
    VDEC_DispFrame *pDispFrm;

    DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    if(BufInfo) {
        pDispFrm = pDevInf->pGetFrmInf;
        pBuf->ulBufAddr = MS_PA2KSEG0(pDispFrm->stFrmInfo.u32LumaAddr);
        pBuf->ulSize = (pDispFrm->stDispInfo.u16HorSize * pDispFrm->stDispInfo.u16VerSize * 3)>>1;
        pBuf->ulTime = pDispFrm->stFrmInfo.u32TimeStamp;
        //pDevInf->u32PriData[pDevInf->ulWrQIdx%pDevInf->ulQIdxNum] = pDispFrm->u32PriData;
        //pDevInf->u32Idx[pDevInf->ulWrQIdx%pDevInf->ulQIdxNum] = pDispFrm->u32Idx;
        CamOsDebug("1:u32Idx:x%x u32PriData:x%x\n", pDispFrm->u32Idx, pDispFrm->u32PriData);
        MApi_VDEC_DumpShmInfo();
    }
#endif
    return MMP_ERR_NONE;
}

MMP_ERR Component_HVD_EmptyBuffer (void *handler, MMP_ULONG ulSize, void *BufInfo)
{
#if 0
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_HVD *pDevInf = (MMP_COMPONENT_HANDLER_HVD *)pComp->DeviceInfo;
    VDEC_DispFrame *pDispFrm;

    DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    if(BufInfo) {
        pDispFrm = pDevInf->pGetFrmInf;
        pBuf->ulBufAddr = MS_PA2KSEG0(pDispFrm->stFrmInfo.u32LumaAddr);
        pBuf->ulSize = (pDispFrm->stDispInfo.u16HorSize * pDispFrm->stDispInfo.u16VerSize * 3)>>1;
        pBuf->ulTime = pDispFrm->stFrmInfo.u32TimeStamp;
        MApi_VDEC_DumpShmInfo();
    }
#endif

    return MMP_ERR_NONE;
}

MMP_ERR Component_HVD_EmptyBufferDone (void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_HVD *pDevInf = (MMP_COMPONENT_HANDLER_HVD *)pComp->DeviceInfo;
    VDEC_DispFrame *pDispFrm;

    DBG_MSG_TRACE(COMP_HVD_DBG_EN);
    pDispFrm = pDevInf->pGetFrmInf;
    COMPONENT_HVD_DBG_MSG(0, "Rls(x%x:x%x:x%x)\n", pDispFrm->stFrmInfo.u32TimeStamp,
                                                   pDispFrm->u32Idx,
                                                   pDispFrm->u32PriData);
    if (MApi_VDEC_ReleaseFrame(pDispFrm) != E_VDEC_OK) {
        COMPONENT_HVD_DBG_ERR(1, "RlsFail\n");
    }

    return MMP_ERR_NONE;
}

MMP_ERR ComponentPort_HVD_Close(void *handler)
{
    MMP_ULONG ulIdx = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pComp == NULL) {
        COMPONENT_HVD_DBG_ERR(1, FG_RED("Component is NULL\r\n"));
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
    MApi_VDEC_Flush(E_VDEC_FREEZE_AT_CUR_PIC);

    COMPONENT_HVD_DBG_MSG(0, FG_YELLOW("[%s] PortClose for Flush!\r\n"), pComp->name);

    return MMP_ERR_NONE;
}
