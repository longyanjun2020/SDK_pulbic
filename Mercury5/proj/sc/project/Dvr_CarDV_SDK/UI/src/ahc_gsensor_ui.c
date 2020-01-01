
//==============================================================================
//
//  File        : AHC_Gsensor_UI.c
//  Description : AHC Gsensor UI layer function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_menu.h"
#include "ahc_message.h"
#include "ahc_gsensor.h"
//#include "ahc_general.h"
//#include "ahc_general_cardv.h"
#include "ahc_parameter.h"
#include "dsc_Key.h"
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"
#include "MenuSetting.h"
//#include "statevideofunc.h"
#include "parkingmodectrl.h"

#if (GSENSOR_CONNECT_ENABLE)

/*===========================================================================
 * Global varible
 *===========================================================================*/
#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
AHC_GSENSOR_DATA TempGValue = {{0, 0, 0}};
#endif
AHC_BOOL    dump_GValues = AHC_FALSE;
AHC_GSENSOR_DATA dump_GValue = {{0, 0, 0}};

AHC_BOOL    m_ubGsnrIsObjMove           = AHC_FALSE; //Status, check if the system is shaking or not.
AHC_BOOL    m_ubGsnrIsObjMove_Parking   = AHC_FALSE;
AHC_BOOL    m_ubGsnrEnter_Parking       = AHC_FALSE;

#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
extern UINT32       GSNRPowerOnThd;
extern AHC_BOOL     ubGsnrPwrOnActStart;
extern UINT32       m_ulGSNRRecStopCnt;
extern AHC_BOOL     ubUIInitDone(void);
extern UINT32       AHC_GSNR_PWROn_MovieTimeReset(void);
#endif

AHC_BOOL        dump_GValues_osd = AHC_FALSE;

/*===========================================================================
 * Main body
 *===========================================================================*/
AHC_BOOL AHC_Gsensor_GetIntGpioStatus(MMP_UBYTE *pstatus)
{
    MMP_UBYTE   value   = 0;

#if POWER_ON_BY_GSENSOR_EN && defined(GSENSOR_INT)
    if (GSENSOR_INT != MMP_GPIO_MAX) {
        AHC_GPIO_ConfigPad(GSENSOR_INT, 0);
        AHC_GPIO_SetOutputMode(GSENSOR_INT, MMP_FALSE);
        AHC_GPIO_GetData(GSENSOR_INT, &value);
    }
#endif

    *pstatus = (value & 0xFF);

    return MMP_ERR_NONE;
}

/* Use Gsensor Acceleration */
/* Output: milli-g */
INT16 AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS axis)//Move to UI layer
{
    switch (axis) {
    case AHC_GSENSOR_AXIS_X:
    case AHC_GSENSOR_AXIS_Y:
    case AHC_GSENSOR_AXIS_Z:
        {
            UINT32  thd = 0x7FFF;//Unit: gravivy tolerance * (Scale 1000)

            switch(MenuSettingConfig()->uiGsensorSensitivity)
            {
            #if (MENU_GENERAL_GSENSOR_EN==GSENSOR_5_LEVEL)
                #if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
                case GSENSOR_SENSITIVITY_L0:
                    thd = GSNR_SENS_5LEVEL0;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL1_EN)
                case GSENSOR_SENSITIVITY_L1:
                    thd = GSNR_SENS_5LEVEL1;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
                case GSENSOR_SENSITIVITY_L2:
                    thd = GSNR_SENS_5LEVEL2;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL3_EN)
                case GSENSOR_SENSITIVITY_L3:
                    thd = GSNR_SENS_5LEVEL3;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
                case GSENSOR_SENSITIVITY_L4:
                    thd = GSNR_SENS_5LEVEL4;
                break;
                #endif
            #elif (MENU_GENERAL_GSENSOR_EN==GSENSOR_4_LEVEL)
                case GSENSOR_SENSITIVITY_L0:    // HIGH
                    thd = GSNR_SENS_5LEVEL0;
                break;
                case GSENSOR_SENSITIVITY_L2:    // MIDDLE
                    thd = GSNR_SENS_5LEVEL2;
                break;
                case GSENSOR_SENSITIVITY_L3:    // LOW
                    thd = GSNR_SENS_5LEVEL3;
                break;
                case GSENSOR_SENSITIVITY_L4:    // STANDARD
                    thd = GSNR_SENS_5LEVEL4;
                break;
            #else
                #if (MENU_GENERAL_GSENSOR_LEVEL0_EN)
                case GSENSOR_SENSITIVITY_L0:
                    thd = GSNR_SENS_3LEVEL0;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL2_EN)
                case GSENSOR_SENSITIVITY_L2:
                    thd = GSNR_SENS_3LEVEL1;
                break;
                #endif
                #if (MENU_GENERAL_GSENSOR_LEVEL4_EN)
                case GSENSOR_SENSITIVITY_L4:
                    thd = GSNR_SENS_3LEVEL2;
                break;
                #endif
            #endif
                default:
                    thd = 0x7FFF;
                break;
            }

            return thd;
        }
        break;

    default:
        AHC_DBG_ERR(1, "--W-- %s - TBD\r\n", __FUNCTION__);
        return 0x7FFF;
    }

    return 0x7FFF;
}

/* Output: milli-g */
INT16 AHC_Gsensor_GetAcceSensitivity_Parking(AHC_GSENSOR_AXIS axis) //Move to Parking mode?
{
    #if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4)
    return AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);
    #endif

    AHC_DBG_ERR(1, "--W-- %s is TBD\r\n", __FUNCTION__);
    return 0x7FFF;
}

#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
AHC_BOOL AHC_Gsensor_GetCurAcc_Diff(AHC_BOOL* bObjMove, AHC_BOOL* bObjMove_1, AHC_BOOL* bObjMove_2)
{
    MMP_ERR             err;
    AHC_GSENSOR_DATA    sdata = {{0, 0, 0}};
    AHC_GSENSOR_DATA    sDiffData = {{0, 0, 0}};
    INT16               CurSensitivity = 0;
#if ((SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2) || (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4))
    INT16               CurSensitivityParking = 0;
#endif
#if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
    INT16               SensX = 0,SensY = 0,SensZ = 0;
#endif
    static  UINT8       ubCounter = 10;//Check the different value every 1 second.
    static  AHC_GSENSOR_DATA TempMax = {{-32767, -32767, -32767}};
    static  AHC_GSENSOR_DATA TempMin = {{32767, 32767, 32767}};
    MMP_UBYTE           i;

    if(AHC_Gsensor_Module_Attached() == AHC_FALSE) {
        if (bObjMove)
            *bObjMove = AHC_FALSE;
        return AHC_FALSE;
    }

#if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
    SensX = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);
    SensY = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_Y);
    SensZ = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_Z);
#else
    CurSensitivity = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);

    #if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    CurSensitivityParking = AHC_Gsensor_GetAcceSensitivity_Parking(AHC_GSENSOR_AXIS_X);
    #endif
    #if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4)
    CurSensitivityParking = AHC_Gsensor_GetAcceSensitivity_Parking(AHC_GSENSOR_AXIS_X);
    #endif
#endif

    //AHC_DBG_MSG(1, "Sen Nor : %d\r\n",CurSensitivity);
    //AHC_DBG_MSG(1, "Sen Parking : %d\r\n",CurSensitivityParking);

    //err = AHC_Gsensor_Read_XYZ(&sdata);
    err = AHC_Gsensor_Read_XYZ_WithCompensation(&sdata);

    if(dump_GValues)
    {
         AHC_DBG_MSG(1, "x: %d mg\r\n", sdata.acc_val[0]);
         AHC_DBG_MSG(1, "y: %d mg\r\n", sdata.acc_val[1]);
         AHC_DBG_MSG(1, "z: %d mg\r\n", sdata.acc_val[2]);
    }

    ubCounter--;

    for(i = 0; i < 3; i++) {
        if (sdata.acc_val[i] > TempMax.acc_val[i]) {
            TempMax.acc_val[i] = sdata.acc_val[i];
        }
        if (sdata.acc_val[i] < TempMin.acc_val[i]) {
            TempMin.acc_val[i] = sdata.acc_val[i];
        }
    }

    if(ubCounter == 0) {
        for(i = 0; i < 3; i++) {
            sDiffData.acc_val[i] = TempMax.acc_val[i] - TempMin.acc_val[i];
        }

        if(dump_GValues) {
            AHC_DBG_MSG(1, "Max Diff x: %d mg\r\n", sDiffData.acc_val[0]);
            AHC_DBG_MSG(1, "Max Diff y: %d mg\r\n", sDiffData.acc_val[1]);
            AHC_DBG_MSG(1, "Max Diff z: %d mg\r\n", sDiffData.acc_val[2]);
        }
    }

    if(ubCounter == 0) {
        #if ((SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2) || (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4))
        if( sDiffData.acc_val[0] >= CurSensitivityParking ||
            sDiffData.acc_val[1] >= CurSensitivityParking ||
            sDiffData.acc_val[2] >= CurSensitivityParking) {
            if (bObjMove_1)
            *bObjMove_1 = AHC_TRUE;
        }
        else {
            if (bObjMove_1)
                *bObjMove_1 = AHC_FALSE;
        }
        #else
        if (bObjMove_1)
            *bObjMove_1 = AHC_FALSE;
        #endif

        #if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
        if (bObjMove_2)
            *bObjMove_2 = AHC_FALSE;
        #endif

        #if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
        if( sDiffData.acc_val[0] >= SensX ||
            sDiffData.acc_val[1] >= SensY ||
            sDiffData.acc_val[2] >= SensZ) {
            if (bObjMove)
                *bObjMove = AHC_TRUE;
        }
        else {
            if (bObjMove)
                *bObjMove = AHC_FALSE;
        }
        #else

        if( sDiffData.acc_val[0] >= CurSensitivity ||
            sDiffData.acc_val[1] >= CurSensitivity ||
            sDiffData.acc_val[2] >= CurSensitivity) {
            if (bObjMove)
                *bObjMove = AHC_TRUE;
        }
        else {
            if (bObjMove)
                *bObjMove = AHC_FALSE;
        }
        #endif

        if(dump_GValues_osd) {
            dump_GValue.acc_val[0] = sDiffData.acc_val[0];
            dump_GValue.acc_val[1] = sDiffData.acc_val[1];
            dump_GValue.acc_val[2] = sDiffData.acc_val[2];
            //AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0); // For reflesh OSD frequently.
        }

        for(i = 0; i< 3; i++) {
            TempMax.acc_val[i] = -32767;
            TempMin.acc_val[i] = 32767;
        }

        ubCounter = 10;
    }
    else {
        if (bObjMove)
            *bObjMove = AHC_FALSE;
    }

    return AHC_TRUE;
}
#endif

#if (GSENSOR_DETECT_MODE == GSENSOR_DETECT_DIRECT)
AHC_BOOL AHC_Gsensor_GetCurAcc_Direct(AHC_BOOL* bObjMove, AHC_BOOL* bObjMove_1, AHC_BOOL* bObjMove_2)
{
    if(AHC_Gsensor_Module_Attached() == AHC_FALSE) {
        return AHC_FALSE;
    }

    MMP_ERR             err;
    AHC_GSENSOR_DATA    sdata = {{0, 0, 0}};
    INT16               CurSensitivity = 0;
#if ((SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2) || (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4))
    INT16               CurSensitivityParking = 0;
#endif
#if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
    INT16               SensX = 0,SensY = 0,SensZ = 0;
#endif

#if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
    SensX = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);
    SensY = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_Y);
    SensZ = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_Z);
#else
    CurSensitivity = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);

#if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    CurSensitivityParking = AHC_Gsensor_GetAcceSensitivity_Parking(AHC_GSENSOR_AXIS_X);
#endif
#if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4)
    CurSensitivityParking = AHC_Gsensor_GetAcceSensitivity_Parking(AHC_GSENSOR_AXIS_X);
#endif
#endif

    //AHC_DBG_MSG(1, "Sen Nor : %d\r\n",CurSensitivity);
    //AHC_DBG_MSG(1, "Sen Parking : %d\r\n",CurSensitivityParking);

    //err = AHC_Gsensor_Read_XYZ(&sdata);
    err = AHC_Gsensor_Read_XYZ_WithCompensation(&sdata);

    if(dump_GValues) {
        AHC_DBG_MSG(1, "x: %d mg\r\n", sdata.acc_val[0]);
        AHC_DBG_MSG(1, "y: %d mg\r\n", sdata.acc_val[1]);
        AHC_DBG_MSG(1, "z: %d mg\r\n", sdata.acc_val[2]);
    }

#if ((SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2) || (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4))
    if( sdata.acc_val[0] >= CurSensitivityParking ||
        sdata.acc_val[1] >= CurSensitivityParking ||
        sdata.acc_val[2] >= CurSensitivityParking) {
        if (bObjMove_1)
            *bObjMove_1 = AHC_TRUE;
    }
    else {
        if (bObjMove_1)
            *bObjMove_1 = AHC_FALSE;
    }
#else
    if (bObjMove_1)
        *bObjMove_1 = AHC_FALSE;
#endif

#if(SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    if (bObjMove_2)
        *bObjMove_2 = AHC_FALSE;
#endif

#if (MENU_MOVIE_GSENSOR_SENSITIVITY_XYZ_EN)
    if( sdata.acc_val[0] >= SensX ||
        sdata.acc_val[1] >= SensY ||
        sdata.acc_val[2] >= SensZ) {
        if (bObjMove)
            *bObjMove = AHC_TRUE;
    }
    else {
        if (bObjMove)
            *bObjMove = AHC_FALSE;
    }
#else

    if( sdata.acc_val[0] >= CurSensitivity ||
        sdata.acc_val[1] >= CurSensitivity ||
        sdata.acc_val[2] >= CurSensitivity) {
        if (bObjMove)
            *bObjMove = AHC_TRUE;
    }
    else {
        if (bObjMove)
            *bObjMove = AHC_FALSE;
    }
#endif

    if(dump_GValues_osd) {
        dump_GValue.acc_val[0] = sdata.acc_val[0];
        dump_GValue.acc_val[1] = sdata.acc_val[1];
        dump_GValue.acc_val[2] = sdata.acc_val[2];
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0); // For reflesh OSD frequently.
    }

    return AHC_TRUE;
}
#endif

AHC_BOOL AHC_Gsensor_GetCurAcceleration(AHC_BOOL* bObjMove, AHC_BOOL* bObjMove_1, AHC_BOOL* bObjMove_2)
{
#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
    return AHC_Gsensor_GetCurAcc_Diff(bObjMove, bObjMove_1, bObjMove_2);
#elif (GSENSOR_DETECT_MODE == GSENSOR_DETECT_DIRECT)
    return AHC_Gsensor_GetCurAcc_Direct(bObjMove, bObjMove_1, bObjMove_2);
#else
    return AHC_FALSE;
#endif
}

MMP_UBYTE AHC_Gsensor_IsGroundAxisRotate(void)
{
    if(AHC_Gsensor_Module_Attached())
    {
        MMP_UBYTE       pos;

        AHC_Gsensor_GetGroundAxisStatus(&pos);

        return pos;
    }

    return GSNR_POSITION_NOCHANGE;
}

/* Use Gsensor Interrupt Status */
AHC_BOOL AHC_Gsensor_UI_SetIntThreshold(void)
{
    AHC_BOOL bRet = AHC_FALSE;

    if(AHC_Gsensor_Module_Attached())
    {
        MMP_ERR     err;
        INT16       thd;

        thd = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);

        bRet = AHC_Gsensor_SetIntThreshold(thd);
    }

    return bRet;
}

AHC_BOOL AHC_Gsensor_GetCurIntStatus(AHC_BOOL* bObjMove)
{
    AHC_BOOL bRet = AHC_FALSE;

    if (AHC_Gsensor_Module_Attached())
    {
        MMP_ERR         err;
        MMP_UBYTE       int_status = 0;

        bRet = AHC_Gsensor_GetIntStatus(&int_status);
        if (bRet == AHC_FALSE) {
            return bRet;
        }

        if(int_status)
            *bObjMove = AHC_TRUE;
        else
            *bObjMove = AHC_FALSE;
    }

    return bRet;
}

AHC_BOOL AHC_Gsensor_Polling(UINT8 ubType)
{
    if(AHC_Gsensor_Module_Attached())
    {
        AHC_BOOL bLockVRFile = VideoFunc_LockFileEnabled();

        switch(ubType)
        {
        case MOVE_BY_ACCELERATION:
            #if (POWER_ON_BY_GSENSOR_EN)
            if (MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF &&
                !bLockVRFile && !m_ubGsnrIsObjMove)
            {
                //extern AHC_BOOL ubUIInitDone(void);
                // when m_ubGsnrIsObjMove was TRUE, should not call it,
                // must wait m_ubGsnrIsObjMove cleaned!

                if(ubGsnrPwrOnActStart && ubUIInitDone())
                {
                    AHC_Gsensor_GetCurAcceleration(&m_ubGsnrIsObjMove, &m_ubGsnrIsObjMove_Parking, &m_ubGsnrEnter_Parking);

                    if(m_ubGsnrIsObjMove)
                    {
                        if(GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_SHAKED)
                        {
                            m_ulGSNRRecStopCnt = AHC_GSNR_PWROn_MovieTimeReset();

                            if(!VideoFunc_GetRecordStatus())
                                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, 0);
                        }
                    }
                }
                else
                {
                    if(VideoFunc_GetRecordStatus())
                        AHC_Gsensor_GetCurAcceleration(&m_ubGsnrIsObjMove, &m_ubGsnrIsObjMove_Parking, &m_ubGsnrEnter_Parking);
                }
            }
            else
            {
                if(ubGsnrPwrOnActStart && ubUIInitDone())
                {
                    AHC_BOOL ubShaked;
                    AHC_Gsensor_GetCurAcceleration(&ubShaked, NULL, NULL);

                    if(ubShaked)
                    {
                        if(GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_SHAKED)
                        {
                            m_ulGSNRRecStopCnt = AHC_GSNR_PWROn_MovieTimeReset();
                        }
                    }
                }
            }
            #else
            if( MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF &&
                VideoFunc_GetRecordStatus() && !bLockVRFile && !m_ubGsnrIsObjMove)
            {
                AHC_Gsensor_GetCurAcceleration(&m_ubGsnrIsObjMove, &m_ubGsnrIsObjMove_Parking, &m_ubGsnrEnter_Parking);
            }
            #endif

            if (uiGetParkingModeEnable() &&
                (MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF) &&
                !VideoFunc_GetRecordStatus() &&
                !m_ubGsnrIsObjMove)
            {
                AHC_Gsensor_GetCurAcceleration(&m_ubGsnrIsObjMove, &m_ubGsnrIsObjMove_Parking, &m_ubGsnrEnter_Parking);
            }
            break;

        case MOVE_BY_INTERUPT:
            if (dump_GValues)
            {
                AHC_GSENSOR_DATA    sdata;

                AHC_Gsensor_Read_XYZ_WithCompensation(&sdata);
                AHC_DBG_MSG(1, "x: %d mg, y: %d mg, z: %d mg\r\n", sdata.acc_val[0], sdata.acc_val[1], sdata.acc_val[2]);
            }

            #if (POWER_ON_BY_GSENSOR_EN)
            if( MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF &&
                !bLockVRFile && !m_ubGsnrIsObjMove)
            {
                // when m_ubGsnrIsObjMove was TRUE, should not call it,
                // must wait m_ubGsnrIsObjMove cleaned!

                if(ubGsnrPwrOnActStart && ubUIInitDone())
                {
                    AHC_Gsensor_GetCurIntStatus(&m_ubGsnrIsObjMove);

                    if(m_ubGsnrIsObjMove)
                    {
                        if(GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_SHAKED)
                        {
                            m_ulGSNRRecStopCnt = AHC_GSNR_PWROn_MovieTimeReset();

                            if(!VideoFunc_GetRecordStatus())
                                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, 0);
                        }
                    }
                }
                else
                {
                    if(VideoFunc_GetRecordStatus())
                        AHC_Gsensor_GetCurIntStatus(&m_ubGsnrIsObjMove);
                }
            }
            else
            {
                if(ubGsnrPwrOnActStart && ubUIInitDone())
                {
                    AHC_BOOL ubShaked;
                    AHC_Gsensor_GetCurIntStatus(&ubShaked);

                    if(ubShaked)
                    {
                        if(GSNR_PWRON_REC_BY && GSNR_PWRON_REC_BY_SHAKED)
                        {
                            m_ulGSNRRecStopCnt = AHC_GSNR_PWROn_MovieTimeReset();
                        }
                    }
                }
            }
            #else
            if( MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF &&
                VideoFunc_GetRecordStatus() && !bLockVRFile && !m_ubGsnrIsObjMove)
            {
                // when m_ubGsnrIsObjMove was TRUE, should not call it,
                // must wait m_ubGsnrIsObjMove cleaned!
                AHC_Gsensor_GetCurIntStatus(&m_ubGsnrIsObjMove);
            }
            #endif
            break;

        case Z_AXIS_GRAVITY_CAHNGE:
            {
                static MMP_UBYTE    ubDetectCnt = 0;
                MMP_UBYTE           pos;

                ubDetectCnt = (ubDetectCnt+1) % 8;

                if(ubDetectCnt>0)
                    break;

                AHC_SetRotateSrc(SRC_G_SNR);

                pos = AHC_Gsensor_IsGroundAxisRotate();

#if (FLIP_CTRL_METHOD & CTRL_BY_G_SNR) && (G_SNR_FLIP_SELECT != FLIP_NONE)
                if (pos == GSNR_POSITION_DOWN) {
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, DEVICE_LCD_INV, 0);
                } else if(pos == GSNR_POSITION_UP) {
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, DEVICE_LCD_NOR, 0);
                }
#endif
            }
            break;

        default:
            // NOP
            break;
        }

        if(m_ubGsnrIsObjMove || m_ubGsnrIsObjMove_Parking)
        {
            static MMP_ULONG ulLastTriggerTime = 0;
            //MMP_ULONG ulCurrentTime = (OSTimeGet() * 1000) / OS_TICKS_PER_SEC;
            MMP_ULONG ulCurrentTime = 0;
            MMPF_OS_GetTime(&ulCurrentTime);
            ulCurrentTime = (ulCurrentTime * 1000) / OS_TICKS_PER_SEC;
            if ((ulCurrentTime - ulLastTriggerTime) < 500) // SW debounce: 500 ms
            {
                AHC_DBG_MSG(0, " ##too short gsnr interval, bypass.\r\n");
                return AHC_TRUE;
            }
            ulLastTriggerTime = ulCurrentTime;

            #if (((SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_1)  || (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2))|| (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4) )
            if(uiGetParkingModeEnable() && m_ubGsnrIsObjMove_Parking)
            {
                #if 1
                if (!VideoFunc_GetRecordStatus() && (AHC_GetAhcSysMode() == AHC_MODE_RECORD_PRERECD) && !uiGetParkingModeRecord())

                #else
                if(!VideoFunc_GetRecordStatus() && (uiGetCurrentState() != UI_PARKING_MENU_STATE && uiGetCurrentState() != UI_PARKING_EXIT_STATE
                && uiGetCurrentState() != UI_PARKING_MOVE_HINT && uiGetCurrentState() != UI_PARKING_SPACE_HINT))
                #endif
                {
#if GSENSOR_DBG_MSG
                    AHC_DBG_MSG(1, "Parking mode Gsensor Act\r\n");

                    #if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
                    AHC_DBG_MSG(1, "GValue 0 %d\r\n",TempGValue.acc_val[0]);
                    AHC_DBG_MSG(1, "GValue 1 %d\r\n",TempGValue.acc_val[1]);
                    AHC_DBG_MSG(1, "GValue 2 %d\r\n",TempGValue.acc_val[2]);
                    #endif
#endif

                    #if 1
                    AHC_DBG_MSG(0, " ##gsnr start record-3, %d.\r\n", __LINE__);
                    uiSetParkingModeRecord(AHC_TRUE);
                    m_ubGsnrIsObjMove = AHC_FALSE;
                    m_ubGsnrIsObjMove_Parking = AHC_FALSE;
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, KEY_VIDEO_RECORD, 0);

                    #else
                    uiSetParkingModeRecordState(AHC_TRUE);
                    uiSetParkingModeRecord(AHC_TRUE);
                    //SetKeyPadEvent(BUTTON_SET_PRESS);
                    GPSCtrl_GPSRawResetBuffer();
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_RECSTART_PRESS, 0);
                    #endif
                }
            }
            else if(!uiGetParkingModeEnable())
            #endif
            {
                if(m_ubGsnrIsObjMove)
                {
                    if (AHC_SDMMC_BasicCheck()) {
#if GSENSOR_DBG_MSG
                        AHC_DBG_MSG(1, "Normal mode Gsensor Act\r\n");

                        #if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
                        AHC_DBG_MSG(1, "GValue 0 %d\r\n",TempGValue.acc_val[0]);
                        AHC_DBG_MSG(1, "GValue 1 %d\r\n",TempGValue.acc_val[1]);
                        AHC_DBG_MSG(1, "GValue 2 %d\r\n",TempGValue.acc_val[2]);
                        #endif
#endif

                        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, GSENSOR_ACT, 0);
                        AHC_OS_SleepMs(100);
                    }
                }
            }

        }
    }

    return AHC_TRUE;
}

#endif
