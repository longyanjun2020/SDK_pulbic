#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_hvd)/src\

PATH_H += \
    $(PATH_hal)\
    $(PATH_hvd_hal)/inc\
    $(PATH_hvd)/inc\
    $(PATH_mmio)/inc\
    $(PATH_vpu_hal)/inc\
    $(PATH_utopia_common)/inc\
    $(PATH_utopia_chip)/inc\
    $(PATH_utopia_msos)/inc\
    $(PATH_utopia_vdec)/inc\
    
SRC_C_LIST = \
    drvHVD.c\
    drvHVD_sub.c\
    HVD_Common.c\
    osalHVD.c

#------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
    #SRC_C_LIST += hvd_test.c
endif

