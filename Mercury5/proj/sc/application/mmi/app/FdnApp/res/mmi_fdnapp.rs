ApBegin(RS,CLSID_FDNAPP)
    WndBegin(FDNAPP_WND_EDIT_CONTACT)
        WndSetAllSoftkeyRC({SK_SAVE, SK_OK, SK_CANCEL})
        WndSetTitleRC( {IMG_NULL_ID,TXT_LTL_N_EDIT_FDN } )

        WdgBegin(CLSID_DOUBLE_TEXT_WIDGET,NameDoubleTextWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{50,50},DOUBLEITEM_STYLE_DOUBLE_TEXT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_NAME,TXT_NULL_ID})
        WdgEnd(CLSID_DOUBLE_TEXT_WIDGET,NameDoubleTextWidget)

        WdgBegin(CLSID_TEXT_INPUT_WIDGET,NumberTextInputWidget)
            WdgDoubleItemCreateForWndRC({{0,0},{50,50},DOUBLEITEM_STYLE_TEXT_INPUT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_MOBILE,TXT_NULL_ID})

            ChildBegin(CLSID_INPUTWIDGET,CHILD_SECOND_ORDER, dbInputWdg)
                WdgInputSetCurrentInputModeRC(MAE_INPUTMODE_DIALING)
                WdgInputSetHandWritingEnableRC(FALSE)
            ChildEnd(CLSID_INPUTWIDGET,CHILD_SECOND_ORDER, dbInputWdg)
        WdgEnd(CLSID_TEXT_INPUT_WIDGET,NumberTextInputWidget)
    WndEnd(FDNAPP_WND_EDIT_CONTACT)

    WndBegin(FDNAPP_WND_ENTRY_MENU_WAITING)
        WdgBegin(CLSID_VTMMENU, vtmWaitingMenu)
            VtmCreateMenuRC({ IMG_NULL_ID,TXT_LTL_N_FDN,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, {
                                {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_FDNAPP_EM_FDN_LIST}, TXT_LIL_N_FDN_LIST },
                                {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_FDNAPP_EM_FDN_STATUS}, TXT_LIL_N_TURN_ON }  })
        WdgEnd(CLSID_VTMMENU,vtmWaitingMenu)
    WndEnd(FDNAPP_WND_ENTRY_MENU_WAITING)

    WndBegin(FDNAPP_WND_ENTRY_MENU)
        WdgBegin(CLSID_VTMMENU,vtmEntryMenu)
            VtmCreateMenuRC({IMG_NULL_ID,TXT_LTL_N_FDN,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, {
                                {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_FDNAPP_EM_FDN_LIST}, TXT_LIL_N_FDN_LIST },
                                {{MENUMODEL_ITEM_VISABLE, {DEFAULT_SK,DEFAULT_SK,DEFAULT_SK}, MNU_FDNAPP_EM_FDN_STATUS}, TXT_LIL_N_TURN_OFF } })
        WdgEnd(CLSID_VTMMENU,vtmEntryMenu)
    WndEnd(FDNAPP_WND_ENTRY_MENU)

    WndBegin(FDNAPP_WND_CONTACT_LIST)
        WdgBegin(CLSID_VTMMENU,vtmContactMenu)
            VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_FDN_LIST,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_IMAGETEXT_SPACEIMAGETEXT,WDG_MENU_CHECK_STYLE_NONE,0,0,0})
        WdgEnd(CLSID_VTMMENU,vtmContactMenu)
    WndEnd(FDNAPP_WND_CONTACT_LIST)

    WndBegin(FDNAPP_WND_CONTACT_LIST_OPTION)
        WdgBegin(CLSID_VTMOPTIONMENU,vtmContactOption)
            VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,4})
            VtmCreateOptionMenuDataRC(4, {
                                    {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_FDNAPP_MAKE_CALL}, TXT_OIL1_N_CALL },
                                    {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_FDNAPP_NEW_CONTACT}, TXT_OIL1_N_NEW_CONTACT },
                                    {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_FDNAPP_EDIT_CONTACT}, TXT_OIL1_N_EDIT_CONTACT },
                                    {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_FDNAPP_DELETE_CONTACT}, TXT_OIL1_N_DELETE_CONTACT }  })
        WdgEnd(CLSID_VTMOPTIONMENU,vtmContactOption)
    WndEnd(FDNAPP_WND_CONTACT_LIST_OPTION)

    WndBegin(FDNAPP_WND_FULLEDITOPTION)
        WdgBegin(CLSID_VTMOPTIONMENU,vtmFulledOption)
            VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,2})
            VtmCreateOptionMenuDataRC(2, {  {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_COMMON_TEXT_SAVE}, TXT_LSK_N_OK },
                                            {{MENUMODEL_ITEM_VISABLE | WDG_MENU_ITEM_FLAG_HAS_CHILD, {SK_SELECT, SK_OK, SK_CANCEL}, MNU_COMMON_TEXT_INPUT_MENU}, TXT_OIL1_N_INPUT_MENU } })
        WdgEnd(CLSID_VTMOPTIONMENU,vtmFulledOption)
    WndEnd(FDNAPP_WND_FULLEDITOPTION)


    WndBegin(FDNAPP_WND_FULLEDIT)
        WdgBegin(CLSID_VTMINPUT,vtmFullEdit)
            VtmCreateInputRC({IMG_NULL_ID,TXT_LIL_N_NAME,0,FALSE})
				VTMWdgBegin (CLSID_INPUTWIDGET, INPUT_INPUT_WDG, VtmInputWdg)                    
					WdgInputSetMultilineRC(TRUE)
					WdgInputSetLineFeedDisableRC(TRUE)    
				VTMWdgEnd (CLSID_INPUTWIDGET, INPUT_INPUT_WDG, VtmInputWdg)
        WdgEnd(CLSID_VTMINPUT,vtmFullEdit)
    WndEnd(FDNAPP_WND_FULLEDIT)

ApEnd(RS,CLSID_FDNAPP)

