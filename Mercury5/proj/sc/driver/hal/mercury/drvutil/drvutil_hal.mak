#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_H +=\
  $(PATH_dma_hal)/inc\
  $(PATH_uart_hal)/inc
PATH_C +=\
  $(PATH_drvutil_hal)/src
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	hal_drv_util.c
