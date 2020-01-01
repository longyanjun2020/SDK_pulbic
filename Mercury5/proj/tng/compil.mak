TARGET_MAK=$(PATH_$(TARGET))/$(TARGET)$(FLAVOR_$(TARGET)).mak
# -- Modification for project DUO
# The steering file used to rename all exported symbols in a specified SW module.
#
DUP_STR=$(TNG)duplicate.str

# $(call update_if_necessary,target,source,cmd)
# exec cmd if
#  1.target is older than source file
#  2.target not exist
define update_if_necessary
	if [ ! -e $1 -o $1 -ot $2 ] ; then \
		$3; \
	fi
endef

# $(call do_if_order,file list,source,cmd;)
# exec cmd if any file in the file list is older than source file
# source should already exist !
# note that a ';'  should be added to the end of 'cmd'
define do_if_order
	if [ -e $2 ] ; then \
		for file in $1 ; do \
			if [ -e $$file -a $$file -ot $2 ] ; then \
				echo -e "do_if_order: exec $3 because $$file is order than $2"; \
				$3 \
			fi; \
		done \
	else \
			echo -e "fo_if_order: $2 not exist"; \
			exit 1; \
	fi
endef

#-------------------------------------------------------------------------------
#                  File definition
#-------------------------------------------------------------------------------
RELEASE_MAK=$(COMMON)release_mak/
COMMON_PRODUCT_MAK = $(COMMON)final_product.mak
COMMON_OPTIONS_MAK=$(COMMON)common_option.mak
OPTIONS_CUS_MAK=$(if $(wildcard $(MAK)options_$(PRODUCT).mak),$(MAK)options_$(PRODUCT).mak,\
				$(if $(wildcard $(MAK)Eng/options_$(PRODUCT).mak),$(MAK)Eng/options_$(PRODUCT).mak,\
				$(error options_$(PRODUCT).mak does not exist in $(MAK) and $(MAK)Eng/)))
TRACE_TABLE=$(TNG)remtrace/remtraceID
LIST_MODULE_MAK=$(BUILD)$(PRODUCT)module_mak_checking_list.lst
MODULE_MAK_CHECKING_LIST=$(if $(filter 1, $(FILE_CHECK)), $(ALL_MODULE_MAK))
COMPILER_OPTION_MAK=$(COMMON)compiler_option.mak

include $(COMMON_OPTIONS_MAK)
ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
PATHS_MAK=$(COMMON)lib_paths_g1.mak
else
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
ifeq ($(filter __ISW_INFINITY__ ,$(PP_OPT_COMMON)),__ISW_INFINITY__)
PATHS_MAK=$(COMMON)lib_paths_i_sw_infinity.mak
else
PATHS_MAK=$(COMMON)lib_paths_i_sw.mak
endif
else
ifeq ($(filter __CORE_SOFTWARE__ ,$(PP_OPT_COMMON)),__CORE_SOFTWARE__)
PATHS_MAK=$(COMMON)lib_paths_core_sw.mak
else
PATHS_MAK=$(COMMON)lib_paths.mak
endif
endif
endif
_PATHS_MAK=$(COMMON)paths.mak
PATHS_PUB=$(COMMON)paths_pub.mak
EXT_LIBS_MAK=$(COMMON)ext_libs.mak
include $(PATHS_MAK) $(EXT_LIBS_MAK)

ifeq ($(RELEASE_PROCESS),1)
FOR_RELEASE_OPTION_MAK = $(COMMON)for_release_options.mak
include $(FOR_RELEASE_OPTION_MAK)
endif


# for prepare build/quick build
MAKE_PREPARE_FILE=$(MAKE) -r -f $(PATH_common_mak)normal_mak/prepare_file.mak
MAKE_RESTORE_FILE=$(MAKE) -r -f $(PATH_common_mak)normal_mak/restore_file.mak

# for smart lint
UPDATED_LIB_LST=$(OUT)updated_lib_list.txt

# the lst decides pure lib
SC_LIB_LIST= $(PATH_pure_lib_lst)$(PRODUCT)_pure_lib_list.mak
NON_CT_LIST= $(RELEASE_MAK)non_critical_trace_list.mak
COMMON_LIB_LIST_FILE := $(RELEASE_MAK)common_lib_list.mak
include $(NON_CT_LIST) $(COMMON_LIB_LIST_FILE)

NON_CMPR_OBJ_LIST_MAK=$(OUT)list_obj.mak

#-------------------------------------------------------------------------------
# Make Commands and Variable Setting
#-------------------------------------------------------------------------------
#NUM_THREAD_FOR_IBUILD_OUTER_FORK=5

### parallel build default parameters for normal build
# set default NUM_THREAD to 2*NUMBER_OF_PROCESSORS+1 if it's not set before
#
#if user doesn't specify the thread number,
#for local build, NUM_THREAD=2*$NUMBER_OF_PROCESSORS+1 if fast is enabled
#for ibuild, NUM_THREAD=16

NUM_THREAD ?= $(if $(filter 1,$(IBUILD)),$(if $(filter 1,$(FAST)),$$(($$NUMBER_OF_PROCESSORS+1)),$$((2*$$NUMBER_OF_PROCESSORS))),$$(($$NUMBER_OF_PROCESSORS+1)))

NUM_THREAD_FOR_IBUILD_INNER_FORK := $$(($(NUM_THREAD)/3+1))

ifndef NUM_THREAD_FOR_TPP
NUM_THREAD_FOR_TPP=10
endif
MAKE_ALLTPP=$(MAKE) -j$(NUM_THREAD_FOR_TPP) -r -f $(TNG)genalltpp.mak
MAKE_GEN_REMTRACE=$(MAKE) -j1 -f $(TNG)lib.mak GEN_REMTRACE=1
MAKE_ONLY_TPP=$(MAKE) -r -f $(TNG)lib.mak GENTPPONLY=1

# for parallel rtpp
NUM_THREAD_FOR_RTPP=1

###

### parallel build default parameters for release build
REL_NUM_THREAD=3
REL_NUM_THREAD_FOR_TPP=10
REL_MAKE_ALLTPP=$(MAKE) -j$(REL_NUM_THREAD_FOR_TPP) -r -f $(TNG)genalltpp.mak
REL_MAKE_GEN_REMTRACE=$(MAKE) -j1 -r -f $(RELEASE_MAK)rellib.mak GEN_REMTRACE=1
REL_MAKE_ONLY_TPP=$(MAKE) -r -f $(RELEASE_MAK)rellib.mak GENTPPONLY=1
###

ifeq ($(RELEASE_PROCESS),1)
MAKE_LIB=$(MAKE) -j$(REL_NUM_THREAD) -r -f $(RELEASE_MAK)rellib.mak
else
MAKE_LIB=$(MAKE) -j$(NUM_THREAD) -r -f $(TNG)lib.mak
endif

COPY_SOURCE_CODE_LIB=$(MAKE) -r -s -f $(RELEASE_MAK)gen_lib_sc_group_for_release.mak
GEN_SOURCE_CODE_LIB=$(MAKE) -r -s -f $(RELEASE_MAK)gen_lib_sc_group_for_release.mak NO_COPY=1
ifeq ($(GLOBAL_HEADER),TRUE)
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
GLOBAL_HEADER_FILE:=$(PATH_global_header_file)global_config_$(PRODUCT).h
else
GLOBAL_HEADER_FILE:=$(PATH_global_header_file)global_config.h
endif
GLOBAL_HEADER_DEFINE:=$(strip $(shell $(TNG)define_parser.pl $(GLOBAL_HEADER_FILE)))
endif

MAKE_DSP_PATCH=$(MAKE) -r -f $(TNG)dsp_patch.mak
MAKE_LINK_DPM=$(MAKE) -r -f $(TNG)link_dpm.mak
MAKE_SLDLM_CUS=$(MAKE) -r -f $(TNG)sldlm_cus.mak
MAKE_DPM_CUS=$(MAKE) -r -f $(TNG)dpm_cus.mak
MAKE_DLM_PRE=$(MAKE) -r -f $(TNG)dlm_pre.mak
MAKE_DLM_BIN=$(MAKE) -r -f $(TNG)dlm_bin.mak
MAKE_DLM_GEN=$(MAKE) -r -f $(TNG)dlm_gen.mak
MAKE_DLM_BLD=$(MAKE) -r -f $(TNG)dlm_bld.mak
MAKE_EML_BIN=$(MAKE) -r -f $(TNG)eml/eml_bin.mak
MAKE_EML_GEN_DLM=$(MAKE) -r -f $(TNG)eml/eml_gen_dlm.mak
MAKE_EML_GEN_BIN=$(MAKE) -r -f $(TNG)eml/eml_gen_bin.mak
MAKE_EML_BLD=$(MAKE) -r -f $(TNG)eml/eml_bld.mak
MAKE_PREPROCESS_SCATTER=$(MAKE) -j5 -r -f $(DIR_BUILD_POST)link/preprocess_scatter.mak
STUBGEN=$(BIN)StubGen
VENEERGEN=$(BIN)VeneerGen
DLMIZE=$(BIN)Dlmize
DLMCUS=$(BIN)DlmCus
EMLIZE=$(BIN)Emlize

MAKE_CSN=$(MAKE) -r -f $(TNG)csn.mak
MAKE_ID=$(MAKE) -r -f $(TNG)id.mak
MAKE_DFN=$(MAKE) -r -f $(TNG)dfn.mak
MAKE_TPP=$(MAKE) -r -f $(TNG)tpp.mak
MAKE_STACK2=$(MAKE) -r -f $(TNG)stack2.mak
MAKE_INSTALL=$(MAKE) -r -f $(TNG)install.mak
MAKE_LINK=$(MAKE) -r -f $(TNG)link.mak
MAKE_E2P=$(MAKE) -r -f $(TNG)e2p.mak
MAKE_TMT=$(MAKE) -r -f $(TNG)tmt.mak
MAKE_MSG=$(MAKE) -r -f $(DIR_BUILD_POST)tmt/msg.mak
MAKE_E2PCE=$(MAKE) -r -f $(TNG)e2pce.mak
MAKE_TSK_PRIO=$(MAKE) -r -f $(DIR_BUILD_PRE)tsk_prio/tsk_prio_gen.mak TARGET=tsk_prio PATH_tsk_prio=$(DIR_BUILD_PRE)tsk_prio/
MAKE_HELP_COMMON=$(DIR_BUILD_UTILITY)help/make_help_common.mak
MAKE_HELP_NORMAL=$(DIR_BUILD_UTILITY)help/make_help_normal.mak
MAKE_HELP_RELEASE=$(DIR_BUILD_UTILITY)help/make_help_release.mak

LEX=$(BIN)flex
LEX_OPT=--nounistd -L
YACC=$(BIN)bison
YACC_OPT=-d -y -l
MAKE_PARSER=$(MAKE) -r -f $(TNG)atparser.mak

#-------------------------------------------------------------------------------
# For NAND Platform, Binary Image has to transfer to Partition Image.
#-------------------------------------------------------------------------------
ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
MAKE_NAND=$(MAKE) -r -f $(TNG)nandprt_g1.mak
else
MAKE_NAND=$(MAKE) -r -f $(TNG)nandprt_b3.mak
endif

#-------------------------------------------------------------------------------
# For SD Card Download
#-------------------------------------------------------------------------------
MAKE_SDTARGET=$(MAKE) -r -f $(TNG)sdtarget.mak

#----------------------------------------------------
#                  Technical Support
#----------------------------------------------------

#
# for armcc option
#
ifeq (RVCTV22,$(COMPILER_VERSION))
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
feedback_server_backup=$(PATH_feedback)fb.txt
feedback_server=$(PATH_feedback)fb_$(PRODUCT).txt
feedback_out=$(BUILD)$(PRODUCT)/fb_$(PRODUCT).txt
else
feedback_server=$(PATH_feedback)fb.txt
feedback_out=$(BUILD)$(PRODUCT)/fb.txt
endif
FEEDBACK_OPTION = $(if $(filter 1, $(DISABLE_FEEDBACK)), ,--feedback $(feedback_out))
endif

#
# for build process to distribute ARM/THUMB mode
#
SHOW_COMPILER_MODE=$(if $(filter $(notdir $(basename $@)), $(ARM_LIB_LIST)), "(arm mode)")
COMPILER_CMD=$(if $(filter $(notdir $(basename $@)), $(ARM_LIB_LIST)), COMPILER=$(COMPILER_ARM), COMPILER=$(COMPILER_THUMB))

# $(call critical-trace-option, lib)
#  return 1 if
#  1. enable LOG_LEVEL_CUT_OPTION to LOG_LEVEL_CRITICAL_ONLY in opt_<product>.mak
#  2. in normal build
#     or in release build with the library not defined in NON_CRITICAL_TRACE_LIST set
#  else, return 0
critical-trace-option=$(if $(filter LOG_LEVEL_CRITICAL_ONLY,$(LOG_LEVEL_CUT_OPTION)),$(if $(filter 0,$(RELEASE_PROCESS)),1,$(if $(filter-out $(NON_CRITICAL_TRACE_LIST),$(1)),1)))

#
# for build system to disable feedback options
#
SHOW_FEEDBACK_OPTION=$(if $(filter $(notdir $(basename $@)), $(UT_LIB_LIST)), "(without feedback) (disable autoinline)")
UT_CMD=$(if $(filter $(notdir $(basename $@)), $(UT_LIB_LIST)), DISABLE_FEEDBACK=1)

CT_CMD = $(if $(call critical-trace-option,$(notdir $(basename $@))),CRITICAL_TRACE_OPTION=1)

#
# for parasoft
#
CPPTESTSCAN=cpptestscan


#-------------------------------------------------------------------------------
#                  compiler & linker
#-------------------------------------------------------------------------------
ifeq ($(COMPILER_VERSION),AEONGCC)
MAKEDEP=$(BIN)makedepend
PLTM_CC   = aeon-elf-gcc
PLTM_AS   = aeon-elf-gcc -xassembler-with-cpp
PLTM_AR   = aeon-elf-ar
PLTM_ELF  = aeon-elf-objdump
PLTM_LINK = aeon-elf-gcc
PLTM_OBJDUMP = aeon-elf-objdump
PLTM_OBJCOPY = aeon-elf-objcopy
PLTM_RANLIB = aeon-elf-ranlib
PLTM_NM 	= aeon-elf-nm
PLTM_READELF= aeon-elf-readelf
else ifeq ($(COMPILER_VERSION),MIPSGCC)
MAKEDEP=$(BIN)makedepend
PLTM_CC   = mips-sde-elf-gcc
PLTM_AS   = mips-sde-elf-gcc -xassembler-with-cpp
PLTM_AR   = mips-sde-elf-ar
PLTM_ELF  = mips-sde-elf-objdump
PLTM_LINK = mips-sde-elf-gcc
PLTM_OBJDUMP = mips-sde-elf-objdump
PLTM_OBJCOPY = mips-sde-elf-objcopy
PLTM_RANLIB = mips-sde-elf-ranlib
PLTM_NM 	= mips-sde-elf-nm
PLTM_READELF= mips-sde-elf-readelf
else ifeq ($(COMPILER_VERSION),X86LINUXGCC)
MAKEDEP=$(BIN)makedepend
PLTM_CC   = i686-unknown-linux-gnu-gcc
PLTM_AS   = i686-unknown-linux-gnu-gcc -xassembler-with-cpp
PLTM_AR   = i686-unknown-linux-gnu-ar
PLTM_ELF  = i686-unknown-linux-gnu-objdump
PLTM_LINK = i686-unknown-linux-gnu-gcc
PLTM_OBJDUMP = i686-unknown-linux-gnu-objdump
PLTM_OBJCOPY = i686-unknown-linux-gnu-objcopy
PLTM_RANLIB = i686-unknown-linux-gnu-ranlib
PLTM_NM 	= i686-unknown-linux-gnu-nm
PLTM_READELF= i686-unknown-linux-gnu-readelf

else ifeq ($(COMPILER_VERSION),ARMGCC)

MAKEDEP=$(BIN)makedepend
ifeq ($(COMPILER_EXECUTABLE),arm-linux-gnueabihf-gcc)
PLTM_CC   = $(CCACHE) arm-linux-gnueabihf-gcc
PLTM_CPP   = $(CCACHE) arm-linux-gnueabihf-cpp
PLTM_AS   = $(CCACHE) arm-linux-gnueabihf-gcc -xassembler-with-cpp
PLTM_AR   = arm-linux-gnueabihf-ar
PLTM_ELF  = arm-linux-gnueabihf-objdump
PLTM_LINK = arm-linux-gnueabihf-gcc
PLTM_OBJDUMP = arm-linux-gnueabihf-objdump
PLTM_OBJCOPY = arm-linux-gnueabihf-objcopy
PLTM_RANLIB = arm-linux-gnueabihf-ranlib
PLTM_NM 	= arm-linux-gnueabihf-nm
PLTM_READELF = arm-linux-gnueabihf-readelf
else
PLTM_CC   = $(CCACHE) arm-none-eabi-gcc
PLTM_CPP   = $(CCACHE) arm-none-eabi-cpp
PLTM_AS   = $(CCACHE) arm-none-eabi-gcc -xassembler-with-cpp
PLTM_AR   = arm-none-eabi-ar
PLTM_ELF  = arm-none-eabi-objdump
PLTM_LINK = arm-none-eabi-gcc
PLTM_OBJDUMP = arm-none-eabi-objdump
PLTM_OBJCOPY = arm-none-eabi-objcopy
PLTM_RANLIB = arm-none-eabi-ranlib
PLTM_NM 	= arm-none-eabi-nm
PLTM_READELF = arm-none-eabi-readelf
endif

else
MAKEDEP=$(BIN)makedepend
PLTM_CC = $${ARMCONF}/armcc $(FEEDBACK_OPTION)
PLTM_THUMB_CC = $${ARMCONF}/tcc
PLTM_AS = $${ARMCONF}/armasm
PLTM_AR = $${ARMCONF}/armar
PLTM_ELF = $${ARMCONF}/fromelf
PLTM_LINK = $${ARMCONF}/armlink
endif

ifeq "$(CTS)" "1"
PLTM_CC   := $(CPPTESTSCAN) $(PLTM_CC)
#PLTM_CC   := $(CPPTESTSCAN) --cpptestscanOutputFile=$(TOP)$(PRODUCT)_parasoftRepost.bdf  $(PLTM_CC)
PLTM_LINK := $(CPPTESTSCAN) $(PLTM_LINK)
endif



#-------------------------------------------------------------------------------
# DFLAGS:   collact compiler option PP_OPT_TARGET+PP_OPT_COMMON for all lib
# IFLAGS:    include path
# CFLAGS:   collect all compiler option to feed to compiler
#-------------------------------------------------------------------------------
ifeq ($(GLOBAL_HEADER),TRUE)
DFLAGS=$(PP_OPT_TARGET:%=-D%) $(PP_OPT_COMMON:%=-D%) $(GLOBAL_HEADER_DEFINE:%=-D%)
else
DFLAGS=$(PP_OPT_TARGET:%=-D%) $(PP_OPT_COMMON:%=-D%)
endif

DFLAGS2=$(PP_OPT_DUO:%=-D%)
IFLAGS=$(PATH_H:%=-I%)
CFLAGS=$(C_OPTIONS) $(DFLAGS)
CXXFLAGS=$(CXX_OPTIONS)
