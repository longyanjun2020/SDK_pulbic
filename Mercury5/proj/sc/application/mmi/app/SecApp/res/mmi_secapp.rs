ApBegin(RS,CLSID_SECAPP)


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifyMasterCodeWnd()
    WndBegin(WINID_SECAPP_POWERON_VERIFY_MASTER_CODE)
        WndSetTitleRC({IMG_NULL_ID,TXT_LIL_N_PHONE_LOCK})

        WdgBegin(CLSID_DOUBLE_TEXT_WIDGET,TxtDouble)
            WdgDoubleItemCreateForWndRC({{0,0},{MAIN_DEFVIEW_WIDTH,MAIN_DEFVIEW_HEIGHT},DOUBLEITEM_STYLE_DOUBLE_TEXT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_MASTER_KEY,TXT_NULL_ID})
            ChildBegin(CLSID_TEXTWIDGET,CHILD_SECOND_ORDER, ChildTxtWdg)
                WdgCommonSetBGColorRC(DEF_THM_SECAPP_BG)
            ChildEnd(CLSID_TEXTWIDGET,CHILD_SECOND_ORDER, ChildTxtWdg)
        WdgEnd(CLSID_DOUBLE_TEXT_WIDGET,TxtDouble)

        WdgBegin(CLSID_TEXT_INPUT_WIDGET,TxtInput)
            WdgDoubleItemCreateForWndRC({{0,SEC_VERIFY_LOCK_YPOS},{MAIN_DEFVIEW_WIDTH,MAIN_DEFVIEW_HEIGHT},DOUBLEITEM_STYLE_TEXT_INPUT})
            WdgDoubleItemDBTextSetDataByIDRC({TXT_LIL_N_MASTER_CODE,TXT_NULL_ID})
            ChildBegin(CLSID_INPUTWIDGET,CHILD_SECOND_ORDER, ChildInputWdg)
                WdgInputSetDisableSymbolTableRC(TRUE)
                WdgInputSetPasswordStyleRC(TRUE)
                WdgInputSetDisableSwitchInputModeRC(TRUE)
                WdgInputSetCurrentInputModeRC(MAE_INPUTMODE_NUMERIC)
                WdgInputSetHandWritingEnableRC(FALSE)
                WdgInputSetMultilineRC(FALSE)
            ChildEnd(CLSID_INPUTWIDGET,CHILD_SECOND_ORDER, ChildInputWdg)
        WdgEnd(CLSID_TEXT_INPUT_WIDGET,TxtInput)
    WndEnd(WINID_SECAPP_POWERON_VERIFY_MASTER_CODE)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifyPinCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_PIN_ONESIM)
		WdgBegin(CLSID_VTMPOPUPINPUT,tPINVerify_OneSIM)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_LIL_N_PIN,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tPINVerify_OneSIM)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_PIN_ONESIM)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifyPinCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_PIN_TWOSIM_MASTER)
		WdgBegin(CLSID_VTMPOPUPINPUT,tPINVerify_TwoSIMMaster)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_MASTER,TXT_LTL_N_MASTER,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tPINVerify_TwoSIMMaster)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_PIN_TWOSIM_MASTER)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifyPinCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_PIN_TWOSIM_SLAVE)
		WdgBegin(CLSID_VTMPOPUPINPUT,tPINVerify_TwoSIMSlave)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_SLAVE,TXT_LTL_N_SLAVE,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tPINVerify_TwoSIMSlave)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_PIN_TWOSIM_SLAVE)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifySIMCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_SIM_ONESIM)
		WdgBegin(CLSID_VTMPOPUPINPUT,tSIMVerify_OneSIM)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_LIL_N_SIM_LOCK,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tSIMVerify_OneSIM)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_SIM_ONESIM)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifySIMCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_SIM_TWOSIM_MASTER)
		WdgBegin(CLSID_VTMPOPUPINPUT,tSIMVerify_TwoSIMMaster)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_MASTER,TXT_LIL_N_SIM_LOCK,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tSIMVerify_TwoSIMMaster)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_SIM_TWOSIM_MASTER)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePowerOnVerifySIMCodeWnd()
	WndBegin(WINID_SECAPP_POWERON_VERIFY_SIM_TWOSIM_SLAVE)
		WdgBegin(CLSID_VTMPOPUPINPUT,tSIMVerify_TwoSIMSlave)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_SLAVE,TXT_LIL_N_SIM_LOCK,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tSIMVerify_TwoSIMSlave)
	WndEnd(WINID_SECAPP_POWERON_VERIFY_SIM_TWOSIM_SLAVE)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateUnBlockPINCodeWnd()
	WndBegin(WINID_SECAPP_UNBLOCK_PIN_ONESIM)
		WdgBegin(CLSID_VTMPOPUPINPUT,tUnBlockPIN_OneSIM)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_NULL_ID,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tUnBlockPIN_OneSIM)
	WndEnd(WINID_SECAPP_UNBLOCK_PIN_ONESIM)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateUnBlockPINCodeWnd()
	WndBegin(WINID_SECAPP_UNBLOCK_PIN_TWOSIM_MASTER)
		WdgBegin(CLSID_VTMPOPUPINPUT,tUnBlockPIN_TwoSIM_Master)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_MASTER,TXT_LTL_N_MASTER,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tUnBlockPIN_TwoSIM_Master)
	WndEnd(WINID_SECAPP_UNBLOCK_PIN_TWOSIM_MASTER)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateUnBlockPINCodeWnd()
	WndBegin(WINID_SECAPP_UNBLOCK_PIN_TWOSIM_SLAVE)
		WdgBegin(CLSID_VTMPOPUPINPUT,tUnBlockPIN_TwoSIM_Slave)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,CALL_IMG_DUAL_SLAVE,TXT_LTL_N_SLAVE,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tUnBlockPIN_TwoSIM_Slave)
	WndEnd(WINID_SECAPP_UNBLOCK_PIN_TWOSIM_SLAVE)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateAllChangeAndConfirmWnd()
	WndBegin(WINID_SECAPP_ALL_CHAMGE_CONFIRM)
		WdgBegin(CLSID_VTMPOPUPINPUT,tAllChangeConfirm)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_NULL_ID,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tAllChangeConfirm)
	WndEnd(WINID_SECAPP_ALL_CHAMGE_CONFIRM)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateEmergencyCallListWnd()
	WndBegin(WINID_SECAPP_EMERGENCYCALL_LIST)
		WdgBegin(CLSID_VTMMENU,tEmergencyCall)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LTL_N_EMERGENCY_CALL,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_NONE,0,0,0})
		WdgEnd(CLSID_VTMMENU,tEmergencyCall)
	WndEnd(WINID_SECAPP_EMERGENCYCALL_LIST)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateSecurityMenuWnd()
	WndBegin(WINID_SECAPP_SECURITY_MENU)
		WdgBegin(CLSID_VTMMENU,tSecurityMenu)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_SECURITY,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT,WDG_MENU_CHECK_STYLE_NONE,9,0,0})
            VtmCreateMenuDataRC(9, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_MASTER_PIN_CODE},{TXT_LIL_N_MASTER_PIN_CODE, TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_SLAVE_PIN_CODE },{TXT_LIL_N_SLAVE_PIN_CODE,  TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PIN_CODE       },{TXT_LIL_N_PIN_CODE,        TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PHONE_LOCK     },{TXT_LIL_N_PHONE_LOCK,      TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_SIM_LOCK       },{TXT_LIL_N_SIM_LOCK,        TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_AUTO_KEYPAD_LOCK    },{TXT_LIL_N_AUTO_KEYPAD_LOCK,TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ANTI_STEAL          },{TXT_LIL_N_ANTI_STEAL,      TXT_NULL_ID}},
						             {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_MSG_SET_BLACKLIST       },{TXT_LIL_N_SMS_BLACKLIST,   TXT_NULL_ID}},
						             {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_PRIVATEPROTECT      },{TXT_LIL_N_PRIVATE_DATA_PROTECTION, TXT_NULL_ID}}    })
		WdgEnd(CLSID_VTMMENU,tSecurityMenu)
	WndEnd(WINID_SECAPP_SECURITY_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePINCodeMenuWnd()
	WndBegin(WINID_SECAPP_PIN_CODE_MENU)
		WdgBegin(CLSID_VTMMENU,tPINCodeMenu)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_PIN_CODE,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT,WDG_MENU_CHECK_STYLE_NONE,3,0,0})
            VtmCreateMenuDataRC(3, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_PIN_STATUS      },{TXT_LIL_N_PIN_STATUS, TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_CHANGE_PIN },{TXT_LIL_N_CHANGE_PIN, TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_CHANGE_PIN2},{TXT_LIL_N_CHANGE_PIN2,TXT_NULL_ID}} })
		WdgEnd(CLSID_VTMMENU,tPINCodeMenu)
	WndEnd(WINID_SECAPP_PIN_CODE_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePhoneLockMenuWnd()
	WndBegin(WINID_SECAPP_PHONE_LOCK_MENU)
		WdgBegin(CLSID_VTMMENU,tPhoneLockMenu)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_PHONE_LOCK,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_PHONE_LOCK_STATUS     },{TXT_LIL_N_PHONE_LOCK_STATUS,TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_CHANGE_PHONE_CODE},{TXT_LIL_N_CHANGE_PASSWORD,  TXT_NULL_ID}} })
		WdgEnd(CLSID_VTMMENU,tPhoneLockMenu)
	WndEnd(WINID_SECAPP_PHONE_LOCK_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateSIMLockMenuWnd()
	WndBegin(WINID_SECAPP_SIM_LOCK_MENU)
		WdgBegin(CLSID_VTMMENU,tSIMLockMenu)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_SIM_LOCK,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_SIM_LOCK_STATUS     },{TXT_LIL_N_SIM_LOCK_STATUS,TXT_NULL_ID}},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_CHANGE_SIM_CODE},{TXT_LIL_N_CHANGE_PASSWORD,TXT_NULL_ID}} })
		WdgEnd(CLSID_VTMMENU,tSIMLockMenu)
	WndEnd(WINID_SECAPP_SIM_LOCK_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateAutoKeypadLockMenuWnd()
	WndBegin(WINID_SECAPP_AUTO_KEYPAD_LOCK_MENU)
		WdgBegin(CLSID_VTMPOPUPSELECT,tAutoKeypadLockMenu)
			VtmCreatePopUpSelectRC({NULL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_RADIO,7,0,0})
			VtmCreatePopUpSelectDataRC(7, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_OFF   },TXT_LIL_N_OFF},
                                            {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_5_SECS },TXT_LIL_N_5_SECONDS},
                                            {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_15_SECS },TXT_LIL_N_15_SECONDS},
                                            {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_30_SECS },TXT_LIL_N_30_SECONDS},
                                            {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_1_MIN },TXT_LIL_N_1_MINUTE},
                                            {{MENUMODEL_ITEM_HIDE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_3_MINS},TXT_LIL_N_3_MINUTES},
                                            {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_5_MINS},TXT_LIL_N_5_MINUTES} })
		WdgEnd(CLSID_VTMPOPUPSELECT,tAutoKeypadLockMenu)
	WndEnd(WINID_SECAPP_AUTO_KEYPAD_LOCK_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePINStatusMenuWnd()
	WndBegin(WINID_SECAPP_PIN_STATUS_MENU)
		WdgBegin(CLSID_VTMMENU,tPINStatusMenu)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_PIN_STATUS,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PIN_STATUS_ON },TXT_LIL_N_ON},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PIN_STATUS_OFF},TXT_LIL_N_OFF} })
		WdgEnd(CLSID_VTMMENU,tPINStatusMenu)
	WndEnd(WINID_SECAPP_PIN_STATUS_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreatePhoneLockStatusMenuWnd()
	WndBegin(WINID_SECAPP_PHONE_LOCK_STATUS_MENU)
		WdgBegin(CLSID_VTMMENU,tPhoneLockStatus)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_PHONE_LOCK_STATUS,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PHONE_STATUS_ON },TXT_LIL_N_ON},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_PHONE_STATUS_OFF},TXT_LIL_N_OFF} })
		WdgEnd(CLSID_VTMMENU,tPhoneLockStatus)
	WndEnd(WINID_SECAPP_PHONE_LOCK_STATUS_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateSIMLockStatusMenuWnd()
	WndBegin(WINID_SECAPP_SIM_LOCK_STATUS_MENU)
		WdgBegin(CLSID_VTMMENU,tSIMLockStatus)
			VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_SIM_LOCK_STATUS,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_RADIO,2,0,0})
            VtmCreateMenuDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_SIM_STATUS_ON },TXT_LIL_N_ON},
                                     {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_SEC_ITEM_SIM_STATUS_OFF},TXT_LIL_N_OFF} })
		WdgEnd(CLSID_VTMMENU,tSIMLockStatus)
	WndEnd(WINID_SECAPP_SIM_LOCK_STATUS_MENU)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _SecCreateAllVerifyAndPowerOnWnd()
	WndBegin(WINID_SECAPP_ALL_VERIFY_POWERON)
		WdgBegin(CLSID_VTMPOPUPINPUT,tAllVerifyPowerOn)
			VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_NULL_ID,MAE_INPUTMODE_NUMERIC})
		WdgEnd(CLSID_VTMPOPUPINPUT,tAllVerifyPowerOn)
	WndEnd(WINID_SECAPP_ALL_VERIFY_POWERON)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
    WndBegin(MCA_WND_OPTMENU_BLACKLIST_NUMBER)
        WdgBegin(CLSID_VTMOPTIONMENU, vtmBlcakListOpt)
            VtmCreateOptionMenuRC(WDG_MENU_ITEM_TYPE_TEXT,5)
            VtmCreateOptionMenuDataRC(5, {
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_ADD_NEW}, TXT_OIL1_N_SECAPP_ADD_TOBLACKLIST_NEW },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_ADD_FROM_PHB}, TXT_OIL1_N_SECAPP_ADD_TOBLACKLIST_FROM_PHONEBOOK },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_EDIT}, TXT_OIL1_N_EDIT },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_REMOVE}, TXT_OIL1_N_REMOVE },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_REMOVE_ALL}, TXT_OIL1_N_SECAPP_REMOVE_ALL}  })
        WdgEnd(CLSID_VTMOPTIONMENU, vtmBlcakListOpt)
    WndEnd(MCA_WND_OPTMENU_BLACKLIST_NUMBER)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
	 WndBegin(MCA_WND_OPTMENU_BLACKLIST_ADD_NEW)
		    WdgBegin(CLSID_VTMPOPUPINPUT,vtmBlackListAddNew)
			      VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_LIL_N_BLACKLIST_PHONENUMER,MAE_INPUTMODE_DIALING})
		    WdgEnd(CLSID_VTMPOPUPINPUT,vtmBlackListAddNew)
	 WndEnd(MCA_WND_OPTMENU_BLACKLIST_ADD_NEW)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
    WndBegin(MCA_WND_OPTMENU_BLACKLIST_KEYWORD)
        WdgBegin(CLSID_VTMOPTIONMENU, vtmBlcakListKeywordOpt)
            VtmCreateOptionMenuRC(WDG_MENU_ITEM_TYPE_TEXT,4)
            VtmCreateOptionMenuDataRC(4, {
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_ADD_NEW}, TXT_OIL1_N_SECAPP_ADD_TOBLACKLIST_NEW },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_EDIT}, TXT_OIL1_N_EDIT },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_REMOVE}, TXT_OIL1_N_REMOVE },
                    {{MENUMODEL_ITEM_HIDE, {SK_SELECT, SK_OK, SK_BACK}, MNU_MSG_SET_BLACKLIST_REMOVE_ALL}, TXT_OIL1_N_SECAPP_REMOVE_ALL}  })
        WdgEnd(CLSID_VTMOPTIONMENU, vtmBlcakListKeywordOpt)
    WndEnd(MCA_WND_OPTMENU_BLACKLIST_KEYWORD)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
	 WndBegin(MCA_WND_OPTMENU_BLACKLIST_KEYWORD_ADD_NEW)
		    WdgBegin(CLSID_VTMPOPUPINPUT,vtmBlackListKeywordAdd)
			      VtmCreatePopUpInputRC({THM_COMMON_IMG_LIST_SEL_2,IMG_NULL_ID,TXT_LIL_N_BLACKLIST_PHONENUMER,MAE_INPUTMODE_NUMERIC})
		    WdgEnd(CLSID_VTMPOPUPINPUT,vtmBlackListKeywordAdd)
	 WndEnd(MCA_WND_OPTMENU_BLACKLIST_KEYWORD_ADD_NEW)
//<------------------------------------------------------------------------------
ApEnd(RS,CLSID_SECAPP)

