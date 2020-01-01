//==============================================================================
//
//  File        : AHC_Gsensor.c
//  Description : AHC Gsensor control function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "mmpf_gsensor.h"
#include "ahc_gsensor.h"
#include "GSensor_ctrl.h"
#include "ahc_menu.h"

#if(SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
UINT32  GSNRPowerOnThd = 0;
#endif

extern MMPF_OS_FLAGID GsensorCtrlFlag;

/*===========================================================================
 * Main body
 *===========================================================================*/
AHC_BOOL AHC_Gsensor_Module_Attached(void)
{
    return ((MMPF_3RDParty_Gsensor_Attached() == MMP_TRUE) ? AHC_TRUE : AHC_FALSE);
}

AHC_BOOL AHC_Gsensor_Initial(void)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_Initial();
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_ReadRegister(UINT16 reg , UINT16* pval)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_ReadRegister((MMP_UBYTE)reg, (MMP_UBYTE *)pval );
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_WriteRegister(UINT16 reg , UINT16 pval)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_WriteRegister((MMP_UBYTE)reg, (MMP_UBYTE)pval);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_ReadOffsetFromFile(void)
{
   return AHC_FALSE;
}

AHC_BOOL AHC_Gsensor_WriteOffsetToFile(void)
{
   return AHC_FALSE;
}

AHC_BOOL AHC_Gsensor_ResetDevice(void)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_ResetDevice();
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_GetSensorOffset(AHC_GSENSOR_DATA *offset)
{
    MMP_ERR ret_val;
    GSENSOR_DATA GsnrOffset;

    ret_val = MMPF_3RDParty_Gsensor_GetSensorOffset(&GsnrOffset);
    offset->acc_val[0] = GsnrOffset.acc_val[0];
    offset->acc_val[1] = GsnrOffset.acc_val[1];
    offset->acc_val[2] = GsnrOffset.acc_val[2];
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetSensorOffset(AHC_GSENSOR_DATA *offset)
{
    MMP_ERR ret_val;
    GSENSOR_DATA GsnrOffset;

    GsnrOffset.acc_val[0] = offset->acc_val[0];
    GsnrOffset.acc_val[1] = offset->acc_val[1];
    GsnrOffset.acc_val[2] = offset->acc_val[2];
    ret_val = MMPF_3RDParty_Gsensor_SetSensorOffset(&GsnrOffset);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_Read_XYZ(AHC_GSENSOR_DATA *data)
{
    MMP_ERR ret_val;
    GSENSOR_DATA GsnrData;

    ret_val = MMPF_3RDParty_Gsensor_Read_XYZ(&GsnrData);
    data->acc_val[0] = GsnrData.acc_val[0];
    data->acc_val[1] = GsnrData.acc_val[1];
    data->acc_val[2] = GsnrData.acc_val[2];
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_Read_XYZ_WithCompensation(AHC_GSENSOR_DATA *data)
{
    MMP_ERR ret_val;
    GSENSOR_DATA GsnrData;

    ret_val = MMPF_3RDParty_Gsensor_Read_XYZ_WithCompensation(&GsnrData);
    data->acc_val[0] = GsnrData.acc_val[0];
    data->acc_val[1] = GsnrData.acc_val[1];
    data->acc_val[2] = GsnrData.acc_val[2];
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_Read_Accel_Avg(AHC_GSENSOR_DATA *data)
{
    MMP_ERR ret_val;
    GSENSOR_DATA GsensorData;

    ret_val = MMPF_3RDParty_Gsensor_Read_Accel_Avg(&GsensorData);
    data->acc_val[0] = GsensorData.acc_val[0];
    data->acc_val[1] = GsensorData.acc_val[1];
    data->acc_val[2] = GsensorData.acc_val[2];
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_Calibration(void)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_Calibration();
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetIntDuration(UINT8 arg)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetIntDuration(arg);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_GetIntStatus(UINT8* pstatus)
{
    MMP_ERR ret_val;
    UINT8 u8IntStatus;
    ret_val = MMPF_3RDParty_Gsensor_GetIntStatus(&u8IntStatus);
    *pstatus = u8IntStatus;
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetPowerSaveMode(UINT8 mode)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetPowerSaveMode(mode);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetNormalModeDataRate(UINT8 rate)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetNormalModeDataRate(rate);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetInterruptSource(UINT8 src)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetInterruptSource(src);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_GetDataRate(UINT16 *wDataRate)
{
    MMP_ERR ret_val;
    UINT16 usDataRate;
    ret_val = MMPF_3RDParty_Gsensor_GetDataRate(&usDataRate);
    *wDataRate = usDataRate;
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetDynamicRange(UINT8 ubDrange)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetDynamicRange(ubDrange);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_GetDynamicRange(UINT8 *ubDrange)
{
    MMP_ERR ret_val;
    UINT8 ubDynamicRange;
    ret_val = MMPF_3RDParty_Gsensor_GetDynamicRange(&ubDynamicRange);
    *ubDrange = ubDynamicRange;
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

AHC_BOOL AHC_Gsensor_SetCurInfo(void)
{
#if (GSENSOR_CONNECT_ENABLE)
    MMPF_OS_SetFlags(GsensorCtrlFlag, GSENSOR_FLAG_GSNRINFO2CHUCK, MMPF_OS_FLAG_SET);
#endif
    return AHC_TRUE;
}

/* Set Power On Gsensor Interrupt Status */
AHC_BOOL AHC_Gsensor_SetPowerOnIntThreshold(void)
{
    MMP_ERR err = MMP_ERR_NONE;
#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
    UINT32 sens;
    UINT8  ubStableTimes = 0;

    if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GSENSOR_PWR_ON_SENS, &sens) == AHC_FALSE)
    {
        sens = GSENSOR_POWERON_SENSITIVITY_OFF; // default
    }

    switch(sens)
    {
        case GSENSOR_POWERON_SENSITIVITY_L0:
            GSNRPowerOnThd = POWER_ON_GSNR_SENS_LEVEL0;
        break;
        case GSENSOR_POWERON_SENSITIVITY_L1:
            GSNRPowerOnThd = POWER_ON_GSNR_SENS_LEVEL1;
        break;
        case GSENSOR_POWERON_SENSITIVITY_L2:
            GSNRPowerOnThd = POWER_ON_GSNR_SENS_LEVEL2;
        break;
        default:
            GSNRPowerOnThd = 0;
        break;
    }
    printc(FG_BLUE("GSNRPowerOnThd=%d\r\n"),GSNRPowerOnThd);
    err = MMPF_3RDParty_Gsensor_IOControl(GSNR_CMD_SET_PWR_ON_INT_THD, (void*)&GSNRPowerOnThd);
    if (err != MMP_ERR_NONE) {
        return FALSE;
    }

    while (1) {
        MMP_UBYTE ubIntStatus = 0;

        err = MMPF_3RDParty_Gsensor_IOControl(GSNR_CMD_GET_INT_STATUS, (void*)&ubIntStatus);
        if (err != MMP_ERR_NONE) {
            return FALSE;
        }

        if (0 == ubIntStatus) {
            ubStableTimes++;
        }
        else {
            ubStableTimes = 0;
            RTNA_DBG_Str(0, FG_RED("G-Sensor is sharking ...\r\n"));
        }

        AHC_OS_SleepMs(10);

        if (ubStableTimes >= 20) {
            RTNA_DBG_Str(0, "G-Sensor is silent ...\r\n");
            break;
        }
    }
#endif

    return AHC_TRUE;
}

#if(SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
UINT32 AHC_GSNR_PWROn_MovieTimeReset(void)
{
    return POWER_ON_GSNR_MOVIE_TIME*10;
}
#endif

AHC_BOOL AHC_Gsensor_GetGroundAxisStatus(UINT8* pos)
{
    return AHC_FALSE;
}

AHC_BOOL AHC_Gsensor_SetIntThreshold(INT16 thd)
{
    MMP_ERR ret_val;
    ret_val = MMPF_3RDParty_Gsensor_SetIntThreshold((MMP_SHORT)thd);
    AHC_GSENSOR_CHECK_RETURE_VALUE(ret_val, AHC_GSENSOR_NO_ERROR, AHC_GSENSOR_RET_TRUE, AHC_GSENSOR_RET_FALSE)
}

