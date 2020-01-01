#------------------------------------------------------------------------------
#   List of source  files   of  the library or  executable to generate
#------------------------------------------------------------------------------

PATH_H +=\
$(PATH_lcd)/pub\
$(PATH_gpd_mdl)/pub

ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =    \
	cus_tmt.c \
	cus_wtest_gps.c\
	cus_wtest_pvw.c\
	dev_imgdec.c
else
SRC_C_LIST =    \
	cus_tmt.c \
	cus_wtest_gps.c\
	cus_wtest_pvw.c\
	dev_imgdec.c\
	cus_dummy.c
endif