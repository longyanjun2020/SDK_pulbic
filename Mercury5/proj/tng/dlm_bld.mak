
#-------------------------------------------------------------------------------
# for debuging
#-------------------------------------------------------------------------------
DLM_BLD_VERBOSE=0
DLM_BLD_VERBOSE_FUNC=$(call MAK_VERBOSE, $(DLM_BLD_VERBOSE), $(1))

OUT_DLM_TARGET_DIR=$(OUT_DLM)$(TARGET)_dir/
PP_LINE=$(INSTALL) $< $@;
CPP_LINE=$(COPY) -fu $< $@#;$(WARN) src=$< dst=$@;

include $(CONFIG_MAK)
include $(TARGET_MAK)

ifneq "$(CLEAN_FILE)" "1"
include $(OUT_DLM_TARGET_DIR)$(TARGET).dfn
include $(OUT_DLM_TARGET_DIR)$(TARGET).tpp
endif

.PHONY: .phony

LD_LIST = --map --symbols --xref --info sizes --info unused
LDFLAGS = --diag_suppress 6305 --diag_suppress 6314
INC_PATH = -I$(INC)

ASMFLAGS = -g --16 
CFLAGS1 = -g -O2 --loose_implicit_cast --cpu 5TEJ --fpu softvfp --debug --loose_implicit_cast --min_array_alignment=4 -O2 --c90 

ASMFLAGS += $(if $(filter INDEPENDENT, $(DLM_LINKER)), --apcs /ropi/rwpi) $(if $(filter ARM, $(DLM_COMPILER)), --arm, --thumb)
CFLAGS1  += $(if $(filter INDEPENDENT, $(DLM_LINKER)), --apcs /ropi/rwpi) $(if $(filter ARM, $(DLM_COMPILER)), --arm, --thumb)

CFLAGS1 += $(DFLAGS)

DLM_BIN_LIB = $(OUT_DLM_TARGET_DIR)$(TARGET).lib
DLL_BIN_AXF = $(OUT_DLM_TARGET_DIR)$(TARGET).axf
DLL_BIN = $(OUT_DLM_TARGET_DIR)$(TARGET).bin
DLL_BIN_OBJ = $(OUT_DLM_TARGET_DIR)$(TARGET)_pveneer.o $(OBJS:%=$(OUT_DLM_TARGET_DIR)%)
DLM_SCATTER=$(if $(filter ABSTRACT,$(DLM_LINKER)), $(TNG)dlm_scatter_abs.dsc, $(TNG)dlm_scatter.dsc)
DEP_HEADER_FILE=$(filter %.h %.hc %.hi %.hv %.hm %.ho %.hp %.ht, $(DEPENDS))

all : prepare_file $(DLL_BIN)

prepare_file: .phony
ifeq ($(RELEASE_PROCESS),0)
	$(COPY) -fu $(C_SRCS) $(OUT_DLM_TARGET_DIR)
else
	$(WARN) "DLM: prepare_file do nothing in release process"
endif

$(DLL_BIN): $(DEP_HEADER_FILE) $(OUT_DLM_TARGET_DIR)$(TARGET)_pveneer.o $(DLM_BIN_LIB) $(OUT_DLM_TARGET_DIR)$(TARGET)_xmmi.ref
	$(WARN) $@
	$(PLTM_LINK) --scatter $(DLM_SCATTER) $(LDFLAGS) \
            $(DLL_BIN_OBJ) $(OUT_DLM_TARGET_DIR)$(TARGET)_xmmi.ref $(LD_LIST) \
            --list $(OUT_DLM_TARGET_DIR)$(TARGET)_link.info \
            --symdefs  $(OUT_DLM_TARGET_DIR)$(TARGET)_symdefs.info -o $(DLL_BIN_AXF)
	$(PLTM_ELF) $(DLL_BIN_AXF) --bin -o $(DLL_BIN)


ifeq ($(RELEASE_PROCESS),0)
# normal build
$(DLM_BIN_LIB): $(SRC_C_LIST:%.c=$(OUT_DLM_TARGET_DIR)%.o)
	$(call DLM_BLD_VERBOSE_FUNC, 3-1 store file)
	$(PLTM_AR) -r $@  $(SRC_C_LIST:%.c=$(OUT_DLM_TARGET_DIR)%.o)
	$(COPY) -fu $@ $(PATH_DLM_LIB)
else
# release build
$(DLM_BIN_LIB): .phony
	$(call DLM_BLD_VERBOSE_FUNC, 3-2 restore file)
	$(COPY) -fu $(PATH_DLM_LIB)$(notdir $@) $@
	$(PLTM_AR) -x $@
	mv $(OBJS) $(OUT_DLM_TARGET_DIR)
endif

	
%.o: %.s
	$(call DLM_BLD_VERBOSE_FUNC, 1. src=$< dst=$@)
	$(TDEBUG) $(PLTM_AS) $(INC_DIRS:%=-I%) $(ASMFLAGS) -o $@ $<


%.o: %.c
	$(call DLM_BLD_VERBOSE_FUNC, 2. src=$< dst=$@)
ifeq ($(RELEASE_PROCESS),0)
	$(TDEBUG) $(CCACHE) $(CC) -c ${CFLAGS1} $(INC_DIRS:%=-I%) -o $@ $<
else
	$(ERROR "dlm should not come here, stop building...")
endif


#
# DLL_DLM get from dlm_gen.mak
#
clean: .phony
	$(CLEAN) $(DLL_BIN) $(DLL_DLM) 
