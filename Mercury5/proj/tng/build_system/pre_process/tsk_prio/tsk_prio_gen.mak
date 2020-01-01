#----------------------------------------------------------------------
# This makefile is used to generate task priority identification by
# preprocessing/parsing/sorting cus_app.c and init.c
# Version | Date       | Description   | Owner
# v1.00   | 2011.06.03 | first version | system team
#----------------------------------------------------------------------


#----------------------------------------------------------------------
# include $(CONFIG_MAK) to get build system info.
#----------------------------------------------------------------------
include $(CONFIG_MAK)


#----------------------------------------------------------------------
# main target
#----------------------------------------------------------------------
all: tsk


#----------------------------------------------------------------------
# setting phony target
#----------------------------------------------------------------------
.PHONY: .phony tsk


#----------------------------------------------------------------------
# variable definition
#----------------------------------------------------------------------
CPP_LINE=$(COPY) $< $@
CUS_TASK_PRIO_FILE=$(OUT)cus_app.c.pp
# sys task would only be parsing in normal build
SYS_TASK_PRIO_FILE=$(if $(filter 1, $(RELEASE_PROCESS)),,$(OUT)init.c.pp )


#----------------------------------------------------------------------
# include file
#----------------------------------------------------------------------
include $(TARGET_MAK)
include $(OUT)$(TARGET).tpp


#----------------------------------------------------------------------
# process...
#----------------------------------------------------------------------
tsk: $(OUT)tsk_prio.lst


#----------------------------------------------------------------------
# dfn, tpp file: to generate file dependency
#----------------------------------------------------------------------
$(OUT)$(TARGET).tpp: $(OUT)$(TARGET).dfn $(INC_DIRS)
	$(MAKE) -r -f $(TNG)tpp.mak NO_GROUP_TRACE_ID=1 PATH_csnout=


$(OUT)$(TARGET).dfn: $(TARGET_MAK) $(SRC_DIRS) $(PATHS_MAK) $(_PATHS_MAK) $(PATHS_PUB)
	$(MAKE) -r -f $(TNG)dfn.mak dfn NO_GROUP_TRACE_ID=1 PATH_csnout=


#----------------------------------------------------------------------
# $(OUT)tsk_prio.lst : final output which contains all task priority
# Add "-v 2" for debugging, -h for user guide
#----------------------------------------------------------------------
$(OUT)tsk_prio.lst: $(SYS_TASK_PRIO_FILE) $(CUS_TASK_PRIO_FILE)
	perl $(DIR_BUILD_PRE)tsk_prio/tsk_prio.pl \
        -c $(CUS_TASK_PRIO_FILE) \
		-o $@ \
		$(if $(filter 1, $(RELEASE_PROCESS)),,-s $(SYS_TASK_PRIO_FILE) -t $(OUT)tsk_prio.tpp)


#----------------------------------------------------------------------
# SYS_TASK_PRIO_FILE : Only be parsing in normal build
#----------------------------------------------------------------------
$(OUT)init.c.pp: $(TMP)init.c
	$(TDEBUG) $(CCACHE) $(CC) -c $(DFLAGS) $(INC_DIRS:%=-I%) -E $< -o $@


#----------------------------------------------------------------------
# CUS_TASK_PRIO_FILE
#----------------------------------------------------------------------
$(OUT)cus_app.c.pp: $(TMP)cus_app.c
	$(TDEBUG) $(CCACHE) $(CC) -c $(DFLAGS) $(INC_DIRS:%=-I%) -E $< -o $@

