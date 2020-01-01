#ifndef __MMI_COMMON_MESSAGEVIEWER_TYPE_H__
#define __MMI_COMMON_MESSAGEVIEWER_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_common_sms_master.h"
#include "mmi_messageorganizationsrv.h" //for MOI_SMS_SIZE_MAX

typedef enum
{
    PHONE_SMS = 0,  
    SIM_SMS_MASTER, // single or master
    SIM_SMS_SLAVE,
    CBSMS,
    CBNEW,
    SMS_CLASS0,
    MMS,
    MMS_PREVIEW,
    OTA_PROVISION
} SMS_VIEWER_TYPE_e;

typedef struct
{
    SMI_MsgID_t msgID;
    SMS_VIEWER_TYPE_e msgType;
    SMI_MsgLocation_e elocation;
    SMI_MsgFlag msgFlag;
#ifdef __MMI_SMS_WAPPUSH__
	SMI_MsgType_e eMsgMtType;
#endif
    MAE_WChar *pContent;
    MAE_WChar *pSender;
} SVA_INIT_DATA_t;

typedef struct SVA_CLASS0_STACK_ITEM_TAG {
    SMI_SmEncoding_t    Encoding;
    u16                 Reference;
	u8                  PduData[MOI_SMS_SIZE_MAX];
	u8                  DataLength;    
    u8                  HeaderLen;
    u8                  MaxPartNum;
    u8                  PartNum;
	u8                  SimModule;
    u8                  TPUDHeaderLen;
} SVA_Class0_Stack_Item_t;

typedef struct SVA_CLASS0_STACK_GROUPITEM_TAG {
    u8  NumItems;
    u8  reservied[3];
    SVA_Class0_Stack_Item_t *pItems;
} SVA_Class0_Stack_GroupItem_t;

#endif //__MMI_COMMON_MESSAGEVIEWER_TYPE_H__
