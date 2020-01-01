#
# Makefile : lcdcust.a
#

LCDCUST_SRC_LIST = $(notdir $(wildcard ./lcd/cust/src/*.c))

LCDCUST_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(LCDCUST_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(LCDCUST_SRC_LIST))

#LIB_LIST += $(OUT_DIR)/lcdcust.a

DEP_INC += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(CHIP)/inc

VPATH += lcd/cust/src

$(LCDCUST_OBJ_LIST): INC_LIST += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(HAL)/inc

#$(OUT_DIR)/lcdcust.a: $(LCDCUST_OBJ_LIST)
#	@ $(AR) $(ARFLAGS) $@ $(LCDCUST_OBJ_LIST)
#	@ echo $@ "... library created"
#	@ echo "Backlight source $(LCDCUST_SRC_LIST)"

EXTRA_OBJS += $(LCDCUST_OBJ_LIST)