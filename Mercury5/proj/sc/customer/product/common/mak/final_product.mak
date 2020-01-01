#Ignored by mak parser
#================================================= product.mak ============================================

include $(CONFIG_MAK)
include $(PATH_common_mak)e2p_stack.mak
include $(PATH_common_mak)GenOpt.mak
include $(PATH_common_mak)driver_resource.mak
include $(TOP)/../proj/tng/cus/cus_parameter.mak
include $(TOP)/../proj/tng/cus/languagePack.mak

#-----------------------------------------------------------------------------
# include CL_LIST.mak for CTS per file scanning
#-----------------------------------------------------------------------------
ifeq "$(PER_FILE)" "1"
include CL_LIST.mak
endif

#parallel XRG
PARA_XRG ?= 0
PARA_XRG_HEADER ?= 0
ifeq ($(PARA_XRG_HEADER),1)
PARA_XRG=1
endif

TARGET = $(PRODUCT)
MAKE_EBT=$(MAKE) -r -f $(COMMON)cus_tmt.mak

#for release_build
LIBS_DIR_BY_CHIP 			:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/
LIBS_DUP_DIR_BY_FEATURE 	:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/dup/

RELEASE_PROCESS=0
PARAL_TPP=0

#parallel TPP with IBUILD
ifeq ($(IBUILD),1)
PARAL_TPP=1
endif

#Download size for DLM, SLDLM and SLDPM
DLM_CUS_LIST +=	$(wildcard $(OUT)DLM_bin.CUS )
DLM_CUS_LIST +=	$(wildcard $(OUT)SLDLM_bin.CUS)
DLM_CUS_LIST +=	$(wildcard $(OUT)DP_PAGE.CUS)

FIRST_CUS="$(firstword $(LANGUAGE_PACK_LIST))"
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
	FIRST_CUS = LangPack0000
endif


# driver rule 1
ifeq ($(call FIND_COMPILER_OPTION, __MULTIPLE_SENSOR_TABLE_DETECTION__), TRUE)
CHECK_CUS_EXIST += $(addprefix $(PATH_sensor),$(SENSOR_CUS_SRC))
CUS_LIST += $(SENSOR_CUS_FILE)
ifneq ($(strip $(FIRST_SENSOR_CUS)),)
CUS_LIST += $(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS)
endif # $(FIRST_SENSOR_CUS)
endif # __MULTIPLE_SENSOR_TABLE_DETECTION__

# driver rule 2
ifeq ($(call FIND_COMPILER_OPTION, __CUS_LCM_TABLE_DRV__), TRUE)
CHECK_CUS_EXIST +=  $(addprefix $(PATH_lcd_res)lcdtbl/,$(LCD_CUS_SRC))
CUS_LIST += $(LCD_CUS_FILE)
endif  # __CUS_LCM_TABLE_DRV__

#ifeq ($(call FIND_COMPILER_OPTION, __CUS_DISPLAY_TABLE_DRV__), TRUE)
#CHECK_CUS_EXIST +=  $(addprefix $(PATH_disp),$(DISP_CUS_SRC))
#CUS_LIST += $(DISPTBL_CUS_FILE)
#endif  # __CUS_DISPLAY_TABLE_DRV__

# driver rule 3
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
ifneq ($(strip $(FLASH_TYPE)),)
CHECK_FLASH_LIST = $(addprefix -f ,$(FLASH_TYPE))
endif
endif

LIBS = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC)) $(sort $(PRODUCT_LIB)))
LIBS_MDL = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC_MDL)) $(sort $(PRODUCT_LIB_MDL)))
LIBS_DRV = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC_DRV)) $(sort $(PRODUCT_LIB_DRV)))
LIBS_SYS = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC_SYS)) $(sort $(PRODUCT_LIB_SYS)))
LIBS_MMI = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC_MMI)) $(sort $(PRODUCT_LIB_MMI)))
LIBS_3RD = $(patsubst %,$(OUT)%.lib,$(sort $(PRODUCT_SC_3RD)) $(sort $(PRODUCT_LIB_3RD)))

ifeq ($(RELEASE_PROCESS),0)
LIBS_STACK2 = $(patsubst %,$(OUT_DUP)%_2.axf,$(sort $(PRODUCT_SC_STACK2)) $(sort $(PRODUCT_LIB_STACK2)))
endif


#include all libraries to build tpp concurrently
ALL_LIBS = $(PRODUCT_ALL)
ALL_LIBS_STACK2 = $(PRODUCT_ALL_STACK2)

LIBS_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC)) $(sort $(PRODUCT_LIB)))
LIBS_MDL_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC_MDL)) $(sort $(PRODUCT_LIB_MDL)))
LIBS_DRV_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC_DRV)) $(sort $(PRODUCT_LIB_DRV)))
LIBS_SYS_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC_SYS)))
LIBS_MMI_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC_MMI)) $(sort $(PRODUCT_LIB_MMI)))
LIBS_3RD_CLEAN = $(patsubst %,$(OUT)%.clean,$(sort $(PRODUCT_SC_3RD)))

### Add for XMMI
LIBS_MMI_APP = $(PRODUCT_SC_MMI_APP:%=$(OUT)%.lib)
LIBS_MMI_SRV = $(PRODUCT_SC_MMI_SRV:%=$(OUT)%.lib)
LIBS_MMI_MAE = $(PRODUCT_SC_MMI_MAE:%=$(OUT)%.lib)
LIBS_MMI_MAE_PORTING = $(PRODUCT_SC_MMI_MAE_PORTING:%=$(OUT)%.lib)
LIBS_MMI_CORE = $(PRODUCT_SC_MMI_CORE:%=$(OUT)%.lib)
LIBS_MMI_COMMON = $(PRODUCT_SC_MMI_MMICOMN:%=$(OUT)%.lib)
LIBS_MMI_WIDGET = $(PRODUCT_SC_MMI_WIDGET:%=$(OUT)%.lib)
LIBS_MMI_MODEL = $(PRODUCT_SC_MMI_MODEL:%=$(OUT)%.lib)
LIBS_MMI_SRVWRAPPER = $(PRODUCT_SC_MMI_SRVWRAPPER:%=$(OUT)%.lib)
LIBS_MMI_APPLAUNCHER = $(PRODUCT_SC_MMI_APP_LAUNCHER:%=$(OUT)%.lib)
LIBS_MMI_CUSDEFINE = $(PRODUCT_SC_MMI_CUSDEFINE:%=$(OUT)%.lib)
### end XMMI



#-----------------------------------------------------------------------------
# main target :
#-----------------------------------------------------------------------------
# Normal build
ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
ifeq ($(PARAL_TPP), 1)
ifeq ($(IBUILD_ENHANCE), 1)
product: build_preprocess versionUpdate mmi_cus libs mmi_enum driver_cus final
else
product: build_preprocess mmi_cus libs gen_stack2 libs_mdl libs_drv libs_sys libs_3rd libs_mmi driver_cus final
endif
else
ifeq ($(NoFinalAndDRVcusMMIcus), 1)
product: build_preprocess libs gen_stack2 libs_mdl libs_drv libs_sys libs_3rd libs_mmi
else
product: product_start restore_file_for_quick_build dlm_pre libs libs_mdl libs_drv libs_sys mmi_cus libs_3rd libs_mmi driver_cus final
endif
endif
else #__I_SW__
ifneq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),__INFINITY__)
product: product_start build_preprocess libs final
else
product: product_start restore_file_for_quick_build libs final
endif
endif

	$(WARN) done

#
# TODO: fix ibuild mst
#
ibuild_mst: build_preprocess mmi_cus csn csn2 all_libs_fast_release driver_cus final

# ibuild architecture, but using local build
fast: build_preprocess mmi_cus csn csn2 all_libs_fast mmi_enum driver_cus final
	$(WARN) done

#-------------------------------------------------------------------------------
# build_preprocess: handle some process before lib generation
#-------------------------------------------------------------------------------
build_preprocess: .phony product_start check_paths_3rd restore_file_for_quick_build feedback dlm_pre gen_patch_table drv_pre_process dump_compiler_option clean_updated_lib_list chk_pure_lib upadte_app_calibration_table upadte_arp_calibration_table ati2sati
	$(MKDIR) $(DIR_MSG)


#-------------------------------------------------------------------------------
# to check the modify time of paths_3rd.mak is newer than 3rd library?
# if yes, clean 3rd library
#-------------------------------------------------------------------------------
%.check_3rd:
	$(call do_if_order, \
		$(OUT)$*.dfn $(OUT)$*.tpp, \
		$(PATH_common_mak)paths_3rd.mak, \
		$(PRODUCT_SC_3RD:%=$(MAKE) clean_lib TARGET=%;) $(PRODUCT_LIB_3RD:%=$(MAKE) clean_lib TARGET=%;))

check_paths_3rd: $(PRODUCT_SC_3RD:%=%.check_3rd)  $(PRODUCT_LIB_3RD:%=%.check_3rd)


#-------------------------------------------------------------------------------
# record start time
#-------------------------------------------------------------------------------
product_start:
	@echo "<Build step: product_start>"
	@date


#-------------------------------------------------------------------------------
# delete following file to update sw version
#-------------------------------------------------------------------------------
versionUpdate: .phony
	$(CLEAN) $(OUT)sw_ver.c $(OUT)sw_ver.o $(OUT)sw_ver_cus.c $(OUT)sw_ver_cus.o
	$(CLEAN) $(OUT)cus_app.c $(OUT)cus_app.o $(OUT)mmi_common_info.c $(OUT)mmi_common_info.o $(OUT)init.o
	$(CLEAN) $(OUT)cus_app.tpp2 $(OUT)cus_app.rem
	#reserve for tmt stage
	#$(CLEAN) $(OUT)cus_app.tpp

#-------------------------------------------------------------------------------
# --feedback for armcc and armlink
#-------------------------------------------------------------------------------
feedback: $(feedback_out)

$(feedback_out): $(feedback_server)
	$(COPY) -fu $< $@

$(feedback_server): $(feedback_server_backup)
	$(WARN) "------------------------------------------------------"
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
	$(WARN) $@ is not existed, using backup file $(feedback_server_backup)
	$(COPY) -f  $(feedback_server_backup) $@
else
	$(WARN) $(feedback_server) is not existed, create it
	@echo ";" > $@;
endif
	$(WARN) please commit $(feedback_out) to $@ after build process is finish.
	$(WARN) "------------------------------------------------------"

$(feedback_server_backup):
	touch $@;

#-------------------------------------------------------------------------------
# generate display_table.txt, boot_logo.txt, sub_boot_logo.txt
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
drv_pre_process:
else
ifneq ($(call FIND_COMPILER_OPTION, __DUAL_LCD__), TRUE)
drv_pre_process: $(PATH_build)$(PRODUCT)/boot_logo.txt display_table
else
drv_pre_process: $(PATH_build)$(PRODUCT)/boot_logo.txt $(PATH_build)$(PRODUCT)/sub_boot_logo.txt display_table
endif
endif

ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)

ifeq ($(call FIND_COMPILER_OPTION, __PNG_BOOTUP_LOGO__), TRUE)
#### PNG bootlogo ####
$(PATH_build)$(PRODUCT)/boot_logo.txt: $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)

	$(WARN) "Converting .png boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)/*.png"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/boot_logo.txt"
	../tools/PngLogoConvert/PngToBin.exe -IPATH $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE boot_logo.txt -X $(LCM_WIDTH) -Y $(LCM_HEIGHT) -MAIN_SUB MAIN
	$(WARN) "done...\n"

ifeq ($(call FIND_COMPILER_OPTION, __DUAL_LCD__), TRUE)
$(PATH_build)$(PRODUCT)/sub_boot_logo.txt: $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)

	$(WARN) "Converting .png boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)/*.png"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/sub_boot_logo.txt"
	../tools/PngLogoConvert/PngToBin.exe -IPATH $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE sub_boot_logo.txt -X $(SUB_LCM_WIDTH) -Y $(SUB_LCM_HEIGHT) -MAIN_SUB SUB
	$(WARN) "done...\n"
endif

else
#### BMP bootlogo ####
ifeq ($(call FIND_COMPILER_OPTION, __BMP_BOOTUP_LOGO__), TRUE)
$(PATH_build)$(PRODUCT)/boot_logo.txt: $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)

	$(WARN) "Converting .bmp boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)/*.bmp"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/boot_logo.txt"
	../tools/BmpLogoConvert/ToRGB565.exe -IPATH $(PATH_cust_drv)lcm/logo/$(LCD_LOGO_BASE)/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE boot_logo.txt -ENDIAN 0 -COLOR 0 -X $(LCM_WIDTH) -Y $(LCM_HEIGHT) -MAIN_SUB MAIN
	$(WARN) "done...\n"

ifeq ($(call FIND_COMPILER_OPTION, __DUAL_LCD__), TRUE)
$(PATH_build)$(PRODUCT)/sub_boot_logo.txt: $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)

	$(WARN) "Converting .bmp boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)/*.bmp"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/sub_boot_logo.txt"
ifeq ($(strip $(SUB_LCM_WIDTH)), 0)
ifeq ($(strip $(SUB_LCM_HEIGHT)), 0)
	$(WARN) "Please give the correct option to \"LCM_SUB_RESOLUTION\" in options.mak"
	exit 1
endif
endif
	../tools/BmpLogoConvert/ToRGB565.exe -IPATH $(PATH_cust_drv)lcm/logo/$(SUB_LCD_LOGO_BASE)/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE sub_boot_logo.txt -ENDIAN 0 -COLOR 0 -X $(SUB_LCM_WIDTH) -Y $(SUB_LCM_HEIGHT) -MAIN_SUB SUB
	$(WARN) "done...\n"
endif
endif
endif #__PNG_BOOTUP_LOGO__

else #__COMPONENT_BASE_CONFIGURATION__


$(PATH_build)$(PRODUCT)/boot_logo.txt: $(PATH_cust_drv)/logo/main

	$(WARN) "Converting .bmp boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)/logo/main/*.bmp"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/boot_logo.txt"
	../tools/BmpLogoConvert/ToRGB565.exe -IPATH $(PATH_cust_drv)/logo/main/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE boot_logo.txt -ENDIAN 0 -COLOR 0 -X $(LCM_WIDTH) -Y $(LCM_HEIGHT) -MAIN_SUB MAIN
	$(WARN) "done...\n"

ifeq ($(call FIND_COMPILER_OPTION, __DUAL_LCD__), TRUE)
$(PATH_build)$(PRODUCT)/sub_boot_logo.txt: $(PATH_cust_drv)/logo/sub

	$(WARN) "Converting .bmp boot logo to binary array"
	$(WARN) "source: $(PATH_cust_drv)/logo/sub/*.bmp"
	$(WARN) "output: $(PATH_build)$(PRODUCT)/sub_boot_logo.txt"
ifeq ($(strip $(SUB_LCM_WIDTH)), 0)
ifeq ($(strip $(SUB_LCM_HEIGHT)), 0)
	$(WARN) "Please give the correct option to \"LCM_SUB_RESOLUTION\" in options.mak"
	exit 1
endif
endif
	../tools/BmpLogoConvert/ToRGB565.exe -IPATH $(PATH_cust_drv)/logo/sub/ -OPATH $(PATH_build)$(PRODUCT)/ -OUTFILE sub_boot_logo.txt -ENDIAN 0 -COLOR 0 -X $(SUB_LCM_WIDTH) -Y $(SUB_LCM_HEIGHT) -MAIN_SUB SUB
	$(WARN) "done...\n"
endif

endif #__COMPONENT_BASE_CONFIGURATION__

display_table:
	$(WARN) "Converting Display table(.dat) to display_table.txt"
	$(WARN) "source: $(PATH_customer_product_disptbl)DT_DEFAULT_$(Disptbl_IC_TYPE)_$(DISPTBL_DEFAULT).dat"
	$(WARN) "output: $(PATH_drv)lcd/inc/display_table.txt"
	../tools/DispTblConvert/Mst.exe -t "$(PATH_customer_product_disptbl)/DT_DEFAULT_$(strip $(Disptbl_IC_TYPE))_$(strip $(DISPTBL_DEFAULT)).dat" $(PATH_drv)/lcd/inc/display_table.txt
	$(WARN) "done...\n"

#-------------------------------------------------------------------------------
# Update APP and ARP Calibration Table
#-------------------------------------------------------------------------------
upadte_app_calibration_table: .phony
ifneq ($(strip $(TARGET_APP_ENGINE_ID)),)
	$(WARN) "Update APP Calibration Table"
	$(WARN) "option: $(TARGET_APP_ENGINE_ID)"
	$(WARN) "source: $(PATH_cust_drv)app_calibration_table/src/app_calibration_table_$(CALTBL).c"
	$(WARN) "output: $(PATH_cust_drv)app_calibration_table/src/app_calibration_table_$(CALTBL).c"
	../tools/AudCalibTableGTR/app_tgr.exe $(TARGET_APP_ENGINE_ID) $(PATH_cust_drv)app_calibration_table/src/app_calibration_table_$(strip $(CALTBL)).c $(PATH_cust_drv)app_calibration_table/src/app_calibration_table_$(strip $(CALTBL)).c
	$(WARN) "done...\n"
else
	$(WARN) "Because app_gtr.exe input option is empty, the app_gtr.exe process will be skipped"
endif

upadte_arp_calibration_table: .phony
ifneq ($(strip $(TARGET_ARP_ENGINE_ID)),)
	$(WARN) "Update ARP Calibration Table"
	$(WARN) "option: $(TARGET_ARP_ENGINE_ID)"
	$(WARN) "source: $(PATH_cust_drv)arp_calibration_table/src/arp_calibration_table_$(CALTBL).c"
	$(WARN) "output: $(PATH_cust_drv)arp_calibration_table/src/arp_calibration_table_$(CALTBL).c"
	../tools/AudCalibTableGTR/arp_tgr.exe $(TARGET_ARP_ENGINE_ID) $(PATH_cust_drv)arp_calibration_table/src/arp_calibration_table_$(strip $(CALTBL)).c $(PATH_cust_drv)arp_calibration_table/src/arp_calibration_table_$(strip $(CALTBL)).c
	$(WARN) "done...\n"
else
	$(WARN) "Because arp_gtr.exe input option is empty, the arp_gtr.exe process will be skipped"
endif
#-------------------------------------------------------------------------------
# Generate patch ID array for patches tracking
#-------------------------------------------------------------------------------
ifeq ($(RELEASE_PROCESS),1)
gen_patch_table: $(PATH_sc)/libs/patchlog
	$(WARN) "Converting patch ID to C string array"
	perl $(TNG)genPatchIdToArray.pl $(PATH_sc)/libs/patchlog $(PATH_application)/mmi/app/EmApp/inc/patchid_array.h
else
gen_patch_table:

endif

#-------------------------------------------------------------------------------
# dump compiler option in "(OUT)compiler_option.info"
# warn if null or false (case-insensitive
#-------------------------------------------------------------------------------
dump_compiler_option:
	if [ -e $(OUT)compiler_option.info ]; then\
		echo "$(OUT)compiler_option.info exist, delete it";\
		rm -f $(OUT)compiler_option.info;\
	fi;
	for defname in $(PP_OPT_COMMON);do\
		echo $$defname>>$(OUT)compiler_option.info;\
	done;
	@if grep -iq -w -e 'null' -e 'false' $(OUT)compiler_option.info; then \
		$(TWARN) echo -ne "NULL or FALSE is not allowed to define in compiler option!!\nplease check your compiler option in $(OUT)compiler_opiton.info\n"; \
		exit 1;\
	fi

#-------------------------------------------------------------------------------
# clean updated lib list
#-------------------------------------------------------------------------------
clean_updated_lib_list: .phony
	@echo 'LST_UPDATED_LIB=\' > $(UPDATED_LIB_LST)

chk_pure_lib:
ifeq ($(RELEASE_PROCESS),1)
	grep pure_lib_magic $(SC_LIB_LIST) || $(GEN_SOURCE_CODE_LIB)
else
	echo "normal build do nothing"
endif


#-------------------------------------------------------------------------------
# task priority
#-------------------------------------------------------------------------------
tsk_priority: .phony
	$(MAKE_TSK_PRIO)


#-------------------------------------------------------------------------------
# final process: handle some process after lib generation
#-------------------------------------------------------------------------------
ifeq ($(filter __X86LINUXGCC__, $(PP_OPT_COMMON)),__X86LINUXGCC__)
final:
	$(WARN) ABI check done!
else
ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
final: tsk_priority merge_remtrace install ud_ver_in_e2p e2p link mcpconfig_bin hwl_dsp_patch DwlWin_config nandprt wintarget bootup nvram cus conv fat_preload tmt dlchk dlm_bin prepare_file_for_quick_build sdtarget_cus
	@echo "<Build step: final completed>"
	@date
else
ifneq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),__INFINITY__)
final: install link mcpconfig_bin nandprt conv wintarget bootup
else
final: merge_remtrace install e2p link tmt tftp
endif
endif
endif

fat_preload:
ifeq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)), __DALVIK__)
	$(WARN) dalvik fat_preload
	@$(MKDIR) $(OUT)fat
	@$(MKDIR) $(OUT)fat/.system
	cp -f -r ./sc/application/3rd/dalvik/jar/* $(OUT)fat/.system
else
	$(WARN)
endif

merge_remtrace:
	$(WARN) merge remtrace
	$(TNG)remtrace/mergeRemtrace.pl $(OUT)

install:
	$(WARN) install
	$(MAKE_INSTALL)

scatter_dpm:
ifneq ($(filter AEONGCC_link MIPSGCC_link X86LINUXGCC_link ARMGCC_link, $(LINKER)), )
	$(PLTM_CC) $(CFLAGS) -I$(PATH_hal)/kernel/inc/ -E -P -xc $(PATH_cust_scatter)$(PRE_LOAD_DPM_SCRIPT) -o $(PATH_cust_scatter)$(DSC_DPM_FILE)
endif


#-------------------------------------------------------------------------------
# mcpconfig_bin
#-------------------------------------------------------------------------------
mcpconfig_bin:
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)),MCP_CONFIG_TABLE)
ifeq ($(call FIND_COMPILER_OPTION, __SAMSUNG_K5L2833ATA_PAGE_PAGE_MODE__), TRUE)
	cp -f $(PATH_common)mcpconfig_xml/$(MCPCONFIG_PAGE_PRM) $(OUT)
else
	$(TNG)McpConfig/xml2bin.exe -i $(PATH_common)mcpconfig_xml/$(MCPCONFIG_XML_FILE) -o $(OUT)MemSettings.prm
	$(BIN)LoadConverter -h16 $(OUT)MemSettings.prm -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 25
endif
	@echo "<Build step: mcpconfig_bin completed>"
else
	echo "MCP_CONFIG_TABLE not supported"
endif
endif






link:
	@echo "<***************** copy sdk lib to obj path**************************>"
	$(WARN) link 
ifneq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
	$(MAKE_LINK)
else
	$(MAKE_LINK) DUP_FLAG=0
endif
	@echo "<Build step: link completed>"
	@date
ifeq "$(OSTYPE)" "linux"
	$(WARN)  omit the procedure of $(PATH_project_Dvr_CarDV_SDK_downloadtool)
	$(WARN) cp $(OUT)$(BIN_FILES) $(PATH_project_Dvr_CarDV_SDK_downloadtool)
	$(COPY) $(OUT)$(BIN_FILES) $(PATH_project_Dvr_CarDV_SDK_downloadtool)
	@xz -z -k -f $(PATH_project_Dvr_CarDV_SDK_downloadtool)/$(BIN_FILES)
else
	$(WARN) copy $(OUT)$(BIN_FILES) $(PATH_project_Dvr_CarDV_SDK_downloadtool)
	$(COPY) $(OUT)$(BIN_FILES) $(PATH_project_Dvr_CarDV_SDK_downloadtool)
	@xz -z -k -f $(PATH_project_Dvr_CarDV_SDK_downloadtool)/$(BIN_FILES)
	$(WARN) DownloadTool.exe
	@cd $(PATH_project_Dvr_CarDV_SDK_downloadtool) && ./DownloadTool.exe /SIF
endif
	
link_dpm: scatter_dpm
	$(WARN) link_dpm
	$(MAKE_LINK_DPM)
	@echo "<Build step: link_dpm completed>"
	@date

ifeq ($(call FIND_COMPILER_OPTION, __COMPATIBLE_CHIP_SUPPORT__), TRUE)
DWL_COMMA = ,
ifneq ($(strip $(DZ_COMPATIBLE_CHIP)),)
DWL_COMPATIBLE = Compatible=$(subst +,$(DWL_COMMA),$(DZ_COMPATIBLE_CHIP))
endif
endif

dl_cfg:
	$(WARN) Generate dl_cfg.ini
	$(shell cp -af $(PATH_system)Wintarget/dl_cfg.ini $(OUT)/dl_cfg.ini)
	$(shell sed -i 's/CPU_TYPE=/CPU_TYPE=$(DWL_CPU_TYPE)/g' $(OUT)/dl_cfg.ini)
	$(shell sed -i 's/Flash_Mode=/Flash_Mode=$(DWL_FLASH_MODE)/g' $(OUT)/dl_cfg.ini)
	$(shell sed -i 's/EraseBackTrace=/EraseBackTrace=1/g' $(OUT)/dl_cfg.ini)
	$(shell sed -i 's/ChipType=/ChipType=$(DZ_CHIP_TYPE)/g' $(OUT)/dl_cfg.ini)
	$(shell sed -i 's/Compatible=/$(DWL_COMPATIBLE)/g' $(OUT)/dl_cfg.ini)
	$(shell unix2dos $(OUT)/dl_cfg.ini)

DwlWin_config: dl_cfg
ifeq ($(call FIND_COMPILER_OPTION, __FMS_E2P_ON_RAI__), TRUE)
	$(WARN) Generate DwlWin config
	$(BIN)GenDwlWinConfig.exe $(PATH_cust_sys)/src/fms_config.c $(OUT)config.ini
else
	rm -f $(OUT)config.ini
endif #__FMS_E2P_ON_RAI__

nandprt:
ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	$(WARN) nandprt
	$(MAKE_NAND) cpimg
	$(MAKE_NAND) mkimg
ifneq ($(filter KeyStone RDA8207_Si4220 RDA8207_Si4210 Si4229 RDA8207_Si4220_CanisV Si4229_CanisV, $(RF_TRANSCEIVER)),)
ifeq ($(filter KeyStone ,$(RF_TRANSCEIVER)),KeyStone)
	$(MAKE_NAND) mkprt RF=KeyStone
endif
ifeq ($(filter RDA8207_Si4220 ,$(RF_TRANSCEIVER)),RDA8207_Si4220)
	$(MAKE_NAND) mkprt RF=RDA8207_Si4220
endif
ifeq ($(filter RDA8207_Si4210 ,$(RF_TRANSCEIVER)),RDA8207_Si4210)
	$(MAKE_NAND) mkprt RF=RDA8207_Si4210
endif
ifeq ($(filter Si4229 ,$(RF_TRANSCEIVER)),Si4229)
	$(MAKE_NAND) mkprt RF=Si4229
endif
ifeq ($(filter RDA8207_Si4220_CanisV ,$(RF_TRANSCEIVER)),RDA8207_Si4220_CanisV)
	$(MAKE_NAND) mkprt RF=RDA8207_Si4220_CanisV
endif
ifeq ($(filter Si4229_CanisV ,$(RF_TRANSCEIVER)),Si4229_CanisV)
	$(MAKE_NAND) mkprt RF=Si4229_CanisV
endif
else
	$(MAKE_NAND) mkprt
endif
ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)), __G1__)
	$(MAKE_NAND) mkconfig
endif
else
	$(INFO) "nandprt" stage do nothing in this product
endif

sdtarget:
	$(WARN) sdtarget
	$(MAKE_SDTARGET)

sdtarget_genlib:
	$(WARN) sdtarget
	$(MAKE_SDTARGET) genlib

sdtarget_cus:
	$(WARN) sdtarget
	$(MAKE_SDTARGET) cus

ifeq ($(call FIND_COMPILER_OPTION, __DWL_ALL_DSP_SUPPORT__), TRUE)
DSP_PATCH_FILE=dsp.all
else
DSP_PATCH_FILE=dsp.par
endif

ifneq ($(call FIND_COMPILER_OPTION, __TARGET_DSP_PATCH_SOLO_BIN__), TRUE)
hwl_dsp_patch:
	rm -f $(OUT)dsp.pat
else # compiler option "__TARGET_DSP_PATCH_SOLO_BIN__" on
ifeq ($(RELEASE_PROCESS),0)

ifdef QUICK ###--> make quick

# "make quick"
hwl_dsp_patch: $(OUT)dsp.pat

$(OUT)dsp.pat: $(LIBS_DIR_FOR_QUICK)$(DSP_PATCH_FILE)
	$(WARN) copy $< to $@
	$(COPY) $< $@

else ###"make prepare" + "normal build"

# "make prepare"
hwl_dsp_patch:
	$(MAKE_DSP_PATCH) TARGET=$@ COMPILER=$(COMPILER_THUMB) OPTIMIZATION=OPTIMIZED_LEVEL_2 DUP_FLAG=0
ifeq ($(BB_CHIP_ID),msw8535x)
	$(BIN)DSPPatchPacker.exe -o $(OUT)dsp.pat $(OUT)hwldsp_spat_big2*.dsp
	$(BIN)LoadConverter -h16 $(OUT)dsp.pat -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 6
else
	$(BIN)DSPPatchPacker.exe -o $(OUT)dsp.all -p $(OUT) -c sc/telecom/hwl/hwldsp/src/dsp_spat_config_$(BB_CHIP_ID).txt -a
	$(BIN)DSPPatchPacker.exe -o $(OUT)dsp.par -p $(OUT) -c sc/telecom/hwl/hwldsp/src/dsp_spat_config_$(BB_CHIP_ID).txt
	$(BIN)LoadConverter -h16 $(OUT)dsp.all -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 6
	$(BIN)LoadConverter -h16 $(OUT)dsp.par -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 6
endif
	$(COPY) -fu $(OUT)$(DSP_PATCH_FILE) $(OUT)dsp.pat

ifdef PREPARE
	$(MKDIR)  $(LIBS_DIR_FOR_QUICK)
	$(COPY) -fu  $(OUT)dsp.all   $(LIBS_DIR_FOR_QUICK)dsp.all
	$(COPY) -fu  $(OUT)dsp.par   $(LIBS_DIR_FOR_QUICK)dsp.par
endif

endif ### end of ifdef QUICK

else # $(RELEASE_PROCESS)
hwl_dsp_patch: $(OUT)dsp.pat

$(OUT)dsp.pat: $(LIBS_DIR_BY_CHIP)$(DSP_PATCH_FILE)
	$(WARN) $@
	$(COPY) $< $@
endif  # $(RELEASE_PROCESS)

endif  # compiler option "__TARGET_DSP_PATCH_SOLO_BIN__"


wintarget:
	@if [ -e $(PATH_system)Wintarget ];then\
        echo $(PATH_system)Wintarget folder exists;\
        cp -f $(PATH_system)Wintarget/$(if $(WINTARGET_SRC),$(WINTARGET_SRC),$(WINTARGET)) \
            $(OUT)$(WINTARGET);\
    else\
        echo $(PATH_system)Wintarget folder does not exists;\
    fi;
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	cp -f $(PATH_system)Wintarget/$(MCPTARGET) \
	$(OUT)$(MCPTARGET);
endif
ifeq ($(MERGE_TO_BIN),MergeAll.dll)
ifeq ($(call FILE_EXISTED, $(PATH_system)Wintarget/$(MERGE_TO_BIN)), TRUE)
	echo "using $(PATH_system)Wintarget/$(MERGE_TO_BIN)"
	cp -f $(PATH_system)Wintarget/$(MERGE_TO_BIN) $(OUT)
endif
endif
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)), MCP_CONFIG_TABLE)
	cp -f $(PATH_system)Wintarget/MergeAll.dll $(OUT)
	cp -f $(PATH_system)Wintarget/config.ini $(OUT)
ifneq ($(filter __SMALL_ROM_32__ ,$(PP_OPT_COMMON)),)
	perl $(TNG)ConfiginiEdit.pl  $(OUT)config.ini 8 4 01000000
else
	perl $(TNG)ConfiginiEdit.pl  $(OUT)config.ini 8 4 00000000
endif
endif
endif


bootup:
ifneq ($(strip $(RAM_CLOCK)),)
	$(WARN) RAM setting: $(RAM_CLOCK)

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	-if [ $$(($(SYS_PHY_RAM_SIZE_SETTING))) -eq $$((0x4000000)) ]; then \
        echo "using $(PATH_system)BootUp/$(RAM_CLOCK)/64MB/$(BOOTLOADER)"; \
        cp -f $(PATH_system)BootUp/$(RAM_CLOCK)/64MB/$(BOOTLOADER) $(OUT); \
    else \
        echo "using $(PATH_system)BootUp/$(RAM_CLOCK)/$(BOOTLOADER)"; \
        cp -f $(PATH_system)BootUp/$(RAM_CLOCK)/$(BOOTLOADER) $(OUT); \
    fi
endif

ifeq ($(call FILE_EXISTED, $(PATH_system)BootUp/$(RAM_CLOCK)/$(BOOTSTRAP)), TRUE)
		echo "using $(PATH_system)BootUp/$(RAM_CLOCK)/$(BOOTSTRAP)"
		cp -f $(PATH_system)BootUp/$(RAM_CLOCK)/$(BOOTSTRAP) $(OUT)
endif

endif


tmt:
	$(WARN) tmt
	$(MAKE_TMT)
	$(MAKE_EBT)
	@echo "<Build step: tmt completed>"
	@date


tftp:
	$(WARN) "======== Generate new [[rtk.es ... ========"
	#-rm $(OUT)*.es
	#cp $(PATH_Boot_bin)/*.es $(OUT)
	#Mercury5 TBD. It causes error.
	#rm: cannot remove './build/316d_32_128_msw/out/*.es': No such file or directory
	#sed: can't read ./build/316d_32_128_msw/out/[[system.es: No such file or directory
	#sed -i "s/bin_name/$(PRODUCT).bin/g" $(OUT)[[system.es
	

#-------------------------------------------------------------------------------
#nvram
#-------------------------------------------------------------------------------
DBB_LIST := tdd fdd
PROTOCOL_TYPE := $(strip $(foreach dbb,$(DBB_LIST),$(findstring $(dbb),$(CUST_NVRAM_CFG))))
NVRAM_FILES := $(notdir $(wildcard $(PATH_nvram)nrw/*$(PROTOCOL_TYPE).*))

nvram:
ifeq ($(filter __UPGRADE_NVRAM__ ,$(PP_OPT_COMMON)), __UPGRADE_NVRAM__)

	cp -f $(PATH_nvram)$(CUST_NVRAM_CFG)/*.* $(OUT)
	cp -f $(PATH_nvram)common/*.* $(OUT)

#$(PRODUCT)
#	cp -f $(PATH_nvram)nro/audio_calibration_dbb_no_comments$(subst $(PROTOCOL_TYPE),,$(CUST_NVRAM_CFG)).nro $(OUT)audio_calibration_dbb_no_comments.nro
#ifeq ($(filter __UPGRADE_NVRAM_ENHANCED__ ,$(PP_OPT_COMMON)), __UPGRADE_NVRAM_ENHANCED__)
##	cp -f $(filter %.dll %.exe, $(wildcard $(PATH_nvram)nrw/*)) $(OUT)
#	cp -f $(PATH_nvram)nrw/nvram_rw_$(CUST_NVRAM_CFG).nrw $(OUT)
#	$(foreach file,$(NVRAM_FILES), \
 #     cp -f $(PATH_nvram)nrw/$(file) $(OUT)$(subst _$(PROTOCOL_TYPE),,$(basename $(file)))$(suffix $(file));)
#endif
endif

#-------------------------------------------------------------------------------
# Write version to e2p according to compile options
#-------------------------------------------------------------------------------
ud_ver_in_e2p: .phony
ifneq ($(strip $(DSP_VER)),)
ifneq ($(strip $(AEC_VER)),)
	$(WARN) "Write version to audioparam.e2p"
	$(WARN) "source: $(PATH_e2p_product)/audioparam_$(strip $(MAKE_AUD_E2P)).e2p"
	../tools/AudE2pVersion/WriteVerToE2p.exe $(DSP_VER) $(AEC_VER) $(PATH_e2p_product)/audioparam_$(strip $(MAKE_AUD_E2P)).e2p
	$(WARN) "done...\n"
else
	$(WARN) "Because WriteVerToE2p.exe input option is empty, the WriteVerToE2p.exe process will be skipped"
endif
endif

#-------------------------------------------------------------------------------
# e2p setting
#-------------------------------------------------------------------------------
PRODUCT_E2P_FILES := $(wildcard $(PATH_e2p_product)/*.*)
AUD_E2P := $(PATH_e2p_product)/audioparam_$(strip $(MAKE_AUD_E2P)).e2p
CUS_E2P := $(PATH_e2p_product)/cusSetting_$(strip $(MAKE_CUS_E2P)).e2p.val
FINAL_AUD_E2P := audioparam.e2p
FINAL_CUS_E2P := cusSetting.e2p.val
E2P_OVERWRITES =
ifneq ($(call FIND_COMPILER_OPTION, __BACKTRACE_COMPRESSED__), TRUE)
E2P_OVERWRITES += \
$(OUT)stack.e2p:WTrcNumberOf32k=4 \
$(OUT)stack.e2p:WTrcFormatChkSum=96
endif
#-------------------------------------------------------------------------------
# e2p
#-------------------------------------------------------------------------------
e2p:
	$(WARN) e2p
	rm -rf $(OUT)e2p
	-rm $(OUT)*.e2p
	@$(MKDIR) $(OUT)e2p
	cp $(PATH_e2p_common)/*.* $(OUT)e2p
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
	$(WARN) Case1
	cp $(AUD_E2P) $(OUT)e2p/$(FINAL_AUD_E2P)
	cp $(CUS_E2P) $(OUT)e2p/$(FINAL_CUS_E2P)
else
	$(WARN) Case2
	for file in $(PRODUCT_E2P_FILES); do \
		$(WARN) cp $$file $(OUT)e2p;\
		cp $$file $(OUT)e2p;\
	done
endif
	for file in $(OUT)e2p/*.*; do \
		echo >> $$file;\
	done
	chmod u+w $(OUT)e2p/*.*
	dos2unix $(OUT)e2p/*.*
	$(BIN)E2pBlender -c $(OUT)e2p/cusSetting.e2p.val -d $(OUT)e2p/*.e2p,$(OUT)e2p/*.e2p.val
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) init
	$(WARN) "============== Make stack, calibration and custom E2P files ... ============="
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_stack
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_stack
	$(WARN) "============== Make Middleware e2p_lib_mrl E2P file ...            ============="
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_lib_mrl
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_lib_mrl
	$(WARN) "============== Make Application e2p_app E2P file ...            ============="
	$(MAKE_E2P) COMPILER=$(COMPILER_ARM) TARGET=e2p_app
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) list TARGET=e2p_app
	cat $(OUT)e2p_app.h $(OUT)e2p_lib.h $(OUT)e2p_stack.h > $(OUT)e2p.h
	$(MAKE_E2PCE) COMPILER=$(COMPILER_ARM) final

	perl $(TNG)e2p_overwrite.pl $(E2P_OVERWRITES)

	perl $(TNG)genE2p_sym.pl $(OUT)
	@echo "<Build step: e2p completed>"
	perl $(TNG)genFactoryE2P.pl $(OUT)app.e2p $(OUT)z_factory.e2p
	@echo "<Build step: fac_e2p completed>"
	@date

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
E2P_HTML_FILES = $(PRODUCT)*.html
else
E2P_HTML_FILES = default_calibration*.html
endif


fac_e2p:
	perl $(TNG)genFactoryE2P.pl $(OUT)v2751_app.e2p $(OUT)z_factory.e2p
	@echo "<Build step: fac_e2p completed>"
	@date

BIN_FILES = $(PRODUCT).bin
ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRT_FILES = $(PRODUCT).prt
else
WPB_FILES = $(PRODUCT).wpb
endif
CUS_FILES = $(CUS_PROJECT_PERL).cus

ifeq ($(call FIND_COMPILER_OPTION, __TARGET_DSP_PATCH_SOLO_BIN__), TRUE)
FORCE_PATCH = 1
else
FORCE_PATCH = 0
endif

ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
FORCE_PATCH = 0
endif

E2P_FILE_LIST = $(wildcard $(OUT)*.e2p)
NVRAM_NRO_FILE_LIST = $(wildcard $(OUT)*.nro)
NVRAM_NRW_FILE_LIST = $(wildcard $(OUT)*.nrw)
EXTRA_PRTS := tdd fdd tdd-antf fdd-antf fdd-32m tdd-32m fdd-32m-antf tdd-32m-antf tdd-64m tdd-64m-antf tdd-32m-u01 tdd-32m-antf-u01 tdd-64m-u01 tdd-64m-antf-u01

conv:
	for file in $(E2P_FILE_LIST) $(NVRAM_NRO_FILE_LIST); do \
        $(BIN)LoadConverter -e32 $$file -dv $(DWLWIN_VER) -wv $(WINTARGET_VER);\
    done
	for file in $(NVRAM_NRW_FILE_LIST); do \
        $(BIN)LoadConverter -h16 $$file -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 2 -ForcePatch $(FORCE_PATCH); \
    done

	@echo "<Build step: conv e2p completed>"
	$(BIN)LoadConverter -bnew $(OUT)$(BIN_FILES) -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -ForcePatch $(FORCE_PATCH)
ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	$(BIN)LoadConverter -h16 $(OUT)$(PRT_FILES) -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 5 -ForcePatch $(FORCE_PATCH)
	for f in $(EXTRA_PRTS); do \
        if [ -e $(OUT)$(PRODUCT)-$$f.prt ]; then \
            $(BIN)LoadConverter -h16 $(OUT)$(PRODUCT)-$$f.prt -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 5 -ForcePatch $(FORCE_PATCH); \
            cp -f $(PATH_transceiver)$(RF_TRANSCEIVER)/g1upsdev-$$f.7z $(OUT); \
        fi \
    done
else
	$(BIN)LoadConverter -bnew $(OUT)$(WPB_FILES) -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -ForcePatch $(FORCE_PATCH)
endif # __NAND__
	@echo "<Build step: conv completed>"
	@date

$(E2P_TO_DWL): .phony
	$(WARN) convert e2p files $(OUT)$@
	$(BIN)LoadConverter -e32 $(OUT)$@ -dv $(DWLWIN_VER) -wv $(WINTARGET_VER)

ifeq ($(call FIND_COMPILER_OPTION, __AUTO_PARTITION__), TRUE)
NOR_FS_OPT += -a
endif
ifeq ($(call FIND_COMPILER_OPTION, __SUPPORT_HIDDEN_PARTITION__), TRUE)
NOR_FS_OPT += -h
endif
ifeq ($(call FIND_COMPILER_OPTION, __M18_MCP_SUPPORT__), TRUE)
NOR_FS_OPT += -m
endif
ifeq ($(call FIND_COMPILER_OPTION, __ONBOARD_USER_STORAGE_MMI__), TRUE)
NOR_FS_OPT += -u
endif

cus:
	$(WARN) cus
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	$(TNG)/nor_fs.pl $(NOR_FS_OPT)
endif
	$(WARN) "Copying Download sequence ini file."
	@cp $(PATH_common_mak)DlSequence.ini $(OUT)DlSequence.ini

#-------------------------------------------------------------------------------
# incredibuild for release package
#-------------------------------------------------------------------------------

#add parallel build command for generating TPP concurrently
all_tpp_rel:
	$(WARN) "calling all_tpp"
	$(REL_MAKE_ALLTPP) ALLTPP='$(ALL_LIBS)' ALLDUOTPP=''
	$(WARN) "leaving all_tpp"


#-------------------------------------------------------------------------------
# incredibuild for release package and pratial source code
#-------------------------------------------------------------------------------

REL_ALL_TPP_MAK=$(shell echo '$(REL_MAKE_ALLTPP) ALLTPP='\''$(ALL_LIBS)'\'' ALLDUOTPP='\''$(ALL_LIBS_STACK2)'\' | sed -e "s/\//\\\/g")
REL_XG_TPP_PROFILE=$(shell echo '$(TNG)incredibuild/tpp_profile.xml' | sed -e "s/\//\\\/g")

## STAGE1: generate .tpp files by ibuild
## STAGE2: A.sequentially call rtpp, and B.generate .o and .lib files by ibuild
all_libs_fast_release:
	@echo "<Build step: START fast library generation mode>"
	@date
ifeq ($(RELEASE_PROCESS),1)
	$(MAKE) -r -f $(TNG)lib_ib.mak IBUILD_ENHANCE=3
else
ifdef QUICK
	$(MAKE) -r -f $(TNG)lib_ib.mak IBUILD_ENHANCE=4
else
	$(error make should not go here...)
endif
endif
	@echo "<Build step: END fast library generation mode>"
	@date




all_libs_fast: .phony
	@echo "<Build step: START fast library generation mode>"
	@date
ifdef QUICK
	$(MAKE) -r -f $(TNG)lib_ib.mak IBUILD_ENHANCE=0 \
	'PRODUCT_SC=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_SC_3RD))' \
	\
	'PRODUCT_LIB=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter-out $(LIB_$(QUICK)_SET), $(PRODUCT_LIB_3RD))'
else
	$(MAKE) -r -f $(TNG)lib_ib.mak IBUILD_ENHANCE=0
endif
	@echo "<Build step: END fast library generation mode>"
	@date


#-------------------------------------------------------------------------------
#  incredibuild for full source code
#-------------------------------------------------------------------------------

#add parallel build command for generating TPP concurrently
ifeq ($(PARAL_TPP), 1)

ALL_TPP_MAK=$(shell echo '$(MAKE_ALLTPP) ALLTPP='\''$(ALL_LIBS)'\'' ALLDUOTPP='\''$(ALL_LIBS_STACK2)'\' | sed -e "s/\//\\\/g")
XG_TPP_PROFILE=$(shell echo '$(TNG)incredibuild/tpp_profile.xml' | sed -e "s/\//\\\/g")

all_tpp:
	@echo "<Build step: START all_tpp >"
	@date
ifeq ($(IBUILD),1)
	@echo XGConsole /command="$(ALL_TPP_MAK)" /profile="$(XG_TPP_PROFILE)" /openmonitor
	$(if $(findstring msys,$(OSTYPE)),\
		XGConsole //command="$(ALL_TPP_MAK)" //profile="$(XG_TPP_PROFILE)" //openmonitor,\
		XGConsole /command="$(ALL_TPP_MAK)" /profile="$(XG_TPP_PROFILE)" /openmonitor)
else
	$(MAKE_ALLTPP) ALLTPP='$(ALL_LIBS)' ALLDUOTPP='$(ALL_LIBS_STACK2)'
endif
	@echo "leaving all_tpp"
	@echo "<Build step: END all_tpp >"
	@date


ifeq ($(IBUILD), 1)
#libs: csn csn2 all_tpp
libs: csn csn2
	@echo "<Build step: start IBUILD_ENHANCE>"
	@date
	$(MAKE) -r -f $(TNG)lib_ib.mak IBUILD_ENHANCE=2
else
libs: csn csn2 all_tpp $(LIBS)
endif
else
libs: csn $(LIBS)
endif
	@echo "<Build step: libs completed>"
	@date

#= DUO section==================================================================

# -- Modification for project DUO
# Temporary solution to:
# 1. Combine the trace from original lib and the duplicated lib. The principle
#    is that there should only be one copy of remtrace throughout the process.
#    If the source files are being compiled in "dup" directory, the remtrace
#    files must be there. And after that, the remtrace files should be moved
#    back to it's original directory, $(OUT).
# 2. For csn files, it's different case from remtrace. Moving in/out the traces
#    everytime will cause .tpp/.dfn remaked everytime, which is a little
#    annoying. We simply use updating copy (cp with -u option) to make sure that
#    all the csn files included by duplicated modules are up to date.
#    ==> FIXME: "cp -u" may be not the best solution. Should we do this by dependency rules?
#

ifeq ($(RELEASE_PROCESS),0)
libs_stack2: $(LIBS_STACK2)
else
libs_stack2:
ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
	cp $(LIBS_DUP_DIR_BY_FEATURE)stack_2.axf $(OUT_DUP)/stack_2.axf
endif
endif

csn2:
ifeq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),)
	$(MKDIR) $(OUT_DUP)/csn
	cp -u $(OUT_ORG)csn/* $(OUT_DUP)/csn
endif

remtrace_in:
	-mv -f $(OUT_ORG)remtrace_lib $(OUT_DUP)remtrace_lib

remtrace_out:
	-mv -f $(OUT_DUP)remtrace_lib $(OUT_ORG)remtrace_lib

gen_stack2: csn2 remtrace_in libs_stack2 remtrace_out
ifeq ($(ABI_VER),)
	$(WARN) genstack2
	$(MAKE_STACK2)
	@echo "<Build step: gen_stack2 completed>"
	@date
endif

#===============================================================================

ifeq ($(RELEASE_PROCESS),0)
libs_mmi: $(LIBS_MMI) mmi_enum
	@echo "<Build step: libs_mmi completed>"
	@date
else
libs_mmi: $(LIBS_MMI)
	@echo "<Build step: libs_mmi completed>"
	@date
endif

libs_mdl: csn $(LIBS_MDL)
	@echo "<Build step: libs_mdl completed>"
	@date

libs_drv: csn $(LIBS_DRV)
	@echo "<Build step: libs_drv completed>"
	@date

libs_sys: csn $(LIBS_SYS)
	@echo "<Build step: libs_sys completed>"
	@date

libs_3rd: csn check_paths_3rd $(LIBS_3RD)
	@echo "<Build step: libs_3rd completed>"
	@date

mdl: libs_mdl final
drv: libs_drv final
sys: libs_sys final
3rd: libs_3rd final

release_mdl: libs_mdl final
release_drv: libs_drv final
release_sys: libs_sys final
release_3rd: libs_3rd final
release_libs: libs final
release_final: final
release_e2p: e2p

SCM_clean: $(LIBS_CLEAN) $(LIBS_MMI_CLEAN) $(LIBS_MDL_CLEAN) $(LIBS_3RD_CLEAN) $(LIBS_DRV_CLEAN) $(LIBS_SYS_CLEAN)
	$(WARN) clean garbage sources..
	@perl $(TNG)keepUnusedFiles.pl $(TOP)sc/ReleaseConfigurations.xml $(TOP)keepFiles.log
	$(TNG)garbage.pl $(TOP)sc

ifeq ($(PARAL_TPP), 1)
release_build: build_preprocess trace libs_stack2 mmi_cus all_tpp_rel $(PRODUCT_SC_CUS) $(LIBS) $(LIBS_MDL) $(LIBS_DRV) $(LIBS_SYS) $(LIBS_MMI) $(LIBS_3RD) driver_cus final e2p tmt
else
ifeq ($(NoFinalAndDRVcusMMIcus), 1)
release_build: build_preprocess  trace libs_stack2 $(PRODUCT_SC_CUS) $(LIBS) $(LIBS_MDL) $(LIBS_DRV) $(LIBS_SYS) $(LIBS_MMI) $(LIBS_3RD)
else
release_build: build_preprocess trace libs_stack2 $(PRODUCT_SC_CUS) $(LIBS) $(LIBS_MDL) $(LIBS_DRV) $(LIBS_SYS) mmi_cus $(LIBS_MMI) $(LIBS_3RD) driver_cus final e2p tmt
endif
endif
	$(WARN) done

release_ibuild: build_preprocess trace libs_stack2 mmi_cus versionUpdate all_libs_fast_release driver_cus final e2p tmt
	$(WARN) done

release_fast: build_preprocess trace libs_stack2 mmi_cus versionUpdate all_libs_fast_release driver_cus final e2p tmt
	$(WARN) done


### Added for XMMI
libs_mmi_app: $(LIBS_MMI_APP)
libs_mmi_srv: $(LIBS_MMI_SRV)
libs_mmi_mae: $(LIBS_MMI_MAE)
libs_mmi_mae_porting: $(LIBS_MMI_MAE_PORTING)
libs_mmi_core: $(LIBS_MMI_CORE)
libs_mmi_common: $(LIBS_MMI_COMMON)
libs_mmi_widget: $(LIBS_MMI_WIDGET)
libs_mmi_model: $(LIBS_MMI_MODEL)
libs_mmi_SrvWrapper: $(LIBS_MMI_SRVWRAPPER)
libs_mmi_AppLauncher: $(LIBS_MMI_APPLAUNCHER)


mmi: mmi_cus libs_mmi final
mmi_app: libs_mmi_app final
mmi_srv: libs_mmi_srv final
mmi_mae: libs_mmi_mae final
mmi_mae_porting: libs_mmi_mae_porting final
mmi_core: libs_mmi_core final
mmi_common: libs_mmi_common final
mmi_widget: libs_mmi_widget final
mmi_model: libs_mmi_model final
mmi_res: mmi_cus final
mmi_SrvWrapper: libs_mmi_SrvWrapper final
mmi_AppLauncher: libs_mmi_AppLauncher final

release_mmi: mmi_cus libs_mmi final
release_mmi_app: libs_mmi_app final
release_mmi_srv: libs_mmi_srv final
release_mmi_mae: libs_mmi_mae final
release_mmi_mae_porting: libs_mmi_mae_porting final
release_mmi_core: libs_mmi_core final
release_mmi_common: libs_mmi_common final
release_mmi_widget: libs_mmi_widget final
release_mmi_model: libs_mmi_model final
release_mmi_res: mmi_cus final
release_mmi_SrvWrapper: libs_mmi_SrvWrapper final
release_mmi_AppLauncher: libs_mmi_AppLauncher final
### End of XMMI

$(PRODUCT_SC_CUS): .phony
	$(WARN) $@
	$(MAKE_LIB) TARGET=$@ COMPILER=$(COMPILER_ARM)


#trace: $(OUT)remtrace.csv $(OUT)remtrace.ini
#include $(FEATURE_LIB_LIST_FILE) $(COMMON_LIB_LIST_FILE) $(NON_CRITICAL_TRACE_LIST)
include $(NON_CT_LIST) $(COMMON_LIB_LIST_FILE)

LIBS_DIR_COMMON				:= ./sc/libs/COMMON/
LIBS_DIR_CT_COMMON			:= ./sc/libs/COMMON/ct/

LIBS_DIR_BY_FEATURE 		:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/
#LIBS_DUP_DIR_BY_FEATURE 	:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/dup/
# critical trace libraries
LIBS_DIR_CT_COMMON			:= ./sc/libs/COMMON/ct/
LIBS_DIR_CT_BY_FEATURE 		:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/ct/
LIBS_DUP_DIR_CT_BY_FEATURE 	:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/dup/ct/

LIBS_DIR_BY_BSP				:= ./sc/libs/$(LIBS_PATH_BY_BSP)/
LIBS_DUP_DIR_BY_BSP			:= ./sc/libs/$(LIBS_PATH_BY_BSP)/dup/
LIBS_DIR_CT_BY_BSP			:= ./sc/libs/$(LIBS_PATH_BY_BSP)/ct/
LIBS_DUP_DIR_CT_BY_BSP		:= ./sc/libs/$(LIBS_PATH_BY_BSP)/dup/ct/

#LIBS_DIR_BY_CHIP 			:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/
LIBS_DUP_DIR_BY_CHIP 		:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/dup/
# critical trace libraries
LIBS_DIR_CT_BY_CHIP			:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/ct/
LIBS_DUP_DIR_CT_BY_CHIP		:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/dup/ct/

PURE_LIBS_GET_BY_AWK =$(shell awk '/LIB_LIST=/{next} /\\$$/{gsub(/\\/,""); printf("%s ",$$1);}' $(SC_LIB_LIST))

ifeq (LOG_LEVEL_CRITICAL_ONLY,$(strip $(LOG_LEVEL_CUT_OPTION)))

non-ct-libs-list		=$(filter $(NON_CRITICAL_TRACE_LIST),$(PURE_LIBS_GET_BY_AWK))
ct-libs-list			=$(filter-out $(NON_CRITICAL_TRACE_LIST),$(PURE_LIBS_GET_BY_AWK))

LIBS_COMMON_LIST		=$(call filter_common_libs,$(non-ct-libs-list))
CT_LIBS_COMMON_LIST		=$(call filter_common_libs,$(ct-libs-list))

LIBS_BY_FEATURE_LIST	=$(call filter_feature_libs,$(non-ct-libs-list))
CT_LIBS_BY_FEATURE_LIST	=$(call filter_feature_libs,$(ct-libs-list))

LIBS_BY_BSP_LIST		=$(call filter_bsp_libs,$(non-ct-libs-list))
CT_LIBS_BY_BSP_LIST		=$(call filter_bsp_libs,$(ct-libs-list))

LIBS_BY_CHIP_LIST		=$(call filter_chip_libs,$(non-ct-libs-list))
CT_LIBS_BY_CHIP_LIST	=$(call filter_chip_libs,$(ct-libs-list))
else
LIBS_COMMON_LIST		=$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK))
LIBS_BY_FEATURE_LIST	=$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK))
LIBS_BY_BSP_LIST		=$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK))
LIBS_BY_CHIP_LIST		=$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK))
endif

#copy-remtrace-to-out=$(if $(wildcard $(patsubst %,$(2)remtrace_lib/%_remtrace.*,$(1))),\
#	$(COPY) -fu $(wildcard $(patsubst %,$(2)remtrace_lib/%_remtrace.*,$(1))) $(OUT)/remtrace_lib/)

remtrace-csvs=\
			$(patsubst %,$(LIBS_DIR_COMMON)remtrace_lib/%_remtrace.csv,$(LIBS_COMMON_LIST)) \
			$(patsubst %,$(LIBS_DIR_CT_COMMON)remtrace_lib/%_remtrace.csv,$(CT_LIBS_COMMON_LIST)) \
			$(patsubst %,$(LIBS_DIR_BY_FEATURE)remtrace_lib/%_remtrace.csv,$(LIBS_BY_FEATURE_LIST)) \
			$(patsubst %,$(LIBS_DIR_CT_BY_FEATURE)remtrace_lib/%_remtrace.csv,$(CT_LIBS_BY_FEATURE_LIST)) \
			$(patsubst %,$(LIBS_DIR_BY_BSP)remtrace_lib/%_remtrace.csv,$(LIBS_BY_BSP_LIST)) \
			$(patsubst %,$(LIBS_DIR_CT_BY_BSP)remtrace_lib/%_remtrace.csv,$(CT_LIBS_BY_BSP_LIST)) \
			$(patsubst %,$(LIBS_DIR_BY_CHIP)remtrace_lib/%_remtrace.csv,$(LIBS_BY_CHIP_LIST)) \
			$(patsubst %,$(LIBS_DIR_CT_BY_CHIP)remtrace_lib/%_remtrace.csv,$(CT_LIBS_BY_CHIP_LIST))

existed-csvs	=$(wildcard $(remtrace-csvs))
lost-csvs		=$(filter-out $(existed-csvs),$(remtrace-csvs))

trace: $(OUT)remtrace_lib $(SC_LIB_LIST)
	$(if $(strip $(lost-csvs)),\
		echo "Warning: lost remtrace files $(lost-csvs)")
	$(COPY) -fu $(existed-csvs) $(wildcard $(patsubst %.csv,%.ini,$(existed-csvs))) $(OUT)/remtrace_lib/
	@$(TNG)remtrace/mergeRemtrace.pl $(OUT)

#trace: $(OUT)remtrace_lib $(SC_LIB_LIST)
#	@$(call copy-remtrace-to-out,$(LIBS_COMMON_LIST),$(LIBS_DIR_COMMON))
#	@$(call copy-remtrace-to-out,$(CT_LIBS_COMMON_LIST),$(LIBS_DIR_CT_COMMON))
#	@$(call copy-remtrace-to-out,$(LIBS_BY_FEATURE_LIST),$(LIBS_DIR_COMMON))
#	@$(call copy-remtrace-to-out,$(CT_LIBS_BY_FEATURE_LIST),$(LIBS_DIR_CT_BY_FEATURE))
#	@$(call copy-remtrace-to-out,$(LIBS_BY_BSP_LIST),$(LIBS_DIR_BY_BSP))
#	@$(call copy-remtrace-to-out,$(CT_LIBS_BY_BSP_LIST),$(LIBS_DIR_CT_BY_BSP))
#	@$(call copy-remtrace-to-out,$(LIBS_BY_CHIP_LIST),$(LIBS_DIR_BY_CHIP))
#	@$(call copy-remtrace-to-out,$(CT_LIBS_BY_CHIP_LIST),$(LIBS_DIR_CT_BY_CHIP))
#	@$(TNG)remtrace/mergeRemtrace.pl $(OUT)

#$(OUT)remtrace.csv: $(LIBS_DIR_BY_CHIP)remtrace.csv
#	$(WARN) $@
##	$(COPY) $< $@
#	-cp -r $(LIBS_DIR_BY_CHIP)remtrace_lib $(OUT)

#$(OUT)remtrace_lib: $(LIBS_DIR_BY_CHIP)remtrace_lib/
#	$(WARN) $@
#	$(COPY) -a $< $@


restore_file_for_quick_build: .phony
ifndef QUICK
ifeq ($(RELEASE_PROCESS),0)
# for normal build
	#-$(COPY) -fur $(TOP)libs/$(PRODUCT)_LIB_MSZ/remtrace_lib          $(OUT)
	#-chmod -R +w $(OUT)/remtrace_lib
else
# for relasee build
	-$(COPY) -fur $(REL_DIR_MSG) $(OUT)
endif
else
	$(WARN) resotre files...
	$(MAKE_RESTORE_FILE)
endif ### end of ifdef QUICK

prepare_file_for_quick_build: .phony
ifdef PREPARE
	$(WARN) prepare files...
	$(MKDIR)                         $(LIBS_DIR_FOR_QUICK)
	$(MAKE_PREPARE_FILE)
endif ### end of ifdef PREPARE


.PHONY: .phony libs gen_stack2 libs_stack2  libs_mdl libs_drv libs_sys libs_mmi libs_3rd csn final install link e2p cus tmt conv

csn:
ifeq ($(filter __INFINITY__ ,$(PP_OPT_COMMON)),)
	$(WARN) "This time we used $(NUM_THREAD) threads"
	@echo "<Build step: csn started>"
	@date
	$(WARN) $@
	$(MAKE_CSN)
	@echo "<Build step: csn completed>"
endif
	@date

atparser:
	$(WARN) $@
	$(MAKE_PARSER)

#-------------------------------------------------------------------------------
# add a dependence for dlm_entry
#-------------------------------------------------------------------------------
$(OUT)dlm_entry.lib: .phony dlm_pre

#-------------------------------------------------------------------------------
# for SCM_clean
#-------------------------------------------------------------------------------
$(OUT)%.clean:
	$(WARN) $@
	$(MAKE) -i -f $(RELEASE_MAK)clr.mak SCM_clean TARGET=$* $(COMPILER_CMD) $(CT_CMD)

#-------------------------------------------------------------------------------
# Normal section
#-------------------------------------------------------------------------------
$(OUT)%.lib: .phony versionUpdate
	$(WARN) $@ $(SHOW_COMPILER_MODE) $(SHOW_FEEDBACK_OPTION)
	$(call do_if_order,$(OUT)$*.dfn $(OUT)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,$(MAKE) clean_lib TARGET=$*;)
ifneq "$(PER_FILE)" "1"
	$(MAKE_LIB) TARGET=$* $(COMPILER_CMD) $(UT_CMD) $(CT_CMD) DUP_FLAG=0
else
ifdef CTS_SRC_C_LIST
	-grep -i -w $(CTS_SRC_C_LIST:%=-e %) $(PATH_$(*))/$*$(FLAVOR_$*).mak && \
		$(MAKE) clean_lib TARGET=$* && \
		$(MAKE_LIB) TARGET=$* $(COMPILER_CMD) $(UT_CMD) $(CT_CMD) DUP_FLAG=0
	-$(CLEAN) $(OUT)$*.dfn
endif
endif

$(EXISTED_LIBS): .phony
	$(WARN) "$(notdir $@) \t -LIBRARY"

#= DUO section==================================================================
# -- Modification for project DUO
# 1. This is the rule for compiling duplicated software modules.
# 2. The output is .axf because partial link is used instead of archive.
# 3. DUP_FLAG was introduced to make maximum reuse of lib.mak/tpp.mak/dfn.mak.
#
$(OUT_DUP)%_2.axf: .phony versionUpdate
	$(WARN) $@ $(SHOW_COMPILER_MODE) $(SHOW_FEEDBACK_OPTION)
ifneq "$(PER_FILE)" "1"
	$(MAKE_LIB) TARGET=$* $(COMPILER_CMD) $(UT_CMD) $(CT_CMD) DUP_FLAG=1
else
ifdef CTS_SRC_C_LIST
	-grep -i -w $(CTS_SRC_C_LIST:%=-e %) $(PATH_$(*))/$*$(FLAVOR_$*).mak && \
		$(MAKE) clean_lib TARGET=$* && \
		$(MAKE_LIB) TARGET=$* $(COMPILER_CMD) $(UT_CMD) $(CT_CMD) DUP_FLAG=1
	-$(CLEAN) $(OUT)$*.dfn
endif
endif


$(EXISTED_DUO_LIBS): .phony
	$(WARN) "$(notdir $@) \t -LIBRARY"


#===============================================================================



#-------------------------------------------------------------------------------
# Generate mmi enum tables
#-------------------------------------------------------------------------------
mmi_enum:
	@echo
	@echo "Generating mmi enumeration tables..."
	-@$(MAKE) -r -f enum.mak -C $(PATH_application)mmi/enum OUT=$(shell cygpath -a $(OUT))


#-------------------------------------------------------------------------------
# dlm
#-------------------------------------------------------------------------------
dlm_pre: .phony
	$(WARN) "dlm_pre step"
	$(MAKE_DLM_PRE)

dlm_bin: .phony
	$(WARN) "dlm_bin step"
	$(MAKE_DLM_BIN) RELEASE_PROCESS=$(RELEASE_PROCESS)

release_dlm_bin: .phony
	$(WARN) "dlm_bin step (release process)"
	$(MAKE_DLM_BIN) RELEASE_PROCESS=1

eml_bin: .phony
	$(WARN) "eml dlm_bin step"
	$(MAKE_EML_BIN)

dlm_ut_sys dlm_ut_drv dlm_ut_mdl dlm_ut_mmi dlm_ut_3rd dlm_general:
	$(WARN) $@ step
	$(MAKE_DLM_BIN) $@

OBJS=$(SRC_C_LIST:%.c=%.o) $(SRC_ASM_LIST:%.asm=%.o)

CLEAN_SRC_ASM_LIST=$(SRC_C_LIST:%.c=$(OUT)%.c)
CLEAN_SRC_C_LIST=$(SRC_ASM_LIST:%.asm=$(OUT)%.asm)
CLEAN_OBJS=$(OBJS:%.o=$(OUT)%.o)

clean_lib:
	$(CLEAN) $(CLEAN_SRC_ASM_LIST)
	$(CLEAN) $(CLEAN_SRC_C_LIST)
	$(CLEAN) $(CLEAN_OBJS)
	$(CLEAN) $(OUT)$(TARGET).dfn
	$(CLEAN) $(OUT)$(TARGET).tpp
	$(CLEAN) $(OUT)$(TARGET).lib

ifeq ($(PARA_XRG),1)
mmi_cus : cus_boot_log mmi_preprocess mmi_cus_common_header
else
mmi_cus : cus_boot_log mmi_preprocess mmi_cus_common
endif
debug_cus : mmi_preprocess debug_cus_common

cus_boot_log :
ifeq ($(filter  __CUS_BOOTUP_LOGO__ ,$(PP_OPT_COMMON)), __CUS_BOOTUP_LOGO__)
ifeq ($(filter  __PNG_BOOTUP_LOGO__ ,$(PP_OPT_COMMON)), __PNG_BOOTUP_LOGO__)
	$(shell sed -i 's/<item>boot_res_.*<\/item>/<item>boot_res_png<\/item>/g' $(PATH_customer_default)mmi/resource/$(CUS_PATH)/system/global/project/Boot.xml)
endif

ifeq ($(filter  __BMP_BOOTUP_LOGO__ ,$(PP_OPT_COMMON)), __BMP_BOOTUP_LOGO__)
	$(shell sed -i 's/<item>boot_res_.*<\/item>/<item>boot_res_bmp<\/item>/g' $(PATH_customer_default)mmi/resource/$(CUS_PATH)/system/global/project/Boot.xml)
endif
endif

mmi_preprocess:
	@echo "undefine layout id"
	$(TNG)undef_layout_id.pl

gen_lcd:
	make gen_lcd_

gen_lcd_update:
	tng/GenLCM/gen_lcm_global_base_script.pl > $(OUT)gen_lcm_script.log
	sc/customer/product/cust/drv/lcm/global_base/global_base_script.sh
	make gen_lcd_

gen_lcd_:
	mkdir -p $(PATH_cust_drv)lcm/allinone_base
	tng/GenLCM/GenLCM.exe -s -b $(PATH_cust_drv)lcm/cust_lcd_base.c -c tng/GenLCM/GenLCM.ini -o $(PATH_cust_drv)lcm/allinone_base/cust_lcd_drv_all.c $(wildcard $(PATH_cust_drv)lcm/global_base/*.c) 2>&1 | tee $(OUT)gen_lcd.log

mmi_cus_common_header: xrg_pre_load
	@echo "<Build step: START XRG Header >"
	@date
ifeq "$(OSTYPE)" "Win32"
	@echo "Generating mmi customization header files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	"..\tools\XRG\XRGConsole.exe" -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -header
	@echo "Finish header build"
else

ifneq ($(XRG),1)
ifneq ($(strip $(XRG_CUS)),)
	$(WARN) "Generating mmi customization header files (CUS=$(XRG_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(XRG_CUS) -header
	$(WARN) "Finish header build"
else
ifneq ($(XRG_FIRST_CUS),1)
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
	$(WARN) "Generating mmi customization header files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -header
	$(WARN) "Finish header build"
else
	$(WARN) "Generating mmi customization header files (LANGUAGE_PACK_LIST=$(LANGUAGE_PACK_LIST)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(LANGUAGE_PACK_LIST) -header
	$(WARN) "Finish header build"
endif # end of ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
else  # ifneq ($(XRG_FIRST_CUS),1)
	$(WARN) "Generating mmi customization header files (FIRST_CUS=$(FIRST_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(FIRST_CUS) -header
	$(WARN) "Finish header build"
endif # endif of ifneq ($(XRG_FIRST_CUS),1)
endif # end of ifneq ($(XRG_CUS), )
endif # end of ifneq ($(XRG),1)
endif # end of ifeq "$(OSTYPE)" "Win32"
	@echo "<Build step: END XRG Header>"
	@date

mmi_cus_common: xrg_pre_load
	@echo "<Build step: START XRG >"
	@date
ifeq "$(OSTYPE)" "Win32"
	@echo "Generating mmi customization files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	"..\tools\XRG\XRGConsole.exe" -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	@echo "Finish resource build"
else

ifneq ($(XRG),1)
ifneq ($(strip $(XRG_CUS)),)
	$(WARN) "Generating mmi customization files (CUS=$(XRG_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(XRG_CUS)
	$(WARN) "Finish resource build"
else
ifneq ($(XRG_FIRST_CUS),1)
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
	$(WARN) "Generating mmi customization files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(WARN) "Finish resource build"
else
	$(WARN) "Generating mmi customization files (LANGUAGE_PACK_LIST=$(LANGUAGE_PACK_LIST)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(LANGUAGE_PACK_LIST)
	$(WARN) "Finish resource build"
endif # end of ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
else  # ifneq ($(XRG_FIRST_CUS),1)
	$(WARN) "Generating mmi customization files (FIRST_CUS=$(FIRST_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(FIRST_CUS)
	$(WARN) "Finish resource build"
endif # endif of ifneq ($(XRG_FIRST_CUS),1)
endif # end of ifneq ($(XRG_CUS), )
endif # end of ifneq ($(XRG),1)
endif # end of ifeq "$(OSTYPE)" "Win32"
	@echo "<Build step: END XRG >"
	tng/cus/cus_sizeCheck.pl $(PRODUCT) $(CUS_PROJECT_PERL) $(CUS_MMAP_SIZE) $(CUS_MMAP_SUPPORT)
	@date

mmi_cus_common_cus: xrg_pre_load
	@echo "<Build step: START XRG Cus>"
	@date
ifeq "$(OSTYPE)" "Win32"
	@echo "Generating mmi customization cus files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	"..\tools\XRG\XRGConsole.exe" -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -cus
	@echo "Finish resource build"
else

ifneq ($(XRG),1)
ifneq ($(strip $(XRG_CUS)),)
	$(WARN) "Generating mmi customization cus files (CUS=$(XRG_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(XRG_CUS) -cus
	$(WARN) "Finish resource build"
else
ifneq ($(XRG_FIRST_CUS),1)
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
	$(WARN) "Generating mmi customization cus files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -cus
	$(WARN) "Finish resource build"
else
	$(WARN) "Generating mmi customization cus files (LANGUAGE_PACK_LIST=$(LANGUAGE_PACK_LIST)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(LANGUAGE_PACK_LIST) -cus
	$(WARN) "Finish resource build"
endif # end of ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
else  # ifneq ($(XRG_FIRST_CUS),1)
	$(WARN) "Generating mmi customization cus files (FIRST_CUS=$(FIRST_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(FIRST_CUS) -cus
	$(WARN) "Finish resource build"
endif # endif of ifneq ($(XRG_FIRST_CUS),1)
endif # end of ifneq ($(XRG_CUS), )
endif # end of ifneq ($(XRG),1)
endif # end of ifeq "$(OSTYPE)" "Win32"
	@echo "<Build step: END XRG Cus>"
	tng/cus/cus_sizeCheck.pl $(PRODUCT) $(CUS_PROJECT_PERL) $(CUS_MMAP_SIZE) $(CUS_MMAP_SUPPORT)
	@date

debug_cus_common: xrg_pre_load
	@echo "<Build step: START XRG2 Debug Mode>"
	@date
ifeq "$(OSTYPE)" "Win32"
	@echo "Gen mmi resource files... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	"..\tools\XRG\XRGConsole.exe" -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -d
	@echo "Finish resource build"
else

ifneq ($(XRG),1)
ifneq ($(strip $(XRG_CUS)),)
	$(WARN) "Gen mmi resource files (LP=$(XRG_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(XRG_CUS) -d
	$(WARN) "Finish resource build"
else
ifneq ($(XRG_FIRST_CUS),1)
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
	$(WARN) "Gen mmi resource files... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -d
	$(WARN) "Finish resource build"
else
	$(WARN) "Generating mmi customization files (LANGUAGE_PACK_LIST=$(LANGUAGE_PACK_LIST)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(LANGUAGE_PACK_LIST)
	$(WARN) "Finish resource build"
endif # end of ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
else  # ifneq ($(XRG_FIRST_CUS),1)
	$(WARN) "Generating mmi customization files (FIRST_CUS=$(FIRST_CUS)) ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp $(FIRST_CUS)
	$(WARN) "Finish resource build"
endif # endif of ifneq ($(XRG_FIRST_CUS),1)
endif # end of ifneq ($(XRG_CUS), )
endif # end of ifneq ($(XRG),1)
endif # end of ifeq "$(OSTYPE)" "Win32"
	@echo "<Build step: END XRG2 Debug Mode>"
	tng/cus/cus_sizeCheck.pl $(PRODUCT) $(CUS_PROJECT_PERL) $(CUS_MMAP_SIZE) $(CUS_MMAP_SUPPORT)
	@date

ifneq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
LCD_CUS_FOLDER =
endif


SENSOR_CUS_FROM_FOLDER := $(wildcard $(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)/*.dat) $(wildcard $(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)/*.DAT)
SENSOR_CUS_FROM_FOLDER_FILE:= $(subst $(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)/,"",$(SENSOR_CUS_FROM_FOLDER))
SENSOR_CUS_FROM_FOLDER_PREFIX:= $(SENSOR_CUS_FROM_FOLDER_FILE:.dat="")

LT_CUS_FROM_FOLDER := $(wildcard $(PATH_customer_product_lcm)$(LCD_CUS_FOLDER)/LT*.dat) $(wildcard $(PATH_customer_product_lcm)$(LCD_CUS_FOLDER)/LT*.DAT)
LT_CUS_FROM_FOLDER_FILE:= $(subst $(PATH_customer_product_lcm)$(LCD_CUS_FOLDER)/,"",$(LT_CUS_FROM_FOLDER))
LT_CUS_FROM_FOLDER_PREFIX:= $(LT_CUS_FROM_FOLDER_FILE:.dat="")


DISP_CUS_FROM_FOLDER := $(wildcard $(PATH_customer_product_disptbl)$(DISP_CUS_FOLDER)/DT_*.dat)
DISP_CUS_FROM_FOLDER_FILE:= $(subst $(PATH_customer_product_disptbl)$(DISP_CUS_FOLDER)/,"",$(DISP_CUS_FROM_FOLDER))
DISP_CUS_FROM_FOLDER_PREFIX:= $(DISP_CUS_FROM_FOLDER_FILE:.dat="")

driver_cus : $(CHECK_CUS_EXIST)
ifneq "$(OSTYPE)" "Win32"
ifeq ($(call FIND_COMPILER_OPTION, __SENSOR_LZF_SUPPORT__), TRUE)
ifeq ($(call FIND_COMPILER_OPTION, __MULTIPLE_SENSOR_TABLE_DETECTION__), TRUE)
	$(WARN) "Generating sensor customization files from $(PATH_sensor)"
	rm -rf $(OUT)sensor $(OUT)$(SENSOR_CUS_FILE)
	mkdir $(OUT$)sensor
	for PREFIX in $(SENSOR_CUS_LIST);do\
		"tng/MSComprs.exe" -f$(PATH_sensor)$$PREFIX.dat -o$(OUT)sensor/$$PREFIX.daf ;\
		"../tools/XRG/CusPack.exe" -i "$(OUT)sensor/$$PREFIX.daf" -o "$(OUT)sensor/$$PREFIX.cus";\
		"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)sensor/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET) -g 0;\
	done;
ifneq ($(strip $(SENSOR_CUS_FOLDER)),)
	$(WARN) "Generating sensor customization files from $(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)"
	for PREFIX in $(SENSOR_CUS_FROM_FOLDER_PREFIX);do\
		"tng/MSComprs.exe" -f"$(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)/$$PREFIX.dat" -o"$(OUT)sensor/$$PREFIX.daf" ;\
		"../tools/XRG/CusPack.exe" -i "$(OUT)sensor/$$PREFIX.daf" -o "$(OUT)sensor/$$PREFIX.cus";\
		"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)sensor/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET) -g 0;\
	done;
endif
	../tools/XRG/MergeCus.exe -f $(OUT)sensor -d $(OUT)$(SENSOR_CUS_FILE)
	for PREFIX in $(FIRST_SENSOR_CUS);do\
		$(WARN) "Generating first sensor customization files $(PATH_sensor)$(FIRST_SENSOR_CUS_SRC) ==> $(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus";\
		"tng/MSComprs.exe" -f"$(PATH_sensor)$(FIRST_SENSOR_CUS_SRC)" -o"$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).daf" ;\
		"../tools/XRG/CusPack.exe" -i "$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).daf" -o "$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus";\
		"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus" -dv $(DWLWIN_VER) -wv $(WINTARGET) -g 0;\
	done;
endif
else
ifeq ($(call FIND_COMPILER_OPTION, __MULTIPLE_SENSOR_TABLE_DETECTION__), TRUE)
	$(WARN) "Generating sensor customization files from $(PATH_sensor)"
	rm -rf $(OUT)sensor $(OUT)$(SENSOR_CUS_FILE)
	mkdir $(OUT$)sensor
	for PREFIX in $(SENSOR_CUS_LIST);do\
			"../tools/XRG/CusPack.exe" -i "$(PATH_sensor)$$PREFIX.dat" -o "$(OUT)sensor/$$PREFIX.cus";\
			"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)sensor/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
ifneq ($(strip $(SENSOR_CUS_FOLDER)),)
	$(WARN) "Generating sensor customization files from $(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)"
	for PREFIX in $(SENSOR_CUS_FROM_FOLDER_PREFIX);do\
			"../tools/XRG/CusPack.exe" -i "$(PATH_customer_product_sensor)$(SENSOR_CUS_FOLDER)/$$PREFIX.dat" -o "$(OUT)sensor/$$PREFIX.cus";\
			"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)sensor/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
endif
	../tools/XRG/MergeCus.exe -f $(OUT)sensor -d $(OUT)$(SENSOR_CUS_FILE)
	for PREFIX in $(FIRST_SENSOR_CUS);do\
		$(WARN) "Generating first sensor customization files $(PATH_sensor)$(FIRST_SENSOR_CUS_SRC) ==> $(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus";\
		"../tools/XRG/CusPack.exe" -i "$(PATH_sensor)$(FIRST_SENSOR_CUS_SRC)" -o "$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus";\
		"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)$(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
endif
endif

ifeq ($(call FIND_COMPILER_OPTION, __CUS_LCM_TABLE_DRV__), TRUE)
	$(WARN) "Generating lcd customization files from $(PATH_lcd_res)lcdtbl/"
	rm -rf $(OUT)lcd $(OUT)$(LCD_CUS_FILE)
	mkdir $(OUT$)lcd
	for PREFIX in $(LCD_CUS_LIST);do\
			"../tools/XRG/CusPack.exe" -t 1 -i "$(PATH_lcd_res)lcdtbl/$$PREFIX.dat" -o "$(OUT)lcd/$$PREFIX.cus";\
			"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)lcd/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
ifneq ($(strip $(LT_CUS_FROM_FOLDER_PREFIX)),)
	for PREFIX in $(LT_CUS_FROM_FOLDER_PREFIX);do\
			"../tools/XRG/CusPack.exe" -t 1 -i "$(PATH_customer_product_lcm)$(LCD_CUS_FOLDER)/$$PREFIX.dat" -o "$(OUT)lcd/$$PREFIX.cus";\
			"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)lcd/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
endif
	../tools/XRG/MergeCus.exe -f $(OUT)lcd -d $(OUT)$(LCD_CUS_FILE)
endif
	#rm -rf $(OUT)/sensor $(OUT)/lcd

ifeq ($(filter __CUS_DISPLAY_TABLE_DRV__ ,$(PP_OPT_COMMON)),__CUS_DISPLAY_TABLE_DRV__)
	$(WARN) "Generating display customization files from $(PATH_customer_product_disptbl)"
	rm -rf $(OUT)disptbl $(OUT)$(DISPTBL_CUS_FILE)
	mkdir $(OUT$)disptbl
	for PREFIX in $(DISPTBL_CUS_LIST);do\
            "../tools/XRG/CusPack.exe" -t 1 -i "$(PATH_customer_product_disptbl)/$$PREFIX.dat" -o "$(OUT)disptbl/$$PREFIX.cus";\
            "../tools/XRG/LoadConverter.exe" -cnew "$(OUT)disptbl/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
	for PREFIX in $(DISP_CUS_FROM_FOLDER_PREFIX);do\
            "../tools/XRG/CusPack.exe" -t 1 -i "$(PATH_customer_product_disptbl)/$(DISP_CUS_FOLDER)/$$PREFIX.dat" -o "$(OUT)disptbl/$$PREFIX.cus";\
		"../tools/XRG/LoadConverter.exe" -cnew "$(OUT)disptbl/$$PREFIX.cus" -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -g 0;\
	done;
	../tools/XRG/MergeCus.exe -f $(OUT)disptbl -d $(OUT)$(DISPTBL_CUS_FILE)

endif


	$(WARN) "Finish driver customization build"
endif

mmi_cus_lp:
	$(WARN) "Generating mmi customization LP files ... $(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml"
	$(TDEBUG) ../tools/XRG/XRGConsole.exe -build -Project "$(PATH_customer_default)mmi/resource/$(CUS_PATH)/$(CUS_PROJECT_PERL).xml" -lp XRG_AUTOMAX
	$(WARN) "Finish resource LP build"

clean_mmi_cus_temp_resource: .phony
	$(WARN) "Clean mmi temp files ..."
	$(CLEAN) $(BUILD)*.h
	$(CLEAN) $(BUILD)*.c
	$(CLEAN) $(BUILD)*.CUS
	$(CLEAN) $(BUILD)*.cus
	$(CLEAN) $(BUILD)*.readme

#-------------------------------------------------------------------------------
# Generate Slim_ATI files for library SLIM_ATI usage
#-------------------------------------------------------------------------------
ati2sati:
ifneq ($(RELEASE_PROCESS),1)
#ifndef QUICK
	$(WARN) "Duplicate the files in sc/telserv/ati/(ex.abc.c to abc_ati.c)..."
	-perl $(DIR_BUILD_PRE)/slim_ati/ati2sati.pl $(PATH_sc)/telserv/ati/src
#endif
endif
clean_mmi_cus: .phony clean_mmi_cus_temp_resource
	$(MKDIR) $(OUT)
	$(WARN) "Clean mmi customization files ... $(OUT)$(CUS_PROJECT_PERL)"
	$(CLEAN) $(OUT)$(CUS_PROJECT_PERL)
	$(WARN) "Clean mmi customization files ... $(OUT)$*.CUS"
	$(CLEAN) $(OUT)*.CUS
	$(CLEAN) $(OUT)*.cus
	$(WARN) "Clean mmi temp customization files ... $(OUT)$../$(CUS_PROJECT_PERL)"
	$(CLEAN) $(OUT)$/../$(CUS_PROJECT_PERL)

clean: clean_mmi_cus clean_opt

clean_mae:
	@$(MAKE) -s -f $(TNG)clean.mak TARGET=mae

clean_logo:
	$(WARN) "Clean boot logo files ... $(PATH_build)$(PRODUCT)/"
	$(CLEAN) $(PATH_build)$(PRODUCT)/boot_logo.txt
	$(CLEAN) $(PATH_build)$(PRODUCT)/boot_logo_default_dimension.txt
	$(CLEAN) $(PATH_build)$(PRODUCT)/boot_logo_param.h
	$(CLEAN) $(PATH_build)$(PRODUCT)/sub_boot_logo.txt
	$(CLEAN) $(PATH_build)$(PRODUCT)/sub_boot_logo_default_dimension.txt
	$(CLEAN) $(PATH_build)$(PRODUCT)/sub_boot_logo_param.h

clean_mmi:
	@$(MAKE) clean_lib TARGET=mae
	@$(MAKE) clean_lib TARGET=mae_porting
	@$(MAKE) clean_lib TARGET=core
	@$(MAKE) clean_lib TARGET=app
	@$(MAKE) clean_lib TARGET=srv
	@$(MAKE) clean_lib TARGET=mmicomn
	@$(MAKE) clean_lib TARGET=widget
	@$(MAKE) clean_lib TARGET=model
	@$(MAKE) clean_lib TARGET=SrvWrapper



#-------------------------------------------------------------------------------
# dlchk: download size checking
#-------------------------------------------------------------------------------
DOWNLOAD_CHECKER_SRC_C_LIST = mcp_drv_$(BB_CHIP_ID).c

ifneq ($(strip $(CHECK_SIZE_CRITICAL_MCP)),)
CHECK_CRITICAL_CMD = $(addprefix -r ,$(CHECK_SIZE_CRITICAL_MCP))
endif
ifneq ($(strip $(PRODUCT_SIZE)),)
PRODUCT_SIZE_CMD = -p $(PRODUCT_SIZE)
endif

dlchk:
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
ifneq "$(OSTYPE)" "Win32"
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)), MCP_CONFIG_TABLE)
	$(WARN) Do size checking based on default.xml.
else
	$(WARN) Do size checking based on $(DOWNLOAD_CHECKER_SRC_C_LIST).
endif
	cp $(PATH_customer_default)drv/acc/src/$(DOWNLOAD_CHECKER_SRC_C_LIST) $(OUT)check_mcp.c -f
	#@cp $(PATH_drv)acc/pub/mcp_drv_pub_types.h $(OUT) -f
	#@cp -t $(OUT) $(PATH_fc)/pub/vm_types.ht $(PATH_fc)/pub/comdefs.hc -f
	#@cp -t $(OUT) $(PATH_flash)/pub/drv_flash_lowl_ho_pub.h $(PATH_flash)/pub/drv_flash_lowl_ht_pub.h -f
	#@cp $(PATH_drv)flash/inc/*.* $(OUT) -f
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)), MCP_CONFIG_TABLE)
	@cp $(PATH_chk)src/Download_CheckerNew.c $(OUT)Download_Checker.c -f
else
	@cp $(PATH_chk)src/Download_Checker.c $(OUT) -f
endif
	@cp $(PATH_chk)inc/Download_Checker.h $(OUT) -f
	@cp $(PATH_chk)src/CompressRatioCounter.c $(OUT) -f
	@cp $(PATH_chk)inc/CompressRatioCounter.h $(OUT) -f

	$(CC) -I$(PATH_drv)acc/pub/ -I$(PATH_fc)/pub/ -I$(PATH_flash)/pub/ -I$(PATH_drv)/flash/inc -I$(PATH_emi)/inc -I$(PATH_emi)/pub -I$(PATH_clkgen)/inc -I$(PATH_sys)/pub $(OUT)Download_Checker.c $(OUT)CompressRatioCounter.c -o $(OUT)$(DOWNLOAD_CHECKER) $(addprefix -D,$(PP_OPT_COMMON))
	$(CC) -I$(PATH_drv)acc/pub/ -I$(PATH_fc)/pub/ -I$(PATH_flash)/pub/ -I$(PATH_drv)/flash/inc -I$(PATH_emi)/inc -I$(PATH_emi)/pub -I$(PATH_clkgen)/inc -I$(PATH_sys)/pub $(OUT)Download_Checker.c $(OUT)CompressRatioCounter.c -o $(DOWNLOAD_CHECKER) $(addprefix -D,$(PP_OPT_COMMON))
	$(TINFO) $(OUT)$(DOWNLOAD_CHECKER) -o $(OUT) $(addprefix -c ,$(CUS_LIST)) $(addprefix -dlm ,$(DLM_CUS_LIST)) -b $(BIN_FILES) $(CHECK_FLASH_LIST) -g $(OUT)checksize.sh $(CHECK_CRITICAL_CMD) $(PRODUCT_SIZE_CMD)
# to check if there are critical path
ifneq ($(filter __EXTRACT_BOOT_IMAGE__  __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
	$(DIR_BUILD_UTILITY)call_graph.pl -t 1	-p $(PRODUCT) -c $(OUT)$(PRODUCT).htm -l $(OUT)link.info -f $(OUT)list_fun.mak 	-o $(NON_CMPR_OBJ_LIST_MAK) -z 2 \
      $(if $(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)), -e 1 -n 1000 -s 48, -e 0 -n 1000 -s 36) -t 1 -r CheckLog.txt
endif
endif
	@$(COPY) -f CheckLog.txt $(OUT)
endif  # Win32
endif
ifeq ($(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),__COMPRESS_SELECTED_BIN__)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
	$(DIR_BUILD_POST)/link/link_utility.pl -f 3 -l $(OUT)link.info -w $(OUT)list_fun.mak -s $(if $(filter 1,$(RELEASE_PROCESS)),104448,92126)
endif
endif


mmi_cus_addition:

ifeq "$(OSTYPE)" "Win32"
	@echo $(CUS_LP_NAME)
	@echo "Generating mmi additional customization files ... "
	$(CLEAN) $(subst /,\,$(OUT))$(CUS_PROJECT_PERL).cus
	${COPY} -f $(subst /,\,$(OUT))$(CUS_LP_NAME).cus .\MStarStudio_UP\MStarDeveloper\XMMI\debug\$(CUS_LP_NAME).cus
#	${COPY} -f ..\tools\xiToolSet\$(CUS_LP_NAME).CUS .\MStarStudio_UP\MStarDeveloper\XMMI\debug\$(CUS_PROJECT_PERL).cus
	$(BIN)LoadConverter -cnew $(subst /,\,$(OUT))$(CUS_LP_NAME).cus
#	$(BIN)LoadConverter -cnew $(subst /,\,$(OUT))$(CUS_PROJECT_PERL).cus

	@echo "Finish additional resource build"
else
	$(WARN) $(CUS_LP_NAME)
	$(WARN) "Generating mmi additional customization files ... "
	$(CLEAN) $(OUT)$(CUS_PROJECT_PERL).cus
	$(TDEBUG) cp $(OUT)$(CUS_LP_NAME).cus .\MStarStudio_UP\MStarDeveloper\XMMI\debug\$(CUS_LP_NAME).cus
#	$(TDEBUG) cp ../tools/xiToolSet/$(CUS_LP_NAME).CUS ./MStarStudio_UP/MStarDeveloper/XMMI/debug/$(CUS_PROJECT_PERL).cus
	$(TDEBUG) $(BIN)LoadConverter -cnew $(OUT)$(CUS_LP_NAME).cus
#	$(TDEBUG) $(BIN)LoadConverter -cnew $(OUT)$(CUS_PROJECT_PERL).cus

	$(WARN) "Finish additional resource build"
endif


#-------------------------------------------------------------------------------
# Partial Make
#-------------------------------------------------------------------------------
BuildSubLib1:
	@$(MAKE) -r -s product \
	NoFinalAndDRVcusMMIcus=1 \
	QUICK=$(QUICK) \
	SPEED=$(SPEED) \
	ABI_VER=$(ABI_VER) \
	AUTO_CLEAN=$(AUTO_CLEAN) \
	NUM_THREAD=$(NUM_THREAD) \
	NUM_THREAD_FOR_TPP=$(NUM_THREAD_FOR_TPP) \
	PARTIAL_BUILD=1 \
	PARAL_TPP=$(PARAL_TPP)

BuildSubLib: check_paths_3rd
	@$(MAKE) -r -s product \
	NoFinalAndDRVcusMMIcus=1 \
	QUICK=$(QUICK) \
	SPEED=$(SPEED) \
	AUTO_CLEAN=$(AUTO_CLEAN) \
	NUM_THREAD=$(NUM_THREAD) \
	NUM_THREAD_FOR_TPP=$(NUM_THREAD_FOR_TPP) \
	PARAL_TPP=$(PARAL_TPP) \
	PARTIAL_BUILD=1 \
	\
	$(if $(LIB_PARTIAL),\
	'PRODUCT_SC=$(filter $(LIB_PARTIAL), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_3RD))' \
	\
	'PRODUCT_LIB=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_3RD))'\
	)

BuildSubLib_fast : check_paths_3rd
	@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) \
	PARTIAL_BUILD=1 \
	\
	'PRODUCT_SC=$(filter $(LIB_PARTIAL), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_3RD))' \
	\
	'PRODUCT_LIB=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_3RD))'



#-------------------------------------------------------------------------------
# cust_check: check if some sources in cust_drv are able to be built
#-------------------------------------------------------------------------------
LCD_FILES = $(filter-out ./sc/customer/product/cust/drv/lcm/cust_lcd_base.c, $(shell find ./sc/customer/product/cust/drv/lcm -name 'cust_lcd_*.c'))
cust_check: csn build_preprocess
	echo "cust_check begin"
	for c_file in ${LCD_FILES}; do $(TDEBUG) $(PLTM_CC) -c $(CFLAGS) $(PATH_H:%=-I%) -I$(PATH_lcd_hal)/inc -I$(PATH_disp)/pub -I$(PATH_lcd)/pub -I$(PATH_gpd)/pub -o $(OUT)temp.o $$c_file || exit 1; done
	$(shell rm $(OUT)temp.o)
	-$(MAKE_LIB) TARGET=cust_drv_check $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=0 && echo "cust_check done" > $(OUT)/cust_check.log
	$(MAKE) clean_lib TARGET=cust_drv_check
	echo "cust_check end"

#-------------------------------------------------------------------------------
# gen_path: generate path for auto deployment
#-------------------------------------------------------------------------------
gen_path: .phony
	@echo $(PATH_H:%=%,) $(PATH_C:%=%,) > $(OUT)gen_path


#-------------------------------------------------------------------------------
# lint preprocess, generate all dfn file for lint
#-------------------------------------------------------------------------------
lint_preprocess: build_preprocess csn csn2 dlm_pre mmi_cus
	$(WARN) $@
	$(MAKE_ALLTPP) DFN ALLTPP='$(ALL_LIBS)' ALLDUOTPP='$(ALL_LIBS_STACK2)'


#-------------------------------------------------------------------------------
# for checking multiple defined symbol
#-------------------------------------------------------------------------------
check_sym:
	$(MAKE_LINK) check_sym


#-include $(FEATURE_LIB_LIST_FILE) $(COMMON_LIB_LIST_FILE)
LIBS_DIR_BY_CHIP = ./sc/libs/$(LIBS_PATH_BY_CHIP)/

check_pure_lib_list: .phony
	@if [ -e $(SC_LIB_LIST) ]; then \
		grep 'pure_lib_magic' $(SC_LIB_LIST) || $(GEN_SOURCE_CODE_LIB); \
		else \
		$(GEN_SOURCE_CODE_LIB); \
		fi

#-------------------------------------------------------------------------------
# commands to build common libraries, libraries categorized by feature, libraries categorized by chip
# partial build them with fast architecture
#-------------------------------------------------------------------------------
$(SC_LIB_LIST): check_pure_lib_list

build_common_libs: $(SC_LIB_LIST)
	@$(INFO) "\e[1m\e[33mbuild common libraries: $(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK))\e[0m\n"
	@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) \
	'PRODUCT_SC=$(filter 			$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter 	$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_3RD))' \
	'PRODUCT_LIB=$(filter 			$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter 	$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter 		$(call filter_common_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_3RD))'
	@$(COPY_SOURCE_CODE_LIB)
	$(WARN) "build_common_libs finished\n"

build_feature_libs: $(SC_LIB_LIST)
	@$(INFO) "\e[1m\e[33mbuild libraries by feature: $(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK))\e[0m\n"
	@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) \
	'PRODUCT_SC=$(filter 			$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter 	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter    	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter    	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter    	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter    	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter    	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_3RD))' \
	'PRODUCT_LIB=$(filter       	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter 	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter   	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter   	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter   	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter   	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter   	$(call filter_feature_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_3RD))'
	@$(MAKE) -r -f $(TNG)stack2.mak
	@$(COPY_SOURCE_CODE_LIB)
	$(WARN) "build_feature_libs finished\n"

build_bsp_libs: $(SC_LIB_LIST)
	@$(INFO) "\e[1m\e[33mbuild libraries by bsp: $(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK))\e[0m\n"
	@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) \
	'PRODUCT_SC=$(filter 			$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter 	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter    	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter    	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter    	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter    	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter    	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_3RD))' \
	'PRODUCT_LIB=$(filter       	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter 	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter   	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter   	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter   	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter   	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter   	$(call filter_bsp_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_3RD))'
	@$(COPY_SOURCE_CODE_LIB)
	$(WARN) "build_bsp_libs finished\n"

build_chip_libs: $(SC_LIB_LIST)
	@$(INFO) "\e[1m\e[33mbuild libraries by chip: $(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK))\e[0m\n"
	@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) \
	'PRODUCT_SC=$(filter 			$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter 	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter    	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter    	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter    	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter    	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter    	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_SC_3RD))' \
	'PRODUCT_LIB=$(filter       	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter 	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter   	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter   	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter   	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter   	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter   	$(call filter_chip_libs,$(PURE_LIBS_GET_BY_AWK)), $(PRODUCT_LIB_3RD))'
	@$(COPY_SOURCE_CODE_LIB)
	@../tools/XRG/gnu/bin/gcc -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/sys/src_cus/init.c > $(OUT)init.c.pp
	$(TDEBUG) $(TNG)RemoteDefs_Generator.pl -o $(LIBS_DIR_BY_CHIP)RemoteDefs.ini -i $(OUT) -s
	#@$(MAKE) -r -f $(TNG)lib_ib.mak RELEASE_PROCESS=$(RELEASE_PROCESS) 'PRODUCT_SC=sys_cus'
	#@$(COPY) $(OUT)init.o $(LIBS_DIR_BY_CHIP)init.lib
	@$(MKDIR) $(REL_DIR_MSG)
	-$(COPY) $(DIR_MSG)*_message_define__.hi $(REL_DIR_MSG)
ifeq ($(call FIND_COMPILER_OPTION, __TARGET_DSP_PATCH_SOLO_BIN__), TRUE)
	@$(MAKE) -rs hwl_dsp_patch
	$(COPY) $(OUT)dsp.par $(LIBS_DIR_BY_CHIP)dsp.par
	$(COPY) $(OUT)dsp.all $(LIBS_DIR_BY_CHIP)dsp.all
endif
	$(WARN) "build_chip_libs finished\n"


makdep_cache_clean:
	$(TNG)build_system/lib_generation/makdep_cache_clean.pl -d=$(BUILD)dep_cache -l=200m

#-------------------------------------------------------------------------------
# quota check
#-------------------------------------------------------------------------------

quota-check-category-setting	:=	$(TNG)quota_check/category_setting_$(PRODUCT).xml
quota-check-lib-mapping			:=	$(TNG)quota_check/folder_list.xml
quota-check-object-mapping		:=	$(TNG)quota_check/object_mapping.xml

quota_check:
	$(if $(notdir $(word 1,$(wildcard $(BUILD)$(PRODUCT)/$(CUS_PROJECT_PERL)/TP_DefaultLangPack*.cus))),,\
		$(error "unable to locate CUS name in $(BUILD)$(PRODUCT)/$(CUS_PROJECT_PERL)/, please check if the TP_DefaultLangPack*.cus exist"))
	$(if $(notdir $(word 1,$(wildcard $(TNG)quota_check/category_setting_$(PRODUCT).xml))),,\
		$(error "unable to locate category_setting_$(PRODUCT).xml in $(TNG)quota_check/, please check if category_setting.xml exist"))
	@echo "start test";
	$(TNG)quota_check/linkinfocheck2.exe $(OUT)link.info $(BUILD)$(PRODUCT) $(quota-check-category-setting) \
		$(quota-check-lib-mapping) $(quota-check-object-mapping) $(notdir $(word 1,$(wildcard $(BUILD)$(PRODUCT)/$(CUS_PROJECT_PERL)/TP_DefaultLangPack*.cus)))

check_dup_source:
	$(TNG)build_system/utility/check_dup_file.pl -i=$(OUT)

network_setting:
	$(TNG)/NetworkSetting/NetworkSettingCusConvert.exe 0 $(TNG)NetworkSetting/NetworkSetting.xls $(OUT)NetworkSetting.tmp >> $(OUT)NetworkSettingCusLog.txt
	../tools/XRG/CusPack.exe -i $(OUT)/NetworkSetting.tmp -p NETS -o $(OUT)NetworkSetting.cus
	../tools/XRG/LoadConverter.exe -h16 $(OUT)NetworkSetting.cus -dv $(DWLWIN_VER) -wv $(WINTARGET_VER) -y 3 -bit 13.6.1.1
