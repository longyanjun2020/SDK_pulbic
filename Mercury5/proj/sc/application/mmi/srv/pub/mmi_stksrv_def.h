/**
 * @file mmi_stksrv_def.h
 *
 * SIMSRV structure definition
 *
 * $Id: mmi_stksrv_def.h 35920 2009-07-16 11:25:32Z ryb.chen $
 */
#ifndef __MMI_STKSRV_DEF_H__
#define __MMI_STKSRV_DEF_H__

#include "mmi_mae_langcode.h"
#include "mmi_common_sim.h"


enum
{
    STKSRV_SETUP_IDLE_TEXT = 1 << 0
,        //Setup Idle Text indication
    STKSRV_REFRESH = 1 << 1
,    //Refresh indication
    STKSRV_ALL_MASK = 0xFFFF
};

typedef u32 STKSRV_NOTIFY_MASK_e;

typedef enum
{
    STKSRV_RSP_OK = 0
,          //No error and user respond is included 
    STKSRV_RSP_HELP
,            //Help information require
    STKSRV_RSP_BACKWARD
,        //Backward move requested by user
    STKSRV_RSP_END_SESSION
,     //ME sends END session
    STKSRV_RSP_NO_RESPOND
,      //No respond from user
    STKSRV_RSP_BEYOND_CAP
,      //Beyond ME capability
    STKSRV_RSP_ME_UNABLE
,       //ME unable to process
    STKSRV_RSP_REFUSE_CALL      //User refuse the call
} STKSRV_RSP_RSLT_e;

#ifdef __3G_RIL_MMI__
typedef enum
{
  STKSRV_MENU_SEL,	                /* Select menu item */
  STKSRV_MENU_HELP,                /* Request help info for specific menu item */
  STKSRV_EVENT_IDLE,              /* Send idle screen event to SIM */
  STKSRV_EVENT_UA = 5,             /* Send user activity event to SIM */
  STKSRV_EVENT_LAN = 8,            /* Language Selection Event */
  STKSRV_EVENT_BROWSER_END,        /* Browser Termination Event */
  STKSRV_EVENT_DISP_CHANGE = 12    /* Display Parameters Changed */
} STKSRV_ACTION_TYPE_e;
#else //__3G_RIL_MMI__
typedef enum
{
    STKSRV_MENU_SEL
,            //Select menu item  
    STKSRV_MENU_HELP
,           //Request help info for specific menu item
    STKSRV_EVENT_IDLE
,          //Send idle screen event to SIM
    STKSRV_EVENT_UA             //Send user activity event to SIM
} STKSRV_ACTION_TYPE_e;
#endif //__3G_RIL_MMI__

#define STKSRV_STR_MAX          350
#define STKSRV_NUM_MAX          64

enum
{
    //STKSRV_CMD_IDLE = -2,    /* STK session terminated */
    //STKSRV_CMD_INVALID = -1,
    STKSRV_CMD_IDLE = 0xFFFE
   ,/* STK session terminated */
    STKSRV_CMD_INVALID = 0xFFFF
   ,STKSRV_CMD_SETUPMENU = 0
   ,/* SETUP MENU */
    STKSRV_CMD_DISPTEXT
   ,/* DISPLAY TEXT */
    STKSRV_CMD_GETINKEY
   ,/* GET INKEY */
    STKSRV_CMD_GETINPUT
   ,/* GET INPUT */
    STKSRV_CMD_SETUPCALL
   ,/* SETUP CALL */
    STKSRV_CMD_PLAYTONE
   ,/* PLAY TONE */
    STKSRV_CMD_SELITEM
   ,/* SEL ITEM */
    STKSRV_CMD_REFRESH
   ,/* REFRESH */
    STKSRV_CMD_SENDSS
   ,/* SEND SS */
    STKSRV_CMD_SENDSMS
   ,/* SEND SMS */
    STKSRV_CMD_SENDUSSD
   ,/* SEND USSD */
    STKSRV_CMD_SETUPEVTLIST
   ,/* SETUP EVENT LIST */
    STKSRV_CMD_SETIDLETEXT
   ,/* SETUP IDLE MODE TEXT */ 
    STKSRV_CMD_SENDDTMF
   ,/* SEND DTMF */
    STKSRV_CMD_LANG_NOTI
   ,/* LANGUAGE NOTIFICATION */
    STKSRV_CMD_LAUNCH_BROWSER
   ,/* LAUNCH BROWSER */   
#ifdef __3G_RIL_MMI__
    STKSRV_CMD_OPEN_CHANNEL
   ,/* open channel */
    STKSRV_CMD_SEND_DATA
   ,/* send data */
    STKSRV_CMD_RECEIVE_DATA
   ,/* receive data */
#endif // __3G_RIL_MMI__
    STKSRV_CMD_ERROR         /* ERROR */
};
typedef u32 STKSRV_CommandType_e;

typedef struct
{
    u8 Id;                         /* Menu item id */
    u8 padding1;
    u8 padding2;
    u8 padding3;
    u16 AlphaId[STKSRV_STR_MAX + 1];   /* Alpha indentifier of the menu item */
} STKSRV_MenuItem_t;

typedef struct
{
    boolean HelpInfoAvail;            /* Help information available if TRUE */
    u8 ItemNb;                   /* Number of items in the menu */
    u16 AlphaId[STKSRV_STR_MAX + 1];  /* Alpha indentifier of the main menu */
    STKSRV_MenuItem_t *MenuItem;                /* Menu item list*/
} STKSRV_SetupMenu_t;

typedef struct
{
    boolean HelpInfoAvail;             /* Help information available if TRUE */
    u8 ItemNb;                    /* Number of items in the menu */
    u8 DefaultItem;               /* Default item */
    u16 AlphaId[STKSRV_STR_MAX + 1];   /* Alpha indentifier of the menu */  
    STKSRV_MenuItem_t *MenuItem;                 /* Menu items. The size of this array is changeable, see following note */
} STKSRV_SelectItem_t; 

typedef struct
{
    boolean Prior;                /* TRUE if high priority */
    boolean ClearMode;            /* TRUE if wait for user to clear */
    u16 Text[STKSRV_STR_MAX + 1];/* Text to display */
} STKSRV_DisplayText_t; 

typedef enum
{
    STKSRV_INKEY_DIGIT
   ,/* 0-9, *, #, and + */
    STKSRV_INKEY_SMS_ALPHA
   ,/* SMS alphabet */
    STKSRV_INKEY_UCS2
   ,/* UCS2 */
    STKSRV_INKEY_YORN         /* Y or N (yes or no) */
} STKSRV_InkeyFormat_e;

typedef struct
{
    boolean HelpInfoAvail;              /* Help information available if TRUE */
    STKSRV_InkeyFormat_e InkeyFormat;                /* Inkey format */
    u16 TextInfo[STKSRV_STR_MAX + 1];  /* Text information */
} STKSRV_GetInkey_t; 

typedef enum
{
    STKSRV_INPUT_DIGIT
   ,/* 0-9, *, #, and + */
    STKSRV_INPUT_SMS_ALPHA
   ,/* SMS alphabet */
    STKSRV_INPUT_UCS2
   ,/* UCS2 */
    STKSRV_INPUT_UNPACKED
   ,/* Unpacker format */
    STKSRV_INPUT_PACKER       /* Packer format */
} STKSRV_InputFormat_e;

typedef struct
{
    boolean HelpInfoAvail;               /* Help information available if TRUE */
    boolean EchoMode;                    /* On if TRUE */
    u8 SizeMin;                     /* Input minimum length */
    u8 SizeMax;                     /* Input maximum length */
    STKSRV_InputFormat_e InputFormat;                 /* Input format */
    u16 TextInfo[STKSRV_STR_MAX + 1];   /* Text information */
    u16 DefaultText[STKSRV_STR_MAX + 1];/*Default input text */
} STKSRV_GetInput_t; 


typedef enum
{
    STKSRV_CALL_NO_CALL
   ,/* Setup call only when no other call */
    STKSRV_CALL_HOLD_OTHER
   ,/* Setup call and hold another call */
    STKSRV_CALL_DISC_OTHER  /* Setup call and disconnect another call */
} STKSRV_CallType_e;

typedef enum
{
    STKSRV_CALLCLASS_VOICE
   ,/* Voice call */
    STKSRV_CALLCLASS_DATA
   ,/* Data call */
    STKSRV_CALLCLASS_FAX     /* Fax call */
} STKSRV_CallClass_e;

typedef struct
{
    STKSRV_CallType_e Type;                       /* Call behavior */
    u8 CalledNb[STKSRV_NUM_MAX + 1];   /* Called party number */
    u8 SubAddress[STKSRV_NUM_MAX + 1]; /* Called party sub-address */
    STKSRV_CallClass_e Class;                      /* Call class */
    u16 AlphaId[STKSRV_STR_MAX + 1];   /* Text info for user confirmation phase */
    u16 AlphaId2[STKSRV_STR_MAX + 1];  /* Text info for call setup and calling phase */
} STKSRV_SetupCall_t;

typedef enum
{
    STKSRV_TONETYPE_DIAL
   ,/* Dial */ 
    STKSRV_TONETYPE_BUSY
   ,/* Busy */
    STKSRV_TONETYPE_CONGESTION
   ,/* Congestion */
    STKSRV_TONETYPE_RADIO_ACK
   ,/* Radio ack */
    STKSRV_TONETYPE_DROPPED
   ,/* Dropped */ 
    STKSRV_TONETYPE_ERROR
   ,/* Error */
    STKSRV_TONETYPE_CALLWAITING
   ,/* Call waiting */
    STKSRV_TONETYPE_RINGING
   ,/* Ringing */
    STKSRV_TONETYPE_GEN_BEEP
   ,/* General beep */
    STKSRV_TONETYPE_POS_BEEP
   ,/* Positive beep */
    STKSRV_TONETYPE_NEG_BEEP
   ,/* Negative beep */
    STKSRV_TONETYPE_UNSPECIFIED = 0xFF
} STKSRV_ToneType_e;

typedef struct
{
    u32 TimeInterval;                /* Time for tone playing */
    STKSRV_ToneType_e ToneType;                    /* Tone type */
    u16 TextInfo[STKSRV_STR_MAX + 1];   /* Text information */
} STKSRV_PlayTone_t; 

typedef struct
{
	//Mrl_STK_CmdQualInfo_e	  CmdQualifierInfo; 		  /* Command qualifier information from command detail object. */
	u16						  Url[STKSRV_STR_MAX+1]; 	  /* String format: 8bit data usng GSM default 7bit alphabet. */
	u8						  BrowserId;				  /* Browser Id to use. */
	//Mrl_STK_Bearer_e		  Bearer;					  /* Indicate list of allowed bearers in priority order. */
	//Mrl_Stlk_ProvFileInfo_t   ProvFileInfo; 			  /* Provinsioning file information. */
	u8						  GatewayInfo[STKSRV_STR_MAX+1]; 			   /* Gateway information. */
	u8						  AlphaId[STKSRV_STR_MAX+1];   /* String format: using either SMS default alphabet or UCS2. */
} STKSRV_LaunchBrowser_t; 

typedef enum
{
    STKSRV_REFRESH_SIM_FULLFILE
   ,/* SIM initialization and full file change notification */
    STKSRV_REFRESH_FILE
   ,/* File change notification */
    STKSRV_REFRESH_SIM_FILE
   ,/* SIM initialization and file change notification */
    STKSRV_REFRESH_SIM
   ,/* SIM initialization */
    STKSRV_REFRESH_SIM_RESET
   ,/* SIM reset */
} STKSRV_RefreshType_e;

typedef struct
{
    STKSRV_RefreshType_e RefreshType;  /* Refresh type */
} STKSRV_Refresh_t; 

typedef struct
{
    u16 TextInfo[STKSRV_STR_MAX + 1];  /* Text information */
} STKSRV_SendSs_t; 

typedef struct
{
    u16 TextInfo[STKSRV_STR_MAX + 1];  /* Text information */
} STKSRV_SendSms_t; 

typedef struct
{
    u16 TextInfo[STKSRV_STR_MAX + 1];  /* Text information */
} STKSRV_SendUssd_t; 

typedef struct
{
    u16 TextInfo[STKSRV_STR_MAX + 1];  /* Text information */
} STKSRV_SendDtmf_t; 

#ifdef __3G_RIL_MMI__
typedef enum
{
    STKSRV_EVT_USER = 0x05
   ,/* Reporting asked for "User Action" */
    STKSRV_EVT_IDLE = 0x06
   ,/* Reporting asked for "Idle Screen" */
    STKSRV_EVT_LAN_SEL = 0x08
   ,/* Reporting asked for "Language Selection" */
    STKSRV_EVT_BROWSER_END = 0x09
   ,/* Reporting asked for "Browser termination" event" */
    STKSRV_EVT_DISP_CHANGE  = 0x0c
   ,/* Reporting asked for "Display Parameters Changed event" */    
    STKSRV_EVT_CANCEL = 0xFF   /* Cancellation for reporting event */
} STKSRV_Evt_e;
#else //__3G_RIL_MMI__
typedef enum
{
    STKSRV_EVT_IDLE = 1
   ,/* Reporting asked for "Idle Screen" */
    STKSRV_EVT_USER = 2
   ,/* Reporting asked for "User Action" */
    STKSRV_EVT_IDLE_USER = 3
   ,/* Reporting asked for both "Idle Screen" and "User Action" */ 
    STKSRV_EVT_CANCEL = 4   /* Cancellation for reporting event */
} STKSRV_Evt_e;
#endif //__3G_RIL_MMI__

typedef struct
{
    STKSRV_Evt_e Evt; /* Setup event list */
} STKSRV_SetupEventList_t; 

typedef struct
{
    u16 Text[STKSRV_STR_MAX + 1];  /* Text to display */
} STKSRV_SetupIdleText_t; 

typedef struct
{
    boolean Specific;  /* TRUE if specific */
    MAE_LANG_CODE_e Lang;
} STKSRV_LanguageNoti_t; 

typedef enum
{
#ifdef __3G_RIL_MMI__
    STKSRV_ERROR_NO_STK = 0,   /* no stk */

    // No refresh end in TTPCom~~~
    STKSRV_ERROR_REFRESH_END = 89, /* Refresh end indication */   
    STKSRV_ERROR_END_SESSION = 81,   /* End session */
    STKSRV_ERROR_UNKNOWN = 0xFFFF,   /* unknown error */
#else // __3G_RIL_MMI__
    STKSRV_ERROR_REFRESH_END = 89
   ,/* Refresh end indication */
    STKSRV_ERROR_SIM_BUSY = 93
   ,/* "SMS-PP data download" failed due to SIM BUSY */
    STKSRV_ERROR_SIM_ERROR = 94
   ,/* "SMS-PP data download" failed due to SIM ERROR */
    STKSRV_ERROR_TIMEOUT = 98
   ,/* Timeout when no response from user */
    STKSRV_ERROR_END_SESSION = 99   /* End session */
#endif //__3G_RIL_MMI__
} STKSRV_Error_e;

typedef struct
{
    STKSRV_Error_e ErrorType;  /* Error type */
} STKSRV_Error_t; 

typedef union
{
    STKSRV_SelectItem_t StkSelectItem;
    STKSRV_DisplayText_t StkDisplayText;
    STKSRV_GetInkey_t StkGetInkey;
    STKSRV_GetInput_t StkGetInput;
    STKSRV_SetupCall_t StkSetupCall;
    STKSRV_PlayTone_t StkPlayTone;
    STKSRV_Refresh_t StkRefresh;
    STKSRV_SendSs_t StkSendSs;
    STKSRV_SendSms_t StkSendSms;
    STKSRV_SendUssd_t StkSendUssd;
    STKSRV_SendDtmf_t StkSendDtmf;
    STKSRV_SetupEventList_t StkSetupEventList;
    STKSRV_SetupIdleText_t StkSetupIdleText;
    STKSRV_LanguageNoti_t StkLanguageNoti;
    STKSRV_LaunchBrowser_t StkLaunchBrowser;
    STKSRV_Error_t StkError;
} STKSRV_Ind_t;

typedef enum    //mapping to Mrl_PWOF_Cfun_e

{
    PWOF_STOP
   ,PWOF_RESET
   ,PWOF_START
   ,PWOF_SIM_ONLY        /* SIM ON and protocol off  */
}PWOF_Type_e;

typedef enum
{
    PWON_OFF_LINE
   ,/* SIM off and protocol off                         */
    PWON_NORMAL
   ,/* SIM ON and protocol on                           */
    PWON_SIM_ONLY
   ,/* SIM ON and protocol off                          */
    PWON_PROTOCAL_ONLY    /* SIM Off and protocol On                          */
}PWON_Type_e;

#endif /* __MMI_STKSRV_DEF_H__ */
