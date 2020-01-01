
OUT_DLM_TARGET_DIR=$(OUT_DLM)$(TARGET)_dir/
OUT_DLM_UT_DIR=$(OUT)dlm_bin/

include $(CONFIG_MAK)
include $(TARGET_MAK)

include $(OUT_DLM_TARGET_DIR)$(TARGET).dfn
include $(OUT_DLM_TARGET_DIR)$(TARGET).tpp

#
# default : $(OUT_DLM_TARGET_DIR)/$(TARGET).dlm
# UT      : $(OUT_DLM_UT_DIR)/$(UT_GROUP)/$(TARGET).dlm
#
DLL_DLM=$(if $(UT_GROUP),$(OUT_DLM_UT_DIR)$(UT_GROUP)/, $(OUT_DLM_TARGET_DIR))$(TARGET).dlm
DEP_PARAMETERS=DUP_FLAG=0 RELEASE_PROCESS=1 \
               PATH_C='$(PATH_SC_$(TARGET))' OUT='$(OUT_DLM_TARGET_DIR)' INC='$(OUT_DLM_TARGET_DIR)'

.PHONY:.phony

all: prepare_dir $(DLL_DLM)

prepare_dir: .phony
	$(if $(UT_GROUP), $(MKDIR) $(OUT_DLM_UT_DIR))
	$(if $(UT_GROUP), $(MKDIR) $(OUT_DLM_UT_DIR)$(UT_GROUP))

$(DLL_DLM): $(OUT)link.info $(TARGET_MAK) $(OUT_DLM_TARGET_DIR)$(TARGET).dfn $(C_SRCS) $(INC_DIRS)
	$(WARN) $@
	$(MAKE_DLM_BLD) clean TARGET=$(TARGET) DLL_DLM='$(DLL_DLM)' CLEAN_FILE='1'
	$(VENEERGEN) -id $(PATH_dlm_entry_inc)$(TARGET).def \
                 -ik $(OUT)link.info \
                 -ov $(OUT_DLM_TARGET_DIR)$(TARGET)_pveneer.s \
                 -or $(OUT_DLM_TARGET_DIR)$(TARGET)_xmmi.ref 
	$(MAKE_DLM_BLD) all TARGET=$(TARGET) 
	$(DLMIZE) -id $(PATH_dlm_entry_inc)$(TARGET).def \
              -is $(OUT_DLM_TARGET_DIR)$(TARGET)_symdefs.info \
              -ik $(OUT_DLM_TARGET_DIR)$(TARGET)_link.info \
              -ib $(OUT_DLM_TARGET_DIR)$(TARGET).bin \
              -om $(DLL_DLM)
	# compress the dlm file
	./tng/MSComprs.exe -f"$@" -o"$(OUT_DLM)$(notdir $@)" "-a1"

#
# add dfn rule for multiple cource code path
#
$(OUT_DLM_TARGET_DIR)$(TARGET).dfn: $(OUT)link.info $(TARGET_MAK) $(C_SRCS)# $(SRC_DIRS)
ifeq ($(RELEASE_PROCESS),0)
#	$(WARN) $(MAKE_DFN) dfn $(DEP_PARAMETERS)
	$(MAKE_DFN) dfn $(DEP_PARAMETERS)
# store file for release process
	$(MKDIR) $(PATH_DLM_LIB)
	$(COPY) -fu $@ $(PATH_DLM_LIB)
else
# restore file for release process
	$(WARN) $(COPY) -fu $(PATH_DLM_LIB)$(notdir $@) $@ 
	$(COPY) -fu $(PATH_DLM_LIB)$(notdir $@) $@ 
endif

#
# add tpp rule for copy some header files
# (which do not included by main code) to out folder
#
$(OUT_DLM_TARGET_DIR)$(TARGET).tpp: $(OUT_DLM_TARGET_DIR)$(TARGET).dfn $(INC_DIRS)
ifeq ($(RELEASE_PROCESS),0)
	$(MAKE_TPP) NO_GROUP_TRACE_ID=1 $(DEP_PARAMETERS)
# store file for release process
	$(COPY) -fu $@ $(PATH_DLM_LIB)
else
# restore file for release process
	$(COPY) -fu $(PATH_DLM_LIB)$(notdir $@) $@ 
endif

