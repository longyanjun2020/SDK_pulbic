#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_gop_hal)/src

PATH_H +=\
  $(PATH_gop_hal)/inc\
  $(PATH_gop)/inc\
  $(PATH_cam_os_wrapper)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  hal_gop.c


