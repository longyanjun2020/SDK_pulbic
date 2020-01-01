
#------------------------------------------------------------------------------
#	Description	of	some variables	own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary	module (bin)

PROCESS		= lib

PATH_C +=\
	  $(PATH_kmxtt)/src
	  
PATH_H +=\
	  $(PATH_kmxtt)/inc\
	  $(PATH_SrvWrapper)/pub\
	  $(PATH_mae)/pub\
	  $(PATH_MsWrapper)/inc


#Add files here
ifeq ($(filter __MMI_KMX_TT__, $(PP_OPT_COMMON)), __MMI_KMX_TT__)
REL_SRC_C_LIST += tt_kmx_task.c
REL_SRC_C_LIST += HTTPClient.c
REL_SRC_C_LIST += HTTPClientAuth.c
REL_SRC_C_LIST += HTTPClientString.c
REL_SRC_C_LIST += HTTPClientWrapper.c

endif
 


