/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_gui.h"
#include "ahc_os.h"
#include "ahc_dcf.h"
#include "ahc_menu.h"
#include "ahc_media.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "keyparser.h"
#include "MenuSetting.h"
#include "DrawStateMenuSetting.h"
#include "drawstatemoviepbfunc.h"
#include "drawstatephotopbfunc.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "IconDefine.h"
#include "dsc_charger.h"
#include "ui_drawgeneral.h"

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT8 	m_ubBatteryStatus;
extern AHC_BOOL bLockCurJpegFile;
extern AHC_BOOL gbAhcDbgBrk;
//extern UINT8 						m_DelFile;

/*===========================================================================
 * Main body
 *===========================================================================*/

void DrawJpgPb_FileIndex(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
	DrawMovPb_FileIndex(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawJpgPb_FileInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
	DrawMovPb_FileInfo(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawJpgPb_DateInfo(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
    DrawMovPb_DateInfo(ubID, x, y, bLarge, ubMag, bFlag, bkColor, Para1);
}

void DrawJpgPb_LockCurFile(UINT16 ubID, UINT32 x, UINT32 y, AHC_BOOL bLarge, UINT8 ubMag, AHC_BOOL bFlag, GUI_COLOR bkColor, INT32 Para1)
{
#if (QUICK_FILE_EDIT_EN)
    GUI_BITMAP 	IconID 	= BMICOM_FILE_PROTECTKEY;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    BEGIN_LAYER(ubID);

    if(bFlag==AHC_FALSE)
    {
        AHC_OSDSetColor(ubID, bkColor);
        AHC_OSDDrawFillRect(ubID, x, y, x+IconID.XSize*ubMag, y+IconID.YSize*ubMag);
        AHC_OSDSetColor(ubID, 0xAA000000);
    }
    else
    {
        if(bLockCurJpegFile)
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

void DrawStatePhotoPbInit_Lcd(void)
{
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;
    UINT8  idx  = 0;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    CHARGE_ICON_ENABLE(AHC_FALSE);

    OSDDraw_EnterDrawing(&bID0, &bID1);

    //BEGIN_LAYER(bID0);
    //BEGIN_LAYER(bID1);

    OSDDraw_ClearOvlDrawBuffer(bID0);

    BEGIN_LAYER(bID0);
    OSDDraw_EnableSemiTransparent(bID0, AHC_TRUE);
    //OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);
    AHC_OSDSetColor(bID0, 0xFF000000);
    END_LAYER(bID0);

	BEGIN_LAYER(bID1);
	OSDDraw_EnableSemiTransparent(bID1, AHC_TRUE);
    END_LAYER(bID1);

    for (idx = 0; idx < JPGPB_GUI_MAX; idx++)
    {
        UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    }

    BEGIN_LAYER(bID0);
    OSDDraw_MainTouchButton(bID0, UI_PLAYBACK_STATE);
    END_LAYER(bID0);
    OSDDraw_ExitDrawing(&bID0, &bID1);

	AHC_OSDSetActive(bID0, AHC_TRUE);

    CHARGE_ICON_ENABLE(AHC_TRUE);
}
void DrawStatePhotoPbInit_Hdmi(UINT8 bID0, UINT8 bID1)
{
    UINT8   idx;
    UINT32 	iVal[2];
    RECT  	OsdRect = POS_HDMI_PLAY_OSD;

    //OSDDraw_EnterDrawing(&bID0, &bID1);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(bID0, &OsdRect);

 	for (idx = 0; idx < JPGPB_GUI_MAX; idx++)
	{
		UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
	}

#if (SHOW_HDMI_DIR_ICON)
    AHC_OSDDrawBitmap(bID0, &bmIcon_HdmiStillPlay, 100, 45);
#endif

#if (POWER_OFF_CONFIRM_PAGE_EN)
	if(PowerOff_InProcess)
	{
		MenuDrawSubPage_PowerOff_HDMI_Play(bID0);
	}
#endif

    iVal[0] = 1;
    iVal[1] = OSD_COLOR_TRANSPARENT;
    AHC_OSDSetDisplayAttr(bID0, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);
    AHC_OSDSetDisplayAttr(bID1, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

    //OSDDraw_ExitDrawing(&bID0, &bID1);
}


void DrawStatePhotoPbInit_Tv(UINT8 bID0, UINT8 bID1)
{
    //UINT8  	bID0 	= 0;
    //UINT8  	bID1 	= 0;
    UINT8   idx;
    UINT32 	iVal[2];
    RECT  	OsdRect = POS_TV_PLAY_OSD;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(0,0); return; }

    //OSDDraw_EnterDrawing(&bID0, &bID1);

    BEGIN_LAYER(bID0);

    AHC_OSDSetColor(bID0, OSD_COLOR_TRANSPARENT);
    AHC_OSDDrawFillRect2(bID0, &OsdRect);

    END_LAYER(bID0);

	for (idx = 0; idx < JPGPB_GUI_MAX; idx++)
	{
		UIDrawEx(bID0, idx, AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
	}

#if 0//(SHOW_TV_DIR_ICON)
    BEGIN_LAYER(bID0);
    AHC_OSDDrawBitmap(bID0, &bmIcon_HdmiStillPlay, 100, 45);
    END_LAYER(bID0);
#endif

#if (POWER_OFF_CONFIRM_PAGE_EN)
	if(PowerOff_InProcess)
	{
		MenuDrawSubPage_PowerOff_TV_Play(bID0);
	}
#endif

    BEGIN_LAYER(bID0);
    iVal[0] = 1;
    iVal[1] = OSD_COLOR_TRANSPARENT;
    AHC_OSDSetDisplayAttr(bID0, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);
    AHC_OSDSetDisplayAttr(bID1, AHC_OSD_ATTR_TRANSPARENT_ENABLE, iVal);

    //OSDDraw_ExitDrawing(&bID0, &bID1);
    END_LAYER(bID0);
}


void DrawStateJpgPbPageSwitch(UINT8 ubPage)
{
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    OSDDraw_EnterDrawing(&bID0, &bID1);

    OSDDraw_ClearTouchButtons(bID0, JpgPBCtrlPage_TouchButton, ITEMNUM(JpgPBCtrlPage_TouchButton));

    BEGIN_LAYER(bID0);
    if( TOUCH_MAIN_PAGE == ubPage )
        OSDDraw_MainTouchButton(bID0, UI_PLAYBACK_STATE);
	else
        OSDDraw_CtrlTouchButton(bID0, UI_PLAYBACK_STATE);
    END_LAYER(bID0);
    OSDDraw_ExitDrawing(&bID0, &bID1);
#endif
}

void DrawStateJpgPbUpdate(void)
{
    UINT8    bID0 = 0;
    UINT8    bID1 = 0;
    static UINT8 SD_status = AHC_FALSE;
#if (QUICK_FILE_EDIT_EN)
    static UINT8 Lock_status = AHC_FALSE;
#endif

    OSDDraw_EnterDrawing(&bID0, &bID1);

    if(m_ubBatteryStatus != MenuSettingConfig()->uiBatteryVoltage)
    {
        UIDrawEx(bID0, JPGPB_GUI_BATTERY, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        m_ubBatteryStatus = MenuSettingConfig()->uiBatteryVoltage;
    }

    if(SD_status != AHC_SDMMC_IsSD1MountDCF())
    {
        UIDrawEx(bID0, JPGPB_GUI_SD_STATE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        //SD_status = AHC_SDMMC_GetMountState();
    }

#if (QUICK_FILE_EDIT_EN)
    if(Lock_status != bLockCurJpegFile)
    {
        UIDrawEx(bID0, JPGPB_GUI_LOCK_FILE, AHC_TRUE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
        Lock_status = bLockCurJpegFile;
    }
#endif

    UIDrawEx(bID0, JPGPB_GUI_FILE_INDEX, 	AHC_TRUE,  AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, JPGPB_GUI_FILENAME, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);
    UIDrawEx(bID0, JPGPB_GUI_FILEDATE, 	AHC_FALSE, AHC_TRUE, OSD_COLOR_TRANSPARENT, NULL_PARAM);

    OSDDraw_ExitDrawing(&bID0, &bID1);
}

void DrawStateJpgPbMode_Update(void)
{
	DrawStatePhotoPbInit_Lcd();
}

#if 0
void ____Event_Handler____(){ruturn;} //dummy
#endif

void DrawStatePhotoPb_handler_Lcd(UINT32 ubEvent)
{
    switch(ubEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
			DrawStateJpgPbUpdate();
        break;

        case EVENT_JPGPB_UPDATE_MESSAGE			  :
        	DrawStateJpgPbUpdate();
        	break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			AHC_OSDSetFlipDrawMode(OVL_DISPLAY_BUFFER, OSD_FLIP_DRAW_NONE_ENABLE);
			DrawStatePhotoPbInit_Lcd();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
			AHC_OSDRefresh();
        break;

        case EVENT_JPGPB_MODE_INIT                :
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
			DrawStatePhotoPbInit_Lcd();
			AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
			AHC_OSDRefresh();
        break;



        default:
        break;
    }
}
void DrawStatePhotoPb_handler_Hdmi(UINT32 ulEvent)
{
#if (HDMI_ENABLE)
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    //OSDDraw_EnterDrawing(&bID0, &bID1);

    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_DOWN                       :
#if 0  //Andy Liu TBD
			DrawStateHdmiMoviePBDel(m_DelFile);
#endif
        break;

        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
        	DrawStateJpgPbUpdate();//DrawStateHdmiPhotoPBChangeFile();
        break;

        case EVENT_HDMI_DEL_FILE                  :
        	DrawStateJpgPbUpdate();//DrawStateHdmiPhotoPBChangeFile();
        break;

        case EVENT_HDMI_BROWSER_KEY_PLAYBACK      :
#if 0  //Andy Liu TBD
            if(m_DelFile) {
                DrawStateHdmiMoviePBDel(m_DelFile+2);
                break;
            }
#endif
        break;

        case EVENT_HDMI_CHANGE_MODE_INIT          :
			OSDDraw_EnterDrawing(&bID0, &bID1);
			AHC_OSDSetActive(bID0, 0);
			AHC_OSDSetActive(bID1 ,0);
			DrawStatePhotoPbInit_Hdmi(bID0, bID1);
			AHC_OSDSetActive(bID0, 1);
			AHC_OSDSetActive(bID1 ,1);
			OSDDraw_ExitDrawing(&bID0, &bID1);
        break;

        default:
        break;
    }

    //OSDDraw_ExitDrawing(&bID0, &bID1);

#endif
}
void DrawStatePhotoPb_handler_Tv(UINT32 ulEvent)
{
#if (TVOUT_ENABLE)
    UINT8  bID0 = 0;
    UINT8  bID1 = 0;

    //OSDDraw_EnterDrawing(&bID0, &bID1);

    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;

        case EVENT_KEY_DOWN                       :
#if 0  //Andy Liu TBD
            DrawStateTVMoviePBDel(m_DelFile);
#endif
        break;

        case EVENT_KEY_LEFT                       :
        case EVENT_KEY_RIGHT                      :
        	DrawStateJpgPbUpdate();//DrawStateTVPhotoPBChangeFile();
        break;

        case EVENT_TV_DEL_FILE                  :
        	DrawStateJpgPbUpdate();//DrawStateTVPhotoPBChangeFile();
        break;

        case EVENT_TV_BROWSER_KEY_PLAYBACK      :
#if 0  //Andy Liu TBD
            if(m_DelFile) {
                DrawStateTVMoviePBDel(m_DelFile+2);
                break;
            }
#endif
        break;

        case EVENT_TV_CHANGE_MODE_INIT          :
        	OSDDraw_EnterDrawing(&bID0, &bID1);
			AHC_OSDSetActive(bID0, 0);
			AHC_OSDSetActive(bID1, 0);
			DrawStatePhotoPbInit_Tv(bID0, bID1);
			AHC_OSDSetActive(bID0, 1);
			AHC_OSDSetActive(bID1, 1);
			OSDDraw_ExitDrawing(&bID0, &bID1);
        break;

        case EVENT_MOVPB_UPDATE_MESSAGE			:
        break;

        default:
        break;
    }
    //OSDDraw_ExitDrawing(&bID0, &bID1);

#endif
}
