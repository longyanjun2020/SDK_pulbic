#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmpd_display)/src\

PATH_H +=\
	$(PATH_core_application_mmpd_display)/inc\
	$(PATH_core_application_mmpd_system)/inc\
	$(PATH_core_application_mmpd_img_pipe)/inc\
	$(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
	$(PATH_core_driver_common)/inc\
	$(PATH_core_driver_display)/inc\
	$(PATH_core_driver_ccir)/inc\
	$(PATH_core_application_mmph)/inc\
	$(PATH_core_include_img_pipe)\
	$(PATH_core_include_display)\
	$(PATH_core_system_host_if)/inc\
	$(PATH_core_driver_timer)/inc\
	$(PATH_core_driver_bsp)/inc\
	$(PATH_core_include_application)\
	$(PATH_core_include_misc)\
	$(PATH_core_driver_img_pipe)/inc\
        
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
		mmpd_ccir.c\
		mmpd_hdmi.c\
		mmpd_tv.c