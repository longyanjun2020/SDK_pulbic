/**
 * \file    mmi_cfgsrv_common_table.h
 * \brief   common define
 * \author  eric.chen@mstarsemi.com
 *
 * \page    Configuration Service
 *
 *  @version $Id: mmi_cfgsrv_common_table.h 28082 2009-04-12 12:48:34Z eric.chen $  
 */

#ifndef __MMI_CFGSRV_COMMON_TABLE_H__
#define __MMI_CFGSRV_COMMON_TABLE_H__

#include "mmi_mae_common_def.h"



#define ItemSize( type, field ) sizeof( ((type *) 0)->field )

#if defined(__arm__) && defined(__ARMCC_VERSION)
//#undef offsetof
//#include <stddef.h>
//#define ItemPOS(type, field) __INTADDR__(offsetof(type, field))

#define ItemPOS(type, field) /*lint -save -e545 */ ((u32)__INTADDR__ ((void*)&(((type*)0)->field))) /*lint -restore */

//#define offsetof(t, memb) ((__CLIBNS size_t)__INTADDR__(&(((t *)0)->memb)))
#else
// disabled lint warning 545 when the macro is applied to an array member
#define ItemPOS(type, field) /*lint -save -e545 */ ((u32)&((type*)0)->field) /*lint -restore */
#endif

//(  & ((type *)NULL)->field    )
#ifndef ARR_SIZE
#define ARR_SIZE(a)  (sizeof((a))/sizeof((a[0])))
#endif

typedef u32 CFGItemID_e;



/*********************************************************************
*
*                           CGF Item Type
*
*********************************************************************/
//#define __USE_CFG_SITEM__
typedef enum
{
    CACHE_CFG_ITEM = 0X0000
   ,NON_MASTER_RESET_CFG_ITEM
   ,MASTER_RESET_CFG_ITEM
   ,
#ifdef __USE_CFG_SITEM__
    SINGLE_CFG_ITEM
   ,
#endif  
    INFO_ITEM
   ,LAST_ITEM_TYPE
}CFGSrvItemType_e;


#define CFGSRV_ITEM_TYPE_BITS   (16)

#define GET_CFGSRV_ITEM_TYPE(_ItemId)\
        (CFGSrvItemType_e)((_ItemId)>>CFGSRV_ITEM_TYPE_BITS)
/*********************************************************************
*
*                            Cache Item
*
*********************************************************************/

#define CFGSRV_ITEM_START_ID (0x0000)
#define CFGSRV_ITEM_END_ID (0xFFFF)

//Vaild Range is 0X00010000 ~ 0X0001FFFF
#define CACHE_ITEMS_FILE_START                              (((CACHE_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_START_ID)
#define CACHE_ITEMS_FILE_END                                (((CACHE_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_END_ID)

/*********************************************************************
*
*              Not allow master reset
*
*********************************************************************/
//Valid Range is 0X00020000 ~ 0X0002FFFF
#define MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_START      (((NON_MASTER_RESET_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_START_ID)
#define MULTIPLE_ITEMS_FILE_NOTALLOW_MASTER_RESET_END        (((NON_MASTER_RESET_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_END_ID)

/*********************************************************************
*
*               Allow master reset item
*
*********************************************************************/
//Vaild Range is 0X00030000 ~ 0X0003FFFF
#define MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_START       (((MASTER_RESET_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_START_ID)
#define MULTIPLE_ITEMS_FILE_ALLOW_MASTER_RESET_END         (((MASTER_RESET_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_END_ID)

/*********************************************************************
*
*                       Single Item 
*
*********************************************************************/
//Vaild Range is 0X00040000 ~ 0X0004FFFF
#define SINGLE_ITEMS_FILE_START                             (((SINGLE_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_START_ID)
#define SINGLE_ITEMS_FILE_END                               (((SINGLE_CFG_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_END_ID)



/*********************************************************************
*
*                      Information Related Items 
*
*********************************************************************/
//Vaild Range is 0X00050000 ~ 0X0005FFFF
#define INFO_ITEM_START                                 (((INFO_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_START_ID)
#define INFO_ITEM_END                                   (((INFO_ITEM)<<CFGSRV_ITEM_TYPE_BITS)|CFGSRV_ITEM_END_ID)



#endif//__MMI_CFGSRV_COMMON_TABLE_H__
