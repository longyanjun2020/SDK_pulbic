#include "mmi_macro_prop_id.h"


#undef PropValueDefine
#define PropValueDefine(PropID)

/* VTM for AP */
#define	VtmCreateDateInputRC(...)	PropValueDefine(VtmCreateDateInputID)	__VA_ARGS__,
#define	VtmCreateImgRC(...)	PropValueDefine(VtmCreateImgID)	__VA_ARGS__,
#define	VtmCreateInputRC(...)	PropValueDefine(VtmCreateInputID)	__VA_ARGS__,
#define	VtmCreatePromptInputRC(...)	PropValueDefine(VtmCreatePromptInputID)	__VA_ARGS__,
#define	VtmCreateTimeInputRC(...)	PropValueDefine(VtmCreateTimeInputID)	__VA_ARGS__,
#define	VtmCreateImgGridMenuRC(...)	PropValueDefine(VtmCreateImgGridMenuID)	__VA_ARGS__,
#define	VtmCreateImgThumbRC(...)	PropValueDefine(VtmCreateImgThumbID)	__VA_ARGS__,
#define	VtmCreateMenuRC(...)	PropValueDefine(VtmCreateMenuID)	__VA_ARGS__,
#define	VtmCreateSimSelectionRC(...)	PropValueDefine(VtmCreateSimSelectionID)	__VA_ARGS__,
#define	VtmCreateTabMenuRC(...)	PropValueDefine(VtmCreateTabMenuID)	__VA_ARGS__,
#define	VtmCreateTxtGridMenuRC(...)	PropValueDefine(VtmCreateTxtGridMenuID)	__VA_ARGS__,
#define	VtmCreateIpInputRC(...)	PropValueDefine(VtmCreateIpInputID)	__VA_ARGS__,
#define	VtmCreateOptionMenuRC(...)	PropValueDefine(VtmCreateOptionMenuID)	__VA_ARGS__,
#define	VtmCreatePopUpInfoRC(...)	PropValueDefine(VtmCreatePopUpInfoID)	__VA_ARGS__,
#define	VtmCreatePopUpInputRC(...)	PropValueDefine(VtmCreatePopUpInputID)	__VA_ARGS__,
#define	VtmCreatePopUpPromptRC(...)	PropValueDefine(VtmCreatePopUpPromptID)	__VA_ARGS__,
#define	VtmCreatePopUpSelectRC(...)	PropValueDefine(VtmCreatePopUpSelectID)	__VA_ARGS__,

#define	VtmCreateImgGridMenuDataRC(aryNum, ...)	PropValueDefine(VtmCreateImgGridMenuID)	__VA_ARGS__,
#define	VtmCreateImgThumbDataRC(aryNum, ...)	PropValueDefine(VtmCreateImgThumbID)	__VA_ARGS__,
#define	VtmCreateMenuDataRC(aryNum, ...)	PropValueDefine(VtmCreateMenuID)	__VA_ARGS__,
#define	VtmCreateTabMenuDataRC(aryNum, ...)	PropValueDefine(VtmCreateTabMenuID)	__VA_ARGS__,
#define	VtmCreateTxtGridMenuDataRC(aryNum, ...)	PropValueDefine(VtmCreateTxtGridMenuID)	__VA_ARGS__,
#define	VtmCreateOptionMenuDataRC(aryNum, ...)	PropValueDefine(VtmCreateOptionMenuID)	__VA_ARGS__,
#define	VtmCreatePopUpInfoDataRC(aryNum, ...)	PropValueDefine(VtmCreatePopUpInfoID)	__VA_ARGS__,
#define	VtmCreatePopUpSelectDataRC(aryNum, ...)	PropValueDefine(VtmCreatePopUpSelectID)	__VA_ARGS__,


/* Common Create  */
#define	WdgAbsContainerCreateForWndRC(...)	PropValueDefine(WdgAbsContainerCommonCreateID)	__VA_ARGS__,
#define	WdgViewportCreateForWndRC(...)	PropValueDefine(WdgViewportCommonCreateID)	__VA_ARGS__,
#define	WdgButtonCreateForWndRC(...)	PropValueDefine(WdgButtonCommonCreateID)	__VA_ARGS__,
#define	WdgImageCreateForWndRC(...)	PropValueDefine(WdgImageCommonCreateID)	__VA_ARGS__,
#define	WdgTextCreateForWndRC(...)	PropValueDefine(WdgTextCommonCreateID)	__VA_ARGS__,
#define	WdgInputCreateForWndRC(...)	PropValueDefine(WdgInputCommonCreateID)	__VA_ARGS__,
#define	WdgOsdCreateForWndRC(...)	PropValueDefine(WdgOsdCommonCreateID)	__VA_ARGS__,
#define	WdgTabCreateForWndRC(...)	PropValueDefine(WdgTabCommonCreateID)	__VA_ARGS__,
#define	WdgSwitchIconCreateForWndRC(...)	PropValueDefine(WdgSwitchIconCommonCreateID)	__VA_ARGS__,
#define	WdgProgressCreateForWndRC(...)	PropValueDefine(WdgProgressCommonCreateID)	__VA_ARGS__,
#define	WdgIPCreateForWndRC(...)	PropValueDefine(WdgIPCommonCreateID)	__VA_ARGS__,
#define	WdgFadeoutCreateForWndRC(...)	PropValueDefine(WdgFadeoutCommonCreateID)	__VA_ARGS__,
#define	WdgPullDownCreateForWndRC(...)	PropValueDefine(WdgPullDownCommonCreateID)	__VA_ARGS__,
#define	WdgIndicatorCreateForWndRC(...)	PropValueDefine(WdgIndicatorCommonCreateID)	__VA_ARGS__,
#define	WdgTimeCreateForWndRC(...)	PropValueDefine(WdgTimeCommonCreateID)	__VA_ARGS__,
#define	WdgFcDateCreateForWndRC(...)	PropValueDefine(WdgFcDateCommonCreateID)	__VA_ARGS__,
#define	WdgDateCreateForWndRC(...)	PropValueDefine(WdgDateCommonCreateID)	__VA_ARGS__,
#define	WdgFcTimeCreateForWndRC(...)	PropValueDefine(WdgFcTimeCommonCreateID)	__VA_ARGS__,
#define	WdgMenuCreateForWndRC(...)	PropValueDefine(WdgMenuCommonCreateID)	__VA_ARGS__,
#define	WdgPickCreateForWndRC(...)	PropValueDefine(WdgPickCommonCreateID)	__VA_ARGS__,
#define	WdgCommonPickCreateForWndRC(...)	PropValueDefine(WdgCommonPickCommonCreateID)	__VA_ARGS__,
#define	WdgDoubleItemCreateForWndRC(...)	PropValueDefine(WdgDoubleItemCommonCreateID)	__VA_ARGS__,


/* SetDataByID */
#define	WdgButtonSetDataByIDRC(...)	PropValueDefine(WdgButtonSetDataByIDID)	__VA_ARGS__,
#define	WdgImageSetDataByIDRC(...)	PropValueDefine(WdgImageSetDataByIDID)	__VA_ARGS__,
#define	WdgTextSetDataByIDRC(...)	PropValueDefine(WdgTextSetDataByIDID)	__VA_ARGS__,
#define	WdgInputSetTextByIdRC(...)	PropValueDefine(WdgInputSetTextByIdID)	__VA_ARGS__,
#define	WdgSwitchIconSetDataByIDRC(...)	PropValueDefine(WdgSwitchIconSetDataByIDID)	__VA_ARGS__,
#define	WdgPullDownSetDataByIdRC(PullDownInfoNum,...)	PropValueDefine(WdgPullDownSetDataByIdID)	__VA_ARGS__,
#define	WdgIndicatorSetDataRC(...)	PropValueDefine(WdgIndicatorSetDataID)	__VA_ARGS__,
#define	WdgTimeSetTimeValueRC(...)	PropValueDefine(WdgTimeSetTimeValueID)	__VA_ARGS__,
#define	WdgFcDateSetDataRC(...)	PropValueDefine(WdgFcDateSetDataID)	__VA_ARGS__,
#define	WdgDateSetDateValueRC(...)	PropValueDefine(WdgDateSetDateValueID)	__VA_ARGS__,
#define	WdgFcTimeSetDataRC(...)	PropValueDefine(WdgFcTimeSetDataID)	__VA_ARGS__,
#define	WdgPickSetDataByIDRC(...)	PropValueDefine(WdgPickSetDataByIDID)	__VA_ARGS__,
#define	WdgCommonPickSetDataByIDRC(TotalSize,...)	PropValueDefine(WdgCommonPickSetDataByIDID)	__VA_ARGS__,
#define	WdgDoubleItemDBTextSetDataByIDRC(...)	PropValueDefine(WdgDoubleItemDBTextSetDataByIDID)	__VA_ARGS__,
#define	WdgDoubleItemITSTextSetDataByIDRC(...)	PropValueDefine(WdgDoubleItemITSTextSetDataByIDID)	__VA_ARGS__,
#define	WdgDoubleItemTextDateSetDataByIDRC(...)	PropValueDefine(WdgDoubleItemTextDateSetDataByIDID)	__VA_ARGS__,
#define	WdgDoubleItemITSTISetDataByIDRC(...)	PropValueDefine(WdgDoubleItemITSTISetDataByIDID)	__VA_ARGS__,

#define	WdgTabSetDataByIDRC(TabInfoAryNum,...)	PropValueDefine(WdgTabSetDataByIDID)	__VA_ARGS__,
#define	WdgDynamicMenuItemRC(aryNum,...)	PropValueDefine(WdgDynamicMenuItemID)	__VA_ARGS__,
#define	WdgDynamicMenuItemInfRC(aryNum,...)	PropValueDefine(WdgDynamicMenuItemInfID)	__VA_ARGS__,
#define	WdgStaticMenuItemRC(aryNum,...)	PropValueDefine(WdgStaticMenuItemID)	__VA_ARGS__,
#define	WdgMenuItemTextRC(aryNum,...)	PropValueDefine(WdgMenuItemTextID)	__VA_ARGS__,
#define	WdgMenuItemImageRC(aryNum,...)	PropValueDefine(WdgMenuItemImageID)	__VA_ARGS__,
#define	WdgMenuItemTextImageRC(aryNum,...)	PropValueDefine(WdgMenuItemTextImageID)	__VA_ARGS__,
#define	WdgMenuItemImageTextRC(aryNum,...)	PropValueDefine(WdgMenuItemImageTextID)	__VA_ARGS__,
#define	WdgMenuItemImageTextImageRC(aryNum,...)	PropValueDefine(WdgMenuItemImageTextImageID)	__VA_ARGS__,
#define	WdgMenuItemTextDateRc(aryNum,...)	PropValueDefine(WdgMenuItemTextDateID)	__VA_ARGS__,
#define	WdgMenuItemTextTimeRC(aryNum,...)	PropValueDefine(WdgMenuItemTextTimeID)	__VA_ARGS__,
#define	WdgMenuItemTextTextRC(aryNum,...)	PropValueDefine(WdgMenuItemTextTextID)	__VA_ARGS__,
#define	WdgMenuItemTextIpRC(aryNum,...)	PropValueDefine(WdgMenuItemTextIpID)	__VA_ARGS__,
#define	WdgMenuItemL1ImageTextL2TextRC(aryNum,...)	PropValueDefine(WdgMenuItemL1ImageTextL2TextID)	__VA_ARGS__,
#define	WdgMenuItemL1ImageTextL2ImageTextRC(aryNum,...)	PropValueDefine(WdgMenuItemL1ImageTextL2ImageTextID)	__VA_ARGS__,
#define	WdgMenuItemL1ImageTextL2TextImageRC(aryNum,...)	PropValueDefine(WdgMenuItemL1ImageTextL2TextImageID)	__VA_ARGS__,
#define	WdgMenuItemImageL1TextL2TextRC(aryNum,...)	PropValueDefine(WdgMenuItemImageL1TextL2TextID)	__VA_ARGS__,
#define	WdgMenuItemImageL1TextImageL2TextImageRC(aryNum,...)	PropValueDefine(WdgMenuItemImageL1TextImageL2TextImageID)	__VA_ARGS__,
#define	WdgMenuItemImageL1TextImageL2TextRC(aryNum,...)	PropValueDefine(WdgMenuItemImageL1TextImageL2TextID)	__VA_ARGS__,
#define	WdgMenuItemTextL2PickTextRC(aryNum,...)	PropValueDefine(WdgMenuItemTextL2PickTextID)	__VA_ARGS__,
#define	WdgMenuItemTextL2PickImageTextRC(aryNum,...)	PropValueDefine(WdgMenuItemTextL2PickImageTextID)	__VA_ARGS__,
#define	WdgMenuItemImageTextL2PickImageTextRC(aryNum,...)	PropValueDefine(WdgMenuItemImageTextL2PickImageTextID)	__VA_ARGS__,
#define	WdgMenuItemButtonRC(aryNum,...)	PropValueDefine(WdgMenuItemButtonID)	__VA_ARGS__,


/* Common */
#define	WdgCommonSetLookCtrlTypeRC(...)	PropValueDefine(WdgCommonSetLookCtrlTypeID)	(WdgLookCtrlType_t)(__VA_ARGS__),
#define	WdgCommonSetIconStyleRC(...)	PropValueDefine(WdgCommonSetIconStyleID)	(Icon_Style_et)(__VA_ARGS__),
#define	WdgCommonSetTextColorRC(...)	PropValueDefine(WdgCommonSetTextColorID)	__VA_ARGS__,
#define	WdgCommonSetHighlightTextColorRC(...)	PropValueDefine(WdgCommonSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgCommonSetFontTypeRC(...)PropValueDefine(	WdgCommonSetFontTypeID)	__VA_ARGS__,
#define	WdgCommonSetFontCategoryRC(...)	PropValueDefine(WdgCommonSetFontCategoryID)	__VA_ARGS__,
#define	WdgCommonSetLangDirectionRC(...)	PropValueDefine(WdgCommonSetLangDirectionID)	(WdgLangDirection_t)(__VA_ARGS__),
#define	WdgCommonSetBGColorRC(...)	PropValueDefine(WdgCommonSetBGColorID)	__VA_ARGS__,
#define	WdgCommonSetBGImageIdRC(...)	PropValueDefine(WdgCommonSetBGImageIdID)	__VA_ARGS__,
#define	WdgCommonSetBGPositionRC(...)	PropValueDefine(WdgCommonSetBGPositionID)	__VA_ARGS__,
#define	WdgCommonSetBGEnableRC(...)	PropValueDefine(WdgCommonSetBGEnableID)	__VA_ARGS__,
#define	WdgCommonSetBGAlignmentRC(...)	PropValueDefine(WdgCommonSetBGAlignmentID)	(WdgAlignment_t)(__VA_ARGS__),
#define	WdgCommonSetAlignmentRC(...)	PropValueDefine(WdgCommonSetAlignmentID)	(WdgAlignment_t)(__VA_ARGS__),
#define	WdgCommonSetBorderDataRC(...)	PropValueDefine(WdgCommonSetBorderDataID)	__VA_ARGS__,
#define	WdgCommonSetPaddingDataRC(...)	PropValueDefine(WdgCommonSetPaddingDataID)	__VA_ARGS__,
#define	WdgCommonEnableScrollBarRC(...)	PropValueDefine(WdgCommonEnableScrollBarID)	(ScrollBarStyle_t)(__VA_ARGS__),


/* View */
#define	WndSetTitleVisiableRC(...)	PropValueDefine(WndSetTitleVisiableID)	__VA_ARGS__,
#define	WndSetStatusBarVisibleRC(...)	PropValueDefine(WndSetStatusBarVisibleID)	__VA_ARGS__,
#define	WndSetSoftkeyVisibleRC(...)	PropValueDefine(WndSetSoftkeyVisibleID)	__VA_ARGS__,
#define	WndSetStatusBarTransparencyRC(...)	PropValueDefine(WndSetStatusBarTransparencyID)	__VA_ARGS__,
#define	WndSetSoftkeyTransparencyRC(...)	PropValueDefine(WndSetSoftkeyTransparencyID)	__VA_ARGS__,
#define	WndSetTitleRC(...)	PropValueDefine(WndSetTitleID)	__VA_ARGS__,
#define	WndSetBgPosRC(...)	PropValueDefine(WndSetBgPosID)	__VA_ARGS__,
#define	WndSetBgColorRC(...)	PropValueDefine(WndSetBgColorID)	__VA_ARGS__,
#define WndSetAllSoftkeyRC(...) PropValueDefine(WndSetAllSoftkeyID) __VA_ARGS__,


/* Button Widget */
#define	WdgButtonSetDisDisplayTextRC(...)	PropValueDefine(WdgButtonSetDisDisplayTextID)	__VA_ARGS__,
#define	WdgButtonSetUnpressedTextColorRC(...)	PropValueDefine(WdgButtonSetUnpressedTextColorID)	__VA_ARGS__,
#define	WdgButtonSetUnpressedTextOutlineColorRC(...)	PropValueDefine(WdgButtonSetUnpressedTextOutlineColorID)	__VA_ARGS__,
#define	WdgButtonSetPressedTextColorRC(...)	PropValueDefine(WdgButtonSetPressedTextColorID)	__VA_ARGS__,
#define	WdgButtonSetPressedTextOutlineColorRC(...)	PropValueDefine(WdgButtonSetPressedTextOutlineColorID)	__VA_ARGS__,


/* Image */
#define	WdgImageSetFrameWidthRC(...)	PropValueDefine(WdgImageSetFrameWidthID)	__VA_ARGS__,
#define	WdgImageSetFrameIntervalRC(...)	PropValueDefine(WdgImageSetFrameIntervalID)	__VA_ARGS__,
#define	WdgImageSetAutoFitRC(...)	PropValueDefine(WdgImageSetAutoFitID)	__VA_ARGS__,
#define	WdgImageSetEnableUpscaleRC(...)	PropValueDefine(WdgImageSetEnableUpscaleID)	__VA_ARGS__,
#define	WdgImageSetEnablePartialDecodeRC(...)	PropValueDefine(WdgImageSetEnablePartialDecodeID)	__VA_ARGS__,
#define	WdgImageSetEnableDefaultImageRC(...)	PropValueDefine(WdgImageSetEnableDefaultImageID)	__VA_ARGS__,
#define	WdgImageSetDefaultImageIDRC(...)	PropValueDefine(WdgImageSetDefaultImageIDID)	__VA_ARGS__,
#define	WdgImageSetImageScaleRotateRC(...)	PropValueDefine(WdgImageSetImageScaleRotateID)	__VA_ARGS__,

/* OverlayImage */
#define WdgOverlayImageSetDataByIDRC(aryNum,...)	PropValueDefine(WdgOverlayImageSetDataByIDID)	__VA_ARGS__,

/* Text Widget */
#define	WdgTextSetFontHeightRC(...)	PropValueDefine(WdgTextSetFontHeightID)	__VA_ARGS__,
#define	WdgTextSetTextOutlineColorRC(...)	PropValueDefine(WdgTextSetTextOutlineColorID)	__VA_ARGS__,
#define	WdgTextSetHighlightTextOutlineColorRC(...)	PropValueDefine(WdgTextSetHighlightTextOutlineColorID)	__VA_ARGS__,
#define	WdgTextSetHighlightBGColorRC(...)	PropValueDefine(WdgTextSetHighlightBGColorID)	__VA_ARGS__,
#define	WdgTextSetSlideDirectionRC(...)	PropValueDefine(WdgTextSetSlideDirectionID)	__VA_ARGS__,
#define	WdgTextSetSlideStepOffsetRC(...)	PropValueDefine(WdgTextSetSlideStepOffsetID)	__VA_ARGS__,
#define	WdgTextSetSlideStepTimeRC(...)	PropValueDefine(WdgTextSetSlideStepTimeID)	__VA_ARGS__,
#define	WdgTextSetEnableAnimateRC(...)	PropValueDefine(WdgTextSetEnableAnimateID)	__VA_ARGS__,
#define	WdgTextSetSlideOnOffRC(...)	PropValueDefine(WdgTextSetSlideOnOffID)	__VA_ARGS__,
#define	WdgTextSetSlideAutoRepeatRC(...)	PropValueDefine(WdgTextSetSlideAutoRepeatID)	__VA_ARGS__,
#define	WdgTextSetSlideStyleRC(...)	PropValueDefine(WdgTextSetSlideStyleID)	(SlideStyle_t)(__VA_ARGS__),
#define	WdgTextSetLayoutFlagRC(...)	PropValueDefine(WdgTextSetLayoutFlagID)	(TextLayout_t)(__VA_ARGS__),
#define	WdgTextSetFcsItemBGColorRC(...)	PropValueDefine(WdgTextSetFcsItemBGColorID)	__VA_ARGS__,


/* Input */
#define	WdgInputSetDecimalPointEnableRC(...)	PropValueDefine(WdgInputSetDecimalPointEnableID)	__VA_ARGS__,
#define	WdgInputSetFirstKeyPressRC(...)	PropValueDefine(WdgInputSetFirstKeyPressID)	__VA_ARGS__,
#define	WdgInputSetFontSizeRC(...)	PropValueDefine(WdgInputSetFontSizeID)	__VA_ARGS__,
#define	WdgInputSetFontTypeRC(...)	PropValueDefine(WdgInputSetFontTypeID)	__VA_ARGS__,
#define	WdgInputSetHandWritingEnableRC(...)	PropValueDefine(WdgInputSetHandWritingEnableID)	__VA_ARGS__,
#define	WdgInputSetHighlightBGColorRC(...)	PropValueDefine(WdgInputSetHighlightBGColorID)	__VA_ARGS__,
#define	WdgInputSetHighlightTextColorRC(...)	PropValueDefine(WdgInputSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgInputSetLineGapRC(...)	PropValueDefine(WdgInputSetLineGapID)	__VA_ARGS__,
#define	WdgInputSetMaxByteLengthRC(...)	PropValueDefine(WdgInputSetMaxByteLengthID)	__VA_ARGS__,
#define	WdgInputSetMaxlenAfterDecimalPointRC(...)	PropValueDefine(WdgInputSetMaxlenAfterDecimalPointID)	__VA_ARGS__,
#define	WdgInputSetMaxlenAfterExponentRC(...)	PropValueDefine(WdgInputSetMaxlenAfterExponentID)	__VA_ARGS__,
#define	WdgInputSetMultilineRC(...)	PropValueDefine(WdgInputSetMultilineID)	__VA_ARGS__,
#define	WdgInputSetPasswordStyleRC(...)	PropValueDefine(WdgInputSetPasswordStyleID)	__VA_ARGS__,
#define	WdgInputSetShowBorderWhenLoseFocusRC(...)	PropValueDefine(WdgInputSetShowBorderWhenLoseFocusID)	__VA_ARGS__,
#define	WdgInputSetSmartInputOffRC(...)	PropValueDefine(WdgInputSetSmartInputOffID)	__VA_ARGS__,
#define	WdgInputSetSoftKeyBoardEnableRC(...)	PropValueDefine(WdgInputSetSoftKeyBoardEnableID)	__VA_ARGS__,
#define	WdgInputSetTextColorRC(...)	PropValueDefine(WdgInputSetTextColorID)	__VA_ARGS__,
#define	WdgInputSetInitTextRC(...)	PropValueDefine(WdgInputSetInitTextID)	__VA_ARGS__,
#define	WdgInputSetCursorColorRC(...)	PropValueDefine(WdgInputSetCursorColorID)	__VA_ARGS__,
#define	WdgInputSetCurrentInputLanguageRC(...)	PropValueDefine(WdgInputSetCurrentInputLanguageID)	__VA_ARGS__,
#define	WdgInputSetDisableSymbolTableRC(...)	PropValueDefine(WdgInputSetDisableSymbolTableID)	__VA_ARGS__,
#define	WdgInputSetDisableSwitchInputModeRC(...)	PropValueDefine(WdgInputSetDisableSwitchInputModeID)	__VA_ARGS__,
#define	WdgInputSetChineseInputOffRC(...)	PropValueDefine(WdgInputSetChineseInputOffID)	__VA_ARGS__,
#define	WdgInputSetLineFeedDisableRC(...)	PropValueDefine(WdgInputSetLineFeedDisableID)	__VA_ARGS__,
#define	WdgInputSetDialingShiftOldestCharRC(...)	PropValueDefine(WdgInputSetDialingShiftOldestCharID)	__VA_ARGS__,
#define	WdgInputSetModeMaskRC(...)	PropValueDefine(WdgInputSetModeMaskID)	__VA_ARGS__,
#define	WdgInputSetCurrentInputModeRC(...)	PropValueDefine(WdgInputSetCurrentInputModeID)	__VA_ARGS__,


/* Tab */
#define	WdgTabSetModeRC(...)	PropValueDefine(WdgTabSetModeID)	(TabWdgMode_e)(__VA_ARGS__),
#define	WdgTabSetActiveWidthRC(...)	PropValueDefine(WdgTabSetActiveWidthID)	__VA_ARGS__,
#define	WdgTabSetInactiveWidthRC(...)	PropValueDefine(WdgTabSetInactiveWidthID)	__VA_ARGS__,
#define	WdgTabSetTabHeightRC(...)	PropValueDefine(WdgTabSetTabHeightID)	__VA_ARGS__,
#define	WdgTabSetTabHeightOffsetRC(...)	PropValueDefine(WdgTabSetTabHeightOffsetID)	__VA_ARGS__,
#define	WdgTabSetTabPaddingLeftRC(...)	PropValueDefine(WdgTabSetTabPaddingLeftID)	__VA_ARGS__,
#define	WdgTabSetTabPaddingRightRC(...)	PropValueDefine(WdgTabSetTabPaddingRightID)	__VA_ARGS__,
#define	WdgTabSetTabGapRC(...)	PropValueDefine(WdgTabSetTabGapID)	__VA_ARGS__,


/* Switch Icon */
#define	WdgSwitchIconSetIconStyleRC(...)	PropValueDefine(WdgSwitchIconSetIconStyleID)	(Icon_Style_et)(__VA_ARGS__),


/* Progress */
#define	WdgProgressSetRepeatRC(...)	PropValueDefine(WdgProgressSetRepeatID)	__VA_ARGS__,
#define	WdgProgressSetFgBorderColorRC(...)	PropValueDefine(WdgProgressSetFgBorderColorID)	__VA_ARGS__,
#define	WdgProgressSetBgBorderColorRC(...)	PropValueDefine(WdgProgressSetBgBorderColorID)	__VA_ARGS__,
#define	WdgProgressSetFgFillColorRC(...)	PropValueDefine(WdgProgressSetFgFillColorID)	__VA_ARGS__,
#define	WdgProgressSetBgFillColorRC(...)	PropValueDefine(WdgProgressSetBgFillColorID)	__VA_ARGS__,
#define	WdgProgressSetFgRectFlagRC(...)	PropValueDefine(WdgProgressSetFgRectFlagID)	__VA_ARGS__,
#define	WdgProgressSetBgRectFlagRC(...)	PropValueDefine(WdgProgressSetBgRectFlagID)	__VA_ARGS__,
#define	WdgProgressSetTotalRC(...)	PropValueDefine(WdgProgressSetTotalID)	__VA_ARGS__,
#define	WdgProgressSetCurPosRC(...)	PropValueDefine(WdgProgressSetCurPosID)	__VA_ARGS__,
#define	WdgProgressSetPreferCellWidthRC(...)	PropValueDefine(WdgProgressSetPreferCellWidthID)	__VA_ARGS__,
#define	WdgProgressSetPreferCellTotalNumRC(...)	PropValueDefine(WdgProgressSetPreferCellTotalNumID)	__VA_ARGS__,
#define	WdgProgressSetPreferCellRepeatlNumRC(...)	PropValueDefine(WdgProgressSetPreferCellRepeatlNumID)	__VA_ARGS__,
#define	WdgProgressSetAutoOnOffRC(...)	PropValueDefine(WdgProgressSetAutoOnOffID)	__VA_ARGS__,

/* IP Widget */
#define	WdgIPCommonSetFontRC(...)	PropValueDefine(WdgIPCommonSetFontID)	__VA_ARGS__,
#define	WdgIPSetHighlightBGColorRC(...)	PropValueDefine(WdgIPSetHighlightBGColorID)	__VA_ARGS__,
#define	WdgIPSetHighlightTextColorRC(...)	PropValueDefine(WdgIPSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgIPSetIPValueRC(...)	PropValueDefine(WdgIPSetIPValueID)	__VA_ARGS__,

/* Fadeout Widget */
#define	WdgFadeoutSetFoLevelRC(...)	PropValueDefine(WdgFadeoutSetFoLevelID)	__VA_ARGS__,

/* PullDown Widget */
#define	WdgPullDownSetFocusIndexRC(...)	PropValueDefine(WdgPullDownSetFocusIndexID)	__VA_ARGS__,
#define	WdgPullDownSetLayoutModeRC(...)	PropValueDefine(WdgPullDownSetLayoutModeID)	(PullDownWdgMode_et)(__VA_ARGS__),
#define	WdgPullDownSetNaviUpKeyRC(...)	PropValueDefine(WdgPullDownSetNaviUpKeyID)	__VA_ARGS__,
#define	WdgPullDownSetNaviDownKeyRC(...)	PropValueDefine(WdgPullDownSetNaviDownKeyID)	__VA_ARGS__,
#define	WdgPullDownSetToggleListKeyRC(...)	PropValueDefine(WdgPullDownSetToggleListKeyID)	__VA_ARGS__,
#define	WdgPullDownSetArrowWidthRC(...)	PropValueDefine(WdgPullDownSetArrowWidthID)	__VA_ARGS__,
#define	WdgPullDownSetTextColorRC(...)	PropValueDefine(WdgPullDownSetTextColorID)	__VA_ARGS__,
#define	WdgPullDownSetHighlightTextColorRC(...)	PropValueDefine(WdgPullDownSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgPullDownSetHighlightBgColorRC(...)	PropValueDefine(WdgPullDownSetHighlightBgColorID)	__VA_ARGS__,
#define	WdgPullDownSetListBorderColorRC(...)	PropValueDefine(WdgPullDownSetListBorderColorID)	__VA_ARGS__,



/* Indicator Widget */
#define	WdgIndicatorSetLayoutStyleRC(...)	PropValueDefine(WdgIndicatorSetLayoutStyleID)	(WdgLayoutStyle_t)(__VA_ARGS__),
#define	WdgIndicatorSetFGTopOffsetRC(...)	PropValueDefine(WdgIndicatorSetFGTopOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetFGBottomOffsetRC(...)	PropValueDefine(WdgIndicatorSetFGBottomOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetFGLeftOffsetRC(...)	PropValueDefine(WdgIndicatorSetFGLeftOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetFGRightOffsetRC(...)	PropValueDefine(WdgIndicatorSetFGRightOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetINDOffsetRC(...)	PropValueDefine(WdgIndicatorSetINDOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetINDImageIDRC(...)	PropValueDefine(WdgIndicatorSetINDImageIDID)	__VA_ARGS__,
#define	WdgIndicatorSetFGImageIDRC(...)	PropValueDefine(WdgIndicatorSetFGImageIDID)	__VA_ARGS__,
#define	WdgIndicatorSetBGImageIDRC(...)	PropValueDefine(WdgIndicatorSetBGImageIDID)	__VA_ARGS__,

#define	WdgIndicatorSetDWNTopOffsetRC(...)	    PropValueDefine(WdgIndicatorSetDWNTopOffsetID)	    __VA_ARGS__,
#define	WdgIndicatorSetDWNBottomOffsetRC(...)	PropValueDefine(WdgIndicatorSetDWNBottomOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetDWNLeftOffsetRC(...)	    PropValueDefine(WdgIndicatorSetDWNLeftOffsetID)	    __VA_ARGS__,
#define	WdgIndicatorSetDWNRightOffsetRC(...)	PropValueDefine(WdgIndicatorSetDWNRightOffsetID)	__VA_ARGS__,
#define	WdgIndicatorSetDWNEndOffsetRC(...)	    PropValueDefine(WdgIndicatorSetDWNEndOffsetID)	    __VA_ARGS__,
#define	WdgIndicatorSetDWNImageIDRC(...)	    PropValueDefine(WdgIndicatorSetDWNImageIDID)	    __VA_ARGS__,
#define	WdgIndicatorSetDWNENDImageIDRC(...)	    PropValueDefine(WdgIndicatorSetDWNENDImageIDID)	    __VA_ARGS__,


/* Viewport Widget */
#define	WdgViewportSetLockVerMoveRC(...)	PropValueDefine(WdgViewportSetLockVerMoveID)	__VA_ARGS__,
#define	WdgViewportSetLockHoriMoveRC(...)	PropValueDefine(WdgViewportSetLockHoriMoveID)	__VA_ARGS__,
#define	WdgViewportSetKeepCenterRC(...)	PropValueDefine(WdgViewportSetKeepCenterID)	__VA_ARGS__,
#define	WdgViewportSetPanStepRC(...)	PropValueDefine(WdgViewportSetPanStepID)	__VA_ARGS__,
#define	WdgViewportSetCurrentYOffsetRC(...)	PropValueDefine(WdgViewportSetCurrentYOffsetID)	__VA_ARGS__,
#define	WdgViewportSetCurrentXOffsetRC(...)	PropValueDefine(WdgViewportSetCurrentXOffsetID)	__VA_ARGS__,


/* Time Widget */
#define	WdgTimeSetEnableAdjustValueByNaviUpDownRC(...)	PropValueDefine(WdgTimeSetEnableAdjustValueByNaviUpDownID)	__VA_ARGS__,
#define	WdgTimeSetEnableSecondFieldRC(...)	PropValueDefine(WdgTimeSetEnableSecondFieldID)	__VA_ARGS__,
#define	WdgTimeSetHourFormatRC(...)	PropValueDefine(WdgTimeSetHourFormatID)	__VA_ARGS__,
#define	WdgTimeSetHighlightTextColorRC(...)	PropValueDefine(WdgTimeSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgTimeSetHighlightBGColorRC(...)	PropValueDefine(WdgTimeSetHighlightBGColorID)	__VA_ARGS__,


/* FcDate Widget */
#define	WdgFcDateSetMaxYearRC(...)	PropValueDefine(WdgFcDateSetMaxYearID)	__VA_ARGS__,
#define	WdgFcDateSetMinYearRC(...)	PropValueDefine(WdgFcDateSetMinYearID)	__VA_ARGS__,
#define	WdgFcDateSetFocusIndRC(...)	PropValueDefine(WdgFcDateSetFocusIndID)	(_FCDIndType_t)(__VA_ARGS__),


/* Date Widget */
#define	WdgDateSetEnableAdjustValueByNaviUpDownRC(...)	PropValueDefine(WdgDateSetEnableAdjustValueByNaviUpDownID)	__VA_ARGS__,
#define	WdgDateSetHighlightBGColorRC(...)	PropValueDefine(WdgDateSetHighlightBGColorID)	__VA_ARGS__,
#define	WdgDateSetHighlightTextColorRC(...)	PropValueDefine(WdgDateSetHighlightTextColorID)	__VA_ARGS__,
#define	WdgDateSetMaxYearRC(...)	PropValueDefine(WdgDateSetMaxYearID)	__VA_ARGS__,
#define	WdgDateSetMinYearRC(...)	PropValueDefine(WdgDateSetMinYearID)	__VA_ARGS__,

/* FcTime Widget */


/* Menu Widget */
#define	WdgMenuSetItemFocusImageRC(...)	PropValueDefine(WdgMenuSetItemFocusImageID)	__VA_ARGS__,
#define	WdgMenuSetItemUnFocusImageRC(...)	PropValueDefine(WdgMenuSetItemUnFocusImageID)	__VA_ARGS__,
#define	WdgMenuSetRollTypeRC(...)	PropValueDefine(WdgMenuSetRollTypeID)	(WdgMenuRollType_t)(__VA_ARGS__),
#define	WdgMenuSetCheckStyleRC(...)	PropValueDefine(WdgMenuSetCheckStyleID)	(WdgMenuCheckStyle_t)(__VA_ARGS__),
#define	WdgMenuSetMenuBGImageRC(...)	PropValueDefine(WdgMenuSetMenuBGImageID)	__VA_ARGS__,
#define	WdgStaticMenuInitRC(...)	PropValueDefine(WdgStaticMenuInitID)	(WdgMenuItemType_t)(__VA_ARGS__),
#define	WdgMenuSetFirstItemRC(...)	PropValueDefine(WdgMenuSetFirstItemID)	__VA_ARGS__,
#define	WdgMenuSetHighlightedItemRC(...)	PropValueDefine(WdgMenuSetHighlightedItemID)	__VA_ARGS__,
#define	WdgMenuSetToGridStyleRC(...) PropValueDefine(WdgMenuSetToGridStyleID)	__VA_ARGS__,
#define WdgMenuSetItemWidthRC(...)	PropValueDefine(WdgMenuSetItemWidthID)	__VA_ARGS__,
#define WdgMenuSetItemHeightRC(...)	PropValueDefine(WdgMenuSetItemHeightID)	__VA_ARGS__,
#define WdgMenuSetRowGapRC(...)	PropValueDefine(WdgMenuSetRowGapID)	__VA_ARGS__,
#define WdgMenuSetColGapRC(...)	PropValueDefine(WdgMenuSetColGapID)	__VA_ARGS__,
#define WdgMenuSetFixedNumRC(...)	PropValueDefine(WdgMenuSetFixedNumID)	__VA_ARGS__,

/* Image Text Image Widget */
#define WdgITISetPreImageWidthRC(...)       PropValueDefine( WdgITISetPreImageWidthID) __VA_ARGS__,
#define WdgITISetPreImagePrePaddingRC(...)  PropValueDefine( WdgITISetPreImagePrePaddingID) __VA_ARGS__,
#define WdgITISetTextPrePaddingRC(...)      PropValueDefine( WdgITISetTextPrePaddingID) __VA_ARGS__,

/* Pick Widget */
#define	WdgPickSetInvisibleIfDisableRC(...)	PropValueDefine(WdgPickSetInvisibleIfDisableID)	__VA_ARGS__,
#define	WdgPickSetFocusIndexRC(...)	PropValueDefine(WdgPickSetFocusIndexID)	__VA_ARGS__,
#define	WdgPickSetLayoutStyleRC(...)	PropValueDefine(WdgPickSetLayoutStyleID)	(WdgLayoutStyle_t)(__VA_ARGS__),
#define	WdgPickSetArrowInsideRC(...)	PropValueDefine(WdgPickSetArrowInsideID)	__VA_ARGS__,


/* Common Pick Widget */
#define	WdgCommonPickSetInvisibleIfDisableRC(...)	PropValueDefine(WdgCommonPickSetInvisibleIfDisableID)	__VA_ARGS__,
#define	WdgCommonPickSetFocusIndexRC(...)	PropValueDefine(WdgCommonPickSetFocusIndexID)	__VA_ARGS__,
#define	WdgCommonPickSetLayoutStyleRC(...)	PropValueDefine(WdgCommonPickSetLayoutStyleID)	(WdgLayoutStyle_t)(__VA_ARGS__),
#define	WdgCommonPickSetArrowInsideRC(...)	PropValueDefine(WdgCommonPickSetArrowInsideID)	__VA_ARGS__,



/* Double Widget */
#define	WdgDoubleItemSetDisableDownWidgetBGRC(...)	PropValueDefine(WdgDoubleItemSetDisableDownWidgetBGID)	__VA_ARGS__,
#define	WdgDoubleItemSetTextOutlineColorRC(...)	PropValueDefine(WdgDoubleItemSetTextOutlineColorID)	__VA_ARGS__,
#define	WdgDoubleItemSetHighlightedTextOutlineColorRC(...)	PropValueDefine(WdgDoubleItemSetHighlightedTextOutlineColorID)	__VA_ARGS__,
#define	WdgDoubleItemSetSlideOnOffRC(...)	PropValueDefine(WdgDoubleItemSetSlideOnOffID)	__VA_ARGS__,


#define RSCustomize(type, name, ...) __VA_ARGS__,

#define WdgStatusPageDefRC(IconNum,...) __VA_ARGS__,
