ApBegin(RS,CLSID_SEA)

#ifdef __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
    WndBegin(SEA_WND_SMS_SELECTSIMMSG_MENU_VIEW)
        WdgBegin(CLSID_VTMMENU,vtmSmsSelectSimMsgMenuWdg)
            VtmCreateMenuRC({IMG_NULL_ID,TXT_OIL1_N_SAVE_TO_DRAFT,WDG_MENU_TYPE_NUMERIC,WDG_MENU_ITEM_TYPE_IMAGE_TEXT, WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_SEA_MSG_SELECT_MASTER_SIM}, {IMG_NULL_ID, TXT_LIL_N_MASTER_SIM} },
                                            {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_SEA_MSG_SELECT_SLAVE_SIM}, {IMG_NULL_ID, TXT_LIL_N_SLAVE_SIM} } })
        WdgEnd(CLSID_VTMMENU,vtmSmsSelectSimMsgMenuWdg)
    WndEnd(SEA_WND_SMS_SELECTSIMMSG_MENU_VIEW)
#endif
    WndBegin(SEA_WND_MMS_EDITOR_VIEW)
        WndSetStatusBarVisibleRC(VIEWSK_INVISIABLE)
        WndSetSoftkeyVisibleRC(VIEWSK_VISIABLE)
        WndSetAllSoftkeyRC({SK_OPTION, SK_OK, SK_CANCEL})
        /*WndSetTitleRC()   WdgTitleCreateForWnd ask owner modify*/

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsTitleAreaSizeTextWdg)
            WdgTextCreateForWndRC({ {SEA_MMS_SIZE_WDG_X,SEA_MMS_SIZE_WDG_Y},{SEA_MMS_SIZE_WIDTH,SEA_MMS_TITLE_HEIGHT},TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_P_MMS_SLIDE)
            WdgCommonSetFontCategoryRC(FONT_CAT_SUPERSMALL)
            WdgCommonSetAlignmentRC(ALIGN_H_RIGHT | ALIGN_V_MIDDLE)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsTitleAreaSizeTextWdg)

        WdgBegin(CLSID_BUTTONWIDGET,SeaMmsPageSwitchLeftArrowButtonWdg)
            WdgButtonCreateForWndRC( { {SEA_MMS_PAGESWITCH_WDG_X,SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_HEIGHT+(SEA_MMS_PAGESWITCH_HEIGHT-SEA_MMS_PAGESWITCH_ARROW_ICON_HEIGHT)/2},
                                       {SEA_MMS_PAGESWITCH_ARROW_ICON_WIDTH,SEA_MMS_PAGESWITCH_ARROW_ICON_HEIGHT} })
            WdgButtonSetDataByIDRC({TXT_NULL_ID,MMS_IMG_ARROW_LEFT_UNPRESSED,MMS_IMG_ARROW_LEFT_PRESSED})
        WdgEnd(CLSID_BUTTONWIDGET,SeaMmsPageSwitchLeftArrowButtonWdg)

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsPageSwitchPageTextWdg)
            WdgTextCreateForWndRC({ {SEA_MMS_PAGESWITCH_WDG_X + SEA_MMS_PAGESWITCH_ARROW_ICON_WIDTH,SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_HEIGHT},
                                    {SEA_MMS_PAGESWITCH_TEXTWDG_WIDTH,SEA_MMS_PAGESWITCH_HEIGHT}, TEXT_STYLE_COMMON  })
            WdgTextSetDataByIDRC(TXT_LIL_P_MMS_SLIDE)
            WdgCommonSetFontCategoryRC(FONT_CAT_SUPERSMALL)
            WdgCommonSetAlignmentRC(ALIGN_H_CENTER | ALIGN_V_MIDDLE)
            WdgTextSetSlideOnOffRC(FALSE)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsPageSwitchPageTextWdg)

        WdgBegin(CLSID_BUTTONWIDGET,SeaMmsPageSwitchRightArrowButtonWdg)
            WdgButtonCreateForWndRC( { {SEA_MMS_PAGESWITCH_WDG_X + SEA_MMS_PAGESWITCH_ARROW_ICON_WIDTH+SEA_MMS_PAGESWITCH_TEXTWDG_WIDTH,SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_HEIGHT+(SEA_MMS_PAGESWITCH_HEIGHT-SEA_MMS_PAGESWITCH_ARROW_ICON_HEIGHT)/2},
                                       {SEA_MMS_PAGESWITCH_ARROW_ICON_WIDTH,SEA_MMS_PAGESWITCH_ARROW_ICON_HEIGHT} })
            WdgButtonSetDataByIDRC({TXT_NULL_ID,MMS_IMG_ARROW_RIGHT_UNPRESSED,MMS_IMG_ARROW_RIGHT_PRESSED})
        WdgEnd(CLSID_BUTTONWIDGET,SeaMmsPageSwitchRightArrowButtonWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SeaMmsTitleAreaAttachmentIconImageWdg)
            WdgImageCreateForWndRC( {  {SEA_MMS_ATTACHMENT_ICON_WDG_X,SEA_MMS_ATTACHMENT_ICON_WDG_Y},
                                       {SEA_MMS_OBJECT_ICON_WIDTH,SEA_MMS_OBJECT_ICON_HEIGHT},
                                       IMAGE_STYLE_COMMON, {FALSE,MMS_ICON_EDIT_ATTACHED}  })
            WdgImageSetDataByIDRC(MMS_ICON_EDIT_ATTACHED)
        WdgEnd(CLSID_IMAGEWIDGET,SeaMmsTitleAreaAttachmentIconImageWdg)

        WdgBegin(CLSID_VIEWPORTWIDGET,SeaMmsEditorAreaViewpointWdg)
            WdgViewportCreateForWndRC( {  {MAIN_DEFVIEW_X,SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                          {MAIN_DEFVIEW_WIDTH,SEA_MMS_EDITOR_AREA_HEIGHT}, SEA_MMS_RECIPIENT_HEIGHT, ALIGN_H_START|ALIGN_V_TOP })
        WdgEnd(CLSID_VIEWPORTWIDGET,SeaMmsEditorAreaViewpointWdg)


        WdgBegin(CLSID_TEXTWIDGET,SeaMmsEditorAreaToDisplayWdg)
            WdgTextCreateForWndRC({ {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                    {SEA_MMS_EDITOR_AREA_WIDTH,SEA_MMS_RECIPIENT_HEIGHT}, TEXT_STYLE_COMMON })
            WdgTextSetDataByIDRC(TXT_NULL_ID)
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
            WdgCommonSetTextColorRC(DEF_THM_MSGEDITORAPP_RECIPIENT_FONT)
            WdgCommonSetAlignmentRC(ALIGN_H_START | ALIGN_V_MIDDLE)
            WdgTextSetFontHeightRC(SEA_MMS_RECIPIENT_HEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsEditorAreaToDisplayWdg)

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsEditorAreaCcDisplayWdg)
            WdgTextCreateForWndRC({ {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                    {SEA_MMS_EDITOR_AREA_WIDTH,SEA_MMS_RECIPIENT_HEIGHT}, TEXT_STYLE_COMMON })
            WdgTextSetDataByIDRC(TXT_NULL_ID)
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
            WdgCommonSetAlignmentRC(ALIGN_H_START | ALIGN_V_MIDDLE)
            WdgTextSetFontHeightRC(SEA_MMS_RECIPIENT_HEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsEditorAreaCcDisplayWdg)

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsEditorAreaBccDisplayWdg)
            WdgTextCreateForWndRC({ {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                    {SEA_MMS_EDITOR_AREA_WIDTH,SEA_MMS_RECIPIENT_HEIGHT}, TEXT_STYLE_COMMON })
            WdgTextSetDataByIDRC(TXT_NULL_ID)
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
            WdgCommonSetAlignmentRC(ALIGN_H_START | ALIGN_V_MIDDLE)
            WdgTextSetFontHeightRC(SEA_MMS_RECIPIENT_HEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsEditorAreaBccDisplayWdg)

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsEditorAreaSubjectDisplayWdg)
            WdgTextCreateForWndRC({ {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                    {SEA_MMS_EDITOR_AREA_WIDTH,SEA_MMS_RECIPIENT_HEIGHT}, TEXT_STYLE_COMMON })
            WdgTextSetDataByIDRC(TXT_NULL_ID)
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
            WdgCommonSetAlignmentRC(ALIGN_H_START | ALIGN_V_MIDDLE)
            WdgTextSetFontHeightRC(SEA_MMS_RECIPIENT_HEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsEditorAreaSubjectDisplayWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SeaMmsEditorAreaAudioIconImageWdg)
            WdgImageCreateForWndRC( {  {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                        {SEA_MMS_OBJECT_ICON_WIDTH,SEA_MMS_OBJECT_ICON_HEIGHT}, IMAGE_STYLE_COMMON , {FALSE,MMS_IMG_AUDIO} })
            WdgImageSetDataByIDRC(MMS_IMG_AUDIO)
        WdgEnd(CLSID_IMAGEWIDGET,SeaMmsEditorAreaAudioIconImageWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SeaMmsEditorAreaVideoIconImageWdg)
            WdgImageCreateForWndRC( {  {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT}, {SEA_MMS_OBJECT_ICON_WIDTH,SEA_MMS_OBJECT_ICON_HEIGHT},
                                        IMAGE_STYLE_COMMON, {FALSE,MMS_IMG_VIDEO} })
            WdgImageSetDataByIDRC(MMS_IMG_VIDEO)
        WdgEnd(CLSID_IMAGEWIDGET,SeaMmsEditorAreaVideoIconImageWdg)

        WdgBegin(CLSID_TEXTWIDGET,SeaMmsEditorAreaInputWdg)
            WdgTextCreateForWndRC({ {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT},
                                    {MAIN_DEFVIEW_WIDTH,SEA_MMS_EDITOR_AREA_HEIGHT}, TEXT_STYLE_COMMON  })
            WdgTextSetDataByIDRC(TXT_LIL_N_TO)
            WdgCommonSetTextColorRC(DEF_THM_MSGEDITORAPP_FONT_DEFAULT)
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
            WdgCommonSetAlignmentRC(ALIGN_H_START|ALIGN_V_MIDDLE)
            WdgTextSetFontHeightRC(SEA_MMS_TEXTWIDGET_SINGLELINE_HEIGHT)
            WdgTextSetLayoutFlagRC(LAYOUT_MULTILINE|LAYOUT_BREAKONWORD)
        WdgEnd(CLSID_TEXTWIDGET,SeaMmsEditorAreaInputWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SeaMmsEditorAreaImageImgWdg)
            WdgImageCreateForWndRC( { {MAIN_DEFVIEW_X, SEA_MMS_TITLE_WDG_Y+SEA_MMS_TITLE_AREA_HEIGHT}, {1,1}, IMAGE_STYLE_COMMON, {FALSE,IMG_NULL_ID} })
            WdgImageSetDataByIDRC(IMG_NULL_ID)
            WdgCommonSetAlignmentRC(ALIGN_H_CENTER|ALIGN_V_MIDDLE)
        WdgEnd(CLSID_IMAGEWIDGET,SeaMmsEditorAreaImageImgWdg)
    WndEnd(SEA_WND_MMS_EDITOR_VIEW)

    WndBegin(SEA_WND_RECIPIENT_VIEW)
        WndSetTitleRC( {IMG_NULL_ID,TXT_LTL_N_RECIPIENTS } )
        WndSetAllSoftkeyRC({SK_ADD, SK_OK, SK_CANCEL})

        WdgBegin(CLSID_MENUWIDGET,SeaRecipientMenuWdg)
            WdgMenuCreateForWndRC( { {0,0}, {MAIN_DEFVIEW_WIDTH,MAIN_DEFVIEW_HEIGHT- MAIN_TITLE_HEIGHT- SEA_RECIPIENT_EDITOR_BG_HEIGHT}, WDG_MENU_TYPE_NORMAL })
        WdgEnd(CLSID_MENUWIDGET,SeaRecipientMenuWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SeaRecipientEditorBgImgWdg)
            WdgImageCreateForWndRC( { {SEA_RECIPIENT_EDITOR_BG_X, SEA_RECIPIENT_EDITOR_BG_Y}, {MAIN_DEFVIEW_WIDTH,SEA_RECIPIENT_EDITOR_BG_HEIGHT},
                                       IMAGE_STYLE_COMMON, {FALSE,INPUT_IMG_MESSAGE_RECIPIENT_BG}  })
            WdgImageSetDataByIDRC(INPUT_IMG_MESSAGE_RECIPIENT_BG)
            WdgCommonSetAlignmentRC(ALIGN_H_CENTER|ALIGN_V_MIDDLE)
        WdgEnd(CLSID_IMAGEWIDGET,SeaRecipientEditorBgImgWdg)

        WdgBegin(CLSID_BUTTONWIDGET,SeaRecipientEditorButtonWdg)
            WdgButtonCreateForWndRC( { {SEA_RECIPIENT_EDITOR_ICON_X, SEA_RECIPIENT_EDITOR_ICON_Y}, {SEA_RECIPIENT_EDITOR_ICON_WIDTH,SEA_RECIPIENT_EDITOR_ICON_HEIGHT} })
            WdgButtonSetDataByIDRC({TXT_NULL_ID,INPUT_IMG_MESSAGE_RECIPIENT_ICON_UNPRESSED,INPUT_IMG_MESSAGE_RECIPIENT_ICON_PRESSED})
        WdgEnd(CLSID_BUTTONWIDGET,SeaRecipientEditorButtonWdg)

        WdgBegin(CLSID_INPUTWIDGET,SeaRecipientEditorInputWdg)
            WdgInputCreateForWndRC( { {SEA_RECIPIENT_EDITOR_WDG_X, SEA_RECIPIENT_EDITOR_WDG_Y}, {SEA_RECIPIENT_EDITOR_WDG_WIDTH,SEA_RECIPIENT_EDITOR_WDG_HEIGHT}, {TRUE,SKBOARD_ENABLE} })
            WdgInputSetShowBorderWhenLoseFocusRC(TRUE)
            WdgInputSetMaxByteLengthRC(MAX_RECIPIENTS_LENGTH_BYTE_RS)
        WdgEnd(CLSID_INPUTWIDGET,SeaRecipientEditorInputWdg)
    WndEnd(SEA_WND_RECIPIENT_VIEW)
ApEnd(RS,CLSID_SEA)

