#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_tv_mdl)/src
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
  abi_headers_tv_mdl.c\
  Mdl_tv_api.c\
  Mdl_tv_handle.c
  
    
#ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_atv_pub)
#endif    
  
PATH_H +=\
  $(PATH_camera_mdl)/pub\
  $(PATH_gss)/pub\
  $(PATH_avp)/pub\
  $(PATH_tv_mdl)/pub\
  $(PATH_drv)/scl/pub\
  $(PATH_dynldr)/pub\
  $(PATH_mmaudio)/pub\
  $(PATH_tv_mdl)/inc