
ApBegin(RS,CLSID_HAMSTERFIGHTAPP)
    WndBegin(HF_WND_MENU)
        WdgBegin(CLSID_IMAGEWIDGET,MenuBGImgWdg)
            WdgImageCreateForWndRC({{0,0},
                                    {MAIN_LCD_WIDTH,MAIN_LCD_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_BEGIN_BACKGROUND}})
        WdgEnd(CLSID_IMAGEWIDGET,MenuBGImgWdg)

        WdgBegin(CLSID_BUTTONWIDGET,MenuButtonWdg)
            WdgButtonCreateForWndRC({{HF_MENU_BTN_POS_X,HF_MENU_BTN_POS_Y},{HF_MENU_BTN_WIDTH,HF_MENU_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HAMSTERFIGHT_IMG_MENU_NEW_GAME_0,HAMSTERFIGHT_IMG_MENU_NEW_GAME_1})
        WdgEnd(CLSID_BUTTONWIDGET,MenuButtonWdg)

        WdgBegin(CLSID_BUTTONWIDGET, MenuSelectLeftBtnWdg)
            WdgButtonCreateForWndRC({{HF_MENU_SELECT_LEFT_BTN_POS_X, HF_MENU_SELECT_LEFT_BTN_POS_Y},{HF_MENU_SELECT_LEFT_BTN_WIDTH, HF_MENU_SELECT_LEFT_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID, HF_IMG_SELECT_LEFT, HF_IMG_SELECT_LEFT})
        WdgEnd(CLSID_BUTTONWIDGET, MenuSelectLeftBtnWdg)

        WdgBegin(CLSID_BUTTONWIDGET, MenuSelectRightBtnWdg)
            WdgButtonCreateForWndRC({{HF_MENU_SELECT_RIGHT_BTN_POS_X, HF_MENU_SELECT_RIGHT_BTN_POS_Y},{HF_MENU_SELECT_RIGHT_BTN_WIDTH, HF_MENU_SELECT_RIGHT_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID, HF_IMG_SELECT_RIGHT, HF_IMG_SELECT_RIGHT})
        WdgEnd(CLSID_BUTTONWIDGET, MenuSelectRightBtnWdg)
    WndEnd(HF_WND_MENU)

    WndBegin(HF_WND_GAME)
        WdgBegin(CLSID_BUTTONWIDGET,GameBackBtnWdg)
            WdgButtonCreateForWndRC({{HF_GAME_BACK_BTN_POS_X,HF_GAME_BACK_BTN_POS_Y},{HF_GAME_BACK_BTN_WIDTH,HF_GAME_BACK_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HF_IMG_RETURN_0,HF_IMG_RETURN_1})
        WdgEnd(CLSID_BUTTONWIDGET,GameBackBtnWdg)

        WdgBegin(CLSID_IMAGEWIDGET,GameBGImgWdg)
            WdgImageCreateForWndRC({{HF_GAME_BG_IMG_POS_X,HF_GAME_BG_IMG_POS_Y},
                                    {HF_GAME_BG_IMG_WIDTH,HF_GAME_BG_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_BACKGROUND}})
        WdgEnd(CLSID_IMAGEWIDGET,GameBGImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,AnimalImgWdg)
            WdgImageCreateForWndRC({{HF_GAME_ANIMAL_IMG_X,HF_GAME_ANIMAL_IMG_Y},
                                    {HF_GAME_ANIMAL_IMG_WIDTH,HF_GAME_ANIMAL_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {FALSE,HF_IMG_ANIMAL_0}})
        WdgEnd(CLSID_IMAGEWIDGET,AnimalImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,GrassShelterImgWdg)
            WdgImageCreateForWndRC({{HF_GRASS_SHELTER_IMG_POS_X,HF_GRASS_SHELTER_IMG_POS_Y},
                                    {HF_GRASS_SHELTER_IMG_WIDTH,HF_GRASS_SHELTER_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_GRASS_SHELTER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,GrassShelterImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HPImgWdg)
            WdgImageCreateForWndRC({{HF_IMG_POS_X,HF_IMG_POS_Y},
                                    {HF_IMG_WIDTH,HF_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_HEALTH_HEART_2}})
        WdgEnd(CLSID_IMAGEWIDGET,HPImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SmallHamsterSignImgWdg)
            WdgImageCreateForWndRC({{HF_SMALL_HAMSTER_SIGN_IMG_POS_X,HF_SMALL_HAMSTER_SIGN_IMG_POS_Y},
                                    {HF_SMALL_HAMSTER_SIGN_IMG_WIDTH,HF_SMALL_HAMSTER_SIGN_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_SMALL_HAMSTER_ICON}})
        WdgEnd(CLSID_IMAGEWIDGET,SmallHamsterSignImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HamsterNumberImgWdg_10)
            WdgImageCreateForWndRC({{HF_NUMER_10_IMG_POS_X,HF_NUMER_10_IMG_POS_Y},
                                    {HF_NUMER_10_IMG_WIDTH,HF_NUMER_10_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NUMBER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,HamsterNumberImgWdg_10)

        WdgBegin(CLSID_IMAGEWIDGET,HamsterNumberImgWdg_1)
            WdgImageCreateForWndRC({{HF_NUMER_1_IMG_POS_X,HF_NUMER_1_IMG_POS_Y},
                                    {HF_NUMER_1_IMG_WIDTH,HF_NUMER_1_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NUMBER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,HamsterNumberImgWdg_1)

        WdgBegin(CLSID_IMAGEWIDGET,CDMotionImgWdg)
            WdgImageCreateForWndRC({{HF_CD_MOTION_POS_X,HF_CD_MOTION_POS_Y},
                                    {HF_CD_MOTION_WIDTH,HF_CD_MOTION_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_COUNT_DOWN_TIMER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,CDMotionImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,LevelNumberImgWdg)
            WdgImageCreateForWndRC({{HF_LEVEL_NUMBER_IMG_POS_X,HF_LEVEL_NUMBER_IMG_POS_Y},
                                    {HF_LEVEL_NUMBER_IMG_WIDTH,HF_LEVEL_NUMBER_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NUMBER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,LevelNumberImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HammerMotionImgWdg)
            WdgImageCreateForWndRC({{HF_MOTION_POS_X,HF_MOTION_POS_Y},
                                    {HF_MOTION_WIDTH,HF_MOTION_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_HAMMER}})
        WdgEnd(CLSID_IMAGEWIDGET,HammerMotionImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,SparkImgWdg)
            WdgImageCreateForWndRC({{HF_SPARK_IMG_POS_X,HF_SPARK_IMG_POS_Y},
                                    {HF_SPARK_IMG_WIDTH,HF_SPARK_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_SPARK_1}})
        WdgEnd(CLSID_IMAGEWIDGET,SparkImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HitSignImgWdg)
            WdgImageCreateForWndRC({{HF_HIT_SIGN_IMG_POS_X,HF_HIT_SIGN_IMG_POS_Y},
                                    {HF_HIT_SIGN_IMG_WIDTH,HF_HIT_SIGN_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_HIT}})
        WdgEnd(CLSID_IMAGEWIDGET,HitSignImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,GameMultiSignImgWdg)
            WdgImageCreateForWndRC({{HF_MULTI_SIGN_IMG_POS_X,HF_MULTI_SIGN_IMG_POS_Y},
                                    {HF_MULTI_SIGN_IMG_WIDTH,HF_MULTI_SIGN_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_MULTI_SIGN}})
        WdgEnd(CLSID_IMAGEWIDGET,GameMultiSignImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,ComboNumberImgWdg_1)
            WdgImageCreateForWndRC({{HF_COMBO_NUMBER_1_IMG_POS_X,HF_COMBO_NUMBER_1_IMG_POS_Y},
                                    {HF_COMBO_NUMBER_1_IMG_WIDTH,HF_COMBO_NUMBER_1_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NUMBER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,ComboNumberImgWdg_1)

        WdgBegin(CLSID_IMAGEWIDGET,ComboNumberImgWdg_10)
            WdgImageCreateForWndRC({{HF_COMBO_NUMBER_10_IMG_POS_X,HF_COMBO_NUMBER_10_IMG_POS_Y},
                                    {HF_COMBO_NUMBER_10_IMG_WIDTH,HF_COMBO_NUMBER_10_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NUMBER_0}})
        WdgEnd(CLSID_IMAGEWIDGET,ComboNumberImgWdg_10)

        WdgBegin(CLSID_IMAGEWIDGET,WinGameImgWdg)
            WdgImageCreateForWndRC({{HF_WIN_GAME_IMG_POS_X,HF_WIN_GAME_IMG_POS_Y},
                                    {HF_WIN_GAME_IMG_WIDTH,HF_WIN_GAME_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_NEXT_GAME}})
        WdgEnd(CLSID_IMAGEWIDGET,WinGameImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,LoseGameImgWdg)
            WdgImageCreateForWndRC({{HF_LOSE_GAME_IMG_POS_X,HF_LOSE_GAME_IMG_POS_Y},
                                    {HF_LOSE_GAME_IMG_WIDTH,HF_LOSE_GAME_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_LOSE_GAME}})
        WdgEnd(CLSID_IMAGEWIDGET,LoseGameImgWdg)
    WndEnd(HF_WND_GAME)

    WndBegin(HF_WND_OPTIONS)
        WdgBegin(CLSID_IMAGEWIDGET,OptionsBGImgWdg)
            WdgImageCreateForWndRC({{HF_OPTION_BG_IMG_POS_X,HF_OPTION_BG_IMG_POS_Y},
                                    {HF_OPTION_BG_IMG_WIDTH,HF_OPTION_BG_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_BACKGROUND}})
        WdgEnd(CLSID_IMAGEWIDGET,OptionsBGImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,OptionsFadeoutWdg)
            WdgImageCreateForWndRC({{HF_OPTION_FADE_OUT_POS_X,HF_OPTION_FADE_OUT_POS_Y},
                                      {HF_OPTION_FADE_OUT_WIDTH,HF_OPTION_FADE_OUT_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_OPTIONS_BG}})
        WdgEnd(CLSID_IMAGEWIDGET,OptionsFadeoutWdg)

        WdgBegin(CLSID_TEXTWIDGET,OptionsTxtSoundWdg)
            WdgTextCreateForWndRC({{HF_OPTION_TXT_SOUND_POS_X,HF_OPTION_TXT_SOUND_POS_Y},
                                   {HF_OPTION_TXT_SOUND_WIDTH,HF_OPTION_TXT_SOUND_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_OPTIONS_SOUND)
            WdgCommonSetFontCategoryRC(HF_OPTION_TXT_SOUND_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_OPTION_TXT_SOUND_COLOR)
            WdgCommonSetAlignmentRC(HF_OPTION_TXT_SOUND_ALIGN)
        WdgEnd(CLSID_TEXTWIDGET,OptionsTxtSoundWdg)
        
			WdgBegin(CLSID_BUTTONWIDGET,OptionsSoundSwitchBtnWdg)
				WdgButtonCreateForWndRC({{HF_OPTION_SOUND_SWITCH_BTN_POS_X,HF_OPTION_SOUND_SWITCH_BTN_POS_Y},{HF_OPTION_SOUND_SWITCH_BTN_WIDTH,HF_OPTION_SOUND_SWITCH_BTN_HEIGHT}})
				WdgButtonSetDataByIDRC({TXT_NULL_ID, HF_IMG_OPTIONS_CLICK, HF_IMG_OPTIONS_CLOSE})
			WdgEnd(CLSID_BUTTONWIDGET,OptionsSoundSwitchBtnWdg)

        WdgBegin(CLSID_IMAGEWIDGET,OptionsImgFrameWdg)
            WdgImageCreateForWndRC({{HF_OPTION_IMG_FRAME_POS_X,HF_OPTION_IMG_FRAME_POS_Y},
                                    {HF_OPTION_IMG_FRAME_WIDTH,HF_OPTION_IMG_FRAME_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_OPTIONS_FRAME}})
        WdgEnd(CLSID_IMAGEWIDGET,OptionsImgFrameWdg)

        WdgBegin(CLSID_TEXTWIDGET,OptionsTxtDefaultPicWdg)
            WdgTextCreateForWndRC({{HF_OPTION_TXT_DEFAULT_PIC_POS_X,HF_OPTION_TXT_DEFAULT_PIC_POS_Y},
                                   {HF_OPTION_TXT_DEFAULT_PIC_WIDTH,HF_OPTION_TXT_DEFAULT_PIC_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_OPTIONS_PICTURES)
            WdgCommonSetFontCategoryRC(HF_OPTION_TXT_CHANGE_PIC_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_OPTION_TXT_CHANGE_PIC_COLOR)
            WdgCommonSetAlignmentRC(HF_OPTION_TXT_CHANGE_PIC_ALIGN)
        WdgEnd(CLSID_TEXTWIDGET,OptionsTxtDefaultPicWdg)

        WdgBegin(CLSID_IMAGEWIDGET,OptionsImgDefaultPicWdg)
            WdgImageCreateForWndRC({{HF_OPTION_IMG_DEFAULT_PIC_POS_X,HF_OPTION_IMG_DEFAULT_PIC_POS_Y},
                                    {HF_OPTION_IMG_DEFAULT_PIC_WIDTH,HF_OPTION_IMG_DEFAULT_PIC_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {FALSE,HF_IMG_ANIMAL_0}})
        WdgEnd(CLSID_IMAGEWIDGET,OptionsImgDefaultPicWdg)


        WdgBegin(CLSID_TEXTWIDGET,OptionsTxtStartCameraWdg)
            WdgTextCreateForWndRC({{HF_OPTION_TXT_START_CAMERA_POS_X,HF_OPTION_TXT_START_CAMERA_POS_Y},
                                   {HF_OPTION_TXT_START_CAMERA_WIDTH,HF_OPTION_TXT_START_CAMERA_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_OPTIONS_START_CAMERA)
            WdgCommonSetFontCategoryRC(HF_OPTION_TXT_START_CAMERA_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_OPTION_TXT_START_CAMERA_COLOR)
            WdgCommonSetAlignmentRC(HF_OPTION_TXT_START_CAMERA_ALIGN)
        WdgEnd(CLSID_TEXTWIDGET,OptionsTxtStartCameraWdg)

        WdgBegin(CLSID_BUTTONWIDGET,OptionsCameraBtnWdg)
            WdgButtonCreateForWndRC({{HF_OPTION_CAMERA_BTN_POS_X,HF_OPTION_CAMERA_BTN_POS_Y},{HF_OPTION_CAMERA_BTN_WIDTH,HF_OPTION_CAMERA_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HF_IMG_OPTIONS_CAMERA_UNPRESSED,HF_IMG_OPTIONS_CAMERA_PRESSED})
        WdgEnd(CLSID_BUTTONWIDGET,OptionsCameraBtnWdg)

        WdgBegin(CLSID_TEXTWIDGET,OptionsTxtChangePicWdg)
            WdgTextCreateForWndRC({{HF_OPTION_TXT_CHANGE_PIC_POS_X,HF_OPTION_TXT_CHANGE_PIC_POS_Y},
                                   {HF_OPTION_TXT_CHANGE_PIC_WIDTH,HF_OPTION_TXT_CHANGE_PIC_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_OPTIONS_CHANGE_PIC)
            WdgCommonSetFontCategoryRC(HF_OPTION_TXT_CHANGE_PIC_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_OPTION_TXT_CHANGE_PIC_COLOR)
            WdgCommonSetAlignmentRC(HF_OPTION_TXT_CHANGE_PIC_ALIGN)
        WdgEnd(CLSID_TEXTWIDGET,OptionsTxtChangePicWdg)

        WdgBegin(CLSID_BUTTONWIDGET,OptionsChangePicBtnWdg)
            WdgButtonCreateForWndRC({{HF_OPTION_CHANGE_PIC_BTN_POS_X,HF_OPTION_CHANGE_PIC_BTN_POS_Y},{HF_OPTION_CHANGE_PIC_BTN_WIDTH,HF_OPTION_CHANGE_PIC_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HF_IMG_OPTIONS_SELECT_FILE_UNPRESSED,HF_IMG_OPTIONS_SELECT_FILE_PRESSED})
        WdgEnd(CLSID_BUTTONWIDGET,OptionsChangePicBtnWdg)

		WdgBegin(CLSID_BUTTONWIDGET,OptionsBackDefaultBtnWdg)
			WdgButtonCreateForWndRC({{HF_OPTION_BACK_DEFAULT_BTN_POS_X,HF_OPTION_BACK_DEFAULT_BTN_POS_Y},{HF_OPTION_BACK_DEFAULT_BTN_WIDTH,HF_OPTION_BACK_DEFAULT_BTN_HEIGHT}})
			WdgButtonSetDataByIDRC({TXT_LIL_N_HAMSTERFIGHTAPP_OPTIONS_BACK_DEFAULT, HF_IMG_OPTIONS_BTN_BG_UNPRESSED, HF_IMG_OPTIONS_BTN_BG_PRESSED})
			WdgCommonSetFontCategoryRC(HF_OPTION_BACK_DEFAULT_BTN_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_OPTION_BACK_DEFAULT_BTN_COLOR)
            WdgCommonSetAlignmentRC(HF_OPTION_BACK_DEFAULT_BTN_ALIGN)
		WdgEnd(CLSID_BUTTONWIDGET,OptionsBackDefaultBtnWdg)

        WdgBegin(CLSID_BUTTONWIDGET,OptionsBackBtnWdg)
            WdgButtonCreateForWndRC({{HF_OPTION_BACK_BTN_POS_X,HF_OPTION_BACK_BTN_POS_Y},{HF_OPTION_BACK_BTN_WIDTH,HF_OPTION_BACK_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HF_IMG_RETURN_0,HF_IMG_RETURN_1})
        WdgEnd(CLSID_BUTTONWIDGET,OptionsBackBtnWdg)

    WndEnd(HF_WND_OPTIONS)

    WndBegin(HF_WND_HELP)
        WdgBegin(CLSID_IMAGEWIDGET,HelpBGImgWdg)
            WdgImageCreateForWndRC({{HF_HELP_BG_IMG_POS_X,HF_HELP_BG_IMG_POS_Y},
                                    {HF_HELP_BG_IMG_WIDTH,HF_HELP_BG_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_BACKGROUND}})
        WdgEnd(CLSID_IMAGEWIDGET,HelpBGImgWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HelpFadeoutWdg)
            WdgFadeoutCreateForWndRC({{HF_HELP_FADE_OUT_IMG_POS_X,HF_HELP_FADE_OUT_IMG_POS_Y},
                                      {HF_HELP_FADE_OUT_IMG_WIDTH,HF_HELP_FADE_OUT_IMG_HEIGHT},
                                      FADEOUT_LEVEL_1})
        WdgEnd(CLSID_IMAGEWIDGET,HelpFadeoutWdg)

        WdgBegin(CLSID_TEXTWIDGET,HelpTxtContentWdg)
            WdgTextCreateForWndRC({{HF_HELP_TXT_CONTENT_POS_X,HF_HELP_TXT_CONTENT_POS_Y},
                                   {HF_HELP_TXT_CONTENT_WIDTH,HF_HELP_TXT_CONTENT_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_HELP_CONTENT)
            WdgCommonSetFontCategoryRC(HF_HELP_TXT_CONTENT_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_HELP_TXT_CONTENT_COLOR)
            WdgCommonSetAlignmentRC(HF_HELP_TXT_CONTENT_ALIGN)
            WdgTextSetLayoutFlagRC(HF_HELP_TXT_CONTENT_LAYOUT_FLAG)
        WdgEnd(CLSID_TEXTWIDGET,HelpTxtContentWdg)

        WdgBegin(CLSID_TEXTWIDGET,HelpTxtNoticeWdg)
            WdgTextCreateForWndRC({{HF_HELP_TXT_NOTICE_POS_X,HF_HELP_TXT_NOTICE_POS_Y},
                                   {HF_HELP_TXT_NOTICE_WIDTH,HF_HELP_TXT_NOTICE_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_HELP_NOTICE)
            WdgCommonSetFontCategoryRC(HF_HELP_TXT_NOTICE_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_HELP_TXT_NOTICE_COLOR)
            WdgCommonSetAlignmentRC(HF_HELP_TXT_NOTICE_ALIGN)
            WdgTextSetLayoutFlagRC(HF_HELP_TXT_NOTICE_LAYOUT_FLAG)
        WdgEnd(CLSID_TEXTWIDGET,HelpTxtNoticeWdg)

        WdgBegin(CLSID_TEXTWIDGET,HelpTxtRuleWdg)
            WdgTextCreateForWndRC({{HF_HELP_TXT_RULE_POS_X,HF_HELP_TXT_RULE_POS_Y},
                                   {HF_HELP_TXT_RULE_WIDTH,HF_HELP_TXT_RULE_HEIGHT},
                                   TEXT_STYLE_COMMON})
            WdgTextSetDataByIDRC(TXT_LIL_N_HAMSTERFIGHTAPP_HELP_RULE)
            WdgCommonSetFontCategoryRC(HF_HELP_TXT_RULE_CAT)
            WdgCommonSetTextColorRC((RGBColor_t)HF_HELP_TXT_RULE_COLOR)
            WdgCommonSetAlignmentRC(HF_HELP_TXT_RULE_ALIGN)
            WdgTextSetLayoutFlagRC(HF_HELP_TXT_RULE_LAYOUT_FLAG)
        WdgEnd(CLSID_TEXTWIDGET,HelpTxtRuleWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HelpImgHitWdg)
            WdgImageCreateForWndRC({{HF_HELP_HIT_IMG_POS_X,HF_HELP_HIT_IMG_POS_Y},
                                    {HF_HELP_HIT_IMG_WIDTH,HF_HELP_HIT_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_HIT}})
        WdgEnd(CLSID_IMAGEWIDGET,HelpImgHitWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HelpImgMultiSignWdg)
            WdgImageCreateForWndRC({{HF_HELP_MULTI_SIGN_IMG_POS_X,HF_HELP_MULTI_SIGN_IMG_POS_Y},
                                    {HF_HELP_MULTI_SIGN_IMG_WIDTH,HF_HELP_MULTI_SIGN_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HF_IMG_MULTI_SIGN}})
        WdgEnd(CLSID_IMAGEWIDGET,HelpImgMultiSignWdg)

        WdgBegin(CLSID_IMAGEWIDGET,HelpImgGetHPWdg)
            WdgImageCreateForWndRC({{HF_HELP_GET_HP_IMG_POS_X,HF_HELP_GET_HP_IMG_POS_Y},
                                    {HF_HELP_GET_HP_IMG_WIDTH,HF_HELP_GET_HP_IMG_HEIGHT},
                                    IMAGE_STYLE_COMMON,
                                    {TRUE,HAMSTERFIGHT_IMG_GET_HEALTH_POINT}})
        WdgEnd(CLSID_IMAGEWIDGET,HelpImgGetHPWdg)

        WdgBegin(CLSID_BUTTONWIDGET,HelpBackBtnWdg)
            WdgButtonCreateForWndRC({{HF_HELP_BACK_BTN_POS_X,HF_HELP_BACK_BTN_POS_Y},{HF_HELP_BACK_BTN_WIDTH,HF_HELP_BACK_BTN_HEIGHT}})
            WdgButtonSetDataByIDRC({TXT_NULL_ID,HF_IMG_RETURN_0,HF_IMG_RETURN_1})
        WdgEnd(CLSID_BUTTONWIDGET,HelpBackBtnWdg)
    WndEnd(HF_WND_HELP)
    WndBegin(HF_WND_COMMON)
    RSCustomize(u32,nAnimImgWidth, HF_ANIMAL_IMG_WIDTH)
    RSCustomize(u32,nAnimImgHeight, HF_ANIMAL_IMG_HEIGHT)
    RSCustomize(s32,nAnimImgPosX, HF_ANIMAL_IMG_WDG_POS_X)
    RSCustomize(s32,nAnimImgPosY, HF_ANIMAL_IMG_WDG_POS_Y)
    RSCustomize(s32,nAnimMotionPosIncY, HF_ANIMAL_MOTION_POS_INC_Y)
    RSCustomize(s32,nGrassShelterPosX, HF_GRASS_SHELTER_WDG_POS_X)
    RSCustomize(s32,nGrassShelterPosY, HF_GRASS_SHELTER_WDG_POS_Y)
    RSCustomize(u32,nHoldPosIncX, HF_GAME_HOLE_POS_INC_X)
    RSCustomize(u32,nHoldPosIncY, HF_GAME_HOLE_POS_INC_Y)
    RSCustomize(u32,nValidHammerHitAreaWidth, HF_VALID_HAMMER_HIT_AREA_WIDTH)
    RSCustomize(u32,nValidHammerHitAreaHeight, HF_VALID_HAMMER_HIT_AREA_HEIGHT)
    RSCustomize(u32,nValidHammerHitAreaPosX, HF_VALID_HAMMER_HIT_AREA_POS_X)
    RSCustomize(u32,nValidHammerHitAreaPosY, HF_VALID_HAMMER_HIT_AREA_POS_Y)
	RSCustomize(s32,nHammerPosX, HF_HAMMER_WDG_POS_X)
    RSCustomize(s32,nHammerPosY, HF_HAMMER_WDG_POS_Y)
    RSCustomize(u16,nSpark1PosX, HF_SPARK_1_WDG_POS_X)
    RSCustomize(u16,nSpark1PosY, HF_SPARK_1_WDG_POS_Y)
    RSCustomize(u16,nSpark2PosX, HF_SPARK_2_WDG_POS_X)
    RSCustomize(u16,nSpark2PosY, HF_SPARK_2_WDG_POS_Y)
    RSCustomize(u16,nSpark3PosX, HF_SPARK_3_WDG_POS_X)
    RSCustomize(u16,nSpark3PosY, HF_SPARK_3_WDG_POS_Y)
    RSCustomize(u32,nSparkMotionIncX, HF_SPARK_MOTION_WDG_INC_X)
    RSCustomize(u32,nSparkMotionIncY, HF_SPARK_MOTION_WDG_INC_Y)
    RSCustomize(s32,nHitSignPosX, HF_HIT_SIGN_WDG_POS_X)
    RSCustomize(s32,nHitSignPosY, HF_HIT_SIGN_WDG_POS_Y)
    RSCustomize(s32,nHitMultiSignPosX, HF_GAME_MULTI_SIGN_POS_X)
    RSCustomize(s32,nHitMultiSignPosY, HF_GAME_MULTI_SIGN_POS_Y)
    RSCustomize(s32,nComboNum1PosX, HF_COMBO_NUMBER_WDG_1_POS_X)
    RSCustomize(s32,nComboNum1PosY, HF_COMBO_NUMBER_WDG_1_POS_Y)
    RSCustomize(s32,nComboNum10PosX, HF_COMBO_NUMBER_WDG_10_POS_X)
    RSCustomize(s32,nComboNum10PosY, HF_COMBO_NUMBER_WDG_10_POS_Y)
    RSCustomize(u32,nShockMotionDistanceY, HF_SHOCK_MOTION_DISTANCE_Y)
    RSCustomize(s32,nHPWidgetPosX, HF_HP_WDG_POS_X)
    RSCustomize(s32,nHPWidgetPosY, HF_HP_WDG_POS_Y)
    RSCustomize(u32,nHPDistanceX, HF_HP_WDG_DISTANCE_X)
    RSCustomize(s32,nWinGamePosX, HF_WIN_GAME_WDG_POS_X)
    RSCustomize(s32,nWinGamePosY, HF_WIN_GAME_WDG_POS_Y)
    RSCustomize(u32,nWinGamePosIncX, HF_WIN_GAME_WDG_POS_INC_X)
    RSCustomize(s32,nLoseGamePosX, HF_LOSE_GAME_WDG_POS_X)
	RSCustomize(s32,nLoseGamePosY, HF_LOSE_GAME_WDG_POS_Y)
    RSCustomize(u32,nLoseGamePosIncY, HF_LOSE_GAME_WDG_POS_INC_Y)

	RSCustomize(u32,nCountDownMotionImgAlign, HF_COUNT_DOWN_ALIGN) 

	RSCustomize(u32,nAnimalOut, HAMSTERFIGHT_ANIMAL_OUT)
    RSCustomize(u32,nHammerHit, HAMSTERFIGHT_HAMMER_HIT)
	RSCustomize(u32,nGameWin, HAMSTERFIGHT_WIN_GAME)
    RSCustomize(u32,nGameLose, HAMSTERFIGHT_LOSE_GAME)
	
    WndEnd(HF_WND_COMMON)
ApEnd(RS,CLSID_HAMSTERFIGHTAPP)
