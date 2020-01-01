
.PHONY: bin lib clean cflags

all: bin

include $(CONFIG_MAK)

include $(OUT)$(TARGET).dfn
include $(OUT)$(TARGET).tpp
# include SC makefile
include $(TARGET_MAK)

TARGET_BIN = $(OUT)$(TARGET).dfn $(OBJS:%.o=$(TMP)%.dsp)
SCATTER_DSP_PATCH = $(COMMON)scatter_b2_dsp.dsc

ifeq ($(LINKER),ADSV12_link)
LDFLAGS_DSP_PATCH=-elf -noremove -info sizes -info unused -xref -list $(OUT)link.info
endif
ifeq ($(LINKER),RVCTV22_link)
LDFLAGS_DSP_PATCH=--elf --no_remove --map --symbols --info sizes --info unused --xref --list $(OUT)$*.info --symdefs symdefs_$*.info
endif

# library rules
#lib: $(TMP) $(INC) cflags $(TARGET_LIB)
bin: $(TMP) $(INC) cflags $(TARGET_BIN)

# library rules
export CFLAGS

# link bin file
$(TMP)%.dsp: $(TMP)%.o
	$(INFO) Src=$< Out=$@
ifeq ($(LINKER),RVCTV22_link)
# generate elf
	$(TDEBUG) $(PLTM_LINK) $(LDFLAGS_DSP_PATCH) --scatter $(SCATTER_DSP_PATCH) -o $*.elf $<
# generate bin
	$(PLTM_ELF) $*.elf --bin --output $@
ifneq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
	mv $@ $@0
	./tng/MSComprs.exe -f"$@0" -o"$@" -a2
	./tng/dsp/align_to_4byte.pl -b $@
endif
endif

DSP_IFLAGS=$(INC_DIRS:%=-I%)
# compile C modules
$(TMP)%.o: $(TMP)%.c
ifeq "$(OSTYPE)" "Win32"
	@echo c Compile Src=$< Out=$@
	$(CC) -c $(CFLAGS) $(DSP_IFLAGS) -o $@ $<
else
	$(INFO) Src=$< Out=$@
	$(TDEBUG) $(CCACHE) $(CC) -c $${CFLAGS} $(DSP_IFLAGS)  -o $@ $<
endif

# assemble ASM modules
$(TMP)%.o: $(TMP)%.asm
ifeq "$(OSTYPE)" "Win32"
	@echo ASM Compile Src=$< Out=$@
	$(PLTM_AS) $(ASM_OPTIONS) $(DSP_IFLAGS) -o $@ $<
else
	$(INFO) Src=$< Out=$@
	$(TDEBUG) $(PLTM_AS) $(ASM_OPTIONS) $(DSP_IFLAGS) -o $@ $<
endif

# create subdirs
$(TMP) $(INC):
	$(INFO) $@
	$(MKDIR) $@

clean:
	$(CLEAN) $(TARGET_LIB)
	$(CLEAN) $(TMP)


cflags:
	$(DEBUG) "CFLAGS = "$(CFLAGS)

ifeq "$(OSTYPE)" "Win32"
CPP_LINE=$(BIN_RTPP) -i $< -o $@
else
CPP_LINE=$(BIN)rtpp -i $< -o $@
endif

PP_LINE=$(INSTALL) $< $@

#include $(OUT)$(TARGET).tpp

$(DEPENDS):;

$(OUT)$(TARGET).tpp: $(OUT)$(TARGET).dfn $(DEPENDS)
	$(MAKE_TPP) DUP_FLAG=0

$(OUT)$(TARGET).dfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)
	$(MAKE_DFN) DUP_FLAG=0
#
#$(OUT)$(TARGET).dfn $(OUT)$(TARGET).tpp:
