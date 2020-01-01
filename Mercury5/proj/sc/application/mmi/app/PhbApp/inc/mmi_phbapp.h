////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_phpapp.h
* @version $Id: mmi_phbapp.h 2010-01-13 11:30:23Z shin.lin $
* @brief   Phonebook applet header file
*
*/

#ifndef __MMI_PHBAPP_H__
#define __MMI_PHBAPP_H__

/*-------------------------------------------------------------------------*/
/*
Include
*/
#include "mmi_phbsrv.h"
#include "mmi_launcher_phb.h"
#include "mmi_mae_arraymodel.h"

/*
    Enum
*/

enum
{
    PHB_AP_FID_UNKNOWN                              = 0,

    PHB_AP_FID_VIEW                                     = 1,    /* Browse phonebook list from menu. */
    PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER                 = 2,    /* Add an new contact with number from SMS/MMS/Idle/Call Log. */
    PHB_AP_FID_SAVE_CONTACT_WITH_IMAGE_ID               = 3,    /* Add an new contact with image ID from file manager. */
    PHB_AP_FID_SAVE_CONTACT_WITH_RING_ID                = 4,    /* Add an new contact with ring ID from file manager. */
#ifndef __SMALL_PHB_MMI__    
    PHB_AP_FID_SAVE_CONTACT_WITH_EMAIL                  = 5,    /* Add an new contact with email from email client/MMS. */
    PHB_AP_FID_SAVE_CONTACT_WITH_URL                    = 6,    /* Add an new contact with url from WAP/MMS. */
#endif    
    PHB_AP_FID_SAVE_CONTACT_WITH_DETAILS                = 7,    /* Save a contact's details to SIM or phone. */
    PHB_AP_FID_SAVE_CONTACT_WITH_VCARD                  = 8,    /* Save a vCard from MMS as a contact to SIM or phone. */
    PHB_AP_FID_EDIT_CG_WITH_IMAGE_ID                    = 9,    /* Edit a caller group with image ID from file manager. */
    PHB_AP_FID_EDIT_CG_WITH_RING_ID                     = 10,   /* Edit a caller group with ring ID from file manager. */
    PHB_AP_FID_SELECT_CONTACT_AS_VCARD                  = 11,   /* Select a contact and encode as vCard, then insert to MMS or Email. */
    PHB_AP_FID_SELECT_CONTACT_DETAILS                   = 12,   /* Select a contact's details for SMS. */
    PHB_AP_FID_SELECT_CONTACT_NAME_NUMBER               = 13,   /* Select a contact's name and number for SMS or MMS. */
#ifndef __SMALL_PHB_MMI__
    PHB_AP_FID_SELECT_CONTACT_EMAIL                     = 14,   /* Select a contact's email for email client. */
    PHB_AP_FID_SELECT_CONTACT_NAME_NUMBER_EMAIL         = 15,   /* Select a contact's name and number for SMS or MMS. */
    PHB_AP_FID_SELECT_CONTACT_NAME_EMAIL                = 16,   /* Select a contact's email and name for email client. */
#endif
    PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER        = 17,   /* Multi-select contacts' name and numbers for SMS or MMS. */
#ifndef __SMALL_PHB_MMI__    
    PHB_AP_FID_SELECT_MULTI_CONTACTS_EMAIL              = 18,   /* Multi-select contacts' email for email client. */
    PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER_EMAIL  = 19,   /* Multi-select contacts' name and numbers for SMS or MMS. */
    PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_EMAIL         = 20,   /* Select a contact's email and name for email client. */
#endif    
    PHB_AP_FID_SHOW_BUSINESS_CARD                       = 21,   /* Show business card. */
    PHB_AP_FID_SHOW_MY_NUMBER                           = 22,   /* Show my number list. */
    PHB_AP_FID_QUICK_DIAL                               = 23,   /* Abbreviated dialling code. */
    PHB_AP_FID_SELECT_CONTACT_MAKE_CALL                 = 24,   /* Select a contact and make a MO all. */
    PHB_AP_FID_IMPORT_WITH_FILES                        = 25,   /* Import contacts with a file array */
    PHB_AP_FID_SHOW_CONTACT_DETAILS                     = 26,                     /* Show  a contact's details by   u16PhbPhysicalIdx  , add by zq.li 2009.8.26 */
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__   
    PHB_AP_FID_SAVE_CONTACT_WITH_VIDEO_ID               = 27,    /* Add an new contact with video ID from file manager. */
    PHB_AP_FID_MAX                                      = 27
#else
    PHB_AP_FID_MAX                                      = 26
#endif
};

typedef s32 MMI_PHB_AP_FID_E;

#if defined(__3D_UI_PHONEBOOK__)
enum
{
    //view-entering
    MMI_PHB_ANISTATE_EMPTY = 0, 
    MMI_PHB_ANISTATE_FLIP_ANIMATION_START,
    MMI_PHB_ANISTATE_FLIP_ANIMATION_2ND_STEP,    
    MMI_PHB_ANISTATE_FLIP_ANIMATION_END,    
    //Page-changing 
    MMI_PHB_ANISTATE_ROTATE_ANIMATION_START,
    MMI_PHB_ANISTATE_ROTATE_ANIMATION_END,  
    //Page-changing fail
    MMI_PHB_ANISTATE_FAIL_ANIMATION_START,
    MMI_PHB_ANISTATE_FAIL_ANIMATION_END,    
};
typedef u8 MmiPhbApAnimationState_e;

enum
{
    MMI_PHB_HALFVIEW_CURRENT_IMG = 0,
    MMI_PHB_HALFVIEW_NEXT_IMG,
    MMI_PHB_HALFVIEW_TOTAL_NUM
};
typedef u8 MmiPhbApHalfViewImageType_e;

#endif //end of #if defined(__3D_UI_PHONEBOOK__)

/*
    Structure
*/


typedef struct
{
    MAE_WChar               wcName[MMI_PHB_NAME_LEN+1];     /* +1 is for null termination. */
} MmiPhbApName_t;

typedef struct
{
    MAE_WChar               wcNumber[MMI_PHB_NUMBER_LEN+1]; /* +1 is for null termination. */
} MmiPhbApNumber_t;

#ifndef __SMALL_PHB_MMI__ 
typedef struct
{
    MAE_WChar               wcEmail[MMI_PHB_EMAIL_LEN+1];   /* +1 is for null termination. */
} MmiPhbApEmail_t;

typedef struct
{
    MAE_WChar               wcUrl[MMI_PHB_URL_LEN+1];       /* +1 is for null termination. */
} MmiPhbApUrl_t;

typedef struct
{
    MAE_WChar               wcText[MMI_PHB_TEXT_MAX+1];     /* +1 is for null termination. */
} MmiPhbApText_t;
#endif

typedef struct
{
	MAE_WChar               wcFilePath[PHB_MAX_FILEPATH_SIZE];       /* UCS2 Format. */
} MmiPhbApFilePath_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_VIEW */
    MmiPhbBookType_e     s32PhbBookType;
    u16                     u16PhbSortingIdx;
	boolean					bNeedGroupWdg;
} MmiPhbApFidView_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_NUMBER */
    MmiPhbApNumber_t        tPhbApNumber;       /* UCS2 Format. */
} MmiPhbApFidSaveContactWithNumber_t;


typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_IMAGE_ID */
    MmiPhbApFilePath_t      tPhbApFilePath;     /* UCS2 Format. */
} MmiPhbApFidSaveContactWithImageId_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_RING_ID */
    MmiPhbApFilePath_t      tPhbApFilePath;     /* UCS2 Format. */
} MmiPhbApFidSaveContactWithRingId_t;

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_VIDEO_ID */
    MmiPhbApFilePath_t      tPhbApFilePath;     /* UCS2 Format. */
} MmiPhbApFidSaveContactWithVideoId_t;
#endif

#ifndef __SMALL_PHB_MMI__
typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_EMAIL */
    MmiPhbApEmail_t         tPhbApEmail;        /* UCS2 Format. */
} MmiPhbApFidSaveContactWithEmail_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_URL */
    MmiPhbApUrl_t           tPhbApUrl;          /* UCS2 Format. */
} MmiPhbApFidSaveContactWithUrl_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_CONTACT_EMAIL */
    MmiPhbBookType_e     	s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    MmiPhbApName_t          tPhbApName;         /* UCS2 Format. */
    MmiPhbApEmail_t         tPhbApEmail;        /* UCS2 Format. */
} MmiPhbApFidSelectContactNameEmail_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_CONTACT_EMAIL */
    MmiPhbApEmail_t         tPhbApEmail;        /* UCS2 Format. */
} MmiPhbApFidSelectContactEmail_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_MULTI_CONTACTS_EMAIL */
    u16                     u16PhbMaxContacts;  /* Only support MMI_PHB_BOOK_TYPE_ADR. */
    MmiPhbApEmail_t         *ptPhbApEmail;      /* UCS2 Format, allocate and release by caller AP. */
} MmiPhbApFidSelectMultiContactsEmail_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_MULTI_CONTACTS_EMAIL */
    MmiPhbBookType_e     s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    u16                     u16PhbMaxContacts;  /* Only support MMI_PHB_BOOK_TYPE_ADR. */
    MmiPhbApName_t          *ptPhbApName;       /* UCS2 Format, allocate and release by caller AP. */
    MmiPhbApEmail_t         *ptPhbApEmail;      /* UCS2 Format, allocate and release by caller AP. */
} MmiPhbApFidSelectMultiContactsNameEmail_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER_EMAIL */
    MmiPhbBookType_e     s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    u16                     u16PhbMaxContacts;
    MmiPhbApName_t          *ptPhbApName;       /* UCS2 Format, allocate and release by caller AP. */
    MmiPhbApText_t          *ptPhbApText;       /* UCS2 Format, allocate and release by caller AP. */
    /* ptPhbApText will store number or email. */
} MmiPhbApFidSelectMultiContactsNameNumberEmail_t;

#endif //#ifndef __SMALL_PHB_MMI__

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_DETAILS */
    MmiPhbContactContent_t  tPhbContactContent; /* SIM Format. */
} MmiPhbApFidSaveContactWithDetails_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SAVE_CONTACT_WITH_VCARD */
    u8                      *pu8vCard;          /* vCard Format. */
    u16                     u16VCardLen;
} MmiPhbApFidSaveContactWithvCard_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_EDIT_CG_WITH_IMAGE_ID */
    u32                     u32PhbImageId;
} MmiPhbApFidEditCGWithImageId_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_EDIT_CG_WITH_RING_ID */
    u32                     u32PhbRingId;
} MmiPhbApFidEditCGWithRingId_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_CONTACT_AS_VCARD */
    MmiPhbBookType_e     s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    u8                      *pu8vCard;          /* vCard Format. */
} MmiPhbApFidSelectContactAsvCard_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_CONTACT_DETAILS */
    MmiPhbBookType_e     s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    MmiPhbContactContent_t  tPhbContactContent; /* SIM Format. */
} MmiPhbApFidSelectContactDetails_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_CONTACT_NAME_NUMBER */
    MmiPhbBookType_e     	s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    MmiPhbApName_t          tPhbApName;         /* UCS2 Format. */
    MmiPhbApNumber_t        tPhbApNumber;       /* UCS2 Format. */
	u32 					u32ContactImageId;	/* Out: Contact Image ID. */
} MmiPhbApFidSelectContactNameNumber_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SELECT_MULTI_CONTACTS_NAME_NUMBER */
    MmiPhbBookType_e     s32PhbBookType;     /* Only support MMI_PHB_BOOK_TYPE_ADN and MMI_PHB_BOOK_TYPE_ADR. */
    u16                     u16PhbMaxContacts;
    MmiPhbApName_t          *ptPhbApName;       /* UCS2 Format, allocate and release by caller AP. */
    MmiPhbApNumber_t        *ptPhbApNumber;     /* UCS2 Format, allocate and release by caller AP. */
} MmiPhbApFidSelectMultiContactsNameNumber_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SHOW_BUSINESS_CARD */
} MmiPhbApFidShowBusinessCard_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_SHOW_MY_NUMBER */
} MmiPhbApFidShowMyNumber_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_QUICK_DIAL */
    u16                     u16QuickDialValue;  /* This value is physical index. Fill it with 0 will start with sorting index 1. */
} MmiPhbApFidQuickDial_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_IMPORT_WITH_FILES */
    //TBD.
    IArrayModel             *pIArrayModel;      /* release by caller */
} MmiPhbApFidImportWithFileArray_t;

typedef struct
{
	MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_IMPORT_WITH_FILES */
	u32             uFileHandle;      /* Can represent a list of marked files */
} MmiPhbApFidImportWithFileHandle_t;

typedef struct
{
    MMI_PHB_AP_FID_E        s32PhbApFid;        /* PHB_AP_FID_IMPORT_WITH_FILES */
    u16                             u16PhbPhysicalIdx;
} MmiPhbApFidShowContactDetails_t;


///Param data to startup the Phb Applet
typedef struct PhbParamData_tag
{
	MMI_PHB_AP_FID_E eFid;

	//Param data
	union
	{
		//Save
		MmiPhbApFidSaveContactWithNumber_t *pSaveContactWithNumber;
		MmiPhbApFidSaveContactWithImageId_t *pSaveContactWithImageId;
		MmiPhbApFidSaveContactWithRingId_t *pSaveContactWithRingId;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
        MmiPhbApFidSaveContactWithVideoId_t *pSaveContactWithVideoId;
#endif
#ifndef __SMALL_PHB_MMI__ 
		MmiPhbApFidSaveContactWithEmail_t *pSaveContactWithEmail;
		MmiPhbApFidSaveContactWithUrl_t *pSaveContactWithUrl;

        MmiPhbApFidSelectContactEmail_t *pSelectContactEmail;
		MmiPhbApFidSelectMultiContactsEmail_t *pSelectMultiContactsEmail;
		MmiPhbApFidSelectMultiContactsNameNumberEmail_t *pSelectMultiContactsNameNumberEmail;

        MmiPhbApFidSelectContactNameEmail_t *pSelectContactNameEmail;
        MmiPhbApFidSelectMultiContactsNameEmail_t *pSelectMultiContactsNameEmail;
#endif        
		MmiPhbApFidSaveContactWithvCard_t *pSaveContactWithvCard;
        MmiPhbApFidSaveContactWithDetails_t *pSaveContactWithDetails;

		//Select
		MmiPhbApFidSelectContactDetails_t *pSelectContactDetails;
		MmiPhbApFidSelectContactNameNumber_t *pSelectContactNameNumber;
		MmiPhbApFidSelectMultiContactsNameNumber_t *pSelectMultiContactsNameNumber;
        
		MmiPhbApFidSelectContactAsvCard_t *pSelectContactAsvCard;

		//Other
		MmiPhbApFidShowContactDetails_t *pShowContactDetails;
		MmiPhbApFidQuickDial_t *pQuickDial;
		MmiPhbApFidView_t   *pViewPhbAp;

		///Need to refine, use FileUrl
		MmiPhbApFidImportWithFileHandle_t *pImportWithFileHandle;
	} pParamData;

	//Callback info data
	union
	{
		CmnAppLaunchRspCbInfo_t pCmnAppLaunchRspCbInfo;
		PhoneBookGetContactRspCbInfo_t pGetContactRspCbInfo;
		PhoneBookGetVCardRspCbInfo_t pGetVCardRspCbInfo;
	} psRspCbInfo;

	//Response data
	union
	{
		PhoneBookGetContactRecord_t *pGetContactRspData;
		PhoneBookGetVCardRspData_t *pGetVCardRspData;
	} psRspData;

} PhbAppParamData_t;

/* Kick software watchdog for long-span operation */
#define PHB_COUNT_TO_KICK 100
#define PHB_KICK_WATCHDOG(CONTACT_IDX)  \
                            if (CONTACT_IDX % PHB_COUNT_TO_KICK == 0)   \
                            {   \
                                vm_sysDelayWatchDogReset(); \
                            }

/*-------------------------------------------------------------------------*/

/**
 * External Events
 */



/**
 * Functions
 */
void PHBAP_Init(void);
MAE_Ret PHBAP_New(MAE_ClsId id, void **ppObj);

/*-------------------------------------------------------------------------*/
#ifdef __UI_STYLE_MMI_IFONE__
void PhbAppInputWdgFocusChangCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bFocus, IWidget *pWidget);
#endif
/*-------------------------------------------------------------------------*/
#endif /* __MMI_PHBAPP_H__ */
