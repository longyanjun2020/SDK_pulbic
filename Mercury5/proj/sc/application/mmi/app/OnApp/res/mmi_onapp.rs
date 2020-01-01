ApBegin(RS,CLSID_ONAPP)


//------------------------------------------------------------------------------>
// refer to _CreateLogoWindow()
	WndBegin(ONAPP_WND_LOGO)
		WdgBegin(CLSID_VTMIMG,tLogo)
#ifdef __APP_MMI_SMALLROM__
			VtmCreateImgRC(COMMON_IMG_POWERON_ANIM01)
#else
			VtmCreateImgRC(COMMON_IMG_LOGO)
#endif
		WdgEnd(CLSID_VTMIMG,tLogo)
	WndEnd(ONAPP_WND_LOGO)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreatePowerOnAnimWindow()
	WndBegin(ONAPP_WND_POWER_ON_ANIMATION)
		WdgBegin(CLSID_IMAGEWIDGET,tAnimation)
#ifdef __USER_DEFINE_POWERONOFF_ANIM__
          WdgImageCreateForWndRC({{0,0},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
          WdgImageSetDataByIDRC(IMG_NULL_ID)
#else
          WdgImageCreateForWndRC({{0,0},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,COMMON_IMG_POWERON_ANIM01}})
          WdgImageSetDataByIDRC(COMMON_IMG_POWERON_ANIM01)
#endif
		WdgEnd(CLSID_IMAGEWIDGET,tAnimation)
	WndEnd(ONAPP_WND_POWER_ON_ANIMATION)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreatePowerOnVideoWindow()
#ifdef __USER_DEFINE_POWERONOFF_VIDEO__
	WndBegin(ONAPP_WND_POWER_ON_VIDEO)
        WdgBegin(CLSID_OSDWIDGET,tVideoOsdWdg)
            WdgOsdCreateForWndRC({{0, 0}, {MAIN_LCD_WIDTH, MAIN_LCD_HEIGHT}})
        WdgEnd(CLSID_OSDWIDGET,tVideoOsdWdg)
		WdgBegin(CLSID_IMAGEWIDGET,tWaitingImg)
            WdgImageCreateForWndRC({{0,0},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,TOOLS_BLUETOOTH_IMG_SEARCH_ANIM}})
            WdgImageSetDataByIDRC(TOOLS_BLUETOOTH_IMG_SEARCH_ANIM)
		WdgEnd(CLSID_IMAGEWIDGET,tWaitingImg)
	WndEnd(ONAPP_WND_POWER_ON_VIDEO)
#endif
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
// refer to _CreateStandbyWindow()
    WndBegin(ONAPP_WND_STANDBY)
        WndSetTitleRC({IMG_NULL_ID,TXT_LTL_N_STANDBY_MODE})
        WdgBegin(CLSID_MENUWIDGET,tStandby)
            WdgMenuCreateForWndRC({{0,MAIN_TITLE_HEIGHT},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT-MAIN_TITLE_HEIGHT-MAIN_SK_HEIGHT},WDG_MENU_TYPE_NORMAL})
            WdgMenuSetCheckStyleRC(WDG_MENU_CHECK_STYLE_RADIO)
        WdgEnd(CLSID_MENUWIDGET,tStandby)
    WndEnd(ONAPP_WND_STANDBY)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreateSearchNetworkWindow()
	WndBegin(ONAPP_WND_SEARCH_NETWORK)
		WdgBegin(CLSID_VTMIMG,tSearchNetwork)
			VtmCreateImgRC(COMMON_IMG_NETWORK_SEARCH_ANIM)
		WdgEnd(CLSID_VTMIMG,tSearchNetwork)
	WndEnd(ONAPP_WND_SEARCH_NETWORK)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreateChargingWindow()
	WndBegin(ONAPP_WND_CHARGING)
		WdgBegin(CLSID_VTMIMG,tCharging)
			VtmCreateImgRC(COMMON_IMG_POWEROFF_CHARGING_ANIM)
		WdgEnd(CLSID_VTMIMG,tCharging)
	WndEnd(ONAPP_WND_CHARGING)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreateChargerFullWindow()
	WndBegin(ONAPP_WND_CHARGER_FULL)
		WdgBegin(CLSID_VTMIMG,tChargerFull)
			VtmCreateImgRC(COMMON_IMG_POWEROFF_CHARGE_FULL)
		WdgEnd(CLSID_VTMIMG,tChargerFull)
	WndEnd(ONAPP_WND_CHARGER_FULL)
//<------------------------------------------------------------------------------

#ifdef __DUAL_LCD__
//------------------------------------------------------------------------------>
// refer to _CreateSubLogoWindow()
	WndBegin(ONAPP_SUB_WND_LOGO)
		WdgBegin(CLSID_VTMIMG,tSubLogo)
#ifdef __APP_MMI_SMALLROM__
			VtmCreateImgRC(SUB_COMMON_IMG_POWERON_ANIM01)
#else
			VtmCreateImgRC(SUB_COMMON_IMG_LOGO)
#endif
		WdgEnd(CLSID_VTMIMG,tSubLogo)
	WndEnd(ONAPP_SUB_WND_LOGO)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
// refer to _CreateSubPowerOnAnimWindow()
	WndBegin(ONAPP_SUB_WND_POWER_ON_ANIMATION)
		WdgBegin(CLSID_VTMIMG,tSubAnimation)
			VtmCreateImgRC(SUB_COMMON_IMG_POWERON_ANIM01)
		WdgEnd(CLSID_VTMIMG,tSubAnimation)
	WndEnd(ONAPP_SUB_WND_POWER_ON_ANIMATION)
//<------------------------------------------------------------------------------

//------------------------------------------------------------------------------>
// refer to _CreateSubSearchNetworkWindow()
	WndBegin(ONAPP_SUB_WND_SEARCH_NETWORK)
		WdgBegin(CLSID_VTMIMG,tSubSearchNetwork)
			VtmCreateImgRC(SUB_COMMON_IMG_NETWORK_SEARCH_ANIM)
		WdgEnd(CLSID_VTMIMG,tSubSearchNetwork)
	WndEnd(ONAPP_SUB_WND_SEARCH_NETWORK)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreateSubChargingWindow()
	WndBegin(ONAPP_SUB_WND_CHARGING)
		WdgBegin(CLSID_VTMIMG,tSubCharging)
			VtmCreateImgRC(SUB_COMMON_IMG_POWEROFF_CHARGING_ANIM)
		WdgEnd(CLSID_VTMIMG,tSubCharging)
	WndEnd(ONAPP_SUB_WND_CHARGING)
//<------------------------------------------------------------------------------


//------------------------------------------------------------------------------>
// refer to _CreateSubChargerFullWindow()
	WndBegin(ONAPP_SUB_WND_CHARGER_FULL)
		WdgBegin(CLSID_VTMIMG,tSubChargerFull)
			VtmCreateImgRC(SUB_COMMON_IMG_POWEROFF_CHARGE_FULL)
		WdgEnd(CLSID_VTMIMG,tSubChargerFull)
	WndEnd(ONAPP_SUB_WND_CHARGER_FULL)
//<------------------------------------------------------------------------------

#endif // __DUAL_LCD__

#ifdef __DUAL_BATT_MMI__
//------------------------------------------------------------------------------>
// refer to _CreateDualBatWindow()
	WndBegin(ONAPP_WND_DUALBATTERY_CHARGER)
        WdgBegin(CLSID_IMAGEWIDGET,Bat1ImgWdg)
            WdgImageCreateForWndRC({{ONAPP_BATTERY_IMG1_IMAGEWIDGET_POS_X,ONAPP_BATTERY_IMG1_IMAGEWIDGET_POS_Y},{ONAPP_BATTERY_IMG_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_IMG_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,Bat1ImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,Bat2ImgWdg)
            WdgImageCreateForWndRC({{ONAPP_BATTERY_IMG2_IMAGEWIDGET_POS_X,ONAPP_BATTERY_IMG2_IMAGEWIDGET_POS_Y},{ONAPP_BATTERY_IMG_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_IMG_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,Bat2ImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,Id1ImgWdg)
            WdgImageCreateForWndRC({{ONAPP_BATTERY_ID1_IMAGEWIDGET_POS_X,ONAPP_BATTERY_ID1_IMAGEWIDGET_POS_Y},{ONAPP_BATTERY_ID_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_ID_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,Id1ImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,Id12mgWdg)
            WdgImageCreateForWndRC({{ONAPP_BATTERY_ID2_IMAGEWIDGET_POS_X,ONAPP_BATTERY_ID2_IMAGEWIDGET_POS_Y},{ONAPP_BATTERY_ID_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_ID_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,Id2ImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,DBBgImgWdg)
            WdgImageCreateForWndRC({{0,0},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetBGColorRC(DEF_THM_OFFAPP_BUTTON_TEXT)
        WdgEnd(CLSID_IMAGEWIDGET,DBBgImgWdg)
	WndEnd(ONAPP_WND_DUALBATTERY_CHARGER)
//<------------------------------------------------------------------------------
//------------------------------------------------------------------------------>
// refer to _CreateDualBatSingleWindow()
	WndBegin(ONAPP_WND_DUALBATTERY_SINGLE_CHARGER)
        WdgBegin(CLSID_IMAGEWIDGET,BatImgWdg)
            WdgImageCreateForWndRC({{ONAPP_BATTERY_IMG_IMAGEWIDGET_POS_X,ONAPP_BATTERY_IMG_IMAGEWIDGET_POS_Y},{ONAPP_BATTERY_IMG_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_IMG_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,BatImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,IdImgWdg)
            WdgImageCreateForWndRC({{220,105},{ONAPP_BATTERY_ID_IMAGEWIDGET_WIDTH,ONAPP_BATTERY_ID_IMAGEWIDGET_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetAlignmentRC((ALIGN_H_CENTER|ALIGN_V_MIDDLE))
        WdgEnd(CLSID_IMAGEWIDGET,IdImgWdg)
        WdgBegin(CLSID_IMAGEWIDGET,DBSBgImgWdg)
            WdgImageCreateForWndRC({{0,0},{MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},IMAGE_STYLE_COMMON,{FALSE,IMG_NULL_ID}})
            WdgCommonSetBGColorRC(DEF_THM_OFFAPP_BUTTON_TEXT)
        WdgEnd(CLSID_IMAGEWIDGET,DBSBgImgWdg)
	WndEnd(ONAPP_WND_DUALBATTERY_SINGLE_CHARGER)
//<------------------------------------------------------------------------------
#endif

ApEnd(RS,CLSID_ONAPP)

