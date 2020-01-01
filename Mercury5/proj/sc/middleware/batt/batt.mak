#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PATH_C +=\
    $(PATH_batt)/src\
    $(PATH_batt)/opxc


PATH_H +=\
$(PATH_batt)/inc\
$(PATH_adc)/pub\
$(PATH_abb_mdl)/pub\
$(PATH_batt)/pub\
$(PATH_gpd_mdl)/pub

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_batt_mdl.c \
    bat_pars.c \
	opec_bat.c\
    ut_mdl_bat.c


