
#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_sys_hal)/src
  
PATH_H +=\
    $(PATH_hal)\
    $(PATH_sys_hal)/inc\
    $(PATH_sys_drv)/inc\
    $(PATH_mmio)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_vdec)/inc\
	
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    halSYS.c\
    halDMD_VD_MBX.c\

