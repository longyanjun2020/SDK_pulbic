#
# Makefile for MStar MFE (Multi-Format Encoder) device driver.

#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# MFE_PLATFORM = linux
MFE_PLATFORM = rtk

PATH_C +=\
  $(PATH_mfe)/src/common\
  $(PATH_mfe)/src/$(MFE_PLATFORM)\
  $(PATH_mfe)/test

PATH_H +=\
  $(PATH_mfe)/inc\
  $(PATH_mfe)/test\
  $(PATH_mfe_hal)/inc\
  $(PATH_mhve)/pub\
  $(PATH_cam_os_wrapper)/pub\
  $(PATH_mfe)/pub\
  $(PATH_core_driver_common)/inc\
  $(PATH_core_include_application)\
  $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mfe_test_i_sw.c\
    drv_mfe_enc.c\
    drv_mfe_ctx.c\
    drv_mfe_dev.c\
    drv_mfe_module.c\
    drv_mfe_clk.c