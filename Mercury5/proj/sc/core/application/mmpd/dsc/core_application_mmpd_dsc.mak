#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_application_mmpd_dsc)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_application_mmpd_dsc)/inc\
    $(PATH_core_application_mmph)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_misc)\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_exif)/inc\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_utility)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpd_dsc.c\

