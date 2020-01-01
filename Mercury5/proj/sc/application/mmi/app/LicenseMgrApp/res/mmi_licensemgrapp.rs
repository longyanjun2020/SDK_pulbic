ApBegin(RS,CLSID_LICENSEMGRAPP)
    WndBegin(LICENSEMGR_WND_DETAIL)
        WndSetAllSoftkeyRC({SK_NONE, SK_OK, SK_NONE})
        WndSetTitleRC({IMG_NULL_ID,TXT_LTL_N_VIEW_DETAILS})

#if 0
        WdgBegin(CLSID_TEXTWIDGET,SummaryLableWdg)
            WdgTextCreateForWndRC({{0, MAIN_LCD_ONELINE_HEIGHT},{MAIN_LCD_WIDTH,MAIN_LCD_ONELINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_LICENSEMGRAPP_SUMMARY)
            WdgCommonSetTextColorRC(RGBCOLOR_BLACK)
        WdgEnd(CLSID_TEXTWIDGET,SummaryLableWdg)

        WdgBegin(CLSID_TEXTWIDGET,TypeLableWdg)
            WdgTextCreateForWndRC({{0, MAIN_LCD_ONELINE_HEIGHT*2},{MAIN_LCD_WIDTH,MAIN_LCD_ONELINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgCommonSetTextColorRC(RGBCOLOR_BLACK)
        WdgEnd(CLSID_TEXTWIDGET,TypeLableWdg)

        WdgBegin(CLSID_TEXTWIDGET,UsageCountLableWdg)
            WdgTextCreateForWndRC({{0, MAIN_LCD_ONELINE_HEIGHT*3},{MAIN_LCD_WIDTH,MAIN_LCD_ONELINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_LICENSEMGRAPP_USAGECOUNT_LEFT)
            WdgCommonSetTextColorRC(RGBCOLOR_BLACK)
        WdgEnd(CLSID_TEXTWIDGET,UsageCountLableWdg)

        WdgBegin(CLSID_TEXTWIDGET,UsageCountWdg)
            WdgTextCreateForWndRC({{0, MAIN_LCD_ONELINE_HEIGHT*4},{MAIN_LCD_WIDTH,MAIN_LCD_ONELINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_LICENSEMGRAPP_SUMMARY)
            WdgCommonSetTextColorRC(RGBCOLOR_BLACK)
        WdgEnd(CLSID_TEXTWIDGET,UsageCountWdg)

    WndEnd(LICENSEMGR_WND_DETAIL)
    WndBegin(LICENSEMGR_WND_DETAIL)
#endif
        WdgBegin(CLSID_VTMMENU, LicenseMgrDetailVtm)
			VtmCreateInputRC({IMG_NULL_ID,TXT_LTL_N_VIEW_DETAILS,0,TRUE})
		WdgEnd(CLSID_VTMMENU, LicenseMgrDetailVtm)
    WndEnd(LICENSEMGR_WND_DETAIL)


ApEnd(RS,CLSID_LICENSEMGRAPP)

