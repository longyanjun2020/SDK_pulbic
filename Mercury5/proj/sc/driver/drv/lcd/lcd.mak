#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_lcd)/src

PATH_H +=\
  $(PATH_emi)/pub\
  $(PATH_adc)/pub\
  $(PATH_adc_hal)/pub\
  $(PATH_gss)/pub\
  $(PATH_drv)/ofn/pub\
  $(PATH_image_codec)/pub\
  $(PATH_acc_inc)/pub\
  $(PATH_fms)/inc\
  $(PATH_lcd)/pub\
  $(PATH_disp)/pub\
  $(PATH_gpd_mdl)/pub\
  $(PATH_gpd)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST +=\
  abi_headers_lcd.c \
  drv_lcd.c \
  drv_lcd_table.c

PATH_H+=$(PATH_lcd)/inc
PATH_H+=$(PATH_lcd_hal)/inc
  
