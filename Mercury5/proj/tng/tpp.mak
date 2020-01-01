# Makefiles used to generate pre-processing rules (.tpp)

all: tpp

include $(CONFIG_MAK)

ifeq ($(DUP_FLAG),1)
	tpp-folder:=$(BUILD)dep_cache/tpps/$(PRODUCT)/dup/
else
	tpp-folder:=$(BUILD)dep_cache/tpps/$(PRODUCT)/
endif

# include target definitions
include $(OUT)$(TARGET).dfn
include $(TARGET_MAK)
-include $(tpp-folder)$(TARGET).inc
-include $(OUT)$(TARGET).tpp
DEP_FILES = $(if $(ASM_SRCS),$(OUT)$(TARGET).adep) $(if $(C_SRCS)$(CPP_SRCS),$(OUT)$(TARGET).cdep)

.PHONY: tpp

# main rule
tpp: $(TMP) $(OUT)$(TARGET).tpp

.INTERMEDIATE: $(DEP_FILES)

# folders for makedepend to find necessary header files
CDEP_PATH_H := $(sort $(subst //,/,$(patsubst ./%,%,$(patsubst %/,%,$(subst \,/,$(MMI_PATH_H) \
	$(if $(filter yes, $(NO_PLATFORM_INCLUDE)),,$(filter-out $(MMI_PATH_H), $(PATH_H))) \
	$(if $(filter AEONGCC, $(COMPILER_VERSION)), $(AEONINC)) \
	$(if $(filter MIPSGCC, $(COMPILER_VERSION)), $(MIPSINC)) \
	$(if $(filter X86LINUXGCC, $(COMPILER_VERSION)), $(X86LINUXINC)) \
	$(if $(filter ARMGCC, $(COMPILER_VERSION)), $(ARMGCCINC)))))))

# $(call reorder-folders,PATHS,ALL_PATHS)
# reorder the paths, move PATHS to the front of ALL_PATHS
reorder-folders	=	$(if $(strip $1),$(filter $2,$1) $(filter-out $1,$2),$2)

# $(call _filter-deps,C_FILE,TOUCHED_FILES)
# determine if any of TOUCHED_FILES may change the dependency chain of C_FILE
# 	return C_FILE if it may have already changed
_filter-deps	=	$(if $(filter $(dep_$1),$2),$1)

# $(call touched-srcs,TOUCHED_FILES)
#  find all source files that their dependency may have already changed
touched-srcs	=	$(strip $(foreach f,$(C_SRCS) $(CPP_SRCS),$(call _filter-deps,$f,$1)) \
							$(filter-out $(DEPENDS),$(C_SRCS) $(CPP_SRCS)))

# -I flags for makedepend, re-order if LAST_USED_DIRS is saved in tpp cache
inc-flags		:=	$(patsubst %,-I%,$(call reorder-folders,$(LAST_USED_DIRS),$(CDEP_PATH_H)))

# makedepend options
makdep-opts:= \
	$(if $(filter AEONGCC,$(COMPILER_VERSION)), \
			$(DFLAGS) -D__aeon__ -D__cplusplus, \
		 $(if $(filter MIPSGCC X86LINUXGCC ARMGCC,$(COMPILER_VERSION)), \
			$(DFLAGS) $(MKDEP_FLAGS), \
			-Y$(ARMINC_FOLDER) $(DFLAGS) -D__arm -D__arm__ -D__ARMCC_VERSION -D__cplusplus))\
	$(inc-flags)

# $(call srcs-to-makdep,TOUCHED_FILES)
# identify files need to run makedepend
#srcs-to-makdep = $(if $(call touched-srcs,$1),$(call touched-srcs,$1),$(C_SRCS) $(CPP_SRCS))
srcs-to-makdep = $(call touched-srcs,$1)

# make pre-processing rules (.tpp) from dependencies
$(OUT)$(TARGET).tpp: $(DEP_FILES)
	$(if $(filter %dep,$(DEP_FILES)),,$(error tpp.mak: there is no any c/cpp/asm source file in $(OUT)$(TARGET).dfn and $(TARGET_MAK)))
	$(INFO) $@
	$(TNG)dep2tpp.pl -f $@ -t $(OSTYPE) -i $(OUT)$(TARGET).dfn -o "\$$(TMP)" $(if $(filter 1, $(NO_GROUP_TRACE_ID)),,-g) -r $(DEP_FILES)
	@if [ ! -d $(tpp-folder) ]; then \
		$(MKDIR) $(tpp-folder); \
		touch $(tpp-folder)"These files can be used to speedup makedepend stage.txt"; \
	fi;
	@sed -n -e /INC_DIRS/s//LAST_USED_DIRS/ -e /LAST_USED_DIRS/,/^$$/p $@ > $(tpp-folder)$(TARGET).inc

# gather C and ASM dependencies
#$(OUT)$(TARGET).dep: $(OUT)$(TARGET).cdep $(OUT)$(TARGET).adep
#	cat $^ > $@
#	dos2unix $@

# build C dependencies
$(OUT)$(TARGET).cdep: $(OUT)$(TARGET).dfn $(DEPENDS)
	$(INFO) $@
	echo "cdep [$(TARGET)] \$$?=[$?] files to makdep=[$(call srcs-to-makdep,$?)]"
	echo "-f $@ "$(strip $(makdep-opts))" $(call srcs-to-makdep,$?)" > $(OUT)$(TARGET).opt
	$(TNG)$(OSTYPE)/makedepend @$(OUT)$(TARGET).opt
	@sed -i '/^\(..*\)#/s//\1\n#/g' $@
	#$(TNG)build_system/lib_generation/makdep_cache.pl -p=$(TNG)cygwin/makedepend.exe -d=$(BUILD)dep_cache/ -i=$(OUT)$(TARGET).opt -o=$@
	#-$(CLEAN) $(OUT)$(TARGET).opt

	#echo "$$ ?: $?"
	#echo "run makdep: $(call srcs-to-makdep,$?)"
	## the following line is to enable file-based dependency only, without using dependency cache
	#echo "-f $@ "$(strip $(makdep-opts))" $(call srcs-to-makdep,$?)" > $(OUT)$(TARGET).opt
	## the following line is the original version
	#echo "-f $@ "$(strip $(makdep-opts))" $(C_SRCS) $(CPP_SRCS)" > $(OUT)$(TARGET).opt
	#$(TDEBUG) $(MAKEDEP) @$(OUT)$(TARGET).opt
	#@sed -i '/^\(..*\)#/s//\1\n#/g' $@

ASM_LINE = $(PLTM_AS) $(ASM_OPTIONS) $(PATH_I:%=-I%)
export ASM_LINE
# build ASM dependencies
$(OUT)$(TARGET).adep: $(OUT)$(TARGET).dfn $(ASM_SRCS)
	$(INFO) "asmdep:\t" $@
ifeq ($(findstring gcc, $(PLTM_AS)), )
	$(TNG)asmdep.pl $(if $(FAST),-q) $@ $(ASM_SRCS)
else
	$(TNG)asmdep-gcc.pl $(if $(FAST),-q) $@ $(ASM_SRCS)
endif

$(DEPENDS):;

$(TMP):
	$(INFO) $@
	$(MKDIR) $@

# update target definition file (.dfn)
$(OUT)$(TARGET).dfn: $(TARGET_MAK) $(PATHS_MAK) $(SRC_DIRS)
ifeq ($(DUP_FLAG),1)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)dfn.mak dfn DUP_FLAG=1
else
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)dfn.mak dfn DUP_FLAG=0
endif

