//------------------------------------------------------------------------------
//
//  File        : component_adas.c
//  Description : Source file of adas component configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "ahc_parameter.h"
#include "mmp_component_ctl.h"
#include "mmps_3gprecd.h"
#include "mmps_iva.h"
#include "mmpf_adas.h"
#include "component_adas.h"
#include "cam_os_wrapper.h"
#include "mmpf_vmd.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPONENT_ADAS_DBG_MSG(enable, format, args...) do{if (0) UartSendTrace(format, ##args);}while(0)
#define COMPONENT_ADAS_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/* ADAS */
MMP_ERR Component_Adas_InitDevice(void *handler);
MMP_ERR Component_Adas_UnInitDevice(void *handler);
MMP_ERR Component_Adas_OpenDevice(void *handler);
MMP_ERR Component_Adas_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_Adas_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_Adas_AllocateBuffer(void *handler);
MMP_ERR Component_Adas_FreeBuffer(void *handler);

MMP_COMPONENT_BUFFER_INFO Component_Adas_BufInfo[ADAS_COMPONENT_MAX][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_Adas_InPort[ADAS_COMPONENT_MAX];
MMP_COMPONENT_PORT_INFO Component_Adas_OutPort[ADAS_COMPONENT_MAX][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_Adas_MemoryInfo[ADAS_COMPONENT_MAX];
MMP_COMPONENT_HANDLER_ADAS Component_Adas_DevInfo[ADAS_COMPONENT_MAX];

/* MDTC */
MMP_ERR Component_Mdtc_InitDevice(void *handler);
MMP_ERR Component_Mdtc_UnInitDevice(void *handler);
MMP_ERR Component_Mdtc_OpenDevice(void *handler);
MMP_ERR Component_Mdtc_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_Mdtc_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo);
MMP_ERR Component_Mdtc_AllocateBuffer(void *handler);
MMP_ERR Component_Mdtc_FreeBuffer(void *handler);

MMP_COMPONENT_BUFFER_INFO Component_Mdtc_BufInfo[MDTC_COMPONENT_MAX][COMP_MAX_OUTBUF_NUM];
MMP_COMPONENT_PORT_INFO Component_Mdtc_InPort[MDTC_COMPONENT_MAX];
MMP_COMPONENT_PORT_INFO Component_Mdtc_OutPort[MDTC_COMPONENT_MAX][MAX_OUTPUT_COMP_NUM];
MMP_COMPONENT_MEMORY_INFO Component_Mdtc_MemoryInfo[MDTC_COMPONENT_MAX];
MMP_COMPONENT_HANDLER_MDTC Component_Mdtc_DevInfo[MDTC_COMPONENT_MAX];

MMP_COMPONENT_BASE Component_Adas[ADAS_COMPONENT_MAX] = {
    {
        "ADAS",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_Adas_MemoryInfo[ADAS_COMPONENT_STD], // MemoryInfo
        Component_Adas_BufInfo[ADAS_COMPONENT_STD],     // BufferInfo
        &Component_Adas_InPort[ADAS_COMPONENT_STD],     // pInPort
        NULL,                                           // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_Adas_InitDevice,                      // pfInit
        Component_Adas_OpenDevice,                      // pfOpen
        Component_Adas_AllocateBuffer,                  // pfAllocateMemory
        Component_Adas_FreeBuffer,                      // pfFreeMemory
        Component_Adas_UnInitDevice,                    // pfUnInit
        NULL,                                           // pfClose
        NULL,                                           // pfSetParameter
        NULL,                                           // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        Component_Adas_EmptyBuffer,                     // pfEmptyBuffer
        Component_Adas_EmptyBufferDone,                 // pfEmptyBufferDone
        NULL,                                           // pfGetBufferInfo
        &Component_Adas_DevInfo[ADAS_COMPONENT_STD],    // DeviceInfo
    },
};

MMP_COMPONENT_BASE Component_Mdtc[MDTC_COMPONENT_MAX] = {
    {
        "MDTC",
        MMP_COMPONENT_STATE_INVALID,                    // ulState
        MMP_TRUE,                                       // bRegistered
        MMP_FALSE,                                      // bByPass
        0,                                              // ubOutputPortNum
        &Component_Mdtc_MemoryInfo[MDTC_COMPONENT_STD], // MemoryInfo
        Component_Mdtc_BufInfo[MDTC_COMPONENT_STD],     // BufferInfo
        &Component_Mdtc_InPort[MDTC_COMPONENT_STD],     // pInPort
        NULL,                                           // pOutPort
        {
            &MMP_CompCtl_UpdateBuffer_Frm,
            &MMP_CompCtl_EmptyBuffer_Frm,
            &MMP_CompCtl_EmptyOrderBuffer_Frm,
            &MMP_CompCtl_EmptyBufferDone_Frm,
        },
        Component_Mdtc_InitDevice,                      // pfInit
        Component_Mdtc_OpenDevice,                      // pfOpen
        Component_Mdtc_AllocateBuffer,                  // pfAllocateMemory
        Component_Mdtc_FreeBuffer,                      // pfFreeMemory
        Component_Mdtc_UnInitDevice,                    // pfUnInit
        NULL,                                           // pfClose
        NULL,                                           // pfSetParameter
        NULL,                                           // pfGetParameter
        NULL,                                           // pfUpdateBuffer
        Component_Mdtc_EmptyBuffer,                     // pfEmptyBuffer
        Component_Mdtc_EmptyBufferDone,                 // pfEmptyBufferDone
        NULL,                                           // pfGetBufferInfo
        &Component_Mdtc_DevInfo[MDTC_COMPONENT_STD],    // DeviceInfo
    },
};

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____ADAS_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_Adas_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_OpenDevice(void *handler)
{
#if (SUPPORT_ADAS)
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_ADAS  *pAdasInfo = (MMP_COMPONENT_HANDLER_ADAS *)pComp->DeviceInfo;
    COMMON_LDWS_EN              bLDWS_En = pAdasInfo->bLdwsEnable;
    COMMON_FCWS_EN              bFCWS_En = pAdasInfo->bFcwsEnable;
    COMMON_SAG_EN               bSAG_En  = pAdasInfo->bSagEnable;
    UINT32                      uiAdasFlag = 0;

    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_LDWS_EN, &bLDWS_En) == AHC_TRUE) {
        if (bLDWS_En == LDWS_EN_ON) {
            uiAdasFlag |= AHC_ADAS_ENABLED_LDWS;
        }
    }

    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_FCWS_EN, &bFCWS_En) == AHC_TRUE) {
        if (bFCWS_En == FCWS_EN_ON) {
            uiAdasFlag |= AHC_ADAS_ENABLED_FCWS;
        }
    }

    if (AHC_Menu_SettingGetCB( (char *)COMMON_KEY_SAG_EN, &bSAG_En) == AHC_TRUE) {
        if (bSAG_En == SAG_EN_ON) {
            uiAdasFlag |= AHC_ADAS_ENABLED_SAG;
        }
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
#if (SUPPORT_ADAS)
    static MMP_UBYTE ubLdwsFrameDiff = 0;
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if (MMPF_ADAS_IsEnable()) {

        MMPF_ADAS_STATE state = MMPF_ADAS_GetState();

        if (state == MMPF_ADAS_ACTIVE_STATE) {
            // Update luma source, and trigger motion detection
            MMPF_LDWS_UpdateInputLumaAddr(MsNonCache2Cache(pComp->pInPort->bufInfo.ulBufAddr));
        }
        else if ((state == MMPF_ADAS_FRAME_READY_STATE) ||
                 (state == MMPF_ADAS_OPERATING_STATE)) {
            // Wait until gap count meet
            ubLdwsFrameDiff++;
        }
        else if (state == MMPF_ADAS_WAIT_FRAME_STATE) {

            if (ubLdwsFrameDiff >= MMPF_LDWS_GetFrameGapConfig()) {
                // Update luma source, and trigger LDWS
                MMPF_LDWS_UpdateInputLumaAddr(MsNonCache2Cache(pComp->pInPort->bufInfo.ulBufAddr));

                ubLdwsFrameDiff = 0;
            }
            else {
                ubLdwsFrameDiff++;
            }
        }
    }
    else {
        ubLdwsFrameDiff = 0;
    }

    MMP_CompCtl_StoreBufferDone((void *)pComp, 0, NULL);
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_EmptyBufferDone
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_AllocateBuffer(void *handler)
{
#if (SUPPORT_ADAS)
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_COMPONENT_MEMORY_INFO   *pMem = pComp->MemoryInfo;
    MMP_ULONG                   ulStartAddr = 0;

    ulStartAddr = pBuf[0].u64BufPhyAddr;

    // Allocate memory for Motion detection source buffer (Y only)
    if (MMPS_Sensor_AllocateADASBuffer(&ulStartAddr, MMP_TRUE, pMem->ulBufSize) != MMP_ERR_NONE) {
        COMPONENT_ADAS_DBG_ERR(1, "Allocate ADAS buffer Failed\r\n");
        return MMP_SENSOR_ERR_LDWS;
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Adas_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Adas_FreeBuffer(void *handler)
{
#if (SUPPORT_ADAS)
    MMP_COMPONENT_BASE  *pComp = (MMP_COMPONENT_BASE *)handler;
    CamOsRet_e          eCamOsRet = CAM_OS_OK;
    MMP_ULONG           ulWorkBufAddr = 0;
    MMP_ULONG           ulWorkBufSize = 0;

    MMPS_Sensor_GetADASWorkBuf(&ulWorkBufAddr, &ulWorkBufSize);

    if (ulWorkBufAddr) {
        eCamOsRet = CamOsDirectMemRelease(ulWorkBufAddr, ulWorkBufSize);
        if (eCamOsRet != CAM_OS_OK) {
            COMPONENT_ADAS_DBG_ERR(1, "[%s] Free Mem failed.\n", pComp->name);
        }
    }
#endif
    return MMP_ERR_NONE;
}

#if 0
void _____MDTC_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_InitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_InitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_UnInitDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_UnInitDevice(void *handler)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_OpenDevice
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_OpenDevice(void *handler)
{
#if (SUPPORT_MDTC)
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_HANDLER_MDTC  *pAdasInfo = (MMP_COMPONENT_HANDLER_MDTC *)pComp->DeviceInfo;
    UINT8                       bParkingMode = pAdasInfo->bParkingMode;
    UINT8                       uiMdtcSensitivity = pAdasInfo->uiMotionDtcSensitivity;
    UINT8                       uiVMDRecTime = pAdasInfo->uiVMDRecTime;

    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_PARK_TYPE, &bParkingMode) == AHC_TRUE) {
        uiSetParkingModeEnable(bParkingMode);
    }
    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_MOTION_SENS, &uiMdtcSensitivity) == AHC_TRUE) {
        MenuSettingConfig()->uiMotionDtcSensitivity = uiMdtcSensitivity;
    }
    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_VMD_REC_TIME, &uiVMDRecTime) == AHC_TRUE) {
        MenuSettingConfig()->uiVMDRecTime = uiVMDRecTime;
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_EmptyBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_EmptyBuffer(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
#if (SUPPORT_MDTC)
    static MMP_UBYTE ubMotionFrameDiff = 0;
    MMP_COMPONENT_BASE *pComp = (MMP_COMPONENT_BASE *)handler;

    if (MMPF_VMD_IsEnable()) {

        MMPF_VMD_STATE state = MMPF_VMD_GetState();

        if (state == MMPF_VMD_ACTIVE_STATE) {
            // Update luma source, and trigger motion detection
            MMPF_VMD_UpdateInputLumaAddr(MsNonCache2Cache(pComp->pInPort->bufInfo.ulBufAddr));
        }
        else if ((state == MMPF_VMD_FRAME_READY_STATE) ||
                 (state == MMPF_VMD_OPERATING_STATE)) {
            // Wait until gap count meet
            ubMotionFrameDiff++;
        }
        else if (state == MMPF_VMD_WAIT_FRAME_STATE) {

            if (ubMotionFrameDiff >= MMPF_VMD_GetFrameGapConfig()) {
                // Update luma source, and trigger motion detection
                MMPF_VMD_UpdateInputLumaAddr(MsNonCache2Cache(pComp->pInPort->bufInfo.ulBufAddr));
                ubMotionFrameDiff = 0;
            }
            else {
                ubMotionFrameDiff++;
            }
        }
    }
    else {
        ubMotionFrameDiff = 0;
    }

    MMP_CompCtl_StoreBufferDone((void *)pComp, 0, NULL);
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_EmptyBufferDone
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_EmptyBufferDone(void *handler, MMP_ULONG ulSize, void *BufInfo)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_AllocateBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_AllocateBuffer(void *handler)
{
#if (SUPPORT_MDTC)
    MMP_COMPONENT_BASE          *pComp = (MMP_COMPONENT_BASE *)handler;
    MMP_COMPONENT_BUFFER_INFO   *pBuf = pComp->BufferInfo;
    MMP_ULONG                   ulStartAddr = 0;

    ulStartAddr = pBuf[0].u64BufPhyAddr;

    // Allocate memory for Motion detection source buffer (Y only)
    if (MMPS_Sensor_AllocateVMDBuffer(&ulStartAddr, MMP_TRUE) != MMP_ERR_NONE) {
        COMPONENT_ADAS_DBG_ERR(1, "Allocate MDTC buffer failed\r\n");
        return MMP_SENSOR_ERR_VMD;
    }
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Component_Mdtc_FreeBuffer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Component_Mdtc_FreeBuffer(void *handler)
{
#if (SUPPORT_MDTC)
    MMP_COMPONENT_BASE  *pComp = (MMP_COMPONENT_BASE *)handler;
    CamOsRet_e          eCamOsRet = CAM_OS_OK;
    MMP_ULONG           ulWorkBufAddr = 0;
    MMP_ULONG           ulWorkBufSize = 0;

    MMPS_Sensor_GetVMDWorkBuf(&ulWorkBufAddr, &ulWorkBufSize);

    if (ulWorkBufAddr) {
        eCamOsRet = CamOsDirectMemRelease(ulWorkBufAddr, ulWorkBufSize);
        if (eCamOsRet != CAM_OS_OK) {
            COMPONENT_ADAS_DBG_ERR(1, "[%s] Free Mem failed.\n", pComp->name);
        }
    }
#endif
    return MMP_ERR_NONE;
}
