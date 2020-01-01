
/*===========================================================================
 * Include file
 *===========================================================================*/
#include "Customer_config.h"

#if (MENU_GENERAL_LDWS_CALIBRATION_EN)

#include "lib_retina.h"
#include "ahc_common.h"
#include "ahc_display.h"
#include "ahc_general.h"
#include "ahc_utility.h"
#include "ahc_gui.h"
#include "ahc_macro.h"
#include "ahc_menu.h"
#include "ahc_parameter.h"
#include "mmps_fs.h"
#include "MenuDrawCommon.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "MenuStateGeneralSettingsMenu.h"
#include "MenuStateMenu.h"
#include "ShowOSDFunc.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "OSDStrings.h"
#include "IconDefine.h"
#include "ldws.h"
#include "ldws_cfg.h"
#include "lcd_common.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "mmps_adas.h"
enum USERLDWSTATUS
{
    USER_LDWS_CALIB_INIT    = 0,
    USER_LDWS_CALIB_UP_Y,
    USER_LDWS_CALIB_DOWN_Y,
#if MENU_GENERAL_FCWS_CALIBRATION_EN
    USER_FCWS_CALIB_POS,
#endif
    USER_LDWS_CALIB_EXIT
};

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0) // temp
#define OSD_WIDTH(X)    (m_OSD[X]->width)
#define OSD_HEIGHT(X)   (m_OSD[X]->height)
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define OSD_WIDTH(X)    (AHC_GET_ATTR_OSD_W(X))
#define OSD_HEIGHT(X)   (AHC_GET_ATTR_OSD_H(X))
#endif
#define FCWS_CALIBRATION_SHIFT_OFFSET  (1)
static unsigned char User_Ldws_Status = USER_LDWS_CALIB_INIT;

#define MENU_AUTO_LDWS_CALIBRATION_EN           1

/*===========================================================================
 * Local function
 *===========================================================================*/
AHC_BOOL MenuItemLdwsCalibrationSettings(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global variable
 *===========================================================================*/
extern AHC_OSD_INSTANCE         *m_OSD[];
extern MMP_BOOL                 m_bCalibrated;
extern ldws_tuning_params       ldwsTuningParms;
extern AHC_BOOL                 gbAhcDbgBrk;

static GUI_POINT    m_TriangleL[] = { {  0, 0}, {10,  -7}, {10,  7} };
static GUI_POINT    m_TriangleR[] = { {  0, 0}, {-10, -7}, {-10, 7} };

ldws_tuning_params UserldwsTuningParms =  {
    432,   //laneCalibrationImageWidth
    240,   //laneCalibrationImageHeight
    202,   //laneCalibrationUpPointX
    134,   //laneCalibrationUpPointY
    124,   //laneCalibrationLeftPointX
    195,   //laneCalibrationLeftPointY
    293,   //laneCalibrationRightPointX
    195,   //laneCalibrationRightPointY
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
LdwsSetupPosi           UserldwsSetupPosi = LDWS_SETUP_CENTER;

fcws_tuning_params ADASfcwsTuningParms =  {
    120,
    134,    //CalibrationStarY
    195    //CalibrationEndY
};
fcws_tuning_params OSDfcwsTuningParms;
#if 0
void ________LDWS_Calibration_Function_______(){ruturn;}
#endif
void User_LDWS_CalibrationParam_Convert(void)
{
    MMP_ULONG ulOffsetX = 0, ulOffsetY = 0;               //offset of OSD start and preview start(in OSD)
    MMP_ULONG ulOSD_W   = 0, ulOSD_H   = 0;               //OSD_W buffer width calculate by DUPLICATE
    MMP_ULONG ulPreview_width = 0, ulPreview_height = 0;  //Preview_width in OSD buffer calculate by DUPLICATE
    MMP_USHORT usPreviewMode;
    MMPS_3GPRECD_PRESET_CFG *pVideoConfig = MMPS_3GPRECD_GetPresetCfg();
    //Calculate offset X,Y
    ulOSD_W = STRETCH_W(ORIGINAL_OSD_W);
    ulOSD_H = STRETCH_H(ORIGINAL_OSD_H);
    //Get preview Width Height in OSD
    usPreviewMode = VIDRECD_FULL_PREVIEW_MODE;//MMPS_3GPRECD_GetPreviewDispMode();
    if(usPreviewMode == VIDRECD_FULL_PREVIEW_MODE || usPreviewMode == VIDRECD_NORMAL_PREVIEW_MODE)
    {
    #ifdef VERTICAL_PANEL  //TBD, this conversion should be set by MMPC_3gpRecd_InitConfig in ait_config.c
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufH[VIDRECD_FULL_PREVIEW_MODE];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufW[VIDRECD_FULL_PREVIEW_MODE];
    #else
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufW[VIDRECD_FULL_PREVIEW_MODE];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufH[VIDRECD_FULL_PREVIEW_MODE];
    #endif
        //Convert to OSD buffer Width Height
        if(OSD_DISPLAY_SCALE_LCD)
        {
            ulPreview_width  = ulPreview_width  / OSD_DISPLAY_SCALE_LCD;
            ulPreview_height = ulPreview_height / OSD_DISPLAY_SCALE_LCD;
        }
    }
    else
    {
        MMP_ULONG ulFullWidth;
        MMP_ULONG ulFullHeight;
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufW[usPreviewMode];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufH[usPreviewMode];
        switch (usPreviewMode)
        {
            case VIDRECD_NTSC_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->ntsctv.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->ntsctv.usDisplayHeight;
                break;
            case VIDRECD_PAL_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->paltv.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->paltv.usDisplayHeight;
                break;
            case VIDRECD_HDMI_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->hdmi.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->hdmi.usDisplayHeight;
                break;
            case VIDRECD_CCIR_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->ccir.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->ccir.usDisplayHeight;
                break;
            default:
                printc("Warning!!! switch preview mode error!! %s\r\n",__func__);
                break;
        }
        ulPreview_width = (ulPreview_width  * ulOSD_W) / ulFullWidth ;
        ulPreview_height= (ulPreview_height * ulOSD_H) / ulFullHeight;
    }
    //Calculate offset by OSD_W and ulPreview_width
    //assume that preview align center of OSD, in other case should change this function
    if(ulOSD_W > ulPreview_width)
    {
        ulOffsetX = (ulOSD_W - ulPreview_width) / 2;
    }
    if(ulOSD_H > ulPreview_height)
    {
        ulOffsetY = (ulOSD_H - ulPreview_height) / 2;
    }

    //OSD coordinate to Preview Image of OSD
    ADASfcwsTuningParms.CalibrationStarY = OSDfcwsTuningParms.CalibrationStarY - ulOffsetY; //ADAS
    ADASfcwsTuningParms.CalibrationEndY  = OSDfcwsTuningParms.CalibrationEndY  - ulOffsetY; //ADAS
    MMPS_ADAS_CustomerCalibration(LDWS_HEIGHT * ADASfcwsTuningParms.CalibrationStarY / ulPreview_height,
        LDWS_HEIGHT * ADASfcwsTuningParms.CalibrationEndY / ulPreview_height);
    //tranform to ADAS Image X,Y //ADAS
    ADASfcwsTuningParms.CalibrationStarY = UserldwsTuningParms.laneCalibrationImageHeight * ADASfcwsTuningParms.CalibrationStarY / ulPreview_height;
    ADASfcwsTuningParms.CalibrationEndY = UserldwsTuningParms.laneCalibrationImageHeight * ADASfcwsTuningParms.CalibrationEndY / ulPreview_height;
    MMPS_ADAS_CustomeLdwsCalibratedParam(UserldwsTuningParms);
    //change calibration status
    m_bCalibrated = AHC_TRUE;
    //ADAS
    //set calibration value startY,endY to vars for ADAS lib in mmpf_adas_ctl.c
    //set calibration value height position to vars for ADAS lib in mmpf_adas_ctl.c
#if MENU_GENERAL_FCWS_CALIBRATION_EN
    //ADAS
    MMPS_ADAS_CustomerCameraHeight(ADASfcwsTuningParms.cardv_height_pos);
#endif
    LDWS_SetChanged(AHC_TRUE);
#if(ADAS_OUTPUT_LOG)
    printc("\r\n====Convert Calibration Result and Parameters====\r\n");
    printc("Before Convert StartY : %d\r\n",OSDfcwsTuningParms.CalibrationStarY);
    printc("Before Convert EndY   : %d\r\n",OSDfcwsTuningParms.CalibrationEndY);
    printc("ulOSD_W               : %d\r\n",ulOSD_W);
    printc("ulOSD_H               : %d\r\n",ulOSD_H);
    printc("ulPreview_width       : %d\r\n",ulPreview_width);
    printc("ulPreview_height      : %d\r\n",ulPreview_height);
    printc("ulOffsetX             : %d\r\n",ulOffsetX);
    printc("ulOffsetY             : %d\r\n",ulOffsetY);
    printc("After Convert StartY  : %d\r\n",ADASfcwsTuningParms.CalibrationStarY);
    printc("After Convert EndY    : %d\r\n",ADASfcwsTuningParms.CalibrationEndY);
    printc("====End of Calibration Result and Parameters====\r\n");
#endif
}

void User_LDWS_CalibrationParam_Inverse(void)
{
    MMP_ULONG ulOffsetX = 0, ulOffsetY = 0;               //offset of OSD start and preview start(in OSD)
    MMP_ULONG ulOSD_W   = 0, ulOSD_H   = 0;               //OSD_W buffer width calculate by DUPLICATE
    MMP_ULONG ulPreview_width = 0, ulPreview_height = 0;  //Preview_width in OSD buffer calculate by DUPLICATE
    MMP_USHORT usPreviewMode;
    MMPS_3GPRECD_PRESET_CFG *pVideoConfig = MMPS_3GPRECD_GetPresetCfg();
    //Calculate offset X,Y
    ulOSD_W = STRETCH_W(ORIGINAL_OSD_W);
    ulOSD_H = STRETCH_H(ORIGINAL_OSD_H);
    usPreviewMode = VIDRECD_FULL_PREVIEW_MODE;//MMPS_3GPRECD_GetPreviewDispMode();
    //Get preview Width Height in OSD
    if(usPreviewMode == VIDRECD_FULL_PREVIEW_MODE || usPreviewMode == VIDRECD_NORMAL_PREVIEW_MODE)
    {
    #ifdef VERTICAL_PANEL  //TBD, this conversion should be set by MMPC_3gpRecd_InitConfig in ait_config.c
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufH[VIDRECD_FULL_PREVIEW_MODE];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufW[VIDRECD_FULL_PREVIEW_MODE];
    #else
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufW[VIDRECD_FULL_PREVIEW_MODE];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufH[VIDRECD_FULL_PREVIEW_MODE];
    #endif
        //Convert to OSD buffer Width Height
        if(OSD_DISPLAY_SCALE_LCD)
        {
            ulPreview_width  = ulPreview_width  / OSD_DISPLAY_SCALE_LCD;
            ulPreview_height = ulPreview_height / OSD_DISPLAY_SCALE_LCD;
        }
    }
    else
    {
        MMP_ULONG ulFullWidth;
        MMP_ULONG ulFullHeight;
        //ulPreview_width  = pVideoConfig->previewdata->usVidPreviewBufW[usPreviewMode];
        //ulPreview_height = pVideoConfig->previewdata->usVidPreviewBufH[usPreviewMode];
        switch (usPreviewMode)
        {
            case VIDRECD_NTSC_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->ntsctv.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->ntsctv.usDisplayHeight;
                break;
            case VIDRECD_PAL_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->paltv.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->paltv.usDisplayHeight;
                break;
            case VIDRECD_HDMI_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->hdmi.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->hdmi.usDisplayHeight;
                break;
            case VIDRECD_CCIR_PREVIEW_MODE:
                ulFullWidth  = MMPS_Display_GetConfig()->ccir.usDisplayWidth;
                ulFullHeight = MMPS_Display_GetConfig()->ccir.usDisplayHeight;
                break;
            default:
                printc("Warning!!! switch preview mode error!! %s\r\n",__func__);
                break;
        }
        ulPreview_width = (ulPreview_width  * ulOSD_W) / ulFullWidth ;
        ulPreview_height= (ulPreview_height * ulOSD_H) / ulFullHeight;
    }
    //Calculate offset by OSD_W and ulPreview_width
    //assume that preview align center of OSD, in other case should change this function
    if(ulOSD_W > ulPreview_width)
    {
        ulOffsetX = (ulOSD_W - ulPreview_width) / 2;
    }
    if(ulOSD_H > ulPreview_height)
    {
        ulOffsetY = (ulOSD_H - ulPreview_height) / 2;
    }
    //tranform to Preview Image x,y of OSD from ADAS Image X,Y
    //OSD
    OSDfcwsTuningParms.CalibrationStarY = ADASfcwsTuningParms.CalibrationStarY * ulPreview_height / UserldwsTuningParms.laneCalibrationImageHeight;
    OSDfcwsTuningParms.CalibrationEndY  = ADASfcwsTuningParms.CalibrationEndY  * ulPreview_height / UserldwsTuningParms.laneCalibrationImageHeight;
    //Preview Image of OSD to OSD coordinate
    //OSD
    OSDfcwsTuningParms.CalibrationStarY += ulOffsetY;
    OSDfcwsTuningParms.CalibrationEndY  += ulOffsetY;
#if(ADAS_OUTPUT_LOG)
    printc("====Inverse Calibration Result and Parameters====\r\n");
    printc("Before Inverse StartY : %d\r\n",ADASfcwsTuningParms.CalibrationStarY);
    printc("Before Inverse EndY   : %d\r\n",ADASfcwsTuningParms.CalibrationEndY);
    printc("ulOSD_W               : %d\r\n",ulOSD_W);
    printc("ulOSD_H               : %d\r\n",ulOSD_H);
    printc("ulPreview_width       : %d\r\n",ulPreview_width);
    printc("ulPreview_height      : %d\r\n",ulPreview_height);
    printc("ulOffsetX             : %d\r\n",ulOffsetX);
    printc("ulOffsetY             : %d\r\n",ulOffsetY);
    printc("After Inverse StartY  : %d\r\n",OSDfcwsTuningParms.CalibrationStarY);
    printc("After Inverse EndY    : %d\r\n",OSDfcwsTuningParms.CalibrationEndY);
    printc("====End of Calibration Result and Parameters====\r\n");
#endif
}

void Menudraw_UserLdwsCalibrationLines(UINT16 bID0)
{
    AHC_OSDSetColor(bID0, OSD_COLOR_RED);
    AHC_OSDSetPenSize(bID0, 5);

    AHC_OSDDrawLine(bID0, 0, OSD_WIDTH(bID0), OSDfcwsTuningParms.CalibrationStarY, OSDfcwsTuningParms.CalibrationStarY);

    AHC_OSDSetColor(bID0, OSD_COLOR_GREEN);
    AHC_OSDDrawLine(bID0, OSD_WIDTH(bID0)/2, OSD_WIDTH(bID0)/2, OSDfcwsTuningParms.CalibrationStarY, OSDfcwsTuningParms.CalibrationEndY);
    AHC_OSDDrawLine(bID0, 100, OSD_WIDTH(bID0)-100, OSDfcwsTuningParms.CalibrationEndY, OSDfcwsTuningParms.CalibrationEndY);
}

void Menudraw_AutoLdwsCalibrationLines(UINT16 bID0)
{
    AHC_OSDSetColor(bID0, OSD_COLOR_YELLOW);
    AHC_OSDSetPenSize(bID0, 5);

    AHC_OSDDrawLine(bID0, UserldwsTuningParms.laneCalibrationLeftPointX, UserldwsTuningParms.laneCalibrationRightPointX, UserldwsTuningParms.laneCalibrationUpPointY, UserldwsTuningParms.laneCalibrationUpPointY);
    AHC_OSDDrawLine(bID0, UserldwsTuningParms.laneCalibrationUpPointX, UserldwsTuningParms.laneCalibrationLeftPointX, UserldwsTuningParms.laneCalibrationUpPointY, UserldwsTuningParms.laneCalibrationLeftPointY);
    AHC_OSDDrawLine(bID0, UserldwsTuningParms.laneCalibrationUpPointX, UserldwsTuningParms.laneCalibrationRightPointX, UserldwsTuningParms.laneCalibrationUpPointY, UserldwsTuningParms.laneCalibrationRightPointY);
}

void Menudraw_UserLdwsCalibrationInit(UINT16 bID0)
{
    MMP_ULONG ulFileId;
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG ulTurningParamlSize,ulSetupPosSize;
    ldws_tuning_params templdwsTuningParms;
    LdwsSetupPosi temp_ldwsSetupPosi;
    fcws_tuning_params tempfcwsTuningParms;

    if (MMP_ERR_NONE == MMPS_FS_FileOpen(LDWS_CALIBRATION_FILENAME, strlen(LDWS_CALIBRATION_FILENAME), "rb", strlen("rb"), &ulFileId))
    {
        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *) &templdwsTuningParms, sizeof(ldws_tuning_params), &ulTurningParamlSize);
        err |= MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *)&temp_ldwsSetupPosi, sizeof(LdwsSetupPosi), &ulSetupPosSize);
        MMPS_FS_FileClose(ulFileId);

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(ldws_tuning_params)))
        {
            memcpy(&UserldwsTuningParms, &templdwsTuningParms, sizeof(ldws_tuning_params));
            memcpy(&UserldwsSetupPosi, &temp_ldwsSetupPosi, sizeof(LdwsSetupPosi));
        }
    }

    if (MMP_ERR_NONE == MMPS_FS_FileOpen(FCWS_CALIBRATION_FILENAME, strlen(FCWS_CALIBRATION_FILENAME), "rb", strlen("rb"), &ulFileId))
    {
        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *) &tempfcwsTuningParms, sizeof(fcws_tuning_params), &ulTurningParamlSize);
        MMPS_FS_FileClose(ulFileId);

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(fcws_tuning_params)))
        {
            //ADAS
            memcpy(&ADASfcwsTuningParms, &tempfcwsTuningParms, sizeof(fcws_tuning_params));
        }
        else
        {
            //ADAS
            ADASfcwsTuningParms.cardv_height_pos = 120;
        }
    }
    else
    {
        //ADAS
        ADASfcwsTuningParms.cardv_height_pos = 120;
    }

    User_LDWS_CalibrationParam_Inverse();
}

void Menudraw_UserLdwsCalibrationIcon(UINT16 bID0)
{
    AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
    AHC_OSDDrawFillRect(bID0, 0, OSD_HEIGHT(bID0)-30, OSD_WIDTH(bID0), OSD_HEIGHT(bID0));

    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_DARKGRAY2);

    AHC_OSDSetPenSize(bID0, 2);
    AHC_OSDSetFont(bID0, &GUI_Font20B_1);

    AHC_OSDDrawFillPolygon(bID0, m_TriangleL, 3, 3, OSD_HEIGHT(bID0)-30/2);
    AHC_OSDDrawFillPolygon(bID0, m_TriangleR, 3, 26, OSD_HEIGHT(bID0)-30/2);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"Adjust", 28, OSD_HEIGHT(bID0)-30, 108, OSD_HEIGHT(bID0), GUI_TA_LEFT|GUI_TA_VCENTER,  strlen("Adjust"), 0);

    AHC_OSDDrawRect(bID0, 110, OSD_HEIGHT(bID0)-28, 170, OSD_HEIGHT(bID0)-2);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"Menu", 112, OSD_HEIGHT(bID0)-28, 168, OSD_HEIGHT(bID0)-2, GUI_TA_HCENTER|GUI_TA_VCENTER,  strlen("Menu"), 0);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"Exit", 172, OSD_HEIGHT(bID0)-28, 220, OSD_HEIGHT(bID0)-2, GUI_TA_LEFT|GUI_TA_VCENTER,  strlen("Exit"), 0);

    AHC_OSDDrawRect(bID0, 220, OSD_HEIGHT(bID0)-28, 270, OSD_HEIGHT(bID0)-2);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"OK", 222, OSD_HEIGHT(bID0)-28, 268, OSD_HEIGHT(bID0)-2, GUI_TA_HCENTER|GUI_TA_VCENTER,  strlen("OK"), 0);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"Next", 272, OSD_HEIGHT(bID0)-28, OSD_WIDTH(bID0), OSD_HEIGHT(bID0)-2, GUI_TA_LEFT|GUI_TA_VCENTER,  strlen("Next"), 0);
}


#if 0
void ________FCWS_Calibration_Function_______(){ruturn;}
#endif

#if MENU_GENERAL_FCWS_CALIBRATION_EN


void Menudraw_UserFcwsCalibrationInit(UINT16 bID0)
{
    //MMP_ULONG ulFileId;
    //MMP_ERR err = MMP_ERR_NONE;
    //MMP_ULONG ulTurningParamlSize;
    //fcws_tuning_params tempfcwsTuningParms;
/*
    if (MMP_ERR_NONE == MMPS_FS_FileOpen(FCWS_CALIBRATION_FILENAME, strlen(FCWS_CALIBRATION_FILENAME), "rb", strlen("rb"), &ulFileId))
    {
        err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *) &tempfcwsTuningParms, sizeof(fcws_tuning_params), &ulTurningParamlSize);
        MMPS_FS_FileClose(ulFileId);

        if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(fcws_tuning_params)))
        {
            memcpy(&UserfcwsTuningParms, &tempfcwsTuningParms, sizeof(fcws_tuning_params));
        }
        else
        {
            UserfcwsTuningParms.cardv_height_pos = 120;
        }
    }
    else
    {
        UserfcwsTuningParms.cardv_height_pos = 120;
    }
*/
}

void Menudraw_UserFcwsCalibrationLines(UINT16 bID0)
{
    UINT8   sz[6] = {0};
    UINT8   StartX = 60, StartY = 10, EndY = OSD_HEIGHT(bID0)-50;
    UINT8   GapX = 2, GapY = 7;
    UINT8   LineW = 10;
    UINT32  CurPosX, CurPosY;

        AHC_OSDSetColor(bID0, OSD_COLOR_RED);
        AHC_OSDSetPenSize(bID0, 3);
        AHC_OSDSetFont(bID0, &GUI_Font24B_1);

    AHC_OSDDrawLine(bID0, OSD_WIDTH(bID0)-StartX, OSD_WIDTH(bID0)-StartX, StartY, EndY);
    AHC_OSDDrawLine(bID0, OSD_WIDTH(bID0)-StartX, OSD_WIDTH(bID0)-StartX+LineW, StartY, StartY);
    AHC_OSDDrawLine(bID0, OSD_WIDTH(bID0)-StartX, OSD_WIDTH(bID0)-StartX+LineW, EndY, EndY);

    AHC_OSDDrawText_Transparent(bID0,(UINT8 *)"220", OSD_WIDTH(bID0)-StartX+LineW+GapX, StartY-GapY,  strlen("220"));
    AHC_OSDDrawText_Transparent(bID0,(UINT8 *)"100", OSD_WIDTH(bID0)-StartX+LineW+GapX, EndY-GapY,  strlen("100"));
    //OSD
    CurPosX = OSD_WIDTH(bID0) - StartX - GapX - 5;
    CurPosY = EndY - (ADASfcwsTuningParms.cardv_height_pos-100)*(EndY-LineW)/(220-100);

    AHC_OSDSetColor(bID0, OSD_COLOR_GREEN);
    AHC_OSDDrawFillPolygon(bID0, m_TriangleR, 3, CurPosX, CurPosY);
    AHC_OSDDrawLine(bID0, OSD_WIDTH(bID0)-StartX, OSD_WIDTH(bID0)-StartX+LineW, CurPosY, CurPosY);

    sprintf((char *) &sz, "%03d", ADASfcwsTuningParms.cardv_height_pos);
    AHC_OSDDisableDrawFontBk(AHC_TRUE);
    AHC_OSDDrawTextInRectEx(bID0, sz, CurPosX-50, CurPosY-7, CurPosX, CurPosY+7, GUI_TA_LEFT|GUI_TA_VCENTER,  strlen("120"), 0);
    AHC_OSDDisableDrawFontBk(AHC_FALSE);
}
#endif

#if 0
void ________MenuDraw_UserLdwsCalibrationProcess_Function_______(){ruturn;}
#endif

void MenuDraw_UserLdwsCalibrationProcess(PSMENUSTRUCT pMenu, unsigned char status, int offset)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterMenuDrawing(&bID0, &bID1 );

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bID0, 0, 0, OSD_WIDTH(bID0), OSD_HEIGHT(bID0));
    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"LDWS Calibration Process ...",
                            0, 10, OSD_WIDTH(bID0), 30,
                            GUI_TA_HCENTER | GUI_TA_VCENTER,
                            strlen("LDWS Calibration Process ..."),
                            AHC_OSD_ROTATE_NONE);
    switch (User_Ldws_Status)
    {
    case USER_LDWS_CALIB_INIT:
        Menudraw_UserLdwsCalibrationInit(bID0);
        break;

    case USER_LDWS_CALIB_UP_Y:
        if (offset)
        {
            OSDfcwsTuningParms.CalibrationStarY += offset;

            if (OSDfcwsTuningParms.CalibrationStarY <= 1)
            {
                OSDfcwsTuningParms.CalibrationStarY = 1;
            }
            else if(OSDfcwsTuningParms.CalibrationStarY >= OSD_HEIGHT(bID0))
            {
                OSDfcwsTuningParms.CalibrationStarY = OSD_HEIGHT(bID0);
            }
        }
        break;

    case USER_LDWS_CALIB_DOWN_Y:
        if(offset)
        {
            //OSD
            OSDfcwsTuningParms.CalibrationEndY += offset;

            if(OSDfcwsTuningParms.CalibrationEndY <= 1)
            {
                OSDfcwsTuningParms.CalibrationEndY = 1;
            }
            else if(OSDfcwsTuningParms.CalibrationEndY >= OSD_HEIGHT(bID0))
            {
                OSDfcwsTuningParms.CalibrationEndY  = OSD_HEIGHT(bID0);
            }
        }
        break;

#if MENU_GENERAL_FCWS_CALIBRATION_EN
    case USER_FCWS_CALIB_POS:
        if(offset)
        {
            //OSD
            ADASfcwsTuningParms.cardv_height_pos += offset;

            if(ADASfcwsTuningParms.cardv_height_pos <= 100)
                ADASfcwsTuningParms.cardv_height_pos = 100;
            else if(ADASfcwsTuningParms.cardv_height_pos >= 220)
                ADASfcwsTuningParms.cardv_height_pos = 220;
        }
        else
        {
            Menudraw_UserFcwsCalibrationInit(bID0);
        }
        break;
#endif
    }

#if MENU_AUTO_LDWS_CALIBRATION_EN
    Menudraw_AutoLdwsCalibrationLines(bID0);
#else
#if MENU_GENERAL_FCWS_CALIBRATION_EN
    if(User_Ldws_Status == USER_FCWS_CALIB_POS)
    {
        Menudraw_UserFcwsCalibrationLines(bID0);
        Menudraw_UserLdwsCalibrationIcon(bID0);
    }
    else
#endif
    {
        Menudraw_UserLdwsCalibrationLines(bID0);
        Menudraw_UserLdwsCalibrationIcon(bID0);
    }
#endif
    OSDDraw_ExitMenuDrawing( &bID0, &bID1 );

    END_LAYER(bID0);
}

MMP_ERR User_LDWS_CalibrationParam_Save(void)
{
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG   ulFileId;
    MMP_ULONG   ulActualSize;
#if 0
    err = MMPS_FS_FileOpen(LDWS_CALIBRATION_FILENAME, strlen(LDWS_CALIBRATION_FILENAME), "wb", strlen("wb"),  &ulFileId );

    if (MMP_ERR_NONE == err)
    {
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&m_LdwsCalibratedParam, sizeof(m_LdwsCalibratedParam), &ulActualSize);
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&UserldwsSetupPosi, sizeof(UserldwsSetupPosi), &ulActualSize);
        err |= MMPS_FS_FileClose(ulFileId);

        if (MMP_ERR_NONE != err)
        {
            printc(FG_RED("%s: MMPS_FS_FileWrite %s error")"%d \r\n", __func__, LDWS_CALIBRATION_FILENAME,__LINE__);
        }
    }
    else
    {
        printc(FG_RED("%s: MMPS_FS_FileOpen %s error")"%d \r\n", __func__, LDWS_CALIBRATION_FILENAME,__LINE__);
    }
#endif
#if MENU_GENERAL_FCWS_CALIBRATION_EN
    err = MMPS_FS_FileOpen(FCWS_CALIBRATION_FILENAME, strlen(FCWS_CALIBRATION_FILENAME), "wb", strlen("wb"),  &ulFileId );

    if (MMP_ERR_NONE == err)
    {
        err |= MMPS_FS_FileWrite(ulFileId, (MMP_UBYTE *)&ADASfcwsTuningParms, sizeof(ADASfcwsTuningParms), &ulActualSize);
        err |= MMPS_FS_FileClose(ulFileId);

        if (MMP_ERR_NONE != err)
        {
            printc(FG_RED("%s: MMPS_FS_FileWrite %s error")"%d \r\n", __func__, FCWS_CALIBRATION_FILENAME,__LINE__);
        }
        #if(ADAS_OUTPUT_LOG)
        printc("====Saving FCWS Parameters====\r\n");
        printc("ADASfcwsTuningParms.CalibrationStarY : %d\r\n",ADASfcwsTuningParms.CalibrationStarY);
        printc("ADASfcwsTuningParms.CalibrationEndY  : %d\r\n",ADASfcwsTuningParms.CalibrationEndY);
        printc("ADASfcwsTuningParms.cardv_height_pos : %d\r\n",ADASfcwsTuningParms.cardv_height_pos);
        printc("====End of Saving FCWS Parameters====\r\n");
        #endif
    }
    else
    {
        printc(FG_RED("%s: MMPS_FS_FileOpen %s error")" %d \r\n", __func__, FCWS_CALIBRATION_FILENAME,__LINE__);
    }
#endif

    return err;
}

UINT32 SubMenuEventHandler_UserLdwsCalibration(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    switch(ulEvent)
    {

        case MENU_BATTERY_DETECTION:
        case MENU_UPDATE_MESSAGE:
        break;

        case MENU_EXIT:
            return MENU_ERR_EXIT;
            break;

        case MENU_INIT:
            CHARGE_ICON_ENABLE(AHC_FALSE);

            pMenu->uiStatus = MENU_STATUS_NONE;
            pMenu->bSetOne = 0;
            if (pMenu->pfMenuGetDefaultVal)
            {
                pMenu->iSelected = pMenu->pfMenuGetDefaultVal(pMenu);
            }
            else
            {
                pMenu->iSelected = 0;
            }
            pMenu->iCurrentPos = pMenu->iSelected;

            User_Ldws_Status = USER_LDWS_CALIB_INIT;
            MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, 0);
            #if MENU_AUTO_LDWS_CALIBRATION_EN
            User_Ldws_Status = USER_LDWS_CALIB_EXIT;
            MMPS_Display_SetWinActive(UPPER_IMAGE_WINDOW_ID, MMP_FALSE);
            #else
            User_Ldws_Status = USER_LDWS_CALIB_UP_Y;
            #endif
            break;

        case MENU_OK:
            User_Ldws_Status++;
            printc("User_Ldws_Status = %d\r\n", User_Ldws_Status);

            if (User_Ldws_Status < USER_LDWS_CALIB_EXIT)
            {
                MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, 0);
            }
            else
            {
                User_LDWS_CalibrationParam_Convert();
                User_LDWS_CalibrationParam_Save();
                AHC_OS_SleepMs(500);
                SubMenuEventHandler_UserLdwsCalibration(pMenu, MENU_MENU, 0);
                User_Ldws_Status = USER_LDWS_CALIB_INIT;
                CHARGE_ICON_ENABLE(AHC_TRUE);
                #if MENU_AUTO_LDWS_CALIBRATION_EN
                MMPS_Display_SetWinActive(UPPER_IMAGE_WINDOW_ID, MMP_TRUE);
                #endif
            }
        break;

        case MENU_UP:
        case MENU_RIGHT:
            #if MENU_GENERAL_FCWS_CALIBRATION_EN
            if(User_Ldws_Status == USER_FCWS_CALIB_POS)
            {
                MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, 10);
            }
            else
            #endif
            {
                MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, -(FCWS_CALIBRATION_SHIFT_OFFSET));
            }
        break;

        case MENU_DOWN:
        case MENU_LEFT:
            #if MENU_GENERAL_FCWS_CALIBRATION_EN
            if(User_Ldws_Status == USER_FCWS_CALIB_POS)
            {
                MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, -10);
            }
            else
            #endif
            {
                MenuDraw_UserLdwsCalibrationProcess(pMenu, User_Ldws_Status, FCWS_CALIBRATION_SHIFT_OFFSET);
            }
        break;

        case MENU_MENU:
            {
                PSMENUSTRUCT    pParentMenu;

                pParentMenu = pMenu->pParentMenu;
                pMenu->pParentMenu = NULL;
                pMenu->bSetOne = 0;

                if (pParentMenu == NULL)
                {
                    return MENU_ERR_EXIT;
                }
                #if TVOUT_ENABLE
                if(AHC_IsTVConnectEx())
                {
                    UINT8  bID0, bID1;

                    OSDDraw_EnterDrawing(&bID0, &bID1 );
                    OSDDraw_SetAlphaBlending(bID0,0);
                    AHC_OSDSetActive(bID0, 0);
                    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
                    AHC_OSDDrawFillRect(bID0, 0, 0,  OSD_WIDTH(bID0), OSD_HEIGHT(bID0));
#if 0//TVOUT_ENABLE
                    Scale_MenuOSD_Window(MMP_DISPLAY_DUPLICATE_2X);
#endif
                    OSDDraw_ExitDrawing(&bID0, &bID1 );
                }
                #endif

                SetCurrentMenu(pParentMenu);
                pParentMenu->pfEventHandler(pParentMenu, MENU_INIT, 0);

                #if TVOUT_ENABLE
                if(AHC_IsTVConnectEx())
                {
                    AHC_OSDSetActive(TVFunc_GetMenuOsdID(), 1);
                }
                #endif
                #if MENU_AUTO_LDWS_CALIBRATION_EN
                MMPS_Display_SetWinActive(UPPER_IMAGE_WINDOW_ID, MMP_TRUE);
                #endif
            }
            break;

        default:
            break;
    }

    return MENU_ERR_OK;
}
#endif
