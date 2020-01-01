
TARGET=tmt

all: tmt

include $(CONFIG_MAK)
include $(TARGET_MAK)
include $(RELEASE_MAK)cus_table.mak

TMT=$(BUILD)$(PRODUCT)/tmt/
TMT_ZIP=$(TMT)$(PRODUCT).zip
TMT_WKS=$(TMT)$(PRODUCT).wks
LIBS_DIR_BY_CHIP = ./sc/libs/$(LIBS_PATH_BY_CHIP)/
#TMT_MSG=$(TMT)$(PRODUCT).msg
# mark TMT_MSG since tmt.mak is already done.

STEM=$(OUT)$(PRODUCT)

TODAY=$(shell date +"%m%d%y-%X")

.PHONY: tmt $(DYNAMIC_ID_TABLES:%=$(OUT)%)

tmt: $(TMT) $(TMT_ZIP) $(TMT_WKS)# $(TMT_MSG)


$(TMT_WKS): $(TMT_TEMPLATE) $(TMT_FILES)
	$(INFO) $@
	$(INSTALL) $(TMT_TEMPLATE) $@
	echo "" >> $@
	echo "[Binary]" >> $@
	echo 'Date=$(TODAY)' >> $@

$(TMT_ZIP): $(TMT_FILES) $(TABLE_FILES)# $(TMT_MSG)
	$(INFO) $@ "(Enhanced Backtrace)"
	$(BIN)zip -j $@ $^
#	$(RM) $(TMT_MSG)

$(TMT):
	$(MKDIR) $@

#dynamically generate ini files for TMT
$(DYNAMIC_ID_TABLES:%=$(OUT)%):
	$(TDEBUG) $(TNG)TaskState_Generator.pl -o $(OUT)TaskState.ini -i sc/system/rtk/pub
	$(TDEBUG) $(TNG)exceptionType_Generator.pl -o $(OUT)exceptionType.ini -i sc/system/rtk/pub
ifeq ($(RELEASE_PROCESS),1)
	#copy previous RemoteDefs.ini to $(OUT)
	$(COPY) -f $(LIBS_DIR_BY_CHIP)RemoteDefs.ini $(OUT)RemoteDefs.ini
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/rtk/pub/sys_rtk_config.h > $(OUT)sys_rtk_config.h.pp
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/fc/pub/osdefs.hc > $(OUT)osdefs.hc.pp
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/trc/pub/sys_vm_dbg.ho > $(OUT)sys_vm_dbg.ho.pp
	$(TDEBUG) $(TNG)RemoteDefs_Generator.pl -r -o $(OUT)RemoteDefs.ini -i $(OUT)
else
ifeq ($(OSTYPE), cygwin)
	@../tools/XRG/gnu/bin/gcc -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/sys/src_cus/init.c > $(OUT)init.c.pp
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/rtk/pub/sys_rtk_config.h > $(OUT)sys_rtk_config.h.pp
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/fc/pub/osdefs.hc > $(OUT)osdefs.hc.pp
	@../tools/XRG/gnu/bin/cpp -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/trc/pub/sys_vm_dbg.ho > $(OUT)sys_vm_dbg.ho.pp
	$(TDEBUG) $(TNG)RemoteDefs_Generator.pl -o $(OUT)RemoteDefs.ini -i $(OUT)
else
	$(PLTM_CC) -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/sys/src_cus/init.c > $(OUT)init.c.pp
	$(PLTM_CPP) -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/rtk/pub/sys_rtk_config.h > $(OUT)sys_rtk_config.h.pp
	$(PLTM_CPP) -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/fc/pub/osdefs.hc > $(OUT)osdefs.hc.pp
	$(PLTM_CPP) -dM -E $(DFLAGS) $(PATH_H:%=-I%) sc/system/trc/pub/sys_vm_dbg.ho > $(OUT)sys_vm_dbg.ho.pp
	$(TDEBUG) $(TNG)RemoteDefs_Generator.pl -o $(OUT)RemoteDefs.ini -i $(OUT)
endif
endif


$(TMT_MSG):
ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"

ifdef QUICK
# quick build
	$(COPY) -f $(LIBS_DIR_FOR_QUICK)$(notdir $@) $@
else
# normal build or prepare build
	$(TNG)get_msg_id.pl -i$(OUT) -o$@
ifdef PREPARE
# prepare build
	$(MKDIR)        $(LIBS_DIR_FOR_QUICK)
	$(COPY) -f $@   $(LIBS_DIR_FOR_QUICK)
endif
endif # ifdef QUICK

else # ifneq "$(SKIP_GEN_MSG_MAE_ID)" "1"
	@echo "SKIP_GEN_MSG_MAE_ID" > $@
endif

clean:
	$(CLEAN) $(TMT)


