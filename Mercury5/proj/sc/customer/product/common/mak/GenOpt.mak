#check whether compile option file has been changed or not
XRG_OPT:=$(TOP)../tools/XRG/option.rte.2005
XRG_ini:=$(TOP)XRG_config.ini
XRG_OPT_HEADER_FN:=option.h
XRG_OPT_Header:=$(TOP)../tools/XRG/$(XRG_OPT_HEADER_FN)
OPT_readme_file:=$(TOP)./sc/customer/product/CompilerOptionReadMe.txt

MStarStudio_OPT:=$(TOP)./MStarStudio_Config/option.rte.2005
MStarStudio_ini:=$(TOP)MStarStudio_config.ini
MStarStudio_OPT_Header:=$(TOP)./MStarStudio_Config/$(XRG_OPT_HEADER_FN)

GLOBAL_HEADER_FN:=global_config.h
XRG_GLOBAL_HEADER:=$(TOP)../tools/XRG/$(GLOBAL_HEADER_FN)
STRIP_PATH:=$(TNG)GenOpt/strip/

ifeq ($(COMPILER_VERSION),RVCTV22)
STRIPCC:=armcc
PREINCLUDE:= --preinclude
else
STRIPCC:=$(PLTM_CC)
PREINCLUDE:= -include
endif

OPT_GENEXE=$(TNG)GenComOpt.exe

.PHONY: .phony e2p_pc xrg_pre_load  clean_opt

#Generate PC simulator e2p
e2p_pc:
	$(WARN) generate e2p for mstar studio usage
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) init
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_pc
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_pc
	$(WARN) "============== Make Middleware e2p_lib_mrl E2P file ...            ============="
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_lib_mrl
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_lib_mrl
	$(WARN) "============== Make Application e2p_app E2P file ...            ============="
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_app
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_app
	$(WARN) "============== Make stack, calibration and custom E2P files ... ============="
	$(BIN)LoadConverter -enew $(OUT)v2751_app.e2p
	$(BIN)LoadConverter -enew $(OUT)v2751_lib.e2p
	$(BIN)LoadConverter -enew $(OUT)v2751_stack.e2p
	$(BIN)LoadConverter -enew $(OUT)stack_cus.e2p

ifeq ($(MMI_CUS_ONLY),1)
xrg_pre_load: $(XRG_OPT_Header) $(XRG_GLOBAL_HEADER) $(MStarStudio_OPT_Header) e2p_pc
else
xrg_pre_load: $(XRG_OPT_Header) $(XRG_GLOBAL_HEADER) $(MStarStudio_OPT_Header)
endif

$(XRG_OPT_Header): $(OPTIONS_CUS_MAK) $(COMMON_OPTIONS_MAK)
	$(WARN) Generate XRG Option File $(XRG_OPT_Header)
	$(COPY) $(TNG)/GenOpt/XRG_options.cfg $(TNG)options.cfg
ifneq ($(findstring $(OSTYPE),msys),)
	@cd $(NTG)/GenOpt && \
		cmd //c buildOpt_w32_setenv.bat
else
	$(TNG)/GenOpt/buildOpt_w32_setenv.bat
endif
	$(OPT_GENEXE) $(XRG_OPT) $(PP_OPT_COMMON) $(PP_OPT_TARGET)
	@perl $(TNG)/GenOpt/GenOpt_INI.pl $(XRG_ini) $(PRODUCT) $(XRG_OPT) $(OPT_readme_file)
	@perl $(TNG)/copy_rte_to_header.pl $(XRG_OPT) $(XRG_OPT_Header)
	@echo done

$(XRG_GLOBAL_HEADER): $(XRG_OPT_Header)
ifeq ($(GLOBAL_HEADER),TRUE)
	@$(STRIP_PATH)remccoms3.sed < $(GLOBAL_HEADER_FILE) > $(STRIP_PATH)$(GLOBAL_HEADER_FN)
	@cp -f $(XRG_OPT_Header) $(STRIP_PATH)
	@cd $(STRIP_PATH) && ./stripcc.exe -n -c "$(STRIPCC) $(PREINCLUDE) $(XRG_OPT_HEADER_FN) -E $(GLOBAL_HEADER_FN)" && rm -f $(XRG_OPT_HEADER_FN)
	@mv $(STRIP_PATH)$(GLOBAL_HEADER_FN) $(XRG_GLOBAL_HEADER)
endif
	@echo done

$(MStarStudio_OPT_Header): $(OPTIONS_CUS_MAK) $(COMMON_OPTIONS_MAK)
	$(WARN) Generate MStarStudio Option File $(MStarStudio_OPT_Header)
	$(COPY) $(TNG)/GenOpt/MStarStudio_options.cfg $(TNG)options.cfg
ifneq ($(findstring $(OSTYPE),msys),)
	@cd $(NTG)/GenOpt && \
		cmd //c buildOpt_w32_setenv.bat
else
	$(TNG)/GenOpt/buildOpt_w32_setenv.bat
endif
	$(OPT_GENEXE) $(MStarStudio_OPT) $(PP_OPT_COMMON) $(PP_OPT_TARGET)
	@perl $(TNG)/GenOpt/GenOpt_INI.pl $(MStarStudio_ini) $(PRODUCT) $(MStarStudio_OPT) $(OPT_readme_file)
	@perl $(TNG)/copy_rte_to_header.pl $(MStarStudio_OPT) $(MStarStudio_OPT_Header)
	$(RM) $(MStarStudio_OPT)
	@echo done

clean_opt:
	$(CLEAN) $(XRG_OPT)
	$(CLEAN) $(MStarStudio_OPT)
	$(CLEAN) $(XRG_OPT_Header)
	$(CLEAN) $(MStarStudio_OPT_Header)
	$(CLEAN) $(XRG_GLOBAL_HEADER)

