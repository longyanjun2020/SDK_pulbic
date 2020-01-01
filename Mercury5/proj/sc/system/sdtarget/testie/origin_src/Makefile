#########################################################################
# Makefile for ARM ASM tests
#########################################################################

.SUFFIXES: .hex .bin .axf .o .s .asm

HEXFILES= 	test_boot.hex  \
		test_ie.hex \
		test_ie_dc_ldst.hex \
		test_ie_thumb.hex \
		test_ie_java.hex \
		test_ie_bus.hex \
		test_ie_speed_cache.hex \
		test_ie_dhry.hex

ARMASM	= 	armasm
ASFLAGS	=	--cpu 5TE --unsafe --nowarn
AS	=	$(ARMASM) $(ASFLAGS)

ARMLINK	=	armlink
LDFLAGS	=	--map --noremove --nodebug
LK	=	$(ARMLINK) $(LDFLAGS)

FROMELF	=	fromelf

BIN2HEX =	$(PWD)/bin2hex
BH	=	$(BIN2HEX)

CODEADDR=	0x1C000000  # 0x1C020000	# Invalid address, require a specified address
BOOTADDR=	0x00000000	# Invalid address, require a specified address

# main targets
all:	arm.vectors

arm.vectors: bin $(HEXFILES)
		mv *.hex *.bin *.dis bin
		mv *.axf *.map *.sym bin
		rm test_boot.o test_ie_thumb.o

bin:
		mkdir -p bin

clean:
		rm -f *.axf
		rm -f *.o
		rm -f *.bin
		rm -f *.hex
		rm -f *.map *.sym
		rm -rf bin

# generic rule for test cases
%.hex:%.bin
	grep LR_1 $*.map  | sed -e 's/..*Base: //' | sed -e 's/Size: //' | sed -e 's/Max: ..*/\/\/ <- RO\/RW base\/size/' >  $@
	grep ER_RW $*.map | sed -e 's/..*Base: //' | sed -e 's/Size: //' | sed -e 's/Max: ..*/\/\/ <- RW base\/size/' >> $@
	grep ER_ZI $*.map | sed -e 's/..*Base: //' | sed -e 's/Size: //' | sed -e 's/Max: ..*/\/\/ <- ZI base\/size/' >> $@
	$(BH) $< >> $@

%.bin:%.axf
	$(FROMELF) --bin -o $@ $<
	$(FROMELF) -c -o $*.dis $<

%.axf:%.o
	$(LK) --ro_base $(CODEADDR) --entry $(CODEADDR) --info totals --info unused --map --symbols --xref --list $*.map --symdefs $*.sym -o $@ $<

test_ie_thumb.o:src/test_ie_thumb.s
	$(AS) --apcs /inter -o $@ --pd "CODE_ADDR SETA $(CODEADDR)" --pd "BOOT_ADDR SETA $(BOOTADDR)"  --pd "RUN_VAL SETL {TRUE}" $<

%.o:src/%.s
	$(AS) -o $@ --pd "CODE_ADDR SETA $(CODEADDR)" --pd "BOOT_ADDR SETA $(BOOTADDR)" $<

# explicit rule for boot
test_boot.axf:	test_boot.o
	$(LK) --ro_base $(BOOTADDR) --entry $(BOOTADDR) --info totals --info unused --map --symbols --xref --list $*.map  --symdefs $*.sym -o $@ $<
