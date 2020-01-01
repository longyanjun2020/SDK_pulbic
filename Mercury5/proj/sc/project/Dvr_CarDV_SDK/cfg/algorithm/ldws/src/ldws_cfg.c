//------------------------------------------------------------------------------
//
//  File        : lwds_cfg.c
//  Description : Source file of LDWS configuration
//  Author      : SunnyChang
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "Customer_config.h"
#include "ldws.h"
#include "ldws_cfg.h"
#include "mmps_fs.h"
#include "ahc_utility.h"



//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

#if (SUPPORT_ADAS)
/*
 * Resolution of source image
 */
LDWS_RESOL      gstLdwsResol = {
    LDWS_WIDTH, // width
    LDWS_HEIGHT // height
};

/*
 * Gap of frames to do LDWS
 */
unsigned char   gubLdwsFrameGap = LDWS_FRAME_GAP;

static MMP_BOOL             ldwsSetupChanged = MMP_FALSE;

/*
 * default setting
 */
static const LdwsSetupPosi  defLdwsSetupPosi = LDWS_SETUP_CENTER;

static const ldws_tuning_params   default_ldwsTuningParms = {
    LDWS_WIDTH,         //laneCalibrationImageWidth
    LDWS_HEIGHT,        //laneCalibrationImageHeight
    LDWS_WIDTH / 2,     //laneCalibrationUpPointX
    LDWS_HEIGHT / 2,    //laneCalibrationUpPointY
    LDWS_WIDTH / 4,     //laneCalibrationLeftPointX
    LDWS_HEIGHT - 1,    //laneCalibrationLeftPointY
    LDWS_WIDTH * 3 / 4, //laneCalibrationRightPointX
    LDWS_HEIGHT - 1,    //laneCalibrationRightPointY
    768,                //departureHighThr1
    1024,               //departureHighThr2
    333,                //departureMiddleThr1
    384,                //departureMiddleThr2
    230,                //departureLowThr1
    282,                //departureLowThr2
    32,                 //minLaneRatioX256
    768,                //maxLaneRatioX256
    10                  //alarmShowCnt

};

/*
 * working setting
 */
ldws_tuning_params ldwsTuningParms =  {
    LDWS_WIDTH,   //laneCalibrationImageWidth
    LDWS_HEIGHT,   //laneCalibrationImageHeight
    201,   //laneCalibrationUpPointX
    144,   //laneCalibrationUpPointY
    142,   //laneCalibrationLeftPointX
    193,   //laneCalibrationLeftPointY
    271,   //laneCalibrationRightPointX
    193,   //laneCalibrationRightPointY
    768,   //departureHighThr1
    1024,   //departureHighThr2
    307,   //departureMiddleThr1
    332,   //departureMiddleThr2
    230,   //departureLowThr1
    282,   //departureLowThr2
    204,   //minLaneRatioX256
    512,   //maxLaneRatioX256
     10    //alarmShowCnt
};

static fcws_tuning_params UserfcwsTuningParms =  {
    120,
    134,    //CalibrationStarY
    195    //CalibrationEndY
};
#endif

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//extern MMP_ERR MMPS_3GPRECD_GetPreviewRes(MMP_UBYTE ubSnrSel, MMP_ULONG *width, MMP_ULONG *height);

#if (SUPPORT_ADAS)

/* log functions for MD library, please porting for it */
void LDWS_printk(char *fmt, ...)
{
    // do nothing
    //printc(fmt);
}

void LDWS_CalibrationParamReset(void)
{
    ldwsTuningParms = default_ldwsTuningParms;
    ldwsSetupPosi = defLdwsSetupPosi;
}

void LDWS_CalibrationParam_Convert(ldws_tuning_params menu_ldws_tuning_params)
{
    MMP_ULONG width, height;
    MMP_ULONG offsetX, offsetY;

    //_AHC_PRINT_FUNC_ENTRY_();

    printc("OSD: %dx%d, %dx%d, %dx%d, %dx%d\r\n", menu_ldws_tuning_params.laneCalibrationImageWidth, menu_ldws_tuning_params.laneCalibrationImageHeight,
                                                  menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointY,
                                                  menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointY,
                                                  menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointY);

    //MMPS_3GPRECD_GetPreviewRes(gsAhcPrmSensor, &width, &height);

    offsetX = (menu_ldws_tuning_params.laneCalibrationImageWidth - width) / 2;
    offsetY = (menu_ldws_tuning_params.laneCalibrationImageHeight - height) / 2;
    printc("Preview Size = %dx%d\r\n", width, height);

    // Convert to Preview Buffer
    menu_ldws_tuning_params.laneCalibrationImageWidth = width;
    menu_ldws_tuning_params.laneCalibrationImageHeight = height;
    menu_ldws_tuning_params.laneCalibrationUpPointX *= OSD_DISPLAY_SCALE_LCD;//-= offsetX;
    menu_ldws_tuning_params.laneCalibrationUpPointY *= OSD_DISPLAY_SCALE_LCD;//-= offsetY;
    menu_ldws_tuning_params.laneCalibrationLeftPointX *= OSD_DISPLAY_SCALE_LCD;//-= offsetX;
    menu_ldws_tuning_params.laneCalibrationLeftPointY *= OSD_DISPLAY_SCALE_LCD;//-= offsetY;
    menu_ldws_tuning_params.laneCalibrationRightPointX *= OSD_DISPLAY_SCALE_LCD;//-= offsetX;
    menu_ldws_tuning_params.laneCalibrationRightPointY *= OSD_DISPLAY_SCALE_LCD;//-= offsetY;


    printc("PIP: %dx%d, %dx%d, %dx%d, %dx%d\r\n", menu_ldws_tuning_params.laneCalibrationImageWidth, menu_ldws_tuning_params.laneCalibrationImageHeight,
                                                  menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointY,
                                                  menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointY,
                                                  menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointY);

    // Convert to LDWS working Buffer
    ldwsTuningParms.laneCalibrationImageWidth = LDWS_WIDTH;
    ldwsTuningParms.laneCalibrationImageHeight = LDWS_HEIGHT;
    ldwsTuningParms.laneCalibrationUpPointX = LDWS_WIDTH * menu_ldws_tuning_params.laneCalibrationUpPointX / menu_ldws_tuning_params.laneCalibrationImageWidth;
    ldwsTuningParms.laneCalibrationUpPointY = LDWS_HEIGHT * menu_ldws_tuning_params.laneCalibrationUpPointY / menu_ldws_tuning_params.laneCalibrationImageHeight;
    ldwsTuningParms.laneCalibrationLeftPointX = LDWS_WIDTH * menu_ldws_tuning_params.laneCalibrationLeftPointX / menu_ldws_tuning_params.laneCalibrationImageWidth;
    ldwsTuningParms.laneCalibrationLeftPointY = LDWS_HEIGHT * menu_ldws_tuning_params.laneCalibrationLeftPointY / menu_ldws_tuning_params.laneCalibrationImageHeight;
    ldwsTuningParms.laneCalibrationRightPointX = LDWS_WIDTH * menu_ldws_tuning_params.laneCalibrationRightPointX / menu_ldws_tuning_params.laneCalibrationImageWidth;
    ldwsTuningParms.laneCalibrationRightPointY = LDWS_HEIGHT * menu_ldws_tuning_params.laneCalibrationRightPointY / menu_ldws_tuning_params.laneCalibrationImageHeight;
    printc("Calibration: %dx%d, %dx%d, %dx%d, %dx%d\r\n",
                                                   ldwsTuningParms.laneCalibrationImageWidth, ldwsTuningParms.laneCalibrationImageHeight,
                                                   ldwsTuningParms.laneCalibrationUpPointX, ldwsTuningParms.laneCalibrationUpPointY,
                                                   ldwsTuningParms.laneCalibrationLeftPointX, ldwsTuningParms.laneCalibrationLeftPointY,
                                                   ldwsTuningParms.laneCalibrationRightPointX, ldwsTuningParms.laneCalibrationRightPointY);

   if (ldwsTuningParms.laneCalibrationUpPointX <= (ldwsTuningParms.laneCalibrationImageWidth / 3 + LDWS_SETUP_POS_OFFSET))
        ldwsSetupPosi = LDWS_SETUP_RIGHT;
    else if (ldwsTuningParms.laneCalibrationUpPointX >= (ldwsTuningParms.laneCalibrationImageWidth * 2 / 3 - LDWS_SETUP_POS_OFFSET))
        ldwsSetupPosi = LDWS_SETUP_LEFT;
    else
        ldwsSetupPosi = LDWS_SETUP_CENTER;

    printc("LDWS setup position = %d\r\n", ldwsSetupPosi);

    ldwsSetupChanged = MMP_TRUE;
}

MMP_ERR LDWS_CalibrationParam_Backup(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulActualSize;

    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_BACKUP_FILENAME, strlen(LDWS_CALIBRATION_BACKUP_FILENAME), "wb", strlen("wb"),  &ulFileId );

    if (MMP_ERR_NONE == err) {
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&ldwsTuningParms, sizeof(ldws_tuning_params), &ulActualSize);
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulActualSize);
        err |= MMPS_FS_FileClose(ulFileId);

        if (MMP_ERR_NONE != err)
        {
            printc(FG_RED("%s: MMPS_FS_FileWrite %s error")"\r\n", __func__, LDWS_CALIBRATION_BACKUP_FILENAME);
        }
    }
    else
    {
        printc(FG_RED("%s: MMPS_FS_FileOpen %s error")"\r\n", __func__, LDWS_CALIBRATION_BACKUP_FILENAME);
    }

    return err;
}

MMP_ERR LDWS_CalibrationParam_Default(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulTurningParamlSize, ulSetupPosSize;
    ldws_tuning_params templdwsTuningParms;
    LdwsSetupPosi temp_ldwsSetupPosi;

    LDWS_CalibrationParamReset();

    // Check default table is existed
    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_DEFAULT_FILENAME, strlen(LDWS_CALIBRATION_DEFAULT_FILENAME), "rb", strlen("rb"), &ulFileId);

    if (MMP_ERR_NONE == err) {
        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&templdwsTuningParms, sizeof(ldws_tuning_params), &ulTurningParamlSize);
        err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&temp_ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulSetupPosSize);
        MMPS_FS_FileClose(ulFileId);

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(ldws_tuning_params)) && (ulSetupPosSize == sizeof(LdwsSetupPosi))) {
            memcpy(&ldwsTuningParms, &templdwsTuningParms, sizeof(ldws_tuning_params));
            ldwsSetupPosi = temp_ldwsSetupPosi;
        }
        else {
            if (MMP_ERR_NONE == err)
                err = MMP_FS_ERR_INVALID_SIZE;

            printc(FG_RED("Read %s Error !!!")"\r\n", LDWS_CALIBRATION_DEFAULT_FILENAME);
        }
    }

    if (MMP_ERR_NONE != err) {
        MMP_ULONG ulActualSize;

        err = MMPS_FS_FileOpen(LDWS_CALIBRATION_DEFAULT_FILENAME, strlen(LDWS_CALIBRATION_DEFAULT_FILENAME), "wb", strlen("wb"),  &ulFileId );

        if (MMP_ERR_NONE == err) {
            err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *) &default_ldwsTuningParms, sizeof(ldws_tuning_params), &ulActualSize);
            err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *) &defLdwsSetupPosi, sizeof(LdwsSetupPosi), &ulActualSize);
            err |= MMPS_FS_FileClose(ulFileId);

            if (MMP_ERR_NONE != err)
            {
                printc(FG_RED("%s: MMPS_FS_FileWrite %s error")"\r\n", __func__, LDWS_CALIBRATION_DEFAULT_FILENAME);
            }
        }
    }

    return err;
}

MMP_ERR LDWS_CalibrationParam_UserUpdate(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulTurningParamlSize, ulSetupPosSize;
    ldws_tuning_params templdwsTuningParms;
    LdwsSetupPosi temp_ldwsSetupPosi;

    // Check SD update file is existed
    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_UPDATE_FILENAME, strlen(LDWS_CALIBRATION_UPDATE_FILENAME), "rb", strlen("rb"), &ulFileId);

    if (MMP_ERR_NONE == err) {
        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&templdwsTuningParms, sizeof(ldws_tuning_params), &ulTurningParamlSize);
        err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&temp_ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulSetupPosSize);
        MMPS_FS_FileClose(ulFileId);
        MMPS_FS_FileDirRename(LDWS_CALIBRATION_UPDATE_FILENAME, strlen(LDWS_CALIBRATION_UPDATE_FILENAME),
                              LDWS_CALIBRATION_UPDATE_FILENAME2, strlen(LDWS_CALIBRATION_UPDATE_FILENAME2));

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(ldws_tuning_params)) && (ulSetupPosSize == sizeof(LdwsSetupPosi))) {
            memcpy(&ldwsTuningParms, &templdwsTuningParms, sizeof(ldws_tuning_params));
            ldwsSetupPosi = temp_ldwsSetupPosi;
            LDWS_CalibrationParam_Save();
        }
        else {
            if (MMP_ERR_NONE == err)
                err = MMP_FS_ERR_INVALID_SIZE;
        }
    }

    return err;
}

MMP_ERR LDWS_CalibrationParam_Save(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulActualSize;

    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_FILENAME, strlen(LDWS_CALIBRATION_FILENAME), "wb", strlen("wb"),  &ulFileId );

    if (MMP_ERR_NONE == err) {
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&ldwsTuningParms, sizeof(ldws_tuning_params), &ulActualSize);
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulActualSize);
        err |= MMPS_FS_FileClose(ulFileId);

        if (MMP_ERR_NONE != err)
        {
            printc(FG_RED("%s: MMPS_FS_FileWrite %s error")" %d \r\n", __func__, LDWS_CALIBRATION_FILENAME,__LINE__);
        }
        else
        {
            printc("LDWS_CalibrationParam_Save OK\r\n");
        }
    }
    else
    {
        printc(FG_RED("%s: MMPS_FS_FileOpen %s error")" %d \r\n", __func__, LDWS_CALIBRATION_FILENAME,__LINE__);
    }

    #ifdef BACKUP_LDWS_CALIBRATION_FILE
    LDWS_CalibrationParam_Backup();
    #endif

    return err;
}

extern void MMPS_ADAS_CustomerCalibration(MMP_ULONG CablitionStarY,MMP_ULONG CablitionEndY);
extern void MMPS_ADAS_CustomerCameraHeight(MMP_ULONG CameraHeight);
extern void MMPS_ADAS_CustomerWarningMode(MMP_ULONG WarningMode);

MMP_ERR LDWS_CalibrationParam_Read(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;

    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_FILENAME, strlen(LDWS_CALIBRATION_FILENAME), "rb", strlen("rb"), &ulFileId);

    if (MMP_ERR_NONE == err) {
        MMP_ULONG ulTurningParamlSize, ulSetupPosSize;
        ldws_tuning_params templdwsTuningParms;
        LdwsSetupPosi temp_ldwsSetupPosi;

        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&templdwsTuningParms, sizeof(ldws_tuning_params), &ulTurningParamlSize);
        err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&temp_ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulSetupPosSize);
        MMPS_FS_FileClose(ulFileId);

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(ldws_tuning_params)) && (ulSetupPosSize == sizeof(LdwsSetupPosi))) {
            ldwsTuningParms.laneCalibrationImageWidth = templdwsTuningParms.laneCalibrationImageWidth;
            ldwsTuningParms.laneCalibrationImageHeight = templdwsTuningParms.laneCalibrationImageHeight;
            ldwsTuningParms.laneCalibrationUpPointX = templdwsTuningParms.laneCalibrationUpPointX;
            ldwsTuningParms.laneCalibrationUpPointY = templdwsTuningParms.laneCalibrationUpPointY;
            ldwsTuningParms.laneCalibrationLeftPointX = templdwsTuningParms.laneCalibrationLeftPointX;
            ldwsTuningParms.laneCalibrationLeftPointY = templdwsTuningParms.laneCalibrationLeftPointY;
            ldwsTuningParms.laneCalibrationRightPointX = templdwsTuningParms.laneCalibrationRightPointX;
            ldwsTuningParms.laneCalibrationRightPointY = templdwsTuningParms.laneCalibrationRightPointY;

            ldwsSetupPosi = temp_ldwsSetupPosi;
        }
        else {
            if (MMP_ERR_NONE == err)
                err = MMP_FS_ERR_INVALID_SIZE;

            printc(FG_RED("Read %s Error !!!")"%d \r\n", LDWS_CALIBRATION_FILENAME,__LINE__);
        }
    }
    else
    {
        printc(FG_RED("Open %s Error !!!")"%d \r\n", LDWS_CALIBRATION_FILENAME,__LINE__);
    }

    if (MMP_ERR_NONE != err) {
        printc("====Using LDWS Default Value====\r\n");
        printc("Source %s\r\n",LDWS_CALIBRATION_DEFAULT_FILENAME);
        LDWS_CalibrationParam_Default();
        LDWS_CalibrationParam_Save();
    }
    err = MMPS_FS_FileOpen(FCWS_CALIBRATION_FILENAME, strlen(FCWS_CALIBRATION_FILENAME), "rb", strlen("rb"), &ulFileId);

    if (MMP_ERR_NONE == err) {
        MMP_ULONG ulTurningParamlSize;
        fcws_tuning_params tempfcwsTuningParms;

        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&tempfcwsTuningParms, sizeof(fcws_tuning_params), &ulTurningParamlSize);
        MMPS_FS_FileClose(ulFileId);
        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(fcws_tuning_params))){
            MMPS_ADAS_CustomerCameraHeight(tempfcwsTuningParms.cardv_height_pos);
            UserfcwsTuningParms.CalibrationStarY = tempfcwsTuningParms.CalibrationStarY;
            UserfcwsTuningParms.CalibrationEndY = tempfcwsTuningParms.CalibrationEndY;
        }
        else{
            printc("Read %s err %s %d\r\n",FCWS_CALIBRATION_FILENAME,__func__,__LINE__);
        }
        printc("Camer Height = %d\r\n",tempfcwsTuningParms.cardv_height_pos);
    }
    else{
        MMP_ULONG   ulActualSize;
        printc("====Using FCWS Default Value====\r\n");
        err = MMPS_FS_FileOpen(FCWS_CALIBRATION_FILENAME, strlen(FCWS_CALIBRATION_FILENAME), "wb", strlen("wb"),  &ulFileId );

        if (MMP_ERR_NONE == err){
            UserfcwsTuningParms.CalibrationStarY = ldwsTuningParms.laneCalibrationUpPointY ;
            UserfcwsTuningParms.CalibrationEndY = ldwsTuningParms.laneCalibrationLeftPointY;
            err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&UserfcwsTuningParms, sizeof(fcws_tuning_params), &ulActualSize);
            MMPS_FS_FileClose(ulFileId);
        }
        else{
            printc("Creat file %s  err %s %d\r\n",FCWS_CALIBRATION_FILENAME,__func__,__LINE__);
        }
    }
    //if FCWS_Calibration.bin StartY, EndY are not ADAS Image coordinate point, it should be converted.
    UserfcwsTuningParms.CalibrationStarY = UserfcwsTuningParms.CalibrationStarY * LDWS_HEIGHT / ldwsTuningParms.laneCalibrationImageHeight;
    UserfcwsTuningParms.CalibrationEndY  = UserfcwsTuningParms.CalibrationEndY  * LDWS_HEIGHT / ldwsTuningParms.laneCalibrationImageHeight;
    MMPS_ADAS_CustomerCalibration(UserfcwsTuningParms.CalibrationStarY,UserfcwsTuningParms.CalibrationEndY);
    MMPS_ADAS_CustomerWarningMode(ADAS_WARNING_MODE_WAIT);
    #if 0//(ADAS_OUTPUT_LOG == 1)
    printc("\r\n====ADAS Parameter Read %s====\r\n");
    printc("LDWS Source      : %s\r\n",LDWS_CALIBRATION_FILENAME);
    printc("FCWS Source      : %s\r\n",FCWS_CALIBRATION_FILENAME);
    printc("Image Size       : %dx%d\r\n", ldwsTuningParms.laneCalibrationImageWidth, ldwsTuningParms.laneCalibrationImageHeight);
    printc("Up Pos           : %dx%d\r\n", ldwsTuningParms.laneCalibrationUpPointX, ldwsTuningParms.laneCalibrationUpPointY);
    printc("Left Pos         : %dx%d\r\n", ldwsTuningParms.laneCalibrationLeftPointX, ldwsTuningParms.laneCalibrationLeftPointY);
    printc("Right Pos        : %dx%d\r\n", ldwsTuningParms.laneCalibrationRightPointX, ldwsTuningParms.laneCalibrationRightPointY);
    printc("CalibrationStarY : %d\r\n",UserfcwsTuningParms.CalibrationStarY);
    printc("CalibrationEndY  : %d\r\n",UserfcwsTuningParms.CalibrationEndY);
    printc("CameraHeight     : %d \r\n",UserfcwsTuningParms.cardv_height_pos);
    printc("Setup Pos        : %d\r\n\r\n", ldwsSetupPosi);
    printc("====End of ADAS Parameter Read ====\r\n");
    #endif
    return err;
}

MMP_BOOL LDWS_SettingChanged(void)
{
    MMP_BOOL changed = ldwsSetupChanged;
    ldwsSetupChanged = MMP_FALSE;

    return changed;
}

void LDWS_SetChanged(MMP_BOOL changed)
{
    ldwsSetupChanged = changed;
}

#endif
