////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_emapp_priv.h
*
* Class Id: CLSID_EMAPP
*
* @version $Id: mmi_em_priv.h 37347 2009-08-06 11:29:55Z lena.lin $
*/
#ifndef __MMI_EMAPP_PRIV_H__
#define __MMI_EMAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_e2p.ho"
#include "Vm_e2p_stack.ho"
#include "vm_e2p_app.ho"

#include "mmi_emapp.h"
#include "mmi_emapp_custom.h"
#include "mmi_baseapplet.h"
#include "mmi_util_ati.h"
#include "mmi_emapp_text.h"
#include "mmi_launcher_calibration.h"
#ifdef __STREAMING_MODULE__
#include "mmi_launcher_videoplayer.h"
#endif

#ifdef __PC_SIMULATOR__
#include <time.h> ///< for diagnosis features
#endif // __PC_SIMULATOR__

#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_base_util.h"
#include "mmi_emapp_id.h"
#include "emapp_resource.h"
#include "Mmimsg.h"

#ifdef __GPS_MMI__
#include "mmi_srv_gps.h"
#include "mmi_mae_gps.h"
#include "mmi_mae_gps_types.h"
#endif	//__GPS_MMI__

#ifdef __WLAN_MMI__
#include "esl_wifi_itf.h"
#include "mmi_wlansrv.h"
#endif

#ifdef __EM_AUDIO__
#include "em_audio_itf_pub.h"
#else
#include "em_itf_pub_types.h"
#include "em_itf_pub_api.h"
#endif

#ifndef __SDK_SIMULATION__
//Device info
#include "acc_task_pub_types.h"
#include "acc_task_pub_api.h"
#endif
#ifdef __APP_MMI_FM_RADIO__
#include "mmi_srv_fmradio.h"
#endif
#include "mmi_common_display.h"
#if defined(__ATV_MMI__)
#include "mmi_atvapp.h"
#endif

//Add a compiler option for CR0243535, [DSP audio] add new EM menu item to use test sequence to replace DL speech signal
//according to Clark Tseng,  in order to avoid using general defined(__SMALL_ROM__), add __EM_DSP_TESTSEQ__
//This new compiler option is not open to customer, and is used to exclude small rom case
#ifndef __SMALL_ROM__
#define __EM_DSP_TESTSEQ__
#endif


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_EM_IMEI_BUF_SIZE            (18)
#define MMI_EM_SN_BUF_SIZE              (21)
#define MMI_EM_BT_BUF_SIZE              (8)
#define MMI_EM_GPS_BUF_SIZE             (100)

#define MMI_EM_LCD_READREG_MAX_COUNT    30
#define MMI_EM_DEVICE_INFO_MAX_LEN      100
#define MMI_EM_PDP_APN_MAX_LENGTH       100
#define MMI_EM_MAX_AT_STRING_LEN        256
#define PDP_ADDRESS_LEN 4

#define MMI_EM_MENULIST_DIFFSIZE        (2)

#define MAX_DEFAULT_TEXT_NUM            (COMMON_NUM_TEXT_LABEL+256)  //use only for text test to finding missing unicode,reserve some buffer(256)
#define TXT_LABEL_NUMBER_START			256    //use only for text test to finding missing unicode
#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
#define MMI_EM_TOUCHPANEL_MAX_NUM_REDRAW (3)
#endif

#ifdef __ATV_MMI__
#define MMI_EM_ATV_DIALOG_TIMER             (2000)
#define MMI_EM_ATV_POLLING_STATUS_TIMER     (500)
/* The customer can input their switch channel timer. */
#define MMI_EM_ATV_SWITCH_CHANNEL_TIMER     (3000)
#define MMI_EM_CMMB_SWITCH_CHANNEL_TIMER    (3000)
#define MMI_EM_ISDBT_SWITCH_CHANNEL_TIMER   (5000)
#define MMI_EM_DTV_SWITCH_CHANNEL_MAX_NUM   (3)
#endif

#define MMI_EM_STEP_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                  (100)
#define MMI_EM_MIN_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                   (100)
#define MMI_EM_MAX_DEBOUNCE_TIME_FOR_MONITOR_NOTIFY                   (600)

#ifdef __APP_MMI_FM_RADIO__
/* The customer can input init fm radio parameter. */
#define FMRINIT_FREQUENCY 9420
#define FMRINIT_VOLUME (FMRADIOSRV_VOLUME_LEVEL__MIN+FMRADIOSRV_VOLUME_LEVEL__MAX)/2
#define FMR_EM_AUTO_LIST_MAX 100
#endif

#ifdef __WLAN_MMI__
#define EM_THROUGHPUT_IPERF_TX_PORT 5001
#define EM_THROUGHPUT_IPERF_RX_PORT 5002
#define EM_THROUGHPUT_RX_SAMPLE_INTERVAL 10
#define EM_THROUGHPUT_RX_SAMPLE_DURATION 90
#define EM_THROUGHPUT_REPEAT_TIME 20
#define EM_THROUGHPUT_MAX_IP_LEN 16
#endif

#define EM_FACTORY_RESET_FOR_TOOL_COMMAND_TYPE 1

#define ABS(a)           ((a)<0?-(a):(a))

#define __EM_KEYPAD_TEST_FUN__

//WIFI test Scan AP
//#define __EM_WIFI_SCAN_TEST__

#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MMI_EM_LEFT_TOP_DOT = 0,
    MMI_EM_LEFT_BOTTOM_DOT,
    MMI_EM_RIGHT_TOP_DOT,
    MMI_EM_RIGHT_BOTTOM_DOT,
    MMI_EM_MAX_DOT_NUM
} EmAppDotType_e;

typedef enum
{
    MMI_EM_MAIN_MENU_NONE = 0,
    MMI_EM_MAIN_MENU_NORMAL,
    MMI_EM_MAIN_MENU_FACTORY
} EmAppMainMenuType_e;

typedef enum
{
    MMI_EM_GPRS_PDP_HEADER_COMPRESSION_OFF = 0,
    MMI_EM_GPRS_PDP_HEADER_COMPRESSION_ON = 1
} EmAppGprsPdpHeaderCompression_e;

typedef enum
{
    MMI_EM_GPRS_PDP_DATA_COMPRESSION_OFF = 0,
    MMI_EM_GPRS_PDP_DATA_COMPRESSION_ON = 1
} EmAppGprsPdpDataCompression_e;

typedef enum
{
    MMI_EM_RES_WAITING = -2,
    MMI_EM_RES_CONTINUE = -1,
    MMI_EM_RES_FINISH = 0,
    MMI_EM_RES_ERROR = 1,
    MMI_EM_RES_END
} EmAppResRet_e;

typedef enum
{
    MMI_EM_FMRADIO_FOCUS_INPUT_WDG = 0,
    MMI_EM_FMRADIO_FOCUS_VIEW_ONLY_INPUT_WDG
} EmAppFmRadioFocusWidget_e;

typedef enum
{
    MMI_EM_WRITE_REGISTER_STATE_REGISTER = 0,
    MMI_EM_WRITE_REGISTER_STATE_VALUE = 1
} EmAppWriteRegisterState_e;

typedef enum
{
    MMI_EM_RESET_QOS_REQUEST_STATE = 0,
    MMI_EM_RESET_QOS_MINIMUM_STATE = 1
} EmAppResetQosState_e;

typedef enum
{
    MMI_EM_AT_COMMAND_STATE_INTERMEDIATE = 0,   //Query data
    MMI_EM_AT_COMMAND_STATE_COMMAND_RSP,        //Response OK or FAILURE
    MMI_EM_AT_COMMAND_STATE_UNSOLICITED         //Auto indicator
} EmAppAtCommandState_e;

typedef enum
{
    MMI_EM_BT_STATE_TURN_ON_BT = 0,             //Query data
    MMI_EM_BT_STATE_INQUIRY_DEV,
    MMI_EM_BT_STATE_WAIT_STOP_INQUIRY_CNF,
    MMI_EM_BT_STATE_TURN_OFF_BT_CNF,
    MMI_EM_BT_STATE_TEST_END
} EmAppBtState_e;

typedef enum
{
    MMI_EM_FMR_TEST_STATE_REQUEST_TURN_ON = 0,
    MMI_EM_FMR_TEST_STATE_ADJUSTING,
    MMI_EM_FMR_TEST_STATE_END
} EmAppFmrState_e;

typedef enum
{
    MMI_EM_BT_RF_TEST_IDLE = 0,
    MMI_EM_BT_RF_TEST_REQUEST,                  //Query data
    MMI_EM_BT_RF_TEST_END
} EmAppBtRfState;

typedef enum
{
    MMI_EM_FMR_RF_TEST_IDLE = 0,
    MMI_EM_FMR_RF_TEST_REQUEST_TURN_ON,
    MMI_EM_FMR_RF_TEST_REQUEST_FREQ,            //Query data
    MMI_EM_FMR_RF_TEST_BROADCAST,
    MMI_EM_FMR_RF_TEST_REQUEST_TURN_OFF,
    MMI_EM_FMR_RF_TEST_END
} EmAppFmrRfState_e;

typedef enum
{
    MMI_EM_FMR_RF_AUTO_LIST_TURN_ON = 0,
    MMI_EM_FMR_RF_AUTO_LIST_REQUEST_FREQ,       //Query data
    MMI_EM_FMR_RF_AUTO_LIST_AUTO_LIST,
    MMI_EM_FMR_RF_AUTO_LIST_END
} EmAppFmrRfAutoListState_e;

typedef enum
{
    MMI_EM_FMR_RF_AUTO_LIST_EX_INPUT = 0,
    MMI_EM_FMR_RF_AUTO_LIST_EX_TURN_ON,
    MMI_EM_FMR_RF_AUTO_LIST_EX_REQUEST_FREQ,       //Query data
    MMI_EM_FMR_RF_AUTO_LIST_EX_AUTO_LIST,
    MMI_EM_FMR_RF_AUTO_LIST_EX_END
} EmAppFmrRfAutoListExState_e;

typedef enum
{
    MMI_EM_HEADSET_TEST_STATE_DETECT = 0,
    MMI_EM_HEADSET_TEST_STATE_AUDIO_LOOP
} EmAppHeadsetTestState_e;

typedef enum
{
    MMI_EM_SD_TEST_STATE_DETECT = 0,
    MMI_EM_SD_TEST_STATE_RW_OPERATE,
    MMI_EM_SD_TEST_STATE_END
} EmAppSdTestState_e;

typedef enum
{
    MMI_EM_USB_TEST_STATE_DETECT = 0,
    MMI_EM_USB_TEST_STATE_END
} EmAppUsbTestState_e;

typedef enum
{
    MMI_EM_STATE_ON = 0,
    MMI_EM_STATE_OFF
} EmAppOnOffState_e;

typedef enum
{
    MMI_EM_TOUCH_PANEL_TEST_STATE_INITIAL = 0,
    MMI_EM_TOUCH_PANEL_TEST_STATE_LTRB_DRAW_DIAGONAL,   // draw left-top to right-bottom diagonal
    MMI_EM_TOUCH_PANEL_TEST_STATE_LTRB_TESTING,         // left-top to right-bottom testing
    MMI_EM_TOUCH_PANEL_TEST_STATE_RTLB_DRAW_DIAGONAL,   // draw right-top to left-bottom diagonal
    MMI_EM_TOUCH_PANEL_TEST_STATE_RTLB_TESTING,         // right-top to left-bottom testing
    MMI_EM_TOUCH_PANEL_TEST_STATE_END
} EmAppTouchPanelTestState_e;

#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
typedef enum
{
    MMI_EM_TOUCH_PANEL_DRAW_GRID_TEST,
#if defined(__HANDWRITING_MMI__)
    MMI_EM_TOUCH_PANEL_DRAW_POINTS_TEST,
    MMI_EM_TOUCH_PANEL_DRAW_CROSSLINE_TEST,
    MMI_EM_TOUCH_PANEL_DRAW_VLINE_TEST,
    MMI_EM_TOUCH_PANEL_DRAW_HLINE_TEST,
#endif
} EmAppTouchPanelEnhanceTest_e;
#endif

typedef enum
{
    MMI_EM_ATV_TEST_STATE_START = 0,
    MMI_EM_ATV_TEST_STATE_SWITCH_CHANNEL = 1,
    MMI_EM_ATV_TEST_STATE_END
} EmAppAtvState_e;

typedef enum
{
    MMI_EM_AUTO_TEST_ITEM_NONE,
    MMI_EM_AUTO_TEST_ITEM_FAIL,
    MMI_EM_AUTO_TEST_ITEM_PASS
} EmAppAutoTestItem_e;

typedef enum
{
    MMI_EM_AUDIO_TONE_GENERATOR_START = 0,
    MMI_EM_AUDIO_TONE_GENERATOR_PLAY = 1,
    MMI_EM_AUDIO_TONE_GENERATOR_STOP,
    MMI_EM_AUDIO_TONE_GENERATOR_END
} MMI_EM_AUDIO_TONE_STATE_e;

typedef enum
{
    MMI_EM_GPS_TEST_STATE_START = 0,
    MMI_EM_GPS_TEST_STATE_CONFIRM = 1,
    MMI_EM_GPS_TEST_STATE_GET_GPRMC,
    MMI_EM_GPS_TEST_STATE_GET_GPGSA,
    MMI_EM_GPS_TEST_STATE_GET_GPGSV,
    MMI_EM_GPS_TEST_STATE_GET_ALL,
    MMI_EM_GPS_TEST_STATE_ERROR,
    MMI_EM_GPS_TEST_STATE_END
} MMI_EM_GPS_STATE_e;

#ifdef __WLAN_MMI__
typedef enum
{
    MMI_EM_WLAN_TP_TEST_STATE_START = 0,
    MMI_EM_WLAN_TP_CREATE_DATALINK = 1,
    MMI_EM_WLAN_TP_CREATE_SOCKET,
    MMI_EM_WLAN_TP_DESTROY_SOCKET,
    MMI_EM_WLAN_TP_DESTROY_DATALINK,
    MMI_EM_WLAN_TP_TEST_STATE_END
} MMI_EM_WLAN_TP_STATE_e;
#endif  //__WLAN_MMI__

typedef enum
{
    MMI_EM_DRMP_RAI_OK = 0,
    MMI_EM_DRMP_RAI_SDINSERT = 1,
    MMI_EM_DRMP_RAI_NOMEMORY,
    MMI_EM_DRMP_RAI_RESULT_END
} MMI_EM_DRMP_RAI_RESULT_e;

#ifdef __BLUETOOTH_NEW_CONTINUOUS_TX_FEATURE__
typedef enum
{
    MMI_EM_BT_TEST_DATA_1MBPS = 0,
    MMI_EM_BT_TEST_DATA_2MBPS = 1,
    MMI_EM_BT_TEST_DATA_3MBPS
}MMI_EM_BT_TEST_DATA_MODE_e;

typedef enum
{
    MMI_EM_BT_TEST_PAYLOAD_ALL0 = 0,
    MMI_EM_BT_TEST_PAYLOAD_ALL1 = 1,
    MMI_EM_BT_TEST_PAYLOAD_11110000,
    MMI_EM_BT_TEST_PAYLOAD_10101010,
    MMI_EM_BT_TEST_PAYLOAD_PN9
}MMI_EM_BT_TEST_PAYLOAD_DATA_e;
#endif

typedef enum
{
        EM_AUDIO_TEST               ,
        EM_SPEAKER_TEST             ,
        EM_VIBRATE_TEST             ,
#ifdef __EM_KEYPAD_TEST_FUN__
        EM_KEYPAD_TEST              ,
#endif//__EM_KEYPAD_TEST_FUN__
        EM_BACKLIGHT_TEST           ,
        EM_LCD_TEST                 ,
#ifdef __D300_V2__
        EM_KEYPAD_LIGHT_TEST        ,
#endif
#ifdef __EM_CALIBRATE_TEST_IN_AUTO_TEST__
        EM_CALIBRATE_TEST           ,
#endif//__EM_CALIBRATE_TEST_IN_AUTO_TEST__
#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
        EM_TOUCH_PANEL_DRAWGRID_TEST,
#else //!defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
#if defined(__TOUCH_SCREEN_MMI__)
#if defined(__HANDWRITING_MMI__)
        EM_TOUCH_PANEL_TEST         ,
#else
        EM_TOUCH_PANEL_TEST_USE_CALIBRATE     ,
#endif
#endif
#endif //!defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
        EM_SD_TEST                  ,
#ifdef __DUAL_CARD__
        EM_SD2_TEST					,
#endif
        EM_CAMERA_TEST              ,
#ifdef __DUAL_CAMERA_MMI__
	 EM_CAMERA_TEST1           ,
#endif
#ifdef __EM_USB_TEST_AVAILABLE__
        EM_USB_TEST                 ,
#endif//__EM_USB_TEST_AVAILABLE__
        EM_HEADSET_TEST             ,
#ifdef __APP_MMI_FM_RADIO__
        EM_FMRADIO_TEST             ,
#endif
#ifdef __BLUETOOTH_MMI__
        EM_BT_TEST                  ,
#endif//__BLUETOOTH_MMI__

#ifdef __G_SENSOR_MMI__
       EM_GSENSOR_TEST              ,
#endif//__G_SENSOR_MMI__

#ifdef __ATV_MMI__
#ifdef __ATV_CMMB__
       EM_CMMB_TEST                 ,
#else // !__ATV_CMMB__
       EM_ATV_TEST                  ,
#ifdef __ATV_ISDBT__
       EM_ISDBT_TEST                ,
#endif // __ATV_ISDBT__
#endif // __ATV_CMMB__
#endif  //__ATV_MMI__

#ifdef __WLAN_MMI__
       EM_WIFI_TEST                  ,
#endif  //__WLAN_MMI__


       EM_AUTO_TEST_NUM

} EmAppAutoTestItems_e;

#define EM_NON_AUTO_TEST_ITEM_NUM (2)// 2means AUTO TEST+PROJECT VERSION
#define EM_AUTO_TEST_MENU_ITEMS_NUM (EM_AUTO_TEST_NUM+EM_NON_AUTO_TEST_ITEM_NUM)

#ifdef __3G_RIL_MMI__
typedef boolean (*EM_KEYPRESS_CB)(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
typedef void (*EM_EVENT_CB)(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
#endif //__3G_RIL_MMI__

typedef union
{
    MMSRV_CellInfoCnf_t             CellInfoCnf;
} MMSRV_Msg_t;

typedef struct
{
    IWidget *pIMenuWdg;
} EmAppMainList_t;

#ifdef __GPRS_MMI__
typedef struct
{
    //Mrl_GPRS_PDP_Ctx_t
    // pdp ctx param
    MMI_MMSRV_GPRS_PDP_Type_e mmi_em_pdptype;           //= 0;  // default is 0 : IP,  1 is PPP
    u8 mmi_em_pdpaddr[PDP_ADDRESS_LEN];                 //= {0, 0, 0, 0}; // default is 000.000.000.000
    u8 mmi_em_apn[MMI_EM_PDP_APN_MAX_LENGTH + 1];       //= {'A', 'P', 'N'}; // default is "APN"
    EmAppGprsPdpDataCompression_e mmi_em_dcomp;     //= 0;  // default is 0: OFF, 1 is ON
    EmAppGprsPdpHeaderCompression_e mmi_em_hcomp;   //= 0;  // default is 0: OFF, 1 is ON

    //Mrl_GPRS_SetQoSReq_t
    // pdp QoS requested param                          //
    u8 mmi_em_qosreq_prece;                             //= 0;
    u8 mmi_em_qosreq_delay;                             //= 0;
    u8 mmi_em_qosreq_relia;                             //= 0;
    u8 mmi_em_qosreq_peak;                              //= 0;
    u8 mmi_em_qosreq_mean;                              //= 0;
                                                        //
    // pdp QoS minimum param                            //
    u8 mmi_em_qosmin_prece;                             //= 0;
    u8 mmi_em_qosmin_delay;                             //= 0;
    u8 mmi_em_qosmin_relia;                             //= 0;
    u8 mmi_em_qosmin_peak;                              //= 0;
    u8 mmi_em_qosmin_mean;                              //= 0;
                                                        //
    // send config                                      //
    u32 mmi_em_send_datalen;                            //= 440;
    u16 mmi_em_send_num_repeat;                         //= 0;
    u16 mmi_em_send_iterator;                           //= 0;

    //Use in AT command
    MmiATHdl  mmi_EMATHdl;

} EmAppGsmGprs_t;
#endif //__GPRS_MMI__

#ifdef __GPS_MMI__
typedef struct
{
    s32					satID;			/**< satellite ID */
    s32					SNR;			/**< signal value */
    boolean				bIsFixed;		/**< if satellite is fixed*/
} EmAppGPSSatData_t;

typedef struct
{
    s32					fixMode;								/**< fix mode: 1=No, 2=2D, 3=3D */
    s32					latitude;								/**< latitude position: XXXX.XXXXXX */
    s8					northInd;								/**< North or South, 'N'=north, 'S'=south */
    s32					longitude;								/**< longitude position: XXXX.XXXXXX */
    s8					eastInd;								/**< West or East, 'W'=west, 'E'=east */
    s32					time;									/**< time: HHMMSS */
    s32					date;									/**< date: YYYYMMDD */
    s32					fixsatNum;								/**< satellite number */
    s32					fixsatID[GPS_PARSER_MAX_SAT_NUM];		/**< satellite ID array */
    s32					satNum;									/**< satellite number */
    EmAppGPSSatData_t	satView[GPS_PARSER_MAX_SAT_NUM];		/**< satellite information */
} MMI_EMAPP_GPS_INFO_t;
#endif

typedef struct
{
    MMSRV_Msg_t stMasterMsg;
    MMSRV_Msg_t stSlaveMsg;
    u8 u8DualMode;
} EmAppNetworkInfo_t;

#ifdef __APP_MMI_FM_RADIO__
typedef struct
{
    u32         FMRFrequency;
    u32         FMRVolume;
} EmAppRaiSetting_t;

typedef struct
{
    u16 FMRRSSI;
    u32 FMRFrequency;
} EmAppFmAutoListData_t;
#endif

#ifdef __WLAN_MMI__
typedef struct
{
    u32 nTpRepeatCnt;
    u32 nTpCurrTick;
    u32 nTpLastStampTick;
    u32 nTpSample;
    u32 nTpSizeStamp;
    u32 nTpSampleAcc;
    u32 nTpSampleCurrTime;
    u32 nTpSampleStartTime;
} EmAppWifiTPTestData_t;
#endif

typedef struct
{
    LCDSrv_BacklightLevel_e backlight_level;

#ifdef __APP_MMI_FM_RADIO__
    //FM Radio
    IWidget         *pInputWdg;
    IWidget         *pViewOnlyInputWdg;//View Only
    u32             FMRFrequency;
    u8              FMRVolume;          //FM Radio currenct volume
    u8              FMRSpeaker;
    u8             FMRChannelIndex;    //Channel index for FM Auto list
    //MMI_FMRADIOSRV_Status_e     FMRStatus;       //FM Radio stuas
    u8              FMRChannelNum;
    u8              *pRFPerfomaance;
    EmAppFmAutoListData_t *pChanInfo;
#ifdef __PC_SIMULATOR__
    clock_t         AutoListReqStart;
#else
    u32             AutoListReqStart;
#endif
#endif

#ifdef __BLUETOOTH_MMI__
    //BT
    boolean bFoundBTDev;
    boolean bNeedTurnOffBT;
#ifdef __BLUETOOTH_NEW_CONTINUOUS_TX_FEATURE__
    MMI_EM_BT_TEST_DATA_MODE_e eBtTestSetDataMode;
    MMI_EM_BT_TEST_PAYLOAD_DATA_e eBtTestPayloadData;
#endif
#endif

    u16         u16WriteValue;
    u8          u8WriteRegister;
    u8   u8State;
    u8   u8PressedKeyNum;

    //Calibration
    ModelListener_t stCalDataMdLsn;

    /////////////G Sensor//////////////
#ifdef  __G_SENSOR_MMI__
	u16             nAxisNum;
    u16				nSensitiveLevel;
    //////////4 way detector///////////
    u8				nGsensorResult;
    //////////motion detector//////////
    u32             nGsensorX;
    u32             nGsensorY;
    u8              nCount;
    ORIENTATION_e   eCurrentOrientation;
    u32             nCurrentTurnoverCnt;
    u32             nCurrentShackingCnt;
#endif  /* __G_SENSOR_MMI__ */
    //////////////////////////////////
#ifdef __ATV_MMI__
    boolean bIsATVPowerOn;
    boolean bIsATVPreviewOn;
    boolean bIsPollingTimerCreated;
    boolean bIsSwitchTimerCreated;
    boolean bBit2;
    boolean bIsWaitCnf;
    IView *pIView;
    u8 nTestMenuID;
    u8 nChannel;
    u8 nChannelIndex;
    u16 nTFValue;
    u16 nTGValue;
    ABL_TvRegion_e eTvRegion;
#ifdef __ATV_ISDBT__
    MAE_WChar wszChannelName[MMI_ATVAPP_CHANNEL_NAME_MAX+1];
#endif // __ATV_ISDBT__
#ifdef __ATV_CMMB__
    TvSrvCmmbTvInfo_t tCMMBTvInfo;
    ATVFrequency_t *pCMMBChannelInfo;
    u8 nCMMBChannelNumber;
#endif // __ATV_CMMB__
#endif  //__ATV_MMI__

#ifdef __GPS_MMI__
    MMI_EMAPP_GPS_INFO_t *pGPSInfo;
#endif	//__GPS_MMI__

#ifdef __WLAN_MMI__
    ABL_WiFiSetFwTestConfig_t   tWifiFwTstConf;
    ABL_WiFiSetHwReg_t          tWifiHwReg;
    ABL_WiFiSetRfReg_t          tWifiRFReg;
    ABL_WiFiSetRxFilter_t       tWifiRxFilter;
    MmlWlanSetAQUMem_t          tWifiAQUMem;
    MAE_WChar *pProductionResult;
    IWLANSRV *pWLANSrv;
    u32 nProductionTx;
    u32 nRfRegIdx;
    EmAppWifiTPTestData_t       tThroughPutData;
    u16 nConnectIP[4];
#endif

    char LcdWriteParam[MMI_EM_MAX_AT_STRING_LEN];
    char LcdReadParam[MMI_EM_MAX_AT_STRING_LEN];

} EmAppDriverInfo_t;

typedef struct
{
    boolean                 bStartAutoTest;
#if (defined(__TOUCH_SCREEN_MMI__) && defined(__HANDWRITING_MMI__))
    ModelListener_t         sHandWritingMdlLsn;
#endif
    EmAppAutoTestItem_e TestItems[EM_AUTO_TEST_NUM];
    EmAppTxtLabel_e     TestItemsFailResult[EM_AUTO_TEST_NUM];
    u8                      nTestItemIdx;
} EmAppAutoTestInfo_t;

typedef struct MMI_EMAPP_EMMI_DEBUG
{
    u32			u32FirstItemIndex;
#ifdef __EM_AUDIO__
    em_ProfileType_e		eProfile;			/**< 0:handset  1:headset  2:handsfree  3:bt */
    em_StereoFormat_e		eStereoType;		/**< 0:mp3  1:midi  2:amr  3:aac  4:3gp  5:wave  6:m2 pcm  7:fm  8:dtmf  9:atv  */
#endif
#if defined(__MMS_MMI_CDMMS__) && defined(__WAP_MMI__)  //This is only for sending MMS settings
    u32			nUnsent;	// Indicate how many callback not received
    MAE_Ret     nResult;
#endif
#ifdef __STREAMING_MODULE__
    MAE_WChar VideoStream[URL_MAX_LENGTH];
    VideoPlayerLauncherStreamingMode_e eStreamMode;
#endif
} MMI_EMAPP_EMMI_DEBUG_t;

typedef struct
{
    MAE_EventId EvtId;
    u32 Param1;
    u32 Param2;
} EmAppEventInfo_t;

typedef enum
{
    MMI_EM_CHECK_SYNC_EVENT = 0,
    MMI_EM_CHECK_ASYNC_EVENT,
    MMI_EM_CHECK_EDIT_EVENT
} EmAppCheckEventType_e;

typedef struct EM_Menu_Table_Info_TAG EM_Menu_Info_ti;
typedef struct EM_Menu_Item_Info_TAG EM_Menu_Item_Info_ti;

typedef enum
{
    EMAPP_MODE_NONE,
    EMAPP_MODE_LAUNCHAP,
    EMAPP_MODE_AUTOTEST
} EmAppModeId_e;

typedef struct
{
    u32 param1;
    u32 param2;
} EmAppParam_t;

typedef struct
{
    IView *pIView;
} EmAppEdit_t;

typedef struct
{
    boolean bWaitingDialog;
} EmAppAsyncInfo_t;

typedef struct
{
    IView *pIView;
} EmAppSyncInfo_t;

typedef struct
{
    u8 u8PressedKeyNum;

	boolean *pbKeyPressed;
	IWidget **ppKeyPadTextWdg;

} EmAppKeypadTest_t;

typedef struct
{
    IView *pIView;
} EmAppFmRadio_t;

#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
typedef struct
{
    u32 nWdgIdx;
    void *pUserData;
    WidgetHandler_t tWdgHandler;
    boolean bPressed;
}EmAppTPDrawGridTestData_t;

typedef struct
{
    u32 nDrawNum;
    u32 nCurDrawGridNum;
    u32 nTotalDrawGridNum;
    IWidget **ppBasicBitmapWdg;
    EmAppTPDrawGridTestData_t *pDrawGridData;
#if defined(__HANDWRITING_MMI__)
    IWidget *pHwWidget;
#endif
}EmAppTPEnhanceTest_t;
#endif //defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)

#if defined(__TOUCH_SCREEN_MMI__) && defined(__HANDWRITING_MMI__)
typedef struct
{
    IWidget         *pTextWdg;
    IWidget         *pHWWdg;
    ModelListener_t sHandWritingMdlLsn;
} EmAppTouchPanelTest_t;
#endif

#ifdef __MULTI_TOUCH__
typedef struct
{
    IWidget *pITextWidget;
    IWidget *pIFRQTextWidget;
}EmAppMultiTouchWdgList_t;

typedef struct
{
    EmAppMultiTouchWdgList_t tWdgList;
    int                      nEventCount;
    u32                      nSpecificEvt;
    u32                      nSpecificEvtCnt;
}MultiTouchWndData_t;

typedef struct
{
    IWidget *pMultiTouchTestWdg;
} TouchSrvWdgTestData_t;
#endif //__MULTI_TOUCH__

#ifdef __MULTI_TOUCH_SLIM__
typedef struct
{
    IWidget *pITextWidget;
}EmAppPinchTestWdgList_t;

typedef struct
{
    EmAppPinchTestWdgList_t  tWdgList;
    u32                      nPinchInEvtCnt;
    u32                      nPinchOutEvtCnt;
}PinchTestWndData_t;
#endif

typedef struct
{
    IView *pIView;
} EmAppSystemInfo_t;

typedef struct
{
    IWidget *pIInputWdg;
#ifndef __EM_KEYPAD_TEST_FUN__
    IWidget *pIEndKeyWdg;
    IWidget *pISendKeyWdg;
#endif//__EM_KEYPAD_TEST_FUN__
} EmAppDisplayAutoTestResult_t;

#ifdef __WLAN_MMI__
typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
} EmAppWifiTest_t;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pMenuWdg;
} EmAppWifiTestSetParam_t;
#endif

typedef struct
{
    IWidget *pIMenuWdg;
    boolean bShowMenuHistory;
} EmAppShowMenuHistory_t;

typedef struct
{
    IWidget *pOsdWidget;
    IWidget *pTfTextWidget;
    IWidget *pTgTextWidget;
    IWidget *pBit2TextWidget;
    IWidget *pChannelTextWidget;
} EmAppAtv_t;

typedef struct
{
    IWidget *pPickWidget;
} EmAppToneGenerator_t;

typedef struct
{
    IWidget *pTitleWdg;
    IWidget *pTextWdg;
    u32 nApIdx;
    u32 nTextIdx;
} EmAppTextWndData_t;

typedef struct
{
    MAE_WChar *pWStrResult;
    SoftkeyID_e eLSK;
    SoftkeyID_e eCSK;
    SoftkeyID_e eRSK;
} EmAppDisplayAutoTestResultParam_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    VectorClass_t *pIMenuHistoryVector;

    s32 s32StartReason;
    u32 u32State;                       //If EM Item have more than 1 states. we must use this.

    u16 u16InterruptLevel;

    bool    bProductMode;
    bool    bBetweenAutoTest;
    boolean bIsAutoTestRunning;         //Check if in auto test porcedure.
    boolean bFirstEnterProductMode;     //special case, if first jump to production menu, we should jump to auto test item automatically.
    u32     u32KeyCode;                 //Used in auto test procedure. this variable could use in program auto-dis
    EmAppTxtLang_e CurrentLang;     //To figure out which language used in auto test mode.

    const EM_Menu_Info_ti        *pCurrentMenuInfo;     //To figure out  current menu list information.
    const EM_Menu_Item_Info_ti   *pCurrentMenuItemInfo; //To figure out  current menu item information.

    boolean bDialogView;
    boolean bIgnoreEndKey;

    boolean bIsPreCard1Plug;
    boolean bIsPreCard2Plug;

    IWidget     *pIMenuWdg;
    IWidget     *pLcdBmpWdg;
#ifdef __GPRS_MMI__
    EmAppGsmGprs_t      *pMMIGSM_GPRS;//In dual mode this pointer point to pMMIGSM_GPRS_Master or pMMIGSM_GPRS_Slave
#endif //__GPRS_MMI__                                           //no need to release.
#ifdef __DUAL_SIM_MMI__
    boolean             bUseMasterSIM;
    boolean             bUseSlvaeSIM;
#ifdef __GPRS_MMI__
    EmAppGsmGprs_t      *pMMIGSM_GPRS_Master;
    EmAppGsmGprs_t      *pMMIGSM_GPRS_Slave;
#endif //__GPRS_MMI__
#endif
    EmAppNetworkInfo_t  *pMMINetworkInfo;
    EmAppDriverInfo_t   *pMMIDriverInfo;
    EmAppAutoTestInfo_t *pMMIAutoTest;
    MMI_EMAPP_EMMI_DEBUG_t		*pMMIEMMIDebug;

    EmAppDisplayAutoTestResultParam_t stDisplayAutoTestResultParam;
    EmAppParam_t stParam;
    EmAppModeId_e eMode;

    u32         u32FirstItemIndex;
    u32         u32HightlightItemIndex;

    //INPUT Info  Driver info mode
    IWidget     *pIInputWdg;
    boolean     bInEdit;
    boolean     bPopupSystemInfo;

    u32         u32SelectedItemIndexInTable;
    boolean     bIsUsedOfflineReq;

#if defined(__DUAL_CAMERA_MMI__)  && (defined(__ENABLE_CAMERA__) || defined(__ENABLE_CAMCORDER__))
    DualCameraType_e eCameraId;
    boolean     bNeedResetCamCfg;
#endif

#ifdef __GPS_MMI__
    u8 u8GpsRunCount;
    float fGpsMaxTime;
    float fGpsMinTime;
    float fGpsAvgTime;
#endif

	AudEnvSrvSpeakerType_e eSpkType;

#ifdef __3G_RIL_MMI__
    EM_KEYPRESS_CB emKeyPressCb;
    EM_EVENT_CB    emEventCb;
#endif //__3G_RIL_MMI__

#ifdef __TOUCH_SCREEN_FWUPDATE_MMI__
    u8* pFirmwareData;
#endif
} EmAppData_t;

#if !defined(__SDK_SIMULATION__)
typedef struct
{
    MAE_WChar *pWstrOutput;
    dev_DeviceInfoType_t eDeviceItem;
} EmAppDeviceInfoData_t;
#endif

/**
 *  @brief The enumeration defines the EM factory reset for tool return value
 */
typedef enum
{
  EM_RESET_RET_DEFAULT = 0,                     /**< Factory Reset Return Default */
  EM_RESET_RET_SUCCESS = EM_RESET_RET_DEFAULT,  /**< Factory Reset Return Success */
  EM_RESET_RET_NOT_SUPPOURT,                    /**< Factory Reset Return Not Support  */
  EM_RESET_RET_FAIL,                            /**< Factory Reset Return Fail  */
  EM_RESET_RET_MAX,
}em_FactoryResetReturn_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret EmAppConstructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
__DLM_EMAPP_FREE__ MAE_Ret EmAppDestructor(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppStartCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppKeyPressCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppResumeCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppSuspendCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppKeyLongPressCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppKeyRepeatCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppCellInfoCnfCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppHandleEvent(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppTouchPanelReleaseCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppTouchPanelSlideCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean EmAppHookDrawCb(IApplet *pApplet, u32 pDispInfo, u32 pRect, u32 bIsTopAp);
boolean EmAppPreHookCb(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
#if defined(__TOUCH_SCREEN_MMI__) && !defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
void EmAppLaunchCalibrationCb(void *pvUserData, MAE_Ret nRspCode, CalibrationAppLaunchRspData_t *psRspData, CalibrationAppRspDataFreeCb pfnDataFreeCb);
#endif
#ifdef __ATV_MMI__
#ifdef __ATV_CMMB__
boolean EmAppCMMBEvent(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
#else // !__ATV_CMMB__
boolean EmAppAtvEvent(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
#endif // __ATV_CMMB__
#endif // __ATV_MMI__
boolean EmAppBackHistory(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/
MAE_Ret _EmAppWndCreateMainList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyMainList(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowMainList(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideMainList(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateMenuHistory(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyMenuHistory(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowMenuHistory(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideMenuHistory(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateEdit(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyEdit(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowEdit(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideEdit(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateAsyncInfo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyAsyncInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowAsyncInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideAsyncInfo(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateSyncInfo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroySyncInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowSyncInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideSyncInfo(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateKeypadTest(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyKeypadTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowKeypadTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideKeypadTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndSetKeypadTest(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateFmRadio(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyFmRadio(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowFmRadio(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideFmRadio(void *pCusHandle, void *pWndData);

#if defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)
boolean _EmAppTouchPanelDrawGridTestHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
MAE_Ret _EmAppWndTouchPanelDrawTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndCreateTouchPanelDrawTest(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyTouchPanelDrawTest(void *pCusHandle, void *pWndData);

#else //!defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)

MAE_Ret _EmAppWndTouchPanelTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndCreateTouchPanelTest(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyTouchPanelTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowTouchPanelTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideTouchPanelTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndSetTouchPanelTest(void *pCusHandle, void *pWndData);
#endif //!defined(__EM_TOUCHSCREEN_TEST_ENHANCE__)

MAE_Ret _EmAppWndCreateSystemInfo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroySystemInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowSystemInfo(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideSystemInfo(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateATV(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyATV(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowATV(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideATV(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndSetATV(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateDisplayAutoTestResult(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyDisplayAutoTestResult(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowDisplayAutoTestResult(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideDisplayAutoTestResult(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndSetDisplayAutoTestResult(void *pCusHandle, void *pWndData);

#ifdef __WLAN_MMI__
MAE_Ret _EmAppWndCreateWifiTest(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyWifiTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowWifiTest(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideWifiTest(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndCreateWifiTestSetParam(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyWifiTestSetParam(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowWifiTestSetParam(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideWifiTestSetParam(void *pCusHandle, void *pWndData);
void _EmAppWifiTestSetParamSoftkeyActCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pReserve);
#endif

MAE_Ret _EmAppWndCreateToneGenerator(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDestroyToneGenerator(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndShowToneGenerator(void *pCusHandle, void *pWndData);
MAE_Ret _EmAppWndHideToneGenerator(void *pCusHandle, void *pWndData);

MAE_Ret _EmAppWndMainListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndMenuHistoryHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndEditHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndAsyncInfoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndSyncInfoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndKeypadTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndFmRadioHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndSystemInfoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndATVHdl(void *pWndHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndDisplayAutoTestResultHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndTextTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __WLAN_MMI__
MAE_Ret _EmAppWndWifiTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndWifiTestSetParamHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _EmAppWndToneGeneratorHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void EmAppDetectAccStatusCb(void *pApplet, ACCDeviceType_e eDeviceType, bool bPlug);

#ifdef __BLUETOOTH_MMI__
void EmAppBtPowerOnOffCnfCb(void *pApplet, BTSRV_StatusCode_e eResult, BTSRV_PowerAction_e eOnOffStatus);
void EmAppBtInquiryIndCb(void *pApplet, BTSRV_DevInfo_t *pBTDevInfo);
void EmAppBtInquiryCnfCb(void *pApplet, BTSRV_StatusCode_e eResult, u32 nNum);
#endif

void EmAppFmRadioTurnOnCnfCb(void *pApplet, MediaSrvErrCode_e nErrorCode);
void EmAppFmRadioTurnOffCnfCb(void *pApplet, MediaSrvErrCode_e nErrorCode);
void EmAppFmRadioSetFrequencyCnfCb(void *pApplet, MediaSrvErrCode_e nErrorCode);
void EmAppFmRadioSearchChannelCnfCb(void *pApplet, MediaSrvErrCode_e nErrorCode, FmradioSrvChannelInfo_t *pChanInfo);
void EmAppFmRadioGetChannelInfoCnfCb(void *pApplet, MediaSrvErrCode_e nErrorCode, FmradioSrvChannelInfo_t *pChanInfo);

void EmAppMobilityMgrCellInfoCnfCb(void *pApplet, MMSRV_CellInfoCnf_t *pData, MAE_DualMode_t eDualMode);
void EmAppMobilityMgrChangeBandCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#ifdef __GPRS_MMI__
void EmAppMobilityMgrGprsAttachCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
void EmAppMobilityMgrNetworkRegCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#ifdef __GPRS_MMI__
void EmAppMobilityMgrMsClassCnfCb(void *pApplet, MMSRV_MSClassCnf_t *pData, MAE_DualMode_t eDualMode);
void EmAppMobilityMgrGprsPdpContextActCnfCb(void *pApplet, MMSRV_GPRSPDPContextActCnf_t *pData, MAE_DualMode_t eDualMode);
void EmAppMobilityMgrGprsSetQosCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
void EmAppMobilityMgrGprsAddPDPContextCnfCb(void *pApplet, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
#endif //__GPRS_MMI__
#ifdef __WLAN_MMI__
void EmAppWifiDeleteFifoCb(u16 senderID, u32 userValue, esl_WifiErrCode_e errCode, esl_WifiInfo_t *pWifiInfo);
void EmAppWifiOffCb(u16 senderID, u32 userValue, esl_WifiErrCode_e errCode, esl_WifiInfo_t *pWifiInfo);
void EmAppWifiInitFifoCb(u16 senderID, u32 userValue, esl_WifiErrCode_e errCode, esl_WifiInfo_t *pWifiInfo);
void EmAppWifiAirplaneOnCb(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
void EmAppWifiAirplaneOffCb(void *pThis, MMI_MMSRV_Result_e eResult, MAE_DualMode_t eDualMode);
void EmAppWifiCreateDataLinkCb(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
void EmAppWifiDestroyDataLinkCb(IBase *piCaller, void *pvUserData, MAE_Ret nResult);
void EmAppWifiScanDoneCB(void *pCusHandle, ABL_WiFiScanResultData_t *pScanResultData, boolean bIsAutoConnect);
void EmAppWifiSocketConnectCb(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
void EMAPPSocketSendCb(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
void EMAPPSocketRecvCb(IBase *piCaller, SrvSocketHdl_t hSockets, u8 *buf, s32 len, void *pvUserData);
void EMAPPSocketDestroyCb(IBase *piCaller, SrvSocketHdl_t hSocket, void *pvUserData, MAE_Ret nResult);
#endif //__WLAN_MMI__

//Multi touch test
#ifdef __MULTI_TOUCH__
MAE_Ret _EmAppWndMultiTouchHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndCreateMultiTouch(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndTouchSrvWdgTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndCreateTouchSrvWdgTest(void *pCusHandle, void *pWndData, u32 nWndInitParam);
#endif
#ifdef __MULTI_TOUCH_SLIM__
MAE_Ret _EmAppWndPinchTestHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _EmAppWndCreatePinchTest( void *pCusHandle, void *pWndData, u32 nWndInitParam);
#endif
#endif /* __MMI_EMAPP_PRIV_H__ */
