
#ifndef __MMI_COMMON_CFG__H__
#define __MMI_COMMON_CFG__H__

//cb
#include "mmi_mae_common_def.h"
#include "mae_textlabel.h"
//cb end
//profile
#include "mmi_mae_filemgr.h"
//profile
#include "mmi_setting_cfg.h"/// setting
#include "mmi_common_sim.h" /// sim
#include "mmi_ttssrv.h"     /// tts service
#include "mmi_common_encoding.h"

//sim
#define MAX_STK_MENU_ITEM_LEN (15)
//sim end

//tts
#define TTS_PROMPT_TEXT_WCHAR_LEN (30)
#define TTS_PROMPT_TEXT_WCHAR_LEN_MIN (4)
//tts end

//call setting start
#define IPCALL_MAX_SET_NUM (10)
#define IPCALL_MAX_NAME_LEN (8)
#define IPCALL_MAX_NUM_LEN (5)
#define CBS_EFFECT_SOUND_MAX (20)
enum
{
    CALLSETTING_CALLER_IDENTITY_DEFAULT=0,
    CALLSETTING_CALLER_IDENTITY_ON=1,
    CALLSETTING_CALLER_IDENTITY_OFF=2
};
typedef u8 MMI_CALLSETTING_CALLER_IDENTITY_e;
enum
{
    CALLSETTING_ANSWER_MODE_ANY=0,
    CALLSETTING_ANSWER_MODE_SEND=1,
    CALLSETTING_ANSWER_MODE_FLIP=2
};
typedef u8 MMI_CALLSETTING_ANSWER_MODE_e;
enum
{
    CALLSETTING_AUTO_REDIAL_OFF=0,
    CALLSETTING_AUTO_REDIAL_ON=1
};
typedef u8 MMI_CALLSETTING_AUTO_REDIAL_e;
enum
{
    CALLSETTING_INCOMING_CALL_RECORD_OFF=0,
    CALLSETTING_INCOMING_CALL_RECORD_ON=1
};
enum
{
    CALLSETTING_ANSWER_IND_OFF=0,
    CALLSETTING_ANSWER_IND_RING=1,
    CALLSETTING_ANSWER_IND_VIBRATE=2,
    CALLSETTING_ANSWER_IND_BLINKING=3
};
typedef u8 MMI_CALLSETTING_ANSWER_INDICATOR_e;
typedef struct _IPCALL_SET_t
{
    MAE_WChar Name[IPCALL_MAX_NAME_LEN+1];
    u8 Number[IPCALL_MAX_NUM_LEN+1];
} IPCALL_SET_t;
enum
{
    CALLSETTING_DISTORTED_EFFECT_KID=0,
    CALLSETTING_DISTORTED_EFFECT_GIRL,
    CALLSETTING_DISTORTED_EFFECT_WOMAN,
    CALLSETTING_DISTORTED_EFFECT_YOUNGMAN,
    CALLSETTING_DISTORTED_EFFECT_MAN,
    CALLSETTING_DISTORTED_EFFECT_BASS,

	// total number
    CALLSETTING_DISTORTED_EFFECT_NUM
};
typedef u8 MMI_CALLSETTING_DISTORTED_EFFECT_e;
enum
{
    CBS_PLAY_TYPE_ONCE=0,
    CBS_PLAY_TYPE_REPEAT=1,
    CBS_PLAY_TYPE_INTERVAL=2,
};
typedef u8 CallBgSound_Play_Type_e;
//call setting end

// Voice Memo
enum
{
    VOICE_MEMO_AMR_QUALITY = 0,
    VOICE_MEMO_AWB_QUALITY,
    VOICE_MEMO_MP3_QUALITY,
    VOICE_MEMO_WAV_QUALITY,
    VOICE_MEMO_QUALITY_NUM
};
typedef u8 VOICE_MEMO_RECORD_Type_e;

//cb start
#define MSG_CB_SETTING_TOPIC_MAX_CHAR (20)
#define MSG_CB_SETTING_TOPIC_MAX_NUM (10)
enum
{
    Msg_CB_Reception_ON=0,
    Msg_CB_Reception_OFF=1,
    Msg_CB_Information_ON=2,
    Msg_CB_Information_OFF=3,
    Msg_CB_AutoDisplay_ON=4,
    Msg_CB_AutoDisplay_OFF=5
};
typedef u8 Msg_CB_Setting_e;
typedef struct _Msg_CB_Setting_Topic_Hdr_t
{
    u8 listNum;
} Msg_CB_Setting_Topic_Hdr_t;
typedef struct _Msg_CB_Setting_Topic_Item_t
{
    u32 nFromChannel;
    u32 nToChannel;
    MAE_WChar TopicName[MSG_CB_SETTING_TOPIC_MAX_CHAR+1];
    u8 eSingleChannel;
    u8 eTopicEnable;
} Msg_CB_Setting_Topic_Item_t;
typedef struct _Msg_CB_Setting_Topic_List_t
{
    Msg_CB_Setting_Topic_Hdr_t msgCbTopicLstHdr;
    Msg_CB_Setting_Topic_Item_t msgCbTopicItem[MSG_CB_SETTING_TOPIC_MAX_NUM];
} Msg_CB_Setting_Topic_List_t;
typedef struct _Msg_CB_Setting_Language_List_t
{
    Msg_CB_Setting_Topic_Hdr_t msgCbLangLstHdr;
    u8 msgCbLangItem[MSG_CB_SETTING_TOPIC_MAX_NUM];
} Msg_CB_Setting_Language_List_t;
//cb  end

//common
#define MAX_PHONE_ECC_LEN (6)
#define MAX_PHONE_ECC_NUM (5)
enum
{
    FEATURE_DUAL_SIM_DISABLE=0,
    FEATURE_DUAL_SIM_ENABLE=1
};
typedef u8 FeatureDualSIM_e;
typedef struct _PhoneEccList_t
{
    u8 nPhoneEccNum;
    u8 au8PhoneEccList[MAX_PHONE_ECC_NUM][MAX_PHONE_ECC_LEN+1];
} PhoneEccList_t;
//common end

enum
{
    Msg_SMS_BlackList_Status_On=1,
    Msg_SMS_BlackList_Status_Off=0
};
typedef u8 Msg_SMS_Setting_BlackList_Status_e; // add by dongnan

#ifdef __MMI_CALL_FIREWALL__
enum
{
	FIREWALL_ANSWERING_TYPE_DEFAULT = 0,
    FIREWALL_ANSWERING_TYPE_BUSY,
    FIREWALL_ANSWERING_TYPE_INEXISTENT_NUMBER,
    FIREWALL_ANSWERING_TYPE_POWEROFF,
    FIREWALL_ANSWERING_TYPE_OUT_OF_SERVICE,
    FIREWALL_ANSWERING_TYPE_NUM
};
typedef u8 Firewall_Answering_Type_e;

enum
{
    FIREWALL_FILTER_TYPE_DENY_BLACKLIST_ONLY = 0,
    FIREWALL_FILTER_TYPE_ALLOW_CONTACT_ONLY,
    FIREWALL_FILTER_TYPE_DENY_ALL,
    FIREWALL_FILTER_TYPE_NUM
};
typedef u8 Firewall_Filter_Type_e;
#endif

//consetting
#ifdef __APP_MMI_SMALLROM__
#define MAX_NUM_DATA_ACCOUNT (5)
#define MAX_NUM_WAP_PROFILE (2)
#define MAX_NUM_MMS_PROFILE (2)
#define MAX_NUM_JAVA_PROFILE (2)
#define MAX_NUM_OTHER_PROFILE (2)
#define MAX_NUM_LBS_PROFILE (2)
#define MAX_NUM_EMAIL_PROFILE (2)
#define MAX_NUM_QQ_PROFILE (2)
#define MAX_NUM_STREAMING_PROFILE (2)
#define MAX_NUM_NTP_PROFILE (2)
#else
#define MAX_NUM_DATA_ACCOUNT (9)
#define MAX_NUM_WAP_PROFILE (9)
#define MAX_NUM_MMS_PROFILE (9)
#define MAX_NUM_JAVA_PROFILE (9)
#define MAX_NUM_OTHER_PROFILE (9)
#define MAX_NUM_LBS_PROFILE (9)
#define MAX_NUM_EMAIL_PROFILE (9)
#define MAX_NUM_QQ_PROFILE (9)
#define MAX_NUM_STREAMING_PROFILE (9)
#define MAX_NUM_NTP_PROFILE (9)
#endif
#define NameLength (30)
#define PasswordLength (30)
#define DialNumberLength (20)
#define IPAddressSize (4)
#define PortLength (4)
#define URL_MAX_LENGTH (1024)
#define HomePageLength (URL_MAX_LENGTH)
#define MMSCLength (50)

enum
{
    GPRS_E_SETTINGS_START=0,
    GPRS_E_ALWAYS=GPRS_E_SETTINGS_START,
    GPRS_E_WHEN_NEEDED=1,
    GPRS_E_SETTINGS_TOTAL=2
};
typedef u8 ConSetting_GPRS_e;
enum
{
    DATA_ACCOUNT_E_GPRS_AUTH_TYPE_START=0,
    DATA_ACCOUNT_E_GPRS_AUTH_TYPE_NORMAL=DATA_ACCOUNT_E_GPRS_AUTH_TYPE_START,
    DATA_ACCOUNT_E_GPRS_AUTH_TYPE_SECURE=1,
    DATA_ACCOUNT_E_GPRS_AUTH_TYPE_TOTAL=2
};
typedef u8 DataAccount_GPRS_Type_e;
enum
{
    DATA_ACCOUNT_E_CSD_LINE_START=0,
    DATA_ACCOUNT_E_CSD_LINE_ANALOGUE=DATA_ACCOUNT_E_CSD_LINE_START,
    DATA_ACCOUNT_E_CSD_LINE_ISDN=1,
    DATA_ACCOUNT_E_CSD_LINE_TOTAL=2
};
typedef u8 DataAccount_CSD_LineType_e;
enum
{
    DATA_ACCOUNT_E_CSD_SPEED_START=0,
    DATA_ACCOUNT_E_CSD_SPEED_4_8_KPBS=DATA_ACCOUNT_E_CSD_SPEED_START,
    DATA_ACCOUNT_E_CSD_SPEED_9_6_KPBS=1,
    DATA_ACCOUNT_E_CSD_SPEED_14_4_KPBS=2,
    DATA_ACCOUNT_E_CSD_SPEED_TOTAL=3
};
typedef u8 DataAccount_CSD_Speed_e;
enum
{
    CONNECTION_TYPE_E_START=0,
    CONNECTION_TYPE_E_CONNECTION_ORIENTED=CONNECTION_TYPE_E_START,
    CONNECTION_TYPE_E_HTTP=1,
    CONNECTION_TYPE_E_TOTAL=2
};
typedef u8 Connection_Type_e;
typedef u8 SortIdx;
typedef struct _Data_Account_t
{
    boolean bCSD;
    MAE_WChar AccountName[NameLength];
    MAE_WChar APN[NameLength];
    MAE_WChar DialNumber[DialNumberLength];
    MAE_WChar UserName[NameLength];
    MAE_WChar Password[PasswordLength];
    u8 DNS[IPAddressSize];
    DataAccount_GPRS_Type_e AuthType;
    DataAccount_CSD_LineType_e LineType;
    DataAccount_CSD_Speed_e Speed;
    u8 u8Pad;
} Data_Account_t;
typedef struct _WAP_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar HomePage[HomePageLength];
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 u8Pad[3];
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} WAP_Profile_t;
typedef struct _MMS_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar MMSC[MMSCLength];
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 u8Pad[3];
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} MMS_Profile_t;
typedef struct _Java_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} Java_Profile_t;
typedef struct _Other_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} Other_Profile_t;
typedef struct _LBS_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} LBS_Profile_t;

typedef struct _EMAIL_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    u8 u8Pad[3];
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} Email_Profile_t;

#ifdef __NCCQQ_MMI__
typedef struct _QQ_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    u8 u8Pad[3];
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} QQ_Profile_t;
#endif // __NCCQQ_MMI__


#ifdef __APP_MMI_NTP__
typedef struct _NTP_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    u8 u8Pad[3];
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} NTP_Profile_t;

enum
{
	NTP_SERVER_NTSC = 0,
    NTP_SERVER_MICROSOFT
};
typedef u8 NTP_ServerSetting_e;

#endif // __APP_MMI_NTP__


#ifdef __STREAMING_MODULE__
typedef struct _Streaming_Profile_t
{
    MAE_WChar ProfileName[NameLength];
    u32 DataAccount;
    MAE_WChar Port[PortLength];
    u8 Proxy[IPAddressSize];
    Connection_Type_e ConnType;
    u8 MccMnc1[7];
    u8 MccMnc2[7];
    u8 MccMnc3[7];
} Streaming_Profile_t;
#endif
//consetting end

//mplayer
enum
{
    MMI_MPLAYER_SHUFFLE_ON=0,
    MMI_MPLAYER_SHUFFLE_OFF=1,
    MMI_MPLAYER_SHUFFLE_NO=2
};
typedef u8 MPlayer_Shuffle_e;
enum
{
    MMI_MPLAYER_REPEAT_OFF=0,
    MMI_MPLAYER_REPEAT_ONE=1,
    MMI_MPLAYER_REPEAT_ALL=2,
    MMI_MPLAYER_REPEAT_NO=3
};
typedef u8 MPlayer_Repeat_e;
enum
{
    MMI_MPLAYER_EQ_NORMAL=0,
    MMI_MPLAYER_EQ_BASS=1,
    MMI_MPLAYER_EQ_CLASSIC=3,
    MMI_MPLAYER_EQ_TREBLE=2,
    MMI_MPLAYER_EQ_LIVE=5,
    MMI_MPLAYER_EQ_ROCK=4,
    MMI_MPLAYER_EQ_NO=6
};
typedef u8 MPlayer_EQ_e;
enum
{
    MMI_MPLAYER_BackgroundPlay_ON=0,
    MMI_MPLAYER_BackgroundPlay_OFF=1,
    MMI_MPLAYER_BackgroundPlay_NO=2
};
typedef u8 MPlayer_BackgroundPlay_e;
enum
{
    MMI_MPLAYER_3DSurround_ON=0,
    MMI_MPLAYER_3DSurround_OFF=1,
    MMI_MPLAYER_3DSurround_NO=2
};
typedef u8 MPlayer_3DSurround_e;
enum
{
    MMI_MPLAYER_TimeStretch_x05=0,
    MMI_MPLAYER_TimeStretch_x075,
    MMI_MPLAYER_TimeStretch_x1,
    MMI_MPLAYER_TimeStretch_x15,
    MMI_MPLAYER_TimeStretch_x2,
    MMI_MPLAYER_TimeStretch_NO
};
typedef u8 MPlayer_TimeStretch_e;
enum
{
    MMI_MPLAYER_Reverb_NONE=0,
    MMI_MPLAYER_Reverb_CHURCH,
    MMI_MPLAYER_Reverb_BATHROOM,
    MMI_MPLAYER_Reverb_MEDIUMCONCERT,
    MMI_MPLAYER_Reverb_SMALLCLUB,
    MMI_MPLAYER_Reverb_CAVE,
    MMI_MPLAYER_Reverb_NO
};
typedef u8 MPlayer_Reverb_e;
enum
{
    MMI_MPLAYER_PitchShidt_OFF=0,
    MMI_MPLAYER_PitchShidt_LEVEL_1,
    MMI_MPLAYER_PitchShidt_LEVEL_2,
    MMI_MPLAYER_PitchShidt_LEVEL_3,
    MMI_MPLAYER_PitchShidt_LEVEL_4,
    MMI_MPLAYER_PitchShidt_LEVEL_5,
    MMI_MPLAYER_PitchShidt_LEVEL_6,
    MMI_MPLAYER_PitchShidt_LEVEL_NO
};
typedef u8 MPlayer_PitchShift_e;
enum
{
    MMI_MPLAYER_DOLBY_ON=0,
    MMI_MPLAYER_DOLBY_OFF=1,
    MMI_MPLAYER_DOLBY_NO=2
};
typedef u8 MPlayer_Dolby_e;
enum
{
    MMI_MPLAYER_Lyric_ON=0,
    MMI_MPLAYER_Lyric_OFF=1,
    MMI_MPLAYER_Lyric_NO=2
};
typedef u8 MPlayer_Lyric_e;
enum
{
    MMI_MPLAYER_VolLevel_Min=0,
    MMI_MPLAYER_VolLevel_0=MMI_MPLAYER_VolLevel_Min,
    MMI_MPLAYER_VolLevel_1=1,
    MMI_MPLAYER_VolLevel_2=2,
    MMI_MPLAYER_VolLevel_3=3,
    MMI_MPLAYER_VolLevel_4=4,
    MMI_MPLAYER_VolLevel_5=5,
    MMI_MPLAYER_VolLevel_6=6,
    MMI_MPLAYER_VolLevel_7=7,
    MMI_MPLAYER_VolLevel_8=8,
    MMI_MPLAYER_VolLevel_Max=MMI_MPLAYER_VolLevel_8
};
typedef u8 MPlayer_VolLevel_e;
#if defined(ENABLE_SRSWOWHD)
enum
{
    MMI_MPLAYER_SRS_OFF=0,
    MMI_MPLAYER_SRS_ON=1,
    MMI_MPLAYER_SRS_NO=2
};
typedef u8 MPlayer_SRS_e;
enum
{
    MMI_MPLAYER_SRS_TYPE_NORMAL=0,
    MMI_MPLAYER_SRS_TYPE_CLASSIC=1,
    MMI_MPLAYER_SRS_TYPE_BASS=2,
    MMI_MPLAYER_SRS_TYPE_HIPHOP=3,
    MMI_MPLAYER_SRS_TYPE_PERFORM=4,
    MMI_MPLAYER_SRS_TYPE_NO=5
};
typedef u8 MPlayer_SRS_Type_e;
enum
{
    MMI_MPLAYER_SRS_PARAM_3DSPACE=0,
    MMI_MPLAYER_SRS_PARAM_3DCENTER=1,
    MMI_MPLAYER_SRS_PARAM_TRUBASS=2,
    MMI_MPLAYER_SRS_PARAM_FOCUS=3,
    MMI_MPLAYER_SRS_PARAM_DEFINITION=4,
    MMI_MPLAYER_SRS_PARAM_NO=5,
};
typedef u8 MPlayer_SRS_Param_e;
typedef struct _MPlayer_SRS_Param_t
{
    u32 n3DSpace;
    u32 n3DCenter;
    u32 nTruBass;
    u32 nFocus;
    u32 nDefinition;
} MPlayer_SRS_Param_t;
#define MPLAYER_SRS_PARAM_LEVEL_MAX     (10)
#define MPLAYER_SRS_PARAM_LEVEL_BOUND   (MPLAYER_SRS_PARAM_LEVEL_MAX+1)
#endif // defined(ENABLE_SRSWOWHD)

enum
{
    MMI_MPLAYER_VirtualBass_ON=0,
    MMI_MPLAYER_VirtualBass_OFF=1,
    MMI_MPLAYER_VirtualBass_NO=2
};
typedef u8 MPlayer_VirtualBass_e;
//mplayer end

//onoffapp
#define ONOFFAPP_MAX_POOL_NUMBER (10)
enum
{
    LockCheckPoint_VerifyPINLock=0,
    LockCheckPoint_VerifySIMLock=1,
    LockCheckPoint_VerifyNetworkLock=2,
    LockCheckPoint_VerifyPhoneLock=3,
    LockCheckPoint_AllVerified=4
};
typedef u32 LockCheckPoint_e;
enum
{
    ONOFFAPP_OnProcessCheckPoint_CheckBattery=0,
    ONOFFAPP_OnProcessCheckPoint_OffCharging
};
typedef u8 ONOFFAPP_OnProcessCheckPoint_e;
typedef struct _ONOFFAPP_Pool_Status_t
{
    u16 au16STKPoolStatus[ONOFFAPP_MAX_POOL_NUMBER];
    u16 au16CUSPoolStatus[ONOFFAPP_MAX_POOL_NUMBER];
} ONOFFAPP_Pool_Status_t;
//onoffapp end

//profile
enum
{
    PROFILESRV_ID_FIRST=0,
    PROFILESRV_ID_NONE=0,
    PROFILESRV_ID_GENERAL=1,
    PROFILESRV_ID_MEETING=2,
    PROFILESRV_ID_OUTDOOR=3,
    PROFILESRV_ID_SILENT=4,
    PROFILESRV_ID_PERSONAL=5,
    PROFILESRV_ID_HEADSET=6,
    PROFILESRV_ID_BLUETOOTH=7,
    PROFILESRV_ID_POWER_SAVING=8,
    PROFILESRV_ID_LAST=9,
};
typedef u8 ProfileID_e;
typedef struct _ProfileSettings_t
{
    SetVibrateType_e eVibrateType;
    SetRingToneVolume_e eVolume;
    SetOnOff_e ePowerOnTone;
    SetOnOff_e ePowerOffTone;
    SetRingToneRingType_e eRingingType;
    SetRingToneMessageTone_e eMessageTone;
    SetRingToneCalendarTone_e eCalendarTone;
    SetRingToneAlarmTone_e eAlarmTone;
    SetOnOff_e eMissEventReminder;
    SetRingToneKeypadTone_e eKeypadTone;
    SetRingToneSlideTone_e eSlideTone;
    boolean eAutoAnswer;
    MAE_WChar stVoiceCallRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
#ifdef __DUAL_PROFILE_MMI__
    MAE_WChar stSIM2VoiceCallRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
#endif
    MAE_WChar stMessageRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
#ifdef __DUAL_PROFILE_MMI__
	MAE_WChar stSIM2MessageRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
#endif
    MAE_WChar stCalendarRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar stAlarmRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar stPowerOnRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
    MAE_WChar stPowerOffRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
} ProfileSettings_t;
//profile end

//wlan
enum
{
    WLANSRV_SHOW_WLAN_OFF=0,
    WLANSRV_SHOW_WLAN_SCAN=1,
    WLANSRV_SHOW_WLAN_SCANCONNECT=2,
    WLANSRV_SHOW_WLAN_FORCESCAN=3
};
typedef u8 WLANSRV_ShowWLAN_e;
enum
{
    WLANSRV_POWER_STATUS_OFF=0,
    WLANSRV_POWER_STATUS_ON=1,
    WLANSRV_POWER_STATUS_TURNING_ON=2
};
typedef u8 WLANSRV_PowerStatus_e;
enum
{
    WLANSRV_SCAN_NETWORK_10SEC=0,
    WLANSRV_SCAN_NETWORK_20SEC=1,
    WLANSRV_SCAN_NETWORK_30SEC=2,
    WLANSRV_SCAN_NETWORK_45SEC=3,
    WLANSRV_SCAN_NETWORK_1MIN =4,
    WLANSRV_SCAN_NETWORK_2MIN =5,
    WLANSRV_SCAN_NETWORK_5MIN =6,
    WLANSRV_SCAN_NETWORK_10MIN=7
};
typedef u8 WLANSRV_ScanNetwork_e;
enum
{
    ConnectSet_WiFi_Only=0,
    ConnectSet_GPRS_Only=1,
    ConnectSet_WiFi_Preferred=2,
    ConnectSet_GPRS_Preferred=3
};
typedef u8 ConSetting_ConnectSet_e;

//wlan end

#ifdef __SMART_DIALER__
typedef struct _SmartSearchType_t
{
    boolean IsTypeLetter;
    boolean IsTypeNUM;
    boolean IsTypePinYin_First;
    boolean IsTypeStrokes;
}SmartSearchType_t;
#endif

// band selection
#ifdef __3G_RIL_MMI__
enum
{
    BandSelection_Auto=0,
    BandSelection_3G_Only=1,
    BandSelection_2G_Only=2,
};
typedef u8 BandSelection_Mode_e;

typedef struct _BandSetting_t
{
    u16                           gsmBitmap;
    u16                           fddBitmap;
    u16                           tddBitmap;
    BandSelection_Mode_e eBandSelectionMode;
} BandSetting_t;
#endif

#ifdef __FEATURE_FONT_STYLE__
typedef struct _VectorFontStyle_t
{
    u8                            nCusFontId;
    MAE_WChar                     wCardFontName[FILEMGR_MAX_FILENAME_SIZE];
}VectorFontStyle_t;
#endif //__FEATURE_FONT_STYLE__

// Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)

#define CONFIG_AMR_MESSAGE_BLACKLIST_STATUS  CONFIG_DEFINE(CFGIT_MESSAGE_BLACKLIST_STATUS, Msg_SMS_Setting_BlackList_Status_e, 1, Msg_SMS_BlackList_Status_Off) // add by dongnan

//liuping add for Private Setting -begin-
//private setting
#define PRIVATE_PASSWORD_LEN_MIN 4  //密码的最小长度
#define PRIVATE_PASSWORD_LEN_MAX 6  //密码的最大长度
#define PRIVATE_APP_COUNT 4     //被锁定APP的数量

enum
{
	PRIVATE_APP_CALLLOG = 0,
	PRIVATE_APP_PHONEBOOK,
	PRIVATE_APP_SMS,
	PRIVATE_APP_FILEMANAGER
};

enum
{
	PRIVATE_UNLOCK = 0,         //解锁
	PRIVATE_LOCK                //加锁
};
enum
{
	PRIVATE_UNVERIFY = 0,      //未验证
	PRIVATE_VERIFIED           //已验证
};
enum
{
	PRIVATE_STOPAPP = 0,       //APP启动
	PRIVATE_STARTAPP           //APP停止
};
typedef u8 LockApp_t;
typedef u8 VerifyApp_t;
typedef int CallApp_t;  //私有APP是否被启动还是被停止
typedef struct PrivateAPP_Data_t_
{
	MAE_WChar    wPassword[PRIVATE_PASSWORD_LEN_MAX+1]; //设定私人空间的密码
	LockApp_t    tLockApp[PRIVATE_APP_COUNT];         //设定APP是否加锁
	VerifyApp_t  tVerifyApp[PRIVATE_APP_COUNT];       //设定APP是否验证过密码
	CallApp_t    tCallApp[PRIVATE_APP_COUNT];         //记录KeyGuard回来后私有APP是否存在
}PrivateAPP_Data_t;

typedef enum
{
	CALLSETTING_VIDEO_CALL_ASK,
	CALLSETTING_VIDEO_CALL_AUTO
} VideoCall_Setting_MODE_e;

enum
{
	CALLSETTING_VIDEO_CALL_LOOPBACK_OFF = 0,
	CALLSETTING_VIDEO_CALL_LOOPBACK_ON
};
typedef u8 VideoCall_Setting_LoopBack_e;

#ifdef __3G_RIL_MMI__
typedef enum
{
	DEBUG_DBB_SILENT_REBOOT_OFF = 0,
	DEBUG_DBB_SILENT_REBOOT_ON
} Debug_DBB_Silent_Reboot_e;

typedef enum
{
	DEBUG_DBB_ANTF_TRACE_OFF = 0,
	DEBUG_DBB_ANTF_TRACE_ON
} Debug_DBB_ANTF_Trace_e;
#endif // __3G_RIL_MMI__

//desktop widget/shortcut
enum
{
    DESKTOP_WIDGET_FIRST = 0,

    DESKTOP_WIDGET_ACLOCK = DESKTOP_WIDGET_FIRST,
    DESKTOP_WIDGET_SMALL_ACLOCK,
    DESKTOP_WIDGET_DCLOCK,
    DESKTOP_WIDGET_SMALL_DCLOCK,
    DESKTOP_WIDGET_PAGE_DCLOCK,
    DESKTOP_WIDGET_CALENDAR,
    DESKTOP_WIDGET_SMALL_CALENDAR,
    DESKTOP_WIDGET_MPLAYER,
    DESKTOP_WIDGET_SMALL_MPLAYER,
    DESKTOP_WIDGET_FMRADIO,
    DESKTOP_WIDGET_SMALL_FMRADIO,
    DESKTOP_WIDGET_PHOTO,
    DESKTOP_WIDGET_MESSAGE,
    DESKTOP_WIDGET_PHONEBOOK,
    DESKTOP_WIDGET_OPERATOR,
    DESKTOP_WIDGET_WORLDCLOCK01,
    DESKTOP_WIDGET_WORLDCLOCK02,
    DESKTOP_WIDGET_WORLDCLOCK03,
    DESKTOP_WIDGET_WORLDCLOCK04,
    DESKTOP_WIDGET_NOTEPAD,
    DESKTOP_WIDGET_SEARCH,

    DESKTOP_WIDGET_INVALID,
    DESKTOP_WIDGET_NUM = DESKTOP_WIDGET_INVALID
};
typedef u8 DesktopWidget_e;

enum
{
    DESKTOP_SHORTCUT_FIRST = 0,

    DESKTOP_SHORTCUT_01 = DESKTOP_SHORTCUT_FIRST,
    DESKTOP_SHORTCUT_02,
    DESKTOP_SHORTCUT_03,
    DESKTOP_SHORTCUT_04,
    DESKTOP_SHORTCUT_05,
    DESKTOP_SHORTCUT_06,
    DESKTOP_SHORTCUT_07,
    DESKTOP_SHORTCUT_08,
    DESKTOP_SHORTCUT_09,
    DESKTOP_SHORTCUT_10,
    DESKTOP_SHORTCUT_11,
    DESKTOP_SHORTCUT_12,
    DESKTOP_SHORTCUT_13,
    DESKTOP_SHORTCUT_14,
    DESKTOP_SHORTCUT_15,
    DESKTOP_SHORTCUT_16,
    DESKTOP_SHORTCUT_17,
    DESKTOP_SHORTCUT_18,
    DESKTOP_SHORTCUT_19,
    DESKTOP_SHORTCUT_20,

    DESKTOP_SHORTCUT_INVALID,
    DESKTOP_SHORTCUT_NUM = DESKTOP_SHORTCUT_INVALID
};
typedef u8 DesktopShortcut_e;
//desktop widget/shortcut end

#ifdef __PRIVATE_PROTECT__
//private setting
#define CONFIG_AMR_PRIVATESETTING_LIST        CONFIG_DEFINE(CFGIT_PRIVATESETTING_ID, PrivateAPP_Data_t, 1, {0,0,0,0})
//liuping add for Private Setting -end-
#else
#define CONFIG_AMR_PRIVATESETTING_LIST
#endif

//call setting
#define CONFIG_AMR_CALLSETTING_CALLER_ID        CONFIG_DEFINE(CFGIT_CALLSETTING_CALLER_ID, MMI_CALLSETTING_CALLER_IDENTITY_e, 1, CALLSETTING_CALLER_IDENTITY_ON)
#define CONFIG_AMR_CALLSETTING_CALLER_ID_SLAVE  CONFIG_DEFINE(CFGIT_CALLSETTING_CALLER_ID_SLAVE, MMI_CALLSETTING_CALLER_IDENTITY_e, 1, CALLSETTING_CALLER_IDENTITY_ON )
#define CONFIG_AMR_CALLSETTING_ANSWER_MODE      CONFIG_DEFINE(CFGIT_CALLSETTING_ANSWER_MODE, MMI_CALLSETTING_ANSWER_MODE_e, 1, CALLSETTING_ANSWER_MODE_SEND)
#define CONFIG_AMR_CALLSETTING_AUTO_REDIAL      CONFIG_DEFINE(CFGIT_CALLSETTING_AUTO_REDIAL, MMI_CALLSETTING_AUTO_REDIAL_e, 1, CALLSETTING_AUTO_REDIAL_OFF)
#ifdef __APP_VIDEO_TELEPHONY__
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL       CONFIG_DEFINE(CFGIT_CALLSETTING_VIDEO_CALL, VideoCall_Setting_MODE_e, 1, CALLSETTING_VIDEO_CALL_ASK )
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL_LOOPBACK CONFIG_DEFINE(CFGIT_CALLSETTING_VIDEO_CALL_LOOPBACK, VideoCall_Setting_LoopBack_e, 1, CALLSETTING_VIDEO_CALL_LOOPBACK_OFF )
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL_STORAGE CONFIG_DEFINE(CFGIT_CALLSETTING_VIDEO_CALL_STORAGE, StorageCfg_t, 1, {STORAGE_CARD})
#else
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL_LOOPBACK
#define CONFIG_AMR_CALLSETTING_VIDEO_CALL_STORAGE
#endif

#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_DEBUG_DBB_SILENT_REBOOT CONFIG_DEFINE(CFGIT_DEBUG_DBB_SILENT_REBOOT, Debug_DBB_Silent_Reboot_e, 1, DEBUG_DBB_SILENT_REBOOT_OFF )
#else // __3G_RIL_MMI__
#define CONFIG_AMR_DEBUG_DBB_SILENT_REBOOT
#endif // __3G_RIL_MMI__

#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_DEBUG_DBB_ANTF_TRACE CONFIG_DEFINE(CFGIT_DEBUG_DBB_ANTF_TRACE, Debug_DBB_ANTF_Trace_e, 1, DEBUG_DBB_ANTF_TRACE_OFF )
#else // __3G_RIL_MMI__
#define CONFIG_AMR_DEBUG_DBB_ANTF_TRACE
#endif // __3G_RIL_MMI__

#define CONFIG_AMR_CALLSETTING_AUTO_ANSWER      CONFIG_DEFINE(CFGIT_CALLSETTING_AUTO_ANSWER, boolean, 1, FALSE )

#ifdef __ANSWER_INDICATOR_MMI__
#define CONFIG_AMR_CALLSETTING_ANSWER_INDICATOR CONFIG_DEFINE(CFGIT_CALLSETTING_ANSWER_INDICATOR, MMI_CALLSETTING_ANSWER_INDICATOR_e, 1, CALLSETTING_ANSWER_IND_OFF )
#else
#define CONFIG_AMR_CALLSETTING_ANSWER_INDICATOR
#endif

#define CONFIG_AMR_CALLSETTING_MINUTE_REMINDER  CONFIG_DEFINE(CFGIT_CALLSETTING_MINUTE_REMINDER, u16, 1, 0 )

#ifdef __IP_CALL_MMI__
#define CONFIG_AMR_CALL_SETTING_IPCALL_LIST     CONFIG_DEFINE(CFGIT_CALL_SETTING_IPCALL_LIST, IPCALL_SET_t, IPCALL_MAX_SET_NUM, \
{{{L""}/*Name*/,{0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/},\
{{L""}/*Name*/, {0}/*Number*/}}/*astIPCallSetList*/  )
#else
#define CONFIG_AMR_CALL_SETTING_IPCALL_LIST
#endif

#define CONFIG_AMR_CALLSETTING_REJECT_MT  CONFIG_DEFINE(CFGIT_CALLSETTING_REJECT_MT, boolean, 1, FALSE )

// call setting for __HALL_SWITCH_MMI__
#ifdef __HALL_SWITCH_MMI__
#define CONFIG_AMR_CALLSETTING_HALL_OPEN_ANSWER      CONFIG_DEFINE(CFGIT_CALLSETTING_HALL_OPEN_ANSWER, boolean, 1, TRUE )
#define CONFIG_AMR_CALLSETTING_HALL_CLOSE_HANG_UP    CONFIG_DEFINE(CFGIT_CALLSETTING_HALL_CLOSE_HANG_UP, boolean, 1, TRUE )
#define CONFIG_AMR_SETTING_RINGTONE_SLIDE_SOUND_STATUS CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_SLIDE_SOUND_STATUS, SetRingToneSlideTone_e, 1, SLIDE_TONE_OFF)
#define CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE_URL CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_HALL_OPEN_TONE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_MESSAGE_PATH})
#else
#define CONFIG_AMR_SETTING_RINGTONE_SLIDE_SOUND_STATUS
#define CONFIG_AMR_CALLSETTING_HALL_OPEN_ANSWER
#define CONFIG_AMR_CALLSETTING_HALL_CLOSE_HANG_UP
#define CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE_URL
#endif

// distorted vocie setting
#ifdef __DISTORTED_VOICE_MMI__
#define CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_STATUS     CONFIG_DEFINE(CFGIT_CALLSETTING_DISTORTED_VOICE_STATUS, boolean, 1, FALSE)
#define CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_EFFECT     CONFIG_DEFINE(CFGIT_CALLSETTING_DISTORTED_VOICE_EFFECT, MMI_CALLSETTING_DISTORTED_EFFECT_e, 1, CALLSETTING_DISTORTED_EFFECT_KID)
#else
#define CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_STATUS
#define CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_EFFECT
#endif

// Answer machine
#ifndef AM_AnswerGreetingVoice_PATH
#define AM_AnswerGreetingVoice_PATH L""
#endif
#ifndef AM_Beep_PATH
#define AM_Beep_PATH L""
#endif
#ifdef __APP_MMI_ANSWERING_MACHINE__
#define CONFIG_AMR_CALLSETTING_AM_STATUS CONFIG_DEFINE(CFGIT_CALLSETTING_AM_STATUS, boolean, 1, FALSE)
#define CONFIG_AMR_CALLSETTING_AM_ANSWER_GREETING_VOICE_URL CONFIG_DEFINE(CFGIT_CALLSETTING_AM_ANSWER_GREETING_VOICE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {AM_AnswerGreetingVoice_PATH})
#define CONFIG_AMR_CALLSETTING_AM_BEEP_URL CONFIG_DEFINE(CFGIT_CALLSETTING_AM_BEEP_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {AM_Beep_PATH})
#define CONFIG_AMR_CALLSETTING_AM_AUTO_ANSWER_AFTER_RING CONFIG_DEFINE(CFGIT_CALLSETTING_AM_AUTO_ANSWER_AFTER_RING, u8, 1, 0 )
#define CONFIG_AMR_CALLSETTING_AM_STORAGE CONFIG_DEFINE(CFGIT_CALLSETTING_AM_STORAGE, StorageCfg_t, 1, {STORAGE_CARD})
#define CONFIG_AMR_CALLSETTING_AM_VOICE_BOX_COUNT CONFIG_DEFINE(CFGIT_CALLSETTING_AM_VOICE_BOX_COUNT, u16, 1, 0 )
#else
#define CONFIG_AMR_CALLSETTING_AM_STATUS
#define CONFIG_AMR_CALLSETTING_AM_ANSWER_GREETING_VOICE_URL
#define CONFIG_AMR_CALLSETTING_AM_BEEP_URL
#define CONFIG_AMR_CALLSETTING_AM_AUTO_ANSWER_AFTER_RING
#define CONFIG_AMR_CALLSETTING_AM_STORAGE
#define CONFIG_AMR_CALLSETTING_AM_VOICE_BOX_COUNT
#endif

#ifndef Sound_Dou_PATH
#define Sound_Dou_PATH L""
#endif

#ifndef Sound_KTV_PATH
#define Sound_KTV_PATH L""
#endif

#ifndef Sound_MRT1_PATH
#define Sound_MRT1_PATH L""
#endif

#ifndef Sound_MRT2_PATH
#define Sound_MRT2_PATH L""
#endif

#ifndef Sound_Motorcycle_PATH
#define Sound_Motorcycle_PATH L""
#endif

#ifndef Sound_Noise_PATH
#define Sound_Noise_PATH L""
#endif

#ifndef Sound_Pub_PATH
#define Sound_Pub_PATH L""
#endif

#ifndef Sound_Restaurant_PATH
#define Sound_Restaurant_PATH L""
#endif

#ifndef Sound_Sidewalk_PATH
#define Sound_Sidewalk_PATH L""
#endif

// Call background sound
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
#define CONFIG_AMR_CALLSETTING_CBS_STATUS CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_STATUS, boolean, 1, FALSE)
#define CONFIG_AMR_CALLSETTING_CBS_PLAY_TYPE CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_PLAY_TYPE, CallBgSound_Play_Type_e, 1, CBS_PLAY_TYPE_REPEAT)
#define CONFIG_AMR_CALLSETTING_CBS_PLAY_INTERVAL CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_PLAY_INTERVAL, u8, 1, 2)
#define CONFIG_AMR_CALLSETTING_CBS_CURRENT_EFFECT CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_CURRENT_EFFECT, u8, 1, 0)
#define CONFIG_AMR_CALLSETTING_CBS_VOLUME CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_5)
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_1 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_1, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Motorcycle_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_2 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_2, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Sidewalk_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_3 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_3, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_MRT1_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_4 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_4, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_MRT2_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_5 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_5, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Restaurant_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_6 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_6, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Pub_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_7 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_7, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_KTV_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_8 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_8, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Dou_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_9 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_9, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {Sound_Noise_PATH})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_10 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_10, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_11 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_11, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_12 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_12, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_13 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_13, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_14 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_14, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_15 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_15, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_16 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_16, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_17 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_17, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_18 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_18, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_19 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_19, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_20 CONFIG_DEFINE(CFGIT_CALLSETTING_CBS_EFFECT_SOUND_20, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#else
#define CONFIG_AMR_CALLSETTING_CBS_STATUS
#define CONFIG_AMR_CALLSETTING_CBS_PLAY_TYPE
#define CONFIG_AMR_CALLSETTING_CBS_PLAY_INTERVAL
#define CONFIG_AMR_CALLSETTING_CBS_CURRENT_EFFECT
#define CONFIG_AMR_CALLSETTING_CBS_VOLUME
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_1
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_2
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_3
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_4
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_5
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_6
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_7
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_8
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_9
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_10
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_11
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_12
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_13
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_14
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_15
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_16
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_17
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_18
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_19
#define CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_20
#endif // __APP_MMI_CALL_BACKGROUND_SOUND__
// Voice Memo recording format
#define CONFIG_AMR_VOICEMEMO_RECORD_FORMAT CONFIG_DEFINE(CFGIT_VOICEMEMO_RECORD_FORMAT, VOICE_MEMO_RECORD_Type_e, 1, VOICE_MEMO_AMR_QUALITY)

#ifdef __AUTO_RECORDING_MMI__
#define CONFIG_AMR_CALLSETTING_AUTO_RECORDING CONFIG_DEFINE(CFGIT_CALLSETTING_AUTO_RECORDING, boolean, 1, FALSE)
#else
#define CONFIG_AMR_CALLSETTING_AUTO_RECORDING
#endif

//cb
#define CONFIG_AMR_CB_MASTER_SETTING_AUTO_DISPLAY  CONFIG_DEFINE(CFGIT_CB_MASTER_SETTING_AUTO_DISPLAY, Msg_CB_Setting_e, 1, Msg_CB_AutoDisplay_OFF )
#define CONFIG_AMR_CB_SLAVE_SETTING_AUTO_DISPLAY  CONFIG_DEFINE(CFGIT_CB_SLAVE_SETTING_AUTO_DISPLAY, Msg_CB_Setting_e, 1, Msg_CB_AutoDisplay_OFF )
#define CONFIG_AMR_CB_MASTER_SETTING_RECEPTION  CONFIG_DEFINE(CFGIT_CB_MASTER_SETTING_RECEPTION, Msg_CB_Setting_e, 1, Msg_CB_Reception_OFF )
#define CONFIG_AMR_CB_MASTER_SETTING_CELL_INFORMATION  CONFIG_DEFINE(CFGIT_CB_MASTER_SETTING_CELL_INFORMATION, Msg_CB_Setting_e, 1, Msg_CB_Information_OFF )
#define CONFIG_AMR_CB_SLAVE_SETTING_RECEPTION  CONFIG_DEFINE(CFGIT_CB_SLAVE_SETTING_RECEPTION, Msg_CB_Setting_e, 1, Msg_CB_Reception_OFF )
#define CONFIG_AMR_CB_SLAVE_SETTING_CELL_INFORMATION  CONFIG_DEFINE(CFGIT_CB_SLAVE_SETTING_CELL_INFORMATION, Msg_CB_Setting_e, 1, Msg_CB_Information_OFF )

#if 1 /* CBSAPP_SetLangShowListMenuMdlListener */
#define CONFIG_AMR_MESSAGE_CB_MASTER_LANGLIST
#define CONFIG_AMR_MESSAGE_CB_SLAVE_LANGLIST
#else
#define CONFIG_AMR_MESSAGE_CB_MASTER_LANGLIST  CONFIG_DEFINE(CFGIT_MESSAGE_CB_MASTER_LANGLIST, Msg_CB_Setting_Language_List_t, 1, {{{0/*listNum*/}/*msgCbLangLstHdr*/, {1,0,0,0,0,0,0,0,0,0}/*msgCbLangItem*/}/*MasterCBLangList*/} )
#define CONFIG_AMR_MESSAGE_CB_SLAVE_LANGLIST  CONFIG_DEFINE(CFGIT_MESSAGE_CB_SLAVE_LANGLIST, Msg_CB_Setting_Language_List_t, 1, {{{0/*listNum*/}/*msgCbLangLstHdr*/, {1,0,0,0,0,0,0,0,0,0}/*msgCbLangItem*/}/*SlaveCBLangList*/} )
#endif

#define CONFIG_AMR_MESSAGE_CB_MASTER_TOPICLIST  CONFIG_DEFINE(CFGIT_MESSAGE_CB_MASTER_TOPICLIST, Msg_CB_Setting_Topic_List_t, 1, \
                                                                                        {{{0/*listNum*/}/*msgCbTopicLstHdr*/,  \
                                                                                        {{0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/}}/*msgCbTopicItem*/}/*MasterCBTopicList*/ })


#define CONFIG_AMR_MESSAGE_CB_SLAVE_TOPICLIST  CONFIG_DEFINE(CFGIT_MESSAGE_CB_SLAVE_TOPICLIST, Msg_CB_Setting_Topic_List_t, 1,  \
                                                                                        {{{0/*listNum*/}/*msgCbTopicLstHdr*/,  \
                                                                                        {{0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/},\
                                                                                        {0/*nFromChannel*/, 0/*nToChannel*/, {L""}/*TopicName*/, 0/*eSingleChannel*/, 0/*eTopicEnable*/}}/*msgCbTopicItem*/}/*SlaveCBTopicList*/} )


//consetting

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT1      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT1, Data_Account_t, 1, \
{{0/*bCSD*/, {L"CMWAP GPRS"}/*AccountName*/, {L"cmwap"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount1*/} )

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT2      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT2, Data_Account_t, 1, \
{{0/*bCSD*/, {L"CMNET GPRS"}/*AccountName*/, {L"cmnet"}/*APN*/, {L""}/*DialNumber*/,  {L""}/*UserName*/, {L""}/*Password*/,  {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount2*/} )

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT3      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT3, Data_Account_t, 1,\
{{0/*bCSD*/, {L"UNIWAP GPRS"}/*AccountName*/, {L"uniwap"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount3*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT4      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT4, Data_Account_t, 1,  \
{{0/*bCSD*/, {L"UNINET GPRS"}/*AccountName*/, {L"uninet"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount4*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT5      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT5, Data_Account_t, 1, \
{{0/*bCSD*/, {L"TWN GPRS"}/*AccountName*/, {L"mms"}/*APN*/, {L""}/*DialNumber*/, {L"wap"}/*UserName*/, {L"wap"}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount5*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT6      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT6, Data_Account_t, 1, \
{{0/*bCSD*/, {L"INTERNET"}/*AccountName*/, {L"internet"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount6*/} )

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT7      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT7, Data_Account_t, 1, \
{{0/*bCSD*/, {L"CHT GPRS"}/*AccountName*/, {L"emome"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount3*/} )

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT8      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT8, Data_Account_t, 1, \
{{0/*bCSD*/, {L"FET GPRS"}/*AccountName*/, {L"fetnet01"}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount8*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT9      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT9, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/,{0}/*DNS*/, 0/*AuthType*/,0/*LineType*/,0/*Speed*/,0/*u8Pad*/}/*DataAccount9*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT10      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT10, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount10*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT11      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT11, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount11*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT12      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT12, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount12*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT13      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT13, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount13*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT14      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT14, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount14*/})

#define CONFIG_AMR_CONNECT_DATA_ACCOUNT15      CONFIG_DEFINE(CFGIT_CONNECT_DATA_ACCOUNT15, Data_Account_t, 1, \
{{0/*bCSD*/, {L""}/*AccountName*/, {L""}/*APN*/, {L""}/*DialNumber*/, {L""}/*UserName*/, {L""}/*Password*/, {0}/*DNS*/, 0/*AuthType*/, 0/*LineType*/, 0/*Speed*/, 0/*u8Pad*/}/*DataAccount15*/})
#define CFGIT_DATA_ACCOUNT_NUM      (CFGIT_CONNECT_DATA_ACCOUNT15-CFGIT_CONNECT_DATA_ACCOUNT1+1)
#else
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT6
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT7
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT8
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT9
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT10
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT11
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT12
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT13
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT14
#define CONFIG_AMR_CONNECT_DATA_ACCOUNT15
#define CFGIT_DATA_ACCOUNT_NUM      (CFGIT_CONNECT_DATA_ACCOUNT5-CFGIT_CONNECT_DATA_ACCOUNT1+1)
#endif // !__APP_MMI_SMALLROM__

#define CONFIG_AMR_CONNECT_GPRS_SETTINGS      CONFIG_DEFINE(CFGIT_CONNECT_GPRS_SETTINGS, ConSetting_GPRS_e, 1, GPRS_E_ALWAYS )

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_WAP_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE1, WAP_Profile_t, 1, \
    {{{L"CHINA MOBILE WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT1/*DataAccount*/, {L"http://wap.monternet.com"}/*HomePage*/, {L"80"}/*Port*/, {0x0a,0x0,0x0,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile1*/} )

#define CONFIG_AMR_CONNECT_WAP_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE2, WAP_Profile_t, 1, \
    {{{L"CHINA UNICOM WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT3/*DataAccount*/, {L"http://wap.uni-info.com.cn"}/*HomePage*/, {L"80"}/*Port*/, {0x0a,0x00,0x00,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile2*/})
#else
#define CONFIG_AMR_CONNECT_WAP_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE1, WAP_Profile_t, 1, \
    {{{L"CHINA MOBILE WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT1/*DataAccount*/, {L"http://waptt.com"}/*HomePage*/, {L"80"}/*Port*/, {0x0a,0x0,0x0,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile1*/} )

#define CONFIG_AMR_CONNECT_WAP_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE2, WAP_Profile_t, 1, \
    {{{L"CHINA UNICOM WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT3/*DataAccount*/, {L"http://wap.10010.com"}/*HomePage*/, {L"80"}/*Port*/, {0x0a,0x00,0x00,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile2*/})
#endif

#ifndef __APP_MMI_SMALLROM__
#ifdef NCC_WSP
#define CONFIG_AMR_CONNECT_WAP_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE3, WAP_Profile_t, 1, \
    {{{L"FET WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT8/*DataAccount*/, {L"http://www.istyle.com.tw"}/*HomePage*/, {0x39,0x32,0x30,0x31}/*Port*/, {0xd2,0xf1,0xc7,0xc7}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile3*/})
#else
#define CONFIG_AMR_CONNECT_WAP_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE3, WAP_Profile_t, 1, \
    {{{L"FET WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT8/*DataAccount*/, {L"http://www.istyle.com.tw"}/*HomePage*/, {L"80"}/*Port*/, {0xd2,0xf1,0xc7,0xc7}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile3*/})
#endif /* NCC_WSP */

#ifdef NCC_WSP
#define CONFIG_AMR_CONNECT_WAP_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE4, WAP_Profile_t, 1, \
    {{{L"TWN WAP"}/*ProfileName*/,CFGIT_CONNECT_DATA_ACCOUNT5/*DataAccount*/, {L"http://catch"}/*HomePage*/, {0x39,0x32,0x30,0x31}/*Port*/, {0x0a,0x01,0x01,0x02}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*WAP_Profile4*/)
#else
#define CONFIG_AMR_CONNECT_WAP_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE4, WAP_Profile_t, 1, \
    {{{L"TWN WAP"}/*ProfileName*/,CFGIT_CONNECT_DATA_ACCOUNT5/*DataAccount*/, {L"http://catch"}/*HomePage*/, {L"80"}/*Port*/, {0x0a,0x01,0x01,0x02}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*WAP_Profile4*/)
#endif /* NCC_WSP */

#define CONFIG_AMR_CONNECT_WAP_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE5, WAP_Profile_t, 1, \
    {{{L"CHT WAP"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT7/*DataAccount*/, {L"http://wap.emome.net"}/*HomePage*/, {0x38,0x30,0x38,0x30}/*Port*/, {0x0a,0x01,0x01,0x01}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile5*/})

#define CONFIG_AMR_CONNECT_WAP_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE6, WAP_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*HomePage*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile6*/})

#define CONFIG_AMR_CONNECT_WAP_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE7, WAP_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*HomePage*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile7*/})

#define CONFIG_AMR_CONNECT_WAP_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE8, WAP_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*HomePage*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile8*/})

#define CONFIG_AMR_CONNECT_WAP_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE9, WAP_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*HomePage*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile9*/})

#define CONFIG_AMR_CONNECT_WAP_PROFILE10     CONFIG_DEFINE(CFGIT_CONNECT_WAP_PROFILE10, WAP_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*HomePage*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*WAP_Profile10*/})
#define CFGIT_WAP_PROFILE_NUM      (CFGIT_CONNECT_WAP_PROFILE10-CFGIT_CONNECT_WAP_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_WAP_PROFILE3
#define CONFIG_AMR_CONNECT_WAP_PROFILE4
#define CONFIG_AMR_CONNECT_WAP_PROFILE5
#define CONFIG_AMR_CONNECT_WAP_PROFILE6
#define CONFIG_AMR_CONNECT_WAP_PROFILE7
#define CONFIG_AMR_CONNECT_WAP_PROFILE8
#define CONFIG_AMR_CONNECT_WAP_PROFILE9
#define CONFIG_AMR_CONNECT_WAP_PROFILE10
#define CFGIT_WAP_PROFILE_NUM      (CFGIT_CONNECT_WAP_PROFILE2-CFGIT_CONNECT_WAP_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__

#define CONFIG_AMR_CONNECT_WAP_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_WAP_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_WAP_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_WAP_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )

#ifdef NCC_WSP
#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_CONNECT_MMS_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE1, MMS_Profile_t, 1, \
    {{{L"CHINA MOBILE MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT1/*DataAccount*/, {L"http://mmsc.monternet.com"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x0,0x0,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile1*/} )
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE1, MMS_Profile_t, 1, \
    {{{L"CHINA MOBILE MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT1/*DataAccount*/, {L"http://mmsc.monternet.com"}/*MMSC*/, {0x39,0x32,0x30,0x31}/*Port*/, {0x0a,0x0,0x0,0xac}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile1*/} )
#endif
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE1, MMS_Profile_t, 1, \
    {{{L"CHINA MOBILE MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT1/*DataAccount*/, {L"http://mmsc.monternet.com"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x0,0x0,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile1*/} )
#endif /* NCC_WSP */

#ifdef NCC_WSP
#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_CONNECT_MMS_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE2, MMS_Profile_t, 1, \
    {{{L"CHINA UNICOM MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT3/*DataAccount*/, {L"http://mmsc.myuni.com.cn"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x00,0x00,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile2*/})
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE2, MMS_Profile_t, 1, \
    {{{L"CHINA UNICOM MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT3/*DataAccount*/, {L"http://mmsc.myuni.com.cn"}/*MMSC*/, {0x39,0x32,0x30,0x31}/*Port*/, {0x0a,0x00,0x00,0xac}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile2*/})
#endif
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE2, MMS_Profile_t, 1, \
    {{{L"CHINA UNICOM MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT3/*DataAccount*/, {L"http://mmsc.myuni.com.cn"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x00,0x00,0xac}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile2*/})
#endif /* NCC_WSP */

#ifndef __APP_MMI_SMALLROM__
#ifdef NCC_WSP
#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_CONNECT_MMS_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE3, MMS_Profile_t, 1, \
    {{{L"FET MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT8/*DataAccount*/, {L"http://mms"}/*MMSC*/, {L"80"}/*Port*/, {0xd2,0xf1,0xc7,0xc7}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile3*/})
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE3, MMS_Profile_t, 1, \
    {{{L"FET MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT8/*DataAccount*/, {L"http://mms"}/*MMSC*/, {0x39,0x32,0x30,0x31}/*Port*/, {0xd2,0xf1,0xc7,0xc7}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile3*/})
#endif
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE3, MMS_Profile_t, 1, \
    {{{L"FET MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT8/*DataAccount*/, {L"http://mms"}/*MMSC*/, {L"80"}/*Port*/, {0xd2,0xf1,0xc7,0xc7}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile3*/})
#endif /* NCC_WSP */

#ifdef NCC_WSP
#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_CONNECT_MMS_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE4, MMS_Profile_t, 1, \
    {{{L"TWN MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT5/*DataAccount*/, {L"http://mms"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x01,0x01,0x02}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*MMS_Profile4*/)
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE4, MMS_Profile_t, 1, \
    {{{L"TWN MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT5/*DataAccount*/, {L"http://mms"}/*MMSC*/, {0x39,0x32,0x30,0x31}/*Port*/, {0x0a,0x01,0x01,0x02}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*MMS_Profile4*/)
#endif
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE4, MMS_Profile_t, 1, \
    {{{L"TWN MMS"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT5/*DataAccount*/, {L"http://mms"}/*MMSC*/, {L"80"}/*Port*/, {0x0a,0x01,0x01,0x02}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*MMS_Profile4*/)
#endif /* NCC_WSP */

#ifdef NCC_WSP
#ifdef __3G_RIL_MMI__
#define CONFIG_AMR_CONNECT_MMS_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE5, MMS_Profile_t, 1, \
    {{{L"CHT MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT7/*DataAccount*/, {L"http://mms.emome.net:8002"}/*MMSC*/, {0x38,0x30,0x38,0x30}/*Port*/, {0x0a,0x01,0x01,0x01}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile5*/})
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE5, MMS_Profile_t, 1, \
    {{{L"CHT MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT7/*DataAccount*/, {L"http://mms.emome.net:8002"}/*MMSC*/, {0x39,0x32,0x30,0x31}/*Port*/, {0x0a,0x01,0x01,0x01}/*Proxy*/, CONNECTION_TYPE_E_CONNECTION_ORIENTED/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile5*/})
#endif
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE5, MMS_Profile_t, 1, \
    {{{L"CHT MMS"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT7/*DataAccount*/, {L"http://mms.emome.net:8002"}/*MMSC*/, {0x38,0x30,0x38,0x30}/*Port*/, {0x0a,0x01,0x01,0x01}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile5*/})
#endif /* NCC_WSP */

#define CONFIG_AMR_CONNECT_MMS_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE6, MMS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*MMSC*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile6*/})

#define CONFIG_AMR_CONNECT_MMS_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE7, MMS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*MMSC*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile7*/} )

#define CONFIG_AMR_CONNECT_MMS_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE8, MMS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*MMSC*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile8*/})

#define CONFIG_AMR_CONNECT_MMS_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE9, MMS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*MMSC*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile9*/})

#define CONFIG_AMR_CONNECT_MMS_PROFILE10     CONFIG_DEFINE(CFGIT_CONNECT_MMS_PROFILE10, MMS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*MMSC*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*u8Pad*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*MMS_Profile10*/})
#define CFGIT_MMS_PROFILE_NUM      (CFGIT_CONNECT_MMS_PROFILE10-CFGIT_CONNECT_MMS_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_MMS_PROFILE3
#define CONFIG_AMR_CONNECT_MMS_PROFILE4
#define CONFIG_AMR_CONNECT_MMS_PROFILE5
#define CONFIG_AMR_CONNECT_MMS_PROFILE6
#define CONFIG_AMR_CONNECT_MMS_PROFILE7
#define CONFIG_AMR_CONNECT_MMS_PROFILE8
#define CONFIG_AMR_CONNECT_MMS_PROFILE9
#define CONFIG_AMR_CONNECT_MMS_PROFILE10
#define CFGIT_MMS_PROFILE_NUM      (CFGIT_CONNECT_MMS_PROFILE2-CFGIT_CONNECT_MMS_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__

#define CONFIG_AMR_CONNECT_MMS_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_MMS_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_MMS_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_MMS_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )

#define CONFIG_AMR_APN_DETECTION_SIM1      CONFIG_DEFINE(CFGIT_APN_DETECTION_SIM1, boolean, 1, FALSE )
#define CONFIG_AMR_APN_DETECTION_SIM2      CONFIG_DEFINE(CFGIT_APN_DETECTION_SIM2, boolean, 1, FALSE )

#ifdef __EMAIL_MMI__
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE1, Email_Profile_t, 1, \
    {{{L"CHINA MOBILE EMAIL"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile1*/} )

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE2, Email_Profile_t, 1, \
    {{{L"CHINA UNICOM EMAIL"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE3, Email_Profile_t, 1, \
    {{{L"FET EMAIL"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile3*/})

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE4, Email_Profile_t, 1, \
    {{{L"TWN EMAIL"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*EMAIL_Profile4*/)

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE5, Email_Profile_t, 1, \
    {{{L"CHT EMAIL"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile5*/})

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE6, Email_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile6*/})

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE7, Email_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile7*/} )

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE8, Email_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile8*/})

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE9, Email_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile9*/})

#define CONFIG_AMR_CONNECT_EMAIL_PROFILE10      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_PROFILE10, Email_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*EMAIL_Profile10*/})
#define CFGIT_EMAIL_PROFILE_NUM      (CFGIT_CONNECT_EMAIL_PROFILE10-CFGIT_CONNECT_EMAIL_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE3
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE4
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE5
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE6
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE7
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE8
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE9
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE10
#define CFGIT_EMAIL_PROFILE_NUM      (CFGIT_CONNECT_EMAIL_PROFILE2-CFGIT_CONNECT_EMAIL_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__

#else// __EMAIL_MMI__
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE1
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE2
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE3
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE4
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE5
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE6
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE7
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE8
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE9
#define CONFIG_AMR_CONNECT_EMAIL_PROFILE10
#define CFGIT_EMAIL_PROFILE_NUM      (0)
#endif// __EMAIL_MMI__

#ifdef __EMAIL_MMI__
#define CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_EMAIL_DEFAULT_ACCOUNT_ID       CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_DEFAULT_ACCOUNT_ID, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM2
#define CONFIG_AMR_CONNECT_EMAIL_DEFAULT_ACCOUNT_ID
#endif

#ifdef __NCCQQ_MMI__
#define CONFIG_AMR_CONNECT_QQ_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE1, QQ_Profile_t, 1, \
    {{{L"CHINA MOBILE QQ"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile1*/} )

#define CONFIG_AMR_CONNECT_QQ_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE2, QQ_Profile_t, 1, \
    {{{L"CHINA UNICOM QQ"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_QQ_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE3, QQ_Profile_t, 1, \
    {{{L"FET QQ"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile3*/})

#define CONFIG_AMR_CONNECT_QQ_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE4, QQ_Profile_t, 1, \
    {{{L"TWN QQ"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*QQ_Profile4*/)

#define CONFIG_AMR_CONNECT_QQ_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE5, QQ_Profile_t, 1, \
    {{{L"CHT QQ"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile5*/})

#define CONFIG_AMR_CONNECT_QQ_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE6, QQ_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile6*/})

#define CONFIG_AMR_CONNECT_QQ_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE7, QQ_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile7*/} )

#define CONFIG_AMR_CONNECT_QQ_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE8, QQ_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile8*/})

#define CONFIG_AMR_CONNECT_QQ_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE9, QQ_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile9*/})

#define CONFIG_AMR_CONNECT_QQ_PROFILE10      CONFIG_DEFINE(CFGIT_CONNECT_QQ_PROFILE10, QQ_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*QQ_Profile10*/})
#define CFGIT_QQ_PROFILE_NUM      (CFGIT_CONNECT_QQ_PROFILE10-CFGIT_CONNECT_QQ_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_QQ_PROFILE3
#define CONFIG_AMR_CONNECT_QQ_PROFILE4
#define CONFIG_AMR_CONNECT_QQ_PROFILE5
#define CONFIG_AMR_CONNECT_QQ_PROFILE6
#define CONFIG_AMR_CONNECT_QQ_PROFILE7
#define CONFIG_AMR_CONNECT_QQ_PROFILE8
#define CONFIG_AMR_CONNECT_QQ_PROFILE9
#define CONFIG_AMR_CONNECT_QQ_PROFILE10
#define CFGIT_QQ_PROFILE_NUM      (CFGIT_CONNECT_QQ_PROFILE2-CFGIT_CONNECT_QQ_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__

#else
#define CONFIG_AMR_CONNECT_QQ_PROFILE1
#define CONFIG_AMR_CONNECT_QQ_PROFILE2
#define CONFIG_AMR_CONNECT_QQ_PROFILE3
#define CONFIG_AMR_CONNECT_QQ_PROFILE4
#define CONFIG_AMR_CONNECT_QQ_PROFILE5
#define CONFIG_AMR_CONNECT_QQ_PROFILE6
#define CONFIG_AMR_CONNECT_QQ_PROFILE7
#define CONFIG_AMR_CONNECT_QQ_PROFILE8
#define CONFIG_AMR_CONNECT_QQ_PROFILE9
#define CONFIG_AMR_CONNECT_QQ_PROFILE10
#define CFGIT_QQ_PROFILE_NUM      (0)
#endif // !__APP_MMI_SMALLROM__

#ifdef __NCCQQ_MMI__
#define CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_QQ_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_QQ_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM2
#endif

#ifdef __STREAMING_MODULE__
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE1, Streaming_Profile_t, 1, \
    {{{L"CHINA MOBILE"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile1*/} )
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE2, Streaming_Profile_t, 1, \
    {{{L"CHINA UNICOM"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile2*/} )
#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE3, Streaming_Profile_t, 1, \
    {{{L"FET"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile3*/} )
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE4, Streaming_Profile_t, 1, \
    {{{L"TWN"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile4*/} )
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE5, Streaming_Profile_t, 1, \
    {{{L"CHT"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile5*/} )
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE6, Streaming_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile6*/})
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE7, Streaming_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile7*/})
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE8, Streaming_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile8*/})
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE9, Streaming_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile9*/})
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE10     CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_PROFILE10, Streaming_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*STREAMING_Profile9*/})
#else
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE3
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE4
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE5
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE6
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE7
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE8
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE9
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE10
#endif // !__APP_MMI_SMALLROM__

#else// __STREAMING_MODULE__
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE1
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE2
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE3
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE4
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE5
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE6
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE7
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE8
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE9
#define CONFIG_AMR_CONNECT_STREAMING_PROFILE10
#endif// __STREAMING_MODULE__

#ifdef __STREAMING_MODULE__
#define CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM2
#endif

#ifdef __APP_MMI_NTP__
#define CONFIG_AMR_CONNECT_NTP_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE1, NTP_Profile_t, 1, \
    {{{L"CHINA MOBILE NTP"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile1*/} )

#define CONFIG_AMR_CONNECT_NTP_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE2, NTP_Profile_t, 1, \
    {{{L"CHINA UNICOM NTP"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_NTP_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE3, NTP_Profile_t, 1, \
    {{{L"FET NTP"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile3*/})

#define CONFIG_AMR_CONNECT_NTP_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE4, NTP_Profile_t, 1, \
    {{{L"TWN NTP"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*NTP_Profile4*/)

#define CONFIG_AMR_CONNECT_NTP_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE5, NTP_Profile_t, 1, \
    {{{L"CHT NTP"}/*ProfileName*/,  \
    CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/,  \
    {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile5*/})

#define CONFIG_AMR_CONNECT_NTP_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE6, NTP_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile6*/})

#define CONFIG_AMR_CONNECT_NTP_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE7, NTP_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile7*/} )

#define CONFIG_AMR_CONNECT_NTP_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE8, NTP_Profile_t, 1, \
    {{{L""}/*ProfileName*/,  \
    0/*DataAccount*/,  \
    {0,0,0}/*u8Pad*/,  \
    {0,0,0,0,0,0,0}/*MccMnc1*/,  \
    {0,0,0,0,0,0,0}/*MccMnc2*/,  \
    {0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile8*/})

#define CONFIG_AMR_CONNECT_NTP_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE9, NTP_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile9*/})

#define CONFIG_AMR_CONNECT_NTP_PROFILE10      CONFIG_DEFINE(CFGIT_CONNECT_NTP_PROFILE10, NTP_Profile_t, 1, \
{{{L""}/*ProfileName*/,  \
0/*DataAccount*/,  \
{0,0,0}/*u8Pad*/,  \
{0,0,0,0,0,0,0}/*MccMnc1*/,  \
{0,0,0,0,0,0,0}/*MccMnc2*/,  \
{0,0,0,0,0,0,0}/*MccMnc3*/}/*NTP_Profile10*/})
#else
#define CONFIG_AMR_CONNECT_NTP_PROFILE3
#define CONFIG_AMR_CONNECT_NTP_PROFILE4
#define CONFIG_AMR_CONNECT_NTP_PROFILE5
#define CONFIG_AMR_CONNECT_NTP_PROFILE6
#define CONFIG_AMR_CONNECT_NTP_PROFILE7
#define CONFIG_AMR_CONNECT_NTP_PROFILE8
#define CONFIG_AMR_CONNECT_NTP_PROFILE9
#define CONFIG_AMR_CONNECT_NTP_PROFILE10
#endif // !__APP_MMI_SMALLROM__

#else
#define CONFIG_AMR_CONNECT_NTP_PROFILE1
#define CONFIG_AMR_CONNECT_NTP_PROFILE2
#define CONFIG_AMR_CONNECT_NTP_PROFILE3
#define CONFIG_AMR_CONNECT_NTP_PROFILE4
#define CONFIG_AMR_CONNECT_NTP_PROFILE5
#define CONFIG_AMR_CONNECT_NTP_PROFILE6
#define CONFIG_AMR_CONNECT_NTP_PROFILE7
#define CONFIG_AMR_CONNECT_NTP_PROFILE8
#define CONFIG_AMR_CONNECT_NTP_PROFILE9
#define CONFIG_AMR_CONNECT_NTP_PROFILE10
#endif // !__APP_MMI_NTP__

#ifdef __APP_MMI_NTP__
#define CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_NTP_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_NTP_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM2
#endif

#ifdef __JAVA_MMI__
#define CONFIG_AMR_CONNECT_JAVA_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE1, Java_Profile_t, 1, \
    {{{L"CHINA MOBILE"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile1*/} )

#define CONFIG_AMR_CONNECT_JAVA_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE2, Java_Profile_t, 1, \
    {{{L"CHINA UNICOM"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_JAVA_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE3, Java_Profile_t, 1, \
    {{{L"FET"}/*ProfileName*/,  CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile3*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE4, Java_Profile_t, 1, \
    {{{L"TWN"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*JAVA_Profile4*/)

#define CONFIG_AMR_CONNECT_JAVA_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE5, Java_Profile_t, 1, \
    {{{L"CHT"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile5*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE6, Java_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile6*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE7, Java_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile7*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE8, Java_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile8*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE9, Java_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile9*/})

#define CONFIG_AMR_CONNECT_JAVA_PROFILE10     CONFIG_DEFINE(CFGIT_CONNECT_JAVA_PROFILE10, Java_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*JAVA_Profile9*/})
#define CFGIT_JAVA_PROFILE_NUM      (CFGIT_CONNECT_JAVA_PROFILE10-CFGIT_CONNECT_JAVA_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_JAVA_PROFILE3
#define CONFIG_AMR_CONNECT_JAVA_PROFILE4
#define CONFIG_AMR_CONNECT_JAVA_PROFILE5
#define CONFIG_AMR_CONNECT_JAVA_PROFILE6
#define CONFIG_AMR_CONNECT_JAVA_PROFILE7
#define CONFIG_AMR_CONNECT_JAVA_PROFILE8
#define CONFIG_AMR_CONNECT_JAVA_PROFILE9
#define CONFIG_AMR_CONNECT_JAVA_PROFILE10
#define CFGIT_JAVA_PROFILE_NUM      (CFGIT_CONNECT_JAVA_PROFILE2-CFGIT_CONNECT_JAVA_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_JAVA_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_JAVA_PROFILE1
#define CONFIG_AMR_CONNECT_JAVA_PROFILE2
#define CONFIG_AMR_CONNECT_JAVA_PROFILE3
#define CONFIG_AMR_CONNECT_JAVA_PROFILE4
#define CONFIG_AMR_CONNECT_JAVA_PROFILE5
#define CONFIG_AMR_CONNECT_JAVA_PROFILE6
#define CONFIG_AMR_CONNECT_JAVA_PROFILE7
#define CONFIG_AMR_CONNECT_JAVA_PROFILE8
#define CONFIG_AMR_CONNECT_JAVA_PROFILE9
#define CONFIG_AMR_CONNECT_JAVA_PROFILE10
#define CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM2
#define CFGIT_JAVA_PROFILE_NUM      (0)
#endif

#ifdef __WLAN_MMI__
#define CONFIG_AMR_CONNECT_OTHER_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE1, Other_Profile_t, 1, \
    {{{L"CHINA MOBILE"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile1*/} )

#define CONFIG_AMR_CONNECT_OTHER_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE2, Other_Profile_t, 1, \
    {{{L"CHINA UNICOM"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_OTHER_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE3, Other_Profile_t, 1, \
    {{{L"FET"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile3*/})

#define CONFIG_AMR_CONNECT_OTHER_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE4, Other_Profile_t, 1, \
    {{{L"TWN"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*OTHER_Profile4*/)

#define CONFIG_AMR_CONNECT_OTHER_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE5, Other_Profile_t, 1, \
    {{{L"CHT"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile5*/})

#define CONFIG_AMR_CONNECT_OTHER_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE6, Other_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile6*/})

#define CONFIG_AMR_CONNECT_OTHER_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE7, Other_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile7*/})

#define CONFIG_AMR_CONNECT_OTHER_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE8, Other_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile8*/})

#define CONFIG_AMR_CONNECT_OTHER_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_PROFILE9, Other_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*OTHER_Profile9*/})
#define CFGIT_OTHER_PROFILE_NUM      (CFGIT_CONNECT_OTHER_PROFILE9-CFGIT_CONNECT_OTHER_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_OTHER_PROFILE3
#define CONFIG_AMR_CONNECT_OTHER_PROFILE4
#define CONFIG_AMR_CONNECT_OTHER_PROFILE5
#define CONFIG_AMR_CONNECT_OTHER_PROFILE6
#define CONFIG_AMR_CONNECT_OTHER_PROFILE7
#define CONFIG_AMR_CONNECT_OTHER_PROFILE8
#define CONFIG_AMR_CONNECT_OTHER_PROFILE9
#define CFGIT_OTHER_PROFILE_NUM      (CFGIT_CONNECT_OTHER_PROFILE2-CFGIT_CONNECT_OTHER_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_OTHER_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_OTHER_PROFILE1
#define CONFIG_AMR_CONNECT_OTHER_PROFILE2
#define CONFIG_AMR_CONNECT_OTHER_PROFILE3
#define CONFIG_AMR_CONNECT_OTHER_PROFILE4
#define CONFIG_AMR_CONNECT_OTHER_PROFILE5
#define CONFIG_AMR_CONNECT_OTHER_PROFILE6
#define CONFIG_AMR_CONNECT_OTHER_PROFILE7
#define CONFIG_AMR_CONNECT_OTHER_PROFILE8
#define CONFIG_AMR_CONNECT_OTHER_PROFILE9
#define CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM2
#define CFGIT_OTHER_PROFILE_NUM      (0)
#endif

#ifdef __MAP_MMI_LBS__
#define CONFIG_AMR_CONNECT_LBS_PROFILE1      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE1, LBS_Profile_t, 1, \
    {{{L"CHINA MOBILE"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT2/*DataAccount*/, {L"0"}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x30,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile1*/} )

#define CONFIG_AMR_CONNECT_LBS_PROFILE2      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE2, LBS_Profile_t, 1, \
    {{{L"CHINA UNICOM"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT4/*DataAccount*/, {L"0"}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x30,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x30,0x30,0x30,0x36,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile2*/})

#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_LBS_PROFILE3      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE3, LBS_Profile_t, 1, \
    {{{L"FET"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L"0"}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x30,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x38,0x38,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile3*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE4      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE4, LBS_Profile_t, 1, \
    {{{L"TWN"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/,  {L"0"}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x39,0x33,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x37,0x00}/*MccMnc2*/, {0x34,0x36,0x36,0x30,0x39,0x39,0x00}/*MccMnc3*/}}/*LBS_Profile4*/)

#define CONFIG_AMR_CONNECT_LBS_PROFILE5      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE5, LBS_Profile_t, 1, \
    {{{L"CHT"}/*ProfileName*/, CFGIT_CONNECT_DATA_ACCOUNT6/*DataAccount*/, {L"0"}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0x34,0x36,0x36,0x30,0x31,0x31,0x00}/*MccMnc1*/, {0x34,0x36,0x36,0x30,0x39,0x32,0x00}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile5*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE6      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE6, LBS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile6*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE7      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE7, LBS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile7*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE8      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE8, LBS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile8*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE9      CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE9, LBS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile9*/})

#define CONFIG_AMR_CONNECT_LBS_PROFILE10     CONFIG_DEFINE(CFGIT_CONNECT_LBS_PROFILE10, LBS_Profile_t, 1, \
    {{{L""}/*ProfileName*/, 0/*DataAccount*/, {L""}/*Port*/, {0}/*Proxy*/, CONNECTION_TYPE_E_HTTP/*ConnType*/, {0}/*MccMnc1*/, {0}/*MccMnc2*/, {0}/*MccMnc3*/}/*LBS_Profile10*/})
#define CFGIT_LBS_PROFILE_NUM      (CFGIT_CONNECT_LBS_PROFILE10-CFGIT_CONNECT_LBS_PROFILE1+1)
#else
#define CONFIG_AMR_CONNECT_LBS_PROFILE3
#define CONFIG_AMR_CONNECT_LBS_PROFILE4
#define CONFIG_AMR_CONNECT_LBS_PROFILE5
#define CONFIG_AMR_CONNECT_LBS_PROFILE6
#define CONFIG_AMR_CONNECT_LBS_PROFILE7
#define CONFIG_AMR_CONNECT_LBS_PROFILE8
#define CONFIG_AMR_CONNECT_LBS_PROFILE9
#define CONFIG_AMR_CONNECT_LBS_PROFILE10
#define CFGIT_LBS_PROFILE_NUM      (CFGIT_CONNECT_LBS_PROFILE2-CFGIT_CONNECT_LBS_PROFILE1+1)
#endif // !__APP_MMI_SMALLROM__
#define CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM1      CONFIG_DEFINE(CFGIT_CONNECT_LBS_ACTIVE_PROFILE_SIM1, SortIdx, 1, 0 )
#define CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM2      CONFIG_DEFINE(CFGIT_CONNECT_LBS_ACTIVE_PROFILE_SIM2, SortIdx, 1, 0 )
#else
#define CONFIG_AMR_CONNECT_LBS_PROFILE1
#define CONFIG_AMR_CONNECT_LBS_PROFILE2
#define CONFIG_AMR_CONNECT_LBS_PROFILE3
#define CONFIG_AMR_CONNECT_LBS_PROFILE4
#define CONFIG_AMR_CONNECT_LBS_PROFILE5
#define CONFIG_AMR_CONNECT_LBS_PROFILE6
#define CONFIG_AMR_CONNECT_LBS_PROFILE7
#define CONFIG_AMR_CONNECT_LBS_PROFILE8
#define CONFIG_AMR_CONNECT_LBS_PROFILE9
#define CONFIG_AMR_CONNECT_LBS_PROFILE10
#define CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM1
#define CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM2
#define CFGIT_LBS_PROFILE_NUM      (0)
#endif

#ifdef __WLAN_MMI__
#define CONFIG_AMR_CONNECT_WAP_CONNECT_SET          CONFIG_DEFINE(CFGIT_CONNECT_WAP_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only )
#define CONFIG_AMR_CONNECT_JAVA_CONNECT_SET         CONFIG_DEFINE(CFGIT_CONNECT_JAVA_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only )
#define CONFIG_AMR_CONNECT_EMAIL_CONNECT_SET        CONFIG_DEFINE(CFGIT_CONNECT_EMAIL_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only)
#ifdef __NCCQQ_MMI__
#define CONFIG_AMR_CONNECT_QQ_CONNECT_SET           CONFIG_DEFINE(CFGIT_CONNECT_QQ_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only)
#else
#define CONFIG_AMR_CONNECT_QQ_CONNECT_SET
#endif // __NCCQQ_MMI__

#ifdef __APP_MMI_NTP__
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SET           CONFIG_DEFINE(CFGIT_CONNECT_NTP_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only)
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SERVER        CONFIG_DEFINE(CFGIT_CONNECT_NTP_CONNECT_SERVER, NTP_ServerSetting_e, 1, NTP_SERVER_NTSC)
#else
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SET
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SERVER
#endif // __APP_MMI_NTP__

#ifdef __STREAMING_MODULE__
#define CONFIG_AMR_CONNECT_STREAMING_CONNECT_SET           CONFIG_DEFINE(CFGIT_CONNECT_STREAMING_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only)
#else
#define CONFIG_AMR_CONNECT_STREAMING_CONNECT_SET
#endif // __STREAMING_MODULE__

#define CONFIG_AMR_CONNECT_OTHER_CONNECT_SET        CONFIG_DEFINE(CFGIT_CONNECT_OTHER_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only )
#else
#define CONFIG_AMR_CONNECT_WAP_CONNECT_SET
#define CONFIG_AMR_CONNECT_JAVA_CONNECT_SET
#ifdef __NCCQQ_MMI__
#define CONFIG_AMR_CONNECT_QQ_CONNECT_SET
#else
#define CONFIG_AMR_CONNECT_QQ_CONNECT_SET
#endif // __NCCQQ_MMI__

#ifdef __APP_MMI_NTP__
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SET           CONFIG_DEFINE(CFGIT_CONNECT_NTP_CONNECT_SET, ConSetting_ConnectSet_e, 1, ConnectSet_GPRS_Only)
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SERVER        CONFIG_DEFINE(CFGIT_CONNECT_NTP_CONNECT_SERVER, NTP_ServerSetting_e, 1, NTP_SERVER_NTSC)
#else
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SET
#define CONFIG_AMR_CONNECT_NTP_CONNECT_SERVER
#endif // __APP_MMI_NTP__


#ifdef __STREAMING_MODULE__
#define CONFIG_AMR_CONNECT_STREAMING_CONNECT_SET
#else
#define CONFIG_AMR_CONNECT_STREAMING_CONNECT_SET
#endif
#define CONFIG_AMR_CONNECT_OTHER_CONNECT_SET
#define CONFIG_AMR_CONNECT_EMAIL_CONNECT_SET
#endif

//Date time
#define CONFIG_AMR_SETTING_PHONE_TIME_ZONE_AUTOMATIC_UPDATE         CONFIG_DEFINE(CFGIT_SETTING_PHONE_TIME_ZONE_AUTOMATIC_UPDATE, SetPhoneTimeZoneAutomaticUpdate_e, 1, TIMEZONE_AUTOMATICUPDATE_OFF )
#define CONFIG_AMR_SETTING_PHONE_DATE_FORMAT                        CONFIG_DEFINE(CFGIT_SETTING_PHONE_DATE_FORMAT, SetPhoneDateFormat_e, 1, DATEFORMAT_MMDDYYYY )
#define CONFIG_AMR_SETTING_PHONE_TIME_FORMAT                        CONFIG_DEFINE(CFGIT_SETTING_PHONE_TIME_FORMAT, SetPhoneTimeFormat_e, 1, TIMEFORMAT_24FORMAT )
#define CONFIG_AMR_SETTING_PHONE_SECOND_TIME                        CONFIG_DEFINE(CFGIT_SETTING_PHONE_SECOND_TIME, SetOnOff_e, 1, SET_OFF )
#define CONFIG_AMR_SECOND_TIMEZONE                                  CONFIG_DEFINE(CFGIT_SECOND_TIMEZONE, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )
#define CONFIG_AMR_SYS_TIMEZONE                                     CONFIG_DEFINE(CFGIT_SYS_TIMEZONE, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )
#define CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK1                       CONFIG_DEFINE(CFGIT_SYS_TIMEZONE_WIDGET_CLOCK1, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )
#define CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK2                       CONFIG_DEFINE(CFGIT_SYS_TIMEZONE_WIDGET_CLOCK2, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )
#define CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK3                       CONFIG_DEFINE(CFGIT_SYS_TIMEZONE_WIDGET_CLOCK3, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )
#define CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK4                       CONFIG_DEFINE(CFGIT_SYS_TIMEZONE_WIDGET_CLOCK4, SysTimeZoneType_e, 1, SYS_TZ_GMTplus0800 )

//Display
#define CONFIG_AMR_SETTING_DISPLAY_MENU_TRANSITION_STATUS    CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MENU_TRANSITION_STATUS, SetOnOff_e, 1, SET_ON )
#define CONFIG_AMR_SETTING_DISPLAY_OTHERS_TRANSITION_STATUS  CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_OTHERS_TRANSITION_STATUS, SetOnOff_e, 1, SET_ON )
#define CONFIG_AMR_SETTING_PHONE_DAYLIGHT_SAVING_TIME        CONFIG_DEFINE(CFGIT_SETTING_PHONE_DAYLIGHT_SAVING_TIME, SetOnOff_e, 1, SET_OFF )
#if defined(__TOUCH_SCREEN_MMI__)
#define CONFIG_AMR_SETTING_DISPLAY_BACKLIGHT_DURATION        CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_BACKLIGHT_DURATION, SetDisplayBKLDuration_e, 1, BACKLIGHT_DURATION_30SECS )
#else
#define CONFIG_AMR_SETTING_DISPLAY_BACKLIGHT_DURATION        CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_BACKLIGHT_DURATION, SetDisplayBKLDuration_e, 1, BACKLIGHT_DURATION_15SECS )
#endif
#ifdef __SCREEN_EFFECTS_SUPPORT__
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_TYPE            CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_TYPE, SetDisplayScreenEffectType_e, 1, SCREENEFFECT_SNOW )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_BEZIER_NUM      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_BEZIER_NUM, SetDisplayScreenEffectBezierNum_e, 1, SCREENEFFECT_BEZIER_NUM_8 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_SPEED      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_SPEED, SetDisplayScreenEffectSnowSpeed_e, 1, SCREENEFFECT_SNOW_SPEED_1 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_NUM        CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_NUM, SetDisplayScreenEffectSnowNum_e, 1, SCREENEFFECT_SNOW_NUM_500 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BIG_NUM    CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_BIG_NUM, SetDisplayScreenEffectSnowBigNum_e, 1, SCREENEFFECT_SNOW_BIG_NUM_30 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_DIR   CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_DIR, SetDisplayScreenEffectSnowBlowDir_e, 1, SCREENEFFECT_SNOW_BLOW_DIR_RANDOM )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_TIME  CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_TIME, SetDisplayScreenEffectSnowBlowTime_e, 1, SCREENEFFECT_SNOW_BLOW_TIME_500 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_PILE_SPEED CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_PILE_SPEED, SetDisplayScreenEffectSnowPileSpeed_e, 1, SCREENEFFECT_SNOW_PILE_SPEED_10 )
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_COLOR      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREENEFFECT_SNOW_COLOR, SetDisplayScreenEffectSnowColor_e, 1, SCREENEFFECT_SNOW_COLOR_WHITE )
#else
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_TYPE
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_BEZIER_NUM
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_SPEED
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_NUM
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BIG_NUM
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_DIR
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_TIME
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_PILE_SPEED
#define CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_COLOR
#endif

#ifdef __POWER_SAVING_PROFILE_MMI__
#define CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_DURATION   CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_LAST_BACKLIGHT_DURATION, SetDisplayBKLDuration_e, 1, BACKLIGHT_DURATION_30SECS )
#define CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_LEVEL      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_LAST_BACKLIGHT_LEVEL, u16, 1, 4 )
#else
#define CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_DURATION
#define CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_LEVEL
#endif

#ifdef __LUNAR_CALENDAR_MMI__
#define CONFIG_AMR_SETTING_DISPLAY_LUNAR_CALENDAR            CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_LUNAR_CALENDAR, SetOnOff_e, 1, SET_ON )
#else
#define CONFIG_AMR_SETTING_DISPLAY_LUNAR_CALENDAR
#endif

#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__
#define CONFIG_AMR_SETTING_DISPLAY_MENU_ANIMATION_STYLE      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MENU_ANIMATION_STYLE, SetDisplayMenuAnimationStyle_e, 1,SET_MENU_ANIMATION_STYLE_RANDOM )
#else
#define CONFIG_AMR_SETTING_DISPLAY_MENU_ANIMATION_STYLE
#endif

#define CONFIG_AMR_SETTING_DISPLAY_MENU_STYLE                CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MENU_STYLE, SetDisplayMenuStyle_e, 1, SET_MENU_STYLE_3D_GRID)
#define CONFIG_AMR_SETTING_DISPLAY_OPERATOR_NAME             CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_OPERATOR_NAME, SetOnOff_e, 1, SET_ON )

#ifdef __APP_MMI_SCREENSAVER__
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_STATUS       CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREEN_SAVER_STATUS, SetOnOff_e, 1, SET_OFF )
#if defined(__3D_UI_SCREENSAVER_EFFECT__)
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_3D_STYLE     CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREEN_SAVER_3D_STYLE, SetOnOff_e, 1, SET_OFF )
#else
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_3D_STYLE
#endif
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_DURATION     CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREEN_SAVER_DURATION, SetDisplayScreenSaverDuration_e, 1, SCREEN_SAVER_DURATION_5SECS )
#ifndef __APP_MMI_SMALLROM__
#define CONFIG_AMR_SETTING_DISPLAY_DISPLAY_SCREEN_SAVER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREEN_SAVER_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_05_PATH})
#else
#define CONFIG_AMR_SETTING_DISPLAY_DISPLAY_SCREEN_SAVER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SCREEN_SAVER_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_04_PATH})
#endif // !__APP_MMI_SMALLROM__
#else
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_STATUS
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_3D_STYLE
#define CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_DURATION
#define CONFIG_AMR_SETTING_DISPLAY_DISPLAY_SCREEN_SAVER_URL
#endif

#define CONFIG_AMR_SETTING_DISPLAY_START_POWER_SAVING_TIME   CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_START_POWER_SAVING_TIME, SetDisplayStartPowerSavingTime_e, 1, POWER_SAVING_60SECS )
#define CONFIG_AMR_SETTING_DISPLAY_BACKLIGHT_LEVEL           CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_BACKLIGHT_LEVEL, u16, 1, 4 )

#if defined(__LIVE_WALLPAPER_SEASHORE__)
#define CONFIG_AMR_SETTING_3D_WALLPAPER_ID                   CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_ID, SetWallpaper_3DEffect_e, 1, WALLPAPER_3DEFFECT_SEASHORE)
#elif defined(__LIVE_WALLPAPER_FLUTTERSNOW__)
#define CONFIG_AMR_SETTING_3D_WALLPAPER_ID                   CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_ID, SetWallpaper_3DEffect_e, 1, WALLPAPER_3DEFFECT_FLUTTERSNOW)
#else
#define CONFIG_AMR_SETTING_3D_WALLPAPER_ID                   CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_ID, SetWallpaper_3DEffect_e, 1, WALLPAPER_3DEFFECT_IMAGE)
#endif

//Idle Pet Clock Feature
#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#define CONFIG_AMR_IDLEAPP_SHORTCUTBAR                   CONFIG_DEFINE(CFGIT_IDLEAPP_SHORTCUTBAR, boolean, 1, FALSE )
#define CONFIG_AMR_IDLEAPP_CLOCK_POS                     CONFIG_DEFINE(CFGIT_IDLEAPP_CLOCK_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_CALENDAR_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_CALENDAR_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_TODOLIST_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_TODOLIST_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_QQ_POS                        CONFIG_DEFINE(CFGIT_IDLEAPP_QQ_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_DIGCLOCK_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_DIGCLOCK_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_MAP_POS                       CONFIG_DEFINE(CFGIT_IDLEAPP_MAP_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_FMRADIO_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_FMRADIO_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_GAME_POS                      CONFIG_DEFINE(CFGIT_IDLEAPP_GAME_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_LIVEWALLPAPER_POS             CONFIG_DEFINE(CFGIT_IDLEAPP_LIVEWALLPAPER_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_OPERATOR_POS                  CONFIG_DEFINE(CFGIT_IDLEAPP_OPERATOR_POS, s16, 2, {120,100} )
#define CONFIG_AMR_IDLEAPP_MPLAYER_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_MPLAYER_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_NOTE_POS                      CONFIG_DEFINE(CFGIT_IDLEAPP_NOTE_POS, s16, 2, {140,100} )
#define CONFIG_AMR_SHORTCUTBAR_ITEM_ORDER                CONFIG_DEFINE(CFGIT_SHORTCUTBAR_ITEM_ORDER, u8, 14, {0,1,2,3,4,5,6,7,8,9,10,11,12,13} )
#define CONFIG_AMR_IDLEAPP_PROFILE_POS                   CONFIG_DEFINE(CFGIT_IDLEAPP_PROFILE_POS, s16, 2, {140,100} )
#define CONFIG_AMR_IDLEAPP_SEARCH_POS                    CONFIG_DEFINE(CFGIT_IDLEAPP_SEARCH_POS, s16, 2, {140,100} )
#else
#define CONFIG_AMR_IDLEAPP_SHORTCUTBAR
#define CONFIG_AMR_IDLEAPP_CLOCK_POS
#define CONFIG_AMR_IDLEAPP_CALENDAR_POS
#define CONFIG_AMR_IDLEAPP_TODOLIST_POS
#define CONFIG_AMR_IDLEAPP_QQ_POS
#define CONFIG_AMR_IDLEAPP_DIGCLOCK_POS
#define CONFIG_AMR_IDLEAPP_MAP_POS
#define CONFIG_AMR_IDLEAPP_FMRADIO_POS
#define CONFIG_AMR_IDLEAPP_GAME_POS
#define CONFIG_AMR_IDLEAPP_LIVEWALLPAPER_POS
#define CONFIG_AMR_IDLEAPP_OPERATOR_POS
#define CONFIG_AMR_IDLEAPP_MPLAYER_POS
#define CONFIG_AMR_IDLEAPP_NOTE_POS
#define CONFIG_AMR_SHORTCUTBAR_ITEM_ORDER
#define CONFIG_AMR_IDLEAPP_PROFILE_POS
#define CONFIG_AMR_IDLEAPP_SEARCH_POS
#endif

#ifdef __3D_UI_IDLE_SIMPLE__
#define CONFIG_AMR_IDLEAPP_FLIP_WDG_IDX CONFIG_DEFINE(CFGIT_IDLEAPP_FLIP_WDG_IDX, u8, 1, 0 )
#else
#define CONFIG_AMR_IDLEAPP_FLIP_WDG_IDX
#endif

//*******************************************************************************************************************************
//setting
#define CONFIG_AMR_SETTING_PHONE_AUTO_POWER_ON_TIME  CONFIG_DEFINE(CFGIT_SETTING_PHONE_AUTO_POWER_ON_TIME, u32, 1, 946688400)
#define CONFIG_AMR_SETTING_PHONE_AUTO_POWER_OFF_TIME  CONFIG_DEFINE(CFGIT_SETTING_PHONE_AUTO_POWER_OFF_TIME, u32, 1, 946684800)
#define CONFIG_AMR_SETTING_PHONE_AUTO_POWER_ON_STATUS  CONFIG_DEFINE(CFGIT_SETTING_PHONE_AUTO_POWER_ON_STATUS, SetOnOff_e, 1, SET_OFF)
#define CONFIG_AMR_SETTING_PHONE_AUTO_POWER_OFF_STATUS  CONFIG_DEFINE(CFGIT_SETTING_PHONE_AUTO_POWER_OFF_STATUS, SetOnOff_e, 1, SET_OFF)

#ifdef __TOUCH_SCREEN_MMI__
#define CONFIG_AMR_SETTING_SLIDE_TO_POWER_OFF_STATUS  CONFIG_DEFINE(CFGIT_SETTING_SLIDE_TO_POWER_OFF_STATUS, SetOnOff_e, 1, SET_ON)
#else
#define CONFIG_AMR_SETTING_SLIDE_TO_POWER_OFF_STATUS
#endif

#define CONFIG_AMR_SETTING_RINGTONE_VOLUME CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_6)
#define CONFIG_AMR_SETTING_INCALL_VOLUME CONFIG_DEFINE(CFGIT_SETTING_INCALL_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_6)
#define CONFIG_AMR_SETTING_INCALL_CLSETTING_SHOW_MT CONFIG_DEFINE(CFGIT_SETTING_INCALL_CLSETTING_SHOW_MT, SetOnOff_e, 1, SET_OFF)
#define CONFIG_AMR_SETTING_INCALL_CLSETTING_SHOW_MO CONFIG_DEFINE(CFGIT_SETTING_INCALL_CLSETTING_SHOW_M0, SetOnOff_e, 1, SET_OFF)
#define CONFIG_AMR_SETTING_RINGTONE_POWER_ON_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_POWER_ON_TONE, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_RINGTONE_POWER_OFF_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_POWER_OFF_TONE, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_RINGTONE_VOICE_CALL_RING_TYPE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_VOICE_CALL_RING_TYPE, SetRingToneRingType_e, 1, RING_TYPE_RINGING)
#define CONFIG_AMR_SETTING_RINGTONE_MESSAGE_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_MESSAGE_TONE, SetRingToneMessageTone_e, 1, MESSAGE_TONE_ON)
#define CONFIG_AMR_SETTING_RINGTONE_CALENDAR_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_CALENDAR_TONE, SetRingToneCalendarTone_e, 1, CALENDAR_TONE_ON)
#define CONFIG_AMR_SETTING_RINGTONE_ALARM_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_ALARM_TONE, SetRingToneAlarmTone_e, 1, ALARM_TONE_ON)
#define CONFIG_AMR_SETTING_RINGTONE_MISS_EVENT_REMINDER CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_MISS_EVENT_REMINDER, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_RINGTONE_KEYPAD_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_KEYPAD_TONE, SetRingToneKeypadTone_e, 1, KEYPAD_TONE_OFF)
#ifdef __FEATURE_FONT_STYLE__
#define CONFIG_AMR_SETTING_FONT_STYLE CONFIG_DEFINE(CFGIT_SETTING_FONT_STYLE, VectorFontStyle_t, 1, {0xFF, {L""}})
#else
#define CONFIG_AMR_SETTING_FONT_STYLE
#endif //__FEATURE_FONT_STYLE__
#define CONFIG_AMR_SETTING_PHONE_LANGUAGE CONFIG_DEFINE(CFGIT_SETTING_PHONE_LANGUAGE, MAE_LANG_CODE_e, 1, MAE_LANG_ENGLISH)
#define CONFIG_AMR_SETTING_PHONE_INPUT_LANGUAGE CONFIG_DEFINE(CFGIT_SETTING_PHONE_INPUT_LANGUAGE, MAE_LANG_CODE_e, 1, MAE_LANG_ENGLISH)
#define CONFIG_AMR_SETTING_ENCODING CONFIG_DEFINE(CFGIT_SETTING_ENCODING, Common_Encoding_StringType_e, 1, Common_Encoding_StringType_ASCII)
#define CONFIG_AMR_SETTING_PHONE_SELECTED_CHINESE_INPUT_MODE CONFIG_DEFINE(CFGIT_SETTING_PHONE_SELECTED_CHINESE_INPUT_MODE, SetChineseInputMode_e, 1, SET_CHINESE_INPUTMODE_SCHINESE_PINYIN)
#define CONFIG_AMR_SETTING_PHONE_SELECTED_NOT_CHINESE_INPUT_MODE CONFIG_DEFINE(CFGIT_SETTING_PHONE_SELECTED_NOT_CHINESE_INPUT_MODE, u32, 1, 0x00000000)
#define CONFIG_AMR_SETTING_PHONE_INPUT_MODE_ABC CONFIG_DEFINE(CFGIT_SETTING_PHONE_INPUT_MODE_ABC, SetDefaultInputModeABC_e, 1, SET_DEFAULT_INPUT_MODE_NOT_ABC)
#define CONFIG_AMR_SETTING_PHONE_INPUT_MODE_SMART CONFIG_DEFINE(CFGIT_SETTING_PHONE_INPUT_MODE_SMART, SetSmartInput_e, 1, SET_SMART_INPUT_MODE_OFF)
#define CONFIG_AMR_SETTING_PHONE_SOFTKEYBOARD_STATUS CONFIG_DEFINE(CFGIT_SETTING_PHONE_SOFTKEYBOARD_STATUS, SetSoftKeyboard_e, 1, SET_SOFT_KEYBOARD_MODE_ON)
#define CONFIG_AMR_SETTING_PHONE_HANDWRITING_ONOFF CONFIG_DEFINE(CFGIT_SETTING_PHONE_HANDWRITING_ONOFF, boolean, 1, TRUE)
//Hall Switch ring tone setting, __HALL_SWITCH_MMI__
#ifdef __HALL_SWITCH_MMI__
#define CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_HALL_OPEN_TONE, boolean, 1, TRUE)
#define CONFIG_AMR_SETTING_IDLE_HALL_CLOSE_KEYGUARD CONFIG_DEFINE(CFGIT_SETTING_IDLE_HALL_CLOSE_KEYGUARD, boolean, 1, TRUE)
#else
#define CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE
#define CONFIG_AMR_SETTING_IDLE_HALL_CLOSE_KEYGUARD
#endif
//setting end

//camera
#ifdef __DUAL_CAMERA_MMI__
#define CONFIG_AMR_DUAL_CAMERA_TYPE  CONFIG_DEFINE(CFGIT_DUAL_CAMERA_TYPE, DualCameraType_e, 1, DUAL_CAMERA_TYPE_PRI)
#else
#define CONFIG_AMR_DUAL_CAMERA_TYPE
#endif

#ifdef __SMART_DIALER__
#define CONFIG_AMR_SMART_SEARCH_TYPE  CONFIG_DEFINE(CFGIT_SMART_SEARCH_TYPE, SmartSearchType_t, 1, {TRUE,TRUE,TRUE,TRUE})
#else
#define CONFIG_AMR_SMART_SEARCH_TYPE
#endif

//phbapp
#if 1
#define CONFIG_AMR_PHBAPP_BLACKLIST
#else
#define CONFIG_AMR_PHBAPP_BLACKLIST CONFIG_DEFINE(CFGIT_PHBAPP_BLACKLIST, boolean, 1, FALSE)
#endif
//phbapp end

//networksetting
#define CONFIG_AMR_NETWORKSETTING_REG_MODE CONFIG_DEFINE(CFGIT_NETWORKSETTING_REG_MODE, MMI_MMSRV_RegMode_e, 1, MMI_MMSRV_REGMODE_ATUOMATIC)
#define CONFIG_AMR_NETWORKSETTING_REG_MODE_SLAVE CONFIG_DEFINE(CFGIT_NETWORKSETTING_REG_MODE_SLAVE, MMI_MMSRV_RegMode_e, 1, MMI_MMSRV_REGMODE_ATUOMATIC)
#ifdef __GPRS_MMI__
#define CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE CONFIG_DEFINE(CFGIT_NETWORKSETTING_NET_ACCESS_MODE, MMI_MMSRV_NetAccess_Mode_e, 1, MMI_MMSRV_NETACCESS_GSM_ONLY)
#define CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE_SLAVE CONFIG_DEFINE(CFGIT_NETWORKSETTING_NET_ACCESS_MODE_SLAVE, MMI_MMSRV_NetAccess_Mode_e, 1, MMI_MMSRV_NETACCESS_GSM_ONLY)
#else
#define CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE
#define CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE_SLAVE
#endif
//networksetting end

//setting
#define CONFIG_AMR_SETTING_PHONE_DEFAULT_SIM CONFIG_DEFINE(CFGIT_SETTING_PHONE_DEFAULT_SIM, SetDefaultSIM_e, 1, DEFAULT_SIM_MASTER)
//setting end

//nativegame
#define CONFIG_AMR_NATIVEGAME_SETTING_VOLUME CONFIG_DEFINE(CFGIT_NATIVEGAME_SETTING_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_3)
#define CONFIG_AMR_NATIVEGAME_BIG2_SETTING_VOLUME CONFIG_DEFINE(CFGIT_NATIVEGAME_BIG2_SETTING_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_3)
#define CONFIG_AMR_NATIVEGAME_BIG2_SETTING_SOUND CONFIG_DEFINE(CFGIT_NATIVEGAME_BIG2_SETTING_SOUND, boolean, 1, TRUE )
#define CONFIG_AMR_NATIVEGAME_PACMAN_SETTING_VOLUME CONFIG_DEFINE(CFGIT_NATIVEGAME_PACMAN_SETTING_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_3)
#define CONFIG_AMR_NATIVEGAME_PACMAN_SETTING_SOUND CONFIG_DEFINE(CFGIT_NATIVEGAME_PACMAN_SETTING_SOUND, boolean, 1, TRUE )

//nativegame end

//setting
#define CONFIG_AMR_SETTING_RINGTONE_VIBRATE_TYPE CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_VIBRATE_TYPE, SetVibrateType_e, 1, VIBRATE_TYPE_VIBRATE_OFF)
//setting end

//mplayer
#define CONFIG_AMR_MPLAYER_3DSURROUND CONFIG_DEFINE(CFGIT_MPLAYER_3DSURROUND, MPlayer_3DSurround_e, 1, MMI_MPLAYER_3DSurround_OFF)
#define CONFIG_AMR_MPLAYER_REVERB CONFIG_DEFINE(CFGIT_MPLAYER_REVERB, MPlayer_Reverb_e, 1, MMI_MPLAYER_Reverb_NONE)
#define CONFIG_AMR_MPLAYER_EQ CONFIG_DEFINE(CFGIT_MPLAYER_EQ, MPlayer_EQ_e, 1, MMI_MPLAYER_EQ_NORMAL)
#define CONFIG_AMR_MPLAYER_DOLBY CONFIG_DEFINE(CFGIT_MPLAYER_DOLBY, MPlayer_Dolby_e, 1, MMI_MPLAYER_DOLBY_OFF)
#define CONFIG_AMR_MPLAYER_LYRIC CONFIG_DEFINE(CFGIT_MPLAYER_LYRIC, MPlayer_Lyric_e, 1, MMI_MPLAYER_Lyric_OFF)
#define CONFIG_AMR_MPLAYER_REPEAT CONFIG_DEFINE(CFGIT_MPLAYER_REPEAT, MPlayer_Repeat_e, 1, MMI_MPLAYER_REPEAT_OFF)
#define CONFIG_AMR_MPLAYER_SHUFFLE CONFIG_DEFINE(CFGIT_MPLAYER_SHUFFLE, MPlayer_Shuffle_e, 1, MMI_MPLAYER_SHUFFLE_OFF)
#define CONFIG_AMR_MPLAYER_VOLUME CONFIG_DEFINE(CFGIT_MPLAYER_VOLUME, MPlayer_VolLevel_e, 1, MMI_MPLAYER_VolLevel_4)
#define CONFIG_AMR_MPLAYER_PITCHSHIFT CONFIG_DEFINE(CFGIT_MPLAYER_PITCHSHIFT, MPlayer_PitchShift_e, 1, MMI_MPLAYER_PitchShidt_OFF)
#define CONFIG_AMR_MPLAYER_BACKGROUND_PLAY CONFIG_DEFINE(CFGIT_MPLAYER_BACKGROUND_PLAY, MPlayer_BackgroundPlay_e, 1, MMI_MPLAYER_BackgroundPlay_ON)
#if defined(ENABLE_SRSWOWHD)
#define CONFIG_AMR_MPLAYER_SRS CONFIG_DEFINE(CFGIT_MPLAYER_SRS, MPlayer_SRS_e, 1, MMI_MPLAYER_SRS_OFF)
#define CONFIG_AMR_MPLAYER_SRS_TYPE CONFIG_DEFINE(CFGIT_MPLAYER_SRS_TYPE, MPlayer_SRS_Type_e, 1, MMI_MPLAYER_SRS_TYPE_NORMAL)
#define CONFIG_AMR_MPLAYER_SRS_PARAM_NORMAL CONFIG_DEFINE(CFGIT_MPLAYER_SRS_PARAM_NORMAL, MPlayer_SRS_Param_t, 1, {8, 5, 6, 4, 4})
#define CONFIG_AMR_MPLAYER_SRS_PARAM_CLASSIC CONFIG_DEFINE(CFGIT_MPLAYER_SRS_PARAM_CLASSIC, MPlayer_SRS_Param_t, 1, {6, 6, 4, 6, 3})
#define CONFIG_AMR_MPLAYER_SRS_PARAM_BASS CONFIG_DEFINE(CFGIT_MPLAYER_SRS_PARAM_BASS, MPlayer_SRS_Param_t, 1, {6, 5, 9, 6, 4})
#define CONFIG_AMR_MPLAYER_SRS_PARAM_HIPHOP CONFIG_DEFINE(CFGIT_MPLAYER_SRS_PARAM_HIPHOP, MPlayer_SRS_Param_t, 1, {7, 4, 7, 7, 6})
#define CONFIG_AMR_MPLAYER_SRS_PARAM_PERFORM CONFIG_DEFINE(CFGIT_MPLAYER_SRS_PARAM_PERFORM, MPlayer_SRS_Param_t, 1, {6, 5, 7, 6, 7})
#else
#define CONFIG_AMR_MPLAYER_SRS
#define CONFIG_AMR_MPLAYER_SRS_TYPE
#define CONFIG_AMR_MPLAYER_SRS_PARAM_NORMAL
#define CONFIG_AMR_MPLAYER_SRS_PARAM_CLASSIC
#define CONFIG_AMR_MPLAYER_SRS_PARAM_BASS
#define CONFIG_AMR_MPLAYER_SRS_PARAM_HIPHOP
#define CONFIG_AMR_MPLAYER_SRS_PARAM_PERFORM
#endif // defined(ENABLE_SRSWOWHD)
#define CONFIG_AMR_MPLAYER_VIRTUALBASS CONFIG_DEFINE(CFGIT_MPLAYER_VIRTUALBASS, MPlayer_VirtualBass_e, 1, MMI_MPLAYER_VirtualBass_ON)
//mplayer end

//fmradio
#define CONFIG_AMR_SETTING_FMRADIO_VOLUME CONFIG_DEFINE(CFGIT_FMRADIO_VOLUME, MPlayer_VolLevel_e, 1, MMI_MPLAYER_VolLevel_4)
//fmradio end

//ATV
#define CONFIG_AMR_SETTING_ATV_VOLUME CONFIG_DEFINE(CFGIT_ATV_VOLUME, MPlayer_VolLevel_e, 1, MMI_MPLAYER_VolLevel_4)
//ATV end

//filemgr
#define CONFIG_AMR_SETTING_FILEMGR_VOLUME CONFIG_DEFINE(CFGIT_FILEMGR_VOLUME, MPlayer_VolLevel_e, 1, MMI_MPLAYER_VolLevel_4)
//filemgr end

//voicememo
#define CONFIG_AMR_SETTING_VOICEMEMO_VOLUME CONFIG_DEFINE(CFGIT_VOICEMEMO_VOLUME, SetRingToneVolume_e, 1, VOLUME_LEVEL_4)
//voicememo end

//G-sensor
#ifdef __G_SENSOR_MMI__
#ifdef __AUTO_ROTATE_DISPLAY__
#define CONFIG_AMR_SETTING_GSENSOR_WND_AUTOROTATE  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_WND_AUTOROTATE, SetOnOff_e, 1, SET_ON)
#else
#define CONFIG_AMR_SETTING_GSENSOR_WND_AUTOROTATE
#endif
#define CONFIG_AMR_SETTING_GSENSOR_SHAKE_WALLPAPER  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_SHAKE_WALLPAPER, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_GSENSOR_SHAKE_SONG  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_SHAKE_SONG, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_GSENSOR_CHANGE_PICTURE  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_CHANGE_PICTURE, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_GSENSOR_ROTATE_PICTURE  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_ROTATE_PICTURE, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_GSENSOR_FLIP_SILENT  CONFIG_DEFINE(CFGIT_SETTING_GSENSOR_FLIP_SILENT, SetOnOff_e, 1, SET_OFF)
#else
#define CONFIG_AMR_SETTING_GSENSOR_WND_AUTOROTATE
#define CONFIG_AMR_SETTING_GSENSOR_SHAKE_WALLPAPER
#define CONFIG_AMR_SETTING_GSENSOR_SHAKE_SONG
#define CONFIG_AMR_SETTING_GSENSOR_CHANGE_PICTURE
#define CONFIG_AMR_SETTING_GSENSOR_ROTATE_PICTURE
#define CONFIG_AMR_SETTING_GSENSOR_FLIP_SILENT
#endif
//G-sensor end

//setting
#ifndef __APP_MMI_SMALLROM__
#ifdef __UI_STYLE_MMI_ANDROID_4_0__
#ifndef WALLPAPER_IMG_ANDROID_40_PATH
#define WALLPAPER_IMG_ANDROID_40_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_ANDROID_40_PATH})
#else // __UI_STYLE_MMI_ANDROID_4_0__
#ifndef WALLPAPER_IMG_05_PATH
#define WALLPAPER_IMG_05_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_05_PATH})
#endif // __UI_STYLE_MMI_ANDROID_4_0__
#else
#ifndef WALLPAPER_IMG_04_PATH
#define WALLPAPER_IMG_04_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_04_PATH})
#endif // !__APP_MMI_SMALLROM__
#ifndef MAINMENU_IMG_DEFAULT_BG_PATH
#define MAINMENU_IMG_DEFAULT_BG_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_MAINMENU_IMG_BG_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MAINMENU_IMG_BG_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MAINMENU_IMG_DEFAULT_BG_PATH})
#ifndef POWER_ONOFF_ANIMATION_PATH
#define POWER_ONOFF_ANIMATION_PATH L""
#endif
#ifdef __USER_DEFINE_POWERONOFF_ANIM__
#define CONFIG_AMR_SETTING_DISPLAY_POWER_OFF_ANIMATION_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_OFF_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {POWER_ONOFF_ANIMATION_PATH})
#else
#define CONFIG_AMR_SETTING_DISPLAY_POWER_OFF_ANIMATION_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_OFF_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#endif
#ifndef MID_POWER_OFF_PATH
#define MID_POWER_OFF_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_POWER_OFF_RINGTONE_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_OFF_RINGTONE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_POWER_OFF_PATH})

#ifdef __USER_DEFINE_POWERONOFF_ANIM__
#define CONFIG_AMR_SETTING_DISPLAY_POWER_ON_ANIMATION_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_ON_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {POWER_ONOFF_ANIMATION_PATH})
#else
#define CONFIG_AMR_SETTING_DISPLAY_POWER_ON_ANIMATION_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_ON_ANIMATION_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#endif

#ifndef MID_POWER_ON_PATH
#define MID_POWER_ON_PATH L""
#endif
#define CONFIG_AMR_SETTING_DISPLAY_POWER_ON_RINGTONE_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_POWER_ON_RINGTONE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_POWER_ON_PATH})

#ifdef __DUAL_LCD__
#define CONFIG_AMR_SETTING_DISPLAY_SUB_DISPLAY_WALLPAPER_URL CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_SUB_DISPLAY_WALLPAPER_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})
#else
#define CONFIG_AMR_SETTING_DISPLAY_SUB_DISPLAY_WALLPAPER_URL
#endif

#ifndef MID_ALARM_PATH
#define MID_ALARM_PATH L""
#endif
#define CONFIG_AMR_SETTING_RINGTONE_ALARM_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_ALARM_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_ALARM_PATH})
#ifndef MID_CALENDAR_PATH
#define MID_CALENDAR_PATH L""
#endif
#define CONFIG_AMR_SETTING_RINGTONE_CALENDAR_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_CALENDAR_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_CALENDAR_PATH})
#ifndef MID_MESSAGE_PATH
#define MID_MESSAGE_PATH L""
#endif
#define CONFIG_AMR_SETTING_RINGTONE_MESSAGE_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_MESSAGE_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_MESSAGE_PATH})
#ifdef __DUAL_PROFILE_MMI__
#define CONFIG_AMR_SETTING_RINGTONE_SIM2_MESSAGE_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_SIM2_RINGTONE_MESSAGE_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_MESSAGE_PATH})
#else
#define CONFIG_AMR_SETTING_RINGTONE_SIM2_MESSAGE_MELODY_URL
#endif

#ifndef MID_INCOMING_PATH
#define MID_INCOMING_PATH L""
#endif
#define CONFIG_AMR_SETTING_RINGTONE_VOICE_CALL_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_RINGTONE_VOICE_CALL_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_INCOMING_PATH})
#ifdef __DUAL_PROFILE_MMI__
#define CONFIG_AMR_SETTING_RINGTONE_SIM2_VOICE_CALL_MELODY_URL CONFIG_DEFINE(CFGIT_SETTING_SIM2_RINGTONE_VOICE_CALL_MELODY_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {MID_INCOMING_PATH})
#else
#define CONFIG_AMR_SETTING_RINGTONE_SIM2_VOICE_CALL_MELODY_URL
#endif

#define CONFIG_AMR_SETTING_VOICE_CALL_DEFAULT_CALLER_IMAGE_URL CONFIG_DEFINE(CFGIT_SETTING_VOICE_CALL_DEFAULT_CALLER_IMAGE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""})

#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
#ifndef WALLPAPER_IMG_06_PATH
#define WALLPAPER_IMG_06_PATH L""
#endif
#define CONFIG_AMR_SETTING_KEYGUARD_WALLPAPER_URL CONFIG_DEFINE(CFGIT_SETTING_KEYGUARD_WALLPAPER_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {WALLPAPER_IMG_06_PATH})
#else
#define CONFIG_AMR_SETTING_KEYGUARD_WALLPAPER_URL
#endif

#define CONFIG_AMR_SETTING_3D_WALLPAPER_POND_CFG CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_POND_CFG, u32, 3, {0x00000020, 0x00122334, 0x456789ff})

#ifdef __LIVE_WALLPAPER_DROPLET__
#define CONFIG_AMR_SETTING_3D_WALLPAPER_DROPLET_CFG CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_DROPLET_CFG, u16, 1, {0x00000011})
#else
#define CONFIG_AMR_SETTING_3D_WALLPAPER_DROPLET_CFG
#endif

#define CONFIG_AMR_SETTING_3D_WALLPAPER_EARTH_CFG CONFIG_DEFINE(CFGIT_SETTING_3D_WALLPAPER_EARTH_CFG, u8, 1, {0x0})


#define CONFIG_AMR_ANTF_TRACE_SMS_BACKUP CONFIG_DEFINE(CFGIT_ANTF_TRACE_SMS_BACKUP, u8, 400, {0})

// TTS
#ifdef __TTS__
#define CONFIG_AMR_SETTING_TTS_MISSED_CALL_PROMPT  CONFIG_DEFINE(CFGIT_SETTING_TTS_MISSED_CALL_PROMPT, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT  CONFIG_DEFINE(CFGIT_SETTING_TTS_NEW_MESSAGE_PROMPT, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_HOUR_REPORT  CONFIG_DEFINE(CFGIT_SETTING_TTS_HOUR_REPORT, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_WEEK_REPORT  CONFIG_DEFINE(CFGIT_SETTING_TTS_WEEK_REPORT, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_DATE_TIME_REPORT  CONFIG_DEFINE(CFGIT_SETTING_TTS_DATE_TIME_REPORT, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_INCOMMING_CALL_STATUS  CONFIG_DEFINE(CFGIT_SETTING_TTS_INCOMMING_CALL_STATUS, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_INCOMMING_PROMPT_WORDS  CONFIG_DEFINE(CFGIT_SETTING_TTS_INCOMMING_PROMPT_WORDS, MAE_WChar, TTS_PROMPT_TEXT_WCHAR_LEN, {L""})
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_STATUS  CONFIG_DEFINE(CFGIT_SETTING_TTS_NEW_MESSAGE_STATUS, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT_WORDS  CONFIG_DEFINE(CFGIT_SETTING_TTS_NEW_MESSAGE_PROMPT_WORDS, MAE_WChar, TTS_PROMPT_TEXT_WCHAR_LEN, {L""})
#define CONFIG_AMR_SETTING_TTS_AUTO_READ_MESSAGE  CONFIG_DEFINE(CFGIT_SETTING_TTS_AUTO_READ_MESSAGE, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_SETTING_TTS_VOLUME_SETTING  CONFIG_DEFINE(CFGIT_SETTING_TTS_VOLUME_SETTING, TTSSRV_VOLUMESETTING_e, 1, TTSSRV_VolumeSetting_Default)
#define CONFIG_AMR_SETTING_TTS_ATTR_STYLE  CONFIG_DEFINE(CFGIT_SETTING_TTS_ATTR_STYLE, TTSSRV_ATTR_STYLE_e, 1, TTSSRV_Attr_Style_Normal)
#define CONFIG_AMR_SETTING_TTS_ATTR_PITCH  CONFIG_DEFINE(CFGIT_SETTING_TTS_ATTR_PITCH, TTSSRV_ATTR_PITCH_e, 1, TTSSRV_Attr_Pitch_Normal)
#define CONFIG_AMR_SETTING_TTS_ATTR_SPEED  CONFIG_DEFINE(CFGIT_SETTING_TTS_ATTR_SPEED, TTSSRV_ATTR_SPEED_e, 1, TTSSRV_Attr_Normal)
#define CONFIG_AMR_SETTING_TTS_ATTR_ALL_SETTING  CONFIG_DEFINE(CFGIT_SETTING_TTS_ATTR_ALL_SETTING, TTSSrvAttr_t, 1, \
 {TTSSRV_Attr_ReadDigit_Auto,TTSSRV_Attr_ChineseNumOne_Yao,TTSSRV_Attr_Role_YanPing,TTSSRV_Attr_Language_Chinese,TTSSRV_Attr_Style_Normal,TTSSRV_Attr_Normal,TTSSRV_Attr_Pitch_Normal,TTSSRV_Attr_Volume_Normal,TTSSrv_Attr_VeMode_None})
#else
#define CONFIG_AMR_SETTING_TTS_MISSED_CALL_PROMPT
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT
#define CONFIG_AMR_SETTING_TTS_HOUR_REPORT
#define CONFIG_AMR_SETTING_TTS_WEEK_REPORT
#define CONFIG_AMR_SETTING_TTS_DATE_TIME_REPORT
#define CONFIG_AMR_SETTING_TTS_INCOMMING_CALL_STATUS
#define CONFIG_AMR_SETTING_TTS_INCOMMING_PROMPT_WORDS
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_STATUS
#define CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT_WORDS
#define CONFIG_AMR_SETTING_TTS_AUTO_READ_MESSAGE
#define CONFIG_AMR_SETTING_TTS_VOLUME_SETTING
#define CONFIG_AMR_SETTING_TTS_ATTR_STYLE
#define CONFIG_AMR_SETTING_TTS_ATTR_PITCH
#define CONFIG_AMR_SETTING_TTS_ATTR_SPEED
#define CONFIG_AMR_SETTING_TTS_ATTR_ALL_SETTING
#endif
// TTS end

// Breath Light
#ifdef __BREATHLIGHT_MMI__
#define CONFIG_AMR_SETTING_BREATHLIGHT  CONFIG_DEFINE(CFGIT_SETTING_BREATHLIGHT, SetOnOff_e, 1, SET_ON)
#else
#define CONFIG_AMR_SETTING_BREATHLIGHT
#endif
// Breath Light end

#ifdef __WLAN_MMI__
#define CONFIG_AMR_SETTING_WIFI_HOMEPAGE CONFIG_DEFINE(CFGIT_SETTING_WIFI_HOMEPAGE, MAE_WChar, HomePageLength, {L"http://wap.baidu.com"} )
#else
#define CONFIG_AMR_SETTING_WIFI_HOMEPAGE
#endif //__WLAN_MMI__


#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
#define CONFIG_AMR_COUNTDOWNAPP_RINGTONE_URL CONFIG_DEFINE(CONFIG_COUNTDOWNAPP_RINGTONE_URL, MAE_WChar, 266, {L"ad:/SOUND/3000.mid"})
#else
#define CONFIG_AMR_COUNTDOWNAPP_RINGTONE_URL
#endif

#ifdef __APP_MMI_TODOLIST__
#define CONFIG_AMR_TODOLIST_SORTING_MODE	CONFIG_DEFINE(CFGIT_TODOLIST_SORT_MODE, u32 , 1, 1538) //(u32) TASKDBATTR_CHECKSTATUS 0x602=1538
#else
#define CONFIG_AMR_TODOLIST_SORTING_MODE
#endif

// Caller Location
#ifdef __CALLER_LOCATION__
#define CONFIG_AMR_CALLERLOCATION_STATUS    CONFIG_DEFINE(CFGIT_CALLERLOCATION_STATUS, SetOnOff_e, 1, SET_ON)
#define CONFIG_AMR_CALLERLOCATION_DOWNLOAD_URL    CONFIG_DEFINE(CFGIT_CALLERLOCATION_DOWNLOAD_URL, u8, HomePageLength, {"http://114.32.29.193/other/"})
#else
#define CONFIG_AMR_CALLERLOCATION_STATUS
#define CONFIG_AMR_CALLERLOCATION_DOWNLOAD_URL
#endif
// Caller Location end

#ifdef __MMI_CALL_FIREWALL__
#define CONFIG_AMR_CALL_FIREWALL_STATUS CONFIG_DEFINE(CFGIT_CALL_FIREWALL_STATUS, boolean, 1, FALSE)
#define CONFIG_AMR_CALL_FIREWALL_ANSWERING_TYPE CONFIG_DEFINE(CFGIT_CALL_FIREWALL_ANSWERING_TYPE, Firewall_Answering_Type_e, 1, FIREWALL_ANSWERING_TYPE_DEFAULT)
#define CONFIG_AMR_CALL_FIREWALL_FILTER_TYPE CONFIG_DEFINE(CFGIT_CALL_FIREWALL_FILTER_TYPE, Firewall_Filter_Type_e, 1, FIREWALL_FILTER_TYPE_DENY_BLACKLIST_ONLY)
#else
#define CONFIG_AMR_CALL_FIREWALL_STATUS
#define CONFIG_AMR_CALL_FIREWALL_ANSWERING_TYPE
#define CONFIG_AMR_CALL_FIREWALL_FILTER_TYPE
#endif


//********************************************************************************************************************************

/**************************************************************
Customer behavior Setting (Set for change service  inner behavior) (_CUS_)
**************************************************************/
//miss call pop up dialog cancel action setting
enum
{
	MISSCALL_DIALOG_SETTING_CANCEL_WITH_RESET = 0,
	//when miss call dialog is pop up, if user press endkey or cancel key, still auto reset the miss call counter and status bar will clear the miss call icon
	MISSCALL_DIALOG_SETTING_CANCEL_WITHOUT_RESET
	//when miss call dialog is pop up, if user press endkey or cancel key, will not reset the miss call counter
};
typedef u8 CusBehavior_MissCallDialogSetting_e;
#define CONFIG_AMR_CUS_MISSCALLDIALOG_CANCEL_ACTION        CONFIG_DEFINE(CFGIT_CUS_MISSCALLDIALOG_CANCEL_ACTION, CusBehavior_MissCallDialogSetting_e, 1, MISSCALL_DIALOG_SETTING_CANCEL_WITHOUT_RESET)

//else...
#ifdef __MULTI_THEMES_ENABLED__
#define CONFIG_AMR_SETTING_DISPLAY_MENU_CHANGE_THEME      CONFIG_DEFINE(CFGIT_SETTING_DISPLAY_MENU_CHANGE_THEME, u32, 1, 16641) //SET_MENU_CHANGE_THEME_DEFAULT
#else
#define CONFIG_AMR_SETTING_DISPLAY_MENU_CHANGE_THEME
#endif

#ifdef __3D_UI_KEYGUARD_BEAUTY_CLK__
#define CONFIG_AMR_BEAUTY_CLOCK_SETTING_KEYGUARD CONFIG_DEFINE(CONFIG_BEAUTY_CLOCK_SETTING_KEYGUARD, boolean, 1, TRUE)
#else
#define CONFIG_AMR_BEAUTY_CLOCK_SETTING_KEYGUARD
#endif

#ifdef __GOGOBOX_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_GOGOBOX_CFG  CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_GOGOBOX_CFG, u32, 1, 0x1)
#else
#define CONFIG_AMR_SETTING_3D_GAME_GOGOBOX_CFG
#endif

#ifdef __VAMPIRE_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_VAMPIRE_CFG		CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_VAMPIRE_CFG, u32, 1, 0x1)
#else
#define CONFIG_AMR_SETTING_3D_GAME_VAMPIRE_CFG
#endif

#ifdef __ZOMBIE_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_ZOMBIE_CFG		CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_ZOMBIE_CFG, u8, 1, 0)
#else
#define CONFIG_AMR_SETTING_3D_GAME_ZOMBIE_CFG
#endif

#ifdef __RUBIKCUBE_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_RUBIKSCUBE_CFG   CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_RUBIKSCUBE_CFG, u32, 1, 0x1)
#else
#define CONFIG_AMR_SETTING_3D_GAME_RUBIKSCUBE_CFG
#endif

#ifdef __IPLAYCUBE_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_IPLAYCUBE_CFG    CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_IPLAYCUBE_CFG, u32, 1, 0x1)
#else
#define CONFIG_AMR_SETTING_3D_GAME_IPLAYCUBE_CFG
#endif

#ifdef __ANGRYBIRD_GAME__
#define CONFIG_AMR_SETTING_PHYSIC_GAME_ANGRYBIRD_CFG    CONFIG_DEFINE(CFGIT_SETTING_PHYSIC_GAME_ANGRYBIRD_CFG, u32, 11, {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0})
#else
#define CONFIG_AMR_SETTING_PHYSIC_GAME_ANGRYBIRD_CFG
#endif

#ifdef __FISHFURY_GAME__
#define CONFIG_AMR_SETTING_GAME_FISHFURY_BEST_SCORE CONFIG_DEFINE(CFGIT_SETTING_GAME_FISHFURY_BEST_SCORE, u16, 10, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, })
#define CONFIG_AMR_SETTING_GAME_FISHFURY_MUSIC CONFIG_DEFINE(CFGIT_SETTING_GAME_FISHFURY_MUSIC, u8, 1, 1)
#else
#define CONFIG_AMR_SETTING_GAME_FISHFURY_BEST_SCORE
#define CONFIG_AMR_SETTING_GAME_FISHFURY_MUSIC
#endif

#ifdef __FRUITSLICE_GAME__
#define CONFIG_AMR_FRUITSLICE_CFG             CONFIG_DEFINE(CFGIT_FRUITSLICE_CFG, u32, 1, 0x3)
#define CONFIG_AMR_FRUITSLICE_BEST_SCORE      CONFIG_DEFINE(CFGIT_FRUITSLICE_BEST_SCORE, u32, 1, 0)
#else
#define CONFIG_AMR_FRUITSLICE_CFG
#define CONFIG_AMR_FRUITSLICE_BEST_SCORE
#endif

#ifdef __LABYRINTH_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_STAGE_OPEN CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_LABYRINTH_STAGE_OPEN, u8, 1, 1)
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_CFG CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_LABYRINTH_CFG, boolean, 4, {TRUE, TRUE, TRUE, TRUE})
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_BEST_SCORE CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_LABYRINTH_BEST_SCORE, u16, 24, {3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, 3599, })
#else
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_STAGE_OPEN
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_CFG
#define CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_BEST_SCORE
#endif

#ifdef __CUTROPE_GAME__
#define CONFIG_AMR_SETTING_3D_GAME_CUTROPE_SCORE CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_CUTROPE_SCORE, u8, 36, {0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,})
#define CONFIG_AMR_SETTING_3D_GAME_CUTROPE_CONFIG CONFIG_DEFINE(CFGIT_SETTING_3D_GAME_CUTROPE_CONFIG, u8, 1, 1)
#else
#define CONFIG_AMR_SETTING_3D_GAME_CUTROPE_SCORE
#define CONFIG_AMR_SETTING_3D_GAME_CUTROPE_CONFIG
#endif

//notepad desktop
#define CONFIG_AMR_NOTEPAD_CURRENT_NOTE_INDEX CONFIG_DEFINE(CONFIG_NOTEPAD_CURRENT_NOTE_INDEX, u8, 1, 0)
#define CONFIG_AMR_NOTEPAD_NEED_READ_CFG CONFIG_DEFINE(CONFIG_NOTEPAD_NEED_READ_CFG, boolean, 1, FALSE)

//dialer group
#define CONFIG_AMR_DIALERGROUP_CURRENT_AP_INDEX CONFIG_DEFINE(CONFIG_DIALERGROUP_CURRENT_AP_INDEX, u8, 1, 0)
#define CONFIG_AMR_DIALERGROUP_PHB_NEED_GROUP CONFIG_DEFINE(CONFIG_DIALERGROUP_PHB_NEED_GROUP, boolean, 1, 0)

#define CONFIG_AMR_GROUP_HIDING CONFIG_DEFINE(CONFIG_GROUP_HIDING, boolean, 1, 1)

#ifdef __NETWORK_COUNTER_MMI__
#define CONFIG_AMR_NETWORKCOUNTER_SIM_MASTER CONFIG_DEFINE(CFGIT_NETWORKCOUNTER_SIM_MASTER, u8, 9, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00})
#define CONFIG_AMR_NETWORKCOUNTER_SIM_SLAVE  CONFIG_DEFINE(CFGIT_NETWORKCOUNTER_SIM_SLAVE , u8, 9, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00})
#else
#define CONFIG_AMR_NETWORKCOUNTER_SIM_MASTER
#define CONFIG_AMR_NETWORKCOUNTER_SIM_SLAVE
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_PHOTOSLIDE_MMI__)
#define CONFIG_AMR_PHOTOSLIDE_WIDGET_CURIDX                     CONFIG_DEFINE(CFGIT_PHOTOSLIDE_WIDGET_CURIDX, u32, 1, 0)
#define CONFIG_AMR_PHOTOSLIDE_WIDGET_TYPE                     CONFIG_DEFINE(CFGIT_PHOTOSLIDE_WIDGET_TYPE, u8, 1, 0)
#else
#define CONFIG_AMR_PHOTOSLIDE_WIDGET_CURIDX
#define CONFIG_AMR_PHOTOSLIDE_WIDGET_TYPE
#endif

#ifdef __NETWORK_SETTING_CUS__
#define CONFIG_NAMR_NETWORK_SETTING_CUS CONFIG_DEFINE(CFGIT_SYS_NETWORK_CUS_BOOT_FIRST_TIME, boolean, 1, TRUE)
#else
#define CONFIG_NAMR_NETWORK_SETTING_CUS
#endif
//********************************************************************************************************************************

#define COMMON_AMR_ALL_CONFIG \
/*call setting*/           CONFIG_AMR_CALLSETTING_CALLER_ID \
                        CONFIG_AMR_CALLSETTING_CALLER_ID_SLAVE \
                        CONFIG_AMR_CALLSETTING_ANSWER_MODE \
                        CONFIG_AMR_CALLSETTING_VIDEO_CALL \
                        CONFIG_AMR_CALLSETTING_VIDEO_CALL_LOOPBACK \
                        CONFIG_AMR_CALLSETTING_VIDEO_CALL_STORAGE \
                        CONFIG_AMR_CALLSETTING_AUTO_REDIAL \
                        CONFIG_AMR_CALLSETTING_AUTO_ANSWER \
                        CONFIG_AMR_CALLSETTING_ANSWER_INDICATOR \
                        CONFIG_AMR_CALLSETTING_MINUTE_REMINDER \
                        CONFIG_AMR_CALL_SETTING_IPCALL_LIST \
                        CONFIG_AMR_CALLSETTING_REJECT_MT \
                        CONFIG_AMR_CALLSETTING_HALL_OPEN_ANSWER \
                        CONFIG_AMR_CALLSETTING_HALL_CLOSE_HANG_UP \
                        CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_STATUS \
                        CONFIG_AMR_CALLSETTING_DISTORTED_VOICE_EFFECT \
                        CONFIG_AMR_CALLSETTING_AM_STATUS \
                        CONFIG_AMR_CALLSETTING_AM_ANSWER_GREETING_VOICE_URL \
                        CONFIG_AMR_CALLSETTING_AM_BEEP_URL \
                        CONFIG_AMR_CALLSETTING_AM_AUTO_ANSWER_AFTER_RING \
                        CONFIG_AMR_CALLSETTING_AM_STORAGE \
                        CONFIG_AMR_CALLSETTING_AM_VOICE_BOX_COUNT \
                        CONFIG_AMR_CALLSETTING_CBS_STATUS \
                        CONFIG_AMR_CALLSETTING_CBS_PLAY_TYPE \
                        CONFIG_AMR_CALLSETTING_CBS_PLAY_INTERVAL \
                        CONFIG_AMR_CALLSETTING_CBS_CURRENT_EFFECT \
                        CONFIG_AMR_CALLSETTING_CBS_VOLUME \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_1 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_2 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_3 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_4 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_5 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_6 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_7 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_8 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_9 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_10 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_11 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_12 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_13 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_14 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_15 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_16 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_17 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_18 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_19 \
                        CONFIG_AMR_CALLSETTING_CBS_EFFECT_SOUND_20 \
                        CONFIG_AMR_CALLSETTING_AUTO_RECORDING \
                        CONFIG_AMR_DEBUG_DBB_ANTF_TRACE \
                        CONFIG_AMR_CALL_FIREWALL_STATUS \
                        CONFIG_AMR_CALL_FIREWALL_ANSWERING_TYPE \
                        CONFIG_AMR_CALL_FIREWALL_FILTER_TYPE \
                        CONFIG_AMR_DEBUG_DBB_SILENT_REBOOT \
/*voice memo*/          CONFIG_AMR_VOICEMEMO_RECORD_FORMAT \
/*call setting*/           CONFIG_AMR_CB_MASTER_SETTING_AUTO_DISPLAY \
                        CONFIG_AMR_CB_SLAVE_SETTING_AUTO_DISPLAY \
                        CONFIG_AMR_CB_MASTER_SETTING_RECEPTION \
                        CONFIG_AMR_CB_MASTER_SETTING_CELL_INFORMATION \
                        CONFIG_AMR_CB_SLAVE_SETTING_RECEPTION \
                        CONFIG_AMR_CB_SLAVE_SETTING_CELL_INFORMATION \
                        CONFIG_AMR_MESSAGE_CB_MASTER_TOPICLIST \
                        CONFIG_AMR_MESSAGE_CB_SLAVE_TOPICLIST \
                        CONFIG_AMR_MESSAGE_CB_MASTER_LANGLIST \
                        CONFIG_AMR_MESSAGE_CB_SLAVE_LANGLIST \
/*consetting*/            CONFIG_AMR_CONNECT_DATA_ACCOUNT1 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT2 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT3 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT4 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT5 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT6 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT7 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT8 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT9 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT10 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT11 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT12 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT13 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT14 \
                        CONFIG_AMR_CONNECT_DATA_ACCOUNT15 \
                        CONFIG_AMR_CONNECT_GPRS_SETTINGS \
                        CONFIG_AMR_CONNECT_WAP_PROFILE1 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE2 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE3 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE4 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE5 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE6 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE7 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE8 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE9 \
                        CONFIG_AMR_CONNECT_WAP_PROFILE10 \
                        CONFIG_AMR_CONNECT_WAP_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_WAP_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE1 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE2 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE3 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE4 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE5 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE6 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE7 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE8 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE9 \
                        CONFIG_AMR_CONNECT_MMS_PROFILE10 \
                        CONFIG_AMR_CONNECT_MMS_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_MMS_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE1 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE2 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE3 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE4 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE5 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE6 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE7 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE8 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE9 \
                        CONFIG_AMR_CONNECT_JAVA_PROFILE10 \
                        CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_JAVA_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE1 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE2 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE3 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE4 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE5 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE6 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE7 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE8 \
                        CONFIG_AMR_CONNECT_OTHER_PROFILE9 \
                        CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_OTHER_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE1 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE2 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE3 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE4 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE5 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE6 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE7 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE8 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE9 \
                        CONFIG_AMR_CONNECT_LBS_PROFILE10 \
                        CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_LBS_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE1 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE2 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE3 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE4 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE5 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE6 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE7 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE8 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE9 \
                        CONFIG_AMR_CONNECT_EMAIL_PROFILE10 \
                        CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_EMAIL_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_EMAIL_DEFAULT_ACCOUNT_ID \
                        CONFIG_AMR_CONNECT_QQ_PROFILE1 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE2 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE3 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE4 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE5 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE6 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE7 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE8 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE9 \
                        CONFIG_AMR_CONNECT_QQ_PROFILE10 \
                        CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_QQ_ACTIVE_PROFILE_SIM2 \
	                    CONFIG_AMR_CONNECT_NTP_PROFILE1 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE2 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE3 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE4 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE5 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE6 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE7 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE8 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE9 \
                        CONFIG_AMR_CONNECT_NTP_PROFILE10 \
                        CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_NTP_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE1 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE2 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE3 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE4 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE5 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE6 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE7 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE8 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE9 \
                        CONFIG_AMR_CONNECT_STREAMING_PROFILE10 \
                        CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM1 \
                        CONFIG_AMR_CONNECT_STREAMING_ACTIVE_PROFILE_SIM2 \
                        CONFIG_AMR_CONNECT_WAP_CONNECT_SET \
                        CONFIG_AMR_CONNECT_OTHER_CONNECT_SET \
                        CONFIG_AMR_CONNECT_JAVA_CONNECT_SET \
                        CONFIG_AMR_CONNECT_EMAIL_CONNECT_SET \
                        CONFIG_AMR_CONNECT_QQ_CONNECT_SET \
	                    CONFIG_AMR_CONNECT_NTP_CONNECT_SET \
	                    CONFIG_AMR_CONNECT_NTP_CONNECT_SERVER \
                        CONFIG_AMR_CONNECT_STREAMING_CONNECT_SET \
                        CONFIG_AMR_APN_DETECTION_SIM1 \
                        CONFIG_AMR_APN_DETECTION_SIM2 \
/*Date time*/            CONFIG_AMR_SETTING_PHONE_TIME_ZONE_AUTOMATIC_UPDATE \
                        CONFIG_AMR_SETTING_PHONE_DATE_FORMAT \
                        CONFIG_AMR_SETTING_PHONE_TIME_FORMAT \
                        CONFIG_AMR_SETTING_PHONE_SECOND_TIME \
                        CONFIG_AMR_SECOND_TIMEZONE \
                        CONFIG_AMR_SYS_TIMEZONE \
                        CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK1 \
                        CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK2 \
                        CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK3 \
                        CONFIG_AMR_SYS_TIMEZONE_WIDGET_CLOCK4 \
/*Display*/              CONFIG_AMR_SETTING_DISPLAY_MENU_TRANSITION_STATUS \
                        CONFIG_AMR_SETTING_DISPLAY_OTHERS_TRANSITION_STATUS \
                        CONFIG_AMR_SETTING_PHONE_DAYLIGHT_SAVING_TIME \
                        CONFIG_AMR_SETTING_DISPLAY_BACKLIGHT_DURATION \
                        CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_DURATION \
                        CONFIG_AMR_SETTING_DISPLAY_LAST_BACKLIGHT_LEVEL \
                        CONFIG_AMR_SETTING_DISPLAY_LUNAR_CALENDAR \
                        CONFIG_AMR_SETTING_DISPLAY_MENU_ANIMATION_STYLE \
                        CONFIG_AMR_SETTING_DISPLAY_MENU_STYLE \
                        CONFIG_AMR_SETTING_DISPLAY_OPERATOR_NAME \
                        CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_3D_STYLE \
                        CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_DURATION \
                        CONFIG_AMR_SETTING_DISPLAY_SCREEN_SAVER_STATUS \
                        CONFIG_AMR_SETTING_DISPLAY_START_POWER_SAVING_TIME \
                        CONFIG_AMR_SETTING_DISPLAY_BACKLIGHT_LEVEL \
                        CONFIG_AMR_SETTING_3D_WALLPAPER_ID \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_TYPE \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_BEZIER_NUM \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_SPEED \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_NUM \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BIG_NUM \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_DIR \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_BLOW_TIME \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_PILE_SPEED \
                        CONFIG_AMR_SETTING_DISPLAY_SCREENEFFECT_SNOW_COLOR \
/*Idle Pet Clock Feature*/  CONFIG_AMR_IDLEAPP_SHORTCUTBAR \
                        CONFIG_AMR_IDLEAPP_CLOCK_POS \
                        CONFIG_AMR_IDLEAPP_CALENDAR_POS \
                        CONFIG_AMR_IDLEAPP_TODOLIST_POS \
                        CONFIG_AMR_IDLEAPP_QQ_POS \
                        CONFIG_AMR_IDLEAPP_DIGCLOCK_POS \
                        CONFIG_AMR_IDLEAPP_MAP_POS \
                        CONFIG_AMR_IDLEAPP_FMRADIO_POS \
                        CONFIG_AMR_IDLEAPP_GAME_POS \
                        CONFIG_AMR_IDLEAPP_LIVEWALLPAPER_POS \
                        CONFIG_AMR_IDLEAPP_OPERATOR_POS \
                        CONFIG_AMR_IDLEAPP_MPLAYER_POS \
                        CONFIG_AMR_IDLEAPP_NOTE_POS \
                        CONFIG_AMR_IDLEAPP_PROFILE_POS \
                        CONFIG_AMR_IDLEAPP_SEARCH_POS \
	CONFIG_AMR_IDLEAPP_FLIP_WDG_IDX \
                        CONFIG_AMR_SHORTCUTBAR_ITEM_ORDER \
                        CONFIG_AMR_SETTING_PHONE_AUTO_POWER_ON_TIME \
                        CONFIG_AMR_SETTING_PHONE_AUTO_POWER_OFF_TIME \
                        CONFIG_AMR_SETTING_PHONE_AUTO_POWER_ON_STATUS \
                        CONFIG_AMR_SETTING_PHONE_AUTO_POWER_OFF_STATUS \
                        CONFIG_AMR_SETTING_SLIDE_TO_POWER_OFF_STATUS \
                        CONFIG_AMR_SETTING_RINGTONE_VOLUME \
                        CONFIG_AMR_SETTING_INCALL_VOLUME \
                        CONFIG_AMR_SETTING_INCALL_CLSETTING_SHOW_MT \
                        CONFIG_AMR_SETTING_INCALL_CLSETTING_SHOW_MO \
                        CONFIG_AMR_SETTING_RINGTONE_POWER_ON_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_POWER_OFF_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_VOICE_CALL_RING_TYPE \
                        CONFIG_AMR_SETTING_RINGTONE_MESSAGE_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_CALENDAR_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_ALARM_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_MISS_EVENT_REMINDER \
                        CONFIG_AMR_SETTING_RINGTONE_KEYPAD_TONE \
                        CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE \
                        CONFIG_AMR_SETTING_IDLE_HALL_CLOSE_KEYGUARD \
						CONFIG_AMR_SETTING_FONT_STYLE \
                        CONFIG_AMR_SETTING_PHONE_LANGUAGE \
                        CONFIG_AMR_SETTING_PHONE_INPUT_LANGUAGE \
                        CONFIG_AMR_SETTING_ENCODING \
                        CONFIG_AMR_SETTING_PHONE_SELECTED_CHINESE_INPUT_MODE \
						CONFIG_AMR_SETTING_PHONE_SELECTED_NOT_CHINESE_INPUT_MODE \
                        CONFIG_AMR_SETTING_PHONE_INPUT_MODE_ABC \
                        CONFIG_AMR_SETTING_PHONE_INPUT_MODE_SMART \
                        CONFIG_AMR_SETTING_PHONE_SOFTKEYBOARD_STATUS \
						CONFIG_AMR_SETTING_PHONE_HANDWRITING_ONOFF \
                        CONFIG_AMR_PHBAPP_BLACKLIST \
                        CONFIG_AMR_NETWORKSETTING_REG_MODE \
                        CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE \
                        CONFIG_AMR_NETWORKSETTING_REG_MODE_SLAVE \
                        CONFIG_AMR_NETWORKSETTING_NET_ACCESS_MODE_SLAVE \
                        CONFIG_AMR_SETTING_PHONE_DEFAULT_SIM \
                        CONFIG_AMR_NATIVEGAME_SETTING_VOLUME \
                        CONFIG_AMR_NATIVEGAME_BIG2_SETTING_VOLUME \
                        CONFIG_AMR_NATIVEGAME_BIG2_SETTING_SOUND \
                        CONFIG_AMR_NATIVEGAME_PACMAN_SETTING_VOLUME \
                        CONFIG_AMR_NATIVEGAME_PACMAN_SETTING_SOUND \
                        CONFIG_AMR_SETTING_RINGTONE_VIBRATE_TYPE \
                        CONFIG_AMR_MPLAYER_3DSURROUND \
                        CONFIG_AMR_MPLAYER_REVERB \
                        CONFIG_AMR_MPLAYER_EQ \
                        CONFIG_AMR_MPLAYER_DOLBY \
                        CONFIG_AMR_MPLAYER_LYRIC \
                        CONFIG_AMR_MPLAYER_REPEAT \
                        CONFIG_AMR_MPLAYER_SHUFFLE \
                        CONFIG_AMR_MPLAYER_VOLUME \
                        CONFIG_AMR_MPLAYER_PITCHSHIFT\
                        CONFIG_AMR_MPLAYER_BACKGROUND_PLAY \
                        CONFIG_AMR_MPLAYER_SRS \
                        CONFIG_AMR_MPLAYER_SRS_TYPE \
                        CONFIG_AMR_MPLAYER_SRS_PARAM_NORMAL \
                        CONFIG_AMR_MPLAYER_SRS_PARAM_CLASSIC \
                        CONFIG_AMR_MPLAYER_SRS_PARAM_BASS \
                        CONFIG_AMR_MPLAYER_SRS_PARAM_HIPHOP \
                        CONFIG_AMR_MPLAYER_SRS_PARAM_PERFORM \
                        CONFIG_AMR_MPLAYER_VIRTUALBASS \
                        CONFIG_AMR_SETTING_FMRADIO_VOLUME \
                        CONFIG_AMR_SETTING_ATV_VOLUME \
                        CONFIG_AMR_SETTING_VOICEMEMO_VOLUME \
                        CONFIG_AMR_SETTING_FILEMGR_VOLUME \
                        CONFIG_AMR_SETTING_DISPLAY_MAIN_DISPLAY_WALLPAPER_URL \
                        CONFIG_AMR_SETTING_DISPLAY_MAINMENU_IMG_BG_URL \
                        CONFIG_AMR_SETTING_DISPLAY_POWER_OFF_ANIMATION_URL \
                        CONFIG_AMR_SETTING_DISPLAY_POWER_OFF_RINGTONE_URL \
                        CONFIG_AMR_SETTING_DISPLAY_POWER_ON_ANIMATION_URL \
                        CONFIG_AMR_SETTING_DISPLAY_POWER_ON_RINGTONE_URL \
                        CONFIG_AMR_SETTING_DISPLAY_SUB_DISPLAY_WALLPAPER_URL \
                        CONFIG_AMR_SETTING_DISPLAY_DISPLAY_SCREEN_SAVER_URL \
                        CONFIG_AMR_SETTING_RINGTONE_ALARM_MELODY_URL \
                        CONFIG_AMR_SETTING_RINGTONE_CALENDAR_MELODY_URL \
                        CONFIG_AMR_SETTING_RINGTONE_MESSAGE_MELODY_URL \
                        CONFIG_AMR_SETTING_RINGTONE_SIM2_MESSAGE_MELODY_URL \
                        CONFIG_AMR_SETTING_RINGTONE_VOICE_CALL_MELODY_URL \
                        CONFIG_AMR_SETTING_RINGTONE_SIM2_VOICE_CALL_MELODY_URL \
                        CONFIG_AMR_SETTING_VOICE_CALL_DEFAULT_CALLER_IMAGE_URL \
                        CONFIG_AMR_SETTING_RINGTONE_HALL_OPEN_TONE_URL \
                        CONFIG_AMR_SETTING_3D_WALLPAPER_POND_CFG \
                        CONFIG_AMR_SETTING_3D_WALLPAPER_DROPLET_CFG \
                        CONFIG_AMR_SETTING_3D_WALLPAPER_EARTH_CFG \
/* camera*/             CONFIG_AMR_DUAL_CAMERA_TYPE \
                        CONFIG_AMR_ANTF_TRACE_SMS_BACKUP \
                        CONFIG_AMR_MESSAGE_BLACKLIST_STATUS \
                        CONFIG_AMR_PRIVATESETTING_LIST \
/*G-sensor*/            CONFIG_AMR_SETTING_GSENSOR_WND_AUTOROTATE\
                        CONFIG_AMR_SETTING_GSENSOR_SHAKE_WALLPAPER\
                        CONFIG_AMR_SETTING_GSENSOR_SHAKE_SONG\
                        CONFIG_AMR_SETTING_GSENSOR_CHANGE_PICTURE\
                        CONFIG_AMR_SETTING_GSENSOR_ROTATE_PICTURE\
                        CONFIG_AMR_SETTING_GSENSOR_FLIP_SILENT\
 /* TTS */              CONFIG_AMR_SETTING_TTS_MISSED_CALL_PROMPT\
                        CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT\
                        CONFIG_AMR_SETTING_TTS_HOUR_REPORT\
                        CONFIG_AMR_SETTING_TTS_WEEK_REPORT\
                        CONFIG_AMR_SETTING_TTS_DATE_TIME_REPORT\
                        CONFIG_AMR_SETTING_TTS_INCOMMING_CALL_STATUS\
                        CONFIG_AMR_SETTING_TTS_INCOMMING_PROMPT_WORDS\
                        CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_STATUS\
                        CONFIG_AMR_SETTING_TTS_NEW_MESSAGE_PROMPT_WORDS\
                        CONFIG_AMR_SETTING_TTS_AUTO_READ_MESSAGE\
                        CONFIG_AMR_SETTING_TTS_VOLUME_SETTING\
                        CONFIG_AMR_SETTING_TTS_ATTR_STYLE\
                        CONFIG_AMR_SETTING_TTS_ATTR_PITCH\
                        CONFIG_AMR_SETTING_TTS_ATTR_SPEED\
                        CONFIG_AMR_SETTING_TTS_ATTR_ALL_SETTING\
/* Breath Light */         CONFIG_AMR_SETTING_BREATHLIGHT\
/* Caller Location*/       CONFIG_AMR_CALLERLOCATION_STATUS\
                        CONFIG_AMR_CALLERLOCATION_DOWNLOAD_URL\
/* ToDoList SortMode */	CONFIG_AMR_TODOLIST_SORTING_MODE\
                        CONFIG_AMR_CUS_MISSCALLDIALOG_CANCEL_ACTION\
/* hall switch*/           CONFIG_AMR_SETTING_RINGTONE_SLIDE_SOUND_STATUS\
                        CONFIG_AMR_SETTING_DISPLAY_MENU_CHANGE_THEME \
                        CONFIG_AMR_SETTING_WIFI_HOMEPAGE\
                        CONFIG_AMR_COUNTDOWNAPP_RINGTONE_URL \
                        CONFIG_AMR_PHOTOSLIDE_WIDGET_CURIDX \
                        CONFIG_AMR_PHOTOSLIDE_WIDGET_TYPE \
/* smart search*/         CONFIG_AMR_SMART_SEARCH_TYPE  \
                        CONFIG_AMR_BEAUTY_CLOCK_SETTING_KEYGUARD \
                        CONFIG_AMR_SETTING_3D_GAME_VAMPIRE_CFG\
                        CONFIG_AMR_SETTING_3D_GAME_ZOMBIE_CFG\
                        CONFIG_AMR_SETTING_3D_GAME_GOGOBOX_CFG \
                        CONFIG_AMR_SETTING_3D_GAME_RUBIKSCUBE_CFG \
                        CONFIG_AMR_SETTING_3D_GAME_IPLAYCUBE_CFG \
                        CONFIG_AMR_SETTING_PHYSIC_GAME_ANGRYBIRD_CFG \
                        CONFIG_AMR_SETTING_GAME_FISHFURY_BEST_SCORE \
                        CONFIG_AMR_SETTING_GAME_FISHFURY_MUSIC \
                        CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_STAGE_OPEN \
                        CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_CFG \
                        CONFIG_AMR_SETTING_3D_GAME_LABYRINTH_BEST_SCORE \
                        CONFIG_AMR_SETTING_3D_GAME_CUTROPE_SCORE \
                        CONFIG_AMR_SETTING_3D_GAME_CUTROPE_CONFIG \
                        CONFIG_AMR_NOTEPAD_CURRENT_NOTE_INDEX \
                        CONFIG_AMR_NOTEPAD_NEED_READ_CFG \
                        CONFIG_AMR_DIALERGROUP_CURRENT_AP_INDEX \
                        CONFIG_AMR_DIALERGROUP_PHB_NEED_GROUP \
                        CONFIG_AMR_FRUITSLICE_CFG \
                        CONFIG_AMR_FRUITSLICE_BEST_SCORE \
                        CONFIG_AMR_SETTING_KEYGUARD_WALLPAPER_URL\
                        CONFIG_AMR_NETWORKCOUNTER_SIM_MASTER\
                        CONFIG_AMR_NETWORKCOUNTER_SIM_SLAVE\
                        CONFIG_AMR_GROUP_HIDING \
                        CONFIG_NAMR_NETWORK_SETTING_CUS

#endif //__MMI_COMMON_CFG__H__
