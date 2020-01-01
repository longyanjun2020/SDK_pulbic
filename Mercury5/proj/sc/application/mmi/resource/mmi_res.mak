#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

REL_SRC_C_LIST = \
	mae_menu_data.c

MMI_PATH_H += \
	$(PATH_mmi_res) \
	$(PATH_mmi_res)/resourceLib \
	$(PATH_widget)/inc


PATH_C =\
	$(PATH_mmi_res) \
	$(PATH_build) \
	$(PATH_mmi_res)/resourceLib
