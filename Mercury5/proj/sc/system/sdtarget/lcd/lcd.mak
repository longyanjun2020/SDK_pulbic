#
# Makefile : lcd.a
#

LCD_SRC_LIST = $(notdir $(wildcard ./lcd/drv/src/*.c))

LCD_OBJ_LIST=$(patsubst %.c, $(OUT_DIR)/%.o, $(patsubst %.s, $(OUT_DIR)/%.o, $(LCD_SRC_LIST)))

DEPFILES += $(patsubst %.c, $(DEP_DIR)/%.d, $(LCD_SRC_LIST))

LIB_LIST += $(OUT_DIR)/lcd.a

DEP_INC += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(HAL)/inc

VPATH += lcd/drv/src

$(LCD_OBJ_LIST): INC_LIST += -Ilcd/drv/inc -Ilcd/cust/inc -Ilcd/hal_$(HAL)/inc

$(OUT_DIR)/lcd.a: $(LCD_OBJ_LIST)
	@ $(AR) $(ARFLAGS) $@ $(LCD_OBJ_LIST)
	@ echo $@ "... library created"
	@ echo "LCD source $(LCD_SRC_LIST)"
