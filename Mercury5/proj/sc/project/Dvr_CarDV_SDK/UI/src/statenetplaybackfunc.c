#if defined(WIFI_PORT) && (WIFI_PORT == 1)
/*===========================================================================
 * Include files
 *===========================================================================*/
#include "Customer_config.h"

#include "ahc_general.h"
#include "ahc_message.h"
#include "ahc_display.h"
#include "ahc_menu.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_media.h"
#include "ahc_os.h"
#include "ahc_fs.h"
#include "ahc_warningmsg.h"
#include "ahc_usb.h"
#include "ahc_general_cardv.h"
#include "ahc_general.h"
#include "ahc_stream.h"
#include "ahc_wireless.h"
#include "IconPosition.h"
#include "ColorDefine.h"
#include "IconPosition.h"
#include "keyparser.h"

#include "MenuDrawCommon.h"
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "netapp.h"
#include "amn_config.h"
#include "statenetplaybackfunc.h"
#if defined(SPEECH_RECOGNIZE_EN) && (SPEECH_RECOGNIZE_EN)
#include "3rd_speech.h"
#include "mmpd_audio.h"
#include "mmpf_ringbuf.h"
#endif
/*===========================================================================
 * Macro define
 *===========================================================================*/
#define NET_PLAYBACK_HEARTBEAT_COUNTER	(5)	//50 seconds
#define NET_PLAYBACK_TIMER_UNIT         (10000)//unit :ms
#define NET_PLAYBACK_TIMEOUT_NEW_METHOD
/*===========================================================================
 * Global variable
 *===========================================================================*/
static UINT32	gulheartbeatcounter = NET_PLAYBACK_HEARTBEAT_COUNTER;
static UINT8	gNetPlaybackTimerID = AHC_OS_CREATE_TMR_INT_ERR;
static UINT32	gulBackUpAppTimeout;
/*===========================================================================
 * Extern variable
 *===========================================================================*/

extern AHC_BOOL bForce_PowerOff ;
extern AHC_BOOL gbAhcDbgBrk;
/*===========================================================================
 * Extern Function
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/
static void NetPlaybackTimerCB(void *tmr, void *arg)
{
#if defined (NET_PLAYBACK_TIMEOUT_NEW_METHOD)
	if(uiIsAppTimeOut())
		AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, EVENT_NET_EXIT_PLAYBACK, 0);
#else
	OS_CRITICAL_INIT();

	OS_ENTER_CRITICAL();
	if(gulheartbeatcounter)
		gulheartbeatcounter--;
	OS_EXIT_CRITICAL();
	if(gulheartbeatcounter == 0)
		AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, EVENT_NET_EXIT_PLAYBACK, 0);
#endif
}

static AHC_BOOL NetPlaybackTimer_Start(void)
{
    if (AHC_OS_CREATE_TMR_INT_ERR == gNetPlaybackTimerID) {
        gulheartbeatcounter = NET_PLAYBACK_HEARTBEAT_COUNTER;
        gNetPlaybackTimerID = AHC_OS_StartTimer( NET_PLAYBACK_TIMER_UNIT, AHC_OS_TMR_OPT_PERIODIC, NetPlaybackTimerCB, (void*)NULL );
		printc(FG_GREEN("NetPlaybackTimer_Start: gNetPlaybackTimerID =0x%X\r\n"), gNetPlaybackTimerID);
        if(AHC_OS_CREATE_TMR_INT_ERR == gNetPlaybackTimerID) {
            printc(FG_RED("Start Net playback Timer fail - 0x%X!!!")"\r\n", gNetPlaybackTimerID);
            return AHC_FALSE;
        }
    }

    return AHC_TRUE;
}

static AHC_BOOL NetPlaybackTimer_Stop(void)
{
    UINT8 ret = 0;

    if (AHC_OS_CREATE_TMR_INT_ERR != gNetPlaybackTimerID) {

        printc(FG_GREEN("NetPlaybackTimer_Stop: gNetPlaybackTimerID =0x%X\r\n"), gNetPlaybackTimerID);

        ret = AHC_OS_StopTimer( gNetPlaybackTimerID, AHC_OS_TMR_OPT_PERIODIC );
        gNetPlaybackTimerID = AHC_OS_CREATE_TMR_INT_ERR;

        if(ret) {
            printc(FG_RED("Stop Net playback Timer fail !!!")"\r\n");
            return AHC_FALSE;
        }
    }

    return AHC_TRUE;
}

static void Draw_NetPlayback(void)
{
	UINT8			bID0;
    UINT8			bID1;
    UINT16      	OSDWidth,OSDHeight,OSDColor;
    UINT32      	OSDAddr;
    UINT16			MaxBarLine = 135;
    UINT16			BarLineStartX = 90;
    UINT16			BarLineStartY = 110;
    const GUI_FONT  *pGuiFont = &GUI_Font20B_ASCII;
	AHC_DISPLAY_OUTPUTPANEL  OutputDevice;

    if (AHC_FALSE == AIHC_GetOSDInitStatus()) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,0); return; }

    OSDDraw_EnterDrawing(&bID0, &bID1);
    BEGIN_LAYER(bID0);

	AHC_OSDGetBufferAttr(bID0,&OSDWidth,&OSDHeight,&OSDColor,&OSDAddr);
    AHC_GetDisplayOutputDev(&OutputDevice);

	BarLineStartX = (AHC_GET_ATTR_OSD_W(bID0) - MaxBarLine) >> 1;
    BarLineStartY = (AHC_GET_ATTR_OSD_H(bID0) - 20) >> 1;

	AHC_OSDSetColor(bID0, OSD_COLOR_BLACK);
	AHC_OSDSetBkColor(bID0, OSD_COLOR_BLACK);
	#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
	AHC_OSDDrawFillRect(bID0, 0, 0, OSDWidth, OSDHeight);
	#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
	AHC_OSDDrawFillRect(bID0, 0, 0, OSDHeight, OSDWidth);
	#endif

    //Draw Text
    AHC_OSDSetColor(bID0, OSD_COLOR_WHITE);
    AHC_OSDSetBkColor(bID0, OSD_COLOR_BLACK);
	AHC_OSDSetFont(bID0, pGuiFont);
    AHC_OSDDrawText(bID0, (UINT8*)"Network playback", BarLineStartX, BarLineStartY, 1);

    OSDDraw_ExitDrawing(&bID0, &bID1);

	END_LAYER(bID0);
}

//void STATE_NET_PLAYBACK_DROP_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_DROP_EVENT)
{
    //Do nothing
}

//void STATE_NET_PLAYBACK_ENTER_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_ENTER_EVENT)
{
	/*
	The real case is : App carsh => reopen the App => enter browser page
	Feedback here,or app will stuck for 6 seconds.
	*/
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_HEARTBEAT)
{
	OS_CRITICAL_INIT();

	OS_ENTER_CRITICAL();
	//reset timer counter
	gulheartbeatcounter = NET_PLAYBACK_HEARTBEAT_COUNTER;
	OS_EXIT_CRITICAL();
}

//void STATE_NET_PLAYBACK_EXIT_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_EXIT_EVENT)
{
    /*if(uiGetLastState() == UI_CLOCK_SETTING_STATE)
    	StateSwitchMode(UI_CLOCK_SETTING_STATE);
    else*/
    	StateSwitchMode(UI_VIDEO_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

//void STATE_NET_PLAYBACK_DISCONNECT_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_DISCONNECT_EVENT)
{
    /*if(uiGetLastState() == UI_CLOCK_SETTING_STATE)
    	StateSwitchMode(UI_CLOCK_SETTING_STATE);
    else*/
    	StateSwitchMode(UI_VIDEO_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

//void STATE_NET_PLAYBACK_SD_REMOVE_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_SD_REMOVE_EVENT)
{
    if(AHC_TRUE == AHC_SDMMC_IsSD1MountDCF())
	{
		AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
		Enable_SD_Power(0 /* Power Off */);
	}
}

//void STATE_NET_PLAYBACK_SD_DETECT_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_SD_DETECT_EVENT)
{
    #if (FS_FORMAT_FREE_ENABLE)
    SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 0; //Reset it in case user plug-in correct card
    if( AHC_CheckMedia_FormatFree( AHC_MEDIA_MMC ) == AHC_FALSE )
    {
        SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 1;
    }
    else
    #endif
    {
    	AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
    }

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8 *) VIDEO_DEFAULT_FLIE_FREECHAR);
}

//void STATE_NET_PLAYBACK_USB_REMOVE_EVENT(UINT32 ulEvent, UINT32 ulParam)
DECL_AHC_EV_HANDLER(STATE_NET_PLAYBACK_USB_REMOVE_EVENT)
{
    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC mode
	{
		//AHC_SetMode(AHC_MODE_IDLE);
    	bForce_PowerOff = AHC_TRUE;
    	AHC_PowerOff_NormalPath();
	}
}

#if 0
void StateNetPlaybackMode(UINT32 ulEvent)
{
    UINT32      ulJobEvent = ulEvent;

    switch(ulJobEvent)
    {
    	case EVENT_NET_EXIT_PLAYBACK 			:

    		if(uiGetLastState() == UI_CLOCK_SETTING_STATE)
    			StateSwitchMode(UI_CLOCK_SETTING_STATE);
    		else
    			StateSwitchMode(UI_VIDEO_STATE);
    		CGI_SET_STATUS(ulJobEvent, 0 /* SUCCESSFULLY */)

    	break;
    	case EVENT_SD_REMOVED                     :

			if(AHC_TRUE == AHC_SDMMC_GetMountState())
			{
				AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
				Enable_SD_Power(0 /* Power Off */);
			}

        break;
    	case EVENT_SD_DETECT                      :
            #if (FS_FORMAT_FREE_ENABLE)
            SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 0; //Reset it in case user plug-in correct card
            if( AHC_CheckMedia_FormatFree( AHC_MEDIA_MMC ) == AHC_FALSE )
            {
                SystemSettingConfig()->byNeedToFormatMediaAsFormatFree = 1;
            }
            else
            #endif
            {
            	AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
            }

            AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8 *) VIDEO_DEFAULT_FLIE_FREECHAR);
        break;
        case EVENT_TV_DETECT                      :
        	if(AHC_IsTVConnectEx()) {
            	//SetTVState(AHC_TV_NET_PLAYBACK_STATUS);
            	StateSwitchMode(UI_TVOUT_STATE);
            }
        break;
    #if HDMI_ENABLE
        case EVENT_HDMI_DETECT                    :
        	//HDMIFunc_SetStatus(AHC_HDMI_NET_PLAYBACK_STATUS);
        	HDMIFunc_SetStatus(AHC_HDMI_VIDEO_PREVIEW_STATUS);
            StateSwitchMode(UI_HDMI_STATE);
            HDMIFunc_Enable(AHC_TRUE);
        break;
    #endif
        case EVENT_USB_REMOVED					:
        if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC mode
		{
			//AHC_SetMode(AHC_MODE_IDLE);
        	bForce_PowerOff = AHC_TRUE;
        	AHC_PowerOff_NormalPath();
		}
		break;
    }
}
#endif

AHC_BOOL StateNetPlaybackFuncInit(void* pData)
{
	UINT32 ulAppNewTimeout = NET_PLAYBACK_TIMER_UNIT;

    UartSendTrace("%s,%d \n", __FUNCTION__, __LINE__);

    #if defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN)//avoid conflicting with speech function
	MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_FALSE, MMP_FALSE);
    if (MMP_ERR_NONE != MMPS_LiveAudio_StopRecord()) {
        UartSendTrace(FG_RED("[ERR] Unable to stop audio encode\r\n"));
    }
    #endif
	{
		/*
		Fix for the operation :
		1.Turn on streaming via App
		2.Turn off wifi connection in the smart phone side
		3.Turn on wifi connection in the smart phone side
		4.Enter browser page in App
		Result : system hang up
		*/
		AHC_SetStreamingMode(AHC_STREAM_OFF);
	}
	AHC_SetMode(AHC_MODE_IDLE);
	//if come from JPEG playback state,must disable PIP window
    AHC_SetDisplayMode(DISPLAY_MODE_PIP_DISABLE);
    AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 0);
	Draw_NetPlayback();
	AHC_OSDSetActive(OVL_DISPLAY_BUFFER, 1);
	uiRefreshLastCgiTick();
	ncfg_get(NCFG_APP_TIMEOUT, &gulBackUpAppTimeout );
	ncfg_set(NCFG_APP_TIMEOUT, &ulAppNewTimeout );
	NetPlaybackTimer_Start();
    return AHC_TRUE;
}

AHC_BOOL StateNetPlaybackFuncShutDown(void* pData)
{
    UartSendTrace("%s,%d \n", __FUNCTION__, __LINE__);

	/*
	beacuase net may recive a command from App for accessing the rear cam directory,
	just reset rear cam flag here to ensure recording can work well.
	*/
	AHC_UF_SetRearCamPathFlag(AHC_FALSE);
	NetPlaybackTimer_Stop();
	ncfg_set(NCFG_APP_TIMEOUT, &gulBackUpAppTimeout );
#if defined(SPEECH_RECOGNIZE_EN)&&(SPEECH_RECOGNIZE_EN)//avoid conflicting with speech function
    MMPS_AUDIO_InitLiveRecord(MMP_AUDIO_PCM_ENCODE, 0, 16000, (MMP_LivePCMCB)Speech_PCMTransferCB);
    MMPS_LiveAudio_StartRecord();
    MMPD_Streaming_Enable(AUDIO_RING_STREAM, MMP_TRUE, MMP_TRUE);
#endif
    return AHC_TRUE;
}

UINT32 StateNetPlaybackModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
	UINT32 ulNetPlaybackEvent = 0;
    ulNetPlaybackEvent  = KeyParser_NetPlaybackEvent(ulMsgId, ulEvent, ulParam);
    printc("ulNetPlaybackEvent:%d\r\n", ulNetPlaybackEvent);
    StateModeDoHandlerEvent(AHLM_UI_NOTIFICATION, ulNetPlaybackEvent, ulParam);

    return 0;
}

AHC_BOOL StateSelectFuncNetPlaybackMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

	ahcRet = StateModeSetOperation(UI_NET_PLAYBACK_STATE, StateNetPlaybackFuncInit,
			 StateNetPlaybackFuncShutDown, StateNetPlaybackModeHandler);

   	RegisterEventCb(EVENT_DROP,							STATE_NET_PLAYBACK_DROP_EVENT);
   	RegisterEventCb(EVENT_NET_EXIT_PLAYBACK,			STATE_NET_PLAYBACK_EXIT_EVENT);
   	RegisterEventCb(EVENT_WIRELESS_CONNECT_FAIL,		STATE_NET_PLAYBACK_DISCONNECT_EVENT);
   	RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,			STATE_NET_PLAYBACK_ENTER_EVENT);
   	RegisterEventCb(EVENT_NET_PLAYBACK_HEARTBEAT,		STATE_NET_PLAYBACK_HEARTBEAT);
   	RegisterEventCb(EVENT_SD_REMOVED,					STATE_NET_PLAYBACK_SD_REMOVE_EVENT);
   	RegisterEventCb(EVENT_SD_DETECT,					STATE_NET_PLAYBACK_SD_DETECT_EVENT);
   	RegisterEventCb(EVENT_USB_REMOVED,					STATE_NET_PLAYBACK_USB_REMOVE_EVENT);

    return ahcRet;
}


#endif//#if defined(WIFI_PORT) && (WIFI_PORT == 1)
