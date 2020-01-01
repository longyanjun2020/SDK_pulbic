
/*===========================================================================
 * Include file
 *===========================================================================*/
#include "Customer_config.h"
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

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
#define OSD_WIDTH(X)    (m_OSD[X]->width)
#define OSD_HEIGHT(X)   (m_OSD[X]->height)
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
#define OSD_WIDTH(X)    (m_OSD[X]->height)
#define OSD_HEIGHT(X)   (m_OSD[X]->width)
#endif

#if (MENU_RD_LDWS_CALIBRATION_EN)

enum LDWSTATUS
{
    LDWS_CALIB_INIT = 0,
    LDWS_CALIB_UP_X,
    LDWS_CALIB_UP_Y,
    LDWS_CALIB_LEFT_X,
    LDWS_CALIB_LEFT_Y,
    LDWS_CALIB_RIGHT_X,
    LDWS_CALIB_RIGHT_Y,
    LDWS_CALIB_EXIT
};

static unsigned char Ldws_Status = LDWS_CALIB_INIT;
static ldws_tuning_params menu_ldws_tuning_params = {
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

/*===========================================================================
 * Local function
 *===========================================================================*/
AHC_BOOL MenuItemLdwsCalibrationSettings(PSMENUITEM pItem, AHC_BOOL bIsHover);

/*===========================================================================
 * Global variable
 *===========================================================================*/
extern AHC_OSD_INSTANCE         *m_OSD[];
extern MMP_BOOL                 m_bCalibrated;
extern ldws_tuning_params       m_LdwsCalibratedParam;
extern AHC_BOOL                 gbAhcDbgBrk;
#if 0
void ________Calibration_Function_______(){ruturn;}
#endif

void MenuDrawSubPage_LdwsCalibrationSetting(PSMENUSTRUCT pMenu)
{
    UINT8  bID0, bID1;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterMenuDrawing(&bID0, &bID1 );

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);

    AHC_OSDDrawFillRect(bID0, 0, 0, OSD_WIDTH(bID0), OSD_HEIGHT(bID0));

    AHC_OSDSetColor(bID0, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_DARKGRAY2);

    ShowOSD_SetLanguage(bID0);
    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"LDWS Calibration",
                            0, 30, OSD_WIDTH(bID0), 50,
                            GUI_TA_HCENTER | GUI_TA_VCENTER,
                            strlen("LDWS Calibration"),
                            AHC_OSD_ROTATE_NONE);
    AHC_OSDDrawTextInRectEx(bID0,
                            (UINT8 *)"Press PWR key to start",
                            0, 120, OSD_WIDTH(bID0), 160,
                            GUI_TA_HCENTER | GUI_TA_VCENTER,
                            strlen("Press PWR key to start"),
                            AHC_OSD_ROTATE_NONE);

    #if 0//TVOUT_ENABLE
    if(AHC_IsTVConnectEx())
    {
        AHC_OSDSetActive(TVFunc_GetMenuOsdID(), 0);
        Scale_MenuOSD_Window(MMP_DISPLAY_DUPLICATE_1X);
        AHC_OSDSetActive(bID0, 1);
        OSDDraw_SetAlphaBlending(bID0,1);
        AHC_OSDSetCurrentDisplay(bID0);
        AHC_OSDRefresh();
    }
    #endif

    OSDDraw_ExitMenuDrawing( &bID0, &bID1 );
    END_LAYER(bID0);
}

void LDWS_CalibrationParam_Inverse(UINT8 ubID, ldws_tuning_params ldws_tuning_params)
{
    MMP_ULONG width, height;
    MMP_ULONG offsetX = 0, offsetY = 0;
    MMP_ULONG ulOsdW, ulOsdH;

    //MMPS_3GPRECD_GetPreviewRes(gsAhcPrmSensor, &width, &height);
    ulOsdW = OSD_WIDTH(ubID);
    ulOsdH = OSD_HEIGHT(ubID);
    height = ulOsdH;
    width = LDWS_WIDTH*height/LDWS_HEIGHT;
    offsetX = abs(ulOsdW-width)/2;
    offsetY = abs(ulOsdH-height)/2;

    menu_ldws_tuning_params.laneCalibrationUpPointX = ldws_tuning_params.laneCalibrationUpPointX * width/ldws_tuning_params.laneCalibrationImageWidth + offsetX;
    menu_ldws_tuning_params.laneCalibrationUpPointY = ldws_tuning_params.laneCalibrationUpPointY * height/ldws_tuning_params.laneCalibrationImageHeight + offsetY;
    menu_ldws_tuning_params.laneCalibrationLeftPointX = ldws_tuning_params.laneCalibrationLeftPointX * width/ldws_tuning_params.laneCalibrationImageWidth + offsetX;
    menu_ldws_tuning_params.laneCalibrationLeftPointY = ldws_tuning_params.laneCalibrationLeftPointY * height/ldws_tuning_params.laneCalibrationImageHeight + offsetY;
    menu_ldws_tuning_params.laneCalibrationRightPointX = ldws_tuning_params.laneCalibrationRightPointX * width/ldws_tuning_params.laneCalibrationImageWidth + offsetX;
    menu_ldws_tuning_params.laneCalibrationRightPointY = ldws_tuning_params.laneCalibrationRightPointY * height/ldws_tuning_params.laneCalibrationImageHeight + offsetY;

    printc("Get OSD: %dx%d, %dx%d, %dx%d, %dx%d\r\n", menu_ldws_tuning_params.laneCalibrationImageWidth, menu_ldws_tuning_params.laneCalibrationImageHeight,
                                                  menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointY,
                                                  menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointY,
                                                  menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointY);
}

void MenuDrawChangeSubItem_LdwsCalibrationProcess(PSMENUSTRUCT pMenu, unsigned char status, int offset)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    UINT8  X_offset = 100;
    UINT8  Y_offset = 60;
    MMP_ULONG ulFileId;
    MMP_ERR err = MMP_ERR_NONE;
    MMP_ULONG ulTurningParamlSize;
    ldws_tuning_params templdwsTuningParms;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterMenuDrawing(&bID0, &bID1 );

    BEGIN_LAYER(bID0);
    {
      X_offset = 40;
      Y_offset = 30;
    }

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);

    if(status == LDWS_CALIB_INIT)
        AHC_OSDDrawFillRect(bID0, 0, 0,  OSD_WIDTH(bID0), OSD_HEIGHT(bID0));
    else
    {
        AHC_OSDSetPenSize(bID0, 5);

        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationLeftPointX,
                        menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationLeftPointY);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                        menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                        menu_ldws_tuning_params.laneCalibrationLeftPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);

        AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointY, 5);
        AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointY, 5);
        AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointY, 5);
    }

    AHC_OSDSetColor(bID0, MENU_TEXT_COLOR);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);

    AHC_OSDSetFont(bID0, &GUI_Font20B_1);

    AHC_OSDDrawTextInRectEx(bID0, (UINT8 *)"LDWS Calibration Process ...",
                            0, 10, OSD_WIDTH(bID0), 30,
                            GUI_TA_HCENTER | GUI_TA_VCENTER,
                            strlen("LDWS Calibration Process ..."),
                            AHC_OSD_ROTATE_NONE);
    AHC_OSDDrawTextInRectEx(bID0,
                            (UINT8 *)"Move red line to intersection point by Left / Right key",
                            0, OSD_HEIGHT(bID0) - Y_offset + 12, OSD_WIDTH(bID0), OSD_HEIGHT(bID0),
                            GUI_TA_HCENTER | GUI_TA_VCENTER,
                            strlen("Move red line to intersection point by Left / Right key"),
                            AHC_OSD_ROTATE_NONE);

    AHC_OSDSetPenSize(bID0, 5);

    switch (status) {
    case LDWS_CALIB_INIT:
        menu_ldws_tuning_params.laneCalibrationImageWidth = OSD_WIDTH(bID0);//RTNA_LCD_GetAttr()->usPanelH;//usPanelW;  //OSD_WIDTH(bID0);
        menu_ldws_tuning_params.laneCalibrationImageHeight = OSD_HEIGHT(bID0);//RTNA_LCD_GetAttr()->usPanelW;//usPanelH;    //OSD_HEIGHT(bID0);

        if (MMP_ERR_NONE == MMPS_FS_FileOpen(LDWS_CALIBRATION_DEFAULT_FILENAME, strlen(LDWS_CALIBRATION_DEFAULT_FILENAME), "rb", strlen("rb"), &ulFileId))
        {
            err = MMPS_FS_FileRead(ulFileId, (MMP_UBYTE *) &templdwsTuningParms, sizeof(ldws_tuning_params), &ulTurningParamlSize);
            MMPS_FS_FileClose(ulFileId);

            if ((MMP_ERR_NONE == err) && (ulTurningParamlSize == sizeof(ldws_tuning_params)))
            {
                //memcpy(&menu_ldws_tuning_params, &templdwsTuningParms, sizeof(ldws_tuning_params));
                LDWS_CalibrationParam_Inverse(bID0,templdwsTuningParms);
            }

            //LDWS_CalibrationParam_Inverse(menu_ldws_tuning_params);
        }
        else
        {
            menu_ldws_tuning_params.laneCalibrationUpPointX = OSD_WIDTH(bID0) / 2;
            menu_ldws_tuning_params.laneCalibrationUpPointY = OSD_HEIGHT(bID0) / 2;
            menu_ldws_tuning_params.laneCalibrationLeftPointX = OSD_WIDTH(bID0) / 4;
            menu_ldws_tuning_params.laneCalibrationLeftPointY = OSD_HEIGHT(bID0) - Y_offset - 10;
            menu_ldws_tuning_params.laneCalibrationRightPointX = OSD_WIDTH(bID0) * 3 / 4;
            menu_ldws_tuning_params.laneCalibrationRightPointY = OSD_HEIGHT(bID0) - Y_offset - 10;
        }

        AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
        AHC_OSDSetPenSize(bID0, 2);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX-3, menu_ldws_tuning_params.laneCalibrationUpPointX-3,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX+3, menu_ldws_tuning_params.laneCalibrationUpPointX+3,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);

        AHC_OSDSetColor(bID0, OSD_COLOR_RED);
        AHC_OSDSetPenSize(bID0, 5);

        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointX,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        break;

    case LDWS_CALIB_UP_X:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointX,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        if (offset)
        {
            menu_ldws_tuning_params.laneCalibrationUpPointX += offset;

            if(menu_ldws_tuning_params.laneCalibrationUpPointX <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationUpPointX = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationUpPointX >= OSD_WIDTH(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationUpPointX = OSD_WIDTH(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationUpPointX-3, menu_ldws_tuning_params.laneCalibrationUpPointX-3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationUpPointX+3, menu_ldws_tuning_params.laneCalibrationUpPointX+3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointX,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        }
        else
        {
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY-3, menu_ldws_tuning_params.laneCalibrationUpPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY+3, menu_ldws_tuning_params.laneCalibrationUpPointY+3);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationUpPointY);
        }
        break;

    case LDWS_CALIB_UP_Y:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        X_offset, OSD_WIDTH(bID0)-X_offset,
                        menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationUpPointY);
        if (offset)
        {
            menu_ldws_tuning_params.laneCalibrationUpPointY += offset;

            if (menu_ldws_tuning_params.laneCalibrationUpPointY <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationUpPointY = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationUpPointY >= OSD_HEIGHT(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationUpPointY = OSD_HEIGHT(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY-3, menu_ldws_tuning_params.laneCalibrationUpPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY+3, menu_ldws_tuning_params.laneCalibrationUpPointY+3);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationUpPointY);
        }
        else
        {
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX-3, menu_ldws_tuning_params.laneCalibrationLeftPointX-3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX+3, menu_ldws_tuning_params.laneCalibrationLeftPointX+3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointX,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        }
        break;

    case LDWS_CALIB_LEFT_X:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointX,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        if(offset)
        {
            menu_ldws_tuning_params.laneCalibrationLeftPointX += offset;

            if (menu_ldws_tuning_params.laneCalibrationLeftPointX <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationLeftPointX = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationLeftPointX >= OSD_WIDTH(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationLeftPointX = OSD_WIDTH(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX-3, menu_ldws_tuning_params.laneCalibrationLeftPointX-3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX+3, menu_ldws_tuning_params.laneCalibrationLeftPointX+3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointX,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        }
        else
        {
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY-3, menu_ldws_tuning_params.laneCalibrationLeftPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY+3, menu_ldws_tuning_params.laneCalibrationLeftPointY+3);
            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY, menu_ldws_tuning_params.laneCalibrationLeftPointY);
        }
        break;

    case LDWS_CALIB_LEFT_Y:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        X_offset, OSD_WIDTH(bID0)-X_offset,
                        menu_ldws_tuning_params.laneCalibrationLeftPointY, menu_ldws_tuning_params.laneCalibrationLeftPointY);
        if(offset)
        {
            menu_ldws_tuning_params.laneCalibrationLeftPointY += offset;

            if(menu_ldws_tuning_params.laneCalibrationLeftPointY <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationLeftPointY = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationLeftPointY >= OSD_HEIGHT(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationLeftPointY = OSD_HEIGHT(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY-3, menu_ldws_tuning_params.laneCalibrationLeftPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY+3, menu_ldws_tuning_params.laneCalibrationLeftPointY+3);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationLeftPointY, menu_ldws_tuning_params.laneCalibrationLeftPointY);
        }
        else
        {
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX-3, menu_ldws_tuning_params.laneCalibrationRightPointX-3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX+3, menu_ldws_tuning_params.laneCalibrationRightPointX+3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        }
        break;

    case LDWS_CALIB_RIGHT_X:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                        Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        if (offset)
        {
            menu_ldws_tuning_params.laneCalibrationRightPointX += offset;

            if (menu_ldws_tuning_params.laneCalibrationRightPointX <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationRightPointX = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationRightPointX >= OSD_WIDTH(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationRightPointX = OSD_WIDTH(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX-3, menu_ldws_tuning_params.laneCalibrationRightPointX-3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX+3, menu_ldws_tuning_params.laneCalibrationRightPointX+3,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);
            AHC_OSDDrawLine(bID0,
                            menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                            Y_offset, OSD_HEIGHT(bID0)-Y_offset);
        }
        else {
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY-3, menu_ldws_tuning_params.laneCalibrationRightPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY+3, menu_ldws_tuning_params.laneCalibrationRightPointY+3);
            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);
        }
        break;

    case LDWS_CALIB_RIGHT_Y:
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetPenSize(bID0, 12);
        AHC_OSDDrawLine(bID0,
                        X_offset, OSD_WIDTH(bID0)-X_offset,
                        menu_ldws_tuning_params.laneCalibrationRightPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);
        if (offset)
        {
            menu_ldws_tuning_params.laneCalibrationRightPointY += offset;

            if (menu_ldws_tuning_params.laneCalibrationRightPointY <= 1)
            {
                menu_ldws_tuning_params.laneCalibrationRightPointY = 1;
            }
            else if(menu_ldws_tuning_params.laneCalibrationRightPointY >= OSD_HEIGHT(bID0))
            {
                menu_ldws_tuning_params.laneCalibrationRightPointY = OSD_HEIGHT(bID0);
            }
            AHC_OSDSetColor(bID0, OSD_COLOR_DARKGRAY2);
            AHC_OSDSetPenSize(bID0, 2);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY-3, menu_ldws_tuning_params.laneCalibrationRightPointY-3);
            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY+3, menu_ldws_tuning_params.laneCalibrationRightPointY+3);

            AHC_OSDSetColor(bID0, OSD_COLOR_RED);
            AHC_OSDSetPenSize(bID0, 5);

            AHC_OSDDrawLine(bID0,
                            X_offset, OSD_WIDTH(bID0)-X_offset,
                            menu_ldws_tuning_params.laneCalibrationRightPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);
        }
        break;
    }

    AHC_OSDSetColor(bID0, OSD_COLOR_GREEN);
    AHC_OSDSetPenSize(bID0, 5);

    AHC_OSDDrawLine(bID0,
                    menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationLeftPointX,
                    menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationLeftPointY);
    AHC_OSDDrawLine(bID0,
                    menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                    menu_ldws_tuning_params.laneCalibrationUpPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);
    AHC_OSDDrawLine(bID0,
                    menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationRightPointX,
                    menu_ldws_tuning_params.laneCalibrationLeftPointY, menu_ldws_tuning_params.laneCalibrationRightPointY);

    AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationUpPointX, menu_ldws_tuning_params.laneCalibrationUpPointY, 5);
    AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationLeftPointX, menu_ldws_tuning_params.laneCalibrationLeftPointY, 5);
    AHC_OSDDrawFillCircle(bID0, menu_ldws_tuning_params.laneCalibrationRightPointX, menu_ldws_tuning_params.laneCalibrationRightPointY, 5);

    OSDDraw_ExitMenuDrawing( &bID0, &bID1 );

    END_LAYER(bID0);
}

AHC_BOOL MenuItemLdwsCalibrationSettings(PSMENUITEM pItem, AHC_BOOL bIsHover)
{
    return AHC_TRUE;
}

AHC_BOOL MenuInitLdwsCalibration(void)
{
    return AHC_TRUE;
}

UINT32 SubMenuEventHandler_LdwsCalibration(PSMENUSTRUCT pMenu, UINT32 ulEvent, UINT32 ulParam)
{
    printc("SubMenuEventHandler_LdwsCalibration - %d\r\n", ulEvent);

    switch(ulEvent)
    {

        case MENU_BATTERY_DETECTION:
            MenuDrawSubPage_LdwsCalibrationSetting( pMenu );
        break;

        case MENU_UPDATE_MESSAGE:
        break;

        case MENU_EXIT:
            return MENU_ERR_EXIT;
            break;

        case MENU_INIT:
            CHARGE_ICON_ENABLE(AHC_FALSE);

            #ifdef SLIDE_STRING
            StopSlideString();
            #endif

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
            Ldws_Status = LDWS_CALIB_INIT;
            MenuDrawSubPage_LdwsCalibrationSetting(pMenu);
            break;

        case MENU_OK:
            printc("Ldws_Status = %d\r\n", Ldws_Status);

            if (Ldws_Status < (LDWS_CALIB_EXIT - 1))
            {
                MenuDrawChangeSubItem_LdwsCalibrationProcess(pMenu, Ldws_Status, 0);
                Ldws_Status++;
            }
            else
            {
                LDWS_CalibrationParam_Convert(menu_ldws_tuning_params);
                LDWS_CalibrationParam_Save();
                AHC_OS_SleepMs(500);
                SubMenuEventHandler_LdwsCalibration(pMenu, MENU_MENU, 0);
                Ldws_Status = LDWS_CALIB_INIT;
                CHARGE_ICON_ENABLE(AHC_TRUE);
            }
        break;

        case MENU_UP:
        case MENU_RIGHT:
            MenuDrawChangeSubItem_LdwsCalibrationProcess(pMenu, Ldws_Status, OSD_DISPLAY_SCALE_LCD?(-6/OSD_DISPLAY_SCALE_LCD):-6);
        break;

        case MENU_DOWN:
        case MENU_LEFT:
            MenuDrawChangeSubItem_LdwsCalibrationProcess(pMenu, Ldws_Status, OSD_DISPLAY_SCALE_LCD?(6/OSD_DISPLAY_SCALE_LCD):6);
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
            }
            break;

        default:
            break;
    }

    return MENU_ERR_OK;
}

#endif
