
include $(CONFIG_MAK)

include $(PATH_dlm_entry_inc)dlm_entry.lst

TARGET=DLM

#
# It controls whether to compress DLM file or not
#
COMPRESS_DLM_FILE=1

LIST_OF_PRODUCTS=$(wildcard $(OUT_DLM)/*_dir/*.dlm)
LIST_OF_COMPRESS_PRODUCTS=$(wildcard $(OUT_DLM)*.dlm)

.PHONY: .phony

all: dlm_bin

dlm_bin: $(DLM_KERNEL_LST:%=$(OUT_DLM)%.dlm2) $(OUT)DLM_bin.CUS

$(OUT)DLM_bin.CUS: .phony
ifneq "$(strip $(DLM_GENERAL_LST))" ""
	$(WARN) $@
	$(WARN) DLM module for cus file are list in $(OUT_DLM)/dlm_list.txt
	@echo "include dlm: " '$(LIST_OF_PRODUCTS)' > $(OUT_DLM)/dlm_list.txt
ifeq "1" "$(COMPRESS_DLM_FILE)"
	$(DLMCUS) -o $@.tmp -i $(LIST_OF_COMPRESS_PRODUCTS)
# Do not remove compressed dlm file ! 
#	$(RM) $(LIST_OF_COMPRESS_PRODUCTS)
else
	$(DLMCUS) -o $@.tmp -i $(LIST_OF_PRODUCTS)
endif
	../tools/XRG/CusPack -i $@.tmp -o $@ -p DLMM
	../tools/XRG/LoadConverter -cnew $@ -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0
else
	$(WARN) No dlm module.
endif


#---------------------------------------------------------------------------
# always run the dlm_gen.mak to detect source file change
#---------------------------------------------------------------------------
$(OUT_DLM)%.dlm2: .phony
	$(WARN) $*
	$(MKDIR) $(OUT_DLM) $(OUT_DLM)$*_dir
	$(MAKE_DLM_GEN) all TARGET=$* COMPILER=$(COMPILER_THUMB)

#---------------------------------------------------------------------------
# partial dlm build
#---------------------------------------------------------------------------
dlm_ut_sys: $(DLM_UT_SYS_LST:%=$(OUT_DLM)%.dlm2)
dlm_ut_drv: $(DLM_UT_DRV_LST:%=$(OUT_DLM)%.dlm2)
dlm_ut_mdl: $(DLM_UT_MDL_LST:%=$(OUT_DLM)%.dlm2)
dlm_ut_mmi: $(DLM_UT_MMI_LST:%=$(OUT_DLM)%.dlm2)
dlm_ut_3rd: $(DLM_UT_3RD_LST:%=$(OUT_DLM)%.dlm2)
dlm_general:$(DLM_GENERAL_LST:%=$(OUT_DLM)%.dlm2) $(OUT)DLM_bin.CUS

