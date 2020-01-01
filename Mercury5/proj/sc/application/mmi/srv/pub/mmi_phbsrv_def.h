
#ifndef __MMI_PHBSRV_DEF_H__
#define __MMI_PHBSRV_DEF_H__

#include "img_data.h"
#include "mmi_common_custom.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_base_util.h"
#include "filemgr_fstream.h"
#include "mmi_common_storage_mgr_cfg.h"

/*
    Define
*/
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#define __MMI_PHB_IMPORT_EXPORT_ENCODING_GB__
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#define MMI_PHB_AP_DEFAULT_HEADPIC  0 //PHONEBOOK_IMG_CONTACT_THUMBNAIL
#define MMI_PHB_AP_DEFAULT_RINGID   0
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
#define MMI_PHB_AP_VIDEOID_NONE     0 // Since we don't have default video, the default video is set to none
#endif

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#define MMI_PHB_GENERIC_EXPORT_EXT_NAME             L"vcf"
#define MMI_PHB_GENERIC_EXPORT_FILE_NAME_TAIL       L"." MMI_PHB_GENERIC_EXPORT_EXT_NAME
#define MMI_PHB_BT_EXPORT_FILE_EXT_NAME             L"vcf"
#define MMI_PHB_BT_EXPORT_FILE_NAME_TAIL            L"." MMI_PHB_BT_EXPORT_FILE_EXT_NAME

#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
#define MMI_PHB_GENERIC_EXPORT_EXT_NAME_CSV			L"csv"
#define MMI_PHB_GENERIC_EXPORT_FILE_NAME_TAIL_CSV	L"." MMI_PHB_GENERIC_EXPORT_EXT_NAME_CSV
#endif

#define MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR             L"tmp/"
#define MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR_PATH_PHONE  (DIR_PHONE DIR_PHONEBOOK MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR)
#define MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR_PATH_CARD   (DIR_CARD DIR_PHONEBOOK MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR)
#define MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR_PATH_CARD2  (DIR_CARD2 DIR_PHONEBOOK MMI_PHB_BT_EXPORT_VCARD_TEMP_DIR)
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

//#define MMI_PHB_GROUP_BLIST_MASK (1 << 29) // 29 is defined in MMI_PHB_GROUP_BLACK_LIST

#ifndef __SMALL_PHB_MMI__  
#define MMI_PHB_GROUP_URL_MASK (1 << 30) // 30 is defined in MMI_PHB_GROUP_URL
#define MMI_PHB_GROUP_EMAIL_MASK (1 << 31) // 31 is defined in MMI_PHB_GROUP_EMAIL
#endif
/*
    Enum
*/

/************************************************************************/
/* PHB Function execution status                                                */
/************************************************************************/
enum
{
    MMI_PHB_RETURN_OK                  = 0,
    MMI_PHB_RETURN_INVALID_PARM        = 1,
    MMI_PHB_RETURN_BUSY                = 2,
    MMI_PHB_RETURN_RECORD_NOT_FOUND    = 3,
    MMI_PHB_RETURN_RECORD_FULL         = 4,
    MMI_PHB_RETURN_MEMORY_FULL         = 5,
    MMI_PHB_RETURN_FAILED              = 6,
    MMI_PHB_RETURN_STATUS_NOT_MATCH    = 7,    /* When the status is different between sorting table and contacts. */
    MMI_PHB_RETURN_NUMBER_EMPTY        = 8,    // all number are empty
    MMI_PHB_RETURN_NUMBER_INVALID      = 9,    // one of the number contains invalid char
    MMI_PHB_RETURN_MAX                 = 9
};

typedef s32 MmiPhbReturn_e;


enum
{
    MMI_PHB_RESULT_OK = 0
   ,MMI_PHB_RESULT_NOT_READY = 1
   ,MMI_PHB_FOLDER_NOT_FOUND = 2
   ,MMI_PHB_RESULT_RECORD_NOT_FOUND = 3
   ,MMI_PHB_RESULT_RECORD_FULL = 4
   ,MMI_PHB_RESULT_MEMORY_FULL = 5
   ,MMI_PHB_RESULT_FAILED = 6
   ,MMI_PHB_IMPORT_PARTIAL = 7
   ,MMI_PHB_RESULT_FILE_EXISTS = 8
   ,MMI_PHB_RESULT_NUMBER_EMPTY = 9     // all number are empty
   ,MMI_PHB_RESULT_NUMBER_INVALID = 10	// one of the number contains invalid char
   ,MMI_PHB_RESULT_NO_FREE_EMAIL = 11   // All email slots are used
   ,MMI_PHB_RESULT_NO_FREE_EXT = 12     // All extension number slots are used
   ,MMI_PHB_RESULT_MAX = 12
};

typedef s32 MmiPhbResult_e;


enum
{
    MMI_PHB_BOOK_TYPE_UNKNOWN = 0
   ,MMI_PHB_BOOK_TYPE_ECC = 1
  , //Emergency Call Code
    MMI_PHB_BOOK_TYPE_ADN_M = 2
  , //Query Master Sim data
    MMI_PHB_BOOK_TYPE_ADN_S = 3
  , //Query Slave Sim data
    MMI_PHB_BOOK_TYPE_ADN_M_ADN_S = 4
  , //Query Master/Slave Sim data
    MMI_PHB_BOOK_TYPE_FDN = 5
  , //Query Fixed Dialing Number
    MMI_PHB_BOOK_TYPE_BDN = 6
   ,MMI_PHB_BOOK_TYPE_LDN = 7
  , //Last Dialed Number. It is stored in handset flash.
    MMI_PHB_BOOK_TYPE_LRN = 8
  , //Last Received Number. It is stored in handset flash.
    MMI_PHB_BOOK_TYPE_LMN = 9
  , //Last Missed Number. It is stored in handset flash.
    MMI_PHB_BOOK_TYPE_LXN = 10
   ,MMI_PHB_BOOK_TYPE_SDN = 11
  , //Service Dialing Number. It is stored in SIM card.
    MMI_PHB_BOOK_TYPE_MSISDN = 12
  , //Mobile Station international ISDN Number.It is stored in SIM card. Usually it is named ¡§Own Number¡¨ or ¡§My Number¡¨.
    MMI_PHB_BOOK_TYPE_MBX = 13
  , // Mail Box Number. Store dialing numbers to be used for voice message retrieval form mailboxes.

    /*
    ADR is similar to ADN.
    The differences are:
    (1) ADR is stored in handset flash.
    (2) the elements of an ADR record are variety and project dependent.
    */
    MMI_PHB_BOOK_TYPE_ADR = 14
  , MMI_PHB_BOOK_TYPE_ADR_ADN_M = 15
  , //ADR Master
    MMI_PHB_BOOK_TYPE_ADR_ADN_S = 16
  , //ADR Slave
    MMI_PHB_BOOK_TYPE_ADR_ADN_M_ADN_S = 17
  , //ADR Master & Slave

    MMI_PHB_BOOK_TYPE_BCARD = 18
#ifndef __MMI_PHB_DISABLE_BLACKLIST__	    
  , MMI_PHB_BOOK_TYPE_BKLIST = 19
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__	  
  , // blacklist
   MMI_PHB_BOOK_TYPE_QUERY_ADN_M = 20
  ,MMI_PHB_BOOK_TYPE_QUERY_ADN_S = 21
  , // Special case for query SIM email and ext-num information
   MMI_PHB_BOOK_TYPE_MAX = 21,
};

typedef s32 MmiPhbBookType_e;


enum
{
    MMI_PHB_GROUP_UNKNOWN = 0
   ,MMI_PHB_GROUP_CG_START = 1
   ,/*
        MMI_PHB_GROUP_CG01          = 1,
        MMI_PHB_GROUP_CG02          = 2,
        MMI_PHB_GROUP_CG03          = 3,
        MMI_PHB_GROUP_CG04          = 4,
        MMI_PHB_GROUP_CG05          = 5,
        MMI_PHB_GROUP_CG06          = 6,
        MMI_PHB_GROUP_CG07          = 7,
        MMI_PHB_GROUP_CG08          = 8,
        MMI_PHB_GROUP_CG09          = 9,
        MMI_PHB_GROUP_CG10          = 10,
        MMI_PHB_GROUP_CG11          = 11,
        MMI_PHB_GROUP_CG12          = 12,
        MMI_PHB_GROUP_CG13          = 13,
        MMI_PHB_GROUP_CG14          = 14,
        MMI_PHB_GROUP_CG15          = 15,
        MMI_PHB_GROUP_CG16          = 16,
        MMI_PHB_GROUP_CG17          = 17,
        MMI_PHB_GROUP_CG18          = 18,
        MMI_PHB_GROUP_CG19          = 19,
        MMI_PHB_GROUP_CG20          = 20,
        MMI_PHB_GROUP_CG21          = 21,
        MMI_PHB_GROUP_CG22          = 22,
        MMI_PHB_GROUP_CG23          = 23,
        MMI_PHB_GROUP_CG24          = 24,
        MMI_PHB_GROUP_CG25          = 25,
        MMI_PHB_GROUP_CG26          = 26,
        MMI_PHB_GROUP_CG27          = 27,
        MMI_PHB_GROUP_CG28          = 28,
        */
#ifdef __APP_MMI_SMALLROM__
    MMI_PHB_GROUP_CG_END = 10
#else //__APP_MMI_SMALLROM__
    MMI_PHB_GROUP_CG_END = 28
#endif //__APP_MMI_SMALLROM__
   //,MMI_PHB_GROUP_BLACK_LIST = 29
   ,MMI_PHB_GROUP_URL = 30
   ,MMI_PHB_GROUP_EMAIL = 31
   
   ,MMI_PHB_GROUP_MAX = MMI_PHB_GROUP_CG_END
};

typedef s32 MmiPhbGroup_e;

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__


/*
 *  IMPORTMENT!!!!!!!!!!!!!!
 *  if you add any item to MmiPhbContactContent_t, you need to update this enum!!!!!!!!
 *  please read the mmi_phb_utility.c:MMI_PHB_UTIL_COPY_ITEM_TO_CONTACT
 *                                                  by Cosmo
 */

// format : definelen+2+1, 2 for '"', one for ','
#define MMI_PHB_CONTACT_CSV_BUF_SIZE ((MMI_PHB_NAME_LEN+2+1)+(MMI_PHB_NUMBER_LEN+1+1+2)*MMI_PHB_NUMBER_MAX +\
                                    (MMI_PHB_COMPANY_LEN+2+1)+(MMI_PHB_DEPARTMENT_LEN+2+1)+(MMI_PHB_POSITION_LEN+2+1)+\
                                    (MMI_PHB_HOME_ADDRESS_LEN+2+1)+(MMI_PHB_OFFICE_ADDRESS_LEN+2+1)+(MMI_PHB_EMAIL_LEN+2+1)+\
                                    (MMI_PHB_URL_LEN+2+1)+(MMI_PHB_NOTE_LEN+2+1)+10*3+((2*6)+2+1))
enum
{
	MMI_PHB_CSV_CONTACT_NAME		= 0,
	MMI_PHB_CSV_CONTACT_NUMBER1,
#ifndef __SMALL_PHB_MMI__
	MMI_PHB_CSV_CONTACT_NUMBER2,

	MMI_PHB_CSV_CONTACT_COMPANYNAME,

	MMI_PHB_CSV_CONTACT_EMAIL,

	MMI_PHB_CSV_CONTACT_NUMBER3,

	MMI_PHB_CSV_CONTACT_NUMBER4,

	MMI_PHB_CSV_CONTACT_BIRTHDAY,

	// the above is for other phone compatible 

	MMI_PHB_CSV_CONTACT_DEPARTMENT,

	MMI_PHB_CSV_CONTACT_POSITION,

	MMI_PHB_CSV_CONTACT_HOMEADR,  

	//MMI_PHB_CSV_CONTACT_OFFICEADR, // not support

	MMI_PHB_CSV_CONTACT_URL,

	MMI_PHB_CSV_CONTACT_NOTE,

	//MMI_PHB_CSV_CONTACT_IMAGEIDX,  // not support

	//MMI_PHB_CSV_CONTACT_RINGTONEIDX,  // not support

	//MMI_PHB_CSV_CONTACT_GROUPID,  // not support

	MMI_PHB_CSV_CONTACT_MAX = MMI_PHB_CSV_CONTACT_NOTE
#else
    MMI_PHB_CSV_CONTACT_MAX = MMI_PHB_CSV_CONTACT_NUMBER1
#endif // __SMALL_PHB_MMI__

};

typedef s32 MMI_PHB_CONTACT_ITEM_ID_E;

#endif // __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

enum
{
    MMI_PHB_NUMBER_TYPE_MOBILE = 0
#ifndef __SMALL_PHB_MMI__        
   ,MMI_PHB_NUMBER_TYPE_HOME = 1
   ,MMI_PHB_NUMBER_TYPE_OFFICE = 2
   ,MMI_PHB_NUMBER_TYPE_OTHER = 3
   ,MMI_PHB_NUMBER_TYPE_MAX = 3
#else
    ,MMI_PHB_NUMBER_TYPE_MAX = 0
#endif    
};

typedef s32 MmiPhbNumberType_e;

/************************************************************************/
/* PHB Function Type                                                                  */
/************************************************************************/
enum
{
    PHB_SRV_FID_NONE = 0
   ,PHB_SRV_FID_QUERY_STATUS = 1
   ,PHB_SRV_FID_READ_ONE_BY_SORTING = 2
   ,PHB_SRV_FID_READ_ONE_BY_PHYSICAL = 3
   ,PHB_SRV_FID_READ_MULTI_BY_SORTING = 4
   ,PHB_SRV_FID_READ_MULTI_BY_PHYSICAL = 5
   ,PHB_SRV_FID_WRITE_ONE_NEW = 6
   ,PHB_SRV_FID_WRITE_ONE_BY_PHYSICAL = 7
   ,PHB_SRV_FID_WRITE_MULTI_NEW = 8
   ,PHB_SRV_FID_WRITE_MULTI_BY_PHYSICAL = 9
   ,PHB_SRV_FID_COPY_ONE_BY_PHYSICAL = 10
   ,PHB_SRV_FID_COPY_MULTI_BY_PHYSICAL = 11
   ,PHB_SRV_FID_COPY_ONE_BY_SORTING = 12
   ,PHB_SRV_FID_COPY_MULTI_BY_SORTING = 13
   ,PHB_SRV_FID_COPY_ALL = 14
   ,PHB_SRV_FID_DELETE_ONE_BY_PHYSICAL = 15
   ,PHB_SRV_FID_DELETE_MULTI_BY_PHYSICAL = 16
   ,PHB_SRV_FID_DELETE_ONE_BY_SORTING = 17
   ,PHB_SRV_FID_DELETE_MULTI_BY_SORTING = 18
   ,PHB_SRV_FID_DELETE_ALL = 19
   ,PHB_SRV_FID_SEARCH_BY_NAME = 20
   ,PHB_SRV_FID_SEARCH_BY_NUMBER = 21
   ,PHB_SRV_FID_READ_CALL_BY_SORTING = 22
   ,PHB_SRV_FID_WRITE_CALL_BY_SORTING = 23
   ,PHB_SRV_FID_IMPORT_CONTACT = 24
   ,PHB_SRV_FID_EXPORT_CONTACT = 25
   ,PHB_SRV_FID_MAX = 25
};

typedef s32 MmiPhbSrvFunId_e;

/*
    Constant
*/

enum
{
    MMI_PHB_ADN_SUPPORT_MAX = 255
   ,MMI_PHB_TOTAL_SUPPORT_MAX = (MMI_PHB_ADR_SUPPORT_MAX+2*MMI_PHB_ADN_SUPPORT_MAX) // 1510
   ,MMI_PHB_SIM_NAME_LEN = 31
   ,MMI_PHB_SIM_NUMBER_LEN = 40
   ,MMI_PHB_TEXT_MAX = 100
#ifndef __SMALL_PHB_MMI__     
   ,MMI_PHB_NUMBER_MAX = 4                  /* The maximum number per contact. */
#else
   ,MMI_PHB_NUMBER_MAX = 1  
#endif
   ,MMI_PHB_MULTI_READ_MAX = 6
   ,MMI_PHB_MULTI_WRITE_MAX = 6
   ,MMI_PHB_COPY_WRITE_MAX = 6
   ,MMI_PHB_NUMBER_ITEM_IN_CONTACT = 11
   ,MMI_PHB_MAX_COMPARE_LEN = 20            /* The maximum length of compare string, for PinYin. */
   ,MMI_PHB_MULTI_WORD_PREFIX_MAX = 8       /* The maximum length of compare string, for multiple words prefix. */

#ifdef __UNICODE_TO_STROKE__
   ,MMI_PHB_MAX_NAME_STROKE_LEN    = 20        /* The maximum length of name's stroke. */
   ,MMI_PHB_MWP_STROKE_MAX            = 8        /* The maximum length of multiple words prefix, for stroke. */
#endif

   ,MMI_PHB_CHECK_VALUE_START = 20001
   ,MMI_PHB_ADD_CONTACT_SAFE_SIZE = 1024    /* Contact's maximum size. */
#ifndef __MMI_PHBAP_DISABLE_GROUP__
   ,MMI_PHB_ADD_GROUP_SAFE_SIZE = MMI_PHB_GROUP_CG_END * 88 + 1     /* The size of all group's properties. 88 = sizeof(MmiPhbGroupContent_t) */
#endif   
   ,MMI_PHB_TIME_TO_KICK_WATCHDOG    = 50
   ,MMI_PHB_SELECT_FILES_MAX = 300      /* The maximum when select files from FileMgr. */
#ifdef __MMI_PHB_SUPPORT_CONTACT_CHANGED_NOTIFY__
   ,MMI_PHB_CONTACT_CHANGED_NOTIFY_MAX = 200 /* used for notify contact changed. If number of changed contacts is larger than this, we only notify number instead of MmiPhbContactChangedInfo_t */
#endif
};

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

enum
{
    MMI_PHB_EXPORT_IMPORT_NONE
   ,MMI_PHB_EXPORT_IMPORT_SUSPEND
   ,MMI_PHB_EXPORT_IMPORT_PROCESS
};
typedef u8 MmiPhbExportImportStatus_e;

enum
{
    MMI_PHB_EXPORT_ACTION
   ,MMI_PHB_IMPORT_ACTION
};
typedef u8 MmiPhbActionType_e;

enum
{
	MMI_PHB_EXPORT_FORMAT_PHB = 0,
#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
	MMI_PHB_EXPORT_FORMAT_CSV,
#endif
};

enum
{
	MMI_PHB_CSV_TYPE_MSTAR = 0, // UTF16, separate by tab
	MMI_PHB_CSV_TYPE_MSTAR_OLD,
	MMI_PHB_CSV_TYPE_OLD,    // separate by ',' , 8 column
	MMI_PHB_CSV_TYPE_NEW_8,    // separate by tab, 8 column
	MMI_PHB_CSV_TYPE_NEW_2,    // separate by tab, 2 column
};

#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

enum
{
    MMI_PHB_EXPORTTYPE_GENERIC,
    MMI_PHB_EXPORTTYPE_BT,
    MMI_PHB_EXPORTTYPE_PLAINTEXT,
#ifdef __PHB_SEND_MULTI_VCARD_BY_BT__
    MMI_PHB_EXPORTTYPE_MULTI_BT,
#endif
};
typedef u8 MmiPhbExportType_e;

enum
{
    MMI_PHB_SEARCH_UNICODE            = 0x0001,
    MMI_PHB_SEARCH_PINYIN_ABC        = 0x0002,    /* Not support yet. */
//    MMI_PHB_SEARCH_PINYIN_KEY        = 0x0004,    /* Not support yet. */
    MMI_PHB_SEARCH_PINYIN_MWP_ABC    = 0x0008,
//    MMI_PHB_SEARCH_PINYIN_MWP_KEY    = 0x0010,    /* Not support yet. */

#ifdef __UNICODE_TO_STROKE__
    MMI_PHB_SEARCH_STROKE_KEY        = 0x0020,
    MMI_PHB_SEARCH_STROKE_MWP_KEY    = 0x0040,
#endif

#ifdef __MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__
    MMI_PHB_SEARCH_SMART_ALPHABET = 0x0080,
    MMI_PHB_SEARCH_SMART_ALPHABET_MWP = 0x0100,
#endif

#ifdef __MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__
    MMI_PHB_SEARCH_SMART_NUMBER = 0x0200,
#endif

//    MMI_PHB_SEARCH_ALL                = 0xFFFF    /* Not support yet. */
};
typedef u16 MMI_PHB_SEARCH_TYPE_E;

enum
{
    MMI_PHB_CONTACT_COMPANYNAME = 0
   ,MMI_PHB_CONTACT_DEPARTMENT
   ,MMI_PHB_CONTACT_POSITION
   ,MMI_PHB_CONTACT_HOMEADR
   ,MMI_PHB_CONTACT_OFFICEADR
   ,MMI_PHB_CONTACT_EMAIL
   ,MMI_PHB_CONTACT_URL
   ,MMI_PHB_CONTACT_NOTE
   ,MMI_PHB_CONTACT_MAX = MMI_PHB_CONTACT_NOTE
};

typedef s32 MmiPhbContactItemDataID_e;

typedef enum
{
    MMI_PHB_EXPORT_CARD = STORAGE_CARD,
    MMI_PHB_EXPORT_CARD2 = STORAGE_CARD2,
    MMI_PHB_EXPORT_PHONE = STORAGE_PHONE
}MmiPhbExportPath_e;

#ifdef __3G_RIL_MMI__
typedef enum
{	
    MMI_PHB_TON_NOT_HIDDEN	= 0,	
	MMI_PHB_TON_HIDDEN	= 1,
	MMI_PHB_TON_NO_NUMBER  = 0xFF
} MMI_PHB_USIM_HIDDEN_MODE_E;
#endif //#ifdef __3G_RIL_MMI__

typedef enum
{
    MMI_PHB_FUZZY_TYPE_NONE = 0,
    MMI_PHB_FUZZY_TYPE_NUMBER,
    MMI_PHB_FUZZY_TYPE_DIGIT_TO_ALPHABET,
    MMI_PHB_FUZZY_TYPE_BOTH
}MmiPhbSrvFuzzySearchType_e;

/************************************************************************/
/* Data Structure:
        Request & Confirmation
*/
/************************************************************************/

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbQueryPhbStatusReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbMaxContacts;
    u16 u16PhbUsedContacts;
    u16 u16PhbAvailContacts;
    u16 u16PhbMaxExtNum;
    u16 u16PhbUsedExtNum;
    u8 u8PhbMaxNameLen;
    u8 u8PhbMaxNumberLen;
#ifndef __SMALL_PHB_MMI__    
#ifdef __3G_RIL_MMI__
    u16 u16PhbMaxEmailNum;
    u16 u16PhbUsedEmailNum;
    u8 u8PhbMailLen; 
    // Though USIM may support multiple email, but we just support one at this time since most phone don't support multiple mail
    // If the value is 0, it means the SIM doesn't support email.
#endif //__3G_RIL_MMI__
#endif // #ifndef __SMALL_PHB_MMI__
} MmiPhbQueryPhbStatusCnf_t;

typedef struct
{
    u8 u8NameLen;
    u8 au8Name[MMI_PHB_NAME_LEN];
} MmiPhbName_t;             /* 42 bytes */

typedef struct
{
    u8 u8NumberLen;
    u8 au8Number[MMI_PHB_NUMBER_LEN];
    MmiPhbNumberType_e s32NumberType;
} MmiPhbNumber_t;           /* 45 bytes */

typedef struct
{
    u8 u8EmailLen;
    u8 au8Email[MMI_PHB_EMAIL_LEN];
} MmiPhbEmail_t;            /* 101 bytes */

#ifndef __SMALL_PHB_MMI__ 

typedef struct
{
    u8 u8CompanyLen;
    u8 au8Company[MMI_PHB_COMPANY_LEN];
} MmiPhbCompany_t;          /* 41 bytes */

typedef struct
{
    u8 u8DepartmentLen;
    u8 au8Department[MMI_PHB_DEPARTMENT_LEN];
} MmiPhbDepartment_t;       /* 41 bytes */

typedef struct
{
    u8 u8PositionLen;
    u8 au8Position[MMI_PHB_POSITION_LEN];
} MmiPhbPosition_t;         /* 41 bytes */

typedef struct
{
    u8 u8HomeAddressLen;
    u8 au8HomeAddress[MMI_PHB_HOME_ADDRESS_LEN];
} MmiPhbHomeAddress_t;      /* 101 bytes */

typedef struct
{
    u8 u8OfficeAddressLen;
    u8 au8OfficeAddress[MMI_PHB_OFFICE_ADDRESS_LEN];
} MmiPhbOfficeAddress_t;    /* 101 bytes */

typedef struct
{
    u8 u8UrlLen;
    u8 au8Url[MMI_PHB_URL_LEN];
} MmiPhbUrl_t;              /* 101 bytes */

typedef struct
{
    u8 u8NoteLen;
    u8 au8Note[MMI_PHB_NOTE_LEN];
} MmiPhbNote_t;             /* 101 bytes */

typedef struct
{
    u8 au8Year[2];
    u8 au8Month[2];
    u8 au8Day[2];
    u8 au8Hour[2];
    u8 au8Minute[2];
    u8 au8Second[2];
} MmiPhbDateTime_t;         /* 12 bytes */

#endif // #ifndef __SMALL_PHB_MMI__ 

/* if modify the following structure - MmiPhbContactContent_t , you must modify MMI_PHB_DH_WriteContactContent and MMI_PHB_DH_ReadContactContent in mmi_phb_data_handle.c */
typedef struct
{
    MmiPhbName_t tPhbName;
    MmiPhbNumber_t tPhbNumber[MMI_PHB_NUMBER_MAX];
#ifndef __SMALL_PHB_MMI__     
    MmiPhbCompany_t tPhbCompanyName;
    MmiPhbDepartment_t tPhbDepartment;
    MmiPhbPosition_t tPhbPosition;
    MmiPhbHomeAddress_t tPhbHomeAddress;
    MmiPhbOfficeAddress_t tPhbOfficeAddress;
    MmiPhbEmail_t tPhbEmail;
    MmiPhbUrl_t tPhbUrl;
    MmiPhbNote_t tPhbNote;
#endif    
    u32 u32PhbImageIdx;
    u32 u32PhbRingtoneIdx;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    u32 u32PhbVideotoneIdx;
#endif

#ifndef __SMALL_PHB_MMI__ 
    MmiPhbDateTime_t tPhbBirthday;
#endif
    u32 u32PhbFilter;
    boolean bIsPreNum;
#ifdef __UNICODE_TO_STROKE__
    u8 u8NameStroke[MMI_PHB_MAX_NAME_STROKE_LEN+1];
    u8 u8MWPStroke[MMI_PHB_MWP_STROKE_MAX+1];
#endif
} MmiPhbContactContent_t;   /* 946 bytes */

typedef struct
{
    MmiPhbName_t tPhbName;
    MmiPhbNumber_t tPhbNumber;
#ifdef __MMI_PHB_BK_WITH_SORTING__
#ifdef __UNICODE_TO_STROKE__
    u8                        u8NameStroke[MMI_PHB_MAX_NAME_STROKE_LEN+1];
    u8                        u8MWPStroke[MMI_PHB_MWP_STROKE_MAX+1];
#endif
#endif // #ifdef __MMI_PHB_BK_WITH_SORTING__
} MmiPhbBlackListMemberContent_t;   /* 946 bytes */

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbSortingIdx;
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbReadOneContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Sorting;
    MmiPhbBookType_e s32PhbBookType_Physical;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbReadOneContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbPhysicalIdx;
} MmiPhbReadOneContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbReadOneContactByPhysicalIdxCnf_t;

typedef struct
{
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbSortingIdx;
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbReadPartialBySortingIdxReq_t;

typedef struct
{
    MmiPhbName_t tPhbName;
    MmiPhbNumber_t tPhbNumber[MMI_PHB_NUMBER_MAX];

    u32 u32Filter;  /*
                                        bit 31 30 29 ~ 10 9 8 7 6 5 4 3 2 1 0
                                        bit 0       : Reserve
                                        bit 1~28    : for normal group
                                        bit 29      : for caller group Black List
                                        bit 30      : indicate the contact has url
                                        bit 31      : indicate the contact has email
                                    */
    boolean bIsPreNum;
} MmiPhbReadPartialBySortingIdxCnf_t;   /* 94 bytes */

typedef struct
{
    u16 u16PhbBlackListRaiIdx;
} MmiPhbReadBlackListByRaiIdxReq_t;

typedef struct
{
    MmiPhbName_t tPhbName;
    MmiPhbNumber_t tPhbNumber;       //only one number
} MmiPhbReadBlackListByRaiIdxCnf_t; /* 94 bytes */

typedef struct
{
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbNumber_t tPhbNumber;
} MmiPhbGetNameByNumberReq_t;

typedef struct
{
    MmiPhbName_t tPhbName;
} MmiPhbGetNameByNumberCnf_t;

typedef struct
{
    MmiPhbBookType_e s32PhbBookType_Sorting;
    MmiPhbBookType_e s32PhbBookType_Physical;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbMultiContactContent_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 au16PhbSortingIdx[MMI_PHB_MULTI_READ_MAX];
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbReadMultiContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbMultiContactContent_t atPhbMultiContactContent[MMI_PHB_MULTI_READ_MAX];
} MmiPhbReadMultiContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 au16PhbPhysicalIdx[MMI_PHB_MULTI_READ_MAX];
} MmiPhbReadMultiContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbMultiContactContent_t atPhbMultiContactContent[MMI_PHB_MULTI_READ_MAX];
} MmiPhbReadMultiContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbContactContent_t tPhbContactContent;
} MmiPhbWriteOneNewContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbWriteOneNewContactCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbContactContent_t tPhbContactContent[MMI_PHB_MULTI_WRITE_MAX];
} MmiPhbWriteMultiNewContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    u16 au16PhbSortingIdx[MMI_PHB_MULTI_WRITE_MAX];
    u16 au16PhbPhysicalIdx[MMI_PHB_MULTI_WRITE_MAX];
} MmiPhbWriteMultiNewContactCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbPhysicalIdx;
} MmiPhbWriteOneContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbWriteOneContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbContactContent_t tPhbContactContent[MMI_PHB_MULTI_WRITE_MAX];
    u16 au16PhbPhysicalIdx[MMI_PHB_MULTI_WRITE_MAX];
} MmiPhbWriteMultiContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType;
    u16 au16PhbSortingIdx[MMI_PHB_MULTI_WRITE_MAX];
    u16 au16PhbPhysicalIdx[MMI_PHB_MULTI_WRITE_MAX];
} MmiPhbWriteMultiContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType_Source;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 u16PhbPhysicalIdx_Source;
} MmiPhbCopyOneContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 u16PhbSortingIdx_Destination;
    u16 u16PhbPhysicalIdx_Destination;
} MmiPhbCopyOneContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType_Source;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 u16PhbSortingIdx_Source;
} MmiPhbCopyOneContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 u16PhbSortingIdx_Destination;
    u16 u16PhbPhysicalIdx_Destination;
} MmiPhbCopyOneContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType_Source;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 au16PhbPhysicalIdx_Source[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbCopyMultiContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 au16PhbSortingIdx_Destination[MMI_PHB_COPY_WRITE_MAX];
    u16 au16PhbPhysicalIdx_Destination[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbCopyMultiContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType_Source;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 au16PhbSortingIdx_Source[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbCopyMultiContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Destination;
    u16 au16PhbSortingIdx_Destination[MMI_PHB_COPY_WRITE_MAX];
    u16 au16PhbPhysicalIdx_Destination[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbCopyMultiContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType_Source;
    MmiPhbBookType_e s32PhbBookType_Destination;
} MmiPhbCopyAllContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbCopyAllContactCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbPhysicalIdx;
} MmiPhbDeleteOneContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbDeleteOneContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbSortingIdx;
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbDeleteOneContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbDeleteOneContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 u16PhbPhysicalIdx[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbDeleteMultiContactByPhysicalIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbDeleteMultiContactByPhysicalIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    u16 au16PhbSortingIdx[MMI_PHB_COPY_WRITE_MAX];
} MmiPhbDeleteMultiContactBySortingIdxReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbDeleteMultiContactBySortingIdxCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
} MmiPhbDeleteAllContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbDeleteAllContactCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbName_t tPhbSearchName;
} MmiPhbSearchContactByNameReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Sorting;
    MmiPhbBookType_e s32PhbBookType_Physical;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbSearchContactByNameCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbNumber_t tPhbSearchNumber;
    boolean bIsNeedFullContent;
} MmiPhbSearchContactByNumberReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
    MmiPhbBookType_e s32PhbBookType_Sorting;
    MmiPhbBookType_e s32PhbBookType_Physical;
    MmiPhbContactContent_t tPhbContactContent;
    u16 u16PhbSortingIdx;
    u16 u16PhbPhysicalIdx;
} MmiPhbSearchContactByNumberCnf_t;


typedef struct
{
	u16     u16PhysicalIdx;
	u16     u16SortNum;				/* For filter sorting. */
	u16     u16NumIndex;
	u16     u16TotalSortingIdx;		/* Sorting index that without input any search string. */
} MmiPhbSearchResultForNum_t;				/* For Multiple Word Prefix Search. */

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbGroup_e s32PhbGroup;
    boolean bIsInit;

    FileMgr_Stream_t *pIFStream;
    u16 u16ExportImportCounter;
    MmiPhbContactContent_t *ptContactContent;       /* Store contact's content for mode transition. */

    u8 *pu8LineBuf; //The buffer to store string for one contact
    u8 *pu8ContactStringBuf; //The buffer for reading VCARD file.
    u32 u32ContactStringBufSize; //The size of the data in the buffer.

    MmiPhbResult_e s32PhbErrorReturn;
    VectorClass_t *pIDList;
	u8		u8ExportFormat;
	u8		u8CSVType;
	u8  	u8IsUCS2;
    boolean bIsNeedStopWriteSoftTable;

    boolean bIsCheckContactWithSameName;
    u16 u16StartSortingIdx; //The start sorting index for a contact name
    u16 u16TargetContactCount; //The counter for contacts with the same name

	boolean bIsNumberEmpty;	/* When any contact's number is empty, will set it to TRUE to show error message. */
} MmiPhbImportContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbResult_e s32PhbResult;
} MmiPhbImportContactCnf_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbGroup_e s32PhbGroup;
    MmiPhbExportType_e eExportType;
    boolean bIsInit;

    FileMgr_Stream_t *pIFStream;
    u16 u16ExportImportCounter;
    MmiPhbContactContent_t *ptContactContent;       /* Store contact's content for mode transition. */
    u32 u32UsedSpace;

    boolean bIsFull;
    u16 u16PhbUsedContacts;
    u16 u16CurContactIdx;

    void *pu16ExportData;

    MmiPhbResult_e s32PhbErrorReturn;
    VectorClass_t *pIDList;
    MmiPhbExportPath_e eExportPath;
	u8				u8ExportFormat; // phb or csv
#ifdef __PHB_SEND_MULTI_VCARD_BY_BT__
	u16 u16ExportFileUrlIndCount;
#endif
} MmiPhbExportContactReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbGroup_e s32PhbGroup;
} MmiPhbExportContactCnf_t;
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

//#ifndef __MMI_PHBAP_DISABLE_GROUP__
typedef struct
{
    MmiPhbGroup_e s32PhbGroup;
    MmiPhbName_t tPhbName;
    u32 u32PhbImageIdx;
    u32 u32PhbRingtoneIdx;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    u32 u32PhbVideotoneIdx;
#endif
} MmiPhbGroupContent_t; /* 88 bytes */

typedef struct
{
    MmiPhbGroupContent_t atPhbGroups[MMI_PHB_GROUP_CG_END];

    u8 u8GroupCnt;
} MmiPhbGroups_t;
//#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__

typedef struct
{
    MAE_WChar wcFirstChar;
    u16 u16PhbSortingIdx;
    u8 u8Alphabet;
} MmiPhbBJX_t;  /* For Bia Jia Xing. */


/*
    Modify this structure need modify MmiPhbDhSortByNameTable_t (in mmi_phb_data_handle.h) at the same time.
*/
typedef struct
{
    u16 u16PhysicalIdx;
    u16 u16SortNum;             /* For filter sorting. */
    u16 u16TotalSortingIdx;     /* Sorting index that without input any search string. */
    u16    u16AllSortingIdx;        /* Sorting index of ADR_ADN_M_ADN_S without book type and group. */
} MmiPhbSearchResult_t;             /* For Multiple Word Prefix Search. */

#ifdef __NAND_MMI__
typedef struct
{
     u16 u16PhysicalIdx;
} MmiPhbDefaultContact_t; /* default contact's physical index (For PreNumList)   2020-08-05   Modify by John & Robin */
typedef struct
{
    MmiPhbNumber_t    tPhbNumber[MMI_PHB_NUMBER_MAX];
} MmiPhbAllNumbers_t;            /* 180 bytes */

#ifdef __UNICODE_TO_STROKE__
typedef struct
{
    u8                u8NameStroke[MMI_PHB_MAX_NAME_STROKE_LEN+1];
    u8                u8MWPStroke[MMI_PHB_MWP_STROKE_MAX+1];
} MmiPhbStroke_t;            /* 30 bytes */
#endif /* __UNICODE_TO_STROKE__ */
#endif /* __NAND_MMI__ */


typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbBookType_e s32PhbBookType;
    MAE_WChar *pImportFilePath;
    VectorClass_t *pIDList;
} MmiPhbSrvImportReq_t;

typedef struct
{
    u32 u32PhbCheckValue;
    MmiPhbExportType_e eExportType;
    MmiPhbBookType_e s32PhbBookType;
    MmiPhbGroup_e s32PhbActionGroup;
    VectorClass_t *pIDList;
    MmiPhbExportPath_e eExportPath;
	u8	u8ExportFormat; // phb or csv
} MmiPhbSrvExportReq_t;

#ifdef __3G_RIL_MMI__
typedef struct
{
	u32	u8MailLen;
    u8 au8Mail[MMI_PHB_USIM_MAIL_LEN];
} MMI_PHB_REQ_MAIL_t;

typedef struct
{
	u32	u8GroupLen;
    u8 au8Group[MMI_PHB_USIM_GROUP_LEN];
} MMI_PHB_REQ_GROUP_t;
#endif //__3G_RIL_MMI__

#ifdef __MMI_PHB_SUPPORT_CONTACT_CHANGED_NOTIFY__
typedef struct
{
    u16 u16PhysicalIdx;
    MmiPhbNumber_t tPhbNumber;
} MmiPhbContactChangedInfo_t;

typedef struct
{
    u16 u16TotalNum;
    MmiPhbContactChangedInfo_t *patChangedInfo;
} MmiPhbContactChangedNotifyData_t;
#endif // #ifdef __MMI_PHB_SUPPORT_CONTACT_CHANGED_NOTIFY__
#endif /* __MMI_PHBSRV_DEF_H__ */

