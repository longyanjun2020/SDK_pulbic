#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# generate preprocess file (e.g. A.c --> A.o.pp)
#GEN_PREPROCESS = 1

# generate preprocess file (e.g. A.c --> A.o.asm)
#GEN_ASSEMBLY=1

PATH_I +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/pub

PATH_ASM +=\
  $(PATH_rtk)/src/arm

PATH_H +=\
  $(PATH_rtk)/inc\
  $(PATH_rtk)/itf\
  $(PATH_rtk)/itf_open\
  $(PATH_rtk)/tests/inc\
  $(PATH_lcd)/pub\
  $(PATH_sys)/inc

PATH_C +=\
  $(PATH_rtk)/src\

#-------------------------------------------------------------------------------
# if turn on __DIAG_ERROR__, build system would treat warning as error
# this is use to suppress the #66, 186 warning
#-------------------------------------------------------------------------------
ifeq ($(COMPILER_VERSION),RVCTV22)
C_OPTIONS+=--diag_suppress 66,186
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

A_OBJS = rtk2util.o

ifeq ($(COMPILER_VERSION),RVCTV22)
$(A_OBJS:%=$(OUT)%): AFLAGS += --diag_suppress 1581,1609
endif

ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
  abi_headers_rtk.c\
  rtk10tim.c\
  rtk7mem.c\
  rtk3init.c\
  rtk5task.c\
  rtk9que.c\
  rtk4env.c\
  rtk11utl.c\
  rtk6mbox.c\
  rtk8sem.c\
  rtktools.c \
  rtk_dynsem.c\
  rtk_flag.c\
  kmdynmem.c\
  msmem.c\
  ms_os_hmem.c\
  hmem_rtk7mem.c
else
SRC_C_LIST =\
  abi_headers_rtk.c\
  rtk10tim.c\
  rtk7mem.c\
  rtk3init.c\
  rtk5task.c\
  rtk9que.c\
  rtk4env.c\
  rtk11utl.c\
  rtk6mbox.c\
  rtk8sem.c\
  rtktools.c \
  rtk_dynsem.c\
  rtk_flag.c\
  kmdynmem.c\
  msmem.c\
  ms_os_hmem.c\
  hmem_rtk7mem.c\
  rtk_dummy.c
endif

ifeq ($(call FIND_COMPILER_OPTION, __RTK_OVER_R2__), TRUE)
SRC_ASM_LIST =\
  rtk2util.S
else ifeq ($(COMPILER_VERSION), RVCTV22)
SRC_ASM_LIST =\
  rtk2util.asm
else ifeq ($(COMPILER_VERSION), ARMGCC)
SRC_ASM_LIST =\
  rtk2util_arm.S
endif
