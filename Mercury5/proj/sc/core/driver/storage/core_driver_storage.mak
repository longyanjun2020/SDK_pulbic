#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_storage)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg)/fs/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_storage)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_kernel_hal)/inc\
	$(PATH_flash)/pub\
	$(PATH_ms_sdmmc)/inc\
	$(PATH_fc)/pub\
	$(PATH_core_system_fs)/inc\
	$(PATH_core_lib_fs)/inc\
	$(PATH_core_lib_gui)/inc/Core
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_sd.c\
    mmpf_sf.c\
    mmpf_sfnand.c\
    mmpf_nand.c\
    sd_test.c\

