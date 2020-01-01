# build dependencies for tags.mak
.PHONY: dep

all: dep

include $(CONFIG_MAK)

include $(OUT)$(TARGET).dfn

DEP=$(OUT)$(TARGET).lst

# main rule: build list of source files
dep: $(DEP)

# command lines used in "tpp" makefile
CPP_LINE=echo $<
PP_LINE=echo $<

include $(OUT)$(TARGET).tpp

# source list depends on source files
$(DEP): $(DEPENDS)
	$(INFO) $@
	ls -1t $(DEPENDS) > $@

# intermediate makefiles rules
$(OUT)$(TARGET).tpp: $(OUT)$(TARGET).dfn $(INC_DIRS)

$(OUT)$(TARGET).dfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)

$(OUT)$(TARGET).dfn $(OUT)$(TARGET).tpp:
	$(MAKE_TPP)
