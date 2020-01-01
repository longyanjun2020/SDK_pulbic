#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_ofn)/src

PATH_H +=\
$(PATH_drv)/ofn/pub
    
OFN_DRV_INC +=\
  inc


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  abi_headers_ofn.c \
  drv_ofn.c \
  drv_ofn_glue.c

PATH_H += $(addprefix $(PATH_ofn)/, $(OFN_DRV_INC))  
