
all: clean_lib

include $(CONFIG_MAK)

# include SC makefile
include $(TARGET_MAK)

OBJS=$(SRC_C_LIST:%.c=%.o) \
	$(SRC_ASM_LIST:%.asm=%.o) \
	$(REL_SRC_C_LIST:%.c=%.o) \
	$(REL_SRC_ASM_LIST:%.asm=%.o) \
	$(SRC_CPP_LIST:%.cpp=%.o) \
	$(REL_SRC_CPP_LIST:%.cpp=%.o)

CLEAN_SRC_ASM_LIST=$(SRC_ASM_LIST:%.asm=$(OUT)%.asm) $(REL_SRC_ASM_LIST:%.asm=$(OUT)%.asm)
CLEAN_SRC_C_LIST=$(SRC_C_LIST:%.c=$(OUT)%.c)         $(REL_SRC_C_LIST:%.c=$(OUT)%.c)
CLEAN_SRC_CPP_LIST=$(SRC_CPP_LIST:%.cpp=$(OUT)%.cpp) $(REL_SRC_CPP_LIST:%.cpp=$(OUT)%.cpp)
CLEAN_OBJS_LIST=$(OBJS:%.o=$(OUT)%.o)
CLEAN_CAA_LIST=$(OBJS:%.o=$(OUT)%.caa)
CLEAN_HEADER_LIST=$(OBJS:%.o=$(OUT)%.h)

clean_lib:
	$(WARN) clean lib $(TARGET)
	$(CLEAN) $(CLEAN_SRC_ASM_LIST) \
			  $(CLEAN_SRC_C_LIST) \
			  $(CLEAN_SRC_CPP_LIST)\
			  $(CLEAN_OBJS_LIST) \
			  $(CLEAN_CAA_LIST) \
			  $(CLEAN_HEADER_LIST) \
			  $(OUT)$(TARGET).dfn \
			  $(OUT)$(TARGET).lib \
			  $(OUT)$(TARGET).rem \
			  $(OUT)$(TARGET).tpp \
			  $(OUT)$(TARGET).tpp2 \
			  $(OUT)remtrace_lib/$(TARGET)_remtrace.csv \
			  $(OUT)remtrace_lib/$(TARGET)_remtrace.ini
