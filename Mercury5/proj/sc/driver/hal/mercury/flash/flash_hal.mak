#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_flash_hal)/src

PATH_I +=\
  $(PATH_flash)/inc\
  $(PATH_bus)/pub\

PATH_H +=\
  $(PATH_flash)/inc\
  $(PATH_bdma_hal)/inc\
  $(PATH_bdma)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_bus_fsp_spi.c\
  hal_serial_flash.c