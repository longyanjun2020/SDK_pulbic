
#
# The lib set list is define in lib_path.mak
#

p4-acc-list=ap sys ps

.PHONY: .phony all restore_file

all: restore_file

include $(CONFIG_MAK)
$(eval \
	$(foreach acc,$(p4-acc-list),\
	 $(eval quick-lib-list.$(acc) 				:= $(LIB_$(acc)_SET)) \
	 $(eval LIBS_DIR_COMMON.$(acc)				:= ./libs/$(acc)/COMMON/) \
	 $(eval LIBS_DIR_BY_FEATURE.$(acc) 			:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/) \
	 $(eval LIBS_DIR_BY_BSP.$(acc)				:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/) \
	 $(eval LIBS_DIR_BY_CHIP.$(acc) 			:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/) \
	 $(eval LIBS_DIR_CT_COMMON.$(acc)			:= ./libs/$(acc)/COMMON/ct/) \
	 $(eval LIBS_DIR_CT_BY_FEATURE.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/ct/) \
	 $(eval LIBS_DIR_CT_BY_BSP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/ct/) \
	 $(eval LIBS_DIR_CT_BY_CHIP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/ct/) \
	 $(eval LIBS_DUP_DIR_BY_FEATURE.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/dup/) \
	 $(eval LIBS_DUP_DIR_BY_BSP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/dup/) \
	 $(eval LIBS_DUP_DIR_BY_CHIP.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/dup/) \
	 $(eval LIBS_DUP_DIR_CT_BY_BSP.$(acc)		:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/dup/ct/) \
	 $(eval LIBS_DUP_DIR_CT_BY_CHIP.$(acc)		:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/dup/ct/) \
	 $(eval LIBS_DUP_DIR_CT_BY_FEATURE.$(acc) 	:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/dup/ct/) \
	)\
)

ifeq (LOG_LEVEL_CRITICAL_ONLY,$(LOG_LEVEL_CUT_OPTION))
$(eval \
	$(foreach acc,$(p4-acc-list),\
		$(eval non-ct-libs-list.$(acc)			:=$(filter $(NON_CRITICAL_TRACE_LIST),$(quick-lib-list.$(acc)))) \
		$(eval ct-libs-list.$(acc)				:=$(filter-out $(NON_CRITICAL_TRACE_LIST),$(quick-lib-list.$(acc)))) \
		$(eval LIBS_COMMON_LIST.$(acc)			:=$(call filter_common_libs,$(non-ct-libs-list.$(acc)))) \
		$(eval LIBS_BY_FEATURE_LIST.$(acc)		:=$(call filter_feature_libs,$(non-ct-libs-list.$(acc)))) \
		$(eval LIBS_BY_BSP_LIST.$(acc)			:=$(call filter_bsp_libs,$(non-ct-libs-list.$(acc)))) \
		$(eval LIBS_BY_CHIP_LIST.$(acc)			:=$(call filter_chip_libs,$(non-ct-libs-list.$(acc)))) \
		$(eval CT_LIBS_COMMON_LIST.$(acc)		:=$(call filter_common_libs,$(ct-libs-list.$(acc)))) \
		$(eval CT_LIBS_BY_FEATURE_LIST.$(acc)	:=$(call filter_feature_libs,$(ct-libs-list.$(acc)))) \
		$(eval CT_LIBS_BY_BSP_LIST.$(acc)		:=$(call filter_bsp_libs,$(ct-libs-list.$(acc)))) \
		$(eval CT_LIBS_BY_CHIP_LIST.$(acc)		:=$(call filter_chip_libs,$(ct-libs-list.$(acc)))) \
	)\
)
else 
$(eval\
	$(foreach acc,$(p4-acc-list),\
	$(eval LIBS_COMMON_LIST.$(acc)			:=$(call filter_common_libs,$(quick-lib-list.$(acc)))) \
	$(eval LIBS_BY_FEATURE_LIST.$(acc)		:=$(call filter_feature_libs,$(quick-lib-list.$(acc)))) \
	$(eval LIBS_BY_BSP_LIST.$(acc)			:=$(call filter_bsp_libs,$(quick-lib-list.$(acc)))) \
	$(eval LIBS_BY_CHIP_LIST.$(acc)			:=$(call filter_chip_libs,$(quick-lib-list.$(acc)))) \
	)\
)
endif

copy-libs-to-out=$(if $1,\
	$(if $(filter-out $(words $1),$(words $(wildcard $(patsubst %,$(2)%.lib,$(1))))),\
		$(error $(filter-out $(wildcard $(patsubst %,$(2)%.lib,$(1))),$(patsubst %,$(2)%.lib,$(1))) not exist...),\
		$(if $(filter-out $(words $1),$(words $(wildcard $(patsubst %,$(2)remtrace_lib/%_remtrace.csv,$(1))))),\
			$(error $(filter-out $(wildcard $(patsubst %,$(2)remtrace_lib/%_remtrace.csv,$(1))),$(patsubst %,$(2)remtrace_lib/%_remtrace.csv,$1)) not exist...),\
			$(COPY) -fu $(wildcard $(patsubst %,$(2)%.lib,$(1))) $(OUT) &&\
			$(COPY) -fu $(wildcard $(patsubst %,$(2)remtrace_lib/%_remtrace.*,$(1))) $(OUT)remtrace_lib/)))

# Use "update" instead of "overwrite", to reserve the previous remtrace
restore_file: .phony 
	$(call copy-libs-to-out,$(LIBS_COMMON_LIST.$(QUICK)),$(LIBS_DIR_COMMON.$(QUICK)))
	$(call copy-libs-to-out,$(LIBS_BY_FEATURE_LIST.$(QUICK)),$(LIBS_DIR_BY_FEATURE.$(QUICK)))
	$(call copy-libs-to-out,$(LIBS_BY_BSP_LIST.$(QUICK)),$(LIBS_DIR_BY_BSP.$(QUICK)))
	$(call copy-libs-to-out,$(LIBS_BY_CHIP_LIST.$(QUICK)),$(LIBS_DIR_BY_CHIP.$(QUICK)))
	$(call copy-libs-to-out,$(CT_LIBS_COMMON_LIST.$(QUICK)),$(LIBS_DIR_CT_COMMON.$(QUICK)))
	$(call copy-libs-to-out,$(CT_LIBS_BY_FEATURE_LIST.$(QUICK)),$(LIBS_DIR_CT_BY_FEATURE.$(QUICK)))
	$(call copy-libs-to-out,$(CT_LIBS_BY_BSP_LIST.$(QUICK)),$(LIBS_DIR_CT_BY_BSP.$(QUICK)))
	$(call copy-libs-to-out,$(CT_LIBS_BY_CHIP_LIST.$(QUICK)),$(LIBS_DIR_CT_BY_CHIP.$(QUICK)))
	#$(COPY) -fur $(LIBS_DIR_FOR_QUICK)remtrace_lib          $(OUT)
	#$(COPY) -fu  $(EXISTED_LIBS_FILE)                       $(OUT)
	$(COPY) -fu  $(LIBS_DIR_BY_CHIP.$(QUICK))msg_id/*_message_define__.hi    $(DIR_MSG)

ifeq ($(filter __MAK_ARM__ ,$(PP_OPT_COMMON)),__MAK_ARM__)
	-$(COPY) -fu  $(LIBS_DIR_BY_CHIP.$(QUICK))drv_keypad.o         $(OUT)
endif

ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
	$(MKDIR)  $(OUT_DUP)/
	$(COPY) -fu  $(LIBS_DUP_DIR_BY_FEATURE.$(QUICK))stack_2.axf           $(OUT_DUP)/
endif

