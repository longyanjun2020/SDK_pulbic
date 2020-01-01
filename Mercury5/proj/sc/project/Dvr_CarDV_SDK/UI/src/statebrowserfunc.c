/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_sensor.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_browser.h"
#include "ahc_menu.h"
#include "ahc_media.h"
#include "ahc_fs.h"
#include "ahc_warningmsg.h"
#include "ahc_usb.h"
#include "ahc_general_cardv.h"
#include "keyparser.h"
#include "statebrowserfunc.h"
#include "statephotopbfunc.h"
#include "statemoviepbfunc.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "ui_drawgeneral.h"
#include "drawstatebrowserfunc.h"
#include "drawstatetvfunc.h"
#include "drawstatehdmifunc.h"
#include "MenuCommon.h"
#include "MenuSetting.h"
#include "MenuDrawingFunc.h"
#include "MenuTouchButton.h"
#include "MenuDrawCommon.h"
#include "ledcontrol.h"
#include "lcd_common.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "dsc_charger.h"
#include "mediaplaybackctrl.h"
#include "MenuStatePlaybackMenu.h"
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#endif
#include "ait_utility.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

/*===========================================================================
 * Global varible
 *===========================================================================*/


UINT32      ObjSelect           = 0;
AHC_BOOL bRefreshBrowser        = AHC_FALSE;
static AHC_THUMB_CFG        m_ThumbConfig;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL bForce_PowerOff;
extern AHC_BOOL Delete_File_Confirm;
extern AHC_BOOL Deleting_InBrowser;
extern AHC_BOOL Delete_Option;
extern AHC_BOOL Protect_File_Confirm;
extern AHC_BOOL Protecting_InBrowser;
extern AHC_BOOL Protect_Option;
extern AHC_BOOL UnProtect_File_Confirm;
extern AHC_BOOL UnProtect_Option;
extern AHC_BOOL m_ubPlaybackRearCam;
extern AHC_BOOL bPreviewModeHDMI; //Andy Liu. Remove it later.
extern AHC_BOOL bShowHdmiWMSG; //Andy Liu. Remove it later.
extern AHC_BOOL gbAhcDbgBrk;
extern UINT32 m_ulDrawingThumbOSD;

/*===========================================================================
 * Main body
 *===========================================================================*/

void BrowserFunc_CheckLCDstatus(void)
{
//  UINT8           status;
//  AHC_THUMB_CFG   ThumbConfig;
//
//  AHC_LCD_GetStatus(&status);
//
//  AHC_SetKitDirection(status, AHC_TRUE, AHC_SNR_NOFLIP, AHC_FALSE);
//
//  ThumbConfig.uwTHMPerLine    = THUMB_PER_LINE;
//  ThumbConfig.uwTHMPerColume  = THUMB_PER_COLUMN;
//  ThumbConfig.uwHGap          = THUMB_HORIZ_GAP;
//  ThumbConfig.uwVGap          = THUMB_VERTIC_GAP;
//  ThumbConfig.byBkColor       = 0x101010;
//  ThumbConfig.byFocusColor    = 0x0000FF;
//  ThumbConfig.StartX          = POS_THUMB_AREA_X0;
//  ThumbConfig.StartY          = POS_THUMB_AREA_Y0;
//  ThumbConfig.DisplayWidth    = POS_THUMB_AREA_W;
//  ThumbConfig.DisplayHeight   = POS_THUMB_AREA_H;
//
//  AHC_Thumb_SetConfig(&ThumbConfig, AHC_TRUE);
}

void BrowserFunc_LCDSetting(void)
{
    UINT32      MaxDcfObj = 0;
    UINT8       status;
    UINT16      u16OsdW, u16OsdH;

    AHC_LCD_GetStatus(&status);
    AHC_SetKitDirection(status, AHC_TRUE, AHC_SNR_NOFLIP, AHC_FALSE);

    m_ThumbConfig.uwTHMPerColume    = THUMB_PER_COLUMN;
    m_ThumbConfig.byBkColor         = OSD_THUMB_BACKGROUND; // for RGB overlay window do "focus" BkColor.
    m_ThumbConfig.byFocusColor      = 0x0000FF;
    m_ThumbConfig.u32DispStartX     = POS_THUMB_AREA_X0;
    m_ThumbConfig.u32DispStartY     = POS_THUMB_AREA_Y0;
    m_ThumbConfig.uwHGap            = THUMB_HORIZ_GAP;
    m_ThumbConfig.uwVGap            = THUMB_VERTIC_GAP;

    u16OsdW = AHC_GET_ATTR_OSD_W(m_ulDrawingThumbOSD);
    u16OsdH = AHC_GET_ATTR_OSD_H(m_ulDrawingThumbOSD);

    if (u16OsdW >= 1280) {
        m_ThumbConfig.uwTHMPerLine  = 4;
        m_ThumbConfig.u32DispAreaW  = POS_THUMB_AREA_W;
        m_ThumbConfig.u32DispAreaH  = POS_THUMB_AREA_H;
    }
    else if (u16OsdW >= 854) {
        m_ThumbConfig.uwTHMPerLine  = THUMB_PER_LINE;
        m_ThumbConfig.u32DispAreaW  = POS_THUMB_AREA_W;
        m_ThumbConfig.u32DispAreaH  = POS_THUMB_AREA_H;
    }
    else {
        m_ThumbConfig.uwTHMPerLine  = 2;
        m_ThumbConfig.u32DispAreaW  = STRETCH_W(260);
        m_ThumbConfig.u32DispAreaH  = STRETCH_H(160);
    }

    AHC_Thumb_SetConfig(&m_ThumbConfig, AHC_TRUE);

    if (JPGPB_MODE == GetCurrentOpMode())
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    }
    else if (MOVPB_MODE == GetCurrentOpMode())
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    }
    else if (JPGPB_MOVPB_MODE == GetCurrentOpMode())
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
    }

    if (MaxDcfObj == 0)
    {
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_FILE_IN_BROWSER, 2);

        #if (UVC_HOST_VIDEO_ENABLE)
        AHC_OS_SleepMs(1000);
        #endif
    }
    else
    {
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }

        AHC_UF_GetCurrentIndex(&ObjSelect);

        if (ObjSelect > MaxDcfObj - 1)
            ObjSelect = MaxDcfObj - 1;

        #ifdef CFG_BROWSER_ALWAYS_SELECT_LAST //may be defined in config_xxx.h
        ObjSelect = MaxDcfObj - 1;
        #endif

        AHC_UF_SetCurrentIndex(ObjSelect);

        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }
    }
}

void BrowserFunc_HDMISetting(void)
{
    UINT32 MaxDcfObj;
    UINT16 uwWidth, uwHeight;
    AHC_DISPLAY_HDMIOUTPUTMODE HdmiMode;
    UINT32      iVal[2] = {0};

    AHC_GetHdmiDisplayWidthHeight(&uwWidth, &uwHeight);
    AHC_GetHDMIOutputMode(&HdmiMode);

    m_ThumbConfig.uwTHMPerLine    = 4;
    m_ThumbConfig.uwTHMPerColume  = 3;
    m_ThumbConfig.uwHGap          = 12;
    m_ThumbConfig.uwVGap          = 12;
    m_ThumbConfig.byBkColor       = 0x101010;
    m_ThumbConfig.byFocusColor    = 0x0000FF;

    switch(MenuSettingConfig()->uiHDMIOutput)
    {
    case HDMI_OUTPUT_1080I:
        m_ThumbConfig.u32DispStartX          = 50;
        m_ThumbConfig.u32DispStartY          = 30;
        break;
    case HDMI_OUTPUT_720P:
        m_ThumbConfig.u32DispStartX          = 30;
        m_ThumbConfig.u32DispStartY          = 20;
        break;
    case HDMI_OUTPUT_480P:
        m_ThumbConfig.u32DispStartX          = 30;
        m_ThumbConfig.u32DispStartY          = 20;
        break;
    default:
    case HDMI_OUTPUT_1080P:
        m_ThumbConfig.u32DispStartX          = 50;
        m_ThumbConfig.u32DispStartY          = 30;
        break;
    }

    switch(HdmiMode)
    {
        case AHC_DISPLAY_HDMIOUTPUT_1920X1080P:
            m_ThumbConfig.u32DispAreaW    = uwWidth - m_ThumbConfig.u32DispStartX - 40;
            m_ThumbConfig.u32DispAreaH   = uwHeight - POS_HDMI_1080P_BROWSER_OSD_H - 50;
            break;
        case AHC_DISPLAY_HDMIOUTPUT_1920X1080I:
            m_ThumbConfig.u32DispAreaW    = uwWidth - m_ThumbConfig.u32DispStartX - 40;
            m_ThumbConfig.u32DispAreaH   = (uwHeight<<1) - POS_HDMI_1080I_BROWSER_OSD_H - 50;
            break;
        case AHC_DISPLAY_HDMIOUTPUT_1280X720P:
            m_ThumbConfig.u32DispAreaW    = uwWidth  - m_ThumbConfig.u32DispStartX - 30;
            m_ThumbConfig.u32DispAreaH   = uwHeight - POS_HDMI_720P_BROWSER_OSD_H - 30;
            break;
        case AHC_DISPLAY_HDMIOUTPUT_720X480P:   // TBD
            m_ThumbConfig.u32DispAreaW    = uwWidth  - m_ThumbConfig.u32DispStartX - 30;
            m_ThumbConfig.u32DispAreaH   = uwHeight - POS_HDMI_480P_BROWSER_OSD_H - 20;
            break;
        case AHC_DISPLAY_HDMIOUTPUT_640X480P:  //TBD
        case AHC_DISPLAY_HDMIOUTPUT_720X576P:
        case AHC_DISPLAY_HDMIOUTPUT_1280X720P_50FPS:
        case AHC_DISPLAY_HDMIOUTPUT_1920X1080P_30FPS:
        default:
            printc("BrowserFunc_HDMISetting Error!!\r\n");
            break;
    }

    AHC_Thumb_SetConfig(&m_ThumbConfig, AHC_FALSE);

    if(GetCurrentOpMode()==MOVPB_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    else if(GetCurrentOpMode()==JPGPB_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);

    if (0 == MaxDcfObj) {
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_FILE_IN_BROWSER, 2);
        #if UVC_HOST_VIDEO_ENABLE
        AHC_OS_SleepMs(1000);
        #endif
    }
    else {
        if( ObjSelect > MaxDcfObj - 1)
            ObjSelect = MaxDcfObj - 1;
    }

    switch(MenuSettingConfig()->uiHDMIOutput)
    {
        case HDMI_OUTPUT_1080I:
            iVal[1] = POS_HDMI_1080I_BROWSER_OSD_H>>1;
            break;
        case HDMI_OUTPUT_720P:
            iVal[1] = POS_HDMI_720P_BROWSER_OSD_H;
            break;
        case HDMI_OUTPUT_480P:  // TBD
            iVal[1] = POS_HDMI_480P_BROWSER_OSD_H;
            break;
        default:
        case HDMI_OUTPUT_1080P:
            iVal[1] = POS_HDMI_1080P_BROWSER_OSD_H;
            break;
    }

    AIHC_DrawReservedOSD(AHC_TRUE);
    AHC_OSDSetDisplayAttr(THUMBNAIL_OSD_BACK_ID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);
    AHC_OSDSetCurrentDisplay(THUMBNAIL_OSD_BACK_ID);

    AHC_OSDSetDisplayAttr(THUMBNAIL_OSD_FRONT_ID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);
    AHC_OSDSetCurrentDisplay(THUMBNAIL_OSD_FRONT_ID);
    AIHC_DrawReservedOSD(AHC_FALSE);
}

void BrowserFunc_TVSetting(void)
{
    UINT32 MaxDcfObj;
    UINT16 uwWidth, uwHeight;
    UINT32      iVal[2] = {0};

    m_ThumbConfig.uwTHMPerLine    = 4;
    m_ThumbConfig.uwTHMPerColume  = 3;
    m_ThumbConfig.uwHGap          = 15;
    m_ThumbConfig.uwVGap          = 15;
    m_ThumbConfig.byBkColor       = 0x101010;
    m_ThumbConfig.byFocusColor    = 0x404090;

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_NTSC:
            m_ThumbConfig.u32DispStartX          = 20;
            m_ThumbConfig.u32DispStartY          = 20;

            AHC_GetNtscTvDisplayWidthHeight(&uwWidth, &uwHeight);
            m_ThumbConfig.u32DispAreaW    = uwWidth  - m_ThumbConfig.u32DispStartX - 30;
            m_ThumbConfig.u32DispAreaH   = uwHeight - POS_TV_NTSC_BROWSER_OSD_H - 45;
        break;
        case TV_SYSTEM_PAL:
            m_ThumbConfig.u32DispStartX          = 48;
            m_ThumbConfig.u32DispStartY          = 30;//65;

            AHC_GetPalTvDisplayWidthHeight(&uwWidth, &uwHeight);
            m_ThumbConfig.u32DispAreaW    = uwWidth  - m_ThumbConfig.u32DispStartX - 34;
            m_ThumbConfig.u32DispAreaH   = uwHeight - POS_TV_PAL_BROWSER_OSD_H - 58;
        break;
    }

    AHC_Thumb_SetConfig(&m_ThumbConfig, AHC_FALSE);

    if(GetCurrentOpMode()==MOVPB_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    else if(GetCurrentOpMode()==JPGPB_MODE)
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    else if(GetCurrentOpMode()==JPGPB_MOVPB_MODE)
            MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);

    if(MaxDcfObj==0) {
        AHC_WMSG_Draw(AHC_TRUE, WMSG_NO_FILE_IN_BROWSER, 2);
        #if UVC_HOST_VIDEO_ENABLE
        AHC_OS_SleepMs(1000);
        #endif
    } else {
        if( ObjSelect > MaxDcfObj - 1)
            ObjSelect = MaxDcfObj - 1;
    }

    switch(MenuSettingConfig()->uiTVSystem)
    {
        case TV_SYSTEM_NTSC:
            iVal[1] = POS_TV_NTSC_BROWSER_OSD_H;
        break;
        case TV_SYSTEM_PAL:
            iVal[1] = POS_TV_PAL_BROWSER_OSD_H;
        break;
        default:
            printc("BrowserFunc_TVSetting Error!!\r\n");
        break;
    }

    AIHC_DrawReservedOSD(AHC_TRUE);
    AHC_OSDSetDisplayAttr(THUMBNAIL_OSD_BACK_ID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);
    AHC_OSDSetCurrentDisplay(THUMBNAIL_OSD_BACK_ID);

    AHC_OSDSetDisplayAttr(THUMBNAIL_OSD_FRONT_ID, AHC_OSD_ATTR_DISPLAY_OFFSET, iVal);
    AHC_OSDSetCurrentDisplay(THUMBNAIL_OSD_FRONT_ID);
    AIHC_DrawReservedOSD(AHC_FALSE);

}

void BrowserFunc_DisplaySetting(void)
{
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){
        BrowserFunc_TVSetting();
    }else
#endif
#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){
        BrowserFunc_HDMISetting();
    }else
#endif
    {
        BrowserFunc_LCDSetting();
    }
}

AHC_BOOL BrowserFunc_ModeSwitch(void)
{
    AHC_BOOL  ahc_ret = AHC_TRUE;

    if(MOVPB_MODE == GetCurrentOpMode())
    {
        MenuStatePlaybackSelectDB( JPGPB_MODE );
        SetCurrentOpMode(JPGPB_MODE);
    }
    else if(JPGPB_MODE == GetCurrentOpMode())
    {
        MenuStatePlaybackSelectDB( MOVPB_MODE );
        SetCurrentOpMode(MOVPB_MODE);
    }
    else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
    {
        MenuStatePlaybackSelectDB( JPGPB_MOVPB_MODE );
        SetCurrentOpMode(JPGPB_MOVPB_MODE);
    }
    else
    {
        SetCurrentOpMode(JPGPB_MODE);
    }

    #if (FOCUS_ON_LATEST_FILE)
    if(!Deleting_InBrowser && !Protecting_InBrowser)
        AHC_SetPlayFileOrder(PLAY_LAST_FILE);
    #endif

    BrowserFunc_DisplaySetting();
    //BrowserFunc_CheckLCDstatus();
    StateSwitchMode(UI_BROWSER_STATE);

    return ahc_ret;
}

AHC_BOOL BrowserFunc_LCDThumbnailOption(UINT8 Op)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    if(!AHC_CheckCurSysMode(AHC_MODE_THUMB_BROWSER))
        return AHC_FALSE;

    switch(Op)
    {
        case BROWSER_UP:
            ahc_ret = AHC_Thumb_Rewind(m_ThumbConfig.uwTHMPerLine);
        break;

        case BROWSER_DOWN:
            ahc_ret = AHC_Thumb_Forward(m_ThumbConfig.uwTHMPerLine);
        break;

        case BROWSER_LEFT:
            ahc_ret = AHC_Thumb_Rewind(1);
        break;

        case BROWSER_RIGHT:
            ahc_ret = AHC_Thumb_Forward(1);
        break;

        case BROWSER_PLAY:
            {
                UINT32              CurDcfIdx;
                UINT8               FileType;
                if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                    AHC_UF_SetRearCamPathFlag(AHC_TRUE);
                }
                AHC_UF_GetCurrentIndex(&CurDcfIdx);
                AHC_UF_GetFileTypebyIndex(CurDcfIdx, &FileType);
                if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
                    AHC_UF_SetRearCamPathFlag(AHC_FALSE);
                }
                if ( ( FileType == DCF_OBG_MP3 ) ||
                     ( FileType == DCF_OBG_WAV ) ||
                     ( FileType == DCF_OBG_OGG ) ||
                     ( FileType == DCF_OBG_WMA ) )

                SetCurrentOpMode(AUDPB_MODE);
            }

        ahc_ret = StateSwitchMode(UI_PLAYBACK_STATE);
        break;

        case BROWSER_PAGEUP:
            ahc_ret = AHC_Thumb_RewindPage();
        break;

        case BROWSER_PAGEDOWN:
            ahc_ret = AHC_Thumb_ForwardPage();
        break;

        default:
        break;
    }
    return ahc_ret;
}

AHC_BOOL BrowserFunc_HDMIThumbnailOption(UINT8 ubOp)
{
#if (HDMI_ENABLE)

    AHC_BOOL ahc_ret = AHC_TRUE;
//
//  switch(ubOp)
//  {
//      case BROWSER_UP:
//          ahc_ret = AHC_Thumb_Rewind(m_ThumbConfig.uwTHMPerLine);
//      break;
//
//      case BROWSER_DOWN:
//          ahc_ret = AHC_Thumb_Forward(m_ThumbConfig.uwTHMPerLine);
//      break;
//
//      case BROWSER_LEFT:
//          ahc_ret = AHC_Thumb_Rewind(1);
//      break;
//
//      case BROWSER_RIGHT:
//          ahc_ret = AHC_Thumb_Forward(1);
//      break;
//
//      case BROWSER_PLAY:
//          ahc_ret = HDMIFunc_ThumbnailPlayback();
//      break;
//
//      case BROWSER_PAGEUP:
//          ahc_ret = AHC_Thumb_RewindPage();
//      break;
//
//      case BROWSER_PAGEDOWN:
//          ahc_ret = AHC_Thumb_ForwardPage();
//      break;
//
//      default:
//      break;
//  }
    return ahc_ret;
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL BrowserFunc_TVThumbnailOption(UINT8 ubOp)
{
#if (TVOUT_ENABLE)

    AHC_BOOL ahc_ret = AHC_TRUE;

//  switch(ubOp)
//  {
//      case BROWSER_UP:
//          ahc_ret = AHC_Thumb_Rewind(m_ThumbConfig.uwTHMPerLine);
//      break;
//
//      case BROWSER_DOWN:
//          ahc_ret = AHC_Thumb_Forward(m_ThumbConfig.uwTHMPerLine);
//      break;
//
//      case BROWSER_LEFT:
//          ahc_ret = AHC_Thumb_Rewind(1);
//      break;
//
//      case BROWSER_RIGHT:
//          ahc_ret = AHC_Thumb_Forward(1);
//      break;
//
//      case BROWSER_PLAY:
//          ahc_ret = TVFunc_ThumbnailPlayback();
//      break;
//
//      case BROWSER_PAGEUP:
//          ahc_ret = AHC_Thumb_RewindPage();
//      break;
//
//      case BROWSER_PAGEDOWN:
//          ahc_ret = AHC_Thumb_ForwardPage();
//      break;
//
//      default:
//
//      break;
//  }
    return ahc_ret;
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL BrowserFunc_ThumbnailOption(UINT8 Op)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = BrowserFunc_LCDThumbnailOption(Op);
    return ahc_ret;
}

AHC_BOOL BrowserFunc_ThumbnailResetVarible(UINT8 EditOp)
{
    switch(EditOp)
    {
        case EDIT_OP_DELETE:
            Delete_File_Confirm     = 0;
            Deleting_InBrowser      = 0;
            Delete_Option           = CONFIRM_NOT_YET;
        break;
        case EDIT_OP_PROTECT:
            Protect_File_Confirm    = 0;
            Protecting_InBrowser    = 0;
            Protect_Option          = CONFIRM_NOT_YET;
        break;
        case EDIT_OP_UNPROTECT:
            UnProtect_File_Confirm  = 0;
            Protecting_InBrowser    = 0;
            UnProtect_Option        = CONFIRM_NOT_YET;
        break;
        default:
        break;
    }
    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailResetAllEditOp(void)
{
    BrowserFunc_ThumbnailResetVarible(EDIT_OP_DELETE);
    BrowserFunc_ThumbnailResetVarible(EDIT_OP_PROTECT);
    BrowserFunc_ThumbnailResetVarible(EDIT_OP_UNPROTECT);
    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailEditFilelUpdatePage(void)
{
    if(AHC_IsTVConnectEx())
    {
        #if (TVOUT_ENABLE)
        DrawBrowserStatePageUpdate();//DrawStateTVBrowserPageUpdate();
        #endif
    }
    else if(AHC_IsHdmiConnect())
    {
        #if (HDMI_ENABLE)
        DrawBrowserStatePageUpdate();   //DrawStateHdmiBrowserPageUpdate();
        #endif
    }
    else
    {
        DrawBrowserStatePageUpdate();
    }
    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailEditFilelComplete(void)
{
    UINT16 osdW;
    UINT16 osdH;

    BrowserFunc_ThumbnailResetAllEditOp();

#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_WITH_CONFIRM) // TBD
    AHC_OSDSetColor(OVL_BUFFER_INDEX, OSD_COLOR_TRANSPARENT);
    osdW = AHC_GET_ATTR_OSD_W(OVL_BUFFER_INDEX);
    osdH = AHC_GET_ATTR_OSD_H(OVL_BUFFER_INDEX);
    AHC_OSDDrawFillRect(OVL_BUFFER_INDEX,    0, 40, osdW, osdH - 40);
    #if (OVL_BUFFER_INDEX1 != OVL_BUFFER_INDEX)
    AHC_OSDSetColor(OVL_BUFFER_INDEX1, OSD_COLOR_TRANSPARENT);
    osdW = AHC_GET_ATTR_OSD_W(OVL_BUFFER_INDEX1);
    osdH = AHC_GET_ATTR_OSD_H(OVL_BUFFER_INDEX1);
    AHC_OSDDrawFillRect(OVL_BUFFER_INDEX1,   0, 40, osdW, osdH - 40);
    #endif
#endif

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

#if (SUPPORT_TOUCH_PANEL)
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&Browser_TouchButton[0], ITEMNUM(Browser_TouchButton));
#endif

    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailEditFile(UINT8 Op)
{
    UINT8 ret;

    ret = QuickFileOperation(Op);

    if(ret!=EDIT_FILE_SUCCESS)
    {
        printc("Edit File ERROR!!!%d\r\n", ret);
        DrawFileOperationResult(ret);

        return AHC_FALSE;
    }
    else
    {
        printc("Edit File Complete!\r\n");
        //DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_SUB_MODE_EXIT)
        //redraw in other place.
        //AHC_Thumb_DrawPage(AHC_TRUE);
    }
    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailEditCheckFileObj(void)
{
    UINT32 MaxDcfObj = 0;

    if(MOVPB_MODE == GetCurrentOpMode())
        MaxDcfObj = AHC_GetMappingFileNum(FILE_MOVIE);
    else if(JPGPB_MODE == GetCurrentOpMode())
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO);
    else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);
    else{
        printc("%s:GetCurrentOpMode need TODO!---lei.qin\r\n",__func__);
    }

    if(!AHC_IsSDInserted() && MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD)
    {
        BrowserFunc_ThumbnailResetAllEditOp();
    }
    else if(MaxDcfObj == 0)
    {
        MaxDcfObj = AHC_GetMappingFileNum(FILE_PHOTO_MOVIE);

        if(MaxDcfObj==0) // No File In Movie/Photo Browser.
        {
            BrowserFunc_ThumbnailResetAllEditOp();
            //bForceSwitchBrowser = AHC_TRUE;
        }

        if(MOVPB_MODE == GetCurrentOpMode())
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
        else if(JPGPB_MODE == GetCurrentOpMode())
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO);
        else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_PHOTO_MOVIE);
        else
            AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) SEARCH_MOVIE);
    }

    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_ThumbnailEditFile_Option(UINT32 ulEvent)
{
    UINT32 MaxDcfObj;
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
    }
    AHC_UF_GetTotalFileCount(&MaxDcfObj);
    if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }
    if(MaxDcfObj == 0)
    {
        //BrowserFunc_ThumbnailResetAllEditOp();
        printc("No Files in Browser\r\n");
        return AHC_TRUE;
    }

    if(ulEvent==EVENT_KEY_LEFT)
    {
        if(Deleting_InBrowser)
        {
            if(Delete_File_Confirm)
            {
                Delete_Option = CONFIRM_OPT_YES;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur Delete_Option YES\r\n");
            }
            else
            {
                if(AHC_IsTVConnectEx())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);//TVFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateTVBrowserUpdate(ulEvent);
                }
                else if(AHC_IsHdmiConnect())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);//HDMIFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateHdmiBrowserUpdate(ulEvent);
                }
                else
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);
                }
            }
        }
        else if(Protecting_InBrowser)
        {
            if(Protect_File_Confirm && Protecting_InBrowser==1)
            {
                Protect_Option = CONFIRM_OPT_YES;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur Protect_Option YES\r\n");
            }
            else if(UnProtect_File_Confirm && Protecting_InBrowser==2)
            {
                UnProtect_Option = CONFIRM_OPT_YES;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur UnProtect_Option YES\r\n");
            }
            else
            {
                if(AHC_IsTVConnectEx())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);//TVFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateTVBrowserUpdate(ulEvent);
                }
                else if(AHC_IsHdmiConnect())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);//HDMIFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateHdmiBrowserUpdate(ulEvent);
                }
                else
                {
                    BrowserFunc_ThumbnailOption(BROWSER_LEFT);
                    DrawStateBrowserUpdate(ulEvent);
                }
            }
        }
    }
    else if(ulEvent==EVENT_KEY_RIGHT)
    {
        if(Deleting_InBrowser)
        {
            if(Delete_File_Confirm)
            {
                Delete_Option = CONFIRM_OPT_NO;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur Delete_Option NO\r\n");
            }
            else
            {
                if(AHC_IsTVConnectEx())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);//TVFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateTVBrowserUpdate(ulEvent);
                }
                else if(AHC_IsHdmiConnect())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);//HDMIFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateHdmiBrowserUpdate(ulEvent);
                }
                else
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);
                }
            }
        }
        else if(Protecting_InBrowser)
        {
            if(Protect_File_Confirm && Protecting_InBrowser==1)
            {
                Protect_Option = CONFIRM_OPT_NO;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur Protect_Option NO\r\n");
            }
            else if(UnProtect_File_Confirm && Protecting_InBrowser==2)
            {
                UnProtect_Option = CONFIRM_OPT_NO;
                MenuDrawChangeSubItem_EditOneFile();
                printc("Cur UnProtect_Option NO\r\n");
            }
            else
            {
                if(AHC_IsTVConnectEx())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);//TVFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateTVBrowserUpdate(ulEvent);
                }
                else if(AHC_IsHdmiConnect())
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);//HDMIFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);//DrawStateHdmiBrowserUpdate(ulEvent);
                }
                else
                {
                    BrowserFunc_ThumbnailOption(BROWSER_RIGHT);
                    DrawStateBrowserUpdate(ulEvent);
                }
            }
        }
    }
    else if(ulEvent==EVENT_THUMBNAIL_KEY_PLAYBACK   ||
            ulEvent==EVENT_TV_BROWSER_KEY_PLAYBACK  ||
            ulEvent==EVENT_HDMI_BROWSER_KEY_PLAYBACK)
    {

        if(Deleting_InBrowser)
        {
            printc("OK:Cur Delete_Option[%d]\r\n",Delete_Option);

            if(Delete_Option == CONFIRM_NOT_YET)
            {
                MenuDrawSubPage_EditOneFile(NULL);
            }
            else
            {
                if(Delete_Option == CONFIRM_OPT_YES)
                {
                    BrowserFunc_ThumbnailEditFile(DCF_FILE_DELETE_ALL_CAM);
                }
                else if(Delete_Option == CONFIRM_OPT_NO)
                {
                    BrowserFunc_ThumbnailEditFilelComplete();
                }
                #if (MENU_EDIT_CONTINUOUSLY)
                // delete continuously
                AHC_UF_GetCurrentIndex(&ObjSelect);
                Delete_Option        = CONFIRM_NOT_YET;
                Deleting_InBrowser   = 1;
                Delete_File_Confirm  = 0;
                #endif
                BrowserFunc_ThumbnailEditFilelUpdatePage();
            }
        }
        else if(Protecting_InBrowser)
        {
            if(Protecting_InBrowser==1)
            {
                printc("OK:Cur Protect_Option[%d]\r\n",Protect_Option);

                if(Protect_Option == CONFIRM_NOT_YET)
                {
                    MenuDrawSubPage_EditOneFile(NULL);
                }
                else
                {
                    if(Protect_Option == CONFIRM_OPT_YES)
                    {
                        BrowserFunc_ThumbnailEditFile(DCF_FILE_READ_ONLY_ALL_CAM);
                    }
                    else if(Protect_Option == CONFIRM_OPT_NO)
                    {
                        BrowserFunc_ThumbnailEditFilelComplete();
                    }
                    #if (MENU_EDIT_CONTINUOUSLY)
                    // protect continuously
                    AHC_UF_GetCurrentIndex(&ObjSelect);
                    Protect_Option        = CONFIRM_NOT_YET;
                    Protecting_InBrowser  = 1;
                    Protect_File_Confirm  = 0;
                    #endif
                    BrowserFunc_ThumbnailEditFilelUpdatePage();
                }
            }
            else if(Protecting_InBrowser==2)
            {
                printc("OK:Cur UnProtect_Option[%d]\r\n",UnProtect_Option);

                if(UnProtect_Option == CONFIRM_NOT_YET)
                {
                    MenuDrawSubPage_EditOneFile(NULL);
                }
                else
                {
                    if(UnProtect_Option == CONFIRM_OPT_YES)
                    {
                        if (AHC_IsCurFileCharLock())
                            BrowserFunc_ThumbnailEditFile(DCF_FILE_CHAR_UNLOCK_ALL_CAM);
                        else
                            BrowserFunc_ThumbnailEditFile(DCF_FILE_NON_READ_ONLY_ALL_CAM);
                    }
                    else if(UnProtect_Option == CONFIRM_OPT_NO)
                    {
                        BrowserFunc_ThumbnailEditFilelComplete();
                    }
                    #if (MENU_EDIT_CONTINUOUSLY)
                    // unprotect continuously
                    AHC_UF_GetCurrentIndex(&ObjSelect);
                    Protect_Option         = CONFIRM_NOT_YET;
                    Protecting_InBrowser   = 2;
                    UnProtect_File_Confirm = 0;
                    #endif
                    BrowserFunc_ThumbnailEditFilelUpdatePage();
                }
            }
        }
    }

    #ifdef FLM_GPIO_NUM
    AHC_OSDRefresh_PLCD();
    #endif

    return AHC_TRUE;
}

AHC_BOOL BrowserFunc_TouchValid(UINT8 ubIndex)
{
#if(SUPPORT_TOUCH_PANEL)
    UINT16  ThumbCount = 0;

    AHC_Thumb_GetCountCurPage(&ThumbCount);

    if(ubIndex < ThumbCount)
        return AHC_TRUE;
    else
        return AHC_FALSE;
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL BrowserFunc_Thumbnail_Focus(UINT8 CurIdx, UINT8 ubIndex)
{
#if (SUPPORT_TOUCH_PANEL)
    if( ubIndex > CurIdx )
        return AHC_Thumb_Forward(ubIndex - CurIdx);
    else
        return AHC_Thumb_Rewind(CurIdx - ubIndex);
#else
    return AHC_TRUE;
#endif
}

AHC_BOOL BrowserMode_Start(void)
{
    AHC_BOOL    ahc_ret = AHC_TRUE;

    BrowserFunc_ThumbnailEditCheckFileObj();

    BrowserFunc_DisplaySetting();//BrowserFunc_Setting();

    #if (!SWITCH_MODE_FREEZE_WIN)
    AHC_SetDisplayMode(DISPLAY_MODE_DISABLE);
    #else
    MMPS_Display_SetWinActive(UPPER_IMAGE_WINDOW_ID, MMP_FALSE);
    #endif

    //BrowserFunc_CheckLCDstatus();
    DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE_INIT);
    AHC_SetDisplayMode(DISPLAY_MODE_OSD_ENABLE);

    ahc_ret = AHC_SetMode(AHC_MODE_THUMB_BROWSER);

    if(AHC_TRUE == ahc_ret)
    {
#if (SUPPORT_TOUCH_PANEL)
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&Browser_TouchButton[0], ITEMNUM(Browser_TouchButton));
#endif
    }

    return ahc_ret;
}

void BrowserMode_Update(void)
{
    BrowserFunc_ThumbnailEditCheckFileObj();

#if (SUPPORT_TOUCH_PANEL)
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&Browser_TouchButton[0], ITEMNUM(Browser_TouchButton));
#endif

#if (QUICK_EDIT_BROWSER_FILE==QUICK_EDIT_WITH_CONFIRM)
    if( (Deleting_InBrowser   && Delete_File_Confirm)  ||
        (Protecting_InBrowser && Protect_File_Confirm) ||
        (Protecting_InBrowser && UnProtect_File_Confirm) )
    {
        MenuDrawSubPage_EditOneFile(NULL);
    }
    else
#endif
    {
        //BrowserFunc_CheckLCDstatus();
        DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE_INIT);
    }
}

//******************************************************************************
//
//                              AHC State Browser Mode
//
//******************************************************************************
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_UP)
{
    if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
        return;

    CHARGE_ICON_ENABLE(AHC_FALSE);

    BrowserFunc_ThumbnailOption (BROWSER_UP);
    DrawBrowserStatePageUpdate();

    CHARGE_ICON_ENABLE(AHC_TRUE);

}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_DOWN)
{
    if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
        return;

    CHARGE_ICON_ENABLE(AHC_FALSE);

    BrowserFunc_ThumbnailOption(BROWSER_DOWN);
    DrawBrowserStatePageUpdate();

    CHARGE_ICON_ENABLE(AHC_TRUE);

}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_LEFT)
{
    //if(Deleting_InBrowser || Protecting_InBrowser)
    //{
    //  BrowserFunc_ThumbnailEditFile_Option(ulEvent);
    //}
    //else
    {
            CHARGE_ICON_ENABLE(AHC_FALSE);

            BrowserFunc_ThumbnailOption(BROWSER_LEFT);
            DrawBrowserStatePageUpdate();

            CHARGE_ICON_ENABLE(AHC_TRUE);
            AHC_UF_GetCurrentIndex(&ObjSelect);
            if(ObjSelect == -1)
                return;
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_RIGHT)
{
    //if(Deleting_InBrowser || Protecting_InBrowser)
    //{
    //  BrowserFunc_ThumbnailEditFile_Option(ulEvent);
    //}
    //else
    {
            CHARGE_ICON_ENABLE(AHC_FALSE);

            BrowserFunc_ThumbnailOption(BROWSER_RIGHT);
            DrawBrowserStatePageUpdate();

            CHARGE_ICON_ENABLE(AHC_TRUE);
            AHC_UF_GetCurrentIndex(&ObjSelect);
        if(ObjSelect == -1)
            return;
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_DEL_ONE)
{
    BrowserFunc_ThumbnailEditFile(DCF_FILE_DELETE_ALL_CAM);

    //BrowserFunc_ThumbnailEditFilelComplete();
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_PROTECT_ONE)
{
    BrowserFunc_ThumbnailEditFile(DCF_FILE_READ_ONLY_ALL_CAM);
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_UNPROTECT_ONE)
{
    if(AHC_IsCurFileCharLock())
        BrowserFunc_ThumbnailEditFile(DCF_FILE_CHAR_UNLOCK_ALL_CAM);
    else
        BrowserFunc_ThumbnailEditFile(DCF_FILE_NON_READ_ONLY_ALL_CAM);
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_EDIT_CONFIRM)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    ahcRet = StateAttachSubMode(UI_EDIT_TOOL_MENU_STATE);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet);}
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_PLAYBACK)
{
    UINT32      MaxObjIdx   = 0;

//  if(Deleting_InBrowser || Protecting_InBrowser)
//  {
        BrowserFunc_ThumbnailEditFile_Option(ulEvent);
//  }
//  else
    {
        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        }
        AHC_UF_GetTotalFileCount(&MaxObjIdx);

        if(MaxObjIdx == 0)
            return;

        AHC_UF_GetCurrentIndex(&ObjSelect);

        if(ObjSelect == -1)
            return;

        if( m_ubPlaybackRearCam == AHC_TRUE && AHC_MULTI_TRACK_EN == 0 ){
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }
        if(!BrowserFunc_ThumbnailOption(BROWSER_PLAY))
        {
            ResetCurrentMenu();
            StateSwitchMode(UI_BROWSER_STATE);
            AHC_WMSG_Draw(AHC_TRUE, WMSG_FILE_ERROR, 3);
        }
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_MENU)
{
#if CR_USE_STATE_SWITCH_SUB_MODE == 0
    AHC_BOOL    ahcRet = AHC_TRUE;
    UI_STATE_ID ubParentUIState = 0;
#endif
#if 0
    if(Deleting_InBrowser || Protecting_InBrowser)
    {
        if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
        {
            return;
        }
        else
        {
            BrowserFunc_ThumbnailResetAllEditOp();
        }
    }

    ret = StateSwitchMode(UI_PLAYBACK_MENU_STATE);
#endif
#if CR_USE_STATE_SWITCH_SUB_MODE
    StateReplaceSubMode(UI_PLAYBACK_MENU_STATE);
#else
    StateModeGetParent(uiGetCurrentState(), &ubParentUIState);
    if(UI_STATE_UNSUPPORTED != ubParentUIState){
        printc("%s,%d, DettachSubMode:%d\r\n", __func__, __LINE__, uiGetCurrentState());
        ahcRet = StateDetachSubMode();
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ahcRet);}
    }
    ahcRet = StateAttachSubMode(UI_PLAYBACK_MENU_STATE);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); /*return ahcRet;*/}
#endif
}


DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_MODE)
{
    AHC_BOOL ret = AHC_TRUE;
    {
#if (CYCLIC_MODE_CHANGE)
            {
                UINT8 ubNextMode = UI_VIDEO_STATE;

                switch(GetCurrentOpMode())
                {
                case CAPTURE_MODE   :
                case JPGPB_MODE     :
    #if (DSC_MODE_ENABLE) && defined(CFG_BROWSER_JPGPB_TO_VIDEO_MENU) //may be defined in config_xxx.h
                    /* Clean Thumbnail page, customer requested */
                    AHC_Thumb_DrawEmptyPage();
                    ubNextMode = UI_VIDEO_MENU_STATE;
                    /* Make Menu be in Video mode to switch for this UI flow */
                    SetCurrentOpMode(VIDEOREC_MODE);
#else
                    ubNextMode = UI_VIDEO_STATE;
#endif
                    break;

                case VIDEOREC_MODE  :
                case MOVPB_MODE     :
#if (DSC_MODE_ENABLE) || defined(CFG_BROWSER_MOVPB_TO_BROWSER_MENU) //may be defined in config_xxx.h
                    ubNextMode = UI_BROWSER_STATE;
#else
                    ubNextMode = UI_VIDEO_STATE;
#endif
                    break;
                }

                if (GetCurrentOpMode() == MOVPB_MODE || GetCurrentOpMode() == JPGPB_MODE || GetCurrentOpMode() == JPGPB_MOVPB_MODE)
                {
                    DrawBrowserStatePlaybackRearCam( m_ubPlaybackRearCam );
                }

                if(ubNextMode==UI_VIDEO_MENU_STATE)
                {
                    BrowserFunc_ThumbnailResetAllEditOp();
                    ret = StateSwitchMode(UI_VIDEO_MENU_STATE);
                }
                else if(ubNextMode==UI_VIDEO_STATE)
                {
                    BrowserFunc_ThumbnailResetAllEditOp();
                    ret = StateSwitchMode(UI_VIDEO_STATE);
                }
                else //if(ubNextMode==UI_BROWSER_STATE)//Browser Switch
                {
                    if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
                        return;

                    DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE_CLEAR_OSD);
                    ret = BrowserFunc_ModeSwitch();
                    DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE);
                }
            }
#else
    #if (DSC_MODE_ENABLE)
            if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
                break;

            DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE_CLEAR_OSD);
            ret = BrowserFunc_ModeSwitch();
            DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE);
#endif
#endif

    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_KEY_PLAYBACK_MODE)
{
//#if (HDMI_ENABLE)
//  if (AHC_IsHdmiConnect()){
//      if(MOVPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          HDMIFunc_PreviewVideo();
//      }
//      else if(JPGPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          HDMIFunc_PreviewCamera();
//      }
//      else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          HDMIFunc_PreviewVideo();
//      }
//  }else
//#endif
//#if (TVOUT_ENABLE)
//  if (AHC_IsTVConnectEx()){
//      if(MOVPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          TVFunc_PreviewVideo();
//      }
//      else if(JPGPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          TVFunc_PreviewCamera();
//      }
//      else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
//      {
//          BrowserFunc_ThumbnailResetAllEditOp();
//          TVFunc_PreviewVideo();
//      }
//  }else
//#endif
    {
        if(MOVPB_MODE == GetCurrentOpMode())
        {
            BrowserFunc_ThumbnailResetAllEditOp();
             StateSwitchMode(UI_VIDEO_STATE);
        }
        else if(JPGPB_MODE == GetCurrentOpMode())
        {
            BrowserFunc_ThumbnailResetAllEditOp();
            StateSwitchMode(UI_CAMERA_STATE);
        }
        else if(JPGPB_MOVPB_MODE == GetCurrentOpMode())
        {
            BrowserFunc_ThumbnailResetAllEditOp();
            StateSwitchMode(UI_VIDEO_STATE);
        }

    }
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_POWER_OFF)
{
    AHC_Thumb_DrawEmptyPage();
    AHC_PowerOff_NormalPath();
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_BROWSER_SELECT_MENU)
{
#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){


    }else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){


    }else
#endif
    {

    }
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_FILE_DELETING)
{

    Deleting_InBrowser = 1;
    BrowserFunc_ThumbnailEditFile_Option(EVENT_THUMBNAIL_KEY_PLAYBACK);

}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_LOCK_FILE_M)
{

    if (AHC_CheckCurFileLockStatus() || AHC_IsCurFileCharLock())
        Protecting_InBrowser = 2;//Unprotect
    else
        Protecting_InBrowser = 1;//Protect

    BrowserFunc_ThumbnailEditFile_Option(EVENT_THUMBNAIL_KEY_PLAYBACK);

}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_CAMERA_PREVIEW)
{
    BrowserFunc_ThumbnailResetAllEditOp();

    StateSwitchMode(UI_CAMERA_STATE);
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_VIDEO_PREVIEW)
{
    BrowserFunc_ThumbnailResetAllEditOp();

    StateSwitchMode(UI_VIDEO_STATE);
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_LCD_POWER_SAVE)
{
    AHC_SwitchLCDBackLight();
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_DC_CABLE_IN)
{
    {
#if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
        BrowserFunc_ThumbnailResetAllEditOp();
        ret = StateSwitchMode(UI_VIDEO_STATE);
        AHC_SetRecordByChargerIn(3);
#elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
        SetKeyPadEvent(KEY_POWER_OFF);
#endif
    }
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_DC_CABLE_OUT)
{
    {
        AHC_Charger_SetEnable(AHC_FALSE);
#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
        AHC_SetShutdownByChargerOut(AHC_TRUE);
#endif
    }
}

#if (HDMI_ENABLE)
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_HDMI_DETECT)
{
//  SetHDMIState(AHC_HDMI_BROWSER_STATUS);
    StateSwitchMode(UI_BROWSER_STATE);
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_HDMI_REMOVED)
{
    bShowHdmiWMSG = AHC_TRUE;
    StateSwitchMode(UI_BROWSER_STATE);
}
#endif

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_TV_DETECT)
{
    //SetTVState(AHC_TV_BROWSER_STATUS);
    StateSwitchMode(UI_BROWSER_STATE);
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_TV_REMOVED)
{
    StateSwitchMode(UI_BROWSER_STATE);
}
#endif

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_USB_DETECT)
{
    {
        if(IsAdapter_Connect())
        {
#if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
            BrowserFunc_ThumbnailResetAllEditOp();
            ret = StateSwitchMode(UI_VIDEO_STATE);
            AHC_SetRecordByChargerIn(3);
#elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
            SetKeyPadEvent(KEY_POWER_OFF);
#endif
        }
        else
        {
            BrowserFunc_ThumbnailResetAllEditOp();
#if (USB_MODE_SELECT_EN)
            if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
                StateSwitchMode(UI_USBSELECT_MENU_STATE);
            }
            else
            {
#ifdef CFG_POWER_ON_ENTER_CAMERA_STATE
                StateSwitchMode(UI_CAMERA_STATE);
#else
                StateSwitchMode(UI_VIDEO_STATE);
#endif
            }
#else
            if(MenuSettingConfig()->uiUSBFunction == MENU_SETTING_USB_MSDC)
            {
                StateSwitchMode(UI_MSDC_STATE);
            }
            else
            {
                StateSwitchMode(UI_PCCAM_STATE);
            }
#endif
        }

    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_USB_REMOVED)
{
    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC mode
    {
        AHC_SetMode(AHC_MODE_IDLE);
        bForce_PowerOff = AHC_TRUE;
        AHC_PowerOff_NormalPath();
    }
    else
    {
        if (AHC_IsDcCableConnect() == AHC_TRUE)
            return;

        AHC_Charger_SetEnable(AHC_FALSE);
    #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
        AHC_SetShutdownByChargerOut(AHC_TRUE);
    #endif
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_SD_DETECT)
{
//#if (HDMI_ENABLE)
//  if (AHC_IsHdmiConnect()){


//  }else
//#endif
//#if (TVOUT_ENABLE)
//  if (AHC_IsTVConnectEx()){


//  }else
//#endif
    {
        AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
                    DrawBrowserStateSDMMC_In();
                    AHC_SetMode(AHC_MODE_THUMB_BROWSER);
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_SD_REMOVED)
{
//#if (HDMI_ENABLE)
//  if (AHC_IsHdmiConnect()){


//  }else
//#endif
//#if (TVOUT_ENABLE)
//  if (AHC_IsTVConnectEx()){


//  }else
//#endif
    {
        if(Deleting_InBrowser || Protecting_InBrowser)
        {
            BrowserFunc_ThumbnailEditFilelComplete();
        }
        if(AHC_TRUE == AHC_SDMMC_IsSD1MountDCF())
        {
            AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
            Enable_SD_Power(0 /* Power Off */);
        }
        DrawBrowserStateSDMMC_Out();
        AHC_Thumb_DrawEmptyPage();
    }
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_LCD_COVER_OPEN)
{
    LedCtrl_LcdBackLight(AHC_TRUE);
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_LCD_COVER_CLOSE)
{
    LedCtrl_LcdBackLight(AHC_FALSE);
}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_LCD_COVER_NORMAL)
{

}
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_THUMBNAIL_UPDATE_MESSAGE)
{
    DrawStateBrowserUpdate(EVENT_THUMBNAIL_UPDATE_MESSAGE);
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_MOVPB_MODE)
{
    {
        if( GetCurrentOpMode() == MOVPB_MODE || GetCurrentOpMode() == JPGPB_MODE || GetCurrentOpMode() == JPGPB_MOVPB_MODE)
        {
            m_ubPlaybackRearCam = (m_ubPlaybackRearCam == AHC_TRUE)? AHC_FALSE : AHC_TRUE;
            DrawBrowserStatePlaybackRearCam( m_ubPlaybackRearCam );

            Component_Display_CloseDevice();

            BrowserFunc_DisplaySetting();

            #if (AHC_MULTI_TRACK_EN)
            if (m_ubPlaybackRearCam == AHC_TRUE) {
                MMPS_VIDPLAY_SetCurrentTrack(1);  //playback rear cam.
            }
            else {
                MMPS_VIDPLAY_SetCurrentTrack(0);  //playback front cam.
            }
            #endif

            #if (MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
            if (m_ubPlaybackRearCam)
                AHC_MIMF_SetMultiDBBrowseEnable(AHC_FALSE);
            #endif

            AHC_Thumb_DrawPage(AHC_TRUE);
            DrawStateBrowserUpdate(EVENT_THUMBNAIL_MODE);
        }
    }
}

#if (UVC_HOST_VIDEO_ENABLE)
DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_USB_B_DEVICE_DETECT)
{
    AHC_USB_PauseDetection(0);
    if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
            (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else{
        AHC_PRINT_RET_ERROR(0, 0);
        printc("KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted.\r\n");
    }
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_USB_B_DEVICE_REMOVED)
{
    AHC_USB_PauseDetection(0);
    if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
            (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else{
        AHC_PRINT_RET_ERROR(0, 0);
        printc("KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted.\r\n");
    }
}
#endif

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_SUB_MODE_ENTER)
{

}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_SUB_MODE_EXIT)
{
#if 0
    if(bForceSwitchBrowser)
    {
        StateBrowserModeInitLCD(NULL);
    }
    else
#endif
    {
        Component_Display_CloseDevice();
        if(AHC_TRUE == AHC_SDMMC_IsSD1MountDCF())
        {
            if(bRefreshBrowser)
            {
                DrawBrowserStateSDMMC_In();
                AHC_Thumb_DrawPage(AHC_TRUE);

#if (SUPPORT_TOUCH_PANEL)
                KeyParser_ResetTouchVariable();
                KeyParser_TouchItemRegister(&Browser_TouchButton[0], ITEMNUM(Browser_TouchButton));
#endif

                bRefreshBrowser = AHC_FALSE;
            }
            else
            {
                BrowserMode_Update();
                AHC_Thumb_DrawPage(AHC_FALSE);
            }
        }
        else
        {
            DrawBrowserStateSDMMC_Out();
            AHC_Thumb_DrawEmptyPage();
            //FIXME To reviewer: If you think this fix is OK, please remove this line. It worked but I'm not sure it's the right way.
            BrowserMode_Update(); //Truman@130514 Fix the issue entering Global Setting Menu in browser mode, OSD hangs.
        }
    }

    if (GetCurrentOpMode() == MOVPB_MODE){
        DrawBrowserStatePlaybackRearCam( m_ubPlaybackRearCam );
    }
    else{
        DrawBrowserStatePlaybackRearCam( AHC_FALSE );
    }
}

DECL_AHC_EV_HANDLER(STATE_BROWSER_MODE_EVENT_ENTER_NET_PLAYBACK)
{
    BrowserFunc_ThumbnailResetAllEditOp();
    StateSwitchMode(UI_NET_PLAYBACK_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

UINT32 StateBrowserModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    UINT32 ulBrowserEvent = 0;
    ulBrowserEvent = KeyParser_ThumbnailEvent(ulMsgId, ulEvent, ulParam);
    StateModeDoHandlerEvent(ulMsgId, ulBrowserEvent, ulParam);
    DrvLCDRefresh();
    return 0;
}

#if (SUPPORT_TOUCH_PANEL)
UINT32 BrowserFunc_Touch(UINT16 pt_x,UINT16 pt_y)
{
    UINT32      CurrIdx   = 0;
    UINT32      SelObjIdx = 0;
    UINT32      PageFileNum = 0;
    UINT32      uiMaxIdx;
    UINT16      uiCurPage = 0;
    UINT16      uiCurNumPage = 0;

    SelObjIdx = (pt_x - POS_THUMB_AREA_X0)/(POS_THUMB_AREA_W/THUMB_PER_LINE);
    SelObjIdx += ((pt_y - POS_THUMB_AREA_Y0)/(POS_THUMB_AREA_H/THUMB_PER_COLUMN)) * THUMB_PER_LINE;

    AHC_Thumb_GetMaxNumPerPage(&PageFileNum);
    AHC_Thumb_GetCurIdx(&CurrIdx);
    AHC_UF_GetTotalFileCount(&uiMaxIdx);
    AHC_Thumb_GetCurPage(&uiCurPage);
    AHC_Thumb_GetCountCurPage(&uiCurNumPage);
//  printc("SelObjIdx %d CurrIdx %d uiMaxIdx %d \r\n",SelObjIdx,CurrIdx,uiMaxIdx);
//  printc(" uiCurNumPage %d uiCurPage %d \r\n",uiCurNumPage,uiCurPage);
    if(SelObjIdx>(uiCurNumPage-1)) return EVENT_NONE;
    if( SelObjIdx != (CurrIdx %PageFileNum) )
    {
        BrowserFunc_Thumbnail_Focus(CurrIdx%PageFileNum, SelObjIdx);
        //DrawStateTVBrowserUpdate(EVENT_THUMBNAIL_TOUCH_PAGE_UPDATE);
    }
    else
    {
        if(Deleting_InBrowser || Protecting_InBrowser)
        {
            BrowserFunc_ThumbnailEditFile_Option(EVENT_THUMBNAIL_KEY_PLAYBACK);
        }
        else
        {
            if(!BrowserFunc_ThumbnailOption(BROWSER_PLAY))
            {
                ResetCurrentMenu();
                StateSwitchMode(UI_BROWSER_STATE);
                AHC_WMSG_Draw(AHC_TRUE, WMSG_FILE_ERROR, 3);
            }
        }
    }
    return EVENT_NONE;
}

UINT32 Browser_FileEdit_Touch(UINT16 pt_x,UINT16 pt_y)
{
    UINT16  i = 0;
    UINT32 ulEvent;
    UINT32 ret = MENU_ERR_OK;
    RECT rc = RECT_MENU_CONFIRM_YES;
    #define STR_GAP     (30)

    i = (pt_x -rc.uiLeft)/(rc.uiWidth+ STR_GAP);

     if(Delete_Option == CONFIRM_OPT_NO || Protect_Option == CONFIRM_OPT_NO || UnProtect_Option == CONFIRM_OPT_NO)
     {
        if(i==0)
            ulEvent = EVENT_KEY_LEFT;
        else
            ulEvent = EVENT_THUMBNAIL_KEY_PLAYBACK;
     }
     else    if(Delete_Option == CONFIRM_OPT_YES || Protect_Option == CONFIRM_OPT_YES || UnProtect_Option == CONFIRM_OPT_YES)
     {
        if(i==1)
            ulEvent = EVENT_KEY_RIGHT;
        else
            ulEvent = EVENT_THUMBNAIL_KEY_PLAYBACK;
     }
    BrowserFunc_ThumbnailEditFile_Option(ulEvent);
    return EVENT_NONE;

}
#endif

AHC_BOOL StateBrowserModeInitCommon(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    switch(GetCurrentOpMode())
    {
        case VIDEOREC_MODE  :
        case MOVPB_MODE     :
            MenuStatePlaybackSelectDB( MOVPB_MODE );
            SetCurrentOpMode(MOVPB_MODE);
            break;

        case CAPTURE_MODE   :
        case JPGPB_MODE     :
            MenuStatePlaybackSelectDB( JPGPB_MODE );
            SetCurrentOpMode(JPGPB_MODE);
            break;

        case JPGPB_MOVPB_MODE     :
            MenuStatePlaybackSelectDB( JPGPB_MOVPB_MODE );
            SetCurrentOpMode(JPGPB_MOVPB_MODE);
            break;

        case AUDPB_MODE     :
            SetCurrentOpMode(MOVPB_MODE);
            break;

        case SLIDESHOW_MODE :
            break;

        default             :
            SetCurrentOpMode(MOVPB_MODE);
            break;
    }

    //bForceSwitchBrowser = AHC_FALSE;
    ahcRet = BrowserMode_Start();

    return ahcRet;
}

// for ADAS_LDWS, TBD
AHC_BOOL StateBrowserModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

#if (SWITCH_MODE_FREEZE_WIN)
    AHC_OS_SleepMs(100);// Prevent changing mode too fast
#endif
    //AHC_SetMode(AHC_MODE_IDLE);

    //Force OSD init for browser mode.
    AHC_OSDUninit();

    ahcRet = AHC_SwitchDisplayOutputDevLCD();

    // TBD
    AIHC_DrawReservedOSD(AHC_TRUE);
    if (AHC_FALSE == AHC_OSDCreateBuffer(   THUMBNAIL_OSD_FRONT_ID,
                                            RTNA_LCD_GetAttr()->usPanelW,
                                            RTNA_LCD_GetAttr()->usPanelH,
                                            THUMBNAIL_OSD_COLOR_FORMAT)) {
        AIHC_DrawReservedOSD(AHC_FALSE);
        return AHC_FALSE;
    }
    AIHC_DrawReservedOSD(AHC_FALSE);

    StateLedControl(UI_BROWSER_STATE);
    StateLCDCheckStatus(UI_BROWSER_STATE);
    RTNA_LCD_Backlight(MMP_TRUE);

    DrawBrowserStateFunctionSelectLCD(); //HDMI
    ahcRet = StateBrowserModeInitCommon();
    return ahcRet;
}

#if (HDMI_ENABLE)
AHC_BOOL StateBrowserModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_LCD_Backlight(MMP_FALSE);

#ifdef CFG_ENBLE_PANEL_SLEEP
    RTNA_LCD_Enter_Sleep();
#endif

    //Force OSD init for browser mode.
    AHC_OSDUninit();

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();

    //InitOSD_HDMI();//InitOSD();

    StateLedControl(UI_BROWSER_STATE);
    //StateLCDCheckStatus(UI_BROWSER_STATE);

    DrawBrowserStateFunctionSelectHDMI(); //HDMI

    ahcRet = StateBrowserModeInitCommon();
    return ahcRet;
}
#endif //#if (HDMI_ENABLE)

#if (TVOUT_ENABLE)
AHC_BOOL StateBrowserModeInitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    RTNA_LCD_Backlight(MMP_FALSE);

#ifdef CFG_ENBLE_PANEL_SLEEP
    RTNA_LCD_Enter_Sleep();
#endif

    //Force OSD init for browser mode.
    AHC_OSDUninit();

    ahcRet = AHC_SwitchDisplayOutputDevTVout();

    StateLedControl(UI_BROWSER_STATE);
    //StateLCDCheckStatus(UI_BROWSER_STATE);

    //AHC_SetMode(AHC_MODE_IDLE);
    DrawBrowserStateFunctionSelectTv();
    ahcRet = StateBrowserModeInitCommon();
    return ahcRet;
}
#endif

AHC_BOOL StateBrowserModeShutDown(void* pData)
{
    //m_ubPlaybackRearCam = AHC_FALSE;
    Component_Display_CloseDevice();

    AHC_SetMode(AHC_MODE_IDLE);

    //Force OSD init when exiting browser mode.
    AHC_OSDUninit();

    // TBD
    //AIHC_DrawReservedOSD(AHC_TRUE);
    //AHC_OSDDestroyBuffer(THUMBNAIL_OSD_FRONT_ID);
    //AIHC_DrawReservedOSD(AHC_FALSE);

    return AHC_TRUE;
}

AHC_BOOL StateSelectFuncBrowserMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    RegisterEventCb(EVENT_KEY_UP,                       STATE_BROWSER_MODE_EVENT_KEY_UP);
    RegisterEventCb(EVENT_KEY_DOWN,                     STATE_BROWSER_MODE_EVENT_KEY_DOWN);
    RegisterEventCb(EVENT_KEY_LEFT,                     STATE_BROWSER_MODE_EVENT_KEY_LEFT);
    RegisterEventCb(EVENT_KEY_RIGHT,                    STATE_BROWSER_MODE_EVENT_KEY_RIGHT);
    RegisterEventCb(EVENT_THUMBNAIL_KEY_PLAYBACK,       STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_PLAYBACK);
    RegisterEventCb(EVENT_THUMBNAIL_KEY_EDIT_CONFIRM,   STATE_BROWSER_MODE_EVENT_THUMBNAIL_KEY_EDIT_CONFIRM);
    RegisterEventCb(EVENT_KEY_MENU,                     STATE_BROWSER_MODE_EVENT_KEY_MENU);
    RegisterEventCb(EVENT_KEY_MODE,                     STATE_BROWSER_MODE_EVENT_KEY_MODE);
    RegisterEventCb(EVENT_KEY_PLAYBACK_MODE,            STATE_BROWSER_MODE_EVENT_KEY_PLAYBACK_MODE);
    RegisterEventCb(EVENT_POWER_OFF,                    STATE_BROWSER_MODE_EVENT_POWER_OFF);
    RegisterEventCb(EVENT_BROWSER_SELECT_MENU,          STATE_BROWSER_MODE_EVENT_BROWSER_SELECT_MENU);
    RegisterEventCb(EVENT_FILE_DELETING,                STATE_BROWSER_MODE_EVENT_FILE_DELETING);
    RegisterEventCb(EVENT_LOCK_FILE_M,                  STATE_BROWSER_MODE_EVENT_LOCK_FILE_M);
    RegisterEventCb(EVENT_CAMERA_PREVIEW,               STATE_BROWSER_MODE_EVENT_CAMERA_PREVIEW);
    RegisterEventCb(EVENT_VIDEO_PREVIEW,                STATE_BROWSER_MODE_EVENT_VIDEO_PREVIEW);
    RegisterEventCb(EVENT_LCD_POWER_SAVE,               STATE_BROWSER_MODE_EVENT_LCD_POWER_SAVE);

    RegisterEventCb(EVENT_DC_CABLE_IN,                  STATE_BROWSER_MODE_EVENT_DC_CABLE_IN);
    RegisterEventCb(EVENT_DC_CABLE_OUT,                 STATE_BROWSER_MODE_EVENT_DC_CABLE_OUT);
#if (TVOUT_ENABLE)
    RegisterEventCb(EVENT_TV_DETECT,                    STATE_BROWSER_MODE_EVENT_TV_DETECT);
    RegisterEventCb(EVENT_TV_REMOVED,                   STATE_BROWSER_MODE_EVENT_TV_REMOVED);
#endif
#if (HDMI_ENABLE)
    RegisterEventCb(EVENT_HDMI_DETECT,                  STATE_BROWSER_MODE_EVENT_HDMI_DETECT);
    RegisterEventCb(EVENT_HDMI_REMOVED,                 STATE_BROWSER_MODE_EVENT_HDMI_REMOVED);
#endif
    RegisterEventCb(EVENT_USB_DETECT,                   STATE_BROWSER_MODE_EVENT_USB_DETECT);
    RegisterEventCb(EVENT_USB_REMOVED,                  STATE_BROWSER_MODE_EVENT_USB_REMOVED);
    RegisterEventCb(EVENT_SD_DETECT,                    STATE_BROWSER_MODE_EVENT_SD_DETECT);
    RegisterEventCb(EVENT_SD_REMOVED,                   STATE_BROWSER_MODE_EVENT_SD_REMOVED);

    RegisterEventCb(EVENT_LCD_COVER_OPEN,               STATE_BROWSER_MODE_EVENT_LCD_COVER_OPEN);
    RegisterEventCb(EVENT_LCD_COVER_CLOSE,              STATE_BROWSER_MODE_EVENT_LCD_COVER_CLOSE);
    RegisterEventCb(EVENT_LCD_COVER_NORMAL,             STATE_BROWSER_MODE_EVENT_LCD_COVER_NORMAL);

    RegisterEventCb(EVENT_THUMBNAIL_UPDATE_MESSAGE,     STATE_BROWSER_MODE_EVENT_THUMBNAIL_UPDATE_MESSAGE);
    RegisterEventCb(EVENT_MOVPB_MODE,                   STATE_BROWSER_MODE_EVENT_MOVPB_MODE);
#if (UVC_HOST_VIDEO_ENABLE)
    RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,          STATE_BROWSER_MODE_EVENT_USB_B_DEVICE_DETECT);
    RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,         STATE_BROWSER_MODE_EVENT_USB_B_DEVICE_REMOVED);
#endif

    RegisterEventCb(EVNET_SUB_MODE_ENTER,               STATE_BROWSER_MODE_EVENT_SUB_MODE_ENTER);
    RegisterEventCb(EVNET_SUB_MODE_EXIT,                STATE_BROWSER_MODE_EVENT_SUB_MODE_EXIT);

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,           STATE_BROWSER_MODE_EVENT_ENTER_NET_PLAYBACK);
#endif

#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){
        StateModeSetOperation(UI_BROWSER_STATE, StateBrowserModeInitHDMI, StateBrowserModeShutDown, StateBrowserModeHandler);
    }else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx())
    {
        StateModeSetOperation(UI_BROWSER_STATE, StateBrowserModeInitTV, StateBrowserModeShutDown, StateBrowserModeHandler);
    }else
#endif
    {
        StateModeSetOperation(UI_BROWSER_STATE, StateBrowserModeInitLCD, StateBrowserModeShutDown, StateBrowserModeHandler);
    }

    ahcRet =  SwitchUIDrawSetBrowserMode();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet); return ahcRet;}

    return ahcRet;
}
