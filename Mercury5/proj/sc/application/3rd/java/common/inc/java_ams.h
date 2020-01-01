#ifndef __NCC_3RD_JAVA_PORTING_LAYER__
#ifndef __JAVA_AMS_DEFINE_H__

#define __JAVA_AMS_DEFINE_H__

#include "ven_std.h"


#ifdef  __SDK_SIMULATION__
// Java Delta is not supported in simulator
#if defined(__JAVA_DELTA__) && !defined(__DALVIK__) // dalvik is using Java delta option right now
#undef __JAVA__
#undef __JAVA_MMI__
#undef __JAVA_DELTA__
#endif /* defined(__JAVA_DELTA__) */

#endif /* __SDK_SIMULATION__ */


enum

{

    JAVA_INSTALL_NAND = 0,

    JAVA_INSTALL_NOR,

    JAVA_INSTALL_MEMCARD,

    JAVA_INSTALL_MEMCARD2,
    JAVA_INSTALL_PREINSTALL,
};

typedef u8 java_install_storage_e;


typedef struct _java_install_param_struct

{

	u16 *jadPath;

	u16 *jarPath;

	java_install_storage_e storage;

	int KeepRMS;

	s32 oldId;

} java_install_param_struct;


typedef struct _java_icon_struct_t

{

    u32 icon_size;

    u32 icon_width;

    u32 icon_height;

    u8 *icon_data;

} java_icon_struct;


typedef struct _java_midlet_struct_t

{

    u16 *midlet_name;

    java_icon_struct *icon_data;

} java_midlet_struct;


typedef struct _java_suite_struct_t

{

    u16 *suite_name; /* MIDletSuite Name */

    u16 *jad_url;

    u16 *jar_url; /*MIDlet-JAR-URL */

    u16 *website;

    java_icon_struct suite_icon; /* MIDletSuite Icon */

    s32 suite_size; /* MIDlet-JAR-Size */

    u16 *suite_version; /* MIDlet-Version */

    u16 *suite_vendor; /* MIDlet-Vendor */

    u16 *suite_description; /* MIDlet-Description */

    u8 suite_authorized;

    u16 *suite_authorized_by;

    u16 *suite_auto_start; /* MIDlet-Push-X */

	u8  is_preinstall;               //  add for checking preinstall,  1 is preinstall, 0 is postinstall.

	java_install_storage_e storage; // The suite is installed on NAND or memory card

} java_suite_struct;


typedef struct _java_suite_struct_list_t

{

    struct _java_suite_struct *java_suite_struct;  //detail

    struct _java_suite_struct_list_t *java_suite_next;  //pointer to next java_suite_struct_list


} java_suite_struct_list;

#if !defined(__DALVIK__)
static java_suite_struct_list *all_suite_list;
#endif



// for permission


typedef struct _java_permission_setting_t

{

    u8 permission_network; /* Network Access */

    u8 permission_multimedia; /* Multimedia Recording */

    u8 permission_messaging; /* Wireless Messaging */

    u8 permission_autostart; /* Application Auto Invocation */

    u8 permission_localconnect; /* Local Connectivity */

    u8 permission_dataread; /* User Data Read */

    u8 permission_datawrite; /* User Data Write */

} java_permission_setting;


#define JAVA_PERMISSION_NEVER  0x00

#define JAVA_PERMISSION_ALLOW  0x01

#define JAVA_PERMISSION_BLANKET_GRANTED  0x02

#define JAVA_PERMISSION_BLANKET  0x04

#define JAVA_PERMISSION_SESSION  0x08

#define JAVA_PERMISSION_ONE_SHOT  0x10

#define JAVA_PERMISSION_DENY_SESSION  0x20

#define JAVA_PERMISSION_DENY  0x40

#define JAVA_PERMISSION_USER_DENIED  0x80


//=====================================================

#define JAVA_RET_OK                     (0)

#define JAVA_RET_FAIL                   (-1)

#define JAVA_RET_FAIL_AMSLIST_FULL      (-2)

#define JAVA_RET_FAIL_LARGE_JAR         (-3)

#define JAVA_RET_FAIL_NO_ENOUGH_SPACE   (-4) // No enough space for AMS operation

#define JAVA_RET_FAIL_STORAGE_ERROR     (-5) // Operation failed due to storage failure

#define JAVA_RET_FAIL_OUT_OF_MEMORY     (-6) // Out Of Memory

#define JAVA_RET_FAIL_REINIT_BUSY            (-7) //



// result definition for java_ams_installProgressCB()

#define JAVA_INSTALL_OK   (900)

#define JAVA_ERR_INSTALL_NO_ENOUGH_SPACE   (901)

#define JAVA_ERR_INSTALL_USER_CANCEL   (902)

#define JAVA_ERR_INSTALL_LOSS_OF_SERVICE   (903)

#define JAVA_ERR_INSTALL_JAR_SIZE_MISMATCH   (904)

#define JAVA_ERR_INSTALL_ATTRIBUTE_MISMATCH   (905)

#define JAVA_ERR_INSTALL_INVALID_JAD   (906)

#define JAVA_ERR_INSTALL_INVALID_JAR   (907)

#define JAVA_ERR_INSTALL_CLDC_MIDP_VERSION   (908)

#define JAVA_ERR_INSTALL_AUTHENTICATION_FAILURE   (909)

#define JAVA_ERR_INSTALL_AUTHORIZATION_FAILURE   (910)

#define JAVA_ERR_INSTALL_PUSH_REGISTRATION_FALIURE   (911)

#define JAVA_ERR_INSTALL_DELETION_NOTIFICATION   (912)

#define JAVA_ERR_INSTALL_NO_ENOUGH_SPACE_PHONE   (913)

#define JAVA_ERR_INSTALL_NO_ENOUGH_SPACE_CARD   (914)

//PR154243
#define JAVA_ERR_INSTALL_STEP_0_FAIL   (790)

#define JAVA_ERR_INSTALL_NOT_DEFINE   (999)


typedef enum

{

	Java_Launch_Normal = 0,

	Java_Launch_Alarm,

	Java_Launch_Port

}Java_Launch_Cause_e;





typedef struct _java_LaunchCause

{

    Java_Launch_Cause_e    launch_cause;

    u32    msgId;

    int 	port;

} java_LanuchCause;




//=====================================================

int java_ams_initial_req(void);

int java_ams_initial_rsp(int retCode);


int java_ams_release_req(void);

int java_ams_release_rsp(int retCode);

//========================

//layer 1

//========================

int java_ams_getSuiteCount_req(void);

int java_ams_getSuiteCount_rsp(int retCode, int suiteCount);

//ARRAY include suite detail information

// and midlet count, suite icon

int java_ams_getSuiteInfo_req(int index);

int java_ams_getSuiteInfo_rsp(int retCode, int index,java_suite_struct *ret);


int java_ams_removeSuite_req(int index);

int java_ams_removeSuite_rsp(int retCode, int index);


int java_ams_getPermission_req(int index);

int java_ams_getPermission_rsp(int retCode, int index, java_permission_setting *ps);


int java_ams_setPermission_req(int index, java_permission_setting *ps);

int java_ams_setPermission_rsp(int retCode, int index, java_permission_setting *ps);


//========================

//layer 2

//========================

int java_ams_getMidletCount_req(int suite_index);

int java_ams_getMidletCount_rsp(int retCode, int suite_index, int midletCount);

// midlet name, midlet icon

int java_ams_getMidletInfo_req(int  suite_index,int midlet_index);

int java_ams_getMidletInfo_rsp(int retCode, int  suite_index,int midlet_index, java_midlet_struct *ret);


int java_ams_launchMidlet_req(int suite_index,int midlet_index, java_LanuchCause cause);

int java_ams_launchMidlet_rsp(int retCode, int suite_index,int midlet_index);


//========================

//Local Install by mmi

//========================

typedef struct _java_CheckResult

{

    s32    otaCode; // check ota code in AJMS_CheckResult

    s32    update;

    s32    trusted; // 0 means untrusted, 1 means trusted

    s32    oldId;   // must pass to Aplix install function

} java_CheckResult;


typedef struct _java_InstallResult

{

    s32    otaCode; // check ota code in AJMS_CheckResult

    s32    suiteIndex;

} java_InstallResult;




#define JAVA_UPDATE_MIDLET_SUITE_NOT_EXIST   (1)

#define JAVA_UPDATE_NOT_ALLOW                         	(2)

#define JAVA_UPDATE_NEWER_VERSION            		(3)

#define JAVA_UPDATE_SAME_VERSION             		(4)

#define JAVA_UPDTAE_OLDER_VERSION            		(5)




typedef int(* java_ams_InstallCheckCB)(int total, int step, java_CheckResult Result);

#ifdef __JAVA_OAKMONT__
int java_ams_checkMidletSuite_req(u16 *jadPath, u16 *jarPath, u8 nStorage, java_ams_InstallCheckCB cb);
#else
int java_ams_checkMidletSuite_req(u16 *jadPath, u16 *jarPath, java_ams_InstallCheckCB cb);
#endif
int java_ams_checkMidletSuite_rsp(int retCode);


typedef int(* java_ams_installProgressCB)(int total, int step, java_InstallResult Result);


int java_ams_installMidletSuite_req(java_install_param_struct *pInstallParam, java_ams_installProgressCB cb);


#ifdef __JAVA_OAKMONT__

int java_ams_installMidletSuite_rsp(int retCode);

#else

int java_ams_installMidletSuite_rsp(int retCode,int installSuiteId);

#endif




int java_ams_cancelinstallSuite_req(void);

int java_ams_cancelinstallSuite_rsp(void);


int jams_installProgressCB(int total, int step, java_InstallResult Result);

int jams_installCheckCB(int total, int step, java_CheckResult Result);


//========================

//Local Install by kvm

//========================

#define INFOKEY(key) ((key)<<24)

#define LEFTKEY(key) ((key)<<16)

#define MIDKEY(key) ((key) << 8)

#define RIGHTKEY(key) (key)


#define GET_INFOKEY(key)  (((key) >> 24) & 0xff)

#define GET_LEFTKEY(key)  (((key) >> 16) & 0xff)

#define GET_MIDKEY(key)  (((key) >> 8 ) & 0xff)

#define GET_RIGHTKEY(key) (((key) & 0xff))




#define AMS_KEY_OK 1

#define AMS_KEY_CANCEL 2

#define AMS_KEY_SELECT 3

#define AMS_KEY_YES 4

#define AMS_KEY_NO 5

#define AMS_KEY_DONE 6


// This info comes with user selected key from java_ams_set_show_progress_rsp() and java_ams_draw_install_dialog_sync()

// Currently used with AMS_KEY_CANCEL for cancel reason.

#define AMS_INFO_NONE 0 // Nonthing special

#define AMS_INFO_MEM_CARD_LOST 1 // External memory card is lost.


int java_ams_set_show_progress_req(int percent,u32 softkey);

int java_ams_set_show_progress_rsp(u32 *selected_key);

int java_ams_draw_install_dialog_sync(int jamMsgID, u16* Msg,u32 softkey, u32 *selected_key);





typedef enum

{

	Java_J2ME_INSTALL_NO_ERROR = 0,

	Java_J2ME_INSTALL_JAD_NOT_FOUND = 2,

	Java_J2ME_INSTALL_MISSING_PROVIDER_CERT = 4,

	Java_J2ME_INSTALL_CORRUPT_PROVIDER_CERT = 5,

	Java_J2ME_INSTALL_UNKNOWN_CA = 6,

	Java_J2ME_INSTALL_INVALID_PROVIDER_CERT = 7,

	Java_J2ME_INSTALL_CORRUPT_SIGNATURE = 8,

	Java_J2ME_INSTALL_INVALID_SIGNATURE = 9,

	Java_J2ME_INSTALL_UNSUPPORTED_CERT = 10,

	Java_J2ME_INSTALL_EXPIRED_PROVIDER_CERT = 11,

	Java_J2ME_INSTALL_EXPIRED_CA_KEY = 12,

	Java_J2ME_INSTALL_MISSING_SUITE_NAME = 13,

	Java_J2ME_INSTALL_MISSING_VENDOR = 14,

	Java_J2ME_INSTALL_MISSING_VERSION = 15,

	Java_J2ME_INSTALL_INVALID_VERSION = 16,

	Java_J2ME_INSTALL_OLD_VERSION = 17,

	Java_J2ME_INSTALL_MISSING_JAR_URL = 18,

	Java_J2ME_INSTALL_JAR_NOT_FOUND = 20,

	Java_J2ME_INSTALL_MISSING_JAR_SIZE = 21,

	Java_J2ME_INSTALL_SUITE_NAME_MISMATCH = 25,

	Java_J2ME_INSTALL_VERSION_MISMATCH = 26,

	Java_J2ME_INSTALL_VENDOR_MISMATCH = 27,

	Java_J2ME_INSTALL_INVALID_KEY = 28,

	Java_J2ME_INSTALL_INVALID_VALUE = 29,

	Java_J2ME_INSTALL_INSUFFICIENT_STORAGE = 30,

	Java_J2ME_INSTALL_JAR_SIZE_MISMATCH = 31,

	Java_J2ME_INSTALL_NEW_VERSION = 32,

	Java_J2ME_INSTALL_JAD_MOVED = 34,

	Java_J2ME_INSTALL_CORRUPT_JAR = 36,

	Java_J2ME_INSTALL_ALREADY_INSTALLED = 39,

	Java_J2ME_INSTALL_DEVICE_INCOMPATIBLE = 40,

	Java_J2ME_INSTALL_MISSING_CONFIGURATION = 41,

	Java_J2ME_INSTALL_MISSING_PROFILE = 42,

	Java_J2ME_INSTALL_INVALID_JAD_URL = 43,

	Java_J2ME_INSTALL_INVALID_JAR_URL = 44,

	Java_J2ME_INSTALL_PUSH_DUP_FAILURE = 45,

	Java_J2ME_INSTALL_PUSH_FORMAT_FAILURE = 46,

	Java_J2ME_INSTALL_PUSH_PROTO_FAILURE = 47,

	Java_J2ME_INSTALL_PUSH_CLASS_FAILURE = 48,

	Java_J2ME_INSTALL_AUTHORIZATION_FAILURE = 49,

	Java_J2ME_INSTALL_ATTRIBUTE_MISMATCH = 50,

	Java_J2ME_INSTALL_TRUSTED_OVERWRITE_FAILURE = 52,

	Java_J2ME_INSTALL_DEFAULT_GAME = 60,

	Java_J2ME_INSTALL_DISK_OPERATION_FAIL = 80,

    Java_J2ME_INSTALL_PATH_NOT_FOUND_WHEN_UPDATE = 81,

	Java_J2ME_INSTALL_USER_CANCEL = 90,

	Java_J2ME_INSTALL_PUSH_INSTALL = 91,

	Java_J2ME_INSTALL_NORMAL_INSTALL = 92,

	Java_J2ME_INSTALL_INSTALL_NA = 93,

	Java_J2ME_INSTALL_OVER_MAX_INSTALL = 94,

	Java_J2ME_INSTALL_DRM_PROHIBIT = 95,

	Java_J2ME_INSTALL_POST_ERROR = 100,

	Java_J2ME_INSTALL_MEMORY_ALLACTION_FAILURE = 101,

	Java_J2ME_INSTALL_MIDLET_RUNNING = 206,

	Java_J2ME_INSTALL_KEEP_RMS = 207,

	Java_J2ME_INSTALL_DELETE_SUITE = 208,

	Java_J2ME_INSTALL_UNKOWN_FAILUIRE = 999,

	Java_J2ME_INSTALL_OK = 0, // Delta project use Java_J2ME_INSTALL_NO_ERROR

	Java_J2ME_INSTALL_LAUNCH = 8193,

	Java_J2ME_INSTALL_CUSTOM_STRING_CONFIRM=8194, //we need some custom string to show in nemomp_jam_install_user_confirm function

	Java_J2ME_INSTALL_PUSH_AND_NORMAL_INSTALL=8195,

	Java_J2ME_INSTALL_PUSH_AND_ALREADY_INSTALLEDL=8196,

    Java_J2ME_INSTALL_PUSH_AND_INSTALL_OLD_VERSION=8197,

    Java_J2ME_INSTALL_PUSH_AND_INSTALL_NEW_VERSION=8198,


    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_NAND = 8199,

    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_SD = 8200,

    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_LARGE_MIDLET = 8201,

    Java_J2ME_INSTALL_NEED_JAD_FILE = 8202,

    Java_J2ME_INSTALL_NOT_DEX_FILE = 8203,

} install_error_code_enum;







/*

* JAM Message ID and the Message content (suggestion)

J2ME_INSTALL_JAD_NOT_FOUND:Install failure

J2ME_INSTALL_MISSING_PROVIDER_CERT:Certificate chain is missing in JAD

J2ME_INSTALL_CORRUPT_PROVIDER_CERT:JAD certificate is corrupt

J2ME_INSTALL_UNKNOWN_CA:Jad certificate is unknown

J2ME_INSTALL_INVALID_PROVIDER_CERT:JAD certificate is invalid

J2ME_INSTALL_CORRUPT_SIGNATURE:JAR signature is corrupt

J2ME_INSTALL_INVALID_SIGNATURE:JAR signature is invalid

J2ME_INSTALL_UNSUPPORTED_CERT:JAD certificate is unsupported

J2ME_INSTALL_EXPIRED_PROVIDER_CERT:JAD certificate is expired.

J2ME_INSTALL_EXPIRED_CA_KEY:JAD certificate's public key has expired.

J2ME_INSTALL_MISSING_SUITE_NAME:The suite name is missing

J2ME_INSTALL_MISSING_VENDOR:The vender name is missing

J2ME_INSTALL_MISSING_VERSION:The version is missing

J2ME_INSTALL_INVALID_VERSION:The version is invalid

J2ME_INSTALL_OLD_VERSION:An older version of %1 is already installed.\nWould you like to update anyway?\nCurrently installed: %5\nVersion found:%3\nVendor: %2\nWebsite: %4

J2ME_INSTALL_MISSING_JAR_URL:The JAR URL is missing.

J2ME_INSTALL_JAR_NOT_FOUND:The JAR was not found at the URL given in the JAD

J2ME_INSTALL_MISSING_JAR_SIZE:The JAR size is missing

J2ME_INSTALL_SUITE_NAME_MISMATCH:The suite name mismatch in JAD and JAR manifest

J2ME_INSTALL_VERSION_MISMATCH:The version mismatch in JAD and JAR manifest

J2ME_INSTALL_VENDOR_MISMATCH:The vender name mismatch in JAD and JAR manifest

J2ME_INSTALL_INVALID_KEY:A key for an attribute is not formatted correctly

J2ME_INSTALL_INVALID_VALUE:A value for an attribute is not formatted correctly

J2ME_INSTALL_INSUFFICIENT_STORAGE:Cannot download the MIDlet as there is insufficient memory space

J2ME_INSTALL_JAR_SIZE_MISMATCH:The JAR size mismatch

J2ME_INSTALL_NEW_VERSION:An newer version of %1 is already installed. Would you like to update anyway?\nCurrently installed: %5\nVersion found: %3\nVendor: %2\nWebsite: %4

J2ME_INSTALL_JAD_MOVED:The JAD URL of %1 is for an installed suite but different than the orginal JAD URL.\nDo you want to install the new version?\nOld URL: %5\nNew URL: %4

J2ME_INSTALL_CORRUPT_JAR:The JAR file is corrupt

J2ME_INSTALL_ALREADY_INSTALLED:The same version of %1 is already installed.Would you like to update anyway?\nCurrently installed: %5\nVersion found: %3\nVendor: %2\nWebsite: %4

J2ME_INSTALL_DEVICE_INCOMPATIBLE:the JAD contained an invalid Configuration/Profile

J2ME_INSTALL_MISSING_CONFIGURATION:J2ME configuration was not specified

J2ME_INSTALL_MISSING_PROFILE:J2ME profile was not specified

J2ME_INSTALL_INVALID_JAD_URL:The JAD URL is invalid

J2ME_INSTALL_INVALID_JAR_URL:The JAR URL is invalid

J2ME_INSTALL_PUSH_DUP_FAILURE:The connection in a push entry is already taken

J2ME_INSTALL_PUSH_FORMAT_FAILURE:The format of a push attribute has an invalid format

J2ME_INSTALL_PUSH_PROTO_FAILURE:The connection in a push attribute is not supported

J2ME_INSTALL_PUSH_CLASS_FAILURE:The class in a push attribute is not in JAD

J2ME_INSTALL_AUTHORIZATION_FAILURE:Application authorization failure

J2ME_INSTALL_ATTRIBUTE_MISMATCH:A attribute mismatch in JAD and JAR manifest

J2ME_INSTALL_TRUSTED_OVERWRITE_FAILURE:Overwrite a trusted suite with an untrusted suite during an update

J2ME_INSTALL_DEFAULT_GAME:The default application update failed

J2ME_INSTALL_DISK_OPERATION_FAIL:Disk IO operation failed

J2ME_INSTALL_USER_CANCEL:The installation was cancelled by the user

J2ME_INSTALL_PUSH_INSTALL:%1 will need to start itself periodically to receive information.\nIf there is already an application running,\n%1 will interrupt and that application will exit.

J2ME_INSTALL_NORMAL_INSTALL:Would you like to install %1 ?\nSize: %2K\nVersion: %3\nVendor: %4\nDescription: %5\nMedia-price: %6\nWebsite: %7 J2ME_INSTALL_INSTALL_NA:Not Applicable

J2ME_INSTALL_OVER_MAX_INSTALL:Over the maximum install limit

J2ME_INSTALL_DRM_PROHIBIT:DRM Disallow

J2ME_INSTALL_POST_ERROR:Installed successfully, but report post failed

J2ME_INSTALL_MEMORY_ALLACTION_FAILURE:Install failure for memory allocation failed

J2ME_INSTALL_MIDLET_RUNNING:Update failed for application is runng

J2ME_INSTALL_KEEP_RMS:Do you want to keep the RMS data of the previous version ?

J2ME_DELETE_SUITE: Would you like to delete ?

J2ME_INSTALL_UNKOWN_FAILUIRE:Unkown Failure

J2ME_PERMISSION_PUSH_EXCLUSIVE:Auto Invocation and Network Access are mutually exclusive

J2ME_PERMISSION_NET_EXCLUSIVE:Network Access and Auto Invocation are mutually exclusive


*/


int java_ams_HTTP_download_req(u16* u16Http,u16* u16FilePath);

int java_ams_HTTP_download_abort(void);

int java_ams_HTTP_download_rsp(int retCode, u16* u16FileName);


int java_ams_get_logo_image_req(void);

int java_ams_get_logo_image_rsp(int retCode, u32 pImageRawData, u32 u32DataLen);


//======== Push Register funciton ============

int java_ams_push_RegisterAlarm_sync(int suiteId, int midletId, unsigned long TimeH, unsigned long TimeL);

int java_ams_push_DeregisterAlarm_sync(int suiteId, int midletId, unsigned long TimeH, unsigned long TimeL);


int java_ams_push_RegisterPort_sync(int suiteId, int midletId, int port);

int java_ams_push_DeregisterPort_sync(int suiteId, int midletId, int port);

#ifdef __JAVA_OAKMONT_NFC_PUSH_SUPPORT__
int java_ams_push_RegisterNDEF_sync(int suiteId, int midletId,unsigned char* protocol,unsigned char* filter);
int java_ams_push_DeRegisterNDEF_sync(int suiteId, int midletId,unsigned char* protocol);
#endif

int java_ams_push_QueryIndex_Req(int suiteId);

int java_ams_push_QueryIndex_Rsp(int suiteId, int suiteIndex);


void java_accessory_mem_card_status(bool bPlugIn);


void jams_FuncParse(u32 srcHandle, void * pData);

#endif

#else

#ifndef __JAVA_AMS_DEFINE_H__
#define __JAVA_AMS_DEFINE_H__
#include "ven_std.h"
#include "javaamsapp_resource.h"
#define USE_AMS_LOGO

#define MINIJAVA_SHOW_LOGO
#define MINIJAVA_MAX_MIDLET_FILE_NAME_LENGTH  (128)
#define MINIJAVA_MIDLET_STRICT_CHECK

#define MINIJAVA_MIDLET_CHECK_ERROR (-1)
#define MINIJAVA_MIDLET_CHECK_OK    (0)

enum
{
    JAVA_INSTALL_NAND = 0,
    JAVA_INSTALL_MEMCARD,
};
typedef u8 java_install_storage_e;

typedef struct _java_icon_struct_t
{
    u32 icon_size;
    u32 icon_width;
    u32 icon_height;
    u8 *icon_data;
} java_icon_struct;

typedef struct _java_midlet_struct_t
{
    u16 *midlet_name;
    java_icon_struct *icon_data;
} java_midlet_struct;

typedef struct _java_suite_struct_t
{
    u16 *suite_name; /* MIDletSuite Name */
    u16 *jad_url;
    u16 *jar_url; /*MIDlet-JAR-URL */
    u16 *suite_website;
    java_icon_struct suite_icon; /* MIDletSuite Icon */
    s32 suite_size; /* MIDlet-JAR-Size */
    u16 *suite_version; /* MIDlet-Version */
    u16 *suite_vendor; /* MIDlet-Vendor */
    u16 *suite_description; /* MIDlet-Description */
    u8 suite_authorized;
    u16 *suite_authorized_by;
    u16 *suite_auto_start; /* MIDlet-Push-X */
    u8  is_preinstall;               //  add for checking preinstall,  1 is preinstall, 0 is postinstall.
    java_install_storage_e storage; // The suite is installed on NAND or memory card
} java_suite_struct;

typedef struct _java_suite_struct_list_t
{
    struct _java_suite_struct *java_suite_struct;  //detail
    struct _java_suite_struct_list_t *java_suite_next;  //pointer to next java_suite_struct_list

} java_suite_struct_list;

static java_suite_struct_list *all_suite_list;


// for permission

typedef struct _java_permission_setting_t
{
    u8 permission_network; /* Network Access */
    u8 permission_multimedia; /* Multimedia Recording */
    u8 permission_messaging; /* Wireless Messaging */
    u8 permission_autostart; /* Application Auto Invocation */
    u8 permission_localconnect; /* Local Connectivity */
    u8 permission_dataread; /* User Data Read */
    u8 permission_datawrite; /* User Data Write */
} java_permission_setting;

#define JAVA_PERMISSION_NEVER  0x00
#define JAVA_PERMISSION_ALLOW  0x01
#define JAVA_PERMISSION_BLANKET_GRANTED  0x02
#define JAVA_PERMISSION_BLANKET  0x04
#define JAVA_PERMISSION_SESSION  0x08
#define JAVA_PERMISSION_ONE_SHOT  0x10
#define JAVA_PERMISSION_DENY_SESSION  0x20
#define JAVA_PERMISSION_DENY  0x40
#define JAVA_PERMISSION_USER_DENIED  0x80

//=====================================================
#define JAVA_RET_OK                     (0)
#define JAVA_RET_FAIL                   (-1)
#define JAVA_RET_FAIL_AMSLIST_FULL      (-2)
#define JAVA_RET_FAIL_LARGE_JAR         (-3)
#define JAVA_RET_FAIL_NO_ENOUGH_SPACE   (-4) // No enough space for AMS operation
#define JAVA_RET_FAIL_STORAGE_ERROR     (-5) // Operation failed due to storage failure
#define JAVA_RET_FAIL_OUT_OF_MEMORY     (-6) // Out Of Memory


// result definition for java_ams_installProgressCB()
typedef enum
{
    //PR154243
    JAVA_ERR_INSTALL_STEP_0_FAIL = 790,
    JAVA_INSTALL_OK = 900,
    JAVA_ERR_INSTALL_NO_ENOUGH_SPACE,
    JAVA_ERR_INSTALL_USER_CANCEL,
    JAVA_ERR_INSTALL_LOSS_OF_SERVICE,
    JAVA_ERR_INSTALL_JAR_SIZE_MISMATCH,
    JAVA_ERR_INSTALL_ATTRIBUTE_MISMATCH,
    JAVA_ERR_INSTALL_INVALID_JAD,
    JAVA_ERR_INSTALL_INVALID_JAR,
    JAVA_ERR_INSTALL_CLDC_MIDP_VERSION,
    JAVA_ERR_INSTALL_AUTHENTICATION_FAILURE,
    JAVA_ERR_INSTALL_AUTHORIZATION_FAILURE,
    JAVA_ERR_INSTALL_PUSH_REGISTRATION_FALIURE,
    JAVA_ERR_INSTALL_DELETION_NOTIFICATION,
//#ifdef ___NCC_3RD_JAVA_PORTING_LAYER__
    JAVA_ERR_INSTALL_IO_CONFLICT,
    JAVA_ERR_INSTALL_CONFLICT_MMS,
    JAVA_ERR_INSTALL_CONFLICT_BT,
    JAVA_ERR_INSTALL_NO_SUITE_PRESENT,
    JAVA_ERR_INSTALL_JAR_TOO_LARGE,
//#endif
    JAVA_ERR_INSTALL_NOT_DEFINE = 999,
    JAVA_ERR_INSTALL_LAST_ONE,
} jMMIInstallErr;

typedef enum
{
    Java_Launch_Normal = 0,
    Java_Launch_Alarm,
    Java_Launch_Port
}Java_Launch_Cause_e;

enum
{
    JAVA_CONFLICT_WITH_NONE = 0,
    JAVA_CONFLICT_WITH_MMS,
    JAVA_CONFLICT_WITH_BT,
    JAVA_CONFLICT_WITH_BROWSER,
    JAVA_CONFLICT_LAST_ONE
};

typedef int javaCurBusyModule;

typedef struct _java_LaunchCause
{
    Java_Launch_Cause_e    launch_cause;
    u32    msgId;
    int     port;
} java_LanuchCause;


#ifdef __NCC_3RD_JAVA_WITH_PREINSTALL__
int java_ams_is_preinstall_running(void);
#endif

//=====================================================
int java_ams_initial_req(void);
int java_ams_initial_rsp(int retCode);

int java_ams_release_req(void);
int java_ams_release_rsp(int retCode);
//========================
//layer 1
//========================
int java_ams_getSuiteCount_req(void);
int java_ams_getSuiteCount_rsp(int retCode, int suiteCount);
//ARRAY include suite detail information
// and midlet count, suite icon
int java_ams_getSuiteInfo_req(int index);
int java_ams_getSuiteInfo_rsp(int retCode, int index,java_suite_struct *ret);

int java_ams_removeSuite_req(int index);
int java_ams_removeSuite_rsp(int retCode, int index);

int java_ams_getPermission_req(int index);
int java_ams_getPermission_rsp(int retCode, int index, java_permission_setting *ps);

int java_ams_setPermission_req(int index, java_permission_setting *ps);
int java_ams_setPermission_rsp(int retCode, int index, java_permission_setting *ps);

//========================
//layer 2
//========================
int java_ams_getMidletCount_req(int suite_index);
int java_ams_getMidletCount_rsp(int retCode, int suite_index, int midletCount);
// midlet name, midlet icon
int java_ams_getMidletInfo_req(int  suite_index,int midlet_index);
int java_ams_getMidletInfo_rsp(int retCode, int  suite_index,int midlet_index, java_midlet_struct *ret);

int java_ams_launchMidlet_req(int suite_index,int midlet_index, java_LanuchCause cause);
int java_ams_launchMidlet_rsp(int retCode, int suite_index,int midlet_index);
int java_ams_reset_preinstall_req(void);
int java_ams_reset_preinstall_rsp(int retCode);
int java_ams_reset_netProfile_req(void);
int java_ams_reset_netProfile_rsp(int retCode);

int java_ams_setNetProfile_req(int simCard);
int java_ams_setNetProfile_rsp(int retCode);

//========================
//Local Install by mmi
//========================
typedef struct _java_CheckResult
{
    s32    otaCode; // check ota code in AJMS_CheckResult
    s32    update;
    s32    trusted; // 0 means untrusted, 1 means trusted
    s32    oldId;   // must pass to Aplix install function
} java_CheckResult;

typedef struct _java_InstallResult
{
    s32    otaCode; // check ota code in AJMS_CheckResult
    s32    suiteIndex;
} java_InstallResult;

typedef enum
{
    Java_J2ME_INSTALL_NO_ERROR = 0,
    Java_J2ME_INSTALL_JAD_NOT_FOUND = 2,
    Java_J2ME_INSTALL_MISSING_PROVIDER_CERT = 4,
    Java_J2ME_INSTALL_CORRUPT_PROVIDER_CERT = 5,
    Java_J2ME_INSTALL_UNKNOWN_CA = 6,
    Java_J2ME_INSTALL_INVALID_PROVIDER_CERT = 7,
    Java_J2ME_INSTALL_CORRUPT_SIGNATURE = 8,
    Java_J2ME_INSTALL_INVALID_SIGNATURE = 9,
    Java_J2ME_INSTALL_UNSUPPORTED_CERT = 10,
    Java_J2ME_INSTALL_EXPIRED_PROVIDER_CERT = 11,
    Java_J2ME_INSTALL_EXPIRED_CA_KEY = 12,
    Java_J2ME_INSTALL_MISSING_SUITE_NAME = 13,
    Java_J2ME_INSTALL_MISSING_VENDOR = 14,
    Java_J2ME_INSTALL_MISSING_VERSION = 15,
    Java_J2ME_INSTALL_INVALID_VERSION = 16,
    Java_J2ME_INSTALL_OLD_VERSION = 17,
    Java_J2ME_INSTALL_MISSING_JAR_URL = 18,
    Java_J2ME_INSTALL_NAME_TOO_LONG = 19,
    Java_J2ME_INSTALL_JAR_NOT_FOUND = 20,
    Java_J2ME_INSTALL_MISSING_JAR_SIZE = 21,
    Java_J2ME_INSTALL_SUITE_NAME_MISMATCH = 25,
    Java_J2ME_INSTALL_VERSION_MISMATCH = 26,
    Java_J2ME_INSTALL_VENDOR_MISMATCH = 27,
    Java_J2ME_INSTALL_INVALID_KEY = 28,
    Java_J2ME_INSTALL_INVALID_VALUE = 29,
    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE = 30,
    Java_J2ME_INSTALL_JAR_SIZE_MISMATCH = 31,
    Java_J2ME_INSTALL_NEW_VERSION = 32,
    Java_J2ME_INSTALL_JAD_MOVED = 34,
    Java_J2ME_INSTALL_CORRUPT_JAR = 36,
    Java_J2ME_INSTALL_ALREADY_INSTALLED = 39,
    Java_J2ME_INSTALL_DEVICE_INCOMPATIBLE = 40,
    Java_J2ME_INSTALL_MISSING_CONFIGURATION = 41,
    Java_J2ME_INSTALL_MISSING_PROFILE = 42,
    Java_J2ME_INSTALL_INVALID_JAD_URL = 43,
    Java_J2ME_INSTALL_INVALID_JAR_URL = 44,
    Java_J2ME_INSTALL_PUSH_DUP_FAILURE = 45,
    Java_J2ME_INSTALL_PUSH_FORMAT_FAILURE = 46,
    Java_J2ME_INSTALL_PUSH_PROTO_FAILURE = 47,
    Java_J2ME_INSTALL_PUSH_CLASS_FAILURE = 48,
    Java_J2ME_INSTALL_AUTHORIZATION_FAILURE = 49,
    Java_J2ME_INSTALL_ATTRIBUTE_MISMATCH = 50,
    Java_J2ME_INSTALL_TRUSTED_OVERWRITE_FAILURE = 52,
    Java_J2ME_INSTALL_DEFAULT_GAME = 60,
    Java_J2ME_INSTALL_DISK_OPERATION_FAIL = 80,
    Java_J2ME_INSTALL_PATH_NOT_FOUND_WHEN_UPDATE = 81,
    Java_J2ME_INSTALL_USER_CANCEL = 90,
    Java_J2ME_INSTALL_PUSH_INSTALL = 91,
    Java_J2ME_INSTALL_NORMAL_INSTALL = 92,
    Java_J2ME_INSTALL_INSTALL_NA = 93,
    Java_J2ME_INSTALL_OVER_MAX_INSTALL = 94,
    Java_J2ME_INSTALL_DRM_PROHIBIT = 95,
    Java_J2ME_INSTALL_POST_ERROR = 100,
    Java_J2ME_INSTALL_MEMORY_ALLACTION_FAILURE = 101,
    Java_J2ME_INSTALL_MIDLET_RUNNING = 206,
    Java_J2ME_INSTALL_KEEP_RMS = 207,
    Java_J2ME_INSTALL_DELETE_SUITE = 208,
    Java_J2ME_INSTALL_INVALID_DESCRIPTOR,
    Java_J2ME_INSTALL_IO_CONFLICT,
    Java_J2ME_INSTALL_IO_CONFLICT_WITH_MMS,
    Java_J2ME_INSTALL_IO_CONFLICT_WITH_BT,
    Java_J2ME_INSTALL_UNKOWN_FAILUIRE = 999,
    Java_J2ME_INSTALL_OK = 0, // Delta project use Java_J2ME_INSTALL_NO_ERROR
    Java_J2ME_INSTALL_LAUNCH = 8193,
    Java_J2ME_INSTALL_CUSTOM_STRING_CONFIRM=8194, //we need some custom string to show in nemomp_jam_install_user_confirm function
    Java_J2ME_INSTALL_PUSH_AND_NORMAL_INSTALL=8195,
    Java_J2ME_INSTALL_PUSH_AND_ALREADY_INSTALLEDL=8196,
    Java_J2ME_INSTALL_PUSH_AND_INSTALL_OLD_VERSION=8197,
    Java_J2ME_INSTALL_PUSH_AND_INSTALL_NEW_VERSION=8198,

    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_NAND = 8199,
    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_SD = 8200,
    Java_J2ME_INSTALL_INSUFFICIENT_STORAGE_LARGE_MIDLET = 8201,


} install_error_code_enum;

#define JAVA_UPDATE_MIDLET_SUITE_NOT_EXIST  (1)
#define JAVA_UPDATE_NOT_ALLOW               (2)
#define JAVA_UPDATE_NEWER_VERSION           (3)
#define JAVA_UPDATE_SAME_VERSION            (4)
#define JAVA_UPDTAE_OLDER_VERSION           (5)
#define JAVA_UPDATE_INVALID_MIDLET          (6)
#define JAVA_UPDATE_IO_CONFLICT             (7)

typedef int(* java_ams_InstallCheckCB)(int total, int step, java_CheckResult Result);
int java_ams_checkMidletSuite_req(u16 *jadPath, u16 *jarPath, java_ams_InstallCheckCB cb);
int java_ams_checkMidletSuite_rsp(int retCode, java_CheckResult* pResult);

typedef int(* java_ams_installProgressCB)(int total, int step, java_InstallResult Result);
int java_ams_installMidletSuite_req(u16 *jadPath, u16 *jarPath, int KeepRMS, s32 oldId, java_ams_installProgressCB cb);

#ifdef __JAVA_OAKMONT__
int java_ams_installMidletSuite_rsp(int retCode);
#else
//int java_ams_installMidletSuite_rsp(install_error_code_enum retCode,u16 installSuiteId);
int java_ams_installMidletSuite_rsp(int retCode,int installSuiteId);
#endif


int java_ams_cancelinstallSuite_req(void);
int java_ams_cancelinstallSuite_rsp(void);

#ifdef JAVAAMS_OTA
int jams_installProgressCB(int total, int step, java_InstallResult Result);
int jams_installCheckCB(int total, int step, java_CheckResult Result);
#endif //JAVAAMS_OTA

//========================
//Local Install by kvm
//========================
#define INFOKEY(key) ((key)<<24)
#define LEFTKEY(key) ((key)<<16)
#define MIDKEY(key) ((key) << 8)
#define RIGHTKEY(key) (key)

#define GET_INFOKEY(key)  (((key) >> 24) & 0xff)
#define GET_LEFTKEY(key)  (((key) >> 16) & 0xff)
#define GET_MIDKEY(key)  (((key) >> 8 ) & 0xff)
#define GET_RIGHTKEY(key) (((key) & 0xff))


#define AMS_KEY_OK 1
#define AMS_KEY_CANCEL 2
#define AMS_KEY_SELECT 3
#define AMS_KEY_YES 4
#define AMS_KEY_NO 5
#define AMS_KEY_DONE 6

// This info comes with user selected key from java_ams_set_show_progress_rsp() and java_ams_draw_install_dialog_sync()
// Currently used with AMS_KEY_CANCEL for cancel reason.
#define AMS_INFO_NONE 0 // Nonthing special
#define AMS_INFO_MEM_CARD_LOST 1 // External memory card is lost.
void java_ams_show_logo(void);
int java_ams_set_show_progress_req(int percent,u32 softkey);
int java_ams_set_show_progress_rsp(u32 *selected_key);
int java_ams_draw_install_dialog_sync(int jamMsgID, u16* Msg,u32 softkey, u32 *selected_key);

/*
* JAM Message ID and the Message content (suggestion)
J2ME_INSTALL_JAD_NOT_FOUND:Install failure
J2ME_INSTALL_MISSING_PROVIDER_CERT:Certificate chain is missing in JAD
J2ME_INSTALL_CORRUPT_PROVIDER_CERT:JAD certificate is corrupt
J2ME_INSTALL_UNKNOWN_CA:Jad certificate is unknown
J2ME_INSTALL_INVALID_PROVIDER_CERT:JAD certificate is invalid
J2ME_INSTALL_CORRUPT_SIGNATURE:JAR signature is corrupt
J2ME_INSTALL_INVALID_SIGNATURE:JAR signature is invalid
J2ME_INSTALL_UNSUPPORTED_CERT:JAD certificate is unsupported
J2ME_INSTALL_EXPIRED_PROVIDER_CERT:JAD certificate is expired.
J2ME_INSTALL_EXPIRED_CA_KEY:JAD certificate's public key has expired.
J2ME_INSTALL_MISSING_SUITE_NAME:The suite name is missing
J2ME_INSTALL_MISSING_VENDOR:The vender name is missing
J2ME_INSTALL_MISSING_VERSION:The version is missing
J2ME_INSTALL_INVALID_VERSION:The version is invalid
J2ME_INSTALL_OLD_VERSION:An older version of %1 is already installed.\nWould you like to update anyway?\nCurrently installed: %5\nVersion found:%3\nVendor: %2\nWebsite: %4
J2ME_INSTALL_MISSING_JAR_URL:The JAR URL is missing.
J2ME_INSTALL_JAR_NOT_FOUND:The JAR was not found at the URL given in the JAD
J2ME_INSTALL_MISSING_JAR_SIZE:The JAR size is missing
J2ME_INSTALL_SUITE_NAME_MISMATCH:The suite name mismatch in JAD and JAR manifest
J2ME_INSTALL_VERSION_MISMATCH:The version mismatch in JAD and JAR manifest
J2ME_INSTALL_VENDOR_MISMATCH:The vender name mismatch in JAD and JAR manifest
J2ME_INSTALL_INVALID_KEY:A key for an attribute is not formatted correctly
J2ME_INSTALL_INVALID_VALUE:A value for an attribute is not formatted correctly
J2ME_INSTALL_INSUFFICIENT_STORAGE:Cannot download the MIDlet as there is insufficient memory space
J2ME_INSTALL_JAR_SIZE_MISMATCH:The JAR size mismatch
J2ME_INSTALL_NEW_VERSION:An newer version of %1 is already installed. Would you like to update anyway?\nCurrently installed: %5\nVersion found: %3\nVendor: %2\nWebsite: %4
J2ME_INSTALL_JAD_MOVED:The JAD URL of %1 is for an installed suite but different than the orginal JAD URL.\nDo you want to install the new version?\nOld URL: %5\nNew URL: %4
J2ME_INSTALL_CORRUPT_JAR:The JAR file is corrupt
J2ME_INSTALL_ALREADY_INSTALLED:The same version of %1 is already installed.Would you like to update anyway?\nCurrently installed: %5\nVersion found: %3\nVendor: %2\nWebsite: %4
J2ME_INSTALL_DEVICE_INCOMPATIBLE:the JAD contained an invalid Configuration/Profile
J2ME_INSTALL_MISSING_CONFIGURATION:J2ME configuration was not specified
J2ME_INSTALL_MISSING_PROFILE:J2ME profile was not specified
J2ME_INSTALL_INVALID_JAD_URL:The JAD URL is invalid
J2ME_INSTALL_INVALID_JAR_URL:The JAR URL is invalid
J2ME_INSTALL_PUSH_DUP_FAILURE:The connection in a push entry is already taken
J2ME_INSTALL_PUSH_FORMAT_FAILURE:The format of a push attribute has an invalid format
J2ME_INSTALL_PUSH_PROTO_FAILURE:The connection in a push attribute is not supported
J2ME_INSTALL_PUSH_CLASS_FAILURE:The class in a push attribute is not in JAD
J2ME_INSTALL_AUTHORIZATION_FAILURE:Application authorization failure
J2ME_INSTALL_ATTRIBUTE_MISMATCH:A attribute mismatch in JAD and JAR manifest
J2ME_INSTALL_TRUSTED_OVERWRITE_FAILURE:Overwrite a trusted suite with an untrusted suite during an update
J2ME_INSTALL_DEFAULT_GAME:The default application update failed
J2ME_INSTALL_DISK_OPERATION_FAIL:Disk IO operation failed
J2ME_INSTALL_USER_CANCEL:The installation was cancelled by the user
J2ME_INSTALL_PUSH_INSTALL:%1 will need to start itself periodically to receive information.\nIf there is already an application running,\n%1 will interrupt and that application will exit.
J2ME_INSTALL_NORMAL_INSTALL:Would you like to install %1 ?\nSize: %2K\nVersion: %3\nVendor: %4\nDescription: %5\nMedia-price: %6\nWebsite: %7 J2ME_INSTALL_INSTALL_NA:Not Applicable
J2ME_INSTALL_OVER_MAX_INSTALL:Over the maximum install limit
J2ME_INSTALL_DRM_PROHIBIT:DRM Disallow
J2ME_INSTALL_POST_ERROR:Installed successfully, but report post failed
J2ME_INSTALL_MEMORY_ALLACTION_FAILURE:Install failure for memory allocation failed
J2ME_INSTALL_MIDLET_RUNNING:Update failed for application is runng
J2ME_INSTALL_KEEP_RMS:Do you want to keep the RMS data of the previous version ?
J2ME_DELETE_SUITE: Would you like to delete ?
J2ME_INSTALL_UNKOWN_FAILUIRE:Unkown Failure
J2ME_PERMISSION_PUSH_EXCLUSIVE:Auto Invocation and Network Access are mutually exclusive
J2ME_PERMISSION_NET_EXCLUSIVE:Network Access and Auto Invocation are mutually exclusive

*/
#ifdef JAVAAMS_OTA
int java_ams_HTTP_download_req(u16* u16Http,u16* u16FilePath);
int java_ams_HTTP_download_abort(void);
int java_ams_HTTP_download_rsp(int retCode, u16* u16FileName);
#endif //JAVAAMS_OTA

#ifdef USE_AMS_LOGO
int java_ams_get_logo_image_req(void);
int java_ams_get_logo_image_rsp(int retCode, u32 pImageRawData, u32 u32DataLen,u16 *pAmsLogoTxt);
#endif

#ifdef JAVAAMS_WMA
//======== Push Register funciton ============
int java_ams_push_RegisterAlarm_sync(int suiteId, int midletId, unsigned long TimeH, unsigned long TimeL);
int java_ams_push_DeregisterAlarm_sync(int suiteId, int midletId, unsigned long TimeH, unsigned long TimeL);

int java_ams_push_RegisterPort_sync(int suiteId, int midletId, int port);
int java_ams_push_DeregisterPort_sync(int suiteId, int midletId, int port);

int java_ams_push_QueryIndex_Req(int suiteId);
int java_ams_push_QueryIndex_Rsp(int suiteId, int suiteIndex);
#endif //JAVAAMS_WMA
#ifdef JAVAAMS_MEMORYSTATUS
void java_accessory_mem_card_status(bool bPlugIn);
#endif//JAVAAMS_MEMORYSTATUS
void jams_FuncParse(u32 srcHandle, void * pData);
#endif
#endif

