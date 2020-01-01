#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
	$(PATH_vt_mm)/src

PATH_H += \
	$(PATH_middleware)/avp/pub \
	$(PATH_mmaudio)/swmixer/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
SRC_C_LIST +=\
	mdl_vt.c \
	mdl_vt_state.c \
	mdl_vt_state_handler.c \
	mdl_vt_media_itf.c \
	mdl_vt_common.c \
	mdl_vt_rec_mux.c \
	mdl_vt_rec_aud_enc.c
else
SRC_C_LIST +=\
	mdl_vt_fake.c
endif
