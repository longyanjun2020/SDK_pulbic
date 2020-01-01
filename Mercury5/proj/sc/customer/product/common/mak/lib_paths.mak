


#-------------------------------------------------------------------------------
#
# scope: Specify which module should be link!
#
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
#
# WARNING: The following path should be placed to dedicated file !!!
#
#          e.g.  PATH_sys = $(PATH_system)/sys
#					--> please add to 'paths.mak'
#
#          e.g.  PATH_C += $(PATH_sys)/src
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/inc
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/pub
#					--> it is public path, please add to 'paths_pub.mak'
#
#          e.g. path is telecom folder
#                   --> it is telecom path, please add to 'paths_tel.mak'
#
#-------------------------------------------------------------------------------







# Specify all libraries which should not be compiled from source code
# in PRODUCT_LIB, and note that:
# 1. Library name specified here should not appear in PRODUCT_SC again.
# 2. Don't specify any library name which was not originally specified in
#    PRODUCT_SC. For example, "mmi", "camera" shall not be specified in
#    PRODUCT_LIB.
#

#= Core SW =================================================================
PRODUCT_LIB = \
  csn1\
  cc\
  ce\
  data\
  dl\
  fax\
  hwl\
  hwl_prod\
  hwl_tiny\
  ip\
  ip_dummy\
  l1c\
  llc\
  mmc\
  mmc_cus\
  mmp\
  mmp_cus\
  mms\
  mnp2\
  ngip\
  ngos\
  ngppp\
  pps\
  rld\
  rlu\
  sim\
  sim_cus\
  tel_cus\
  smg\
  sms\
  sn\
  ss\
  v42\
  v42b\
ps_cork

ifeq (TRUE, $(strip $(CHIP_TGGE_RF)))
PRODUCT_LIB += \
  hwl_rf_tgge
else
PRODUCT_LIB += \
  hwl_rf_aero2\
  hwl_rf_msr7100\
  hwl_rf_msr7120
endif

ifeq ($(COMPILER_VERSION), RVCTV22)
PRODUCT_LIB += \
  rrc1\
  rrc2\
  rrc3\
  rrd\
  rrs\
  rrm\
  rrt\
  rrp
endif


PRODUCT_SC = \
  ati_main\
  ati_cc\
  ati_cphs\
  ati_phb\
  ati_ps\
  ati_mm\
  ati_modem\
  ati_serial\
  ati_sim\
  ati_sms\
  ati_ss\
  sati_main\
  sati_cc\
  sati_cphs\
  sati_phb\
  sati_ps\
  sati_mm\
  sati_modem\
  sati_serial\
  sati_sim\
  sati_sms\
  sati_ss\
  cus_app\
  cus_app_lib\
  cus_app_sc\
  dynldr\
  dynldr_cus\
  fcm\
  hwl_cus\
  MsWrapper\
  rtk\
  rtk_cus\
  sys\
  sys_cus\
  trc\
  trc_cus\
  vml_ase\
  vml_cc\
  vml_cphs\
  vml_ps\
  vml_sms\
  vml_sim\
  vml_phb\
  vml_mm\
  vml_ss\
  vml_stlk\
  vml_util\
  v24\
  v24_cus\
  fc

ifeq ($(COMPILER_VERSION), RVCTV22)
PRODUCT_SC += \
  boot\
  arm
endif


PRODUCT_SC += \
  dlm_entry

#= DUO section ================================================================
# -- Modification for project DUO
# JY: Place the name of module you want to duplicate here. An additional library
#     will be produced with all exported symbols renamed (by post-fix "_2")
#
# Alex: Add sim module to duplicate for B2/B3.
#ifeq ($(call FIND_COMPILER_OPTION, __WLAN_IP_SUPPORT__), TRUE)
PRODUCT_LIB_STACK2 =        \
  ip\
  ngip\
  ngos
#else
#PRODUCT_LIB_STACK2 =        \

# -- Reduce code size
#  cc\
#  dl\
#  grr\
#  ip\
#  llc\
#  mmc\
#  mmp\
#  mms\
#  ngip\
#  ngos\
#  ngppp\
#  pps\
#  rld\
#  rlu\
#  sim\
#  sms\
#  smg\
#  sn\
#  ss
#endif

#ifeq ($(call FIND_COMPILER_OPTION, __WLAN_IP_SUPPORT__), TRUE)
PRODUCT_LIB_STACK2_MERGE =     \
  stack_2
#endif

PRODUCT_SC_STACK2 =        \

# -- Reduce code size
#  ati\
#  vml

#= MDL section ================================================================

PRODUCT_SC_MDL = \
  audio\
  abb_mdl\
  audio_mdl\
  batt\
  compression_mdl\
  cpu_mdl\
  fms_cus\
  gpd_mdl\
  gss\
  image_config\
  keypad_mdl\
  pm_mdl\
  rai\
  tscr_mdl\
  vfs\
  drm_vfs\
  ut_mdl\
  camera_mdl\
  camera_top\
  camera_ip\
  demuxer\
  efat\
  efat_cust\
  efat_wrapper\
  eml_dlm\
  image_capture\
  mmaudio_common\
  mmaudio_common_release\
  mmaudio_getinfo\
  midi\
  mp3dec_codec\
  aacdec_codec\
	wmadec_codec\
	cookdec_codec\
  mp3enc_codec\
  mp3layer3enc_codec\
  sbcenc_codec\
  wavenc_codec\
  wavdec_codec\
  mmaudio_spectrum\
  mmmanager\
  mmmanager_lib\
  3dsurround\
  peq\
  hw_geq\
  hw_peq\
  exp_vol\
  drc_limiter\
  drc_limiter_v2\
  drclookahead_limiter\
  hard_limiter\
  hw_drc\
  reverb\
  bass\
  sc_fade\
  srs_wowhd\
  time_stretch\
  timepitch_stretch\
  app_mgr\
  app_mgr_shell\
  arp_exp_vol\
  arp_sw_agc\
  arp_hw_agc\
  arp_mgr\
  arp_mgr_shell\
  mmp_common\
  storage_mdl\
  usb_mdl\
  mtmgr\
  vdr\
  vdr_mux\
  vdr_top \
  stereo_image_main\
  sril\
  sril_msync\
  sril_wrapper\
  ril_kernel\
  ril_cb\
  ril_cc\
  ril_cphs\
  ril_ps\
  ril_phb\
  ril_pwof\
  ril_rr\
  ril_sec\
  ril_stk\
  ril_ss\
  ril_sms\
  ril_sim\
  ril_msync

ifeq ($(filter ENABLE_AMRNB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_DEC)
PRODUCT_SC_MDL += amrnbdec_codec
endif

ifeq ($(filter ENABLE_AMRNB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_ENC)
PRODUCT_SC_MDL += amrnbenc_codec
endif

ifeq ($(filter ENABLE_AMRWB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_DEC)
PRODUCT_SC_MDL += amrwbdec_codec
endif

ifeq ($(filter ENABLE_AMRWB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_ENC)
PRODUCT_SC_MDL += amrwbenc_codec
endif

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PRODUCT_SC_MDL += \
  ofn_mdl
endif

ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PRODUCT_SC_MDL += \
  ball_mdl
endif

ifeq ($(call FIND_COMPILER_OPTION,__ATV_DRV__),TRUE)
PRODUCT_SC_MDL += \
  tv_mdl
endif

ifeq ($(call FIND_COMPILER_OPTION,__GPS_DUALSTAR_DRV__),TRUE)
PRODUCT_SC_MDL += \
  gps_mdl
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
PRODUCT_SC_MDL += \
  rfid_mdl
#endif

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC_MDL += fms_nand
else
PRODUCT_SC_MDL += fms_nor
endif

ifeq ($(call FIND_COMPILER_OPTION,__MDL_OMA_DRM_V1__),TRUE)
PRODUCT_SC_MDL += \
  drm_util
endif

ifeq ($(filter __SMALL_ROM_32__ ,$(PP_OPT_COMMON)), __SMALL_ROM_32__)
PRODUCT_SC_MDL += \
  image_codec_32\
  mp4demux_s32\
  mmplayer_s32\
  viddecoder_s32
else
PRODUCT_SC_MDL += \
  image_codec\
  mp4demux\
  mmplayer\
  viddecoder
endif


ifeq ($(filter __MULTI_TOUCH_SLIM__ ,$(PP_OPT_COMMON)), __MULTI_TOUCH_SLIM__)
PRODUCT_SC_MDL += \
  tscr_mdl_slim
endif

#= DRV section ===============================================================

PRODUCT_SC_DRV = \
  acc\
  adc\
  adc_hal\
  audio_drv\
  audio_hal\
  batt_hal\
  battery\
  bluetooth\
  bus\
  bus_hal\
  clkgen\
  clkgen_hal\
  cust_drv\
  cust_drv_dummy\
  disp\
  disp_hal\
  dma2d\
  dma2d_hal\
  emi\
  emi_hal\
  flash\
  flash_hal\
  gpd_drv\
  gpd_hal\
  gsensor\
  proximitysensor\
  proximitysensor_hal\
  backlight\
  int\
  int_hal\
  io\
  io_hal\
  kernel_hal\
  keypad\
  keypad_hal\
  lcd\
  lcd_hal\
  pll_hal\
  pm\
  pm_hal\
  power\
  rtc\
  rtc_hal\
  timer\
  timer_hal\
  tscr\
  tscr_hal\
  uart\
  uart_hal\
  time\
  disk\
  disk_storage\
  drvutil_hal\
  drvtable_hal\
  dynscl\
  dynscl_hal\
  fmrx\
  fmrx_hal\
  jpd\
  jpe\
  jpe_hal\
  pmu_hal\
  scl\
  scl_hal\
  sensorif\
  sensorif_hal\
  sensordriver\
  fcie\
  sdio\
  storage\
  usb\
  usb_hal\
  glue\
  bdma\
  bdma_hal




ifeq ($(filter __QUAD_SIM_DUAL_STANDBY__ ,$(PP_OPT_COMMON)),__QUAD_SIM_DUAL_STANDBY__)
PRODUCT_LIB_DRV +=\
    sim_mux_switch
endif

ifneq ($(filter __DRV_NO_HW_DMA__ ,$(PP_OPT_COMMON)),__DRV_NO_HW_DMA__)
PRODUCT_SC_DRV +=\
    dma\
    dma_hal
endif

ifeq ($(filter __PICVIEWERAPP_SUPPORT_HW_JPD_MMI__ ,$(PP_OPT_COMMON)),__PICVIEWERAPP_SUPPORT_HW_JPD_MMI__)
PRODUCT_SC_DRV +=\
    jpd_hal
endif

ifeq ($(filter __ROMPATCH_SUPPORT__ ,$(PP_OPT_COMMON)),__ROMPATCH_SUPPORT__)
ifeq ($(COMPILER_VERSION), RVCTV22)
PRODUCT_SC_DRV +=\
    rompatch_hal
endif
endif

ifeq ($(filter __GDMA_SUPPORT__ ,$(PP_OPT_COMMON)),__GDMA_SUPPORT__)
PRODUCT_SC_DRV +=\
    gdma_hal
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PRODUCT_LIB_DRV +=\
    g3d
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PRODUCT_LIB_DRV += \
  gps
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
PRODUCT_LIB_DRV += \
  rfid
#endif

ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PRODUCT_SC_DRV +=\
    atv\
    atv_util
endif

ifeq ($(call FIND_COMPILER_OPTION, __MPIF_HAL__), TRUE)
PRODUCT_SC_DRV += mpif_hal
endif

ifeq ($(call FIND_COMPILER_OPTION, __MPIF_DRV__), TRUE)
PRODUCT_SC_DRV += mpif
endif

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC_DRV += \
  unfd\
  unfd_hal
endif

ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PRODUCT_SC_DRV += \
  ball\
  ball_hal
endif
ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PRODUCT_SC_DRV += \
  ofn\
  ofn_hal
endif

ifeq ($(filter __HW_ZLIB_SUPPORT__ ,$(PP_OPT_COMMON)),__HW_ZLIB_SUPPORT__)
PRODUCT_SC_DRV +=\
  zlib_drv\
  zlib_hal
endif

# WIFI
PRODUCT_SC_DRV += wlan_cus
PRODUCT_SC_DRV += supplicant_cus
ifeq ($(call FIND_COMPILER_OPTION, __WLAN__), TRUE)
PRODUCT_SC_DRV += wlan
PRODUCT_SC_DRV += supplicant_ctrl
PRODUCT_SC_DRV += supplicant_crypto
PRODUCT_SC_DRV += supplicant_common
PRODUCT_SC_DRV += wlan_drv
PRODUCT_SC_DRV += wlan_hal
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for bluetooth library
PRODUCT_LIB_DRV +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
PRODUCT_LIB_DRV +=\
	a2dp
endif
else
PRODUCT_LIB_DRV +=\
	bt_host
endif
endif




#= SYS section ================================================================

PRODUCT_SC_SYS = \
  cn\
  ResMgr\
  truetype\
  ucs2\
  cust_sys\
  bsp_837\
  bsp_8f4\
  bsp_833\
  bsp_737\
  bsp_838\
  bsp_c3c\
  bsp_6k3\
  bsp_mn\
  sqlite\
  sddl

ifeq ($(filter __MSERVICES__, $(PP_OPT_COMMON)),__MSERVICES__)
PRODUCT_SC_SYS += SocketMgr
endif

#= MMI section ================================================================

PRODUCT_SC_MMI_APP = \
  cust_mmi \
  AlarmApp \
  AtvApp \
  BjxApp \
  BmiApp \
  CalculatorApp \
  CallLogApp \
  CallSettingApp \
  CamApp \
  CbSettingApp \
  CcApp \
  CcMtaApp \
  ConSettingApp \
  DesktopWidget \
  DialerApp \
  DialogApp \
  EmApp \
  EvtCenterApp \
  FdnApp \
  FileMgrApp \
  MessageCenterApp \
  MessageEditorApp \
  MessageTemplateApp \
  MessageViewerApp \
  MmsSettingApp \
  MplayerApp \
  NetworkApp \
  OffApp \
  OnApp \
  PhbApp \
  PicViewerApp \
  ProfileApp \
  RemoteControlApp \
  SecApp \
  SendViaApp \
  SettingApp \
  SmsSettingApp \
  StkApp \
  UnitConverterApp \
  UsbApp \
  UssdApp \
  VendorApp \
  VideoPlayerApp \
  VideoTelephonyApp \
  VoiceMailApp \
  VoiceMemoApp \
  RfidApp

ifeq ($(filter __UI_STYLE_MMI_ANDROID_IDLE__ ,$(PP_OPT_COMMON)),__UI_STYLE_MMI_ANDROID_IDLE__)
PRODUCT_SC_MMI_APP += AndroidIdleApp
else
PRODUCT_SC_MMI_APP += IdleApp
endif

ifeq ($(filter __UI_STYLE_MMI_ANDROID_KEYGUARD__ ,$(PP_OPT_COMMON)),__UI_STYLE_MMI_ANDROID_KEYGUARD__)
PRODUCT_SC_MMI_APP += AndroidKeyGuardApp
else
PRODUCT_SC_MMI_APP += KeyGuardApp
endif

ifeq ($(filter __UI_STYLE_MMI_STYLE_SWITCH__ ,$(PP_OPT_COMMON)),__UI_STYLE_MMI_STYLE_SWITCH__)
PRODUCT_SC_MMI_APP += KeyGuardApp
endif

ifeq ($(filter __UI_STYLE_MMI_ANDROID_MAIN_MENU__ ,$(PP_OPT_COMMON)),__UI_STYLE_MMI_ANDROID_MAIN_MENU__)
PRODUCT_SC_MMI_APP += AndroidMainMenuApp
endif

PRODUCT_SC_MMI_APP += MainMenuApp

# AliveWidget is enabled when
# defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
ifneq ($(filter __GADGETS_MMI__ __3D_UI_IDLE_GADGETBAR__, $(PP_OPT_COMMON)),)
PRODUCT_SC_MMI_APP += AliveWidget
endif

ifeq ($(filter __ANTI_STEAL_MMI__ ,$(PP_OPT_COMMON)),__ANTI_STEAL_MMI__)
PRODUCT_SC_MMI_APP += AntiStealApp
endif

ifeq ($(filter __FT_AUTO_TEST__ ,$(PP_OPT_COMMON)),__FT_AUTO_TEST__)
PRODUCT_SC_MMI_APP += AutotestApp
endif

ifeq ($(filter __APP_MMI_AZAN__ ,$(PP_OPT_COMMON)),__APP_MMI_AZAN__)
PRODUCT_SC_MMI_APP += AzanApp
endif

ifeq ($(filter __MMI_BEAUTY_CLK_APP__ ,$(PP_OPT_COMMON)), __MMI_BEAUTY_CLK_APP__)
PRODUCT_SC_MMI_APP += BeautyClkSettingApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_BIG2__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_BIG2__)
PRODUCT_SC_MMI_APP += Big2
endif

ifeq ($(filter __BLUETOOTH_MMI__ ,$(PP_OPT_COMMON)), __BLUETOOTH_MMI__)
PRODUCT_SC_MMI_APP += BtApp
PRODUCT_SC_MMI_APP += BtNotifyApp
endif

ifeq ($(filter __APP_MMI_CALCULATOR_PLUS__ ,$(PP_OPT_COMMON)), __APP_MMI_CALCULATOR_PLUS__)
PRODUCT_SC_MMI_APP += CalculatorPlusApp
endif

ifeq ($(filter __APP_MMI_CALENDAR__ ,$(PP_OPT_COMMON)), __APP_MMI_CALENDAR__)
PRODUCT_SC_MMI_APP += CalendarApp
endif

ifeq ($(filter __TOUCH_SCREEN_MMI__ ,$(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
PRODUCT_SC_MMI_APP += CalibrationApp
endif

ifeq ($(filter __CALLER_LOCATION__ ,$(PP_OPT_COMMON)), __CALLER_LOCATION__)
PRODUCT_SC_MMI_APP += CallerLocationApp
endif

ifeq ($(filter __WAP_MMI_CDWAP__ ,$(PP_OPT_COMMON)), __WAP_MMI_CDWAP__)
PRODUCT_SC_MMI_APP += CdWapApp
endif

ifeq ($(filter __APP_MMI_CHECKDISK__ ,$(PP_OPT_COMMON)),__APP_MMI_CHECKDISK__)
PRODUCT_SC_MMI_APP += CheckDiskApp
endif

ifeq ($(filter __APP_MMI_COUNTDOWN_TIMER__ ,$(PP_OPT_COMMON)), __APP_MMI_COUNTDOWN_TIMER__)
PRODUCT_SC_MMI_APP += CountdownTimerApp
endif

ifeq ($(filter __DICTAPP_MMI__ ,$(PP_OPT_COMMON)), __DICTAPP_MMI__)
PRODUCT_SC_MMI_APP += DictApp
endif

ifeq ($(filter __APP_MMI_GROUP_APP__ ,$(PP_OPT_COMMON)), __APP_MMI_GROUP_APP__)
PRODUCT_SC_MMI_APP += DialerGroupApp
endif


ifeq ($(filter __E_BOOK_MMI__ ,$(PP_OPT_COMMON)), __E_BOOK_MMI__)
PRODUCT_SC_MMI_APP += EbookApp
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)), __EMAIL_MMI__)
PRODUCT_SC_MMI_APP += EmailApp
endif

ifeq ($(filter __GAME_ENGINE_EMU_MMI__ ,$(PP_OPT_COMMON)), __GAME_ENGINE_EMU_MMI__)
PRODUCT_SC_MMI_APP += EmuApp
endif

ifeq ($(filter __APP_MMI_GROUP_APP__ ,$(PP_OPT_COMMON)), __APP_MMI_GROUP_APP__)
PRODUCT_SC_MMI_APP += FavoritePhbApp
endif

ifeq ($(filter __UI_STYLE_MMI_IFONE__ ,$(PP_OPT_COMMON)), __UI_STYLE_MMI_IFONE__)
PRODUCT_SC_MMI_APP += FavoritePhbApp
endif

ifeq ($(filter __APP_MMI_FM_RADIO__ ,$(PP_OPT_COMMON)), __APP_MMI_FM_RADIO__)
PRODUCT_SC_MMI_APP += FmRadioApp
endif

ifeq ($(filter __APP_MMI_FM_SCHEDULE__ ,$(PP_OPT_COMMON)), __APP_MMI_FM_SCHEDULE__)
PRODUCT_SC_MMI_APP += FmSchApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_FRUIT__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_FRUIT__)
PRODUCT_SC_MMI_APP += FruitGambleGame
endif

ifeq ($(filter __FRUITSLICE_GAME__ ,$(PP_OPT_COMMON)), __FRUITSLICE_GAME__)
PRODUCT_SC_MMI_APP += FruitSliceGame
endif

ifeq ($(filter __3D_UI_MAINMENU__ ,$(PP_OPT_COMMON)), __3D_UI_MAINMENU__)
PRODUCT_SC_MMI_APP += G3DMainMenuApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_GOBANG__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_GOBANG__)
PRODUCT_SC_MMI_APP += GoBangApp
endif

ifeq ($(filter __GOGOBOX_GAME__ ,$(PP_OPT_COMMON)), __GOGOBOX_GAME__)
PRODUCT_SC_MMI_APP += GogoBoxGame
endif

ifeq ($(filter __NATIVE_GAME_MMI_HAMSTERFIGHT__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_HAMSTERFIGHT__)
PRODUCT_SC_MMI_APP += HamsterFightApp
endif

ifeq ($(filter __3D_UI_IDLE_MULTIPAGE__ ,$(PP_OPT_COMMON)), __3D_UI_IDLE_MULTIPAGE__)
PRODUCT_SC_MMI_APP += IdlePreviewApp
PRODUCT_SC_MMI_APP += ShortcutPhbApp
endif

ifneq ($(filter __3D_UI_IDLE_MULTIPAGE__ __3D_UI_PHOTOSLIDE_MMI__ , $(PP_OPT_COMMON)),)
PRODUCT_SC_MMI_APP += PicPreviewApp
endif

ifeq ($(filter __IPLAYCUBE_GAME__,$(PP_OPT_COMMON)), __IPLAYCUBE_GAME__)
PRODUCT_SC_MMI_APP += IplayCube
endif

ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
PRODUCT_SC_MMI_APP += JavaAmsApp
PRODUCT_SC_MMI_APP += JavaFactoryApp
endif

ifeq ($(filter __MMI_KING_MOVIE__, $(PP_OPT_COMMON)), __MMI_KING_MOVIE__)
PRODUCT_SC_MMI_APP += KingMovieApp
endif

ifeq ($(filter __LABYRINTH_GAME__, $(PP_OPT_COMMON)), __LABYRINTH_GAME__)
PRODUCT_SC_MMI_APP += LabyrinthGame
endif

ifeq ($(filter __ANGRYBIRD_GAME__, $(PP_OPT_COMMON)), __ANGRYBIRD_GAME__)
PRODUCT_SC_MMI_APP += AngryBird
endif

ifeq ($(filter __CUTROPE_GAME__, $(PP_OPT_COMMON)), __CUTROPE_GAME__)
PRODUCT_SC_MMI_APP += CutRope
endif

ifeq ($(filter __FISHFURY_GAME__, $(PP_OPT_COMMON)), __FISHFURY_GAME__)
PRODUCT_SC_MMI_APP += FishFuryGame
endif

ifeq ($(filter __VAMPIRE_GAME__, $(PP_OPT_COMMON)), __VAMPIRE_GAME__)
PRODUCT_SC_MMI_APP += VampireGame
endif

ifeq ($(filter __ZOMBIE_GAME__, $(PP_OPT_COMMON)), __ZOMBIE_GAME__)
PRODUCT_SC_MMI_APP += ZombieGame
endif

ifeq ($(filter __APP_MMI_NTP__ ,$(PP_OPT_COMMON)), __APP_MMI_NTP__)
PRODUCT_SC_MMI_APP += NtpApp
endif

ifeq ($(filter __APP_MMI_LICENSEMGR__, $(PP_OPT_COMMON)), __APP_MMI_LICENSEMGR__)
PRODUCT_SC_MMI_APP += LicenseMgrApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_LINKUP__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_LINKUP__)
PRODUCT_SC_MMI_APP += LinkUpApp
endif

ifeq ($(filter __MGL_DEMO__ ,$(PP_OPT_COMMON)), __MGL_DEMO__)
PRODUCT_SC_MMI_APP += MglDemoApp
PRODUCT_SC_MMI_APP += WdgDemoApp
endif

ifeq ($(filter __NETWORK_COUNTER_MMI__ ,$(PP_OPT_COMMON)), __NETWORK_COUNTER_MMI__)
PRODUCT_SC_MMI_APP += NetworkCounterApp
endif

ifeq ($(filter __APP_MMI_NOTEPAD__ ,$(PP_OPT_COMMON)), __APP_MMI_NOTEPAD__)
PRODUCT_SC_MMI_APP += NotepadApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_PACMAN__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_PACMAN__)
PRODUCT_SC_MMI_APP += PacMan
endif

ifeq ($(filter __APP_MMI_PRIVATEPROTECT__ ,$(PP_OPT_COMMON)), __APP_MMI_PRIVATEPROTECT__)
PRODUCT_SC_MMI_APP += PrivateprotectApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_PUZZLE__ ,$(PP_OPT_COMMON)), __NATIVE_GAME_MMI_PUZZLE__)
PRODUCT_SC_MMI_APP += PuzzleApp
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)),__NCCQQ_MMI__)
PRODUCT_SC_MMI_APP += QQApp
endif

ifeq ($(filter  __RUBIKCUBE_GAME__, $(PP_OPT_COMMON)), __RUBIKCUBE_GAME__)
PRODUCT_SC_MMI_APP += RubiksCube
endif

ifeq ($(filter __MMI_SEARCH_APP__, $(PP_OPT_COMMON)), __MMI_SEARCH_APP__)
PRODUCT_SC_MMI_APP += SearchApp
endif

ifeq ($(filter __APP_MMI_SCREENSAVER__, $(PP_OPT_COMMON)), __APP_MMI_SCREENSAVER__)
PRODUCT_SC_MMI_APP += ScreensaverApp
endif

ifeq ($(filter __APP_MMI_SHORTCUT__, $(PP_OPT_COMMON)), __APP_MMI_SHORTCUT__)
PRODUCT_SC_MMI_APP += ShortcutsApp
endif

ifeq ($(filter __APP_MMI_SKETCHNOTE__, $(PP_OPT_COMMON)), __APP_MMI_SKETCHNOTE__)
PRODUCT_SC_MMI_APP += SnoteApp
endif

#ifeq ($(filter __APP_MMI_SOHU_UPDATER__, $(PP_OPT_COMMON)), __APP_MMI_SOHU_UPDATER__)
PRODUCT_SC_MMI_APP += SoHuUpdaterApp
#endif

ifeq ($(filter __NATIVE_GAME_MMI_SOKOBAN__, $(PP_OPT_COMMON)), __NATIVE_GAME_MMI_SOKOBAN__)
PRODUCT_SC_MMI_APP += SokobanApp
endif

ifeq ($(filter __APP_MMI_STOPWATCH__, $(PP_OPT_COMMON)), __APP_MMI_STOPWATCH__)
PRODUCT_SC_MMI_APP += StopwatchApp
endif

ifeq ($(filter __NATIVE_GAME_MMI_SUDOKU__, $(PP_OPT_COMMON)), __NATIVE_GAME_MMI_SUDOKU__)
PRODUCT_SC_MMI_APP += SudokuApp
endif

ifeq ($(filter __APP_MMI_TODOLIST__, $(PP_OPT_COMMON)), __APP_MMI_TODOLIST__)
PRODUCT_SC_MMI_APP += ToDoListApp
endif

ifeq ($(filter __APP_MMI_TUDOU__ ,$(PP_OPT_COMMON)),__APP_MMI_TUDOU__)
PRODUCT_SC_MMI_APP += TuDouApp
endif

ifeq ($(filter __WLAN_MMI__, $(PP_OPT_COMMON)), __WLAN_MMI__)
PRODUCT_SC_MMI_APP += WiFiApp
endif

ifeq ($(filter __APP_MMI_WORLDCLOCK__, $(PP_OPT_COMMON)), __APP_MMI_WORLDCLOCK__)
PRODUCT_SC_MMI_APP += WorldClockApp
endif

ifeq ($(filter __UNIT_TEST_APP__ ,$(PP_OPT_COMMON)),__UNIT_TEST_APP__)
PRODUCT_SC_MMI_APP += \
  UnitTestApp
endif

ifeq ($(filter __APP_MMI_TUDOU__ ,$(PP_OPT_COMMON)),__APP_MMI_TUDOU__)
PRODUCT_SC_MMI_APP += \
  TuDouApp
endif
PRODUCT_SC_MMI_CUSDEFINE = \
  CusDefine

PRODUCT_SC_MMI_SRVWRAPPER = \
  SrvWrapper

PRODUCT_SC_MMI_SRV = \
  srv

ifeq ($(filter __UNIT_TEST_SRV__ ,$(PP_OPT_COMMON)),__UNIT_TEST_SRV__)
PRODUCT_SC_MMI_SRV += \
  UnitTestSrv
endif

PRODUCT_SC_MMI_MAE = \
  mae

PRODUCT_SC_MMI_MAE_PORTING = \
  mae_porting

PRODUCT_LIB_MMI_MGL = \
  mgl

PRODUCT_LIB_MMI_MGL_PORTING = \
  mgl_porting

ifeq ($(filter __FEATURE_PGL__ ,$(PP_OPT_COMMON)),__FEATURE_PGL__)
PRODUCT_SC_MMI_PGL = \
  pgl
endif

PRODUCT_SC_MMI_CORE = \
  core

PRODUCT_SC_MMI_MMICOMN = \
  mmicomn

PRODUCT_SC_MMI_WIDGET = \
  widget\
  widget_priv

PRODUCT_SC_MMI_MODEL = \
  model

PRODUCT_SC_MMI_APP_LAUNCHER = \
  AppLauncher

PRODUCT_SC_MMI_NCCMms_ = \
  NCCMms_target
PRODUCT_SC_MMI_NCCMms_cus_ = \
  NCCMms_cus
PRODUCT_SC_MMI_NCCCommon_ = \
  NCCCommon_target
PRODUCT_SC_MMI_NCCCommon_wsp_ = \
  NCCCommon_wsp
PRODUCT_SC_MMI_NCCCommon_cus_ = \
  NCCCommon_cus
PRODUCT_SC_MMI_NCCBrowser_ = \
  NCCBrowser_target
PRODUCT_SC_MMI_NCCBrowser_cus_ = \
  NCCBrowser_cus

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PRODUCT_SC_MMI_NCCEmail_ = \
  NCCEmail_target
endif

PRODUCT_SC_MMI = \
  $(PRODUCT_SC_MMI_CORE)\
  $(PRODUCT_SC_MMI_MAE)\
  $(PRODUCT_SC_MMI_MAE_PORTING)\
  $(PRODUCT_SC_MMI_MMICOMN)\
  $(PRODUCT_SC_MMI_SRVWRAPPER)\
  $(PRODUCT_SC_MMI_WIDGET)\
  $(PRODUCT_SC_MMI_SRV)\
  $(PRODUCT_SC_MMI_MODEL)\
  $(PRODUCT_SC_MMI_PGL)\
  $(PRODUCT_SC_MMI_APP_LAUNCHER)\
  $(PRODUCT_SC_MMI_CUSDEFINE)\
  $(PRODUCT_SC_MMI_APP)

ifneq ($(filter __WAP__ __MMS__ ,$(PP_OPT_COMMON)),)
PRODUCT_SC_MMI += \
  $(PRODUCT_SC_MMI_NCCMms_)\
  $(PRODUCT_SC_MMI_NCCMms_cus_)\
  $(PRODUCT_SC_MMI_NCCCommon_)\
  $(PRODUCT_SC_MMI_NCCCommon_cus_)\
  $(PRODUCT_SC_MMI_NCCBrowser_)\
  $(PRODUCT_SC_MMI_NCCBrowser_cus_)
endif

ifeq ($(filter NCC_WSP ,$(PP_OPT_COMMON)),NCC_WSP)
PRODUCT_SC_MMI += $(PRODUCT_SC_MMI_NCCCommon_wsp_)
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PRODUCT_SC_MMI += $(PRODUCT_SC_MMI_NCCEmail_)
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PRODUCT_SC_MMI_QQ_ = qq


PRODUCT_SC_MMI += $(PRODUCT_SC_MMI_QQ_)
endif

PATH_EXT_LIB += $(PATH_stereo_video)
PATH_EXT_LIB += $(PATH_stereo_image)
PATH_EXT_LIB += $(PATH_core_lib_algorithm)/adas

ifeq (TRUE, $(strip $(WIFI_PORT)))
PATH_EXT_LIB += $(PATH_LibSourceInc_wifi_WiFi-RTL8189_lib)
PATH_EXT_LIB += $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_lib)
PATH_EXT_LIB += $(PATH_LibSourceInc_wifi_WiFi-ATBM6022_lib)
endif


ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
ifneq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)
PRODUCT_LIB_MMI += $(PRODUCT_LIB_MMI_MGL)
endif
endif

ifeq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)
PRODUCT_SC_MMI += $(PRODUCT_LIB_MMI_MGL_PORTING)
endif

PRODUCT_SC_CUS = \




#
# module FLAVOR setting
#

#FLAVOR_bus = _cork
#FLAVOR_io  = _cork
#FLAVOR_ir   = _cork
#FLAVOR_sim = _cork
FLAVOR_v42  = _cork
FLAVOR_fax  = _cork
FLAVOR_data = _cork






include $(COMMON)paths.mak











#==============================================================================#
#
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
#
#==============================================================================#




# CUS group source code

#==============================================================================#
# Core SW group source code
PATH_C +=\
    $(PATH_cus_app)/src\
    $(PATH_cus_app_lib)/src\
    $(PATH_cus_app_sc)/src

PATH_H +=\
    $(PATH_app)\
    $(PATH_core)/interface/inc\
    $(PATH_cus_app)/inc

# MMI group source code
PATH_H +=\
    $(PATH_mmicomn)/inc

# MDL group source code

PATH_H +=\
    $(PATH_mmmanager)/inc\
    $(PATH_mmmanager_lib)/inc\
    $(PATH_vfs)/inc


ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H +=\
    $(PATH_tv_mdl)/inc
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PATH_H +=\
    $(PATH_gps_mdl)/inc
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
PATH_H +=\
	$(PATH_rfid_mdl)/inc
#endif

ifeq ($(call FIND_COMPILER_OPTION, __BARCODE__), TRUE)
PRODUCT_SC_DRV += \
  rfid

PATH_C += $(PATH_uart)/src
PATH_H += $(PATH_uart)/inc

endif

# DRV group source code
PATH_H +=\
    $(PATH_audio_hal)/inc\
    $(PATH_disk)/inc\
    $(PATH_clkgen_hal)\inc\
    $(PATH_pmu_hal)/inc

# ZLIB
ifeq ($(filter __HW_ZLIB_SUPPORT__ ,$(PP_OPT_COMMON)),__HW_ZLIB_SUPPORT__)
PATH_H +=\
    $(PATH_zlib_drv)/inc\
    $(PATH_zlib_hal)/inc
endif

# WIFI
PATH_H +=\
    $(PATH_wlan_cus)/inc\
    $(PATH_supplicant_cus)/inc


ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PATH_H +=\
    $(PATH_g3d)/inc \
    $(PATH_g3d)/inc/EGL \
    $(PATH_g3d)/inc/GLES \
    $(PATH_g3d)/inc/KHR \
    $(PATH_g3d)/inc/g3d
PATH_EXT_LIB +=\
    $(PATH_g3d)/lib
endif


ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
ifeq (,$(strip $(PATH_atv)))
$(error Unsupported atv: $(ATV_CHIP))
endif

CHECK_ATV_DRIVER := $(wildcard $(PATH_atv))
ifeq ($(strip $(CHECK_ATV_DRIVER)),)
$(error Cannot find driver of $(ATV_CHIP) in $(PATH_atv))
endif


PATH_C +=\
    $(PATH_atv)/src
PATH_H +=\
    $(PATH_atv)/inc \
	$(PATH_atv_pub)
endif



ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_C +=\
    $(PATH_ofn_hal)/src
PATH_H +=\
    $(PATH_ofn_hal)/inc
endif


ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PATH_H +=\
    $(PATH_unfd_hal)/inc
endif

ifneq ($(filter __NO_HW_JPD__ ,$(PP_OPT_COMMON)),__NO_HW_JPD__)
PATH_C +=\
    $(PATH_jpd_hal)/src
endif

ifeq ($(call FIND_COMPILER_OPTION, __WLAN__), TRUE)
PATH_C += $(PATH_wlan_hal)/src
PATH_H += $(PATH_wlan_drv)/inc
PATH_H += $(PATH_wlan_hal)/inc
endif

# SYS group source code
PATH_C +=\
    $(PATH_application)sys/file_mgr/src\
    $(PATH_hopper)/src\
    $(PATH_cn)/src\
    $(PATH_ResMgr)/src/ABL \
    $(PATH_ResMgr)/src/DataStruct \
    $(PATH_ResMgr)/src/DBL \
    $(PATH_ResMgr)/src/HAL \
    $(PATH_ResMgr)/src/MediaCmd \
    $(PATH_ResMgr)/src/ResMgr \
    $(PATH_ResMgr)/src/Simulator \
    $(PATH_ResMgr)/src/Util \
    $(PATH_ResMgr)/src/SocketCore \
    $(PATH_ResMgr)/src/SocketResMgr \
    $(PATH_bsp_837)/src \
    $(PATH_bsp_8f4)/src \
    $(PATH_bsp_833)/src \
    $(PATH_bsp_737)/src \
    $(PATH_bsp_838)/src \
    $(PATH_bsp_c3c)/src \
    $(PATH_bsp_6k3)/src

PATH_H +=\
    $(PATH_application)sys/file_mgr/inc\
    $(PATH_hopper)/inc\
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/DBL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/SocketResMgr \
    $(PATH_mae)/inc \

#MMI group source code

MMI_PATH_H +=\
    $(PATH_mae)/porting/inc\
    $(PATH_mae)/inc \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmi_res)\
    $(PATH_cust_mmi)/inc

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc\
    $(PATH_mgl)/mParticle/inc\
    $(PATH_mgl)/mPorting/inc
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
MMI_PATH_H +=\
    $(PATH_g3d)/inc \
    $(PATH_g3d)/inc/EGL \
    $(PATH_g3d)/inc/GLES \
    $(PATH_g3d)/inc/KHR \
    $(PATH_g3d)/inc/g3d
endif

MMI_PATH_H +=\
    $(PATH_core) \
    $(PATH_core)/interface/inc\

# CUS group source code
PATH_C +=\

PATH_H +=\




































#
#= virtual libs group ==========================================================================
#


# This library set defines the libs which use ARM mode in compiling
# Note that it is a virtual libs group which indicate these libs use ARM mode,
# RD must add same lib name at above lib group.  e.g PRODUCT_LIB
ARM_LIB_LIST = \
#   dlm_entry


# This library set defines the libs which disable feedback options in compiling and linking
# Note that it is a virtual libs group which indicate these libs disable feedback options,
# RD must add same lib name at above lib group.  e.g PRODUCT_LIB
ifeq ($(filter __UNIT_TEST_APP__ ,$(PP_OPT_COMMON)),__UNIT_TEST_APP__)
UT_LIB_LIST = \
    dlm_entry \
    ut_mdl \
    MsWrapper

ifeq ($(filter __ENABLE_DLM_SRVUT__ ,$(PP_OPT_COMMON)),__ENABLE_DLM_SRVUT__)
UT_LIB_LIST += \
    SrvWrapper \
    UnitTestApp
endif

endif

UT_LIB_LIST += \
   mp3dec_codec \
   aacdec_codec

# This library set defines the libs which would not be linked to image.
# Note that it is a virtual libs group which indicate these libs would not be linked to image.
# RD must add same lib at above lib group.  e.g PRODUCT_LIB

# Description = [RF] Determine which radio driver should be included in the software build.
ifeq (FALSE, $(strip $(CHIP_TGGE_RF)))
ifeq ($(strip $(RFIC)), $(filter $(RFIC),msr7100 msr7100d))
# For Legacy
DUMMY_LIB_LIST +=\ hwl_rf_aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7120
else
ifeq ($(strip $(RFIC)),msr7120)
# For Apus
DUMMY_LIB_LIST +=\ hwl_rf_aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7100
else
# For Aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7100
DUMMY_LIB_LIST +=\ hwl_rf_msr7120
endif
endif
endif

# For bsp
BSP_FILE_LIST = $(foreach n, $(wildcard $(PATH_system)bsp/bsp*.mak), $(n:$(PATH_system)bsp/%.mak=%))
DUMMY_LIB_LIST += $(addprefix \ , $(filter-out $(BSP_ID) bsp_mn bsp_c0f, $(BSP_FILE_LIST)))

# Internal Audio Codec / Control


# Audio Post-Processer IPs
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_3D_SURROUND), TRUE)
DUMMY_LIB_LIST +=\ 3dsurround
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_USER_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SPEAKER_PEQ), TRUE)
DUMMY_LIB_LIST +=\ peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_GEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_GEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_geq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_GEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_GEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_geq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SPEAKER_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_USER_PEQ), TRUE)
DUMMY_LIB_LIST +=\ peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_PEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_PEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_VOL_CONTROL_EXP), TRUE)
DUMMY_LIB_LIST +=\ exp_vol
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DRC_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ drc_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DRC_LIMITER_V2), TRUE)
DUMMY_LIB_LIST +=\ drc_limiter_v2
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_LOOKAHEAD_DRC_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ drclookahead_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_HARD_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ hard_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_DRC), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_DRC), TRUE)
DUMMY_LIB_LIST +=\ hw_drc
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_DRC), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_DRC), TRUE)
DUMMY_LIB_LIST +=\ hw_drc
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SC_FADE), TRUE)
DUMMY_LIB_LIST +=\ sc_fade
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_TIME_STRETCH), TRUE)
DUMMY_LIB_LIST +=\ time_stretch
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_TIMEPITCH_STRETCH), TRUE)
DUMMY_LIB_LIST +=\ timepitch_stretch
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DM2), TRUE)
DUMMY_LIB_LIST +=\ dm2
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_REVERB), TRUE)
DUMMY_LIB_LIST +=\ reverb
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BASS), TRUE)
DUMMY_LIB_LIST +=\ bass
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SRSWOWHD), TRUE)
DUMMY_LIB_LIST +=\ srs_wowhd
endif

# Audio Pre-Processer IPs
ifneq ($(call FIND_COMPILER_OPTION, ARP_SW_GAINCTR_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_exp_vol
endif

ifneq ($(call FIND_COMPILER_OPTION, ARP_SW_AGC_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_sw_agc
endif

ifneq ($(call FIND_COMPILER_OPTION, ARP_BIG3HW_AGC_ENABLE), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ARP_G1HW_AGC_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_hw_agc
endif
endif


DUMMY_LIB_LIST +=\ cust_drv_dummy

ifeq ($(call FIND_COMPILER_OPTION, __WLAN_IP_SUPPORT__), TRUE)
DUMMY_LIB_LIST +=\ ip_dummy
endif
ifeq ($(call FIND_COMPILER_OPTION, __NO_GPRS__), TRUE)
DUMMY_LIB_LIST +=\ data
DUMMY_LIB_LIST +=\ ip
DUMMY_LIB_LIST +=\ llc
DUMMY_LIB_LIST +=\ ngip
DUMMY_LIB_LIST +=\ ngos
DUMMY_LIB_LIST +=\ ngppp
DUMMY_LIB_LIST +=\ pps
DUMMY_LIB_LIST +=\ rld
DUMMY_LIB_LIST +=\ rlu
DUMMY_LIB_LIST +=\ smg
DUMMY_LIB_LIST +=\ sn
else
DUMMY_LIB_LIST +=\ ps_cork
endif

#
# The following lib set e.g. LIB_ap_SET and LIB_sys_SET identify
# libs which do not want to release for each specified accounts.
#

#
# ap
#
LIB_ap_SET = \
  csn1 \
  cc \
  ce \
  data \
  demuxer \
  dl \
  dynldr \
  fax \
  rrc1\
  rrc2\
  rrc3\
  rrd\
  rrs\
  rrm\
  rrt\
  rrp\
  hwl \
  hwl_prod\
  hwl_tiny \
  ip \
  ip_dummy \
  l1c \
  llc \
  mmc \
  mmc_cus \
  mmp \
  mmplayer \
  mmp_cus \
  mms \
  mnp2 \
  mp4demux \
  ngip \
  ngos \
  ngppp \
  pps \
  rld \
  rlu \
  sim \
  sim_cus\
  tel_cus\
  smg \
  sms \
  sn \
  ss \
  v42 \
  v42b \
  ps_cork\
  viddecoder \
  aacdec_codec \
  cookdec_codec \
  midi \
  mmaudio_common_release \
  mmaudio_getinfo \
  mmaudio_spectrum \
  mp3dec_codec \
  mp3enc_codec\
  mp3layer3enc_codec\
  sbcenc_codec\
  wavdec_codec \
  wavenc_codec \
  wmadec_codec \
  3dsurround\
  arp_exp_vol\
  arp_sw_agc\
  arp_hw_agc\
  mmaudio_common\
  peq\
  hw_geq\
  hw_peq\
  exp_vol\
  drc_limiter\
  drc_limiter_v2\
  drclookahead_limiter\
  hard_limiter\
  hw_drc\
  reverb\
  bass\
  sc_fade\
  time_stretch\
  timepitch_stretch\
  srs_wowhd

ifeq (TRUE, $(strip $(CHIP_TGGE_RF)))
LIB_ap_SET += \
  hwl_rf_tgge
else
LIB_ap_SET += \
  hwl_rf_aero2\
  hwl_rf_msr7100\
  hwl_rf_msr7120
endif


ifeq ($(filter ENABLE_AMRNB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_DEC)
LIB_ap_SET += amrnbdec_codec
endif

ifeq ($(filter ENABLE_AMRNB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_ENC)
LIB_ap_SET += amrnbenc_codec
endif

ifeq ($(filter ENABLE_AMRWB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_DEC)
LIB_ap_SET += amrwbdec_codec
endif

ifeq ($(filter ENABLE_AMRWB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_ENC)
LIB_ap_SET += amrwbenc_codec
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
LIB_ap_SET += g3d
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
LIB_ap_SET += gps
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
LIB_ap_SET += rfid
#endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
ifneq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)
LIB_ap_SET += $(PRODUCT_LIB_MMI_MGL)
endif
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for B3 G1
LIB_ap_SET +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
LIB_ap_SET +=\
	a2dp
endif
else
LIB_ap_SET +=\
	bt_host
endif
endif


#
# PRODUCT_ALL = all library group
#
PRODUCT_ALL=$(PRODUCT_SC) $(PRODUCT_LIB) \
	$(PRODUCT_SC_MDL) $(PRODUCT_LIB_MDL)  \
	$(PRODUCT_SC_DRV) $(PRODUCT_LIB_DRV)  \
	$(PRODUCT_SC_SYS) $(PRODUCT_LIB_SYS)  \
	$(PRODUCT_SC_MMI) $(PRODUCT_LIB_MMI)  \
	$(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD)

ifeq ($(RELEASE_PROCESS),1)
PRODUCT_ALL += $(PRODUCT_SC_CUS)
else
PRODUCT_ALL_STACK2 += $(PRODUCT_SC_STACK2) $(PRODUCT_LIB_STACK2)
endif

ifneq ($(call FIND_COMPILER_OPTION, __SLIM_RIL__), TRUE)
DUMMY_LIB_LIST += sril\
    sril_wrapper\
    sati_main\
    sati_cc\
    sati_cphs\
    sati_phb\
    sati_ps\
    sati_mm\
    sati_modem\
    sati_serial\
    sati_sim\
    sati_sms\
    sati_ss
else
DUMMY_LIB_LIST +=\
    ril_kernel\
	ril_cb\
	ril_cc\
	ril_cphs\
	ril_ps\
	ril_phb\
	ril_pwof\
	ril_rr\
	ril_sec\
	ril_stk\
	ril_ss\
	ril_sms\
	ril_sim\
	ril_msync\
	ati_main\
    ati_cc\
    ati_cphs\
    ati_phb\
    ati_ps\
    ati_mm\
    ati_modem\
    ati_serial\
    ati_sim\
    ati_sms\
    ati_ss
endif

ifneq ($(call FIND_COMPILER_OPTION, __MSYNC_TOOL__), TRUE)
DUMMY_LIB_LIST +=  sril_msync
else
ifneq ($(call FIND_COMPILER_OPTION, __SLIM_RIL__), TRUE)
DUMMY_LIB_LIST +=  sril_msync
endif
endif

#
# MST, MST is a special case, it contains all module except acc & keypad
#
LIB_ps_SET := $(PRODUCT_ALL)
LIB_ps_SET := $(filter-out acc keypad, $(LIB_ps_SET))

LIB_ps_SET = \
    3dsurround\
    NCCBrowser_target\
    NCCCommon_target\
    NCCCommon_wsp\
    NCCMms_target\
    a2dp\
    aacdec_codec\
    arm\
    arp_exp_vol\
    arp_hw_agc\
    arp_sw_agc\
    ati_cc\
    ati_cphs\
    ati_main\
    ati_mm\
    ati_modem\
    ati_phb\
    ati_ps\
    ati_serial\
    ati_sim\
    ati_sms\
    ati_ss\
    sati_main\
    sati_cc\
    sati_cphs\
    sati_phb\
    sati_ps\
    sati_mm\
    sati_modem\
    sati_serial\
    sati_sim\
    sati_sms\
    sati_ss\
    boot\
    bsp_737\
    bsp_833\
    bsp_837\
    bsp_838\
    bsp_8f4\
    bsp_c3c\
    bsp_mn\
    bt_host_acrux2\
    bt_mac_critical\
    bt_mac_normal\
    compression_mdl\
    cookdec_codec\
    demuxer\
    disk\
    drc_limiter\
    drc_limiter_v2\
    drclookahead_limiter\
    drm_util\
    dynldr\
    efat\
    exp_vol\
    fcie\
    fcm\
    hard_limiter\
    hw_drc\
    hw_geq\
    hw_peq\
    i18n\
    image_codec\
    midi\
    mmaudio_common\
    mmaudio_common_release\
    mmaudio_getinfo\
    mmaudio_spectrum\
    mmmanager_lib\
    mmplayer\
    mp3dec_codec\
    mp3enc_codec\
    mp3layer3enc_codec\
    mp4demux\
    peq\
    pps\
    reverb\
    bass\
    rtk\
    sbcenc_codec\
    sc_fade\
    sdio\
    sim\
    sim_cus\
    smg\
    sms\
    storage\
    supplicant_common\
    supplicant_crypto\
    supplicant_ctrl\
    sys\
    time_stretch\
    timepitch_stretch\
    trc\
    trc_cus\
    truetype\
    ucs2\
    utility\
    v24\
    vdr_mux\
    viddecoder\
    vml_ase\
    vml_cc\
    vml_cphs\
    vml_mm\
    vml_phb\
    vml_ps\
    vml_sim\
    vml_sms\
    vml_ss\
    vml_stlk\
    vml_util\
    wavdec_codec\
    wavenc_codec\
    wlan\
    wlan_drv\
    wlan_hal\
    wmadec_codec\
    zlib\

ifeq ($(filter ENABLE_AMRNB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_DEC)
LIB_ps_SET += amrnbdec_codec
endif

ifeq ($(filter ENABLE_AMRNB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRNB_ENC)
LIB_ps_SET += amrnbenc_codec
endif

ifeq ($(filter ENABLE_AMRWB_DEC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_DEC)
LIB_ps_SET += amrwbdec_codec
endif

ifeq ($(filter ENABLE_AMRWB_ENC ,$(PP_OPT_COMMON)),ENABLE_AMRWB_ENC)
LIB_ps_SET += amrwbenc_codec
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
LIB_ps_SET += NCCEmail_target
endif

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
LIB_ps_SET += fms_nand
else
LIB_ps_SET += fms_nor
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
LIB_ps_SET += g3d
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
LIB_ps_SET += gps
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
LIB_ps_SET += rfid
#endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
ifneq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)
LIB_ps_SET += $(PRODUCT_LIB_MMI_MGL)
endif
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for B3 G1
LIB_ps_SET +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
LIB_ps_SET +=\
	a2dp
endif
else
LIB_ps_SET +=\
	bt_host
endif
endif

#
# for ap/sys/ps it does not need libs in LIB_(ap/sys/ps)_SET
# so we need filter-out unnecessary libraries
#
ifeq ($(QUICK),ap)
PRODUCT_ALL:=$(filter-out $(LIB_ap_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_ap_SET),$(PRODUCT_ALL_STACK2))
endif
ifeq ($(QUICK),sys)
PRODUCT_ALL:=$(filter-out $(LIB_sys_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_sys_SET),$(PRODUCT_ALL_STACK2))
endif
ifeq ($(QUICK),ps)
PRODUCT_ALL:=$(filter-out $(LIB_ps_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_ps_SET),$(PRODUCT_ALL_STACK2))
endif

