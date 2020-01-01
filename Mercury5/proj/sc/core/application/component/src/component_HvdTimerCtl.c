//------------------------------------------------------------------------------
//
//  File        : component_hvd.c
//  Description : Source file of timer control component configuration
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
#include "component_HvdTimerCtl.h"
#include "mmpf_media_core.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_TCL_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_TCL_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_ERR Component_TIMECTL_OpenDevice(void *handler);
MMP_ERR Component_TIMECTL_CloseDevice(void *handler);
MMP_ERR Component_TIMECTL_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_TIMECTL_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo);
// Function of Port:
MMP_ERR ComponentPort_TIMECTL_Close(void *handler);

MMP_COMPONENT_BUFFER_INFO Component_TIMECTL_BufInfo[COMP_MAX_OUTBUF_NUM] = {0}; 
MMP_COMPONENT_PORT_INFO Component_TIMECTL_InPort = {0};
MMP_COMPONENT_PORT_INFO Component_TIMECTL_OutPort[2] = {0};
MMP_COMPONENT_MEMORY_INFO Component_TIMECTL_MemoryInfo;
MMP_COMPONENT_HANDLER_TIMECTL Component_TIMECTL_DevInfo;

MMP_COMPONENT_BASE Component_TCL =
{
    "TCL",
    MMP_COMPONENT_STATE_INVALID,            // ulState
    MMP_TRUE,                               // bRegistered
    MMP_FALSE,                              // bByPass
    0,                                      // ubOutputPortNum
    &Component_TIMECTL_MemoryInfo,          // MemoryInfo
    &Component_TIMECTL_BufInfo[0],          // BufferInfo
    &Component_TIMECTL_InPort,              // pInPort
    &Component_TIMECTL_OutPort[0],          // pOutPort
    {
        &MMP_CompCtl_UpdateBuffer_Frm,
        &MMP_CompCtl_EmptyBuffer_Frm,
        &MMP_CompCtl_EmptyOrderBuffer_Frm,
        &MMP_CompCtl_EmptyBufferDone_Frm,
    },
    NULL,                                   // pfInit
    Component_TIMECTL_OpenDevice,           // pfOpen
    NULL,                                   // pfAllocateMemory
    NULL,                                   // pfFreeMemory
    NULL,                                   // pfUnInit
    Component_TIMECTL_CloseDevice,          // pfClose
    NULL,                                   // pfSetParameter
    NULL,                                   // pfGetParameter
    NULL,                                   // pfUpdateBuffer
    Component_TIMECTL_EmptyBuffer,          // pfEmptyBuffer
    Component_TIMECTL_EmptyBufferDone,      // pfEmptyBufferDone
    NULL,                                   // pfGetBufferInfo
    &Component_TIMECTL_DevInfo              // DeviceInfo
};

MMP_COMPONENT_PORT_INFO ComponentPort_TCL[MAX_OUTPUT_COMP_NUM] =
{
    { //Port0
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_TIMECTL_Close,            // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.                                                               
        &Component_TIMECTL_BufInfo[0],          // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port1
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_TIMECTL_Close,            // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.                                                               
        &Component_TIMECTL_BufInfo[0],          // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port2
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_TIMECTL_Close,            // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.                                                               
        &Component_TIMECTL_BufInfo[0],          // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port3
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_TIMECTL_Close,            // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.                                                               
        &Component_TIMECTL_BufInfo[0],          // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },
    { //Port4
        PORT_INVALID,                           // State;
        NULL,                                   // (*pfOpen)(void* handle);    // Callback for Open this port. EX: Use for jpeg capture
        ComponentPort_TIMECTL_Close,            // (*pfClose)(void* handle);   // Callback for Close this port.
        NULL,                                   // (*pfInit)(void* handle);    // Callback for Init this port. EX: Use for jpeg capture
        NULL,                                   // (*pfUnInit)(void* handle);  // Callback for Uninit this port.
                                                                              // This call back should release memory usage. With real Open MAX. This need event task handler.                                                               
        &Component_TIMECTL_BufInfo[0],          // bufInfo;                    // bufInfo keep buffer information. For ex: Buffer index/Buffer address/Time stamp.
        NULL,                                   // *pCurComponent;             // For in/out port
        NULL,                                   // *PrevComponent;             // For in port
        NULL,                                   // *NextComponent;             // For out port
    },    
};

MMP_TIMECTL_BUFCTL CmpTCtl = {0};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

MMP_ERR Component_TIMECTL_OpenDevice(void *handler)
{
    MMP_ULONG ulIdx = 0;
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BASE *pPrevComp = (MMP_COMPONENT_BASE *)pComp->pInPort->PrevComponent;
    MMP_COMPONENT_MEMORY_INFO *pPrevMem = pPrevComp->MemoryInfo;

    CmpTCtl.WCnt = CmpTCtl.RCnt = CmpTCtl.CurSkipFrmCnt = 0;

    CmpTCtl.lBufNum = pPrevMem->ubBufNum;

    for (ulIdx = 0; ulIdx < MAX_TMC_DQNUM; ulIdx++) {
        CmpTCtl.lTime[ulIdx] = UNDEFINED_TIME;
    }
    
    return MMP_ERR_NONE;
}

MMP_ERR Component_TIMECTL_CloseDevice(void *handler)
{
    MMP_ULONG ulIdx = 0;

    CmpTCtl.WCnt = CmpTCtl.RCnt = CmpTCtl.CurSkipFrmCnt = 0;

    for (ulIdx = 0; ulIdx < MAX_TMC_DQNUM; ulIdx++) {
        CmpTCtl.lTime[ulIdx] = UNDEFINED_TIME;
    }

    return MMP_ERR_NONE;
}

MMP_ERR Component_TIMECTL_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE  *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_ULONG           ulRCnt = 0, ulWCnt = 0;

    DBG_MSG_TRACE(0);

    // W:PushQ
    ulWCnt = CmpTCtl.WCnt;
    ulWCnt %= MAX_TMC_DQNUM;

    CmpTCtl.lVBuf[ulWCnt] = pComp->pInPort->bufInfo.ulBufAddr;
    CmpTCtl.l64PhyBuf[ulWCnt] = pComp->pInPort->bufInfo.u64BufPhyAddr;
    CmpTCtl.lTime[ulWCnt] = pComp->pInPort->bufInfo.ulTime;
    
    // R:PopQ
    ulRCnt = CmpTCtl.RCnt;
    ulRCnt %= MAX_TMC_DQNUM;

    pComp->BufferInfo->ulTime = CmpTCtl.lTime[ulRCnt];
    pComp->BufferInfo->ulBufAddr = CmpTCtl.lVBuf[ulRCnt];
    pComp->BufferInfo->u64BufPhyAddr = CmpTCtl.l64PhyBuf[ulRCnt];
    //pComp->BufferInfo->u64BufMiuAddr = pComp->pInPort->bufInfo.u64BufMiuAddr;

    COMPONENT_TCL_DBG_MSG(0, FG_CYAN("M:x%x(%d:%d)\n"), pComp->BufferInfo->ulTime, (CmpTCtl.WCnt%4), (CmpTCtl.RCnt%4));
    COMPONENT_TCL_DBG_MSG(0, FG_CYAN("M:x%x %2d %2d x%x\n"), pComp->BufferInfo->ulTime,
                                                             (CmpTCtl.WCnt%MAX_TMC_DQNUM),
                                                             (CmpTCtl.RCnt%MAX_TMC_DQNUM),
                                                             pComp->BufferInfo->ulBufAddr);
    COMPONENT_TCL_DBG_MSG(0, FG_CYAN("M:x%x x%x x%x\n"), pComp->BufferInfo->ulBufAddr, 
                                                         pComp->BufferInfo->u64BufPhyAddr, 
                                                         pComp->BufferInfo->ulTime);

    CmpTCtl.WCnt++;

    return MMP_ERR_NONE;
}

MMP_ERR Component_TIMECTL_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_COMPONENT_BASE              *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_TIMECTL   *pDevInf = (MMP_COMPONENT_HANDLER_TIMECTL *)pComp->DeviceInfo;

    pComp->BufferInfo->ulBufAddr = 0;
    pComp->BufferInfo->u64BufPhyAddr = 0;
    //pComp->BufferInfo->u64BufMiuAddr = 0;

    //if (CmpTCtl.CurSkipFrmCnt >= pDevInf->ulSkipStartFrmNum) 
    {
        MMP_CompCtl_EmptyBufferDoneEx(pComp, 0, NULL);
        CmpTCtl.RCnt++;
    }
    CmpTCtl.CurSkipFrmCnt++;

    MMPF_VPP_DISPLAY();

    return MMP_ERR_NONE;
}

MMP_ERR Component_TIMECTL_CleanDirty(MMP_ULONG ulLastRefreshTime, MMP_ULONG ulCurTime)
{
    MMP_UBYTE i = 0x00;
    MMP_ULONG ulRCnt = CmpTCtl.RCnt%MAX_TMC_DQNUM;
    
    for (i=ulRCnt; i<MAX_TMC_DQNUM; i++) {
        if(ulLastRefreshTime > CmpTCtl.lTime[i%MAX_TMC_DQNUM]) {
            CmpTCtl.lTime[i%MAX_TMC_DQNUM] = UNDEFINED_TIME;
        }
    }
    COMPONENT_TCL_DBG_MSG(0, FG_YELLOW("[TCL]ClrDirty!\r\n"));
    
    return 0;
}

MMP_ERR ComponentPort_TIMECTL_Close(void *handler)
{
    MMP_ULONG ulIdx = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pComp == NULL) {
        COMPONENT_TCL_DBG_ERR(1, FG_RED("Component is NULL\r\n"));
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
    
    CmpTCtl.WCnt = CmpTCtl.RCnt = CmpTCtl.lBufNum = CmpTCtl.CurSkipFrmCnt = 0;
    for (ulIdx = 0; ulIdx < MAX_TMC_DQNUM; ulIdx++) {
        CmpTCtl.lTime[ulIdx] = UNDEFINED_TIME;
    }
    COMPONENT_TCL_DBG_MSG(0, FG_YELLOW("[%s] PortClose for Flush!\r\n"), pComp->name);

    return MMP_ERR_NONE;
}

MMP_ULONG Component_TIMECTL_GetPTR(TCL_RW_PTR ubPtrType)
{
    return (ubPtrType == TCL_WPTR) ? CmpTCtl.WCnt : CmpTCtl.RCnt;
}

