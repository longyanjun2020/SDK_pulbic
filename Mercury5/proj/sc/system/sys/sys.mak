#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# path to C source files
PATH_C +=\
  $(PATH_trc)/src\
  $(PATH_sys)/src

PATH_I +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
  $(PATH_sys)/pub
    
PATH_ASM +=\
  $(PATH_sys)/src

PATH_H +=\
  $(PATH_arm)/pub\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
  $(PATH_sys)/itf_open\
  $(PATH_rtk)/inc\
  $(PATH_emi)/pub\
  $(PATH_compression_mdl)/pub\
  $(PATH_timer_hal)/pub\
  $(PATH_rtc)/pub\
  $(PATH_3rd)/utility/zlib/inc\
  $(PATH_cpu_mdl)/pub\
  $(PATH_acc)/pub
# path to C source files in "opxc" directories
PATH_C +=\
  $(PATH_sys)/opxc


#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
  abi_headers_sys.c\
  watch.c\
  traces.c\
  sys_sig.c\
  sys_cali.c\
  sys_ngos.c\
  sys_ftr.c\
  sys_tools.c\
  sys_rand.c\
  tasks.c\
  sys_reset.c\
  sys_speed_profile.c \
  sys_power_mngt.c \
  sys_math.c	\
  sys_chip.c \
  sys_queue.c \
  opec_std.c\
  opec_printf.c\
  opec_sys.c \
  sys_profiling.c \
  sys_cpu.c \
  sys_ram.c
else
SRC_C_LIST =\
  abi_headers_sys.c\
  watch.c\
  traces.c\
  sys_sig.c\
  sys_cali.c\
  sys_ngos.c\
  sys_ftr.c\
  sys_tools.c\
  sys_rand.c\
  tasks.c\
  sys_reset.c\
  sys_speed_profile.c \
  sys_power_mngt.c \
  sys_math.c	\
  sys_chip.c \
  sys_queue.c \
  opec_std.c\
  opec_printf.c\
  opec_sys.c \
  sys_profiling.c \
  sys_cpu.c \
  sys_dummy.c \
  sys_ram.c
endif

ifneq ($(filter __NO_GPRS__ ,$(PP_OPT_COMMON)),__NO_GPRS__)
SRC_C_LIST +=\
  sys_fcs.c
endif

ifeq ($(BB_CHIP_ID),msw8533x)
SRC_C_LIST +=\
  sys_core.c\
  sys_virtual_mem.c\
  sys_sleep_b3_a.c
SRC_ASM_LIST =\
  sys_kereset.asm\
  sys_abort.asm\
  fms_perf_asm.asm
endif

ifeq ($(BB_CHIP_ID),msw8533d)
SRC_C_LIST +=\
  sys_core.c\
  sys_virtual_mem.c\
  sys_sleep_b3_a.c
SRC_ASM_LIST =\
  sys_kereset.asm\
  sys_abort.asm\
  fms_perf_asm.asm
endif

ifeq ($(BB_CHIP_ID),msw853xb)
SRC_C_LIST +=\
  sys_core.c\
  sys_virtual_mem.c\
  sys_sleep_b3_a.c
SRC_ASM_LIST =\
  sys_kereset.asm\
  sys_abort.asm\
  fms_perf_asm.asm
endif

ifeq ($(BB_CHIP_ID),msw8556x)
SRC_C_LIST +=\
  sys_core.c\
  sys_virtual_mem.c\
  sys_sleep_b3_a.c
SRC_ASM_LIST =\
  sys_kereset.asm\
  sys_abort.asm\
  fms_perf_asm.asm
endif

ifeq ($(BB_CHIP_ID),msw8573)
SRC_C_LIST +=\
  sys_core.c\
  sys_virtual_mem.c\
  sys_sleep_b3_a.c
SRC_ASM_LIST =\
  sys_kereset.asm\
  sys_abort.asm\
  fms_perf_asm.asm
endif

ifeq ($(BB_CHIP_ID),msw8830x)
SRC_C_LIST +=\
  sys_r2.c\
  sys_sleep_g1.c\
  sys_g1_gdb_rsp.c\
  sys_g1_gdb_r2.c
endif

ifeq ($(COMPILER_VERSION),X86LINUXGCC)
SRC_ASM_LIST =
endif
#-------------------------------------------------------------------------------
#	List of EEPROM file
#-------------------------------------------------------------------------------
E2P_LIST_FOR_W_E2P_STACK =\
  stack.e2p
