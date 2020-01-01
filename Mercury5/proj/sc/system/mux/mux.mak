#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H += \
  $(PATH_mux)/inc
  
PATH_C +=\
 $(PATH_mux)/src

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
   abi_headers_mux.c \
   mux_ctx.c    \
   mux_itf.c    \
   mux_mux.c    \
   mux_send.c   \
   mux_tim.c    \
   mux_util.c   \

