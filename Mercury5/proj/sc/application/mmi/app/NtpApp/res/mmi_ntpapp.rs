ApBegin(RS,CLSID_NTPAPP)
	WndBegin(NTP_WND_MAIN)
		WdgBegin(CLSID_VTMMENU,tNtpMainMenu)
            		VtmCreateMenuRC({IMG_NULL_ID,TXT_LIL_N_NTP,WDG_MENU_TYPE_NORMAL,WDG_MENU_ITEM_TYPE_TEXT_THEMETEXT,WDG_MENU_CHECK_STYLE_NONE,2,0,0})
            		VtmCreateMenuDataRC(2,{{{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_NTP_START_SYNC},{TXT_LIL_N_NTP_START, TXT_NULL_ID}}, 
            		                                        {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_NTP_SELECT_SERVER},{TXT_LIL_N_NTP_IP, TXT_NULL_ID}}})
        	WdgEnd(CLSID_VTMMENU,tNtpMainMenu)
   	WndEnd(NTP_WND_MAIN)
   	WndBegin(NTP_WND_SELECT_SIM)
   	    	WdgBegin(CLSID_VTMSIMSELECTION,tNtpDualMenu)
            		VtmCreateSimSelectionRC({IMG_NULL_ID,TXT_LIL_N_NTP})
        	WdgEnd(CLSID_VTMSIMSELECTION,tNtpDualMenu)
   	WndEnd(NTP_WND_SELECT_SIM)
   	WndBegin(NTP_WND_SELECT_SERVER)
		WdgBegin(CLSID_VTMPOPUPSELECT,tNtpSelectServer)
			VtmCreatePopUpSelectRC({NULL,WDG_MENU_ITEM_TYPE_TEXT,WDG_MENU_CHECK_STYLE_RADIO,2,0,0})
			VtmCreatePopUpSelectDataRC(2, { {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_NTP_IP_NTSC},TXT_LIL_N_NTP_NTSC},
                                            				   {{MENUMODEL_ITEM_VISABLE,{DEFAULT_SK,DEFAULT_SK,DEFAULT_SK},MNU_NTP_IP_MICROSOFT },TXT_LIL_N_NTP_MICROSOFT}})
		WdgEnd(CLSID_VTMPOPUPSELECT,tNtpSelectServer)
	WndEnd(NTP_WND_SELECT_SERVER)
ApEnd(RS,CLSID_NTPAPP)

