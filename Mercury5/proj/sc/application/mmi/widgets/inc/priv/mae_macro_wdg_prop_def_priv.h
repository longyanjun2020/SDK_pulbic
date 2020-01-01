
/* widget default */
#define	WdgAbsDefRC(...)	AbscontainerWdgtDef_t	tAbsWdgDef;
#define	WdgViewportDefRC(...)	ViewportWdgtDef_t	tViewportWdgDef;
#define	WdgButtonDefRC(...)	ButtonWdgtDef_t	tButtonWdgDef;
#define	WdgImageDefRC(...)	ImageWdgtDef_t	tImageWdgDef;
#define	WdgOverlayImageDefRC(...)	OverlayImageWdgtDef_t	tOverlayImageWdgDef;
#define	WdgTextDefRC(...)	TextWdgDef_t	tTextWdgDef;
#define	WdgInputDefRC(...)	InputWdgDef_t	tInputWdgDef;
#define	WdgTabDefRC(...)	TabWdgDef_t	tTabWdgDef;
#define	WdgSwitchIconDefRC(...)	SwitchIconWdgDef_t	tSwitchIconWdgDef;
#define	WdgSwitchIconItemDefRC(...) SwitchIconItemWdgDef_t tSwitchIconItemWdgDef;
#define	WdgProgressDefRC(...)	ProgressWdgDef_t	tProgressWdgDef;
#define	WdgFadeoutDefRC(...)	FadeoutWdgDef_t	tFadeoutWdgDef;
#define	WdgIndicatorDefRC(...)	IndicatorWdgDef_t	tIndicatorWdgDef;
#define	WdgTextBubbleDefRC(...)	TextBubbleWdgDef_t	tTextBubbleWdgDef;
#define	WdgFcDateDefRC(...)	FcDateWdgDef_t	tFcDateWdgDef;
#define	WdgDateDefRC(...)	DateWdgDef_t	tDateWdgDef;
#define	WdgFcTimeDefRC(...)	FcTimeWdgDef_t	tFcTimeWdgDef;
#define	WdgMenuDefRC(...)	MenuWdgDef_t	tMenuWdgDef;
#define	WdgPickDefRC(...)	PickWdgDef_t	tPickWdgDef;
#define	WdgL2InfoPickDefRC(...)	L2InfoPickTxtWdgDef_t	tL2InfoPickWdgDef;
#define	WdgTxtPickImgTxtDefRC(...)	TxtPickImgTxtWdgDef_t	tTxtPickImgTxtWdgDef;
#define	WdgTxtPickTxtDefRC(...)	TxtPickTxtWdgDef_t	tTxtPickTxtWdgDef;
#define	WdgImgTxtPickImgTxtDefRC(...)	ImgTxtPickImgTxtWdgDef_t	tImgTxtPickTxtWdgDef;
#define	WdgFormatInpDefRC(...)	FormatInputWdgDef_t	tFormatInpWdgDef;
#define	WdgGridBaseDefRC(...)	GridBaseWdgDef_t	tGridBaseWdgDef;

#ifdef __HANDWRITING_MMI__
#define	WdgHandwriteDefRC(...)	HandwriteWdgDef_t	tHandwriteWdgDef;
#else
#define	WdgHandwriteDefRC(...)
#endif

#define	WdgImeAssistDefRC(...)	ImeAssistWdgDef_t	tImeAssistWdgDef;
#define	WdgListDefRC(...)	ListWdgDef_t	tListWdgDef;
#define	WdgScrollbarDefRC(...)	ScrollbarWdgDef_t	tScrollbarWdgDef;
#define	WdgScrollIndDefRC(...)	ScrollIndicatorWdgDef_t	tScrollIndWdgDef;
#define	WdgTitleDefRC(...)	TitleWdgDef_t	tTitleWdgDef;
#define	WdgMflDefRC(...)	MflcontainerWdgDef_t	tMflWdgDef;
#define	WdgOpMenuDefRC(...)	OpMenuWdgDef_t	tOpMenuWdgDef;
#define	WdgPopUpSelDefRC(...)	PopUpSelectWdgDef_t	tPopUpSelWdgDef;
#define	WdgShortcutBarDefRC(...)	ShortcutBarWdgDef_t	tShortcutWdgDef;
#define	WdgSlideSwDefRC(...)	SlideSwitchWdgDef_t	tSlideSwWdgDef;
#define	WdgPropDefRC(...)	PropcontainerWdgDef_t	tPropWdgDef;
#define	WdgTimerFormatDefRC(...)	TimerFormatWdgDef_t	tTimerFormatWdgDef;
#define	WdgTransitionDefRC(...)	TransitionWdgDef_t	tTransitionWdgDef;
#define	WdgVolumeDefRC(...)	VolumeWdgDef_t	tVolumeWdgDef;
#define	WdgImgTextDefRC(...)	ImageTextWdgDef_t	tImgTextWdgDef;
#define	WdgImgTextImgDefRC(...)	ImageTextImageWdgDef_t	tImgTextImgWdgDef;
#define	WdgTextImgDefRC(...)	TextImageWdgDef_t	tTextImgWdgDef;
#define	WdgTxtL2InfoDefRC(...)	DoubleItemWdgL2I_t	tTxtL2InfoWdgDef;
#define	WdgDbTxtInputDefRC(...)	DoubleItemWdgPlusSpace_t	tDbTxtInputWdgDef;
#define	WdgDbTextDefRC(...)	DoubleItemWdgComm_t	tDbTextWdgDef;
#define	WdgITSTextDefRC(...)	DoubleItemWdgComm_t	tITSTextWdgDef;
#define	WdgITSInputDefRC(...)	DoubleItemWdgPlusSpace_t	tITSInputWdgDef;
#define	WdgDbTxtDateDefRC(...)	DoubleItemWdgPlusSpace_t	tDbTxtDateWdgDef;
#define	WdgDbTxtTimeDefRC(...)	DoubleItemWdgPlusSpace_t	tDbTxtTimeWdgDef;
#define	WdgITSITDefRC(...)	DoubleItemWdgComm_t	tITSITWdgDef;
#define	WdgITSTIDefRC(...)	DoubleItemWdgComm_t	tITSTIWdgDef;
#define	WdgTextIPDefRC(...)	DoubleItemWdgPlusSpace_t	tTextIPWdgDef;
#define WdgStatusBarDefRC(IconNum,...) StatusBarWdgDef_t tSBLayoutWdgDef[IconNum];
#define	WdgSoftkeyboardDefRC(...)	SoftkeyboardWdgDef_t	tSKWdgDef;
#define WdgSoftkeyDefRC(...)  SoftkeyWdgDef_t tSoftkeyDef;
#define WdgCanvasDefRC(...)  CanvasWdgDef_t tCanvasDef;

#define WdgInputControllerMenuItemNumRC(...) s32 nMenuItemNum;
#define WdgInputControllerMenuItemRC(firstDimNum, ...) u32 nMenuItem[firstDimNum][7];
#define WdgInputControllerCopyModeItemNumRC(...) s32 nCpModeItemNum;
#define WdgInputControllerCopyModeRC(firstDimNum, ...) u32 nCopyMode[firstDimNum][7];
#define WdgInputControllerSmartOnOffItemNumRC(...) s32 nOnOffItemNum;
#define WdgInputControllerSmartOnOffRC(firstDimNum, ...) u32 nSmartOnOff[firstDimNum][7];


//
//Softkeyboard data
//
#define	WdgSoftkeyboardCnStrokeItemNumRC(...)   s32 nCnStrokeNum;
#define	WdgSoftkeyboardCnStrokeRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nCnStroke[firstDimNum];
#define	WdgSoftkeyboardEnCapitalItemNumRC(...)   s32 nEnCapitalNum;
#define	WdgSoftkeyboardEnCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nEnCapital[firstDimNum];
#define	WdgSoftkeyboardEnLcItemNumRC(...)   s32 nEnLcNum;
#define	WdgSoftkeyboardEnLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nEnLc[firstDimNum];
#define	WdgSoftkeyboardSymbolItemNumRC(...)   s32 nSymbolNum;
#define	WdgSoftkeyboardSymbolRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nSymbol[firstDimNum];
#define	WdgSoftkeyboardCnPinyinItemNumRC(...)   s32 nCnPinyinNum;
#define	WdgSoftkeyboardCnPinyinRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nCnPinyin[firstDimNum];
#define	WdgSoftkeyboardCnBpmfItemNumRC(...)   s32 nCnBpmfNum;
#define	WdgSoftkeyboardCnBpmfRC(firstDimNum, ...)  SoftKeyBoardWidget_VectorModelData_t nCnBpmf[firstDimNum];
#define	WdgSoftkeyboardNumericItemNumRC(...)   s32 nNumericNum;
#define	WdgSoftkeyboardNumericRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nNumeric[firstDimNum];
#define	WdgSoftkeyboardFormatInputItemNumRC(...)   s32 nFormatInputNum;
#define	WdgSoftkeyboardFormatInputRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nFormatInput[firstDimNum];
#define	WdgSoftkeyboardRateItemNumRC(...)   s32 nRateNum;
#define	WdgSoftkeyboardRateRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nRate[firstDimNum];
#define	WdgSoftkeyboardPinItemNumRC(...)   s32 nPinNum;
#define	WdgSoftkeyboardPinRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPin[firstDimNum];
#define	WdgSoftkeyboardDialingItemNumRC(...)   s32 nDialingNum;
#define	WdgSoftkeyboardDialingRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nDialing[firstDimNum];
#define	WdgSoftkeyboardEsCapitalItemNumRC(...)   s32 nEsCapitalNum;
#define	WdgSoftkeyboardEsCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nEsCapital[firstDimNum];
#define	WdgSoftkeyboardEsLcItemNumRC(...)   s32 nEsLcNum;
#define	WdgSoftkeyboardEsLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nEsLc[firstDimNum];
#define	WdgSoftkeyboardFrCapitalItemNumRC(...)   s32 nFrCapitalNum;
#define	WdgSoftkeyboardFrCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nFrCapital[firstDimNum];
#define	WdgSoftkeyboardFrLcItemNumRC(...)   s32 nFrLcNum;
#define	WdgSoftkeyboardFrLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nFrLc[firstDimNum];
#define	WdgSoftkeyboardVnCapitalItemNumRC(...)   s32 nVnCapitalNum;
#define	WdgSoftkeyboardVnCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nVnCapital[firstDimNum];
#define	WdgSoftkeyboardVnLcItemNumRC(...)   s32 nVnLcNum;
#define	WdgSoftkeyboardVnLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nVnLc[firstDimNum];
#define	WdgSoftkeyboardPtCapitalItemNumRC(...)   s32 nPtCapitalNum;
#define	WdgSoftkeyboardPtCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPtCapital[firstDimNum];
#define	WdgSoftkeyboardPtLcItemNumRC(...)   s32 nPtLcNum;
#define	WdgSoftkeyboardPtLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPtLc[firstDimNum];
#define	WdgSoftkeyboardRuCapitalItemNumRC(...)   s32 nRuCapitalNum;
#define	WdgSoftkeyboardRuCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nRuCapital[firstDimNum];
#define	WdgSoftkeyboardRuLcItemNumRC(...)   s32 nRuLcNum;
#define	WdgSoftkeyboardRuLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nRuLc[firstDimNum];
#define	WdgSoftkeyboardTrCapitalItemNumRC(...)   s32 nTrCapitalNum;
#define	WdgSoftkeyboardTrCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTrCapital[firstDimNum];
#define	WdgSoftkeyboardTrLcItemNumRC(...)   s32 nTrLcNum;
#define	WdgSoftkeyboardTrLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTrLc[firstDimNum];
#define	WdgSoftkeyboardThCapitalItemNumRC(...)   s32 nThCapitalNum;
#define	WdgSoftkeyboardThCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nThCapital[firstDimNum];
#define	WdgSoftkeyboardThLcItemNumRC(...)   s32 nThLcNum;
#define	WdgSoftkeyboardThLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nThLc[firstDimNum];
#define	WdgSoftkeyboardArabicItemNumRC(...)   s32 nArabicNum;
#define	WdgSoftkeyboardArabicRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nArabic[firstDimNum];
#define	WdgSoftkeyboardPersianItemNumRC(...)   s32 nPersianNum;
#define	WdgSoftkeyboardPersianRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPersian[firstDimNum];
#define WdgSoftkeyboardGMCapitalItemNumRC(...)   s32 nGMCapitalNum;
#define	WdgSoftkeyboardGMCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nGMCapital[firstDimNum];
#define WdgSoftkeyboardGMLcItemNumRC(...)   s32 nGMLcNum;
#define	WdgSoftkeyboardGMLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nGMLc[firstDimNum];
#define WdgSoftkeyboardITCapitalItemNumRC(...)   s32 nITCapitalNum;
#define	WdgSoftkeyboardITCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nITCapital[firstDimNum];
#define WdgSoftkeyboardITLcItemNumRC(...)   s32 nITLcNum;
#define	WdgSoftkeyboardITLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nITLc[firstDimNum];
#define WdgSoftkeyboardHindiCapitalItemNumRC(...)   s32 nHindiCapitalNum;
#define	WdgSoftkeyboardHindiCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nHindiCapital[firstDimNum];
#define WdgSoftkeyboardHindiLcItemNumRC(...)   s32 nHindiLcNum;
#define	WdgSoftkeyboardHindiLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nHindiLc[firstDimNum];
#define WdgSoftkeyboardTamil1ItemNumRC(...)   s32 nTamil1Num;
#define	WdgSoftkeyboardTamil1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTamil1[firstDimNum];
#define WdgSoftkeyboardTamil2ItemNumRC(...)   s32 nTamil2Num;
#define	WdgSoftkeyboardTamil2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTamil2[firstDimNum];
#define WdgSoftkeyboardTelugu1ItemNumRC(...)   s32 nTelugu1Num;
#define	WdgSoftkeyboardTelugu1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTelugu1[firstDimNum];
#define WdgSoftkeyboardTelugu2ItemNumRC(...)   s32 nTelugu2Num;
#define	WdgSoftkeyboardTelugu2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nTelugu2[firstDimNum];
#define WdgSoftkeyboardBurmese1ItemNumRC(...)   s32 nBurmese1Num;
#define	WdgSoftkeyboardBurmese1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nBurmese1[firstDimNum];
#define WdgSoftkeyboardBurmese2ItemNumRC(...)   s32 nBurmese2Num;
#define	WdgSoftkeyboardBurmese2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nBurmese2[firstDimNum];
#define WdgSoftkeyboardPunjabi1ItemNumRC(...)   s32 nPunjabi1Num;
#define	WdgSoftkeyboardPunjabi1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPunjabi1[firstDimNum];
#define WdgSoftkeyboardPunjabi2ItemNumRC(...)   s32 nPunjabi2Num;
#define	WdgSoftkeyboardPunjabi2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPunjabi2[firstDimNum];
#define	WdgSoftkeyboardUrdu1ItemNumRC(...)   s32 nUrdu1Num;
#define	WdgSoftkeyboardUrdu1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nUrdu1[firstDimNum];
#define	WdgSoftkeyboardUrdu2ItemNumRC(...)   s32 nUrdu2Num;
#define	WdgSoftkeyboardUrdu2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nUrdu2[firstDimNum];
#define	WdgSoftkeyboardBengali1ItemNumRC(...)   s32 nBengali1Num;
#define	WdgSoftkeyboardBengali1RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nBengali1[firstDimNum];
#define	WdgSoftkeyboardBengali2ItemNumRC(...)   s32 nBengali2Num;
#define	WdgSoftkeyboardBengali2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nBengali2[firstDimNum];
#define	WdgSoftkeyboardCzechCapitalItemNumRC(...)   s32 nCzechCapitalNum;
#define	WdgSoftkeyboardCzechCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nCzechCapital[firstDimNum];
#define	WdgSoftkeyboardCzechLcItemNumRC(...)   s32 nCzechLcNum;
#define	WdgSoftkeyboardCzechLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nCzechLc[firstDimNum];
#define	WdgSoftkeyboardGreekCapitalItemNumRC(...)   s32 nGreekCapitalNum;
#define	WdgSoftkeyboardGreekCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nGreekCapital[firstDimNum];
#define	WdgSoftkeyboardGreekLcItemNumRC(...)   s32 nGreekLcNum;
#define	WdgSoftkeyboardGreekLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nGreekLc[firstDimNum];
#define	WdgSoftkeyboardPlCapitalItemNumRC(...)   s32 nPlCapitalNum;
#define	WdgSoftkeyboardPlCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPlCapital[firstDimNum];
#define	WdgSoftkeyboardPlLcItemNumRC(...)   s32 nPlLcNum;
#define	WdgSoftkeyboardPlLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nPlLc[firstDimNum];
#define	WdgSoftkeyboardNlCapitalItemNumRC(...)   s32 nNlCapitalNum;
#define	WdgSoftkeyboardNlCapitalRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nNlCapital[firstDimNum];
#define	WdgSoftkeyboardNlLcItemNumRC(...)   s32 nNlLcNum;
#define	WdgSoftkeyboardNlLcRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nNlLc[firstDimNum];
#define	WdgSoftkeyboardSmartItemNumRC(...)   s32 nSmartNum;
#define	WdgSoftkeyboardSmartRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nSmart[firstDimNum];
#define	WdgSoftkeyboardChSymbolTblItemNumRC(...)  s32 nChSymbolTblNum;
#define	WdgSoftkeyboardChSymbolTblRC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nChSymbolTbl[firstDimNum];
#define	WdgSoftkeyboardSymbolTblPage2ItemNumRC(...)  s32 nSymbolTblPage2Num;
#define	WdgSoftkeyboardSymbolTblPage2RC(firstDimNum, ...) SoftKeyBoardWidget_VectorModelData_t nSymbolTblPage2[firstDimNum];

#define RSCustomize(type,name, ...) type name;
