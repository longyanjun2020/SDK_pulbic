# Makefile used to generate definition files (.dfn)
# from "VK" software components makefiles

include $(CONFIG_MAK)

# include SC makefile
include $(TARGET_MAK)


C_FILE_LIST:= $(REL_SRC_C_LIST) $(SRC_C_LIST) $(REL_SRC_CPP_LIST) $(SRC_CPP_LIST)
ASM_FILE_LIST := $(REL_SRC_ASM_LIST) $(SRC_ASM_LIST)
CODE_FILE_LIST := $(C_FILE_LIST) $(ASM_FILE_LIST)


#-----------------------------------------------------------------------------
# include CL_LIST.mak for CTS per file scanning
#-----------------------------------------------------------------------------
ifeq "$(PER_FILE)" "1"
include CL_LIST.mak
CODE_FILE_LIST := $(filter $(CTS_SRC_C_LIST),$(CODE_FILE_LIST))
endif

CPATHS=$(OUT)$(TARGET)_cpaths.lst
ASMPATHS=$(OUT)$(TARGET)_asmpaths.lst
.INTERMEDIATE: $(CPATHS) $(ASMPATHS)

.PHONY: dfn

# main rule
dfn: $(OUT) $(OUT)$(TARGET).dfn

# make target definition file (.dfn)
$(OUT)$(TARGET).dfn: $(if $(strip $(C_FILE_LIST)),$(CPATHS)) $(if $(strip $(ASM_FILE_LIST)),$(ASMPATHS)) $(TARGET_MAK)
	$(if $(strip $(CODE_FILE_LIST)),,$(error dfn.mak: there is no any c/cpp/asm source file in $(TARGET_MAK)))
#	$(INFO) $@
	$(TNG)define.pl -o $@ $(if $(strip $(C_FILE_LIST)),-c $(CPATHS)) $(if $(strip $(ASM_FILE_LIST)),-a $(ASMPATHS)) $(CODE_FILE_LIST)
#	write $(TARGET) to $(UPDATED_LIB_LST) for smart build of lint
	@echo '    $(TARGET)\' >> $(UPDATED_LIB_LST)


$(CPATHS): $(PATH_C) $(PATHS_MAK)
#	$(INFO) $@
	@echo $(PATH_C) > $@

$(ASMPATHS): $(PATH_ASM) $(PATHS_MAK)
#	$(INFO) $@
	@echo $(PATH_ASM) > $@

$(OUT):
	$(MKDIR) $@
