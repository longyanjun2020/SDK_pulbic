//==============================================================================
//
//  File        : mmpd_sensor.c
//  Description : Ritian Sensor Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "mmpd_sensor.h"
#include "mmph_hif.h"
#include "mmpf_sensor.h"

/** @addtogroup MMPD_Sensor
 *  @{
 */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief The function initializes the sensor by sending host command request

The function initializes the sensor.

@param[in] ubSnrSel         the sensor module
@param[in] ubPreviewMode    the preview mode
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_Initialize(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_UBYTE ubHdrEnable, MMP_ULONG ulIqCfgIdx)
{
    MMP_ERR err = MMP_ERR_NONE;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ubPreviewMode);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 8, ubHdrEnable);
	MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 12, ulIqCfgIdx);
	
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_INIT_SENSOR);

    err = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set sensor camera preview mode or video preview mode

The function initializes the sensor. It returns the status about the set mode result.

@param[in] sensormode the sensor mode
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetMode(MMP_UBYTE ubSnrSel, MMP_SNR_MODE sSnrMode)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, sSnrMode);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_SET_SENSOR_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_ChangePreviewMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the sensor preview mode

@param[in] ubPreviewMode the preview mode
@param[in] ubWaitCount the phase count
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_ChangePreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_UBYTE ubWaitCount)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ubPreviewMode);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 8, ubWaitCount);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_CHANGE_SENSOR_RES_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetPreviewMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the sensor preview mode

@param[in] ubPreviewMode the preview mode
@param[in] ubPhaseCount the phase count
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetPreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterW(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterW(GRP_IDX_FLOWCTL, 2, ubPreviewMode);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_SET_SENSOR_RES_MODE | SENSOR_PREVIEW_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetCaptureMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Sensor_SetCaptureMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubCaptureMode)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ubCaptureMode);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_SET_SENSOR_RES_MODE | SENSOR_CAPTURE_MODE);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_PowerDown
//  Description :
//------------------------------------------------------------------------------
/** @brief The function power down the sensor by sending host command request

The function power down  the sensor. It returns the status about the initialization result.

@param[in] ubSnrSel the sensor module
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_PowerDown(MMP_UBYTE ubSnrSel)
{
    MMP_ERR mmpstatus = MMP_ERR_NONE;
    
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);

    mmpstatus = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_POWERDOWN_SENSOR);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return mmpstatus;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetGain
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Sensor_SetGain(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain, MMP_UBYTE ubType)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ulGain);
    
    if (ubType == MMP_SNR_PREV_MODE) {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_PREV_GAIN);
    }
    else {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_CAP_GAIN);
    }
    
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetShutter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Sensor_SetShutter(MMP_UBYTE ubSnrSel, MMP_UBYTE ubIndex, MMP_UBYTE ubType)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ubIndex);
    
    if (ubType == MMP_SNR_PREV_MODE) {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_PREV_SHUTTER);
    }
    else {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_CAP_SHUTTER);
    }
    
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetExposureLimit
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPD_Sensor_SetExposureLimit(MMP_ULONG ulBufaddr, MMP_ULONG ulDataTypeByByte, 
                                     MMP_ULONG ulSize, MMP_UBYTE ubType)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ulBufaddr);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ulDataTypeByByte);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 8, ulSize);
    
    if (ubType == MMP_SNR_PREV_MODE) {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_PREV_EXP_LIMIT);
    }
    else {
        MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_CAP_EXP_LIMIT);
    }

    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return MMP_ERR_NONE;
}
                                     
//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetNightMode
//  Description :
//------------------------------------------------------------------------------
/** @brief config the night mode

@param[in] usMode the night mode
@retval MMPS_DSC_SUCCESS success
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetNightMode(MMP_UBYTE ubSnrSel, MMP_ULONG ulMode, MMP_ULONG ulMinFPS)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
	MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ulMode);
	MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 8, ulMinFPS);

    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_AE_FUNC | SET_NIGHT_MODE);
    
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_SetFlip
//  Description :
//------------------------------------------------------------------------------
/** @brief Configure the sensor flip

The function sets the sensor flip with the specified flip type input. It saves the flip type for internal
use after the setting.

@param[in] ubFlipType the flip type
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_SetFlip(MMP_UBYTE ubSnrSel, MMP_UBYTE ubFlipType)
{
    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, ubFlipType);
    
    MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_SET_SENSOR_FLIP);
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPD_Sensor_GetDriverParam
//  Description :
//------------------------------------------------------------------------------
/** @brief The function get the parameters from sensor device driver

@param[in]  ubSnrId      : the sensor id
@param[in]  type         : the parameters to be retrieved.
@param[in]  ubInputSize  : the inputs size in unit of integer (4-byte)
@param[in]  pInput       : the array of inputs
@param[in]  ubOutputSize : the expected return size in unit of integer (4-byte)
@param[out] pParam       : the output parameter arrays
@return It reports the status of the operation.
*/
MMP_ERR MMPD_Sensor_GetDriverParam(MMP_UBYTE            ubSnrSel, 
                                   MMP_SNR_DRV_PARAM    type,
                                   MMP_UBYTE ubInputSize,  MMP_ULONG *pInput,
                                   MMP_UBYTE ubOutputSize, MMP_ULONG *pParam)
{   
    MMP_UBYTE   i;
    MMP_ERR     err;

    MMPH_HIF_WaitSem(GRP_IDX_FLOWCTL, 0);
    
    MMPH_HIF_SetParameterB(GRP_IDX_FLOWCTL, 0, ubSnrSel);
    MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, 4, type);

    for (i = 0; i < ubInputSize; i++) {
        MMPH_HIF_SetParameterL(GRP_IDX_FLOWCTL, (i << 2) + 8, pInput[i]);
    }

    err = MMPH_HIF_SendCmd(GRP_IDX_FLOWCTL, HIF_FCTL_CMD_GET_SENSOR_DRV_PARAM);
    
    for (i = 0; i < ubOutputSize; i++) {
        pParam[i] = MMPH_HIF_GetParameterL(GRP_IDX_FLOWCTL, (i << 2));
    }
    MMPH_HIF_ReleaseSem(GRP_IDX_FLOWCTL);
    
    return err;
}
