
include $(CONFIG_MAK)

include $(PATH_middleware)$(MAPPER)/$(TARGET).mak

all: $(OUT_EML)$(TARGET).bin

$(OUT_EML)$(TARGET).bin: $(OUT)link.info $(PATH_middleware)$(MAPPER) $(C_SRC_LIST:%=$(PATH_middleware)$(MAPPER)$(SRC)%)
	$(WARN) $@
	$(MAKE_EML_BLD) clean TARGET=$(TARGET) MAPPER=$(MAPPER)
	$(MAKE_EML_BLD) TARGET=$(TARGET) MAPPER=$(MAPPER)
