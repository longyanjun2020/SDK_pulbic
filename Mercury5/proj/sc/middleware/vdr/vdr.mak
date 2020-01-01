#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += VDR_SLDLM
endif
endif

PATH_C +=\
  $(PATH_vdr)/src
  
#ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
#PATH_C +=\
#  $(PATH_vdr)/src/vtmx
#PATH_H +=\
#  $(PATH_vdr)/inc/vtmx
#endif

PATH_H +=\
    $(PATH_dynscl)/pub\
    $(PATH_vdr)/pub\
    $(PATH_vdr)/inc/mx\
    $(PATH_arp_engine)/arp_mgr_shell/pub\
    $(PATH_camera_mdl)/pub\
    $(PATH_jpe)/pub\
    $(PATH_scl)/pub\
    $(PATH_vdr)/inc\
    $(PATH_vdr)/inc/cus

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
    abi_headers_vdr.c\
	mdl_vdr.c\
	mdl_vdr_ado_file.c\
	mdl_vdr_ado_mar.c\
	mdl_vdr_ado_dummy.c\
	mdl_vdr_biliner.c\
	mdl_vdr_mem.c\
	mdl_vdr_mux_14496_12.c\
	mdl_vdr_plugin.c\
	mdl_vdr_system.c\
	mdl_vdr_drv_jpe_fake.c\
	mdl_vdr_vdo_file.c\
	mdl_vdr_vdo_h263i.c\
	mdl_vdr_vdo_sw_h263i.c\
	mdl_vdr_vdo_utility.c

#ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
#SRC_C_LIST +=\
#	mdl_vdr_mux_videotelephony.c
#endif
