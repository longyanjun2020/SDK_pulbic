/// @ait_only
//==============================================================================
//
//  File        : mmpd_iva.c
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
#include "mmpd_iva.h"
#include "mmph_hif.h"

/** @addtogroup MMPD_IVA
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____MDTC_Functions_____(){}
#endif

#if (SUPPORT_MDTC)
//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_InitializeVMD
//  Description :
//------------------------------------------------------------------------------
/** @brief Function to initialize VMD

The function initailizes the VMD configuration
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_InitializeVMD(void)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | INIT_VMD);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetVMDBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief Set working buffer address for motion detection operation.

The function set video motion detection buffer for operation
@param[in] buf_addr the address of motion detection working buffer
@param[out] buf_size the total size of working buffer
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetVMDBuf(MMP_ULONG buf_addr, MMP_ULONG *buf_size)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, buf_addr);
    
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | SET_VMD_BUF);
    *buf_size = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_GetVMDResolution
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the configured resolution of motion detection frame.

The function gets the configured resolution of motion detection frame.
@param[out] width   The width of motion detection source frame
@param[out] height  The height of motion detection source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_GetVMDResolution(MMP_ULONG *width, MMP_ULONG *height)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | GET_VMD_RESOL);
    *width  = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    *height = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_RegisterVMDCallback
//  Description :
//------------------------------------------------------------------------------
/** @brief the function configures the sensitivity of video motion detection.

The function set command to firmware to configures the sensitivity of motion detection.
@param[in] ulDiffThreshold The threshold of movement to be regarded as motion
@param[in] ulCntThreshold  The threshold of MB counts with difference larger than
                           ulDiffThreshold
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_RegisterVMDCallback(void *Callback)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, (MMP_ULONG)Callback);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | REG_VMD_CALLBACK);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_EnableVMD
//  Description :
//------------------------------------------------------------------------------
/** @brief the function enable the video motion detection.

The function set command to firmware to start the video motion detection.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_EnableVMD(MMP_BOOL bEnable)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, (MMP_ULONG)bEnable);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | ENABLE_VMD);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

MMP_ERR MMPD_Sensor_GetVMDWorkBuf(MMP_ULONG *ulWorkBuf, MMP_ULONG *ulBufSize)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_VMD | GET_VMD_BUF);
    *ulWorkBuf  = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    *ulBufSize = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}
#endif

#if 0
void _____ADAS_Functions_____(){}
#endif

#if (SUPPORT_ADAS)
//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_InitializeADAS
//  Description :
//------------------------------------------------------------------------------
/** @brief Function to initialize ADAS

The function initailizes the ADAS configuration
@param[in] usWidth the width of input frame for ADAS detection
@param[in] usHeight the height of input frame for ADAS detection
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_InitializeADAS(void)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | INIT_ADAS);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_GetADASResolution
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the configured resolution of ADAS frame.

The function gets the configured resolution of ADAS frame.
@param[out] width   The width of ADAS source frame
@param[out] height  The height of ADAS source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_GetADASResolution(MMP_ULONG *width, MMP_ULONG *height)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | GET_ADAS_RESOL);
    *width  = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    *height = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetADASFeature
//  Description :
//------------------------------------------------------------------------------
/** @brief Enable or disable each feature in ADAS.

The function control each feature within ADAS ON/OFF.
@param[in] ldws_on Enable LDWS feature
@param[in] fcws_on Enable FCWS feature
@param[in] sng_on Enable SnG feature
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetADASFeature(MMP_BOOL ldws_on, MMP_BOOL fcws_on, MMP_BOOL sag_on)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterB(GRP_IDX_FLOWCTL, 0, ldws_on);
    MMPH_HIF_SetParameterB(GRP_IDX_FLOWCTL, 1, fcws_on);
    MMPH_HIF_SetParameterB(GRP_IDX_FLOWCTL, 2, sag_on);

    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | CTL_ADAS_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetADASBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief Set working buffer address for ADAS operation.

The function set video ADAS buffer for operation
@param[in] buf_addr the address of ADAS working buffer
@param[in] buf_addr the address of ADAS DMA destination buffer
@param[out] buf_size the total size of working buffer
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetADASBuf(MMP_ULONG buf_addr, MMP_ULONG *buf_size, MMP_ULONG dma_buf_addr)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, buf_addr);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, dma_buf_addr);
        
    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | SET_ADAS_BUF);
    *buf_size = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_EnableADAS
//  Description :
//------------------------------------------------------------------------------
/** @brief the function enable ADAS feature.

The function set command to firmware to start ADAS feature.
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_EnableADAS(MMP_BOOL bEnable)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, (MMP_ULONG)bEnable);

    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | ENABLE_ADAS);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_GetADASImgBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the Image address of ADAS frame.

The function gets the Image address of ADAS frame.
@param[out] ulInputLumaAddr The Y of ADAS source frame
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_GetADASImgBuf(MMP_ULONG* ulInputLumaAddr)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | GET_ADAS_IMGBUF);
    *ulInputLumaAddr  = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return status;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_GetADASWorkBuf
//  Description :
//------------------------------------------------------------------------------
/** @brief the function gets the work buf of ADAS frame.
@param[out] ulWorkAddr Adas work buf addr
@param[out] ulWorkSize Adas work buf size
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_GetADASWorkBuf(MMP_ULONG* ulWorkAddr, MMP_ULONG* ulWorkSize)
{
    MMP_ERR status;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    status = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_ADAS | GET_ADAS_WORKBUF);
    *ulWorkAddr  = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    *ulWorkSize    = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 4);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return status;
}
#endif

