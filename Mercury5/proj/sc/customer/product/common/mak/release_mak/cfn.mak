# Makefile used to generate definition files (.dfn)
# from "VK" software components makefiles

include $(CONFIG_MAK)

# include SC makefile
include $(TARGET_MAK)
REL_OBJS=$(REL_SRC_C_LIST) \
         $(REL_SRC_ASM_LIST) 
         $(REL_SRC_CPP_LIST)
DEL_SRCS=$(SRC_C_LIST) $(SRC_ASM_LIST) $(SRC_CPP_LIST)

CPATHS=$(OUT)$(TARGET)_cpaths.lst
ASMPATHS=$(OUT)$(TARGET)_asmpaths.lst
.INTERMEDIATE: $(CPATHS) $(ASMPATHS)

.PHONY: cfn rfn

# main rule
#cfn: $(OUT)$(TARGET).cfn

cfn: $(CPATHS) $(ASMPATHS) $(TARGET_MAK)
	$(INFO) $(OUT)$(TARGET).$@
	$(TNG)remove.pl -o $(OUT)$(TARGET).$@ -c $(CPATHS) -a $(ASMPATHS) $(DEL_SRCS)

rfn: $(CPATHS) $(ASMPATHS) $(TARGET_MAK)
	$(INFO) $(OUT)$(TARGET).$@
	$(TNG)define.pl -o $(OUT)$(TARGET).$@ -c $(CPATHS) -a $(ASMPATHS) $(REL_OBJS)

# paths files rules
$(CPATHS) $(ASMPATHS): $(PATHS_MAK)

$(CPATHS): $(PATH_C)
	#$(INFO) $@
	@echo $(PATH_C) > $@

$(ASMPATHS): $(PATH_ASM)
	#$(INFO) $@
	@echo $(PATH_ASM) > $@
