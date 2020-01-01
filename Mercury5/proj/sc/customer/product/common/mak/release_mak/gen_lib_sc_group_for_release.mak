
include $(CONFIG_MAK)
include $(NON_CT_LIST) $(COMMON_LIB_LIST_FILE)

# for parse library.mak e.g. rtk.mak
ifeq (1,$(INCLUDE_TARGET))
include $(TARGET_MAK)
endif


ALL_LIBS2=$(PRODUCT_SC) $(PRODUCT_SC_MDL) $(PRODUCT_SC_DRV) $(PRODUCT_SC_SYS) $(PRODUCT_SC_MMI) $(PRODUCT_SC_3RD)
ALL_LIBS2+=$(PRODUCT_LIB) $(PRODUCT_LIB_MDL) $(PRODUCT_LIB_DRV) $(PRODUCT_LIB_3RD) $(PRODUCT_LIB_SYS) $(PRODUCT_LIB_MMI)
ALL_STACK_LIB2=$(PRODUCT_SC_STACK2) $(PRODUCT_LIB_STACK2)
3RD_LIB_OUT = $(LIBS_3RD:%=$(OUT)%) $(EXT_LIBS:%=$(OUT)%)
NON_PURE_LIB= dlm_entry
ALL_LIB_OUT = $(ALL_LIBS2:%=$(OUT)%.lib)
FIND_LIB_LIST = $(sort $(filter-out $(3RD_LIB_OUT) $(NON_PURE_LIB:%=$(OUT)%.lib), $(ALL_LIB_OUT)))

all:  $(FIND_LIB_LIST:%=%.lib_sc) copy_lib_to_libs_folder_stage_1
	@echo "#pure_lib_magic" >>$(SC_LIB_LIST)

lib_list_preprocess: $(PATH_pure_lib_lst)
	-$(CLEAN) $(SC_LIB_LIST)
	@echo "LIB_LIST=\\" > $(SC_LIB_LIST)

$(PATH_pure_lib_lst):
	$(MKDIR) $@
	
%.lib_sc: lib_list_preprocess
#	@echo " target = $(notdir $(basename $(basename $@))) "
	@$(MAKE) -r -s -f $(RELEASE_MAK)gen_lib_sc_group_for_release.mak detect_lib_or_sc \
	TARGET='$(notdir $(basename $(basename $@)))' INCLUDE_TARGET=1

detect_lib_or_sc:
ifeq (,$(strip $(REL_SRC_C_LIST)))
	@echo "    $(TARGET)\\" >> $(SC_LIB_LIST)
endif

copy_lib_to_libs_folder_stage_1:
ifneq "$(NO_COPY)" "1"
	@$(MAKE) -r -s -f $(RELEASE_MAK)gen_lib_sc_group_for_release.mak \
	copy_lib_to_libs_folder_stage_2 INCLUDE_LIB=1
endif
	
	


# include sc_lib_list.mak in order to get LIB_LIST
ifeq (1,$(INCLUDE_LIB))
include $(SC_LIB_LIST)
#COPY_LIB_LIST=$(LIB_LIST:%=$(OUT)%.lib)
#AXF_LIST=$(filter $(basename $(LIB_LIST)), $(notdir $(basename $(ALL_STACK_LIB2))))
ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
COPY_AXF_LIST=$(OUT)dup/stack_2.axf #$(AXF_LIST:%=$(OUT)dup/%_2.axf) 
endif


# critical trace libraries
LIBS_DIR_COMMON				:= ./sc/libs/COMMON/
LIBS_DIR_CT_COMMON			:= ./sc/libs/COMMON/ct/
LIBS_DIR_BY_FEATURE 		:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/
LIBS_DUP_DIR_BY_FEATURE 	:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/dup/
LIBS_DIR_CT_BY_FEATURE 		:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/ct/
LIBS_DUP_DIR_CT_BY_FEATURE 	:= ./sc/libs/$(LIBS_PATH_BY_FEATURE)/dup/ct/
LIBS_DIR_BY_BSP				:= ./sc/libs/$(LIBS_PATH_BY_BSP)/
LIBS_DUP_DIR_BY_BSP			:= ./sc/libs/$(LIBS_PATH_BY_BSP)/dup/
LIBS_DIR_CT_BY_BSP			:= ./sc/libs/$(LIBS_PATH_BY_BSP)/ct/
LIBS_DUP_DIR_CT_BY_BSP		:= ./sc/libs/$(LIBS_PATH_BY_BSP)/dup/ct/
LIBS_DIR_BY_CHIP 			:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/
LIBS_DUP_DIR_BY_CHIP 		:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/dup/
LIBS_DIR_CT_BY_CHIP			:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/ct/
LIBS_DUP_DIR_CT_BY_CHIP		:= ./sc/libs/$(LIBS_PATH_BY_CHIP)/dup/ct/

ifeq (LOG_LEVEL_CRITICAL_ONLY,$(strip $(LOG_LEVEL_CUT_OPTION)))

non-ct-libs-list		:=$(filter $(NON_CRITICAL_TRACE_LIST),$(LIB_LIST))
ct-libs-list			:=$(filter-out $(NON_CRITICAL_TRACE_LIST),$(LIB_LIST))

LIBS_COMMON_LIST		:=$(call filter_common_libs,$(non-ct-libs-list))
CT_LIBS_COMMON_LIST		:=$(call filter_common_libs,$(ct-libs-list))
LIBS_BY_FEATURE_LIST	:=$(call filter_feature_libs,$(non-ct-libs-list))
CT_LIBS_BY_FEATURE_LIST	:=$(call filter_feature_libs,$(ct-libs-list))
LIBS_BY_BSP_LIST		:=$(call filter_bsp_libs,$(non-ct-libs-list))
CT_LIBS_BY_BSP_LIST		:=$(call filter_bsp_libs,$(ct-libs-list))
LIBS_BY_CHIP_LIST		:=$(call filter_chip_libs,$(non-ct-libs-list))
CT_LIBS_BY_CHIP_LIST	:=$(call filter_chip_libs,$(ct-libs-list))
else
LIBS_COMMON_LIST		:=$(call filter_common_libs,$(LIB_LIST))
LIBS_BY_FEATURE_LIST	:=$(call filter_feature_libs,$(LIB_LIST))
LIBS_BY_BSP_LIST		:=$(call filter_bsp_libs,$(LIB_LIST))
LIBS_BY_CHIP_LIST		:=$(call filter_chip_libs,$(LIB_LIST))
endif
endif

copy-libs-to-dir=$(if $(wildcard $(patsubst %,$(OUT)%.lib,$(1))),\
	$(COPY) -fu $(wildcard $(patsubst %,$(OUT)%.lib,$(1))) $(2) && \
	$(COPY) -fu $(wildcard $(patsubst %,$(OUT)remtrace_lib/%_remtrace.*,$(1))) $(2)remtrace_lib/)

copy_lib_to_libs_folder_stage_2:
ifeq (LOG_LEVEL_CRITICAL_ONLY,$(strip $(LOG_LEVEL_CUT_OPTION)))
	$(MKDIR) $(addsuffix remtrace_lib,\
		$(LIBS_DIR_BY_FEATURE) \
		$(LIBS_DIR_BY_CHIP) \
		$(LIBS_DUP_DIR_BY_FEATURE) \
		$(LIBS_DUP_DIR_BY_CHIP) \
		$(LIBS_DIR_CT_BY_FEATURE) \
		$(LIBS_DIR_CT_BY_CHIP) \
		$(LIBS_DUP_DIR_CT_BY_FEATURE) \
		$(LIBS_DUP_DIR_CT_BY_CHIP) \
		$(LIBS_DIR_COMMON) \
		$(LIBS_DIR_CT_COMMON) \
		$(LIBS_DUP_DIR_CT_BY_BSP) \
		$(LIBS_DIR_CT_BY_BSP)\
		$(LIBS_DIR_BY_BSP)\
		$(LIBS_DUP_DIR_BY_BSP))
	$(call copy-libs-to-dir,$(LIBS_COMMON_LIST),$(LIBS_DIR_COMMON))
	$(call copy-libs-to-dir,$(CT_LIBS_COMMON_LIST),$(LIBS_DIR_CT_COMMON))
	$(call copy-libs-to-dir,$(LIBS_BY_FEATURE_LIST),$(LIBS_DIR_BY_FEATURE))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_FEATURE_LIST),$(LIBS_DIR_CT_BY_FEATURE))
	$(call copy-libs-to-dir,$(LIBS_BY_CHIP_LIST),$(LIBS_DIR_BY_CHIP))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_CHIP_LIST),$(LIBS_DIR_CT_BY_CHIP))
	$(call copy-libs-to-dir,$(LIBS_BY_BSP_LIST),$(LIBS_DIR_BY_BSP))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_BSP_LIST),$(LIBS_DIR_CT_BY_BSP))
else
	$(MKDIR) $(addsuffix remtrace_lib,\
		$(LIBS_DIR_BY_FEATURE) \
		$(LIBS_DIR_BY_CHIP) \
		$(LIBS_DUP_DIR_BY_FEATURE) \
		$(LIBS_DUP_DIR_BY_CHIP) \
		$(LIBS_DIR_COMMON) \
		$(LIBS_DIR_BY_BSP) \
		$(LIBS_DUP_DIR_BY_BSP))
	$(call copy-libs-to-dir,$(LIBS_COMMON_LIST),$(LIBS_DIR_COMMON))
	$(call copy-libs-to-dir,$(LIBS_BY_FEATURE_LIST),$(LIBS_DIR_BY_FEATURE))
	$(call copy-libs-to-dir,$(LIBS_BY_BSP_LIST),$(LIBS_DIR_BY_BSP))
	$(call copy-libs-to-dir,$(LIBS_BY_CHIP_LIST),$(LIBS_DIR_BY_CHIP))
endif
ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
	$(if $(wildcard $(COPY_AXF_LIST)),$(COPY) -fu $(COPY_AXF_LIST) $(LIBS_DUP_DIR_BY_FEATURE))
endif
