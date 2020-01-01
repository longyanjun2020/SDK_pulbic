#ifndef __MMI_WDG_ITF_MENU_ITEM_H__
#define __MMI_WDG_ITF_MENU_ITEM_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_common_thmid.h"
#include "mmi_mae_shell.h"
#include "mmi_wdg_common_interface.h"
#include "mmi_wdg_image_text_image.h"
#include "mmi_wdg_popupselect.h"
#include "mmi_wdg_doubleitem.h"
#include "mmi_wdg_image_doubleitem.h"
#include "mmi_wdg_commonpickitem.h"
#include "mmi_wdg_button.h"
#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
#include "mmi_wdg_indicator.h"
#include "mmi_wdg_image_doubleitem_multifield.h"
#endif

#define WDG_MENU_ITEM_FLAG_HIDE         MENUMODEL_ITEM_HIDE
#define WDG_MENU_ITEM_FLAG_VISABLE      MENUMODEL_ITEM_VISABLE
#define WDG_MENU_ITEM_FLAG_UNSELECTABLE MENUMODEL_ITEM_UNSELECTABLE
#define WDG_MENU_ITEM_FLAG_SELECTED     MENUMODEL_ITEM_SELECTED
#define WDG_MENU_ITEM_FLAG_HAS_CHILD    MENUMODEL_ITEM_HAS_CHILD
#define WDG_MENU_ITEM_FLAG_ALL          MENUMODEL_ITEM_ALL

#define WDG_MENU_MONTH_GRID_ITEM_MAX_STRING_LENGTH (3)

typedef enum
{
    /* one line */
    WDG_MENU_ITEM_TYPE_NONE = 0,
    WDG_MENU_ITEM_TYPE_TEXT = CLSID_TEXTWIDGET,
    WDG_MENU_ITEM_TYPE_IMAGE = CLSID_IMAGEWIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_IMAGE = CLSID_TEXTIMAGEWIDGET,
    WDG_MENU_ITEM_TYPE_IMAGE_TEXT = CLSID_IMAGETEXTWIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXT_IMAGE = CLSID_IMAGETEXTIMAGEWIDGET,

    /* two lines */
    WDG_MENU_ITEM_TYPE_TEXT_DATE = CLSID_TEXT_DATE_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_TIME = CLSID_TEXT_TIME_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_INPUT = CLSID_TEXT_INPUT_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_IP = CLSID_TEXT_IP_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXT_SPACEINPUT = CLSID_IT_SINPUT_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_TEXT = CLSID_DOUBLE_TEXT_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT = CLSID_TEXT_LINE2INFO_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXT_SPACETEXT = CLSID_IT_STEXT_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXT_SPACEIMAGETEXT = CLSID_IT_SIT_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXT_SPACETEXTIMAGE = CLSID_IT_STI_WIDGET,

    /* image + two lines */
    WDG_MENU_ITEM_TYPE_IMAGE_TEXT_TEXT = CLSID_IMAGE_DOUBLE_TEXT_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGE_TEXTIMAGE_TEXTIMAGE = CLSID_IMAGE_TITI_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGE_TEXTIMAGE_TEXT = CLSID_IMAGE_TITEXT_WIDGET,
#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
    WDG_MENU_ITEM_TYPE_IMAGE_TEXT_ITIT = CLSID_IMAGE_TEXT_ITIT_WIDGET,
    WDG_MENU_ITEM_TYPE_IMAGE_TEXT_CITT = CLSID_IMAGE_TEXT_CITT_WIDGET,
#endif
    /* pick text + two lines */
    WDG_MENU_ITEM_TYPE_TEXTPICK_TEXT = CLSID_TEXTPICK_TEXTWIDGET,
	WDG_MENU_ITEM_TYPE_THEMETEXTPICK_TEXT = CLSID_LINE2INFOPICK_TEXTWIDGET,
    WDG_MENU_ITEM_TYPE_TEXTPICK_IMAGETEXT = CLSID_TEXTPICK_IMAGETEXTWIDGET,
    WDG_MENU_ITEM_TYPE_IMAGETEXTPICK_IMAGETEXT = CLSID_IMAGETEXTPICK_IMAGETEXTWIDGET,

    /* button */
    WDG_MENU_ITEM_TYPE_BUTTON = CLSID_BUTTONWIDGET,

    /* user define */
    WDG_MENU_ITEM_TYPE_USER_DEF_BEGIN = CLSID_END_OF_WIDGET,
    WDG_MENU_ITEM_TYPE_TEXTTIME,
    WDG_MENU_ITEM_TYPE_PROPCONTAINER_TEXT_TEXT,
	WDG_MENU_ITEM_TYPE_PROPCONTAINER_TEXT,
    WDG_MENU_ITEM_IMAGETEXTIMAGE_SPACETEXTIMAGE,
    WDG_MENU_ITEM_TYPE_USER_DEF_END
} WdgMenuItemType_e;
typedef u32 WdgMenuItemType_t;

typedef enum
{
    WDG_MENU_ITEM_LINE_1_FIRST,
    WDG_MENU_ITEM_LINE_1_SECOND,
    WDG_MENU_ITEM_LINE_1_THIRD,
    WDG_MENU_ITEM_LINE_2_FIRST,
    WDG_MENU_ITEM_LINE_2_SECOND,
    WDG_MENU_ITEM_LINE_2_THIRD
} WdgMenuItemComponetId_e;

typedef struct
{
	MAE_WChar aDayStr[WDG_MENU_MONTH_GRID_ITEM_MAX_STRING_LENGTH];
    boolean bDayInCurrentMonth;
    boolean bIsToday;
    boolean bDrawIndicator;

} WdgMenuMonthGridItem_t;

typedef struct
{
    u32 u32Year;      ///< Year value after 1900, value range is 0~255
    u32 u32Month;     ///< Month, value range is 1~12
    u32 u32Day;       ///< Day, value range is 1~31
    u32 u32DayOfWeek; ///< [1 = Monday, 7 = Sunday]
} WdgMenuItemDate_t;

typedef struct
{
    u32 u32Hour;      ///< Hour, value range is 0~23
    u32 u32Minute;    ///< Minute, value range is 0~59
    u32 u32Second;    ///< Second, value range is 0~59
} WdgMenuItemTime_t;

typedef struct
{
    MAE_WChar   u16DisplayChar;
    u16         u16Idx;
    u16         u16Visible;
    u16         u16Alphabet;
} WdgMenuItemAlphabet_t;

typedef struct
{
    u32 u32TextId;
} WdgMenuItemText_t;

typedef struct
{
    u16 *pu16Text;
} WdgMenuItemTextPtr_t;

typedef struct
{
    u32 u32ImageId;
} WdgMenuItemImage_t;

typedef struct
{
    IImage *pImage;
} WdgMenuItemImagePtr_t;

typedef struct
{
    u32 u32TextId;
    u32 u32ImageId;
} WdgMenuItemTextImage_t;

typedef struct
{
    u16 *pu16Text;
    IImage *pImage;
} WdgMenuItemTextImagePtr_t;

typedef struct
{
    u32 u32ImageId;
    u32 u32TextId;
} WdgMenuItemImageText_t;

typedef struct
{
    IImage *pImage;
    u16 *pu16Text;
} WdgMenuItemImageTextPtr_t;

typedef struct
{
    u32 u32Image1Id;
    u32 u32TextId;
    u32 u32Image2Id;
} WdgMenuItemImageTextImage_t;

typedef struct
{
    IImage *pImage1;
    u16 *pu16Text;
    IImage *pImage2;
} WdgMenuItemImageTextImagePtr_t;

typedef struct
{
    u32 u32TextId;
    WdgMenuItemDate_t sDate;
} WdgMenuItemTextDate_t;

typedef struct
{
    u16 *pu16Text;
    WdgMenuItemDate_t sDate;
} WdgMenuItemTextDatePtr_t;

typedef struct
{
    u32 u32TextId;
    WdgMenuItemTime_t sTime;
} WdgMenuItemTextTime_t;

typedef struct
{
    u16 *pu16Text;
    WdgMenuItemTime_t sTime;
} WdgMenuItemTextTimePtr_t;

typedef struct
{
    u32 u32TextId;
    u32 u32Ip;
} WdgMenuItemTextIp_t;

typedef struct
{
    u16 *pu16Text;
    u32 u32Ip;
} WdgMenuItemTextIpPtr_t;

typedef struct
{
    u32 u32Text1Id;
    u32 u32Text2Id;
} WdgMenuItemTextText_t;

typedef struct
{
    u16 *pu16Text1;
    u16 *pu16Text2;
} WdgMenuItemTextTextPtr_t;

typedef struct
{
    WdgMenuItemImageText_t sImageText;
    u32 u32TextId;
} WdgMenuItemL1ImageTextL2Text_t;

typedef struct
{
    WdgMenuItemImageTextPtr_t sImageText;
    u16 *pu16Text;
} WdgMenuItemL1ImageTextL2TextPtr_t;

typedef struct
{
    WdgMenuItemImageText_t sImageText1;
    WdgMenuItemImageText_t sImageText2;
} WdgMenuItemL1ImageTextL2ImageText_t;

typedef struct
{
    WdgMenuItemImageTextPtr_t sImageText1;
    WdgMenuItemImageTextPtr_t sImageText2;
} WdgMenuItemL1ImageTextL2ImageTextPtr_t;


typedef struct
{
    WdgMenuItemImageText_t sImageText;
    WdgMenuItemTextImage_t sTextImage;
} WdgMenuItemL1ImageTextL2TextImage_t;

typedef struct
{
    WdgMenuItemImageTextPtr_t sImageText;
    WdgMenuItemTextImagePtr_t sTextImage;
} WdgMenuItemL1ImageTextL2TextImagePtr_t;


typedef struct
{
    u32 u32ImageId;
    u32 u32Text1Id;
    u32 u32Text2Id;
} WdgMenuItemImageL1TextL2Text_t;

typedef struct
{
    IImage *pImage;
    u16 *pu16Text1;
    u16 *pu16Text2;
} WdgMenuItemImageL1TextL2TextPtr_t;

typedef struct
{
    u32 u32ImageId;
    WdgMenuItemTextImage_t sTextImage1;
    WdgMenuItemTextImage_t sTextImage2;
} WdgMenuItemImageL1TextImageL2TextImage_t;

typedef struct
{
    IImage *pImage;
    WdgMenuItemTextImagePtr_t sTextImage1;
    WdgMenuItemTextImagePtr_t sTextImage2;
} WdgMenuItemImageL1TextImageL2TextImagePtr_t;

typedef struct
{
    u32 u32ImageId;
    WdgMenuItemTextImage_t sTextImage;
    u32 u32TextId;
} WdgMenuItemImageL1TextImageL2Text_t;

typedef struct
{
    IImage *pImage;
    WdgMenuItemTextImagePtr_t sTextImage;
    u16 *pu16Text;
} WdgMenuItemImageL1TextImageL2TextPtr_t;

typedef struct
{
    u32 u32TextId;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    u32 *pu32TextIdArray;
} WdgMenuItemTextL2PickText_t;

typedef struct
{
    u16 *pu16Text;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    u32 *pu32TextArray;
} WdgMenuItemTextL2PickTextPtr_t;

typedef struct
{
    u32 u32TextId;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    WdgMenuItemImageText_t *psImageTextArray;
} WdgMenuItemTextL2PickImageText_t;

typedef struct
{
    u16 *pu16Text;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    WdgMenuItemImageTextPtr_t *psImageTextArray;
} WdgMenuItemTextL2PickImageTextPtr_t;

typedef struct
{
    WdgMenuItemImageText_t sImageText;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    WdgMenuItemImageText_t *psImageTextArray;
} WdgMenuItemImageTextL2PickImageText_t;

typedef struct
{
    WdgMenuItemImageTextPtr_t sImageText;
    u32 u32ForcusIndex;
    u32 u32ArraySize;
    WdgMenuItemImageTextPtr_t *psImageTextArray;
} WdgMenuItemImageTextL2PickImageTextPtr_t;

typedef struct
{
    u32 u32TextId;
    u32 u32UnPressImageId;
    u32 u32PressImageId;
} WdgMenuItemButton_t;

typedef struct
{
    u16 *pu16Text;
    IImage *pUnPressImage;
    IImage *pPressImage;
} WdgMenuItemButtonPtr_t;

typedef struct
{
    u32 au32ItemData[6];
} WdgMenuItemUser_t;

typedef struct
{
    void *apItemData[6];
} WdgMenuItemUserPtr_t;

#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
typedef struct
{
    u32 u32PreWdgImgId;
    u32 u32BackUpWdgTextId;
    u32 u32BackDownFirstWdgImgId;
    u32 u32BackDownFirstWdgTextId;
    u32 u32BackDownSecWdgImgId;
    u32 u32BackDownSecWdgTextId;
} WdgMenuImgTextImgTextImgText_t;
typedef struct
{
    IImage 	    *pPreWdgImg;
    MAE_WChar 	*pBackUpWdgText;
    IImage 	    *pBackDownFirstWdgImg;
    MAE_WChar   *pBackDownFirstWdgText;
	IImage 	    *pBackDownSecWdgImg;
    MAE_WChar   *pBackDownSecWdgText;
} WdgMenuImgTextImgTextImgTextPtr_t;
typedef struct
{
    u32 u32PreWdgImgId;
    u32 u32BackUpWdgTextId;
    IndicatorData_t tBackDownFirstWdgIndData;
    u32 u32BackDownSecWdgImgId;
    u32 u32BackDownThirdWdgTextId;
    u32 u32BackDownForthWdgTextId;
}WdgMenuImgTextCITT_t;
typedef struct
{
    IImage 	    *pPreWdgImg;
    MAE_WChar 	*pBackUpWdgText;
	IndicatorData_t tBackDownFirstWdgIndData;
    IImage 	    *pBackDownSecWdgImg;
    MAE_WChar   *pBackDownThirdWdgText;
    MAE_WChar   *pBackDownForthWdgText;
} WdgMenuImgTextCITTPtr_t;
#endif
typedef union
{
    WdgMenuItemUser_t                        sUserDef;
    WdgMenuItemText_t                      sText;
    WdgMenuItemText_t                      sThemeText;
    WdgMenuItemImage_t                     sImage;
    WdgMenuItemTextImage_t                 sTextImage;
    WdgMenuItemImageText_t                 sImageText;
    WdgMenuItemImageTextImage_t            sImageTextImage;
    WdgMenuItemTextDate_t                 sTextDate;
    WdgMenuItemTextTime_t                 sTextTime;
    WdgMenuItemTextText_t                 sTextInput;
    WdgMenuItemTextIp_t                   sTextIp;
    WdgMenuItemL1ImageTextL2Text_t            sImageTextSpaceInput;
    WdgMenuItemTextText_t                 sTextText;
    WdgMenuItemTextText_t                 sTextThemeText;
    WdgMenuItemL1ImageTextL2Text_t            sImageTextSpaceText;
    WdgMenuItemL1ImageTextL2ImageText_t       sImageTextSpaceImageText;
    WdgMenuItemL1ImageTextL2TextImage_t       sImageTextSpaceTextImage;
    WdgMenuItemImageL1TextL2Text_t           sImageL1TextL2Text;
    WdgMenuItemImageL1TextImageL2TextImage_t sImageL1TextImageL2TextImage;
    WdgMenuItemImageL1TextImageL2Text_t      sImageL1TextImageL2Text;
    WdgMenuItemTextL2PickText_t             sTextL2PickText;
    WdgMenuItemTextL2PickText_t             sThemeTextL2PickText;
    WdgMenuItemTextL2PickImageText_t        sTextL2PickImageText;
    WdgMenuItemImageTextL2PickImageText_t   sImageTextL2PickImageText;
    WdgMenuItemButton_t                      sButton;
#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
    WdgMenuImgTextImgTextImgText_t  sImgTextImgTextImgText;
    WdgMenuImgTextCITT_t sImgTextIndImgTextText;
#endif
} WdgMenuItem_t;

typedef union
{

    WdgMenuItemUserPtr_t                        sUserDef;
    WdgMenuItemTextPtr_t                      sText;
    WdgMenuItemTextPtr_t                      sThemeText;
    WdgMenuItemImagePtr_t                     sImage;
    WdgMenuItemTextImagePtr_t                 sTextImage;
    WdgMenuItemImageTextPtr_t                 sImageText;
    WdgMenuItemImageTextImagePtr_t            sImageTextImage;
    WdgMenuItemTextDatePtr_t                 sTextDate;
    WdgMenuItemTextTimePtr_t                 sTextTime;
    WdgMenuItemTextTextPtr_t                 sTextInput;
    WdgMenuItemTextIpPtr_t                   sTextIp;
    WdgMenuItemL1ImageTextL2TextPtr_t            sImageTextSpaceInput;
    WdgMenuItemTextTextPtr_t                 sTextText;
    WdgMenuItemTextTextPtr_t                 sTextThemeText;
    WdgMenuItemL1ImageTextL2TextPtr_t            sImageTextSpaceText;
    WdgMenuItemL1ImageTextL2ImageTextPtr_t       sImageTextSpaceImageText;
    WdgMenuItemL1ImageTextL2TextImagePtr_t       sImageTextSpaceTextImage;
    WdgMenuItemImageL1TextL2TextPtr_t           sImageL1TextL2Text;
    WdgMenuItemImageL1TextImageL2TextImagePtr_t sImageL1TextImageL2TextImage;
    WdgMenuItemImageL1TextImageL2TextPtr_t      sImageL1TextImageL2Text;
    WdgMenuItemTextL2PickTextPtr_t             sTextL2PickText;
    WdgMenuItemTextL2PickTextPtr_t             sThemeTextL2PickText;
    WdgMenuItemTextL2PickImageTextPtr_t        sTextL2PickImageText;
    WdgMenuItemImageTextL2PickImageTextPtr_t   sImageTextL2PickImageText;
    WdgMenuItemButtonPtr_t                      sButton;
#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
    WdgMenuImgTextImgTextImgTextPtr_t  sImgTextImgTextImgText;
    WdgMenuImgTextCITTPtr_t sImgTextIndImgTextText;
#endif
} WdgMenuItemPtr_t;

__SLDPM_FREE__ void* WdgMenuItemMallocInternal(WdgMenuItemPtr_t *pItemData, WdgMenuItemType_e eItemType);
__SLDPM_FREE__ void WdgMenuItemTransferAndFree(void *pInternalItemData, WdgMenuItemPtr_t *pItemData, WdgMenuItemType_e eItemType, boolean bFree);
void WdgMenuItemTransferToInternal(WdgMenuItemPtr_t *pItemData, void *pInternalItemData, WdgMenuItemType_e eItemType);
void WdgMenuItemFree(void *pItemData, WdgMenuItemType_e eItemType, IBase *pOwner, boolean bFreeStr);
__SLDPM_FREE__ void WdgMenuItemLoadRes(WdgMenuItemType_e eItemType, WdgMenuItem_t *pInputItemData, WdgMenuItemPtr_t *pOutupItemData, IBase *pOwner);
IWidget* WdgMenuItemGetComponetWidget(IWidget *pIItemWidget, WdgMenuItemType_e eItemType, WdgMenuItemComponetId_e eComponet);
__SLDPM_FREE__ MAE_Ret WdgMenuItemSetType(IWidget *pMenu, WdgMenuItemType_e eItemType);

#endif /*__MMI_WDG_ITF_MENU_ITEM_H__*/

