#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C += $(PATH_wlan)/src
PATH_H += $(PATH_supplicant)/inc

ifeq ($(call FIND_COMPILER_OPTION, __MPIF_HAL__), TRUE)
PATH_H +=$(PATH_mpif_hal)/pub\
	     $(PATH_mpif)/pub
endif
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_wlan.c \
    wlan_pif.c \
    aquarius_image.c

