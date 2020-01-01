#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to Customizable source files
PATH_C +=\
  $(PATH_v24)/src_cus

PATH_H +=\
  $(PATH_v24)/inc\
  $(PATH_uart_hal)/inc

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
   v24_wrap.c     \
   v24_io.c       \
   v24_uart.c     

