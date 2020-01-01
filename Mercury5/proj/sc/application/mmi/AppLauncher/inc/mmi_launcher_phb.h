#ifndef __PHB_APP_H__
#define __PHB_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

#define PHB_NUMBER_LEN         (40)
#define PHB_NAME_LEN           (40)
#define PHB_COMPANY_LEN		   (40)
#define PHB_DEPARTMENT_LEN     (40)
#define PHB_POSITION_LEN       (40)
#define PHB_HOME_ADDRESS_LEN   (100)
#define PHB_OFFICE_ADDRESS_LEN (100)
#define PHB_EMAIL_LEN          (100)
#define PHB_RECEIVER_LEN       (100)
#define PHB_URL_LEN            (100)
#define PHB_NOTE_LEN           (100)
#define PHB_MAX_FILEPATH_SIZE   FILEMGR_MAX_FILEPATH_SIZE ///< Define maximum length of path including filename

typedef enum
{
	PHB_BOOK_TYPE_MIN               = 0,
	PHB_BOOK_TYPE_UNKNOWN			= PHB_BOOK_TYPE_MIN,
	PHB_BOOK_TYPE_ECC				= 1,
	PHB_BOOK_TYPE_ADN_M				= 2,
	PHB_BOOK_TYPE_ADN_S				= 3,
	PHB_BOOK_TYPE_ADN_M_ADN_S		= 4,
	PHB_BOOK_TYPE_FDN				= 5,
	PHB_BOOK_TYPE_BDN				= 6,
	PHB_BOOK_TYPE_LDN				= 7,
	PHB_BOOK_TYPE_LRN				= 8,
	PHB_BOOK_TYPE_LMN				= 9,
	PHB_BOOK_TYPE_LXN				= 10,
	PHB_BOOK_TYPE_SDN				= 11,
	PHB_BOOK_TYPE_MSISDN			= 12,
	PHB_BOOK_TYPE_MBX				= 13,
	PHB_BOOK_TYPE_ADR				= 14,
	PHB_BOOK_TYPE_ADR_ADN_M			= 15,
	PHB_BOOK_TYPE_ADR_ADN_S			= 16,
	PHB_BOOK_TYPE_ADR_ADN_M_ADN_S	= 17,
	PHB_BOOK_TYPE_BCARD				= 18,
	PHB_BOOK_TYPE_MAX = PHB_BOOK_TYPE_BCARD,
}PhoneBookType_e;

typedef enum
{
	PHB_GROUP_UNKNOWN	= 0,
	PHB_GROUP_CG_START,
	PHB_GROUP_CG_END	= 28,
	PHB_GROUP_BLACK_LIST,
	PHB_GROUP_URL,
	PHB_GROUP_EMAIL,
	PHB_GROUP_MAX = PHB_GROUP_BLACK_LIST,
	PHB_GROUP_INVALID,
}PhoneBookGroupType_e;

typedef struct
{
	PhoneBookType_e eType;
	PhoneBookGroupType_e eGroupType;
}PhoneBookContactDes_t;

typedef enum
{
    PHB_FIELD_MASK_NONE           = 0,
    PHB_FIELD_MASK_NAME           = 1 << 0,
    PHB_FIELD_MASK_NUMBER         = 1 << 1,
    PHB_FIELD_MASK_COMPANY        = 1 << 2,
	PHB_FIELD_MASK_DEPARTMENT     = 1 << 3,
    PHB_FIELD_MASK_POSITION       = 1 << 4,
	PHB_FIELD_MASK_HOME_ADDRESS   = 1 << 5,
	PHB_FIELD_MASK_OFFICE_ADDRESS = 1 << 6,
	PHB_FIELD_MASK_EMAIL          = 1 << 7,
    PHB_FIELD_MASK_URL            = 1 << 8,
	PHB_FIELD_MASK_NOTE           = 1 << 9,
	PHB_FIELD_MASK_IMAGE_ID       = 1 << 10,
	PHB_FIELD_MASK_RINGTONE_ID    = 1 << 11,
	PHB_FIELD_MASK_BIRTHDAY       = 1 << 12,
	PHB_FIELD_MASK_GROUP_ID       = 1 << 13,
	PHB_FIELD_MASK_RECEIVER       = 1 << 14,
 #ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    PHB_FIELD_MASK_VIDEOTONE_ID    = 1 << 15,
#endif
   PHB_FIELD_MASK_ALL            = 0XFFFF,
}PhoneBookContactFieldMask_e;

typedef enum
{
	PHB_INSTANCE_1              = 0,
	PHB_INSTANCE_2 				= 1,
}PhoneBookInstance_e;

typedef struct
{
	u8 au8Year[2+1];
	u8 au8Month[2+1];
	u8 au8Day[2+1];
	u8 au8Hour[2+1];
	u8 au8Minute[2+1];
	u8 au8Second[2+1];
}PhoneBookDateTime_t;

typedef struct
{
	MAE_WChar *wStrName;                    /// Name
	MAE_WChar *wStrNumber;/// For data exchange (Save & Select),

	MAE_WChar *wStrMobileNumber;/// MMI_PHB_NUMBER_TYPE_MOBILE = 0,
#ifndef __SMALL_PHB_MMI__	
	MAE_WChar *wStrHomeNumber;///MMI_PHB_NUMBER_TYPE_HOME = 1,
	MAE_WChar *wStrOfficeNumber;///MMI_PHB_NUMBER_TYPE_OFFICE = 2,
	MAE_WChar *wStrOtherNumber;///MMI_PHB_NUMBER_TYPE_OTHER = 3,

	MAE_WChar *wStrCompany;              /// Company
	MAE_WChar *wStrDepartment;        /// Department
	MAE_WChar *wStrPosition;            /// Position
	MAE_WChar *wStrHomeAddress;       /// HomeAddress
	MAE_WChar *wStrOfficeAddress; /// OfficeAddress
	MAE_WChar *wStrEMail;                  /// EMail
	MAE_WChar *wStrURL;               /// URL
	MAE_WChar *wStrNote;                    /// Note
#endif // #ifndef __SMALL_PHB_MMI__		
	MAE_WChar *wStrReceiver;                /// Email or Number
	MAE_WChar *wStrImagePath; ///Image Url
	MAE_WChar *wStrRingPath; ///Ring Url
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    MAE_WChar *wStrVideoPath; ///Video Url
#endif
#ifndef __SMALL_PHB_MMI__
	PhoneBookDateTime_t sBirthDay;                          /// Birthday
#endif	
	u32 uGroupId;                                           /// GroupId
}PhoneBookContactData_t;

typedef struct
{
    PhoneBookContactFieldMask_e eMask;
	//u32 uSize;
    PhoneBookContactData_t *psContact;
}PhoneBookSaveContactRecord_t;

/*
typedef struct
{
	PhoneBookType_e eType;
	PhoneBookContactFieldMask_e eMask;
	u32 uContactNum;
	PhoneBookContactData_t *psContacts;
}PhoneBookGetContactRecord_t;
*/
/* Get vCard callback */
typedef struct
{
	u32 uVCardSize;
	u8 *puVCard;
}PhoneBookGetVCardRspData_t;

typedef void (*PhoneBookGetVCardRspDataFreeCb)(PhoneBookGetVCardRspData_t *psRspData);
typedef void (*PhoneBookGetVCardRspCb)(void *pvUserData, MAE_Ret nRspCode, PhoneBookGetVCardRspData_t *psRspData, PhoneBookGetVCardRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
	PhoneBookGetVCardRspCb pfnRspCb;
}PhoneBookGetVCardRspCbInfo_t;

/* Get Contact Callback */
typedef struct
{
	//PhoneBookType_e eType;
	PhoneBookContactFieldMask_e eMask;
	u32 uContactNum;
	PhoneBookContactData_t *psContacts;
	u32 u32ContactImageId;
}PhoneBookGetContactRecord_t;

typedef void (*PhoneBookGetContactRspDataFreeCb)(PhoneBookGetContactRecord_t *psRspData);
typedef void (*PhoneBookGetContactRspCb)(void *pvUserData, MAE_Ret nRspCode, PhoneBookGetContactRecord_t *psRspData, PhoneBookGetContactRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pvUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
	PhoneBookGetContactRspCb pfnRspCb;
}PhoneBookGetContactRspCbInfo_t;


/// 1. CallLog App,      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithNumber_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER,
/// 2. Cc App,           APM_Mode = APM_LAUNCH_EMBEDDED,     param = Mode,                                           Mode = PHB_AP_FID_SELECT_CONTACT_MAKE_CALL
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithNumber_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER
/// 3. Dialer App,       APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithNumber_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidQuickDial_t,                         Mode = PHB_AP_FID_QUICK_DIAL
/// 4. File Manager App, APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithRingId_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_RING_ID
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithImageId_t,            Mode = PHB_AP_FID_SAVE_CONTACT_WITH_IMAGE_ID
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidImportWithFileArray_t,               Mode = PHB_AP_FID_IMPORT_WITH_FILES
/// 5. Pic Viewer App,   APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithImageId_t,            Mode = PHB_AP_FID_SAVE_CONTACT_WITH_IMAGE_ID
/// 6. Sea App,          APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactDetails_t,              Mode = PHB_AP_FID_SELECT_CONTACT_DETAILS
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactAsvCard_t,              Mode = PHB_AP_FID_SELECT_CONTACT_AS_VCARD
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectMultiContactsNameNumber_t,     Mode = PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectMultiContactsNameNumberEmail_t,Mode = PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER_EMAIL
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactDetails_t,              Mode = PHB_AP_FID_SELECT_CONTACT_DETAILS
/// 7. Search App,       APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidShowContactDetails_t,                Mode = PHB_AP_FID_SHOW_CONTACT_DETAILS
/// 8. Shortcut App,     APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactNameNumber_t,           Mode = PHB_AP_FID_SELECT_CONTACT_NAME_NUMBER
/// 9. Sva App,          APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithNumber_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithEmail_t,              Mode = PHB_AP_FID_SAVE_CONTACT_WITH_EMAIL
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithvCard_t,              Mode = PHB_AP_FID_SAVE_CONTACT_WITH_VCARD
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSaveContactWithvCard_t,              Mode = PHB_AP_FID_SAVE_CONTACT_WITH_VCARD
///10. Vendor App,       APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectMultiContactsNameNumber_t,     Mode = PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactNameNumber_t,           Mode = PHB_AP_FID_SELECT_CONTACT_NAME_NUMBER
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectMultiContactsEmail_t,          Mode = PHB_AP_FID_SELECT_MULTI_CONTACTS_EMAIL
///                      APM_Mode = APM_LAUNCH_EMBEDDED,     param = MmiPhbApFidSelectContactEmail_t,                Mode = PHB_AP_FID_SELECT_CONTACT_EMAIL
///11. Shortcut Srv,     APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = MmiPhbApFidSaveContactWithNumber_t,             Mode = PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER
///                      APM_Mode = APM_LAUNCH_INTERRUPTIVE, param = NULL,                                           Mode = NULL

void LaunchPhoneBookApp
(
  AppLaunchMode_e eAppLaunchMode,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#ifdef __APP_MMI_GROUP_APP__
void LaunchPhoneBookAppWithGroup
( 
	AppLaunchMode_e eAppLaunchMode,
	LaunchAppTransParam_t *psTransParam,
	CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif

void LaunchPhoneBookAppToMakeCall
(
  AppLaunchMode_e eAppLaunchMode,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#ifdef __SPEED_DIALER_MMI__
void LaunchPhoneBookAppToMakeQuickDailCall
(
  AppLaunchMode_e eAppLaunchMode,
  u16 uQuickDialNum,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif //#ifdef __SPEED_DIALER_MMI__

void LaunchPhoneBookAppToSaveContact
(
  AppLaunchMode_e eAppLaunchMode,
  PhoneBookSaveContactRecord_t *psSaveContacts,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__ 

void LaunchPhoneBookAppToSaveContactByVCard
(
  AppLaunchMode_e eAppLaunchMode,
  u8 *puVCard,
  u32 uSize,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__ 

void LaunchPhoneBookAppToGetContacts
(
  AppLaunchMode_e eAppLaunchMode,
  PhoneBookType_e ePhbType,
  PhoneBookContactFieldMask_e eMask,
  u32 uMaxContactNum,
   LaunchAppTransParam_t *psTransParam,
  PhoneBookGetContactRspCbInfo_t *psRspCbInfo
);

void LaunchPhoneBookAppToGetMultiContacts
(
  AppLaunchMode_e eAppLaunchMode,
  PhoneBookType_e ePhbType,
  PhoneBookContactFieldMask_e eMask,
  u32 uMaxContactNum,
   LaunchAppTransParam_t *psTransParam,
  PhoneBookGetContactRspCbInfo_t *psRspCbInfo,
  boolean	bIsForceMulti	/* TRUE means menu type will set to multi selection, even the uMaxContactNum is 1. */
);

void  LaunchPhoneBookAppToGetContactsNumberOrEmail(
	AppLaunchMode_e eAppLaunchMode,
	PhoneBookType_e ePhbType,
	u32 uMaxRetNum,
	 LaunchAppTransParam_t *psTransParam,
	PhoneBookGetContactRspCbInfo_t *psRspCbInfo
);

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__ 

void LaunchPhoneBookAppToGetContactAsVCard
(
  AppLaunchMode_e eAppLaunchMode,
  PhoneBookType_e ePhbType,
   LaunchAppTransParam_t *psTransParam,
  PhoneBookGetVCardRspCbInfo_t *psRspCbInfo
);

void LaunchPhoneBookAppToImportContactByFileMarkListHandle
(
  AppLaunchMode_e eAppLaunchMode,
  u32 uHandleID,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__ 
void LaunchPhoneBookAppToViewContact
(
  AppLaunchMode_e eAppLaunchMode,
  u16 uContactId,
   LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif
