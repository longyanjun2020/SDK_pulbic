ApBegin(RS,CLSID_BMI)
    WndBegin(BMI_WND_CALCULATOR)
        WndSetTitleRC({IMG_NULL_ID,TXT_LIL_N_BMI})
        WndSetStatusBarVisibleRC(VIEWSB_INVISIABLE)
        WndSetSoftkeyVisibleRC(VIEWSK_VISIABLE)

        WdgBegin(CLSID_TEXTWIDGET,HeightTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_LABEL_OFFSET,BMI_RS_HEIGHT_TXT_POS_Y},{BMI_CALCULATOR_LABEL_WIDTH,BMI_CALCULATOR_TEXT_LINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_BMI_HEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,HeightTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,HeightValueTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_VALUE_X_OFFSET,BMI_RS_HEIGHT_TXT_POS_Y+BMI_CALCULATOR_VALUE_Y_OFFSET},{BMI_CALCULATOR_VALUE_WIDTH,BMI_CALCULATOR_TEXT_LINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgCommonSetBGColorRC(DEF_THM_BMIAPP_VALUE_BG)
            WdgCommonSetBorderDataRC({1,1,1,1,DEF_THM_BMIAPP_VALUE_BORDER})
        WdgEnd(CLSID_TEXTWIDGET,HeightValueTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,WeightTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_LABEL_OFFSET,BMI_RS_WEIGHT_TXT_POS_Y},{BMI_CALCULATOR_LABEL_WIDTH,BMI_CALCULATOR_TEXT_LINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_BMI_WEIGHT)
        WdgEnd(CLSID_TEXTWIDGET,WeightTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,WeightValueTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_VALUE_X_OFFSET,BMI_RS_WEIGHT_TXT_POS_Y+BMI_CALCULATOR_VALUE_Y_OFFSET},{BMI_CALCULATOR_VALUE_WIDTH,BMI_CALCULATOR_TEXT_LINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgCommonSetBGColorRC(DEF_THM_BMIAPP_VALUE_BG)
            WdgCommonSetBorderDataRC({1,1,1,1,DEF_THM_BMIAPP_VALUE_BORDER})
        WdgEnd(CLSID_TEXTWIDGET,WeightValueTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,BmiLimitTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_LABEL_OFFSET,BMI_RS_LIMIT_TXT_POS_Y},{BMI_CALCULATOR_DESCRIPTION_WIDTH,BMI_RS_LIMIT_TXT_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_CENTER))
            WdgCommonSetFontCategoryRC(FONT_CAT_SUPERSMALL)
            WdgTextSetDataByIDRC(TXT_PML_N_BMI_LIMIT)
        WdgEnd(CLSID_TEXTWIDGET,BmiLimitTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,JudgementTextWdg)
            WdgTextCreateForWndRC({{BMI_CALCULATOR_LABEL_OFFSET,BMI_RS_JUDGEMENT_TXT_POS_Y},{BMI_CALCULATOR_DESCRIPTION_WIDTH,BMI_CALCULATOR_TEXT_LINE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_START))
            WdgTextSetDataByIDRC(TXT_LIL_N_BMI)
        WdgEnd(CLSID_TEXTWIDGET,JudgementTextWdg)
        WdgBegin(CLSID_TEXTWIDGET,BmiValueTextWdg)
            WdgTextCreateForWndRC({{BMI_VALUE_TEXT_X_SHIFT,BMI_RS_VALUE_POS_Y},{BMI_VALUE_TEXT_WIDTH,BMI_RS_VALUE_HEIGHT},TEXT_STYLE_COMMON})
            WdgCommonSetAlignmentRC((ALIGN_V_MIDDLE|ALIGN_H_CENTER))
            WdgCommonSetBorderDataRC({1,1,1,1,DEF_THM_BMIAPP_VALUE_BORDER})
        WdgEnd(CLSID_TEXTWIDGET,BmiValueTextWdg)
        WdgBegin(CLSID_IMAGEWIDGET,ValueBgImageWdg)
            WdgImageCreateForWndRC({{BMI_RS_VALUE_BG_IMG_POS_X,BMI_RS_VALUE_BG_IMG_POS_Y},{BMI_VALUE_BG_IMAGE_WIDTH,BMI_RS_VALUE_BG_IMG_HEIGHT},IMAGE_STYLE_COMMON,{TRUE,BMI_IMG_BAR}})
        WdgEnd(CLSID_IMAGEWIDGET,ValueBgImageWdg)
        WdgBegin(CLSID_IMAGEWIDGET,ValueImageWdg)
            WdgImageCreateForWndRC({{BMI_RS_VALUE_IMG_POS_X,BMI_RS_VALUE_IMG_POS_Y},{BMI_VALUE_IMAGE_WIDTH, BMI_RS_VALUE_IMG_HEIGHT},IMAGE_STYLE_COMMON,{TRUE, BMI_IMG_TARGET}})
        WdgEnd(CLSID_IMAGEWIDGET,ValueImageWdg)
        WdgBegin(CLSID_INPUTWIDGET,InputHeightWdg)
            WdgInputCreateForWndRC({{BMI_CALCULATOR_VALUE_X_OFFSET,BMI_RS_HEIGHT_TXT_POS_Y+BMI_CALCULATOR_VALUE_Y_OFFSET},{BMI_CALCULATOR_VALUE_WIDTH,BMI_CALCULATOR_INPUT_HEIGHT},{TRUE,SKBOARD_ENABLE}})
            WdgInputSetCurrentInputModeRC(MAE_INPUTMODE_RATE)
/*            WdgInputSetDecimalPointEnableRC(TRUE)*/
/*            WdgInputSetMaxlenAfterDecimalPointRC(1)*/
/*            WdgInputSetMaxByteLengthRC(10)*/
/*            WdgInputSetSoftKeyBoardAlwaysOnRC(TRUE)*/
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
/*            WdgInputSetHandWritingEnableRC(FALSE)*/
/*            WdgInputSetSoftKeyBoardAlwaysOnRC(TRUE)*/
            WdgCommonSetPaddingDataRC({BMI_RS_PADDING_L,0,0,0})
        WdgEnd(CLSID_INPUTWIDGET,InputHeightWdg)
        WdgBegin(CLSID_INPUTWIDGET,InputWeightWdg)
            WdgInputCreateForWndRC({{BMI_CALCULATOR_VALUE_X_OFFSET,BMI_RS_WEIGHT_TXT_POS_Y+BMI_CALCULATOR_VALUE_Y_OFFSET},{BMI_CALCULATOR_VALUE_WIDTH,BMI_CALCULATOR_INPUT_HEIGHT},{TRUE,SKBOARD_ENABLE}})
            WdgInputSetCurrentInputModeRC(MAE_INPUTMODE_RATE)
/*            WdgInputSetDecimalPointEnableRC(TRUE)*/
/*            WdgInputSetMaxlenAfterDecimalPointRC(1)*/
/*            WdgInputSetMaxByteLengthRC(10)*/
            WdgCommonSetFontCategoryRC(FONT_CAT_NORMAL)
/*            WdgInputSetHandWritingEnableRC(FALSE)*/
            WdgCommonSetPaddingDataRC({BMI_RS_PADDING_L,0,0,0})
        WdgEnd(CLSID_INPUTWIDGET,InputWeightWdg)
    WndEnd(BMI_WND_CALCULATOR)

    WndBegin(BMI_WND_CUS)
    	RSCustomize(WPos_t,tWPosViewer,{TRUE, BMI_RS_CUS_POS_X, BMI_RS_CUS_POS_Y})
    WndEnd(BMI_WND_CUS)
/*
    WndBegin(BMI_WND_HISTORY)
        WdgBegin(CLSID_VTMMENU,tMenuWdgList)
            VtmCreateMenuRC({{BMI_VALUE_BG_IMAGE_POS_X,MAIN_LCD_ONELINE_HEIGHT*6},{BMI_VALUE_BG_IMAGE_WIDTH,MAIN_LCD_ONELINE_HEIGHT*2},IMAGE_STYLE_COMMON,{TRUE,TRUE,BMI_IMG_BAR,NULL},BMI_IMG_BAR})
        WdgEnd(CLSID_VTMMENU,tMenuWdgList)
    WndEnd(BMI_WND_HISTORY)
*/
/*
    WndBegin(BMI_WND_VIEWER)
        WdgBegin(CLSID_IMAGEWIDGET,IValueBgImageWdg)
            WdgCommonSetBGColorRC,IBmiValueTextWdg,, nRGBColor
        WdgEnd(CLSID_IMAGEWIDGET,IValueBgImageWdg)
    WndEnd(BMI_WND_VIEWER)
*/
/*
    WndBegin(BMI_WND_OPTION)
        WdgBegin(CLSID_VTMOPTIONMENU,tOptionMenuWdgList)
            VtmCreateOptionMenuRC({{BMI_VALUE_BG_IMAGE_POS_X,MAIN_LCD_ONELINE_HEIGHT*6},{BMI_VALUE_BG_IMAGE_WIDTH,MAIN_LCD_ONELINE_HEIGHT*2},IMAGE_STYLE_COMMON,{TRUE,TRUE,BMI_IMG_BAR,NULL},BMI_IMG_BAR})
        WdgEnd(CLSID_VTMOPTIONMENU,tOptionMenuWdgList)
    WndEnd(BMI_WND_OPTION)
*/
ApEnd(RS,CLSID_BMI)

