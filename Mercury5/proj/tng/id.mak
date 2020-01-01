
TARGET=id

all: id

include $(TOP)config.mak

HEADER = $(OUT)sys_rel.hp

.PHONY: id

# main rule
id: $(HEADER)

$(HEADER):
	$(INFO) $@
	$(TNG)id.pl $@

