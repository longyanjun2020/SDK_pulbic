#
# Makefile : backlighthal.a
#

BACKLIGHTHAL_SRC_LIST = $(notdir $(wildcard ./backlight/hal_$(HAL)/src/*.c))

BACKLIGHTHAL_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(BACKLIGHTHAL_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(BACKLIGHTHAL_SRC_LIST))

LIB_LIST += $(OUT_DIR)/backlighthal.a

DEP_INC += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

VPATH += backlight/hal_$(HAL)/src

$(BACKLIGHTHAL_OBJ_LIST): INC_LIST += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

$(OUT_DIR)/backlighthal.a: $(BACKLIGHTHAL_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $(BACKLIGHTHAL_OBJ_LIST)
	@ echo $@ "... library created"
	@ echo "Backlight source $(BACKLIGHTHAL_SRC_LIST)"

#EXTRA_OBJS += $(BACKLIGHTHAL_OBJ_LIST)