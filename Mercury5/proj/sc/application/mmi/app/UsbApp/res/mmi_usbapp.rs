ApBegin(RS,CLSID_USBAPP)
    WndBegin(USB_WND_CONNECT_MENU)
        WndSetTitleVisiableRC( FALSE )
        WndSetStatusBarVisibleRC(VIEWSK_INVISIABLE)
        WndSetAllSoftkeyRC({SK_SELECT, SK_OK, SK_CANCEL})
        WndSetSoftkeyVisibleRC(VIEWSK_VISIABLE)

        WdgBegin(CLSID_NUMERIC_POPUPSELECTWIDGET,MenuWdg)
            WdgMenuCreateForWndRC({{0,0},{MAIN_DEFVIEW_WIDTH,MAIN_DEFVIEW_HEIGHT},WDG_MENU_TYPE_NUMERIC_POPUPSELECT_MENU})
            WdgStaticMenuItemRC(4, {
                            {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_USB_MASS_STORAGE},{IMG_NULL_ID, TXT_LIL_N_MASS_STORAGE}},
                            {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_USB_MODEM       },{IMG_NULL_ID, TXT_LIL_N_MODEM       }},
                            {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_USB_WEBCAM      },{IMG_NULL_ID, TXT_LIL_N_WEBCAM      }},
                            {{MENUMODEL_ITEM_VISABLE,{SK_SELECT,SK_OK,SK_BACK},MNU_USB_PC_SYNC_TOOL},{IMG_NULL_ID, TXT_LIL_N_PC_SYNC_TOOL}},
                            } )

            WdgMenuSetCheckStyleRC(WDG_MENU_CHECK_STYLE_NONE)
            WdgMenuSetFirstItemRC(0)
            WdgMenuSetHighlightedItemRC(0)
            WdgStaticMenuInitRC(WDG_MENU_ITEM_TYPE_IMAGE_TEXT)
        WdgEnd(CLSID_NUMERIC_POPUPSELECTWIDGET,MenuWdg)
    WndEnd(USB_WND_CONNECT_MENU)

    WndBegin(USB_WND_DUALSIM)
        WdgBegin(CLSID_VTMSIMSELECTION,DualSim)
            VtmCreateSimSelectionRC({0,TXT_LIL_N_CDW_SIM_SELECTED})
        WdgEnd(CLSID_VTMSIMSELECTION,DualSim)
    WndEnd(USB_WND_DUALSIM)
ApEnd(RS,CLSID_USBAPP)

