#if 1


#define    VTM_CREATE_START 0x0100
#define    VtmCreateDateInputID 0x0100
#define    VtmCreateImgID 0x0101
#define    VtmCreateInputID 0x0102
#define    VtmCreatePromptInputID 0x0103
#define    VtmCreateTimeInputID 0x0104
#define    VtmCreateImgGridMenuID 0x0105
#define    VtmCreateImgThumbID 0x0106
#define    VtmCreateMenuID 0x0107
#define    VtmCreateSimSelectionID 0x0108
#define    VtmCreateTabMenuID 0x0109
#define    VtmCreateTxtGridMenuID 0x010A
#define    VtmCreateIpInputID 0x010B
#define    VtmCreateOptionMenuID 0x010C
#define    VtmCreatePopUpInfoID 0x010D
#define    VtmCreatePopUpInputID 0x010E
#define    VtmCreatePopUpPromptID 0x010F
#define    VtmCreatePopUpSelectID 0x0110
#define    VtmCreateImgGridMenuDataID 0x0111
#define    VtmCreateImgThumbDataID 0x0112
#define    VtmCreateMenuDataID 0x0113
#define    VtmCreateTabMenuDataID 0x0114
#define    VtmCreateTxtGridMenuDataID 0x0115
#define    VtmCreateOptionMenuDataID 0x0116
#define    VtmCreatePopUpInfoDataID 0x0117
#define    VtmCreatePopUpSelectDataID 0x0118
#define    NUMBER_OF_VTM 0x0118

#define    WDG_COMMON_PROPERTY_START 0x0200
#define    WdgCommonSetLookCtrlTypeID 0x0200
#define    WdgCommonSetIconStyleID 0x0201
#define    WdgCommonSetTextColorID 0x0202
#define    WdgCommonSetHighlightTextColorID 0x0203
#define    WdgCommonSetFontTypeID 0x0204
#define    WdgCommonSetFontCategoryID 0x0205
#define    WdgCommonSetLangDirectionID 0x0206
#define    WdgCommonSetBGColorID 0x0207
#define    WdgCommonSetBGImageIdID 0x0208
#define    WdgCommonSetBGPositionID 0x0209
#define    WdgCommonSetBGEnableID 0x020A
#define    WdgCommonSetBGAlignmentID 0x020B
#define    WdgCommonSetAlignmentID 0x020C
#define    WdgCommonSetBorderDataID 0x020D
#define    WdgCommonSetPaddingDataID 0x020E
#define    WdgCommonEnableScrollBarID 0x020F
#define    NUMBER_OF_COMMON_PROP 0x020F

#define    WndViewWidget 0x0300
#define    WndSetTitleVisiableID 0x0300
#define    WndSetStatusBarVisibleID 0x0301
#define    WndSetSoftkeyVisibleID 0x0302
#define    WndSetStatusBarTransparencyID 0x0303
#define    WndSetSoftkeyTransparencyID 0x0304
#define    WndSetTitleID 0x0305
#define    WndSetBgPosID 0x0306
#define    WndSetBgColorID 0x0307
#define    WndSetSoftkeyID 0x0308
#define    WndSetAllSoftkeyID 0x0309

#define    WdgTextCommonCreateID 0x0400
#define    WdgTextSetDataByIDID 0x0400
#define    WdgTextSetFontHeightID 0x0402
#define    WdgTextSetTextOutlineColorID 0x0403
#define    WdgTextSetHighlightTextOutlineColorID 0x0404
#define    WdgTextSetHighlightBGColorID 0x0405
#define    WdgTextSetSlideDirectionID 0x0406
#define    WdgTextSetSlideStepOffsetID 0x0407
#define    WdgTextSetSlideStepTimeID 0x0408
#define    WdgTextSetEnableAnimateID 0x0409
#define    WdgTextSetSlideOnOffID 0x040A
#define    WdgTextSetSlideAutoRepeatID 0x040B
#define    WdgTextSetSlideStyleID 0x040C
#define    WdgTextSetLayoutFlagID 0x040D
#define    WdgTextSetFcsItemBGColorID 0x040E

#define    WdgImageCommonCreateID 0x0500
#define    WdgImageSetDataByIDID 0x0501
#define    WdgImageSetFrameWidthID 0x0502
#define    WdgImageSetFrameIntervalID 0x0503
#define    WdgImageSetAutoFitID 0x0504
#define    WdgImageSetEnableUpscaleID 0x0505
#define    WdgImageSetEnablePartialDecodeID 0x0506
#define    WdgImageSetEnableDefaultImageID 0x0507
#define    WdgImageSetDefaultImageIDID 0x0508
#define    WdgImageSetImageScaleRotateID 0x0509

#define    WdgInputCommonCreateID 0x0601
#define    WdgInputSetTextByIdID 0x0602
#define    WdgInputSetDecimalPointEnableID 0x0603
#define    WdgInputSetFirstKeyPressID 0x0604
#define    WdgInputSetFontSizeID 0x0605
#define    WdgInputSetFontTypeID 0x0606
#define    WdgInputSetHandWritingEnableID 0x0607
#define    WdgInputSetHighlightBGColorID 0x0608
#define    WdgInputSetHighlightTextColorID 0x0609
#define    WdgInputSetLineGapID 0x060A
#define    WdgInputSetMaxByteLengthID 0x060B
#define    WdgInputSetMaxlenAfterDecimalPointID 0x060C
#define    WdgInputSetMaxlenAfterExponentID 0x060D
#define    WdgInputSetMultilineID 0x060E
#define    WdgInputSetPasswordStyleID 0x060F
#define    WdgInputSetShowBorderWhenLoseFocusID 0x0610
#define    WdgInputSetSmartInputOffID 0x0611
#define    WdgInputSetSoftKeyBoardEnableID 0x0612
#define    WdgInputSetTextColorID 0x0613
#define    WdgInputSetInitTextID 0x06014
#define    WdgInputSetCursorColorID 0x06015
#define    WdgInputSetCurrentInputLanguageID 0x0616
#define    WdgInputSetDisableSymbolTableID 0x0617
#define    WdgInputSetDisableSwitchInputModeID 0x0618
#define    WdgInputSetChineseInputOffID 0x0619
#define    WdgInputSetLineFeedDisableID 0x061A
#define    WdgInputSetDialingShiftOldestCharID 0x061B
#define    WdgInputSetModeMaskID 0x061C
#define    WdgInputSetCurrentInputModeID 0x061D

#define    WdgButtonCommonCreateID 0x0700
#define    WdgButtonSetDataByIDID 0x0701
#define    WdgButtonSetDisDisplayTextID 0x0702
#define    WdgButtonSetUnpressedTextColorID 0x0703
#define    WdgButtonSetUnpressedTextOutlineColorID 0x0704
#define    WdgButtonSetPressedTextColorID 0x0705
#define    WdgButtonSetPressedTextOutlineColorID 0x0706

#define    WdgTabCommonCreateID 0x0800
#define    WdgTabSetDataByIDID 0x0801
#define    WdgTabSetModeID 0x0802
#define    WdgTabSetActiveWidthID 0x0803
#define    WdgTabSetInactiveWidthID 0x0804
#define    WdgTabSetTabHeightID 0x0805
#define    WdgTabSetTabHeightOffsetID 0x0806
#define    WdgTabSetTabPaddingLeftID 0x0807
#define    WdgTabSetTabPaddingRightID 0x0808
#define    WdgTabSetTabGapID 0x0809

#define    WdgSwitchIconCommonCreateID 0x0900
#define    WdgSwitchIconSetDataByIDID 0x0901
#define    WdgSwitchIconSetIconStyleID 0x0902

#define    WdgProgressCommonCreateID 0x0A00
#define    WdgProgressSetRepeatID 0x0A01
#define    WdgProgressSetFgBorderColorID 0x0A02
#define    WdgProgressSetBgBorderColorID 0x0A03
#define    WdgProgressSetFgFillColorID 0x0A04
#define    WdgProgressSetBgFillColorID 0x0A05
#define    WdgProgressSetFgRectFlagID 0x0A06
#define    WdgProgressSetBgRectFlagID 0x0A07
#define    WdgProgressSetTotalID 0x0A08
#define    WdgProgressSetCurPosID 0x0A09
#define    WdgProgressSetPreferCellWidthID 0x0A0A
#define    WdgProgressSetPreferCellTotalNumID 0x0A0B
#define    WdgProgressSetPreferCellRepeatlNumID 0x0A0C
#define    WdgProgressSetAutoOnOffID 0x0A0D

#define    WdgIPCommonCreateID 0x0B00
#define    WdgIPCommonSetFontID 0x0B01
#define    WdgIPSetHighlightBGColorID 0x0B02
#define    WdgIPSetHighlightTextColorID 0x0B03
#define    WdgIPSetIPValueID 0x0B04

#define    WdgFadeoutCommonCreateID 0x0C00
#define    WdgFadeoutSetFoLevelID 0x0C01

#define    WdgPullDownCommonCreateID 0x0D00
#define    WdgPullDownSetDataByIdID 0x0D01
#define    WdgPullDownSetFocusIndexID 0x0D02
#define    WdgPullDownSetLayoutModeID 0x0D03
#define    WdgPullDownSetNaviUpKeyID 0x0D04
#define    WdgPullDownSetNaviDownKeyID 0x0D05
#define    WdgPullDownSetToggleListKeyID 0x0D06
#define    WdgPullDownSetArrowWidthID 0x0D07
#define    WdgPullDownSetTextColorID 0x0D08
#define    WdgPullDownSetHighlightTextColorID 0x0D09
#define    WdgPullDownSetHighlightBgColorID 0x0D0A
#define    WdgPullDownSetListBorderColorID 0x0D0B

#define    WdgIndicatorCommonCreateID 0x0E00
#define    WdgIndicatorSetDataID 0x0E01
#define    WdgIndicatorSetLayoutStyleID 0x0E02
#define    WdgIndicatorSetFGTopOffsetID 0x0E03
#define    WdgIndicatorSetFGBottomOffsetID 0x0E04
#define    WdgIndicatorSetFGLeftOffsetID 0x0E05
#define    WdgIndicatorSetFGRightOffsetID 0x0E06
#define    WdgIndicatorSetINDOffsetID 0x0E07
#define    WdgIndicatorSetINDImageIDID 0x0E08
#define    WdgIndicatorSetFGImageIDID 0x0E09
#define    WdgIndicatorSetBGImageIDID 0x0E0A
#define    WdgIndicatorSetDWNTopOffsetID 0x0E0B
#define    WdgIndicatorSetDWNBottomOffsetID 0x0E0C
#define    WdgIndicatorSetDWNLeftOffsetID 0x0E0D
#define    WdgIndicatorSetDWNRightOffsetID 0x0E0E
#define    WdgIndicatorSetDWNEndOffsetID 0x0E0F
#define    WdgIndicatorSetDWNImageIDID 0x0E10
#define    WdgIndicatorSetDWNENDImageIDID 0x0E11

#define    WdgViewportCommonCreateID 0x0F00
#define    WdgViewportSetLockVerMoveID 0x0F01
#define    WdgViewportSetLockHoriMoveID 0x0F02
#define    WdgViewportSetKeepCenterID 0x0F03
#define    WdgViewportSetPanStepID 0x0F04
#define    WdgViewportSetCurrentYOffsetID 0x0F05
#define    WdgViewportSetCurrentXOffsetID 0x0F06

#define    WdgTimeCommonCreateID 0x1000
#define    WdgTimeSetTimeValueID 0x1001
#define    WdgTimeSetEnableAdjustValueByNaviUpDownID 0x1002
#define    WdgTimeSetEnableSecondFieldID 0x1003
#define    WdgTimeSetHourFormatID 0x1004
#define    WdgTimeSetHighlightTextColorID 0x1005
#define    WdgTimeSetHighlightBGColorID 0x1006

#define    WdgFcDateCommonCreateID 0x1101
#define    WdgFcDateSetDataID 0x1102
#define    WdgFcDateSetMaxYearID 0x1103
#define    WdgFcDateSetMinYearID 0x1104
#define    WdgFcDateSetFocusIndID 0x1105

#define    WdgFcTimeCommonCreateID 0x1200
#define    WdgFcTimeSetDataID 0x1201

#define    WdgDateCommonCreateID 0x1300
#define    WdgDateSetDateValueID 0x1301
#define    WdgDateSetEnableAdjustValueByNaviUpDownID 0x1302
#define    WdgDateSetHighlightBGColorID 0x1303
#define    WdgDateSetHighlightTextColorID 0x1304
#define    WdgDateSetMaxYearID 0x1305
#define    WdgDateSetMinYearID 0x1306

#define    WdgMenuCommonCreateID 0x1401
#define    WdgMenuDataItemID 0x1402
#define    WdgDynamicMenuItemID 0x1403
#define    WdgDynamicMenuItemInfID 0x1404
#define    WdgStaticMenuItemID 0x1405
#define    WdgMenuItemTextID 0x1406
#define    WdgMenuItemImageID 0x1407
#define    WdgMenuItemTextImageID 0x1408
#define    WdgMenuItemImageTextID 0x1409
#define    WdgMenuItemImageTextImageID 0x140A
#define    WdgMenuItemTextDateID 0x140B
#define    WdgMenuItemTextTimeID 0x140C
#define    WdgMenuItemTextTextID 0x140D
#define    WdgMenuItemTextIpID 0x140E
#define    WdgMenuItemL1ImageTextL2TextID 0x140F
#define    WdgMenuItemL1ImageTextL2ImageTextID 0x1410
#define    WdgMenuItemL1ImageTextL2TextImageID 0x1411
#define    WdgMenuItemImageL1TextL2TextID 0x1412
#define    WdgMenuItemImageL1TextImageL2TextImageID 0x1413
#define    WdgMenuItemImageL1TextImageL2TextID 0x1414
#define    WdgMenuItemTextL2PickTextID 0x1415
#define    WdgMenuItemTextL2PickImageTextID 0x1416
#define    WdgMenuItemImageTextL2PickImageTextID 0x1417
#define    WdgMenuItemButtonID 0x1418
#define    WdgMenuSetItemFocusImageID 0x1419
#define    WdgMenuSetItemUnFocusImageID 0x141A
#define    WdgMenuSetRollTypeID 0x141B
#define    WdgMenuSetCheckStyleID 0x141C
#define    WdgMenuSetMenuBGImageID 0x141D
#define    WdgStaticMenuInitID 0x141E
#define    WdgMenuSetFirstItemID 0x141F
#define    WdgMenuSetHighlightedItemID 0x1420
#define    WdgMenuSetToGridStyleID 0x1421
#define    WdgMenuSetItemWidthID 0x1422
#define    WdgMenuSetItemHeightID 0x1423
#define    WdgMenuSetRowGapID 0x1424
#define    WdgMenuSetColGapID 0x1425
#define    WdgMenuSetFixedNumID 0x1426

#define    WdgPickCommonCreateID 0x1500
#define    WdgPickSetDataByIDID 0x1501
#define    WdgPickSetInvisibleIfDisableID 0x1502
#define    WdgPickSetFocusIndexID 0x1503
#define    WdgPickSetLayoutStyleID 0x1504
#define    WdgPickSetArrowInsideID 0x1505

#define    WdgCommonPickCommonCreateID 0x1600
#define    WdgCommonPickSetDataByIDID 0x1601
#define    WdgCommonPickSetDispDataID 0x1602
#define    WdgCommonPickSetInvisibleIfDisableID 0x1603
#define    WdgCommonPickSetFocusIndexID 0x1604
#define    WdgCommonPickSetLayoutStyleID 0x1605
#define    WdgCommonPickSetArrowInsideID 0x1606

#define    WdgDoubleItemCommonCreateID 0x1700
#define    WdgDoubleItemDBTextSetDataByIDID 0x1701
#define    WdgDoubleItemITSTextSetDataByIDID 0x1702
#define    WdgDoubleItemTextDateSetDataByIDID 0x1703
#define    WdgDoubleItemITSTISetDataByIDID 0x1704
#define    WdgDoubleItemSetDisableDownWidgetBGID 0x1705
#define    WdgDoubleItemSetTextOutlineColorID 0x1706
#define    WdgDoubleItemSetHighlightedTextOutlineColorID 0x1707
#define    WdgDoubleItemSetSlideOnOffID 0x1708
#define    WdgDoubleItemSetFocusOnUpperWidgetID 0x1709

#define    WdgOsdCommonCreateID 0x1800

#define    WdgAbsContainerCommonCreateID 0x1900

#define    WdgOverlayImageSetDataByIDID 0x1A00

#endif

