/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_adas.h"
#include "mdtc_cfg.h"
#include "MenuSetting.h"
#include "MenuConfig_SDK.h"
#include "mmps_iva.h"

/*===========================================================================
 * Global variables
 *===========================================================================*/

#if (MOTION_DETECTION_EN)
UINT8       m_ubMotionMvTh          = 0xFF;
UINT8       m_ubMotionCntTh         = 0xFF;
#if defined(CFG_MVD_MODE_POWER_ON_ENABLE) && (VMD_ACTION != VMD_ACTION_NONE)
AHC_BOOL    m_ubMotionDtcEn         = AHC_TRUE;
#else
AHC_BOOL    m_ubMotionDtcEn         = AHC_FALSE;
#endif
#endif

/*===========================================================================
 * Extern variables
 *===========================================================================*/

#if (MOTION_DETECTION_EN)
extern UINT32       m_ulVMDRemindTime;
#endif

extern MMP_USHORT   gsAhcPrmSensor;
extern AHC_BOOL     gbAhcDbgBrk;

extern MDParamsIn_t   gstMdtcWinParam[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV];
extern MDParamsOut_t  gstMdtcWinResult[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV];

/*===========================================================================
 * Main Body
 *===========================================================================*/

#if 0
void ____Motion_Detect_Function_____(){ruturn;} //dummy
#endif

#if (MOTION_DETECTION_EN)
//------------------------------------------------------------------------------
//  Function    : AHC_GetMotionDetectionStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetMotionDetectionStatus(void)
{
    return m_ubMotionDtcEn;
}

//------------------------------------------------------------------------------
//  Function    : AHC_EnableMotionDetection
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_EnableMotionDetection(AHC_BOOL bEn)
{
    MMPS_Sensor_EnableVMD(bEn);
    m_ubMotionDtcEn = bEn;
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMotionDtcWinCfg
//  Description :
//------------------------------------------------------------------------------
void AHC_SetMotionDtcWinCfg(UINT8 ubWindowNum_X, UINT8 ubWindowNum_Y)
{
    if (ubWindowNum_X > MDTC_MAX_WIN_W_DIV) {
        printc(FG_RED("WARNING!! Set MD W_Window over limitation (Modify: %d --> %d)\r\n"), ubWindowNum_X, MDTC_MAX_WIN_W_DIV);
        ubWindowNum_X = MDTC_MAX_WIN_W_DIV;
    }
    if (ubWindowNum_Y > MDTC_MAX_WIN_H_DIV) {
        printc(FG_RED("WARNING!! Set MD H_Window over limitation (Modify: %d --> %d)\r\n"), ubWindowNum_Y, MDTC_MAX_WIN_H_DIV);
        ubWindowNum_Y = MDTC_MAX_WIN_H_DIV;
    }

    gstMdtcWinCfg.x_div = ubWindowNum_X;
    gstMdtcWinCfg.y_div = ubWindowNum_Y;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GetMotionDtcSensitivity
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_GetMotionDtcSensitivity(UINT8 *pubMvTh, UINT8 *pubCntTh)
{
    if (pubMvTh)
        *pubMvTh    = m_ubMotionMvTh;
    if (pubCntTh)
        *pubCntTh   = m_ubMotionCntTh;
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SetMotionDtcSensitivity
//  Description :
//------------------------------------------------------------------------------
int AHC_SetMotionDtcSensitivity(UINT8 ubMvTh, UINT8 ubCntTh)
{
    UINT8 i, j;

    m_ubMotionMvTh  = ubMvTh;
    m_ubMotionCntTh = ubCntTh;

    for (i = 0; i < gstMdtcWinCfg.x_div; i++)
    {
        for (j = 0; j < gstMdtcWinCfg.y_div; j++)
        {
            gstMdtcWinParam[i][j].enable = 1;
            gstMdtcWinParam[i][j].size_perct_thd_min = ubCntTh;
            gstMdtcWinParam[i][j].size_perct_thd_max = 100;
            gstMdtcWinParam[i][j].sensitivity        = ubMvTh;
            gstMdtcWinParam[i][j].learn_rate         = 500;
        }
    }

    //MMPS_Sensor_ConfigVMDThreshold(m_ubMotionMvTh, m_ubMotionCntTh, MVD_FRAME_GAP);
    return 2;
}

UINT32 AHC_GetVMDRecTimeLimit(void)
{
    UINT32 u32VMDRecTime = 0;

    switch(MenuSettingConfig()->uiVMDRecTime)
    {
    #if (MENU_MOVIE_VMD_REC_TIME_5SEC_EN)
        case VMD_REC_TIME_5SEC:
            u32VMDRecTime = 5;
            break;
    #endif
    #if (MENU_MOVIE_VMD_REC_TIME_10SEC_EN)
        case VMD_REC_TIME_10SEC:
            u32VMDRecTime = 10;
            break;
    #endif
    #if (MENU_MOVIE_VMD_REC_TIME_30SEC_EN)
        case VMD_REC_TIME_30SEC:
            u32VMDRecTime = 30;
            break;
    #endif
    #if (MENU_MOVIE_VMD_REC_TIME_1MIN_EN)
        case VMD_REC_TIME_1MIN:
            u32VMDRecTime = 60;
            break;
    #endif
        default:
            u32VMDRecTime = 5;
            break;
    }

    return u32VMDRecTime;
}

UINT32 AHC_GetVMDShotNumber(void)
{
    UINT32 u32VMDShotNum = 1;

    switch(MenuSettingConfig()->uiVMDShotNum)
    {
    #if (MENU_STILL_VMD_SHOT_NUM_1P_EN)
        case VMD_SHOT_NUM_1P:
            u32VMDShotNum = 1;
            break;
    #endif
    #if (MENU_STILL_VMD_SHOT_NUM_2P_EN)
        case VMD_SHOT_NUM_2P:
            u32VMDShotNum = 2;;
            break;
    #endif
    #if (MENU_STILL_VMD_SHOT_NUM_3P_EN)
        case VMD_SHOT_NUM_3P:
            u32VMDShotNum = 3;
            break;
    #endif
    #if (MENU_STILL_VMD_SHOT_NUM_5P_EN)
        case VMD_SHOT_NUM_5P:
            u32VMDShotNum = 5;
            break;
    #endif
        default:
            u32VMDShotNum = 1;
            break;
    }

    return u32VMDShotNum;
}
#endif

void AHC_AdjustVMDPreviewRes(int *w, int *h)
{
    #define VMD_MB_SIZE (16)

    UINT32 ulWidth, ulHeight;

    ulWidth  = *w;
    ulHeight = *h;

    printc("Original Preview W/H for VMD [%d]*[%d]\r\n", ulWidth, ulHeight);

    if( ulWidth%VMD_MB_SIZE != 0)
    {
        ulWidth = ((ulWidth/VMD_MB_SIZE)+1)*VMD_MB_SIZE;
    }

    if( ulHeight%VMD_MB_SIZE != 0)
    {
        ulHeight = ((ulHeight/VMD_MB_SIZE)+1)*VMD_MB_SIZE;
    }

    printc("Adjust Preview W/H for VMD [%d]*[%d]\r\n", ulWidth, ulHeight);

    *w = ulWidth;
    *h = ulHeight;
}

UINT16 AHC_VMDGetMotionCnt(void)
{
    UINT16 x, y;
    UINT16 usTotalObjCnt = 0;

    for (x = 0; x < gstMdtcWinCfg.x_div; x++) {
        for (y = 0; y < gstMdtcWinCfg.y_div; y++) {
            usTotalObjCnt += gstMdtcWinResult[x][y].obj_cnt;
        }
    }

    return usTotalObjCnt;
}

UINT8 AHC_VMDGetMotionRatio(void)
{
    UINT16  usTotalObjCnt = 0, usTotalObjTh = 0;
    UINT8   ubRatio = 0;
    UINT16  x, y;

    usTotalObjCnt = AHC_VMDGetMotionCnt();

    if (usTotalObjCnt >= (MDTC_WIDTH * MDTC_HEIGHT))
        return 100;

    for (x = 0; x < gstMdtcWinCfg.x_div; x++) {
        for (y = 0; y < gstMdtcWinCfg.y_div; y++) {
            usTotalObjTh += gstMdtcWinParam[x][y].size_perct_thd_min;
        }
    }

    if (usTotalObjCnt >= (((MDTC_WIDTH * MDTC_HEIGHT) *  usTotalObjTh) / 100)) {
        ubRatio = 100;
    }
    else {
        if (usTotalObjTh != 0)
            ubRatio = (usTotalObjCnt * 100) / (((MDTC_WIDTH * MDTC_HEIGHT) *  usTotalObjTh) / 100);
        else
            ubRatio = 100;
    }

    return ubRatio;
}

// Switch MVD mode when sensitivity is changed under Sensor Preview
void AHC_SwitchMotionDetectionMode(void)
{
#if defined(CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY) && (MOTION_DETECTION_EN) && (VMD_ACTION != VMD_ACTION_NONE)
    UINT8   ubMvTh, ubCntTh;

    AHC_GetMotionDtcSensitivity(&ubMvTh, &ubCntTh);
    m_ubMotionDtcEn = AHC_FALSE;

    if (0xFF != ubMvTh || 0xFF != ubCntTh) {
        m_ubMotionDtcEn = AHC_TRUE;
    }
    else {
        #if (VR_PREENCODE_EN)
        m_ubPreEncodeEn = AHC_FALSE;
        #endif
    }

    switch (uiGetCurrentState()) {
    #if (VMD_ACTION & VMD_RECORD_VIDEO)
    case UI_VIDEO_STATE:
        if (!VideoFunc_GetRecordStatus())
            VideoTimer_Stop();

        VideoRecMode_PreviewUpdate();
        break;
    #endif

    #if (VMD_ACTION & VMD_BURST_CAPTURE)
    case UI_CAMERA_STATE:
        CaptureTimer_Stop();
        CaptureMode_PreviewUpdate();
        break;
    #endif
    }
#endif
}

#if defined(CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY) && (MOTION_DETECTION_EN) && (VMD_ACTION != VMD_ACTION_NONE)
void check_mvd_mode_with_menu_sensitivity(UINT8 val)
{
    AHC_BOOL resetDownCount = AHC_FALSE;

    switch (uiGetCurrentState()) {
        #if (VMD_ACTION & VMD_RECORD_VIDEO)
        case UI_VIDEO_MENU_STATE:
        case UI_VIDEO_STATE: // for WiFi APP
        #endif
        #if (VMD_ACTION & VMD_BURST_CAPTURE)
        case UI_CAMERA_MENU_STATE:
        case UI_CAMERA_STATE: // for WiFi APP
        #endif
        //case UI_HDMI_STATE:
        //case UI_TVOUT_STATE:
            switch(val) {
                #if (MENU_GENERAL_MOTION_DTC_LOW_EN)
                case MOTION_DTC_SENSITIVITY_LOW:
                    if ((MVD_LO_MVTH != m_ubMotionMvTh) && (MVD_LO_CNTH != m_ubMotionCntTh))
                        resetDownCount = AHC_TRUE;
                break;
                #endif

                #if (MENU_GENERAL_MOTION_DTC_MID_EN)
                case MOTION_DTC_SENSITIVITY_MID:
                    if ((MVD_MI_MVTH != m_ubMotionMvTh) && (MVD_MI_CNTH != m_ubMotionCntTh))
                        resetDownCount = AHC_TRUE;
                break;
                #endif

                #if (MENU_GENERAL_MOTION_DTC_HIGH_EN)
                case MOTION_DTC_SENSITIVITY_HIGH:
                    if ((MVD_HI_MVTH != m_ubMotionMvTh) && (MVD_HI_CNTH != m_ubMotionCntTh))
                        resetDownCount = AHC_TRUE;
                break;
                #endif

                #if (MENU_GENERAL_MOTION_DTC_OFF_EN)
                case MOTION_DTC_SENSITIVITY_OFF:
                #endif
                default:

                    #if (VR_PREENCODE_EN)
                    m_ubPreEncodeEn = AHC_FALSE;
                    #endif
                    m_ubMotionDtcEn = AHC_FALSE;
                    m_ubInRemindTime = AHC_FALSE;
                    bDisableVideoPreRecord = AHC_TRUE;

                    if (m_ulVMDRemindTime) {
                        m_ulVMDCancel = AHC_TRUE;
                    }
                break;
            }

            if (MOTION_DTC_SENSITIVITY_OFF != val) {
            #if (VR_PREENCODE_EN)
                m_ubPreEncodeEn = AHC_FALSE;
            #endif
                m_ubMotionDtcEn = AHC_TRUE;
            }

            if (AHC_TRUE == resetDownCount) {
                m_ulVMDCancel = AHC_FALSE;
                m_ubInRemindTime = AHC_TRUE;

                #ifdef CFG_REC_CUS_VMD_REMIND_TIME
                m_ulVMDRemindTime = CFG_REC_CUS_VMD_REMIND_TIME;
                #else
                m_ulVMDRemindTime = 10;
                m_ulVMDCloseBacklightTime = 43;
                #endif
            }
        break;

        default:
            // Just only turn-on/off m_ubMotionDtcEn
            m_ubInRemindTime = AHC_FALSE;
            bDisableVideoPreRecord = AHC_TRUE;
            m_ulVMDRemindTime = 0;
            m_ulVMDCloseBacklightTime = 0;

            #if (VR_PREENCODE_EN)
            m_ubPreEncodeEn = AHC_FALSE;
            #endif

            if (MOTION_DTC_SENSITIVITY_OFF == val) {
                m_ubMotionDtcEn = AHC_FALSE;
            }
            else {
                m_ubMotionDtcEn = AHC_TRUE;
            }
        break;
    }
}
#endif

#if 0
void ____LDWS_Detect_Function_____(){ruturn;} //dummy
#endif

AHC_BOOL AHC_EnableADAS(AHC_BOOL bEn)
{
#if (SUPPORT_ADAS)
    MMP_BOOL bVideoPreview = MMP_FALSE, bDSCPreview = MMP_FALSE;
    MMP_ERR sRet = MMP_ERR_NONE;
    
    sRet = MMPS_3GPRECD_GetPreviewPipeStatus(gsAhcPrmSensor, &bVideoPreview);
    if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;}

    sRet = MMPS_DSC_GetPreviewPipeStatus(gsAhcPrmSensor, &bDSCPreview);
    if (sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;}

    if (bEn)
    {
        if (bVideoPreview) {
            //NOP
        }
        else if (bDSCPreview) {
            AHC_DBG_ERR(1, FG_RED("Not support DSC ADAS now!\r\n"));
            return AHC_FALSE;
        }
        else{
           AHC_DBG_ERR(1, FG_RED("[ERR] Preview not stable yet during ADAS Enable\r\n"));
           return AHC_FALSE;
        }
    }
    
    sRet = MMPS_Sensor_EnableADAS(bEn);
    if(sRet != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,sRet); return AHC_FALSE;}    
#endif

    return AHC_TRUE;
}

AHC_BOOL AHC_IsADASEnabled(void)
{
#if (SUPPORT_ADAS)
    return (AHC_BOOL)MMPS_Sensor_IsADASEnable();
#endif
    return AHC_FALSE;
}

#if 0
void ____MenuSet_Function_________(){ruturn;} //dummy
#endif

AHC_BOOL Menu_SetMotionDtcSensitivity(UINT8 val)
{
#if (MOTION_DETECTION_EN)

    #if defined(CFG_MVD_MODE_LINK_WITH_MENU_SENSITIVITY) && (VMD_ACTION != VMD_ACTION_NONE)
    extern AHC_BOOL m_ubInRemindTime;
    check_mvd_mode_with_menu_sensitivity(val);
    if(m_ubInRemindTime)
        uiSetParkingModeEnable(AHC_TRUE);
    else
        uiSetParkingModeEnable(AHC_FALSE);
    #endif

    switch(val)
    {
    case MOTION_DTC_SENSITIVITY_LOW:
        m_ubMotionMvTh  = MVD_LO_MVTH;
        m_ubMotionCntTh = MVD_LO_CNTH;
        break;
    case MOTION_DTC_SENSITIVITY_MID:
        m_ubMotionMvTh  = MVD_MI_MVTH;
        m_ubMotionCntTh = MVD_MI_CNTH;
        break;
    case MOTION_DTC_SENSITIVITY_HIGH:
        m_ubMotionMvTh  = MVD_HI_MVTH;
        m_ubMotionCntTh = MVD_HI_CNTH;
        break;
    default:
    //case MOTION_DTC_SENSITIVITY_OFF:
        m_ubMotionMvTh  = 0xFF;
        m_ubMotionCntTh = 0xFF;
        break;
    }
#endif

    return AHC_TRUE;
}
