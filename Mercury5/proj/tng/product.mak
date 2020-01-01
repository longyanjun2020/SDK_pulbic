
export TOP
export CONFIG_MAK
include $(COMMON)Dz_Config.mak
include $(COMMON)sdimg_config.mak

ifeq ($(FILE_CHECK),1)
include $(LIST_MODULE_MAK)
endif

ifeq "$(OSTYPE)" "Win32"
TNG_MAKE = @.\tng\log.pl $(LOG_FILE) $(TIME) $(MAKE) -r
else
TNG_MAKE = @$(TNG)log.pl $(LOG_FILE) $(TIME) $(MAKE) -r
endif

LOG_LINE = || $(TERROR) echo -e "*** ERRORS: for details use \"make log\" or look in file \"$(LOG_FILE)\" ***" > /dev/null

PRODUCT_MAK = $(COMMON)/normal_mak/product.mak

RELEASE_PROCESS?=0

# rules
.PHONY: product log final libs workspace dz_normal dz_redownload

product: workspace
ifeq ($(COMPILER_VERSION),AEONGCC)
ifneq ($(shell ./tng/leadingunderscore.sh),n)
	@echo -n -e "!!!!!! Please update toolchain from g1p. !!!!!!\n"; false
endif
endif
ifeq "$(OSTYPE)" "Win32"
	$(MAKE) -f  $(PRODUCT_MAK) product  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) product RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)
endif

# Turn on chip_mak if we need to check the consistency between chip makefile and excel file.
#workspace: out_dir chip_mak $(OUT)
workspace: out_dir $(OUT)



#-----------------------------------------------------------------------------
# go to final stage (post build)  e.g. genremtrace, link, tmt...
#-----------------------------------------------------------------------------
final: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE) -f  $(PRODUCT_MAK) final  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) final RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)
endif

libs: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE) -f  $(PRODUCT_MAK) libs  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) libs RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)
endif

sublibs: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) $(USER_LIB)  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) $(USER_LIB) RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)
endif


tags: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(TNG)tags.mak tags  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(TNG)tags.mak tags $(LOG_LINE)
endif



#-----------------------------------------------------------------------------
# MMI special rule
#-----------------------------------------------------------------------------
mmi: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi $(LOG_LINE)
endif

mmi_app: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)   -f $(PRODUCT_MAK) mmi_app  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_app $(LOG_LINE)
endif

mmi_srv: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi_srv  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_srv $(LOG_LINE)
endif

mmi_mae: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi_mae  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_mae $(LOG_LINE)
endif

mmi_core: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi_core  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_core $(LOG_LINE)
endif

mmi_common: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi_common  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_common $(LOG_LINE)
endif

mmi_cus: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mmi_cus  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mmi_cus $(LOG_LINE)
endif

mae_purelib: workspace
ifeq "$(OSTYPE)" "Win32"
	$(MAKE)  -f $(PRODUCT_MAK) mae_purelib  1>$(LOG_FILE)
else
	$(TNG_MAKE) -f $(PRODUCT_MAK) mae_purelib $(LOG_LINE)
endif


#-----------------------------------------------------------------------------
# generate out folder, the <ifeq "$(OSTYPE)" "Win32"> can not be removed since
# in configuration, the $(OSTYPE) is 'Win32', not 'cygwin'
# Warning, DO NOT remove <ifeq "$(OSTYPE)" "Win32"> ! it for configuration !!!
#-----------------------------------------------------------------------------
out_dir:
ifeq "$(OSTYPE)" "Win32"
	-$(MKDIR) $(OUT)
	-$(MKDIR) $(OUT)remtrace_lib
	-$(MKDIR) $(OUT)msg_id/
	-echo "<TNG>$(PRODUCT):	 done" > $(LOG_FILE)
else
	@$(MKDIR) $(OUT)
	@$(MKDIR) $(OUT)remtrace_lib
	@$(MKDIR) $(OUT)msg_id/
	@echo "<TNG>$(PRODUCT):	 done" > $(LOG_FILE)
endif


#-----------------------------------------------------------------------------
# incredibuild for MST
#-----------------------------------------------------------------------------
__ibuild_mst: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) ibuild_mst RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)

#-----------------------------------------------------------------------------
# fast build
#-----------------------------------------------------------------------------
__fast: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) fast RELEASE_PROCESS=$(RELEASE_PROCESS) $(LOG_LINE)

#-----------------------------------------------------------------------------
# clean_mmi_cus_temp_resource can not add dependence "workspace"
#-----------------------------------------------------------------------------
clean_mmi_cus_temp_resource:
	$(MAKE) -f $(PRODUCT_MAK) $@

#-------------------------------------------------------------------------------
# gen_path: generate path for auto deployment
#-------------------------------------------------------------------------------
_gen_path: workspace
	$(MAKE) -r -f $(PRODUCT_MAK) gen_path


#-------------------------------------------------------------------------------
# lint_preprocess
#-------------------------------------------------------------------------------
_lint_preprocess: workspace
	$(TNG_MAKE) -f $(PRODUCT_MAK) lint_preprocess RELEASE_PROCESS=$(RELEASE_PROCESS)


#-------------------------------------------------------------------------------
# By calling stage1 of library generation(tpp file generation)
# to checking files is existed or not
#-------------------------------------------------------------------------------
file_checking: workspace
	$(WARN) Finish source code checking

#-------------------------------------------------------------------------------
# gen all lib list
#-------------------------------------------------------------------------------
$(LIST_MODULE_MAK):
	$(MAKE_MODULE_MAKE_LIT)

#$(GLOBAL_HEADER_FILE):
#	@touch

#-----------------------------------------------------------------------------
# checking whether if chip.mak need to be updated or not
# Make sure the shell is executed only once
#-----------------------------------------------------------------------------
CHIP_MAK_VERIFY_RESULT=$(shell ./tng/genChipMak/check_chipmak_excel.sh)
OPTIONS_CHIP_MAK=options_$(BB_CHIP_ID).mak

chip_mak:
	@echo "Comparing the content of "$(OPTIONS_CHIP_MAK)" with options_summary_ChipSeries.xls..."
	@if [ ! -z '$(CHIP_MAK_VERIFY_RESULT)' ];then \
		if [ '$(CHIP_MAK_VERIFY_RESULT)' == 'file_not_exist' ];then \
			echo -e "\e[1m\e[34mFile $(COMMON)hal/options_summary_ChipSeries.xls does not exist.\n\e[0m";\
		elif [ '$(CHIP_MAK_VERIFY_RESULT)' == 'file_corrupted' ];then \
			echo -ne "\e[1m\e[31mFile $(COMMON)hal/options_summary_ChipSeries.xls is corrupted or is in wrong format.\nPlease re-sync file from P4 server and edit again.\n\e[0m";\
			read -t 1;\
		elif [ '$(CHIP_MAK_VERIFY_RESULT)' == 'mismatch' ];then \
			echo -ne "\e[1m\e[31m"\
			"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"\
			"!!!!!! options_$(BB_CHIP_ID).mak content mismatch with options_summary_ChipSeries.xls !!!!!!\n"\
			"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"\
			"Please edit chip options in options_summary_ChipSeries.xls,\n"\
			"then execute \"make gen_chip_mak\" to generate options_$(BB_CHIP_ID).mak.\n"\
			"Please don't edit options_$(BB_CHIP_ID).mak directly. It will be generated by \"make gen_chip_mak\".\e[0m\n";\
			read -t 1;\
		else\
			echo -ne "\e[1m\e[31m"$(CHIP_MAK_VERIFY_RESULT)"\n\e[0m";\
			read -t 1;\
		fi;\
	fi;


#-----------------------------------------------------------------------------
# checking whether to recommend to clean build or not
# AUTO_CLEAN = 1 : auto execute "make clean" command
# AUTO_CLEAN = 2 : skip checking
# otherwise            : checking whether to recommend to clean build or not
# Warning, DO NOT remove <ifeq "$(OSTYPE)" "Win32"> ! it for configuration !!!
#-----------------------------------------------------------------------------
$(OUT): $(COMMON)hal/options_$(BB_CHIP_ID).mak $(COMMON_PRODUCT_MAK) $(COMMON_OPTIONS_MAK) $(PATHS_MAK) $(_PATHS_MAK) $(PATHS_PUB) $(OPTIONS_CUS_MAK) $(TRACE_TABLE) $(MODULE_MAK_CHECKING_LIST) $(GLOBAL_HEADER_FILE) $(COMPILER_OPTION_MAK) ../tools/XRG/XRGConsole.exe $(feedback_server_backup)
	@echo -ne "product.mak ostype=$(OSTYPE)\n"
	@echo -ne "critical files: $^\n"
	#@$(INFO) "product.mak ostype=$(OSTYPE)\n"
ifeq "$(OSTYPE)" "Win32"
#	@echo $? has changed, please make clean. "Hit <Enter> to continue"
#	@pause
else
ifeq ($(AUTO_CLEAN),1)
	$(if $(filter 1, $(XRG)),echo -ne "XRG can't be set 1 when AUTO CLEAN is necessary" && false)
	@echo -ne "\e[1m\e[34m Start auto clean. \e[0m\n"
	@echo -ne "changed critical files: $?\n"
	$(MAKE) -f ./Makefile clean
	$(MAKE) -f ./Makefile out_dir
	@echo -n -e "\e[1m\e[34m End auto clean.\e[0m\n"
else
ifeq ($(AUTO_CLEAN),2)
else
	@echo -ne "$? has changed, please make clean\nHit <Enter> to skip make clean or <Ctrl+c> to stop \nIf no <Enter> detected in 90 seconds, make clean will auto-start\n";
	@read -t 90 || \
	( echo -ne "\n\e[1m\e[34m Start auto clean. \e[0m\n" && \
	$(MAKE) -f ./Makefile clean && \
	$(MAKE) -f ./Makefile out_dir && \
	echo -ne "\e[1m\e[34m End auto clean.\e[0m\n" )
endif ### AUTO_CLEAN == 2
endif ### AUTO_CLEAN == 1

ifeq ($(FILE_CHECK),1)
	$(WARN) Start source code checking
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	$(TNG_MAKE) -f $(PRODUCT_MAK) check_file_for_partial_code_P4_account $(LOG_LINE)
endif ### CHECK_FILE == 1
endif



#-----------------------------------------------------------------------------
# showing build log
#-----------------------------------------------------------------------------
log:
	@echo -n -e "\e[1m\e[34mChecking \"$(BUILD)$(PRODUCT)/log\" can get detailed build information.\e[0m\n";
	@$(TNG)sumup.pl $(LOG_FILE)

#-----------------------------------------------------------------------------
#
#-----------------------------------------------------------------------------
img:
	-$(CLEAN) $(BUILD)$(PRODUCT)/img/
	-$(MKDIR) $(BUILD)$(PRODUCT)/img/
	-$(MKDIR) $(BUILD)$(PRODUCT)/img/trace32
	-$(COPY) $(OUT)$(PRODUCT).bin $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)$(PRODUCT).wpb $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.CUS $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.cus $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.e2p $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)link.info $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)symdefs.info $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)backtraces.axf $(BUILD)$(PRODUCT)/img/trace32
	-$(COPY) $(OUT)$(PRODUCT).axf $(BUILD)$(PRODUCT)/img/trace32
	-$(CPDIR) $(BUILD)$(PRODUCT)/tmt/ $(BUILD)$(PRODUCT)/img/tmt/
	-$(COPY) $(OUT)*.wt $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.dll $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.pat $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.ini $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.bst $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)/app_calibration_table_$(CALTBL).c $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)/arp_calibration_table_$(CALTBL).c $(BUILD)$(PRODUCT)/img/
ifeq ($(filter __BOOTUP_LOGO_BY_E2P__ ,$(PP_OPT_COMMON)), __BOOTUP_LOGO_BY_E2P__)
	-$(COPY) $(OUT)/../boot_logo_param.h $(BUILD)$(PRODUCT)/img/
endif
ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
	-$(COPY) $(OUT)*.img $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)$(PRODUCT).prt $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.nni $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.pni $(BUILD)$(PRODUCT)/img/
	-$(COPY) $(OUT)*.ldr $(BUILD)$(PRODUCT)/img/
else
ifeq ($(filter __ONBOARD_USER_STORAGE_MMI__ ,$(PP_OPT_COMMON)), __ONBOARD_USER_STORAGE_MMI__)
	-$(COPY) $(OUT)custo_nor_*.wpb $(BUILD)$(PRODUCT)/img/
endif
ifeq ($(filter __SUPPORT_HIDDEN_PARTITION__ ,$(PP_OPT_COMMON)), __SUPPORT_HIDDEN_PARTITION__)
	-$(COPY) $(OUT)hidden_nor_*.fat $(BUILD)$(PRODUCT)/img/
endif
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)), MCP_CONFIG_TABLE)
	-$(COPY) $(OUT)MemSettings.prm $(BUILD)$(PRODUCT)/img/
endif
endif

#-----------------------------------------------------------------------------
# Generate SD download image
#-----------------------------------------------------------------------------
sd_normal: sdimg_start sdimg_normal sdimg_clean
	$(WARN) sdimg normal image finished.

sd_redownload: sdimg_start sdimg_redownload sdimg_clean
	$(WARN) sdimg redownload image finished.

sdimg_start:
	$(WARN) generate sdimg
	$(WARN) $(BUILD)$(PRODUCT)
	$(WARN) 1. Clean/Create Soruce/Destination Image Folder.
	-$(CLEAN) $(BUILD)$(PRODUCT)/$(MERGESDLOG)
	-$(CLEAN) $(BUILD)$(PRODUCT)/$(SRCFOLDER)/
	-$(CLEAN) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/
	-$(MKDIR) $(BUILD)$(PRODUCT)/$(SRCFOLDER)
	-$(MKDIR) $(BUILD)$(PRODUCT)/$(DSTFOLDER)
	$(WARN) 2. Copy MergeSD.exe to product folder.
	-$(COPY) $(MERGESD) $(BUILD)$(PRODUCT)

sdimg_normal:
	$(WARN) 3. Make DZ and copy to proudct folder as SD.zip.
	-$(MAKE) dz_normal
	-$(COPY) $(OUT)$(DZ_VERSION_STRING)dz $(BUILD)$(PRODUCT)/SD.zip
	$(WARN) 4. Unzip DZ file to source image folder.
	$(UNZIP) $(BUILD)$(PRODUCT)/SD.zip -d $(BUILD)$(PRODUCT)/$(SRCFOLDER)
	$(WARN) 5. Execute MergeSD.exe to generate SD image into temp SD image folder
ifndef SDTYPE
	$(MERGESD) -t dz_normal -p $(BUILD)$(PRODUCT) -s $(SRCFOLDER) -d $(DSTFOLDER) -l $(MERGESDLOG)
	-$(CLEAN) $(BUILD)$(PRODUCT)/$@
	-$(MKDIR) $(BUILD)$(PRODUCT)/$@
else
	$(MERGESD) -t $(SDTYPE) -p $(BUILD)$(PRODUCT) -s $(SRCFOLDER) -d $(DSTFOLDER) -l $(MERGESDLOG)
	-$(CLEAN) $(BUILD)$(PRODUCT)/sdimg_default
	-$(MKDIR) $(BUILD)$(PRODUCT)/sdimg_default
endif
	$(WARN) 6. Copy SD image from temp folder to final folder.
	-$(MAKE) sdimg_copy
ifndef SDTYPE
	-$(COPY) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/*.* $(BUILD)$(PRODUCT)/$@/
else
	-$(COPY) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/*.* $(BUILD)$(PRODUCT)/sdimg_default/
endif

sdimg_redownload:
	$(WARN) 3. Make DZ and copy to proudct folder as SD.zip.
	-$(MAKE) dz_redownload
	-$(COPY) $(OUT)$(DZ_VERSION_STRING)redownload.dz $(BUILD)$(PRODUCT)/SD.zip
	$(WARN) 4. Unzip DZ file to source image folder.
	$(UNZIP) $(BUILD)$(PRODUCT)/SD.zip -d $(BUILD)$(PRODUCT)/$(SRCFOLDER)
	$(WARN) 5. Execute MergeSD.exe to generate SD image into temp SD image folder
	$(MERGESD) -t dz_redownload -p $(BUILD)$(PRODUCT) -s $(SRCFOLDER) -d $(DSTFOLDER) -l $(MERGESDLOG)
	$(WARN) 6. Copy SD image from temp folder to final folder.
	-$(MAKE) sdimg_copy
	-$(CLEAN) $(BUILD)$(PRODUCT)/$@
	-$(MKDIR) $(BUILD)$(PRODUCT)/$@
	-$(COPY) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/*.* $(BUILD)$(PRODUCT)/$@/

sdimg_copy:
	$(WARN) 7. Copy sdtarge.bin, sdappram.bin, main descriptor, MemSettings.prm, sensor cus
	-$(COPY) $(SDAPPRAM_SRC) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/SDAPPRAM.BIN
	-$(COPY) $(SDTARGET_SRC) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/SDTARGET.BIN
	-$(COPY) $(BUILD)$(PRODUCT)/$(SRCFOLDER)/dsp.pat $(BUILD)$(PRODUCT)/$(DSTFOLDER)/DSP00000.PAT
	-$(COPY) $(MAINDES_SRC) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/MAIN0000.DES
ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)),)
	-$(COPY) $(BUILD)$(PRODUCT)/$(SRCFOLDER)/MemSettings.prm $(BUILD)$(PRODUCT)/$(DSTFOLDER)/MEM00000.PRM
endif
	-$(COPY) $(LCD_CUS) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/LCD00000.CUS
ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
	$(WARN) 8. Crete NAND FAT
	-$(MKDIR) $(BUILD)$(PRODUCT)/$(SDIMG)/fat
	$(WARN) 9. If user want to have the defualt data in normal or hidden FAT, it must assign normal or fidden folder.
	-$(MKDIR) $(FATNORMAL)
	-$(MKDIR) $(FATHIDDEN)
	$(PACKFAT) -n $(NANDINFO_NNI) -p $(PARTITION_PIN) -o $(BUILD)$(PRODUCT)/$(DSTFOLDER)/fat -x $(FATNORMAL) -y $(FATHIDDEN)
endif

sdimg_clean:
	$(WARN) 10. Clean all temp files
	-$(CLEAN) $(BUILD)$(PRODUCT)/$(SRCFOLDER)/
	-$(CLEAN) $(BUILD)$(PRODUCT)/$(DSTFOLDER)/
	-$(CLEAN) $(BUILD)$(PRODUCT)/SD.zip
	-$(CLEAN) $(BUILD)$(PRODUCT)/MergeSD.exe

#-----------------------------------------------------------------------------
# make clean command, it delete out folder and clean mmi temp resource and clean dlm pre
#-----------------------------------------------------------------------------
clean:
ifeq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)), __INFINITY__)
	-$(CLEAN) $(OUT)
	-$(CLEAN) $(LOG_FILE)
	-$(CLEAN) build/*.log
else
	-$(MAKE_DLM_PRE) clean_dlm_pre
	-$(MAKE) -f $(TNG)tags.mak clean
	-$(MAKE)  -f $(PRODUCT_MAK) clean_mmi_cus
	-$(MAKE)  -f $(PRODUCT_MAK) clean_logo
	-$(MAKE_TMT) clean
	-$(CLEAN) $(OUT)
	-$(CLEAN) $(LOG_FILE)
	-$(CLEAN) $(SC_LIB_LIST)
	-$(CLEAN) ../tools/XRG/XRGconsole/*.log
	-$(CLEAN) build/*.log
	@echo -n -e "\e[1m\e[34m reconfigure  PRODUCT = $(PRODUCT) $(P4_ACC)\e[0m\n";
	./tng/configure.pl $(PRODUCT) $(P4_ACC)
endif

clean_bin:
	@echo clean binary file
	@$(MAKE_LINK) $@

clean_dlm_pre:
	$(MAKE_DLM_PRE) $@

clean_sce:
	-$(CLEAN) $(OUT)*.sce $(OUT)mmi_scen.o $(OUT)mmi_scen.c

clean_e2p:
	-$(CLEAN) $(OUT)*.e2p


#-----------------------------------------------------------------------------
# partial clean,  command: make clean_lib TARGET=abc, e.g. make clean_lib TARGET=app
#-----------------------------------------------------------------------------
clean_lib:
	@$(MAKE) -f $(TNG)clean.mak



#-----------------------------------------------------------------------------
# clean mmi temp resource and opt
#-----------------------------------------------------------------------------
clean_libs:
	-$(MAKE) -f $(PRODUCT_MAK) clean
	-$(CLEAN) $(OUT)*.c
	-$(CLEAN) $(OUT)*.h*
	-$(CLEAN) $(OUT)*.asm
	-$(CLEAN) $(OUT)*.o
	-$(CLEAN) $(OUT)*.dfn
	-$(CLEAN) $(OUT)*.tpp
	-$(CLEAN) $(OUT)*.lib
	-$(CLEAN) $(OUT)*.lst



#-----------------------------------------------------------------------------
# generate package file for DwlWin factory mode
#-----------------------------------------------------------------------------
dz_normal:
	@$../../tools/DzPacker/DzPacker.exe -w . $(DZ_NORMAL_PARAMETER)

dz_redownload:
	@$../../tools/DzPacker/DzPacker.exe -w . $(DZ_REDOWNLOAD_PARAMETER)

gen_chip_mak:
	@tng/genChipMak/ChipMakExcelParser.exe -i $(COMMON)hal -o $(COMMON)hal -c options_summary_ChipSeries.xls
