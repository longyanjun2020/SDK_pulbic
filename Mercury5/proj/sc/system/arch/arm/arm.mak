#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
  $(PATH_arm)/pub\
  $(PATH_arm)/src/common\

ifeq ($(call FIND_COMPILER_OPTION, __CORTEX_A7__), TRUE)
  PATH_C += $(PATH_arm)/src/ca7
else
  PATH_C += $(PATH_arm)/src/arm926
endif


ifeq ($(call FIND_COMPILER_OPTION, __CORTEX_A7__), TRUE)
  PATH_ASM += $(PATH_arm)/src/ca7
else
  PATH_ASM += $(PATH_arm)/src/arm926
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

ifeq ($(call FIND_COMPILER_OPTION, __CORTEX_A7__), TRUE)
SRC_C_LIST =\
  arm_copro_v7.c

SRC_ASM_LIST =\
  arm_copro_s_v7.S
else
SRC_C_LIST =\
  arm_copro.c

SRC_ASM_LIST=\
  arm_copro_s.asm
endif

SRC_C_LIST +=\
  abi_headers_arm.c\
  arm_core.c

#-------------------------------------------------------------------------------
# Ignored by mak parser
#
# Additional configuration of arm.mak
#-------------------------------------------------------------------------------

ifeq ($(COMPILER_VERSION),X86LINUXGCC)
SRC_ASM_LIST =
endif

ifeq ($(COMPILER_VERSION),RVCTV22)

# the list specified the files to be compiled to arm mode
ARM_OBJS=$(SRC_C_LIST) $(SRC_ASM_LIST)
# keep this statement if ARM_OBJS is not null
$(ARM_OBJS:%.c=$(OUT)%.o) $(ARM_OBJS:%.cpp=$(OUT)%.o) $(ARM_OBJS:%.asm=$(OUT)%.o):C_OPTIONS += --arm

endif

