#===============================================================================
#  ** Define customization options **
# Note:
# 1. Some tags are described in flag to let it easy to read, here is the meaning of tags:
#    a. Description: which describes the meaning of this flag
#    b. Pre_Variable_True: the dependency flags need to turn on for this flag
#                         Please write N/A for empty case.
#    c. Pre_Variable_False: Opposite to Pre_Variable_True, please write dependency flag which needs to turn off.
#                         Please write N/A for empty case.
#    d. Option_Selection: If there are more than one choice of this function, please list here for selection.
#                         One flag should be defined in the selection list.
#                         Please write N/A for empty case.
# 2. To turn off a flag, let the flag value be FALSE.
#
# Example 1:
# #Description = Option for LCM resolution
# #Pre_Variable_True = N/A
# #Pre_Variable_False = N/A
# #Option_Selection = __LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_QCIF_PLUS__, __LCM_HVGA_320_480__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_QCIF__, __LCM_LANDSCAPE_HVGA__
# LCM_RESOLUTION += __LCM_QVGA__
#
#       In Example 1, it defines LCM_RESOLUTION as __LCM_QVGA__, which is chosen from the Option_Selection list.
#
# Example 2:
# #Description = Option to enable BMI application
# #Pre_Variable_True = N/A
# #Pre_Variable_False = N/A
# #Option_Selection = TRUE, FALSE
# BMI_SUPPORT = FALSE
#
#       In Example 2, it is to turn off BMI feature. Let BMI_SUPPORT value be FALSE.
#===============================================================================

#===============================================================================
# ** Feature Options **
#===============================================================================
# Feature_Name = CUS DEFINE FOLDER
# Description = Option for change customer define folder
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __CUS_DEFAULT__, __CUS_1__, __CUS_2__, __CUS_3__, __CUS_4__, __CUS_5__
CUS_FOLDER = __CUS_DEFAULT__

# Feature_Name = CHIP TYPE
# Description = Option for chip type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __MSW8533C__, __MSW8533D__, __MSW8533CN__, __MSW8533N__, __MSW8536N__, __MSW8532__,  __MSW8532B__, __MSW8532BL__, __MSW8533BN__, __MSW8533BD__
CHIP_TYPE = __MSCXXXX__


# Feature_Name = Compiler TYPE
# Description = Option for compiler type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __RVCTV22__, __AEONGCC__, __MIPSGCC__,  __X86LINUXGCC__
COMPILER_TYPE = __ARMGCC__
PP_OPT_COMMON += $(COMPILER_TYPE)



# Feature_Name = Small ROM
# Description = Turn on this option, it will use small code size UI (reduce
#           image file usage), and downgrade some multimedia spec. (e.g. do
#           not support AAC, H.264...etc.)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMALL_ROM_SUPPORT = FALSE

# Feature_Name = Small ROM solution
# Description = Turn on this option, it will use small code size UI (reduce
#           image file usage), and downgrade some multimedia spec. (e.g. do
#           not support AAC, H.264...etc.)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = 4MB or 8MB or empty
SMALL_ROM_SOLUTION =

# Feature_Name = Small ROM 32 profile
# Description = For deciding small_rom_32 profile setting setting,profile_0
#           is base set, profile_1 is multimedia set, profile_2 is MMI(touch) set,
#           profile_N is full features set. Only be used when
#           SMALL_ROM_SOLUTION set 4MB
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = SMALL_ROM_32_PROFILE_0, SMALL_ROM_32_PROFILE_1, SMALL_ROM_32_PROFILE_2, SMALL_ROM_32_PROFILE_N
SMALL_ROM_32_SET =

#===============================================================================
# MCP related options
#===============================================================================

# Feature_Name = Numonyx M18 MCP Support
# Description = Option to support numonyx M18 MCP
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
M18_MCP_SUPPORT = FALSE

#===============================================================================
# Sensor related options
#===============================================================================
# Feature_Name = DUAL_CAM
# Description = Option for dual camera feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DUAL_CAM_SUPPORT = FALSE

# Feature_Name = 5M sensor support
# Description = Support Samsung S5K4ECGX 5M Sensor
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
5M_SENSOR_SUPPORT = FALSE

# Feature_Name = Interfered Camera Workaround PATCH
# Description = [Driver] Interfered Camera Workaround Patch (If we don't need
#           any patch solution, please select __INTERFERE_CAMERA_PATCH_NONE__)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __INTERFERE_CAMERA_PATCH_NONE__, __INTERFERE_CAMERA_PATCH_FREEZE_PREVIEW__, __INTERFERE_CAMERA_PATCH_ADJUST_CLOCK__
INTERFERE_CAMERA_PATCH = __INTERFERE_CAMERA_PATCH_NONE__

# Feature_Name = Interfered Camera Workaround PATCH apply on main camera
# Description = the apply range of INTERFERE_CAMERA_PATCH
# Pre_Variable_True = INTERFERE_CAMERA_PATCH
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
INTERFERE_CAMERA_PATCH_FOR_CAMERA_MAIN = FALSE

# Feature_Name = Interfered Camera Workaround PATCH apply on sub camera
# Description = the apply range of INTERFERE_CAMERA_PATCH
# Pre_Variable_True = INTERFERE_CAMERA_PATCH
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
INTERFERE_CAMERA_PATCH_FOR_CAMERA_SUB = FALSE

# Feature_Name = Interfered Camera Workaround PATCH apply range
# Description = the apply range of INTERFERE_CAMERA_PATCH
# Pre_Variable_True = INTERFERE_CAMERA_PATCH
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
INTERFERE_CAMERA_PATCH_FOR_ATV = FALSE

# Feature_Name = Video Stabilizer
# Description = Option to enable video stabilizer
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
VIDEO_STABILIZER_SUPPORT = FALSE

# Feature_Name = CTA support
# Description = Option to support CTA test
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MSTAR_CTA_SUPPORT = FALSE

# Feature_Name = EMAIL
# Description = Option for EMAIL feature
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
EMAIL_SUPPORT = FALSE

# Feature_Name = WAP PICTOGRAM
# Description = Option for WAP PICTOGRAM feature
# Pre_Variable_True = WAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WAP_PICTOGRAM_SUPPORT = FALSE

# Feature_Name = WAP HTML
# Description = Option for WAP HTML feature
# Pre_Variable_True = WAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WAP_HTML_SUPPORT = FALSE

# Feature_Name = WAP SSL
# Description = Option for WAP SSL feature
# Pre_Variable_True = WAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WAP_SSL_SUPPORT = FALSE

# Feature_Name = WAP BROWSE RECORD
# Description = Option for WAP BROWSE RECORD feature
# Pre_Variable_True = WAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WAP_RECORD_SUPPORT = FALSE

# Feature_Name = UNICODE TO GB2312
# Description = Option for UNICODE to GB2312 conversion in WAP input field
# Pre_Variable_True = CHINESE_S_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
UNICODE_TO_GB2312_CONVERSION = FALSE

# Feature_Name = MMS TEMPLATE
# Description = Option for MMS Support Template feature
# Pre_Variable_True = MMS_SUPPORT
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
MMS_TEMPLATE_SUPPORT = FALSE

# Feature_Name = Disable MMS Resize Image Function
# Description = Option to disable the MMS resize image function
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMS_DISABLE_RESIZE_IMAGE_SUPPORT = TRUE

# Feature_Name = Disable MMS Play Video Function
# Description = Option to disable the MMS play video function
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMS_DISABLE_PLAY_VIDEO_SUPPORT = TRUE

# Feature_Name = [MMI] OTA Provisioning Support
# Description = Option for OTA Provisioning
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WAP_OTA_SUPPORT = FALSE

# Feature_Name = JAVA
# Description = JAVA solution
#           __JAVA_OAKMONT__ (Aplix Java solution)
#              JaP-0: __JAVA_OAKMONT_JAP0__, JSR-118(MIDP 2.1), JSR-139(CLDC 1.1), Nokia UI extension, miniSSL
#              JaP-1: __JAVA_OAKMONT__, JTWI (default) - All JaP-0 and JSR-185(JTWI), JSR-120(WMA 1.0), JSR-135(MMAPI 1.2), JSR-75(FC)
#              JaP-2: __JAVA_OAKMONT_JAP2__, All JaP-1 and JSR-172 (Web Services), JSR-257 (Contactless Communication API)
#              More details, please refer to .\proj\sc\application\3rd\java\Oakmont\doc\
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = __JAVA_OAKMONT__, __JAVA_OAKMONT_JAP0__, __JAVA_OAKMONT_JAP2__, __NCC_3RD_JAVA_PORTING_LAYER_S__, __NCC_3RD_JAVA_PORTING_LAYER_M__
JAVA_SOLUTION =

# Feature_Name = SKYENGINE
# Description = Option for supporting sky-engine
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
SKYENGINE_SUPPORT = FALSE

# Feature_Name = SXMENGINE
# Description = Option for supporting sxm-engine
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
SXMENGINE_SUPPORT = FALSE

# Feature_Name = ZMOLENGINE
# Description = Option for supporting zmol-engine
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = TRUE, FALSE
ZMOLENGINE_SUPPORT = FALSE

# Feature_Name = ZYUEENGINE
# Description = Option for supporting zyue-engine
#           Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA).
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = TRUE, FALSE
ZYUEENGINE_SUPPORT = FALSE

# Feature_Name = TTS
# Description = Option for TTS feature. Client should get TTS porting layer
#           resource library by themselves.
# Pre_Variable_True = N/A
# Pre_Variable_False = SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = TRUE, FALSE
TTS_SUPPORT = FALSE

# Feature_Name = QQ_SOLUTION
# Description = Option for QQ Solution (TQQ & QXin need CDWAP enabled)
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT, SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = TENCENT_QQ, NQQ, TENCENT_QXIN
QQ_SOLUTION =

# Feature_Name = Dual battery
# Description = Option to support dual battery
# Pre_Variable_True = N/A
# Pre_Variable_False = LCD_PANEL_DETECT_BY_ADC_SUPPORT
# Option_Selection = TRUE, FALSE
DUAL_BATTERY_SUPPORT = FALSE

# Feature_Name = Dual battery ID PIN SUPPORT
# Description = Option to support ID pin of dual battery
# Pre_Variable_True = N/A
# Pre_Variable_False = LCD_PANEL_DETECT_BY_ADC_SUPPORT
# Option_Selection = TRUE, FALSE
DUAL_BATTERY_NO_ID_PIN_SUPPORT = FALSE

# Feature_Name = charging power on without battery
# Description = Option to support charging power on without battery
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CHARGER_POWER_ON_WITHOUT_BATT_SUPPORT = FALSE

# Feature_Name = SW CHARGING STOP
# Description = Option to support sw stop charging
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SW_CHARGING_STOP_SUPPORT = FALSE

# Feature_Name = Replace PMOS with PNP, using charging volt & current to detect charger plug-out
# Description = Option to Enable charging detection scheme with charging volt & current.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PNP_CHARGING_SUPPORT = FALSE

# Feature_Name = ADC Calibration by efuse
# Description = Instead of original calibration by production tools, the options provide
#               alternative way to do calibration at FT stage, then save releated parameter
#               in EFUSE. while enabling the feature, there is some concern on layout. The
#               connection between VBat and VSense shall be as short and thick as possible
#               to reduce the effect of voltage drop.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ADC_CALI_BY_EFUSE_SUPPORT = FALSE

# Feature_Name = RTC lost time recovery
# Description = Option to enable time recovery mechanism when RTC lost time
#           occur
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
RTC_LOST_TIME_RECOVERY_SUPPORT = FALSE

# Feature_Name = EMU Emulator
# Description = Option to support EMU emulator, please double confirm the license
#           issue first before you use this feature
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
GAME_ENGINE_EMU_SUPPORT = FALSE

# Feature_Name = EMU 16 bit Emulator
# Description = Option to support 16 bit EMU emulator, please double confirm the license
#           issue first before you use this feature
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
GAME_ENGINE_EMU_16BIT_SUPPORT = FALSE

# Feature_Name = EMU Emulator virtual keypad
# Description = Option to enable EMU applet to play game with virtual keypad.
#               Only supported in NAND flash or in NOR flash without enabling EMU 16-bit game
# Pre_Variable_True = GAME_ENGINE_EMU_SUPPORT, TOUCH_SCREEN_DRIVER_SELECT(*), LCM_RESOLUTION(__LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_HVGA_320_480__, __LCM_WVGA__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_WQVGA_240_400__, __LCM_LANDSCAPE_HVGA__, __LCM_LANDSCAPE_WVGA__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EMU_VIRTUAL_KEYPAD_SUPPORT = FALSE

# Feature_Name = EMU Landscape Mode
# Description = Play EMU games in landscape mode
# Pre_Variable_True = GAME_ENGINE_EMU_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EMU_PLAY_IN_LANDSCAPE_MODE = FALSE

#===============================================================================
# WiFi related options
#===============================================================================
# Feature_Name = WLAN
# Description = Option for WLAN feature
# Pre_Variable_True = CHIP_TYPE(__MSW8533CN__, __MSW8533N__, __MSW8536N__, __MSW8532B2__, __MSW8533BN__)
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
WLAN_SUPPORT = FALSE

# Feature_Name = WLAN Auto Connect
# Description = [MMI] Option for WLAN Auto Scan and Connect AP
# Pre_Variable_True = WLAN_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WLAN_AUTOCONNECT_SUPPORT = FALSE

#===============================================================================
# LCM related options
#===============================================================================
# Feature_Name = LCM Resolution
# Description = Option for LCM resolution
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_QCIF_PLUS__, __LCM_HVGA_320_480__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_QCIF__, __LCM_QQVGA__, __LCM_LANDSCAPE_HVGA__
# note: if you try to add a new resolution, please also add corresponding LCM_WIDTH, LCM_HEIGHT in common_option.mak
LCM_RESOLUTION =

# Feature_Name = LCM Sub Resolution
# Description = Option for LCM Sub resolution
# Pre_Variable_True = DUAL_LCD_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = __LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_QCIF_PLUS__, __LCM_HVGA_320_480__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_QCIF__, __LCM_LANDSCAPE_HVGA__
# note: if you try to add a new resolution, please also add corresponding SUB_LCM_WIDTH, SUB_LCM_HEIGHT in common_option.mak.
LCM_SUB_RESOLUTION =

# Feature_Name = LCM_ROTATE_DIRECTION
# Description = Option for LCM ROTATE direction(counter clockwise)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = 0,90,180,270
LCM_ROTATE_DIRECTION_CCW =

# Feature_Name = Option to enable FMARK feature
# Description = Not every panel support FMARK feature, please consult panel
#           vendor.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LCM_FMARK_ENABLE = FALSE

# Feature_Name = LCM Enter Sleep function
# Description = Option for LCM entersleep
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LCM_SLEEP_MODE_SUPPORT = FALSE

# Feature_Name = qwerty keypad
# Description = Option for qwerty keypad feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
QWERTY_KEYPAD_SUPPORT = FALSE

# Feature_Name = Touch Screen Driving IC Select
# Description = If this option is set,Select the mapped driving IC driver (This
#           selection depends on hardware configuration.)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __CUST_CTP__ (Capacitor Type), __R_MSTAR__ (Resistor Type)
TOUCH_SCREEN_DRIVER_SELECT = __R_MSTAR__

# Feature_Name = Touch Screen SLIM
# Description = If this option is set, touch screen Support slim feature.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__R_MSTAR__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TOUCH_SCREEN_SLIM_SUPPORT = TRUE

# Feature_Name = Touch Screen angle select
# Description = If this option is set,Select the mapped driving IC driver (This
#           selection depends on hardware configuration.)
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT = __CUST_CTP__ OR __R_C_COEXIST__
# Pre_Variable_False = TOUCH_SCREEN_DRIVER_SELECT = __R_MSTAR__ OR NULL
# Option_Selection = __90_ANGLE__, __180_ANGLE__, __270_ANGLE__
TOUCH_SCREEN_ANGLE_SELECT =

# Feature_Name = Touch Screen Interrupt Mode Select
# Description = If this option is set, touch screen ADC notify cpu by interrupt.
#           This also can alleviate touch screen jitter or smoothen the line.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__R_MSTAR__), TOUCH_SCREEN_DRIVER_SELECT(__R_C_COEXIST__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TOUCH_SCREEN_ADC_INTERRUPT_SUPPORT = FALSE

# Feature_Name = Touch Screen synamic report rate mode
# Description = If this option is set, c-type touch screen could support dynamic report rate, and MMI could configure it by diffrent application.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__CUST_CTP__), TOUCH_SCREEN_DRIVER_SELECT(__R_C_COEXIST__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TOUCH_SCREEN_DYNAMIC_REPORT_RATE_SUPPORT = FALSE

# Feature_Name = Hall Switch.
# Description = Options to enable hall switch
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HALL_SWITCH_SUPPORT = FALSE

# Feature_Name = Hall Switch Slide/Flip MMI.
# Description = Options to enable hall switch slide/flip
# Pre_Variable_True = HALL_SWITCH_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = __HALL_SWITCH_SLIDE_MMI__, __HALL_SWITCH_FLIP_MMI__
HALL_SWITCH_BEHAVIOR =

# Feature_Name = Flashlight control module(DRV)
# Description = Option to select Flashlight control module
# Pre_Variable_True = FLASHLIGHT_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = __FLASHLIGHT_CTRL_BY_GPIO__, __FLASHLIGHT_CTRL_BY_KEYLED__
FLASHLIGHT_CTRL_METHOD =

# Feature_Name = fill light
# Description = Option to enable fill light
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FILLLIGHT_SUPPORT = FALSE

# Feature_Name = camera motion detect
# Description = Option to enable camera motion detect
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CAMERA_MOTION_DETECT_SUPPORT = FALSE

# Feature_Name = 1) lantern by audio 2) spectrum by audio
# Description = 1) Option to enable lantern by audio: Only the SZ part uses
#           the compile option in AP layer for audio lantern feature. 2) Option
#           to enable spectrum by audio:Service and AP layer both uses the compile
#           option for audio spectrum feature. The audio spectrum feature is
#           not supported in smallrom product (check the __APP_MMI_SMALLROM__
#           in AP code)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LANTERN_BY_AUDIO_SUPPORT = FALSE

# Feature_Name = GPS feature
# Description = Option to enable GPS features
# Pre_Variable_True = CHIP_TYPE(__MSW8533C__), CHIP_TYPE(__MSW8533__), CHIP_TYPE(__MSW8536N__)
# Pre_Variable_False = SDK_API_WAP_MMS_ONLY_SUPPORT
# Option_Selection = TRUE, FALSE
GPS_SUPPORT = FALSE

# Feature_Name = Auto partition
# Description = Option to enable auto partition for NOR Flash
# Pre_Variable_True = ONBOARD_USER_STORAGE_SUPPORT
# Pre_Variable_False = NAND
# Option_Selection = TRUE, FALSE
AUTO_PARTITION_SUPPORT = FALSE

# Feature_Name = Handwriting DB in T-Card
# Description = 1.support read handwring DB from T-Card. 2.reduce CUS size
# Pre_Variable_True = __HANDWRITING_MMI__
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HANDWRITING_DB_TCARD_SUPPORT = FALSE

#===============================================================================
# ** DRV/SYS Options **
#===============================================================================

# Feature_Name = APUS Clock Output for AC CAP support
# Description = Option for APUS Clock Output
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = ZERO_OHM, AC_CAP
CLKOUT_26MHZ_BB_CONFIG = AC_CAP

# Feature_Name = ATV (CHIP)
# Description = Option to select ATV chip.(This selection depends on hardware
#           configuration.)
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = mstar
ATV_CHIP =

# Feature_Name = ATV (Audio Path)
# Description = Option to select ATV audio path
# Pre_Variable_True =  ATV_CHIP(mstar)
# Pre_Variable_False = N/A
# Option_Selection = __ATV_AUD_I2S__ , __ATV_AUD_LINEIN__
ATV_AUDIO_PATH =

# Feature_Name = ATV Crystal mode
# Description = Option to select Crystal mode
# Pre_Variable_True = ATV_CHIP(mstar)
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
ATV_27MCRYSTAL_ENABLE = FALSE

# Feature_Name = Enable ISDBT on ATV chip
# Description = Option to enable ISDBT mode if this chip supports ATV&ISDBT
# Pre_Variable_True = ATV_CHIP(mstar)
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
ATV_SUPPORT_ISDBT = FALSE

# Feature_Name = RF 26MHz AUXCLK support
# Description = Share RF 26MHz AUXCLK for ATV, this can save 26MHz crystal
# Pre_Variable_True = RFIC(msr7120),ATV_CHIP
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
RF_26MHZ_AUXCLK_SUPPORT = FALSE

# Feature_Name = FM (Audio Path)
# Description = Option to select FM audio path
# Pre_Variable_True = N/A
# Pre_Variable_False = ONCHIP_FMRX_ENABLE_SUPPORT
# Option_Selection = __FM_AUD_I2S__ , __FM_AUD_LINEIN__
FM_AUDIO_PATH =

# Feature_Name = Headset Type
# Description = Headset type selection
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __35MM_HEADSET__, __USB_HEADSET__
HEADSET_TYPE = __35MM_HEADSET__

# Feature_Name = Headset Detector Support
# Description = Detection Type of Headset Plug-in/out
# Pre_Variable_True = HEADSET_TYPE(__35MM_HEADSET__)
# Pre_Variable_False = N/A
# Option_Selection = __SPK_DETECTOR_DRV__, __LP_DETECTOR_DRV__
HEADSET_DETECTOR_SUPPORT = __LP_DETECTOR_DRV__

# Feature_Name = Option to Enable Hookkey Polling
# Description = [DRV] Enable polling for hookkey detection after headset plug in
# Pre_Variable_True = HEADSET_TYPE(__35MM_HEADSET__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HOOKKEY_POLLING_SUPPORT = FALSE

# Feature_Name = External audio OP amplifier
# Description = Option to enable external audio OP amplifier. Reserve blank
#           if using internal OP
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __EXT_OPAMP_DRV_HS__, __EXT_OPAMP_DRV_HSL__, __EXT_OPAMP_DRV_HSR__, __EXT_OPAMP_DRV_LINEOUT_HSR__
EXT_AUDIO_OPAMP =

# Feature_Name = External audio codec
# Description = Select one of the external audio codec from Option_Selection
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __EXT_AUDIO_WALFSON_8918_DRV__, __EXT_AUDIO_FORTEMEDIA_34_DRV__
EXT_AUDIO_CODEC_SOLUTION =

# Feature_Name = Enable WLED LDO Switch
# Description = If this option is set, WLED's power (VLCM) can be turned off.
# Pre_Variable_True = BACKLIGHT(wled_embedded)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BACKLIGHT_WLED_LDO_SWITCH_SUPPORT = FALSE

# Feature_Name = Bluetooth
# Description = Option for bluetooth A2DP/AVRCP feature
# Pre_Variable_True = BLUETOOTH_CHIP
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BLUETOOTH_A2DP_SUPPORT = FALSE

# Feature_Name = Bluetooth User Defined Dir (MMI)
# Description = Option for Blueooth : user can set the default receiving file
#           folder by Bluetooth transmition
# Pre_Variable_True = BLUETOOTH_CHIP
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
BLUETOOTH_USER_DEFINED_FOLDER_SUPPORT = FALSE

# Feature_Name = LCD panel detect by adc.
# Description = If this option is set, LCD panel detect by adc.
# Pre_Variable_True = N/A
# Pre_Variable_False = DUAL_BATTERY_SUPPORT
# Option_Selection = TRUE, FALSE
LCD_PANEL_DETECT_BY_ADC_SUPPORT = FALSE

# Feature_Name = Dual LCD
# Description = Options to enable dual_lcd support function
# Pre_Variable_True = LCM_SUB_RESOLUTION
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
DUAL_LCD_SUPPORT = FALSE

# Feature_Name = OFN with gpio control
# Description = Enable Software I2C for OFN
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
OFN_DRV_GPIO_SIMU_I2C = FALSE

# Feature_Name = Skip logo when power on charger
# Description = Skip logo when power on charger
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SKIP_LOGO_WHEN_POWER_ON_CHARGER_SUPPORT = FALSE

# Feature_Name = OFN
# Description = OFN Remapping direction from VERTICAL to HORIZONTAL
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
OFN_REMAPPING_P2L = FALSE

# Feature_Name = bootlogo style
# Description = Select one of bootlogo style from Option_Selection. __CUS_BMP__
#           and __CUS_PNG__ support to build logo binary into CUS file, user
#           can redownload CUS file to change logo without rebuilding SW image.
#           This feature is supportted to select logo by e2p while multi-logos
#           built-in in the CUS. (e2p: WBootUpLogoIndex)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __PNG__, __BMP__, __CUS_BMP__, __CUS_PNG__
BOOTUP_LOGO_TYPE = __BMP__

# Feature_Name = Hall Ball
# Description = Hall ball driver
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HALL_BALL_SUPPORT = FALSE

# Feature_Name = SD single card and dual card data bud configuration
# Description = phone has how many SD socket(s) and SD data bus setting. __SD1_1_BIT_SD2_1_BIT__ means dual 1 bit on sd pad
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __SD1_4_BITS_ONLY_NO_SD2__, __SD1_4_BITS_SD2_4_BITS__, __SD1_4_BITS_SD2_1_BIT__, __SD1_1_BIT_SD2_1_BIT__
SD_DATA_BUS_CONFIG = __SD1_4_BITS_SD2_4_BITS__

# Feature_Name = SD1 socket has card detect pin to support hot plug feature (DRV)
# Description = phone has mechanical card detect switch to detect card insert or remove for SD1
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __SD1_HOT_PLUG_INSERT_LOW__, __SD1_HOT_PLUG_INSERT_HIGH__
SD1_HOT_PLUG_SUPPORT = __SD1_HOT_PLUG_INSERT_LOW__

# Feature_Name = SD2 socket has card detect pin to support hot plug feature (DRV)
# Description = phone has mechanical card detect switch to detect card insert or remove for SD2
# Pre_Variable_True = __SD1_4_BITS_SD2_4_BITS__ or __SD1_4_BITS_SD2_1_BIT__ or __SD1_1_BIT_SD2_1_BIT__
# Pre_Variable_False = __SD1_4_BITS_ONLY_NO_SD2__
# Option_Selection = __SD2_HOT_PLUG_INSERT_LOW__, __SD2_HOT_PLUG_INSERT_HIGH__
SD2_HOT_PLUG_SUPPORT = __SD2_HOT_PLUG_INSERT_LOW__

# Feature_Name = SD card clock downgrade (DRV)
# Description = Option to have slower sd clock, unit: KMz. If has SD2, downgrade together
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = 50000~300 (out of range will result system assert)
SD_CARD_CLOCK = 50000

# Feature_Name = Use the same power source for dual card
# Description =
# Pre_Variable_True = __SD1_4_BITS_SD2_4_BITS__ or __SD1_4_BITS_SD2_1_BIT__ or __SD1_1_BIT_SD2_1_BIT__
# Pre_Variable_False = __SD1_4_BITS_ONLY_NO_SD2__
# Option_Selection = TRUE, FALSE
DUAL_CARD_SHARE_POWER_SUPPORT = FALSE

# Feature_Name = select hall switch behavior for open/slide
# Description = select hall switch behavior for open/slide set hall switch status
#           high as open or low as open
# Pre_Variable_True = __HALL_SWITCH__
# Pre_Variable_False = N/A
# Option_Selection = __HIGH_OPEN__, __LOW_OPEN__
HALL_SWITCH_POLARITY =

# Feature_Name = MIDI down sampling rate in CC call ring tone
# Description = Option to enable midi down sampling rate to 24KHz in CC call to reduce CPU usage.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MIDI_DOWN_SAMPLERATE_SUPPORT = FALSE

# Feature_Name = Audio Decoder Codec Support List
# Description = Option to Enable Audio Codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection =
AMRWB_DEC_SUPPORT = FALSE

# Feature_Name = Audio Encoder Codec Support List
# Description = Option to Enable Audio Codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection =
PCM_ENC_SUPPORT = FALSE
AMRWB_ENC_SUPPORT = FALSE
WAV_ENC_SUPPORT = FALSE
MP3_ENC_SUPPORT = FALSE

# Feature_Name = Audio Spectrum analyzer
# Description = Option to Enable Audio Codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection =
AUD_SPECTRUM_SUPPORT = FALSE

# Feature_Name = Audio Reverb Effrct
# Description = Option to Enable Audio Reverb Effect
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__, __MSW8533C__, __MSW8533D__, __MSW8533BN__, __MSW8533BD__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_MSTAR_REVERB_SUPPORT = FALSE

# Feature_Name = 3rd Party SRS WOWHD Audio Effect
# Description = Option to Enable Audio SRS WOWHD Effect
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__, __MSW8533C__, __MSW8533D__, __MSW8532__, __MSW8533BN__, __MSW8533BD__, __MSW8532B__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_SRS_WOWHD_SUPPORT = FALSE

# Feature_Name = Audio BASS Effect
# Description = Option to Enable Audio BASS Effect
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__, __MSW8533C__, __MSW8533D__, __MSW8532__, __MSW8533BN__, __MSW8533BD__, __MSW8532B__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_MSTAR_BASS_SUPPORT = FALSE

# Feature_Name = Audio Time Stretch Effect
# Description = Option to Enable Audio Time Stretch Effect
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_MSTAR_TIMESTRETCH_SUPPORT = FALSE

# Feature_Name = Audio Pitch Stretch Effect
# Description = Option to Enable Audio Pitch Effect (EXP : Talking Tom)
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__, __MSW8533C__, __MSW8533D__, __MSW8532__, __MSW8533BN__, __MSW8533BD__, __MSW8532B__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_MSTAR_PITCHSTRETCH_SUPPORT = FALSE

# Feature_Name = Force Switch APP DRCLimiter/SpeakerPEQ IP Power for Video Player
# Description = Option to Switch APP DRCLimiter/SpeakerPEQ IP Power for Video Player
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
OPT_VIDEO_APP_DRCLIMITER_POWER = FALSE
OPT_VIDEO_APP_SPEAKERPEQ_POWER = FALSE

# Feature_Name = FM PEQ Support
# Description = Option to enable FM Speaker EQ mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
FM_PEQ_SUPPORT = FALSE

# Feature_Name = [SYS] DPM mechanism
# Description = Demand paging module mechanism support
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DPM_SUPPORT = FALSE

# Feature_Name = [SYS] EMMI SLDPM mechanism
# Description = EMMI with SL-DPM mechanism support
# Pre_Variable_True = DPM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EMMI_SLDPM_SUPPORT = FALSE

# Feature_Name = [SYS] MIDI SLDPM mechanism
# Description = MIDI with SL-DPM mechanism support
# Pre_Variable_True = DPM_SUPPORT, SMALL_ROM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MIDI_SLDPM_SUPPORT = FALSE

#===============================================================================
# RFID related options
#===============================================================================
# Feature_Name = RFID CHIP TYPE
# Description = Option for RFID chip type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __MSR3110__
RFID_CHIP_TYPE =

# Feature_Name = Bar Code Reader
# Description = Option for Bar Code Reader feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BARCODE_SUPPORT = FALSE

#===============================================================================
# Stack related options
#===============================================================================

# Feature_Name = Slim RIL
# Description = Turn on this option to use Slim RIL
# Pre_Variable_True = SMALL_ROM_SOLUTION(4MB)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SLIM_RIL_SUPPORT = FALSE

# Feature_Name = Slim ATI
# Description = Turn on this option to use Slim ATI
# Pre_Variable_True = SMALL_ROM_SOLUTION(4MB)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SLIM_ATI_SUPPORT = FALSE

# Feature_Name = Dial-up networking
# Description = Turn on this option to use dial-up networking
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DIALUP_NETWORKING_SUPPORT = TRUE

#===============================================================================
# ** MMI Options **
#===============================================================================
# mmi (XRG) setting
# Feature_Name = Resource setting
# Description = Resource for Product
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
# CUS_PATH = XML Folder [ Control_Files ]
# CUS_PROJECT = default portrait or landscape mode. [AUTO, CommonPortrait, CommonLandscape, CommonLandscapeTheme, CommonPortraitTheme]
# CUS_RES = Resource Folder [AUTO, HVGA_Res, QCIF_Res, QCIF_SmallRom_Res, QVGA_Res, WQVGA_Res, QQVGA_SmallRom_Res, WQVGA_3D_Res, QQVGA_SmallRom_Res ]
# AUTO : auto select by script. reference to LCM_SUPPORT in common_option.mak
# LANGUAGE_PACK_LIST : set language pack by this parameter.
#					   [important] XRG_CUS parameter is higher priority than LANGUAGE_PACK_LIST. like make mmi_cus0 or make mmi_cus XRG_CUS = LangPack0001
#					   if value is DEFAULT, XRG build language pack by solution file.
#                      otherwise, build language pack by this parameter. Format: LANGUAGE_PACK_LIST = LangPack0001 LangPack0002 LangPack0003
CUS_PATH = Control_Files
CUS_PROJECT = CommonPortrait
CUS_RES = NONE
LANGUAGE_PACK_LIST = DEFAULT

# Feature_Name = EMMI SLDPM mechanism
# Description = EMMI with SL-DPM mechanism support, PLMN,IME and HW support
#           DPM.  (NOR type only)
# Pre_Variable_True = EMMI_SLDPM_SUPPORT
# Pre_Variable_False = NAND
# Option_Selection = TRUE, FALSE
EMMI_SLDPM_CUS_SUPPORT = FALSE

# Feature_Name = [SYS] MMAP mechanism for CUS
# Description = CUS using MMAP mechanism to reduce memory usage
# Pre_Variable_True = NAND
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CUS_MMAP_SUPPORT = FALSE

# Feature_Name = [SYS] MMAP mechanism for CUS
# Description = MMAP address length for mapping CUS file. It needs extra memory to implement this feature.
#				1MB MMAP address length needs 1KB memory
# Pre_Variable_True = CUS_MMAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = MMAP_CUS_16MB, MMAP_CUS_32MB, MMAP_CUS_64MB
CUS_MMAP_SIZE = MMAP_CUS_32MB

# Feature_Name = Optimize Code Size from MMI part.
# Description = Save much more code size by cutting the MMI trace level.
# Pre_Variable_True = SMALL_ROM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = N/A
# LOG_LEVEL_ALL = Nothing Changed. All trace level exists.
# LOG_LEVEL_MMI_CUT_TRACE = Save the code size by cutting the specific one trace level of MMI(i.e. LOG_TRACE)
# LOG_LEVEL_CRITICAL_ONLY = Only one trace level exists.
LOG_LEVEL_CUT_OPTION =

# Feature_Name = On&Sec application feature
# Description = Option for speed-up boot-up time
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
POWERON_ANIM_DONT_WAIT_MELODY_SUPPORT = FALSE

# Feature_Name = King Movie
# Description = Option for supporting king movie
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
KING_MOVIE_SUPPORT = FALSE

# Feature_Name = 3D-King Movie
# Description = Option for supporting 3D king movie
# Pre_Variable_True = KING_MOVIE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
KING_MOVIE_3D_SUPPORT = FALSE

# Feature_Name = Seperate 3D-King Movie and King Movie Apps
# Description = Option for supporting 3D king movie
# Pre_Variable_True = KING_MOVIE_3D_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
INDEPENDENT_KING_MOVIE_3D_SUPPORT = FALSE

# Feature_Name = Stereo Video
# Description = Option for supporting video 2D to 3D
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
STEREO_VIDEO_SUPPORT = FALSE

# Feature_Name = Stereo Images
# Description = Option for supporting image 2D to 3D
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
STEREO_IMAGE_SUPPORT = FALSE

# Feature_Name = RM, RMVB
# Description = Option for supporting RMVB
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
RMVB_SUPPORT = FALSE

# Feature_Name = FLV
# Description = Option for supporting FLV
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FLV_SUPPORT = FALSE

# Feature_Name = Software Dithering
# Description = Option for enabling software dithering
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SW_DITHER_SUPPORT = FALSE

# Feature_Name = IP Call
# Description = Option to enable IP call in China area
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
IP_CALL_SUPPORT = FALSE

# Feature_Name = BS Cause
# Description = Option to enable BS Cause. The user can set 4 kind of causes
#           (busy, no user responding, subscriber absent, and number changed)
#           manually to reject an incoming call.
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
CALL_FIREWALL = TRUE

# Feature_Name = Auto Answer
# Description = Option to enable the auto answer call setting for auto ansering
#           the incoming call. This feature is for headset only
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
AUTO_ANSWER_SUPPORT = FALSE

# Feature_Name = Answer Indicator
# Description = Option to enable the answer indicator call setting for alerting
#           the user by beep, vibrate or screen flash when incoming call is
#           accepted
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ANSWER_INDICATOR_SUPPORT = FALSE

# Feature_Name = Playlist Cover
# Description = Option to enable user to set a cover picture for playlist
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
PLAYLIST_COVER_SUPPORT = FALSE

# Feature_Name = Cash Organizer
# Description = Option to enable cash organizer application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CASHORGANIZER_SUPPORT = FALSE

# Feature_Name = Notepad
# Description = Option to enable Notepad application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NOTEPAD_SUPPORT = FALSE

# Feature_Name = To Do List
# Description = Option to enable to-do list application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TODOLIST_SUPPORT = FALSE

# Feature_Name = To Do List Application sync feature
# Description = Option to enable to-do list application sync feature
# Pre_Variable_True = TODOLIST_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TODOLIST_SYNC_SUPPORT = FALSE

# Feature_Name = To Do List =>Vtodo feature
# Description = Option to enable vtodo feature on to-do list application
# Pre_Variable_True = TODOLIST_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TODOLIST_VTODO_SUPPORT = FALSE

# Feature_Name = Fruit game
# Description = Only support Portrait (QVGA, QCIF, WQVGA, HVGA), and Landscape
#           (QVGA, QCIF, WQVGA, HVGA)
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
FRUITGAME_SUPPORT = FALSE

# Feature_Name = Pacman game
# Description = Only support Portrait (QVGA, QCIF, WQVGA, HVGA), and Landscape
#           (QVGA, QCIF, WQVGA, HVGA)
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
PACMANGAME_SUPPORT = FALSE

# Feature_Name = Big2 game
# Description = Only support Portrait (QVGA, QCIF, WQVGA, HVGA), and Landscape
#           (QVGA, QCIF, WQVGA, HVGA)
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
BIG2GAME_SUPPORT = FALSE

# Feature_Name = Puzzle game
# Description = Support both landscape and portrait of HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
PUZZLEGAME_SUPPORT = FALSE

# Feature_Name = Link Up game
# Description = Support HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
LINKUPGAME_SUPPORT = FALSE

# Feature_Name = SOKOBAN game
# Description = Support HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
SOKOBANGAME_SUPPORT = FALSE

# Feature_Name = SUDOKU game
# Description = Support HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
SUDOKUGAME_SUPPORT = FALSE

# Feature_Name = HamsterFight game
# Description = Support HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
HAMSTERFIGHTGAME_SUPPORT = FALSE

# Feature_Name = Go-Bang game
# Description = Support both landscape and portrait of HVGA, WQVGA, QVGA resolution and Simplified chinese, english
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
GOBANGGAME_SUPPORT = FALSE

# Feature_Name = OMA DRM V1.0
# Description = Option to enable OMA DRM V1.0
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
OMA_DRM_V1_SUPPORT = FALSE

# Feature_Name = BMI
# Description = Option to enable BMI application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BMI_SUPPORT = FALSE

# Feature_Name = Power Saving Profile Setting (MMI)
# Description = Add the extra profile setting item for power saving
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
POWER_SAVING_PROFILE_MMI_SUPPORT = FALSE

# Feature_Name = PRIVATEPROTECT
# Description = Option to enable Privateprotect application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PRIVATEPROTECT_SUPPORT = FALSE

# Feature_Name = Dual Profile Setting (MMI)
# Description = Each sim card has its own voice ring and message tone
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DUAL_PROFILE_MMI_SUPPORT = FALSE

# Feature_Name = User defined power on/off anim (MMI)
# Description = User can define power on/off anim
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
POWERONOFF_USER_DEFINED_ANIM_SUPPORT = FALSE

# Feature_Name = User defined power on/off melody (MMI)
# Description = User can define power on/off melody
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
POWERONOFF_USER_DEFINED_RINGTONE_SUPPORT = FALSE

# Feature_Name = User defined power on/off video (MMI)
# Description = User can define power on/off video
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
POWERONOFF_USER_DEFINED_VIDEO_SUPPORT = FALSE

# Feature_Name = Video Wallpaper (MMI)
# Description = User can set video as wallpaper
# Pre_Variable_True = NAND
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
VIDEO_WALLPAPER_SUPPORT = FALSE

# Feature_Name = User defined mainmenu video (MMI)
# Description = User can set video as mainmenu background
# Pre_Variable_True = NAND
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MAINMENU_VIDEO_SUPPORT = FALSE

# Feature_Name = Support no sim camp on test network
# Description = Option for no sim camp on test network feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NOSIM_CAMP_ON_TEST_NETWORK_SUPPORT = TRUE

# Feature_Name = Indian calendar (MMI)
# Description = Support Indian calendar
# Pre_Variable_True = CALENDAR_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
INDIAN_CALENDAR_SUPPORT = FALSE

# Feature_Name = calllog select display sim
# Description = Option to enable calllog select display sim
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALLLOG_SELECT_DISPLAY_SIM_SUPPORT = FALSE

# Feature_Name = Message Select Sim box
# Description = Option to enable message Select Sim box
# Pre_Variable_True = __SMS_MMI_DISABLE_SIM_FOLDER__, STATUSBAR_SHOW_UNREAD_MESSAGE_SUPPORT(__ICONS_WITH_SIM_NUMBER__)
# Pre_Variable_False = N/A
# Option_Selection = N/A
SMS_SELECT_DISPLAY_SIM_SUPPORT = FALSE

# Feature_Name = Handwriting Notepad
# Description = Option to enable sketchnote application
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SKETCHNOTE_SUPPORT = FALSE

# Feature_Name = Unit Converter
# Description = Option to enable Unit Converter application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
UNITCONVERTER_SUPPORT = FALSE

# Feature_Name = Event Center
# Description = Option to enable Event Center application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EVENTCENTER_SUPPORT = FALSE

# Feature_Name = PHB default group
# Description = Option to enable default group
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_DEFAULT_GROUP_SUPPORT = FALSE

# Feature_Name = add blacklist by selecting from PHB
# Description = Option to enable add blacklist by selecting from PHB function. We suggest disable it in small RAM product because it needs more memory.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SELECT_BK_FROM_PHB_SUPPORT = FALSE

# Feature_Name = PHB All tab
# Description = Option to enable all tab
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_ALL_TAB_SUPPORT = FALSE

# Feature_Name = Stop Watch
# Description = Option to enable stop watch application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
STOPWATCH_SUPPORT = FALSE

# Feature_Name = Countdown Timer
# Description = Option to enable countdown timer application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
COUNTDOWN_TIMER_SUPPORT = FALSE

# Feature_Name = UI style switch
# Description = Option to switch UI style between Android and Ifone, Supported Resolution = __LCM_QVGA__,
#											__LCM_HVGA_320_480__, __LCM_WQVGA_240_400__
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_MMI_STYLE_SWITCH_SUPPORT = FALSE

# Feature_Name = Android MainmenuApp style
# Description = Option to enable Android Mainmenu style, Supported Resolution = __LCM_QVGA__,
#											__LCM_HVGA_320_480__, __LCM_WQVGA_240_400__
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_MMI_ANDROID_MAIN_MENU_SUPPORT = FALSE

# Feature_Name = Android Idle style
# Description = Option to enable Android idle style, Supported Resolution = __LCM_QVGA__,
#											__LCM_HVGA_320_480__, __LCM_WQVGA_240_400__
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_MMI_ANDROID_IDLE_SUPPORT = FALSE

# Feature_Name = Android Keyguard style
# Description = Option to enable Android Keyguard style,Supported Resolution = __LCM_QVGA__,
#											__LCM_HVGA_320_480__, __LCM_WQVGA_240_400__
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_MMI_ANDROID_KEYGUARD_SUPPORT = FALSE

# Feature_Name = Android 4.0 UI style
# Description = Option to enable Android 4.0 UI style (Idle, Mainmenu, Keyguard)
#											__LCM_HVGA_320_480__
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(*), LCM_RESOLUTION(__LCM_HVGA_320_480__)
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_MMI_ANDROID_4_0_SUPPORT = FALSE

# Feature_Name = IFone Style IDLE and Menu
# Description = Compile option to enable / disable the IFONE UI style of idle
#           screen and main menu screen
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT, __LCM_QVGA__ or __LCM_HVGA_320_480__
# Pre_Variable_False = MGLS_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_IFONE_SUPPORT = FALSE

# Feature_Name = Spin Main Menu
# Description = Option to enable the spin main menu
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
UI_STYLE_SPIN_MAIN_MENU_SUPPORT = FALSE

# Feature_Name = Main Menu Animation
# Description = Option to enable the main menu animation
# Pre_Variable_True = N/A
# Pre_Variable_False = MGLS_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_ANIMATION_MAIN_MENU_SUPPORT = FALSE

# Feature_Name = View Transition
# Description = Option to enable the view transition
# Pre_Variable_True = N/A
# Pre_Variable_False = MGLS_SUPPORT, SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
UI_STYLE_VIEW_TRANSITION = FALSE

# Feature_Name = Primary Camera UI layout
# Description = To define camera layout, __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, __CAMERA_LAYOUT_LANDSCAPE_CAPTURE_MMI__
# __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__: camera layout is landscape style in all resolution
# __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__: camera layout is portrait style in all resolution
# __CAMERA_LAYOUT_CUSTOMIZATION_MMI__: camera layout is portrait style in wallpaper/contact resolution, and landscape style in others resolution.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, __CAMERA_LAYOUT_CUSTOMIZATION_MMI__
CAMERA_PRI_UI_LAYOUT =

# Feature_Name = Secondary Camera UI layout
# Description = To define camera layout, __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, __CAMERA_LAYOUT_LANDSCAPE_CAPTURE_MMI__
# __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__: camera layout is landscape style in all resolution
# __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__: camera layout is portrait style in all resolution
# __CAMERA_LAYOUT_CUSTOMIZATION_MMI__: camera layout is portrait style in wallpaper/contact resolution, and landscape style in others resolution.
# Pre_Variable_True = DUAL_CAM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = __CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, __CAMERA_LAYOUT_CUSTOMIZATION_MMI__
CAMERA_SEC_UI_LAYOUT = __CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__

# Feature_Name = On board phone storage for user
# Description = Option to support external storage (file system used by system/user
#           and public for the mass storage). This storage will be mounted as
#           a public disk when the user connects the handset to PC and uses
#           the mass storage. This storage is usually provided by NAND/NOR.
#           The used file system is usually FAT16/FAT32 and can be accessed
#           by standard IO library, such as file_fopen.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ONBOARD_USER_STORAGE_SUPPORT = FALSE

# Feature_Name = Store the application data on phone storage
# Description = Option to support the application data can be stored on phone.
#           Currently this option affects MMS and WAP which the data is stored
#           in .system folder.
# Pre_Variable_True = ONBOARD_USER_STORAGE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APP_DATA_ON_PHONE_SUPPORT = FALSE

# Feature_Name = Use Phone storage in Camera
# Description = Option to indicate Camera application to use the the handset
#           storage or not.  When this option is enabled, camera will save the
#           captured picture into handset's storage (NOR or NAND), when this
#           option is disabled, camera app will only save the captured picture
#           into external SD card.
# Pre_Variable_True = ONBOARD_USER_STORAGE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CAMERA_USE_PHONE_STORAGE_SUPPORT = FALSE

# Feature_Name = Camera Sticker Mode
# Description = To Enable Camera sticker mode
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
CAMERA_STICKER_SUPPORT = FALSE

# Feature_Name = Camera Panorama mode
# Description = To Enable Camera panorama mode
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE, FALSE
CAMERA_PANORAMA_SUPPORT = FALSE

# Feature_Name = Camera Mirror mode
# Description = To Enable Camera Mirror mode
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE, FALSE
CAMERA_MIRROR_SUPPORT = TRUE

# Feature_Name = Camera Lomo mode
# Description = To Enable Camera lomo mode
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE, FALSE
CAMERA_LOMO_SUPPORT = TRUE

# Feature_Name = MMI Band Selection Menu
# Description = Option to activate MMI band selection menu
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BAND_SELECTION_SUPPORT = FALSE

# Feature_Name = Dual send key support
# Description = [MMI] Enable dual send key UI
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
DUAL_SEND_KEY_SUPPORT = FALSE

# Feature_Name = No full keypad
# Description = [MMI] Change UI behavior for products with/without full digit keypad. (such as 0~9, *, # keys)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NO_FULL_KEYPAD_SUPPORT = FALSE

# Feature_Name = E-Book
# Description = Option to enable Ebook application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
E_BOOK_SUPPORT = FALSE

# Feature_Name = Dictionary
# Description = Dictionary applicaiton flag
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DICTIONARY_SUPPORT = FALSE

# Feature_Name = World Clock
# Description = [MMI] Enable world clock application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
WORLDCLOCK_SUPPORT = FALSE

# Feature_Name = Calllog Block Type (MMI)
# Description = To log block call. If you add someone's number to blacklist,
#           we will log it in calllog block call tab if he makes call to you.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALLLOG_BLOCK_CALL_SUPPORT = FALSE

# Feature_Name = Calllog Edit Before Call (MMI)
# Description = Turn on this option, user can launch call edit with the specific
#           number from calllog
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALLLOG_EDIT_BEFORE_CALL_SUPPORT = FALSE

# Feature_Name = Fuzzy number search (MMI)
# Description = Turn on this option, it will enable fuzzy number search in phonebook
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMART_NUMBER_FILTER_SUPPORT = FALSE

# Feature_Name = Digit to laphabet mapping search (MMI)
# Description = Turn on this option, it will enable digit to laphabet mapping
#           search in phonebook
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMART_ALPHABET_FILTER_SUPPORT = FALSE

# Feature_Name = Small phonebook (MMI)
# Description = only support name, number 1, group, image, ringtone
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMALL_PHB_SUPPORT = FALSE

# Feature_Name = import/export phonebook with CSV (MMI)
# Description = support import/export phb with CSV format
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_IMPORT_EXPORT_MULTI_FORMAT = FALSE

# Feature_Name = send multi vcard with BT (MMI)
# Description = send selected contacts with vcard by BT
# Pre_Variable_True = BT_MMI
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_SEND_MULTI_VCARD_BY_BT_SUPPORT = TRUE

# Feature_Name = Status Bar Type (MMI)
# Description = To show an unread message icon in status bar
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __ORIGINAL_ICONS__, __ICONS_WITH_SIM_NUMBER__
STATUSBAR_SHOW_UNREAD_MESSAGE_SUPPORT = __NO_DISPLAY__

# Feature_Name = Status Bar Type (MMI)
# Description = To show a missed call icon in status bar
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
STATUSBAR_SHOW_MISSED_CALL_SUPPORT = FALSE

# Feature_Name = Status bar icon auto arrange.
# Description = Option to enable status bar icon auto arrange.
# Pre_Variable_True = N/A
# Pre_Variable_False = LCM_RESOLUTION(__LCM_QQVGA__, __LCM_LANDSCAPE_QQVGA__)
# Option_Selection = TRUE, FALSE
STATUSBAR_AUTO_ARRANGE_SUPPORT = TRUE

# Feature_Name = [MMI] Statusbar with profile icon
# Description = To show profile status in statusbar, vibrate will be disabled
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
STATUSBAR_PROFILE_STATUS_SUPPORT = TRUE

# Feature_Name = Bidi (MMI)
# Description = UI layout support in right-to-left directional display language
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BIDI_UI_SUPPORT = FALSE

# Feature_Name = The handset has dedicated end key
# Description = To provide call control application to switch audio path from
#           right softkey when this compile option is activated. We will use
#           right softkey to end call if no dedicated end key. The compile should
#           depends on end key supported or not.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DEDICATE_END_KEY_SUPPORT = FALSE

# Feature_Name = VECTOR FONT
# Description = [MMI] Vector font display solution
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __VECTOR_FONT_MMI_FREETYPE__, __VECTOR_FONT_MMI_ETRUMP__
VECTOR_FONT_SOLUTION = __VECTOR_FONT_MMI_FREETYPE__

# Feature_Name = Muti Vector Font in Cus (MMI)
# Description = Option for muti Vector Font in Cus feature in MMI
# Pre_Variable_True = VECTOR_FONT_SOLUTION
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_MUTI_FONT_IN_CUS_SUPPORT = FALSE

# Feature_Name = Vector Font On T Card (MMI)
# Description = Option for Vector Font On T Card feature in MMI
# Pre_Variable_True = VECTOR_FONT_SOLUTION
# Pre_Variable_False = N/A
# Option_Selection = __VECTOR_FONT_ON_T_CARD_FROM_MEMORY__
MMI_VECTOR_FONT_ON_T_CARD_SOLUTION =

# Feature_Name = Change font By Display language (MMI)
# Description = Option for Change vector font By Display language feature in MMI
# Pre_Variable_True = MMI_MUTI_FONT_IN_CUS_SUPPORT
# Pre_Variable_False = MMI_VECTOR_FONT_ON_T_CARD_SUPPORT
# Option_Selection = TRUE, FALSE
MMI_CHANGE_FONT_BY_LANG_SUPPORT = FALSE

# Feature_Name = Fadeout Scrollbar feature (MMI)
# Description = Fadeout scrollbar UI style
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_FADEOUT_SCROLLBAR_SUPPORT = FALSE

# Feature_Name = SDK Background Execution
# Description = [MMI] Enable sdk background execution for 3rd developement
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SDK_BACKGROUND_EXECUTION_SUPPORT = FALSE

# Feature_Name = SDK vendor entry
# Description = [MMI] Enable sdk vendor entry including some SDK example demo
#           for 3rd development reference
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SDK_MMI_VENDOR_ENTRY_SUPPORT = FALSE

# Feature_Name = SDK_API_WAP_MMS_ONLY
# Description = [SDK] Disable some sdk API to only support WAP & MMS for code size reduction
# Pre_Variable_True = N/A
# Pre_Variable_False = JAVA_SOLUTION, QQ_SOLUTION, SKYENGINE_SUPPORT, SXMENGINE_SUPPORT, ZMOLENGINE_SUPPORT, ZYUEENGINE_SUPPORT, TTS_SUPPORT, GPS_SUPPORT
# Option_Selection = TRUE, FALSE
SDK_API_WAP_MMS_ONLY_SUPPORT = FALSE

# Feature_Name = SDK_API_01_SMS_MMS_CC
# Description = Option for sdk new API (sms/mms/cc)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SDK_API_01_SMS_MMS_CC_SUPPORT = FALSE

# Feature_Name = IME
# Description = [MMI] IME solution (If we don't have any ime solution, please
#           select __IME_MMI_DUMMY__.)
# Pre_Variable_True = N/A
# Pre_Variable_False = IME_SOFTKEYBOARD_7COLUMN_UI_SUPPORT
# Option_Selection = __IME_MMI_MY__, __IME_MMI_SG__, __IME_MMI_CSTAR__, __IME_MMI_DUMMY__
IME_SOLUTION =

# Feature_Name = KOMOXO ScriptEasy Bitmap Font engine
# Description = [MMI] KOMOXO ScriptEasy Bitmap Font engine
# Pre_Variable_True = N/A
# Pre_Variable_False = INDIC_FONT_SUPPORT
# Option_Selection = TRUE, FALSE
SCRIPT_EASY_BITMAP_FONT_SUPPORT = FALSE

# Feature_Name = KOMOXO IME CSTAR Softkey Board Style
# Description = [MMI] IME KOMOXO Softkey Board Style(Digial or qwerty).  only support IME_CSTAR_VK_QWERTY for these language(TAMIL,TELUGU,AMHARIC,PUNJABI,GUJARATI,KHMER,MARATHI,MYANMAR)
# Pre_Variable_True = IME_SOLUTION(__IME_MMI_CSTAR__)
# Pre_Variable_False = N/A
# Option_Selection = IME_CSTAR_VK_DIGIT, IME_CSTAR_VK_QWERTY, IME_CSTAR_VK_DIGIT_P_QWERTY_L
IME_CSTAR_VK_STYLE =

# Feature_Name = KOMOXO User Data
# Description = [MMI] let users can customize the phrase
# Pre_Variable_True = N/A
# Pre_Variable_False = IME_SOLUTION(__IME_MMI_CSTAR__)
# Option_Selection = TRUE, FALSE
KMX_USER_DATA_ENABLED = TRUE

# Feature_Name = Use pure foreign lib for IME SG
# Description = [MMI] Use pure foreign lib(Disable simple chinese) for IME SG
#           to save more code size
# Pre_Variable_True = IME_SOLUTION(__IME_MMI_SG__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
IME_SG_FOREIGN_ONLY = FALSE

# Feature_Name = IME SG input language
# Description = [MMI] IME SG input language (!!At most 5 languages can be included.
#           All languages are separated by space!!)
# Pre_Variable_True = IME_SOLUTION(__IME_MMI_SG__)
# Pre_Variable_False = N/A
# Option_Selection = __IME_SG_CHINESE_S__ __IME_SG_ARABIC__ __IME_SG_BENGALI__ __IME_SG_CZECH__ __IME_SG_DUTCH__ __IME_SG_ENGLISH__ __IME_SG_FRENCH__
#                    __IME_SG_GERMAN__ __IME_SG_GREEK__ __IME_SG_HINDI__ __IME_SG_INDONESIAN__ __IME_SG_ITALIAN__ __IME_SG_MALAY__ __IME_SG_PERSIAN__
#                    __IME_SG_POLISH__ __IME_SG_PORTUGUESE__ __IME_SG_RUSSIAN__ __IME_SG_SPANISH__ __IME_SG_THAI__ __IME_SG_TURKISH__ __IME_SG_VIETNAMESE__
IME_SG_LANG_SUPPORT = __IME_SG_CHINESE_S__ __IME_SG_ENGLISH__

# Feature_Name = JAVA_OAKMONT_REDUCE_MEMORY
# Description = JAVA Oakmont reudce memory enable
# Pre_Variable_True = JAVA_SOLUTION (__JAVA_OAKMONT__, __JAVA_OAKMONT_JAP0__, __JAVA_OAKMONT_JAP2__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
JAVA_OAKMONT_LOW_MEMORY = FALSE

# Feature_Name = Support Java Preinstall Data
# Description = [MMI] Support JAVA preinstall data
# Pre_Variable_True = JAVA_SOLUTION(__NCC_3RD_JAVA_PORTING_LAYER_S__,__NCC_3RD_JAVA_PORTING_LAYER_M__, __JAVA_OAKMONT__, __JAVA_OAKMONT_JAP0__, __JAVA_OAKMONT_JAP2__), ONBOARD_USER_STORAGE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
JAVA_PREINSTALL_DATA_SUPPORT = FALSE

# Feature_Name = Java Install To Phone
# Description = [MMI] JAVA install midlet to phone
# Pre_Variable_True = JAVA_SOLUTION(__NCC_3RD_JAVA_PORTING_LAYER_S__,__NCC_3RD_JAVA_PORTING_LAYER_M__), ONBOARD_USER_STORAGE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
JAVA_INSTALL_TO_PHONE_SUPPORT = FALSE

# Feature_Name = AUTO-ROTATE DISPLAY
# Description = Auto-rotate display Flag
# Pre_Variable_True = G_SENSOR_TYPE
# Pre_Variable_False = __LCM_LANDSCAPE__
# Option_Selection = TRUE, FALSE
AUTO_ROTATE_DISPLAY_SUPPORT = FALSE

# Feature_Name = Dropdown StatusPage
# Description = Display Dropdown StatusPage, Support_Resolution = __LCM_QVGA__,
#           __LCM_LANDSCAPE_QVGA__, __LCM_WQVGA_240_400__, __LCM_LANDSCAPE_WQVGA_240_400__,
#           __LCM_HVGA_320_480__
# Pre_Variable_True = __TOUCH_SCREEN__
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = N/A
DROPDOWN_STATUSPAGE_SUPPORT = FALSE

# Feature_Name = Multi-Themes Enabled
# Description = support multi-themes, if enabled this feature, need set CUS_PROJECT = CommonPortraitTheme
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
MULTI_THEMES_ENABLED = FALSE

# Feature_Name = SMS Chat
# Description = Option for SMS Chat feature(MCA)
# Pre_Variable_True = N/A
# Pre_Variable_False = __LCM_QQVGA__, __LCM_LANDSCAPE_QQVGA__
# Option_Selection = TRUE, FALSE
SMS_CHAT_SUPPORT = FALSE

# Feature_Name = SMS-Export
# Description = Option to enable SMS-Export feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_EXPORT_SUPPORT = FALSE

# Feature_Name = SMS-Trashbox
# Description = Option to enable SMS-Trashbox feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_TRASHBOX_SUPPORT = FALSE

# Feature_Name = SMS Single TPSRR
# Description = Option for single TPSRR (MCI)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_SINGLE_TPSRR_SUPPORT = FALSE

# Feature_Name = [MMI] Support R8 SMS encode/decode
# Description = Support R8 SMS encode/decode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_3GPP_R8_SUPPORT = FALSE

# Feature_Name = Send SMS when full
# Description = Option for sending SMS without saving
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_SEND_WHEN_FULL_SUPPORT = FALSE

# Feature_Name = [MMI] Using 7 column IME softkeyboard
# Description = Using 7 column IME softkeyboard
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = LCM_RESOLUTION(__LCM_QCIF_PLUS__), IME_SOLUTION(__IME_MMI_CSTAR__)
# Option_Selection = TRUE, FALSE
IME_SOFTKEYBOARD_7COLUMN_UI_SUPPORT = FALSE

# Feature_Name = MMS read report
# Description = Option for MMS read report feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMS_READ_REPORT_SUPPORT = FALSE

# Feature_Name = File deleter before sending MMS
# Description = File deleter before sending MMS
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
USER_FILE_DELETER_SUPPORT = FALSE

# Feature_Name = [MMI] Animated menu effect
# Description = Animated menu effect
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
MMI_ANIMATED_MENU_EFFECT_SUPPORT = FALSE

# Feature_Name = Distorted Voice
# Description = Option to enable Distorted Voice
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DISTORTED_VOICE_SUPPORT = FALSE

# Feature_Name = Option menu for incoming call view
# Description = Provide option menu in Incoming Call view.
# Pre_Variable_True = DISTORTED_VOICE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CCMTA_OPTION_MENU_SUPPORT = FALSE

# Feature_Name = Answering Machine
# Description = Option for Answering Machine feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ANSWERING_MACHINE_SUPPORT = FALSE

# Feature_Name = Call Background Sound
# Description = Option for Call Background Sound
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALL_BACKGROUND_SOUND_SUPPORT = FALSE

# Feature_Name = Phonebook VideoTone
# Description = Option for Phonebook VideoTone
# Pre_Variable_True = __NAND__
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_VIDEOTONE_SUPPORT = FALSE

# Feature_Name = In Call Recording
# Description = Option for In Call Recording
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
IN_CALL_RECORDING_SUPPORT = TRUE

# Feature_Name = Auto Recording
# Description = Option to enable the auto recording. When a call is established, it will automatically begin the recording session.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
AUTO_RECORDING_SUPPORT = TRUE

# Feature_Name = Program Temp IMEI
# Description = Option to program temp IMEI.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PROGRAM_TEMP_IMEI_SUPPORT = TRUE

# Feature_Name = Indic language layout engine (Ex: Hindi, Bengali, Tamil, Telugu)
# Description = [MMI] Support Indic language layout engine
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT, SCRIPT_EASY_BITMAP_FONT_SUPPORT
# Option_Selection = TRUE, FALSE
INDIC_FONT_SUPPORT = FALSE

# Feature_Name = Chinese Simplified
# Description = [MMI] Support Chinese Simplified, include PINYIN table, GBK
#           table...etc. this feature could be disabled in 64_32 oversea version
#           to get more code size
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CHINESE_S_SUPPORT = TRUE

# Feature_Name = Chinese Traditional
# Description = [MMI] Support Chinese Traditional, include BIG5 table, BOPOMOFO
#           table...etc. this feature could be disabled in 64_32 oversea version
#           to get more code size
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CHINESE_T_SUPPORT = FALSE

# Feature_Name = NAND/SD recovery
# Description = Option to enable CHECKDISK application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CHECK_DISK_APP_SUPPORT = FALSE

# Feature_Name = Remind user to do checkdisk
# Description = Option to enable reminding checkdisk
# Pre_Variable_True = CHECK_DISK_APP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CHECK_DISK_REMIND_SUPPORT = FALSE

# Feature_Name = Hidden Partition
# Description = Option to add hidden Partition in the product
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HIDDEN_PARTITION_SUPPORT = FALSE

# Feature_Name = Screen saver
# Description = Option to enable screen saver application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SCREENSAVER_SUPPORT = FALSE

# Feature_Name = [MMI] Cache ADN to RAM without use RAI.
# Description = Cache ADN to RAM without use RAI.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHB_CACHE_ADN_TO_RAM_SUPPORT = FALSE

# Feature_Name = Navigation Key
# Description = [MMI] Support navigation key in idle mode.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NAVI_KEY_SUPPORT = FALSE

# Feature_Name = Disable handwritting input
# Description = [MMI] handwritting input is default on when touch is supported.
#           You can turn it off by this option.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DISABLE_HANDWRITING_INPUT_SUPPORT = FALSE

# Feature_Name = Touch hotkey
# Description = Option to enable touch hotkey.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TOUCH_HOTKEY_SUPPORT = FALSE

# Feature_Name = Support mp3 id3 tag
# Description = [MMI] Sppport mp3 id3 tag
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ID3_TAG_SUPPORT = TRUE

# Feature_Name = Device Information
# Description = Support Show Device Information in engineer mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DEVICE_INFO_SUPPORT = FALSE

# Feature_Name = Composite hotkey to launch keyguard
# Description = [MMI] Support composite hotkey to launch keyguard in idle mode.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
COMPOSITE_HOTKEY_LAUNCH_KEYGUARD_SUPPORT = FALSE

# Feature_Name = Display GPRS Traffic
# Description = GPRS Icon is twinkling with traffic
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = N/A
SUPPORT_DISPLAY_GPRS_TRAFFIC = FALSE

# Feature_Name = Anti-Steal
# Description = Option to enable Anti-Steal feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ANTI_STEAL_SUPPORT = FALSE

# Feature_Name = Remote-Control
# Description = Option to enable Remote-Control feature
# Pre_Variable_True = ANTI_STEAL_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ANTI_STEAL_REMOTE_CONTROL_SUPPORT = FALSE

# Feature_Name = SMS-Blacklist
# Description = Option to enable SMS-Blacklist feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMSBLACKLIST_SUPPORT = FALSE

# Feature_Name = SMS-Search
# Description = Option to enable SMS-Search feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_SEARCH_SUPPORT = FALSE

# Feature_Name = SMS-WapPush
# Description = Option to enable Wap Push SMS feature
# Pre_Variable_True = WAP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMS_WAPPUSH_SUPPORT = TRUE

# Feature_Name = Caller Location
# Description = Option to enable Caller Location feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALLER_LOCATION_SUPPORT = TRUE

# Feature_Name = View Message in Outbox Support
# Description = Option for View Message in Outbox feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_VIEW_MSG_IN_OUTBOX_SUPPORT = FALSE

# Feature_Name = Smart Dialer
# Description = Option to enable smart dialer function
#               SMART_NUMBER_FILTER_SUPPORT & SMART_ALPHABET_FILTER_SUPPORT will enabled automatically.
#               Only support Portrait (QCIF_PLUS, QVGA, HVGA, WQVGA), and Landscape (HVGA, WQVGA)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SMART_DIALER_SUPPORT = FALSE

# Feature_Name = Shortcut Speed Dialer
# Description = Option to enable shortcut speed dialer function
# Pre_Variable_True = SHORTCUTLIST_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DIAL_SHORTCUT_SUPPORT = FALSE

# Feature_Name = Azan alarm
# Description = Option to enable Azan application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
AZAN_APP_SUPPORT = FALSE

# Feature_Name = Bezier curve screen effect
# Description = Option to enable bezier curve screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_BEZIER_SUPPORT = FALSE

# Feature_Name = Snow screen effect
# Description = Option to enable snow screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_SNOW_SUPPORT = FALSE

# Feature_Name = Ripple screen effect
# Description = Option to enable ripple screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_RIPPLE_SUPPORT = FALSE

# Feature_Name = Fire screen effect
# Description = Option to enable Fire screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_FIRE_SUPPORT = FALSE

# Feature_Name = Fire-fly screen effect
# Description = Option to enable fire-fly screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_FIREFLY_SUPPORT = FALSE

# Feature_Name = Water screen effect
# Description = Option to enable water screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_WATER_SUPPORT = FALSE

# Feature_Name = Meteor screen effect
# Description = Option to enable Meteor screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_METEOR_SUPPORT = FALSE

# Feature_Name = Space screen effect
# Description = Option to enable space screen effect
# Pre_Variable_True = N/A
# Pre_Variable_False = 3D_SUPPORT
# Option_Selection = TRUE, FALSE
SCREEN_EFFECT_SPACE_SUPPORT = FALSE

# Feature_Name = Network Counter App
# Description = Option for a network Counter App
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
NETWORK_COUNTER_MMI_SUPPORT = FALSE

# Feature_Name = mmi search app (MMI)
# Description = Option for search app in MMI
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_SEARCH_APP_SUPPORT = FALSE

# Feature_Name = mmi group app (MMI)
# Description = Option for group app in MMI
#           Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA).
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_GROUP_APP_SUPPORT = FALSE

# Feature_Name = mmi blue dialer app (MMI)
# Description = Option for blue dialer app in MMI
#           Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA).
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
MMI_BLUE_DIALER_APP_SUPPORT = FALSE

# Feature_Name = ntp
# Description = Option to enable ntp application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NTP_SUPPORT = FALSE

# Feature_Name = Sqlite
# Description = Option for sqlite feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SQLITE_SUPPORT = FALSE

# Feature_Name = Calculator(MMI)
# Description = Option for calculator style
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT, LCM_RESOLUTION(__LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_HVGA_320_480__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_HVGA__)
# Pre_Variable_False = N/A
# Option_Selection = __CALCULATOR_NORMAL_STYLE__, __CALCULATOR_PLUS_STYLE__
CALCULATOR_STYLE = __CALCULATOR_NORMAL_STYLE__

# Feature_Name = Cell broadcast area code(MMI)
# Description = There are regulations in some country (ex:Brasil) to specifically display CBMs with channel-50 on Idle screen,
#               but not treat them as normal CBM.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
CBM_AREA_CODE_SUPPORT = FALSE

# Feature_Name = FM Radio Schedule
# Description = Option to enable FM radio schedule function
# Pre_Variable_True = FM_RADIO_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FM_RADIO_SCHEDULE_SUPPORT = FALSE

# Feature_Name = Http Video Streaming feature
# Description = Option to enable http video streaming features
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE, FALSE
VIDEO_HTTP_STREAMING_SUPPORT = FALSE

# Feature_Name = Rtsp Video Streaming feature
# Description = Option to enable rtsp video streaming features
# Pre_Variable_True = CHIP_TYPE(__MSW8536N__, __MSW8533N__)
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE, FALSE
VIDEO_RTSP_STREAMING_SUPPORT = FALSE

# Feature_Name = TuDou
# Description = Only support Portrait (HVGA)
# Pre_Variable_True = LCM_RESOLUTION(__LCM_HVGA_320_480__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TUDOU_SUPPORT = FALSE

# Feature_Name = Support Tudou in GPRS only
# Description = Support Tudou in GPRS only
# Pre_Variable_True = TUDOU_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TUDOU_GPRS_ONLY_SUPPORT = FALSE

# Feature_Name = Factory mode format internal flash
# Description = Option to enable format nand or nor in factory mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FACTORY_MODE_FORMAT_INTERNAL_FLASH = FALSE

# Feature_Name = MMI Engineering Mode Audio APP to SD Feature
# Description = Option for MMI Engineering Mode Audio APP to SD Feature
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SOLUTION(4MB)
# Option_Selection = TRUE , FALSE
MMI_EM_AUDIO_APPTOSD_SUPPORT = TRUE

#===============================================================================
# ** 3D Options **
#===============================================================================
# Feature_Name = 3D SUPPORT
# Description = Option to select 3D engine support. G3D_SUPPORT is used for
#           HW G3D support; MGLS_SUPPORT is used for software 3D engine.
# Pre_Variable_True = LCM_RESOLUTION(__LCM_QVGA__, __LCM_HVGA_320_480__, __LCM_WQVGA_240_400__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_HVGA__, __LCM_LANDSCAPE_WQVGA_240_400__)
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = G3D_SUPPORT, MGLS_SUPPORT
3D_SUPPORT =

# Feature_Name = Physical game engine (MMI)
# Description = Physical game engine in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PHYSICAL_ENGINE_SUPPORT = FALSE

# Feature_Name = MGLS LOW MEMORY SUPPORT
# Description = for 128/32 low memory with MGLS
# Pre_Variable_True = 3D_SUPPORT(MGLS_SUPPORT)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MGLS_LOW_MEMORY_SUPPORT = FALSE

# Feature_Name = 3D PICKING SUPPORT
# Description = Option to select 3D picking support with MGLS. Enable picking will occupy extra memory which size is equal to LCD_WIDTH*LCD_HEIGHT.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(*), 3D_SUPPORT(MGLS_SUPPORT)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MGLS_PICKING_SUPPORT = FALSE

# Feature_Name = 3D-effect option-menu
# Description = Option to enable the 3D-effect option-menu
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_OPTION_MENU_3D_EXT_SUPPORT = FALSE

# Feature_Name = Idle Style
# Description = Idle app UI Style Selection
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = UI_STYLE_MMI_ANDROID_IDLE_SUPPORT
# Option_Selection = APP_MMI_IDLE_GADGETBAR_STYLE, APP_MMI_IDLE_SIMPLE_STYLE, APP_MMI_IDLE_MULTIPAGE3D_STYLE, APP_MMI_IDLE_SIMPLE3D_STYLE, APP_MMI_IDLE_GADGETBAR3D_STYLE
IDLE_EFFECT =

# Feature_Name = Idle Preview Style
# Description = Idlepreview app UI Style Selection
# Pre_Variable_True = APP_MMI_IDLE_MULTIPAGE3D_STYLE
# Pre_Variable_False = N/A
# Option_Selection = PAGEVIEW, CUBEVIEW
IDLEPREVIEW_EFFECT =

# Feature_Name = 3D-effect mainmenu app
# Description = Option to enable 3D-effect mainmenu app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_MAINMENU_SUPPORT = FALSE

# Feature_Name = 3D Spin Main Menu
# Description = Option to enable the 3D spin main menu
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT, UI_STYLE_SPIN_MAIN_MENU_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
UI_STYLE_3D_SPIN_MAIN_MENU_SUPPORT = FALSE

# Feature_Name = 3D-effect keyguard app. If option is APP_MMI_UI_KEYGUARD_SIMPLE, then there is no 3D effect on the keyguard app.
# Description = Keyguard app 3D UI Style Selection
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = APP_MMI_UI_KEYGUARD_SIMPLE, APP_MMI_UI_KEYGUARD_GLOW, APP_MMI_UI_KEYGUARD_BEAUTY_CLK
KEYGUARD_EFFECT =

# Feature_Name = 3D-effect kingmovie
# Description = Option to enable the 3D-effect kingmove
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT, TOUCH_SCREEN_DRIVER_SELECT(*)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_KINGMOVIE_SUPPORT = FALSE

# Feature_Name = 3D-effect e-book app
# Description = Option to enable 3D-effect e-book app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_EBOOK_SUPPORT = FALSE

# Feature_Name = 3D-effect music-player app
# Description = Option to enable 3D-effect music-player app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_MPLAYER_SUPPORT = FALSE

# Feature_Name = 3D-effect music-player coverflow (MMI)
# Description = Option to enable 3D-effect music-player coverflow
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_COVERFLOW_SUPPORT = FALSE

# Feature_Name = 3D-effect FM-radio app
# Description = Option to enable 3D-effect FM-radio app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_FMRADIO_SUPPORT = FALSE

# Feature_Name = 3D-effect picture-viewer slideshow
# Description = Option to enable 3D-effect picture-viewer slideshow
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_PICVIEWER_SLIDESHOW_SUPPORT = FALSE

# Feature_Name = 3D-effect photo slide (MMI)
# Description = Option to enable 3D-effect photo slide
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_PHOTOSLIDE_SUPPORT = FALSE

# Feature_Name = 3D-effect screen saver (MMI)
# Description = Option to enable random 3D-effect screen saver
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_SCREENSAVER_EFFECT_SUPPORT = FALSE

# Feature_Name = 3D-effect phonebook app
# Description = Option to enable 3D-effect phonebook app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_PHONEBOOK_SUPPORT = FALSE

# Feature_Name = 3D-effect shortcut app
# Description = Option to enable 3D-effect shortcut app
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_3DUI_SHORTCUTAPP_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect
# Description = Option for 3D live wallpaper in MMI, it include image wallpaper by default
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Earthrot
# Description = Option for 3D live wallpaper effect(Earthrot) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_EARTHROT_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Solar System
# Description = Option for 3D live wallpaper effect(Solar System) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_SOLARSYSTEM_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Comet
# Description = Option for 3D live wallpaper effect(Comet) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_COMET_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Snakeline
# Description = Option for 3D live wallpaper effect(Snakeline) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_SNAKELINE_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Seashore
# Description = Option for 3D live wallpaper effect(Seashore) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_SEASHORE_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Jump Gate
# Description = Option for 3D live wallpaper effect(Jump Gate) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_JUMPGATE_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Fallsnow
# Description = Option for 3D live wallpaper effect(Fallsnow) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_FALLSNOW_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Weather
# Description = Option for 3D live wallpaper effect(Weather) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_WEATHER_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Fluttersnow
# Description = Option for 3D live wallpaper effect(Fluttersnow) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_FLUTTERSNOW_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Grasstrace
# Description = Option for 3D live wallpaper effect(Grasstrace) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_GRASSTRACE_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect Fish
# Description = Option for 3D live wallpaper effect(Fish) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_FISH_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect FARM
# Description = Option for 3D live wallpaper effect(FARM) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_FARM_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect BIRD
# Description = Option for 3D live wallpaper effect(BIRD) in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_BIRD_SUPPORT = FALSE

# Feature_Name = Beauty clock app
# Description = Option for beauty clock app in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_BEAUTY_CLK_APP_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect DROPLET
# Description = Option for PGL live wallpaper effect(DROPLET) in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT(*)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_DROPLET_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect INWATER
# Description = Option for PGL live wallpaper effect(INWATER) in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT(*)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_INWATER_SUPPORT = FALSE

# Feature_Name = Live WallPaper Effect INWATERSHOOT
# Description = Option for PGL live wallpaper effect(INWATERSHOOT) in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT(*)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LIVE_WALLPAPER_INWATERSHOOT_SUPPORT = FALSE

# Feature_Name = SIM No response handle
# Description = Option for SIM No response handle
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SIM_NO_RESPONSE_HANDLING_SUPPORT = FALSE
#===============================================================================
# Do not modify following option
#===============================================================================
# Feature_Name =
# Description = Option to enable on-chip FMRX
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ONCHIP_FMRX_ENABLE_SUPPORT = TRUE

# Feature_Name = Network lock
# Description = Option for a network lock
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
NETWORK_LOCK_SUPPORT = FALSE

# Feature_Name = SP(Service Provider) lock
# Description = Option for a SP lock
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SP_LOCK_SUPPORT = FALSE
#===============================================================================
# Customer proprietary compile option
#===============================================================================

#-------------------------------------------------------------------------------
# Set proper profile for specific product. It is used for simulator loader.
#-------------------------------------------------------------------------------
# SIMULATOR_PROFILE = [AUTO,HVGA,Landscape_HVGA,Landscape_QCIF,Landscape_QQVGA,Landscape_QVGA,Landscape_WQVGA,QCIF,QQVGA,QVGA,WQVGA]
# AUTO : auto select by script. reference to LCM_SUPPORT in common_option.mak
SIMULATOR_PROFILE = QCIF

#-------------------------------------------------------------------------------
# Set proper RF IC and PA for specific product
#-------------------------------------------------------------------------------
# Feature_Name = define RF IC
# Description = define RF IC
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = msr7100d, msr7100, aero2_4209, aero2_4210
RFIC = msr7100

# Feature_Name = define PA
# Description = define PA
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = rfmd3159, rfmd3166, rfmd3196, rfmd4180, rfmd7163, rfmd7168, rfmd7169, sky77518, sky77531, sky77344, rpf08155b, rpf88130b, rpf89007b, am7801, rda6231, rda6232
PA = rfmd7163

#-------------------------------------------------------------------------------
# Set Sensor Table
# Sensor source file & folder should be located at proj\sc\customer\product\cust\drv\sensor\$(Platform)
#-------------------------------------------------------------------------------
SENSOR_CUS_SRC =

SENSOR_CUS_FOLDER =

#-------------------------------------------------------------------------------
# Set LCD Table
# LCD source file should be located at proj\sc\customer\product\cust\drv\lcm\lcdtbl
# LCD source folder should be located at proj\sc\customer\product\cust\drv\lcm\
# Pre_Variable_True = CUS_LCM_TABLE_SUPPORT
#-------------------------------------------------------------------------------
LCD_CUS_SRC = \
    LT_FAKE.dat

LCD_CUS_FOLDER = $(LCD_BASE)

#-------------------------------------------------------------------------------
# Set Display Table
# Display source file & folder should be located at proj\sc\customer\product\cust\drv\disptbl\$(Platform)
# Pre_Variable_True = CUS_DISPLAY_TABLE_SUPPORT
#-------------------------------------------------------------------------------
DISP_CUS_SRC = \

DISP_CUS_FOLDER =

#-------------------------------------------------------------------------------
# Set SDRAM/DDRAM clock - Assignment must match folder name under \system\bootup\
#-------------------------------------------------------------------------------
RAM_CLOCK = PSRAM

#===============================================================================
# ** Product Configuration Options **
#===============================================================================

#-------------------------------------------------------------------------------
# Cust system configuration
#-------------------------------------------------------------------------------
# Feature_Name = define DRAM/PSRAM size
# Description = define the physical ram size (4MB, 8MB, 32MB)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = 0x00400000, 0x00800000, 0x02000000
SYS_PHY_RAM_SIZE_SETTING = 0x08000000

#-------------------------------------------------------------------------------
# define which sys config c file would be used in \proj\sc\customer\product\cust\sys\src\
#-------------------------------------------------------------------------------
SYS_CONFIG = default

#-------------------------------------------------------------------------------
# define which sys time config c file would be used in \proj\sc\customer\product\cust\sys\src\
#-------------------------------------------------------------------------------
SYSTIME_CONFIG = default

#-------------------------------------------------------------------------------
# define which fms config c file would be used in \proj\sc\customer\product\cust\sys\src\
#-------------------------------------------------------------------------------
FMS_CONFIG = default

#-------------------------------------------------------------------------------
# define which e2p config c file would be used in \proj\sc\customer\product\cust\sys\src\
#-------------------------------------------------------------------------------
SYS_E2P =

#-------------------------------------------------------------------------------
# define maximum string length of vendor name definition for USB device
#-------------------------------------------------------------------------------
MAXIMUM_LENGTH_OF_USB_VENDOR_NAME_SEETING = 8

#-------------------------------------------------------------------------------
# Customer's mmi options : Assign the appropriate customer mmi EM options
#-------------------------------------------------------------------------------
EM_CUSTOM =

#-------------------------------------------------------------------------------
# Customer's APP&ARP calibration table options : Assign the appropriate customer APP&ARP table
# The tables should be sync. with OPT_APP_ENGINE_ID & OPT_ARP_ENGINE_ID
# Configuration files are in \customer\product\cust\drv\app_calibration_table\src\
#                            \customer\product\cust\drv\arp_calibration_table\src\
#-------------------------------------------------------------------------------
CALTBL = isw

#-------------------------------------------------------------------------------
# Customer's driver options : Assign the appropriate customer driver options
# Configuration files are in \proj\sc\customer\product\cust\drv\
#-------------------------------------------------------------------------------
BATTERY = isw
GPIO = isw
PM = isw
KEYPAD = isw
KPDLIGHT =
PWM = default
TOUCHSCREEN =
SERVICE = default
GPD =
DISPTBL_DEFAULT = type_4
LCD_LOGO_BASE =
SUB_LCD_LOGO_BASE =
BACKLIGHT =
OFN =
GSENSOR =

#-------------------------------------------------------------------------------
# Options for Panel Physical Size (The unit is um. 1mm = 1000 um)
#-------------------------------------------------------------------------------
PANEL_PHYSICAL_WIDTH = 0
PANEL_PHYSICAL_HEIGHT = 0

#-------------------------------------------------------------------------------
# Options for LCD Driver Files (folder type)
# All files in the folder will be built.
# Base Path : proj\sc\customer\product\cust\drv\lcm\
# Pre_Variable_False = CUS_LCM_TABLE_SUPPORT
#-------------------------------------------------------------------------------
LCD_BASE =

#-------------------------------------------------------------------------------
# Options for LCD Driver Files (file list type)
# All files of the list will be built.
# Base Path : proj\sc\customer\product\cust\drv\lcm\global_base\
# Pre_Variable_False = CUS_LCM_TABLE_SUPPORT
#-------------------------------------------------------------------------------
LCD_SRC_LIST =

#-------------------------------------------------------------------------------
# Options for TSCR CTP Driver Files (list type)
# Pre_Variable_true = TOUCH_SCREEN_DRIVER_SELECT = __CUST_CTP__
# All files of the list will be built.
# Base Path : proj\sc\customer\product\cust\drv\tscr\src\cust_tscr_*.c
#-------------------------------------------------------------------------------
TSCR_CTP =

#-------------------------------------------------------------------------------
# audio & cus e2p configuration file in \proj\sc\customer\product\cust\e2p\
#-------------------------------------------------------------------------------
MAKE_AUD_E2P = isw
MAKE_CUS_E2P = isw

#-------------------------------------------------------------------------------
# nandprt size configuration : Assign the nandprt size
#-------------------------------------------------------------------------------
NANDPRT_SIZE =

#-------------------------------------------------------------------------------
# nandprt partition configuration file in \proj\sc\customer\product\cust\nandprt\
#-------------------------------------------------------------------------------
PARTITION_V2_PNI = default

#-------------------------------------------------------------------------------
# Options for code size checking tool. (fms_cas_Identifiers[] in customer\default\src\drv\acc\src\mcp_drv_msw*.c)
# Code size checking is skipped on NAND products
#-------------------------------------------------------------------------------
CHECK_SIZE_CRITICAL_MCP = MACRONIX_MX25U6435E
PRODUCT_SIZE = 64

#-------------------------------------------------------------------------------
# Options for file system configuration of NOR product.
# It is skipped on NAND products
#-------------------------------------------------------------------------------
CRITICAL_LANGPACK =
APP_REQ_SIZE =
APP_REQ_OBJ_ENTRY =
FAT_REQ_SIZE =
FAT_PRELOAD_PATH =
HFAT_REQ_SIZE =
HFAT_PRELOAD_PATH =

#===============================================================================
# Customer proprietary compile option
#===============================================================================
PP_OPT_COMMON += __I_SW__
PP_OPT_COMMON += __I_SW_OS__
PP_OPT_COMMON += __I_SW_BOOTFAST__
PP_OPT_COMMON += __ISW_INFINITY__
PP_OPT_COMMON += __ISW_NORBOOT__
PP_OPT_COMMON += __NO_GPRS__

RTK_USER_TICK = 1ms


# Feature_Name = Compiler TYPE
# Description = Option for compiler type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __ARM9__, __CORTEX_A7__, __AEONG__
CPU_TYPE = __CORTEX_A7__
PP_OPT_COMMON += $(CPU_TYPE)

#===============================================================================
# ** Alpha options **
#===============================================================================
# Feature_Name = MKV
# Description = Option for supporting MKV
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MKV_SUPPORT = FALSE

# Feature_Name = TS
# Description = Option for supporting TS
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TS_SUPPORT = FALSE

# Feature_Name = PS
# Description = Option for supporting PS
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
PS_SUPPORT = FALSE

#===============================================================================
# ** Engineer options **
#===============================================================================
# Feature_Name = BRAVO TARGET EVB
# Description = Option for target Board type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
BRAVO_TARGET_EVB = FALSE

# Feature_Name =
# Description = Option for EVB that has no real battery
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EVB_WITHOUT_BATTERY_SUPPORT = FALSE

# Feature_Name =
# Description = [RF] Use RF DB with EVB rather than phone board
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
RADIO_USE_DB_SUPPORT = FALSE

# Feature_Name = SAMSUNG K5L2833ATA operation mode configuration
# Description = Option to Config SAMSUNG K5L2833ATA use page+page mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SAMSUNG_K5L2833ATA_PAGE_PAGE_MODE = FALSE

# Feature_Name = LCM_ROTATE_SIMULATION,temporary solution to rotate by driver.
# Description = rotate by driver
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LCM_ROTATE_SIMULATION = FALSE

# Feature_Name =
# Description = Option for user to choose one of the logos by e2p while multi
#           boot logos binary are built-in in the image. (e2p: WBootLogoID)
# Pre_Variable_True = BOOTUP_LOGO_TYPE
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
BOOTUP_LOGO_BY_E2P_SUPPORT = FALSE

# Feature_Name = LCD table driver
# Description = Option for user to enable/disable lcd table support. If enabled,
#           the makefile will gather all table files assigned from LCD_CUS_SRC
#           and LCD_CUS_FOLDER, then generate the cus file for lcd table.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CUS_LCM_TABLE_SUPPORT = FALSE

# Feature_Name = Display table driver
# Description = Option for user to enable/disable display table support. If
#           enabled, the makefile will gather all table files assigned from
#           DISP_CUS_SRC and DISP_CUS_FOLDER, then generate the CUS file for
#           display table.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CUS_DISPLAY_TABLE_SUPPORT = FALSE

# Feature_Name = Force Turn Off APP Spectial IP's Power
# Description = Option to Turn Off Spectial IP
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
OPT_A2DP_APP_DRCLIMITER_POWER = FALSE
OPT_A2DP_APP_SPEAKERPEQ_POWER = FALSE

# Feature_Name =
# Description = [MMI] Compile option for building sdk example source codes and
#           test cases
# Pre_Variable_True = SDK_MMI_VENDOR_ENTRY_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SDK_MMI_TEST_SUPPORT = FALSE
VFS_TEST_CASE_SUPPORT = FALSE

# Feature_Name = [MMI] Skip Calibration Points Check
# Description = Option to Skip Calibration Points Check
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SKIP_CALIBRATION_POINTS_CHECK = FALSE

# Feature_Name = CPU speed
# Description = Option to force cpu speed 364MHz
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CPU_FORCE_364MHZ_SUPPORT = FALSE

# Feature_Name = IQ dump
# Description = IQ dump with AM patch for Legacy
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
IQDUMP_FOR_SIMU_SUPPORT = FALSE

# Feature_Name =
# Description = [RF] Determine whether radio driver for Legacy should be included
#           in the software build.
# Pre_Variable_True = Corresponding E2P settings
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
RADIO_LEGACY_ANALOG_SUPPORT = FALSE

# Feature_Name =
# Description = [LEGACY] Keep Keypad PWM static for Legacy
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LEGACY_KEYPAD_LIGHT_PATCH_SUPPORT = FALSE

# Feature_Name =
# Description = [LEGACY] Options for Legacy AM DSP patch.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LEGACY_AM_PATCH_SUPPORT = FALSE

# Feature_Name =
# Description = [LEGACY] Asura VBUCK configure for Legacy
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
LEGACY_VBUCK_CLOCK_PATCH_SUPPORT = FALSE

# Feature_Name = Unit test app
# Description = Option for a unit test app
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
UNIT_TEST_APP_SUPPORT = FALSE

# Feature_Name = Auto test engine
# Description = Enable auto test script (64_32 does not support this in release
#           package)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
AUTO_TEST_SUPPORT = FALSE

# Feature_Name = Enable service wrapper unit test app in DLM
# Description = Option for generating the unit test app in DLM format
# Pre_Variable_True = UNIT_TEST_APP_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DLM_SRVUT_SUPPORT = FALSE

# Feature_Name = Diag Error
# Description = Turn off: Compiler error would stop the build process. Turn
#           off: Compiler error and "warning" would stop the build process (since
#           this option would treat compile warning as compile error)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DIAG_ERROR_SUPPORT = FALSE

# Feature_Name = Save Pool Status
# Description = Save Pool Status
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SAVE_POOLSTATUS_MMI_SUPPORT = FALSE

# Feature_Name = GOGOBOX Game (MMI)
# Description = Gogobox 3D game in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_GOGOBOX_GAME_SUPPORT = FALSE

# Feature_Name = FruitSlice Game (MMI)
# Description = FruitSlice 3D game in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_FRUITSLICE_GAME_SUPPORT = FALSE

# Feature_Name = Vampire Game (MMI)
# Description = Vampire physic engine in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_VAMPIRE_GAME_SUPPORT = FALSE

# Feature_Name = Zombie Game (MMI)
# Description = Zombie physic engine in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_ZOMBIE_GAME_SUPPORT = FALSE

# Feature_Name =FishFury Game (MMI)
# Description = FishFury physic game in MMI
# Pre_Variable_True = PHYSICAL_ENGINE_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_FISHFURY_GAME_SUPPORT = FALSE

# Feature_Name = Rubik cube Game
# Description = Rubik cube game in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_RUBIKCUBE_GAME_SUPPORT = FALSE

# Feature_Name = Labyrinth Game (MMI)
# Description = Labyrinth 3D game in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_LABYRINTH_GAME_SUPPORT = FALSE

# Feature_Name = I Play Game
# Description = I play game in MMI
# Pre_Variable_True = G3D_SUPPORT or MGLS_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_IPLAYCUBE_GAME_SUPPORT = FALSE

# Feature_Name = RFID CMD ITF TYPE
# Description = Option for RFID Command Interface Type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __RFID_CMD_ITF_UART0__, __RFID_CMD_ITF_UART1__, __RFID_CMD_ITF_STD_SPI__, __RFID_CMD_ITF_PAGING_SPI__, __RFID_CMD_ITF_GPIO_SPI__, __RFID_CMD_ITF_STD_I2C__, __RFID_CMD_ITF_GPIO_I2C__,__RFID_CMD_ITF_USB__
RFID_COMMAND_ITF_TYPE =

# Feature_Name = RFID FW UPGRADE ITF TYPE
# Description = Option for RFID FW Upgrade Interface Type
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = __RFID_FWU_ITF_CMD__, __RFID_FWU_ITF_STD_I2C__, __RFID_FWU_ITF_GPIO_I2C__
RFID_FWUPG_ITF_TYPE =

# Feature_Name = SPI Max Speed support
# Description = Option for SPI Max Speed support
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
SPI_MAX_SPEED = FALSE

# Feature_Name = Check CPU speed before sleep
# Description = Option for Check CPU speed before sleep
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE , FALSE
CHECK_CPU_STATUS_BEFORE_SLEEP_SUPPORT = FALSE

# Feature_Name = Support Network Setting Cus
# Description = load network setting cus then replace phone setting at first boot phone
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_NETWORK_SETTING_CUS_SUPPORT = TRUE

# Feature_Name = Support all palette 8 image decoded as palette 8 buffer format
# Description = [MMI] Turn on this option, all 8 bit image can be decoded to 8 bit buffer as default
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MMI_SUPPORT_ALL_PALETTE8_IMAGE = FALSE

# Feature_Name = MMI Engineering Mode Touch Panel Enhance Test
# Description = Option for MMI Engineering Mode Touch Panel Enhance Test
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__CUST_CTP__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
EM_TOUCHSCREEN_TEST_ENHANCE_SUPPORT = FALSE

# Feature_Name = Compatible chip download flag
# Description = Make Dwlwin to support compatible chip download
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
COMPATIBLE_CHIP_SUPPORT = TRUE

#===============================================================================
# ** Obsolete options **
#===============================================================================
# Feature_Name = Touch screen, scall down feature
# Description = Option to scaling down the position of touch screen if touch
#           panel was larger than LCD.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
TOUCH_SCREEN_SCALE_DOWN_SUPPORT = FALSE

# Feature_Name = Memory Card
# Description = Option to support memory card. This feature only works when
#           HW have memory card device (e.g. MicroSD/MiniSD/...)
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
MEMCARD_SUPPORT = FALSE

# Feature_Name =
# Description = [SYS] Enable EMI PAD function during sleep mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EMI_PAD_PWD_SUPPORT = FALSE

#+++[M5_CarDV]
# Feature_Name =
# Description = [VDEC] Enable video decoder
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = HW_MJPG, HW_MP4V, HW_H264
VIDEO_DECODER = HW_MP4V

# Feature_Name = Network Option
# Description = [NET] Software Network stack, typically application layer.
# Pre_Variable_True = WIFI_PORT=1
# Pre_Variable_False = N/A
# Option_Selection = (none), _ENABLE_UPNP_, LWIP_DEBUG, __AMNSS_DEBUG__, __UPNP_DEBUG__
NET_OPT = _ENABLE_UPNP_ LWIP_DEBUG __AMNSS_DEBUG__ __UPNP_DEBUG__
WIFI_PORT = TRUE
#---[M5_CarDV]
