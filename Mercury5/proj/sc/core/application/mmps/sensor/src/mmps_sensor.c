//==============================================================================
//
//  File        : mmps_sensor.c
//  Description : Ritian Sensor Control driver function
//  Author      : Alan Wu
//  Revision    : 1.0
//
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "snr_cfg.h"
#include "mmp_snr_inc.h"
#include "mmps_sensor.h"
#include "mmps_display.h"

#include "component_cfg.h"
#include "component_pip.h"
#include "cust_component_cfg.h"
#include "mmpf_hif.h"
#include "os_wrap.h"

/** @addtogroup MMPS_SENSOR
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MMPS_SNR_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMPS_SNR_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

//==============================================================================
//
//                              GLOBAL VARIABLES
//
//==============================================================================

/**@brief The current sensor mode.

Use @ref MMPS_Sensor_Initialize to set it.
*/
static MMP_SNR_MODE     m_eCurSensorMode[VIF_SENSOR_MAX_NUM];

/**@brief The current preview mode.

Use @ref MMPS_Sensor_Initialize to set it.
*/
static MMP_UBYTE        m_ubCurPreviewMode[VIF_SENSOR_MAX_NUM] = {0, 0};
static MMP_UBYTE        m_ubCurCaptureMode[VIF_SENSOR_MAX_NUM] = {0, 0};

/**@brief Sensor initialized or not.

Use @ref MMPS_Sensor_Initialize to set it.
*/
static MMP_BOOL         m_bSensorInit[VIF_SENSOR_MAX_NUM] = {MMP_FALSE, MMP_FALSE};

static MMPF_OS_TMRID    m_ulAnaDecSrcTypeDetectTimer[VIF_SENSOR_MAX_NUM] = {MMPF_OS_CREATE_TMR_INT_ERR, MMPF_OS_CREATE_TMR_INT_ERR};
static MMP_UBYTE        m_ubSnrSel[VIF_SENSOR_MAX_NUM] = {PRM_SENSOR, SCD_SENSOR};

//==============================================================================
//                              EXTERN VARIABLES
//==============================================================================

extern MMPF_OS_FLAGID   SENSOR_Flag;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_InitPresetMode
//  Description :
//------------------------------------------------------------------------------
/** @brief Initialize Sensor Mode

The function initializes Sensor Mode.

@param[in] ubSnrSel the Sensor ID (0, 1, .....)
@param[in] ubPreviewMode Sensor preview mode, choose the input resolution of the sensor
@return It reports the status of the initialization result.
*/
static MMP_ERR MMPS_Sensor_InitPresetMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode)
{
    m_ubCurPreviewMode[ubSnrSel]    = ubPreviewMode;
    m_bSensorInit[ubSnrSel]         = MMP_TRUE;

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetMode
//  Description :
//------------------------------------------------------------------------------
static MMP_ERR MMPS_Sensor_SetMode(MMP_UBYTE ubSnrSel, MMP_SNR_MODE sSnrMode)
{
    MMP_ERR error = MMP_ERR_NONE;

    m_eCurSensorMode[ubSnrSel] = sSnrMode;

    error = MMPD_Sensor_SetMode(ubSnrSel, sSnrMode);

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief Initialize Sensor

The function initializes Sensor.

@param[in] ubSnrSel the Sensor ID (0, 1, .....)
@param[in] ubPreviewMode Sensor preview mode, choose the input resolution of the sensor
@param[in] sensormode Sensor preview mode, choose the camera or video preview mode

@return It reports the status of the initialization result.
*/
MMP_ERR MMPS_Sensor_Initialize(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_SNR_MODE eSnrMode, MMP_UBYTE ubHdrEnable, MMP_ULONG ulIqCfgIdx)
{
    MMP_ERR error = MMP_ERR_NONE;

    error = MMPS_Sensor_InitPresetMode(ubSnrSel, ubPreviewMode);
    error = MMPS_Sensor_SetMode(ubSnrSel, eSnrMode);

    if (error != MMP_ERR_NONE) {
        MMPS_SNR_DBG_ERR(1, "Sensor Initial Set Mode Failed!\r\n");
        return error;
    }

    error = MMPD_Sensor_Initialize(ubSnrSel, ubPreviewMode, ubHdrEnable, ulIqCfgIdx);

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_IsInitialized
//  Description :
//------------------------------------------------------------------------------
/** @brief Check if sensor initialized

The function check sensor initialize status.

@param[in] ubSnrSel the Sensor ID (0, 1, .....)

@return It reports the status of the sensor initialized or not.
*/
MMP_BOOL MMPS_Sensor_IsInitialized(MMP_UBYTE ubSnrSel)
{
    return m_bSensorInit[ubSnrSel];
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_ChangePreviewMode
//  Description :
//------------------------------------------------------------------------------
/** @brief Change the sensor preview mode

The function can be called after sensor is initialized to change the sensor preview mode.

@param[in] ubPreviewMode Sensor preview mode, choose the input resolution of the sensor
@param[in] ubWaitCount Sensor phase count

@return It reports the status of the change mode status
*/
MMP_ERR MMPS_Sensor_ChangePreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode, MMP_UBYTE ubWaitCount)
{
    m_ubCurPreviewMode[ubSnrSel] = ubPreviewMode;

    return MMPD_Sensor_ChangePreviewMode(ubSnrSel, ubPreviewMode, ubWaitCount);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetPreviewMode
//  Description :
//------------------------------------------------------------------------------
/** @brief Change the sensor preview mode

The function can be called after sensor is initialized to change the sensor preview mode.

@param[in] ubPreviewMode Sensor preview mode, choose the input resolution of the sensor
@param[in] ubPhaseCount Sensor phase count

@return It reports the status of the change mode status
*/
MMP_ERR MMPS_Sensor_SetPreviewMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubPreviewMode)
{
    m_ubCurPreviewMode[ubSnrSel] = ubPreviewMode;

    return MMPD_Sensor_SetPreviewMode(ubSnrSel, ubPreviewMode);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetCaptureMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetCaptureMode(MMP_UBYTE ubSnrSel, MMP_UBYTE ubCaptureMode)
{
    m_ubCurCaptureMode[ubSnrSel] = ubCaptureMode;

    return MMPD_Sensor_SetCaptureMode(ubSnrSel, ubCaptureMode);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetCurPrevScalInputRes
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives current sensor preview resolution

The function retrives current sensor preview resolution
@param[out] usWidth  the width
@param[out] usHeight  the height
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_GetCurPrevScalInputRes(MMP_UBYTE ubSnrSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    MMP_ERR   err = MMP_ERR_NONE;
    MMP_ULONG ulMode = 0;

    ulMode = m_ubCurPreviewMode[ubSnrSel];

    err = MMPF_Sensor_GetSensorRes(ubSnrSel, ulMode, pulWidth, pulHeight);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetCurSensorOutputRes
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives current sensor output resolution

The function retrives current sensor output resolution
@param[out] usWidth  the width
@param[out] usHeight  the height
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_GetCurSensorOutputRes(MMP_UBYTE ubSnrSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    MMP_ERR   err = MMP_ERR_NONE;
    MMP_ULONG ulMode = 0;

    ulMode = m_ubCurPreviewMode[ubSnrSel];

    err = MMPF_Sensor_GetSensorOutputRes(ubSnrSel, ulMode, pulWidth, pulHeight);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetScalInputRes
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives sensor output resolution of the specified mode

The function retrives sensor output resolution of the specified mode
@param[in]  ubSnrSel : the sensor id (PRM_SENSOR, SCD_SENSOR)
@param[in]  ubMode   : the sensor mode
@param[out] usWidth  : the width
@param[out] usHeight : the height
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_GetScalInputRes(MMP_UBYTE ubSnrSel, MMP_UBYTE ubMode,
                                    MMP_ULONG *pulWidth, MMP_ULONG *pulHeight)
{
    MMP_ERR   err = MMP_ERR_NONE;
    MMP_ULONG ulMode = 0;

    ulMode = ubMode;

    err = MMPF_Sensor_GetSensorRes(ubSnrSel, ulMode, pulWidth, pulHeight);

    return err;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetPreviewResNum
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives the total number of sensor output resolutions

The function retrives the total number of sensor output resolutions
@param[in]  ubSnrSel : the sensor id (PRM_SENSOR, SCD_SENSOR)
@retval the total number of sensor output resolutions
*/
MMP_UBYTE MMPS_Sensor_GetPreviewResNum(MMP_UBYTE ubSnrSel)
{
    MMP_ULONG ulParam = 0;

    MMPD_Sensor_GetDriverParam(ubSnrSel, MMP_SNR_DRV_PARAM_PREVIEW_RES_NUM,
                               0, NULL, 1, &ulParam);

    return (MMP_UBYTE)ulParam;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetDefPreviewMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives the default preview mode

The function retrives the default preview mode
@param[in]  ubSnrSel : the sensor id (PRM_SENSOR, SCD_SENSOR)
@retval the default preview mode
*/
MMP_UBYTE MMPS_Sensor_GetDefPreviewMode(MMP_UBYTE ubSnrSel)
{
    MMP_ULONG ulParam = 0;

    MMPD_Sensor_GetDriverParam(ubSnrSel, MMP_SNR_DRV_PARAM_DEF_PREVIEW_RES,
                               0, NULL, 1, &ulParam);

    return (MMP_UBYTE)ulParam;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetCurFpsx10
//  Description :
//------------------------------------------------------------------------------
/** @brief The function retrives sensor output frame rate x 10 of current mode

The function retrives current sensor output frame rate x 10 of current mode
@param[out] ulFpsx10  sensor output frame rate x 10
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_GetCurFpsx10(MMP_UBYTE ubSnrSel, MMP_ULONG *pulFpsx10)
{
    MMP_ULONG ulMode = m_ubCurPreviewMode[ubSnrSel];

    return MMPF_Sensor_GetSensorFpsx10(ubSnrSel, ulMode, pulFpsx10);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_PowerDown
//  Description :
//------------------------------------------------------------------------------
/** @brief Power Down Sensor

The function power down Sensor. Before the function is called, the exact firmware code needs
to be downloaded into the MMP memory

@param[in] usSensor the Sensor Module
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_PowerDown(MMP_UBYTE ubSnrSel)
{
    MMP_ERR error = MMP_ERR_NONE;

    m_bSensorInit[ubSnrSel] = MMP_FALSE;

    error = MMPD_Sensor_PowerDown(ubSnrSel);

    return error;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetGain
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetGain(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain, MMP_UBYTE ubType)
{
    return MMPD_Sensor_SetGain(ubSnrSel, ulGain, ubType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetShutter
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetShutter(MMP_UBYTE ubSnrSel, MMP_UBYTE ubIndex, MMP_UBYTE ubType)
{
    return MMPD_Sensor_SetShutter(ubSnrSel, ubIndex, ubType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetExposureLimit
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetExposureLimit(MMP_ULONG ulBufaddr, MMP_ULONG ulDataTypeByByte, MMP_ULONG ulSize, MMP_UBYTE ubType)
{
    return MMPD_Sensor_SetExposureLimit(ulBufaddr, ulDataTypeByByte, ulSize, ubType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetNightMode
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetNightMode(MMP_UBYTE ubSnrSel, MMP_ULONG ulMode, MMP_ULONG ulMinFPS)
{
    return MMPD_Sensor_SetNightMode(ubSnrSel, ulMode, ulMinFPS);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetSensorReg
//  Description :
//------------------------------------------------------------------------------
/** @brief Write the sensor register

@param[in] usAddr the register
@param[in] usData the data
@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_SetSensorReg(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT usData)
{
    if (MMP_TRUE == m_bSensorInit[ubSnrSel]) {
        return MMPF_Sensor_SetSensorReg(ubSnrSel, usAddr, usData);
    }

    return MMP_SENSOR_ERR_INITIALIZE_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetSensorReg
//  Description :
//------------------------------------------------------------------------------
/** @brief Read the sensor register

@param[in] usAddr the register
@param[in] usData the data
@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_GetSensorReg(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT *usData)
{
    if (MMP_TRUE == m_bSensorInit[ubSnrSel]) {
        return MMPF_Sensor_GetSensorReg(ubSnrSel, usAddr, usData);
    }
    else {
        return MMP_SENSOR_ERR_INITIALIZE_NONE;
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetFlip
//  Description :
//------------------------------------------------------------------------------
/** @brief Set the sensor flip mode

The function configures sensor flip type in the preview mode
@param[in] ubFlipType the sensor flip type
@retval MMP_ERR_NONE success
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_SetFlip(MMP_UBYTE ubSnrSel, MMP_UBYTE ubFlipType)
{
    return MMPD_Sensor_SetFlip(ubSnrSel, ubFlipType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_Set3AFunction
//  Description :
//------------------------------------------------------------------------------
/** @brief Set the 3A function

The function Set the 3A function
@param[in] sFunc the index of the 3A function
@param[in] pParam the parameter of the 3A function
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_Set3AFunction(MMP_UBYTE ubSnrSel, MMP_ISP_3A_FUNC eFunc, int pParam)
{
    if (MMPS_Sensor_IsInitialized(PRM_SENSOR))
        return MMPF_ISP_Set3AFunction(ubSnrSel, eFunc, pParam);
    else
        return MMP_SENSOR_ERR_INITIALIZE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetIQFunction
//  Description :
//------------------------------------------------------------------------------
/** @brief Set the IQ function

The function Set the IQ function
@param[in] sFunc the index of the IQ function
@param[in] pParam the parameter of the IQ function
@retval MMP_ERR_NONE success
*/
MMP_ERR MMPS_Sensor_SetIQFunction(MMP_UBYTE ubSnrSel, MMP_ISP_IQ_FUNC eFunc, int pParam)
{
    if (MMPS_Sensor_IsInitialized(PRM_SENSOR))
        return MMPF_ISP_SetIQFunction(ubSnrSel,eFunc, pParam);
    else
        return MMP_SENSOR_ERR_INITIALIZE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_RegisterCallback
//  Description :
//------------------------------------------------------------------------------
/** @brief the function registers the callback function to inform motion detected.

The function registers the callback which will be called when motion detected.
@param[in] Callback The Callback function
@return It reports the status of the operation.
*/
MMP_ERR MMPS_Sensor_RegisterCallback(MMP_UBYTE ubEvent, void *pvCallback)
{
    return MMPF_Sensor_RegisterCallback(ubEvent, pvCallback);
}

#if 0
void _____YUV_Sensor_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetYUVSnrSrcType
//  Description :
//------------------------------------------------------------------------------
void MMPS_Sensor_GetYUVSnrSrcType(MMP_SNR_YUV_SRC_TYPE *peSnrSrc)
{
    *peSnrSrc = MMP_SNR_YUV_SRC_HD; // TBD
}

#if 0
void _____Analog_Decoder_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_TrigCheckAnaDecSrcType
//  Description :
//------------------------------------------------------------------------------
static void MMPS_Sensor_TrigCheckAnaDecSrcType(void *ptmr, void *parg)
{
    MMP_UBYTE ubSnrSel = *(MMP_UBYTE*)parg;

    if (ubSnrSel == SCD_SENSOR && (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER))) {
        MMPF_OS_SetFlags(SENSOR_Flag, SENSOR_FLAG_CHECK_TVDEC_TYPE, MMPF_OS_FLAG_SET);
    }
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(MMP_UBYTE ubSnrSel, void *pvCallback, MMP_ULONG ulPeriod, MMP_BOOL bEnable)
{
    if (bEnable) {

        if (m_ulAnaDecSrcTypeDetectTimer[ubSnrSel] != MMPF_OS_CREATE_TMR_INT_ERR) {
            MMPS_SNR_DBG_ERR(1, "WARNING : Snr[%d] Check Src Type Timer Open Twice\r\n", ubSnrSel);
            return MMP_ERR_NONE;
        }

        MMPS_SNR_DBG_MSG(0, "Start Snr[%d] Check Src Type timer\r\n", ubSnrSel);

        if (pvCallback == NULL)
            m_ulAnaDecSrcTypeDetectTimer[ubSnrSel] = MMPF_OS_StartTimer(ulPeriod, MMPF_OS_TMR_OPT_PERIODIC, (MMPF_OS_TMR_CALLBACK)&MMPS_Sensor_TrigCheckAnaDecSrcType, (void*)&m_ubSnrSel[ubSnrSel]);
        else
            m_ulAnaDecSrcTypeDetectTimer[ubSnrSel] = MMPF_OS_StartTimer(ulPeriod, MMPF_OS_TMR_OPT_PERIODIC, (MMPF_OS_TMR_CALLBACK)pvCallback, (void*)&m_ubSnrSel[ubSnrSel]);
    }
    else {

        if (m_ulAnaDecSrcTypeDetectTimer[ubSnrSel] != MMPF_OS_CREATE_TMR_INT_ERR) {

            MMPS_SNR_DBG_MSG(0, "Stop Snr[%d] Check Src Type timer\r\n", ubSnrSel);

            MMPF_OS_StopTimer(m_ulAnaDecSrcTypeDetectTimer[ubSnrSel], NULL);
            m_ulAnaDecSrcTypeDetectTimer[ubSnrSel] = MMPF_OS_CREATE_TMR_INT_ERR;
        }
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_GetAnaDecSrcType
//  Description :
//------------------------------------------------------------------------------
void MMPS_Sensor_GetAnaDecSrcType(MMP_SNR_ANADEC_SRC_TYPE *peSrcType)
{
    MMPF_Sensor_GetAnaDecSrcType(peSrcType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_CheckAnaDecSrcType
//  Description :
//------------------------------------------------------------------------------
void MMPS_Sensor_CheckAnaDecSrcType(MMP_UBYTE ubSnrSel, MMP_SNR_ANADEC_SRC_TYPE *peSrcType)
{
    MMPF_Sensor_CheckAnaDecSrcType(ubSnrSel, peSrcType);
    MMPF_Sensor_SetAnaDecSrcType(*peSrcType);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_EnableAnaDecSrcTypeDetect
//  Description :
//------------------------------------------------------------------------------
void MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_BOOL bEnable)
{
    MMPF_Sensor_EnableAnaDecSrcTypeDetect(bEnable);
}
//------------------------------------------------------------------------------
//  Function    : MMPS_Sensor_SetMirrorFlip
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_Sensor_SetMirrorFlip(MMP_UBYTE ubSnrSel, MMP_SNR_ORIT Orit)
{
	return MMPF_Sensor_SetMirrorFlip(ubSnrSel, Orit);
}
/// @}
