#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C += $(PATH_wlan_cus)/cus
PATH_H += $(PATH_supplicant)/inc

ifeq ($(call FIND_COMPILER_OPTION, __MPIF_HAL__), TRUE)
PATH_H +=$(PATH_mpif_hal)/pub\
	     $(PATH_mpif)/pub\
	     $(PATH_gpd_mdl)/pub
endif
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
    wlan_heap.c \
    wlan_queue.c \
    wlan_if.c \
    wlan_main.c

