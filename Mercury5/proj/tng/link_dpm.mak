TARGET=link

all: link

include $(CONFIG_MAK)
include $(TARGET_MAK)
include $(COMMON)dwl.mak

STEM=$(OUT)$(DPM)
DPMBINDIR=$(OUT)DlmBin
DPMBIN=$(OUT)DlmBin/$(DPM)

.PHONY: link

link: $(STEM).elf

$(DPMBINDIR):
	@[ -d $@ ] || mkdir -p $@

$(STEM).elf: $(DPMBINDIR)
	$(INFO) $@
ifeq ($(LINKER),AEONGCC_link)
	$(TDEBUG) $(PLTM_LINK) $(LDFLAGS) -Wl,-v -Wl,-Map,$(STEM).map -T$(SCATTER_DPM) -o $@ -Wl,--start-group \
		$(OUT)`$(PLTM_AR) t $(STEM).lib | head -n 1` $(STEM).lib \
	-Wl,--end-group

	$(PLTM_OBJCOPY) -O binary -j .DPM_TEXT_SECT $@ $(STEM)_text_sect.bin
	$(PLTM_OBJCOPY) -O binary -j .DPM_DATA_SECT $@ $(STEM)_data_sect.bin
	$(PLTM_NM) $@ > $(STEM).nm
	perl $(TNG)gen_dpm_header.pl $(DPM) $(STEM).nm $(STEM)_intf.h $(STEM)_header.bin $(STEM)_text_sect.bin $(STEM)_data_sect.bin
	cat $(STEM)_header.bin > $(DPMBIN).dlm
	cat $(STEM)_text_sect.bin >> $(DPMBIN).dlm
	cat $(STEM)_data_sect.bin >> $(DPMBIN).dlm
endif