# Makefiles used to generate pre-processing rules (.tpp)

all: tpp

include $(CONFIG_MAK)

ifeq ($(DUP_FLAG),1)
	tpp-folder:=$(BUILD)dep_cache/tpps/$(PRODUCT)/dup/
else
	tpp-folder:=$(BUILD)dep_cache/tpps/$(PRODUCT)/
endif

# include target definitions
include $(OUT)$(TARGET).rfn
include $(TARGET_MAK)
-include $(tpp-folder)$(TARGET).inc
-include $(OUT)$(TARGET).tpp

DEP_FILES = $(if $(ASM_SRCS),$(OUT)$(TARGET).adep) $(if $(C_SRCS)$(CPP_SRCS),$(OUT)$(TARGET).cdep)

.PHONY: tpp

# main rule
tpp: $(TMP) $(OUT)$(TARGET).tpp

.INTERMEDIATE: $(DEP_FILES)

CDEP_PATH_H := $(sort $(subst //,/,$(patsubst ./%,%,$(patsubst %/,%,$(subst \,/,$(MMI_PATH_H) \
	$(if $(filter yes, $(NO_PLATFORM_INCLUDE)),,$(filter-out $(MMI_PATH_H), $(PATH_H))) \
	$(if $(filter AEONGCC, $(COMPILER_VERSION)), $(AEONINC)) \
	$(if $(filter MIPSGCC, $(COMPILER_VERSION)), $(MIPSINC)) \
	$(if $(filter X86LINUXGCC, $(COMPILER_VERSION)), $(X86LINUXINC)) \
	$(if $(filter ARMGCC, $(COMPILER_VERSION)), $(ARMGCCINC)))))))

reorder-folders	=	$(if $(strip $1),$(filter $2,$1) $(filter-out $1,$2),$2)
_filter-deps	=	$(if $(filter $(dep_$1),$2),$1)
touched-srcs	=	$(strip $(foreach f,$(C_SRCS) $(CPP_SRCS),$(call _filter-deps,$f,$1)) \
							$(filter-out $(DEPENDS),$(C_SRCS) $(CPP_SRCS)))
inc-flags		:=	$(patsubst %,-I%,$(call reorder-folders,$(LAST_USED_DIRS),$(CDEP_PATH_H)))

makdep-opts:= \
	$(if $(filter AEONGCC,$(COMPILER_VERSION)), \
			$(filter -D%,$(CFLAGS)) -D__aeon__ -D__cplusplus, \
		 $(if $(filter MIPSGCC X86LINUXGCC ARMGCC,$(COMPILER_VERSION)), \
			$(filter -D%,$(CFLAGS)) $(MKDEP_FLAGS), \
			-Y$(ARMINC_FOLDER) $(filter -D%,$(CFLAGS)) -D__arm -D__arm__ -D__ARMCC_VERSION -D__cplusplus))\
	$(inc-flags)

#srcs-to-makdep = $(if $(call touched-srcs,$1),$(call touched-srcs,$1),$(C_SRCS) $(CPP_SRCS))
srcs-to-makdep = $(call touched-srcs,$1)

# make pre-processing rules (.tpp) from dependencies
$(OUT)$(TARGET).tpp: $(DEP_FILES)
	$(if $(filter %dep,$(DEP_FILES)),,$(error tpp.mak: there is no any c/cpp/asm source file in $(OUT)$(TARGET).dfn and $(TARGET_MAK)))
	$(INFO) $@
	$(TNG)dep2tpp.pl -f $@ -t $(OSTYPE) -i $(OUT)$(TARGET).rfn -o "\$$(TMP)" $(if $(filter 1, $(NO_GROUP_TRACE_ID)),,-g) -r $(DEP_FILES)
	@if [ ! -d $(tpp-folder) ]; then \
		$(MKDIR) $(tpp-folder); \
		touch $(tpp-folder)"These files can be used to speedup makedepend stage.txt"; \
	fi;
	@sed -n -e /INC_DIRS/s//LAST_USED_DIRS/ -e /LAST_USED_DIRS/,/^$$/p $@ > $(tpp-folder)$(TARGET).inc

# build C dependencies
$(OUT)$(TARGET).cdep: $(OUT)$(TARGET).rfn $(DEPENDS)
	$(INFO) $@
	echo "cdep [$(TARGET)] \$$?=[$?] files to makdep=[$(call srcs-to-makdep,$?)]"
	echo $(strip $(makdep-opts))" $(call srcs-to-makdep,$?)" > $(OUT)$(TARGET).opt
	$(TNG)build_system/lib_generation/makdep_cache.pl -v -p=$(TNG)cygwin/makedepend.exe -d=$(BUILD)dep_cache/ -i=$(OUT)$(TARGET).opt -o=$@
	-$(CLEAN) $(OUT)$(TARGET).opt

	#echo "$$ ?: $?"
	#echo "run makdep: $(call srcs-to-makdep,$?)"
	#echo "-f $@ "$(strip $(makdep-opts))" $(call srcs-to-makdep,$?)" > $(OUT)$(TARGET).opt
	#echo "-f $@ "$(strip $(makdep-opts))" $(C_SRCS) $(CPP_SRCS)" > $(OUT)$(TARGET).opt
	#echo -ne "makdep start "
	#date
	#$(TDEBUG) $(MAKEDEP) @$(OUT)$(TARGET).opt
	#echo -ne "makdep end "
	#date
	#@sed -i '/^\(..*\)#/s//\1\n#/g' $@

ASM_LINE = $(PLTM_AS) $(ASM_OPTIONS) $(PATH_I:%=-I%)
export ASM_LINE
# build ASM dependencies
$(OUT)$(TARGET).adep: $(OUT)$(TARGET).rfn $(ASM_SRCS)
	$(TNG)asmdep.pl $(if $(FAST),-q) $@ $(ASM_SRCS)

$(DEPENDS):;

$(TMP):
	$(INFO) $@
	$(MKDIR) $@

# update target definition file (.rfn)
$(OUT)$(TARGET).rfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)cfn.mak rfn

