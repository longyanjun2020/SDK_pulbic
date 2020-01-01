include $(CONFIG_MAK)

# include sc_lib_list to get $(LIB_LIST)
include $(SC_LIB_LIST) $(NON_CT_LIST)
# enable critical trace option in release build
#CFLAGS += $(if $(filter 1,$(call critical-trace-option,$(TARGET))),-D__CRITICAL_TRACES_ONLY__)

#check $(TARGET) is LIB or SRC
ifeq ($(filter $(TARGET), $(LIB_LIST)), $(TARGET))
#===============================================================
# $(TARGET) is LIB, skip this step
all:
#skip, pure lib in $(LIBS_DIR)
else
#===============================================================
# $(TARGET) is SRC, process lib build 

.PHONY: lib clean SCM_clean cflags

ifeq ($(GENTPPONLY),1)
all: $(OUT)$(TARGET).tpp
else
ifeq ($(GEN_REMTRACE),1)
all: gen_remtrace
else
all: lib
endif
endif

include $(OUT)$(TARGET).rfn
CPP_LINE=$(BIN)rtpp -s -i $< -o $@ -t remtrace_lib/$(TARGET)_remtrace
PP_LINE=$(INSTALL) $< $@

include $(OUT)$(TARGET).tpp

#only includes $(OUT)$(TARGET).tpp2 at normal building steps
ifneq ($(GENTPPONLY),1)
ifneq ($(GEN_REMTRACE),1)
#ifneq ($(IBUILD),1)
include $(OUT)$(TARGET).tpp2
#endif
endif
endif

# include SC makefile
include $(TARGET_MAK)

# library rules
# take off cflags to reduce log size
lib: $(TMP) $(INC_DIRS) $(OUT)$(TARGET).lib# cflags

# library rules
export CFLAGS

#export LIBS_DIR
#LIBS_DIR = ./sc/libs/

lib-folder := $(strip $(if $(call filter_common_libs,$(TARGET)),COMMON,\
				$(if $(call filter_feature_libs,$(TARGET)),$(LIBS_PATH_BY_FEATURE),\
				$(if $(call filter_bsp_libs,$(TARGET)),$(LIBS_PATH_BY_BSP),\
				$(if $(call filter_chip_libs,$(TARGET)),$(LIBS_PATH_BY_CHIP),\
				$(error unable to determine which category $(TARGET).lib belong))))))

LIBS_DIR := $(if $(call critical-trace-option,$(TARGET)),./sc/libs/$(lib-folder)/ct/,./sc/libs/$(lib-folder)/)

#ifeq ($(TARGET),$(filter $(TARGET),$(FEATURE_LIB_LIST)))
#LIBS_DIR = $(if $(call critical-trace-option,$(TARGET)),./sc/libs/$(LIBS_PATH_BY_FEATURE)/ct/,./sc/libs/$(LIBS_PATH_BY_FEATURE)/)
#else
#LIBS_DIR = $(if $(call critical-trace-option,$(TARGET)),./sc/libs/$(LIBS_PATH_BY_CHIP)/ct/,./sc/libs/$(LIBS_PATH_BY_CHIP)/)
#endif

# create archive
$(OUT)$(TARGET).lib: $(OUT)$(TARGET).rfn $(OBJS:%=$(TMP)%)
	$(INFO) $@
ifneq ($(wildcard $(LIBS_DIR)$(TARGET).lib),)
	@echo "copy libraries in release process: "$(COPY) -fu $(LIBS_DIR)$(TARGET).lib $(OUT)
	$(COPY) -f $(LIBS_DIR)$(TARGET).lib $(OUT)
	-$(if $(filter-out $(OBJS),$(shell $(PLTM_AR) -t $(LIBS_DIR)$(TARGET).lib)),\
		$(PLTM_AR) -d $@ $(filter-out $(OBJS),$(shell $(PLTM_AR) -t $(LIBS_DIR)$(TARGET).lib)))
endif
	$(TDEBUG) $(PLTM_AR) -r $@ $(OBJS:%=$(TMP)%)

gen_remtrace: $(OUT)$(TARGET).rem

# using rtpp to transfer string to id
ALL_DEPENDS=$(patsubst %,$(TMP)%,$(notdir $(filter %.c %.cpp %.S %.asm,$(DEPENDS))))
# preprocess *_message_define__.hi for msg id
MSG_DEF_H=$(patsubst %,$(DIR_MSG)%,$(notdir $(filter %_message_define__.hi,$(DEPENDS))))

$(OUT)$(TARGET).rem: $(TMP)remtrace_lib $(ALL_DEPENDS) rem_end $(MSG_DEF_H)
	@date > $@


# compile C modules
ifeq ($(SPEED),1)
$(TMP)%.o: $(TMP)%.c $(TARGET_MAK)
# generate preprocess file
	$(if $(PARTIAL_BUILD),$(INFO) $@)
ifeq "$(GEN_PREPROCESS)" "1"
	$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -E $< -o $@.pp
endif
  ifeq ($(filter __DIAG_ERROR__ ,$(PP_OPT_COMMON)),__DIAG_ERROR__)
	$(TRACE_SPEED) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
  else
    ifeq ($(IBUILD),1)
			$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
    else
			$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
    endif        
  endif        
else
$(TMP)%.o: $(TMP)%.c $(TARGET_MAK)
	$(INFO) $@
# generate preprocess file
ifeq "$(GEN_PREPROCESS)" "1"
	$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -E $< > $@.pp
endif
  ifeq ($(filter __DIAG_ERROR__ ,$(PP_OPT_COMMON)),__DIAG_ERROR__)
	$(TDEBUG_WARNING_STOP) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
  else
	$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<
  endif	      
endif


# cpp models
$(TMP)%.o: $(TMP)%.cpp $(TARGET_MAK)
	$(INFO) Out:$@ Src:$<
	$(TDEBUG) $(CCACHE) $(CC)  -c $${CFLAGS} $(INC_DIRS:%=-I%) -o $@ $<


# assemble ASM modules
$(TMP)%.o: $(TMP)%.asm $(TARGET_MAK)
	$(INFO) $@
	$(TDEBUG) $(PLTM_AS) $(ASM_OPTIONS) $(INC_DIRS:%=-I%) -o $@ $<

# create subdirs
$(sort $(TMP) $(INC) $(TMP)remtrace_lib):
	$(INFO) $@
	$(MKDIR) $@

clean:
	$(CLEAN) $(OUT)$(TARGET).lib
	$(CLEAN) $(TMP)

SCM_clean:
	$(CLEAN) $(DEL_SRCS)

#C_SRCS

cflags:
	$(DEBUG) "CFLAGS = "$(CFLAGS)

rem_end:
	$(TNG)remtrace/remtraceErrDetect.pl $(OUT)remtrace_lib/$(TARGET)_remtrace.csv $(TARGET)

$(DEPENDS):;

$(OUT)$(TARGET).tpp: $(OUT)$(TARGET).rfn $(DEPENDS)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)rpp.mak
ifeq ($(GENTPPONLY),1)
	echo [$@]" tpp generation completed"
else
	#echo [$@]" tpp not generated before"
endif

$(OUT)$(TARGET).rfn: $(TARGET_MAK) $(PATHS_MAK) $(_PATHS_MAK) $(PATHS_PUB) $(SRC_DIRS)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)cfn.mak rfn
	#$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)rpp.mak

$(OUT)$(TARGET).tpp2: $(OUT)$(TARGET).tpp $(C_SRCS) $(CPP_SRCS) $(ASM_SRCS)
ifneq ($(SPEED),1)
	$(INFO) $@
endif
ifeq ($(GENTPPONLY),1)
	echo [$@]" [tpp2] should not come here case:GENTPPONLY, stop building.."
	$(error [$@]" [tpp2] should not come here case:GENTPPONLY, stop building..")
else
ifeq ($(GEN_REMTRACE),1)
	echo [$@]" [tpp2] should not come here case:GEN_REMTRACE, stop building.."
	$(error [$@]" [tpp2] should not come here case:GEN_REMTRACE, stop building..")
else
	$(REL_MAKE_GEN_REMTRACE) TARGET=$(TARGET)
	echo "#NoMeaningJustTemplate">$@
	#echo [$@]" tpp2 build completed, no rtpp C files after"
endif
endif

endif #ifeq ($(filter $(TARGET), $(LIB_LIST)), $(TARGET))
