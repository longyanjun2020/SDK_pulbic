include $(CONFIG_MAK)

all: $(OUT_DUP)stack_2.axf

$(OUT_DUP)stack_2.axf: $(wildcard $(OUT_DUP)*.o)
ifneq (,$(strip $(wildcard $(OUT_DUP)*.o)))
	${PLTM_LINK} --edit $(DUP_STR) --partial $(wildcard $(OUT_DUP)*.o) --Output $(OUT_DUP)stack_2.axf
endif
