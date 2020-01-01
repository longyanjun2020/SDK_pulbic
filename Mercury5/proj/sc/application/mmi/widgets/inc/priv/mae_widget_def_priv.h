
//#ifndef __MAE_TEXTWIDGET_DEF_PRIV_H__
//#define __MAE_TEXTWIDGET_DEF_PRIV_H__

#include "mmi_mae_common_def.h"
//#include "mae_widgetbase.h"
#include "mmi_common_thmid.h"
#include "mae_textlabel.h"

#include "mmi_setting_cfg.h"
#include "mmi_wdg_text.h"
#include "mmi_wdg_button.h"
#include "mmi_wdg_fcdate.h"
#include "mmi_wdg_handwriting.h"
#include "mmi_wdg_progress.h"
#include "mmi_wdg_commonpickitem.h"
#include "mae_decoratorbase.h"
#include "mmi_wdg_doubleitem.h"
#include "mmi_wdg_scrollbar.h"
#include "mmi_wdg_scroll_indicator.h"
#include "mmi_wdg_timerformat.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_wdg_propcontainer.h"
#include "mmi_wdg_volume.h"
#include "mmi_wdg_formatinput.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_wdg_input.h"
#include "mmi_mae_input_common.h"
#include "mmi_wdg_image.h"
#include "mmi_wdg_menu.h"
#include "mmi_wdg_tab.h"
#include "mmi_wdg_list.h"
#include "mmi_mae_font_base.h"
#include "mmi_wdg_fctime.h"
#include "mmi_wdg_statusbar.h"

typedef struct{
    u32 bLayoutInverse;
}AbscontainerWdgtDef_t;

typedef struct{
    u32 nLayout;
}ViewportWdgtDef_t;

typedef struct{
    _TxtColor_t tUnPrsdTxtColor;
    _TxtColor_t tPrsdTxtColor;
    FontCategory_t tFontCat;
    FontType_t tFontType;
    u32 nImgAlign;
}ButtonWdgtDef_t;

typedef struct{
    u32 nInterval;
    u32 nImgAlign;
    u32 bUseDefImage;
    u32 nDefImageID;
}ImageWdgtDef_t;

typedef struct{
    u32 nInterval;
    u32 nImgAlign;
    u32 bUseDefImage;
    u32 nDefImageID;
}OverlayImageWdgtDef_t;

typedef struct{
    TextFontInfo tFontInfo;
    TextSlideInfo tSlideInfo;
    u8 nTextAlign;
    u8 nTextLayout;
    u8 nAlignPriority;
    u8 nLangDir;
    RGBColor_t nColor;
}TextWdgDef_t;

typedef struct{
    u32 nFontHeight;
    SinglelineDisplayInfo tDispInfo;
    boolean bShowBorderWhenLoseFocus;
    TextThemeProperty tTextThemeProperty;
    boolean bDrawUnderLine;
    u32 nWdgAlignment;
    u32 nPaddingSize;
    u32 nBorderSize;
    u32 nBgPos;
    u32 nUnderlineColor;
}InputWdgDef_t;

typedef struct{
    u16 nTabRegionHeight;
    u16 nActiveWidth;
    u16 nInactiveWidth;
    u16 nTabOffset;
    u8 nMode;
    u32 nItemLayout;
    u32 nItemPaddingRight;
    u32 nImgAlignment;
    u32 nImgAPaddingLeft;
    u32 nTextLayoutFlag;
    u32 nTextAlignment;
    u32 nTextFoneCate;
    u32 nTextPaddingLeft;
    u32 nListPaddingLeft;
    u32 nListPaddingRight;
    u32 nListBgPos;

    u32 nTabBg;
    u32 nTabBgAct;
    u32 nTabBgInAct;
    u32 nTabHightlightText;
    u32 nTabText;
}TabWdgDef_t;

typedef struct{
    u32 nIconStyle;
    u32 nAlignment;
}SwitchIconWdgDef_t;

typedef struct{
    u32 nProgressType;
    ProgressCellInfo tCellInfo;
    ProgressCellInfo tPreferCellInfo;
    u32 nBaseWidgetWidth;
    RGBColor_t tFGColorBorderColor;
    RGBColor_t tFGColorFillColor;
    u32 tFGFlags;
    RGBColor_t tBGColorBorderColor;
    RGBColor_t tBGColorFillColor;
    u32 tBGFlags;
}ProgressWdgDef_t;

typedef struct{
    u32 nFO_lvl;
}FadeoutWdgDef_t;

typedef struct{
    u32 nLayoutStyle;
}IndicatorWdgDef_t;

typedef struct{
	WidgetSize_t tTextWdgSize;
}TextBubbleWdgDef_t;

typedef struct{
    u16 nMaxYear;
    u16 nMinYear;
    u32 nBgImageId;
    WidgetSize_t tFCDateSize;
    s32 nWdgX[FCD_IND_SUM];
    s32 nWdgY[FCD_IND_SUM];
    WidgetSize_t tWdgSize[FCD_IND_SUM];
    s32 nIndX[FCD_IND_SUM];
    s32 nIndY[FCD_IND_SUM];
    WidgetSize_t tIndSize[FCD_IND_SUM];
}FcDateWdgDef_t;

typedef struct{
    u8 nSegmentNum;
    MAE_WChar wDelimiter;
}DateWdgDef_t;

typedef struct{
    SetPhoneTimeFormat_e eTimeFormat;
    u32 nFCTime12HoursBG;
    u32 nFCTime24HoursBG;
    u32 nCountdownBG;
    WidgetSize_t tFCTimeSize;
    FCT_TimeDispInfo_t tFCTimeInfo[FCT_TIME_WDG_SUM];
    FCT_TimeDispInfo_t tFCCountTimerInfo[FCT_COUNT_TIMER_WDG_SUM];
    u32 n24FormatHourPosXShift;
    u32 n24FormatMinutePosXShift;
}FcTimeWdgDef_t;


typedef struct{
    u8 nTopBorder;
    u8 nBottomBorder;
    u8 nLeftBorder;
    u8 nRightBorder;
    u32 nBorderColor;
}MenuWdgBorderVar_t;

typedef struct{
    SoftkeyID_e nDefaultSK[NUM_SK];
    SoftkeyID_e nUnavilItemSK[NUM_SK];
    u32 nFocusItemBgImgID;
	u32 nUnFocusItemBgImgID;
    u32 nEmptyTextID;
    RGBColor_t nEmptyTextColor;
	RGBColor_t nItemTextColor;
	RGBColor_t nHighLightItemTextColor;
    ScrollStyle_t nScrollStyle;
    OptionMenuStyle_t nOptionMenuStyle;
    u8 nCheckStyle;
    WidgetSize_t tWdgSize;
    boolean bShowEmptyText;
    boolean bShowTotalNum;
    boolean bShowMarkedItemNum;
    GridItemNumInfo_t tGridItemNum;
    MenuWdgBorderVar_t tBorder;
}MenuWdgDef_t;

typedef struct{
    u32 nSclIndLArrowW;
    u32 nSclIndRArrowW;
    u32 nTextAlignment;
    WidgetSize_t tWSize;
}PickWdgDef_t;

typedef struct{
    u16 nItemHeight;
    u16 nLeftPadding;
    u16 nRightPadding;
}SoftkeyboardWdgDef_t;

typedef struct{
    u32 nFontType;
    u32 nFontCate;
    u32 nAlignment;
    u32 nPadding;
    u32 nBgPosition;
    boolean bBgEnable;
    WProp_t tProp;
}SoftkeyText_t;

typedef struct{
    u32 nAlignment;
    u32 nBgPosition;
    boolean bBgEnable;
    WProp_t tProp;
}SoftkeyImg_t;

typedef struct{
    u32 nStyle;
    u32 nRgbTextColor;
    u32 nRgbOutlineColor;
    SoftkeyText_t tLeft;
    SoftkeyImg_t tMiddle;
    SoftkeyText_t tRight;
    u32 nBgImgId;
    u32 nPressedLRBgId;
    u32 nPressedCSKBgId;
    u32 nLandPressedLRBgId;  //LANDSCAPE
}SoftkeyWdgDef_t;

typedef struct{
	 RGBColor_t	nBgClr;			// the background color
	 RGBColor_t	nFgClr;				// the foreground color
	 RGBColor_t	nLineClr;		// the line and border color
	 RGBColor_t	nFontClr;			// the font color
	 RGBColor_t	nFontOutlineClr;			// the font outline color
	 FontType_t	nFontType;		// the font type
	 FontCategory_t nFontCate;	// the font category
	 DisplayDottedType_e nLineType;	// the line type
	 u8 nBrushSize;						// the brush size
}CanvasWdgDef_t;

// *** common pick *****
typedef struct{
    WidgetSize_t tWSize;
    u32 nFoneCate;
    PickPaddingSize_st nPickPaddingSize;

    u32 nItemLayout;
    u32 nItemAlignment;
    u32 nItemSlideDir;
    PickPaddingSize_st nItemPaddingSize;
    u32 nItemTopLayout;
    u32 nItemTopAlignment;
    u32 nItemTopSlideDir;
    PickPaddingSize_st nItemTopPaddingSize;
}TxtPickTxtWdgDef_t;

typedef struct{
    WidgetSize_t tWSize;
    u32 nFoneCate;

    u32 nItemLayout;
    u32 nItemAlignment;
    u32 nItemSlideDir;
    PickPaddingSize_st nItemPaddingSize;
    u32 nItemTopLayout;
    u32 nItemTopAlignment;
    u32 nItemTopSlideDir;
    PickPaddingSize_st nItemTopPaddingSize;
    u32 nPickLayout;
    u32 nItemBgColor;
    u32 nItemBgPos;
    u32 nItemTxtColorThmID;
    u32 nItemHLTxtColorThmID;
    PickPaddingSize_st nPickPaddingSize;
}L2InfoPickTxtWdgDef_t;

typedef struct{
    WidgetSize_t tWSize;
    u32 nFoneCate;
    PickPaddingSize_st nPickPaddingSize;

    u32 nItemLayout;
    u32 nItemTopLayout;
    u32 nItemTopAlignment;
    u32 nItemTopSlideDir;
    PickPaddingSize_st nItemTopPaddingSize;
}TxtPickImgTxtWdgDef_t;

typedef struct{
    WidgetSize_t tWSize;
    u32 nFoneCate;

    u32 nItemLayout;
    u32 nImgPadding;
    u32 nItemTopLayout;
    PickPaddingSize_st nPickPaddingSize;
}ImgTxtPickImgTxtWdgDef_t;
// *** common pick *****

typedef struct{
    u32 nFontCate;
    u32 nFontType;
    boolean bShowAMPM;
    u16 nAvailableMaxYear;
    u16 nAvailableMinYear;
    WidgetSize_t tPreffredSize;
    u32 nBorderSize;
    u32 nAlign;
}FormatInputWdgDef_t;

typedef struct{
    u16 nItemWidth;
    u16 nItemHeight;
}GridBaseWdgDef_t;

typedef struct{
    u32 nStrokeDuration;
    u32 nFunction;
}HandwriteWdgDef_t;

typedef struct{
    u32 nCurrInputMode;
}ImeAssistWdgDef_t;

typedef struct{
    u8 nGridFixedDir;
    u8 nGridFixedNum;
    u16 nGridItemWidth;
    u16 nOneLineItemHeight;
    u16 nTwoLineItemHeight;
    u16 nExpandItemHeight;
    u16 nExpandSelItemSize;
}ListWdgDef_t;

typedef struct{
    ScrollBarRectInfo tBarInfo;
    ScrollBarRectInfo tIndInfo;
    u8 nScrollStyle;
    WidgetSize_t tHBarSizeMinElement;
    WidgetSize_t tVBarSizeMinElement;
    WidgetSize_t tHIndSizeMinElement;
    WidgetSize_t tVIndSizeMinElement;
}ScrollbarWdgDef_t;

typedef struct{
    u32 nLayoutMode;
    WidgetSize_t tArrowRect[ARROW_NUM];
}ScrollIndicatorWdgDef_t;

typedef struct{
    boolean bElementVisable;
    u32 nElmntAlignment;
    u32 nSmsAlignment;
    u32 nSmsFoneCate;
    u32 nTitleTextFoneCate;
    u32 nTitleTextFoneType;
    u8 nChildLangDir;
    u32 nBgImage;
    RGBColor_t nBgColor;
    RGBColor_t nOutlineColor;
    RGBColor_t nTextColor;
    RGBColor_t nSmsColor;
    u16 nTitleElmntWidth[TITLEWDG_ELMNT_ID_TOTAL];
    WidgetSize_t   tTitleSize;
    u16 nElemtPadding;
    u16 nLeftPadding;
    u16 nRightPadding;
}TitleWdgDef_t;


typedef struct{
    u32 nOffsetY;
    u16 nItemHeight;
    u16 nSelItemSize;
    boolean bCanBeFocused;
    boolean bTouchFocus;
}MflcontainerWdgDef_t;

typedef struct{
    WidgetSize_t tOpMenuL1Size;
    WidgetSize_t tFaoutSize;
    WidgetSize_t tOpMenuL2Size;
    s32 sL1PosX;
    s32 sL2PosX;
    s32 sMenuOffsetY;
    WidgetSize_t tWidgetSize;
    WidgetSize_t tHorSize;
    WidgetSize_t tL1Size;
    WidgetSize_t tL2Size;
    u32 nL2HorX;
    u8 nTopBorder;
    u8 nBottomBorder;
    u8 nLeftBorder;
    u8 nRightBorder;
    u32 nL1MAxItem;
    u32 nL2MAxItem;
    u32 nLineHeight;
}OpMenuWdgDef_t;


typedef struct{
    s32 sPosX;
    u32 nMenuOffsetY;
    WidgetSize_t tWdgSize;
    u32 nHorHeight;
    u8 nMaxItem;
    u8 nTwoLineItem;
    u8 nTopBorder;
    u8 nBottomBorder;
    u8 nLeftBorder;
    u8 nRigthBorder;
    u32 nWidgetWidth;
}PopUpSelectWdgDef_t;

typedef struct{
    WidgetSize_t tSrtCutSize;
    u32 nSrtCutLayout;
    u32 nVPortLayout;
    WidgetSize_t tVPortSize;
    WPos_t tVPortPos;
    u32 nSrtCutTPadding;
    u32 nSrtCutLPadding;
    u32 nSrtCutAlignment;
    u16 nBotGap;
    u16 nTopGap;
}ShortcutBarWdgDef_t;

typedef struct{
    WidgetSize_t tSliderBGSize;
    u32 nDefBgChineseImgId;
    u32 nDefBgOtherLangImgId;
    u32 nDefSwithcImgId;
    WidgetSize_t tSwitchSize;
    WidgetSize_t tContainerSize;
    WPos_t tSliderBGPos;
    WPos_t tSwitchPos;
    u32 nCurrentSwitchPosX;
    u32 nMaxSwitchPosX;
    u32 nMinSwitchPosX;
}SlideSwitchWdgDef_t;

typedef struct{
    WdgLayoutStyle_t tStyle;
}PropcontainerWdgDef_t;

typedef struct{
    TimerTextFont_t tFontInfo;
    TimerFormatInfo_t tFormatInfo;
    u8 nAlignFlag;
}TimerFormatWdgDef_t;


typedef struct{
    u16 nUsrDefInterval;
    u16 nBlockSize;
}TransitionWdgDef_t;

typedef struct{
    WidgetSize_t tVolumeSize;
    WPos_t tVolumePos;
    WidgetSize_t tVolEmptyLevelSize;
    WPos_t tVolEmptyLevelPos;
    WidgetSize_t tVolFullLevelSize;
    WPos_t tVolFullLevelPos;
    WidgetSize_t tVolIncrBtnSize;
    WPos_t tVolIncrBtnPos;
    WidgetSize_t tVolDecrBtnSize;
    WPos_t tVolDecrBtnPos;
    WidgetSize_t tVolMuteSize;
    WPos_t tVolMutePos;
    VolumeWdgInfo_t tVolumeInfo;
    u32 nTimeout;
    u16 nItemHeight;
    u16 nSpaceHeight;
    u8 nDefaultScale;
}VolumeWdgDef_t;

typedef struct {
    u32 nTimeout;
}VolumeWdgDefLayout_t;


// *** double *****
typedef struct{
    WidgetSize_t tImageSize;
    WProp_t nPreImgProportion;
    WProp_t nTextProportion;
    u16 nBidiTextPrePadding;
    u16 nBidiTextPostPadding;
    u16 nTextPrePadding;
    u16 nTextPostPadding;

    u16 nBidiPreImgPrePadding;
    u16 nBidiPreImgPostPadding;
    u16 nPreImgPrePadding;
    u16 nPreImgPostPadding;

    u16 nBidiPostImgPrePadding;
    u16 nBidiPostImgPostPadding;
    u16 nPostImgPrePadding;
    u16 nPostImgPostPadding;
}ImageTextWdgDef_t;

typedef struct{
    WidgetSize_t tPreImageSize;
    WProp_t nPreImgProportion;
    WProp_t nTextProportion;
    WidgetSize_t tPostImageSize;
    WProp_t nPostImgProportion;
    u16 nTextPrePadding;
    u16 nTextPostPadding;

    u16 nBidiPreImgPrePadding;
    u16 nBidiPreImgPostPadding;
    u16 nPreImgPrePadding;
    u16 nPreImgPostPadding;

    u16 nBidiPostImgPrePadding;
    u16 nBidiPostImgPostPadding;
    u16 nPostImgPrePadding;
    u16 nPostImgPostPadding;
}ImageTextImageWdgDef_t;

typedef struct{
    WProp_t nTextProportion;
    WidgetSize_t tPostImageSize;
    WProp_t nPostImgProportion;
    u16 nBidiTextPrePadding;
    u16 nBidiTextPostPadding;
    u16 nTextPrePadding;
    u16 nTextPostPadding;

    u16 nBidiPreImgPrePadding;
    u16 nBidiPreImgPostPadding;
    u16 nPreImgPrePadding;
    u16 nPreImgPostPadding;

    u16 nBidiPostImgPrePadding;
    u16 nBidiPostImgPostPadding;
    u16 nPostImgPrePadding;
    u16 nPostImgPostPadding;
}TextImageWdgDef_t;


typedef struct{
    DoubleItemPaddingSize_t tUpPadSize;
    DoubleItemPaddingSize_t tDownPadSize;
    WidgetSize_t tUpperSize;
    WidgetSize_t tDownSize;
    u32 nBGPosition;
    s32 nUpStartPosX;
    s32 nUpStartPosY;
    s32 nDownStartPosX;
    s32 nDownStartPosY;
    FontCategory_t tUpFontCat;
    FontCategory_t tDownFontCat;
}DoubleItemWdgComm_t;
//CLSID_DOUBLE_TEXT_WIDGET, CLSID_IT_STEXT_WIDGET,CLSID_IT_SIT_WIDGET,CLSID_IT_STI_WIDGET

typedef struct{
    DoubleItemWdgComm_t tCommon;
    s32 nSpaceWidth;
}DoubleItemWdgPlusSpace_t;
//CLSID_TEXT_DATE_WIDGET,CLSID_TEXT_TIME_WIDGET,CLSID_TEXT_INPUT_WIDGET,CLSID_TEXT_IP_WIDGET,CLSID_IT_SINPUT_WIDGET

typedef struct{
    s32 nSpaceWidth;
    u32 nRightSpace;
    u32 nFocusBgColor;
    u32 nUnFocusBgColor;
}L2InfoWdgVar_t;

typedef struct{
    DoubleItemWdgComm_t tCommon;
    u16 nDownHigh;
    u32 nBgColor;
    RGBColor_t tTextColor;
    RGBColor_t tHighlightTextColor;
    s32 nDownStartPosY;
    L2InfoWdgVar_t tL2Info;
}DoubleItemWdgL2I_t;
//CLSID_TEXT_LINE2INFO_WIDGET

// ***** status bar *******
typedef struct {
    u32 nWdgId;
    u8 nPriority;
    u8 nIconPosSide;
    WPos_t tWPos;
    WidgetSize_t tWdgSize;
    u32 nAlignment;
}SBImgType_t;

typedef struct {
    u32 nWdgId;
    u8 nPriority;
    u8 nIconPosSide;      
    WPos_t tWPos;
    WidgetSize_t tWdgSize;
    u32 nAlignment;
    u32 nTxtColor;
    u32 nFontType;
    u32 nFontCate;
}SBTextType_t;

typedef union
{
    SBTextType_t tTxtLayout;
    SBImgType_t  tImgLayout;
}SBItem_t;

typedef struct {
    u32 tType; //MAEClsId_t
    SBItem_t tSBItem;
}StatusBarWdgDef_t;


// ***** status bar *******


typedef struct {
    u8 nIconStyle;
    boolean bShowSIconWdg;
    WidgetSize_t tWidgetSize;
    WidgetSize_t tIconCheck;
    WidgetSize_t tIconMark;
    WidgetSize_t tIconCamera;
    WidgetSize_t tIconGrid;
    u32 nLeftPadding;
    u32 nItemPadding;
    u32 nRightPadding;
    u32 nInnerItemPaddingH;
    u32 nInnerItemPaddingV;
}SwitchIconItemWdgDef_t;

typedef struct {
    u16 nChar;
    u8 nUnPressedImgId;  //If Id = 0, means no image.
    u8 nPressedImgId;    //If Id = 0, means no image.
    u8 SKBCodeType_e; //MAE_SKB_CODE_TYPE_e
} SoftKeyBoardWidget_VectorModelData_t;

