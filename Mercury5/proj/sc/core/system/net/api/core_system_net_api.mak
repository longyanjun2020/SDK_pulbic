#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_ahc                        = $(PATH_sc)ahc
PATH_ahc_api                    = $(PATH_ahc)/api
#PATH_ahc_api_audio              = $(PATH_ahc_api)/audio
#PATH_ahc_api_stream             = $(PATH_ahc_api)/stream
#PATH_ahc_api_general            = $(PATH_ahc_api)/general
PATH_ahc_api_audio            = $(PATH_ahc_api)/audio
PATH_ahc_api_browser            = $(PATH_ahc_api)/browser
PATH_ahc_api_capture            = $(PATH_ahc_api)/capture
PATH_ahc_api_dcfdt            = $(PATH_ahc_api)/dcfdt
PATH_ahc_api_dcf            = $(PATH_ahc_api)/dcf
PATH_ahc_api_debugex            = $(PATH_ahc_api)/debugex
PATH_ahc_api_display            = $(PATH_ahc_api)/display
PATH_ahc_api_fs            = $(PATH_ahc_api)/fs
PATH_ahc_api_general            = $(PATH_ahc_api)/general
PATH_ahc_api_gui            = $(PATH_ahc_api)/gui
PATH_ahc_api_isp            = $(PATH_ahc_api)/isp
PATH_ahc_api_media            = $(PATH_ahc_api)/media
PATH_ahc_api_motor            = $(PATH_ahc_api)/motor
PATH_ahc_api_os            = $(PATH_ahc_api)/os
PATH_ahc_api_parameter            = $(PATH_ahc_api)/parameter
PATH_ahc_api_protection            = $(PATH_ahc_api)/protection
PATH_ahc_api_rtc            = $(PATH_ahc_api)/rtc
PATH_ahc_api_sd            = $(PATH_ahc_api)/sd
PATH_ahc_api_stream            = $(PATH_ahc_api)/stream
PATH_ahc_api_uf            = $(PATH_ahc_api)/uf
PATH_ahc_api_version            = $(PATH_ahc_api)/version
PATH_ahc_api_video            = $(PATH_ahc_api)/video
PATH_ahc_api_gpio            = $(PATH_ahc_api)/gpio


PATH_cardv_cfg_cfg_isp     = $(PATH_project_Dvr_CarDV_SDK_cfg)/isp
PATH_cardv_cfg_cfg_core     = $(PATH_project_Dvr_CarDV_SDK_cfg)/core
PATH_cardv_cfg_cfg_fs     = $(PATH_project_Dvr_CarDV_SDK_cfg)/fs
PATH_cardv_cfg_cfg_net     = $(PATH_project_Dvr_CarDV_SDK_cfg)/net
PATH_cardv_cfg_cfg_sdk     = $(PATH_project_Dvr_CarDV_SDK_cfg)/sdk
PATH_cardv_cfg_cfg_snr     = $(PATH_project_Dvr_CarDV_SDK_cfg)/snr
PATH_cardv_cfg_cfg_usb     = $(PATH_project_Dvr_CarDV_SDK_cfg)/usb

#naming violation!
PATH_core_lib_gui_inc_Core     = $(PATH_core_lib_gui)/inc/Core
PATH_core_lib_gui_inc_Config    = $(PATH_core_lib_gui)/inc/Config
PATH_core_lib_algorithm_adas = $(PATH_core_lib_algorithm)/adas

PATH_core_system_vid_play_inc_parser        = $(PATH_core_system)/vid_play/inc/parser

PATH_core_system_net_cgi        = $(PATH_core_system_net)/cgi
PATH_core_system_net_arch_v4l   = $(PATH_core_system_net)/arch/v4l
PATH_core_system_net_dhcp       = $(PATH_core_system_net)/dhcp
PATH_core_system_net_lib        = $(PATH_core_system_net)/lib

PATH_core_system_net_upnp       = $(PATH_core_system_net)/upnp
PATH_core_system_net_libupnp    = $(PATH_core_system_net)/libupnp
PATH_core_system_net_libupnp_core        = $(PATH_core_system_net_libupnp)/core
PATH_core_system_net_libupnp_core_gena       = $(PATH_core_system_net_libupnp_core)/gena
PATH_core_system_net_libupnp_core_genlib     = $(PATH_core_system_net_libupnp_core)/genlib
PATH_core_system_net_libupnp_upnp     = $(PATH_core_system_net_libupnp)/upnp
PATH_core_system_net_libupnp_ixml     = $(PATH_core_system_net_libupnp)/ixml
PATH_core_system_net_libupnp_pthread  = $(PATH_core_system_net_libupnp)/pthread
PATH_core_system_net_libupnp_threadutil = $(PATH_core_system_net_libupnp)/threadutil

PATH_core_system_net_lwip       = $(PATH_core_system_net)/lwip
PATH_core_system_net_lwip_api   = $(PATH_core_system_net_lwip)/api
PATH_core_system_net_lwip_ipv4  = $(PATH_core_system_net_lwip)/ipv4
PATH_core_system_net_lwip_netif = $(PATH_core_system_net_lwip)/netif
PATH_core_system_net_lwip_port  = $(PATH_core_system_net_lwip)/port

PATH_core_system_net_streaming  = $(PATH_core_system_net)/streaming
PATH_core_system_net_streaming_server  = $(PATH_core_system_net_streaming)/server

PATH_core_include               = $(PATH_sc)core/include
PATH_core_include_application   = $(PATH_core_include)/application
PATH_core_include_display       = $(PATH_core_include)/display
PATH_core_include_img_pipe      = $(PATH_core_include)/img_pipe
PATH_core_include_misc          = $(PATH_core_include)/misc
PATH_core_include_usb           = $(PATH_core_include)/usb

PATH_project_Dvr_CarDV_SDK      = $(PATH_sc)project/Dvr_CarDV_SDK
PATH_project_Dvr_CarDV_SDK_Menu = $(PATH_project_Dvr_CarDV_SDK)/Menu
PATH_project_Dvr_CarDV_SDK_UI = $(PATH_project_Dvr_CarDV_SDK)/UI

PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include = $(PATH_sc)LibSourceInc/wifi/WiFi-BCM-SDIO/wlan/src/include
PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include_proto = $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include)/proto
PATH_vendor_wifi_BCM = $(PATH_sc)vendor/wifi/BCM
PATH_vendor_wifi_Interface = $(PATH_sc)vendor/wifi/Interface

#C_OPTIONS += -DTARGETOS_car=

PATH_C +=\
    $(PATH_core_system_net_api)/src\

PATH_H +=\
	$(PATH_ahc)/inc\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include_proto)\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include)\
    $(PATH_ahc_api_audio)/inc\
    $(PATH_ahc_api_browser)/inc\
    $(PATH_ahc_api_capture)/inc\
    $(PATH_ahc_api_dcfdt)/inc\
    $(PATH_ahc_api_dcf)/inc\
    $(PATH_ahc_api_debugex)/inc\
    $(PATH_ahc_api_display)/inc\
    $(PATH_ahc_api_fs)/inc\
    $(PATH_ahc_api_general)/inc\
    $(PATH_ahc_api_gui)/inc\
    $(PATH_ahc_api_isp)/inc\
    $(PATH_ahc_api_media)/inc\
    $(PATH_ahc_api_modectl)/inc\
    $(PATH_ahc_api_motor)/inc\
    $(PATH_ahc_api_os)/inc\
    $(PATH_ahc_api_msgqueue)/inc\
    $(PATH_ahc_api_parameter)/inc\
    $(PATH_ahc_api_protection)/inc\
    $(PATH_ahc_api_rtc)/inc\
    $(PATH_ahc_api_sd)/inc\
    $(PATH_ahc_api_stream)/inc\
    $(PATH_ahc_api_uf)/inc\
    $(PATH_ahc_api_version)/inc\
    $(PATH_ahc_api_video)/inc\
    $(PATH_ahc_api_gpio)/inc\
    $(PATH_ahc_api)/inc\
    $(PATH_application_sys_utility_FileProspector_Porting)/inc\
    $(PATH_cardv_cfg_cfg_isp)/inc\
    $(PATH_cardv_cfg_cfg_core)/inc\
    $(PATH_cardv_cfg_cfg_fs)/inc\
    $(PATH_cardv_cfg_cfg_net)/inc\
    $(PATH_cardv_cfg_cfg_sdk)/inc\
    $(PATH_cardv_cfg_cfg_snr)/inc\
    $(PATH_cardv_cfg_cfg_usb)/inc\
    $(PATH_core_application_mmpd_audio)/inc\
    $(PATH_core_application_mmpd_dsc)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmpd_img_pipe)/inc\
    $(PATH_core_application_mmpd_vid_play)/inc\
    $(PATH_core_application_mmps_audio)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_vid_play)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_misc)/inc\
    $(PATH_core_driver_pll)/inc\
    $(PATH_core_driver_pwm)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_include_usb)\
    $(PATH_core_lib_algorithm_adas)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Config)\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_exif)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_misc)/inc\
    $(PATH_core_system_net_api)/inc\
    $(PATH_core_system_net_cgi)/inc\
    $(PATH_core_system_net_dhcp)/inc\
    $(PATH_core_system_net_libupnp_core_genlib)/inc\
    $(PATH_core_system_net_libupnp_ixml)/inc\
    $(PATH_core_system_net_libupnp_pthread)/inc\
    $(PATH_core_system_net_libupnp_threadutil)/inc\
    $(PATH_core_system_net_libupnp_upnp)/inc\
    $(PATH_core_system_net_lib)/inc\
    $(PATH_core_system_net_lwip_api)/inc\
    $(PATH_core_system_net_lwip_ipv4)/inc\
    $(PATH_core_system_net_lwip_netif)/inc\
    $(PATH_core_system_net_lwip_port)/inc\
    $(PATH_core_system_net_streaming_server)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_system_usb_dev_uvc)/inc\
    $(PATH_core_system_usb_host)/inc\
    $(PATH_core_system_vid_play_inc_parser)\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_sys)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_driver_drv_int_pub)\
    $(PATH_driver_drv_io_pub)\
    $(PATH_driver_drv_jpd)/inc\
    $(PATH_driver_drv_sensordriver)/inc\
    $(PATH_driver_drv_timer_pub)\
    $(PATH_driver_hal_infinity_int_pub)\
    $(PATH_driver_hal_infinity_io_pub)\
    $(PATH_driver_hal_infinity_kernel)/inc\
    $(PATH_driver_hal_infinity_timer_pub)\
    $(PATH_middleware_pm_pub)\
    $(PATH_project_Dvr_CarDV_SDK_Menu)/inc\
    $(PATH_project_Dvr_CarDV_SDK_UI)/inc\
    $(PATH_system_MsWrapper_pub)\
    $(PATH_system_fc_pub)\
    $(PATH_system_libc)/inc\
    $(PATH_system_rtk_pub)\
    $(PATH_system_sdtarget_common_include)\
    $(PATH_system_sdtarget_wintarget)/inc\
    $(PATH_system_sys_pub)\
    $(PATH_core_system_net_wifi)/inc\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include)\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include_proto)\

ifeq ($(filter WIFI_PORT ,$(PP_OPT_COMMON)),WIFI_PORT)
PATH_H += \
    $(PATH_LibSourceInc_wifi_WiFi-MT7751)/interface/adapter\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189)\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189)/rtk_wifi_api\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189)/include\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189)/src/osdep\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189)/src/osdep/ucosii
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    netapp.c\
    net_utility.c\
    lwip_main.c

