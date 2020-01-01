
#
# The lib set list is define in lib_path.mak
#

#
# identify each account...
#

#ifeq ($(call FIND_COMPILER_OPTION, __G1__), TRUE)
#RELEASE_ACCOUNT=MSC MSZ
#else
#RELEASE_ACCOUNT=MSZ
#MST
#endif

#
# prepare lib list of each account
#
#PREPARE_LIB_MSC=$(LIB_MSC_SET:%=$(OUT)%.lib)
#PREPARE_LIB_MSZ=$(LIB_MSZ_SET:%=$(OUT)%.lib)
#PREPARE_LIB_MST=$(LIB_MST_SET:%=$(OUT)%.lib)


#
# general setting
#
#SUPER_LIB_SET=$(basename $(notdir $(wildcard $(LIBS_DIR_FOR_QUICK)*.lib)))
#START_COPY_FILE=$(RELEASE_ACCOUNT:%=LIB_%)

all:

p4-acc-list=ap sys ps

.PHONY: .phony all prepare_file

all: $(p4-acc-list:%=%.prepare)
	$(WARN) prepare files done

include $(CONFIG_MAK)

$(eval \
	$(foreach acc,$(p4-acc-list),\
	 $(eval quick-lib-list.$(acc) 				:= $(LIB_$(acc)_SET)) \
	 $(eval LIBS_DIR_COMMON.$(acc)				:= ./libs/$(acc)/COMMON/) \
	 $(eval LIBS_DIR_CT_COMMON.$(acc)			:= ./libs/$(acc)/COMMON/ct/) \
	 $(eval LIBS_DIR_BY_FEATURE.$(acc) 			:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/) \
	 $(eval LIBS_DUP_DIR_BY_FEATURE.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/dup/) \
	 $(eval LIBS_DIR_CT_BY_FEATURE.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/ct/) \
	 $(eval LIBS_DUP_DIR_CT_BY_FEATURE.$(acc) 	:= ./libs/$(acc)/$(LIBS_PATH_BY_FEATURE)/dup/ct/) \
	 $(eval LIBS_DIR_BY_BSP.$(acc)				:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/) \
	 $(eval LIBS_DUP_DIR_BY_BSP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/dup/) \
	 $(eval LIBS_DIR_CT_BY_BSP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/ct/) \
	 $(eval LIBS_DUP_DIR_CT_BY_BSP.$(acc)		:= ./libs/$(acc)/$(LIBS_PATH_BY_BSP)/dup/ct/) \
	 $(eval LIBS_DIR_BY_CHIP.$(acc) 			:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/) \
	 $(eval LIBS_DUP_DIR_BY_CHIP.$(acc) 		:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/dup/) \
	 $(eval LIBS_DIR_CT_BY_CHIP.$(acc)			:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/ct/) \
	 $(eval LIBS_DUP_DIR_CT_BY_CHIP.$(acc)		:= ./libs/$(acc)/$(LIBS_PATH_BY_CHIP)/dup/ct/) \
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

copy-libs-to-dir=$(if $(wildcard $(patsubst %,$(OUT)%.lib,$(1))),\
	$(COPY) -fu $(wildcard $(patsubst %,$(OUT)%.lib,$(1))) $(2) &&\
	$(COPY) -fu $(wildcard $(patsubst %,$(OUT)remtrace_lib/%_remtrace.*,$(1))) $(2)remtrace_lib/)

ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
COPY_AXF_LIST=$(OUT)dup/stack_2.axf #$(AXF_LIST:%=$(OUT)dup/%_2.axf) 
endif

%.prepare:
	$(INFO) $@
ifeq (LOG_LEVEL_CRITICAL_ONLY,$(LOG_LEVEL_CUT_OPTION))
	$(MKDIR) $(addsuffix remtrace_lib,\
		$(LIBS_DIR_BY_FEATURE.$*) \
		$(LIBS_DIR_BY_CHIP.$*) \
		$(LIBS_DUP_DIR_BY_FEATURE.$*) \
		$(LIBS_DUP_DIR_BY_CHIP.$*) \
		$(LIBS_DIR_CT_BY_FEATURE.$*) \
		$(LIBS_DIR_CT_BY_CHIP.$*) \
		$(LIBS_DUP_DIR_CT_BY_FEATURE.$*) \
		$(LIBS_DUP_DIR_CT_BY_CHIP.$*) \
		$(LIBS_DIR_COMMON.$*) \
		$(LIBS_DIR_CT_COMMON.$*) \
		$(LIBS_DUP_DIR_CT_BY_BSP.$*) \
		$(LIBS_DIR_CT_BY_BSP.$*)\
		$(LIBS_DIR_BY_BSP.$*)\
		$(LIBS_DUP_DIR_BY_BSP.$*)) $(LIBS_DIR_BY_CHIP.$*)msg_id/
	$(call copy-libs-to-dir,$(LIBS_COMMON_LIST.$*),$(LIBS_DIR_COMMON.$*))
	$(call copy-libs-to-dir,$(CT_LIBS_COMMON_LIST.$*),$(LIBS_DIR_CT_COMMON.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_FEATURE_LIST.$*),$(LIBS_DIR_BY_FEATURE.$*))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_FEATURE_LIST.$*),$(LIBS_DIR_CT_BY_FEATURE.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_CHIP_LIST.$*),$(LIBS_DIR_BY_CHIP.$*))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_CHIP_LIST.$*),$(LIBS_DIR_CT_BY_CHIP.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_BSP_LIST.$*),$(LIBS_DIR_BY_BSP.$*))
	$(call copy-libs-to-dir,$(CT_LIBS_BY_BSP_LIST.$*),$(LIBS_DIR_CT_BY_BSP.$*))
else
	$(MKDIR) $(addsuffix remtrace_lib,\
		$(LIBS_DIR_BY_FEATURE.$*) \
		$(LIBS_DIR_BY_CHIP.$*) \
		$(LIBS_DUP_DIR_BY_FEATURE.$*) \
		$(LIBS_DUP_DIR_BY_CHIP.$*) \
		$(LIBS_DIR_COMMON.$*) \
		$(LIBS_DIR_BY_BSP.$*) \
		$(LIBS_DUP_DIR_BY_BSP.$*)) $(LIBS_DIR_BY_CHIP.$*)msg_id/
	$(call copy-libs-to-dir,$(LIBS_COMMON_LIST.$*),$(LIBS_DIR_COMMON.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_FEATURE_LIST.$*),$(LIBS_DIR_BY_FEATURE.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_BSP_LIST.$*),$(LIBS_DIR_BY_BSP.$*))
	$(call copy-libs-to-dir,$(LIBS_BY_CHIP_LIST.$*),$(LIBS_DIR_BY_CHIP.$*))
endif
	$(COPY) -fu $(DIR_MSG)*_message_define__.hi                 $(LIBS_DIR_BY_CHIP.$*)msg_id/
	$(COPY) -fur $(LIBS_DIR_FOR_QUICK)/*                        $(LIBS_DIR_BY_CHIP.$*)
ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
	$(if $(wildcard $(COPY_AXF_LIST)),\
		$(COPY) -fu $(wildcard $(COPY_AXF_LIST)) $(LIBS_DUP_DIR_BY_FEATURE.$*))
endif
# for B3 BRAVO 
ifeq ($(call FIND_COMPILER_OPTION, __MAK_ARM__), TRUE)
	cp -fu $(OUT)drv_keypad.o                              $(LIBS_DIR_BY_CHIP.$*)
endif

# for G1
ifeq ($(call FIND_COMPILER_OPTION, __G1__), TRUE)
	cp -fu $(OUT)sys_boot_g1_vectors.o                     $(LIBS_DIR_BY_CHIP.$*)
endif

