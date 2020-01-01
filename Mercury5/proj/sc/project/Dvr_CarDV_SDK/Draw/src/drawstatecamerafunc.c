/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "config_fw.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_isp.h"
#include "ahc_warningmsg.h"
#include "ahc_media.h"
#include "ahc_parameter.h"
#include "ahc_display.h"
#include "ahc_utility.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "MenuDrawingFunc.h"
#include "keyparser.h"
#include "MenuSetting.h"
#include "DrawStateMenuSetting.h"
#include "drawstatecamerafunc.h"
#include "drawstatevideofunc.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "statecamerafunc.h"
#include "statevideofunc.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "zoomcontrol.h"
#include "dsc_charger.h"
#include "ui_drawgeneral.h"
#if (SUPPORT_GPS)
#include "gps_ctl.h"
#endif

#define MAX_REMAIN_NUM_LEN      10

/*===========================================================================
 * Global variable
 *===========================================================================*/

UINT8   m_DscDrawCounter = 0;

/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern UINT8        m_ubBatteryStatus;
extern AHC_BOOL     bUpdateFlashLedIcon;

#if (DAY_NIGHT_MODE_SWITCH_EN)
extern AHC_BOOL     bNightMode;
#endif

#if (MOTION_DETECTION_EN)
extern AHC_BOOL     m_ubMotionDtcEn;
extern UINT32       m_ulVMDRemindTime;
extern AHC_BOOL     m_ubInRemindTime;
extern AHC_BOOL     m_ubVMDStart;
extern AHC_BOOL     m_ulVMDCancel;
#endif
extern IMAGESIZE_SETTING    CaptureResolution;
extern AHC_OSD_INSTANCE     *m_OSD[];
extern AHC_BOOL             gbAhcDbgBrk;

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern void     UpdateMotionRemindTime(int rTime);
extern void     DrawStateTVPreviewClear(UINT16 bID0);
extern void     DrawStateHdmiPreviewClear(UINT16 bID0);

/*===========================================================================
 * Main body
 *===========================================================================*/

void UpdateCaptureSelfTimer(void)
{
#if (DSC_MODE_ENABLE==1) && (MENU_STILL_SELF_TIMER_EN) && (DSC_SELFSHOT_EN)

    static UINT16 SelfTime = 0;
    UINT8   bMainWID    = MAIN_DISPLAY_BUFFER;
    //UINT8   bOvlWID;
    UINT16  x           = (m_OSD[bMainWID]->width>>1);
    UINT16  y           = (m_OSD[bMainWID]->height>>1);

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if (SelfTime == CaptureFunc_GetSelfTime())
        return;

    SelfTime = CaptureFunc_GetSelfTime();

    if(SelfTime)
    {
        if(AHC_WMSG_States())
           AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);

        BEGIN_LAYER(bMainWID);

        AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);

        AHC_OSDDrawFillRect(bMainWID, x-40, y-30, x+30, y+35);

        AHC_OSDSetColor(bMainWID, 0xAA000000);
        AHC_OSDSetActive(bMainWID, 1);

        switch(SelfTime)
        {
            case 0:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_0, x-25, y-30);
            break;
            case 1:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_1, x-25, y-30);
            break;
            case 2:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_2, x-25, y-30);
            break;
            case 3:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_3, x-25, y-30);
            break;
            case 4:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_4, x-25, y-30);
            break;
            case 5:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_5, x-25, y-30);
            break;
            case 6:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_6, x-25, y-30);
            break;
            case 7:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_7, x-25, y-30);
            break;
            case 8:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_8, x-25, y-30);
            break;
            case 9:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_9, x-25, y-30);
            break;
            case 10:
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_1, x-25-30, y-30);
                AHC_OSDDrawBitmap(bMainWID, &bmIcon_Num_0, x-25,    y-30);
            break;
        }
    }
    else
    {
        BEGIN_LAYER(bMainWID);
        AHC_OSDSetActive(bMainWID, 0);
        AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bMainWID, x-40, y-30, x+30, y+35);

        if (MenuSettingConfig()->uiSelfTimer == SELF_TIMER_OFF)
        {
            RECT    tSize       = POS_STATE_SELFTIMER;
            // Clean Self-Timer Shot Icon
            BEGIN_LAYER(OVL_BUFFER_INDEX);
            AHC_OSDSetColor(OVL_BUFFER_INDEX, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawFillRect(OVL_BUFFER_INDEX,  tSize.uiLeft, tSize.uiTop,
                                                   tSize.uiLeft+tSize.uiWidth, tSize.uiTop+tSize.uiHeight);

            AHC_OSDSetColor(OVL_BUFFER_INDEX, 0xAA000000);
            END_LAYER(OVL_BUFFER_INDEX);

            #if (OVL_BUFFER_INDEX1 != OVL_BUFFER_INDEX)
            BEGIN_LAYER(OVL_BUFFER_INDEX1);
            AHC_OSDSetColor(OVL_BUFFER_INDEX1, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawFillRect(OVL_BUFFER_INDEX1, tSize.uiLeft, tSize.uiTop,
                                                   tSize.uiLeft+tSize.uiWidth, tSize.uiTop+tSize.uiHeight);
            AHC_OSDSetColor(OVL_BUFFER_INDEX1, 0xAA000000);
            END_LAYER(OVL_BUFFER_INDEX1);
            #endif
        }
    }

    END_LAYER(bMainWID);
#endif
}

#if (DSC_MODE_ENABLE==1)

void DrawCaptureInfo(AHC_BOOL bClear)
{
    UINT8   bOvlWID;
    UINT8   bMainWID = MAIN_DISPLAY_BUFFER;
#if (MENU_STILL_SELF_TIMER_EN)
    RECT    tSize    = POS_STATE_SELFTIMER;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(AHC_TRUE)
    {
        OSDDraw_GetLastOvlDrawBuffer(&bOvlWID);
        AHC_OSDSetActive(bOvlWID, 1);
        BEGIN_LAYER(bMainWID);
        AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bMainWID, 0, 200, 40, DISP_HEIGHT);
        AHC_OSDDrawFillRect(bMainWID, 0, 60, m_OSD[bMainWID]->width, 180); //Clear WMSG and Self Time
        AHC_OSDSetColor(bMainWID, 0xAA000000);
        END_LAYER(bMainWID);

#if (MENU_STILL_SELF_TIMER_EN)
        OSDDraw_GetLastOvlDrawBuffer(&bOvlWID);
        BEGIN_LAYER(bOvlWID);
        AHC_OSDSetColor(bOvlWID, 0xAA000000);

        switch ( MenuSettingConfig()->uiSelfTimer )
        {
            case SELF_TIMER_2S:
                 AHC_OSDDrawBitmap(bOvlWID, &bmIcon_Selftimer_2S, tSize.uiLeft, tSize.uiTop);
            break;
            case SELF_TIMER_10S:
                 AHC_OSDDrawBitmap(bOvlWID, &bmIcon_Selftimer_10S, tSize.uiLeft, tSize.uiTop);
            break;
            default:
                AHC_OSDSetColor(bOvlWID, OSD_COLOR_TRANSPARENT);
                AHC_OSDDrawFillRect(bOvlWID, tSize.uiLeft, tSize.uiTop,
                                    tSize.uiLeft + bmIcon_Selftimer_2S.XSize,
                                    tSize.uiTop  + bmIcon_Selftimer_2S.YSize);
                AHC_OSDSetColor(bOvlWID, 0xAA000000);
            break;
        }

        AHC_OSDSetActive(bOvlWID, 1);
        END_LAYER(bOvlWID);
#endif
    }
}

void DrawCaptureRemainNum(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT8   digit = 0;
    UINT32  ulRemainCaptureNum = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    ulRemainCaptureNum = CaptureFunc_GetRemainCaptureNum();
    digit = NumOfDigit(ulRemainCaptureNum);

    BEGIN_LAYER(ubID);

    if(bLarge==LARGE_SIZE){
        AHC_OSDSetFont(ubID, &GUI_Font32_1);
    }
    else {
        AHC_OSDSetFont(ubID, &GUI_Font20B_1);
    }

    //clear rect,
    AHC_OSDSetColor(ubID, bkColor);
    AHC_OSDDrawDec(ubID, 0, x, y, MAX_REMAIN_NUM_LEN);

    AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);
    AHC_OSDSetBkColor(ubID, bkColor);

    AHC_OSDDrawDec(ubID, ulRemainCaptureNum, x, y, digit);

    #if 0
    if(digit<MAX_REMAIN_NUM_LEN)
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDDrawDec(ubID, 0, x, y, MAX_REMAIN_NUM_LEN-digit);
    }
    #endif

    END_LAYER(ubID);
}

void DrawCaptureMotionDtc(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (MOTION_DETECTION_EN)

    GUI_BITMAP  IconID  = bmIcon_Motion_Detection;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
        else
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize, y+IconID.YSize);

        AHC_OSDSetColor(ubID, 0xAA000000);
    }
    else
    {   if(m_ubMotionDtcEn)
        {
            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID, &IconID, x, y);
        }
    }

    END_LAYER(ubID);
#endif
}

void DrawCaptureFlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    AHC_OSDSetColor(ubID, 0xAA000000);
    OSDDrawSetting_FlashMode(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawCaptureZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if(OSD_SHOW_ZOOM_BAR==1)
    AHC_BOOL bShow = (AHC_BOOL) Para1;

    if(bShow) {
        AHC_OSDSetColor(ubID, 0xAA000000);
    }

    OSDDraw_DigitZoomBar(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1, UI_CAMERA_STATE);
#endif
}

void DrawStateCaptureInit(void)
{
    UINT8   bID0 = 0;
    UINT8   bID1 = 0;
    UINT8   idx  = 0;

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_EnterDrawing(&bID0, &bID1);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
    OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);

    AHC_OSDSetColor(bID0, 0xAA000000);

    for (idx = 0; idx < DSC_GUI_MAX; idx++)
    {
        if (idx == DSC_GUI_GPS_STATE)
            continue;

        UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    BEGIN_LAYER(bID0);
    OSDDraw_MainTouchButton(bID0, UI_CAMERA_STATE);
    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);

    AHC_OSDSetActive(bID0, AHC_TRUE);

    CHARGE_ICON_ENABLE(AHC_TRUE);
}
void DrawStateTVPreviewCameraInit(UINT8 ubID)
{
#if (TVOUT_PREVIEW_EN)
    UINT8   idx  = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    DrawStateTVPreviewClear(ubID);

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, 0xAA000000);

    END_LAYER(ubID);

    SetCurrentOpMode(CAPTURE_MODE);

    for(idx = 0; idx<DSC_GUI_MAX; idx++)
    {
        UIDrawEx(ubID, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#endif
}

#if(SUPPORT_HDMI)
void DrawStateHdmiPreviewCameraInit(UINT8 ubID)
{
#if (HDMI_PREVIEW_EN)
    UINT8   idx  = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    DrawStateHdmiPreviewClear(ubID);

    BEGIN_LAYER(ubID);

    AHC_OSDSetColor(ubID, 0xAA000000);

    END_LAYER(ubID);

    SetCurrentOpMode(CAPTURE_MODE);

    for(idx = 0; idx<DSC_GUI_MAX; idx++)
    {
        UIDrawEx(ubID, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#endif
}
#endif

void DrawStateCaptureEnd(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    #if 0//(HDMI_PREVIEW_EN || TVOUT_PREVIEW_EN) //Should not judge TV out or HDMI here.
    if(AHC_IsTVConnectEx())
    {
        bID0 = TVFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_REMAIN_NUM, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
    }
#if (HDMI_ENABLE)
    else if(AHC_IsHdmiConnect())
    {
        bID0 = HDMIFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_REMAIN_NUM, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
    }
#endif
    else
    #endif
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);

        UIDrawEx(bID0, DSC_GUI_REMAIN_NUM, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
}

void DrawCaptureStatePageSwitch(UINT8 ubPage)
{
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    OSDDraw_ClearTouchButtons(bID0, CaptureCtrlPage_TouchButton, ITEMNUM(CaptureCtrlPage_TouchButton));

    BEGIN_LAYER(bID0);
    if( TOUCH_MAIN_PAGE == ubPage )
        OSDDraw_MainTouchButton(bID0, UI_CAMERA_STATE);
    else
        OSDDraw_CtrlTouchButton(bID0, UI_CAMERA_STATE);
    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
#endif
}

void DrawCaptureStateZoom(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    #if 0//(HDMI_PREVIEW_EN || TVOUT_PREVIEW_EN) //Should not judge TV out or HDMI here.
    if(AHC_IsTVConnectEx())
    {
        bID0 = TVFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
    }
#if (HDMI_ENABLE)
    else if(AHC_IsHdmiConnect())
    {
        bID0 = HDMIFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);//TBD
    }
#endif //#if(SUPPORT_HDMI)
    else
    #endif
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);
        UIDrawEx(bID0, DSC_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
}
#endif

void DrawCaptureStateEV(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    #if 0//(HDMI_PREVIEW_EN || TVOUT_PREVIEW_EN) //Should not judge TV out or HDMI here.
    if(AHC_IsTVConnectEx())
    {
        bID0 = TVFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_EV, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#if (HDMI_ENABLE)
    else if(AHC_IsHdmiConnect())
    {
        bID0 = HDMIFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_EV, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);//TBD
    }
#endif //#if(SUPPORT_HDMI)
    else
    #endif
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);
        UIDrawEx(bID0, DSC_GUI_EV, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
}

#if (DSC_MODE_ENABLE==1)

void DrawCaptureSelfTimer(void)
{
#if (MENU_STILL_SELF_TIMER_EN) && (DSC_SELFSHOT_EN)
    UINT8    bID0 = 0;
    UINT8    bID1 = 0;

#if 0//(HDMI_PREVIEW_EN || TVOUT_PREVIEW_EN) //Should not judge TV out or HDMI here.
    if(AHC_IsTVConnectEx()){
        bID0 = TVFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_SELF_TIMER, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#if (HDMI_ENABLE)
    else if(AHC_IsHdmiConnect()){
        bID0 = HDMIFunc_GetUImodeOsdID();

        UIDrawEx(bID0, DSC_GUI_SELF_TIMER, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);//TBD
    }
#endif
    else
#endif
    {
        OSDDraw_EnterDrawing(&bID0, &bID1);
        UIDrawEx(bID0, DSC_GUI_SELF_TIMER, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
#endif
}

void DrawCaptureStateUpdate(void)
{
    UINT8    bID0 = 0;
    UINT8    bID1 = 0;
    static UINT8    SD_status    = AHC_FALSE;
#if (DAY_NIGHT_MODE_SWITCH_EN)
    static UINT8    Night_status = AHC_FALSE;
#endif
#if (MOTION_DETECTION_EN)
    static UINT8    ubVMDStatus  = AHC_FALSE;
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1);

    UIDrawEx(bID0, DSC_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_FALSE);

    #if (DSC_SELFSHOT_EN)
    UpdateCaptureSelfTimer();
    #endif

    if(m_ubBatteryStatus != MenuSettingConfig()->uiBatteryVoltage)
    {
        UIDrawEx(bID0, DSC_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        m_ubBatteryStatus = MenuSettingConfig()->uiBatteryVoltage;
    }

    if(bUpdateFlashLedIcon)
    {
        UIDrawEx(bID0, DSC_GUI_FLASH, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        bUpdateFlashLedIcon = AHC_FALSE;
    }

    if(SD_status != AHC_SDMMC_IsSD1MountDCF())
    {
        UIDrawEx(bID0, DSC_GUI_SD_STATE,   AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        UIDrawEx(bID0, DSC_GUI_REMAIN_NUM, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        SD_status = AHC_SDMMC_IsSD1MountDCF();
    }

    if(CaptureResolution != MenuSettingConfig()->uiIMGSize)
    {
        UIDrawEx(bID0, DSC_GUI_IMAGE_RES, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    #if (DAY_NIGHT_MODE_SWITCH_EN)
    if(Night_status != bNightMode)
    {
        UIDrawEx(bID0, DSC_GUI_SCENE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        Night_status = bNightMode;
    }
    #endif

    #if (MOTION_DETECTION_EN)
    if(ubVMDStatus != m_ubMotionDtcEn)
    {
        #ifdef CFG_DRAW_REC_MOTION_SEN_OFF //may be defined in config_xxx.h
        if( MenuSettingConfig()->uiMotionDtcSensitivity == MOTION_DTC_SENSITIVITY_OFF)
        {
            UIDrawEx(bID0, DSC_GUI_VMD_STATE, AHC_TRUE, AHC_FALSE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            ubVMDStatus = AHC_FALSE;
        }
        else
        #endif
        {
            UIDrawEx(bID0, DSC_GUI_VMD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            ubVMDStatus = m_ubMotionDtcEn;
        }
    }
    #endif

    if(m_DscDrawCounter%2==0)
    {
        UIDrawEx(bID0, DSC_GUI_RTC_TIME,  AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    #if (SUPPORT_GPS) && GPS_MODULE_SHOW_OSD
        if (!GPSCtrl_ModuleConnected())
            UIDrawEx(bID0, DSC_GUI_GPS_STATE, AHC_TRUE,  AHC_FALSE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        else
            UIDrawEx(bID0, DSC_GUI_GPS_STATE, AHC_TRUE,  AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    #endif

        #if (MOTION_DETECTION_EN)
        if(m_ulVMDRemindTime > 0)
        {
            if (m_ulVMDCancel) {
                m_ulVMDRemindTime = 0;
                // Clean Screen
                UpdateMotionRemindTime(-1);
            } else {
                m_ulVMDRemindTime--;
                if(m_ubInRemindTime)
                    UpdateMotionRemindTime(m_ulVMDRemindTime);
            }
        }
        else
        {
            if (m_ubMotionDtcEn)
                m_ubVMDStart = AHC_TRUE;
        }
        #endif
    }
    m_DscDrawCounter++;
    m_DscDrawCounter = m_DscDrawCounter%2;

    #if OSD_SHOW_BATTERY_STATUS == 1
    AHC_DrawChargingIcon_UsingTimer(bID0);
    #endif
    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateCaptureUpdate(UINT32 ubEvent)
{
#if (DSC_MODE_ENABLE)
    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_MODE                       :
        case EVENT_KEY_MENU                       :
        case EVENT_KEY_PLAYBACK_MODE              :
            DrawCaptureInfo(AHC_TRUE);
        break;

        case EVENT_KEY_TELE_PRESS                 :
        case EVENT_KEY_WIDE_PRESS                 :
        case EVENT_KEY_WIDE_STOP                  :
        case EVENT_KEY_TELE_STOP                  :
        case EVENT_KEY_ZOOM_STATUS_CLEAR          :
            DrawCaptureStateZoom();
        break;

        case EVENT_KEY_LEFT                       :
            DrawCaptureSelfTimer();
        break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
            DrawStateCaptureInit();

            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
            DrawCaptureInfo(AHC_FALSE);
        break;

        case EVENT_DSC_PREVIEW_INIT               :
            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
            DrawStateCaptureInit();
            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
            DrawCaptureInfo(AHC_FALSE);
        break;

        case EVENT_DSC_KEY_CAPTURE_STATUS_CLEAR   :
            DrawStateCaptureEnd();
        break;

        case EVENT_DSC_SET_EV   :
            DrawCaptureStateEV();
        break;

        case EVENT_DSC_KEY_UPDATE_MESSAGE         :
            DrawCaptureStateUpdate();
        break;
    }
#endif  // DSC_MODE_ENABLE
}
