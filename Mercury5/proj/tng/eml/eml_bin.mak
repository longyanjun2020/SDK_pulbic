
include $(CONFIG_MAK)

include $(PATH_dlm_entry_inc)dlm_entry.lst

.PHONY: .phony

all: dlm_bin

dlm_bin: $(OUT_DLM) $(OUT_EML) dlm_eml

dlm_eml: $(EML_KERNEL_LST:%=$(OUT_EML)%.dlm) $(EML_BIN_LST:%=$(OUT_EML)%.bin)
	$(EMLIZE) $(OUT_EML)

$(OUT_DLM) $(OUT_EML):
	$(MKDIR) $@
#
#always run the dlm_gen.mak to detect source file change
#
$(OUT_EML)%.dlm: .phony
	$(WARN) $@
	$(COPY) -fu $(PATH_middleware)$*/inc/* $(OUT)
	$(MAKE_EML_GEN_DLM) TARGET=$* COMPILER=$(COMPILER_ARM) OPTIMIZATION=OPTIMIZED_TIME MAPPER=$(TARGET) SRC='/src/'

$(OUT_EML)%.bin:
	$(MAKE_EML_GEN_BIN) TARGET=$* COMPILER=$(COMPILER_ARM) OPTIMIZATION=OPTIMIZED_TIME MAPPER='/eml_main/src/mapper/'
