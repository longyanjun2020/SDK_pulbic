#ifndef DALVIK_AMS_INFO_H
#define DALVIK_AMS_INFO_H
#include "java_def.h"
#include "java_ams.h"

#define DALVIK_FIELS_DIR                L"/NAND/.system"
#define DALVIK_FIELS_DIR_SD             L"/CARD/.system"

#define SUITE_INFO_FILENAME	      L"/NAND/.system/suitesInfo.utf"
#define TMP_SUITE_INFO_FILENAME	  L"/NAND/.system/temp.utf"
#define SUITE_INFO_BAK_FILENAME	  L"/NAND/.system/suitesInfo.bak"



#define MAX_SUITE_SIZE   60
#define MAX_MIDLET_NUM 10

#define MAX_MIDLET_NAME_NUM  30
#define MAX_MIDLET_NAME_LEN  130

char dalvik_mid_name_arr[MAX_MIDLET_NAME_NUM][MAX_MIDLET_NAME_LEN];
char dalvik_mid_class_name_arr[MAX_MIDLET_NAME_NUM][MAX_MIDLET_NAME_LEN];

typedef struct dalvik_midlet_info_t
{
    struct nm_midlet_info_t *mid_next; /* pointer to next node */
    unsigned short *mid_name;			/* MIDlet-Name-X */
} dalvik_midlet_info;

typedef struct dalvik_suite_info_t
{
    int mid_count;			 /* How many MIDlets in this MIDletSuite */
    int mid_info_size;		/* MIDlet-Data-Size */
    dalvik_midlet_info *mid_list;
} dalvik_suite_info;


typedef struct nm_suite_icon_info_t
{
    u32 icon_size;
    u32 icon_width;
    u32 icon_height;
    u8 *icon_data; /* ARGB8888 */
} dalvik_suite_icon_info;



typedef struct dalvik_suite_detail_t
{
    struct dalivk_suite_detail_t *suite_detail_next;   /* pointer to next node */

    int mids_info_size;                  /* internal use, size of mids_info_rawdata */
    unsigned char  *mids_info_rawdata;   /* pointer to mids info raw data to speed up release */
    unsigned short *mids_name;		       /* MIDletSuite Name */
    unsigned short *mids_root;
    dalvik_suite_icon_info mids_icon;	/* MIDletSuite Icon */
    unsigned short *jad_url;
    unsigned short *jar_url;			       /*MIDlet-JAR-URL */
    unsigned short *website;
    dalvik_suite_info mid_info;		       /* Other Information */
    int mids_size;			                 /* MIDlet-JAR-Size */
    unsigned short *mids_version;		     /* MIDlet-Version */
    unsigned short *mids_vendor;		     /* MIDlet-Vendor */
    unsigned short *mids_description;		/* MIDlet-Description */
} dalvik_suite_detail;

typedef struct dalvik_suites_list_t
{
    int mids_count;                   /* Total mids count */
    int mids_avail_indx;              /* Available mids on list start index */
    int mids_avail_count;             /* Available mids on list count */
    dalvik_suite_detail *mids_info_list;  /* Available mids on list */
} dalvik_suites_list;


typedef struct state_struct
{
	int nextStep;
	int exception;
	unsigned short* exception_extra_data;
	char *error_reason;
	unsigned short* jadUrl;
	bool force;
	bool removeRMS;
	unsigned char* jad;
	int jad_len;
	dalvik_suite_icon_info mids_icon;	/* MIDletSuite Icon */
	unsigned short* jadEncoding;
	unsigned short* suiteName;
	unsigned short* vendor;
	unsigned short* version;
	unsigned short* storageName;
	unsigned short* ca;
	char* domain;
	int expectedJarSize;
	unsigned short* jarUrl;
	unsigned char pushInterruptSetting;
	bool trusted;
	unsigned char* manifest;
	int manifest_len;
	char* tempFilename;
	char* storageRoot;
	bool isPreviousVersion;
	unsigned short* previousUrl;
	unsigned short* previousJadUrl;
	unsigned short* previousJarUrl;
	int previousTrusted;
	int NumberOfMIDlets;
	unsigned short* previousCA;
	int total_file_size;
	bool path_need_recovery;
	unsigned short* midlet[MAX_MIDLET_NUM];
        unsigned short* midlet_class[MAX_MIDLET_NUM];

} install_state;

install_state state;

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
	J2ME_INSTALL_DEFAULT_GAME = 60,
	J2ME_INSTALL_DISK_OPERATION_FAIL = 80,
	J2ME_INSTALL_PATH_NOT_FOUND_WHEN_UPDATE=81,
	J2ME_INSTALL_USER_CANCEL = 90,
	J2ME_INSTALL_PUSH_INSTALL = 91,
	J2ME_INSTALL_NORMAL_INSTALL = 92,
	J2ME_INSTALL_INSTALL_NA = 93,
	J2ME_INSTALL_OVER_MAX_INSTALL = 94,
	J2ME_INSTALL_DRM_PROHIBIT = 95,
	J2ME_INSUFFICIENT_MEMORY = 96,
	J2ME_READ_SUITES_LIST_FAILURE = 97,
	J2ME_INSTALL_POST_ERROR = 100,
	J2ME_INSTALL_MEMORY_ALLACTION_FAILURE = 101,
	J2ME_INSTALL_MIDLET_RUNNING = 206,
	J2ME_INSTALL_KEEP_RMS = 207,
	J2ME_INSTALL_DELETE_SUITE = 208,
	J2ME_INSTALL_UNKOWN_FAILUIRE = 999,
	J2ME_INSTALL_OK = 0, // Delta project use J2ME_INSTALL_NO_ERROR
	J2ME_INSTALL_LAUNCH = 8193,
	J2ME_INSTALL_CUSTOM_STRING_CONFIRM=8194, //we need some custom string to show in nemomp_jam_install_user_confirm function
	J2ME_INSTALL_PUSH_AND_NORMAL_INSTALL=8195,
	J2ME_INSTALL_PUSH_AND_ALREADY_INSTALLEDL=8196,
    J2ME_INSTALL_PUSH_AND_INSTALL_OLD_VERSION=8197,
    J2ME_INSTALL_PUSH_AND_INSTALL_NEW_VERSION=8198,

    J2ME_INSTALL_INSUFFICIENT_STORAGE_NAND = 8199,
    J2ME_INSTALL_INSUFFICIENT_STORAGE_SD = 8200,
    J2ME_INSTALL_INSUFFICIENT_STORAGE_LARGE_MIDLET = 8201,


} install_error_code_enum2;




#define O_RDONLY	0x0000
#define O_WRONLY	0x0001
#define O_RDWR	0x0002
#define O_APPEND       0x0008

#define O_CREAT	0x0100
#define O_TRUNC	0x0200
#define O_BINARY	0x8000

#ifndef SEEK_SET
#  define SEEK_SET        0       /* Seek from beginning of file.  */
#  define SEEK_CUR        1       /* Seek from current position.  */
#  define SEEK_END        2       /* Set file pointer to EOF plus "offset" */
#endif


#endif
