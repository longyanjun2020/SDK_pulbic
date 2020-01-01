
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
    $(PATH_sys_drv)/src

PATH_H +=\
    $(PATH_sys_drv)/inc\
    $(PATH_sys_hal)/inc\
    $(PATH_mmio)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_vdec)/inc\
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
    drvSYS.c \
    drvDMD_VD_MBX.c \


#-------------------------------------------------------------------------------
#   List of source files of verification to generate
#-------------------------------------------------------------------------------
#ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
#SRC_C_LIST += sys_test.c
#endif

