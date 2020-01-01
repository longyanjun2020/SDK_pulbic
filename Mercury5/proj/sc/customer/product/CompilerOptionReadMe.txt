//
//When you want to define a new compiler option, please check if this file have suitable compiler option.
//If you counld not find a suitable compiler option, Please add new compiler option in this file and
//write the description for it.
//
//
//  e.g.    __NO_SD_HOT_SWAPPING__  //Not support SD swapping
//                  ^                       ^
//                  |                       |
//          Compiler option             Description
//
//=======================================================================
//Define Compiler option MMI AP related
//=======================================================================









//MMI resource related
//***************************************MMI Resource Related************************************************
//Define all MMI feature complier for XRG in below list.
//(Between ######__MMI_XRG_COMPILER_OPTION_INPUT_START__##### and
//######__MMI_XRG_COMPILER_OPTION_INPUT_END__#####)
//
//These compiler options will be used in target and XRG(Avaible list).
//
//If you want to enable/disable these compiler options, you coulde modify "proj\sc\product\XXX\option.mak".
//
//e.g. proj\sc\product\xmmi_m188\option.mak
//   XRG Tool will parse the tag "######__MMI_XRG_COMPILER_OPTION_ENABLE_START__#####"
//   and "######__MMI_XRG_COMPILER_OPTION_ENABLE_END__##### " to get enable compiler option.
//
//   ######__MMI_XRG_COMPILER_OPTION_ENABLE_START__#####
//   PP_OPT_COMMON +=\
//      __APP_MMI_CASHORGANIZER__\
//      __NATIVE_GAME_MMI_FRUIT__\
//      __NATIVE_GAME_MMI_BIG2__\
//      __NATIVE_GAME_MMI_PACMAN__\
//      __APP_MMI_TODOLIST__\
//      __APP_MMI_BMI__\
//      __MMI_NEW_ITEM__        ----------------------> new item.
//   ######__MMI_XRG_COMPILER_OPTION_ENABLE_END__#####
//***************************************************************************************
######__MMI_XRG_COMPILER_OPTION_INPUT_START__#####
__UI_STYLE_MMI_IFONE__                      //Main Menu AP - IFone Style
__UI_STYLE_MMI_MAIN_MENU_SPIN__             //Main Menu AP - Spin Style
__UI_STYLE_MMI_MAIN_MENU_GRID_AND_LIST__    //Main Menu AP - Grid Style
__UI_STYLE_MMI_MAIN_MENU_CELL__             //Main Menu AP - Spin Style
__UI_STYLE_MMI_MAIN_MENU_ANIMATION__        //Main Menu AP - Animation effect in Grid Style Main Menu
__UI_STYLE_MMI_ANDROID_MAIN_MENU__          //Main Menu AP - Android Style
__UI_STYLE_MMI_ANDROID_IDLE__               //Idle Android style
__UI_STYLE_MMI_ANDROID_KEYGUARD__           //Keyguard Android style
__UI_STYLE_MMI_ANDROID_4_0__                //Android 4.0 UI Style
__UI_STYLE_FLIPDCLOCK__                     //Flip clock
__APP_MMI_CASHORGANIZER__                   //Cash Organizer AP
__NATIVE_GAME_MMI_FRUIT__                   //Game Fruit AP
__NATIVE_GAME_MMI_BIG2__                    //Game Big2 AP
__NATIVE_GAME_MMI_PACMAN__                  //Game PACMAN AP
__NATIVE_GAME_MMI_BREAKOUT__                //Game Breakout AP
__NATIVE_GAME_MMI_PEDOMETER__               //Game Pedometer AP
__APP_MMI_TODOLIST__                        //Todolist AP
__APP_MMI_EVENTCENTER__                     //Event Center AP
__APP_MMI_BMI__                             //BMI AP
__APP_MMI_SKETCHNOTE__                      //Sketch Note AP. If you want to enable this AP, __TOUCH_SCREEN_MMI__ must be enabled first.
__DICTAPP_MMI__                             //For DICT AP
__E_BOOK_MMI__                              //For E_Book AP
__APP_MMI_WORLDCLOCK__                      //WorldClock AP
__APP_MMI_VOICE_MEMO__                      //Voice Memo AP
__ATV_MMI__                                 //enable Analog TV feature
__MMI_QQ__                                  //enable QQAP
__MMI_KING_MOVIE__                          //enable King Movie
__IME_MMI_MY__                              //MY ime
__IME_MMI_ZI__                              //ZI ime
__APP_MMI_FM_RADIO__                        //FM RADIO AP
__APP_MMI_WDG3DEMO__												//
__TOUCH_SCREEN_MMI__                        //Touch Screen
__IME_MMI_SOFTKEYBOARD__                    //for inout editor soft keyboard
__APP_MMI_NOTEPAD__                         //Notepad AP
__APP_MMI_UNITCONVERTER__                   //UnitConverter AP
__APP_MMI_CALENDAR__                        //Calendar AP
__MAP_MMI__                                 //Map applet
__GADGETS_MMI__                             //gadget style Idle AP
__GADGETS_MMI_PET__                         //Pet in gadget style idle app
__G3D_MMI__                                 //
__APP_MMI_PICTURE_VIEWER__                  //
__APP_MMI_CALCULATOR__                      //
__APP_MMI_CALCULATOR_PLUS__                 //Calculator plus
__APP_MMI_STOPWATCH__                       //
__APP_MMI_COUNTDOWN_TIMER__                 //
__APP_MMI_SHORTCUT__                        //Shortcuts AP
__MMI_SENSE_UI__                            //
__FT_AUTO_TEST__                            //
__MMI_2DUI__                       //
__CALLER_LOCATION__ //check caller location of the tel num or phone num
__AUTO_ROTATE_DISPLAY__                     //
__NOT_SUPPORT_AUTO_ROTATE_DISPLAY__         //
__LCM_LANDSCAPE__																//
__IME_MMI_SOFTKEYBOARD_7COL_UI__            //
__APP_VIDEO_TELEPHONY__			    // Video Telephony AP
__NATIVE_GAME_MMI_GTR_PINGPONG__						// PingPong
__NATIVE_GAME_MMI_GTR_FISHING__							// Fishing
__NATIVE_GAME_MMI_GTR_BUBBLE__							// Bubble
__NATIVE_GAME_MMI_GTR_FRISBEE__							// Frisbee
__APP_MMI_SMALLROM__												// 64_32 smallRom
__APP_MMI_NORMALROM__												// not 64_32
__APP_MMI_BJX__                             // BJX
__BLUETOOTH_MMI__														// Bluetooth
__WAP_MMI_CDWAP__														// WAP
__GAME_ENGINE_EMU_MMI__											// EMU GAME
__JAVA_MMI__																// Java
__MGL_DEMO__																// __MGL_DEMO__
__UNIT_TEST_APP__														// Unit Test
__WLAN_MMI__																// Wlan
__EMAIL_MMI__																// EMail
__NATIVE_GAME_MMI_BIG2__										// Big2
__NATIVE_GAME_MMI_FRUIT__										// Fruit
__NATIVE_GAME_MMI_PACMAN__									// PacMan
__HALL_SWITCH_MMI__								    // Hall switch
__IFONE_STYLE_MMI_COUNTDOWN_TIMER__					// Ifone style countdown timer
__IFONE_STYLE_MMI_VOICEMEMO__								// Ifone style voice memo
__DISABLE_USB_MASS_STORAGE_CLASS__         //Disable USB Mass Storage Function
__DISABLE_USB_VIDEO_CLASS__                //Disable PC Cam Function
__DISABLE_USB_CDC_CLASS__                  //Disable USB Modem(USB TMT) Function
######__MMI_XRG_COMPILER_OPTION_INPUT_END__#####

//=======================================================================
//Define Compiler option handset hardware related
//=======================================================================

//SD related
__NO_SD_HOT_SWAPPING__      //Not support SD swapping


//Keypad related
__NO_FULL_KEYPAD__          //Full keypad means L/R soft key, navigation key, center key, numeric key.
__DEDICATE_POWER_KEY__      //Target has power key.

//Audio Driver related
## PP_OPT_COMMON += $(EXT_AUDIO_OPAMP)   //Reserve blank if using internal OP
__EXT_OPAMP_DRV_HS__                     //Enable External audio OP amplifier on headset
__EXT_OPAMP_DRV_HSL__                    //Enable External audio OP amplifier on headset Left Channel
__EXT_OPAMP_DRV_HSR__                    //Enable External audio OP amplifier on headset Right Channel
__EXT_OPAMP_DRV_LINEOUT_HSR__            //Enable External audio OP amplifier on Lineout speaker connected with Headset Right channel
##
