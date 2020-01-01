
.PHONY: lib clean SCM_clean cflags

all: SCM_clean

include $(CONFIG_MAK)

include $(OUT)$(TARGET).cfn

include $(OUT)$(TARGET).rfn

# include SC makefile
include $(TARGET_MAK)

BACKUP_DIR = $(TOP)backup_src/
MOVE = mv -f

REL_DIR = $(TOP)rel_src/

UNUSED_DIR = $(TOP)unused_src/

clean:
	$(CLEAN) $(OUT)$(TARGET).lib
	$(CLEAN) $(TMP)

SCM_clean: $(BACKUP_DIR) $(DEL_SRC_DIRS:%=%.d1) $(SRC_DIRS:%=%.d2) $(OUT)$(TARGET).cfn  $(OUT)$(TARGET).rfn $(DEL_SRCS:%=%.b) $(REL_DIR) $(C_SRCS:%=%.r) $(ASM_SRCS:%=%.r) $(UNUSED_DIR)
#	$(MKDIR) $(BACKUP_DIR)
#	$(MKDIR) $(BACKUP_DIR)$(SRC_DIRS)
#	$(MOVE) $(DEL_SRCS) $(BACKUP_DIR)$(SRC_DIRS)
#	$(CLEAN) $(DEL_SRCS)

$(OUT)$(TARGET).cfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)
	$(MAKE) -r -f $(RELEASE_MAK)cfn.mak cfn

$(OUT)$(TARGET).rfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)
	$(MAKE) -r -f $(RELEASE_MAK)cfn.mak rfn

$(BACKUP_DIR):
	$(MKDIR) $(BACKUP_DIR)sc/
	
%.d1:
	$(MKDIR) $(BACKUP_DIR)$*
	
%.b: 
	$(MOVE) $* $(BACKUP_DIR)$*

$(REL_DIR):
	$(MKDIR) $(REL_DIR)sc/
	
%.d2:
	$(MKDIR) $(REL_DIR)$*
	
%.r: 
	$(MOVE) $* $(REL_DIR)$*

$(UNUSED_DIR):
	$(MKDIR) $(UNUSED_DIR)sc/
	
