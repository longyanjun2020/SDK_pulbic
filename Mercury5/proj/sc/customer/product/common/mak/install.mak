#-------------------------------------------------------------------------------
#	List of files to copy to output directory
#-------------------------------------------------------------------------------
PATH_COPY =	\
		$(PATH_H)\
		$(PATH_C)\
		$(PATH_E2P)\
		$(PATH_EXT_LIB)

#-------------------------------------------------------------------------------
FILES_TO_COPY +=$(EXT_LIBS)\

#-------------------------------------------------------------------------------

ifeq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),)
FILES_TO_COPY +=\
    vm_sim_appli.hi\
    vm_cd_tlv.hc\
    sys_vm_trc_defs.hc
endif
#-------------------------------------------------------------------------------

ifeq ($(filter AEONGCC MIPSGCC X86LINUXGCC ARMGCC, $(COMPILER_VERSION)), )
FILES_TO_COPY += sig_ta.lib
endif
