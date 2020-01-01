#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
          	$(PATH_Pnl)/src\
		
PATH_H +=\
		$(PATH_Pnl)/inc\
		$(PATH_Pnl_hal)/inc\
		$(PATH_cam_os_wrapper)/pub\
        	$(PATH_core_driver_display)/inc\		
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
		drv_pnl.c \
		pnl_test.c