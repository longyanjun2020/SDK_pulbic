#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

include $(PATH_mmaudio_common)/mmaudio_platform.mak

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/midilib/src/ 
 
# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/midilib/inc/\
$(PATH_app_engine)/app_mgr_shell/pub\
$(PATH_mmaudio)/sbcenc/inc\
$(PATH_mmaudio)/src_converter/inc\
$(PATH_drm_vfs)/pub


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
 

SRC_C_LIST +=\
  alloc.c \
  APP.c \
  bzero.c \
  defWDAT.c \
  defWPRM.c \
  DEVICE.c \
  DRIVER.c \
  faithAPI.c \
  lock.c \
  smf_seq.c \
  SYNTH.c \
  SYNTH_c.c \
  SynthAPI.c \
  SynthDRV.c \
  synthWrapper.c \
  VOICE.c \
  WPRM.c \
  midi_c_new.c

ifeq ($(COMPILER_VERSION), RVCTV22)
SRC_ASM_LIST +=\
  SYNTH_arm.asm
endif

GEN_PREPROCESS = 1
