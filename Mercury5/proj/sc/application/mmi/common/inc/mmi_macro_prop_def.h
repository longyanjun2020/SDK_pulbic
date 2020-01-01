
#undef PropIDDefine
#define PropIDDefine(PropID)

/* VTM for AP */
#define	VtmCreateDateInputRC(...) 	    PropIDDefine( nVtmDateInputID)    DateInputData_t tDateInput;
#define	VtmCreateImgRC(...)	            PropIDDefine( nVtmImgID)          ImageVtmData_t tImage;
#define	VtmCreateInputRC(...)	        PropIDDefine( nVtmInputID)        InputVtmData_t tInput;
#define	VtmCreatePromptInputRC(...)	    PropIDDefine( nVtmPropInputID)    PromptInputData_t	tPrompt;
#define	VtmCreateTimeInputRC(...)	    PropIDDefine( nVtmTimeInputID)    TimeInputData_t tTime;
#define	VtmCreateImgGridMenuRC(...)	    PropIDDefine( nVtmImgGridMenuID)  ImgGridData_t	tImgGrid;
#define	VtmCreateImgThumbRC(...)    	PropIDDefine( nVtmImgThumbID)     ImgThumbData_t	tImgThumb;
#define	VtmCreateMenuRC(...)	        PropIDDefine( nVtmMenuID)         MenuData_t	tMenu;
#define	VtmCreateSimSelectionRC(...)	PropIDDefine( nVtmSimSelectID)    SimSelectionData_t	tSim;
#define	VtmCreateTabMenuRC(...)	        PropIDDefine( nVtmTabMenuID)      TabMenuData_t	tTabMenu;
#define	VtmCreateTxtGridMenuRC(...)	    PropIDDefine( nVtmTxtGridID)      TxtGridData_t	tTxtGrid;
#define	VtmCreateIpInputRC(...)   	    PropIDDefine( nVtmIpInputID)      IpInputData_t	tIp;
#define	VtmCreateOptionMenuRC(...)	    PropIDDefine( nVtmOptionID)       OptionMenuData_t tOptionMenu;
#define	VtmCreatePopUpInfoRC(...)	    PropIDDefine( nVtmPopUpInfoID)    PopUpInfoData_t	tPopInfo;
#define	VtmCreatePopUpInputRC(...)	    PropIDDefine( nVtmPopUp)          PopUpInputData_t tPopInput;
#define	VtmCreatePopUpPromptRC(...)	    PropIDDefine( nVtmPopUpPromptID)  PopUpPromptData_t	tPopPrompt;
#define	VtmCreatePopUpSelectRC(...)	    PropIDDefine( nVtmPopUpSelectID)  PopUpSelectData_t	tPopSelect;

#define	VtmCreateImgGridMenuDataRC(aryNum, ...) PropIDDefine( nVtmImgGridDataID) 	    WdgStaticMenuItem_t tImgGridData[aryNum];
#define	VtmCreateImgThumbDataRC(aryNum, ...)	PropIDDefine( nVtmImgThumbDataID)     WdgStaticMenuItem_t tImgThumbData[aryNum];
#define	VtmCreateMenuDataRC(aryNum, ...)	    PropIDDefine( nVtmMenuDataID)         WdgStaticMenuItem_t tMenuData[aryNum];
#define	VtmCreateTabMenuDataRC(aryNum, ...)     PropIDDefine( nVtmTabMenuDataID)	    TabPageData_t tTabMenuData[aryNum];
#define	VtmCreateTxtGridMenuDataRC(aryNum, ...) PropIDDefine( nVtmTxtGridDataID)	    WdgStaticMenuItem_t tTxtGridData[aryNum];
#define	VtmCreateOptionMenuDataRC(aryNum, ...)  PropIDDefine( nVtmOptionDataID)	    WdgStaticMenuItem_t tOptionMenuData[aryNum];
#define	VtmCreatePopUpInfoDataRC(aryNum, ...)	PropIDDefine( nVtmPopUpInfoDataID)    MAE_WChar tPopInfoData[aryNum];
#define	VtmCreatePopUpSelectDataRC(aryNum, ...) PropIDDefine( nVtmPopUpSelectDataID)	WdgStaticMenuItem_t tPopSelectData[aryNum];

/* Common Create  */
#define	WdgAbsContainerCreateForWndRC(...)  PropIDDefine( nAbsCreateID)           CommonVar_t	tCommon;
#define	WdgViewportCreateForWndRC(...)	    PropIDDefine( nViewportCreateID)      ViewportVar_t tCommon;
#define	WdgButtonCreateForWndRC(...)	    PropIDDefine( nButtonCreateID)        CommonVar_t	tCommon;
#define	WdgImageCreateForWndRC(...)	        PropIDDefine( nImageCreateID)         ImageVar_t	tCommon;
#define	WdgTextCreateForWndRC(...)	        PropIDDefine( nTextCreateID)          CommonVar_t tCommon;
#define	WdgInputCreateForWndRC(...)	        PropIDDefine( nInputCreateID)         InputVar_t	tCommon;
#define	WdgOsdCreateForWndRC(...)	        PropIDDefine( nOsdCreateID)           CommonVar_t	tCommon;
#define	WdgTabCreateForWndRC(...)	        PropIDDefine( nTabCreateID)           CommonVar_t	tCommon;
#define	WdgSwitchIconCreateForWndRC(...)	PropIDDefine( nSwitchIconCreateID)    SwIconVar_t	tCommon;
#define	WdgProgressCreateForWndRC(...)	    PropIDDefine( nProgressCreateID)      Progress_t	tCommon;
#define	WdgIPCreateForWndRC(...)	        PropIDDefine( nIpCreateID)            IPVar_t	tCommon;
#define	WdgFadeoutCreateForWndRC(...)	    PropIDDefine( nFadeoutCreateID)       FadeVar_t	tCommon;
#define	WdgPullDownCreateForWndRC(...)	    PropIDDefine( nPullDownCreateID)      CommonVar_t	tCommon;
#define	WdgIndicatorCreateForWndRC(...)	    PropIDDefine( nIndicatorCreateID)     CommonVar_t	tCommon;
#define	WdgTimeCreateForWndRC(...)	        PropIDDefine( nTimeCreateID)          CommonVar_t	tCommon;
#define	WdgFcDateCreateForWndRC(...)	    PropIDDefine( nFcDateCreateID)        FcDateVar_t	tCommon;
#define	WdgDateCreateForWndRC(...)	        PropIDDefine( nDateCreateID)          DateVar_t	tCommon;
#define	WdgFcTimeCreateForWndRC(...)	    PropIDDefine( nFcTimeCreateID)        FcTimeVar_t	tCommon;
#define	WdgMenuCreateForWndRC(...)	        PropIDDefine( nMenuCreateID)          CommonVar_t	tCommon;
#define	WdgPickCreateForWndRC(...)	        PropIDDefine( nPickCreateID)          PickVar_t	tCommon;
#define	WdgCommonPickCreateForWndRC(...)	PropIDDefine( nCommPickCreateID)      CommonVar_t	tCommon;
#define	WdgDoubleItemCreateForWndRC(...)	PropIDDefine( nDoubleItemCreateID)    CommonVar_t	tCommon;

/* SetDataByID */
#define	WdgButtonSetDataByIDRC(...)	        PropIDDefine( nButtonSetDataByID)     WdgButtonDataID_t	tDataID;
#define	WdgImageSetDataByIDRC(...)	        PropIDDefine( nImageSetDataByID)      u32	nDataID;
#define	WdgTextSetDataByIDRC(...)	        PropIDDefine( nTextSetDataByID)       u32	nDataID;
#define	WdgInputSetTextByIdRC(...)	        PropIDDefine( nInputSetDataByID)      u32	nDataID;
#define	WdgSwitchIconSetDataByIDRC(...)	    PropIDDefine( nSwitchIconSetDataByID) WdgSwitchIconDataId_t	tDataID;
#define	WdgIndicatorSetDataRC(...)	        PropIDDefine( nIndicatorSetDataByID)  IndicatorData_t	tDataID;
#define	WdgTimeSetTimeValueRC(...)	        PropIDDefine( nTimeSetTimeValueID)    MAE_DateTime_t	tDataID;
#define	WdgFcDateSetDataRC(...)	            PropIDDefine( nFcDateSetDataID)       MAE_DateTime_t	tDataID;
#define	WdgDateSetDateValueRC(...)	        PropIDDefine( nDateSetDateValueID)    MAE_DateTime_t	tDataID;
#define	WdgFcTimeSetDataRC(...)	            PropIDDefine( nFcTimeSetDataID)       MAE_DateTime_t	tDataID;
#define	WdgDoubleItemITSTextSetDataByIDRC(...)	PropIDDefine( nDBITSTxtDataID)    WdgDoubleItemTIT_t tDBItemTIT;
#define WdgDoubleItemITSTISetDataByIDRC(...)    PropIDDefine( nDBITSTIDataID)     WdgDoubleItemDBTextImage_t tDBItemITSTI;
#define WdgDoubleItemITSITSetDataByIDRC(...)    PropIDDefine( nDBITSITDataID)     WdgDoubleItemDBTextImage_t tDBItemITSIT;
#define WdgDoubleItemDBTextSetDataByIDRC(...)   PropIDDefine( nDBTxtDataID)       WdgDoubleItemDBText_t tDBItemDBTxt;
#define	WdgDoubleItemTextDateSetDataByIDRC(...) PropIDDefine( nDBTxtDateDataID)   WdgDoubleItemTextTime_t tDBTxtDate;
#define WdgTabSetDataByIDRC(TabInfoNum, ...)    PropIDDefine( nTabSetDataByID)    WdgTabInfo_t pTabInfo[TabInfoNum];
#define WdgPullDownSetDataByIdRC(PullDownInfoNum,...)   PropIDDefine( nPullDownSetDataByID)    WdgPullDownInfo_t pPullDownInfo[PullDownInfoNum];
#define	WdgPickSetDataByIDRC(PickInfoNum,...)   PropIDDefine( nPickSetDataByID)   u32    pPickInfo[PickInfoNum];
#define WdgCommonPickSetDataByIDRC(TotalSize,...)  PropIDDefine( nCommPickSetDispDataID) CommPickVar_t tCommPick; WdgCommonPickInfo_t  pPickDispData[TotalSize];


#define WdgDynamicMenuItemRC(aryNum, ...)       PropIDDefine( nDynamicMenuItemID)     WdgDynamicMenuItem_t tDynamicMenuItemData[aryNum];
#define WdgDynamicMenuItemInfRC(aryNum, ...)    PropIDDefine( nDynamicMenuItemInfID)  WdgDynamicMenuItemInf_t tDynamicMenuItem[aryNum];
#define WdgStaticMenuItemRC(aryNum,...)         PropIDDefine( nStaticMenuItemID)      WdgStaticMenuItem_t tStaticMenuItem[aryNum];

#define WdgMenuItemTextRC(aryNum,...)           PropIDDefine( nMenuItemTxtID)       WdgMenuItemText_t tMenuItemTxt[aryNum];
#define WdgMenuItemImageRC(aryNum,...)          PropIDDefine( nMenuItemImgID)       WdgMenuItemImage_t tMenuItemImg[aryNum];
#define WdgMenuItemTextImageRC(aryNum,...)      PropIDDefine( nMenuItemTxtImgID)    WdgMenuItemTextImage_t tMenuItemTxtImg[aryNum];
#define WdgMenuItemImageTextRC(aryNum,...)      PropIDDefine( nMenuItemTxtImgID)    WdgMenuItemImageText_t tMenuItemImgTxt[aryNum];
#define WdgMenuItemImageTextImageRC(aryNum,...) PropIDDefine( nMenuItemImgTxtImgID) WdgMenuItemImageTextImage_t tMenuItemImgTxtImg[aryNum];
#define WdgMenuItemTextDateRc(aryNum,...)       PropIDDefine( nMenuItemTxtDateID)   WdgMenuItemTextDate_t tMenuItemTxtDate[aryNum];
#define WdgMenuItemTextTimeRC(aryNum,...)       PropIDDefine( nMenuItemTxtTimeID)   WdgMenuItemTextTime_t tMenuItemTxtTime[aryNum];
#define WdgMenuItemTextTextRC(aryNum,...)       PropIDDefine( nMenuItemTxtTxtID)    WdgMenuItemTextText_t tMenuItemTxtTxt[aryNum];
#define WdgMenuItemTextIpRC(aryNum,...)         PropIDDefine( nMenuItemTxtIpID)     WdgMenuItemTextIp_t tMenuItemTxtIp[aryNum];
#define WdgMenuItemL1ImageTextL2TextRC(aryNum,...)      PropIDDefine( nMenuItemL1ImgTxtL2TxtID)     WdgMenuItemL1ImageTextL2Text_t tMenuItemL1ImgTxtL2Txt[aryNum];
#define WdgMenuItemL1ImageTextL2ImageTextRC(aryNum,...) PropIDDefine( nMenuItemL1ImgTxtL2ImgTxtID)  WdgMenuItemL1ImageTextL2ImageText_t tMenuItemL1ImgTxtL2ImgTxt[aryNum];
#define WdgMenuItemL1ImageTextL2TextImageRC(aryNum,...) PropIDDefine( nMenuItemL1ImgTxtL2TxtImgID)  WdgMenuItemL1ImageTextL2TextImage_t tMenuItemL1ImgTxtL2TxtImg[aryNum];
#define WdgMenuItemImageL1TextL2TextRC(aryNum,...)      PropIDDefine( nMenuImgL1TxtL2TxtID)         WdgMenuItemImageL1TextL2Text_t tMenuImgL1TxtL2Txt[aryNum];
#define WdgMenuItemImageL1TextImageL2TextImageRC(aryNum,...)    PropIDDefine( nMenuItemImgL1TxtImgL2TxtImgID)   WdgMenuItemImageL1TextImageL2TextImage_t tMenuItemImgL1TxtImgL2TxtImg[aryNum];
#define WdgMenuItemImageL1TextImageL2TextRC(aryNum,...)         PropIDDefine( nMenuItemL1TxtImgL2TxtID)         WdgMenuItemImageL1TextImageL2Text_t tMenuItemL1TxtImgL2Txt[aryNum];
#define WdgMenuItemTextL2PickTextRC(aryNum,...)                 PropIDDefine( nMenuL2PickTxtID)                 WdgMenuItemTextL2PickText_t tMenuL2PickTxt[aryNum];
#define WdgMenuItemTextL2PickImageTextRC(aryNum,...)            PropIDDefine( nMenuItemTxtL2PickImgTxtID)       WdgMenuItemTextL2PickImageText_t tMenuItemTxtL2PickImgTxt[aryNum];
#define WdgMenuItemImageTextL2PickImageTextRC(aryNum,...)       PropIDDefine( nMenuItemImgTxtL2PickImgTxtID)    WdgMenuItemImageTextL2PickImageText_t tMenuItemImgTxtL2PickImgTxt[aryNum];
#define WdgMenuItemButtonRC(aryNum,...)         PropIDDefine( nMenuItemButtonID)    WdgMenuItemButton_t tMenuItemButton[aryNum];


/* Common */
#define	WdgCommonSetLookCtrlTypeRC(...)	PropIDDefine( nLookCtrlTypeID)	WdgLookCtrlType_t	eLookCtrlType;
#define	WdgCommonSetIconStyleRC(...)	PropIDDefine( nIconStlID)	Icon_Style_et	eIconStl;
#define	WdgCommonSetTextColorRC(...)	PropIDDefine( nTxtClrID)	RGBColor_t	tTxtClr;
#define	WdgCommonSetHighlightTextColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtClr;
#define	WdgCommonSetFontTypeRC(...)	    PropIDDefine( nFntTypeID)	FontType_t	tFntType;
#define	WdgCommonSetFontCategoryRC(...)	PropIDDefine( nFntCateID)	FontCategory_t	tFntCate;
#define	WdgCommonSetLangDirectionRC(...)	PropIDDefine( nLangDirID)	WdgLangDirection_t	eLangDir;
#define	WdgCommonSetBGColorRC(...)	PropIDDefine( nBgClrID)	RGBColor_t	tBgClr;
#define	WdgCommonSetBGImageIdRC(...)	PropIDDefine( nBgImgIdID)	u32	nBgImgId;
#define	WdgCommonSetBGPositionRC(...)	PropIDDefine( nBgPosID)	WdgBackgroundPos_et	tBgPos;
#define	WdgCommonSetBGEnableRC(...)	PropIDDefine( nBgEnbID)	boolean	bBgEnb;
#define	WdgCommonSetBGAlignmentRC(...)	PropIDDefine( nBgAligID)	WdgAlignment_t	eBgAlig;
#define	WdgCommonSetAlignmentRC(...)	PropIDDefine( nAligID)	WdgAlignment_t	eAlig;
#define	WdgCommonSetBorderDataRC(...)	PropIDDefine( nBdrDataID)	WdgBorderData_t	tBdrData;
#define	WdgCommonSetPaddingDataRC(...)	PropIDDefine( nPadDataID)	WdgPaddingData_t	tPadData;
#define WdgCommonEnableScrollBarRC(...) PropIDDefine( nScrollbarID)  ScrollBarStyle_t    eScrollbar;


/* View */
#define	WndSetTitleVisiableRC(...)	PropIDDefine( nTitleVisID)	boolean	bTitleVis;
#define	WndSetStatusBarVisibleRC(...)	PropIDDefine( nSBVisID)	boolean	bSBVis;
#define	WndSetSoftkeyVisibleRC(...)	PropIDDefine( nSKVisID)	boolean	bSKVis;
#define	WndSetStatusBarTransparencyRC(...)	PropIDDefine( nSBTranID)	boolean	bSBTran;
#define	WndSetSoftkeyTransparencyRC(...)	PropIDDefine( nSKTranID)	boolean	bSKTran;
#define	WndSetTitleRC(...)	PropIDDefine( nTitleID)	TitleVar_t	tTitle;
#define	WndSetBgPosRC(...)	PropIDDefine( nBgPosID)	WdgBackgroundPos_et	tBgPos;
#define	WndSetBgColorRC(...)	PropIDDefine( nBgClrID)	RGBColor_t	tBgClr;
#define WndSetAllSoftkeyRC(...) PropIDDefine( nAllSkID) AllSoftkeyVar_t tAllSk;


/* Button Widget */
#define	WdgButtonSetDisDisplayTextRC(...)	PropIDDefine( nDisDisaplyTxtID)	boolean	bDisDisaplyTxt;
#define	WdgButtonSetUnpressedTextColorRC(...)	PropIDDefine( nUnPresTxtClrID)	RGBColor_t	tUnPresTxtClr;
#define	WdgButtonSetUnpressedTextOutlineColorRC(...)	PropIDDefine( nUnPresTxtOutClrID)	RGBColor_t	tUnPresTxtOutClr;
#define	WdgButtonSetPressedTextColorRC(...)	PropIDDefine( nPresTxtClrID)	RGBColor_t	tPresTxtClr;
#define	WdgButtonSetPressedTextOutlineColorRC(...)	PropIDDefine( nPresTxtOutClrID)	RGBColor_t	tPresTxtOutClr;


/* Image */
#define	WdgImageSetFrameWidthRC(...)	PropIDDefine( nFrmWID)	u32	nFrmW;
#define	WdgImageSetFrameIntervalRC(...)	PropIDDefine( nFrmItvlID)	u32	nFrmItvl;
#define	WdgImageSetAutoFitRC(...)	PropIDDefine( nAutoFitID)	ImgWdgAutoFit_t	tAutoFit;
#define	WdgImageSetEnableUpscaleRC(...)	PropIDDefine( nEnbUpsclID)	boolean	bEnbUpscl;
#define	WdgImageSetEnablePartialDecodeRC(...)	PropIDDefine( nEnbPtlDceID)	boolean	bEnbPtlDce;
#define	WdgImageSetEnableDefaultImageRC(...)	PropIDDefine( nEnbDefImgID)	boolean	bEnbDefImg;
#define	WdgImageSetDefaultImageIDRC(...)	PropIDDefine( nDefImgIdID)	u32	bDefImgId;
#define	WdgImageSetImageScaleRotateRC(...)	PropIDDefine( nImgSaeRteID)	ImgScaleRotate_t	tImgSaeRte;

/* OverlayImage */
#define WdgOverlayImageSetDataByIDRC(aryNum,...)	PropIDDefine( nDataIDID)	WdgOverlayImageDataID_t	tOverlayImageDataID[aryNum];

/* Text Widget */
#define	WdgTextSetFontHeightRC(...)	PropIDDefine(nFntHID)	u32	nFntH;
#define	WdgTextSetTextOutlineColorRC(...)	PropIDDefine(nTxtOutClrID)	RGBColor_t	tTxtOutClr;
#define	WdgTextSetHighlightTextOutlineColorRC(...)	PropIDDefine(nHltTxtOutClrID)	RGBColor_t	tHltTxtOutClr;
#define	WdgTextSetHighlightBGColorRC(...)	PropIDDefine(nHltBgClrID)	RGBColor_t	tHltBgClr;
#define	WdgTextSetSlideDirectionRC(...)	PropIDDefine( nSldDirID)	SlideDirection_t	eSldDir;
#define	WdgTextSetSlideStepOffsetRC(...)	PropIDDefine( nSldStpOstID)	s32	nSldStpOst;
#define	WdgTextSetSlideStepTimeRC(...)	PropIDDefine( nSldStpTimeID)	s32	nSldStpTime;
#define	WdgTextSetEnableAnimateRC(...)	PropIDDefine( nEnbAmeID)	boolean	bEnbAme;
#define	WdgTextSetSlideOnOffRC(...)	PropIDDefine( nsldOnOffID)	boolean	bsldOnOff;
#define	WdgTextSetSlideAutoRepeatRC(...)	PropIDDefine( nSldAtoRptID)	boolean	bSldAtoRpt;
#define	WdgTextSetSlideStyleRC(...)	PropIDDefine( nSldStlID)	SlideStyle_t	eSldStl;
#define	WdgTextSetLayoutFlagRC(...)	PropIDDefine( nLayflgID)	TextLayout_t	eLayflg;
#define	WdgTextSetFcsItemBGColorRC(...)	PropIDDefine( nFcsItmBgClrID)	RGBColor_t	tFcsItmBgClr;

/* Input */
#define	WdgInputSetDecimalPointEnableRC(...)	PropIDDefine( nDclPitEnbID)	 boolean	bDclPitEnb;
#define	WdgInputSetFirstKeyPressRC(...)	PropIDDefine( nFstKeyPrsID)	u32	nFstKeyPrs;
#define	WdgInputSetFontSizeRC(...)	PropIDDefine( nFntSizeID)	FontCategory_t	tFntSize;
#define	WdgInputSetFontTypeRC(...)	PropIDDefine( nFntTypeID)	FontType_t	tFontType;
#define	WdgInputSetHandWritingEnableRC(...)	PropIDDefine( nHndWriEnbID)	boolean	bHndWriEnb;
#define	WdgInputSetHighlightBGColorRC(...)	PropIDDefine( nHltBgClrID)	RGBColor_t	tHltBgClr;
#define	WdgInputSetHighlightTextColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtColor;
#define	WdgInputSetLineGapRC(...)	PropIDDefine( nLineGapID)	u32	nLineGap;
#define	WdgInputSetMaxByteLengthRC(...)	PropIDDefine( nMaxByteLenID)	u32	nMaxByteLen;
#define	WdgInputSetMaxlenAfterDecimalPointRC(...)	PropIDDefine( nMaxLenAftDecPntID)	u8	nMaxLenAftDecPnt;
#define	WdgInputSetMaxlenAfterExponentRC(...)	PropIDDefine( nMaxLenAftExpID)	u8	nMaxLenAftExp;
#define	WdgInputSetMultilineRC(...)	PropIDDefine( nMultilineID)	boolean	bMultiline;
#define	WdgInputSetPasswordStyleRC(...)	PropIDDefine( nPwdStlID)	boolean	bPwdStl;
#define	WdgInputSetShowBorderWhenLoseFocusRC(...)	PropIDDefine( nShowBdrLosFusID)	boolean	bShowBdrLosFus;
#define	WdgInputSetSmartInputOffRC(...)	PropIDDefine( nSmtInpOffID)	boolean	bSmtInpOff;
#define	WdgInputSetSoftKeyBoardEnableRC(...)	PropIDDefine( nSKeyBdrEnbID)	boolean	bSKeyBdrEnb;
#define	WdgInputSetTextColorRC(...)	PropIDDefine( nTxtClrID)	RGBColor_t	tTxtColor;
#define	WdgInputSetInitTextRC(...)	PropIDDefine( nInitTxtID)	MAE_Wchar  [128]	pInitTxt;
#define	WdgInputSetCursorColorRC(...)	PropIDDefine( nCusClrID)	RGBColor_t	tCusClr;
#define	WdgInputSetCurrentInputLanguageRC(...)	PropIDDefine( nCutInpLngID)	u32	nCutInpLng;
#define	WdgInputSetDisableSymbolTableRC(...)	PropIDDefine( nDisSblTblID)	boolean	bDisSblTbl;
#define	WdgInputSetDisableSwitchInputModeRC(...)	PropIDDefine( nDisSthInpModID)	boolean	bDisSthInpMod;
#define	WdgInputSetChineseInputOffRC(...)	PropIDDefine( nCnsInpOffID)	boolean	bCnsInpOff;
#define	WdgInputSetLineFeedDisableRC(...)	PropIDDefine( nLineFedDisID)	boolean	bLineFedDis;
#define	WdgInputSetDialingShiftOldestCharRC(...)	PropIDDefine( nDialShtOldChID)	boolean	bDialShtOldCh;
#define	WdgInputSetModeMaskRC(...)	PropIDDefine( nModeMaskID)	u32	nModeMask;
#define	WdgInputSetCurrentInputModeRC(...)	PropIDDefine( nCutiInpModeID)	u32	nCutiInpMode;



/* Tab */
#define	WdgTabSetModeRC(...)	PropIDDefine( nModeID)	TabWdgMode_e	eMode;
#define	WdgTabSetActiveWidthRC(...)	PropIDDefine( nActWID)	u16	nActW;
#define	WdgTabSetInactiveWidthRC(...)	PropIDDefine( nInActWID)	u32	nInActW;
#define	WdgTabSetTabHeightRC(...)	PropIDDefine( nTabHID)	u32	nTabH;
#define	WdgTabSetTabHeightOffsetRC(...)	PropIDDefine( nTabHOsetID)	u16	nTabHOset;
#define	WdgTabSetTabPaddingLeftRC(...)	PropIDDefine( nTabPadLeftID)	u8	nTabPadLeft;
#define	WdgTabSetTabPaddingRightRC(...)	PropIDDefine( nTabPadRhtID)	u8	nTabPadRht;
#define	WdgTabSetTabGapRC(...)	PropIDDefine( nTabGapID)	u16	nTabGap;


/* Switch Icon */
#define	WdgSwitchIconSetIconStyleRC(...)	PropIDDefine( nIconStlID)	Icon_Style_et	eIconStyle;


/* Progress */
#define	WdgProgressSetRepeatRC(...)	PropIDDefine( nRepeatID)	boolean	bRepeat;
#define	WdgProgressSetFgBorderColorRC(...)	PropIDDefine( nFgBdrClrID)	RGBColor_t	tFgBdrClr;
#define	WdgProgressSetBgBorderColorRC(...)	PropIDDefine( nBgBdrClrID)	RGBColor_t	tBgBdrClr;
#define	WdgProgressSetFgFillColorRC(...)	PropIDDefine( nFgFilClrID)	RGBColor_t	tFgFilClr;
#define	WdgProgressSetBgFillColorRC(...)	PropIDDefine( nBgFilClrID)	RGBColor_t	tBgFilClr;
#define	WdgProgressSetFgRectFlagRC(...)	PropIDDefine( nFgRctFlgID)	u32	nFgRctFlg;
#define	WdgProgressSetBgRectFlagRC(...)	PropIDDefine( nBgRctFlgID)	u32	nBgRctFlg;
#define	WdgProgressSetTotalRC(...)	PropIDDefine( nTotalID)	u16	nTotal;
#define	WdgProgressSetCurPosRC(...)	PropIDDefine( nCurPosID)	u16	nCurPos;
#define	WdgProgressSetPreferCellWidthRC(...)	PropIDDefine( nPfrCellWID)	u16	nPfrCellW;
#define	WdgProgressSetPreferCellTotalNumRC(...)	PropIDDefine( nPfrCelTtlNumID)	u16	nPfrCelTtlNum;
#define	WdgProgressSetPreferCellRepeatlNumRC(...)	PropIDDefine( nPfrCelRptNumID)	u16	nPfrCelRptNum;
#define	WdgProgressSetAutoOnOffRC(...)	PropIDDefine( nAutoOnOffID)	boolean	bAutoOnOff;


/* IP Widget */
#define	WdgIPCommonSetFontRC(...)	PropIDDefine( nFontID)	WdgIPFont_t	tFont;
#define	WdgIPSetHighlightBGColorRC(...)	PropIDDefine( nHltBgClrID)	RGBColor_t	tHltBgClr;
#define	WdgIPSetHighlightTextColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtColor;
#define	WdgIPSetIPValueRC(...)	PropIDDefine( nIPValID)	u32	nIPVal;



/* Fadeout Widget */
#define	WdgFadeoutSetFoLevelRC(...)	PropIDDefine( nFoLvlID)	FadeoutLevel_t	tFoLvl;


/* PullDown Widget */
#define	WdgPullDownSetFocusIndexRC(...)	PropIDDefine( nFcsIdxID)	u32	nFcsIdx;
#define	WdgPullDownSetLayoutModeRC(...)	PropIDDefine( nLayModeID)	PullDownWdgMode_et	tLayMode;
#define	WdgPullDownSetNaviUpKeyRC(...)	PropIDDefine( nNaviUpKeyID)	MAE_Key_t	tNaviUpKey;
#define	WdgPullDownSetNaviDownKeyRC(...)	PropIDDefine( nNaviDwnKeyID)	MAE_Key_t	tNaviDwnKey;
#define	WdgPullDownSetToggleListKeyRC(...)	PropIDDefine( nTglLstKeyID)	MAE_Key_t	tTglLstKey;
#define	WdgPullDownSetArrowWidthRC(...)	PropIDDefine( nArrWID)	u32	nArrW;
#define	WdgPullDownSetTextColorRC(...)	PropIDDefine( nTxtClrID)	RGBColor_t	tTxtColor;
#define	WdgPullDownSetHighlightTextColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtColor;
#define	WdgPullDownSetHighlightBgColorRC(...)	PropIDDefine( nHltBgClrID)	RGBColor_t	tHltBgClr;
#define	WdgPullDownSetListBorderColorRC(...)	PropIDDefine( nListBdrClrID)	RGBColor_t	tListBdrClr;


/* Indicator Widget */
#define	WdgIndicatorSetLayoutStyleRC(...)	PropIDDefine( nLayStlID)	WdgLayoutStyle_t	eLayStl;
#define	WdgIndicatorSetFGTopOffsetRC(...)	PropIDDefine( nFgTopOstID)	u8	nFgTopOst;
#define	WdgIndicatorSetFGBottomOffsetRC(...)	PropIDDefine( nFgBtmOstID)	u8	nFgBtmOst;
#define	WdgIndicatorSetFGLeftOffsetRC(...)	PropIDDefine( nFgLeftOstID)	u8	nFgLeftOst;
#define	WdgIndicatorSetFGRightOffsetRC(...)	PropIDDefine( nRgtOstID)	u8	nRgtOst;
#define	WdgIndicatorSetINDOffsetRC(...)	PropIDDefine( nIndOstID)	u8	nIndOst;
#define	WdgIndicatorSetINDImageIDRC(...)	PropIDDefine( nIndImgIdID)	u32	nIndImgId;
#define	WdgIndicatorSetFGImageIDRC(...)	PropIDDefine( nFgImgIdID)	u32	nFgImgId;
#define	WdgIndicatorSetBGImageIDRC(...)	PropIDDefine( nBgImgIdID)	u32	nIndBgImgId;

#define	WdgIndicatorSetDWNTopOffsetRC(...)	    PropIDDefine( nDWNTopOstID)	    u8	nDWNTopOst;
#define	WdgIndicatorSetDWNBottomOffsetRC(...)	PropIDDefine( nDWNBtmOstID)	    u8	nDWNBtmOst;
#define	WdgIndicatorSetDWNLeftOffsetRC(...)	    PropIDDefine( nDWNLeftOstID)	u8	nDWNLeftOst;
#define	WdgIndicatorSetDWNRightOffsetRC(...)	PropIDDefine( nDWNRgtOstID)	    u8	nDWNRgtOst;
#define	WdgIndicatorSetDWNEndOffsetRC(...)	    PropIDDefine( nDWNEndOstID)	    u8	nDWNEndOst;
#define	WdgIndicatorSetDWNImageIDRC(...)	    PropIDDefine( nDWNImgIdID)	    u32	nDWNImgId;
#define	WdgIndicatorSetDWNENDImageIDRC(...)	    PropIDDefine( nDWNEndImgIdID)	u32	nDWNEndImgId;


/* Viewport Widget */
#define	WdgViewportSetLockVerMoveRC(...)	PropIDDefine( nLckVerMoveID)	boolean	bLckVerMove;
#define	WdgViewportSetLockHoriMoveRC(...)	PropIDDefine( nLckHoriMoveID)	boolean	bLckHoriMove;
#define	WdgViewportSetKeepCenterRC(...)	PropIDDefine( nKepCtrID)	boolean	bKepCtr;
#define	WdgViewportSetPanStepRC(...)	PropIDDefine( nPanStpID)	u16	nPanStp;
#define	WdgViewportSetCurrentYOffsetRC(...)	PropIDDefine( nCurYOstID)	u16	nCurYOst;
#define	WdgViewportSetCurrentXOffsetRC(...)	PropIDDefine( nCurXOstID)	u16	nCurXOst;


/* Time Widget */
#define	WdgTimeSetEnableAdjustValueByNaviUpDownRC(...)	PropIDDefine( nEnbAdjValID)	boolean	bEnbAdjVal;
#define	WdgTimeSetEnableSecondFieldRC(...)	PropIDDefine( nEnbScdFldID)	boolean	bEnbScdFld;
#define	WdgTimeSetHourFormatRC(...)	PropIDDefine( nHurFmtID)	boolean	bHurFmt;
#define	WdgTimeSetHighlightTextColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtColor;
#define	WdgTimeSetHighlightBGColorRC(...)	PropIDDefine( nHltBgClrID)	RGBColor_t	tHltBgClr;


/* FcDate Widget */
#define	WdgFcDateSetMaxYearRC(...)	PropIDDefine( nMaxYearID)	u32	nMaxYear;
#define	WdgFcDateSetMinYearRC(...)	PropIDDefine( nMinYearID)	u32	nMinYear;
#define	WdgFcDateSetFocusIndRC(...)	PropIDDefine( nFusIndID)	_FCDIndType_t	eFusInd;


/* Date Widget */
#define	WdgDateSetEnableAdjustValueByNaviUpDownRC(...)	PropIDDefine( nEnbAdjValID)	boolean	bEnbAdjVal;
#define	WdgDateSetHighlightBGColorRC(...)	PropIDDefine( nHltTxtClrID)	RGBColor_t	tHltTxtColor;
#define	WdgDateSetHighlightTextColorRC(...)	PropIDDefine( nHltBgClrID)	RGBColor_t	tHltBgClr;
#define	WdgDateSetMaxYearRC(...)	PropIDDefine( nMaxYearID)	u16	nMaxYear;
#define	WdgDateSetMinYearRC(...)	PropIDDefine( nMinYearID)	u16	nMinYear;



/* FcTime Widget */


/* Menu Widget */
#define	WdgMenuSetItemFocusImageRC(...)	PropIDDefine( nFcsImgID)	u32	nFcsImg;
#define	WdgMenuSetItemUnFocusImageRC(...)	PropIDDefine( nUnFcsImgID)	u32	nUnFcsImg;
#define	WdgMenuSetRollTypeRC(...)	PropIDDefine( nRollTypeID)	WdgMenuRollType_t	eRollType;
#define	WdgMenuSetCheckStyleRC(...)	PropIDDefine( nChkStlID)	WdgMenuCheckStyle_t	eChkStl;
#define	WdgMenuSetMenuBGImageRC(...)	PropIDDefine( nMenuBgImgID)	u32	nMenuBgImg;
#define	WdgStaticMenuInitRC(...)	PropIDDefine( nItemTypeID)	WdgMenuItemType_t	eItemType;
#define	WdgMenuSetFirstItemRC(...)	PropIDDefine( nFirstItemID)	u32	nFirstItem;
#define	WdgMenuSetHighlightedItemRC(...)	PropIDDefine( nSelectedItemID)	u32	nSelectedItem;
#define WdgMenuSetToGridStyleRC(...) PropIDDefine( nGridStlID)	WdgGridStyleInfo_t	tGridStl;
#define WdgMenuSetItemWidthRC(...)	PropIDDefine( nMenuItemWID)	u16 nMenuItemW;
#define WdgMenuSetItemHeightRC(...) PropIDDefine( nMenuItemHID)	u16 nMenuItemH;
#define WdgMenuSetRowGapRC(...)		PropIDDefine( nItemRowGapID)	u16 nItemRowGap;
#define WdgMenuSetColGapRC(...)		PropIDDefine( nItemColGapID)	u16 nItemColGap;
#define WdgMenuSetFixedNumRC(...)   PropIDDefine( nFixedNumID)	u16 nFixedNum;

/* Image Text Image Widget */
#define WdgITISetPreImageWidthRC(...)       PropIDDefine( nPreImageWidth) u16 nPreImageWidth;
#define WdgITISetPreImagePrePaddingRC(...)  PropIDDefine( nPreImagePrePadding) u16 nPreImagePrePadding;
#define WdgITISetTextPrePaddingRC(...)      PropIDDefine( nTextPrePadding) u16 nTextPrePadding;

/* Pick Widget */
#define	WdgPickSetInvisibleIfDisableRC(...)	PropIDDefine( nInVisDisID)	boolean	bInVisDis;
#define	WdgPickSetFocusIndexRC(...)	PropIDDefine( nFcsIdxID)	u32	nFcsIdx;
#define	WdgPickSetLayoutStyleRC(...)	PropIDDefine( nLayStlID)	WdgLayoutStyle_t	eLayStl;
#define	WdgPickSetArrowInsideRC(...)	PropIDDefine( nArrIsdID)	boolean	bArrIsd;

/* Common Pick Widget */
#define	WdgCommonPickSetInvisibleIfDisableRC(...)	PropIDDefine( nInvisDisID)	boolean	bInvisDis;
#define	WdgCommonPickSetFocusIndexRC(...)	PropIDDefine( nFcsIdxID)	u32	nFcsIdx;
#define	WdgCommonPickSetLayoutStyleRC(...)	PropIDDefine( nLayStlID)	WdgLayoutStyle_t	eLayStl;
#define	WdgCommonPickSetArrowInsideRC(...)	PropIDDefine( nArrIsdID)	boolean	bArrIsd;


/* Double Widget */
#define	WdgDoubleItemSetDisableDownWidgetBGRC(...)	PropIDDefine( nDisDownWdgBgID)	boolean	bDisDownWdgBg;
#define	WdgDoubleItemSetTextOutlineColorRC(...)	PropIDDefine( nTxtOutClrID)	RGBColor_t	tTxtOutClr;
#define	WdgDoubleItemSetHighlightedTextOutlineColorRC(...)	PropIDDefine( nHltTxtOutClrID)	RGBColor_t	tHltTxtOutClr;
#define	WdgDoubleItemSetSlideOnOffRC(...)	PropIDDefine( nSldOnOffID)	boolean	bSldOnOff;


#define RSCustomize(type,name, ...) type name;

#define WdgStatusPageDefRC(IconNum,...) StatusPageWdgDef_t tSPLayoutWdgDef[IconNum];
