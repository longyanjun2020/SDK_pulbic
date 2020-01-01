#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PP_OPT_COMMON += IMGCODEC_SDK_FAKE_BUFFSIZE_WORKAROUND

ifeq ($(filter __SMALL_ROM_32__ ,$(PP_OPT_COMMON)),__SMALL_ROM_32__)
PP_OPT_COMMON += IMGCODEC_SMALL_ROM_32
endif

ifeq ($(filter __NO_HW_JPD__ ,$(PP_OPT_COMMON)),__NO_HW_JPD__)
PP_OPT_COMMON += IMGCODEC_USE_BRAVO_SCL
else
PP_OPT_COMMON += IMGCODEC_USE_HW_JPD
endif

PATH_H += \
            $(PATH_image_codec)/inc\
            $(PATH_image_codec)/pub\
            $(PATH_gss)/pub\
            $(PATH_scl)/pub\
            $(PATH_drm_vfs)/pub

PATH_C += \
            $(PATH_image_codec)/src

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST = \
  imgcodec_dispatch.c \
  imgcodec_color_dispatch.c \
  imgcodec_jpg_dispatch.c \
  imgcodec_mjpd_dispatch.c \
  imgcodec_png_dispatch.c \
  Mdl_imgdecode_handle.c
