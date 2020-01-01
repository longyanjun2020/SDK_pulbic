#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_dma2d)/src
    
PATH_H +=\
$(PATH_gss)/pub\
$(PATH_dma2d)/pub\
$(PATH_dma2d_hal)/inc\
$(PATH_dma2d_hal)/pub\
$(PATH_scl_hal)/pub\
$(PATH_drvutil)/pub
#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    drv_dma2d.c


#-------------------------------------------------------------------------------
#	List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += dma2d_test.c\
              bitblt_test.c
endif

PATH_H+=$(PATH_dma2d_hal)/inc
PATH_H+=$(PATH_dma2d)/inc


