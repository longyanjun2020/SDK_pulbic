
include $(CONFIG_MAK)

include $(PATH_middleware)$(MAPPER)/$(TARGET).mak

#TCC = tcc
LD_LIST = --map --symbols --xref --info sizes --info unused
LDFLAGS = --diag_suppress 6305 --diag_suppress 6314
INC_PATH = -I$(INC)
ASMFLAGS = -g --16 --apcs /ropi/rwpi
CFLAGS1 = -g -O2 --apcs /ropi/rwpi --loose_implicit_cast --cpu 5TEJ --fpu softvfp --debug --loose_implicit_cast --min_array_alignment=4 -Otime --c90 
CFLAGS1 += $(DFLAGS)

DLL_BIN_AXF = $(OUT_EML)$(TARGET).axf
DLL_BIN = $(OUT_EML)$(TARGET).bin
DLL_EML = $(OUT_EML)$(TARGET).eml

DLL_BIN_OBJ = $(OUT_EML)$(TARGET)_pveneer.o $(C_SRC_LIST:%.c=$(OUT_EML)%.o)
DLL_BIN_OBJ2 = $(C_OBJ_LIST:%.o=$(OUT_EML)%.o)
DLL_BIN_OBJ3 = $(OUT_EML)eml_main_pveneer.o $(C_SRC_LIST:%.c=$(OUT_EML)%.o)

all : $(DLL_BIN)

$(DLL_BIN): $(DLL_BIN_OBJ3) $(OUT_EML)eml_main_xmmi.ref
	$(PLTM_LINK) --scatter $(TNG)eml/eml_scatter.dsc \
        $(LDFLAGS) $(DLL_BIN_OBJ2) $(DLL_BIN_OBJ3) $(OUT_EML)eml_main_xmmi.ref $(LD_LIST) \
        --list $(OUT_EML)$(TARGET)_link.info \
        --symdefs $(OUT_EML)$(TARGET)_symdefs.info -o $(DLL_BIN_AXF)
	$(PLTM_ELF) $(DLL_BIN_AXF) --bin -o $(DLL_BIN)

%.o: %.s
	$(TDEBUG) $(PLTM_AS) $(ASMFLAGS) -o $@ $<

%.o: %.c
	$(TDEBUG) $(CCACHE) $(CC) -c ${CFLAGS1} -I$(INC) -o $@ $<

$(OUT_EML)%.c: $(PATH_middleware)$(MAPPER)$(SRC)%.c
	$(INSTALL) $< $@
	
clean:
	rm -f $(DLL_BIN) $(DLL_BIN_OBJ) $(DLL_EML)
