

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

PATH_H +=

SRC_C_LIST = \
           stereo_image.c \
           stereo_image_version.c

