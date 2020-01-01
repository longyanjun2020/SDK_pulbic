
TARGET = e2p

.PHONY: e2p

all: e2p

include $(CONFIG_MAK)
include $(TARGET_MAK)

ifeq "$(OSTYPE)" "Win32"
GENE2P = $(BIN_WIN32)gene2p
else
ifneq ($(filter AEONGCC MIPSGCC X86LINUXGCC ARMGCC, $(COMPILER_VERSION)), )
#GENE2P = $(BIN)gene2p_g1
GENE2P = $(BIN)gene2p
else
GENE2P = $(BIN)gene2p
endif
endif


STRUCT_SRC_FILE = $(STRUCT_SRC_NAME:%=$(OUT)%)
STRUCT_PP_FILE = $(STRUCT_SRC_FILE:.c=.pp)
STRUCT_TPP_FILE = $(STRUCT_SRC_FILE:%.c=%.tpp)
STRUCT_DEP_FILE = $(STRUCT_TPP_FILE:%.tpp=%.dep)
PP_OPTIONS = $(PP_OPT_COMMON:%=-D%)
# include dependencies rules
include $(STRUCT_TPP_FILE)

# e2p tempary process directory
CUS_SETTING_E2P := $(wildcard $(E2P_TMP)/cusSetting.e2p.val)
COPY_LIST := $(VALUES_E2P_LIST) $(E2P_TO_DWL)

TARGET_E2P_FILE = $(GENE2P_E2P_FILE:%=$(OUT)%)
VALUES_E2P_FILE = $(TARGET_E2P_FILE:%.e2p=%.e2p.val)
TRACE_FILE=$(OUT).e2ptrace

e2p: $(TARGET_E2P_FILE) $(E2P_TO_DWL:%=$(OUT)%)

# copy all files which within common e2p folder to out/e2p folder
# copy all files which within product e2p folder to out/e2p folder
# if any files with the same name, the product file will OVERWRITE it

PRODUCT_E2P_FILES := $(wildcard $(PATH_e2p_product)/*.*)

copy_e2p:
	for file in $(PRODUCT_E2P_FILES); do \
		cp $$file $(E2P_TMP);\
	done
	dos2unix $(E2P_TMP)/*.*

# blender cusSetting.e2p item with items which within out\e2p

E2P_TMP := $(OUT)e2p

e2p_blender:
	$(BIN)E2pBlender -c $(CUS_SETTING_E2P) -d $(E2P_TMP)/*.e2p,$(E2P_TMP)/*.e2p.val

# $(VALUES_E2P_FILE) is defined herebelow as INTERMEDIATE
# so each time the $(TARGET_E2P_FILE) should be rebuild the $(VALUES_E2P_FILE)
# will be rebuild. Thus if the e2p.mak changed the $(TARGET_E2P_FILE) would be
# rebuild and $(VALUES_E2P_FILE) too.
# generate e2p file based on struct file and all values
$(TARGET_E2P_FILE): $(TARGET_MAK) $(STRUCT_PP_FILE) $(VALUES_E2P_FILE)
	$(RM) $(TRACE_FILE)
	$(INFO) $@
	$(TDEBUG) $(GENE2P) -old $(VALUES_E2P_FILE)\
			-new $(TARGET_E2P_FILE)\
			-s $(STRUCT_PP_FILE)\
			-offset $(GENE2P_OFFSET)\
			-$(GENE2P_LEVEL)\
			-dwl $(OUT)$(GENE2P_DWL_FILE)\
			-h $(OUT)$(GENE2P_HEADER)\
			-c $(OUT)$(GENE2P_CSN)\
			-top $(GENE2P_TOP)\
			$(GENE2P_OMMI)\
			-mask $(GENE2P_MASK)\
			-trc $(TRACE_FILE)

# set search path for values files
# change to $(OUT)\e2p folder
vpath %.e2p.val $(E2P_TMP)
vpath %.e2p $(E2P_TMP)

$(OUT)%.e2p: %.e2p $(STRUCT_PP_FILE)
	$(INFO) $@
	$(TDEBUG) $(GENE2P) -old $< \
	-new $@ \
	-s $(STRUCT_PP_FILE) \
	-dwl $(OUT)$*.dwl \
	-h $(OUT)$*.h \
	-ncsn \
	-trc $(TRACE_FILE)_$*

# $(VALUES_E2P_FILE) is defined as intermediate file, make will remove at the
# end.
#.INTERMEDIATE: $(VALUES_E2P_FILE)

# concatenate all values files
$(VALUES_E2P_FILE): $(VALUES_E2P_LIST)
	cat $^ > $@

# create the pre-processed struct file
$(STRUCT_PP_FILE): $(STRUCT_SRC_FILE)
	$(TDEBUG) $(CC) $(INC_DIRS:%=-I%) -E $(PP_OPTIONS) -P -D__TARGET__ -o $@ $<

# build dependencies rules for the struct file
$(STRUCT_TPP_FILE): $(STRUCT_DEP_FILE)
ifeq "$(OSTYPE)" "Win32"
	$(DEP2TPP) $< $@ "$$(TMP)" "$$(INC)"
else
	$(TNG)dep2tpp.pl -f $@ -t $(OSTYPE) -o "\$$(TMP)" $(STRUCT_DEP_FILE)
endif

#.PHONY: $(STRUCT_HDR_LIST:%=$(OUT)%)
# get dependencies of the struct file
#$(STRUCT_DEP_FILE): $(STRUCT_SRC_FILE) $(STRUCT_HDR_LIST:%=$(OUT)%)
$(STRUCT_DEP_FILE): $(STRUCT_SRC_FILE)
ifeq ($(OSTYPE),$(findstring $(OSTYPE),cygwin msys linux))
ifneq ($(filter AEONGCC MIPSGCC X86LINUXGCC, $(COMPILER_VERSION)), )
	$(MAKEDEP) -o.pp -f $@ $(AEONINC:%=-I%) $(DFLAGS) $(IFLAGS) $(STRUCT_SRC_FILE)
else
ifneq ($(filter ARMGCC, $(COMPILER_VERSION)), )
	$(MAKEDEP) -o.pp -f $@ $(ARMGCCINC:%=-I%) $(DFLAGS) $(IFLAGS) $(STRUCT_SRC_FILE)
else
	$(MAKEDEP) -o.pp -f $@ -Y$(ARMINC_FOLDER) $(DFLAGS) $(IFLAGS) $(STRUCT_SRC_FILE)
endif
endif
else
	$(MAKEDEP) -o.pp -f $@ -Y$(ARMINC) $(DFLAGS) $(IFLAGS) $(STRUCT_SRC_FILE)
endif
	sed -i '/^\(..*\)#/s//\1\n#/g' $@
	dos2unix $@

#CPP_LINE=$(BIN)rtpp -i $< -o $@
PP_LINE=$(INSTALL) $< $@

# create struct source file
$(STRUCT_SRC_FILE): $(TARGET_MAK)
	$(TNG)e2pstruct.pl $@ $(STRUCT_HDR_LIST)

