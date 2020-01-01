#ifndef __NEMOMP_INSTALLER_H
#define __NEMOMP_INSTALLER_H

/*************************************************************************
 * Include Header Files
 *************************************************************************/
#include "nemomp_jam.h"
#include "nemomp_files.h"
#include "nemomp_suite_setting.h"
#ifdef __JAVA_JSR211_CHAPI__
#include "nemomp_chapi_NodeList.h" // 20090218: Added for JSR-211 CHAPI
#endif /* __JAVA_JSR211_CHAPI__ */

/************************************************************************
 * type definition
 ************************************************************************/

/*************************************************************************
 * Global Constant Definition
 *************************************************************************/
typedef enum {
	AMS_OP_INSTALL,
	AMS_OP_INSTALL_JAR,
	AMS_OP_UPDATE,
	AMS_OP_REMOVE,
	AMS_OP_INVALID
} ams_op_enum;

typedef enum
{
    J2ME_INSTALL_NO_ERROR = 0,
    J2ME_INSTALL_JAD_NOT_FOUND = 2,
    J2ME_INSTALL_MISSING_PROVIDER_CERT = 4,
    J2ME_INSTALL_CORRUPT_PROVIDER_CERT = 5,
    J2ME_INSTALL_UNKNOWN_CA = 6,
    J2ME_INSTALL_INVALID_PROVIDER_CERT = 7,
    J2ME_INSTALL_CORRUPT_SIGNATURE = 8,
    J2ME_INSTALL_INVALID_SIGNATURE = 9,
    J2ME_INSTALL_UNSUPPORTED_CERT = 10,
    J2ME_INSTALL_EXPIRED_PROVIDER_CERT = 11,
    J2ME_INSTALL_EXPIRED_CA_KEY = 12,
    J2ME_INSTALL_MISSING_SUITE_NAME = 13,
    J2ME_INSTALL_MISSING_VENDOR = 14,
    J2ME_INSTALL_MISSING_VERSION = 15,
    J2ME_INSTALL_INVALID_VERSION = 16,
    J2ME_INSTALL_OLD_VERSION = 17,
    J2ME_INSTALL_MISSING_JAR_URL = 18,
    J2ME_INSTALL_JAR_NOT_FOUND = 20,
    J2ME_INSTALL_MISSING_JAR_SIZE = 21,
    J2ME_INSTALL_SUITE_NAME_MISMATCH = 25,
    J2ME_INSTALL_VERSION_MISMATCH = 26,
    J2ME_INSTALL_VENDOR_MISMATCH = 27,
    J2ME_INSTALL_INVALID_KEY = 28,
    J2ME_INSTALL_INVALID_VALUE = 29,
    J2ME_INSTALL_INSUFFICIENT_STORAGE = 30,
    J2ME_INSTALL_JAR_SIZE_MISMATCH = 31,
    J2ME_INSTALL_NEW_VERSION = 32,
    J2ME_INSTALL_JAD_MOVED = 34,
    J2ME_INSTALL_CORRUPT_JAR = 36,
    J2ME_INSTALL_ALREADY_INSTALLED = 39,
    J2ME_INSTALL_DEVICE_INCOMPATIBLE = 40,
    J2ME_INSTALL_MISSING_CONFIGURATION = 41,
    J2ME_INSTALL_MISSING_PROFILE = 42,
    J2ME_INSTALL_INVALID_JAD_URL = 43,
    J2ME_INSTALL_INVALID_JAR_URL = 44,
    J2ME_INSTALL_PUSH_DUP_FAILURE = 45,
    J2ME_INSTALL_PUSH_FORMAT_FAILURE = 46,
    J2ME_INSTALL_PUSH_PROTO_FAILURE = 47,
    J2ME_INSTALL_PUSH_CLASS_FAILURE = 48,
    J2ME_INSTALL_AUTHORIZATION_FAILURE = 49,
    J2ME_INSTALL_ATTRIBUTE_MISMATCH = 50,
    J2ME_INSTALL_TRUSTED_OVERWRITE_FAILURE = 52,
// 20090218: Added for JSR-211 CHAPI
#ifdef __JAVA_JSR211_CHAPI__
    J2ME_INSTALL_INVALID_CONTENT_HANDLER = 53,
    J2ME_INSTALL_CONTENT_HANDLER_CONFLICT = 54,
#endif /* __JAVA_JSR211_CHAPI__ */
    J2ME_INSTALL_DEFAULT_GAME = 60,
    J2ME_INSTALL_DISK_OPERATION_FAIL = 80,
    J2ME_INSTALL_USER_CANCEL = 90,
    J2ME_INSTALL_PUSH_INSTALL = 91,
    J2ME_INSTALL_NORMAL_INSTALL = 92,
    J2ME_INSTALL_INSTALL_NA = 93,
    J2ME_INSTALL_OVER_MAX_INSTALL = 94,
    J2ME_INSTALL_DRM_PROHIBIT = 95,
    J2ME_INSTALL_POST_ERROR = 100,
    J2ME_INSTALL_MEMORY_ALLACTION_FAILURE = 101,
    J2ME_INSTALL_MIDLET_RUNNING = 206,
    J2ME_INSTALL_KEEP_RMS = 207,
    J2ME_INSTALL_DELETE_SUITE = 208,
    J2ME_INSTALL_UNKOWN_FAILUIRE = 999,
} intall_error_code_enum;


#define INSTALLER_DEBUG
#define INSTALLER_DETAILED_DEBUG 						(1)

#define CLDC_VERSION 									"CLDC-1.1"
#define MIDP_VERSION 									"MIDP-2.0"

/* Number of fields in native_permissions table */
// 20090218: Changed for Add JSR-211 CHAPI
#ifdef __JAVA_JSR211_CHAPI__
  #define NUMBER_OF_PERMISSIONS 							(30)
#else
  #define NUMBER_OF_PERMISSIONS 							(29)
#endif /* __JAVA_JSR211_CHAPI__ */

extern char* native_permissions[];

  
/*************************************************************************
 * Midlet Attribute names
 *************************************************************************/
#define JAR_MANIFEST									"META-INF/MANIFEST.MF"
#define DATA_SIZE_PROP									"MIDlet-Data-Size"
#define JAR_SIZE_PROP									"MIDlet-Jar-Size"
#define JAR_URL_PROP									"MIDlet-Jar-URL"
#define SUITE_NAME_PROP									"MIDlet-Name"
#define VENDOR_PROP										"MIDlet-Vendor"
#define VERSION_PROP									"MIDlet-Version"
#define DESC_PROP										"MIDlet-Description"
#define NOTIFY_PROP										"MIDlet-Install-Notify"
#define DELETE_PROP										"MIDlet-Delete-Notify"
#define CONFIGURATION_PROP 								"MicroEdition-Configuration"
#define PROFILE_PROP									"MicroEdition-Profile"
#define PERMISSIONS_PROP								"MIDlet-Permissions"
#define PERMISSIONS_OPT_PROP							"MIDlet-Permissions-Opt"
#define CERTIFICATE_PREFIX_PROP						"MIDlet-Certificate-" // 20081223: Added
#ifdef __JAVA_JSR211_CHAPI__
#define CHAPI_HANDLER_PROP							"MicroEdition-Handler-" // 20090218: Added for JSR-211 CHAPI
#endif /* __JAVA_JSR211_CHAPI__ */


#include "nemomp_jam_files.h"


/*************************************************************************
 * Installing Result Code and Message
 *************************************************************************/
#define SUCCESS_MSG 									"900 Success" 
#define INSUFFICIENT_MEM_MSG 							"901 Insufficient Memory" 
#define USER_CANCELLED_MSG 								"902 User Cancelled" 
#define JAR_SIZE_MISMATCH_MSG 							"904 JAR Size Mismatch" 
#define ATTRIBUTE_MISMATCH_MSG 							"905 Attribute Mismatch" 
#define INVALID_JAD_MSG 								"906 Invalid Descriptor" 
#define INVALID_JAR_MSG 								"907 Invalid JAR" 
#define INCOMPATIBLE_MSG 								"908 Incompatible Configuration or Profile" 
#define AUTHENTICATION_FAILURE_MSG 						"909 Application authentication failure" 
#define J2ME_INSTALL_AUTHORIZATION_ERROR_MSG 						"910 Application authorization failure" 
#define PUSH_REG_FAILURE_MSG 							"911 Push registration failure" 
#define DELETE_NOTIFICATION_MSG 						"912 Deletion notification" 
// 20090218: Added for JSR-211 CHAPI
#ifdef __JAVA_JSR211_CHAPI__
#define CONTENT_HANDLER_CONFLICT_MSG				"938 Content handler conflicts with other handlers"
#define INVALID_CONTENT_HANDLER_MSG					"939 Content handler install failed"
#endif /* __JAVA_JSR211_CHAPI__ */


#define MAX_STORAGE_SIZE 								(256 - 10)     

/* IVI Jack adds to distinguish error */
#define INSTALLER_INVALIDJADEXCEPTION					(1)
#define INSTALLER_ILLEGALARGUMENTEXCEPTION				(2)
#define INSTALLER_OTEREXCEPTION							(3)

/*************************************************************************
 * Main Structure to store installing information
 *************************************************************************/
typedef struct state_struct
{
	int nextStep;      
	/* jboolean stopInstallation; */

	int exception; 
	unsigned short* exception_extra_data;
	char *error_reason;
	unsigned short* jadUrl;
	nm_bool force;
	nm_bool removeRMS;
	unsigned char* jad;   
	int jad_len;
	unsigned short* jadEncoding;
	/* unsigned short* username; */
	/* unsigned short* password; */
	/* unsigned short* proxyUsername; */
	/* unsigned short* proxyPassword; */
	unsigned short* suiteName;
	unsigned short* vendor;
	unsigned short* version;
	/* unsigned short* description; */
	unsigned short* storageName;
	unsigned short* ca;
	char* domain; // 20080508: Added
	int expectedJarSize;
	unsigned short* jarUrl;
	unsigned char pushInterruptSetting;
	nm_bool trusted;
	unsigned char* manifest;
	int manifest_len;
	char* tempFilename;
	char* storageRoot;
	nm_bool isPreviousVersion;
	unsigned short* previousUrl;
	unsigned short* previousJadUrl;
	unsigned short* previousJarUrl;
	int previousTrusted;
	int NumberOfMIDlets;        
	unsigned short* previousCA;         

	/*IVI Jack add to reocord the total size of generated files*/
	int total_file_size;
	nm_bool path_need_recovery;

// 20090218: Added for JSR-211 CHAPI
#ifdef __JAVA_JSR211_CHAPI__
	NodeList* chapi_handlers;
#endif /* __JAVA_JSR211_CHAPI__ */

} install_state;

typedef struct _install_update_struct_t
{
    nm_bool is_aborted;		/* check if the install or update is terminated by receiving abort */
    nm_bool can_be_aborted;	/* check if it is in intall or update stage and "aborted" dialog can be popped up */
    nm_bool is_update;		/* make sure the install is an update */
    nm_bool need_to_clean;	/* check needs to use storage recovery module to clean disk */
    nm_bool has_returned_res;	/* make sure the confirm message of install or update has been sent */
    nm_int32 local_install_return_code;
    nm_bool is_force_local_install;	/* check if the local install is by force */
    nm_bool is_local_install;	/* check the install is a local install */
    nm_bool is_normal_install;
    nm_bool install_cancelled; /* check installation is canceled by the user */
} install_update_struct;

/*************************************************************************
 * External Declaration
 *************************************************************************/
extern int getAndCleanMSG(int *);
extern void getAndCleanMSGWithPost(int *);
extern int postInstallMsgBackToProvider(char *);
extern int install_main(ams_op_enum op_type, char* work_path, char *argv);

extern install_update_struct install_update_status;

#endif /* __INSTALLER_H */

