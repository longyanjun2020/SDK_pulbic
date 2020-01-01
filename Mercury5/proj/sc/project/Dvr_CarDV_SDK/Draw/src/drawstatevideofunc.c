/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_browser.h"
#include "ahc_capture.h"
#include "ahc_gsensor.h"
#include "ahc_parameter.h"
#include "ahc_media.h"
#include "ahc_display.h"
#include "ahc_warningmsg.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "MenuDrawingFunc.h"
#include "keyparser.h"
#include "MenuSetting.h"
#include "DrawStateMenuSetting.h"
#include "drawstatevideofunc.h"
#include "drawstatecamerafunc.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "zoomcontrol.h"
#include "statevideofunc.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "dsc_charger.h"
#include "ui_drawgeneral.h"
#include "GSensor_ctrl.h"
#include "disp_drv.h"
#include "ait_utility.h"
#include "ShowOSDFunc.h"
#include "drv_uart.h"
#include "snr_cfg.h"
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#include "wlan.h"
#endif
#if SUPPORT_GSENSOR
#include "GSensor_ctrl.h"
#include "ahc_gsensor.h"
#endif
#if GPS_CONNECT_ENABLE
#include "gps_ctl.h"
#endif

#if (ENABLE_ADAS_LDWS)
#include "ldws.h"
extern void AHC_WMSG_LDWS_Line(UINT16 ubID, AHC_BOOL needClean);
#endif

#if (ENABLE_ADAS_FCWS)
#include "fcws.h"
extern void AHC_WMSG_FCWS_Info(UINT16 ubID, AHC_BOOL needClean);
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define VR_OSD_HIDE_TIME    (120)
#if (AHC_ENABLE_VIDEO_STICKER)
#define VIDEO_STICKER_HEIGHT            (64)  //(32)
#define VIDEO_STICKER_BORDER_OFFSET     (16)
#endif

#define DRAW_VID_FUNC_ENABLE    (1)

/*===========================================================================
 * Global varible
 *===========================================================================*/

UINT8       m_ubBatteryStatus   = 0;
UINT8       ubVRStatus          = VIDEO_REC_STOP;
#if (AUTO_HIDE_OSD_EN)
AHC_BOOL    m_ubHideOSD         = AHC_FALSE;
UINT32      m_ulOSDCounter      = 0;
#endif

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
static UINT8 monoPatternDrawed = AHC_FALSE;
#endif

#if (ENABLE_ADAS_LDWS)
AHC_BOOL    gbLdwsAutoCaliStatus = AHC_FALSE;
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL bUpdateFlashLedIcon;
extern AHC_BOOL bMuteRecord;

#if (CHARGE_FULL_NOTIFY)
extern AHC_BOOL bChargeFull;
#endif

#if (MOTION_DETECTION_EN)
extern AHC_BOOL m_ubMotionDtcEn;
extern UINT32   m_ulVMDRemindTime;
extern AHC_BOOL m_ubInRemindTime;
extern AHC_BOOL m_ubVMDStart;
extern UINT32   m_ulVMDStableCnt;
extern AHC_BOOL m_ulVMDCancel;
#endif

#if (LIMIT_MAX_LOCK_FILE_NUM)
extern UINT32   m_ulLockFileNum;
extern UINT32   m_ulLockEventNum;
#endif

#if (DAY_NIGHT_MODE_SWITCH_EN)
extern AHC_BOOL bNightMode;
#endif
extern MOVIESIZE_SETTING            m_eUiVideoRecResol;
extern AHC_OSD_INSTANCE             *m_OSD[];

extern AHC_BOOL                     gbAhcDbgBrk;

#if (SUPPORT_GSENSOR)
extern AHC_BOOL                     dump_GValues_osd;
extern AHC_GSENSOR_DATA             dump_GValue;
#endif

#if (SUPPORT_GPS)
extern AHC_BOOL                     bGPS_PageExist;
#endif

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern void     DrawCaptureStateEV(void);
void            Dump_Gsensor_XYZ(UINT8 did);
UINT32          AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS axis);

/*===========================================================================
 * Main body
 *===========================================================================*/

void Dump_Gsensor_XYZ(UINT8 did)
{
#if (SUPPORT_GSENSOR)
    char    sz[32];
    INT16   CurSensitivity;

    CurSensitivity = AHC_Gsensor_GetAcceSensitivity(AHC_GSENSOR_AXIS_X);

    sprintf(sz, "[%d] %d / %d / %d         \r\n", CurSensitivity, dump_GValue.acc_val[0], dump_GValue.acc_val[1], dump_GValue.acc_val[2]);

    AHC_OSDSetColor(did, OSD_COLOR_YELLOW);
    AHC_OSDSetBkColor(did, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawText(did, (UINT8*)sz, 160, 50, strlen(sz));
#endif
}

void Dump_ISP_MSG(UINT8 did)
{
#if defined(INFO_ISP_MSG_ON_PNL)&&(INFO_ISP_MSG_ON_PNL)
    U8      sz[MSG_ON_PNL_BYTE_LINE]={0};
    unsigned char* pMsg;
    INT16   CurSensitivity;
    U8      u8IdxWr,u8IdxRd,i,j=0;

    u8IdxWr = ShowOnPnl_GetMsgIdx();
    for(i=0;i<MSG_ON_PNL_LINE_NUM;i++){
        u8IdxRd = (i+u8IdxWr)%MSG_ON_PNL_LINE_NUM;
        pMsg = ShowOnPnl_GetMsg(u8IdxRd);

        if(pMsg){
            memcpy(sz,pMsg,strlen(pMsg));
            //sprintf(sz, "[%d] %d / %d / %d         \r\n", CurSensitivity, dump_GValue.acc_val[0], dump_GValue.acc_val[1], dump_GValue.acc_val[2]);
            AHC_OSDSetColor(did, OSD_COLOR_YELLOW);
            AHC_OSDSetBkColor(did, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawText(did, (UINT8*)sz, 60, (40+(j*32)), strlen(sz));
            j++;
        }
    }
#endif
}

void UpdateMotionRemindTime(int rTime)
{
#if (MOTION_DETECTION_EN)

    static int STime    = -1;
    static const GUI_BITMAP* digicn[] = {   &bmIcon_Num_0,
                                            &bmIcon_Num_1,
                                            &bmIcon_Num_2,
                                            &bmIcon_Num_3,
                                            &bmIcon_Num_4,
                                            &bmIcon_Num_5,
                                            &bmIcon_Num_6,
                                            &bmIcon_Num_7,
                                            &bmIcon_Num_8,
                                            &bmIcon_Num_9};

    UINT8   bMainWID    = MAIN_DISPLAY_BUFFER;
    UINT16  x, y;
    UINT16  Width, Height;
    AHC_DISPLAY_OUTPUTPANEL  OutputDevice;

    if(STime == rTime)
        return;
    else
       STime = rTime;

    AHC_GetDisplayOutputDev(&OutputDevice);

    x = AHC_GET_ATTR_OSD_W(bMainWID)>>1;
    y = AHC_GET_ATTR_OSD_H(bMainWID)>>1;

    AHC_Display_GetWidthHdight(&Width, &Height);
    if(OutputDevice != MMP_DISPLAY_SEL_MAIN_LCD) {
        x = Width>>1;
        y = Height>>1;
    }

#if 0
    if(OutputDevice != MMP_DISPLAY_SEL_MAIN_LCD)
    {
        switch(OutputDevice)
        {
#if (HDMI_ENABLE)
            case MMP_DISPLAY_SEL_HDMI:
                bMainWID = HDMIFunc_GetUImodeOsdID();
                AHC_GetHdmiDisplayWidthHeight(&Width, &Height);
            break;
#endif
#if (TVOUT_ENABLE)
            case MMP_DISPLAY_SEL_NTSC_TV:
                bMainWID = TVFunc_GetUImodeOsdID();
                AHC_GetNtscTvDisplayWidthHeight(&Width, &Height);
            break;
            case MMP_DISPLAY_SEL_PAL_TV:
                bMainWID = TVFunc_GetUImodeOsdID();
                AHC_GetPalTvDisplayWidthHeight(&Width, &Height);
            break;
#endif
                default:
                    break;
        }

        x = Width>>1;
        y = Height>>1;
    }
#endif

    if(STime > 0)
    {
        if(AHC_WMSG_States())
           AHC_WMSG_Draw(AHC_FALSE, WMSG_NONE, 0);

        AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bMainWID, x-40, y-30, x+30, y+35);
        AHC_OSDSetColor(bMainWID, 0xAA000000);
        AHC_OSDSetActive(bMainWID, 1);
        if (STime > 9)
            STime = 9;
        AHC_OSDDrawBitmap(bMainWID, digicn[STime], x-25, y-30);
    }
    else
    {
        AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bMainWID, x-40, y-30, x+30, y+35);
        if(OutputDevice != MMP_DISPLAY_SEL_MAIN_LCD)
            AHC_OSDSetActive(bMainWID, 1);

    }
#endif
}

void UpdateVideoCurrentTimeStamp(AHC_BOOL bSetStickerEnable)
{
    AHC_RTC_TIME    stRtcTime ;

    VideoTimer_Event_Busy(AHC_TRUE);
    AHC_RTC_GetTime(&stRtcTime);
    AHC_VIDEO_UpdateTimeStamp(&stRtcTime, bSetStickerEnable);
    VideoTimer_Event_Busy(AHC_FALSE);
}

void UpdateVideoRecordStatus(UINT8 ubStatus)
{
    ubVRStatus = ubStatus;
}

void DrawVideoRecInfo(AHC_BOOL bClear)
{
    UINT8    bOvlWID;
//    UINT8    bMainWID = MAIN_DISPLAY_BUFFER;

#ifndef STR_STANDBY_STATUS_WIDTH
#define STR_STANDBY_STATUS_WIDTH        32
#endif

#ifndef STR_STANDBY_STATUS_HEIGHT
#define STR_STANDBY_STATUS_HEIGHT       22
#endif

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_GetLastOvlDrawBuffer(&bOvlWID);

    //AHC_OSDSetActive(bOvlWID, 1);
#if 0
    BEGIN_LAYER(bMainWID);
    AHC_OSDSetColor(bMainWID, OSD_COLOR_TRANSPARENT);
    AHC_OSDSetBkColor(bMainWID, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bMainWID, STR_STANDBY_STATUS_X0, STR_STANDBY_STATUS_Y0, STR_STANDBY_STATUS_X0+STR_STANDBY_STATUS_WIDTH, STR_STANDBY_STATUS_Y0+STR_STANDBY_STATUS_HEIGHT); //Clear REC or PAUSE icon
    AHC_OSDSetColor(bMainWID, 0xAA000000);
    END_LAYER(bMainWID);
#endif
}

void DrawVideoRecStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    const UINT8 empty_rec_state[] = {"        "};
    const UINT8 stby_rec_state[] =  {"   STBY "};
    const UINT8 rec_rec_state[] =   {"    REC "};
    const UINT8 cap_rec_state[] =   {"   CAP  "};

#define CFG_DRAW_REC_RECORD_STOP            0xEE30DC30

#define CFG_DRAW_REC_RECORD_COLOR           (OSD_COLOR_RED2)

#ifndef CFG_DRAW_REC_CAPTURE_COLOR //may be defined in config_xxx.h
#define CFG_DRAW_REC_CAPTURE_COLOR          CFG_DRAW_REC_RECORD_COLOR
#endif

    GUI_COLOR   IconColor = OSD_COLOR_TRANSPARENT;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if(bLarge==LARGE_SIZE) {
        AHC_OSDSetFont(ubID, &GUI_Font32B_1);
    }
    else {
        AHC_OSDSetFont(ubID, &GUI_Font16B_1);
    }

    AHC_OSDSetColor(ubID, IconColor);
    AHC_OSDSetBkColor(ubID, bkColor);

    AHC_OSDDrawFillRect(ubID, x-2, y-8, x+48, y+32);

    switch(ubVRStatus)
    {
        case VIDEO_REC_STOP:
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_STOP);
            AHC_OSDDrawText(ubID, (UINT8*) stby_rec_state, x, y, sizeof(stby_rec_state));
            break;

        case VIDEO_REC_START:
#ifdef CFG_DRAW_REC_START_USE_BMP //may be defined in config_xxx.h
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
            AHC_OSDDrawBitmap(ubID, &bmIcon_REC, x, 0);
#elif defined (CFG_DRAW_REC_START_BY_PARAM) //may be defined in config_xxx.h
            if(Para1 == 0)
            {
                AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
                AHC_OSDDrawText(ubID, (UINT8*)rec_rec_state, x, y, strlen(rec_rec_state));
            }
#else
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
            AHC_OSDDrawText(ubID, (UINT8*) rec_rec_state, x, y, sizeof(rec_rec_state));
#endif
            break;

        case VIDEO_REC_PAUSE:
            if(bLarge==LARGE_SIZE)
            {
                AHC_OSDDrawBitmapMag(ubID, &bmIcon_VRPause, x+5, y+5, 2, 2);
            }
            else
            {
                AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
                AHC_OSDDrawText(ubID, (UINT8*) empty_rec_state, x-2, y, sizeof(empty_rec_state));
                AHC_OSDDrawBitmap(ubID, &bmIcon_VRPause, x, y);
            }
            break;

        case VIDEO_REC_CAPTURE:
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_CAPTURE_COLOR);
            AHC_OSDDrawText(ubID, (UINT8*) cap_rec_state, x, y, sizeof(cap_rec_state));
            break;
    }

    END_LAYER(ubID);
}

void DrawVideoAvailableRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UBYTE   Hour, Min, Sec;
    UINT16  leftpos     = x;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
    }
#endif

    if ((AHC_CheckCurSysMode(AHC_MODE_RECORD_PREVIEW))  ||
        (AHC_GetAhcSysMode() == AHC_MODE_RECORD_PRERECD))
    {
        // 0 to get time for current setting of bitrate
        AHC_VIDEO_AvailableRecTimeEx(0, &Hour, &Min, &Sec);

        BEGIN_LAYER(ubID);

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        {
            AHC_OSDSetFont(ubID, &GUI_Font32B_1);
        }
        else
        {
            AHC_OSDSetFont(ubID, &GUI_Font20B_1);
        }

        {
            char    sztime[16];
            int     l;

            /* space in format will clean bitmap when the pixles of width becomes shorter then before*/
            // too many space padding at end, might overwrite lock icon
            l = sprintf(sztime, "%d:%02d:%02d  ", Hour, Min, Sec);
            AHC_OSDDrawText(ubID, (UINT8*)sztime, leftpos ,y, l);
        }

        END_LAYER(ubID);
    }
}

void DrawVideoCurrentRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32  ulTime;
    UINT16  leftpos = x;
    UINT32  ulSysStatus;
    char    sztime[16];
    int     l;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
    }
#endif

    AHC_GetSystemStatus(&ulSysStatus);
    ulSysStatus >>= 16;

    if( (ulSysStatus == AHC_MODE_VIDEO_RECORD))
    {
        AHC_VIDEO_GetCurRecordingTime(&ulTime);
        ulTime += VideoFunc_GetRecordTimeOffset();

        BEGIN_LAYER(ubID);

        #ifdef CFG_DRAW_REC_CUR_TIME_COLOR //may be defined in config_xxx.h
        AHC_OSDSetColor(ubID, CFG_DRAW_REC_CUR_TIME_COLOR);
        #else
        AHC_OSDSetColor(ubID, OSD_COLOR_RED);
        #endif

        AHC_OSDSetBkColor(ubID, bkColor);

        if (bLarge==LARGE_SIZE) {
            AHC_OSDSetFont(ubID, &GUI_Font32B_1);
        }
        else {
            AHC_OSDSetFont(ubID, &GUI_Font20B_1);
        }

        /* space in format will clean bitmap when the pixles of width becomes shorter then before*/
        l = sprintf(sztime, "%d:%02d:%02d  ", TIME_HOUR(ulTime), TIME_MIN(ulTime), TIME_SEC(ulTime));
        AHC_OSDDrawText(ubID, (UINT8*)sztime, leftpos, y, l);

        END_LAYER(ubID);
    }
}

void DrawAudioCurRecordTime(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (AUDIO_REC_PLAY_EN)
    UINT16  leftpos     = x;
    UINT32  ulTime;
    char    sztime[16];
    int     l;

    #if (DRAW_VID_FUNC_ENABLE == 0)
    return;
    #endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(bAudioRecording)
    {
        BEGIN_LAYER(ubID);

    #if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
        if (AHC_Get_WiFi_Streaming_Status()) {
            bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        }
    #endif

        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        {
            AHC_OSDSetFont(ubID, &GUI_Font32B_1);
        }
        else
        {
            AHC_OSDSetFont(ubID, &GUI_Font20B_1);
        }

        AHC_GetAudioCurRecTime(&ulTime);

        /* space in format will clean bitmap when the pixles of width becomes shorter then before*/
        l = sprintf(sztime, "%d:%02d:%02d  ", TIME_HOUR(ulTime), TIME_MIN(ulTime), TIME_SEC(ulTime));
        AHC_OSDDrawText(ubID, (UINT8*)sztime, leftpos ,y, l);

        END_LAYER(ubID);
    }
#endif
}

void DrawVideoFileName(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if defined(AIT_INT_USE) && (AIT_INT_USE == 1)
    UINT32  ulSysStatus;
    UINT8   VideoRFileName[16];

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    AHC_GetSystemStatus(&ulSysStatus);
    ulSysStatus >>= 16;

    if( (ulSysStatus == AHC_MODE_VIDEO_RECORD)  )
    {
        memcpy(VideoRFileName, (UINT8*)AHC_VIDEO_GetCurPrmRecdFileName(AHC_FALSE), 16);
        BEGIN_LAYER(ubID);
        AHC_OSDSetColor(ubID, OSD_COLOR_WHITE);
        AHC_OSDSetBkColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
        {
            AHC_OSDSetFont(ubID, &GUI_Font32B_1);
        }
        else
        {
            AHC_OSDSetFont(ubID, &GUI_Font16B_1);
        }

        AHC_OSDDrawText(ubID,(UINT8*)VideoRFileName, x ,y, strlen((INT8*)VideoRFileName));
        END_LAYER(ubID);
    }
#endif
}

void DrawVideoMuteRecord(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#ifndef CFG_DRAW_REC_MUTE_AT_TOP //may be defined in config_xxx.h
    UINT16      leftpos = x;
    UINT16      toppos  = y;
#else
    UINT16      leftpos = 10;
    UINT16      toppos  = 0;
#endif
    GUI_BITMAP  IconID  = bmIcon_mutemicW;
#ifdef CFG_DRAW_REC_MIC //may be defined in config_xxx.h
    GUI_BITMAP  NorMuteIconID   = bmIcon_micW;
#endif
    GUI_COLOR   IconColor = 0xAA000000;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, leftpos, toppos, leftpos+IconID.XSize*ubMag, toppos+IconID.YSize*ubMag);
        else
            AHC_OSDDrawFillRect(ubID, leftpos, toppos, leftpos+IconID.XSize, toppos+IconID.YSize);

        AHC_OSDSetColor(ubID, IconColor);
    }
    else
    {
        if(bMuteRecord)
        {
            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID,  &IconID, leftpos, toppos, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID,  &IconID, leftpos, toppos);
        }
    #ifdef CFG_DRAW_REC_MIC
        else
        {
            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID,  &NorMuteIconID, leftpos, toppos, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID,  &NorMuteIconID, leftpos, toppos);
        }
    #endif
    }
    END_LAYER(ubID);
}

void DrawVideoMotionDtc(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (MOTION_DETECTION_EN)

    GUI_BITMAP  IconID  = BMICON_MOTION_DETECTION;
    GUI_COLOR   IconColor = 0xAA000000;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
        else
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize, y+IconID.YSize);

        AHC_OSDSetColor(ubID, IconColor);
    }
    else
    {
        if(m_ubMotionDtcEn)
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

#if (ENABLE_ADAS_LDWS)
void DrawVideoLDWS_Line(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    AHC_WMSG_LDWS_Line(ubID, AHC_TRUE);
}
#endif

#if (ENABLE_ADAS_FCWS)
void DrawVideoFCWS_Info(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    AHC_WMSG_FCWS_Info(ubID, AHC_TRUE);
}
#endif

void DrawVideoTimeLapse(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    GUI_BITMAP  IconID  = bmTV_TimeLapseB;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag == AHC_FALSE) {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
        else
            AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize, y+IconID.YSize);

        AHC_OSDSetColor(ubID, 0xAA000000);
    }
    else {
        UINT32 vrTimelapseEn = 1;       // Off

        if (AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &vrTimelapseEn) == AHC_TRUE)
        {
            if (vrTimelapseEn != PRJ_VR_TIMELAPSE_OFF) {
                if (bLarge == LARGE_SIZE)
                    AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
                else
                    AHC_OSDDrawBitmap(ubID, &IconID, x, y);
            }
        }
    }

    END_LAYER(ubID);
#endif
}

void DrawVideoLockFileStatus(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#ifdef CFG_DRAW_REC_CUS_LOCK_FILE //may be defined in config_xxx.h
    GUI_BITMAP  IconID  = CFG_DRAW_REC_CUS_LOCK_FILE;
#else
    GUI_BITMAP  IconID  = bmIcon_ProtectKey;
#endif
    GUI_COLOR   IconColor = 0xAA000000;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
    }
#endif

    if(bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawFillRect(ubID, x-5, y-5, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
        else
            AHC_OSDDrawFillRect(ubID, x,   y,   x+IconID.XSize,       y+IconID.YSize);

#if defined (CFG_DRAW_REC_START_BY_PARAM) //may be defined in config_xxx.h
        if(Para1)
#endif
        {
            AHC_OSDSetColor(ubID, IconColor);
        }
    }
    else
    {
        if(VideoFunc_LockFileEnabled() || VideoFunc_IsShareRecordStarted())
        {
            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID, &IconID, x, y, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID, &IconID, x, y);
        }
    }

    END_LAYER(ubID);
}

void DrawVideoLockFileNum(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{

}

void DrawVideoRecording(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    UINT32  ulSysStatus;
    INT32   r = Para1;
    static UINT8 prog = 0;
    GUI_COLOR   IconColor = OSD_COLOR_TRANSPARENT;
    static  MMP_ULONG preTick = 0;
    MMP_ULONG curTick;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    MMPF_OS_GetTime(&curTick);

    if (curTick >= preTick) {
        if ((curTick - preTick) < MS_TO_TICK(500)) {
            return;
        }
    }
    else {
        if ((curTick + ((MMP_ULONG) -1) - preTick) < MS_TO_TICK(500)) {
            return;
        }
    }

    preTick = curTick;

    AHC_GetSystemStatus(&ulSysStatus);

    if(ulSysStatus == ((AHC_MODE_VIDEO_RECORD<<16)|AHC_SYS_VIDRECD_PAUSE))
    {
        return;
    }

    // Draw static icon at HCarDV_DrawStateVideoFunc.c
#ifdef CFG_DRAW_REC_STATIC_ICON //may be defined in config_xxx.h
    return;
#endif

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
    }
#endif

    AHC_OSDSetColor(ubID, IconColor);
    AHC_OSDSetBkColor(ubID, bkColor);
    AHC_OSDDrawFillCircle(ubID, x, y, r >> ((prog++) & 0x01));

    ulSysStatus >>= 16;

    if(ulSysStatus == AHC_MODE_VIDEO_RECORD)
    {
#ifdef CFG_DRAW_REC_RECORD_COLOR2 //may be defined in config_xxx.h
        if(prog%2 == 0)
        {
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
        }
        else
        {
            AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR2);//when the REC point is small
        }
#else
        AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
#endif
        AHC_OSDDrawFillCircle(ubID, x, y, r >> (prog & 0x1));
    }
    END_LAYER(ubID);
}

void DrawAudioRecording(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (AUDIO_REC_PLAY_EN)

    INT32 r = Para1;
    static UINT8 prog = 0;
    GUI_COLOR   IconColor = OSD_COLOR_TRANSPARENT;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(!bAudioRecording)
        return;

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
    }
#endif

    AHC_OSDSetColor(ubID, IconColor);
    AHC_OSDSetBkColor(ubID, bkColor);
    AHC_OSDDrawFillCircle(ubID, x, y, r >> ((prog++) & 0x01));

    AHC_OSDSetColor(ubID, CFG_DRAW_REC_RECORD_COLOR);
    AHC_OSDDrawFillCircle(ubID, x, y, r >> (prog & 0x1));
    END_LAYER(ubID);
#endif
}

void DrawVideoRecFlashMode(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);
    AHC_OSDSetColor(ubID, 0xAA000000);
    END_LAYER(ubID);
    OSDDrawSetting_FlashMode(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawVideoZoomBar(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (VIDEO_DIGIT_ZOOM_EN)
    AHC_BOOL bShow = (AHC_BOOL) Para1;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    if(bShow) {
        GUI_COLOR   IconColor = 0xAA000000;

        BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
        if (AHC_Get_WiFi_Streaming_Status()) {
            bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
            IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        }
#endif

        AHC_OSDSetColor(ubID, IconColor);
        AHC_OSDSetBkColor(ubID, bkColor);
        END_LAYER(ubID);
    }

    OSDDraw_DigitZoomBar(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1, UI_VIDEO_STATE);
#endif
}

void DrawStateTVPreviewClear(UINT16 bID0)
{
    UINT16  uwTVWidth, uwTVHeight;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_PAL:
            AHC_SetDisplayOutputDev(DISP_OUT_TV_PAL, AHC_DISPLAY_DUPLICATE_1X);
            AHC_GetPalTvDisplayWidthHeight(&uwTVWidth, &uwTVHeight);
        break;

        //case TV_SYSTEM_NTSC:
        default:
            AHC_SetDisplayOutputDev(DISP_OUT_TV_NTSC, AHC_DISPLAY_DUPLICATE_1X);
            AHC_GetNtscTvDisplayWidthHeight(&uwTVWidth, &uwTVHeight);
        break;
    }

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);

    AHC_OSDDrawFillRect(bID0, 0, 0, uwTVWidth, uwTVHeight);

    END_LAYER(bID0);
}

void DrawStateVideoRecInit(void)
{
    UINT8   bID0 = 0;
    UINT8   bID1 = 0;
    UINT8   idx  = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_EnterDrawing(&bID0, &bID1);//OSDDraw_GetOvlDrawBuffer(&bID0);
    MMPS_Display_SetWinTransparent(MMP_DISPLAY_WIN_MAIN, MMP_TRUE, 0);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    BEGIN_LAYER(bID0);
    OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
    AHC_OSDSetColor(bID0, 0xAA000000);
    END_LAYER(bID0);

    BEGIN_LAYER(bID1);
    OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);
    END_LAYER(bID1);

    for (idx = 0; idx < VIDEO_GUI_MAX; idx++)
    {
        if (idx == VIDEO_GUI_REC_STATE)
            UpdateVideoRecordStatus(VIDEO_REC_STOP);

        if ((idx == VIDEO_GUI_REC_POINT) || (idx == VIDEO_GUI_GPS_STATE))
            continue;

        UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    BEGIN_LAYER(bID0);
    OSDDraw_MainTouchButton(bID0, UI_VIDEO_STATE);
    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
    //AHC_OSDSetCurrentDisplay(bID1);

    CHARGE_ICON_ENABLE(AHC_TRUE);

#if (ENABLE_ADAS_LDWS)
    gbLdwsAutoCaliStatus = AHC_FALSE;
#endif
}
void DrawStateTVPreviewVideoInit(UINT8 ubID)
{
#if (TVOUT_PREVIEW_EN)
    UINT8   idx  = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    DrawStateTVPreviewClear(ubID);

    BEGIN_LAYER(ubID);
    AHC_OSDSetColor(ubID, 0xAA000000);
    END_LAYER(ubID);

    SetCurrentOpMode(VIDEOREC_MODE);

    for (idx = 0; idx < VIDEO_GUI_MAX; idx++)
    {
        if(idx==VIDEO_GUI_REC_STATE)
            UpdateVideoRecordStatus(VIDEO_REC_STOP);

        if(idx==VIDEO_GUI_REC_POINT)
            continue;

        UIDrawEx(ubID, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#endif
}
void DrawStateHdmiPreviewClear(UINT16 bID0)
{
    UINT16      uwHDMIWidth, uwHDMIHeight;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    switch(MenuSettingConfig()->uiHDMIOutput)
    {
        case HDMI_OUTPUT_1080I:
            AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);
            break;
        case HDMI_OUTPUT_720P:
            AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);
            break;
        case HDMI_OUTPUT_480P:
            AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);
            break;
        default:
            case HDMI_OUTPUT_1080P:
            AHC_GetHdmiDisplayWidthHeight(&uwHDMIWidth, &uwHDMIHeight);
        break;
    }

    BEGIN_LAYER(bID0);
    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect(bID0, 0, 0, uwHDMIWidth, uwHDMIHeight);
    END_LAYER(bID0);
}

void DrawStateHdmiPreviewVideoInit(UINT8 ubID)
{
#if (HDMI_PREVIEW_EN)
    UINT8   idx  = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    DrawStateHdmiPreviewClear(ubID);

    BEGIN_LAYER(ubID);
    AHC_OSDSetColor(ubID, 0xAA000000);
    END_LAYER(ubID);

    SetCurrentOpMode(VIDEOREC_MODE);

    for (idx = 0; idx < VIDEO_GUI_MAX; idx++)
    {
        if(idx==VIDEO_GUI_REC_STATE)
            UpdateVideoRecordStatus(VIDEO_REC_STOP);

        if(idx==VIDEO_GUI_REC_POINT)
            continue;

        UIDrawEx(ubID, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }
#endif
}

void DrawVideoRecStatePageSwitch(UINT8 ubPage)
{
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    OSDDraw_ClearTouchButtons(bID0, VideoCtrlPage_TouchButton, ITEMNUM(VideoCtrlPage_TouchButton));

    BEGIN_LAYER(bID0);
    if( TOUCH_MAIN_PAGE == ubPage )
        OSDDraw_MainTouchButton(bID0, UI_VIDEO_STATE);
    else
        OSDDraw_CtrlTouchButton(bID0, UI_VIDEO_STATE);
    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
#endif
}

void DrawVideoRecStateRecord(VIDEO_RECORD_STATUS Status)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }
    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    UpdateVideoRecordStatus(Status);

    UIDrawEx(bID0, VIDEO_GUI_REC_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, VIDEO_GUI_MUTE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

#ifdef  _OEM_TOUCH_
    BEGIN_LAYER(bID0);
    OSDDraw_MainTouchButton(bID0, (Status == VIDEO_REC_START)?
        UI_VIDEO_RECORD_STATE : UI_VIDEO_STATE);
    END_LAYER(bID0);
#endif

#if defined(AIT_INT_USE) && (AIT_INT_USE == 1)
    if(Status==VIDEO_REC_START)
    {
        DrawVideoFileName(bID0, 160, 30, NORMAL_SIZE, MAG_1X, AHC_TRUE, OSD_COLOR_TRANSPARENT, 0);
    }
    else if(Status==VIDEO_REC_STOP)
    {
        BEGIN_LAYER(bID0);
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bID0, 160, 30, 260, 80);
        AHC_OSDSetColor(bID0, 0xAA000000);
        END_LAYER(bID0);
    }
#endif

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

void DrawVideoRecStateZoom(void)
{
#if (VIDEO_DIGIT_ZOOM_EN)
    UINT8 bID0 = 0;
    UINT8 bID1 = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

#if 0//(HDMI_ENABLE || TVOUT_ENABLE) //Should not judge TV out or HDMI here.
    if(AHC_IsTVConnectEx())
    {
        bID0 = TVFunc_GetUImodeOsdID();

        UIDrawEx(bID0, VIDEO_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
    }
    else if(AHC_IsHdmiConnect())
    {
        bID0 = HDMIFunc_GetUImodeOsdID();

        UIDrawEx(bID0, VIDEO_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
    }
    else
#endif
    {
        OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);
        UIDrawEx(bID0, VIDEO_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_TRUE);
        OSDDraw_ExitDrawing(&bID0, &bID1);
    }
#endif
}

void DrawVideoRecOsdDuringHide(UINT16 ubID)
{
#if (AUTO_HIDE_OSD_EN)
#endif
}

//------------------------------------------------------------------------------
//  Function    : DrawVideo_GetTimeStampPosition
//  Description :
//------------------------------------------------------------------------------
void DrawVideo_GetTimeStampPosition(UINT16  u16CamSel,
                                    UINT16  u16OSDid,
                                    UINT32  u32TimeStampOp,
                                    UINT32* pu32SrcAddr,
                                    UINT16* pu16SrcW,
                                    UINT16* pu16SrcH,
                                    UINT16* pu16ColorFmt,
                                    UINT32* pu32StickerX,
                                    UINT32* pu32StickerY)
{
    UINT16          u16PositionCfg = 0;
    UINT32          u32CaptureW = 0;
    UINT32          u32CaptureH = 0;
    UI_STATE_ID     eCurUIState = UI_STATE_UNSUPPORTED;
    UI_STATE_ID     eParentUIState = UI_STATE_UNSUPPORTED;
    MMP_ERR         sRet = MMP_ERR_NONE;
    extern MMP_BOOL m_bRearCam_2In1;

    AHC_OSDGetBufferAttr(u16OSDid, pu16SrcW, pu16SrcH, pu16ColorFmt, pu32SrcAddr);

    eCurUIState = uiGetCurrentState();
    StateModeGetParent(eCurUIState, &eParentUIState);

    if (UI_STATE_UNSUPPORTED != eParentUIState) {
        eCurUIState = eParentUIState;
    }

    if (UI_VIDEO_STATE == eCurUIState) {
        AHC_VIDEO_GetRecdResol((UINT8)u16CamSel, &u32CaptureW, &u32CaptureH);
    }
    else if (UI_CAMERA_STATE == eCurUIState) {
        AHC_Capture_GetImageSize((UINT8)u16CamSel, &u32CaptureW, &u32CaptureH);
    }

    if(u16CamSel == gsAhcScdSensor && (MMP_GetANACamType() == ANA_CAM_2I1O)) {
        u32CaptureW /= 2; // For DIP, only scale source image to half of encode buffer.
    }

    u16PositionCfg = u32TimeStampOp & AHC_ACC_TIMESTAMP_POSITION_MASK;

    if (u16PositionCfg == AHC_ACC_TIMESTAMP_BOTTOM_RIGHT) {
        *pu32StickerX = (u32CaptureW > (*pu16SrcW + VIDEO_STICKER_BORDER_OFFSET)) ? (u32CaptureW - *pu16SrcW - VIDEO_STICKER_BORDER_OFFSET) : (0);
        *pu32StickerY = (u32CaptureH > (*pu16SrcH + VIDEO_STICKER_BORDER_OFFSET + AHC_VIDEO_STICKER_Y_DELTA)) ? (u32CaptureH - *pu16SrcH - VIDEO_STICKER_BORDER_OFFSET) : (0);
    }
    else if (u16PositionCfg == AHC_ACC_TIMESTAMP_BOTTOM_LEFT) {
        *pu32StickerX = AHC_VIDEO_STICKER_X_DEFAULT_POS;
        *pu32StickerY = (u32CaptureH > (*pu16SrcH - VIDEO_STICKER_BORDER_OFFSET - AHC_VIDEO_STICKER_Y_DELTA)) ? (u32CaptureH - *pu16SrcH - VIDEO_STICKER_BORDER_OFFSET) : (0);
    }
    else if (u16PositionCfg == AHC_ACC_TIMESTAMP_TOP_RIGHT) {
        *pu32StickerX = (u32CaptureW > (*pu16SrcW - VIDEO_STICKER_BORDER_OFFSET)) ? (u32CaptureW - *pu16SrcW - VIDEO_STICKER_BORDER_OFFSET) : (0);
        *pu32StickerY = AHC_VIDEO_STICKER_Y_DEFAULT_POS;
    }
    else if (u16PositionCfg == AHC_ACC_TIMESTAMP_TOP_LEFT) {
        *pu32StickerX = AHC_VIDEO_STICKER_X_DEFAULT_POS;
        *pu32StickerY = AHC_VIDEO_STICKER_Y_DEFAULT_POS;
    }
}

#if defined(INFO_ISP_MSG_ON_PNL)&&(INFO_ISP_MSG_ON_PNL)
void DrawVideo_ISPMsg(UINT8 u16OSDid)
{
    U8      sz[MSG_ON_PNL_BYTE_LINE]={0};
    unsigned char* pMsg;
    INT16   CurSensitivity;
    U8      u8IdxWr,u8IdxRd,i,j=0;

    u8IdxWr = ShowOnPnl_GetMsgIdx();
    for(i=0;i<MSG_ON_PNL_LINE_NUM;i++){
        u8IdxRd = (i+u8IdxWr)%MSG_ON_PNL_LINE_NUM;
        pMsg = ShowOnPnl_GetMsg(u8IdxRd);

        if(pMsg){
            memcpy(sz,pMsg,strlen(pMsg));
            AHC_OSDSetColor(u16OSDid, OSD_COLOR_YELLOW);
            AHC_OSDSetBkColor(u16OSDid, OSD_COLOR_TRANSPARENT);
            AHC_OSDDrawText(u16OSDid, (UINT8*)sz, 60, (40+(j*32)), strlen(sz));
            j++;
        }
    }

}
#endif

void DrawVideo_GPSInfo(UINT8 u16OSDid)
{
    #if (AHC_GPS_STICKER_ENABLE && SUPPORT_GPS)
    if (AHC_GPS_Module_Attached())
    {
        if (MenuSettingConfig()->uiGPSStamp == GPS_STAMP_ON) {

            UINT16  uiDegree = 0, uiMinute = 0;
            UINT16  tempX = 0;
            UINT16  tempY = 0;
            double  uiSec = 0;

        #if (GPS_MODULE == GPS_MODULE_NMEA0183)
            NMEAINFO   *pInfo;
            pInfo =(NMEAINFO *)GPS_Information();
        #elif (GPS_MODULE == GPS_MODULE_GMC1030)
            GPSRADARINFO   *pInfo;
            pInfo =(GPSRADARINFO *)GPSRadar_Information();
        #endif

            tempX = 0;
            tempY = 40;

            AHC_OSDSetFont(u16OSDid, &STICKER_FRONT_2);

            if (GPSCtrl_GPS_IsValidValue())
            {
                UINT8 ubInterval = 12;
                UINT8 ubDigits   = 1;

                if (pInfo->dwLat>0)
                    AHC_OSDDrawText(u16OSDid,(UINT8 *)"N ", 0, tempY, sizeof("N "));
                else
                    AHC_OSDDrawText(u16OSDid,(UINT8 *)"S ", 0, tempY, sizeof("S "));

                GPSCtrl_GPSFormatTrans(pInfo->dwLat, &uiDegree, &uiMinute, &uiSec);

                if (uiDegree < 10)
                {
                    ubDigits = 1;
                }
                else
                {
                    ubDigits = 2;
                }
                ubInterval *= (2 - ubDigits);

                tempX += 15;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)" ", tempX + ubInterval, tempY, sizeof(" "));
                AHC_OSDDrawFloat(u16OSDid, uiDegree, ubDigits );

                tempX += 30;
                AHC_UC_SetEncodeUTF8();
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"\xB0", tempX, tempY, sizeof("\xB0"));
                AHC_UC_SetEncodeNone();
                AHC_OSDDrawFloat(u16OSDid, uiMinute, 2 );

                tempX += 30;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"'", tempX, tempY, sizeof("'"));
                AHC_OSDDrawFloat(u16OSDid, uiSec, 4 );

                tempX += 50;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"''", tempX, tempY, sizeof("''"));

                if (pInfo->dwLon>0)
                    AHC_OSDDrawText(u16OSDid,(UINT8 *)"E ", 130+20, tempY, sizeof("E "));
                else
                    AHC_OSDDrawText(u16OSDid,(UINT8 *)"W ", 130+20, tempY, sizeof("W "));

                GPSCtrl_GPSFormatTrans(pInfo->dwLon, &uiDegree, &uiMinute, &uiSec);

                ubInterval = 12;

                if (uiDegree < 10)
                {
                    ubDigits = 1;
                }
                else if (uiDegree < 100)
                {
                    ubDigits = 2;
                }
                else
                {
                    ubDigits = 3;
                }

                ubInterval *= (3 - ubDigits);
                tempX = 150+20;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)" ", tempX + ubInterval, tempY, sizeof(" "));
                AHC_OSDDrawFloat(u16OSDid, uiDegree, ubDigits );

                tempX += 45;
                AHC_UC_SetEncodeUTF8();
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"\xB0", tempX, tempY, sizeof("\xB0"));
                AHC_UC_SetEncodeNone();
                AHC_OSDDrawFloat(u16OSDid, uiMinute, 2 );

                tempX += 30;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"'", tempX, tempY, sizeof("'"));
                AHC_OSDDrawFloat(u16OSDid, uiSec, 4 );

                tempX += 50;
                AHC_OSDDrawText(u16OSDid,(UINT8 *)"''",tempX,tempY,sizeof("''"));
            }
            else
            {
                AHC_UC_SetEncodeUTF8();

                AHC_OSDDrawText(u16OSDid,
                                (UINT8*)"-  - -\xB0  - -' - - - -''   -  - -\xB0  - -' - - - -'' ",
                                tempX, tempY,
                                STRLEN("-  - -\xB0  - -' - - - -''   -  - -\xB0  - -' - - - -'' "));

                AHC_UC_SetEncodeNone();
            }
        }
    }
    #endif
}

//------------------------------------------------------------------------------
//  Function    : DrawVideo_TimeStamp
//  Description :
//------------------------------------------------------------------------------
void DrawVideo_TimeStamp(UINT16         u16OSDid,
                         UINT32         u32TimeStampOp,
                         AHC_RTC_TIME*  pstRtcTime,
                         UINT32*        pu32SrcAddr,
                         UINT16*        pu16SrcW,
                         UINT16*        pu16SrcH,
                         UINT16*        pu16TempColorFmt,
                         UINT32*        pu32StickerX,
                         UINT32*        pu32StickerY)
{
#if (AHC_ENABLE_VIDEO_STICKER)
    UINT16                  u16DateCfg = 0;
    UINT16                  u16FormatCfg = 0;
    UINT16                  u16PositionCfg = 0;
    const GUI_FONT*         OldFont = NULL;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
        return;
    }

    BEGIN_LAYER(u16OSDid);

    //BEGIN_LAYER(OVL_BUFFER_INDEX); // TBD
    //BEGIN_LAYER(OVL_BUFFER_INDEX1);

    u16DateCfg      = u32TimeStampOp & (AHC_ACC_TIMESTAMP_DATE_MASK   |
                                        AHC_ACC_TIMESTAMP_LOGOEX_MASK |
                                        AHC_ACC_TIMESTAMP_DATEEX_MASK);
    u16PositionCfg  = u32TimeStampOp & AHC_ACC_TIMESTAMP_POSITION_MASK;
    u16FormatCfg    = u32TimeStampOp & AHC_ACC_TIMESTAMP_FORMAT_MASK;

    #ifdef _OEM_VR_STICKER_
    {
        RECT    rc;
        POINT   p;

        rc.uiLeft  = 0;
        rc.uiTop   = 0;
        rc.uiWidth = pu16SrcW;
        rc.uiHeight= pu16SrcH;

        p = Oem_VideoStamp(u16OSDid, &rc, stRtcTime, u16DateCfg, u16FormatCfg, u16PositionCfg);

        pu32StickerX = p.PointX;
        pu32StickerY = p.PointY;
    }
    #else   // _OEM_VR_STICKER_
    {
        INT8    byDate[64];
        UINT32  uiPosX = 21*16;
        #if (UUID_XML_FEATURE == 1)
        char    szProductName[PRODUCT_NAME_MAX_SIZE] = {0};
        #endif

        MEMSET(byDate, 0, sizeof(byDate));
        AHC_STICKER_TransDateToString(pstRtcTime, byDate, u16DateCfg, u16FormatCfg);
        DrawVideo_GetTimeStampPosition( gsAhcPrmSensor,
                                        u16OSDid,
                                        u32TimeStampOp,
                                        pu32SrcAddr,
                                        pu16SrcW,
                                        pu16SrcH,
                                        pu16TempColorFmt,
                                        pu32StickerX,
                                        pu32StickerY);

        AHC_OSDSetBkColor(u16OSDid, GUI_TRANSPARENT);
        AHC_OSDSetColor(u16OSDid, GUI_BLACK);

        AHC_OSDDrawFillRect(u16OSDid, 0, 0, *pu16SrcW, *pu16SrcH);

        OldFont = AHC_OSDGetFont(u16OSDid);
        AHC_OSDSetFont(u16OSDid, &STICKER_FRONT_1);
        AHC_OSDSetColor(u16OSDid, GUI_WHITE);

        #if (STICKER_PATTERN == 1)
        AHC_OSDSetColor(u16OSDid, GUI_ORANGE);

        // DrawText of LOGO
        if (u32TimeStampOp & AHC_ACC_TIMESTAMP_LOGOEX_MASK)
        {
            #if (UUID_XML_FEATURE == 1)
            UI_GetProductName(szProductName, PRODUCT_NAME_MAX_SIZE);
            AHC_OSDDrawText(u16OSDid, (UINT8*)szProductName, uiPos, 0, STRLEN(szProductName));
            #else
            {
                UINT32 u32ModeNameAddr = 0;

                if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_STICKER_LOGO_TXT, &u32ModeNameAddr) == AHC_TRUE)
                {
                    AHC_OSDDrawText(u16OSDid, (UINT8 *)u32ModeNameAddr, uiPosX, 0, STRLEN((char *)u32ModeNameAddr));
                }
            }
            #endif
        }
        #endif  // #if (STICKER_PATTERN == 1)

        // DrawText of Date TimeStamp
        if (u32TimeStampOp & AHC_ACC_TIMESTAMP_DATEEX_MASK) {
            AHC_OSDDrawText(u16OSDid, (UINT8*)byDate, 0, 0, STRLEN(byDate));
        }
    }
    #endif // _OEM_VR_STICKER_

    #if (AHC_GPS_STICKER_ENABLE && SUPPORT_GPS)
    DrawVideo_GPSInfo(u16OSDid);
    #endif

    #if defined(INFO_ISP_MSG_ON_PNL)&&(INFO_ISP_MSG_ON_PNL)
    DrawVideo_ISPMsg(u16OSDid);
    #endif

    #if (STICKER_DRAW_EDGE)
    AHC_STICKER_DrawTextEdge(pu32SrcAddr, pu16SrcW, pu16SrcH, 0xFF, 0x00, 0x01);
    #endif

    AHC_OSDSetFont(u16OSDid, OldFont);

    AIHC_DrawReservedOSD(AHC_FALSE);

    END_LAYER(u16OSDid);

    //END_LAYER(OVL_BUFFER_INDEX); // TBD
    //END_LAYER(OVL_BUFFER_INDEX1);
#endif
}

void DrawVideoRecStateUpdate(void)
{
    UINT8    bID0 = 0;
    UINT8    bID1 = 0;
    static UINT8 m_VidDrawCounter   = 0;
    static UINT8 ubMediaStatus  = AHC_FALSE;
    static UINT8 ubLockStatus   = AHC_FALSE;
    static UINT8 ubMuteStatus   = AHC_FALSE;
    static UINT8 ubEmerStatus   = AHC_FALSE;
#if (DAY_NIGHT_MODE_SWITCH_EN)
    static UINT8 ubNightStatus  = AHC_FALSE;
#endif
#if (LIMIT_MAX_LOCK_FILE_NUM)
    static UINT8 ubLockFileNum  = 0;
    static UINT8 ubLockEventNum = 0;
#endif
#if (MOTION_DETECTION_EN)
    static UINT8 ubVMDStatus    = AHC_FALSE;
#endif

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1);//OSDDraw_GetOvlDrawBuffer(&bID0);

    #if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        if (AHC_FALSE == monoPatternDrawed) {
            UINT16 idx;

            printc(FG_BLUE("Draw Mono Patttern ...\r\n"));
            AHC_OSDSetBkColor(bID0, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
            OSDDraw_ClearPanel(bID0, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);

            #ifdef CFG_WIFI_STREAMING_LOGO_IN_CENETR
            // NOP - Do not draw all icons
            #else
            for (idx = 0; idx < VIDEO_GUI_MAX; idx++)
            {
                if (idx == VIDEO_GUI_REC_STATE)
                    UpdateVideoRecordStatus(VIDEO_REC_STOP);

                if ((idx == VIDEO_GUI_REC_POINT) || (idx == VIDEO_GUI_GPS_STATE))
                    continue;

                UIDrawEx(bID0, idx, AHC_TRUE, AHC_TRUE, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN, NULL_PARAM);
            }
            #endif

            monoPatternDrawed = AHC_TRUE;
        }

        #ifdef CFG_WIFI_STREAMING_LOGO_IN_CENETR
        // WiFi
        {
            int     status = nhw_get_status();
            /* be careful the enum VIDEO_GUI_BLOCK, the ORDER and NUMBER must be same in enum and UI_DARW_SET */
            UIDrawEx(bID0, VIDEO_GUI_WIFI, AHC_TRUE, AHC_TRUE, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN, status);
            UIDrawEx(bID0, VIDEO_GUI_WIFI_SWITCH, AHC_FALSE, AHC_TRUE, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN, status);
        }

        goto L_DrawExit;
        #endif
    }
    else if (AHC_TRUE == monoPatternDrawed) {
        DrawStateVideoRecInit();
        monoPatternDrawed = AHC_FALSE;
    }
    #endif

    #if (AUTO_HIDE_OSD_EN)
    if(VideoFunc_GetRecordStatus())
    {
        m_ulOSDCounter++;

        if(m_ulOSDCounter==VR_OSD_HIDE_TIME) //60sec
        {
            m_ubHideOSD = AHC_TRUE;
            #ifdef CFG_DRAW_WIFI_STREAMING_MONO_PATTERN
            if (AHC_Get_WiFi_Streaming_Status())
                OSDDraw_ClearPanel(bID0, CFG_DRAW_WIFI_STREAMING_MONO_PATTERN);
            else
            #endif
                OSDDraw_ClearPanel(bID0, OSD_COLOR_TRANSPARENT);

            goto L_DrawExit;
        }
        else if(m_ulOSDCounter > VR_OSD_HIDE_TIME)
        {
            DrawVideoRecOsdDuringHide(bID0);

            goto L_DrawExit;
        }
    }
    else
    {
        m_ulOSDCounter = 0;
    }

    #endif      // #if (AUTO_HIDE_OSD_EN)

    #if (VIDEO_DIGIT_ZOOM_EN)
    UIDrawEx(bID0, VIDEO_GUI_ZOOM_BAR, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, AHC_FALSE);
    #endif

    if(m_ubBatteryStatus != MenuSettingConfig()->uiBatteryVoltage)
    {
        UIDrawEx(bID0, VIDEO_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        m_ubBatteryStatus = MenuSettingConfig()->uiBatteryVoltage;
    }

    if(bUpdateFlashLedIcon)
    {
        UIDrawEx(bID0, VIDEO_GUI_FLASH, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        bUpdateFlashLedIcon = AHC_FALSE;
    }

    if(ubMediaStatus != AHC_SDMMC_IsSD1MountDCF())
    {
        UIDrawEx(bID0, VIDEO_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubMediaStatus = AHC_SDMMC_IsSD1MountDCF();
    }

    if(ubLockStatus != VideoFunc_LockFileEnabled())
    {
        UIDrawEx(bID0, VIDEO_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubLockStatus = !ubLockStatus;
    }

    #if 0
    if (ubEmerStatus != VideoFunc_IsShareRecordStarted())
    {
        UIDrawEx(bID0, VIDEO_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubEmerStatus = !ubEmerStatus;
    }
    #endif

    if(ubMuteStatus != bMuteRecord)
    {
        UIDrawEx(bID0, VIDEO_GUI_MUTE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubMuteStatus = bMuteRecord;
    }

    #if (LIMIT_MAX_LOCK_FILE_NUM)
    if(ubLockFileNum != m_ulLockFileNum)
    {
        UIDrawEx(bID0, VIDEO_GUI_LOCK_NUM, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubLockFileNum = m_ulLockFileNum;
    }

    if(ubLockEventNum != m_ulLockEventNum)
    {
        UIDrawEx(bID0, VIDEO_GUI_LOCK_NUM, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubLockEventNum = m_ulLockEventNum;
    }
    #endif

    #if (DAY_NIGHT_MODE_SWITCH_EN)
    if(ubNightStatus != bNightMode)
    {
        UIDrawEx(bID0, VIDEO_GUI_SCENE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        ubNightStatus = bNightMode;
    }
    #endif

    #if WIFI_PORT == 1
    if (!AHC_Get_WiFi_Streaming_Status())
    #endif
    if (m_eUiVideoRecResol != MenuSettingConfig()->uiMOVSize)
    {
        printc(">>>>>>>>[Video mode]MenuSettingConfig()->uiMOVSize = %d\r\n",MenuSettingConfig()->uiMOVSize);
        UIDrawEx(bID0, VIDEO_GUI_MOVIE_RES, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    #if (MOTION_DETECTION_EN)
    if(ubVMDStatus != m_ubMotionDtcEn)
    {
        #ifdef CFG_DRAW_REC_MOTION_SEN_OFF //may be defined in config_xxx.h
        if( MenuSettingConfig()->uiMotionDtcSensitivity == MOTION_DTC_SENSITIVITY_OFF)
        {
            UIDrawEx(bID0, VIDEO_GUI_VMD_STATE, AHC_TRUE, AHC_FALSE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            ubVMDStatus = AHC_FALSE;
        }
        else
        #endif
        {
            UIDrawEx(bID0, VIDEO_GUI_VMD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            ubVMDStatus = m_ubMotionDtcEn;
        }
    }
    #endif// #if (MOTION_DETECTION_EN)

    #ifdef CFG_DRAW_REC_UPDATE_LOCK_FILE //may be defined in config_xxx.h
    if(VideoFunc_GetRecordStatus() && VideoFunc_LockFileEnabled())
        UIDrawEx(bID0, VIDEO_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, m_VidDrawCounter);

    if (Gsensor_ReadDeviceID() != AHC_ERR_NONE)
    {
        UIDrawEx(bID0, VIDEO_GUI_REC_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, (m_VidDrawCounter & 0x01));
    }
    else
    {
        UIDrawEx(bID0, VIDEO_GUI_REC_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, 0);
    }
    #endif

    UIDrawEx(bID0, VIDEO_GUI_REC_POINT,    AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, 6);
    UIDrawEx(bID0, AUDIO_GUI_REC_POINT,    AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, 6);
    UIDrawEx(bID0, VIDEO_GUI_RTC_TIME,  AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, VIDEO_GUI_REC_TIME,  AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, VIDEO_GUI_REMAIN_TIME,   AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

#if (SUPPORT_GSENSOR)
    if (VideoFunc_GetRecordStatus() && (AHC_GetQuickKey(QUICK_UP) || dump_GValues_osd))
        Dump_Gsensor_XYZ(bID0);
#endif
#if (INFO_ISP_MSG_ON_PNL)
    Dump_ISP_MSG(bID0);
#endif

    #if (SW_STICKER_EN == 1)
    // NOP
    #else
    if (m_VidDrawCounter == 0)
    #endif
    {
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
            if (m_ubMotionDtcEn && m_ulVMDStableCnt == 0)
                m_ubVMDStart = AHC_TRUE;
        }
        #endif
        #if OSD_SHOW_BATTERY_STATUS == 1
        AHC_DrawChargingIcon_UsingTimer(bID0);
        #endif
    }

    #if (SUPPORT_GPS)
    if(bGPS_PageExist)
    {
        CHARGE_ICON_ENABLE(AHC_FALSE);
        QuickDrawGPSInfoPage(bID0, AHC_FALSE);
        QuickDrawGPSInfoPage(bID0, AHC_TRUE);
        CHARGE_ICON_ENABLE(AHC_TRUE);
    }
    else
    {
        #if GPS_MODULE_SHOW_OSD
        if (!GPSCtrl_ModuleConnected())
            UIDrawEx(bID0, VIDEO_GUI_GPS_STATE,    AHC_TRUE,  AHC_FALSE,   OSD_COLOR_TRANSPARENT, NULL_PARAM);
        else
            UIDrawEx(bID0, VIDEO_GUI_GPS_STATE,    AHC_TRUE,  AHC_TRUE,    OSD_COLOR_TRANSPARENT, NULL_PARAM);
        #endif
    }
    #endif

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    // WiFi
    #if (SUPPORT_GPS)
    if(!bGPS_PageExist)
    #endif
    {
        int status = nhw_get_status();
        /* be careful the enum VIDEO_GUI_BLOCK, the ORDER and NUMBER must be same in enum and UI_DARW_SET */
        UIDrawEx(bID0, VIDEO_GUI_WIFI, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, status);
        UIDrawEx(bID0, VIDEO_GUI_WIFI_SWITCH, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, status);
    }
    #endif

    goto L_DrawExit;//avoid warning C2866W label is not used
L_DrawExit:
    #if (ENABLE_ADAS_LDWS)
    // Draw LDWS line
    UIDrawEx(bID0, VIDEO_GUI_LDWS_LINE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    #endif

    #if (ENABLE_ADAS_FCWS)
    // Draw FCWS Distance
    UIDrawEx(bID0, VIDEO_GUI_FCWS_INFO, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    #endif
    OSDDraw_ExitDrawing(&bID0, &bID1);

    m_VidDrawCounter ^= 1;

    #ifdef CFG_SDMMC_ERROR_TURNON_REC_LED
    if (!VideoFunc_GetRecordStatus())
    {
        if(AHC_FALSE == AHC_SDMMC_IsSD1MountDCF())
        {
            LedCtrl_ButtonLed(AHC_GetVideoModeLedGPIOpin(), AHC_TRUE);
        }
        else
        {
            LedCtrl_ButtonLed(AHC_GetVideoModeLedGPIOpin(), AHC_FALSE);
        }
    }
    #endif

    #ifdef FLM_GPIO_NUM
    if (AHC_Get_WiFi_Streaming_Status())
    AHC_OSDRefresh_PLCD();
    #endif
}

#ifdef CFG_BOOT_CLEAR_ICON_WHEN_OFF //may be defined in config_xxx.h
            //If LCD gets poor quality, and icons is sticky
            //Need to clear icons
void DrawStateVideoRecClearIcon(void)
{
    UINT8   bID0 = 0;
    UINT8   bID1 = 0;
    UINT8   idx  = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if(uiGetCurrentState() == UI_HDMI_STATE)
    {
        printc("--E-- %s wrong enter for HDMI \r\n", __func__);
        return AHC_TRUE;
    }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
    //OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);

    AHC_OSDSetColor(bID0, 0xAA000000);

    for (idx = 0; idx < VIDEO_GUI_MAX; idx++)
    {
        if (idx == VIDEO_GUI_REC_STATE)
            UpdateVideoRecordStatus(VIDEO_REC_STOP);

        if ((idx == VIDEO_GUI_REC_POINT) || (idx == VIDEO_GUI_GPS_STATE))
            continue;

        UIDrawEx(bID0, idx, AHC_TRUE, AHC_FALSE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif
#if (ENABLE_ADAS_LDWS)
void DrawVideo_LDWSWarn(int ldws_state, AHC_BOOL bDraw)
{
    static UINT8 RecordPlaySound = 0x01;
    UINT8 bID0 = 0;
    UINT8 bID1 = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (!bDraw) { // Draw exit DrawVideo_LDWSWarn.
        printc("DrawVideo_LDWSWarn....exit\r\n");
        DrawStateVideoRecInit();
        RecordPlaySound = 0x01;
        return;
    }

    if (RecordPlaySound) {
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_ATTENTION);
        AHC_PlaySoundEffect(AHC_SOUNDEFFECT_LDWS_WARNING);
        RecordPlaySound = 0x00;
    }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    // Draw LDWS line
    UIDrawEx(bID0, VIDEO_GUI_LDWS_LINE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if (ENABLE_ADAS_FCWS)
void DrawVideo_FCWSWarn(int ldws_state, AHC_BOOL bDraw)
{
    UINT8 bID0 = 0;
    UINT8 bID1 = 0;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (!bDraw) { // Draw exit DrawVideo_FCWSWarn.
        printc("DrawVideo_FCWSWarn....exit\r\n");
        DrawStateVideoRecInit();
        //RecordPlaySound = 0x01;
        return;
    }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    UIDrawEx(bID0, VIDEO_GUI_FCWS_INFO, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}
#endif

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
void DrawVideoWiFi(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    static int          _cnt = 0;
    const GUI_BITMAP*   aicn[] = {&BMICON_WIFI_CONNECTED,       // Remote has connected
                                  &BMICON_WIFI_STREAMING_1,
                                  &BMICON_WIFI_STREAMING_2,
                                  &BMICON_WIFI_STREAMING_3, // in air
                                };
    const GUI_BITMAP*   pbmp;
    GUI_COLOR           IconColor = 0xAA000000;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    AHC_OSDSetBkColor(ubID, bkColor);
    AHC_OSDSetColor(ubID, IconColor);

#ifdef CFG_DRAW_WIFI_STREAMING_MONO_PATTERN
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
        AHC_OSDSetBkColor(ubID, bkColor);
    }
#endif

    // TODO: bLarge can be replaced by ubMag!!

    if (bLarge != LARGE_SIZE)
        ubMag = 1;

#ifdef CFG_WIFI_STREAMING_LOGO_IN_CENETR
    if (ns_get_streaming_status() & NETAPP_STREAM_PLAY) {
        x = (m_OSD[ubID]->width >> 1) - (aicn[0]->XSize * ubMag >> 1);
        y = (m_OSD[ubID]->height >> 1) - (aicn[0]->YSize * ubMag >> 1);
    }
#endif

    if (Para1 == NULL_PARAM  ||
        bFlag == AHC_FALSE) {
        // Clean Icon
        UINT16      x1;
        UINT16      y1;

        x1 = x + aicn[0]->XSize * ubMag;
        y1 = y + aicn[0]->YSize * ubMag;

        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, x, y, x1, y1);
        AHC_OSDSetColor(ubID, IconColor);
    }
    else
    {
        if ((WLAN_SYS_GetMode() == -1) && (NETAPP_NET_STATUS_INIT != Para1))
        {
            pbmp = &BMICON_WIFI_DISCONNECT;
        }
        else
        {
            if (ns_get_streaming_status() & NETAPP_STREAM_TEARDOWN || Para1 == NETAPP_NET_STATUS_READY)
            {
                // remote connected
                pbmp = &BMICON_WIFI_ON;
            }
            else if (ns_get_streaming_status() & NETAPP_STREAM_PLAY)
            {
                // rtsp in play state
                _cnt = (_cnt + 1) & 0x3;
                pbmp = aicn[_cnt];
            }
            else if (Para1 == NETAPP_NET_STATUS_INIT_FAIL)
            {
                pbmp = &BMICON_WIFI_ERROR;
            }
            else if (Para1 == NETAPP_NET_STATUS_IDLE)
            {
                // remote disconnect!!
                pbmp = &BMICON_WIFI_IDLE;
            }
            else if (Para1 == NETAPP_NET_STATUS_NOIP || NETAPP_NET_STATUS_INIT == Para1)
            {
                // Cannot get IP for DHCP server, or Crypto TYPE/KEY not match!!
                pbmp = &BMICON_WIFI_NO_IP;
            }
            else
            {
                pbmp = &BMICON_WIFI_FAIL;
            }
        }

        if(bLarge==LARGE_SIZE)
            AHC_OSDDrawBitmapMag(ubID, pbmp, x, y, ubMag, ubMag);
        else
            AHC_OSDDrawBitmap(ubID, pbmp, x, y);
    }
    END_LAYER(ubID);
}

void DrawVideoWiFiStreaming(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    const GUI_BITMAP*   aicn[] = {&BMICON_WIFI_STREAMING_OFF, &BMICON_WIFI_STREAMING_ON};
    const GUI_BITMAP*   pbmp;
    GUI_COLOR           IconColor = 0xAA000000;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

#if (defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_DRAW_WIFI_STREAMING_MONO_PATTERN))
    if (AHC_Get_WiFi_Streaming_Status()) {
        bkColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        IconColor = CFG_DRAW_WIFI_STREAMING_MONO_PATTERN;
        AHC_OSDSetColor(ubID, IconColor);
        AHC_OSDSetBkColor(ubID, bkColor);
    }
#endif

    // TODO: bLarge can be replaced by ubMag!!
    if (bLarge != LARGE_SIZE)
        ubMag = 1;

    if ((Para1 <= 0  ||
         Para1 == NETAPP_NET_STATUS_NOIP ||
         bFlag == AHC_FALSE) || (WLAN_SYS_GetMode()==-1)){
        // Clean Icon
        UINT16      x1;
        UINT16      y1;

        x1 = x + aicn[0]->XSize * ubMag;
        y1 = y + aicn[0]->YSize * ubMag;
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDSetBkColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, x, y, x1, y1);
        AHC_OSDSetColor(ubID, IconColor);
    }
    else
    {
        if(nhw_get_status()!=0)
        {
            if(AHC_Get_WiFi_Streaming_Status())
                pbmp = &BMICON_WIFI_STREAMING_ON;
            else
                pbmp = &BMICON_WIFI_STREAMING_OFF;

            if(bLarge==LARGE_SIZE)
                AHC_OSDDrawBitmapMag(ubID, pbmp, x, y, ubMag, ubMag);
            else
                AHC_OSDDrawBitmap(ubID, pbmp, x, y);


           OSDDraw_MainTouchButton(ubID, (VideoFunc_GetRecordStatus())?
                                    UI_VIDEO_RECORD_STATE : UI_VIDEO_STATE);

        }
        if (nhw_get_cur_wifi_mode() == 2 /*STA MODE*/) {
            #define N(p, m) (*(((unsigned char*)(&p)) + m))
            unsigned int    ip;
            UINT8   szip[16];
            GUI_RECT    rc;

            ip = nhw_get_ip_addr();
            snprintf((char*)szip, 16, "%u.%u.%u.%u", N(ip, 0), N(ip, 1), N(ip,2), N(ip, 3));
            AHC_OSDSetColor(ubID, OSD_COLOR_GREEN);
            AHC_OSDSetBkColor(ubID, bkColor);
            AHC_OSDSetPenSize(ubID, 1);
            AHC_OSDSetFont(ubID, &GUI_Font8_1);
            rc.x0 = 0;
            rc.x1 = RTNA_LCD_GetAttr()->usPanelW - 4;
            rc.y0 = y - 10;
            rc.y1 = y;
            AHC_OSDDrawTextInRect(ubID, (UINT8*)szip, &rc, GUI_TA_RIGHT|GUI_TA_VCENTER);
        }
    }

    END_LAYER(ubID);
}

#endif


void DrawRearCamReverseLine(AHC_BOOL bFlag)
{
    UINT8 bID0 = 0;
    UINT8 bID1 = 0;
    const GUI_BITMAP*   pbmp;

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

     if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    BEGIN_LAYER(bID0);
    AHC_OSDSetColor(bID0, 0xAAFF80FF);
    AHC_OSDSetBkColor(bID0, 0xAAFF80FF);
    if (bFlag == AHC_FALSE)
    {
        AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDSetBkColor(bID0, OSD_COLOR_TRANSPARENT);
        AHC_OSDDrawFillRect(bID0, 120, 80, m_OSD[bID0]->width, m_OSD[bID0]->height-128);
        AHC_OSDSetColor(bID0, 0xAA000000);
    }
    else
    {
        pbmp = &BMPICON_Reverse_LINE;
        AHC_OSDDrawBitmap(bID0, pbmp, 120, 80);
    }

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStateVideoRecUpdate(UINT32 ubEvent)
{

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_MODE                       :
        case EVENT_KEY_MENU                       :
        case EVENT_KEY_PLAYBACK_MODE              :
            DrawVideoRecInfo(AHC_TRUE);
        break;

        case EVENT_KEY_TELE_PRESS                 :
        case EVENT_KEY_WIDE_PRESS                 :
        case EVENT_KEY_WIDE_STOP                  :
        case EVENT_KEY_TELE_STOP                  :
        case EVENT_KEY_ZOOM_STATUS_CLEAR          :
            DrawVideoRecStateZoom();
        break;

        case EVENT_KEY_SET                        :
            #if 0//(HDMI_ENABLE || TVOUT_ENABLE) //Should not judge TV out or HDMI here.
            if(AHC_IsTVConnectEx())
            {
                UpdateVideoRecordStatus(VIDEO_REC_PAUSE);
                UIDrawEx(TVFunc_GetUImodeOsdID(), VIDEO_GUI_REC_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            }
            else if(AHC_IsHdmiConnect())
            {
                UpdateVideoRecordStatus(VIDEO_REC_PAUSE);
                UIDrawEx(HDMIFunc_GetUImodeOsdID(), VIDEO_GUI_REC_STATE, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
            }
            else
            #endif
            {
                DrawVideoRecStateRecord(VIDEO_REC_PAUSE);
            }
        break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);

            AHC_OSDSetFlipDrawMode(OVL_DISPLAY_BUFFER, OSD_FLIP_DRAW_NONE_ENABLE);
            DrawStateVideoRecInit();

            if(VideoFunc_GetRecordStatus())
            {
                UINT32  CurSysMode;

                AHC_GetSystemStatus(&CurSysMode);

                if((CurSysMode == ((AHC_MODE_VIDEO_RECORD<<16)|AHC_SYS_VIDRECD_PAUSE)))
                    DrawVideoRecStateRecord(VIDEO_REC_PAUSE);
                else
                    DrawVideoRecStateRecord(VIDEO_REC_START);
            }

            //AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
            DrawVideoRecInfo(AHC_FALSE);
        break;

        case EVENT_VIDEO_KEY_RECORD               :
            {
                DrawVideoRecStateRecord(VIDEO_REC_START);
            }
        break;

        case EVENT_VIDEO_KEY_RECORD_STOP          :
            {
                DrawVideoRecStateRecord(VIDEO_REC_STOP);
            }
        break;

        case EVENT_DSC_SET_EV   :
            DrawCaptureStateEV();
        break;

        case EVENT_VIDEO_KEY_CAPTURE:
            {
                DrawVideoRecStateRecord(VIDEO_REC_CAPTURE);
            }
        break;

        case EVENT_VIDREC_UPDATE_MESSAGE          :
            DrawVideoRecStateUpdate();
        break;

        case EVENT_TIMESTAMP_UPDATE:
            UpdateVideoCurrentTimeStamp(AHC_TRUE);
        break;

        case EVENT_GPSGSENSOR_UPDATE:
            DrawVideoRecStateGsensorInfo();
        break;

        default:
        break;
    }
}

void DrawVideoParkingMode( AHC_BOOL bEnable )
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    RECT   rtIconPosition = { 10, 4, 60, 20 };
    RECT   tvIconPosition = { 30 ,10, 150, 28 };

#if (DRAW_VID_FUNC_ENABLE == 0)
    return;
#endif

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    BEGIN_LAYER(bID0);

    if( bEnable == AHC_TRUE )
    {
        if(AHC_IsTVConnectEx())
        {
            AHC_OSDSetFont(bID0, &GUI_Font24B_ASCII);
            OSD_ShowString(bID0, (char*)"Parking", NULL, tvIconPosition, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_LEFT|GUI_TA_VCENTER);
        }
        else
        {
            AHC_OSDSetFont(bID0, &GUI_Font16B_1);
            OSD_ShowString(bID0, (char*)"Parking", NULL, rtIconPosition, OSD_COLOR_WHITE, OSD_COLOR_TRANSPARENT, GUI_TA_LEFT|GUI_TA_VCENTER);
        }
    }
    else
    {
        if(AHC_IsTVConnectEx())
        {
            AHC_OSDSetColor( bID0, OSD_COLOR_TRANSPARENT );
            AHC_OSDSetBkColor( bID0, OSD_COLOR_TRANSPARENT );
            AHC_OSDDrawFillRect(bID0, tvIconPosition.uiLeft, tvIconPosition.uiTop, tvIconPosition.uiLeft+tvIconPosition.uiWidth, tvIconPosition.uiTop+tvIconPosition.uiHeight);
        }
        else
        {
            AHC_OSDSetColor( bID0, OSD_COLOR_TRANSPARENT );
            AHC_OSDSetBkColor( bID0, OSD_COLOR_TRANSPARENT );
            AHC_OSDDrawFillRect(bID0, rtIconPosition.uiLeft, rtIconPosition.uiTop, rtIconPosition.uiLeft+rtIconPosition.uiWidth, rtIconPosition.uiTop+rtIconPosition.uiHeight);
        }
    }

    END_LAYER(bID0);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

void DrawVideoRecStateGsensorInfo(void)
{
    UINT8 bID0 = 0;
    UINT8 bID1 = 0;
    char strGsnrInfo[32];
    GUI_RECT rc = {30, 100, 230, 130};
    AHC_GSENSOR_DATA tGsnrData = {{0, 0, 0}};
    GUI_COLOR OldColor;
    const GUI_FONT* pOldFont;

    if (AHC_Gsensor_Read_XYZ(&tGsnrData) == AHC_FALSE) {
        goto ERR_EXIT;
    }

    OSDDraw_EnterDrawing(&bID0, &bID1); // OSDDraw_GetOvlDrawBuffer(&bID0);

    OldColor = AHC_OSDGetColor(bID0);
    AHC_OSDSetColor(bID0, GUI_YELLOW);
    pOldFont = AHC_OSDSetFont(bID0, GUI_FONT_16B_ASCII);

    sprintf(strGsnrInfo, "x:%d y:%d z:%d", tGsnrData.acc_val[0], tGsnrData.acc_val[1], tGsnrData.acc_val[2]);
    AHC_OSDClearRect(bID0, rc.x0, rc.y0, rc.x1, rc.y1);
    AHC_OSDDrawTextInRect(bID0, (UINT8*)strGsnrInfo, &rc, GUI_TA_LEFT | GUI_TA_CENTER);

    AHC_OSDSetColor(bID0, OldColor);
    AHC_OSDSetFont(bID0, pOldFont);

    OSDDraw_ExitDrawing(&bID0, &bID1);

ERR_EXIT:
    return;
}
