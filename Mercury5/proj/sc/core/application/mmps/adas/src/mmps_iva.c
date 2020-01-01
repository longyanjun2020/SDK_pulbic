//==============================================================================
//
//  File        : mmps_iva.c
//  Description : Intelligent video analysis function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmps_iva.h"
#include "mmpd_system.h"
#include "mmpd_iva.h"
#include "mmpd_sensor.h"
#if defined(__RTK_OS__)
#include "cam_os_wrapper.h"
#endif

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

#if (SUPPORT_MDTC)
/** @brief The video motion detection mode.

   Use @ref MMPS_Sensor_IsVMDEnable to get it,
   and use @ref MMPS_Sensor_EnableVMD to set it.
*/
static MMP_BOOL                 m_bCurVMDMode = MMP_FALSE;
#endif

#if (SUPPORT_ADAS)
/** @brief The ADAS mode.

   Use @ref MMPS_Sensor_IsADASEnable to get it,
   and use @ref MMPS_Sensor_EnableADAS to set it.
*/
static MMP_BOOL                 m_bCurADASMode = MMP_FALSE;
static MMP_BOOL                 m_bCurADASState[MMPS_ADAS_FEATURE_NUM] = {0};
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____VMD_Functions_____(){}
#endif

#if (SUPPORT_MDTC)
//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_AllocateVMDBuffer
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will allocate buffers for video motion detection.

The function should be called in MMPS_3GPRECD_SetPreviewMemory().
@param[in] ulStartAddr  The start address to allocate buffers.
@param[in] usWidth      The width of VMD input buffer.
@param[in] usHeight     The height of VMD input buffer.
@param[in] bAllocate    Allocate buffers from memory pool.
@return It reports the status of buffer allocation.
*/
MMP_ERR MMPS_Sensor_AllocateVMDBuffer(MMP_ULONG *ulStartAddr, MMP_BOOL bAllocate)
{
    #if (SUPPORT_MDTC)
    MMP_ERR     err         = MMP_ERR_NONE;
    MMP_ULONG   ulCurBufPos = 0, ulBufSize = 0;
    MMP_ULONG* pulUserAddr;
    MMP_ULONG64  nInMiuAddr;
    MMP_ULONG64  nlInPhysAddr;
    CamOsRet_e camret = CAM_OS_OK;

    ulCurBufPos = *ulStartAddr;
    //ulCurBufPos = ALIGN4K(ulCurBufPos); ///< 4K alignment for dynamic adjustment cache mechanism

    err = MMPD_Sensor_InitializeVMD();

    if (err != MMP_ERR_NONE) {
        PRINTF("Initialize video motion detection config failed\r\n");
        return err;
    }
    //get buf Size
   err = MMPD_Sensor_SetVMDBuf(ulCurBufPos, &ulBufSize);
    if (err != MMP_ERR_NONE) {
        PRINTF("Set video motion detection buffers failed\r\n");
        return err;
    }

    //Allocate Adas Work Buf
    camret = CamOsDirectMemAlloc("Work Buf",
                    ulBufSize,
                    (void**)&pulUserAddr,
                    &nInMiuAddr,
                    &nlInPhysAddr);
    if(camret != CAM_OS_OK) { UartSendTrace("[%s,%d] failed.\n",__FUNCTION__, __LINE__);}

    //set buf addr
    err = MMPD_Sensor_SetVMDBuf((MMP_ULONG)nlInPhysAddr, &ulBufSize);
    if (err != MMP_ERR_NONE) {
        PRINTF("Set video motion detection buffers failed\r\n");
        return err;
    }

    ulCurBufPos += ulBufSize;
    //printc("End of VMD buffer = 0x%X\r\n", ulCurBufPos);
    *ulStartAddr = ulCurBufPos;

    return MMP_ERR_NONE;
    #else
    return MMP_SENSOR_ERR_VMD;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetVMDResolution
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the configured resolution of motion detection frame.

The function gets the configured resolution of motion detection frame.
@param[out] width   The width of motion detection source frame
@param[out] height  The height of motion detection source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_GetVMDResolution(MMP_ULONG *ulWidth, MMP_ULONG *ulHeight)
{
    #if (SUPPORT_MDTC)
    return MMPD_Sensor_GetVMDResolution(ulWidth, ulHeight);
    #else
    return MMP_SENSOR_ERR_VMD;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetVMDEnable
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will enable/disable the video motion detection.

The function set command to firmware to enable/disable the motion detection.
@param[in] bEnable Enable or disable motion detection.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_EnableVMD(MMP_BOOL bEnable)
{
    #if (SUPPORT_MDTC)
    if (bEnable != m_bCurVMDMode) {

        MMPD_Sensor_EnableVMD(bEnable);

        m_bCurVMDMode = bEnable; 
    }
    return MMP_ERR_NONE;
    #else
    return MMP_SENSOR_ERR_VMD;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_IsVMDEnable
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will check if motion detection is enabled.

The function get the current status of motion detection.
@return It reports the status of the operation.
*/
MMP_BOOL MMPS_Sensor_IsVMDEnable(void)
{
    #if (SUPPORT_MDTC)
    return m_bCurVMDMode;
    #else
    return MMP_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_RegisterVMDCallback
//  Description :
//------------------------------------------------------------------------------
/** @brief the function registers the callback function to inform motion detected.

The function registers the callback which will be called when motion detected.
@param[in] event to the Callback function
@param[in] Callback The Callback function
@return It reports the status of the operation.

*/
MMP_ERR MMPS_Sensor_RegisterVMDCallback(MMP_UBYTE event, void *callback)
{
    switch(event) {
    case MMPS_IVA_EVENT_MDTC:
        return MMPD_Sensor_RegisterVMDCallback(callback);
    default:
        return MMP_SENSOR_ERR_NOT_SUPPORT;
    }
}

MMP_ERR MMPS_Sensor_GetVMDWorkBuf(MMP_ULONG *ulWorkBuf, MMP_ULONG *ulBufSize)
{
#if (SUPPORT_MDTC)
    return MMPD_Sensor_GetVMDWorkBuf(ulWorkBuf, ulBufSize);
#else
    return MMP_ERR_NONE;
#endif
}
#endif

#if 0
void _____ADAS_Functions_____(){}
#endif

#if (SUPPORT_ADAS)
//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_AllocateADASBuffer
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will allocate buffers for video ADAS.

The function should be called in MMPS_3GPRECD_SetPreviewMemory().
@param[in] ulStartAddr  The start address to allocate buffers.
@param[in] bAllocate    Allocate buffers from memory pool.
@param[in] ulDMABufSize The dma destination buffer size of ADAS.
@return It reports the status of buffer allocation.
*/
extern MMP_ULONG ADAS_CTL_GetWorkBufSize(MMP_ULONG frm_w, MMP_ULONG frm_h);
MMP_ERR MMPS_Sensor_AllocateADASBuffer(MMP_ULONG *ulStartAddr, MMP_BOOL bAllocate, MMP_ULONG ulDMABufSize)
{
    MMP_ERR     err         = MMP_ERR_NONE;
    MMP_ULONG   ulCurBufPos = 0, ulBufSize = 0;
    MMP_ULONG   ulDMAAddr = 0;
    MMP_ULONG ulWidth,ulHeight;
    MMP_ULONG* pulUserAddr;
    MMP_ULONG64  nInMiuAddr;
    MMP_ULONG64  nlInPhysAddr;
    CamOsRet_e camret = CAM_OS_OK;

    ulCurBufPos = *ulStartAddr;

    // Allocate DMA buffer
    ulDMAAddr = ulCurBufPos;
    ulCurBufPos += ulDMABufSize;

    err = MMPD_Sensor_InitializeADAS();

    if (err != MMP_ERR_NONE) {
        PRINTF("Initialize video ADAS config failed\r\n");
        return err;
    }

    err = MMPD_Sensor_SetADASFeature(m_bCurADASState[MMPS_ADAS_LDWS],
                                     m_bCurADASState[MMPS_ADAS_FCWS],
                                     m_bCurADASState[MMPS_ADAS_SAG]);

    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, 
                        ATEST_STS_ADAS_0x0009,  
                        m_bCurADASState[MMPS_ADAS_SAG],  
                        m_bCurADASState[MMPS_ADAS_FCWS]<<8 + m_bCurADASState[MMPS_ADAS_LDWS], 
                        gubMmpDbgBk);

    if (err != MMP_ERR_NONE) {
        PRINTF("Set video ADAS features failed\r\n");
        return err;
    }
    //get buf size
    MMPS_Sensor_GetADASResolution(&ulWidth, &ulHeight);
    ulBufSize = ADAS_CTL_GetWorkBufSize(ulWidth, ulHeight);

    //Allocate Adas Work Buf
    camret = CamOsDirectMemAlloc("Work Buf",
                    ulBufSize,
                    (void**)&pulUserAddr,
                    &nInMiuAddr,
                    &nlInPhysAddr);
    if(camret != CAM_OS_OK) { UartSendTrace("[%s,%d] failed.\n",__FUNCTION__, __LINE__);}

    //set buf addr
    err = MMPD_Sensor_SetADASBuf((MMP_ULONG)nlInPhysAddr, &ulBufSize, ulDMAAddr);
    if (err != MMP_ERR_NONE) {
        PRINTF("Set video ADAS buffers failed\r\n");
        return err;
    }
    ulCurBufPos += ulBufSize;
    //printc("End of ADAS buffer = 0x%X\r\n", ulCurBufPos);
    *ulStartAddr = ulCurBufPos;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetADASResolution
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the configured resolution of ADAS frame.

The function gets the configured resolution of ADAS frame.
@param[out] width   The width of ADAS source frame
@param[out] height  The height of ADAS source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_GetADASResolution(MMP_ULONG *ulWidth, MMP_ULONG *ulHeight)
{
    return MMPD_Sensor_GetADASResolution(ulWidth, ulHeight);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetADASFeatureEn
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will enable/disable sub-feature of ADAS.

The function set command to firmware to enable/disable the ADAS.
@param[in] feature Sub-feature of ADAS
@param[in] bEnable Enable or disable ADAS.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_SetADASFeatureEn(MMPS_IVA_ADAS_FEATURE feature, MMP_BOOL bEnable)
{
    if (feature < MMPS_ADAS_FEATURE_NUM) {
        m_bCurADASState[feature] = bEnable;
        return MMP_ERR_NONE;
    }

    return MMP_SENSOR_ERR_PARAMETER;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetADASFeatureEn
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the current state of ADAS sub-feature.

The function gets the current state of the specified ADAS sub-feature.
@param[in] feature Sub-feature of ADAS
@return It reports the status of the specified ADAS sub-feature.
*/
MMP_BOOL MMPS_Sensor_GetADASFeatureEn(MMPS_IVA_ADAS_FEATURE feature)
{
    if (feature < MMPS_ADAS_FEATURE_NUM)
        return m_bCurADASState[feature] & m_bCurADASMode;

    return MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_EnableADAS
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will enable/disable the ADAS operation.

The function set command to firmware to enable/disable the ADAS.
Note: Use VMD flow/pipe for ADAS
@param[in] bEnable Enable or disable ADAS.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_EnableADAS(MMP_BOOL bEnable)
{
    MMP_ERR sRet = MMP_ERR_NONE;
    
    if (bEnable != m_bCurADASMode) {

        sRet = MMPD_Sensor_EnableADAS(bEnable);
        if(sRet != MMP_ERR_NONE) { MMP_PRINT_RET_ERROR(0, sRet, "",gubMmpDbgBk); return sRet;}

        m_bCurADASMode = bEnable; 
    }
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetADASImgBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the Image address of ADAS frame.

The function gets the Image address of ADAS frame.
@param[out] ulInputLumaAddr The Y of ADAS source frame
@param[out] ulImgBufAddr  The DMA of ADAS source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_GetADASImgBuf(MMP_ULONG* ulInputLumaAddr)
{
    return MMPD_Sensor_GetADASImgBuf(ulInputLumaAddr);
}

MMP_ERR MMPS_Sensor_GetADASWorkBuf(MMP_ULONG* ulWorkAddr, MMP_ULONG* ulWorkSize)
{
    return MMPD_Sensor_GetADASWorkBuf(ulWorkAddr, ulWorkSize);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_IsADASEnable
//  Description :
//------------------------------------------------------------------------------
/** @brief the function will check if ADAS is enabled.

The function get the current status of ADAS.
@return It reports the status of the operation.
*/
MMP_BOOL MMPS_Sensor_IsADASEnable(void)
{
    return m_bCurADASMode;
}
#endif
