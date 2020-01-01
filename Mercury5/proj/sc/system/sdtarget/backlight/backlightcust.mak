#
# Makefile : backlightcust.a
#

BACKLIGHTCUST_SRC_LIST = $(notdir $(wildcard ./backlight/cust/src/*.c))

BACKLIGHTCUST_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(BACKLIGHTCUST_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(BACKLIGHTCUST_SRC_LIST))

#LIB_LIST += $(OUT_DIR)/backlightcust.a

DEP_INC += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

VPATH += backlight/cust/src

$(BACKLIGHTCUST_OBJ_LIST): INC_LIST += -Ibacklight/drv/inc -Ibacklight/cust/inc -Ibacklight/hal_$(HAL)/inc

#$(OUT_DIR)/backlightcust.a: $(BACKLIGHTCUST_OBJ_LIST)
#	@ $(AR) $(ARFLAGS) $@ $(BACKLIGHTCUST_OBJ_LIST)
#	@ echo $@ "... library created"
#	@ echo "Backlight source $(BACKLIGHTCUST_SRC_LIST)"

EXTRA_OBJS += $(BACKLIGHTCUST_OBJ_LIST)