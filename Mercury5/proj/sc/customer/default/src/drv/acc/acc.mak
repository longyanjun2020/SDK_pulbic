#-------------------------------------------------------------------------------
#
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

ACC_DRV_INC +=\
  inc

PATH_C +=\
    $(PATH_acc)/opxc\
    $(PATH_acc)/src

PATH_H +=\
  $(PATH_emi)/pub\
  $(PATH_adc)/pub\
  $(PATH_adc_hal)/pub\
  $(PATH_backlight)/pub\
  $(PATH_batt)/pub\
  $(PATH_image_codec)/pub\
  $(PATH_tscr_mdl)/pub\
  $(PATH_gss)/pub\
  $(PATH_keypad_mdl)/pub\
  $(PATH_flash)/pub\
  $(PATH_drv)/ofn/pub\
  $(PATH_bluetooth)/pub\
  $(PATH_acc_inc)/pub\
  $(PATH_gsensor)/pub\
  $(PATH_tscr)/pub\
  $(PATH_lcd)/pub\
  $(PATH_gpd_mdl)/pub\
  $(PATH_audio_drv)/pub\
  $(PATH_gpd)/pub\
  $(PATH_bdma)/pub\
  $(PATH_sys)/pub\
  $(PATH_sys)/inc\
  $(PATH_fmrx)/pub\
  $(PATH_dynldr)/pub\
  $(PATH_flash)/pub\
  $(PATH_flash)/inc\
  $(PATH_flash_hal)/inc\

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PATH_H += $(PATH_unfd)/pub
endif
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

# XXX: PLEASE SYNC WITH tools\CheckSize\src\Download_Checker.c
# mcp_drv_$(BB_CHIP_ID).c is also used by download checker. Please also check final_product.mak if mcp_drv_$(BB_CHIP_ID).c is modified.
  REL_SRC_C_LIST += mcp_drv_$(BB_CHIP_ID).c

PATH_H += $(addprefix $(PATH_acc_inc)/, $(ACC_DRV_INC))
PATH_H += $(PATH_gpd_hal)/inc
PATH_H += $(PATH_lcd_hal)/inc
PATH_H += $(PATH_bdma_hal)/inc





