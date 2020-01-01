/**
* @file mmi_messageeditorapp.h

* Class Id: CLSID_SEA
*
*
*/
#ifndef __MMI_MESSAGEEDITORAPP_H__
#define __MMI_MESSAGEEDITORAPP_H__

#include "mmi_common_sms_master.h"
#include "mmi_common_sms_tpdu.h"
#include "mmi_common_mms.h"
#include "mmi_message_cfg.h"
#include "mmi_phbsrv_def.h"
#include "mmi_base_util.h"

#define SEA_ENCODING_7BIT_CHARSIZE        7
#define SEA_ENCODING_UCS2_CHARSIZE        16
#define MAX_RECIPIENTS_SIZE               20
#define MAX_MMS_RECEPIENTS_SIZE		      20
#define MAX_RECIPIENTS_LENGTH_BYTE        (SMI_MAX_ADDR_LEN) *2
#define MAX_SMS_SIZE_BYTE_UCS2            (SEA_MULTI_PAGES_SIZE_UCS2*SEA_ENCODING_UCS2_CHARSIZE*9/8)
#define MAX_SMS_SIZE_BYTE 		          (SEA_MULTI_PAGES_SIZE_7BIT*SEA_ENCODING_7BIT_CHARSIZE*9/8) //(8*(1120/8-(UDHL_LEN+IEI_Concat8bitRn_TotalLen)) + 1120/8 ) // IEI_UDHL+IEI_ID_LEN+EMS_IEL+IEI_Concat8bitRn_IEDL for more than one pagesms
#define MAX_MMS_SUBJECT_SIZE_BYTE         (15*2)
#define PrefixChar                        '+'
#define ONE_PAGE                          1
#define MAX_MMS_SLIDE_DURATION            255*1000       // mini second
#define MIN_MMS_SLIDE_DURATION            1*1000         // mini second
#define MMI_MMS_LIMIT_SIZE_KB 			  (3)
#define MMS_SENDING_MIN_SIZE			  (512+496+256) //512 is MMS header estimation value, and 496 is SMIL header estimation value
#define MMS_OBJECT_HEADER_SIZE			  (128+40)	     //128 is MMS SLIDE SMIL object estimation value(384/3), and 40 is object header estimation value


#ifdef __MMS_MMI_CDMMS__
typedef struct SEA_MmsEditorInfo
{
    boolean bNeedToDeleteFile;
	MMI_MmsObjectType_e eAddType;
    MAE_WChar *pfilePath;                   // from vCard, vCalendar, and BT URL. but text content for text type
#ifdef __MMS_MMI_CDMMS_TEMPLATE__
    boolean PreviewOnly;
    u8 TemplateIdx;
#endif	
}SEA_MmsEditorInfo_t;

typedef struct SEA_MmsSlideTag
{
    MMI_MMS_Slide_Link_t tSlideData;        // for interface saving, must at first
    MSG_MMS_TEXT_LOCATION_e eTextLoc;       // text location;
    MSG_MMS_IMAGE_SIZE_e eImageSizeType ;   // for image widget size
} SEA_MmsSlide_t;
#endif //__MMS_MMI_CDMMS__

/****************COMMON*************************/
enum
{
    SEA_Start_e_SMS_NewEditor           =0x0001,
    SEA_Start_e_SMS_NewEditorWithVCard  =0x0002,
    SEA_Start_e_SMS_ReplyEditor         =0x0004,
    SEA_Start_e_SMS_ForwardEditor       =0x0008,
	SEA_Start_e_SMS_DraftEditor           =0x0010,
    SEA_Start_e_SMS_Mask                =0x00FF,
#ifdef __MMS_MMI_CDMMS__
    SEA_Start_e_MMS_NewEditor           =0x0100, // with MsgID(draft), ContentID(filemanager),URL(vCard)
    SEA_Start_e_MMS_ReplyEditor         =0x0200, // with pRecipients
    SEA_Start_e_MMS_ForwardEditor       =0x0400, // with MSGID, eMsglocation
	SEA_Start_e_MMS_NewEditorWithVCard  =0x0800,
	SEA_Start_e_MMS_DraftEditor           =0x1000,
    SEA_Start_e_MMS_Mask                =0xFF00,
#endif
};

typedef u16 SEA_StartType_e;

enum
{
    SEA_RECIPIENT_TYPE_SMS =0,
    SEA_RECIPIENT_TYPE_MMS_TO,
    SEA_RECIPIENT_TYPE_MMS_CC,
    SEA_RECIPIENT_TYPE_MMS_BCC
};
typedef u8 SEA_RecipientType_e;

/* the recipient item */
typedef struct SEA_Recipient
{
    MAE_WChar* Name;
    MAE_WChar* number;
    SEA_RecipientType_e eType;
}SEA_Recipient_t;

typedef union
{
  MAE_WChar           *pContentText;     // for SMS
#ifdef __MMS_MMI_CDMMS__
  SEA_MmsEditorInfo_t *pMmsEditorData;   // for MMS
#endif
}SEA_Content_t;

typedef struct SEA_Editor_Info
{
    SEA_StartType_e StarType;
    u32 MsgID;                  //Msg Id
    SMI_MsgLocation_e eMsglocation;    // msg location e.g.mlInbox
    VectorClass_t *pRecipients;      // store the list of items , for create
    SEA_Content_t tContent;
#ifdef __MMI_SMS_CHAT__
	boolean bIsForwardLengthTooLong;
#endif
}SEA_EDITOR_Info_t;


/**
 * Functions
 */

MAE_Ret SeaNew(MAE_ClsId id, void **ppObj);

extern void SEA_FreeStartParam(IBase *pIssuer, u32 Param);
extern MAE_Ret SEA_DuplicateStartParam(IBase *pThis,SEA_EDITOR_Info_t *pInitData ,SEA_EDITOR_Info_t **pOutInitData );

/*-------------------------------------------------------------------------*/
#endif /* __MMI_MESSAGEEDITORAPP_H__ */
