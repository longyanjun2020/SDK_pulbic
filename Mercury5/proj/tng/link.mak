
TARGET=link

all: link

include $(CONFIG_MAK)
include $(TARGET_MAK)
include $(COMMON)dwl.mak
include $(PATH_cust_scatter)cmpr_bin_list.mak



ifneq ($(filter __EXTRACT_BOOT_IMAGE__  __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
include $(NON_CMPR_OBJ_LIST_MAK)
endif


.PHONY: link $(STEM).elf .phony shrink_check

link: $(STEM).wpb $(OUT)symbols

.INTERMEDIATE: $(STEM).elf $(STEM).nm

$(OUT)symbols: $(STEM).nm
	$(INFO) $@
	$(TNG)symbols.pl $< $@

$(STEM).nm: $(STEM).axf shrink_check
	$(DEBUG) $@
	nm  $< > $@

$(STEM).axf: $(STEM).elf
	$(INFO) $@
ifneq ($(filter AEONGCC MIPSGCC X86LINUXGCC ARMGCC, $(COMPILER_VERSION)), )
	$(PLTM_READELF) --symbols  $(STEM).elf |grep FUNC |sort -k 2 > $(STEM).bt.map
	$(INFO) $(STEM).bt.map
	cp -f $< $@
	size -A $@ > $(OUT)link.info
else
	mv -f $< $@
endif

define check_shrink_output_for_linux
if [ "$(1)"=="SUCCESS : get .debug_frame info" ]; \
then \
echo "Srink OK"; \
else \
echo "Error: Shrink fail"; \
false; \
fi
endef

define check_shrink_output
$(INFO) $(1)
if [ "$(1)" == " get .debug_frame info DONE" ]; \
then \
echo "Srink OK"; \
else \
echo "Error: Shrink fail"; \
false; \
fi
endef

define check_file_size
if [ `stat -c %s $(1)` -lt $(2) ]; \
then \
echo "OK"; \
else \
echo "Error: too larget"; \
false; \
fi
endef
SHRINKER_OUTPUT=$(shell $(BIN)AXFshrinker $(STEM).axf $(OUT)backtraces.axf)
shrink_check: $(STEM).axf
ifeq ($(OSTYPE), cygwin)
	$(call check_shrink_output, $(SHRINKER_OUTPUT))
	$(INFO) "Checking $(OUT)backtraces.axf size"
	$(call check_file_size, $(OUT)backtraces.axf, 15728640)
else
#	$(WARN) "STEM=$(STEM) OUT=$(OUT)  SHRINKER_OUTPUT=$(SHRINKER_OUTPUT))"
	$(call check_shrink_output_for_linux, $(SHRINKER_OUTPUT))
	$(INFO) "Checking $(OUT)backtraces.axf size"
	$(call check_file_size, $(OUT)backtraces.axf, 15728640)
endif

$(STEM).wpb: $(STEM).bin sldlm_cus dpm_cus
	$(INFO) $@ "for Downloader version" $(DWL_VERSION)
	$(BIN)wzpacker -d $(DWL_VERSION) $< $@

sldlm_cus: .phony
ifneq ($(filter __RTK_OVER_ARM_SLDLM__ __RTK_OVER_ARM_NAND_IMI_SLDLM__, $(PP_OPT_COMMON)),)
	perl $(TNG)pre_proc_sldlm.pl $(OUT)link.info $(LDRGN_BIN_DIR)/
	$(MAKE_SLDLM_CUS)
endif


dpm_cus: .phony
ifeq ($(filter __DPM__, $(PP_OPT_COMMON)), __DPM__)
ifneq ($(DPM_LIST),)
	$(MAKE_DPM_CUS)
endif
endif

$(STEM).bin: $(STEM).elf .phony
	$(INFO) $@
ifeq ($(LINKER),RVCTV22_link)
	$(PLTM_ELF) $< --bin --output $(LDRGN_BIN_DIR)
	# check bin size
	perl $(DIR_BUILD_POST)/link/bin_size_check.pl -l $(OUT)link.info
	cp $(LDRGN_BIN_DIR)/ROM_BOOT $@
	cat $(LDRGN_BIN_DIR)/ROM >> $@
	-cat $(LDRGN_BIN_DIR)/ROM_DATA >> $@
  ifeq ($(filter __ZLIB_PRESET_DICT__, $(PP_OPT_COMMON)), __ZLIB_PRESET_DICT__)
	$(DICT_GEN_DIR)/gzip -f -k $(LDRGN_BIN_DIR)/emmi_sldpm_text.bin
	$(DICT_GEN_DIR)/MSDictGenPre.exe -g$(LDRGN_BIN_DIR)/emmi_sldpm_text.bin.gz -f$(LDRGN_BIN_DIR)/emmi_sldpm_text.bin -s4096 -o$(LDRGN_BIN_DIR)/ZlibDictPreprocess.txt
	$(DICT_GEN_DIR)/MSDictGen.exe -f$(LDRGN_BIN_DIR)/ZlibDictPreprocess.txt -s4096 -o$(LDRGN_BIN_DIR)/zlib_4k_dict.bin
  endif

  ifeq ($(filter __LZMA2_PRESET_DICT__, $(PP_OPT_COMMON)), __LZMA2_PRESET_DICT__)
    ifeq ($(filter __EXTRACT_BOOT_IMAGE__, $(PP_OPT_COMMON)), __EXTRACT_BOOT_IMAGE__)
	perl $(TNG)gen_xram_dict.pl $(OUT)link.info 0x10004000 $(LDRGN_BIN_DIR)/XRAM0 $(LDRGN_BIN_DIR)/XRAM_DICT
    endif
  endif

#===== ENABLE DPM =====#
    ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
	for DPM in $(DPM_LIST);do\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_text.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_text.bin;\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_data.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_data.bin;\
		perl $(TNG)gen_dpm_header.pl $$DPM NULL NULL $(LDRGN_BIN_DIR)/"$$DPM"_header.bin $(LDRGN_BIN_DIR)/"$$DPM"_text.bin $(LDRGN_BIN_DIR)/"$$DPM"_data.bin;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_header.bin > $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_text.bin >> $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_data.bin >> $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
	done;
    else
	mkdir -p $(LDRGN_CMPR_BIN_DIR)
      ifeq ($(filter __ZLIB_PRESET_DICT__, $(PP_OPT_COMMON)), __ZLIB_PRESET_DICT__)
	for DPM in $(DPM_LIST);do\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_text.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_text.bin;\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_data.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_data.bin;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_text.bin > $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_data.bin >> $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		if [ "$$DPM" == "emmi_sldpm" ];then\
			./tng/MSComprs.exe -f"$(LDRGN_BIN_DIR)/"$$DPM"_text.bin" -o"$(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin" -s4096 -a1 -p$(LDRGN_BIN_DIR)/zlib_4k_dict.bin $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1) -t;\
		else\
			./tng/MSComprs.exe -f"$(LDRGN_BIN_DIR)/"$$DPM"_text.bin" -o"$(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin" -s4096 -a1 $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1) -t;\
		fi;\
		./tng/MSComprs.exe -f"$(LDRGN_BIN_DIR)/"$$DPM"_data.bin" -o"$(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin" -s4096 -a1 $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1) -t;\
		perl $(TNG)gen_dpm_header.pl "$$DPM" NULL NULL $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_header.bin $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_header.bin > $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin >> $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin >> $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
	done;
      else # __ZLIB_PRESET_DICT__
	for DPM in $(DPM_LIST);do\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_text.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_text.bin;\
		[ -f $(LDRGN_BIN_DIR)/"$$DPM"_data.bin ] || touch $(LDRGN_BIN_DIR)/"$$DPM"_data.bin;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_text.bin > $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_BIN_DIR)/"$$DPM"_data.bin >> $(LDRGN_BIN_DIR)/"$$DPM".dpm;\
		./tng/MSComprs.exe -f"$(LDRGN_BIN_DIR)/"$$DPM"_text.bin" -o"$(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin" -s4096 -a1 $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1) -t;\
		./tng/MSComprs.exe -f"$(LDRGN_BIN_DIR)/"$$DPM"_data.bin" -o"$(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin" -s4096 -a1 $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i1) -t;\
		perl $(TNG)gen_dpm_header.pl "$$DPM" NULL NULL $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_header.bin $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_header.bin > $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_text_cmpr.bin >> $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
		cat $(LDRGN_CMPR_BIN_DIR)/"$$DPM"_data_cmpr.bin >> $(LDRGN_CMPR_BIN_DIR)/"$$DPM".dpm;\
	done;
      endif # __ZLIB_PRESET_DICT__
    endif
#===== enable DPM =====#

#	append compressed or uncompressed binary (load)
  ifneq ($(filter __BOOT_UNCOMPRESS__ __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
	-$(RM) -fr $(CMPR_BIN_DIR) $(CMPR_BIN_DIR_CMPR)
	$(MKDIR) $(CMPR_BIN_DIR) $(CMPR_BIN_DIR_CMPR)
	for PROD in $(CMPR_RO_RW_REGIONS);do\
		if [ -e $(LDRGN_BIN_DIR)/$$PROD ];then\
			cp -f $(LDRGN_BIN_DIR)/$$PROD $(CMPR_BIN_DIR);\
		fi;\
	done;
  endif
  ifeq ($(filter __BOOT_UNCOMPRESS__, $(PP_OPT_COMMON)), __BOOT_UNCOMPRESS__)
    ifneq ($(filter __EXTRACT_BOOT_IMAGE__ __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
	cp $(LDRGN_BIN_DIR)/ROM     $(LDRGN_BIN_DIR)/lzma_rom_dict.bin
    endif
	$(DIR_BUILD_POST)/link/gen_cmpr_bin.pl -l $(OUT)link.info -b $(PATH_cust_scatter)cmpr_bin_list.mak -o $@ -f $(CMPR_BIN_DIR) -c 1 \
      -z 2 $(if $(filter __LZMA2_PRESET_DICT__, $(PP_OPT_COMMON)), -d $(LDRGN_BIN_DIR)/lzma_rom_dict.bin) \
      $(if $(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)), -s 1 -k $(SELECTED_BIN_SIZE))\
      $(if $(filter JMP_OPT_ABSADR, $(CMPR_PRE_PROC)), -i 1)
    ifneq ($(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
	-$(COPY) $(CMPR_BIN_DIR_CMPR)/SelectBin/CompressedBin_bin $(CMPR_BIN_DIR_CMPR)
	-$(COPY) $(CMPR_BIN_DIR_CMPR)/SelectBin/CompressedBin     $(CMPR_BIN_DIR)
	-$(MKDIR) $(CMPR_BIN_DIR_CMPR)/SelectBin/
	-mv $(CMPR_BIN_DIR)/SELECTED_BIN                           $(CMPR_BIN_DIR_CMPR)/SelectBin/SELECTED_BIN
    endif
  else # __BOOT_UNCOMPRESS__
	$(DIR_BUILD_POST)/link/gen_cmpr_bin.pl -l $(OUT)link.info -b $(PATH_cust_scatter)cmpr_bin_list.mak -o $@ -f $(LDRGN_BIN_DIR) -c 0 -z 1 -n 1
	-$(MKDIR) $(CMPR_BIN_DIR_CMPR)/
	-$(MKDIR) $(CMPR_BIN_DIR_CMPR)/SelectBin/
	-mv $(LDRGN_BIN_DIR)/SELECTED_BIN                          $(CMPR_BIN_DIR_CMPR)/SelectBin/SELECTED_BIN
  endif
  ifeq ($(filter __ZLIB_PRESET_DICT__, $(PP_OPT_COMMON)), __ZLIB_PRESET_DICT__)
	$(DIR_BUILD_POST)/link/link_utility.pl -f 2 -o $@
	cat $(LDRGN_BIN_DIR)/zlib_4k_dict.bin >> $@
  endif
  ifneq ($(filter __BOOT_UNCOMPRESS__ __BOOT_SLDLM__ __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
	$(DIR_BUILD_POST)/link/link_utility.pl -f 0 -l $(OUT)link.info -o $@
  endif
  ifeq ($(filter __NAND__, $(PP_OPT_COMMON)),__NAND__)
	$(DIR_BUILD_POST)/link/link_utility.pl -f 1 -l $(OUT)link.info
  endif

endif



ifneq ($(filter AEONGCC_link MIPSGCC_link X86LINUXGCC_link ARMGCC_link, $(LINKER)), )
#	dd if=/dev/zero of=$@ bs=256 count=1
ifeq ($(filter __EMMI_SLDPM__, $(PP_OPT_COMMON)), __EMMI_SLDPM__)
	$(PLTM_OBJCOPY) -O binary -j .emmi_sldpm $< $(OUT)emmi_sldpm_text.bin
	$(PLTM_OBJCOPY) -O binary -R .rw_staticboot -R .debug_area -R .bss -R .bss_sram -R .emmi_sldpm $< $@0
	cat $@0 > $@
	@[ -f $(OUT)/emmi_sldpm_text.bin ] || touch $(OUT)/emmi_sldpm_text.bin
	@[ -f $(OUT)/emmi_sldpm_data.bin ] || touch $(OUT)/emmi_sldpm_data.bin
	perl $(TNG)gen_dpm_header.pl emmi_sldpm NULL NULL $(OUT)/emmi_sldpm_header.bin $(OUT)/emmi_sldpm_text.bin $(OUT)/emmi_sldpm_data.bin
	cat $(OUT)/emmi_sldpm_header.bin > $(OUT)/emmi_sldpm.bin
	cat $(OUT)/emmi_sldpm_text.bin >> $(OUT)/emmi_sldpm.bin
	cat $(OUT)/emmi_sldpm_data.bin >> $(OUT)/emmi_sldpm.bin
	../tools/XRG/CusPack.exe -i $(OUT)emmi_sldpm.bin -p PAGE -o $(OUT)DP_PAGE.CUS
	../tools/XRG/LoadConverter.exe -h16 $(OUT)DP_PAGE.CUS -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 3
else
	$(PLTM_OBJCOPY) -O binary -R .bss -R .bss_sram $< $@0
	cat $@0 > $@
endif
#	$(BIN)swap32.exe $@ $@_swap.bin
endif

full-paths-dsc := $(PATH_cust_scatter)scatter_85xx_emmi_sldpm.dsc $(PATH_cust_scatter)scatter_85xx_sldlm.dsc $(PATH_cust_scatter)scatter_85xx_nand_imi_sldlm.dsc $(SCATTER_STACK_LIB) $(ALL_GROUP_SCATTER)

# In order to regenerate .bin file in each time, we remove dependency
# "$(LINK) $(SCATTER)" and make "$(STEM).elf" as phony target.
$(STEM).elf:
	$(INFO) $@
ifeq ($(LINKER),RVCTV22_link)
# Using preprocessing directives to generate scatter file
	-@$(CLEAN) $(ALL_GROUP_SCATTER)
	$(MAKE_PREPROCESS_SCATTER)
ifeq (1,$(RELEASE_PROCESS))
	for f in $(full-paths-dsc); \
	do $(DIR_BUILD_POST)/link/find-rel-lib-path.pl -f=0 -l="$(shell echo $(filter-out $(OUT)%,$(LINK))| sed -e 's/[ 	][ 	]*/:/g')" $$f > $$f.relpath; done;
endif
	$(PLTM_CC) $(SPECIAL_D) -E $(CFLAGS) -DRELEASE_PROCESS=$(RELEASE_PROCESS) -DTARGET=$(PRODUCT) -DSELECTED_BIN_SIZE=$(SELECTED_BIN_SIZE) -I$(PATH_kernel_hal)/inc -I$(OUT) $(SCATTER) > $(SCATTER_OUT)
	$(TDEBUG) $(PLTM_LINK) $(LDFLAGS) --scatter $(SCATTER_OUT) -o $@ $(LINK) $(CUST_ALL_OBJS_LIST)
endif
ifneq ($(filter AEONGCC_link MIPSGCC_link X86LINUXGCC_link ARMGCC_link, $(LINKER)), )
	$(if $(QUICK), BUILD_FLAG=BUILD_QUICK_$(QUICK);, BUILD_FLAG=BUILD_NORMAL;) \
    $(PLTM_CC) $(CFLAGS) -DTARGET=$(PRODUCT) -D$$BUILD_FLAG -I$(PATH_hal)/kernel/inc -E -P -xc $(SCATTER) -o $(SCATTER_OUT)
#	@(WARN) $(TDEBUG) $(PLTM_LINK) $(LDFLAGS) -T$(SCATTER_OUT) -o $@ -Wl,--start-group $(LINK) $(CUST_ALL_OBJS_LIST) -Wl,--end-group -lgcc -lc -lm
ifeq (arm-linux-gnueabihf-gcc,$(COMPILER_EXECUTABLE))
	$(TDEBUG) $(PLTM_LINK) $(LDFLAGS) -T$(SCATTER_OUT) -o $@ -Wl,--start-group $(LINK) $(CUST_ALL_OBJS_LIST) -Wl,--end-group -lgcc -lc -lm
else
	$(TDEBUG) $(PLTM_LINK) $(LDFLAGS) -T$(SCATTER_OUT) -o $@ -Wl,--start-group $(LINK) $(CUST_ALL_OBJS_LIST) -Wl,--end-group -lgcc -lc -lm -lrdimon
endif
	#check the libc functions
	cat $(STEM).map | ./tng/libc_check_xref.pl ./tng/safe_libc.txt
	#if want to see c code, add -S
	#$(PLTM_OBJDUMP) -d -S $@ > $@.dis
# if do not want to see c code to save assembly size, delete -S
#   $(PLTM_OBJDUMP) -d $@ > $@.dis
endif


#-------------------------------------------------------------------------------
# for checking multiple defined symbol, only B series
#-------------------------------------------------------------------------------
check_sym:
	@$(DIR_BUILD_POST)$(TARGET)/check_sym.pl -c$(COMPILER_VERSION) -o$(OUT) -v0  $(filter-out %.axf %.o, $(LINK))


clean_bin:
	-@$(CLEAN)  $(STEM).wpb  $(STEM).bin  $(STEM).elf  $(STEM).axf


ifneq ($(filter __EXTRACT_BOOT_IMAGE__  __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)

#-------------------------------------------------------------------------------
# generate critcal obj file list, # $(NON_CMPR_OBJ_LIST) is defined in $(NON_CMPR_OBJ_LIST_MAK)
#-------------------------------------------------------------------------------
$(NON_CMPR_OBJ_LIST_MAK): $(NON_CMPR_OBJ_LIST) $(DIR_BUILD_UTILITY)call_graph.pl
	$(WARN) generate $(NON_CMPR_OBJ_LIST_MAK), please wait...
	-@$(CLEAN) $(ALL_GROUP_SCATTER)
	$(MAKE_PREPROCESS_SCATTER)
ifeq (1,$(RELEASE_PROCESS))
	for f in $(full-paths-dsc); \
	do 	$(DIR_BUILD_POST)/link/find-rel-lib-path.pl -f=0 -l="$(shell echo $(filter-out $(OUT)%,$(LINK))| sed -e 's/[ 	][ 	]*/:/g')" $$f > $$f.relpath; 	done;
	$(DIR_BUILD_POST)/link/find-rel-lib-path.pl -f=1 -l="$(shell echo $(filter-out $(OUT)%,$(LINK))| sed -e 's/[ 	][ 	]*/:/g')" $(PATH_cust_scatter)scatter_85xx_stack_lib.dsc > $(PATH_cust_scatter)scatter_85xx_stack_lib.dsc.relpath;
endif
	$(PLTM_CC) $(SPECIAL_D) -E $(CFLAGS) -D__PRE_GEN_CALL_GRAPH__ -DRELEASE_PROCESS=$(RELEASE_PROCESS) -DTARGET=$(PRODUCT) -I$(PATH_kernel_hal)/inc $(SCATTER) > $(SCATTER_OUT)
	$(PLTM_LINK) $(LDFLAGS) --scatter $(SCATTER_OUT) -o $(STEM).elf2 $(LINK) $(CUST_ALL_OBJS_LIST) --callgraph
	$(DIR_BUILD_UTILITY)call_graph.pl 	-p $(PRODUCT) -c $(OUT)$(PRODUCT).htm -l $(OUT)link.info -f $(OUT)list_fun.mak 	-o $(NON_CMPR_OBJ_LIST_MAK) -z 2 \
      $(if $(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)), -e 1, -e 0)
endif


