#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_v24)/src \
  $(PATH_v24)/opxc

PATH_H +=\
  $(PATH_v24)/inc\
  $(PATH_usb_mdl)/pub\
  $(PATH_uart_hal)/inc

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
   abi_headers_v24.c \
   v24_at.c       \
   v24_autobaud.c \
   v24_ctrl.c     \
   v24_data.c     \
   v24_debug.c    \
   v24_hapc.c     \
   v24_hub.c      \
   v24_pal.c      \
   v24_req.c      \
   v24_task.c     \
   v24_util.c     \
   v24_usb.c      \
   opec_v24.c     \
   usb_cdc_fl.c

