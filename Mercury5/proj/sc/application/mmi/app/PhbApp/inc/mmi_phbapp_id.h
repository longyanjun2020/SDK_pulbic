#ifndef __MMI_PHBAPP_ID_H__
#define __MMI_PHBAPP_ID_H__


#ifdef __APP_MMI_SMALLROM__
#define __PHBAPP_SMALLROM__
#endif	// __APP_MMI_SMALLROM__

#define MMI_PHB_NUMBER_MAX_RS 4
typedef enum PhbWndId_e_
{
    PHB_WND_INIT = WND_ID_APP_BASE,
    PHB_WND_TabView,
    PHB_WND_ViewPhbListSelectNumToSave,
    PHB_WND_ViewPhbListOption,
    PHB_WND_ViewContactShowDetail,
    PHB_WND_ViewContactViewItemDetail,
    PHB_WND_ViewContactOption,
    PHB_WND_EditContactShowEdit,
    PHB_WND_EditContactFullEdit,
    PHB_WND_EditContactFullEditOption,
    PHB_WND_EditSelectionShowNewOrExist,
    PHB_WND_EditSelectionShowSaveTo,
    PHB_WND_EditSelectionShowNumType,
    PHB_WND_ViewMemoryStatus,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    PHB_WND_ViewGroupShowGroupList,
    PHB_WND_ViewGroupGroupListOption,
    PHB_WND_ViewGroupEditGroup,
    PHB_WND_ViewGroupEditGroupName,
    PHB_WND_ViewGroupEditGroupNameOption,
    PHB_WND_ViewGroupShowMemberList,
    PHB_WND_ViewGroupMemberListOption,
#endif    
    PHB_WND_BKListOption,
    PHB_WND_BKListEmptyOptionItem,
    PHB_WND_BKListOptionItem,
    PHB_WND_MultiSelectReady,
    PHB_WND_MultiSelectOption,
    PHB_WND_MultiSelectOption1,
    PHB_WND_MultiSelectOption2,
    PHB_WND_SelectImageIDShowCurrent,
    PHB_WND_SelectImageIDShowChangeMenu,
    PHB_WND_SelectRingIDShowCurrent,
    PHB_WND_SelectRingIDShowChangeMenu,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    PHB_WND_SelectVideoIDShowCurrent,
    PHB_WND_SelectVideoIDShowChangeMenu,
#endif
#ifndef __MMI_PHBAP_DISABLE_GROUP__
    PHB_WND_SelectGroupListGroup,
#endif    
    PHB_WND_SetSearchOptions,
    PHB_WND_CopyToMenu,
    PHB_WND_SelectNumber,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__    
    PHB_WND_SelectExportFormat
#endif    
} PhbWndId_e_WndId_e;

enum //VID_PHB_TABLIST_SHOWMENU_VIEW_enum
{
    ePROPCONTAINER = APP_WDG_START,
    eTabWidget,
    eMENUWidget,
    eTextWdg,
    eSearchAbsContainer,
    eSearchBgImageWidget,
    eSearchImgWidget,
    eSearchInputWidget,
}; //VID_PHB_TABLIST_SHOWMENU_VIEW_enum

enum //VID_PHB_MEMBER_LIST_VIEW_enum
{
    ePropContainer = 0x1210,
    eMenuWdg,
    eAbsContainer,
    eBGImageWdg,
    eSearchImageWidget,
    eInputWidget,
}; //VID_PHB_MEMBER_LIST_VIEW_enum

enum //VID_PHB_VIEW_CONTACT_VIEW_enum
{
    eBGImageWidget = 0x1220,
    eHeadImageWidget,
#ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    eHeadBlistImageWidget,
#endif // #ifndef __MMI_PHB_DISABLE_BLACKLIST__    
    eNameTextWidget,
    eDualSimImageWidget,
    eMenuWidget,
#if defined(__3D_UI_PHONEBOOK__)
	eContactViewAniCntr,
	eTopHalfViewAniCntr,	
#endif    
}; //VID_PHB_VIEW_CONTACT_VIEW_enum

enum //VID_PHB_ADD_EDIT_CONTACT_VIEW_enum
{
    eScrollbarWdg = 0x1230,
    eMFLContainer,
    eNameDoubleTextWidget,
    eMobileTextInputWidget,
    eHomeTextInputWidget,
    eOfficeTextInputWidget,
    eOtherTextInputWidget,
#ifndef __MMI_PHBAP_DISABLE_GROUP__    
    eGroupDoubleTextWidget,
#endif    
    ePictureDoubleTextWidget,
    eRingtoneDoubleTextWidget,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
    eVideotoneDoubleTextWidget,
#endif
    eCompanyDoubleTextWidget,
    eDepartmentDoubleTextWidget,
    ePositionDoubleTextWidget,
    eAddressDoubleTextWidget,
    eEmailDoubleTextWidget,
    eUrlDoubleTextWidget,
    eNoteDoubleTextWidget,
}; //VID_PHB_ADD_EDIT_CONTACT_VIEW_enum

enum //VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_enum
{
    eSCROLLBARWIDGET = 0x1250,
    eMFLCONTAINER,
    eDOUBLETEXTWIDGET,
    eTEXTINPUTWIDGET,
}; //VID_PHB_ADD_EDIT_CONTACT_ADN_VIEW_enum

enum //VID_PHB_SETPIC_VIEW_enum
{
    eImageWidget = 0x1260,
}; //VID_PHB_SETPIC_VIEW_enum

enum //VID_PHB_SETRING_VIEW_enum
{
    eTextWidget = 0x1270,
}; //VID_PHB_SETRING_VIEW_enum

#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
enum //VID_PHB_SETVIDEO_VIEW_enum
{
    eVideoTextWidget = 0x1280,
}; //VID_PHB_SETVIDEO_VIEW_enum
#endif

typedef enum
{
	MNU_COMMON_TEXT_EXIT = 0x8000,		/* Change from 0 to 0x8000, prevent the menu id and list id have conflict.  */

	MNU_PHBAP_VIEW_CONTACT,
	MNU_PHBAP_MAKE_CALL,
	MNU_PHBAP_VIDEO_CALL,
	MNU_PHBAP_IP_CALL,
	MNU_PHBAP_SEND,
	MNU_PHBAP_SEND_SMS,
	MNU_PHBAP_SEND_MMS,
	MNU_PHBAP_MARK_MODE_OPTION,
	MNU_PHBAP_MARK,
	MNU_PHBAP_UNMARK,
	MNU_PHBAP_MARK_ALL,
	MNU_PHBAP_UNMARK_ALL,
	MNU_PHBAP_COPY_TO_PHONE,
	MNU_PHBAP_COPY_TO_SIM,
	MNU_PHBAP_COPY_TO_MASTER_SIM,
	MNU_PHBAP_COPY_TO_SLAVE_SIM,
	MNU_PHBAP_COPY_OPTION,
	MNU_PHBAP_ASSIGN_TO_BLACKLIST,
	MNU_PHBAP_ASSIGN_TO_GROUP,
	MNU_PHBAP_VCARD_OPTION,
	MNU_PHBAP_VCARD_IMPORT,
	MNU_PHBAP_VCARD_EXPORT,
	MNU_PHBAP_VCARD_SEND,
	MNU_PHBAP_FDN,
	MNU_PHBAP_MEMORY_DETAILS,
	MNU_PHBAP_SEARCH_OPTIONS,
	MNU_PHBAP_SXM_VIDEO,
    MNU_PHBAP_DELETE_CONTACT,
	MNU_PHBAP_VIEW_CONTACT_OPTION,
	MNU_PHBAP_SET_PICTURE,
	MNU_PHBAP_SET_RINGTONE,
#ifdef __MMI_PHB_VIDEOTONE_SUPPORT__
	MNU_PHBAP_SET_VIDEOTONE,
#endif
	MNU_PHBAP_EDIT_CONTACT,
	MNU_PHBAP_EDIT_NAME,
	MNU_PHBAP_EDIT_MOBILE,
	MNU_PHBAP_EDIT_HOME,
	MNU_PHBAP_EDIT_OFFICE,
	MNU_PHBAP_EDIT_OTHER,
	MNU_PHBAP_EDIT_GROUP,
	MNU_PHBAP_EDIT_COMPANY,
	MNU_PHBAP_EDIT_DEPARTMENT,
	MNU_PHBAP_EDIT_POSITION,
	MNU_PHBAP_EDIT_ADDRESS,
	MNU_PHBAP_EDIT_EMAIL,
	MNU_PHBAP_EDIT_URL,
	MNU_PHBAP_EDIT_NOTE,
	MNU_PHBAP_NEW_CONTACT,
	MNU_PHBAP_GROUP_NONE,
	MNU_PHBAP_VIEW_GROUP,
	MNU_PHBAP_GROUPS_ADD,
	MNU_PHBAP_GROUPS_EDIT,
	MNU_PHBAP_GROUP_ADD_MEMBER,
	MNU_PHBAP_GROUP_REMOVE_MEMBER,
	MNU_PHBAP_ADD_BLACKLIST_OPTION,
	MNU_PHBAP_BLACKLIST_ADD_NEW,
	MNU_PHBAP_BLACKLIST_ADD_FROM_PHB,
	MNU_PHBAP_SEARCH_NUMBER,
	MNU_PHBAP_SEARCH_DIGIT_TO_ALPHABET,
	MNU_PHBAP_MEDIA_USE_DEFAULT,
	MNU_PHBAP_MEDIA_SELECT_NEW,
	MNU_PHBAP_NEW_PHONE,
	MNU_PHBAP_NEW_MASTER_SIM,
	MNU_PHBAP_NEW_SLAVE_SIM,
	MNU_PHBAP_NEW_CONTACT_OPTION,
	MNU_PHBAP_EXPORT_PHB,
	MNU_PHBAP_EXPORT_CSV,
    MNU_PHBAP_SEND_VCARD_BY_BT,
//#ifndef __MMI_PHB_DISABLE_BLACKLIST__	    
    MNU_PHBAP_BLACKLIST_DELETE
//#endif    
}PhbMenuId_e;

#endif //__MMI_PHBAPP_ID_H__

