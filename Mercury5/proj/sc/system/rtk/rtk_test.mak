#   Ignored by mak parser
#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_I +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/pub

PATH_ASM +=\
    $(PATH_rtk)/src/arm

PATH_H +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/itf\
  $(PATH_rtk)/itf_open
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =	  \
  testRtk10tim.c  \
  testRtkDynSem.c \
  testRtk.c       \
  rtk10tim.c  \
  rtk7mem.c   \
  rtk3init.c  \
  rtk5task.c  \
  rtk9que.c   \
  rtk4env.c   \
  rtk11utl.c  \
  rtk6mbox.c  \
  rtk8sem.c   \
  rtkgo.c     \
  rtktools.c  \
  rtk_dynsem.c\
  rtk_backtrace.c

ifeq ($(call FIND_COMPILER_OPTION, __RTK_OVER_R2__), TRUE)
SRC_ASM_LIST =\
  rtk2util.S
else # __RTK_OVER_R2__
SRC_ASM_LIST =\
  rtk2util.asm
endif

