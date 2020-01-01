
TARGET=install

all: install

include $(CONFIG_MAK)
include $(TARGET_MAK)

.PHONY: install pro-lib

install: $(FILES_TO_COPY:%=$(OUT)%)

# for delivery
vpath %.c $(PATH_C)
vpath %.h $(PATH_H)
vpath %.hi $(PATH_H)
vpath %.hc $(PATH_H)
vpath %.ho $(PATH_H)
vpath %.lib $(PATH_EXT_LIB)
vpath %.dsc $(PATH_DSC)

$(OUT)%.c: %.c
	$(INSTALL) $< $@

$(OUT)%.h: %.h
	$(INSTALL) $< $@

$(OUT)%.hi: %.hi
	$(INSTALL) $< $@

$(OUT)%.ho: %.ho
	$(INSTALL) $< $@

$(OUT)%.hc: %.hc
	$(INSTALL) $< $@

$(OUT)%.lib: %.lib
	$(INSTALL) $< $@

$(OUT)%.dsc: %.dsc
	$(INSTALL) $< $@

# for e2p
vpath %.e2p $(PATH_E2P)

$(OUT)%.e2p: %.e2p
	$(INSTALL) $< $@
