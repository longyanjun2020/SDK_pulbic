
TARGET = tags

all: tags

include $(CONFIG_MAK)

TAGS = cscope.out TAGS
DEP_LIST=$(wildcard $(OUT)*.lib)
DEPS = $(DEP_LIST:$(OUT)%.lib=$(OUT)%.lst)
FULL = $(OUT)$(PRODUCT).lst

.PHONY: tags

# main rule
tags: csn $(TAGS)

# "TAGS" file depends on sources full list
TAGS: $(FULL)
	$(INFO) $@
	cat $< | etags -I -l c -

cscope.out: $(FULL)
	$(INFO) $@
	cscope -b -i $<

$(FULL): $(OUT)headers.lst $(OUT)sources.lst
	$(INFO) $@
	cat $^ > $@

# sources full list depends on SC list
$(OUT)headers.lst: $(DEPS)
	$(INFO) $@
	cat $^ | grep -e "\.h" | sort | uniq > $@

# sources full list depends on SC list
$(OUT)sources.lst: $(DEPS)
	$(INFO) $@
	cat $^ | grep -e "\.c" | sort | uniq > $@

.PHONY: .phony csn

# make SC source list
$(OUT)%.lst: .phony
	$(INFO) $@
	$(MAKE) -r -f $(TNG)dep.mak TARGET=$*

csn:
	$(MAKE) -r -f $(MAK)product.mak csn

clean:
	$(CLEAN) $(TAGS)

