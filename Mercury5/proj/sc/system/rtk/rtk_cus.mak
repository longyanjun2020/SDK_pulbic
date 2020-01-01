#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_I +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/pub
  
PATH_ASM +=\
    $(PATH_rtk)/src/arm

PATH_H +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/itf\
  $(PATH_rtk)/itf_open\
  $(PATH_rtk)/tests/inc\
  $(PATH_adc)/pub\
  $(PATH_storage)/pub\
  $(PATH_storage_mdl)/pub\
  $(PATH_compression_mdl)/pub\
  $(PATH_acc_inc)/pub\
  $(PATH_lcd)/pub\
  $(PATH_gpd_mdl)/pub\
  $(PATH_gpd)/pub\
  $(PATH_rtc)/pub\
  $(PATH_core_system_misc)/inc\
  $(PATH_Pnl)/inc\
  $(PATH_Pnl_hal)/inc\
  $(PATH_core_driver_display)/inc
  
PATH_C +=\
  $(PATH_rtk)/src\
  $(PATH_rtk)/src_cus
  
#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  rtkgo.c\
  rtk_backtrace.c\
  ramdump.c
