
TARGET=link

all: link

include $(CONFIG_MAK)
include $(TARGET_MAK)
include $(COMMON)dwl.mak

STEM=$(OUT)$(PRODUCT)

COMPRESS_DLM_FILE=1
SLDLM_DIR=$(OUT)LdRgnBin/
SLDLM_CMPR_DIR=$(OUT)LdRgnBin_Cmpr/
LIST_OF_SLDLM=$(wildcard $(SLDLM_DIR)*.sldlm)
LIST_OF_SLDLM_CMPR=$(wildcard $(SLDLM_CMPR_DIR)*.sldlm)


.PHONY: link .phony

link: $(LIST_OF_SLDLM) $(OUT)SLDLM_bin.CUS

$(LIST_OF_SLDLM): .phony
ifneq ($(filter __RTK_OVER_ARM_SLDLM__ __RTK_OVER_ARM_NAND_IMI_SLDLM__, $(PP_OPT_COMMON)),)
	mv $@ $@.0
	perl $(TNG)gen_sldlm_header.pl $@.0 $(notdir $@.zi) $(OUT)link.info $@.hdr
	cat $@.hdr > $@
	cat $@.0 >> $@
	rm $@.hdr $@.0
ifeq ($(COMPRESS_DLM_FILE), 1)
	mkdir -p $(SLDLM_CMPR_DIR)
  ifeq ($(filter __LZMA2_PRESET_DICT__, $(PP_OPT_COMMON)), __LZMA2_PRESET_DICT__)
    ifeq ($(filter __EXTRACT_BOOT_IMAGE__, $(PP_OPT_COMMON)), __EXTRACT_BOOT_IMAGE__)
	./tng/MSComprs.exe -f"$@" -o"$(SLDLM_CMPR_DIR)$(notdir $@)" -s1048576 -a2 -p$(SLDLM_DIR)/XRAM_DICT $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1)
    else
      ifeq ($(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)), __COMPRESS_SELECTED_BIN__)
	./tng/MSComprs.exe -f"$@" -o"$(SLDLM_CMPR_DIR)$(notdir $@)" -s1048576 -a2 -p$(CMPR_BIN_DIR_CMPR)/SelectBin/SELECTED_BIN $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1)
      else
	./tng/MSComprs.exe -f"$@" -o"$(SLDLM_CMPR_DIR)$(notdir $@)" -s1048576 -a2 -p$(SLDLM_DIR)/ROM $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1)
      endif
    endif
  else
	./tng/MSComprs.exe -f"$@" -o"$(SLDLM_CMPR_DIR)$(notdir $@)" -s1048576 -a2 $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1)
  endif
endif
endif

$(OUT)SLDLM_bin.CUS: $(LIST_OF_SLDLM) .phony
ifneq ($(filter __RTK_OVER_ARM_SLDLM__ __RTK_OVER_ARM_NAND_IMI_SLDLM__, $(PP_OPT_COMMON)),)
ifeq ($(COMPRESS_DLM_FILE), 1)
	$(DLMCUS) -o $@.tmp -i $(LIST_OF_SLDLM_CMPR)
#	rm -rf $(SLDLM_CMPR_DIR)
else
	$(DLMCUS) -o $@.tmp -i $(LIST_OF_SLDLM)
endif
	../tools/XRG/CusPack -i $@.tmp -o $@ -p SDLM
	../tools/XRG/LoadConverter -cnew $@ -dv $(DWLWIN_VER) -wv $(WINTARGET) -g 0
endif
