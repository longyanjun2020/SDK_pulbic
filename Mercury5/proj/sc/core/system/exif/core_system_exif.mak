#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_system_exif)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_project_Dvr_CarDV_SDK_cfg_fs)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_lib_gui_inc_Core)\
    $(PATH_core_lib_fs)/inc\
    $(PATH_core_lib_gui)/inc\Core\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_system_dsc)/inc\
    $(PATH_core_system_fs)/inc\
    $(PATH_core_system_exif)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_exif.c\

