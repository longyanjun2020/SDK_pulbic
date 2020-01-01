#ifndef __MMI_COMMON_MESSAGECENTER_TYPE_H__
#define __MMI_COMMON_MESSAGECENTER_TYPE_H__

#include "mmi_mae_common_def.h"
#include "mmi_launcher_mca.h" //for definition of NewMsgNum_t

/*
 * Data type definition of messagecenterapp that is needed by other libraries
 * */

typedef enum
{
	MCA_E_START_MENU=0x00,
	MCA_E_START_MENU_AND_CLOSE_CURRENT_FUNCTION,
	MCA_E_START_BOX_MENU,
#ifdef __3D_MESSAGE_BOX__   
    MCA_E_START_3D_BOX_MENU,    
#endif
	MCA_E_START_NEW_SMS_EDITOR,
	MCA_E_START_REPLY_FORWARD_SMS_EDITOR,
	MCA_E_START_SMS_VIEWER,
#ifdef __MMS_MMI_CDMMS__
	MCA_E_START_NEW_MMS_EDITOR,
	MCA_E_START_REPLY_FORWARD_MMS_EDITOR,
	MCA_E_START_MMS_VIEWER,
#endif
	MCA_E_START_DIAL_VOICE_MAIL_NUMBER,
	MCA_E_START_DIAL_VOICE_MAIL_NUMBER_WITH_MASTER_SIM,
	MCA_E_START_DIAL_VOICE_MAIL_NUMBER_WITH_SLAVE_SIM,
	MCA_E_START_TYPE_TOTAL,
} e_MCA_START_TYPE;

typedef enum
{
	MCA_E_MAIN_MENU=0x00,
	MCA_E_BOX_START=0x01,
	MCA_E_INBOX=0x01,
	MCA_E_DRAFT=0x02,
	MCA_E_OUTBOX=0x03,
	MCA_E_SENTBOX=0x04,
	MCA_E_CB_BOX = 0x05,
	MCA_E_NOT_PRIVATE_TOTAL,
	MCA_E_BOX_MASK=0xFF
} e_MCA_MENU_BOX;

#ifdef __MMI_SMS_EXPORT__
typedef enum
{
    MCA_E_EXPORT_TO_PHONE=0x00,
    MCA_E_EXPORT_TO_SD=0x01,
#if defined(__DUAL_CARD__)
    MCA_E_EXPORT_TO_SD2=0x02,
#endif
} e_MCA_EXPORT_DEST;
#endif
typedef struct
{
	e_MCA_START_TYPE StartType;
	void *pStartData;               //(SEA_EDITOR_Info_t *) or (SVA_INIT_DATA_t *)
	e_MCA_MENU_BOX EntryMenuBox;
#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
	NewMsgNum_t tNewMessageNum;
	boolean bIsClass0SMSSaving;
	SMI_SmsSimMsgBox_e RecentClass0SMSSimBox;
#endif
    boolean bShowFullNotice;
} MCA_Start_t;

#endif //__MMI_COMMON_MESSAGECENTER_TYPE_H__
