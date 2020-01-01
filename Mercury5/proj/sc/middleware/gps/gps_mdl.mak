#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_gps_mdl)/src

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PATH_H += $(PATH_gps)/pub

#PATH_H +=\
#    $(PATH_gps)/PLATFORM/Common/inc\
#    $(PATH_gps)/PLATFORM/RTK/inc

endif

PATH_H += $(PATH_gps_mdl)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
	mdl_gps.c   \
	abi_headers_gps_mdl.c

