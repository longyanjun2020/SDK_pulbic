
#================================================= release.mak ============================================
export TOP
export CONFIG_MAK

TNG_MAKE = @$(TNG)log.pl $(LOG_FILE) $(TIME) $(MAKE) -r
#LOG_FILE = log
LOG_FILE=$(BUILD)$(PRODUCT)/log.release
LOG_LINE = || $(TERROR) echo -e "*** ERRORS: for details use \"make release_log\" or look in file \"$(LOG_FILE)\" ***" > /dev/null

PRODUCT_MAK = $(RELEASE_MAK)bld.mak

LIBS_DIR_BY_CHIP = ./sc/libs/$(LIBS_PATH_BY_CHIP)/
LIBS_DUP_DIR_BY_CHIP = ./sc/libs/$(LIBS_PATH_BY_CHIP)/dup/

# rules
.PHONY: product log final libs mmi_cus libs_mmi libs_mdl libs_3rd libs_drv libs_sys workspace e2p csn

product: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) product $(LOG_LINE)

workspace: $(OUT)

final: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) final $(LOG_LINE)

libs: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs $(LOG_LINE)

mmi_cus : workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_cus $(LOG_LINE)

libs_mmi: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs_mmi $(LOG_LINE)

libs_mdl: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs_mdl $(LOG_LINE)

libs_3rd: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs_3rd $(LOG_LINE)

libs_drv: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs_drv $(LOG_LINE)

libs_sys: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs_sys $(LOG_LINE)

tags: workspace
	$(TNG_MAKE) -f $(TNG)tags.mak tags $(LOG_LINE)

e2p: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) e2p $(LOG_LINE)

csn: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) csn $(LOG_LINE)

BACKUP_DIR = $(TOP)backup_src/
REL_DIR = $(TOP)rel_src/
MOVE = mv -f

#to filter $(LIBS_3RD) in $(OPY_LIB_IN_OUT)
3RD_LIB_IN_OUT = $(LIBS_3RD:%=$(OUT)%) $(EXT_LIBS:%=$(OUT)%)
ALL_LIB_IN_OUT = $(wildcard $(OUT)*.lib)
COPY_LIB_IN_OUT = $(filter-out $(3RD_LIB_IN_OUT), $(ALL_LIB_IN_OUT))

SCM_clean: $(OUT) csn
	$(MKDIR) $(LIBS_DIR_BY_CHIP)
	@../tools/XRG/gnu/bin/gcc -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/sys/src_cus/init.c > $(OUT)init.c.pp
	$(TDEBUG) $(TNG)RemoteDefs_Generator.pl -o $(LIBS_DIR_BY_CHIP)RemoteDefs.ini -i $(OUT) -s
	$(TNG_MAKE) -f $(PRODUCT_MAK) SCM_clean $(LOG_LINE)
	cp -r $(REL_DIR)sc $(TOP)
	$(CLEAN) $(REL_DIR)
	$(MKDIR) $(LIBS_DUP_DIR_BY_CHIP)
ifeq ($(call FIND_COMPILER_OPTION, __TARGET_DSP_PATCH_SOLO_BIN__), TRUE)
	$(COPY) $(OUT)dsp.par $(LIBS_DIR_BY_CHIP)dsp.par
	$(COPY) $(OUT)dsp.all $(LIBS_DIR_BY_CHIP)dsp.all
endif
	#$(COPY) $(OUT)init.o $(LIBS_DIR_BY_CHIP)init.lib
	@$(COPY_SOURCE_CODE_LIB)
	$(COPY) $(OUT)remtrace.csv $(LIBS_DIR_BY_CHIP)
	$(COPY) $(OUT)remtrace.ini $(LIBS_DIR_BY_CHIP)
	$(COPY) -r $(OUT)remtrace_lib $(LIBS_DIR_BY_CHIP)
	$(MKDIR) $(REL_DIR_MSG)
	-$(COPY) $(DIR_MSG)*_message_define__.hi $(REL_DIR_MSG)
	$(CLEAN) $(OUT)
#	rm $(OUT)*.c
#	rm $(OUT)*.asm

release_undo:
	cp -r $(BACKUP_DIR)sc $(TOP)
	cp -r $(REL_DIR)sc $(TOP)
	$(CLEAN) $(BACKUP_DIR)sc
	$(CLEAN) $(REL_DIR)sc

release_log:
	@echo -n -e "\e[1m\e[34mChecking \"$(BUILD)$(PRODUCT)/log.release\" can get detailed build information.\e[0m\n";
	@$(TNG)sumup.pl $(LOG_FILE)

release_%: workspace $(SC_LIB_LIST)
	$(MKDIR) $(OUT) $(LOG_LINE)
	$(MKDIR) $(OUT_DUP) $(LOG_LINE)
	-./sc/customer/product/common/mak/release_mak/dellibs.bat
	#$(COPY) $(LIBS_DIR_BY_CHIP)init.lib $(OUT)init.o $(LOG_LINE)
	$(TNG_MAKE) -f $(PRODUCT_MAK) $@ $(LOG_LINE)

BuildSubLib_fast: workspace $(SC_LIB_LIST)
	$(TNG_MAKE) -f $(PRODUCT_MAK) $@ \
		"'LIB_PARTIAL=$(LIB_PARTIAL)'" \
		$(LOG_LINE)

PURE_LIB_DEPEND_LIST := $(sort $(filter-out $(3RD_LIB_OUT) dlm_entry,\
	$(PRODUCT_SC) $(PRODUCT_SC_MDL) \
	$(PRODUCT_SC_DRV) $(PRODUCT_SC_SYS) \
	$(PRODUCT_SC_MMI) $(PRODUCT_SC_3RD) \
	$(PRODUCT_LIB) $(PRODUCT_LIB_MDL) \
	$(PRODUCT_LIB_DRV) $(PRODUCT_LIB_3RD) $(PRODUCT_LIB_SYS) $(PRODUCT_LIB_MMI)))

$(SC_LIB_LIST): $(wildcard $(foreach lib-name,$(PURE_LIB_DEPEND_LIST),$(PATH_$(lib-name))/$(lib-name)$(FLAVOR_$(lib-name)).mak))
	@echo generate pure lib list, please wait...;
	@$(GEN_SOURCE_CODE_LIB)

#$(OUT):: /
#	$(MKDIR) $@

$(OUT):: $(COMMON)hal/options_$(BB_CHIP_ID).mak $(COMMON_PRODUCT_MAK) $(COMMON_OPTIONS_MAK) $(PATHS_MAK) $(_PATHS_MAK) $(PATHS_PUB) $(OPTIONS_CUS_MAK) $(TRACE_TABLE)  $(GLOBAL_HEADER_FILE) $(COMPILER_OPTION_MAK) ../tools/XRG/XRGConsole.exe $(feedback_server_backup)
	@echo $? has changed !
	@echo It\'s better to make clean
	@sleep 3
	-$(CLEAN) $(SC_LIB_LIST)
	@echo generate pure lib list, please wait...;
	@$(GEN_SOURCE_CODE_LIB)
#	@exit 1

log:
	@$(TNG)sumup.pl $(LOG_FILE)

clean:
	-$(MAKE) -f $(TNG)tags.mak clean
	-$(MAKE_TMT) clean
	-$(CLEAN) $(OUT)
	-$(CLEAN) $(LOG_FILE)

clean_sce:
	-$(CLEAN) $(OUT)*.sce $(OUT)mmi_scen.o $(OUT)mmi_scen.c

clean_e2p:
	-$(CLEAN) $(OUT)*.e2p

clean_lib:
	-$(MAKE) -f $(TNG)clean.mak
