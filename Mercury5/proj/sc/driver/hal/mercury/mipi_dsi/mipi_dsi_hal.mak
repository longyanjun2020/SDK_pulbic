#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
          	$(PATH_mipi_dsi_hal)/src
		
PATH_H +=\
		$(PATH_mipi_dsi_hal)/inc\
		$(PATH_cam_os_wrapper)/pub
		
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
		halMIPIDsi.c\
		dsi_test.c