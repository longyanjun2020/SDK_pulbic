include $(CONFIG_MAK)

#
# version
# IBUILD_ENHANCE = 2 : normal  build -- full source code)
# IBUILD_ENHANCE = 3 : release build
# IBUILD_ENHANCE = 4 : normal  build -- partial source code

#
# common setting
#
XG_PROFILE=$(subst /,\,$(TNG)incredibuild/profile.xml)

FIX_ARM_LICENSE_PATH?=C:\\ARM\\Licenses\\license.dat
ARMLMD_LICENSE_FILE?=$(FIX_ARM_LICENSE_PATH)
LM_LICENSE_FILE?=$(FIX_ARM_LICENSE_PATH)
export ARMLMD_LICENSE_FILE
export LM_LICENSE_FILE

ifeq ($(RELEASE_PROCESS),0)
%.gentpp:
	@$(call do_if_order,$(OUT)$*.dfn $(OUT)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)lib.mak GENTPPONLY=1 TARGET=$* $(COMPILER_CMD)
%.gentppduo:
	@$(call do_if_order,$(OUT_DUP)$*.dfn $(OUT_DUP)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)lib.mak GENTPPONLY=1 TARGET=$* $(COMPILER_CMD) DUP_FLAG=1
endif
ifeq ($(RELEASE_PROCESS),1)
%.gentpp:
	@$(call do_if_order,$(OUT)$*.dfn $(OUT)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)rellib.mak GENTPPONLY=1 TARGET=$* $(COMPILER_CMD)
%.gentppduo:
	@$(call do_if_order,$(OUT_DUP)$*.dfn $(OUT_DUP)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(RELEASE_MAK)rellib.mak GENTPPONLY=1 TARGET=$* $(COMPILER_CMD) DUP_FLAG=1
endif

#%.gentdfn:
#	$(MAKE_DFN) TARGET=$*   $(COMPILER_CMD)
#%.gendfnduo:
#	$(MAKE_DFN) TARGET=$*   $(COMPILER_CMD) DUP_FLAG=1
#
ifneq ($(IBUILD_ENHANCE),3)

#----------------------------------------------------
#       incredibuild for full source coide (2)
#----------------------------------------------------
#----------------------------------------------------
#          incredibuild for mobile_mst (4)
#----------------------------------------------------
LIB_SET_KERNEL=$(PRODUCT_LIB_MMI) $(PRODUCT_SC) $(PRODUCT_LIB) $(PRODUCT_LIB_MDL) $(PRODUCT_LIB_DRV) $(PRODUCT_LIB_3RD) $(PRODUCT_LIB_SYS)
LIB_SET_STACK2=$(PRODUCT_SC_STACK2) $(PRODUCT_LIB_STACK2)
LIB_SET_OTHER= $(PRODUCT_SC_MMI) $(PRODUCT_SC_MDL) $(PRODUCT_SC_DRV) $(PRODUCT_SC_SYS) $(PRODUCT_SC_3RD)

LIB_SET_KERNEL:=$(filter-out $(LIB_$(QUICK)_SET), $(LIB_SET_KERNEL))
LIB_SET_STACK2:=$(filter-out $(LIB_$(QUICK)_SET), $(LIB_SET_STACK2))
LIB_SET_OTHER:= $(filter-out $(LIB_$(QUICK)_SET), $(LIB_SET_OTHER))

MAKE_COMMAND_IBUILD=$(MAKE) -r -j$(NUM_THREAD) -f $(TNG)lib.mak

## incredibuild commands
PARA_MAKEFILE_ALL_LIB=$(subst /,\,$(MAKE) -r -j$(shell expr 2 \* $(NUM_THREAD)) -f $(TNG)lib_ib.mak IBUILD_ENHANCE=$(IBUILD_ENHANCE) build_lib_all)

all: parallel_all_lib GO_STACK2_MAK GO_MMI_ENUM

ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
remtrace: $(LIB_SET_KERNEL:%=%.genRem) $(LIB_SET_OTHER:%=%.genRem)
else
remtrace: $(LIB_SET_KERNEL:%=%.genRem) $(LIB_SET_STACK2:%=%.genDuoRem) $(LIB_SET_OTHER:%=%.genRem)
endif
%.genRem: %.gentpp
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -j1 -f $(TNG)lib.mak GEN_REMTRACE=1 TARGET=$*

%.genDuoRem: %.gentppduo %.genRem
	@if [ ! -d $(OUT_DUP)remtrace_lib ]; then\
		$(MKDIR) -p $(OUT_DUP)remtrace_lib ;\
	fi;
	@cp -t $(OUT_DUP)remtrace_lib $(OUT_ORG)remtrace_lib/$*_remtrace.csv $(OUT_ORG)remtrace_lib/$*_remtrace.ini -f
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -j1 -f $(TNG)lib.mak GEN_REMTRACE=1 TARGET=$* DUP_FLAG=1
	@cp -t $(OUT_ORG)remtrace_lib $(OUT_DUP)remtrace_lib/$*_remtrace.csv $(OUT_DUP)remtrace_lib/$*_remtrace.ini -f

REM_IN:
	-mv -f $(OUT_ORG)remtrace_lib $(OUT_DUP)remtrace_lib

REM_OUT:
	mv -f $(OUT_DUP)remtrace_lib $(OUT_ORG)remtrace_lib

GO_STACK2_MAK:
ifeq ($(ABI_VER),)
	$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -f $(TNG)stack2.mak
endif

GO_MMI_ENUM:
	IBUILD_ENHANCE=1

parallel_all_lib:
	@echo build with $(NUM_THREAD) threads...
ifeq (1,$(FAST))
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -j$(NUM_THREAD) -f $(TNG)lib_ib.mak IBUILD_ENHANCE=$(IBUILD_ENHANCE) build_lib_all
else
	@$(if $(filter msys,$(OSTYPE)),\
		XGConsole //command="$(PARA_MAKEFILE_ALL_LIB)" //profile="$(XG_PROFILE)" //MaxCPUS=$(NUM_THREAD),\
		XGConsole /command="$(PARA_MAKEFILE_ALL_LIB)" /profile="$(XG_PROFILE)" /MaxCPUS=$(NUM_THREAD))
endif

#parallel XRG
PARA_XRG ?= 0
PARA_XRG_HEADER ?= 0
ifeq ($(PARA_XRG_HEADER),1)
PARA_XRG=1
endif

ifeq ($(PARA_XRG),1)
build_lib_all: mmi_cus_parallel $(LIB_SET_OTHER:%=%.genLib) $(LIB_SET_KERNEL:%=%.genLib) $(LIB_SET_STACK2:%=%.genDuoLib)
else
build_lib_all: $(LIB_SET_OTHER:%=%.genLib) $(LIB_SET_KERNEL:%=%.genLib) $(LIB_SET_STACK2:%=%.genDuoLib)
endif

mmi_cus_parallel:
	$(WARN) PARA_XRG=$(PARA_XRG) PARA_XRG_HEADER=$(PARA_XRG_HEADER)
ifeq (0,$(PARA_XRG_HEADER))
	$(WARN) run mmi_cus_parallel
ifeq (msys,$(OSTYPE))
	make -r -j$(NUM_THREAD_FOR_IBUILD_INNER_FORK) -f $(COMMON)final_product.mak mmi_cus_common_cus
else
	$(MAKE) -r -f $(COMMON)final_product.mak mmi_cus_common_cus
endif
endif

#
# for general lib
#
%.genLib:
	@echo $@ $(SHOW_COMPILER_MODE)
	@$(call do_if_order,$(OUT)$*.dfn $(OUT)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
ifeq (msys,$(OSTYPE))
	@make -r -j$(NUM_THREAD_FOR_IBUILD_INNER_FORK) -f $(TNG)lib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=0
else
	@$(MAKE) -r -f $(TNG)lib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=0
endif

#
# for stack lib
#
%.genDuoLib:
	@echo $@ $(SHOW_COMPILER_MODE)
	@$(call do_if_order,$(OUT_DUP)$*.dfn $(OUT_DUP)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
ifeq (msys,$(OSTYPE))
	@make -r -j$(NUM_THREAD_FOR_IBUILD_INNER_FORK) -f $(TNG)lib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=1
else
	@$(MAKE) -r -f $(TNG)lib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=1
endif

else  ### else of ifeq ($(IBUILD_ENHANCE),3)

#----------------------------------------------------
#         incredibuild for release_package (3)
#----------------------------------------------------
ALL_LIBS= \
	$(PRODUCT_SC_MMI) $(PRODUCT_LIB_MMI) \
	$(PRODUCT_SC) $(PRODUCT_LIB) \
	$(PRODUCT_SC_MDL) $(PRODUCT_LIB_MDL) \
	$(PRODUCT_SC_DRV) $(PRODUCT_LIB_DRV) \
	$(PRODUCT_SC_SYS) $(PRODUCT_LIB_SYS) \
	$(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD)


REL_MAKE_COMMAND_IBUILD=$(MAKE) -r -j$(NUM_THREAD) -f $(RELEASE_MAK)rellib.mak
## incredibuild commands
REL_PARA_MAKEFILE_ALL_LIB=$(subst /,\,$(MAKE) -r -j$(shell expr 2 \* $(NUM_THREAD)) -f $(TNG)lib_ib.mak IBUILD_ENHANCE=$(IBUILD_ENHANCE) build_lib_all)

## A. "remtrace" rule : sequentially call rtpp, and
## B. "parallel_all_lib" rule : generate .o and .lib files by ibuild
all: parallel_all_lib

remtrace: $(ALL_LIBS:%=%.genRem)

%.genRem: %.gentpp
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -j1 -f $(RELEASE_MAK)rellib.mak GEN_REMTRACE=1 TARGET=$*

parallel_all_lib:
	@echo build with $(NUM_THREAD) threads...
ifeq ($(FAST),1)
	@$(if $(filter msys,$(OSTYPE)),make,$(MAKE)) -r -j$(NUM_THREAD) -f $(TNG)lib_ib.mak IBUILD_ENHANCE=$(IBUILD_ENHANCE) build_lib_all
else
	$(if $(filter msys,$(OSTYPE)),\
		XGConsole //command="$(REL_PARA_MAKEFILE_ALL_LIB)" //profile="$(XG_PROFILE)" //MaxCPUS=$(NUM_THREAD),\
		XGConsole /command="$(REL_PARA_MAKEFILE_ALL_LIB)" /profile="$(XG_PROFILE)" /MaxCPUS=$(NUM_THREAD))
endif

build_lib_all: $(ALL_LIBS:%=%.genLib)

#
# for general lib, release build have no stack lib !
#
%.genLib:
	@echo $@ $(SHOW_COMPILER_MODE)
	@$(call do_if_order,$(OUT)$*.rfn $(OUT)$*.tpp,$(PATH_$(*))/$*$(FLAVOR_$*).mak,make clean_lib TARGET=$*;)
ifeq (msys,$(OSTYPE))
	@make -r -j$(NUM_THREAD_FOR_IBUILD_INNER_FORK) -f $(RELEASE_MAK)rellib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=0
else
	@$(MAKE) -r -f $(RELEASE_MAK)rellib.mak TARGET=$* $(COMPILER_CMD) $(CT_CMD) $(UT_CMD) DUP_FLAG=0
endif

endif ### end of ifeq ($(IBUILD_ENHANCE),3)


