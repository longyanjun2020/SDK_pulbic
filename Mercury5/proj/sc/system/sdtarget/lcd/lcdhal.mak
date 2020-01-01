#
# Makefile : lcdhal.a
#

LCDHAL_SRC_LIST = $(notdir $(wildcard ./lcd/hal_$(HAL)/src/*.c))

LCDHAL_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(LCDHAL_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(LCDHAL_SRC_LIST))

LIB_LIST += $(OUT_DIR)/lcdhal.a

DEP_INC += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(HAL)/inc

VPATH += lcd/hal_$(HAL)/src

$(LCDHAL_OBJ_LIST): INC_LIST += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(HAL)/inc

$(OUT_DIR)/lcdhal.a: $(LCDHAL_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $(LCDHAL_OBJ_LIST)
	@ echo $@ "... library created"
	@ echo "Backlight source $(LCDHAL_SRC_LIST)"

#EXTRA_OBJS += $(LCDHAL_OBJ_LIST)