SWV_DIR = $(WINTARGET_DIR)
SWV_SRC_DIRS = src
SWV_INC_DIRS = inc

SWV_SRC_LIST = \
	dwl_version.c

SWV_OBJ_LIST = $(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.asm, $(OUT_DIR)/%.o, $(SWV_SRC_LIST)))
DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(SWV_SRC_LIST))
VPATH += $(foreach n, $(SWV_SRC_DIRS), $(SWV_DIR)/$(n))
INC_LIST += $(foreach n, $(SWV_INC_DIRS), -I$(SWV_DIR)/$(n))
INC_LIST += -IUNFD/inc -IUNFD/pub -IUNFD/inc/sys
DEP_LIST += $(foreach n, $(SWV_INC_DIRS), -I$(SWV_DIR)/$(n))
LIB_LIST += $(OUT_DIR)/swversion.a

$(OUT_DIR)/swversion.a: $(SWV_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $^
	@ echo $@ "... library created"
	@-rm -f $(OUT_DIR)/dwl_version.o
	

