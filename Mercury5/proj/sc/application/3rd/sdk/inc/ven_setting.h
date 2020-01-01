/**
 *
 * @file    ven_setting.h
 * @brief   This file defines the MMI profile and network related settings request vendor API, and response data structure
 *
 * @author  Jorena.Ku
 * @version $Id: ven_setting.h 44157 2009-10-27 07:47:16Z sata.yeh $
 *
 */
#ifndef __VEN_SETTING_DEFINE_H_
#define __VEN_SETTING_DEFINE_H_

#include "ven_sdk.h"
#include "ven_file.h"
#include "ven_cam.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_SETTING_RET_SUCCESS             = 0, ///< operation completed successfully
    VEN_SETTING_RET_BAD_PARAM           = 1, ///< invalid input parameters
    VEN_SETTING_RET_FAILED              = 2, ///< WHAT? every code here is failed
    VEN_SETTING_RET_OUT_OF_MEMORY       = 3, ///< memory is not enough to complete the operation
};
typedef u32 ven_setting_ret_t;

/**
 * MMI Profile Settings
 */
enum
{
    VEN_SETTING_FILE_WALLPAPER = 0,
    VEN_SETTING_FILE_RINGTONE_INCOMING,
    VEN_SETTING_FILE_RINGTONE_ALARM,
    VEN_SETTING_FILE_RINGTONE_MESSAGE,
    VEN_SETTING_FILE_RINGTONE_INCOMING_SIM2,
    VEN_SETTING_FILE_RINGTONE_MESSAGE_SIM2,
    VEN_SETTING_FILE_MAINMENU_IMG_BG,    
    VEN_SETTING_FILE_POWER_OFF_ANIMATION,
    VEN_SETTING_FILE_POWER_ON_ANIMATION,
    VEN_SETTING_FILE_POWER_OFF_RINGTONE,
    VEN_SETTING_FILE_POWER_ON_RINGTONE,
    VEN_SETTING_FILE_SIZE
};
typedef u8 ven_setting_file_type_t;

enum
{
    VEN_SETTING_PROFILE_VOLUME_INCOMING = 0,
    VEN_SETTING_PROFIEL_VOLUME_ALARM,
    VEN_SETTING_PROFILE_VOLUME_MESSAGE,
    VEN_SETTING_PROFILE_VOLUME_SIZE
};
typedef u8 ven_setting_profile_volume_type_t;

enum
{
    VEN_SETTING_PROFILE_VIBRATE_INCOMING = 0,
    VEN_SETTING_PROFIEL_VIBRATE_ALARM,
    VEN_SETTING_PROFILE_VIBRATE_MESSAGE,
    VEN_SETTING_PROFILE_VIBRATE_SIZE,
};
typedef u8 ven_setting_profile_vibration_type_t;


enum
{
    VEN_SETTING_PROFILE_VIBRATION_OFF = 0,
    VEN_SETTING_PROFILE_VIBRATION_ON,
    VEN_SETTING_PROFILE_VIBRATION_SIZE,
};
typedef u8 ven_setting_profile_vibration_value_t;

enum
{
    VEN_SETTING_PROFILE_KEYPAD_TONE_OFF = 0,
    VEN_SETTING_PROFILE_KEYPAD_TONE_ON,
    VEN_SETTING_PROFILE_KEYPAD_TONE_SIZE,
};
typedef u8 ven_setting_profile_keypad_tone_value_t;

//Steve Lee - 1028
#define  VEN_SETTING_MAX_URL_LEN    VEN_FILE_FAT_SPEC_FULLPATH_LEN //MAX_CHAR_LFN //(MAE_MAX_FILEPATH_LEN-3) =>3 means "fs:"


/**
 * Network Connect Profile Settings
 */
#define VEN_SETTING_MAX_LEN_PRFNAME    15     /* max len(profile name) in UCS2 */
#define VEN_SETTING_MAX_LEN_SERVERURL  256    /* max len(server URL) in ASCII */
#define VEN_SETTING_MAX_LEN_LONG_SERVERURL  1024    /* max len(server URL) in ASCII */ 
#define VEN_SETTING_MAX_LEN_GPRSAPN    50     /* max len(GPRS APN) in ASCII */
#define VEN_SETTING_MAX_LEN_USERNAME   31     /* max len(username) in ASCII */
#define VEN_SETTING_MAX_LEN_PASSWORD   31     /* max len(password) in ASCII */
#define VEN_SETTING_IP_BYTESIZE        4      /* xxx.xxx.xxx.xxx */
#define VEN_SETTING_MAX_LEN_MMS_WSP_HEADER     1024   /*max len (MMS WSP header) */
#define VEN_SETTING_MMS_WSP_HEADER "User-Agent:Nokia6120c\r\nProfile:http://nds1.nds.nokia.com/uaprof/N6120c-1r100-CV2G.xml\r\nAccept:*/*\r\nCache-Control:no-cache\r\nPragma:no-cache\r\n"
enum
{
    VEN_SETTING_NETWORK_PROFILE_TYPE_WAP = 0,
    VEN_SETTING_NETWORK_PROFILE_TYPE_MMS,
    VEN_SETTING_NETWORK_PROFILE_TYPE_JAVA,
    VEN_SETTING_NETWORK_PROFILE_TYPE_EMAIL,
    VEN_SETTING_NETWORK_PROFILE_TYPE_QQ,
    VEN_SETTING_NETWORK_PROFILE_TYPE_WAP_CONNECT_SET,
    VEN_SETTING_NETWORK_PROFILE_TYPE_JAVA_CONNECT_SET,
    VEN_SETTING_NETWORK_PROFILE_TYPE_EMAIL_CONNECT_SET,
    VEN_SETTING_NETWORK_PROFILE_TYPE_QQ_CONNECT_SET,
    VEN_SETTING_NETWORK_PROFILE_TYPE_VDO_STREAMING,
    VEN_SETTING_NETWORK_PROFILE_TYPE_VDO_STREAMING_CONNECT_SET,
    VEN_SETTING_NETWORK_PROFILE_TYPE_SIZE
};
typedef u8 ven_setting_network_profile_type_t;

enum
{
    VEN_SETTING_NETWORK_PROTOCOL_WAP = 0,
    VEN_SETTING_NETWORK_PROTOCOL_HTTP,
};
typedef u8 ven_setting_network_protocol_t;

enum
{
    VEN_SETTING_NETWORK_AUTH_NORMAL = 0,
    VEN_SETTING_NETWORK_AUTH_SEC,
};
typedef u8 ven_setting_network_auth_t;

enum
{
    VEN_SETTING_NETWORK_CONNECTSET_WIFI_ONLY = 0,
    VEN_SETTING_NETWORK_CONNECTSET_GPRS_ONLY = 1,
    VEN_SETTING_NETWORK_CONNECTSET_WIFI_PREFERRED = 2,
    VEN_SETTING_NETWORK_CONNECTSET_GPRS_PREFERRED = 3,
};
typedef u8 ven_setting_network_connectset_t;

typedef struct
{
    u16 PrfName[(VEN_SETTING_MAX_LEN_PRFNAME + 1)];  /* profile name (in UCS2) */
    u16 nProxyPort;
    ven_setting_network_protocol_t tProtocol;        /* type of WAP protocol: WAP/HTTP */
    ven_setting_network_auth_t Auth;                 /* Connect Bearer: GPRS Auth */
    u8 ServerUrl[VEN_SETTING_MAX_LEN_SERVERURL + 1]; /* Only for WAP and MMS Profile */
    u8 ProxyIp[VEN_SETTING_IP_BYTESIZE];

    u8 GprsApn[VEN_SETTING_MAX_LEN_GPRSAPN + 1];     /* Connect Bearer: GPRS APN  */
    u8 Username[VEN_SETTING_MAX_LEN_USERNAME + 1];   /* Connect Bearer: User Name */
    u8 Password[VEN_SETTING_MAX_LEN_PASSWORD + 1];   /* Connect Bearer: Password  */
    u8 DnsIp[VEN_SETTING_IP_BYTESIZE];               /* Connect Bearer: DNS IP    */
    ven_setting_network_connectset_t tConnSet;
} ven_setting_network_profile_t;

typedef struct
{
    u16 PrfName[(VEN_SETTING_MAX_LEN_PRFNAME + 1)];  /* profile name (in UCS2) */
    u16 nProxyPort;
    ven_setting_network_protocol_t tProtocol;        /* type of WAP protocol: WAP/HTTP */
    ven_setting_network_auth_t Auth;                 /* Connect Bearer: GPRS Auth */
    u8 ServerUrl[VEN_SETTING_MAX_LEN_LONG_SERVERURL + 1]; /* Only for WAP and MMS Profile */
    u8 ProxyIp[VEN_SETTING_IP_BYTESIZE];

    u8 GprsApn[VEN_SETTING_MAX_LEN_GPRSAPN + 1];     /* Connect Bearer: GPRS APN  */
    u8 Username[VEN_SETTING_MAX_LEN_USERNAME + 1];   /* Connect Bearer: User Name */
    u8 Password[VEN_SETTING_MAX_LEN_PASSWORD + 1];   /* Connect Bearer: Password  */
    u8 DnsIp[VEN_SETTING_IP_BYTESIZE];               /* Connect Bearer: DNS IP    */
    ven_setting_network_connectset_t tConnSet;
} ven_setting_network_profile_ex_t;


/**
 * Select SIM setting
 */
enum
{
    VEN_SETTING_SIM_MAKE_CALL = 0,
    VEN_SETTING_SIM_SEND_SMS,
    VEN_SETTING_SIM_CONNECT_MMS,
    VEN_SETTING_SIM_CONNECT_WAP,
    VEN_SETTING_SIM_CONNECT_JAVA,
    VEN_SETTING_SIM_SELECT_SIM,
    VEN_SETTING_SIM_CONNECT_EMAIL,
    VEN_SETTING_SIM_CONNECT_QQ,
    VEN_SETTING_SIM_CONNECT_VDO_STREAMING,
    VEN_SETTING_SIM_FUNCTION_SIZE,
};
typedef u8 ven_setting_sim_function_type_t;

/**
 * Current Language
 */
enum
{
    VEN_SETTING_LANG_ENG = 0,
    VEN_SETTING_LANG_CHINESE_T,
    VEN_SETTING_LANG_CHINESE_S,
    VEN_SETTING_LANG_AFAR,
    VEN_SETTING_LANG_ABKHAZIAN,
    VEN_SETTING_LANG_AVESTAN,
    VEN_SETTING_LANG_AFRIKAANS,
    VEN_SETTING_LANG_AKAN,
    VEN_SETTING_LANG_AMHARIC,
    VEN_SETTING_LANG_ARAGONESE,
    VEN_SETTING_LANG_ARABIC,
    VEN_SETTING_LANG_ASSAMESE,
    VEN_SETTING_LANG_AVARIC,
    VEN_SETTING_LANG_AYMARA,
    VEN_SETTING_LANG_AZERBAIJANI,
    VEN_SETTING_LANG_BASHKIR,
    VEN_SETTING_LANG_BELARUSIAN,
    VEN_SETTING_LANG_BULGARIAN,
    VEN_SETTING_LANG_BIHARI,
    VEN_SETTING_LANG_BISLAMA,
    VEN_SETTING_LANG_BAMBARA,
    VEN_SETTING_LANG_BENGALI,
    VEN_SETTING_LANG_TIBETAN,
    VEN_SETTING_LANG_BRETON,
    VEN_SETTING_LANG_BOSNIAN,
    VEN_SETTING_LANG_CATALAN,
    VEN_SETTING_LANG_CHECHEN,
    VEN_SETTING_LANG_CHAMORRO,
    VEN_SETTING_LANG_CORSICAN,
    VEN_SETTING_LANG_CREE,
    VEN_SETTING_LANG_CZECH,
    VEN_SETTING_LANG_CHURCH_SLAVIC,
    VEN_SETTING_LANG_CHUVASH,
    VEN_SETTING_LANG_WELSH,
    VEN_SETTING_LANG_DANISH,
    VEN_SETTING_LANG_GERMAN,
    VEN_SETTING_LANG_DIVEHI,
    VEN_SETTING_LANG_DZONGKHA,
    VEN_SETTING_LANG_EWE,
    VEN_SETTING_LANG_GREEK,
    VEN_SETTING_LANG_ESPERANTO,
    VEN_SETTING_LANG_SPANISH,
    VEN_SETTING_LANG_ESTONIAN,
    VEN_SETTING_LANG_BASQUE,
    VEN_SETTING_LANG_PERSIAN ,
    VEN_SETTING_LANG_FULAH ,
    VEN_SETTING_LANG_FINNISH ,
    VEN_SETTING_LANG_FIJIAN ,
    VEN_SETTING_LANG_FAROESE ,
    VEN_SETTING_LANG_FRENCH ,
    VEN_SETTING_LANG_WESTERN_FRISIAN ,
    VEN_SETTING_LANG_IRISH ,
    VEN_SETTING_LANG_SCOTTISH_GAELIC ,
    VEN_SETTING_LANG_GALICIAN ,
    VEN_SETTING_LANG_GUARANI ,
    VEN_SETTING_LANG_GUJARATI ,
    VEN_SETTING_LANG_MANX ,
    VEN_SETTING_LANG_HAUSA ,
    VEN_SETTING_LANG_HEBREW ,
    VEN_SETTING_LANG_HINDI ,
    VEN_SETTING_LANG_HIRI_MOTU ,
    VEN_SETTING_LANG_CROATIAN ,
    VEN_SETTING_LANG_HAITIAN ,
    VEN_SETTING_LANG_HUNGARIAN ,
    VEN_SETTING_LANG_ARMENIAN ,
    VEN_SETTING_LANG_HERERO ,
    VEN_SETTING_LANG_INTERLINGUA ,
    VEN_SETTING_LANG_INDONESIAN ,
    VEN_SETTING_LANG_INTERLINGUE,
    VEN_SETTING_LANG_IGBO ,
    VEN_SETTING_LANG_SICHUAN_YI ,
    VEN_SETTING_LANG_INUPIAQ ,
    VEN_SETTING_LANG_IDO ,
    VEN_SETTING_LANG_ICELANDIC ,
    VEN_SETTING_LANG_ITALIAN ,
    VEN_SETTING_LANG_INUKTITUT ,
    VEN_SETTING_LANG_JAPANESE ,
    VEN_SETTING_LANG_JAVANESE ,
    VEN_SETTING_LANG_GEORGIAN ,
    VEN_SETTING_LANG_KONGO ,
    VEN_SETTING_LANG_KIKUYU ,
    VEN_SETTING_LANG_KWANYAMA ,
    VEN_SETTING_LANG_KAZAKH ,
    VEN_SETTING_LANG_KALAALLISUT ,
    VEN_SETTING_LANG_KHMER ,
    VEN_SETTING_LANG_KANNADA ,
    VEN_SETTING_LANG_KOREAN ,
    VEN_SETTING_LANG_KANURI ,
    VEN_SETTING_LANG_KASHMIRI ,
    VEN_SETTING_LANG_KURDISH ,
    VEN_SETTING_LANG_KOMI ,
    VEN_SETTING_LANG_CORNISH ,
    VEN_SETTING_LANG_KIRGHIZ ,
    VEN_SETTING_LANG_LATIN ,
    VEN_SETTING_LANG_LUXEMBOURGISH ,
    VEN_SETTING_LANG_GANDA ,
    VEN_SETTING_LANG_LIMBURGISH ,
    VEN_SETTING_LANG_LINGALA ,
    VEN_SETTING_LANG_LAO ,
    VEN_SETTING_LANG_LITHUANIAN ,
    VEN_SETTING_LANG_LUBA_KATANGA ,
    VEN_SETTING_LANG_LATVIAN ,
    VEN_SETTING_LANG_MALAGASY ,
    VEN_SETTING_LANG_MARSHALLESE ,
    VEN_SETTING_LANG_MAORI ,
    VEN_SETTING_LANG_MACEDONIAN ,
    VEN_SETTING_LANG_MALAYALAM ,
    VEN_SETTING_LANG_MONGOLIAN ,
    VEN_SETTING_LANG_MOLDAVIAN ,
    VEN_SETTING_LANG_MARATHI ,
    VEN_SETTING_LANG_MALAY ,
    VEN_SETTING_LANG_MALTESE ,
    VEN_SETTING_LANG_BURMESE ,
    VEN_SETTING_LANG_NAURU ,
    VEN_SETTING_LANG_NORWEGIAN_BOKMAL ,
    VEN_SETTING_LANG_NORTH_NDEBELE ,
    VEN_SETTING_LANG_NEPALI ,
    VEN_SETTING_LANG_NDONGA ,
    VEN_SETTING_LANG_DUTCH ,
    VEN_SETTING_LANG_NORWEGIAN_NYNORSK ,
    VEN_SETTING_LANG_NORWEGIAN ,
    VEN_SETTING_LANG_SOUTH_NDEBELE ,
    VEN_SETTING_LANG_NAVAJO ,
    VEN_SETTING_LANG_CHICHEWA ,
    VEN_SETTING_LANG_OCCITAN ,
    VEN_SETTING_LANG_OJIBWA ,
    VEN_SETTING_LANG_OROMO ,
    VEN_SETTING_LANG_ORIYA ,
    VEN_SETTING_LANG_OSSETIAN ,
    VEN_SETTING_LANG_PANJABI ,	//PUNJABI
    VEN_SETTING_LANG_PALI ,
    VEN_SETTING_LANG_POLISH ,
    VEN_SETTING_LANG_PASHTO ,
    VEN_SETTING_LANG_PORTUGUESE ,
    VEN_SETTING_LANG_QUECHUA ,
    VEN_SETTING_LANG_RAETO_ROMANCE ,
    VEN_SETTING_LANG_KIRUNDI ,
    VEN_SETTING_LANG_ROMANIAN ,
    VEN_SETTING_LANG_RUSSIAN ,
    VEN_SETTING_LANG_KINYARWANDA ,
    VEN_SETTING_LANG_RUSYN ,
    VEN_SETTING_LANG_SANSKRIT ,
    VEN_SETTING_LANG_SARDINIAN ,
    VEN_SETTING_LANG_SINDHI ,
    VEN_SETTING_LANG_NORTHERN_SAMI ,
    VEN_SETTING_LANG_SANGO,
    VEN_SETTING_LANG_SERBO_CROATIAN ,
    VEN_SETTING_LANG_SINHALESE ,
    VEN_SETTING_LANG_SLOVAK ,
    VEN_SETTING_LANG_SLOVENIAN ,
    VEN_SETTING_LANG_SAMOAN ,
    VEN_SETTING_LANG_SHONA ,
    VEN_SETTING_LANG_SOMALI ,
    VEN_SETTING_LANG_ALBANIAN ,
    VEN_SETTING_LANG_SERBIAN ,
    VEN_SETTING_LANG_SWATI ,
    VEN_SETTING_LANG_SOTHO ,
    VEN_SETTING_LANG_SUNDANESE ,
    VEN_SETTING_LANG_SWEDISH ,
    VEN_SETTING_LANG_SWAHILI ,
    VEN_SETTING_LANG_TAMIL ,
    VEN_SETTING_LANG_TELUGU ,
    VEN_SETTING_LANG_TAJIK ,
    VEN_SETTING_LANG_THAI ,
    VEN_SETTING_LANG_TIGRINYA ,
    VEN_SETTING_LANG_TURKMEN ,
    VEN_SETTING_LANG_TAGALOG ,
    VEN_SETTING_LANG_TSWANA ,
    VEN_SETTING_LANG_TONGA ,
    VEN_SETTING_LANG_TURKISH ,
    VEN_SETTING_LANG_TSONGA ,
    VEN_SETTING_LANG_TATAR ,
    VEN_SETTING_LANG_TWI ,
    VEN_SETTING_LANG_TAHITIAN ,
    VEN_SETTING_LANG_UIGHUR ,
    VEN_SETTING_LANG_UKRAINIAN ,
    VEN_SETTING_LANG_URDU ,
    VEN_SETTING_LANG_UZBEK ,
    VEN_SETTING_LANG_VENDA ,
    VEN_SETTING_LANG_VIETNAMESE ,
    VEN_SETTING_LANG_VOLAPUK ,
    VEN_SETTING_LANG_WALLOON ,
    VEN_SETTING_LANG_WOLOF ,
    VEN_SETTING_LANG_XHOSA ,
    VEN_SETTING_LANG_YIDDISH ,
    VEN_SETTING_LANG_YORUBA ,
    VEN_SETTING_LANG_ZHUANG ,
    VEN_SETTING_LANG_ZULU,
	VEN_SETTING_LANG_UYGHUR,
	VEN_SETTING_LANG_HINGLISH,    
    VEN_SETTING_LANG_OTHERS=0xff,
};
typedef u8 ven_setting_lang_t;

/**
 * Get SIM ICC ID
 */

#define ICCID_LEN   20
typedef struct
{
    u8 IccID[(ICCID_LEN + 1)];  /* ICC ID (in ASCII) */
} ven_setting_SIMIccID_t;

typedef struct
{
    u16 AccName[(VEN_SETTING_MAX_LEN_PRFNAME + 1)];  /* account name (in UCS2) */
    ven_setting_network_auth_t Auth;                 /* Connect Bearer: GPRS Auth */
    u8 GprsApn[VEN_SETTING_MAX_LEN_GPRSAPN + 1];     /* Connect Bearer: GPRS APN  */
    u8 Username[VEN_SETTING_MAX_LEN_USERNAME + 1];   /* Connect Bearer: User Name */
    u8 Password[VEN_SETTING_MAX_LEN_PASSWORD + 1];   /* Connect Bearer: Password  */
    u8 DnsIp[VEN_SETTING_IP_BYTESIZE];               /* Connect Bearer: DNS IP    */
} ven_setting_data_account_t;

typedef enum
{
	VEN_SETTING_SIM_CARD_UNKNOW	= 0,				//Not receive SIM indication yet.
	VEN_SETTING_SIM_CARD_NOSIM,					//no SIM inserted for both single mode and DUO mode.
	VEN_SETTING_SIM_CARD_SINGLE,					//SIM inserted and activated for single SIM mode.
	VEN_SETTING_SIM_CARD_SINGLE_INACTIVE,				//SIM inserted and inactivated for single SIM mode.
	VEN_SETTING_SIM_CARD_SINGLE_MASTER,			//Master SIM inserted and activated for DUO mode. Slave SIM is not inserted.
	VEN_SETTING_SIM_CARD_SINGLE_MASTER_INACTIVE,		//Master SIM inserted and inactivated for DUO mode. Slave SIM is not inserted.
	VEN_SETTING_SIM_CARD_SINGLE_SLAVE,			//Slave SIM inserted and activated for DUO mode. Master SIM is not inserted.
	VEN_SETTING_SIM_CARD_SINGLE_SLAVE_INACTIVE,			//Slave SIM inserted and inactivated for DUO mode. Master SIM is not inserted.
	VEN_SETTING_SIM_CARD_DUAL_MASTER,			//Master SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
	VEN_SETTING_SIM_CARD_DUAL_SLAVE,				//Slave SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
	VEN_SETTING_SIM_CARD_DUAL_BOTH_ACTIVE,		//Both Master and Slave SIM are inserted and activated for DUO mode.
	VEN_SETTING_SIM_CARD_DUAL_BOTH_INACTIVE	//Both Master and Slave SIM are inserted and inactivated for DUO mode.
}ven_setting_sim_status_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

ven_setting_ret_t ven_setting_getProfileFileURL(ven_setting_file_type_t type, u16 **ppURLStr, u16 *pStrLen, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t RetCode;
    ven_setting_file_type_t type;
    u16 *pURLStr;
    u16 nStrLen;
} ven_setting_getProfileFileURL_rsp_t;

ven_setting_ret_t ven_setting_getProfileFileDisplayName(ven_setting_file_type_t type, u16 **ppDispName, u16 *pStrLen, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_file_type_t type;
    u16 *pDispName;
    u16 nStrLen;
} ven_setting_getProfileFileDisplayName_rsp_t;

ven_setting_ret_t ven_setting_setProfileFileURL(ven_setting_file_type_t type, u16 *pURL, u16 nURLStrLen, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_file_type_t type;
} ven_setting_setProfileFileURL_rsp_t;

ven_setting_ret_t ven_setting_getProfileVibration(ven_setting_profile_vibration_type_t type, ven_setting_profile_vibration_value_t *pValue, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_profile_vibration_type_t type;
    ven_setting_profile_vibration_value_t value;
} ven_setting_getProfileVibration_rsp_t;

ven_setting_ret_t ven_setting_getProfileVolume(ven_setting_profile_volume_type_t type, u8 *pValue, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_profile_volume_type_t type;
    u8 value;
} ven_setting_getProfileVolume_rsp_t;

ven_setting_ret_t ven_setting_getProfileKeypadTone(ven_setting_profile_keypad_tone_value_t *pValue, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_profile_keypad_tone_value_t nValue;
} ven_setting_getProfileKeypadTone_rsp_t;

ven_setting_ret_t ven_setting_getNetworkProfile(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID, ven_setting_network_profile_t *pProfile, ven_req_data_t *ptVenReq);
ven_setting_ret_t ven_setting_getNetworkProfileEx(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID, ven_setting_network_profile_ex_t *pProfile, ven_req_data_t *ptVenReq);


/**
 *  ven_setting_getNetworkProfileNum
 *
 *  @brief  This function gets the number of available network profile
 *
 *  @param  type[in]Network profile type
 *  @param  pProfileNum[out]Number of available network profile
 *  @param  ptVenReq[in]Pointer to request data
 *
 *  @retval VEN_SETTING_RET_SUCCESS      success
 *  @retval others failed
 */
ven_setting_ret_t ven_setting_getNetworkProfileNum(ven_setting_network_profile_type_t type, u8 *pProfileNum, ven_req_data_t *ptVenReq);

/**
 *  ven_setting_getNetworkProfileByIdx
 *
 *  @brief  This function gets the network profile with the given index
 *
 *  @param  type[in]Network profile type
 *  @param  nIdx[in]Index of the profile (start from 0)
 *  @param  pProfile[out]Network profile of the given index
 *  @param  ptVenReq[in]Pointer to request data
 *
 *  @retval VEN_SETTING_RET_SUCCESS      success
 *  @retval others failed
 */
ven_setting_ret_t ven_setting_getNetworkProfileByIdx(ven_setting_network_profile_type_t type, u8 nIdx, ven_setting_network_profile_t *pProfile, ven_req_data_t *ptVenReq);

typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_network_profile_type_t type;
    ven_common_sim_id_t SimID;
    ven_setting_network_profile_t *pProfile;
} ven_setting_getNetworkProfile_rsp_t;

typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_network_profile_type_t type;
    ven_common_sim_id_t SimID;
    ven_setting_network_profile_ex_t *pProfile;
} ven_setting_getNetworkProfile_ex_rsp_t;


ven_setting_ret_t ven_setting_setNetworkProfile(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID, ven_setting_network_profile_t *pProfile, ven_req_data_t *ptVenReq);
ven_setting_ret_t ven_setting_setNetworkProfileEx(ven_setting_network_profile_type_t type, ven_common_sim_id_t SimID, ven_setting_network_profile_ex_t *pProfile, ven_req_data_t *ptVenReq);

typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_network_profile_type_t type;
    ven_common_sim_id_t SimID;
} ven_setting_setNetworkProfile_rsp_t;

ven_setting_ret_t ven_setting_getSelectSIM(ven_setting_sim_function_type_t type, ven_common_sim_id_t *pSimID, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_sim_function_type_t type;
    ven_common_sim_id_t SimID;
} ven_setting_getSelectSIM_rsp_t;

ven_setting_ret_t ven_setting_getDefaultSIM(ven_setting_sim_function_type_t type, ven_common_sim_id_t *pSimID, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_sim_function_type_t type;
    ven_common_sim_id_t SimID;
} ven_setting_getDefaultSIM_rsp_t;

ven_setting_ret_t ven_setting_getSIMIccId(ven_setting_SIMIccID_t *pIccID, ven_common_sim_id_t SimID, ven_req_data_t *ptVenReq);
/* ven_setting_getSIMIccId() API only provides Sync method, therefore need to set ptVenReq.bSync to TRUE */
typedef struct
{
    ven_setting_ret_t       RetCode;
    ven_common_sim_id_t     SimID;
    ven_setting_SIMIccID_t  *pIccID;
} ven_setting_getSIMIccId_rsp_t;

ven_setting_ret_t ven_setting_getCurrentLanguage(ven_setting_lang_t *pLang, ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_lang_t lang;
} ven_setting_getCurrentLanguage_rsp_t;

/**
 *  ven_setting_getDataAccountNum
 *
 *  @brief  This function gets the number of available data accounts
 *
 *  @param  pAccountNum[out]Number of available data account
 *  @param  ptVenReq[in]Pointer to request data
 *
 *  @retval VEN_SETTING_RET_SUCCESS      success
 *  @retval others failed
 */
ven_setting_ret_t ven_setting_getDataAccountNum(u8 *pAccountNum, ven_req_data_t *ptVenReq);

/**
 *  ven_setting_getDataAccountByIdx
 *
 *  @brief  This function gets the data account with the given index
 *
 *  @param  nIdx[in]Index of the data account (start from 0)
 *  @param  pAccount[out]Data account of the given index
 *  @param  ptVenReq[in]Pointer to request data
 *
 *  @retval VEN_SETTING_RET_SUCCESS      success
 *  @retval others failed
 */
ven_setting_ret_t ven_setting_getDataAccountByIdx(u8 nIdx, ven_setting_data_account_t *pAccount, ven_req_data_t *ptVenReq);

s8* ven_setting_getMmsWspHeader(void);

bool ven_setting_queryAirPlaneMode(ven_req_data_t *ptVenReq);

/**
 *  ven_setting_getDefaultCam
 *
 *  @brief  This function get the default camera id
 *          Note: This function supports synchronous only
 *
 *  @param  pCamID      [out] Default camera id
 *  @param  ptVenReq    [in]Pointer to request data
 *
 *  @retval VEN_SETTING_RET_SUCCESS      success
 *  @retval others failed
 */
ven_setting_ret_t ven_setting_getDefaultCam(ven_cam_id_t *pCamID, ven_req_data_t *ptVenReq);

/**
 *  ven_setting_getSIMStatus
 *
 *  @brief  Get sim status.
 *
 *  @param  eStatus         [out] Sim status
 *  @param  output_info     [in] The pointer of the request data.
 *
 *  @retval VEN_SETTING_RET_SUCCESS if success
 *          VEN_SETTING_RET_BAD_PARAM if invalid input parameters
 *          VEN_SETTING_RET_FAILED 
 *          VEN_SETTING_RET_OUT_OF_MEMORY
 */
ven_setting_ret_t ven_setting_getSIMStatus(ven_setting_sim_status_t *eStatus,ven_req_data_t *ptVenReq);
typedef struct
{
    ven_setting_ret_t  RetCode;
    ven_setting_sim_status_t eStatus;
} ven_setting_getSIMStatus_rsp_t;

#endif //__VEN_SETTING_DEFINE_H_
