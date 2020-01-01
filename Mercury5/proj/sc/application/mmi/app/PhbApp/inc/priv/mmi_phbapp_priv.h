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
* @file    mmi_phpapp_priv.h
* @version $Id: mmi_phpapp_priv.h 2010-02-23 23:00:23Z shin.lin $
* @brief   Phonebook applet private header file
*
*/

#ifndef __MMI_PHBAPP_PRIV_H__
#define __MMI_PHBAPP_PRIV_H__

#if defined(__3D_UI_PHONEBOOK__)
#include "mgl_Egl.h"
#include "mgl_Core_Types.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Core_Shape.h"
#endif

#include "mmi_common_util_menu.h"
#include "sys_sys_wmh_sys.h"   /* For vm_sysDelayWatchDogReset(). */
#include "mmi_common_dialog_id.h"
#include "mmi_common_sim.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_content.h"
#include "mmi_baseapplet.h"
#include "mmi_common_thmid.h"
#include "mmi_base_util.h"
#include "mmi_mae_common_content.h"
#include "mmi_common_inttbl.h"
#include "mmi_class.h"
#include "mmi_event.h"
#include "mmi_mae_file_util.h"
//#include "kernel.h"
#include "sys_rtk_ho.h"
#include "mmi_common_storage_mgr_cfg.h"
#include "mmi_common_window.h"

#include "mmi_phbapp_callback.h"
#include "mmi_phbapp.h"

#include "mmi_common_vtm.h"
#include "mmi_phbapp_id.h"
#include "phbapp_resource.h"


//Service wrapper
#include "mmi_srv_client_commondefine.h"
#include "mmi_phbsrv_utility.h"
#ifdef __APP_MMI_PRIVATEPROTECT__ 
#include "mmi_srv_privateprotect.h"
#endif

//Launch App
#include "mmi_srv_header.h"
#include "mmi_launcher_common.h"
#include "mmi_launcher_bt.h"
#include "mmi_launcher_cc.h"
#include "mmi_launcher_bjx.h"
#include "mmi_launcher_fdn.h"
#include "mmi_launcher_mca.h"
#include "mmi_launcher_phb.h"
#include "mmi_launcher_ussd.h"
#include "mmi_launcher_sendvia.h"
#ifdef __APP_VIDEO_TELEPHONY__
#include "mmi_launcher_videotelephony.h"
#endif

#ifdef __EMAIL_MMI__
#include "mmi_launcher_email.h"
#endif

#include "mmi_phbapp_urlhandler.h"
#include "mmi_messagecenterapp.h"
#ifdef __SXMENGINE__
#include "stdio.h"  //for video chat
#include "mmi_launcher_vendor.h"
#endif

#include "mae_propcontainerbase.h"
#include "mmi_wdg_input.h"
#include "mae_abscontainerbase.h"

#define __MMI_PHBAP_SEARCH_USE_ABC__
/*-------------------------------------------------------------------------*/

/*
Define
*/

#define MMI_PHB_AP_MULTI_SEL_IDLE_TIMER             1
#define MMI_PHB_AP_MULTI_SEL_SUSPEND_BY_ITEM_NUM    5
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#define MMI_PHB_AP_EXPORT_RESULT_TIMER          3000
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#define MMI_PHB_AP_INFO_TIMER       1000
#define MMI_PHB_AP_RESET_KEY_REPEAT 3000
#ifdef __MMI_PHBAP_ALL_TAB__
    #ifndef __MMI_PHBAP_DISABLE_GROUP__
        #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
#define MMI_PHB_AP_MAX_TAB_NUM 6
#else
#define MMI_PHB_AP_MAX_TAB_NUM 5
#endif
    #else
        #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
            #define MMI_PHB_AP_MAX_TAB_NUM 5
        #else
            #define MMI_PHB_AP_MAX_TAB_NUM 4
        #endif 
    #endif
#else
    #ifndef __MMI_PHBAP_DISABLE_GROUP__
        #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
            #define MMI_PHB_AP_MAX_TAB_NUM 5
        #else
            #define MMI_PHB_AP_MAX_TAB_NUM 4
        #endif 
    #else
        #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
            #define MMI_PHB_AP_MAX_TAB_NUM 4
        #else
            #define MMI_PHB_AP_MAX_TAB_NUM 3
        #endif 
    #endif
#endif

#ifndef __MMI_PHBAP_DISABLE_GROUP__
#define MMI_PHB_AP_GROUP_MULTI_SAVE_STEP 5      //read and write 5 contact
#define MMI_PHB_AP_GROUP_MULTI_SAVE_STEP_TICK 5 //msec. after saved step contacts
#define PHB_AP_Group_MultiUpdateInfoToCheckRecord(i)        ((u16)((i)& 0xFFFF))
#define PHB_AP_Group_MultiUpdateInfoToSaveResult(i)         ((i)& 0xFF000000)>>24
#define PHB_AP_Group_MultiUpdateInfo(Result, CheckRecord)   ((((u32)((Result)&MMI_PHB_AP_GROUP_MULTI_UPDATE_E_NONE))<<24)|((u32)(CheckRecord)))
#endif
#define MMI_PHB_AP_ONE_KILO 1024
#define PHB_WATCHDOG_TIMEOUT 50

#if defined(__3D_UI_PHONEBOOK__)
#define PHBAP_FLIP_ANGLE_VALUE          (15)
#endif
/*-------------------------------------------------------------------------*/

/*
Structure
*/
/*=============================================================*/
//Phonebook app Create View Template
/*=============================================================*/

typedef struct VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList_tag
{
    IWidget *pPropContainer;
    IWidget *pTabWidget;
    IWidget *pMenuWidget;
    IWidget *pTextWidget;
    IWidget *pSearchAbsContainer;
    IWidget *pSearchBGImageWidget;
    IWidget *pSearchImageWidget;
    IWidget *pSearchInputWidget;
#ifdef __UI_STYLE_MMI_IFONE__
    IWidget* pSwitchAppTabWdg;
#endif

#ifdef __APP_MMI_GROUP_APP__
	IWidget *pGroupWdg;
#endif

} VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList;

MAE_Ret CreateVID_PHB_TABLIST_SHOWMENU_VIEW(HWIN hWin, VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_MEMBER_LIST_VIEW_WdgList_tag
{
    IWidget *pPropContainer;
    IWidget *pMenuWidget;
    IWidget *pAbsContainer;
    IWidget *pBGImageWidget;
    IWidget *pSearchImageWidget;
    IWidget *pInputWidget;
} VID_PHB_MEMBER_LIST_VIEW_WdgList;

MAE_Ret CreateVID_PHB_MEMBER_LIST_VIEW(HWIN hWin, VID_PHB_MEMBER_LIST_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_VIEW_CONTACT_VIEW_WdgList_tag
{
#if defined(__3D_UI_PHONEBOOK__)
	IWidget *pContactViewAniCntr;
	IWidget *pTopHalfViewAniCntr;
#endif
    IWidget *pBGImageWidget;
    IWidget *pHeadImageWidget;
#ifndef __MMI_PHB_DISABLE_BLACKLIST__      
    IWidget *pHeadBlistImageWidget;
#endif
    IWidget *pNameTextWidget;
    IWidget *pDualSimImageWidget;
    IWidget *pMenuWidget;
} VID_PHB_VIEW_CONTACT_VIEW_WdgList;

MAE_Ret CreateVID_PHB_VIEW_CONTACT_VIEW(HWIN hWin, VID_PHB_VIEW_CONTACT_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_ADD_EDIT_CONTACT_VIEW_WdgList_tag
{
    IWidget *pScrollbarWdg;
    IWidget *pMFLContainer;
    IWidget *pNameDoubleTextWidget;
    IWidget *pMobileTextInputWidget;
#ifndef __SMALL_PHB_MMI__      
    IWidget *pHomeTextInputWidget;
    IWidget *pOfficeTextInputWidget;
    IWidget *pOtherTextInputWidget;
#endif    
#ifndef __MMI_PHBAP_DISABLE_GROUP__
    IWidget *pGroupDoubleTextWidget;
#endif
    IWidget *pPictureDoubleTextWidget;
    IWidget *pRingtoneDoubleTextWidget;
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    IWidget *pVideotoneDoubleTextWidget;
#endif
#ifndef __SMALL_PHB_MMI__  
    IWidget *pCompanyDoubleTextWidget;
    IWidget *pDepartmentDoubleTextWidget;
    IWidget *pPositionDoubleTextWidget;
    IWidget *pAddressDoubleTextWidget;
    IWidget *pEmailDoubleTextWidget;
    IWidget *pUrlDoubleTextWidget;
    IWidget *pNoteDoubleTextWidget;
#endif    
} VID_PHB_ADD_EDIT_CONTACT_VIEW_WdgList;

MAE_Ret CreateVID_PHB_ADD_EDIT_CONTACT_VIEW(HWIN hWin, VID_PHB_ADD_EDIT_CONTACT_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_WdgList_tag
{
    IWidget *pScrollbarWidget;
    IWidget *pMFLContainer;
    IWidget *pNameDoubleTextWidget;
    IWidget *pMobileTextInputWidget;
#ifndef __SMALL_PHB_MMI__      
#ifdef __3G_RIL_MMI__    
    IWidget *pEmailDoubleTextWidget;
#endif
#endif
} VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_WdgList;

MAE_Ret CreateVID_PHB_ADD_EDIT_CONTACT_ADN_VIEW(HWIN hWin, VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_SETPIC_VIEW_WdgList_tag
{
    IWidget *pIImageWidget;
} VID_PHB_SETPIC_VIEW_WdgList;

MAE_Ret CreateVID_PHB_SETPIC_VIEW(HWIN hWin, VID_PHB_SETPIC_VIEW_WdgList *pWdgList);

//*******************************************************************//

typedef struct VID_PHB_SETRING_VIEW_WdgList_tag
{
    IWidget *pTextWidget;
} VID_PHB_SETRING_VIEW_WdgList;

MAE_Ret CreateVID_PHB_SETRING_VIEW(HWIN hWin, VID_PHB_SETRING_VIEW_WdgList *pWdgList);

//*******************************************************************//

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
typedef struct VID_PHB_SETVIDEO_VIEW_WdgList_tag
{
    IWidget *pTextWidget;
} VID_PHB_SETVIDEO_VIEW_WdgList;

MAE_Ret CreateVID_PHB_SETVIDEO_VIEW(HWIN hWin, VID_PHB_SETVIDEO_VIEW_WdgList *pWdgList);
#endif
//*******************************************************************//
/*=============================================================*/
//Phonebook app Window data
/*=============================================================*/

typedef struct TabViewWndData_t_
{
    VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList tWdgList;
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    u8  u8GroupUsedCnt; //the number of used group
#endif    
    WidgetSize_t stWidgetSize;
} TabViewWndData_t;

typedef struct ViewPhbListSelectNumToSaveWndData_t_
{
    MAE_WChar   aStr[MMI_PHB_NAME_LEN+1];
    size_t          destLen;
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} ViewPhbListSelectNumToSaveWndData_t;

typedef struct ViewPhbListOption_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} ViewPhbListOptionWndData_t;

typedef struct ViewContactShowDetailWndData_t_
{
#if defined(__3D_UI_PHONEBOOK__)
    boolean bUserPressInRange;
    MmiPhbApAnimationState_e ePhbAniState;
#endif
    VID_PHB_VIEW_CONTACT_VIEW_WdgList pWdgList;
} ViewContactShowDetailWndData_t;

typedef struct ViewContactOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} ViewContactOptionWndData_t;

typedef struct EditContactShowEditWndData_t_
{
    VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_WdgList pADNWdgList;
    VID_PHB_ADD_EDIT_CONTACT_VIEW_WdgList pADRWdgList;
    u8 u8TabItem;

} EditContactShowEditWndData_t;

typedef struct EditContactOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} EditContactOptionWndData_t;

typedef struct EditContactFullEditWndData_t_
{
    u32                     u32TitleID ;
    size_t                   destLen   ;
    MAE_WChar               *pwText ;
    u16                     u16MaxTextLen ;
    u16                     u16MaxContacts ;
    u16                     u16UsedContacts ;
    u8                      u8MaxNameLen ;
    u8                      u8MaxNumberLen ;
#ifdef __3G_RIL_MMI__
    u8                      u8MaxMailLen;
#endif
    MmiPhbContactContent_t  *ptMmiPhbContactContent;
    InputVtmWdgList_t  pWdgList ;
    InputVtmData_t pData ;

} EditContactFullEditWndData_t;

typedef struct EditContactFullEditOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} EditContactFullEditOptionWndData_t;

typedef struct EditSelectionShowNewOrExistWndData_t_
{
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} EditSelectionShowNewOrExistWndData_t;

#ifndef __SMALL_PHB_MMI__  
typedef struct EditSelectionShowNumTypeWndData_t_
{
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} EditSelectionShowNumTypeWndData_t;
#endif

typedef struct EditSelectionShowSaveToWndData_t_
{
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} EditSelectionShowSaveToWndData_t;

#ifndef __SMALL_PHB_MMI__
typedef struct ViewContactViewItemDetailWndData_t_
{
    PopUpInfoWdgList_t    pWdgList;
    PopUpInfoData_t         pData;

} ViewContactViewItemDetailWndData_t;
#endif // #ifndef __SMALL_PHB_MMI__

#ifndef __MMI_PHBAP_DISABLE_GROUP__
typedef struct ViewGroupShowGroupListWndData_t_
{
    VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList tWdgList;
    u8  u8GroupUsedCnt;
    WidgetSize_t stWidgetSize;

} ViewGroupShowGroupListWndData_t;

typedef struct ViewGroupGroupListOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;
    u8  u8GroupUsedCnt;
    WidgetSize_t stWidgetSize;

} ViewGroupGroupListOptionWndData_t;

typedef struct ViewGroupEditGroupWndData_t_
{
    mmi_raiInfo_t   tRaiInfo;
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} ViewGroupEditGroupWndData_t;

typedef struct ViewGroupEditGroupNameWndData_t_
{
    size_t                        destLen;
    MAE_WChar              *pwText;
    InputVtmWdgList_t     pWdgList;
    InputVtmData_t          pData;

} ViewGroupEditGroupNameWndData_t;

typedef struct ViewGroupEditGroupNameOptionWndData_t_
{
    TextInfo textInfo;
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} ViewGroupEditGroupNameOptionWndData_t;

typedef struct ViewGroupShowMemberListWndData_t_
{

    VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList tWdgList;
    VID_PHB_MEMBER_LIST_VIEW_WdgList tWdgList2;
    u8 u8TabItem;

} ViewGroupShowMemberListWndData_t;

typedef struct SelectGroupListGroupWndData_t_
{
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} SelectGroupListGroupWndData_t;

#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__

typedef struct ViewGroupMemberListOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} ViewGroupMemberListOptionWndData_t;

typedef struct SelectImageIDShowCurrentWndData_t_
{
    VID_PHB_SETPIC_VIEW_WdgList pWdgList;

} SelectImageIDShowCurrentWndData_t;

typedef struct SelectImageIDShowChangeMenuWndData_t_
{
    PopUpSelectWdgList_t pWdgList ;
    PopUpSelectCB_t pCB ;

} SelectImageIDShowChangeMenuWndData_t;

typedef struct SelectRingIDShowCurrentWndData_t_
{
    VID_PHB_SETRING_VIEW_WdgList  pWdgList;

} SelectRingIDShowCurrentWndData_t;

typedef struct SelectRingIDShowChangeMenuWndData_t_
{
    boolean     bIsFindContent;
    u32         u32RingID;
    s32         s32TopModeFromStack;
    PopUpSelectWdgList_t pWdgList ;
    PopUpSelectCB_t pCB ;

} SelectRingIDShowChangeMenuWndData_t;

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
typedef struct SelectVideoIDShowCurrentWndData_t_
{
    VID_PHB_SETVIDEO_VIEW_WdgList  pWdgList;

} SelectVideoIDShowCurrentWndData_t;

typedef struct SelectVideoIDShowChangeMenuWndData_t_
{
    boolean     bIsFindContent;
    u32         u32VideoID;
    s32         s32TopModeFromStack;
    PopUpSelectWdgList_t pWdgList ;
    PopUpSelectCB_t pCB ;

} SelectVideoIDShowChangeMenuWndData_t;
#endif

typedef struct MultiSelectReadyWndData_t_
{
    VID_PHB_TABLIST_SHOWMENU_VIEW_WdgList tWdgList;
    VID_PHB_MEMBER_LIST_VIEW_WdgList tWdgList2;
    u8  u8TabItem;

} MultiSelectReadyWndData_t;

typedef struct MultiSelectOptionWndData_t_
{
    OptionMenuWdgList_t pWdgList ;
    OptionMenuCB_t  pCB ;

} MultiSelectOptionWndData_t;

typedef struct ViewMemoryStatusWndData_t_
{
    PopUpInfoWdgList_t    pWdgList;
    PopUpInfoData_t         pData;

} ViewMemoryStatusWndData_t;

/*
typedef struct CopyToMenuWndData_t_
{
    u32                 u32MenuIndex;
    u32                 eMenuID;
    SetDefaultSIM_e     eDefaultSIM;
    MenuWdgList_t  pWdgList;
    MenuData_t pData;
    MenuCB_t  pCB;

} CopyToMenuWndData_t;
*/

#ifndef __SMALL_PHB_MMI__
typedef struct SelectNumberWndData_t_
{
    PopUpSelectWdgList_t pWdgList ;
    PopUpSelectCB_t pCB ;

} SelectNumberWndData_t;
#endif

typedef u32 MmiPhbApMultiUpdateInfo_e;

/*
Enum
*/

/*Window ID*/


/*Phbapp mode, for indentify the function*/
typedef enum
{
    PHBAP_MODE_PHBAP = 0,
    PHBAP_MODE_Idle,
    PHBAP_MODE_Init,
    PHBAP_MODE_CheckStatus,
    PHBAP_MODE_ViewPhbList,
    PHBAP_MODE_ViewPhbList_PrepareData,
    PHBAP_MODE_ViewPhbList_ShowContactList,
    PHBAP_MODE_ViewPhbList_Option,
    PHBAP_MODE_ViewPhbList_GetDetails,
    PHBAP_MODE_ViewPhbList_GetMultiDetails,
    PHBAP_MODE_ViewPhbList_WaitForPhbSrv,
    PHBAP_MODE_ViewPhbList_SelectNumToSave,
    PHBAP_MODE_ViewPhbList_SelectNumToSave_ShowView,
    PHBAP_MODE_ViewPhbList_SelectNumToSave_CheckIfReplace,
    PHBAP_MODE_ViewPhbList_SelectNumToSave_Save,
    PHBAP_MODE_Advance,
    PHBAP_MODE_Advance_ShowMenu,
    PHBAP_MODE_Advance_CopyToMenu,
    PHBAP_MODE_ViewContact,
    PHBAP_MODE_ViewContact_PrepareData,
    PHBAP_MODE_ViewContact_ShowDetail,
    PHBAP_MODE_ViewContact_Option,
    PHBAP_MODE_ViewContact_AddNumber,
    PHBAP_MODE_ViewContact_ViewItemDetail,
    PHBAP_MODE_EditContact,
    PHBAP_MODE_EditContact_PrepareData,
    PHBAP_MODE_EditContact_ShowEdit,
    PHBAP_MODE_EditContact_FullEdit,
    PHBAP_MODE_EditContact_FullEdit_ShowEditor,
    PHBAP_MODE_EditContact_FullEdit_Option,
    PHBAP_MODE_EditContact_FullEdit_StoreData,
    PHBAP_MODE_EditContact_ChangeNumberType,
    PHBAP_MODE_EditContact_CheckIfLeave,
    PHBAP_MODE_EditContact_Save,
    PHBAP_MODE_EditSelection,
    PHBAP_MODE_EditSelection_ShowNewOrExist,
    PHBAP_MODE_EditSelection_ShowSaveTo,
    PHBAP_MODE_EditSelection_ShowNumType,
    PHBAP_MODE_DeleteContact,
    PHBAP_MODE_DeleteContact_ShowConfirm,
    PHBAP_MODE_DeleteContact_Delete,
    PHBAP_MODE_CopyContact,
    PHBAP_MODE_ViewMemoryStatus,
    PHBAP_MODE_ViewGroup,
    PHBAP_MODE_ViewGroup_ShowGroupList,
    PHBAP_MODE_ViewGroup_GroupListOption,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    PHBAP_MODE_ViewGroup_EditGroup,
    PHBAP_MODE_ViewGroup_EditGroupName,
    PHBAP_MODE_ViewGroup_EditGroupName_ShowEdit,
    PHBAP_MODE_ViewGroup_EditGroupName_Option,
    PHBAP_MODE_ViewGroup_EditGroupName_Save,
    PHBAP_MODE_ViewGroup_SaveGroup,
    PHBAP_MODE_ViewGroup_PrepareData,
    PHBAP_MODE_ViewGroup_ShowMemberList,
    PHBAP_MODE_ViewGroup_MemberListOption,
    PHBAP_MODE_ViewGroup_WaitForPhbSrv,
    PHBAP_MODE_ViewGroup_RemoveConfirm,
    PHBAP_MODE_ViewGroup_DeleteGroupConfirm,
    PHBAP_MODE_ViewGroup_DeleteGroup,
#endif
    PHBAP_MODE_MakeCall,
    PHBAP_MODE_MakeCall_PrepareData,
    PHBAP_MODE_MakeCall_Call,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    PHBAP_MODE_SendvCard,
    PHBAP_MODE_SendvCard_PrepareData,
    PHBAP_MODE_SendvCard_Send,
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    PHBAP_MODE_SendMessage,
    PHBAP_MODE_MultiSelect,
    PHBAP_MODE_MultiSelect_PrepareData,
    PHBAP_MODE_MultiSelect_Ready,
    PHBAP_MODE_MultiSelect_Option,
    PHBAP_MODE_MultiSelect_Save,
    PHBAP_MODE_MultiSelect_DeleteConfirm,
    PHBAP_MODE_MultiSelect_DeleteContacts,
    PHBAP_MODE_MultiSelect_StartMultiDelete,
    PHBAP_MODE_MultiSelect_CopyContacts,
    PHBAP_MODE_MultiSelect_WaitForPhbSrv,
    PHBAP_MODE_MultiSelect_RemoveConfirm,
#if defined(__MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__) || defined(__MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__)
    PHBAP_MODE_SetSearchOptions,
#endif
    PHBAP_MODE_SelectImageID,
    PHBAP_MODE_SelectImageID_ShowCurrent,
    PHBAP_MODE_SelectImageID_ShowChangeMenu,
    PHBAP_MODE_SelectImageID_SelectNew,
    PHBAP_MODE_SelectImageID_WaitForPhbSrv,
    PHBAP_MODE_SelectRingID,
    PHBAP_MODE_SelectRingID_ShowCurrent,
    PHBAP_MODE_SelectRingID_ShowChangeMenu,
    PHBAP_MODE_SelectRingID_SelectNew,
    PHBAP_MODE_SelectRingID_WaitForPhbSrv,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    PHBAP_MODE_SelectVideoID_SelectNew,
    PHBAP_MODE_SelectVideoID_ShowCurrent,
    PHBAP_MODE_SelectVideoID_ShowChangeMenu,
#endif
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    PHBAP_MODE_ExportContacts,
    PHBAP_MODE_ExportContacts_GetContactToEncode,
    PHBAP_MODE_ExportContacts_Finish,
    PHBAP_MODE_ImportContacts,
    PHBAP_MODE_ImportContacts_SelectFile,
    PHBAP_MODE_ImportContacts_ReadCheckFile,
    PHBAP_MODE_ImportContacts_AddContactFromFile,
    PHBAP_MODE_ImportContacts_Finish,
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    PHBAP_MODE_LaunchBaiJiaXing,
    PHBAP_MODE_LaunchFDNAP,
    PHBAP_MODE_ShowErrMsg,
    PHBAP_MODE_PrepareRecipientList,
    PHBAP_MODE_PrepareRecipientList_ProcessData,
    PHBAP_MODE_PrepareRecipientList_OK,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    PHBAP_MODE_SelectGroup,
    PHBAP_MODE_SelectGroup_PrepareData,
    PHBAP_MODE_SelectGroup_ListGroup,
    PHBAP_MODE_SelectGroup_WaitForPhbSrv,
#endif    
    PHBAP_MODE_SelectNumber,
    PHBAP_MODE_Rebuild,
    PHBAP_MODE_SelectStorage,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    PHBAP_MODE_SelectExportFormat
#endif     
} MmiPhbAppMode_e;

typedef enum
{
    START_MULTI_COPY = 0,
    START_CSV_REQ,
    START_MULTI_DELETE,
    COPY_ONE_CONTACT_CNF,
    READ_ONE_CONTACT_CNF,
    DELETE_CONTACT_CNF

} MmiPhbAppMultiSelectMode_e;

typedef enum
{
    ViewPhbListOption = 0,
    ViewPhbList_GetDetails,
    ViewPhbList_GetMultiDetails ,
    ViewContact_Option ,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    ViewGroup_MemberListOption,
#endif    
    MakeCall_PrepareData,
    PrepareRecipientList
} MmiPhbAppSelectNumberMode_e;

#ifndef __MMI_PHBAP_DISABLE_GROUP__    
enum
{
    MMI_PHB_AP_GROUP_MULTI_UPDATE_E_SUCCESS     = 0,
    MMI_PHB_AP_GROUP_MULTI_UPDATE_E_FAIL        = 1,
    MMI_PHB_AP_GROUP_MULTI_UPDATE_E_SOME_FAIL   = 2,
    MMI_PHB_AP_GROUP_MULTI_UPDATE_E_NONE        = 0xFF,
};
typedef u8 MmiPhbApMultiUpdateResult_e;
#endif

enum
{
#ifdef __MMI_PHBAP_ALL_TAB__
    MMI_PHB_AP_TAB_LIST_ALL = 0,
    MMI_PHB_AP_TAB_LIST_PHONE,
    #ifndef __MMI_PHBAP_DISABLE_GROUP__    
    MMI_PHB_AP_TAB_LIST_GROUP,
    #endif    
    MMI_PHB_AP_TAB_LIST_SIM1,
    MMI_PHB_AP_TAB_LIST_SIM2,
    #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    MMI_PHB_AP_TAB_LIST_BLIST,
    #endif 
#else
    MMI_PHB_AP_TAB_LIST_PHONE = 0,
    #ifndef __MMI_PHBAP_DISABLE_GROUP__    
    MMI_PHB_AP_TAB_LIST_GROUP,
    #endif    
    MMI_PHB_AP_TAB_LIST_SIM1,
    MMI_PHB_AP_TAB_LIST_SIM2,
    #ifndef __MMI_PHB_DISABLE_BLACKLIST__
    MMI_PHB_AP_TAB_LIST_BLIST,
    #endif
#endif
    MMI_PHB_AP_TAB_LIST_EMPTY = 0xFF
};

enum
{
    MMI_PHB_AP_SIM_BOTH = 0,
    MMI_PHB_AP_SIM_NO_SIM1 = 1,
    MMI_PHB_AP_SIM_NO_SIM2 = 2,
    MMI_PHB_AP_SIM_NO_SIM = 3,
};

enum
{
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NAME     = 0,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NUMBER1,
#ifndef __SMALL_PHB_MMI__    
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NUMBER2,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NUMBER3,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NUMBER4,
#endif // #ifndef __SMALL_PHB_MMI__
#ifndef __MMI_PHBAP_DISABLE_GROUP__
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_GROUP,
#endif    
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_PICTURE,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_RINGTONE,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_VIDEOTONE,
#endif
#ifndef __SMALL_PHB_MMI__
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_COMPANY,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_DEPARTMENT,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_POSITION,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_ADDRESS,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_EMAIL,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_URL,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_NOTE,
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_PHONE_MAX = MMI_PHB_AP_CONTACT_EDITOR_ITEM_NOTE,
#else

#endif // #ifndef __SMALL_PHB_MMI__
    MMI_PHB_AP_CONTACT_EDITOR_ITEM_SIM_MAX = MMI_PHB_AP_CONTACT_EDITOR_ITEM_NUMBER1
};

enum
{
    MMI_PHB_AP_MODE_STACK_MAX           = 10,
    MMI_PHB_AP_MEMORY_DETAILS_STR_LEN   = 16,
    MMI_PHB_AP_MEMORY_DETAILS_STR_SIZE  = 768,

#ifndef __MMI_PHBAP_DISABLE_GROUP__

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    MMI_PHB_AP_GROUP_PROPERTY_NUM       = 4,
#else
    MMI_PHB_AP_GROUP_PROPERTY_NUM       = 3,
#endif

    MMI_PHB_AP_GROUP_NAME_IDX           = 0,
    MMI_PHB_AP_GROUP_PICTURE_IDX        = 1,
    MMI_PHB_AP_GROUP_RINGTONE_IDX       = 2,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    MMI_PHB_AP_GROUP_VIDEOTONE_IDX          = 3,
#endif

#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__

    // change ringtone/picture
    MMI_PHB_AP_CHANGE_RING_PIC_DEFAULT_ITEM_IDX = 0,
    MMI_PHB_AP_CHANGE_RING_PIC_CUSTOM_ITEM_IDX  = 1,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
    // for EXPORT
    MMI_PHB_AP_DIALOG_STR_BUF_SIZE      = 50
#endif    
};

enum
{
    MMI_PHB_SEARCH_TYPE_NUMBER = 0,
    MMI_PHB_SEARCH_TYPE_DIGIT_TO_ALPHABET
};

enum
{
    MMI_PHB_AP_MULTI_SELECT_FCT_NONE        = 0,
    MMI_PHB_AP_MULTI_SELECT_FCT_MARK,
    MMI_PHB_AP_MULTI_SELECT_FCT_SAVE,
    MMI_PHB_AP_MULTI_SELECT_FCT_SEND,
    MMI_PHB_AP_MULTI_SELECT_FCT_ADD_MEMBER,
    MMI_PHB_AP_MULTI_SELECT_FCT_OTHERAP
};
typedef u8 MmiPhbApMultiSelectFct_e;


enum
{
    MMI_PHB_AP_RECIPIENT_LIST_TYPE_SMS      = 0,
    MMI_PHB_AP_RECIPIENT_LIST_TYPE_MMS      = 1
};
typedef u8 MmiPhbApReceipientListType_e;


enum
{
    MMI_PHB_AP_SELECT_NUM_FOR_SELECT    = 0,
    MMI_PHB_AP_SELECT_NUM_FOR_CALL      = 1,
    MMI_PHB_AP_SELECT_NUM_FOR_SEND      = 2
};
typedef u8 MmiPhbApSelectNumFor_e;

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
enum
{
    MMI_PHB_AP_EXPORT_TYPE_ALL      = 0,
    MMI_PHB_AP_EXPORT_TYPE_MARK     = 1,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    MMI_PHB_AP_EXPORT_TYPE_GROUP    = 2,
#endif    
#ifdef __PHB_SEND_MULTI_VCARD_BY_BT__
    MMI_PHB_AP_EXPORT_TYPE_MARK_SEND_BT     = 3,
#endif
};
typedef u8 MmiPhbApExportType_e;
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

enum
{
    MMI_PHB_AP_INFO_DIALOG_TYPE_INFO = 0,
    MMI_PHB_AP_INFO_DIALOG_TYPE_WARN = 1
};
typedef u8 MmiPhbApInfoDialogType_e;

static const u32 atNumMapImgID[MMI_PHB_NUMBER_MAX]
=
{
    PHONEBOOK_IMG_MOBILE,
#ifndef __SMALL_PHB_MMI__        
    PHONEBOOK_IMG_HOME,
    PHONEBOOK_IMG_OFFICE,
    PHONEBOOK_IMG_OTHER
#endif
};

static const u32 u32IdxMapMnuID[MMI_PHB_NUMBER_MAX]
=
{
    MNU_PHBAP_EDIT_MOBILE,
#ifndef __SMALL_PHB_MMI__        
    MNU_PHBAP_EDIT_HOME,
    MNU_PHBAP_EDIT_OFFICE,
    MNU_PHBAP_EDIT_OTHER
#endif
};

static const u32 u32IdxMapTxtID[MMI_PHB_NUMBER_MAX]
=
{
    TXT_LIL_N_MOBILE,
#ifndef __SMALL_PHB_MMI__        
    TXT_LIL_N_HOME_NUMBER,
    TXT_LIL_N_OFFICE,
    TXT_LIL_N_OTHER
#endif
};

static u32 sg_au32nImageId[MMI_PHB_AP_MAX_TAB_NUM]
=
{
#ifdef __MMI_PHBAP_ALL_TAB__
    PHONEBOOK_IMG_TAB_ALL_DISABLE,
#endif
    PHONEBOOK_IMG_T_PHONE_DISABLE,
#ifndef __MMI_PHBAP_DISABLE_GROUP__     
    PHONEBOOK_IMG_TAB_GROUPS_DISABLE,
#endif    
    PHONEBOOK_IMG_TAB_SINGLE_SIM_DISABLE,
    PHONEBOOK_IMG_TAB_SINGLE_SIM_DISABLE,
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    PHONEBOOK_IMG_TAB_BLACK_LIST_DISABLE
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__   
};

static u32 sg_au32nImageFocusId[MMI_PHB_AP_MAX_TAB_NUM]
=
{
#ifdef __MMI_PHBAP_ALL_TAB__
    PHONEBOOK_IMG_TAB_ALL,
#endif
    PHONEBOOK_IMG_T_PHONE,
#ifndef __MMI_PHBAP_DISABLE_GROUP__     
    PHONEBOOK_IMG_TAB_GROUPS,
#endif    
    PHONEBOOK_IMG_TAB_SINGLE_SIM,
    PHONEBOOK_IMG_TAB_SINGLE_SIM,
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    PHONEBOOK_IMG_TAB_BLACK_LIST
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
};

/*-------------------------------------------------------------------------*/

/**
* Application structure
*/

/*=============================================================*/
// Variable Declarations
/*=============================================================*/
typedef struct MMI_PHBAP_TAG
{
    APPLET_BASE_ELEMENTS;
    u32     refCnt;     // reference count
    u32     IsUsingSM : 1; // An ability flag to indicate if using State Machine
    MMI_PHB_AP_FID_E        s32PhbApFid;    /*Define which function to execute*/
    PhbAppParamData_t       *ptPhbAppParamData; /*The point to parameters which the function execution need*/
    s32                     as32PhbModeStack[MMI_PHB_AP_MODE_STACK_MAX];    /*Save the information of the flow*/
    s32                     s32GroupMode;   /*For group, define which group sub-function want to execute*/
    MmiPhbBookType_e     s32PhbBookType; /*The type of phonebook, related to the definition of MmiPhbBookType_e*/
    MmiPhbBookType_e     s32PhbActionBookType;   /*The action type of phonebook, related to the definition of MmiPhbBookType_e*/
    MmiPhbBookType_e     s32PhbCopyDestBookType; /*The type of phonebook of copied destination, related to the definition of MmiPhbBookType_e*/
    MmiPhbGroup_e         s32PhbGroup;    /*The contact's group*/
    MmiPhbGroup_e         s32PhbActionGroup;/*The action group type*/

    u16                     u16PhbTotalSortingIdx;   /*The sorting index of the contact*/
    u16                     u16PhbPhysicalIdx;  /*The physical index of the contact*/
    u32                     u32PhbSrvCheckValue;    /*The check value used for pair the async service and the confirm data.*///The new api handle this comparision  ,this parameter could be removed
    MmiPhbSrvFunId_e       s32PhbSrvFid;   /*Define which service function to execute*/
    u8                      u8PhbNumPos;     /*Save number to which filed:mobile/home/office/other*/
    IWidget                 *pIMenuWdg;
    IWidget                 *pIFullEditInputWidget;
    IWidget                 *pTabWidget;
    u8                      u8TabIdx;   /*Used the index to decide to show which tab view*/
    u8                      u8SimCondition; /*The status of sim: MMI_PHB_AP_SIM_BOTH ,MMI_PHB_AP_SIM_NO_SIM1,MMI_PHB_AP_SIM_NO_SIM2,MMI_PHB_AP_SIM_NO_SIM ,*/
    u8                      au8nTabItem[MMI_PHB_AP_MAX_TAB_NUM];    /*Tab data*/
#ifndef __MMI_PHB_DISABLE_BLACKLIST__        
    u16                     u16PhbBlackListNumIdx;  /*The sorting index for black list*/
    MmiPhbBlackListMemberContent_t *ptBLContactContent; /*Used for adding the contact into black list*/
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__        
    /* For handle key press event for search bar BEGIN*/
    IWidget                 *pSearchBarWidget;
    WidgetHandler_t         tMenuWidgetHandler;
    WidgetHandler_t         tInputWidgetHandler;
    WidgetHandler_t         tMultiSelectMenuWidgetHandler;
    WidgetHandler_t         tMultiSelectInputWidgetHandler;
    WidgetHandler_t         tMemberMenuWidgetHandler;
    WidgetHandler_t         tMemberInputWidgetHandler;
    /* For handle key press event for search bar END*/
    MmiPhbSearchResult_t    *patSearchResult;   /*The all serching result contact's informations*/
    u16                     u16SearchedNum; /*The number of searched contacts*/
    u8                      u8LastInputTextLen; /*The input text length before text changed*/
    MAE_WChar               au16OldSearchText[MMI_PHB_NAME_LEN+1];    /*The input text before text changed*/
    boolean                 bIsNeedToClearSearchText;  /*Check if need to clear the search text*/
    // for inline number input
    HistoryInfo_t           tHistory;             /* Store the result of menu widget select. */
    MenuItemId_e            s32PrevMenuID;  /*Store the previous result of menu widget select.*/
	boolean 				bIsNewData;
    boolean                 bIsApStart; /*Check the phbapp start or not*/
    boolean                 bIsApActive;    /*Check the phapp is in active mode not suspend or stop*/
    u32                     u32StartParam1;
    boolean                 *pbApCheckStatus;       /* Store the Check Status of PHBAP. */
	u16                     u16ApCheckStatusSize;
    boolean                 *pbSrvCheckStatus;      /* Store the Check Status of PHBSRV. */

	boolean 				*pbApAllCheckStatus;
	u16						u16ApAllUsedContacts;
	u16						u16ApAllCheckedNum;

    u32                     u32PhbKeyCode;  /*Store the key press data*/
#ifdef __PHB_NO_SEARCH__
    u8                      u32PhbKeyRepeat;    /*The number of key repeat pressing*/
#endif	
    MmiPhbContactContent_t  *ptContactContent;      /* Store contact's content for mode transition. */
#ifndef __MMI_PHBAP_DISABLE_GROUP__ 
    MmiPhbGroupContent_t    *ptGroupContent;        /* Store group's content for mode transition. */
#endif
    u8                      u8FocusItem;    /*The focus index of menu widget*/
    u8                      u8MFLFocusItem; /*The focus index of MFL container*/
    // multi-select(mark)
    u16                     u16MarkContactNum;  /*The number of mark contacts */
    u16                     u16CurCheckStatusIdx;   /*For multi select loop index*/
    u8                      u8GetCnfTime;   /*The index of get multi contacts' detail */
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    // for  import/export
    MAE_WChar               *pFilePath; /*The file path for import phonebook file*/
    boolean                 bIsImportExportFinish;  /*Check the import/export finished or not*/
    boolean                 bIsSuspendImportExport; /*Check the import/export suspended or not*/
    boolean                 bIsDoImportExport;  /*Check the import/export exucution status*/
    MAE_WChar               *pu16ExportFilePathName;    /*The saving file path of exporting contacts*/
    MAE_WChar               *pu16ExportFileName;    /*The saving file name of exporting contacts,used for showing to user */
    u32 nHandleID;   /*The handle Id which filemgr return for import*/
    u16                     u16CurFileNum;  /*Index of importing multi .phb file */
    u16                     u16AllFileNum;  /*The number of importing files which filemgr return*/
    MmiPhbApExportType_e    u8ExportType;   /*Export type:MMI_PHB_AP_EXPORT_TYPE_ALL,MMI_PHB_AP_EXPORT_TYPE_MARK,MMI_PHB_AP_EXPORT_TYPE_GROUP */
    MmiPhbExportPath_e      eImportExportPath;  /*import or export in Phone or Card*/
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    boolean                 bIsSDInsert;    /*The SD card status*/
#if defined(__DUAL_CARD__)    
    boolean                 bIsSD2Insert;    /*The SD card 2 status*/
#endif
    // support char count in title widget
    IWidget                 *pITitleWidget;
    u16                     u16MaxInputLen;   /*The max length of input text*/
#ifdef __3G_RIL_MMI__                   
    u8                      u8MaxMailInputLenSupporttedInSIM;  /* The max length of mail inputting text in SIM */
#endif
    // endkey in edit contact
    boolean                 bIsResumeStopping;   /*When edit contacts,if stop,need to check the contact changing status.If changed, ask saving then confirm stop.*/
    boolean                 bIsContactChange;   /*Store contact's change status*/
    boolean                 bIsEmbedClose;   /*Receive MAE_EVT_EMBEDDED_AP_CLOSE event and set this flag be TRUE*/
#ifdef __APP_MMI_BJX__	
	// BaiJiaXing
    u16                     u16BJXResultIdx;   /*For BaiJiaXing search, the BJX app would return the result index*/
#endif

#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__PHB_SELECT_BK_FROM_PHB__)
    PhoneBookGetContactRecord_t *psRspData;
#endif
    IImage                  *pImgCache;   /*For contact image cache*/
    boolean                 bIsIntInFullEditor;   /*Check is in full edit mode*/
    /* Phonebook service confirm BEGIN. */
    MmiPhbQueryPhbStatusCnf_t                   *ptPhbQueryPhbStatusCnf;
    MmiPhbReadOneContactBySortingIdxCnf_t       *ptPhbReadOneContactBySortingIdxCnf;
    MmiPhbWriteOneNewContactCnf_t               *ptPhbWriteOneNewContactCnf;
    MmiPhbCopyOneContactBySortingIdxCnf_t       *ptPhbCopyOneContactBySortingIdxCnf;
    MmiPhbWriteOneContactByPhysicalIdxCnf_t     *ptPhbWriteOneContactByPhysicalIdxCnf;
    MmiPhbDeleteOneContactBySortingIdxCnf_t     *ptPhbDeleteOneContactBySortingIdxCnf;
    /* Not used now*/
    /*
    MmiPhbReadOneContactByPhysicalIdxCnf_t      *ptPhbReadOneContactByPhysicalIdxCnf;
    MmiPhbReadMultiContactBySortingIdxCnf_t     *ptPhbReadMultiContactBySortingIdxCnf;
    MmiPhbReadMultiContactByPhysicalIdxCnf_t    *ptPhbReadMultiContactByPhysicalIdxCnf;
    MmiPhbWriteMultiNewContactCnf_t             *ptPhbWriteMultiNewContactCnf;
    MmiPhbWriteMultiContactByPhysicalIdxCnf_t   *ptPhbWriteMultiContactByPhysicalIdxCnf;
    MmiPhbCopyOneContactByPhysicalIdxCnf_t      *ptPhbCopyOneContactByPhysicalIdxCnf;
    MmiPhbCopyMultiContactByPhysicalIdxCnf_t    *ptPhbCopyMultiContactByPhysicalIdxCnf;
    MmiPhbCopyMultiContactBySortingIdxCnf_t     *ptPhbCopyMultiContactBySortingIdxCnf;
    MmiPhbCopyAllContactCnf_t                   *ptPhbCopyAllContactCnf;
    MmiPhbDeleteOneContactByPhysicalIdxCnf_t    *ptPhbDeleteOneContactByPhysicalIdxCnf;
    MmiPhbDeleteMultiContactByPhysicalIdxCnf_t  *ptPhbDeleteMultiContactByPhysicalIdxCnf;
    MmiPhbDeleteMultiContactBySortingIdxCnf_t   *ptPhbDeleteMultiContactBySortingIdxCnf;
    MmiPhbDeleteAllContactCnf_t                 *ptPhbDeleteAllContactCnf;
    MmiPhbSearchContactByNameCnf_t              *ptPhbSearchContactByNameCnf;
    MmiPhbSearchContactByNumberCnf_t            *ptPhbSearchContactByNumberCnf;
    */
    /* Phonebook service confirm END. */
    /*Phonebbok list image BEGIN*/
    IImage *pContactImg;
    IImage *pContactMasterImg;
    IImage *pContactSlaveImg;
    /*Phonebbok list image END*/
    u16     u16ModifySerialNo;/*Modify Serial No is used to mark the data has been modified*/
	
	boolean	bIsRskClear;

    MmiPhbApMultiSelectFct_e   MultiSelectFct; /* Mulit-Select non-mark mode feature */
#ifdef __IP_CALL_MMI__
    boolean bIPCall ;   /*Set TRUE if user want to use IP Call*/
#endif
#ifdef __APP_VIDEO_TELEPHONY__
    boolean bVideoCall;
#endif
    /* For prepare recipient list state */
    u32                             u32CurrentContact;      /* Counter for processing data */
    MmiPhbApReceipientListType_e    u8ReceipentListType;    /* Indicator the receipentlist is prepared for SMS or MMS */
    //!!!!!Don't Set this value directly for easy debug, Please use _PhbSetReceipientListType.
    /* For Messege */
    u32                             nRecipientNum;   /*The total number of SMS/MMS recipients*/
    MsgRecipient_t              *psRecipients;   /*The pointer to the contacts that are the SMS/MMS recipients*/
    IWidget                         *pIRLPopupSelectWdg;
#ifndef __MMI_PHBAP_DISABLE_GROUP__  
    /* For select group */
    bool                            bLoadContact; /* In some case we need to load contact content in SelectGroup mode. */
#endif
    MmiPhbApSelectNumFor_e          eSelectNumFor;   /*For select number window to decide execute which function*/
    MmiPhbAppSelectNumberMode_e eSelectNumberMode;   /*Store the caller*/

    MmiPhbAppMode_e eCurrentMode;  /*Phbapp current mode,used for indentify the function*/ //!!!!!Don't Set this value directly for easy debug, Please use _PhbSetCurrentMode.
    MmiPhbAppMode_e ePrivMode;   /*Phbapp privious mode,used for suspend/resume the ap*///!!!!!Don't Set this value directly for easy debug, Please use _PhbSetPrivMode.

    /* For select ring ID */
    AudioEnvSrvVolLevel_e eAudioTempVolume;

    /* For hash map service. */
    u32     u32PhbImageIdx_New;     /* New image index after edit. */
    u32     u32PhbRingtoneIdx_New;  /* New ringtone index after edit. */
	s32		s32EditOriLen;	/* For Edit to calculate delta length. */
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
#ifdef __PHB_SEND_MULTI_VCARD_BY_BT__
        BtAppSendMultipleInputData_t *ptSendBTMultiFileData;
#endif
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#if defined(__3D_UI_PHONEBOOK__)
    boolean bEnterContactViewFormTabView;
    boolean bChangeContactView;
    boolean bMenuWdgAniPlaying;    
    boolean bPageFlipCounterwise;
#endif //end of #if defined(__3D_UI_PHONEBOOK__)

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
	u8		u8ExportFormat;
#endif
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    u32     u32PhbVideotoneIdx_New; /* New videotone index after edit. */
#endif

} MMI_PHBAP;


/*-------------------------------------------------------------------------*/
/* Epilogue */

/*=============================================================*/
// Private Function Implementations
/*=============================================================*/
MAE_Ret mmi_PHBAP_GetFileURL(u32 nHandleID, u32 nidx, MAE_WChar *pStrDestURL);
//Mode Stack Manager API
void        _PHB_InsertToModeStack(MMI_PHBAP *pThis, s32 s32PhbMode);
static void _PHB_RemoveFromModeStack(MMI_PHBAP *pThis, s32 s32PhbMode);
static void _PHB_RemoveAllFromModeStack(MMI_PHBAP *pThis);
u8          _PHB_GetModeStackTotalLevel(MMI_PHBAP *pThis);
s32         _PHB_GetModeFromModeStack(MMI_PHBAP *pThis, u8 u8ModelLevel);
static MAE_Ret mmi_PHBAP_LaunchUSSD(MMI_PHBAP* pThis, MMI_SSSRV_USSD_Action_Type_e eType, u8 *pStr);
static MAE_Ret mmi_PHBAP_LaunchCCAP(MMI_PHBAP* pThis , u8* pDialStr, CcAppCallType_e eCallType);
#ifdef __APP_VIDEO_TELEPHONY__
static MAE_Ret mmi_PHBAP_LaunchVTAP(MMI_PHBAP* pThis , u8* pDialStr, VideoTelephonyAppCallType_e eCallType);
#endif
static void mmi_PHBAP_PhbSrvReqAsync(MMI_PHBAP *pThis, void *ptReq);
MAE_Ret mmi_PHBAP_SetTabData(MMI_PHBAP *pThis, IWidget *pITabWdg);
static void mmi_PHBAP_VectorModelItemFree(void* pData, IBase *pOwner);
void mmi_PHBAP_GetMenuCheckStatus(IWidget *pMenuWidget,  boolean     *pbCheckStatus);
void mmi_PHBAP_SetMenuCheckStatus(IWidget *pMenuWidget,  boolean *pbCheckStatus);
MAE_Ret mmi_PHBAP_SetTabWidgetBgImage(MMI_PHBAP *pThis, IWidget *pTabWidget);
__SLDPM_FREE__ static void mmi_PHBAP_SetTabViewTitle(MMI_PHBAP *pThis, IWidget *pTitleWidget);
#ifndef __MMI_PHBAP_DISABLE_GROUP__
static void mmi_PHBAP_FullTextEditor_InputMdl(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);//(void *pUsrData, TextModelEvent_t *pMdlEvent);
#endif
static void mmi_PHBAP_AdaptGet_Contact_List_TabView_IT(WdgDynamicMenuItemPtr_t *pItemData, void *pOwner, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
void mmi_PHBAP_AdaptGet_TabView_IT_BlackList(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
#ifndef __MMI_PHBAP_DISABLE_GROUP__
static void mmi_PHBAP_AdapterGet_GroupList(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
static void mmi_PHBAP_AdaptGet_Group_Property(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#endif //#ifndef __MMI_PHBAP_DISABLE_GROUP__
void mmi_PHBAP_AdaptGet_SelectNum(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#ifndef __SMALL_PHB_MMI__ 
static void mmi_PHBAP_AdaptGet_CommonPopUp(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#endif

MmiPhbGroup_e mmi_PHBAP_GetGroupByMode(MMI_PHBAP* pThis, s32 s32PhbApMode);

#ifndef __MMI_PHBAP_DISABLE_GROUP__
static void mmi_PHBAP_GetGroupProperty(MMI_PHBAP                *pThis, s32                      s32MenuIdx, MmiPhbGroupContent_t     *ptGroupContent, IImage                   **ppImage, boolean                  bIsNeedFullContent);
static MAE_Ret mmi_PHBAP_SaveGroupProperty(MMI_PHBAP *pThis, s32 s32MenuIdx, MmiPhbGroupContent_t *ptGroupContent);
static u8 mmi_PHBAP_GetGroupUsedCnt(void);
static boolean  mmi_PHBAP_DeleteGroup(s32 s32PhbGroup);
static void mmi_PHBAP_DeleteGroupCB(void *pUser, void *pUserData);
static void mmi_PHBAP_UpdateGroupCallBack(void *pUser, void *pUserData);
static u32 mmi_PHBAP_GetGroupPosition(MmiPhbGroup_e s32PhbGroup);
static MmiPhbGroup_e mmi_PHBAP_GetGroupByPosition(u32 u32MenuId);
void ViewGroupShowGroupList_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupGroupListOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupEditGroup_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupEditGroupNameOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupMemberListOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectGroupListGroup_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupShowGroupList_MenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupEditGroupNameOption_MenuReqLayer2CB(void *pApplet, void *pUsrData,  WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupGroupListOption_MenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupMemberListOption_MenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectGroupListGroup_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupShowGroupList_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupEditGroup_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupGroupListOption_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __TOUCH_SCREEN_MMI__
void ViewGroupShowGroupList_TouchNoItemCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
#endif
MAE_Ret mmi_PHB_SelectGroupList_SaveDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewGroup_GroupListOptionMultiSelectDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewGroup_SaveGroupInfoDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewGroup_DeleteGroupConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewGroup_RemoveConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewGroup_DeleteGroupWaitingDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_UpdateGroup_FinishDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
void  mmi_PHBAP_ViewGroup_PrepareData(MMI_PHBAP* pThis);
void  mmi_PHBAP_SelectGroup_PrepareData(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewGroup_DeleteGroupConfirm(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewGroup_SaveGroup(MMI_PHBAP* pThis);
void  mmi_PHBAP_EditGroupName_Save(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewGroup_DeleteGroup(MMI_PHBAP* pThis);
MAE_Ret _PhbWndViewGroupGroupListOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewGroupEditGroupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewGroupEditGroupNameHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewGroupEditGroupNameOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewGroupShowMemberListHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectGroupListGroupHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndCreate_ViewGroupGroupListOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupGroupListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupGroupListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewGroupGroupListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupGroupListOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewGroupEditGroup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupEditGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupEditGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewGroupEditGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupEditGroup(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewGroupEditGroupName(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupEditGroupName(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupEditGroupName(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupEditGroupName(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewGroupEditGroupNameOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupEditGroupNameOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupEditGroupNameOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewGroupEditGroupNameOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupEditGroupNameOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewGroupShowMemberList(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupShowMemberList(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupShowMemberList(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewGroupShowMemberList(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupShowMemberList(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewGroupMemberListOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewGroupMemberListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewGroupMemberListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewGroupMemberListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewGroupMemberListOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectGroupListGroup(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_SelectGroupListGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_SelectGroupListGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectGroupListGroup(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectGroupListGroup(void *pCusHandle, void *pWndData);

MAE_Ret _PhbAppMallocAndGetGroupContent(MMI_PHBAP* pThis, MmiPhbGroupContent_t **pptGroupContent, s32 s32MenuIdx, IImage **ppImage, boolean bIsNeedFullContent);

void ViewGroupShowMemberList_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupShowMemberList_MenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewGroupShowMemberList_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _PhbWndViewGroupMemberListOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__
static void mmi_PHBAP_DeleteOptionItemByID(IWidget* pIWidget, u32 s32MenuId);
static void mmi_PHBAP_GetContactContent(MMI_PHBAP *pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, u16 u16SortingIdx, MmiPhbContactContent_t **pptContactContent, boolean bIsNeedFullContent);
static void mmi_PHBAP_WriteOneContactByPhysicalIdxReq(MMI_PHBAP *pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbContactContent_t *ptPhbContactContent, u16 u16PhbPhysicalIdx);
__INLINE void mmi_PHBAP_WriteOneNewContactReq(MMI_PHBAP                  *pThis, MmiPhbBookType_e        s32PhbBookType, MmiPhbContactContent_t     *ptPhbContactContent);
static void mmi_PHBAP_AddMenuItemInViewContactMenu(MMI_PHBAP *pThis, IWidget *pIMenuWdg, u32 eImgID, u32 nItemId, u8 *u8Str, u8 u8StrLen, boolean bIsNumber);
__INLINE void mmi_PHBAP_AddRingtoneMenuItemInViewContactMenu(MMI_PHBAP *pThis, IWidget *pIMenuWdg, u32 eImgID, u32 u32PhbRingtoneIdx);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
__INLINE void mmi_PHBAP_AddVideotoneMenuItemInViewContactMenu(MMI_PHBAP *pThis, IWidget *pIMenuWdg, u32 eImgID, u32 u32PhbVideotoneIdx);
#endif
#ifdef __PHB_NO_SEARCH__
static void mmi_PHBAP_TimeoutKeyRepeat_cb(void* data);
#endif
static void mmi_PHBAP_SetTitleSMSStr(MMI_PHBAP* pThis, IWidget *pITitleWidget, u16 u16Count, u16 u16Max);
static void mmi_PHBAP_PlayCb(void *pUserData, MediaSrvErrCode_e eErrorCode);
static void mmi_PHBAP_StopCb(void *pUserData, MediaSrvErrCode_e eErrorCode);
static void mmi_PHBAP_PlayStatusCb(void *pUserData, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
static void mmi_PHBAP_InterruptCb(void *pUserData, u32 nCusData, MediaSrvInterruptStatus_e eStatus);
static MAERet_t mmi_PHBAP_LoadContactImage(MMI_PHBAP* pThis, IWidget* pIWidget, u32 ImgId);
static void mmi_PHBAP_HandKeyPressWhenShowList(MMI_PHBAP* pThis, u32 nEvt, u32 param1, u32 param2);
MmiPhbBookType_e mmi_PHBAP_GetBookTypeByMode(MMI_PHBAP* pThis, s32 s32PhbApMode);
void mmi_PHBAP_SetTextToDownWidget(MMI_PHBAP* pThis, IWidget *pIWidget, u8 *pu8String, u8 u8Len);
void mmi_PHBAP_SetNumberTextToDownWidget(MMI_PHBAP* pThis, IWidget *pIWidget, u8 *pu8String, u8 u8Len, u32 u32MaxLen, boolean *pbIsNumEmpty);
boolean MMI_PHBAP_GetRecipientByPhbContactContent(MmiPhbContactContent_t *ptContactContent, u8 u8Idx, boolean bIsGetEmail, MsgRecipient_t  *psRecipients);
boolean mmi_PHBAP_MenuWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean mmi_PHBAP_InputWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean mmi_PHBAP_MultiSelect_MenuWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean mmi_PHBAP_MultiSelect_InputWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean mmi_PHBAP_MemberList_MenuWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
boolean mmi_PHBAP_MemberList_InputWidget_Handler(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
static void mmi_PHBAP_SetBJXIconOnTitle(MMI_PHBAP* pThis);
u16 mmi_PHBAP_ConvertFilterSortingIdxToTotal(MMI_PHBAP *pThis, MmiPhbBookType_e s32PhbActionBookType, MmiPhbGroup_e s32PhbActionGroup, u16 u16FilterIdx);
__SLDPM_FREE__ u16 mmi_PHBAP_ConvertTotalSortingIdxToFilterSortingIdx(MMI_PHBAP *pThis, MmiPhbBookType_e s32PhbActionBookType, MmiPhbGroup_e s32PhbActionGroup, u16 u16SortingIdx, u16 u16TotalNumber, u16 u16FilterNumber);
static MAE_Ret mmi_PHBAP_StoreContactField(MMI_PHBAP *pThis, MmiPhbContactContent_t  *ptMmiPhbContactContent, IWidget *pIFullEditInputWidget, u8 u8Field);
#ifndef __SMALL_PHB_MMI__
static u8 mmi_PHBAP_GetFocusItemNumberID(MMI_PHBAP* pThis);
#endif
s32 mmi_PHBAP_CalculateDynamicLen(MmiPhbContactContent_t *ptContent);
#ifdef __APP_MMI_BJX__
static boolean mmi_PHBAP_IsChineseLangPackAvailable(MMI_PHBAP* pThis);
#endif
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void mmi_PHBAP_ImportContacts_Timercb(void* data);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void mmi_PHBAP_RebuildReq_CB(void* data);

#ifdef __SXMENGINE__
void mmi_PHBAP_VideoChat(MMI_PHBAP *pThis);
#endif
boolean mmi_PHBAP_IsCharactorKey(u32 nKeyCode);
#ifdef __MMI_PHBAP_ALL_TAB__
MmiPhbBookType_e mmi_PHBAP_GetContactBookType(MMI_PHBAP* pThis, s32 s32PhbBookType, s32 s32PhbGroup, u16 u16PhbSortingIdx);
static u16 mmi_PHBAP_GetAllTabBookType(void);
#endif

/*=============================================================*/
//AP Level CB
/*=============================================================*/

MAE_Ret _PhbConstructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
MAE_Ret _PhbDestructor(IApplet *pApplet, u32 nEvt, u32 Param1, u32 Param2);
boolean _PhbStartCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _PhbSuspend(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _PhbResume(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _PhbStop(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _PhbEmbeddedApClose(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
boolean _PhbKeyPressCB(IApplet *pApplet, u32 nEvt, u32 param1, u32 param2);
MAE_Ret _PHBAP_UpdateTabIcon(MMI_PHBAP *pThis, IWidget *pITabWdg, u8 u8TabIdx);

#ifdef __APP_MMI_PRIVATEPROTECT__ 
void _PhbPrivateProtectStatusCB(void *pIApplet, PrivateProtectAuthResult_e eAuthResult);
#endif

#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
void ViewBlackList_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewBlackList_MenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewBlackList_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _PhbWndViewBlackListOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndCreate_ViewBlackListOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_ViewBlackListOption(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndHide_ViewBlackListOption(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndConvert_ViewBlackListOption(void* pCusHandle, void* pWndData);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    

u16 _PhbGetBookTypeByPhyIdx(u16 u16PhbPhysicalIdx);

#if defined(__3D_UI_PHONEBOOK__)
boolean _PhbTouchPressCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean _PhbTouchUpAndDownCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _PhbWndRegisterMenuWdgFlipCompleteCb(IWidget *pMenuWdg, PfnMenuWidgetFlipComplete pfn, void *pUserData);
MAE_Ret _PhbWndDeregisterMenuWdgFlipCompleteCb(IWidget *pMenuWdg, PfnMenuWidgetFlipComplete pfn, void *pUserData);
boolean _PhbWndReflash_AfterMenuWdgFlipComplete(IWidget *pMenuWdg, void *pData);
MAE_Ret _PhbWndUpdate_ViewContactShowDetail(IApplet *pApplet);
#endif //end of #if defined(__3D_UI_PHONEBOOK__)

void mmi_PHBAP_SelectImageID_SelectNew_FileMgrCB(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
void mmi_PHBAP_SelectImageID_ImageFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
void mmi_PHBAP_SelectVideoID_VideoFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
#endif
void mmi_PHBAP_SelectRingID_SelectNew_FileMgrCB(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
void mmi_PHBAP_SelectFile_FileFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
#ifdef __APP_MMI_BJX__
void mmi_PHBAP_LaunchBaiJiaXing_BJXAPPCB(void *pUserData, MAE_Ret nRspCode, BjxAppFindContactIdRspData_t *pRspData, BjxAppFindContactIdRspDataFreeCb pfnRspDataFreeCb);
#endif

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void mmi_PHBAP_ImportContacts_FileMgrCB(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
void mmi_PHBAP_ImportContactsMultiPickOptionMenuSelectCb(void *pUserData, u32 nMenuId, FileManagerFileInfo_t *sFileInfo, boolean *pbCloseApp, boolean *pbHandled, CmnAppLaunchFileOpRspCbInfo_t *psRspCbInfo);
void mmi_PHBAP_ImportContactsMultiPickGetOptionMenuCb(void *pUserData, u32 nFolderLevel, void *pFileInfo, u32 *pOptonMeneuItemNum, const WdgStaticMenuItem_t **pOptionMeneuItemList, PfnFileMgrOptMenuSelectCb *pfnSelectCb);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void mmi_PHBAP_GetVirtualVolumeListCb(void *pUserData, u32 *pNumber, const FileMgrVirtualVolumeItem_t **pVirtualVolumeList);

void ViewPhbListShowContactList_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewPhbListOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewPhbListSelectNumToSave_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewContactShowDetail_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewContactOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditContactFullEditOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditSelectionShowNewOrExist_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditSelectionShowSaveTo_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditSelectionShowNumType_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectImageIDShowChangeMenu_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectRingIDShowChangeMenu_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
void SelectVideoIDShowChangeMenu_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif
void MakeCall_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void CopyToMenu_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifndef __SMALL_PHB_MMI__
void SelectNumber_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif // #ifndef __SMALL_PHB_MMI__
void MultiSelectOption_MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void ViewPhbListShowContactList_MenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MultiSelectReady_MenuBackCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void ViewPhbListOption_MenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditContactFullEditOption_MenuReqLayer2CB(void *pApplet, void *pUsrData,  WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewContactOption_MenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MultiSelectOption_MenuReqLayer2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void PHBAP_Common_Layer2MenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void ViewPhbListShowContactList_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectImageIDShowChangeMenu_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MultiSelectReady_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewPhbListShowContactList_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewContactShowDetail_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectImageIDShowChangeMenu_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void SelectRingIDShowChangeMenu_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
void SelectVideoIDShowChangeMenu_SoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

void PHBAP_Common_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void ViewPhbListOption_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditSelectionShowNewOrExist_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void EditSelectionShowSaveTo_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void MultiSelectReady_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#ifndef __SMALL_PHB_MMI__
void SelectNumber_SoftkeyCancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif 
void SelectRingID_VolumeChangeCB(void * pUsrData, ModelEvent_t *pMdlEvent);

void ViewContactShowDetail_OnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);

void EditContactShowEdit_MFLFocusSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void EditContactShowEdit_MFLFocusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);

void InputWdg_TextChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);
void EditContactShowEdit_TextChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

void TabViewTabChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);
void TabViewMultiSelectTabChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TabChangeData_t *pTabData, IWidget *pWidget);
#ifdef __TOUCH_SCREEN_MMI__
void ViewPhbListShowContactList_TouchNoItemCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
#endif
void ViewPhbListShowContactList_MenuMarkedNumberChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
void MultiSelectReady_MenuMarkedNumberChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, void *pReserve);
#ifdef __APP_MMI_BJX__	
void BJX_Title_APIconPressCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 u32TitleIconId, IWidget *pWidget);
#endif

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
MAE_Ret MMI_PHB_SelectStorageCB(void* pCusHandle, const CommWindowMsg_t *pWndMsg, void* pParam1, void* pParam2 );
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
/*=============================================================*/
//Dialog CB
/*=============================================================*/

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
MAE_Ret mmi_PHB_SelectVideoIDShowChangeMenu_VideotoneConfirmCB(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif
MAE_Ret PhonebookReady_WatingDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ViewContact_PrepareDataDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_EditContact_PrepareDataDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_EditContact_SaveCheckDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
MAE_Ret mmi_PHB_ViewPhbList_OptionConfirmAssignBKDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
MAE_Ret mmi_PHB_Common_CloseDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHP_Common_RecreateDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_Common_ReturnToListViewDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_Close_AP_DialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_CheckIfReplace_ConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_CheckIfLeave_ConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_CheckIfLeave_WarningDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
MAE_Ret mmi_PHB_ImportContacts_ConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_ImportContacts_FinishDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
MAE_Ret mmi_PHB_SendMessageRecreateDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_MultiSelect_WatingDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_MultiSelect_RemoveConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_MultiSelect_ContinueConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_MultiSelect_DeleteConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_MultiSelect_DeleteContactsDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_DeleteContact_DeleteDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_HashSrv_ErrorHandle_DialogHandle(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_DeleteContact_ConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
MAE_Ret mmi_PHB_GetDetails_DialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#ifdef __SXMENGINE__
MAE_Ret mmi_PHB_VideoChat_ConfirmDialogHdl(void *pData, MAEEvent_t nEvt, u32 param1, u32 param2);
#endif

/*=============================================================*/
//Internal function
/*=============================================================*/
void  _PHB_InitPHBStyle(MMI_PHBAP* pThis);
void  _PHB_ShowPHBContactList(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewContact_PrepareData(MMI_PHBAP* pThis);
void  mmi_PHBAP_EditContact_PrepareData(MMI_PHBAP* pThis);
void  mmi_PHBAP_EditContact_CheckIfLeave(MMI_PHBAP* pThis);
void  mmi_PHBAP_MakeCall_Call(MMI_PHBAP* pThis, u32  param);
boolean mmi_PHBAP_CheckNumberValid(MmiPhbNumber_t *ptPhbNumber);
boolean mmi_PHBAP_CheckContactNumberValid(MmiPhbContactContent_t  *ptContactContent);
void  mmi_PHBAP_EditContact_Save(MMI_PHBAP* pThis, u32  param);
void mmi_PHBAP_CopyContact(MMI_PHBAP* pThis);

void  mmi_PHBAP_SelectNumToSave_Save(MMI_PHBAP* pThis);
void  mmi_PHBAP_MakeCall_PrepareData(MMI_PHBAP* pThis);
void  mmi_PHBAP_MakeCall_Call(MMI_PHBAP* pThis, u32  param);
void  mmi_PHBAP_DeleteContact(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewPhbList_GetDetails(MMI_PHBAP* pThis);
void  mmi_PHBAP_ViewPhbList_GetMultiDetails(MMI_PHBAP* pThis , boolean bIsFirst);
void mmi_PHBAP_Rebuild(MMI_PHBAP* pThis);
void  mmi_PHBAP_PrepareRecipientList(MMI_PHBAP* pThis);
void  mmi_PHBAP_PrepareRecipientList_ProcessData(MMI_PHBAP* pThis);
void  mmi_PHBAP_PrepareRecipientList_OK(MMI_PHBAP* pThis);
void  mmi_PHBAP_LaunchBaiJiaXing(MMI_PHBAP* pThis);
void  mmi_PHBAP_LaunchFDNAP(MMI_PHBAP* pThis);
#ifndef __SMALL_PHB_MMI__
#ifdef __EMAIL_MMI__
void  mmi_PHBAP_LaunchEmailApp(MMI_PHBAP *pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, u16 u16PhbSortingIdx);
#endif
#endif
void  mmi_PHBAP_ShowErrMsgAndReturn(MMI_PHBAP* pThis , u32 u32TextId);
void  mmi_PHBAP_ErrorHandle(MMI_PHBAP* pThis, MAE_Ret ret);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void  mmi_PHBAP_ExportContacts(MMI_PHBAP* pThis);
void  mmi_PHBAP_ExportContacts_GetContactToEncode(MMI_PHBAP* pThis , MmiPhbExportContactReq_t * param1);
void  mmi_PHBAP_ExportContacts_Finish(MMI_PHBAP* pThis, u32 u32TxtID);
void  mmi_PHBAP_ImportContacts(MMI_PHBAP* pThis);
void  mmi_PHBAP_ImportContacts_ReadCheckFile(MMI_PHBAP* pThis);
void  mmi_PHBAP_ImportContacts_AddContactFromFile(MMI_PHBAP* pThis);
void  mmi_PHBAP_ImportContacts_Finish(MMI_PHBAP* pThis, u32 param1);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void  mmi_PHBAP_MultiSelect_PrepareData(MMI_PHBAP* pThis);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void  mmi_PHBAP_SendvCard(MMI_PHBAP* pThis);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void  mmi_PHBAP_MultiSelect_Save(MMI_PHBAP * pThis);
#ifndef __MMI_PHBAP_DISABLE_GROUP__   
void mmi_PHBAP_MultiSelect_Timeout_CB(void *pUser, void *pUserData);
#endif
void mmi_PHBAP_MultiSelect_DeleteContacts(MMI_PHBAP * pThis);
void mmi_PHBAP_MultiSelect_CopyContacts(MMI_PHBAP * pThis , MmiPhbAppMultiSelectMode_e mode);
void mmi_PHBAP_MultiSelect_StartMultiDelete(MMI_PHBAP * pThis , MmiPhbAppMultiSelectMode_e mode);
void mmi_PHBAP_SetBJXIconInvisible(MMI_PHBAP* pThis);
static MAE_WChar * mmi_PHBAP_GetNameByRegId(MMI_PHBAP* pThis, u32 u32RegId, boolean bIsGetDefaultWhenEmpty);

/*=============================================================*/
//Wnd Functions
/*=============================================================*/

MAE_Ret _PhbWndInitHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndTabViewHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewPhbListOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewContactShowDetailHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifndef __SMALL_PHB_MMI__
MAE_Ret _PhbWndViewContactViewItemDetailHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewPhbListSelectNumToSaveHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditSelectionShowNumTypeHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectNumberHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif
MAE_Ret _PhbWndViewContactOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditContactShowEditHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditContactFullEditHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditContactFullEditOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditSelectionShowNewOrExistHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndEditSelectionShowSaveToHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndViewMemoryStatusHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndMultiSelectReadyHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndMultiSelectOptionHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectImageIDShowCurrentHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectImageIDShowChangeMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectRingIDShowCurrentHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectRingIDShowChangeMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
static MAE_Ret _PhbWndCreate_SelectVideoIDShowCurrent(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_SelectVideoIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectVideoIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectVideoIDShowCurrent(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectVideoIDShowChangeMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_SelectVideoIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectVideoIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectVideoIDShowChangeMenu(void* pCusHandle, void* pWndData);

MAE_Ret _PhbWndSelectVideoIDShowCurrentHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndSelectVideoIDShowChangeMenuHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif

MAE_Ret _PhbWndCreate_Init(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndDestroy_Init(void *pCusHandle, void *pWndData);
MAE_Ret _PhbWndShow_Init(void *pCusHandle, void *pWndData);
MAE_Ret _PhbWndConvert_Init(void* pCusHandle, void* pWndData);

__SLDPM_FREE__ MAE_Ret _PhbWndCreate_TabView(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret _PhbWndDestroy_TabView(void *pCusHandle, void *pWndData);
MAE_Ret _PhbWndShow_TabView(void *pCusHandle, void *pWndData);
MAE_Ret _PhbWndHide_TabView(void *pCusHandle, void *pWndData);
MAE_Ret _PhbWndConvert_TabView(void *pCusHandle, void *pWndData);

static void _PhbWndDeregister_TabMenuCallback(MMI_PHBAP *pThis, IWidget *pIMenuWdg);

static void _PHB_SetSearchOptions_SoftkeyActCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

#ifndef __SMALL_PHB_MMI__
static MAE_Ret _PhbWndCreate_ViewPhbListSelectNumToSave(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_ViewPhbListSelectNumToSave(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndHide_ViewPhbListSelectNumToSave(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndConvert_ViewPhbListSelectNumToSave(void *pCusHandle, void *pWndData);
#endif

static MAE_Ret _PhbWndCreate_ViewPhbListOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewPhbListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewPhbListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewPhbListOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewPhbListOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewContactShowDetail(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewContactShowDetail(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewContactShowDetail(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewContactShowDetail(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewContactShowDetail(void *pCusHandle, void *pWndData);

#ifndef __SMALL_PHB_MMI__
static MAE_Ret _PhbWndCreate_ViewContactViewItemDetail(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewContactViewItemDetail(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewContactViewItemDetail(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewContactViewItemDetail(void* pCusHandle, void* pWndData);
#endif // #ifndef __SMALL_PHB_MMI__

static MAE_Ret _PhbWndCreate_ViewContactOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_ViewContactOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_ViewContactOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_ViewContactOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewContactOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_EditContactShowEdit(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_EditContactShowEdit(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_EditContactShowEdit(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_EditContactShowEdit(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditContactShowEdit(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_EditContactFullEdit(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_EditContactFullEdit(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_EditContactFullEdit(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditContactFullEdit(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_EditContactFullEditOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_EditContactFullEditOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_EditContactFullEditOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_EditContactFullEditOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditContactFullEditOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_EditSelectionShowNewOrExist(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_EditSelectionShowNewOrExist(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_EditSelectionShowNewOrExist(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditSelectionShowNewOrExist(void *pCusHandle, void *pWndData);

static MAE_Ret _PhbWndCreate_EditSelectionShowSaveTo(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_EditSelectionShowSaveTo(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_EditSelectionShowSaveTo(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditSelectionShowSaveTo(void* pCusHandle, void* pWndData);

#ifndef __SMALL_PHB_MMI__
static MAE_Ret _PhbWndCreate_EditSelectionShowNumType(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_EditSelectionShowNumType(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_EditSelectionShowNumType(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_EditSelectionShowNumType(void* pCusHandle, void* pWndData);
#endif

static MAE_Ret _PhbWndCreate_SetSearchOptions(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_SetSearchOptions(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndConvert_SetSearchOptions(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_ViewMemoryStatus(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_ViewMemoryStatus(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_ViewMemoryStatus(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_MultiSelectReady(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_MultiSelectReady(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_MultiSelectReady(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_MultiSelectReady(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_MultiSelectReady(void* pCusHandle, void* pWndData);
static void _PhbWnd_MultiSelectReadySetMenuWdgSoftKey(MMI_PHBAP *pThis, u32 nMenuSize);

static MAE_Ret _PhbWndCreate_MultiSelectOption(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_MultiSelectOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_MultiSelectOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_MultiSelectOption(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_MultiSelectOption(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectImageIDShowCurrent(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_SelectImageIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_SelectImageIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectImageIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectImageIDShowCurrent(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectImageIDShowChangeMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_SelectImageIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectImageIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectImageIDShowChangeMenu(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectRingIDShowCurrent(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_SelectRingIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectRingIDShowCurrent(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectRingIDShowCurrent(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_SelectRingIDShowChangeMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_SelectRingIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectRingIDShowChangeMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectRingIDShowChangeMenu(void* pCusHandle, void* pWndData);

static MAE_Ret _PhbWndCreate_CopyToMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndShow_CopyToMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_CopyToMenu(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_CopyToMenu(void *pCusHandle, void *pWndData);

#ifndef __SMALL_PHB_MMI__ // only support one number and no email in small phb
static MAE_Ret _PhbWndCreate_SelectNumber(void *pCusHandle, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndDestroy_SelectNumber(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndShow_SelectNumber(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndHide_SelectNumber(void* pCusHandle, void* pWndData);
static MAE_Ret _PhbWndConvert_SelectNumber(void *pCusHandle, void *pWndData);
#endif
/*=============================================================*/
//Other Functions used by callback functions
/*=============================================================*/
#if defined(__3D_UI_PHONEBOOK__)
void _PhbWnd_ContactView_AniContainerNotify(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);
#endif //end of #if defined(__3D_UI_PHONEBOOK__)


/*=============================================================*/
//PhbApp param data creation & free functions
/*=============================================================*/
PhbAppParamData_t* _PhbAppAllocateParamData(MMI_PHB_AP_FID_E eFid);
__SLDPM_FREE__ void _PhbAppCopyParamData(MMI_PHB_AP_FID_E eFid, PhbAppParamData_t* pToParam, PhbAppParamData_t* pFromParam);
void _PhbAppFreeParamData(IBase *pIssuer, u32 pInParam);
void _PHBSetWdgBasicLayout(HWIN hWin, IWidget *pWdg, Pos_t *pPos,WidgetSize_t *pSize);

/* Copy contact data to Black list */
void _PhbAppCopyContactDataByMask(PhoneBookContactFieldMask_e eMask,
                                  PhoneBookContactData_t *pToContact,
                                  MmiPhbContactContent_t *pFromContact,
                                  s8 uPhbNumIdx);

PhoneBookGetContactRecord_t* _PhoneBookInitContactRspData(u16 uMaxNum, PhoneBookContactFieldMask_e eMask);

/* Callback free function */
void _PhoneBookGetContactRspDataFreeCb(PhoneBookGetContactRecord_t *psRspData);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void _PhoneBookGetContactVCardRspDataFreeCb(PhoneBookGetVCardRspData_t *psRspData);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#ifndef __MMI_PHBAP_DISABLE_GROUP__
static void mmi_PHBAP_FreeMenuModelData_DoubleText(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
#endif
static void mmi_PHBAP_FreeMenuModelData_ImageText(WdgDynamicMenuItemPtr_t *pItemDataPtr, void *pOwner, WdgMenuItemType_e eItemType);
#ifndef __SMALL_PHB_MMI__ 
static void mmi_PHBAP_FreeMenuModelData_ITSTextInfo(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
#endif
void mmi_PHBAP_FreeMenuHandler(void *pUsrData);
void mmi_PHBAP_FreeInputHandler(void *pUsrData);
void mmi_PHBAP_MultiSelect_FreeMenuHandler(void *pUsrData);
void mmi_PHBAP_MultiSelect_FreeInputHandler(void *pUsrData);
void mmi_PHBAP_MemberLust_FreeMenuHandler(void *pUsrData);
void mmi_PHBAP_MemberLust_FreeInputHandler(void *pUsrData);
#ifdef __SXMENGINE__
static void _PHBAP_CleanFuncForVideoChat(void *pUserData, MAE_Ret nRspCode);
#endif

static void mmi_PHBAP_UpdateAllCheckStatusToLocal(MMI_PHBAP* pThis);
static void mmi_PHBAP_UpdateLocalCheckStatusToAll(MMI_PHBAP* pThis);

void _PhbAppCheckAndSetCheckStatus(boolean *pCheckStatus, s32 s32Index, boolean bValue, u16 u16CheckStatusSize);
MAE_Ret _PhbAppHandleLaunchByCCToSaveNum(MMI_PHBAP* pThis, u32 param1, u32 param2);
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
void _PhbAppHandleAssignContactToBK(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup);
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
void _PhbAppSetMultiSelectText(MMI_PHBAP* pThis, IWidget *pTitleWdg, u16 blacknum);
void _PhbAppHandleImgRingMenuSelect(void *pApplet, u8 u8SelectType, HistoryInfo_t *pHistoryInfo);
boolean _PhbAppHandleReadCnfInGetMultiDetailAndCheckIfNeedSelectNum(MMI_PHBAP* pThis, PhoneBookContactData_t *pGetContactRecordPos);
boolean _PhbAppHandleCheckIfNeedGetNextInGetMultiDetail(MMI_PHBAP* pThis, u16 u16PhbMaxContacts);
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
boolean _PhbAppHandleExport(MMI_PHBAP* pThis, u32 *pTxtId, boolean *pbWarnDialog, u8 u8ExportType);
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
void _PhbAppSetBookGroupTypeInTabChange(MMI_PHBAP* pThis, u32 u32Idx);
void _PhbAppGetSDStatus(MMI_PHBAP   *pThis);
u8 _PhbAppConvertNumHighlightIdxToPhysicalIdx(MmiPhbContactContent_t  *ptContactContent, u8 u8HighlightIdx, boolean *pbIsFocusOnEmail);
void _PhbAppGetNumCountAndLastNumIdx(MmiPhbContactContent_t  *ptContactContent, u8 *pu8TotalNum, u8 *pu8LastNumIdx);
u16	_PhbAppGetMarkNum(boolean *pbCheckStatus, u16 u16Size);
MAE_Ret _PhbAppGetInputStrDup(IWidget *pInputWdg, MAE_WChar **ppwStr, u16 *pu16StrLen, boolean bIsNeedTrim);
MAE_Ret _PhbAppDecodeSIMToStrDup(MAE_WChar **ppwstr, size_t *pLen, u8 *pu8SIMStr, u16 u16SIMLen);
MAE_Ret _PhbAppDecodeAsciiToStrDup(MAE_WChar **ppwstr, size_t *pLen, u8 *pu8ASCIIStr, u16 u16ASCIIMLen);
void _PhbAppFreeImage(IBase **pImg);
MAE_Ret _PhbAppSetTitleStringAndLayout(HWIN hWin, u32 u32ID, WdgTitleStyle_t nLayout);
MAE_Ret _PhbAppQueryPhbStatusAsync(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, SrvPhbQueryPhbStatusCB pfnCallback);
MAE_Ret _PhbAppQueryPhbStatus(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, MmiPhbQueryPhbStatusCnf_t **ppCnf);
MAE_Ret _PhbAppReadOneContactBySortingAsync(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, u16 u16SortingIdx, SrvPhbReadOneContactBySortingIdxCB pfnCallback);
MAE_Ret _PhbAppDeleteOneContactBySortingAsync(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookType, MmiPhbGroup_e s32PhbGroup, u16 u16SortingIdx, SrvPhbDeleteOneContactBySortingIdxCB pfnCallback);
MAE_Ret _PhbAppCopyOneContactBySortingAsync(MMI_PHBAP* pThis, MmiPhbBookType_e s32PhbBookTypeSrc, MmiPhbBookType_e s32PhbBookTypeDst, u16 u16SortingIdx, SrvPhbCopyOneContactBySortingIdxCB pfnCallback);
MAE_Ret _PhbAppDisplayOverMaxDialog(MMI_PHBAP* pThis, u16 u16Max, PFN_DlgHandler pfnDialogHdl);
void _PhbAppHandleSelectFile(MMI_PHBAP   *pThis, AppGetFileRspData_t *psRspData, u32 *pu32IdxNew, u8 u8SelectType);
#ifdef __MMS_MMI_CDMMS__	
u32 _PhbAppCheckMMSIsReady(MMI_PHBAP* pThis);
#endif

#if !defined(__MMI_PHB_DISABLE_BLACKLIST__) && defined(__PHB_SELECT_BK_FROM_PHB__)
void _PhbAppGetMultiContactCb(void *pvUserData,
									  MAE_Ret nRspCode,
									  PhoneBookGetContactRecord_t *psRspData,
									  PhoneBookGetContactRspDataFreeCb pfnRspDataFreeCb);
static void mmi_PHBAP_TimeoutGetMultiContactForBK_cb(void* data);
#endif

void _PhbAppGetMemoryStr(MMI_PHBAP* pThis, u32 u32TempStrLen, s32 s32Size, MAE_WChar *pwMemName, MAE_WChar *pMemoryDetailsStr);

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#ifdef __PHB_SEND_MULTI_VCARD_BY_BT__
void _PhbAppDeleteTmpFiles(MMI_PHBAP* pThis);
void _PhbAppDeleteTmpFilesCb(void *pApplet, void *pInfo);
#endif
#endif //#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

#if defined(__MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__) || defined(__MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__)
void PhbAppGetSearchType(MMI_PHB_SEARCH_TYPE_E *peSearchType);
#endif

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
void _PHB_SelectExportFormatSoftkeyActCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _PHB_WndSelectExportFormatHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
static MAE_Ret _PhbWndCreate_SelectExportFormatView(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndDestory_SelectExportFormatView(void *pCusHandle, void *pWndData);
static MAE_Ret _PhbWndConvert_SelectExportFormatView(void *pCusHandle, void *pWndData);

#endif
#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
static u8 _PhbAppConvertMFLFocusIdx(u8 u8MFLFocusItem);

#ifdef __APP_MMI_GROUP_APP__
void PhbAppInputWdgSKBVisibleChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bVisible, IWidget *pWidget);
#endif

#endif /* __MMI_PHBAPP_PRIV_H__ */
