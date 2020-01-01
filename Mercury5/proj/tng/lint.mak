
.PHONY: lib clean SCM_clean cflags

all: lib

#TMP ==> output folder.
include $(CONFIG_MAK)

include $(OUT)$(TARGET).dfn
include $(OUT)$(TARGET).tpp
include $(TARGET_MAK)

OBJS_EXPAND=$(OBJS)
ifeq "$(OSTYPE)" "Win32"
LINT_PL=perl $(TNG)genlint.pl
LINTREPORT_PL=perl $(TNG)genReport.pl
else
LINT_PL=$(TNG)genlint.pl
LINTREPORT_PL=$(TNG)genReport.pl
endif	

C_SRCS:=$(C_SRCS:%=./%)
C_SRCS_WITHOUT_CSN=$(filter-out $(wildcard $(BUILD)$(PRODUCT)/out/csn/*), $(C_SRCS))
ifeq "$(PER_FILE)" "1"
include CL_LIST.mak
C_SRCS_WITHOUT_CSN:=$(filter $(CL_LIST), $(C_SRCS_WITHOUT_CSN))
endif
C_SRCS_LOG=$(C_SRCS_WITHOUT_CSN:%=%.lintlog)

# library rules
lib: $(TMP) $(INC) cflags  prepare $(OUT)$(TARGET).log
	$(LINTREPORT_PL)	

# library rules
export CFLAGS

#export LIBS_DIR
#LIBS_DIR = ./sc/libs/
#LIBS_DIR = ./sc/libs/$(PRODUCT)/
LINTOPTION = $(filter -D%,$(CFLAGS))
#LINTOPTION+= $(PP_OPT_COMMON)

#ifeq ($(COMPILER),RVCTV22_arm)
    LINTOPTION +=NG_CPU_ARM     \
      __NEW_BACK_TRACE__ \
      NG_COMP_RVCT       \
      NG_CODE_ARM \
      __FUNCTION__="__function__" \
      __LINE__=0
#endif


# create archive
prepare:
	$(INFO) prepare call $(LINT_PL) Target=$@	
	$(LINT_PL) "LINTCLEAN" $(TMP) $(TARGET)
	$(LINT_PL) "LINTDEFINE" $(TMP) $(TARGET) $(LINTOPTION)
	$(LINT_PL) "LINTINCLUDE" $(TMP) $(TARGET) $(INC_DIRS) $(SRC_DIRS)
	#$(LINT_PL) "LINTINCLUDE" $(TMP) $(TARGET) $(PATH_H) $(PATH_C)
	
$(OUT)$(TARGET).log: $(C_SRCS_LOG)
#	$(OBJS_EXPAND:%=$(TMP)%)
#	$(INFO) Target=$@ TMP=$(TMP) SRC=$(C_SRCS) DFLAGS=$(DFLAGS) CSRC=$(PATH_C) CINC=$(PATH_H) INC=$(INC)
	$(INFO) call $(LINT_PL) Target=$@	
#	$(LINT_PL) "LINTCLEAN" $(TMP) $(TARGET)
#	$(LINT_PL) "LINTDEFINE" $(TMP) $(TARGET) $(LINTOPTION)
#	$(LINT_PL) "LINTINCLUDE" $(TMP) $(TARGET) $(PATH_H)
#	$(LINT_PL) "LINTSOURCE" $(TMP) $(TARGET) $(C_SRCS)


	
# compile C modules
$(C_SRCS_LOG):
ifeq "$(OSTYPE)" "Win32"
	@echo Lint Source=$(basename $@)
else
	$(INFO) Lint Source=$(basename $@)
endif		
	$(LINT_PL) "LINTSOURCE" $(TMP) $(TARGET) $(basename $@)

# create subdirs
$(TMP) $(INC):
	$(INFO) $@
	$(MKDIR) $@


cflags:
ifeq "$(OSTYPE)" "Win32"
	@echo "CFLAGS = "$(CFLAGS)
else
	$(DEBUG) "CFLAGS = "$(CFLAGS)
endif		

