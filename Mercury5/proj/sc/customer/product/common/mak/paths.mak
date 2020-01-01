


#-------------------------------------------------------------------------------
#
# scope: Specify path definition e.g.  PATH_sys = $(PATH_system)/sys
#
# WARNING: Do not add any path to this file
# WARNING: Do not add any path to this file
# WARNING: Do not add any path to this file
# WARNING: Do not add any path to this file
# WARNING: Do not add any path to this file
#
# WARNING: The following path should be placed to dedicated file !!!
#
#          e.g.  PATH_C += $(PATH_sys)/src
#                   --> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/inc
#                   --> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/pub
#                   --> it is public path, please add to 'paths_pub.mak'
#
#          e.g. path is telecom folder
#                   --> it is telecom path, please add to 'paths_tel.mak'
#
#-------------------------------------------------------------------------------



#-------------------------------------------------------------------------------
# root folder paths
#-------------------------------------------------------------------------------
PATH_lib_sdk       = $(TOP)libs/sdk_lib/
PATH_sc            = $(TOP)sc/
PATH_tools         = $(TOP)/../tools/
PATH_common        = $(PATH_sc)customer/product/common/
PATH_common_mak    = $(PATH_common)mak/
PATH_build         = $(TOP)build/
PATH_e2p           = $(PATH_common_mak)
PATH_e2p_stack     = $(PATH_common_mak)
PATH_e2p_app       = $(PATH_common_mak)
PATH_e2p_lib       = $(PATH_common_mak)
PATH_e2p_lib_mrl   = $(PATH_common_mak)
PATH_install       = $(PATH_common_mak)
PATH_link          = $(PATH_common_mak)
PATH_tmt           = $(PATH_common_mak)
PATH_e2p_pc	       = $(PATH_common_mak)
PATH_chk           = $(PATH_sc)system/CheckSize/
PATH_dlm           = $(PATH_sc)system/dlm/
PATH_dlm_entry     = $(PATH_dlm)dlm_entry/
PATH_dlm_entry_inc = $(PATH_dlm_entry)/inc/
PATH_dlm_entry_src = $(PATH_dlm_entry)/src/
PATH_dlm_entry_pub = $(PATH_dlm_entry)/pub/
PATH_dlm_kernel    = $(PATH_dlm)dlm_kernel/
PATH_pure_lib_lst  = $(BUILD)
PATH_product       = $(PATH_sc)customer/product/$(PRODUCT)/
PATH_product_mak   = $(PATH_product)mak/
PATH_product_cust  = $(PATH_product)cust/
PATH_system        = $(PATH_sc)system/
PATH_platform      = $(PATH_sc)platform/
PATH_driver        = $(PATH_sc)driver/
PATH_drv           = $(PATH_sc)driver/drv/
PATH_hal           = $(PATH_sc)driver/hal/$(BB_CHIP_ID)/
PATH_utopia        = $(PATH_sc)driver/utopia/
PATH_middleware    = $(PATH_sc)middleware/
PATH_application   = $(PATH_sc)application/
PATH_customer_default = $(PATH_sc)customer/default/src/
PATH_customer_product = $(PATH_sc)customer/default/
PATH_SocketMgr        = $(PATH_application)sys/ResMgr
PATH_Boot_bin         = $(TOP)/../IPL/
PATH_cam_os_wrapper = $(PATH_sc)system/cam_os_wrapper/

#-------------------------------------------------------------------------------
# customer folder paths
#-------------------------------------------------------------------------------
ifeq ($(filter __CUS_DEFAULT__, $(PP_OPT_COMMON)), __CUS_DEFAULT__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/default
endif
ifeq ($(filter __CUS_1__, $(PP_OPT_COMMON)), __CUS_1__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/cus1
endif
ifeq ($(filter __CUS_2__, $(PP_OPT_COMMON)), __CUS_2__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/cus2
endif
ifeq ($(filter __CUS_3__, $(PP_OPT_COMMON)), __CUS_3__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/cus3
endif
ifeq ($(filter __CUS_4__, $(PP_OPT_COMMON)), __CUS_4__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/cus4
endif
ifeq ($(filter __CUS_5__, $(PP_OPT_COMMON)), __CUS_5__)
PATH_customer_define_folder = $(PATH_sc)application/mmi/cus/cus5
endif
PATH_CusDefine         = $(PATH_customer_define_folder)
PATH_customer_product_backlight = $(PATH_sc)customer/product/cust/drv/backlight
PATH_customer_product_bootup = $(PATH_system)BootUp/
PATH_customer_product_hwconfig = $(PATH_system)BootUp/hwconfig/
PATH_customer_product_hwconfig_ramconfig = $(PATH_system)BootUp/hwconfig/$(RAMCLK)
PATH_customer_product_hwconfig_DBB = $(PATH_system)BootUp/hwconfig/DBB/
PATH_cust_drv_check  = $(PATH_product_cust_new_config)drv/
PATH_product_cust_new_config = $(PATH_sc)customer/product/cust/
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_cust_scatter = $(PATH_product_cust_new_config)scatter/
PATH_cust_fat  = $(PATH_product_cust_new_config)fat/
PATH_cust_drv  = $(PATH_product_cust_new_config)drv/
PATH_cust_drv_dummy  = $(PATH_product_cust_new_config)drv/
PATH_cust_sys  = $(PATH_product_cust_new_config)sys/
PATH_cust_mmi  = $(PATH_product_cust_new_config)mmi/
PATH_cust_nandprt = $(PATH_product_cust_new_config)nandprt/
PATH_feedback = $(PATH_product_cust_new_config)/feedback/
PATH_global_header_file = $(PATH_product_cust_new_config)/include/
PATH_customer_product_lcm = $(PATH_product_cust_new_config)drv/lcm/
PATH_customer_product_lcd = $(PATH_product_cust_new_config)drv/lcm/
ROOT_disptbl = $(PATH_sc)customer/product/cust
PATH_customer_product_sensor = $(PATH_sc)customer/product/cust/drv/sensor/$(SENSOR_CUS_PATH)/
else
PATH_cust_scatter = $(MAK)/
PATH_cust_fat  = $(PATH_product)fat/
PATH_cust_drv  = $(PATH_product_cust)drv/
PATH_customer_drv = $(PATH_common)drv
PATH_cust_drv_dummy  = $(PATH_product_cust)drv/
PATH_cust_sys  = $(PATH_product_cust)sys/
PATH_cust_mmi  = $(PATH_product_cust)mmi/
PATH_cust_nandprt = $(PATH_product)nandprt/
PATH_feedback = $(PATH_product)/feedback/
PATH_customer_product_lcm = $(PATH_product_cust)drv/src/lcd/
PATH_customer_product_lcd = $(PATH_common)drv/lcm/
ROOT_disptbl = $(PATH_common)
PATH_customer_product_sensor = $(PATH_common)/drv/sensor/$(SENSOR_CUS_PATH)/
endif
PATH_customer_product_disptbl = $(ROOT_disptbl)/drv/disptbl/$(Disptbl_IC_TYPE)/
PATH_nvram = $(PATH_product_cust_new_config)nvram/
PATH_transceiver = $(PATH_product_cust_new_config)stack/
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_e2p_product  = $(PATH_sc)customer/product/cust/e2p
else
PATH_e2p_product  = $(PATH_product)e2p
endif

# paths to e2p files
PATH_E2P = $(PATH_e2p_product) $(PATH_e2p_common)
PATH_e2p_common   = $(PATH_common)e2p
PATH_e2p_platform = $(PATH_platform)e2p
PATH_mmi_cus = $(PATH_mmi_res)/Customization
PATH_fat_wpb    = $(PATH_cust_fat)

#-------------------------------------------------------------------------------
# application folder paths
#-------------------------------------------------------------------------------
PATH_fat               = $(PATH_application)sys/fat
PATH_UnitTestApp       = $(PATH_sc)application/mmi/app/UnitTestApp
PATH_UnitTestSrv       = $(PATH_sc)application/mmi/srv/UnitTestSrv
PATH_cus_app           = $(PATH_application)cus_app/sc
PATH_cus_app_lib       = $(PATH_application)cus_app/lib
PATH_cus_app_sc        = $(PATH_application)cus_app/lib
PATH_3rd               = $(PATH_application)3rd
PATH_mae               = $(PATH_application)mmi/mae
PATH_mae_porting       = $(PATH_mae)/porting
PATH_mgl               = $(PATH_application)mmi/mgl
PATH_mgl_porting       = $(PATH_application)mmi/mgl
PATH_pgl               = $(PATH_application)mmi/pgl
PATH_app               = $(PATH_application)mmi/app
PATH_UnitTestApp       = $(PATH_app)/UnitTestApp
PATH_srv               = $(PATH_application)mmi/srv
PATH_core              = $(PATH_application)mmi/core
PATH_mmicomn           = $(PATH_application)mmi/common
PATH_widget            = $(PATH_application)mmi/widgets
PATH_widget_priv       = $(PATH_application)mmi/widgets
PATH_model             = $(PATH_application)mmi/models
PATH_mmi_res           = $(PATH_application)mmi/resource
PATH_viewtemplate      = $(PATH_application)mmi/viewtemplate
PATH_SrvWrapper        = $(PATH_application)mmi/SrvWrapper
PATH_AppLauncher       = $(PATH_application)mmi/AppLauncher
PATH_NCCMms_target     = $(PATH_application)mms
PATH_NCCMms_cus        = $(PATH_application)mms
PATH_NCCCommon_wsp     = $(PATH_application)wap
PATH_NCCCommon_cus     = $(PATH_application)wap
PATH_NCCBrowser_cus    = $(PATH_application)wap
PATH_NCCBrowser_target = $(PATH_application)wap
PATH_NCCCommon_target  = $(PATH_application)wap
PATH_NCCEmail_target   = $(PATH_application)email
PATH_cn                = $(PATH_application)sys/cn
PATH_ResMgr            = $(PATH_application)sys/ResMgr
PATH_FileMgr           = $(PATH_application)sys/file_mgr
PATH_truetype          = $(PATH_application)sys/truetype
PATH_hopper            = $(PATH_application)sys/hopper
PATH_sqlite            = $(PATH_application)sys/sqlite

PATH_AlarmApp           = $(PATH_app)/AlarmApp
PATH_AliveWidget        = $(PATH_app)/AliveWidget
PATH_AndroidIdleApp     = $(PATH_app)/AndroidIdleApp
PATH_AndroidKeyGuardApp = $(PATH_app)/AndroidKeyGuardApp
PATH_AndroidMainMenuApp = $(PATH_app)/AndroidMainMenuApp
PATH_AntiStealApp       = $(PATH_app)/AntiStealApp
PATH_AtvApp             = $(PATH_app)/AtvApp
PATH_AutotestApp        = $(PATH_app)/AutotestApp
PATH_AzanApp            = $(PATH_app)/AzanApp
PATH_BeautyClkSettingApp = $(PATH_app)/BeautyClkSettingApp
PATH_Big2               = $(PATH_app)/Big2
PATH_BjxApp             = $(PATH_app)/BjxApp
PATH_BmiApp             = $(PATH_app)/BmiApp
PATH_BtApp              = $(PATH_app)/BtApp
PATH_BtNotifyApp        = $(PATH_app)/BtNotifyApp
PATH_CalculatorApp      = $(PATH_app)/CalculatorApp
PATH_CalculatorPlusApp  = $(PATH_app)/CalculatorPlusApp
PATH_CalendarApp        = $(PATH_app)/CalendarApp
PATH_CalibrationApp     = $(PATH_app)/CalibrationApp
PATH_CallerLocationApp  = $(PATH_app)/CallerLocationApp
PATH_CallLogApp         = $(PATH_app)/CallLogApp
PATH_CallSettingApp     = $(PATH_app)/CallSettingApp
PATH_CamApp             = $(PATH_app)/CamApp
PATH_CbSettingApp       = $(PATH_app)/CbSettingApp
PATH_CcApp              = $(PATH_app)/CcApp
PATH_CcMtaApp           = $(PATH_app)/CcMtaApp
PATH_CdWapApp           = $(PATH_app)/CdWapApp
PATH_CheckDiskApp       = $(PATH_app)/CheckDiskApp
PATH_ConSettingApp      = $(PATH_app)/ConSettingApp
PATH_CountdownTimerApp  = $(PATH_app)/CountdownTimerApp
PATH_DesktopWidget      = $(PATH_app)/DesktopWidget
PATH_DialerApp          = $(PATH_app)/DialerApp
PATH_DialerGroupApp     = $(PATH_app)/DialerGroupApp
PATH_DialogApp          = $(PATH_app)/DialogApp
PATH_DictApp            = $(PATH_app)/DictApp
PATH_EbookApp           = $(PATH_app)/EbookApp
PATH_EmailApp           = $(PATH_app)/EmailApp
PATH_EmApp              = $(PATH_app)/EmApp
PATH_EmuApp             = $(PATH_app)/EmuApp
PATH_EvtCenterApp       = $(PATH_app)/EvtCenterApp
PATH_FavoritePhbApp     = $(PATH_app)/FavoritePhbApp
PATH_FdnApp             = $(PATH_app)/FdnApp
PATH_FileMgrApp         = $(PATH_app)/FileMgrApp
PATH_FishFuryGame       = $(PATH_app)/FishFuryGame
PATH_FmRadioApp         = $(PATH_app)/FmRadioApp
PATH_FmSchApp           = $(PATH_app)/FmSchApp
PATH_FruitGambleGame    = $(PATH_app)/FruitGambleGame
PATH_FruitSliceGame     = $(PATH_app)/FruitSliceGame
PATH_G3DMainMenuApp     = $(PATH_app)/G3DMainMenuApp
PATH_GoBangApp          = $(PATH_app)/GoBangApp
PATH_GogoBoxGame        = $(PATH_app)/GogoBoxGame
PATH_HamsterFightApp    = $(PATH_app)/HamsterFightApp
PATH_IdleApp            = $(PATH_app)/IdleApp
PATH_IdlePreviewApp     = $(PATH_app)/IdlePreviewApp
PATH_IplayCube          = $(PATH_app)/IplayCube
PATH_JavaAmsApp         = $(PATH_app)/JavaAmsApp
PATH_JavaFactoryApp     = $(PATH_app)/JavaFactoryApp
PATH_KeyGuardApp        = $(PATH_app)/KeyGuardApp
PATH_KingMovieApp       = $(PATH_app)/KingMovieApp
PATH_LabyrinthGame      = $(PATH_app)/LabyrinthGame
PATH_LicenseMgrApp      = $(PATH_app)/LicenseMgrApp
PATH_LinkUpApp          = $(PATH_app)/LinkUpApp
PATH_MainMenuApp        = $(PATH_app)/MainMenuApp
PATH_MessageCenterApp   = $(PATH_app)/MessageCenterApp
PATH_MessageEditorApp   = $(PATH_app)/MessageEditorApp
PATH_MessageTemplateApp = $(PATH_app)/MessageTemplateApp
PATH_MessageViewerApp   = $(PATH_app)/MessageViewerApp
PATH_MglDemoApp         = $(PATH_app)/MglDemoApp
PATH_MmsSettingApp      = $(PATH_app)/MmsSettingApp
PATH_MplayerApp         = $(PATH_app)/MplayerApp
PATH_NetworkApp         = $(PATH_app)/NetworkApp
PATH_NetworkCounterApp  = $(PATH_app)/NetworkCounterApp
PATH_NotepadApp         = $(PATH_app)/NotepadApp
PATH_OffApp             = $(PATH_app)/OffApp
PATH_OnApp              = $(PATH_app)/OnApp
PATH_PacMan             = $(PATH_app)/PacMan
PATH_PhbApp             = $(PATH_app)/PhbApp
PATH_PicPreviewApp      = $(PATH_app)/PicPreviewApp
PATH_PicViewerApp       = $(PATH_app)/PicViewerApp
PATH_PrivateprotectApp  = $(PATH_app)/PrivateprotectApp
PATH_ProfileApp         = $(PATH_app)/ProfileApp
PATH_PuzzleApp          = $(PATH_app)/PuzzleApp
PATH_QQApp              = $(PATH_app)/QQApp
PATH_RemoteControlApp   = $(PATH_app)/RemoteControlApp
PATH_RubiksCube         = $(PATH_app)/RubiksCube
PATH_ScreensaverApp     = $(PATH_app)/ScreensaverApp
PATH_SearchApp          = $(PATH_app)/SearchApp
PATH_SecApp             = $(PATH_app)/SecApp
PATH_SendViaApp         = $(PATH_app)/SendViaApp
PATH_SettingApp         = $(PATH_app)/SettingApp
PATH_ShortcutPhbApp     = $(PATH_app)/ShortcutPhbApp
PATH_ShortcutsApp       = $(PATH_app)/ShortcutsApp
PATH_SmsSettingApp      = $(PATH_app)/SmsSettingApp
PATH_SnoteApp           = $(PATH_app)/SnoteApp
PATH_SoHuUpdaterApp     = $(PATH_app)/SoHuUpdaterApp
PATH_SokobanApp         = $(PATH_app)/SokobanApp
PATH_StkApp             = $(PATH_app)/StkApp
PATH_StopwatchApp       = $(PATH_app)/StopwatchApp
PATH_SudokuApp          = $(PATH_app)/SudokuApp
PATH_TestApp            = $(PATH_app)/TestApp
PATH_ToDoListApp        = $(PATH_app)/ToDoListApp
PATH_UnitConverterApp   = $(PATH_app)/UnitConverterApp
PATH_UsbApp             = $(PATH_app)/UsbApp
PATH_UssdApp            = $(PATH_app)/UssdApp
PATH_VendorApp          = $(PATH_app)/VendorApp
PATH_VideoPlayerApp     = $(PATH_app)/VideoPlayerApp
PATH_VideoTelephonyApp  = $(PATH_app)/VideoTelephonyApp
PATH_VoiceMailApp       = $(PATH_app)/VoiceMailApp
PATH_VoiceMemoApp       = $(PATH_app)/VoiceMemoApp
PATH_WdgDemoApp         = $(PATH_app)/WdgDemoApp
PATH_WiFiApp            = $(PATH_app)/WiFiApp
PATH_WorldClockApp      = $(PATH_app)/WorldClockApp
PATH_RfidApp            = $(PATH_app)/RfidApp
PATH_TuDouApp           = $(PATH_app)/TuDouApp
PATH_VampireGame        = $(PATH_app)/VampireGame
PATH_ZombieGame         = $(PATH_app)/ZombieGame
PATH_NtpApp             = $(PATH_app)/NtpApp

#-------------------------------------------------------------------------------
# drv/hal folder paths
#-------------------------------------------------------------------------------
PATH_utopia_msos    = $(PATH_utopia)msos
PATH_utopia_chip    = $(PATH_utopia)chip
PATH_utopia_common  = $(PATH_utopia)common
PATH_utopia_vdec    = $(PATH_utopia)vdec
PATH_storage        = $(PATH_drv)storage
PATH_fcie           = $(PATH_hal)fcie
PATH_sdio           = $(PATH_hal)sdio
PATH_bus            = $(PATH_drv)bus
PATH_bus_hal        = $(PATH_hal)bus
PATH_emi            = $(PATH_drv)emi
PATH_emi_hal        = $(PATH_hal)emi
PATH_flash          = $(PATH_drv)flash
PATH_flash_hal      = $(PATH_hal)flash
PATH_adc            = $(PATH_drv)adc
PATH_adc_hal        = $(PATH_hal)adc
PATH_int            = $(PATH_drv)int
PATH_int_hal        = $(PATH_hal)int
PATH_io             = $(PATH_drv)io
PATH_io_hal         = $(PATH_hal)io
PATH_rtc            = $(PATH_drv)rtc
PATH_rtc_hal        = $(PATH_hal)rtc
PATH_disp           = $(PATH_drv)disp
PATH_disp_hal       = $(PATH_hal)disp
PATH_keypad         = $(PATH_drv)keypad
PATH_keypad_hal     = $(PATH_hal)keypad
PATH_pll_hal        = $(PATH_hal)pll
PATH_tscr           = $(PATH_drv)tscr
PATH_tscr_hal       = $(PATH_hal)tscr
PATH_fmrx           = $(PATH_drv)fmrx
PATH_fmrx_hal       = $(PATH_hal)fmrx
PATH_dma            = $(PATH_drv)dma
PATH_dma_hal        = $(PATH_hal)dma
PATH_gpd            = $(PATH_drv)gpd
PATH_gpd_drv        = $(PATH_drv)/gpd
PATH_gpd_hal        = $(PATH_hal)gpd
PATH_gsensor        = $(PATH_drv)/gsensor
PATH_proximitysensor= $(PATH_drv)/proximitysensor
PATH_proximitysensor_hal= $(PATH_hal)/proximitysensor
PATH_backlight      = $(PATH_drv)/backlight
PATH_power          = $(PATH_drv)power
PATH_clkgen         = $(PATH_drv)clkgen
PATH_clkgen_hal     = $(PATH_hal)clkgen
PATH_timer          = $(PATH_drv)timer
PATH_timer_hal      = $(PATH_hal)timer
PATH_kernel_hal     = $(PATH_hal)kernel
PATH_batt_hal       = $(PATH_hal)batt
PATH_battery        = $(PATH_drv)battery
PATH_audio_drv      = $(PATH_drv)audio
PATH_audio_hal      = $(PATH_hal)audio
PATH_zlib_drv       = $(PATH_drv)zlib
PATH_zlib_hal       = $(PATH_hal)zlib
PATH_dynscl         = $(PATH_drv)dynscl
PATH_dynscl_hal     = $(PATH_hal)dynscl
PATH_pm             = $(PATH_drv)pm
PATH_pm_hal         = $(PATH_hal)pm
PATH_drvutil_hal    = $(PATH_hal)drvutil
PATH_drvtable_hal   = $(PATH_hal)drvtable
PATH_usb            = $(PATH_drv)/usb
PATH_usb_hal        = $(PATH_hal)/usb
PATH_usbhost        = $(PATH_drv)/usbhost
PATH_usbhost_hal    = $(PATH_hal)/usbhost
PATH_otg            = $(PATH_drv)/otg
PATH_pmu            = $(PATH_hal)/pmu
PATH_misc           = $(PATH_drv)/misc
PATH_lcd            = $(PATH_drv)/lcd
PATH_lcd_hal        = $(PATH_hal)lcd
PATH_uart           = $(PATH_drv)/uart
PATH_uart_hal       = $(PATH_hal)/uart
PATH_boot           = $(PATH_hal)/boot
PATH_sim_mux_switch = $(PATH_drv)/sim_mux_switch
PATH_adcdump        = $(PATH_drv)/adcdump
PATH_adcdump_hal    = $(PATH_hal)adcdump
PATH_acc            = $(PATH_customer_default)drv/acc
PATH_acc_inc        = $(PATH_drv)/acc
PATH_bluetooth      = $(PATH_drv)bluetooth
PATH_bt_host        = $(PATH_bluetooth)/bt_host
PATH_bt_host_acrux2 = $(PATH_bluetooth)/bt_host
PATH_a2dp           = $(PATH_bluetooth)/bt_host
PATH_bt_mac         = $(PATH_bluetooth)/bt_mac
PATH_bt_mac_normal  = $(PATH_bt_mac)
PATH_bt_mac_critical= $(PATH_bt_mac)
PATH_scl            = $(PATH_drv)/scl
PATH_scl_hal        = $(PATH_hal)scl
PATH_csi            = $(PATH_drv)/csi
PATH_csi_hal        = $(PATH_hal)csi
PATH_vif            = $(PATH_drv)/vif
PATH_vif_hal        = $(PATH_hal)vif
PATH_sensorif       = $(PATH_drv)/sensorif
PATH_sensorif_hal   = $(PATH_hal)sensorif
PATH_sensordriver   = $(PATH_drv)/sensordriver
PATH_dma2d          = $(PATH_drv)/dma2d
PATH_disk           = $(PATH_drv)/disk
PATH_disk_storage   = $(PATH_drv)/disk
PATH_jpd            = $(PATH_drv)/jpd
PATH_jpd_hal        = $(PATH_hal)jpd
PATH_jpe            = $(PATH_drv)/jpe
PATH_jpe_hal        = $(PATH_hal)jpe
PATH_unfd           = $(PATH_drv)/unfd
PATH_unfd_hal       = $(PATH_hal)/unfd
PATH_g3d            = $(PATH_drv)/g3d
PATH_pmu_hal        = $(PATH_hal)/pmu
PATH_dma2d_hal      = $(PATH_hal)dma2d
PATH_etmi           = $(PATH_drv)/etmi
PATH_etmi_hal       = $(PATH_hal)etmi
PATH_mfd            = $(PATH_drv)/mfd
PATH_mfd_hal        = $(PATH_hal)mfd
PATH_mbas           = $(PATH_drv)/mbas
PATH_mbas_hal       = $(PATH_hal)/mbas
PATH_misc_hal       = $(PATH_hal)/misc
PATH_hwconfig       = $(PATH_drv)/hwconfig
PATH_hwconfig_hal   = $(PATH_hal)/hwconfig
PATH_g3d_hal        = $(PATH_hal)/g3d
PATH_nvram_drv      = $(PATH_drv)/nvram_drv
PATH_wlan_drv       = $(PATH_drv)/wlan
PATH_wlan_hal       = $(PATH_hal)/wlan
PATH_dsr            = $(PATH_drv)/dsr
PATH_rompatch_hal   = $(PATH_hal)/rompatch
PATH_gdma_hal       = $(PATH_hal)gdma
PATH_glue           = $(PATH_drv)/glue
PATH_bdma           = $(PATH_drv)bdma
PATH_bdma_hal       = $(PATH_hal)bdma
PATH_dmagen         = $(PATH_drv)dmagen
PATH_dmagen_hal     = $(PATH_hal)dmagen
PATH_isp            = $(PATH_drv)isp
PATH_isp_hal        = $(PATH_hal)isp
PATH_mfe            = $(PATH_drv)mfe
PATH_mfe_hal        = $(PATH_hal)mfe
PATH_mz             = $(PATH_drv)mz
PATH_mhve           = $(PATH_drv)mhve
PATH_hvd            = $(PATH_drv)hvd
PATH_hvd_hal        = $(PATH_hal)hvd
PATH_vpu_hal        = $(PATH_hal)vpu
PATH_scalar_c3_hal  =$(PATH_hal)scalar
PATH_scalar_c3      =$(PATH_drv)scalar
PATH_scalar_c3_mvop_hal = $(PATH_hal)scalar/mvop
PATH_scalar_c3_mvop = $(PATH_drv)scalar/mvop
PATH_dip            = $(PATH_drv)dip
PATH_dip_hal        = $(PATH_hal)dip
PATH_Pnl            = $(PATH_drv)/pnl
PATH_Pnl_hal        = $(PATH_hal)/pnl
PATH_gop            = $(PATH_drv)gop
PATH_gop_hal        = $(PATH_hal)gop
PATH_dec_scl        = $(PATH_drv)/dec_scl
PATH_dec_scl_hal    = $(PATH_hal)dec_scl
PATH_mipi_dsi       = $(PATH_drv)/mipi_dsi
PATH_mipi_dsi_hal   = $(PATH_hal)mipi_dsi
PATH_mmio           = $(PATH_drv)mmio
PATH_mmio_hal       = $(PATH_hal)mmio
PATH_ipauth         = $(PATH_drv)/ipauth
PATH_sys_drv        = $(PATH_drv)/sys
PATH_sys_hal        = $(PATH_hal)/sys
PATH_spinand        = $(PATH_drv)spinand
PATH_spinand_hal    = $(PATH_hal)spinand
PATH_ms_sdmmc       = $(PATH_drv)sdmmc
PATH_efuse          = $(PATH_drv)/efuse
PATH_pm_chip        = $(PATH_drv)/pm_chip

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_ofn            = $(PATH_drv)/ofn
PATH_ofn_hal        = $(PATH_hal)/ofn
endif
ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PATH_ball           = $(PATH_drv)/ball
PATH_ball_hal       = $(PATH_hal)/ball
endif

PATH_shmcl          = $(PATH_hal)/shmcl
PATH_shmcl_mmp      = $(PATH_hal)/shmcl_mmp

# it is for G1, this atv chip definition should be placed before other atv path definition

ifneq (,$(strip $(ATV_CHIP)))
PATH_atv      = $(PATH_drv)/atv/$(strip $(ATV_CHIP))
PATH_atv_util = $(PATH_drv)/atv
PATH_atv_pub  = $(PATH_drv)/atv/pub
endif

ifeq ($(filter __ATV_DRV_TLG1120__ ,$(PP_OPT_COMMON)),__ATV_DRV_TLG1120__)
PATH_atv            = $(PATH_drv)/atv/tlg1120
endif
ifeq ($(filter __ATV_DRV_TLG1123__ ,$(PP_OPT_COMMON)),__ATV_DRV_TLG1123__)
PATH_atv            = $(PATH_drv)/atv/tlg1123
endif
ifeq ($(call FIND_COMPILER_OPTION ,__ATV_DRV_ALPHA__),TRUE)
PATH_atv            = $(PATH_drv)/atv/alpha
endif
ifeq ($(call FIND_COMPILER_OPTION ,__ATV_DRV_NMI600__),TRUE)
PATH_atv            = $(PATH_drv)/atv/NMI600
endif
ifeq ($(call FIND_COMPILER_OPTION ,__ATV_DRV_RDA5888__),TRUE)
PATH_atv            = $(PATH_drv)/atv/rda5888
endif
ifeq ($(call FIND_COMPILER_OPTION ,__ATV_DRV_RDA5888E__),TRUE)
PATH_atv            = $(PATH_drv)/atv/rda5888e
endif
ifeq ($(call FIND_COMPILER_OPTION ,__ATV_DRV_MSB1303__),TRUE)
PATH_atv            = $(PATH_drv)/atv/msb1303
endif

ifeq ($(call FIND_COMPILER_OPTION, __MPIF_HAL__), TRUE)
PATH_mpif           = $(PATH_drv)/mpif
PATH_mpif_hal       = $(PATH_hal)/mpif
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PATH_gps            = $(PATH_drv)/gps
endif

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
PATH_rfid = $(PATH_drv)/rfid
#endif

# for I SW
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
PATH_dsp_isw = $(PATH_drv)/dsp_isw
PATH_sharedif = $(PATH_drv)/sharedif
endif

#-------------------------------------------------------------------------------
# system folder paths
#-------------------------------------------------------------------------------
PATH_arm            = $(PATH_system)arch/arm
PATH_r2             = $(PATH_system)arch/r2
PATH_rtk            = $(PATH_system)rtk
PATH_rtk_cus        = $(PATH_system)rtk
PATH_libc           = $(PATH_system)libc
PATH_fc             = $(PATH_system)fc
PATH_fcm            = $(PATH_system)fcm
PATH_opec           = $(PATH_system)opec
PATH_dynldr         = $(PATH_system)dynldr
PATH_dynldr_cus     = $(PATH_system)dynldr
PATH_sys            = $(PATH_system)sys
PATH_sys_cus        = $(PATH_system)sys
PATH_r2dummy        = $(PATH_system)sys
PATH_trc            = $(PATH_system)trc
PATH_trc_cus        = $(PATH_system)trc
PATH_v24            = $(PATH_system)v24
PATH_v24_cus        = $(PATH_system)v24
PATH_mux            = $(PATH_system)mux
PATH_time           = $(PATH_system)time
PATH_MsWrapper      = $(PATH_system)MsWrapper
PATH_ucs2           = $(PATH_system)ucs2
PATH_bsp_837        = $(PATH_system)bsp
PATH_bsp_8f4        = $(PATH_system)bsp
PATH_bsp_833        = $(PATH_system)bsp
PATH_bsp_737        = $(PATH_system)bsp
PATH_bsp_838        = $(PATH_system)bsp
PATH_bsp_c0f        = $(PATH_system)bsp
PATH_bsp_c3c        = $(PATH_system)bsp
PATH_bsp_6k3        = $(PATH_system)bsp
PATH_bsp_mn         = $(PATH_system)bsp
PATH_sddl           = $(PATH_system)sddl
# for I SW
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
PATH_bsp            = $(PATH_system)bsp
PATH_I_SW_Other     = $(PATH_system)sys
PATH_sys_I_SW       = $(PATH_system)sys
endif
PATH_cam_os_wrapper = $(PATH_system)/cam_os_wrapper

#-------------------------------------------------------------------------------
# middleware folder paths
#-------------------------------------------------------------------------------
PATH_audio_mdl             = $(PATH_middleware)audio
PATH_storage_mdl           = $(PATH_middleware)storage
PATH_signature             = $(PATH_middleware)sig
PATH_mtmgr                 = $(PATH_middleware)/mtmgr
PATH_rai                   = $(PATH_middleware)rai
PATH_obex                  = $(PATH_middleware)obex
PATH_gss                   = $(PATH_middleware)gss
PATH_audio                 = $(PATH_middleware)audio
PATH_usb_mdl               = $(PATH_middleware)usb
PATH_batt                  = $(PATH_middleware)batt
PATH_fms                   = $(PATH_middleware)fms
PATH_fms_cus               = $(PATH_middleware)fms
PATH_fms_nand              = $(PATH_middleware)fms
PATH_fms_nor               = $(PATH_middleware)fms
PATH_efat                  = $(PATH_middleware)efat
PATH_efat_cust             = $(PATH_middleware)efat
PATH_hostuvc_mdl           = $(PATH_middleware)hostuvc
PATH_tscr_mdl              = $(PATH_middleware)tscr
PATH_tscr_mdl_slim         = $(PATH_middleware)tscr
PATH_gpd_mdl               = $(PATH_middleware)gpd
PATH_mmaudio               = $(PATH_middleware)mmaudio
PATH_mmaudio_codec         = $(PATH_middleware)mmaudio
PATH_mmaudio_common        = $(PATH_mmaudio)/mmaudio_mak
PATH_mmaudio_common_release= $(PATH_mmaudio)/mmaudio_mak
PATH_mmaudio_getinfo       = $(PATH_mmaudio)/mmaudio_mak
PATH_midi                  = $(PATH_mmaudio)/mmaudio_mak
PATH_mp3dec_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_aacdec_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_amrnbdec_codec        = $(PATH_mmaudio)/mmaudio_mak
PATH_amrnbenc_codec        = $(PATH_mmaudio)/mmaudio_mak
PATH_amrwbdec_codec        = $(PATH_mmaudio)/mmaudio_mak
PATH_amrwbenc_codec        = $(PATH_mmaudio)/mmaudio_mak
PATH_wmadec_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_cookdec_codec         = $(PATH_mmaudio)/mmaudio_mak
PATH_mp3enc_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_mp3layer3enc_codec	   = $(PATH_mmaudio)/mmaudio_mak
PATH_sbcenc_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_wavenc_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_wavdec_codec          = $(PATH_mmaudio)/mmaudio_mak
PATH_mmaudio_spectrum      = $(PATH_mmaudio)/mmaudio_mak
PATH_aec_proc              = $(PATH_mmaudio)/mmaudio_mak
PATH_ns_proc               = $(PATH_mmaudio)/mmaudio_mak
PATH_app_engine            = $(PATH_mmaudio)/app_engine
PATH_3dsurround            = $(PATH_app_engine)/app_make
PATH_peq                   = $(PATH_app_engine)/app_make
PATH_hw_geq                = $(PATH_app_engine)/app_make
PATH_hw_peq                = $(PATH_app_engine)/app_make
PATH_exp_vol               = $(PATH_app_engine)/app_make
PATH_bass                  = $(PATH_app_engine)/app_make
PATH_drc_limiter           = $(PATH_app_engine)/app_make
PATH_drc_limiter_v2        = $(PATH_app_engine)/app_make
PATH_drclookahead_limiter  = $(PATH_app_engine)/app_make
PATH_hard_limiter          = $(PATH_app_engine)/app_make
PATH_hw_drc                = $(PATH_app_engine)/app_make
PATH_sc_fade               = $(PATH_app_engine)/app_make
PATH_srs_wowhd             = $(PATH_app_engine)/app_make
PATH_time_stretch          = $(PATH_app_engine)/app_make
PATH_timepitch_stretch     = $(PATH_app_engine)/app_make
PATH_reverb                = $(PATH_app_engine)/app_make
PATH_app_mgr               = $(PATH_app_engine)/app_make
PATH_app_mgr_shell         = $(PATH_app_engine)/app_make
PATH_arp_engine            = $(PATH_mmaudio)/arp_engine
PATH_arp_exp_vol           = $(PATH_arp_engine)/arp_make
PATH_arp_sw_agc            = $(PATH_arp_engine)/arp_make
PATH_arp_hw_agc            = $(PATH_arp_engine)/arp_make
PATH_arp_mgr               = $(PATH_arp_engine)/arp_make
PATH_arp_mgr_shell         = $(PATH_arp_engine)/arp_make
PATH_keypad_mdl            = $(PATH_middleware)keypad
PATH_pm_mdl                = $(PATH_middleware)pm
PATH_venc                  = $(PATH_middleware)venc
PATH_venc_src              = $(PATH_middleware)venc/src
PATH_venc_pub              = $(PATH_middleware)venc/pub
PATH_vdr                   = $(PATH_middleware)vdr
PATH_vdr_mux               = $(PATH_middleware)vdr
PATH_vdr_top               = $(PATH_middleware)vdr
PATH_vt_mm                 = $(PATH_middleware)/vt/vt_mm
PATH_vt_task               = $(PATH_middleware)vt/vt_task
PATH_image_capture         = $(PATH_middleware)image_capture
PATH_eml_dlm               = $(PATH_middleware)eml_dlm
PATH_ut_mdl                = $(PATH_middleware)ut_mdl
PATH_cpu_mdl               = $(PATH_middleware)cpu
PATH_mmp_common            = $(PATH_middleware)/avp/mmp_common/build/arm
PATH_mmplayer              = $(PATH_middleware)/avp/mmplayer/build/arm
PATH_mmplayer_s32          = $(PATH_middleware)/avp/mmplayer/build/arm
PATH_demuxer               = $(PATH_middleware)/avp/demuxer/build
PATH_mp4demux              = $(PATH_middleware)/avp/mp4demux/build/arm
PATH_mp4demux_s32          = $(PATH_middleware)/avp/mp4demux/build/arm
PATH_viddecoder	           = $(PATH_middleware)/avp/viddecoder/build
PATH_viddecoder_s32        = $(PATH_middleware)/avp/viddecoder/build
PATH_ema                   = $(PATH_middleware)/ema
PATH_esl                   = $(PATH_middleware)/esl
PATH_msmdrv                = $(PATH_middleware)/ema/msmdrv
PATH_vfs                   = $(PATH_middleware)/vfs
PATH_drm_vfs               = $(PATH_middleware)/drm_vfs
PATH_drm_util              = $(PATH_middleware)/drm_util
PATH_image_codec           = $(PATH_middleware)/image_codec
PATH_image_codec_32        = $(PATH_middleware)/image_codec
PATH_image_config          = $(PATH_middleware)/image_codec
PATH_stereo_video          = $(PATH_middleware)/stereo/stereo_video
PATH_stereo_image          = $(PATH_middleware)/stereo/stereo_image
PATH_stereo_image_main     = $(PATH_middleware)/stereo/stereo_image
PATH_camera_mdl            = $(PATH_middleware)/camera
PATH_camera_top            = $(PATH_middleware)/camera
PATH_camera_ip             = $(PATH_middleware)/camera
PATH_mmmanager             = $(PATH_middleware)/mmmanager
PATH_mmmanager_lib         = $(PATH_middleware)/mmmanager
PATH_abb_mdl               = $(PATH_middleware)/abb
PATH_compression_mdl       = $(PATH_middleware)/compression
PATH_efat_wrapper          = $(PATH_middleware)/efat
ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_ofn_mdl               = $(PATH_middleware)/ofn
endif
ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PATH_ball_mdl              = $(PATH_middleware)/ball
endif
PATH_avp                   = $(PATH_middleware)/avp
ifeq ($(call FIND_COMPILER_OPTION,__GPS_DUALSTAR_DRV__),TRUE)
PATH_gps_mdl               = $(PATH_middleware)/gps
endif
ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_tv_mdl                = $(PATH_middleware)/tv
endif
PATH_wlan_cus              = $(PATH_middleware)/wlan
PATH_supplicant_cus        = $(PATH_middleware)/supplicant
PATH_wlan                  = $(PATH_middleware)/wlan
PATH_supplicant            = $(PATH_middleware)/supplicant
PATH_supplicant_ctrl       = $(PATH_middleware)/supplicant
PATH_supplicant_crypto     = $(PATH_middleware)/supplicant
PATH_supplicant_common     = $(PATH_middleware)/supplicant

#ifeq ($(filter __RFID__ ,$(PP_OPT_COMMON)), __RFID__)
PATH_rfid_mdl = $(PATH_middleware)/rfid
#endif

# for I SW
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
PATH_isl                    = $(PATH_middleware)/isl
PATH_voc                    = $(PATH_middleware)/voc
PATH_image_capture_i_sw     = $(PATH_middleware)/image_capture
PATH_camera                 = $(PATH_middleware)/camera
PATH_vdr_i_sw               = $(PATH_middleware)/vdr
endif

PATH_isp_mdl                = $(PATH_middleware)/isp


#-------------------------------------------------------------------------------
# Mercury paths
#-------------------------------------------------------------------------------

PATH_ahc                        	= $(PATH_sc)ahc
PATH_ap6181                        	= $(PATH_sc)ap6181
PATH_core_application               = $(PATH_sc)core/application
PATH_core_application_mmps          = $(PATH_core_application)/mmps
PATH_core_application_mmps_adas     = $(PATH_core_application)/mmps/adas
PATH_core_application_mmps_audio    = $(PATH_core_application)/mmps/audio
PATH_core_application_mmps_display  = $(PATH_core_application)/mmps/display
PATH_core_application_mmps_dsc      = $(PATH_core_application)/mmps/dsc
PATH_core_application_mmps_fs       = $(PATH_core_application)/mmps/fs
PATH_core_application_mmps_sensor   = $(PATH_core_application)/mmps/sensor
PATH_core_application_mmps_storage  = $(PATH_core_application)/mmps/storage
PATH_core_application_mmps_system   = $(PATH_core_application)/mmps/system
PATH_core_application_mmps_usb      = $(PATH_core_application)/mmps/usb
PATH_core_application_mmps_vid_play = $(PATH_core_application)/mmps/vid_play
PATH_core_application_mmps_vid_recd = $(PATH_core_application)/mmps/vid_recd
PATH_core_application_mmpd          = $(PATH_core_application)/mmpd
PATH_core_application_mmpd_adas     = $(PATH_core_application)/mmpd/adas
PATH_core_application_mmpd_audio    = $(PATH_core_application)/mmpd/audio
PATH_core_application_mmpd_display  = $(PATH_core_application)/mmpd/display
PATH_core_application_mmpd_dsc      = $(PATH_core_application)/mmpd/dsc
PATH_core_application_mmpd_flow_ctl = $(PATH_core_application)/mmpd/flow_ctl
PATH_core_application_mmpd_fs       = $(PATH_core_application)/mmpd/fs
PATH_core_application_mmpd_img_pipe = $(PATH_core_application)/mmpd/img_pipe
PATH_core_application_mmpd_sensor   = $(PATH_core_application)/mmpd/sensor
PATH_core_application_mmpd_storage  = $(PATH_core_application)/mmpd/storage
PATH_core_application_mmpd_system   = $(PATH_core_application)/mmpd/system
PATH_core_application_mmpd_usb      = $(PATH_core_application)/mmpd/usb
PATH_core_application_mmpd_vid_play = $(PATH_core_application)/mmpd/vid_play
PATH_core_application_mmpd_vid_recd = $(PATH_core_application)/mmpd/vid_recd
PATH_core_application_mmph          = $(PATH_core_application)/mmph
PATH_core_application_component     = $(PATH_core_application)/component

PATH_core_driver                = $(PATH_sc)core/driver
PATH_core_driver_adc            = $(PATH_core_driver)/adc
PATH_core_driver_audio          = $(PATH_core_driver)/audio
PATH_core_driver_bsp            = $(PATH_core_driver)/bsp
PATH_core_driver_ccir           = $(PATH_core_driver)/ccir
PATH_core_driver_common         = $(PATH_core_driver)/common
PATH_core_driver_cpu_comm       = $(PATH_core_driver)/cpu_comm
PATH_core_driver_display        = $(PATH_core_driver)/display
PATH_core_driver_dma            = $(PATH_core_driver)/dma
PATH_core_driver_dram           = $(PATH_core_driver)/dram
PATH_core_driver_gpio           = $(PATH_core_driver)/gpio
PATH_core_driver_i2cm           = $(PATH_core_driver)/i2cm
PATH_core_driver_img_pipe       = $(PATH_core_driver)/img_pipe
PATH_core_driver_irda           = $(PATH_core_driver)/irda
PATH_core_driver_jpeg           = $(PATH_core_driver)/jpeg
PATH_core_driver_misc           = $(PATH_core_driver)/misc
PATH_core_driver_pll            = $(PATH_core_driver)/pll
PATH_core_driver_pwm            = $(PATH_core_driver)/pwm
PATH_core_driver_rtc            = $(PATH_core_driver)/rtc
PATH_core_driver_spi            = $(PATH_core_driver)/spi
PATH_core_driver_storage        = $(PATH_core_driver)/storage
PATH_core_driver_timer          = $(PATH_core_driver)/timer
PATH_core_driver_uart           = $(PATH_core_driver)/uart
PATH_core_driver_usb            = $(PATH_core_driver)/usb/
PATH_core_driver_wd             = $(PATH_core_driver)/wd
PATH_core_driver_dip            = $(PATH_core_driver)/dip

PATH_core_include               = $(PATH_sc)core/include
PATH_core_include_application   = $(PATH_core_include)/application
PATH_core_include_display       = $(PATH_core_include)/display
PATH_core_include_img_pipe      = $(PATH_core_include)/img_pipe
PATH_core_include_misc          = $(PATH_core_include)/misc
PATH_core_include_usb           = $(PATH_core_include)/usb

PATH_core_lib                   = $(PATH_sc)core/lib
PATH_core_lib_algorithm         = $(PATH_core_lib)/algorithm
PATH_core_lib_algorithm_adas    = $(PATH_core_lib_algorithm)/adas
PATH_core_lib_algorithm_mdtc    = $(PATH_core_lib_algorithm)/mdtc
PATH_core_lib_audio             = $(PATH_core_lib)/audio
PATH_core_lib_audio_aac_enc     = $(PATH_core_lib_audio)/aac_enc
PATH_core_lib_audio_aacplus_dec = $(PATH_core_lib_audio)/aacplus_dec
PATH_core_lib_audio_adpcm       = $(PATH_core_lib_audio)/adpcm
PATH_core_lib_audio_adpcm_common= $(PATH_core_lib_audio_adpcm)/common
PATH_core_lib_audio_drc         = $(PATH_core_lib_audio)/drc
PATH_core_lib_audio_eq			= $(PATH_core_lib_audio)/eq
PATH_core_lib_audio_eq_new		= $(PATH_core_lib_audio)/eq_new
PATH_core_lib_audio_mp3_enc     = $(PATH_core_lib_audio)/mp3_enc
PATH_core_lib_audio_mp3_dec     = $(PATH_core_lib_audio)/mp3_dec
PATH_core_lib_audio_amr_dec     = $(PATH_core_lib_audio)/amr_codec
PATH_core_lib_audio_mp12_dec    = $(PATH_core_lib_audio)/mp12_dec
PATH_core_lib_video_avc_dec     = $(PATH_core_lib)/video/avc_dec
PATH_core_lib_video_rc          = $(PATH_core_lib)/video/rc
PATH_core_lib_fs                = $(PATH_core_lib)/fs
PATH_core_lib_gui               = $(PATH_core_lib)/gui
PATH_core_lib_edog              = $(PATH_core_lib)/edog
#naming violation!
PATH_core_lib_gui_inc_Core      = $(PATH_core_lib_gui)/inc/Core
PATH_core_lib_gui_inc_Config    = $(PATH_core_lib_gui)/inc/Config

PATH_core_lib_isp               = $(PATH_core_lib)/isp
PATH_core_lib_video_avc_dec     = $(PATH_core_lib)/video/avc_dec
PATH_core_lib_video_rc          = $(PATH_core_lib)/video/rc

PATH_core_system                = $(PATH_sc)core/system
PATH_core_system_algorithm      = $(PATH_core_system)/algorithm
PATH_core_system_audio          = $(PATH_core_system)/audio
PATH_core_system_audio_agc      = $(PATH_core_system)/audio/agc
PATH_core_system_audio_codec    = $(PATH_core_system)/audio/codec
PATH_core_system_audio_codec_pcm_enc        = $(PATH_core_system)/audio/codec/pcm_enc
PATH_core_system_audio_codec_aac_enc        = $(PATH_core_system)/audio/codec/aac_enc
PATH_core_system_audio_codec_aacplus_dec    = $(PATH_core_system)/audio/codec/aacplus_dec
PATH_core_system_audio_codec_adpcm_enc      = $(PATH_core_system)/audio/codec/adpcm_enc
PATH_core_system_audio_codec_amr_dec        = $(PATH_core_system)/audio/codec/amr_dec
PATH_core_system_audio_codec_mp3_enc        = $(PATH_core_system)/audio/codec/mp3_enc
PATH_core_system_audio_codec_mp3_dec        = $(PATH_core_system)/audio/codec/mp3_dec
PATH_core_system_audio_codec_wav_enc        = $(PATH_core_system)/audio/codec/wav_enc
PATH_core_system_audio_codec_wav_dec        = $(PATH_core_system)/audio/codec/wav_dec
PATH_core_system_audio_control  = $(PATH_core_system)/audio/control
PATH_core_system_audio_nr       = $(PATH_core_system)/audio/nr
PATH_core_system_audio_sbc      = $(PATH_core_system)/audio/sbc
PATH_core_system_audio_src      = $(PATH_core_system)/audio/src
PATH_core_system_audio_wnr      = $(PATH_core_system)/audio/wnr
PATH_core_system_buffering      = $(PATH_core_system)/buffering
PATH_core_system_comp_ctl       = $(PATH_core_system)/comp_ctl
PATH_core_system_dsc            = $(PATH_core_system)/dsc
PATH_core_system_exif           = $(PATH_core_system)/exif
PATH_core_system_fs             = $(PATH_core_system)/fs
PATH_core_system_gsensor        = $(PATH_core_system)/gsensor
PATH_core_system_gyrosensor     = $(PATH_core_system)/gyrosensor
PATH_core_system_host_if        = $(PATH_core_system)/host_if
PATH_core_system_misc           = $(PATH_core_system)/misc
PATH_core_system_mm             = $(PATH_core_system)/mm
PATH_core_system_multicore      = $(PATH_core_system)/multicore
PATH_core_system_os             = $(PATH_core_system)/os
PATH_core_system_ptz            = $(PATH_core_system)/ptz
PATH_core_system_rtc            = $(PATH_core_system)/rtc
PATH_core_system_sensor         = $(PATH_core_system)/sensor
PATH_core_system_sys            = $(PATH_core_system)/sys
PATH_core_system_touchpanel     = $(PATH_core_system)/touchpanel
PATH_core_system_usb_dev        = $(PATH_core_system)/usb_dev
PATH_core_system_usb_dev_common = $(PATH_core_system)/usb_dev/common
PATH_core_system_usb_dev_msdc   = $(PATH_core_system)/usb_dev/msdc
PATH_core_system_usb_dev_uvc    = $(PATH_core_system)/usb_dev/uvc
PATH_core_system_usb_dev_vendor = $(PATH_core_system)/usb_dev/vendor
PATH_core_system_usb_embed_host = $(PATH_core_system)/usb_embed_host
PATH_core_system_usb_host       = $(PATH_core_system)/usb_host
PATH_core_system_vid_play       = $(PATH_core_system)/vid_play
PATH_core_system_vid_play_inc_parser        = $(PATH_core_system_vid_play)/inc/parser
PATH_core_system_vid_recd       = $(PATH_core_system)/vid_recd

PATH_core_system_net            = $(PATH_core_system)/net
PATH_core_system_net_api        = $(PATH_core_system_net)/api
PATH_core_system_net_arch_v4l   = $(PATH_core_system_net)/arch/v4l

PATH_core_system_net_cgi        = $(PATH_core_system_net)/cgi
PATH_core_system_net_dhcp       = $(PATH_core_system_net)/dhcp
PATH_core_system_net_lib        = $(PATH_core_system_net)/lib

PATH_core_system_net_upnp                 = $(PATH_core_system_net)/upnp
PATH_core_system_net_libupnp              = $(PATH_core_system_net)/libupnp
PATH_core_system_net_libupnp_core         = $(PATH_core_system_net_libupnp)/core
PATH_core_system_net_libupnp_core_gena    = $(PATH_core_system_net_libupnp_core)/gena
PATH_core_system_net_libupnp_core_genlib  = $(PATH_core_system_net_libupnp_core)/genlib
PATH_core_system_net_libupnp_upnp         = $(PATH_core_system_net_libupnp)/upnp
PATH_core_system_net_libupnp_ixml         = $(PATH_core_system_net_libupnp)/ixml
PATH_core_system_net_libupnp_pthread      = $(PATH_core_system_net_libupnp)/pthread
PATH_core_system_net_libupnp_threadutil   = $(PATH_core_system_net_libupnp)/threadutil

PATH_core_system_net_lwip       = $(PATH_core_system_net)/lwip
PATH_core_system_net_lwip_api   = $(PATH_core_system_net_lwip)/api
PATH_core_system_net_lwip_core   = $(PATH_core_system_net_lwip)/core
PATH_core_system_net_lwip_ipv4  = $(PATH_core_system_net_lwip)/ipv4
PATH_core_system_net_lwip_netif = $(PATH_core_system_net_lwip)/netif
PATH_core_system_net_lwip_port  = $(PATH_core_system_net_lwip)/port

PATH_core_system_net_streaming          = $(PATH_core_system_net)/streaming
PATH_core_system_net_streaming_protocol = $(PATH_core_system_net_streaming)/protocol
PATH_core_system_net_streaming_server   = $(PATH_core_system_net_streaming)/server

PATH_core_system_net_tutk               = $(PATH_core_system_net)/tutk
PATH_core_system_net_wifi               = $(PATH_core_system_net)/wifi

#-------------------------------------------------------------------------------
#	Project folder paths
#-------------------------------------------------------------------------------
PATH_project                                    = $(PATH_sc)project
PATH_project_Dvr_CarDV_SDK                      = $(PATH_project)/Dvr_CarDV_SDK
PATH_project_Dvr_CarDV_SDK_cfg                  = $(PATH_project_Dvr_CarDV_SDK)/cfg
PATH_project_Dvr_CarDV_SDK_downloadtool         = $(PATH_project_Dvr_CarDV_SDK)/tools/DownloadTool_M5
PATH_project_Dvr_CarDV_SDK_cfg_algorithm        = $(PATH_project_Dvr_CarDV_SDK_cfg)/algorithm
PATH_project_Dvr_CarDV_SDK_cfg_algorithm_agc    = $(PATH_project_Dvr_CarDV_SDK_cfg_algorithm)/agc
PATH_project_Dvr_CarDV_SDK_cfg_algorithm_eq     = $(PATH_project_Dvr_CarDV_SDK_cfg_algorithm)/eq
PATH_project_Dvr_CarDV_SDK_cfg_algorithm_ldws   = $(PATH_project_Dvr_CarDV_SDK_cfg_algorithm)/ldws
PATH_project_Dvr_CarDV_SDK_cfg_algorithm_mdtc   = $(PATH_project_Dvr_CarDV_SDK_cfg_algorithm)/mdtc
PATH_project_Dvr_CarDV_SDK_cfg_algorithm_nr_wnr = $(PATH_project_Dvr_CarDV_SDK_cfg_algorithm)/nr_wnr
PATH_project_Dvr_CarDV_SDK_cfg_clock            = $(PATH_project_Dvr_CarDV_SDK_cfg)/clock
PATH_project_Dvr_CarDV_SDK_cfg_comp             = $(PATH_project_Dvr_CarDV_SDK_cfg)/comp
PATH_project_Dvr_CarDV_SDK_cfg_core             = $(PATH_project_Dvr_CarDV_SDK_cfg)/core
PATH_project_Dvr_CarDV_SDK_cfg_dram             = $(PATH_project_Dvr_CarDV_SDK_cfg)/dram
PATH_project_Dvr_CarDV_SDK_cfg_fs               = $(PATH_project_Dvr_CarDV_SDK_cfg)/fs
PATH_project_Dvr_CarDV_SDK_cfg_hdr              = $(PATH_project_Dvr_CarDV_SDK_cfg)/hdr
PATH_project_Dvr_CarDV_SDK_cfg_isp              = $(PATH_project_Dvr_CarDV_SDK_cfg)/isp
PATH_project_Dvr_CarDV_SDK_cfg_ldc              = $(PATH_project_Dvr_CarDV_SDK_cfg)/ldc
PATH_project_Dvr_CarDV_SDK_cfg_net              = $(PATH_project_Dvr_CarDV_SDK_cfg)/net
PATH_project_Dvr_CarDV_SDK_cfg_pq               = $(PATH_project_Dvr_CarDV_SDK_cfg)/PQ
PATH_project_Dvr_CarDV_SDK_cfg_ptz              = $(PATH_project_Dvr_CarDV_SDK_cfg)/ptz
PATH_project_Dvr_CarDV_SDK_cfg_sdk              = $(PATH_project_Dvr_CarDV_SDK_cfg)/sdk
PATH_project_Dvr_CarDV_SDK_cfg_sf               = $(PATH_project_Dvr_CarDV_SDK_cfg)/SF
PATH_project_Dvr_CarDV_SDK_cfg_snr              = $(PATH_project_Dvr_CarDV_SDK_cfg)/snr
PATH_project_Dvr_CarDV_SDK_cfg_usb              = $(PATH_project_Dvr_CarDV_SDK_cfg)/usb
PATH_project_Dvr_CarDV_SDK_cfg_vidrec           = $(PATH_project_Dvr_CarDV_SDK_cfg)/vidrec
PATH_project_Dvr_CarDV_SDK_Menu									= $(PATH_project_Dvr_CarDV_SDK)/Menu
PATH_project_Dvr_CarDV_SDK_Menu_draw							= $(PATH_project_Dvr_CarDV_SDK_Menu)/draw
PATH_project_Dvr_CarDV_SDK_OSDIcon								= $(PATH_project_Dvr_CarDV_SDK)/OSDIcon
PATH_project_Dvr_CarDV_SDK_OSDIcon_OSDIcon						= $(PATH_project_Dvr_CarDV_SDK_OSDIcon)/OSDIcon
PATH_project_Dvr_CarDV_SDK_OSDIcon_OSDIcon_src					= $(PATH_project_Dvr_CarDV_SDK_OSDIcon_OSDIcon)/src
PATH_project_Dvr_CarDV_SDK_OSDIcon_OSDIconLarge					= $(PATH_project_Dvr_CarDV_SDK_OSDIcon)/OSDIconLarge
PATH_project_Dvr_CarDV_SDK_OSDIcon_position						= $(PATH_project_Dvr_CarDV_SDK_OSDIcon)/position
PATH_project_Dvr_CarDV_SDK_OSDString							= $(PATH_project_Dvr_CarDV_SDK)/OSDString
PATH_project_Dvr_CarDV_SDK_src                           		= $(PATH_project_Dvr_CarDV_SDK)/src
PATH_project_Dvr_CarDV_SDK_sd_updater                    		= $(PATH_project_Dvr_CarDV_SDK)/sd_updater
PATH_project_Dvr_CarDV_SDK_UI                           		= $(PATH_project_Dvr_CarDV_SDK)/UI
PATH_project_Dvr_CarDV_SDK_Draw									= $(PATH_project_Dvr_CarDV_SDK)/Draw

PATH_LibSourceInc_wifi											= $(PATH_sc)LibSourceInc/wifi
PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_lib						= $(PATH_sc)LibSourceInc/wifi/WiFi-BCM-SDIO/lib
PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include       	= $(PATH_sc)LibSourceInc/wifi/WiFi-BCM-SDIO/wlan/src/include
PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include_proto 	= $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include)/proto
PATH_LibSourceInc_wifi_WiFi-MT7751								= $(PATH_sc)LibSourceInc/wifi/WiFi-MT7751
PATH_LibSourceInc_wifi_WiFi-MT7751_lib							= $(PATH_sc)LibSourceInc/wifi/WiFi-MT7751/lib
PATH_LibSourceInc_wifi_WiFi-RTL8189								= $(PATH_sc)LibSourceInc/wifi/WiFi-RTL8189
PATH_LibSourceInc_wifi_WiFi-RTL8189_lib							= $(PATH_sc)LibSourceInc/wifi/WiFi-RTL8189/lib
PATH_LibSourceInc_wifi_WiFi-ATBM6022							= $(PATH_sc)LibSourceInc/wifi/WiFi-ATBM6022
PATH_LibSourceInc_wifi_WiFi-ATBM6022_lib						= $(PATH_sc)LibSourceInc/wifi/WiFi-ATBM6022/lib

PATH_vendor_wifi_BCM       	= $(PATH_sc)vendor/wifi/BCM
PATH_vendor_wifi_Interface 	= $(PATH_sc)vendor/wifi/Interface

PATH_vendor					= $(PATH_sc)vendor
PATH_vendor_gps            	= $(PATH_sc)vendor/gps
PATH_vendor_gsensor        	= $(PATH_sc)vendor/gsensor
PATH_vendor_ir             	= $(PATH_sc)vendor/ir
PATH_vendor_panel          	= $(PATH_sc)vendor/panel
PATH_vendor_RTC				= $(PATH_sc)vendor/RTC
PATH_vendor_sensor         	= $(PATH_sc)vendor/sensor
PATH_vendor_misc           	= $(PATH_sc)vendor/misc
PATH_vendor_tpms			= $(PATH_sc)vendor/TPMS
PATH_vendor_touchpanel		= $(PATH_sc)vendor/touchpanel
PATH_vendor_speech			= $(PATH_sc)vendor/speech

PATH_core_utility			= $(PATH_sc)core/utility

#-------------------------------------------------------------------------------
# others folder paths
#-------------------------------------------------------------------------------
PATH_C +=\
    $(PATH_dlm_entry)/src\
    $(PATH_cust_sys)/src

#ifeq ($(call FIND_COMPILER_OPTION, __RFID__), TRUE)
PATH_C +=\
    $(PATH_rfid)/src
#endif

# path to header files (sys)
PATH_H +=\
    $(PATH_dlm_entry)/inc\

#ifeq ($(call FIND_COMPILER_OPTION, __RFID__), TRUE)
PATH_H +=\
    $(PATH_ResMgr)/pub \
    $(PATH_rfid)/pub \
    $(PATH_rfid)/inc
#endif

# path to header files (app)
PATH_H +=\
    $(PATH_UnitTestApp)/inc\
    $(PATH_srv)/inc\

# path to header files (cust)
PATH_H +=\
    $(PATH_cust_sys)/inc\
    $(PATH_cus_app)/inc\

# path to header files (mdl)
PATH_H +=\
    $(PATH_pm_mdl)/inc\
    $(PATH_mmaudio)/audiocontrol/inc\
    $(PATH_audio)/itf\
    $(PATH_fms)/itf_open\
    $(PATH_audio)/itf_open

# path to header files (drv & hal)
PATH_H +=\
    $(PATH_rtc)/inc\
    $(PATH_bus)/inc\
    $(PATH_pm)/inc\
    $(PATH_fmrx)/inc\
    $(PATH_emi_hal)/inc\
    $(PATH_bus_hal)/inc\
    $(PATH_int_hal)/inc\
    $(PATH_io_hal)/inc\
    $(PATH_clkgen_hal)/inc\
    $(PATH_kernel_hal)/inc\
    $(PATH_flash_hal)/inc\
    $(PATH_rtc_hal)/inc\
    $(PATH_disp_hal)/inc\
    $(PATH_keypad_hal)/inc\
    $(PATH_pll_hal)/inc\
    $(PATH_batt_hal)/inc\
    $(PATH_pm_hal)/inc\
    $(PATH_drvutil_hal)/inc

# path to assembler source files
ifeq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),)
PATH_ASM +=\
    $(PATH_arm)/src\
    $(PATH_int_hal)/src\
    $(PATH_fms)/src\
    $(PATH_pm_hal)/src\
    $(PATH_emi_hal)/src\
    $(PATH_mmaudio)/midilib/src\
    $(PATH_pmu)/src
endif

# path to assembler include files
PATH_I +=\
    $(PATH_kernel_hal)/inc

# if build 8830X then include R2
ifeq ($(filter __MSW8830N__, $(PP_OPT_COMMON)), __MSW8830N__)
PATH_C +=\
    $(PATH_r2)/src\

endif

# path to cust drivers
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
  PATH_C += \
    $(PATH_cust_drv)/app_calibration_table/src\
    $(PATH_cust_drv)/battery/src\
    $(PATH_cust_drv)/gpio/src\
    $(PATH_cust_drv)/keypad/src\
    $(PATH_cust_drv)/kpdlight/src\
    $(PATH_cust_drv)/lcm/logo\
    $(PATH_cust_drv)/lcm//$(LCD_BASE)\
    $(PATH_customer_product_lcd)/global_base \
    $(PATH_customer_product_lcd)/allinone_base \
    $(PATH_cust_drv)/backlight/src \
    $(PATH_cust_drv)/pm/src\
    $(PATH_cust_drv)/pwm/src\
    $(PATH_cust_drv)/touchscreen/src\
    $(PATH_cust_drv)/service/src\
    $(PATH_cust_drv)/gpd/src\
    $(PATH_cust_drv)/arp_calibration_table/src\
    $(PATH_cust_drv)/ofn/src\
    $(PATH_cust_drv)/gsensor/src\
    $(PATH_cust_drv)/proximitysensor/src


  PATH_H += \
    $(PATH_cust_drv)/battery/inc\
    $(PATH_cust_drv)/gpio/inc\
    $(PATH_cust_drv)/keypad/inc\
    $(PATH_cust_drv)/pm/inc\
    $(PATH_cust_drv)/pwm/inc\
    $(PATH_cust_drv)/touchscreen/inc\
    $(PATH_cust_drv)/service/inc\
    $(PATH_cust_drv)/lcm\
    $(PATH_cust_drv)/ofn/inc\
    $(PATH_drv)/ofn/inc\
    $(PATH_cust_drv)/gsensor/inc\
    $(PATH_cust_drv)/backlight/inc\
    $(PATH_cust_drv)/proximitysensor/inc

else
  PATH_C += \
    $(PATH_cust_drv)/src \
    $(PATH_cust_drv)/src/lcd/ \
    $(PATH_customer_product_lcd)/global_base \
    $(PATH_customer_product_lcd)/allinone_base \
    $(PATH_customer_drv)/backlight/src \
    $(PATH_customer_drv)/ofn/src\
    $(PATH_customer_drv)/gsensor/src\
    $(PATH_customer_drv)/touchscreen/src

  PATH_H += \
    $(PATH_cust_drv)/inc\
    $(PATH_customer_drv)/gsensor/inc\
    $(PATH_customer_drv)/backlight/inc\
    $(PATH_customer_drv)/ofn/inc \
    $(PATH_drv)/ofn/inc\
    $(PATH_customer_drv)/touchscreen/inc

endif

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
PATH_H +=\
  $(PATH_vt_mm)/inc\
  $(PATH_vt_task)/inc\
  $(PATH_vdr)/inc/vtmx
endif

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
PATH_H +=\
    $(PATH_vt_task)/itf
endif

# path to external library files
ifeq ($(LINKER),ADSV12_link)
PATH_EXT_LIB +=\
    $(PATH_signature)/lib_ads
endif
ifeq ($(LINKER),RVCTV22_link)
PATH_EXT_LIB +=\
    $(PATH_signature)/lib_rvct
endif

PATH_EXT_LIB +=\
    $(PATH_lib_sdk)

#-------------------------------------------------------------------------------
# public header path is specified in paths_pub.mak
#-------------------------------------------------------------------------------
include $(PATH_common_mak)paths_pub.mak

#-------------------------------------------------------------------------------
# 3rd path
#-------------------------------------------------------------------------------
include $(PATH_3rd)/3rd.mak

#-------------------------------------------------------------------------------
# 3rd path is specified in paths_3rd.mak
# only the module in  $(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD) would include paths_3rd.mak
#-------------------------------------------------------------------------------
ifneq ($(filter $(TARGET), $(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD)),)
include $(PATH_common_mak)paths_3rd.mak
endif

#-------------------------------------------------------------------------------
# dlm_module path is specified in path_dlm.mak
#-------------------------------------------------------------------------------
include $(PATH_dlm_entry)path_dlm.mak



