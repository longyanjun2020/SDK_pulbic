/**
 * \file    mmi_cfgsrv_common_table_priv.h
 * \brief   common define
 * \author  eric.chen@mstarsemi.com
 *
 * \page    Configuration Service
 *
 *  @version $Id:$
 */

#ifndef __MMI_CFGSRV_COMMON_TABLE_PRIV_H__
#define __MMI_CFGSRV_COMMON_TABLE_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_cfgsrv_common_table.h"


//#define ItemSize( type, field ) sizeof( ((type *) 0)->field )
//
//#ifdef __arm
////#undef offsetof
////#include <stddef.h>
////#define ItemPOS(type, field) __INTADDR__(offsetof(type, field))
//
//#define ItemPOS(type, field) /*lint -save -e545 */ ((u32)__INTADDR__ ((void*)&(((type*)0)->field))) /*lint -restore */
//
////#define offsetof(t, memb) ((__CLIBNS size_t)__INTADDR__(&(((t *)0)->memb)))
//#else
//  #define ItemPOS(type, field) ((u32) &((type*) 0)->field)
//#endif
//
//                                   //(  & ((type *)NULL)->field    )
//#ifndef ARR_SIZE
//   #define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))
//#endif

/*
 * When __DLM_MRFILE_BUFFER__ is set,
 * put the two big tables DefaultMItemAllowMRFileBuffer and
 * DefaultMItemNotAllowMRFileBuffer into a sldlm (static link dynamic load
 * module) to save code size.
 * */
#if defined(__DLM_MRFILE_BUFFER__) && defined(__TARGET__) && defined(__arm)
#define __MRFILE_BUFFER_SECTION__ __attribute__((section(".mrfile_buffer")))
#else
#define __MRFILE_BUFFER_SECTION__
#endif





/*********************************************************************
*
*                       CFG Item Path
*
*********************************************************************/
#define CFG_ITEM_ROOT_PATH "fs:/PHON/cfg/"

#define TEMP ".temp"
#define DEFAULT_FOLDER "default/"

#define MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME             "mitemallowmrfile"
#define TEMP_MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME        MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME TEMP

#define MULTIPLE_ITEMS_NOTALLOW_MASTER_RESET_FILE_NAME          "mitemnotallowmrfile"
//#define TEMP_MULTIPLE_ITEMS_NOTALLOW_MASTER_RESET_FILE_NAME       MULTIPLE_ITEMS_NOTALLOW_MASTER_RESET_FILE_NAME TEMP

#define CACHE_ITEM_FILE_NAME                                    "cachefile"
#define TEMP_CACHE_ITEM_FILE_NAME                               CACHE_ITEM_FILE_NAME TEMP

#define INFO_ITEM_FILE_NAME                                     "infofile"


#define END_DIR_PATH                                                '/'
#define SINGLE_ITEM_PATH_PREFIX                                     CFG_ITEM_ROOT_PATH
#define MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_FILE_PATH         CFG_ITEM_ROOT_PATH  MULTIPLE_ITEMS_NOTALLOW_MASTER_RESET_FILE_NAME//"fs:/PHON/cfg/mitemnotallowmrfile"
#define MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_FILE_PATH            CFG_ITEM_ROOT_PATH  MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME//"fs:/PHON/cfg/mitemallowmrfile"
#define CACHE_ITEMS_FILE_PATH                                       CFG_ITEM_ROOT_PATH  CACHE_ITEM_FILE_NAME                              //"fs:/PHON/cfg/cachefile"
#define INFO_ITEM_FILE_PATH                                         CFG_ITEM_ROOT_PATH INFO_ITEM_FILE_NAME

#define DEFAULT_SINGLE_ITEM_PATH_PREFIX                             CFG_ITEM_ROOT_PATH DEFAULT_FOLDER
#define DEFAULT_MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_FILE_PATH CFG_ITEM_ROOT_PATH DEFAULT_FOLDER MULTIPLE_ITEMS_NOTALLOW_MASTER_RESET_FILE_NAME//"fs:/PHON/cfg/defalut/mitemnotallowmrfile"
#define DEFAULT_MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_FILE_PATH    CFG_ITEM_ROOT_PATH DEFAULT_FOLDER MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME//"fs:/PHON/cfg/defalut/mitemallowmrfile"
#define DEFAULT_CACHE_ITEMS_FILE_PATH                                CFG_ITEM_ROOT_PATH DEFAULT_FOLDER CACHE_ITEM_FILE_NAME//"fs:/PHON/cfg/defalut/cachefile"



#define TEMP_MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_FILE_PATH            CFG_ITEM_ROOT_PATH TEMP_MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME
#define TEMP_CACHE_ITEMS_FILE_PATH                                       CFG_ITEM_ROOT_PATH TEMP_CACHE_ITEM_FILE_NAME

//#define UCS2_TEMP_MULTIPLE_ITEMS_ALLOW_MASTER_RESET_FILE_NAME          L"mitemallowmrfile.temp"



#define CFGSRV_MAX_READ_DEFAULT_FILE_BUFFER 256

#define ITEMS_FILE_HEADER_LEN 12    // version(u32) + file size(u32) + last item(u32)



typedef struct MMI_CFGSRV_ITEM_FILE_HEADER_TAG
{
    u32 Version;
    u32 FileSize;
    CFGItemID_e LastItemID;
} MMI_CFGSRV_ITEM_FILE_HEADER;


typedef struct MMI_CFGSRV_MULTIPLE_ITEM_FILE_ENTITY_TAG
{
#ifdef __MAE_DEBUG__
    CFGItemID_e ItemID;
#endif//#ifdef __MAE_DEBUG__
    u32 ItemSize;
    u32 ItemPos;
} MMI_CFGSRV_MULTIPLE_ITEM_FILE_ENTITY;


#ifdef __USE_CFG_SITEM__
typedef struct MMI_CFGSRV_SINGLE_ITEM_FILE_ENTITY_TAG
{
#ifdef __MAE_DEBUG__
    CFGItemID_e ItemID;
#endif
    u8 *FilePath;
    u32 ItemSize;
} MMI_CFGSRV_SINGLE_ITEM_FILE_ENTITY;
#endif//__USE_CFG_SITEM__


typedef struct
{
    CFGSrvItemType_e ItemType;
    const char *pStrFilePath;
}CFGCheckList_t;


MAE_Ret MMI_ICFGSrv_GetDefaultCItemFile(void **ppDefaultFileBuffer);
MAE_Ret MMI_ICFGSrv_GetDefaultMItemFileAllowMR(void **ppDefaultFileBuffer);
MAE_Ret MMI_ICFGSrv_GetDefaultMItemFileNotAllowMR(void **ppDefaultFileBuffer);
MAE_Ret MMI_ICFGSrv_GetDefaultInfoFile(void **ppDefaultFileBuffer);


#endif//__MMI_CFGSRV_COMMON_TABLE_PRIV_H__
