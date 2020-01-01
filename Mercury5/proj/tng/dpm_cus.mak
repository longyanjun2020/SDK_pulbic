
TARGET=link

all: link

include $(CONFIG_MAK)
include $(TARGET_MAK)
include $(COMMON)dwl.mak

STEM=$(OUT)$(PRODUCT)

ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
COMPRESS_DPM_FILE=0
else
COMPRESS_DPM_FILE=1
endif
DPM_DIR=$(OUT)LdRgnBin/
DPM_CMPR_DIR=$(OUT)LdRgnBin_Cmpr/
LIST_OF_DPM=$(wildcard $(DPM_DIR)*.dpm)
LIST_OF_CMPR_DPM=$(wildcard $(DPM_CMPR_DIR)*.dpm)

.PHONY: link .phony

link: $(OUT)DP_PAGE.CUS

$(OUT)DP_PAGE.CUS: .phony
ifeq ($(filter __DPM__, $(PP_OPT_COMMON)), __DPM__)
ifeq ($(COMPRESS_DPM_FILE), 1)
	$(DLMCUS) -o $(DPM_CMPR_DIR)/all_sldpm.dpm.tmp -i $(LIST_OF_CMPR_DPM)
	../tools/XRG/CusPack.exe -i $(DPM_CMPR_DIR)/all_sldpm.dpm.tmp -p PAGE -o $(OUT)DP_PAGE.CUS
else
	$(DLMCUS) -o $(DPM_DIR)/all_sldpm.dpm.tmp -i $(LIST_OF_DPM)
	../tools/XRG/CusPack.exe -i $(DPM_DIR)/all_sldpm.dpm.tmp -p PAGE -o $(OUT)DP_PAGE.CUS
endif
	../tools/XRG/LoadConverter.exe -h16 $(OUT)DP_PAGE.CUS -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 3
endif
