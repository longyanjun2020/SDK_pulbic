#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

NO_PLATFORM_INCLUDE = yes

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# for XML parser
SRC_C_LIST +=\
	xmlrole.c\
	xmltok.c\
	xmlparse.c

# for XML parser
MMI_PATH_H += \
	$(PATH_expat)/xmlparse\
	$(PATH_expat)/xmltok\
	$(PATH_map)/core/exFramework/fwBase/inc\
	$(PATH_sys)/itf\
	$(PATH_sys)/itf_open\
	$(PATH_trc)/inc\
	$(PATH_trc)/pub\
	$(PATH_rtk)/inc\
	$(PATH_rtk)/pub\
	$(PATH_rtk)/itf\
	$(PATH_rtk)/itf_open\
	$(PATH_fc)/pub\
 	$(PATH_fms)/inc/\
	$(PATH_fc)/pub \
 	$(PATH_kernel_hal)/inc \
	$(PATH_timer)/pub \
	$(PATH_timer_hal)/pub \
	$(PATH_int_hal)/inc \
 	 	 	 	
PATH_C =\
	$(PATH_expat)/xmlparse\
	$(PATH_expat)/xmltok


