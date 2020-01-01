#ifndef __MMI_COMMON_VENDOR_TYPE_H__
#define __MMI_COMMON_VENDOR_TYPE_H__

#include "mmi_mae_common_def.h"
/*
 * Data type definition of vendorapp that is needed by other libraries
 * */

#ifdef __TENCENT_MCARE__
enum
{
    VENDORAPP_START_TQQ_E_ENTRY_DEFAULT = 0,            //Default Tencent MCare Info. Center
    VENDORAPP_START_TQQ_E_ENTRY_QQB,                    //QQ browser
    VENDORAPP_START_TQQ_E_ENTRY_QQDDZ,                  //QQ DDZ (not support now)
    VENDORAPP_START_TQQ_E_ENTRY_QZONE,                  //QQ zone
    VENDORAPP_START_TQQ_E_ENTRY_QQBOOKMALL,             //QQ bookmall
    VENDORAPP_START_TQQ_E_ENTRY_QQBOOKMALL_FREE,        //QQ bookmal free
    VENDORAPP_START_TQQ_E_ENTRY_QQMICROBLOG,            //QQ micro blog
    VENDORAPP_START_TQQ_E_ENTRY_SOSO,                   //QQ soso
    VENDORAPP_START_TQQ_E_ENTRY_FRIEND,                 //QQ friend
    VENDORAPP_START_TQQ_E_ENTRY_QQMAIL,                 //QQ mailbox
    VENDORAPP_START_TQQ_E_ENTRY_QQNEWS,                 //QQ news
    VENDORAPP_START_TQQ_E_ENTRY_QQSTOCK,                //QQ stock
    VENDORAPP_START_TQQ_E_ENTRY_QQENTERTAINMENT,        //QQ entertainment
    VENDORAPP_START_TQQ_E_ENTRY_QQSPORTS,               //QQ sports
    VENDORAPP_START_TQQ_E_ENTRY_QQFARM,                 //QQ farm
    VENDORAPP_START_TQQ_E_ENTRY_QQPASTURE,              //QQ pasture
    VENDORAPP_START_TQQ_E_ENTRY_QQHOUSELAND,            //QQ house land
    VENDORAPP_START_TQQ_E_ENTRY_QQCLAN,                 //QQ clan
    VENDORAPP_START_TQQ_E_ENTRY_QQMAGICGARDEN,          //QQ magic garden
    VENDORAPP_START_TQQ_E_ENTRY_QQSUNNYPASTURE,         //QQ sunny pasture
    VENDORAPP_START_TQQ_E_ENTRY_QQJINGWUTANG,           //QQ jing wu tang
    VENDORAPP_START_TQQ_E_ENTRY_QQDELICIOUSTOWN,        //QQ delicious town
    VENDORAPP_START_TQQ_E_ENTRY_QQANIMALHERO,           //QQ animal hero
    VENDORAPP_START_TQQ_E_ENTRY_QQLOVEPET,              //QQ love pet
    VENDORAPP_START_TQQ_E_ENTRY_MAX,                    //Dummy for end of QQ enum
};
typedef u8 VendorAppTqqStartParam_e;
#endif /* __TENCENT_MCARE__ */

typedef struct _VendorApp_StartParam
{
    MAE_WChar *pDisplayName; // Vendor's display name with NULL terminate
    void *pData;   // Pointer to specific data for vendor launch
    u32  nDataLen; // Byte length of data
    boolean bNeedMemCard; // Need Memory card or not
} VendorApp_StartParam_t;

#endif // __MMI_COMMON_VENDOR_TYPE_H__
