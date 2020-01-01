#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

AUDIO_MDL_DRV_INC +=\
  inc
PATH_C +=\
    $(PATH_audio_mdl)/src
    
PATH_H +=\
$(PATH_audio)/inc\
$(PATH_bluetooth)/pub\
$(PATH_acc_inc)/pub\
$(PATH_audio_drv)/pub\
$(PATH_gpd_mdl)/pub
#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
		abi_headers_audio_mdl.c \
        mdl_aud_at.c \
        mdl_aud_wav.c \
        mdl_aud_core.c \
        mdl_aud_parse.c \
        mdl_aud_api.c \
        mdl_aud_dma_api.c \
        mdl_aud_cp_api.c \
        ut_mdl_aud.c \
        em_audio_itf.c

PATH_H += $(addprefix $(PATH_audio_mdl)/, $(AUDIO_MDL_DRV_INC))
