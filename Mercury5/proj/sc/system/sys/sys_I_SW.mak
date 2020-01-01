#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_I +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
  $(PATH_sys)/pub\
  $(PATH_fc)/pub

PATH_ASM +=\
  $(PATH_sys)/src

PATH_H +=\
    $(PATH_sys)/inc\
    $(PATH_sys)/itf\
    $(PATH_sys)/itf_open\
    $(PATH_acc_inc)/pub\
    $(PATH_emi)/pub\
    $(PATH_emi)/inc\
    $(PATH_flash)/inc\
    $(PATH_ahc)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_sdk)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_dram)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_net)/inc\
    $(PATH_project_Dvr_CarDV_SDK_UI)/inc\
    $(PATH_project_Dvr_CarDV_SDK_Menu)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_isp)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_comp)/inc\
    $(PATH_core_application_mmps_vid_recd)/inc\
    $(PATH_core_application_mmps_system)/inc\
    $(PATH_core_application_mmps_display)/inc\
    $(PATH_core_application_mmpd_dsc)/inc\
    $(PATH_core_application_mmpd_flow_ctl)/inc\
    $(PATH_core_application_mmpd_display)/inc\
    $(PATH_core_application_mmpd_img_pipe)/inc\
    $(PATH_core_application_mmpd_system)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_display)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_ccir)/inc\
    $(PATH_core_driver_dram)/inc\
    $(PATH_core_driver_img_pipe)/inc\
    $(PATH_core_driver_timer)/inc\
    $(PATH_core_driver_storage)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_misc)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_algorithm)/inc\
    $(PATH_core_system_comp_ctl)/inc\
    $(PATH_core_system_sensor)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_net_lib)/inc\
    $(PATH_core_system_net_lwip_api_inc_lwip)\
    $(PATH_core_system_net_lwip_api)/inc\
    $(PATH_core_system_net_lwip_ipv4)/inc\
    $(PATH_core_system_net_lwip_netif)/inc\
    $(PATH_core_system_net_lwip_port)/inc\
    $(PATH_core_system_net_lwip_wifi)/inc\
    $(PATH_core_lib_algorithm)/adas/inc\
    $(PATH_core_lib_algorithm)/mdtc/inc\
    $(PATH_core_lib_algorithm)/edog/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_lib_gui_inc_Config)\
    $(PATH_core_system_os)/inc\
    $(PATH_core_utility)/inc\
    $(PATH_hostuvc_mdl)/pub\
    $(PATH_usbhost)/pub\
    $(PATH_usbhost)/inc/include\
    $(PATH_usbhost_hal)/inc\
    $(PATH_utopia)/common/inc\
    $(PATH_utopia)/msos/inc\
    $(PATH_vendor_gsensor)\
    $(PATH_core_system_gsensor)/inc\
    $(PATH_isp)/inc\
    $(PATH_isp)/pub\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include_proto)\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_wlan_src_include)\
PATH_C +=\
  $(PATH_dynldr)/src_cus

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  init.c\
  sys_premain_i_sw.c\
  sys_irq_ctrl.c\
  isw_cli.c\
  isw_cli_main.c\
  traces.c\
  sys_rand.c\
  tasks.c\
  sys_core.c\
  sys_queue.c\
  sys_tools.c\
  custom.c\
  sys_mem.c\
  sys_tools.c\
  sys_reset.c

#  sw_ver.c\
#  sys_mmap_cfg.c\

#  watch.c\
#  sys_tools.c\

#  sys_power_mngt.c\
#  sys_chip.c\
#  sys_profiling.c\
#  sys_core.c\
#  sys_queue.c\
#  sys_cpu_api.c\
#  sys_mmap_cfg.c\

#  sys_speed_profile.c\


ifeq ($(COMPILER_VERSION),ARMGCC)
SRC_ASM_LIST =\
  sys_abort.S\
  sys_kereset.S
endif

ifeq ($(BB_CHIP_ID),msw8533d)
SRC_ASM_LIST =\
  sys_sleep_b3_a.c\
  sys_abort.asm\
  fms_perf_asm.asm
else ifeq ($(BB_CHIP_ID),msw853xb)
SRC_ASM_LIST =\
  sys_sleep_b3_a.c\
  sys_abort.asm\
  fms_perf_asm.asm
else ifeq ($(BB_CHIP_ID),msw8556x)
SRC_ASM_LIST =\
  sys_sleep_b3_a.c\
  sys_abort.asm\
  fms_perf_asm.asm
else ifeq ($(BB_CHIP_ID),msw8573)
SRC_ASM_LIST =\
  sys_sleep_b3_a.c\
  sys_abort.asm\
  fms_perf_asm.asm
else ifeq ($(BB_CHIP_ID),msw8535x)
SRC_ASM_LIST =\
  sys_boot_b2.asm\
  sys_abort_i_sw.asm\
  fms_perf_asm.asm
else ifeq ($(BB_CHIP_ID),msw8533x)
SRC_ASM_LIST =\
  sys_boot_b3.asm\
  sys_abort_i_sw.asm\
  fms_perf_asm.asm
endif

#-------------------------------------------------------------------------------
#	List of EEPROM file
#-------------------------------------------------------------------------------
E2P_LIST_FOR_W_E2P_STACK =\
  stack.e2p
