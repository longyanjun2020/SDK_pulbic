#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

PATH_C +=\
  $(PATH_middleware)/vdr/src\
  $(PATH_drv)/lcd/src\
  $(PATH_drv)/glue/src\
  $(PATH_uart_hal)/src\
  $(PATH_dynldr)/src_cus

#  $(PATH_flash_hal)/src\

PATH_H +=\
  $(PATH_compression_mdl)/pub\
  $(PATH_lcd)/pub\
  $(PATH_disp)/pub\
  $(PATH_emi)/pub\
  $(PATH_audio_drv)/pub\
  $(PATH_fms)/inc\
  $(PATH_gpd_mdl)/pub



# The files are not in build code scope
ifneq ($(call FIND_COMPILER_OPTION, __INFINITY__),)
SRC_C_LIST =\
   sys_dummy.c\
   div64.c\
   sys_e2p_wrap.c\
   sys_dbg.c\
   
#   sys_cust.c\
#   sys_dpm_cfg.c\
#   sys_mmap_api.c\

else
SRC_C_LIST =\
  hwll1_fint.c\
  Hal_fuart.c\
  sys_dbg.c\
  sys_cust.c\
  sys_dpm_api.c\
  sys_e2p_wrap.c\
  sys_sldlm_api.c\
  sys_sldlm_cfg.c\
  sys_dpm_cfg.c\
  sys_mmap_api.c\
  cus_capability.c\
  mdl_vdr_biliner.c\
  drv_lcd_table.c\
  vfs_fat_wrapper.c\
  hal_serial_flash.c\
  drv_glue.c
endif