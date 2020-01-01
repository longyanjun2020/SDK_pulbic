//------------------------------------------------------------------------------
//
//  File        : component_raws.c
//  Description : Source file of Sensor configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_raws.h"
#include "os_wrap.h"
#include "mmpf_hif.h"
#include "cam_os_wrapper.h"
#include "drv_isp.h"
#include "component_cfg.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_RAWS_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_RAWS_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_RawS_BufInfo[RAWS_COMP_USAGE_NUM][COMP_MAX_OUTBUF_NUM] = {NULL};
MMP_COMPONENT_HANDLER_RAW Component_RawS_Handler[RAWS_COMP_USAGE_NUM] = {NULL};
MMP_COMPONENT_MEMORY_INFO Component_RawS_Memory[RAWS_COMP_USAGE_NUM] = {NULL};
MMP_COMPONENT_PORT_INFO Component_RawS_OutPort[RAWS_COMP_USAGE_NUM][5];

static MMP_UBYTE m_ubBt656Field[RAWS_COMP_USAGE_NUM] = {0};
static u32 ulRawStoreLineCntTick[3] = {0};

MMP_COMPONENT_BASE Component_RawS[RAWS_COMP_USAGE_NUM] =
{
    {
        "RAWS_CH0",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_RawS_Memory[0],              // MemoryInfo
        &Component_RawS_BufInfo[0],             // BufferInfo
        NULL,                                   // pInPort
        &Component_RawS_OutPort[0],             // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_RawS_InitDevice,              // pfInit
        Component_RawS_Ch0_OpenDevice,          // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_RawS_UnInitDevice,            // pfUnInit
        Component_RawS_CloseDevice,             // pfClose
        Component_RawS_SetParam,                // pfSetParameter
        Component_RawS_GetParam,                // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        NULL,                                   // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_RawS_Handler[0]              // DeviceInfo
    },
    {
        "RAWS_CH1",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_RawS_Memory[1],              // MemoryInfo
        &Component_RawS_BufInfo[1],             // BufferInfo
        NULL,                                   // pInPort
        &Component_RawS_OutPort[1],             // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_RawS_InitDevice,              // pfInit
        Component_RawS_Ch1_OpenDevice,          // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_RawS_UnInitDevice,            // pfUnInit
        Component_RawS_CloseDevice,             // pfClose
        Component_RawS_SetParam,                // pfSetParameter
        Component_RawS_GetParam,                // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        NULL,                                   // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_RawS_Handler[1]              // DeviceInfo
    },
    {
        "RAWS_CH2",
        MMP_COMPONENT_STATE_INVALID,            // ulState
        MMP_TRUE,                               // bRegistered
        MMP_FALSE,                              // bByPass
        0,                                      // ubOutputPortNum
        &Component_RawS_Memory[2],              // MemoryInfo
        &Component_RawS_BufInfo[2],             // BufferInfo
        NULL,                                   // pInPort
        &Component_RawS_OutPort[2],             // pOutPort
        {
            MMP_CompCtl_UpdateBuffer_Frm,
            MMP_CompCtl_EmptyBuffer_Frm,
            MMP_CompCtl_EmptyOrderBuffer_Frm,
            MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_RawS_InitDevice,              // pfInit
        Component_RawS_Ch2_OpenDevice,          // pfOpen
        NULL,                                   // pfAllocateMemory
        NULL,                                   // pfFreeMemory
        Component_RawS_UnInitDevice,            // pfUnInit
        Component_RawS_CloseDevice,             // pfClose
        Component_RawS_SetParam,                // pfSetParameter
        Component_RawS_GetParam,                // pfGetParameter
        NULL,                                   // pfUpdateBuffer
        NULL,                                   // pfEmptyBuffer
        NULL,                                   // pfEmptyBufferDone
        NULL,                                   // pfGetBufferInfo
        &Component_RawS_Handler[2]              // DeviceInfo
    }
};

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

static MMP_ERR Component_RawS_Common_LineCntHit(void* handle, MMP_ULONG nChannel);
static void Component_RawS_Ch0_LineCntHit(unsigned int ulchannel);
static void Component_RawS_Ch1_LineCntHit(unsigned int ulchannel);
static void Component_RawS_Ch2_LineCntHit(unsigned int ulchannel);
static MMP_ERR Component_RawS_Common_EmptyBuffer(void* handle, MMP_ULONG nChannel);
static void Component_RawS_Ch0_EmptyBuffer(unsigned int ulchannel);
static void Component_RawS_Ch1_EmptyBuffer(unsigned int ulchannel);
static void Component_RawS_Ch2_EmptyBuffer(unsigned int ulchannel);

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : Component_RawS_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Common_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_Common_OpenDevice(void *handler, MMP_ULONG ulChannel)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_HANDLER_RAW   *pRawSDev = (MMP_COMPONENT_HANDLER_RAW *)pComp->DeviceInfo;
    int                         nErr = 0;

    if (pRawSDev->ubSigType == RAWS_COMP_SIG_TYPE_INTERLACE) {
        m_ubBt656Field[ulChannel] = 0;
    }

    nErr = cameraSetRAWStoreMode(ulChannel, pRawSDev->usWidth, pRawSDev->usHeight, (unsigned int)pBuf->u64BufMiuAddr);

    switch (ulChannel) {
    case 0:
        nErr = cameraSetRAWStoreLineCntCallBack(ulChannel, Component_RawS_Ch0_LineCntHit);
        nErr = cameraSetRAWStoreStartCallBack(ulChannel, Component_RawS_Ch0_EmptyBuffer);
        break;
    case 1:
        nErr = cameraSetRAWStoreLineCntCallBack(ulChannel, Component_RawS_Ch1_LineCntHit);
        nErr = cameraSetRAWStoreStartCallBack(ulChannel, Component_RawS_Ch1_EmptyBuffer);
        break;
    case 2:
        nErr = cameraSetRAWStoreLineCntCallBack(ulChannel, Component_RawS_Ch2_LineCntHit);
        nErr = cameraSetRAWStoreStartCallBack(ulChannel, Component_RawS_Ch2_EmptyBuffer);
        break;
    default:
        COMPONENT_RAWS_DBG_ERR(1, "[%s] UnSupport RAWS Comp Name\r\n", pComp->name);
        break;
    }

    pComp->ulState = MMP_COMPONENT_STATE_IDLE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch0_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_Ch0_OpenDevice(void *handler)
{
    return Component_RawS_Common_OpenDevice(handler, 0);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch1_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_Ch1_OpenDevice(void *handler)
{
    return Component_RawS_Common_OpenDevice(handler, 1);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch2_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_Ch2_OpenDevice(void *handler)
{
    return Component_RawS_Common_OpenDevice(handler, 2);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_CloseDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_CloseDevice(void *handler)
{
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    pComp->ulState = MMP_COMPONENT_STATE_LOADED;
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_RAW   *pRawSDev   = (MMP_COMPONENT_HANDLER_RAW *)pComp->DeviceInfo;
    MMP_COMPONENT_HANDLER_RAW   *pRawS      = &Component_RAWS_Handler[0];
    MMP_COMPONENT_MEMORY_INFO   *pRawSMem   = &Component_RAWS_Memory[0];

    if (strcmp("RAWS_CH0", pComp->name) == 0) {
        pRawS    = &Component_RAWS_Handler[0];
        pRawSMem = &Component_RAWS_Memory[0];
    }
    else if (strcmp("RAWS_CH1", pComp->name) == 0) {
        pRawS    = &Component_RAWS_Handler[1];
        pRawSMem = &Component_RAWS_Memory[1];
    }
    else if (strcmp("RAWS_CH2", pComp->name) == 0) {
        pRawS    = &Component_RAWS_Handler[2];
        pRawSMem = &Component_RAWS_Memory[2];
    }
    else {
        COMPONENT_RAWS_DBG_ERR(1, "[%s] UnSupport RAWS Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type)
    {
    case RAWS_COMP_PARAM_WIDTH:
        pRawS->usWidth = *(MMP_USHORT*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Store Width [%d]\r\n", pComp->name, pRawS->usWidth);
        break;
    case RAWS_COMP_PARAM_HEIGHT:
        pRawS->usHeight = *(MMP_USHORT*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Store Height [%d]\r\n", pComp->name, pRawS->usHeight);
        break;
    case RAWS_COMP_PARAM_SNR_SEL:
        pRawS->ubSnrSel = *(MMP_UBYTE*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Snr Sel [%d]\r\n", pComp->name, pRawS->ubSnrSel);
        break;
    case RAWS_COMP_PARAM_SIGNAL_TYPE:
        pRawSDev->ubSigType = *(MMP_UBYTE*)pParam; // For RunTime Change
        pRawS->ubSigType = *(MMP_UBYTE*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Signal Type [%d][%d]\r\n", pComp->name, pRawS->ubSigType, pRawSDev->ubSigType);
        break;
    case RAWS_COMP_PARAM_BUF_COUNT:
        pRawSMem->ubBufNum = *(MMP_UBYTE*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Buf Count [%d]\r\n", pComp->name, pRawSMem->ubBufNum);
        break;
    case RAWS_COMP_PARAM_BUF_SIZE:
        pRawSMem->ulBufSize = *(MMP_ULONG*)pParam;
        COMPONENT_RAWS_DBG_MSG(1, "[%s] Update Buf Size [%d] Bytes\r\n", pComp->name, pRawSMem->ulBufSize);
        break;
    default:
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_RawS_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp      = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_RAW   *pRawSDev   = (MMP_COMPONENT_HANDLER_RAW *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO   *pRawSMem    = pComp->MemoryInfo;

    if ((strcmp("RAWS_CH0", pComp->name) == 0) ||
        (strcmp("RAWS_CH1", pComp->name) == 0) ||
        (strcmp("RAWS_CH2", pComp->name) == 0)) {
    }
    else {
        COMPONENT_RAWS_DBG_ERR(1, "[%s] UnSupport RawS Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case RAWS_COMP_PARAM_WIDTH:
        *(MMP_USHORT*)pParam = pRawSDev->usWidth;
        break;
    case RAWS_COMP_PARAM_HEIGHT:
        *(MMP_USHORT*)pParam = pRawSDev->usHeight;
        break;
    case RAWS_COMP_PARAM_SNR_SEL:
        *(MMP_UBYTE*)pParam = pRawSDev->ubSnrSel;
        break;
    case RAWS_COMP_PARAM_SIGNAL_TYPE:
        *(MMP_UBYTE*)pParam = pRawSDev->ubSigType;
        break;
    case RAWS_COMP_PARAM_BUF_COUNT:
        *(MMP_UBYTE*)pParam = pRawSMem->ubBufNum;
        break;
    case RAWS_COMP_PARAM_BUF_SIZE:
        *(MMP_ULONG*)pParam = pRawSMem->ulBufSize;
        break;
    default:
        COMPONENT_RAWS_DBG_ERR(1, "RawS_GetParamr UnSupport Type\r\n");
        break;
    }

    return MMP_ERR_NONE;
}

static u32 _GetTime(void)
{
    CamOsTimespec_t tTime;

    CamOsGetMonotonicTime(&tTime);

    return ((tTime.nSec*1000000+ tTime.nNanoSec/1000));
}

static void _CheckRawActive(MMP_ULONG ulChannel)
{
    u32     ulCurTick;
    ISP_DRV_HANDLE isp_drv_handle = NULL;
    MMP_COMPONENT_BASE *pRaw1 = &Component_RawS[1];
    MMP_COMPONENT_BASE *pRaw2 = &Component_RawS[2];

	//if line cnt hit interval > 33 ms, reset isp
	ulCurTick = _GetTime()/1000;
    isp_drv_handle = cameraGetDrvHandle();

    if((ulCurTick < ulRawStoreLineCntTick[RAWS_COMP_IDX]) || (ulCurTick < ulRawStoreLineCntTick[RAWS_COMP_IDX2]))
    {
        ulRawStoreLineCntTick[RAWS_COMP_IDX] = ulCurTick;
        ulRawStoreLineCntTick[RAWS_COMP_IDX2] = ulCurTick;
        return;
    }

	if((pRaw1->ulState == MMP_COMPONENT_STATE_IDLE) && ((ulCurTick - ulRawStoreLineCntTick[RAWS_COMP_IDX]) > 330) && (ulRawStoreLineCntTick[RAWS_COMP_IDX] != 0)){
		//isp reset
		UartSendTrace("Time interval %d\n",(ulCurTick - ulRawStoreLineCntTick[RAWS_COMP_IDX]));
		UartSendTrace("DrvIsp_Reset %d\n",RAWS_COMP_IDX);

		DrvIspEnableHwRegShadow(isp_drv_handle, RAWS_COMP_IDX, 0);
		DrvVif_ChannelMask(RAWS_COMP_IDX, 1);
		DrvIsp_Reset(RAWS_COMP_IDX);
		DrvVif_ChannelMask(RAWS_COMP_IDX, 0);
		DrvIspEnableHwRegShadow(isp_drv_handle, RAWS_COMP_IDX, 1);
        ulRawStoreLineCntTick[RAWS_COMP_IDX] = ulCurTick;
	}
    if((pRaw1->ulState == MMP_COMPONENT_STATE_IDLE) && ((ulCurTick - ulRawStoreLineCntTick[RAWS_COMP_IDX2]) > 330) && (ulRawStoreLineCntTick[RAWS_COMP_IDX2] != 0)){
		//isp reset
		UartSendTrace("Time interval %d\n",(ulCurTick - ulRawStoreLineCntTick[RAWS_COMP_IDX2]));
		UartSendTrace("DrvIsp_Reset %d\n",RAWS_COMP_IDX2);

		DrvIspEnableHwRegShadow(isp_drv_handle, RAWS_COMP_IDX2, 0);
		DrvVif_ChannelMask(RAWS_COMP_IDX2, 1);
		DrvIsp_Reset(RAWS_COMP_IDX2);
		DrvVif_ChannelMask(RAWS_COMP_IDX2, 0);
		DrvIspEnableHwRegShadow(isp_drv_handle, RAWS_COMP_IDX2, 1);
        ulRawStoreLineCntTick[RAWS_COMP_IDX2] = ulCurTick;
	}

	ulRawStoreLineCntTick[ulChannel] = ulCurTick;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Common_LineCntHit
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_RawS_Common_LineCntHit(void* handle, MMP_ULONG ulChannel)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handle;
    MMP_COMPONENT_HANDLER_RAW   *pRawSDev = (MMP_COMPONENT_HANDLER_RAW *)pComp->DeviceInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_UBYTE                   ubIndex = 0;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    int                         nErr = 0;
    u32                         ulCurTick;
    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (pRawSDev->ubSigType == RAWS_COMP_SIG_TYPE_INTERLACE) {
        ++m_ubBt656Field[ulChannel];
    }

    ubIndex = pMem->memctl.frm.ubWBufIndex + 1;
    if (ubIndex == pMem->ubBufNum) {
        ubIndex = 0;
    }

    nErr = cameraUpdateRAWStoreAddress(ulChannel, (unsigned int)pComp->BufferInfo[ubIndex].u64BufMiuAddr);

    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch0_LineCntHit
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch0_LineCntHit(unsigned int ulchannel)
{
    Component_RawS_Common_LineCntHit(&Component_RawS[0], 0);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch1_LineCntHit
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch1_LineCntHit(unsigned int ulchannel)
{
    Component_RawS_Common_LineCntHit(&Component_RawS[1], 1);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch2_LineCntHit
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch2_LineCntHit(unsigned int ulchannel)
{
    Component_RawS_Common_LineCntHit(&Component_RawS[2], 2);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Common_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR Component_RawS_Common_EmptyBuffer(void* handle, MMP_ULONG ulChannel)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handle;
    MMP_COMPONENT_HANDLER_RAW   *pRawSDev = (MMP_COMPONENT_HANDLER_RAW *)pComp->DeviceInfo;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    u32                         ulCurTick;
    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if ((pRawSDev->usDropFrameCnt > 0) ||
        (pRawSDev->ubSigType == RAWS_COMP_SIG_TYPE_INTERLACE && (m_ubBt656Field[ulChannel] & 1))) {

        MMP_UBYTE ubCurRIndex = 0;

        // Drop this field.
        pComp->StoreDoneFunc.pfUpdateBuffer(pComp, 0, NULL);

        // Buffer usage minus
        ubCurRIndex = pMem->memctl.frm.ubRBufIndex;
        if (pBuf[ubCurRIndex].bufctl.frm.ubBufUsage > 0) {
            COMPONENT_RAWS_DBG_ERR(1, "[RAWS OV %d,%d]\r\n", ubCurRIndex, pBuf[ubCurRIndex].bufctl.frm.ubBufUsage);
        }
        pBuf[ubCurRIndex].bufctl.frm.ubBufUsage = 0;

        ubCurRIndex++;
        if (ubCurRIndex >= pMem->ubBufNum) {
            ubCurRIndex = 0;
        }
        pMem->memctl.frm.ubRBufIndex = ubCurRIndex;

        if (pRawSDev->usDropFrameCnt > 0) {
            pRawSDev->usDropFrameCnt--;
        }
    }
    else {
        eRetErr = MMP_CompCtl_StoreBufferDone(pComp, 0, NULL);
    }

    //_CheckRawActive(ulChannel);
    return eRetErr;
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch0_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch0_EmptyBuffer(unsigned int ulchannel)
{
    Component_RawS_Common_EmptyBuffer(&Component_RawS[0], 0);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch1_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch1_EmptyBuffer(unsigned int ulchannel)
{
    Component_RawS_Common_EmptyBuffer(&Component_RawS[1], 1);
}

//------------------------------------------------------------------------------
//  Function    : Component_RawS_Ch2_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
static void Component_RawS_Ch2_EmptyBuffer(unsigned int ulchannel)
{
    Component_RawS_Common_EmptyBuffer(&Component_RawS[2], 2);
}

