
TARGET=tmt

all: tmt

include $(CONFIG_MAK)
include $(TARGET_MAK)

TMT=$(BUILD)$(PRODUCT)/tmt/

TMT_MAKE_PRIVATE_TABLE = 1

ifeq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)), __CORE_SOFTWARE__)
TMT_MAKE_PRIVATE_TABLE = 0
endif

ifeq ($(filter __INFINITY__, $(PP_OPT_COMMON)), __INFINITY__)
TMT_MAKE_PRIVATE_TABLE = 0
SKIP_GEN_MSG_MAE_ID = 1
endif

TMT_MMI_CLSID_IN_FILE=$(PATH_core)/pub/mmi_clstbl.h
TMT_MMI_EVENTID_IN_FILE=$(PATH_core)/pub/mmi_event.h
TMT_MAE_STATEID_IN_FILE=$(PATH_mae)/src/mae_apm_priv.h
TMT_MAE_TRANSID_IN_FILE=$(PATH_mae)/pub/mmi_mae_sm_defs.h
TMT_MAE_EVENTID_IN_FILE=$(PATH_mae)/pub/mmi_mae_event.h
TMT_MMI_RAIID_CLASS_IN_FILE=$(PATH_mae)/pub/mmi_mae_rai_id.h
TMT_MMI_RAIID_IN_FILE=$(PATH_mmicomn)/inc/mmi_common_rai_id.h

TMT_MAE_CLSID=$(TMT)$(PRODUCT).clsid.mae
TMT_MAE_STATEID=$(TMT)$(PRODUCT).stateid.mae
TMT_MAE_MODEID=$(TMT)$(PRODUCT).modeid.mae
TMT_MAE_EVENTID=$(TMT)$(PRODUCT).eventid.mae
TMT_MAE_TRANSID=$(TMT)$(PRODUCT).transid.mae
TMT_MAE_RAIID=$(TMT)xmmi_rai_id.mae

TMT_MAE_CLSID_TMP=$(TMT)mae_clsid.h.txt
TMT_MAE_STATEID_TMP=$(TMT)mae_apm_priv.txt
TMT_MAE_EVENT_FILE_TMP=$(TMT)mae_event_file.h.txt
TMT_MAE_EVENT_TMP=$(TMT)mae_event.h.txt
TMT_MAE_TRANSID_TMP=$(TMT)mae_transid.h.txt
TMT_MAE_RAIID_TMP=$(TMT)mae_raiid.h.txt

TMT_TRACE_LEVEL=../tools/TMT/Trace_Level
TMT_TRACE_LEVEL_TMP=Trace_Level

TMT_ZIP=$(TMT)$(PRODUCT).zip
TMT_WKS=$(TMT)$(PRODUCT).wks
TMT_MSG=$(TMT)$(PRODUCT).msg

STEM=$(OUT)$(PRODUCT)

ifeq "$(OSTYPE)" "Win32"
TODAY=$(shell date /T)
else
TODAY=$(shell date +"%m%d%y-%X")
endif

.PHONY: tmt .phony

ifeq ($(TMT_MAKE_PRIVATE_TABLE),1)
tmt: $(TMT) $(TMT_ZIP) $(TMT_WKS) $(TMT_MSG) $(TMT_MAE_CLSID)
else
tmt: $(TMT) $(TMT_ZIP) $(TMT_WKS)
endif


$(TMT_WKS): $(TMT_TEMPLATE) $(TMT_FILES)
	$(INFO) $@
	$(INSTALL) $(TMT_TEMPLATE) $@
	echo "" >> $@
	echo "[Binary]" >> $@
	echo 'Date=$(TODAY)' >> $@

$(TMT_TEMPLATE): .phony
	$(COPY) -f $(TMT_DEFAULT) $(OUT)
	perl $(TNG)replacePattern.pl $@ __PRODUCT_NAME__ $(PRODUCT)

ifeq ($(TMT_MAKE_PRIVATE_TABLE),1)
$(TMT_ZIP): $(TMT_FILES) $(TMT_MSG) $(TMT_MAE_CLSID) $(TMT_MAE_STATEID) $(TMT_MAE_MODEID) $(TMT_MAE_EVENTID) $(TMT_MAE_TRANSID) $(TMT_MAE_RAIID)
	$(INFO) $@
	$(BIN)zip -j $@ $^
	$(COPY) -rf $(TMT_TRACE_LEVEL) $(TMT_TRACE_LEVEL_TMP)
	$(BIN)zip -ur $@ $(TMT_TRACE_LEVEL_TMP)
	$(RM) $(TMT_MSG)
	$(RM) $(TMT_MAE_CLSID)
	$(RM) $(TMT_MAE_MODEID)
	$(RM) $(TMT_MAE_EVENTID)
	$(RM) $(TMT_MAE_STATEID)
	$(RM) $(TMT_MAE_TRANSID)
	$(RM) $(TMT_MAE_RAIID)
	$(RM) -rf $(TMT_TRACE_LEVEL_TMP)
else
$(TMT_ZIP): $(TMT_FILES)
	$(INFO) $@
	$(BIN)zip -j $@ $^
endif

$(TMT):
	$(MKDIR) $@

$(TMT_MSG): .phony
ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"
# call msg.mak to generate msg id
	$(MAKE_MSG)
else # ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"
	@echo "SKIP_GEN_MSG_MAE_ID" > $@
endif

include $(PATH_mmicomn)/mmicomn.mak
CDEP_PATH_H := $(MMI_PATH_H)
CDEP_PATH_H += $(if $(filter yes, $(NO_PLATFORM_INCLUDE)), ,$(filter-out $(MMI_PATH_H), $(PATH_H)))
CDEP_PATH_H += $(if $(filter AEONGCC, $(COMPILER_VERSION)), $(AEONINC))
CDEP_PATH_H += $(if $(filter MIPSGCC, $(COMPILER_VERSION)), $(MIPSINC))
CDEP_PATH_H += $(if $(filter X86LINUXGCC, $(COMPILER_VERSION)), $(X86LINUXINC))
CDEP_PATH_H += $(if $(filter ARMGCC, $(COMPILER_VERSION)), $(ARMGCCINC))

$(OUT)mmi_common_rai_id.tpp: $(TMT_MMI_RAIID_IN_FILE)
ifneq ($(filter AEONGCC MIPSGCC X86LINUXGCC ARMGCC, $(COMPILER_VERSION)), )
	$(if $(filter AEONGCC,$(COMPILER_VERSION)),\
		@echo -e "-f $(OUT)mmi_common_rai_id.dep $(DFLAGS) -D__aeon__ -D__cplusplus $(CDEP_PATH_H:%=-I%) $(TMT_MMI_RAIID_IN_FILE)" >$(OUT)mmi_common_rai_id.opt,\
		@echo -e "-f $(OUT)mmi_common_rai_id.dep $(DFLAGS) $(MKDEP_FLAGS) $(CDEP_PATH_H:%=-I%) $(TMT_MMI_RAIID_IN_FILE)" >$(OUT)mmi_common_rai_id.opt)
else
	@echo "-f $(OUT)mmi_common_rai_id.dep -Y$(ARMINC_FOLDER) $(DFLAGS) -D__arm -D__arm__ -D__ARMCC_VERSION -D__cplusplus $(CDEP_PATH_H:%=-I%) $(TMT_MMI_RAIID_IN_FILE)" > $(OUT)mmi_common_rai_id.opt
endif
	$(TDEBUG) $(MAKEDEP) @$(OUT)mmi_common_rai_id.opt
	sed -i '/^\(..*\)#/s//\1\n#/g' $(OUT)mmi_common_rai_id.dep
	$(TNG)dep2tpp.pl -f $@ -t $(OSTYPE) -o "\$$(TMP)" $(OUT)mmi_common_rai_id.dep
	-rm -f $(OUT)mmi_common_rai_id.opt $(OUT)mmi_common_rai_id.dep

ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"
ifneq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)), __CORE_SOFTWARE__)
include $(OUT)mmi_common_rai_id.tpp
endif
endif

$(TMT_MAE_CLSID): .phony
ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"
	$(PLTM_CC) -c ${CFLAGS} ${IFLAGS} -E $(TMT_MMI_CLSID_IN_FILE) > $(TMT_MAE_CLSID_TMP)
	$(PLTM_CC) -c ${CFLAGS} ${IFLAGS} -E $(TMT_MAE_STATEID_IN_FILE) > $(TMT_MAE_STATEID_TMP)
	perl $(TNG)convertMaeEvent.pl $(TMT_MAE_EVENTID_IN_FILE) $(TMT_MMI_EVENTID_IN_FILE) $(TMT_MAE_EVENT_FILE_TMP)
	$(PLTM_CC) -c ${CFLAGS} ${IFLAGS} -I $(PATH_core) -E $(TMT_MAE_EVENT_FILE_TMP) > $(TMT_MAE_EVENT_TMP)
	$(PLTM_CC) -c ${CFLAGS} ${IFLAGS} -E $(TMT_MAE_TRANSID_IN_FILE) > $(TMT_MAE_TRANSID_TMP)
	perl $(TNG)ParseMaeClsid.pl $(TMT_MAE_CLSID_TMP) $(TMT_MAE_STATEID_TMP) $(TMT_MAE_EVENT_TMP) $(TMT_MAE_TRANSID_TMP) $(TMT_MAE_CLSID) $(TMT_MAE_STATEID) $(TMT_MAE_MODEID) $(TMT_MAE_EVENTID) $(TMT_MAE_TRANSID) $(OUT_ORG)
	$(PLTM_CC) -c ${CFLAGS} ${IFLAGS} $(INC_DIRS:%=-I%) -E $(TMT_MMI_RAIID_IN_FILE) > $(TMT_MAE_RAIID_TMP)
	perl $(TNG)ParseMaeRaiId.pl $(TMT_MMI_RAIID_CLASS_IN_FILE) $(TMT_MMI_RAIID_IN_FILE) $(TMT_MAE_RAIID_TMP) $(TMT_MAE_RAIID)
	$(RM) $(TMT_MAE_CLSID_TMP)
	$(RM) $(TMT_MAE_STATEID_TMP)
	$(RM) $(TMT_MAE_EVENT_FILE_TMP)
	$(RM) $(TMT_MAE_EVENT_TMP)
	$(RM) $(TMT_MAE_TRANSID_TMP)
	$(RM) $(TMT_MAE_RAIID_TMP)
else
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_CLSID)
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_MODEID)
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_EVENTID)
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_STATEID)
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_TRANSID)
	@echo "SKIP_GEN_MSG_MAE_ID" > $(TMT_MAE_RAIID)
endif

clean:
	$(CLEAN) $(TMT)
