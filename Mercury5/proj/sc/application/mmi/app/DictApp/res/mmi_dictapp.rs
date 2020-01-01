ApBegin(RS,CLSID_DICTAPP)
    WndBegin(DICT_WND_INPUT)
        WdgBegin(CLSID_VTMINPUT,vtmInput)
            VtmCreateInputRC({IMG_NULL_ID,TXT_LIL_N_DICT_INPUT_WORDS,DICT_INPUT_MAX_BYTE_RS,FALSE})
        WdgEnd(CLSID_VTMINPUT,vtmInput)
    WndEnd(DICT_WND_INPUT)

    WndBegin(DICT_WND_TRANSLATION)
        WdgBegin(CLSID_VTMINPUT,vtmTransInput)
            VtmCreateInputRC({IMG_NULL_ID,TXT_LIL_N_DICT,0,TRUE})
        WdgEnd(CLSID_VTMINPUT,vtmTransInput)
    WndEnd(DICT_WND_TRANSLATION)

    WndBegin(DICT_WND_OPTION)
        WdgBegin(CLSID_VTMOPTIONMENU,vtmOption)
            VtmCreateOptionMenuRC({WDG_MENU_ITEM_TYPE_TEXT,2})
            VtmCreateOptionMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE, {SK_SELECT, SK_OK, SK_BACK}, MNU_DICT_TRANS}, TXT_LIL_N_DICT_TRANS},
                                           {{MENUMODEL_ITEM_VISABLE | MENUMODEL_ITEM_HAS_CHILD, {SK_SELECT, SK_OK, SK_BACK}, MNU_COMMON_TEXT_INPUT_MENU}, TXT_OIL1_N_INPUT_MENU}  } )
        WdgEnd(CLSID_VTMOPTIONMENU,vtmOption)
    WndEnd(DICT_WND_OPTION)

    /*            WdgProgressSetRepeatRC(TRUE)*/
    /*            WdgProgressSetAutoOnOffRC(TRUE)*/
    /*            VtmCreateMenuRC(,)*/
ApEnd(RS,CLSID_DICTAPP)

