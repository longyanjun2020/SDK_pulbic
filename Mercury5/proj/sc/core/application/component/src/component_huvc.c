//------------------------------------------------------------------------------
//
//  File        : component_huvc.c
//  Description : Source file of host uvc component configuration
//  Author      : Titan
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "component_huvc.h"
#include "mmp_component_ctl.h"
#include "component_cfg.h"
#include "mmpf_usbh_ctl.h"
#include "cam_os_wrapper.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_HUVC_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_HUVC_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)


//==============================================================================
//
//                             extern Function
//
//==============================================================================
extern u8 GetCheckFPSEnable(u8 channel);

//==============================================================================
//
//                              Function Prototype
//
//==============================================================================

MMP_ERR Component_HUVC_InitDevice(void *handler);
MMP_ERR Component_HUVC_UnInitDevice(void *handler);
MMP_ERR Component_HUVC_OpenDevice(void *handler);
MMP_ERR Component_HUVC_SetParam(void *handler, int type, void* pParam);
MMP_ERR Component_HUVC_GetParam(void *handler, int type, void* pParam);
MMP_ERR Component_HUVC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_HUVC_StoreDone_EmptyBuffer_Frm(void *handler, MMP_ULONG ulSize, void *BufInfo);

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_COMPONENT_BUFFER_INFO Component_HUVC_BufInfo[HUVC_COMP_USAGE_NUM][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_HUVC_InPort[HUVC_COMP_USAGE_NUM];
MMP_COMPONENT_PORT_INFO Component_HUVC_OutPort[HUVC_COMP_USAGE_NUM][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_HUVC_MemoryInfo[HUVC_COMP_USAGE_NUM];
MMP_COMPONENT_HANDLER_HUVC Component_HUVC_DevInfo[HUVC_COMP_USAGE_NUM];

MMP_BOOL m_bCompHUVCRdy = MMP_FALSE;    // check if Component_HUVC gets frames

MMP_COMPONENT_BASE Component_HUVC[HUVC_COMP_USAGE_NUM] =
{
    {
        "HostUVC",
        MMP_COMPONENT_STATE_INVALID,                        // ulState
        MMP_TRUE,                                           // bRegistered
        MMP_FALSE,                                          // bByPass
        1,                                                  // ubOutputPortNum
        &Component_HUVC_MemoryInfo[HUVC_COMP_UVC],          // MemoryInfo
        Component_HUVC_BufInfo[HUVC_COMP_UVC],              // BufferInfo
        &Component_HUVC_InPort[HUVC_COMP_UVC],              // pInPort
        Component_HUVC_OutPort[HUVC_COMP_UVC],              // pOutPort
        {
            NULL,
            &Component_HUVC_StoreDone_EmptyBuffer_Frm,
            NULL,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_HUVC_InitDevice,                          // pfInit
        Component_HUVC_OpenDevice,                          // pfOpen
        NULL,                                               // pfAllocateMemory
        NULL,                                               // pfFreeMemory
        Component_HUVC_UnInitDevice,                        // pfUnInit
        NULL,                                               // pfClose
        Component_HUVC_SetParam,                            // pfSetParameter
        Component_HUVC_GetParam,                            // pfGetParameter
        NULL,                                               // pfUpdateBuffer
        Component_HUVC_EmptyBuffer,                         // pfEmptyBuffer
        NULL,                                               // pfEmptyBufferDone
        NULL,                                               // pfGetBufferInfo
        &Component_HUVC_DevInfo[HUVC_COMP_UVC],             // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
static u32 _GetTime(void)
{
    CamOsTimespec_t tTime;

    CamOsGetMonotonicTime(&tTime);

    return ((tTime.nSec*1000000+ tTime.nNanoSec/1000));
}

void Component_HUVC_CalculateFPS(void)
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
        UartSendTrace("HUVC frame duration = %d micro sec, FPS = %d / 1000\r\n", u32Duration, 1000*1000*1000/u32Duration);
        u32ISRCount = 0;
    }
    else {
        u32ISRCount++;
    }
}
//------------------------------------------------------------------------------
//  Function    : Component_HUVC_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_UnInitDevice(void *handler)
{
	MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
	MMP_COMPONENT_HANDLER_HUVC  *pDev = pComp->DeviceInfo;

    m_bCompHUVCRdy = MMP_FALSE;
	if (pDev->ubUsbMode == HUVC_COMP_USB_MODE_ISO) {
		MMPF_USBH_SetUSBRXBuffer(NULL, MMP_FALSE/*bIsBulkMode*/, MMP_TRUE/*bReset*/);
	}
	else {
		MMPF_USBH_SetUSBRXBuffer(NULL, MMP_TRUE/*bIsBulkMode*/, MMP_TRUE/*bReset*/);
	}
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_OpenDevice(void *handler)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_HUVC  *pDev = pComp->DeviceInfo;

    if (pDev->ubUsbMode == HUVC_COMP_USB_MODE_ISO) {
        MMPF_USBH_SetUSBRXBuffer(handler, MMP_FALSE/*bIsBulkMode*/, MMP_FALSE/*bReset*/);
    }
    else {
        MMPF_USBH_SetUSBRXBuffer(handler, MMP_TRUE/*bIsBulkMode*/, MMP_FALSE/*bReset*/);
    }

    m_bCompHUVCRdy = MMP_FALSE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_SetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_SetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_HUVC  *pHUVC = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pHUVCMem = NULL;

    if (strcmp("HostUVC", pComp->name) == 0) {
    	pHUVC    = &Component_HUVC_Handler[0];
    	pHUVCMem = &Component_HUVC_Memory[0];
    }
    else {
    	COMPONENT_HUVC_DBG_ERR(1, "[%s] UnSupport HUVC Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case HUVC_COMP_PARAM_USB_MODE:
    	pHUVC->ubUsbMode = *(MMP_UBYTE *)pParam;
        COMPONENT_HUVC_DBG_MSG(1, "[%s] Update USB Mode to %s\r\n",
                              pComp->name, pHUVC->ubUsbMode == HUVC_COMP_USB_MODE_ISO ? "ISO" : "BULK");
        break;
    case HUVC_COMP_PARAM_ENCODE_RES:
        memcpy(&pHUVC->stEncWH, (HUVC_COMP_RESOL*)pParam, sizeof(HUVC_COMP_RESOL));
        COMPONENT_HUVC_DBG_MSG(1, "[%s] Update Enc Res [%d][%d]\r\n",
                              pComp->name, pHUVC->stEncWH.ulW, pHUVC->stEncWH.ulH);
        break;
    case HUVC_COMP_PARAM_BUF_SIZE:
    	pHUVCMem->ulBufSize = *(MMP_ULONG *)pParam;
        COMPONENT_HUVC_DBG_MSG(1, "[%s] Update Buffer size to %d\r\n",
                              pComp->name, pHUVCMem->ulBufSize);
        break;
    case HUVC_COMP_PARAM_BUF_NUM:
    	pHUVCMem->ubBufNum = *(MMP_UBYTE *)pParam;
        COMPONENT_HUVC_DBG_MSG(1, "[%s] Update Buffer cnt to %s\r\n",
                              pComp->name, pHUVCMem->ubBufNum);
        break;
    default:
    	COMPONENT_HUVC_DBG_ERR(1, "[%s] UnSupport HUVC Param Type for SET\r\n", pComp->name);
        break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_GetParam
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_GetParam(void *handler, int type, void* pParam)
{
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_HUVC  *pHUVC = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pHUVCMem = NULL;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = NULL;
    MMP_COMPONENT_MEMORY_INFO   *pMem = NULL;

    if (strcmp("HostUVC", pComp->name) == 0) {
    	pHUVC    = &Component_HUVC_Handler[0];
    	pHUVCMem = &Component_HUVC_Memory[0];
    	pBuf	 = pComp->BufferInfo;
        pMem 	 = pComp->MemoryInfo;
    }
    else {
    	COMPONENT_HUVC_DBG_ERR(1, "[%s] UnSupport HUVC Comp Name\r\n", pComp->name);
        return MMP_ERR_NONE;
    }

    switch(type) {
    case HUVC_COMP_PARAM_USB_MODE:
    	*(MMP_UBYTE*)pParam = pHUVC->ubUsbMode;
        break;
    case HUVC_COMP_PARAM_ENCODE_RES:
    	memcpy((HUVC_COMP_RESOL*)pParam, &pHUVC->stEncWH, sizeof(HUVC_COMP_RESOL));
        break;
    case HUVC_COMP_PARAM_BUF_SIZE:
    	*(MMP_ULONG*)pParam = pHUVCMem->ulBufSize;
        break;
    case HUVC_COMP_PARAM_BUF_NUM:
    	*(MMP_UBYTE*)pParam = pHUVCMem->ubBufNum;
        break;
    case HUVC_COMP_PARAM_RUNTIME_WBUF_AVAILABLE:
    	{
    		MMP_UBYTE WBufIdx;

    		WBufIdx = *(MMP_UBYTE*)pParam;

    		if(WBufIdx > pMem->ubBufNum - 1) {
    			*(MMP_UBYTE*)pParam = 0;
    		}
    		else {
    			if (pBuf[WBufIdx].bufctl.frm.ubBufUsage) {
    				*(MMP_UBYTE*)pParam = 0;
    			}
    			else {
    				*(MMP_UBYTE*)pParam = 1;
    			}
    		}
    	}
    	break;
    default:
    	COMPONENT_HUVC_DBG_ERR(1, "[%s] UnSupport HUVC Param Type for GET\r\n", pComp->name);
        break;
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_HUVC_StoreDone_EmptyBuffer_Frm
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_HUVC_StoreDone_EmptyBuffer_Frm(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    MMP_ULONG                   i = 0;
    MMP_UBYTE                   ubIndex = 0,ubTriggered = 0;
    MMP_UBYTE                   ubNextFrmIndex = 0;
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_HUVC  *pDev = pComp->DeviceInfo;
    MMP_COMPONENT_BASE          *pNextComp = NULL;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;

    if (pComp == NULL) {
        COMPONENT_HUVC_DBG_ERR(1,"HUVC_StoreDone_EmptyBuffer : NULL component!\n");
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    if (!COMP_CHK_IDLE_STATE(pComp)) {
        return MMP_COMPONENT_ERR_INVALID_STATUS;
    }

    ubNextFrmIndex = ubIndex = pMem->memctl.frm.ubWBufIndex;

    ubNextFrmIndex++;
    if (ubNextFrmIndex >= pMem->ubBufNum) {
        ubNextFrmIndex = 0;
    }

	if (pDev->ubUsbMode == HUVC_COMP_USB_MODE_ISO) {
		//if next frame buffer is NOT free, drop this frame
		if ((pMem->ubBufNum > 1) &&
				(pBuf[ubNextFrmIndex].bufctl.frm.ubBufUsage)) {
			COMPONENT_HUVC_DBG_ERR(1,"HUVC_StoreDone_EmptyBuf : Drop Frame!\n");
			return MMP_UVC_ERR_FRAME_OVERFLOW;
		}
	}
	
    if(GetCheckFPSEnable(0)){
        //Component_HUVC_CalculateFPS();
    }
	
    // Send empty buffer to every port.
    if (pComp->ubOutputPortNum) {

        pBuf[ubIndex].bufctl.frm.ubBufUsage = pComp->ubOutputPortNum;

        for (i = 0 ; i < pComp->ubOutputPortNum; i++) {
            if (pComp->pOutPort[i].State == PORT_OPEN) {
                pBuf[ubIndex].bufctl.frm.bBufUsing[i] = MMP_TRUE;
                pNextComp = pComp->pOutPort[i].NextComponent;

                if (pDev->ubUsbMode == HUVC_COMP_USB_MODE_ISO) {
                    pNextComp->pInPort->bufInfo.ulBufAddr = ALIGN_X_ROUND_UP(pBuf[ubIndex].ulBufAddr,32);
                    pNextComp->pInPort->bufInfo.u64BufMiuAddr = ALIGN_X_ROUND_UP(pBuf[ubIndex].u64BufMiuAddr,32);
                    pNextComp->pInPort->bufInfo.u64BufPhyAddr = ALIGN_X_ROUND_UP(pBuf[ubIndex].u64BufPhyAddr,32);
                }
                else {
                    //memcpy((void *)&pNextComp->pInPort->bufInfo, (void *)&pComp->BufferInfo[ubIndex], sizeof(MMP_COMPONENT_BUFFER_INFO));
                    pNextComp->pInPort->bufInfo.ulBufAddr = pBuf[ubIndex].ulBufAddr;
                    pNextComp->pInPort->bufInfo.u64BufMiuAddr = pBuf[ubIndex].u64BufMiuAddr;
                    pNextComp->pInPort->bufInfo.u64BufPhyAddr = pBuf[ubIndex].u64BufPhyAddr;
                }

                pNextComp->pInPort->bufInfo.bufctl.frm.ubBufUsage = pBuf[ubIndex].bufctl.frm.ubBufUsage;
                pNextComp->pInPort->bufInfo.ubPortIndex = pBuf[ubIndex].ubPortIndex;
                pNextComp->pInPort->bufInfo.ulSize = ALIGN_X_ROUND_UP(ulSize, 32);
                pNextComp->pInPort->bufInfo.ulTime = pBuf[ubIndex].ulTime;
                pNextComp->pInPort->bufInfo.ulFrmType = COMP_BUF_FRM_TYPE_MJPEG;

                if (pNextComp->pfEmptyBuffer) {
                    m_bCompHUVCRdy = MMP_TRUE;
                    pNextComp->pfEmptyBuffer(pNextComp, ulSize, (void *)&pNextComp->pInPort->bufInfo);
                }

                ubTriggered = 1;
            }
            else {
                pBuf[ubIndex].bufctl.frm.bBufUsing[i] = MMP_FALSE;

                // Decrease buffer usage of current component.
                if (pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage > 0) {
                    pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage--;

                    if (pComp->BufferInfo[ubIndex].bufctl.frm.ubBufUsage == 0) {
                        MMP_UBYTE   ubCurRIndex = 0;

                        ubCurRIndex = pMem->memctl.frm.ubRBufIndex;
                        if (pBuf[ubCurRIndex].bufctl.frm.ubBufUsage == 0) {
                            ubCurRIndex++;
                            if (ubCurRIndex >= pMem->ubBufNum) {
                                ubCurRIndex = 0;
                            }
                            pMem->memctl.frm.ubRBufIndex = ubCurRIndex;
                        }
                    }
                }
            }
        }
    }

    // Update frame buffer, Change buffer index for fill buffer.
    if (ubTriggered) {
        pMem->memctl.frm.ubWBufIndex = ubNextFrmIndex;
    }

    return MMP_ERR_NONE;
}

MMP_BOOL Component_HUVC_CheckRdyStatus(void)
{
    return m_bCompHUVCRdy;
}

