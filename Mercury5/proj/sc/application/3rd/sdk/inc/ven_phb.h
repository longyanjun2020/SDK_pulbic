#ifndef __VEN_PHB_H_
#define __VEN_PHB_H_
/********************************************************************************/
/*  File : ven_phb.h                                                            */
/*  Scope: The definition of the data structure or enum for phb related messages*/
/********************************************************************************/

#include "ven_sdk.h"

#define VEN_PHB_ADR_SUPPORT_MAX		2000
#define VEN_PHB_NAME_LEN			41  
#define VEN_PHB_NUMBER_LEN			40
#define VEN_PHB_COMPANY_LEN			40
#define VEN_PHB_DEPARTMENT_LEN		40
#define VEN_PHB_POSITION_LEN		40
#define VEN_PHB_HOME_ADDRESS_LEN	100
#define VEN_PHB_OFFICE_ADDRESS_LEN	100
#define VEN_PHB_EMAIL_LEN			100
#define VEN_PHB_URL_LEN				100
#define VEN_PHB_NOTE_LEN			100

typedef void *ven_phb_handle;

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_PHB_ADN_SUPPORT_MAX = 255
   ,VEN_PHB_TOTAL_SUPPORT_MAX = (VEN_PHB_ADR_SUPPORT_MAX+2*VEN_PHB_ADN_SUPPORT_MAX) // 1510
   ,VEN_PHB_SIM_NAME_LEN = 31
   ,VEN_PHB_SIM_NUMBER_LEN = 30
   ,VEN_PHB_TEXT_MAX = 100
   ,VEN_PHB_NUMBER_MAX = 4                  /* The maximum number per contact. */
   ,VEN_PHB_MULTI_READ_MAX = 6
   ,VEN_PHB_MULTI_WRITE_MAX = 6
   ,VEN_PHB_COPY_WRITE_MAX = 6
   ,VEN_PHB_NUMBER_ITEM_IN_CONTACT = 11
   ,VEN_PHB_MAX_COMPARE_LEN = 20            /* The maximum length of compare string, for PinYin. */
   ,VEN_PHB_MULTI_WORD_PREFIX_MAX = 8       /* The maximum length of compare string, for multiple words prefix. */

#ifdef __UNICODE_TO_STROKE__
   ,VEN_PHB_MAX_NAME_STROKE_LEN    = 20        /* The maximum length of name's stroke. */
   ,VEN_PHB_MWP_STROKE_MAX            = 8        /* The maximum length of multiple words prefix, for stroke. */
#endif

   ,VEN_PHB_CHECK_VALUE_START = 20001
   ,VEN_PHB_ADD_CONTACT_SAFE_SIZE = 1024    /* Contact's maximum size. */
   ,VEN_PHB_ADD_GROUP_SAFE_SIZE = 2560      /* The size of all group's properties. */
   ,VEN_PHB_TIME_TO_KICK_WATCHDOG    = 50

#ifdef __NAND_MMI__
    ,VEN_PHB_MAX_RAI_ONE_PARTITION_SIZE    = 29696    /* 29k for one rai partition */
#else
   ,VEN_PHB_MAX_RAI_ONE_PARTITION_SIZE = 10240     /* 10k for one partition */
#endif

   ,VEN_PHB_MAX_RAI_PARTITION = 19      /* Partition the sorting table */

   ,VEN_PHB_SELECT_FILES_MAX = 300      /* The maximum when select files from FileMgr. */
};

enum
{
    VEN_PHB_RET_SUCCESS = 0,
    VEN_PHB_RET_BAD_PARAM,
    VEN_PHB_RET_OUT_OF_MEMORY,
    VEN_PHB_RET_FAILED
};
typedef u32 ven_phb_ret_t;

enum
{
    VEN_PHB_RESULT_OK = 0
   ,VEN_PHB_RESULT_NOT_READY = 1
   ,VEN_PHB_FOLDER_NOT_FOUND = 2
   ,VEN_PHB_RESULT_RECORD_NOT_FOUND = 3
   ,VEN_PHB_RESULT_RECORD_FULL = 4
   ,VEN_PHB_RESULT_MEMORY_FULL = 5
   ,VEN_PHB_RESULT_FAILED = 6
   ,VEN_PHB_IMPORT_PARTIAL = 7
   ,VEN_PHB_RESULT_FILE_EXISTS = 8
   ,VEN_PHB_RESULT_NUMBER_EMPTY        = 9      /// all number are empty
   ,VEN_PHB_RESULT_NUMBER_INVALID    = 10  /// one of the number contains invalid char
   ,VEN_PHB_RESULT_MAX = 10
};

typedef s32 ven_phb_result_t;

enum
{
    VEN_PHB_NUMBER_TYPE_MOBILE = 0
   ,VEN_PHB_NUMBER_TYPE_HOME = 1
   ,VEN_PHB_NUMBER_TYPE_OFFICE = 2
   ,VEN_PHB_NUMBER_TYPE_OTHER = 3
   ,VEN_PHB_NUMBER_TYPE_MAX = 3
};

typedef s32 ven_phb_number_type_t;


enum
{
    VEN_PHB_BROWSER_TYPE_PHONENO                = 0,
    VEN_PHB_BROWSER_TYPE_EMAIL              = 1,
};
typedef u8 ven_phb_browser_type_t;

enum
{
    VEN_PHB_TYPE_SIM_MASTER,
    VEN_PHB_TYPE_SIM_SLAVE,
    VEN_PHB_TYPE_PHONE
};
typedef u8 ven_phb_phonebook_type_t;

typedef struct
{
    size_t nameLen;
    u16 u16Name[VEN_PHB_NAME_LEN + 1];
} ven_phb_name_t;

typedef struct
{
    u8 u8NumberLen;
    u8 u8Number[VEN_PHB_NUMBER_LEN + 1];
    ven_phb_number_type_t s32NumberType;
} ven_phb_number_t;

typedef struct
{
    size_t companyLen;
    u16 u16Company[VEN_PHB_COMPANY_LEN + 1];
} ven_phb_company_t;

typedef struct
{
    size_t departmentLen;
    u16 u16Department[VEN_PHB_DEPARTMENT_LEN + 1];
} ven_phb_department_t;

typedef struct
{
    size_t positionLen;
    u16 u16Position[VEN_PHB_POSITION_LEN + 1];
} ven_phb_position_t;

typedef struct
{
    size_t homeAddressLen;
    u16 u16HomeAddress[VEN_PHB_HOME_ADDRESS_LEN + 1];
} ven_phb_home_address_t;

typedef struct
{
    size_t officeAddressLen;
    u16 u16OfficeAddress[VEN_PHB_OFFICE_ADDRESS_LEN + 1];
} ven_phb_office_address_t;

typedef struct
{
    size_t emailLen;
    u16 u16Email[VEN_PHB_EMAIL_LEN + 1];
} ven_phb_email_t;

typedef struct
{
    size_t urlLen;
    u16 u16Url[VEN_PHB_URL_LEN + 1];
} ven_phb_url_t;

typedef struct
{
    size_t noteLen;
    u16 u16Note[VEN_PHB_NOTE_LEN + 1];
} ven_phb_note_t; 

typedef struct
{
    u8 au8Year[2];
    u8 au8Month[2];
    u8 au8Day[2];
    u8 au8Hour[2];
    u8 au8Minute[2];
    u8 au8Second[2];
} ven_phb_datetime_t;         /* 12 bytes */

typedef struct
{
    ven_phb_name_t tPhbName;
    ven_phb_number_t tPhbNumber[VEN_PHB_NUMBER_MAX];
    ven_phb_company_t tPhbCompanyName;
    ven_phb_department_t tPhbDepartment;
    ven_phb_position_t tPhbPosition;
    ven_phb_home_address_t tPhbHomeAddress;
    ven_phb_office_address_t tPhbOfficeAddress;
    ven_phb_email_t tPhbEmail;
    ven_phb_url_t tPhbUrl;
    ven_phb_note_t tPhbNote;
    u32 u32PhbImageIdx;
    u32 u32PhbRingtoneIdx;
    ven_phb_datetime_t tPhbBirthday;
    u32 u32PhbFilter;
    u8 u8ComparingString[VEN_PHB_MAX_COMPARE_LEN + 1];
    u8 u8MultiWordPrefix[VEN_PHB_MULTI_WORD_PREFIX_MAX + 1];

#ifdef __UNICODE_TO_STROKE__
    u8 u8NameStroke[VEN_PHB_MAX_NAME_STROKE_LEN+1];
    u8 u8MWPStroke[VEN_PHB_MWP_STROKE_MAX+1];
#endif
} ven_phb_contact_content_t;

typedef struct
{
    u16 u16PhysicalIdx;
    u16 u16SortNum;             /* For filter sorting. */
    u16 u16TotalSortingIdx;     /* Sorting index that without input any search string. */
    u16 u16AllSortingIdx;        /* Sorting index of ADR_ADN_M_ADN_S without book type and group. */
} ven_phb_search_result_t;             /* For Multiple Word Prefix Search. */

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/*************************************************************/
/**
 *  ven_phb_browse
 *
 *  @brief  Browse phonebook to select phone number(s)/email(s)
 *
 *  @param  ptTitle           [in]  String to be shown on title bar
 *  @param  titleLen          [in]  Charater length of title string
 *  @param  type              [in]  Select type, phone number/email
 *  @param  maxMarkSize       [in]  Max select number of number(s)/email(s)
 *  @param  ppOutData         [out] Popinter to store output pointer, for synchoronous using only.
 *  @param  pOutDataLen       [out] Popinter to store output data length, for synchoronous using only.
 *  @param  nOutMarkedSize    [out] Popinter to store output selected size, for synchoronous using only.
 *  @param  ptVenReq          [in]  Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval TRUE   Success
 *          FALSE   Failed
 *
 *  @note Synchronous function
 */
bool ven_phb_browse(u16 *ptTitle, u8 titleLen, ven_phb_browser_type_t type,  u8 maxMarkSize, u16 **ppOutData, u16 *pOutDataLen, u8 *nOutMarkedSize, ven_req_data_t* ptVenReq);

typedef struct
{
    u16 *ptData;
    u16 dataLen;
    u8  nMarkedSize;
} ven_phb_browse_rsp_t;
/*************************************************************/
/* struct for save contact request */
typedef struct
{
    u16  *pName;          ///< Contact name, UCS2 string. This UCS2 string will be encoded to SIM UCS2/ALPHABET according to the content. The max size of encoded string is 41 bytes.
    u8   *pNumber;        ///< Contact phone number. More than 40 digits will be truncated.
    u8   nNameLen;        ///< Character length of contact name
    u8   nNumberLen;      ///< Character length of contact phone number
    ven_phb_phonebook_type_t PhbType;    ///< phonebook type to save
} ven_phb_save_contact_req_t;

/* struct for save contact response, both synchronous and asynchronous */
typedef struct
{
    ven_phb_ret_t RetCode;
} ven_phb_save_contact_rsp_t;

/**
 *  ven_phb_saveContact
 *
 *  @brief  Save a new phonebook contact
 *
 *  @param  pSaveContactReq              [in]  Pointer to the new contact data to save
 *  @param  ven_phb_save_contact_rsp_t   [out] Pointer to store synchronous return structure
 *  @param  ptVenReq                     [in]  Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval VEN_PHB_RET_SUCCESS   Create successfully
 *          VEN_PHB_RET_BAD_PARAM    Given parameters are invalid
 *          VEN_UI_RET_OUT_OF_MEMORY  Not enough memory to perform operation
 *
 *  @note Synchronous function
 */
ven_phb_ret_t ven_phb_saveContact(ven_phb_save_contact_req_t *pSaveContactReq, ven_phb_save_contact_rsp_t *pSyncRsp, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_phb_phonebook_type_t phbBookType;
    ven_phb_contact_content_t tPhbContactContent;
} ven_phb_add_contact_req_t;

typedef struct
{
    ven_phb_ret_t RetCode;
} ven_phb_add_contact_rsp_t;

typedef struct
{
    ven_phb_ret_t RetCode;
    u16 u16Index;
} ven_phb_add_new_contact_rsp_t;

/**
 *  ven_phb_addOneContact
 *
 *  @brief  Add one new contact to the phonebook.
 *
 *  @param  pWriteContactReq         [in] The pointer of the contact data that want to write to the phonebook.
 *  @param  pSyncRsp                 [out] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq                 [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_addOneContact(ven_phb_add_contact_req_t *pWriteContactReq,ven_phb_add_contact_rsp_t *pSyncRsp, ven_req_data_t*ptVenReq);

typedef struct
{     
    ven_phb_phonebook_type_t s32PhbBookType;
    u16 *pwcSearchStr;
}ven_phb_search_req_t;

/**
 *  ven_phb_findFirst
 *
 *  @brief  Find the next contact by handle.
 *
 *  @param  pMWPSearchReq               [in] Search condtion
 *  @param  ptContent                   [out] The next contact find by the handle.Only use for sync.
 *  @param  ptVenReq                    [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_handle ven_phb_findFirst(ven_phb_search_req_t *pMWPSearchReq,ven_phb_contact_content_t *ptContent,u32 handle);

/**
 *  ven_phb_findNext
 *
 *  @brief  Find the next contact by handle.Must findFirst before findNext.
 *
 *  @param  ptContent                   [out] The next contact find by the handle.Only use for sync.
 *  @param  ptVenReq                    [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_findNext(ven_phb_handle handle,ven_phb_contact_content_t *ptContent ,ven_req_data_t* ptVenReq);

/**
 *  ven_phb_setFocusIndex
 *
 *  @brief  Find the assigned contact according to the index of search result.
 *
 *  @param  nIndex                      [in] index of search result
 *  @param  ptContent                   [out] The next contact find by the handle.Only use for sync.
 *  @param  ptVenReq                    [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_setFocusIndex(ven_phb_handle handle, u32 nIndex, ven_phb_contact_content_t *ptContent,ven_req_data_t* ptVenReq);

/**
 *  ven_phb_getFocusIndex
 *
 *  @brief  Find the current contact according to the index of search result.
 *
 *  @param  *nIndex                     [out] current index of search result
 *  @param  ptContent                   [out] The next contact find by the handle.Only use for sync.
 *  @param  ptVenReq                    [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_getFocusIndex(ven_phb_handle handle, u32* nIndex, ven_phb_contact_content_t *ptContent,ven_req_data_t* ptVenReq);

typedef struct
{
    ven_phb_ret_t RetCode;
} ven_phb_delete_contact_rsp_t;

/**
 *  ven_phb_deleteContact
 *
 *  @brief  Delete one contact from the phonebook by handle. The contact must be found before delete.
 *
 *  @param  pSyncRsp                 [out] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq                 [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_deleteContact(ven_phb_handle handle,
ven_phb_delete_contact_rsp_t *pSyncRsp,ven_req_data_t* ptVenReq);

typedef struct
{
    ven_phb_ret_t RetCode;
} ven_phb_save_modifiedContact_rsp_t;

/**
 *  ven_phb_modifiedContact
 *
 *  @brief  Save one modified contact by handle. The contact must be found before modify.
 *
 *  @param  handle                      [in] The handle of the motified contact
 *  @param  ven_phb_contact_content_t   [in] The pointer of the contact data that after modified.
 *  @param  pSyncRsp                    [out] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq                    [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_modifiedContact(ven_phb_handle handle,
ven_phb_contact_content_t *ptContent,ven_phb_save_modifiedContact_rsp_t *
pSyncRsp,ven_req_data_t* ptVenReq);


/**
 *  ven_phb_findClose
 *
 *  @brief  End of finding contacts & release.
 *
 *  @param  handle                      [in] The handle of ven_phb
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_FAILED
 *
 */
void ven_phb_findClose(ven_phb_handle handle);


/**
 *  ven_phb_getSearchTotal
 *
 *  @brief  Get the search total of contacts by handle.
 *
 *  @param  handle                      [in] The handle of ven_phb
 *
 *  @retval u16
 *          0, if no contacts
 *
 */
u16 ven_phb_getSearchTotal(ven_phb_handle handle);

typedef struct
{

    ven_phb_result_t s32PhbResult;
    u16 u16PhbMaxContacts;
    u16 u16PhbUsedContacts;
    u16 u16PhbAvailContacts;
} ven_phb_get_mem_status_rsp_t;

ven_phb_ret_t ven_phb_getMemStatus(const ven_phb_phonebook_type_t
s32PhbBookType, ven_phb_get_mem_status_rsp_t *ptCnf,ven_req_data_t *ptVenReq);


typedef struct
{     
    ven_phb_phonebook_type_t s32PhbBookType;
    u16 *pwcSearchStr;
}ven_phb_number_fuzzy_search_req_t;

typedef struct
{
    ven_phb_handle phbHandle;
    ven_phb_search_result_t *pSearchResult;
	u16 pu16SearchResultTotal;
} ven_phb_number_fuzzy_search_rsp_t;

/**
 *  ven_phb_NumberFuzzySearch
 *
 *  @brief  Fuzzy search PHB contact number.
 *
 *  @param  *pSearchReqData              [in] data needed for fuzzy search
 *  @param  *pSearchRspData              [out] search result data structure
 *  @param  ptVenReq                     [in] Request data structure, including callback function and SDK handle, see ven_sdk.h for more information
 *
 *  @retval handle pointer of search result, including all physical index and total number of these index.
 *
 */
ven_phb_handle ven_phb_NumberFuzzySearch(ven_phb_number_fuzzy_search_req_t *pSearchReqData, ven_phb_number_fuzzy_search_rsp_t *pSearchRspData, ven_req_data_t *ptVenReq);

/**
 *  ven_phb_findFirstContact (Support Sync)
 *
 *  @brief  Find the first contact by handle.
 *
 *  @param  pMWPSearchReq   [in] Search condtion
 *  @param  ptVenReq             [in] The pointer of the request data.
 *  @param  ptContent            [out] The next contact find by the handle.Only use for sync.
 *  @param  pu16Index           [out] The pointer of the index of first contact.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_handle ven_phb_findFirstContact(ven_phb_search_req_t *pMWPSearchReq, ven_req_data_t* ptVenReq, ven_phb_contact_content_t *ptContent, u16 *pu16Index);

/**
 *  ven_phb_findNextContact (Support Sync)
 *
 *  @brief  Find the next contact by phb handle.
 *
 *  @param  phbHandle   [in] phb handle
 *  @param  ptVenReq    [in] The pointer of the request data.
 *  @param  ptContent    [out] The next contact find by the handle.Only use for sync.
 *  @param  pu16Index   [out] The pointer of the index of first contact.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_findNextContact(ven_phb_handle phbHandle, ven_req_data_t* ptVenReq, ven_phb_contact_content_t *ptContent, u16 *pu16Index);

/**
 *  ven_phb_getOneContact (Support Sync)
 *
 *  @brief  Get one contact by index.
 *
 *  @param  u16Index         [in] The index of the contact
 *  @param  phbBookType   [in] The phonebook type of the contact.
 *  @param  ptVenReq         [in] The pointer of the request data.
 *  @param  ptContent        [out] The next contact find by the handle.Only use for sync.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_getOneContact(u16 u16Index, ven_phb_phonebook_type_t phbBookType, ven_req_data_t* ptVenReq, ven_phb_contact_content_t *ptContent);

typedef struct
{
    ven_phb_ret_t RetCode;
    u16 u16index;
} ven_phb_add_one_contact_rsp_t;

/**
 *  ven_phb_addNewContact (support Sync & Async)
 *
 *  @brief  Add one new contact to the phonebook.
 *
 *  @param  phbBookType   [in] The phonebook type of deleted contact.
 *  @param  ptContent         [in] The pointer of the contact data which will be added.
 *  @param  pSyncRsp         [in] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq         [in] The pointer of the request data.
 *  @param  pu16Index       [out] The pointer of the index of added contact.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_addNewContact(ven_phb_phonebook_type_t phbBookType, ven_phb_contact_content_t *ptContent, ven_phb_add_new_contact_rsp_t *pSyncRsp, ven_req_data_t* ptVenReq, u16 *pu16Index);


/**
 *  ven_phb_deleteOneContact (support Sync & Async)
 *
 *  @brief  Delete one contact from the phonebook,the contact must be found before delete.
 *
 *  @param  u16Index         [in] The index of deleted contact.
 *  @param  phbBookType   [in] The phonebook type of deleted contact.
 *  @param  pSyncRsp        [out] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq         [in] The pointer of the request data.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_deleteOneContact(u16 u16Index, ven_phb_phonebook_type_t phbBookType, ven_phb_delete_contact_rsp_t *pSyncRsp, ven_req_data_t* ptVenReq);

typedef struct
{
    ven_phb_ret_t RetCode;
    u16 u16newIndex;
} ven_phb_modify_one_contact_rsp_t;

/**
 *  ven_phb_modifyOneContact (support Sync & Async)
 *
 *  @brief  Save one modified contact.The contact must be found before modify.
 *
 *  @param  u16Index            [in] The index of modified contact.
 *  @param  phbBookType      [in] The phonebook type of modified contact.
 *  @param  ptContent           [in] The pointer of the contact data that after modified.
 *  @param  pSyncRsp           [out] The pointer of the response data.Only use for sync.
 *  @param  ptVenReq            [in] The pointer of the request data.
 *  @param  pu16NewIndex    [out] The pointer of the new index of modified contact.
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_BAD_PARAM if invalid input parameters
 *          VEN_PHB_RET_OUT_OF_MEMORY
 *          VEN_PHB_RET_FAILED
 *
 */
ven_phb_ret_t ven_phb_modifyOneContact(u16 u16Index, ven_phb_phonebook_type_t phbBookType, ven_phb_contact_content_t *ptContent, ven_phb_modify_one_contact_rsp_t *pSyncRsp, ven_req_data_t* ptVenReq, u16 *pu16NewIndex);

/**
 *  ven_phb_getPhoneBookType
 *
 *  @brief  Get the phonebook type of contact by handle.
 *
 *  @param  handle                      [in] The handle of ven_phb
 *
 *  @retval ven_phb_phonebook_type_t
 *          VEN_PHB_TYPE_SIM_MASTER = 2
 *          VEN_PHB_TYPE_SIM_SLAVE = 3
 *          VEN_PHB_TYPE_PHONE = 14
 *          0, if bad handle
 *
 */
ven_phb_phonebook_type_t ven_phb_getPhoneBookType(ven_phb_handle handle);

/**
 *  ven_phb_querySrvReady
 *
 *  @brief  This function will help to query phbSrv ready or not, only support sync.
 *
 *  @param  venHandle       [in] vendor handle
 *  @param  pReady       [out] To check whether phbSrv is ready
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_FAILED if failed
 *          VEN_PHB_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_phb_ret_t ven_phb_querySrvReady(u32 venHandle, bool* pReady);

typedef void (*VEN_PHB_READY_IND_FUNC)(u32 readyInfo, u32 usrData);

/**
 *  ven_phb_registerSrvReadyInd
 *
 *  @brief  This function will help to register notification for phbSrv ready
 *
 *  @param  venHandle       [in] vendor handle
 *  @param  pReadyIndFunc     [in] To receive the notification if phbSrv is ready
 *  @param  usrData           [in] user data for pReadyFunc
 *
 *  @retval VEN_PHB_RET_SUCCESS if success
 *          VEN_PHB_RET_FAILED if failed
 *          VEN_PHB_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_phb_ret_t ven_phb_registerSrvReady(u32 venHandle, VEN_PHB_READY_IND_FUNC pReadyIndFunc, u32 usrData);

/*************************************************************/


#endif //__VEN_PHB_H_

