#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_fs)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_sf)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_storage)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_fc)/pub\
    $(PATH_sys)/pub\
    $(PATH_core_application_mmps_fs)/inc\
    $(PATH_core_application_mmpd_fs)/inc\
    $(PATH_spinand)/inc\
    $(PATH_ahc)/inc
    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_fs_api.c\
    mmpf_storage_api.c\
    NewCache.c\
    NewCacheMisc.c\
    mem_misc.c\
    r_misc.c\
    sd_misc.c\
    sd1_misc.c\
    SDCacheMisc.c\
    sf_misc.c\
    sm_misc.c\
    sn_misc.c\
    fs_test.c\

