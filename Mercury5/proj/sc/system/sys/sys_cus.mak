#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

C_E2P_OBJS = custom.o

ifeq ($(COMPILER_VERSION),RVCTV22)
$(C_E2P_OBJS:%=$(OUT)%): C_OPTIONS += --diag_suppress 1296,170
endif

PATH_I +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
  $(PATH_sys)/pub

PATH_ASM +=\
  $(PATH_sys)/src

PATH_H +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
  $(PATH_sys)/itf_open\
  $(PATH_emi)/pub\
  $(PATH_emi)/inc\
  $(PATH_adc)/pub\
  $(PATH_adc_hal)/pub\
  $(PATH_compression_mdl)/pub\
  $(PATH_mtmgr)/pub\
  $(PATH_batt)/pub\
  $(PATH_usb_mdl)/pub\
  $(PATH_tscr_mdl)/pub\
  $(PATH_flash)/pub\
  $(PATH_rai)/pub\
  $(PATH_acc_inc)/pub\
  $(PATH_tscr)/pub\
  $(PATH_gpd_mdl)/pub\
  $(PATH_gpd)/pub\
  $(PATH_rtc)/pub\
  $(PATH_timer_hal)/pub\
  $(PATH_storage)/pub\
  $(PATH_flash)/inc\
  $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
  
PATH_C +=\
  $(PATH_sys)/src\
  $(PATH_sys)/src_cus

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  sys_premain.c\
  sys_shutdown.c\
  sys_mem.c\
  sys_dbg.c\
  log_util.c\
  custom.c\
  sys_c_start.c\
  sys_VM_table.c\
  sys_factory.c\
  init.c\
  sys_cust.c\
  sys_e2p_wrap.c\
  sys_cpu_api.c

#-------------------------------------------------------------------------------
#	List of EEPROM file
#-------------------------------------------------------------------------------
E2P_LIST_FOR_W_E2P_STACK =\
