

#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

ifeq ($(COMPILER_VERSION),RVCTV22)
C_OPTIONS += \
   -O3 -Otime --arm
else
C_OPTIONS += \
   -O2
endif

#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += $(PATH_stereo_image)/src

PATH_H += \
           $(PATH_image_codec)/pub\
           $(PATH_image_codec)/inc\
           $(PATH_gss)/pub\
           $(PATH_drm_vfs)/pub

SRC_C_LIST = \
           stereo_image_main.c

ifeq ($(filter __MDL_STEREO_IMAGE__ , $(PP_OPT_COMMON)), __MDL_STEREO_IMAGE__)
PP_OPT_COMMON += SUPPORT_STEREO_IMAGE
endif

