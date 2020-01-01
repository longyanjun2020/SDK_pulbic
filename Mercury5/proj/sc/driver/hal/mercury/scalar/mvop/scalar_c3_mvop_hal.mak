#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
          	$(PATH_scalar_c3_mvop_hal)/src\
		
PATH_H +=\
		$(PATH_utopia_msos)/inc\
		$(PATH_utopia_common)/inc\
    		$(PATH_utopia_chip)/inc\
		$(PATH_scalar_c3_mvop)/inc\
		$(PATH_scalar_c3_mvop_hal)/inc\
		$(PATH_scalar_c3)/miu\
		$(PATH_cam_os_wrapper)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
		halMVOP.c
		