#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_gpd_mdl)/src

PATH_H +=\
    $(PATH_storage)/pub\
    $(PATH_storage_mdl)/pub\
    $(PATH_mtmgr)/pub\
    $(PATH_abb_mdl)/pub\
    $(PATH_tscr_mdl)/pub\
    $(PATH_keypad_mdl)/pub\
    $(PATH_gss)/pub\
    $(PATH_gsensor)/pub\
    $(PATH_tscr)/pub\
    $(PATH_batt)/pub\
    $(PATH_proximitysensor)/pub\
    $(PATH_gpd_mdl)/pub\
    $(PATH_gpd)/pub\
    $(PATH_gss)/pub\
    $(PATH_sddl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
  abi_headers_gpd_mdl.c \
  mdl_gpd.c \
  mdl_gsensor.c \
  mdl_proximity_sensor.c \
  mdl_gpd_parse.c \
  mdl_gpd_core.c \
  mdl_gpd_util.c
else
SRC_C_LIST = \
	 abi_headers_gpd_mdl.c \
  mdl_gpd.c \
  mdl_proximity_sensor.c \
  mdl_gpd_parse.c \
  mdl_gpd_core.c \
  mdl_gpd_util.c
endif
PATH_H+=$(PATH_gpd_mdl)/inc

