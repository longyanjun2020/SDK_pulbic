CUSTOMER_DIR = $(WINTARGET_DIR)/customer
CUSTOMER_SRC_DIRS = src
CUSTOMER_INC_DIRS = inc

CUSTOMER_SRC_LIST = \
  mcp_drv.c

CUSTOMER_OBJ_LIST = $(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.asm, $(OUT_DIR)/%.o, $(CUSTOMER_SRC_LIST)))
DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(CUSTOMER_SRC_LIST))
VPATH += $(foreach n, $(CUSTOMER_SRC_DIRS), $(CUSTOMER_DIR)/$(n))
INC_LIST += $(foreach n, $(CUSTOMER_INC_DIRS), -I$(CUSTOMER_DIR)/$(n))
DEP_LIST += $(foreach n, $(CUSTOMER_INC_DIRS), -I$(CUSTOMER_DIR)/$(n))
LIB_LIST += $(OUT_DIR)/customer.a

$(OUT_DIR)/customer.a: $(CUSTOMER_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $^
	@ echo $@ "... library created"

