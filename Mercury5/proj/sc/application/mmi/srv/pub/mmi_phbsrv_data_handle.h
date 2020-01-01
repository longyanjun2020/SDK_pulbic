
/**
 * @file    mmi_phb_data_handle.h
 * @brief   The file handles all phonebook data.
 * @author  ryb.chen@mstarsemi.com
 *
 * @version $Id: mmi_phb_data_handle.h 40244 2009-09-15 02:45:52Z cosmo.sung $
 */

#ifndef __MMI_PHB_DATA_HANDLE_H__
#define __MMI_PHB_DATA_HANDLE_H__

/*
    Include File
*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_phbsrv_def.h"
#include "mmi_common_content.h"



/* For alphabet-digit conversion */
#ifdef __MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__
#define MMI_PHB_ALPHABET_TO_DIGIT_TABLE_SIZE    26
#define MAX_KEY_PRESSED_TIME 5
#endif

/*
    Structure
*/

typedef struct
{
    u8 u8NumberLen;
    u8 au8Number[MMI_PHB_NUMBER_LEN];
    u8 u8NumberType;
} MmiPhbDhNumber_t;     /* 12 bytes */

typedef struct
{
    u8 u8IsValid;

    u8 u8NameLen;
    u8 au8Name[MMI_PHB_NAME_LEN];

    MmiPhbDhNumber_t atNumber[MMI_PHB_NUMBER_MAX];

    u32 u32Filter;  /*
                                    bit 31 30 29 ~ 10 9 8 7 6 5 4 3 2 1 0
                                        bit 0       : Reserve
                                        bit 1~28    : for normal group
                                        bit 29      : for caller group Black List
                                        bit 30      : indicate the contact has url
                                        bit 31      : indicate the contact has email
                                */
} MmiPhbDhSortByPhyIdTable_t;   /* 94 bytes */

typedef struct /* Do not change the order of this structure, this will affect the reading sequence*/
{
    u8 u8NameLen;
    u8 au8Name[MMI_PHB_SIM_NAME_LEN];
    u8 u8NumberLen;
    u8 au8Number[MMI_PHB_SIM_NUMBER_LEN];
#ifndef __SMALL_PHB_MMI__    
#ifdef __3G_RIL_MMI__
    u8 u8EMailLen;
    u8 au8EMail[MMI_PHB_TEXT_MAX];
#endif   
#endif // #ifndef __SMALL_PHB_MMI__

#ifdef __UNICODE_TO_STROKE__
	u8 u8NameStroke[MMI_PHB_MAX_NAME_STROKE_LEN+1];
	u8 u8MWPStroke[MMI_PHB_MWP_STROKE_MAX+1];
#endif
} MmiPhbDhADNBackupData_t;  /* 116 bytes (with 4 byte alignment) 116bytes*256 records = 29696 bytes < 30k rai limit */

typedef struct
{
    u8	u8NameLen;
    u8	au8Name[MMI_PHB_SIM_NAME_LEN];
    u8	u8NumberLen;
    u8	au8Number[MMI_PHB_SIM_NUMBER_LEN];
#ifndef __SMALL_PHB_MMI__    
#ifdef __3G_RIL_MMI__                
    u8	u8EMailLen;
    u8	au8EMail[MMI_PHB_TEXT_MAX];
#endif   
#endif // #ifndef __SMALL_PHB_MMI__
    
} MmiPhbDhADNData_t;

typedef struct
{
    u16 u16PhysicalIdx;
    u16 u16NextAryIdx;
} MmiPhbDhHashByNumberTable_t;  /* 4 bytes */


#define MmiPhbDhSortByNameTable_t	MmiPhbSearchResult_t


//This structure is for comparison buffer usage. In order to do strcmp properly,
//need +1 to size to make it a NULL terminating string
typedef struct
{
    u8 u8NameLen;
    u8 au8Name[MMI_PHB_NAME_LEN + 1];
    u16 u16ComparingString[MMI_PHB_MAX_COMPARE_LEN + 1];
    boolean bIsPreNum;
} MmiPhbDhCompareInfo_t;

typedef struct
{
    /*  < 1 means first string smaller
        > 1 means first string greater
        = 0 means identical */
    int iSearchResult;
    u16 u16IndexFound;
} MmiPhbDhSearchResult_t;


typedef enum
{
    MMI_PHB_DH_INSERTION_SORT = 0
   ,MMI_PHB_DH_SEARCH
} MmiPhbDhSearchType_e;

typedef MmiPhbReturn_e (*PfnCompareFunc) (void *pThis, const u8 u8NameLen, const u8 *pu8NameStr, const u16 *pInputPinYin, MmiPhbDhCompareInfo_t *pCompareInfoBuff, int *pCompareResult, boolean bIsPreNum);


/*
    Constant
*/

enum
{
    MMI_PHB_ADR_ADN_M_ADN_S_SORTBYNAME_TABLE_SIZE = (MMI_PHB_TOTAL_SUPPORT_MAX+1)

    ,MMI_PHB_DH_SORT_BY_PHY_IDX_TABLE_SIZE = (MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADR_SUPPORT_MAX+1)
    ,/* (MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADR_SUPPORT_MAX+1) */
    MMI_PHB_DH_HASH_BY_NUMBER_TABLE_SIZE = (MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADN_SUPPORT_MAX+(MMI_PHB_ADR_SUPPORT_MAX*4)+1)
    ,/* (MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADN_SUPPORT_MAX+(MMI_PHB_ADR_SUPPORT_MAX*4)+1) */
    MMI_PHB_DH_MEMORY_STATUS_TABLE_SIZE = ((MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADN_SUPPORT_MAX+MMI_PHB_ADR_SUPPORT_MAX+8-1)/8)
    ,/* 189 bytes = 1512 bits, to check the physical index is empty or not. */

    MMI_PHB_DH_COMPARE_BUFFER_CHAR = 50
    ,MMI_PHB_DH_NUMBER_COMPARE_MAX = 8
    ,MMI_PHB_DH_PRIME_1 = 629137
    ,/* For hash table. */
    MMI_PHB_DH_PRIME_2 = 251
    /* For hash table. */
    // NOTE!! MMI_PHB_DH_PRIME_3 MUST less than MMI_PHB_DH_HASH_BY_NUMBER_TABLE_SIZE!!!
#if defined(__TINY_RAI_STORAGE_SIZE__)
    ,MMI_PHB_DH_PRIME_3 = 587
#elif defined(__LOW_RAI_STORAGE_SIZE__)
    ,MMI_PHB_DH_PRIME_3 = 1009
#else
    ,MMI_PHB_DH_PRIME_3 = 1009
#endif    
    
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    ,MMI_PHB_DH_PRIME_4 = ((MMI_PHB_BLACKLIST_SUPPORT_MAX*3)/4)
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    ,/* For hash table. */

    //  MMI_PHB_DH_SEARCH_RESULT_BLOCK_SIZE     = 255,      /* For multiple word prefix search. */
    //  MMI_PHB_DH_SEARCH_RESULT_BLOCK_MAX      = 6         /* For multiple word prefix search. */
    MMI_PHB_DH_MWP_PRIORITY_VALUE = 10      /* For multiple word prefix search. */
};

enum
{
/*
The enum for rai partition for sorting table
*/
#ifdef __NAND_MMI__
   MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE    = 29696    /* 29k for one rai partition */
#else
   MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE = 10240     /* 10k for one partition */
#endif

   /* Partition the sorting table */
   //patMmiPhbHashByNumberTable
   ,MMI_PHB_HASH_BY_NUMBER_TABLE_MAX_RAI_PARTITION =
   ((MMI_PHB_DH_HASH_BY_NUMBER_TABLE_SIZE * sizeof(MmiPhbDhHashByNumberTable_t))/MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)

   //patMmiPhbSortByNameTable_ADR_ADN_M_ADN_S
   ,MMI_PHB_SORT_BY_NAME_ADR_ADN_M_ADN_S_MAX_RAI_PARTITION =
   ((MMI_PHB_ADR_ADN_M_ADN_S_SORTBYNAME_TABLE_SIZE * sizeof(MmiPhbDhSortByNameTable_t)) / MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)
#ifdef __NAND_MMI__
   //patMmiPhbSortByNameTable_Name
   ,MMI_PHB_SORT_BY_NAME_NAME_MAX_RAI_PARTITION =
   ((MMI_PHB_ADR_ADN_M_ADN_S_SORTBYNAME_TABLE_SIZE * sizeof(MmiPhbName_t)) / MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)

   //patMmiPhbSortByNameTable_Number
   ,MMI_PHB_SORT_BY_NAME_NUMBER_MAX_RAI_PARTITION =
   ((MMI_PHB_ADR_ADN_M_ADN_S_SORTBYNAME_TABLE_SIZE * sizeof(MmiPhbAllNumbers_t)) / MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)

#ifdef __UNICODE_TO_STROKE__
   //patMmiPhbSortByNameTable_Stroke
   ,MMI_PHB_SORT_BY_NAME_STROKE_MAX_RAI_PARTITION =
   ((MMI_PHB_ADR_ADN_M_ADN_S_SORTBYNAME_TABLE_SIZE * sizeof(MmiPhbStroke_t)) / MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)
#endif
#endif

#ifndef __MMI_PHB_DISABLE_BLACKLIST__
#ifdef __MMI_PHB_BK_WITH_SORTING__
   ,MMI_PHB_SORT_BY_NAME_BK_MAX_RAI_PARTITION =
   (((MMI_PHB_BLACKLIST_SUPPORT_MAX+1) * sizeof(MmiPhbDhSortByNameTable_t)) / MMI_PHB_MAX_RAI_ONE_PARTITION_SIZE)
#endif
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__
};


/*
    Function
*/


/*
    Check the contact is exist or not.
*/

boolean MMI_PHB_DH_IsContactExist(void *pThis, u16 u16PhysicalIdx);

/*
    Initialize phonebook data.
*/

MmiPhbReturn_e MMI_PHB_DH_InitializePhbData(void *pThis);

/*
    to release unused run time memory.
*/
__SLDPM_FREE__ void MMI_PHB_DH_ReleaseResource(void);

/*
    to prepare run time memory.
*/
__SLDPM_FREE__ MmiPhbReturn_e MMI_PHB_DH_PrepareResource(void);
#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_PHB_BK_WITH_SORTING__)
MmiPhbReturn_e MMI_PHB_DH_PrepareResourceBK(void *pThis);
#endif

/*
    For power-off.
*/
MmiPhbReturn_e MMI_PHB_DH_Release(void *pThis);


/*
    Insert Contact's data to all sorting table,
    support ADN, ADR and ADN_ADR.
*/
MmiPhbReturn_e MMI_PHB_DH_InsertDataToSortingTable(void *pThis, MmiPhbBookType_e           s32PhbBookType, const MmiPhbContactContent_t *ptPhbContactContent, u16                          u16PhbPhysicalIdx);

/*
    Remove Contact's data from all sorting table,
    support ADN, ADR and ADN_ADR.
*/

MmiPhbReturn_e MMI_PHB_DH_RemoveDataFromSortingTable(void *pThis, u16 u16PhbPhysicalIdx);

/*
    Write sorting table to file system.
*/

#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__MMI_PHB_BK_WITH_SORTING__)
MmiPhbReturn_e MMI_PHB_DH_WriteSortingTabletoFS(void *pThis, boolean bIsBK);
#else
MmiPhbReturn_e MMI_PHB_DH_WriteSortingTabletoFS(void *pThis);
#endif

MmiPhbReturn_e MMI_PHB_DH_CleanSortingTable(void *pThis);


/*
    Search contact by name, only support ADN, ADR and ADN_ADR.
    *pu16SortingIdx maybe is a exact sorting index,
    or only is a closest index.
*/

MmiPhbReturn_e MMI_PHB_DH_SearchContactByName(void *pThis, MmiPhbBookType_e            s32BookType, const u8                       u8NameLen, const u8 *pu8NameStr, u16 *pu16SortingIdx, MmiPhbDhSearchType_e         eSearchType, boolean bIsPreNum);

/*
 *	Search contact by number, only support ADN, ADR and ADN_ADR.
 *  caller need to free the *ppPhbName
 */

MmiPhbReturn_e MMI_PHB_DH_SearchContactByNumber (void *pThis, MmiPhbBookType_e s32BookType, const u8 u8NumberLen, const u8 *pu8NumberStr, u16 *pu16PhysicalIdx, MmiPhbName_t **ppPhbName, boolean bIsAllowADN_M, boolean bIsAllowADN_S);

#ifndef __MMI_PHB_DISABLE_BLACKLIST__
MmiPhbReturn_e MMI_PHB_DH_SearchBlackListMemberByNumber(void *pThis, boolean *bBlock, const MmiPhbNumber_t *ptNumber);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__
boolean MMI_PHB_DH_IsInGroup(u32 u32Filter, MmiPhbGroup_e s32PhbGroup);

/*
    bit 31 30 29 ~ 10 9 8 7 6 5 4 3 2 1 0

    bit 0       : Reserve
    bit 1~28    : for normal group
    bit 29      : for caller group Black List
    bit 30      : indicate the contact has url
    bit 31      : indicate the contact has email
*/

u32 MMI_PHB_DH_GetFilterValue(void *pThis, u32             u32OldFilter, MmiPhbGroup_e   s32PhbGroup, boolean            bIsAdd);


/*
    Convert sorting index to physical index, only support ADN, ADR, ADN_ADR, CGx, BLACK_LIST, URL and Email.
*/

MmiPhbReturn_e MMI_PHB_DH_ConvertToPhysicalIdx(void *pThis, MmiPhbBookType_e   s32BookType, MmiPhbGroup_e        s32Group, const u16                 u16SortingIdx, u16 *pu16PhysicalIdx);


/*
    Convert physical index to sorting index, only support ADN, ADR, ADN_ADR, CGx, BLACK_LIST, URL and Email.
*/

MmiPhbReturn_e MMI_PHB_DH_ConvertToSortingIdx(void *pThis, MmiPhbBookType_e        s32BookType, MmiPhbGroup_e            s32Group, const u16                 u16PhysicalIdx, u16 *pu16SortingIdx);

__SLDPM_FREE__ MmiPhbReturn_e MMI_PHB_DH_QueryPhbStatus(void *pThis, const MmiPhbQueryPhbStatusReq_t *ptReq, MmiPhbQueryPhbStatusCnf_t *ptCnf, boolean                          bIsAllowADN_M, boolean                          bIsAllowADN_S);

MmiPhbReturn_e MMI_PHB_DH_CleanAllData(void *pThis, MmiPhbBookType_e s32PhbBookType);

void MMI_PHB_DH_SetADNStatusEx(MmiPhbBookType_e s32PhbBookType, u16 u16MaxEmailNum, u16 u16UsedEmailNum, u16 u16MaxExtNum, u16 u16UsedExtNum);
void MMI_PHB_DH_GetADNStatusEx(MmiPhbBookType_e s32PhbBookType, u16 *pu16MaxEmailNum, u16 *pu16UsedEmailNum, u16 *pu16MaxExtNum, u16 *pu16UsedExtNum);

#ifdef __3G_RIL_MMI__
void MMI_PHB_DH_SetADNStatus(void *pThis, MmiPhbBookType_e  s32PhbBookType, u16 u16MaxContacts, u16 u16UsedContacts, u8 u8MaxNameLen, u8 u8MaxNUmberLen, u8 u8MaxMailLen);
#else //__3G_RIL_MMI__
void MMI_PHB_DH_SetADNStatus(void *pThis, MmiPhbBookType_e  s32PhbBookType, u16                 u16MaxContacts, u16                 u16UsedContacts, u8                     u8MaxNameLen, u8                        u8MaxNUmberLen);
#endif // __3G_RIL_MMI__ 

#ifdef __3G_RIL_MMI__
void MMI_PHB_DH_GetPartialPhbStatus(void *pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, u16 *pu16MaxContacts, u16 *pu16UsedContacts, u8 *pu8MaxNameLen, u8 *pu8MaxNumberLen, u8 *pu8MaxMailLen, boolean bIsAllowADN_M, boolean bIsAllowADN_S);
#else //__3G_RIL_MMI__
void MMI_PHB_DH_GetPartialPhbStatus(void *pThis, MmiPhbBookType_e   s32PhbBookType, MmiPhbGroup_e     s32PhbGroup, u16 *pu16MaxContacts, u16 *pu16UsedContacts, u8 *pu8MaxNameLen, u8 *pu8MaxNUmberLen, boolean               bIsAllowADN_M, boolean              bIsAllowADN_S);
#endif //__3G_RIL_MMI__


MmiPhbReturn_e MMI_PHB_DH_ReadOneAdr(void *pThis, u16 u16PhyIdx, MmiPhbContactContent_t **ppContent, boolean bIsNeedFullContent);
#if !defined(__SMALL_PHB_MMI__) || !defined(__NAND_MMI__)
MmiPhbReturn_e MMI_PHB_DH_ReadContactField(void *pThis, u16 u16PhyIdx, MmiPhbName_t **ppName, MmiPhbNumber_t **ppNumber, MmiPhbEmail_t **ppEmail);
#endif
MmiPhbReturn_e MMI_PHB_DH_ReadOneContactByPhysicalIdx(void *pThis, const MmiPhbReadOneContactByPhysicalIdxReq_t *ptReq, MmiPhbReadOneContactByPhysicalIdxCnf_t *ptCnf, boolean                                   bIsNeedFullContent);

MmiPhbReturn_e MMI_PHB_DH_WriteOneAdrByPhysicalIdx(void *pThis, MmiPhbWriteOneContactByPhysicalIdxReq_t *ptReq, MmiPhbWriteOneContactByPhysicalIdxCnf_t *ptCnf);

MmiPhbReturn_e MMI_PHB_DH_DeleteOneAdrByPhysicalIdx(void *pThis, const MmiPhbDeleteOneContactByPhysicalIdxReq_t *ptReq, MmiPhbDeleteOneContactByPhysicalIdxCnf_t *ptCnf);

MmiPhbReturn_e MMI_PHB_DH_UpdateOneAdrGroupByPhysicalIdx(void *pThis, u16 u16PhbPhysicalIdx, MmiPhbGroup_e s32PhbGroup, boolean bIsAdd);

#ifndef __MMI_PHB_DISABLE_BLACKLIST__

MmiPhbReturn_e MMI_PHB_DH_ReadBlackListTotalNum(void *pThis, u8 *u8PhbBlackListNumber);

MmiPhbReturn_e MMI_PHB_DH_ReadBlackListBySortingIdx(void *pThis, MmiPhbReadBlackListByRaiIdxReq_t *ptReq, MmiPhbReadBlackListByRaiIdxCnf_t *ptCnf);
MmiPhbReturn_e MMI_PHB_DH_ReadOneBlackListAdr(void *pThis, u16 u16PhyIdx, /*MmiPhbContactContent_t*/
                                     MmiPhbBlackListMemberContent_t **ppContent/*, boolean bIsNeedFullContent*/);
MmiPhbReturn_e MMI_PHB_DH_WriteBlackListBySortingIdx(void *pThis, MmiPhbBlackListMemberContent_t *ptPhbContactContent, u16                       u16PhBlackListRaiIdx);


MmiPhbReturn_e MMI_PHB_DH_WriteBlackListNew(void *pThis, MmiPhbBlackListMemberContent_t *ptPhbContactContent, u16 *pu16Idx);

MmiPhbReturn_e MMI_PHB_DH_DeleteOneBlackListBySortingIdx(void *pThis, u16        u16PhBlackListRaiIdx);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__

MmiPhbReturn_e MMI_PHB_DH_ReadPartialBySortingIdx(void *pThis, const MmiPhbReadPartialBySortingIdxReq_t *ptReq, MmiPhbReadPartialBySortingIdxCnf_t *ptCnf);

MmiPhbReturn_e MMI_PHB_DH_UpdateMemoryStatus(void *pThis, u16 u16PhysicalIdx, boolean bIsUsed);


/*
    Support ADN_M, ADN_S, ADR.
*/
u16 MMI_PHB_DH_GetEmptyIdx(void *pThis, MmiPhbBookType_e s32BookType);


/*
    Support ADN_M, ADN_S, ADR.
*/
u16 MMI_PHB_DH_GetNextExistedIdx(void *pThis, MmiPhbBookType_e s32BookType, u16 u16CurrentIdx);


/*
    Support ADN_M, ADN_S, ADR.
*/
boolean MMI_PHB_DH_IsPhysicalIdxValid(MmiPhbBookType_e s32PhbBookType, u16 u16PhbPhysicalIdx);

/*
    For Group, get the status that which contacts are included.
*/
MmiPhbReturn_e MMI_PHB_DH_GetContactsInGroupStatusArray(void *pThis, MmiPhbBookType_e    s32PhbBookType, MmiPhbGroup_e     s32PhbGroup, boolean *pbSrvCheckStatus);


/*
    Convert input string to PinYin
    Input:
        u8InputLen: Input u8 string length
        pu8InputStr: Input UTF8 String
        pu8OutPinYinStr: Output UTF8 PinYin String Buffer
        u32OutPinYinLenMax: prepared Output UTF8 buffer length
        pu8OutMWPStr: Output Multiple Word Prefix String Buffer
        u32OutMWPLenMax: prepared Output Multiple Word Prefix buffer length
*/
void MMI_PHB_DH_ConvertSimToPinYin(const u8 u8InputLen, const u8 *pu8InputStr, u16 *pu16OutPinYinStr, u32 u32OutPinYinLenMax, boolean bIsNeedInsertOriginalCode, u8 *pu8OutMWPStr, u32 u32OutMWPLenMax);

#ifdef __UNICODE_TO_STROKE__
void MMI_PHB_DH_ConvertSimToStroke(const u8		u8InputLen,
								   const u8		*pu8InputStr,
								   u8	        *pu8OutStrokeStr,
								   u16			u16OutStrokeLenMax,
								   u8			*pu8OutMWPStr,
								   u16			u16OutMWPLenMax);
#endif

/*
    compare the number string.
    return :
        TRUE : if the string is match.
        FALSE : if the string is mismatch.
*/
boolean MMI_PHB_DH_NumberIsMatch(const u8 *pu8NumStr1, u8              u8NumLen1, const u8 *pu8NumStr2, u8             u8NumLen2);


MmiPhbReturn_e MMI_PHB_DH_InsertADNDataByADNIndex(void *pThis, MmiPhbBookType_e       s32PhbBookType, MmiPhbContactContent_t *data, u16                       u16ADNCnfIndex, u8                      u8InsertNumPos);

void MMI_PHB_DH_SetNumPosByPhysicalIdx(u16 u16PhysicalIdx, u8 u8NumPos);
u8 MMI_PHB_DH_GetNumPosByPhysicalIdx(u16 u16PhysicalIdx);


MmiPhbBJX_t *MMI_PHB_DH_GetBJXTable(void *pThis, MmiPhbBookType_e   s32PhbBookType, MmiPhbGroup_e     s32PhbGroup);

#ifdef __FUZZY_DIAL_SEARCH__

MmiPhbReturn_e MMI_PHB_DH_GetFilterContactsByNumber( void                                  *pThis,
                                                        MmiPhbBookType_e	    s32PhbBookType,
                                                        MmiPhbGroup_e         s32PhbGroup,
                                                        MAE_WChar               *pwcSearchStr,
                                                        VectorClass_t            *pIVCalllog,
                                                        MmiPhbSearchResultForNum_t	**ppatSearchResult,
                                                        u16	                    *pu16SearchResultTotal,
                                                        boolean	                bIsAllowADN_M,
                                                        boolean	                bIsAllowADN_S);
#endif

MmiPhbReturn_e MMI_PHB_DH_MultiWordPrefixSearch(void *pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, MAE_WChar *pwcSearchStr, MmiPhbDhSortByNameTable_t **ppatSearchResult, u16 *pu16SearchResultTotal, boolean bIsAllowADN_M, boolean bIsAllowADN_S, MMI_PHB_SEARCH_TYPE_E eSearchType);

#ifndef __SMALL_PHB_MMI__ 
MmiPhbReturn_e MMI_PHB_DH_SearchContactsByField(void *pThis, MmiPhbContactItemDataID_e   eSearch_Data, MmiPhbDhSortByNameTable_t **ppatSearchResult, u16 *pu16SearchResultTotal);
#endif

static u16 _mmi_PHB_DH_GetTotalUsedContactsNum(void);

boolean MMI_PHB_DH_GetAutoSaveFlag(void);
void MMI_PHB_DH_SetAutoSaveFlag(boolean bIsAutoSave);
__SLDPM_FREE__ void MMI_PHB_DH_AddReferenceToSortingTable(void);
void MMI_PHB_DH_ReleaseReferenceFromSortingTable(void);

void MMI_PHB_DH_AssignHashMapSrv(void *pIHashMapSrv);
MAE_Ret MMI_PHB_DH_RegHashID(MAE_WChar *pInputUrl, u32 *pOutputHashID);
MAE_Ret MMI_PHB_DH_DeregHashID(u32 *pOutputHashID);
MmiPhbReturn_e MMI_PHB_DH_ReEncodeSIM(u8 *pu8String, u8 *pu8StrLen, u8 u8MaxLen);

u16 MMI_PHB_DH_ConvertLocalSortingIdxToTotal(void *pThis, MmiPhbBookType_e   s32PhbBookType, MmiPhbGroup_e     s32PhbGroup, u16                    u16PhbSortingIdx);

#endif /* __MMI_PHB_DATA_HANDLE_H__ */

