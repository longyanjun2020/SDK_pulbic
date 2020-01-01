#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


PATH_H +=$(PATH_mpif_hal)/pub\
		 $(PATH_mpif_hal)/inc\
	     $(PATH_mpif)/pub\
         $(PATH_mpif)/inc

PATH_C +=$(PATH_mpif)/src


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =\
	drv_mpif.c \
	abi_headers_mpif.c


#------------------------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += mpif_test.c
endif




#