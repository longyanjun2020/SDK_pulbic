#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_utopia_msos)/src\

PATH_H +=\
    $(PATH_MsWrapper)/pub\
    $(PATH_MsWrapper)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_mmio_hal)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    MsOS_rtk.c\
    drvMPool.c\

