
include $(CONFIG_MAK)

include $(PATH_middleware)$(TARGET)/$(TARGET).mak

all: $(OUT_EML)$(TARGET).dlm

$(OUT_EML)$(TARGET).dlm: $(OUT)link.info $(PATH_middleware)$(TARGET) $(C_SRC_LIST:%=$(PATH_middleware)$(TARGET)/src/%)
	$(WARN) $@
	$(MAKE_EML_BLD) clean TARGET=$(TARGET) MAPPER=$(TARGET) SRC='$(SRC)'
	$(VENEERGEN) -id $(PATH_dlm_entry_inc)$(TARGET).def \
                 -ik $(OUT)link.info \
                 -ov $(OUT_EML)$(TARGET)_pveneer.s \
                 -or $(OUT_EML)$(TARGET)_xmmi.ref
	$(MAKE_EML_BLD) TARGET=$(TARGET) MAPPER=$(TARGET) SRC='$(SRC)'
	$(DLMIZE) -id $(PATH_dlm_entry_inc)$(TARGET).def \
              -is $(OUT_EML)$(TARGET)_symdefs.info \
              -ik $(OUT_EML)$(TARGET)_link.info \
              -ib $(OUT_EML)$(TARGET).bin \
              -om $(OUT_EML)$(TARGET).dlm
