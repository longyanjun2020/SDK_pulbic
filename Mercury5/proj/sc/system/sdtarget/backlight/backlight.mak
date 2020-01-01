#
# Makefile : backlight.a
#

BACKLIGHT_SRC_LIST = $(notdir $(wildcard ./backlight/drv/src/*.c))

BACKLIGHT_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(BACKLIGHT_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(BACKLIGHT_SRC_LIST))

LIB_LIST += $(OUT_DIR)/backlight.a

DEP_INC += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

VPATH += backlight/drv/src

$(BACKLIGHT_OBJ_LIST): INC_LIST += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

$(OUT_DIR)/backlight.a: $(BACKLIGHT_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $(BACKLIGHT_OBJ_LIST)
	@ echo $@ "... library created"
	@ echo "Backlight source $(BACKLIGHT_SRC_LIST)"

#EXTRA_OBJS += $(BACKLIGHT_OBJ_LIST)