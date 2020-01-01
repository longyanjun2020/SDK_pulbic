include $(CONFIG_MAK)

.PHONY: lib clean cflags


#----------------------------------------------------------------------
# Variable
#----------------------------------------------------------------------
PP_LINE=-$(INSTALL) $< $@
ifeq ($(call FIND_COMPILER_OPTION, __NO_CRITICAL_TRACES__), TRUE)
RTPP_EXT_OPTION=-c
else
RTPP_EXT_OPTION=
endif
CPP_LINE=$(if $(filter 1, $(DIRECT_TRACE_FLAG)), cp -f $< $@, $(BIN)rtpp $(RTPP_EXT_OPTION) -s -i $< -o $@ -t remtrace_lib/$(TARGET)_remtrace)
TARGET_LIB=$(if $(filter 1, $(DUP_FLAG)), $(OUT)$(TARGET)_2.axf, $(OUT)$(TARGET).lib)
#PRE_PROCESS_CMD=$(PLTM_CC) -E $(if $(filter AEONGCC, $(COMPILER_VERSION)), -x c)

#----------------------------------------------------------------------
# Build target
#----------------------------------------------------------------------
ifeq ($(GENTPPONLY),1)
all: $(OUT)$(TARGET).tpp
else
ifeq ($(GEN_REMTRACE),1)
all: gen_remtrace
#all: gen_remtrace_start gen_remtrace
#	@echo -ne "gen_remtrace end "
#	@date +"%H:%M:%S"

#gen_remtrace_start:
#	@echo -ne "gen_remtrace start "
#	@date +"%H:%M:%S"

else
all: lib
endif
endif

#----------------------------------------------------------------------
# include file
#----------------------------------------------------------------------

ifneq ($(BUILD_TPP2),1)
-include $(OUT)$(TARGET).dfn
-include $(OUT)$(TARGET).tpp
else
#only includes $(OUT)$(TARGET).tpp2 at normal building steps
include $(OUT)$(TARGET).dfn
include $(OUT)$(TARGET).tpp
ifneq ($(GENTPPONLY),1)
ifneq ($(GEN_REMTRACE),1)
#ifneq ($(IBUILD),1)
include $(OUT)$(TARGET).tpp2
#endif
endif
endif
endif

# include SC makefile
include $(TARGET_MAK)


# library rules
# take off cflags to reduce log size
lib: $(TMP) $(INC_DIRS) $(TARGET_LIB)# cflags
ifneq ($(ABI_VER), )
	$(INFO) $(OUT)lib_$(TARGET).so
	$(TDEBUG) $(PLTM_CC) -shared -Wl,-soname,$(OUT)lib_$(TARGET).so -o $(OUT)lib_$(TARGET).so $(OBJS:%=$(TMP)%)
endif

# library rules
export CFLAGS

ifeq ($(DUP_FLAG),1)
CFLAGS += $(DFLAGS2)
endif

# create archive
$(TARGET_LIB): $(OUT)$(TARGET).dfn $(OBJS:%=$(TMP)%)
ifeq "$(DEPEND_FLAG)" "1"
	$(INFO) $@ DEPEND_FLAG=$(DEPEND_FLAG)
else
	$(INFO) $@
	$(RM) $@
ifeq ($(DUP_FLAG),1)
# JY: In order to avoid conflicts of symbol names between the original SW modules
#     and the duplicated one, we are using partial link with symbol renaming rule
#     to rename all the exported symbols.
#
	armlink --edit $(DUP_STR) --partial $(OBJS:%=$(TMP)%) --Output $@
else
ifeq "$(strip $(CHK_MULTIPLE_SYMBOL_DEF))" "1"
	$(TDEBUG) $(PLTM_CC) $(CFLAGS) -v -nostdlib -nostartfiles -r -o $@ $(OBJS:%=$(TMP)%)
else
	$(TDEBUG) $(PLTM_AR) -r $@ $(OBJS:%=$(TMP)%)
endif
endif
endif

gen_remtrace: $(OUT)$(TARGET).rem

# using rtpp to transfer string to id
ALL_DEPENDS=$(patsubst %,$(TMP)%,$(notdir $(filter %.c %.cpp %.S %.asm,$(DEPENDS))))
# preprocess *_message_define__.hi for msg id
MSG_DEF_H=$(patsubst %,$(DIR_MSG)%,$(notdir $(filter %_message_define__.hi,$(DEPENDS))))

$(OUT)$(TARGET).rem: $(TMP)remtrace_lib $(ALL_DEPENDS) rem_end $(MSG_DEF_H)
	@date > $@


ifeq ($(DEPEND_FLAG),1)
$(TMP)%.o: $(TMP)%.c $(TARGET_MAK)
	@echo Out:$@ Src:$<
else
# compile C modules
$(TMP)%.o: $(TMP)%.c $(TARGET_MAK)
# generate preprocess file
ifeq "$(GEN_PREPROCESS)" "1"
	$(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -E $< -o $@.pp
endif
ifeq "$(GEN_ASSEMBLY)" "1"
	$(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -S $< -o $@.asm
endif
ifeq ($(filter __DIAG_DUPDEF__ ,$(PP_OPT_COMMON)),__DIAG_DUPDEF__)
	$(TDEBUG) ././tng/cygwin/checkdef -f $@.tcheck $(DFLAGS) -D__ARMCC_VERSION=230000 -D__STRICT_ANSI__ $(INC_DIRS:%=-I%) $<
endif
ifeq ($(SPEED),1)
	$(if $(PARTIAL_BUILD),$(INFO) Src=$< Out=$@)
  ifeq ($(call FIND_COMPILER_OPTION, __DIAG_ERROR__), TRUE)
	$(TRACE_SPEED) $(CCACHE) $(CC) -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
  else
	$(CCACHE) $(CC) -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
  endif
else
	$(INFO) Src=$< Out=$@
    ifeq ($(call FIND_COMPILER_OPTION, __DIAG_ERROR__), TRUE)
	$(TDEBUG_WARNING_STOP) $(CCACHE) $(CC) -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
    else
	$(TDEBUG) $(CCACHE) $(CC) -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
    endif
endif
endif

# cpp models
$(TMP)%.o: $(TMP)%.cpp $(TARGET_MAK)
	$(INFO) Out:$@ Src:$<
	$(TDEBUG) $(CCACHE) $(CC) -c $(CXXFLAGS) $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<

# assemble ASM modules
$(TMP)%.o: $(TMP)%.asm $(TARGET_MAK)
	$(INFO) Src=$< Out=$@
	$(TDEBUG) $(PLTM_AS) $(ASM_OPTIONS) $(INC_DIRS:%=-I%) -o $@ $<

$(TMP)%.o: $(TMP)%.S $(TARGET_MAK)
	$(INFO) Src=$< Out=$@
	$(TDEBUG) $(PLTM_AS) $(ASM_OPTIONS) $(INC_DIRS:%=-I%) -o $@ $<

# create subdirs
$(sort $(TMP) $(INC) $(TMP)remtrace_lib):
	$(INFO) $@
	$(MKDIR) $@

clean:
	$(CLEAN) $(TARGET_LIB)
	$(CLEAN) $(TMP)


cflags:
	$(DEBUG) "CFLAGS = "$(CFLAGS)

rem_end:
	$(TNG)remtrace/remtraceErrDetect.pl $(OUT)remtrace_lib/$(TARGET)_remtrace.csv $(TARGET)

$(DEPENDS):;

$(OUT)$(TARGET).tpp: $(OUT)$(TARGET).dfn $(DEPENDS)
ifeq ($(DUP_FLAG),1)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)tpp.mak DUP_FLAG=1
else
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)tpp.mak DUP_FLAG=0
endif
ifeq ($(GENTPPONLY),1)
	echo [$@]" tpp generation completed"
else
	echo [$@]" tpp not generated before"
endif

$(OUT)$(TARGET).dfn: $(TARGET_MAK) $(PATHS_MAK) $(_PATHS_MAK) $(PATHS_PUB) $(SRC_DIRS)
ifeq ($(DUP_FLAG),1)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)dfn.mak dfn DUP_FLAG=1
else
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)dfn.mak dfn DUP_FLAG=0
endif

$(OUT)$(TARGET).tpp2: $(OUT)$(TARGET).tpp $(C_SRCS) $(CPP_SRCS) $(ASM_SRCS)
	$(INFO) $@
ifeq ($(GENTPPONLY),1)
	echo [$@]" [tpp2] should not come here case:GENTPPONLY, stop building.."
	$(error [$@]" [tpp2] should not come here case:GENTPPONLY, stop building..")
else
ifeq ($(GEN_REMTRACE),1)
	echo [$@]" [tpp2] should not come here case:GEN_REMTRACE, stop building.."
	$(error [$@]" [tpp2] should not come here case:GEN_REMTRACE, stop building..")
else
	$(MAKE_GEN_REMTRACE) TARGET=$(TARGET) BUILD_TPP2=1
	echo "#NoMeaningJustTemplate">$@
	echo [$@]" tpp2 build completed, no rtpp C files after"
endif
endif
