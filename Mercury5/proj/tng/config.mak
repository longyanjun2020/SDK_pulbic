
BIN:=$(TNG)$(OSTYPE)/
BUILD:=$(TOP)build/

# -- Modification for project DUO
# JY: workspace for duplicated SW modules. Activities including compiling,
#     dependency generating, rtpp preprocessing, archive (partial link) should
#     happen in this directory.
#
OUT_ORG:=$(BUILD)$(PRODUCT)/out/
TMP_ORG:=$(OUT_ORG)
INC_ORG:=$(OUT_ORG)
OUT_DUP:=$(BUILD)$(PRODUCT)/out/dup/
TMP_DUP:=$(OUT_DUP)
INC_DUP:=$(OUT_DUP)

#-------------------------------------------------------------------------------
# current workspace
#-------------------------------------------------------------------------------
ifeq ($(DUP_FLAG),1)
OUT:=$(OUT_DUP)
OUT_ARM:=$(OUT_ORG)
TMP:=$(TMP_DUP)
INC:=$(INC_DUP)
else
OUT:=$(OUT_ORG)
OUT_ARM:=$(OUT_ORG)
TMP:=$(TMP_ORG)
INC:=$(INC_ORG)
endif
# -- End of modification for project DUO



#-------------------------------------------------------------------------------
# for DLM
#-------------------------------------------------------------------------------
OUT_DLM=$(OUT)dlm/
OUT_EML=$(OUT_DLM)eml/


#-------------------------------------------------------------------------------
# for prepare/quick/
#-------------------------------------------------------------------------------
ifdef PREPARE
LIBS_DIR_FOR_QUICK=$(TOP)libs/$(PRODUCT)_prepare/
else
LIBS_DIR_FOR_QUICK=$(TOP)libs/$(QUICK)/$(LIBS_PATH_BY_CHIP)/
LIBS_DIR_FOR_QUICK_MSG=$(TOP)libs/$(QUICK)/$(LIBS_PATH_BY_CHIP)/msg_id/
endif


#-------------------------------------------------------------------------------
# for msg
#-------------------------------------------------------------------------------
DIR_MSG=$(OUT)msg_id/
REL_DIR_MSG=./sc/libs/$(LIBS_PATH_BY_CHIP)/msg_id/



#-------------------------------------------------------------------------------
# build system
#-------------------------------------------------------------------------------
DIR_BUILD_SYS=$(TNG)build_system/
DIR_BUILD_PRE=$(DIR_BUILD_SYS)pre_process/
DIR_BUILD_LIB=$(DIR_BUILD_SYS)lib_generation/
DIR_BUILD_POST=$(DIR_BUILD_SYS)post_process/
DIR_BUILD_UTILITY=$(DIR_BUILD_SYS)utility/



#-------------------------------------------------------------------------------
# logging
#-------------------------------------------------------------------------------
ifeq "$(OSTYPE)" "Win32"
#Can't call perl in Win32 platform
#TRACE:=perl .\tng\Win32\trace.pl $(OUT)
#end
TRACE:=echo
DEP2TPP=.\tng\Win32\dep2tpp.pl
ASMDEP=.\tng\Win32\asmdep.pl
BIN_WIN32=.\tng\$(OSTYPE)\\
ECHO=.\tng\Win32\echo -e "$(TARGET)$(FLAVOR_$(TARGET)):\t"
MKDIR=gmkdir -p
BIN_RTPP=.\tng\$(OSTYPE)\rtpp
MAKER_FLAG_MULTI= -j 2
else
TRACE:=$(TNG)trace.pl
TRACE_SPEED=$(TRACE) debug warning_stop_on userout_off
ECHO=echo -e "$(TARGET)$(FLAVOR_$(TARGET)):\t"
DEP2TPP=$(TNG)dep2tpp.pl
ASMDEP=$(TNG)asmdep.pl
MKDIR=mkdir -p
endif

ifeq (1,$(FAST))
TDEBUG_WARNING_STOP:=$(TRACE) debug warning_stop_on userout_on
TDEBUG:=$(TRACE) debug warning_stop_off userout_on
TINFO :=$(TRACE) info warning_stop_off userout_on
TWARN :=$(TRACE) warn warning_stop_off userout_on
TERROR:=$(TRACE) error warning_stop_off userout_on
else
# logging
ifneq ($(IBUILD),1)
TDEBUG_WARNING_STOP:=$(TRACE) debug warning_stop_on userout_on
TDEBUG:=$(TRACE) debug warning_stop_off userout_on
TINFO:=$(TRACE) info warning_stop_off userout_on
TWARN:=$(TRACE) warn warning_stop_off userout_on
TERROR:=$(TRACE) error warning_stop_off userout_on
else
TDEBUG_WARNING_STOP:=$(TRACE) debug warning_stop_on userout_off
TDEBUG:=
TINFO:=
TWARN:=
TERROR:=$(TRACE) error warning_stop_off userout_on
endif
endif

#ECHO=echo -e "$(TARGET)$(FLAVOR_$(TARGET)):\t"
DEBUG=@$(TDEBUG) $(ECHO)
INFO=@$(TINFO) $(ECHO)
WARN=@$(TWARN) $(ECHO)
ERROR=@$(TERROR) $(ECHO)


#-------------------------------------------------------------------------------
# functions
#-------------------------------------------------------------------------------
SEARCH_COMPILER_OPTION=$(firstword $(filter $(1),$(PP_OPT_COMMON)) \
                                   $(filter $(1),$(PP_OPT_TARGET)) \
                                   $(filter $(1),$(PP_OPT_DUO))    )
FIND_COMPILER_OPTION=$(if $(call SEARCH_COMPILER_OPTION,$(1)),TRUE,FALSE)

FILE_EXISTED=$(if $(wildcard $(1)),TRUE, FALSE)

MAK_VERBOSE=$(if $(filter 1, $(1)),$(WARN) $(2))


#-------------------------------------------------------------------------------
# commands
#-------------------------------------------------------------------------------
#MKDIR=mkdir -p
INSTALL=install -m 640
RM=rm -f


#-------------------------------------------------------------------------------
# OSTYPE must be defined for rtpp
#-------------------------------------------------------------------------------
export OSTYPE
include $(TNG)$(OSTYPE).mak

DWLWIN_VER = 3.5.6.21
WINTARGET_VER = 3.03

