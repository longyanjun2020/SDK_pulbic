SHELL=/bin/sh
TOP=./
CONFIG_MAK=$(TOP)config.mak

include $(CONFIG_MAK)
LOG_FILE=$(BUILD)$(PRODUCT)/log
LOG_FILE:=$(if $(LOG_POSTFIX), $(LOG_FILE)_$(LOG_POSTFIX), $(LOG_FILE))

include $(TNG)product.mak

# speedup with not using built-in rules and variables
# -r: don't use built-in rules
# -R: don't use built-in variables
# -no-print directory Make enter or leave
MAKEFLAGS += -rsR --no-print-directory

ifeq ($(COMPILER_VERSION),AEONGCC)
	export UNDERSCORE=$(shell $(TNG)/leadingunderscore.sh)
	export CCACHE=$(shell which ccache 2>/dev/null)
	# use directory from cpp makes makedepend slow, hardcode it first
	# export AEONINC=$(shell echo | LANG=C aeon-cpp -x c++ -Wp,-v 2>&1 | grep '^ ' | xargs cygpath -u)
	GCC_VER=$(shell aeon-elf-gcc -v 2>&1 | sed -nr '/^gcc version /{s/gcc version ([0-9\.]*) .*/\1/;p}')
	export AEONINC=/opt/aeon-elf/aeon-elf/include /opt/aeon-elf/lib/gcc/aeon-elf/$(GCC_VER)/include
#	export AEONINC=$(shell echo "" | LANG=C aeon-elf-cpp -v 2>&1 | grep "^ " | grep "include" | )
#	export AEONINC=/cygdrive/c/Program\ Files/MStar/gcc/lib/gcc/aeon-elf/4.4.3/include /cygdrive/c/Program\ Files/MStar/gcc/lib/gcc/aeon-elf/4.4.3/include-fixed /cygdrive/c/Program\ Files/MStar/gcc/aeon-elf/include
endif

ifeq ($(COMPILER_VERSION),ARMGCC)
#	export UNDERSCORE=$(shell $(TNG)/leadingunderscore.sh)
#	export CCACHE=$(shell which ccache 2>/dev/null)
	# use directory from cpp makes makedepend slow, hardcode it first
	# export AEONINC=$(shell echo | LANG=C aeon-cpp -x c++ -Wp,-v 2>&1 | grep '^ ' | xargs cygpath -u)
ifeq ($(OSTYPE), cygwin)
	GCC_VER=$(shell arm-none-eabi-gcc -v 2>&1 | sed -nr '/^gcc version /{s/gcc version ([0-9\.]*) .*/\1/;p}')
	export ARMGCCINC=/opt/arm-none-eabi/arm-none-eabi/include /opt/arm-none-eabi/lib/gcc/arm-none-eabi/$(GCC_VER)/include
else

ifeq ($(COMPILER_EXECUTABLE),arm-linux-gnueabihf-gcc)
	GCC_VER=$(shell arm-linux-gnueabihf-gcc -v 2>&1 | sed -nr '/^gcc version /{s/gcc version ([0-9\.]*) .*/\1/;p}')
	export ARMGCCINC=/home/toolchain/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/arm-linux-gnueabihf/libc/usr/include \
    /home/toolchain/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/lib/gcc/arm-linux-gnueabihf/4.8.3/include
else
	GCC_VER=$(shell arm-none-eabi-gcc -v 2>&1 | sed -nr '/^gcc version /{s/gcc version ([0-9\.]*) .*/\1/;p}')
	export ARMGCCINC=/home/toolchain/gcc-linaro-arm-none-eabi-4.8-2014.04_linux/arm-none-eabi/include \
    /home/toolchain/gcc-linaro-arm-none-eabi-4.8-2014.04_linux/lib/gcc/arm-none-eabi/4.8.3/include
endif

endif
#	export AEONINC=$(shell echo "" | LANG=C aeon-elf-cpp -v 2>&1 | grep "^ " | grep "include" | )
#	export AEONINC=/cygdrive/c/Program\ Files/MStar/gcc/lib/gcc/aeon-elf/4.4.3/include /cygdrive/c/Program\ Files/MStar/gcc/lib/gcc/aeon-elf/4.4.3/include-fixed /cygdrive/c/Program\ Files/MStar/gcc/aeon-elf/include
endif

ifneq ($(ARMINC),)
	ifeq (msys,$(OSTYPE))
	ARMINC_FOLDER := $(ARMINC)
	else
	ARMINC_FOLDER := $(shell cygpath '$(ARMINC)')
	endif
endif
export ARMINC_FOLDER

#Retrieve products list in sc/product
LIST_OF_PRODUCTS=$(patsubst options_%.mak, %, $(notdir $(wildcard ./mak/options_*.mak)))

.PHONY: .phony

which :
	@echo ;\
	for PROD in $(LIST_OF_PRODUCTS);do\
		((I=I+1));\
		if [ "$$PROD" = "$(PRODUCT)" ];then\
			echo -e "$$I - $$PROD \e[56G(\e[31mDefault\e[0m)";\
		else\
			echo -n "$$I - $$PROD ";\
			if [ ! -f "$(BUILD)$$PROD/config.mak" ];then\
				echo -e "\e[56G(Not Configured yet)";\
			else\
				echo -e "\e[56G(Not current product)";\
			fi;\
		fi;\
	done;

	@for PROD in $(LIST_OF_PRODUCTS);do\
		((I=I+1));\
		if [ "$$PROD" = "$(PRODUCT)" ];then\
			echo -n "Change default [$$I]: "; read new;\
			for PROD2 in $(LIST_OF_PRODUCTS);do\
				((J=J+1));\
				if [ "$$J" = "$$new" ];then\
					if [ "$$PROD2" = "$(PRODUCT)" ];then\
						echo -e "Default is " "\e[31m"$$PROD2"\e[0m";\
					else\
						echo -e "Start configure" "\e[31m"$$PROD2"\e[0m";\
						./tng/configure.pl "$$PROD2";\
						echo -e "Finish configure" "\e[31m"$$PROD2"\e[0m";\
					fi;\
					break;\
				fi;\
			done;\
		fi;\
	done;

%:
	@$(MAKE) -r -s sublibs USER_LIB=$@

#libs rules
$(PRODUCT_SC):
	@$(MAKE) -r -s libs PRODUCT_SC=$@

#Building rules
$(LIST_OF_PRODUCTS):
	@if [ -f $(BUILD)$@/config.mak ];then\
		echo Making $@;\
		$(MAKE) -r -s PRODUCT=$@ CONFIG_MAK=$(BUILD)$@/config.mak LOG_FILE=$(BUILD)$@/log;\
	else\
		echo;\
		echo $@ MUST be configured to be built!!!;\
		echo;\
	fi;

#Cleaning rules
$(LIST_OF_PRODUCTS:%=clean%):
	@if [ -f $(BUILD)$(@:clean%=%)/config.mak ];then\
                echo Cleaning $(@:clean%=%);\
                $(MAKE) -r -s PRODUCT=$(@:clean%=%) CONFIG_MAK=$(BUILD)$(@:clean%=%)/config.mak LOG_FILE=$(BUILD)$(@:clean%=%)/log clean;\
        else\
		echo;\
                echo $(@:clean%=%) MUST be configured cleaned!!!;\
		echo;\
        fi;

#Logging rules
$(LIST_OF_PRODUCTS:%=log%):
	@if [ -f $(BUILD)$(@:log%=%)/config.mak ];then\
                $(MAKE) -r -s PRODUCT=$(@:log%=%) CONFIG_MAK=$(BUILD)$(@:log%=%)/config.mak LOG_FILE=$(BUILD)$(@:log%=%)/log log;\
        else\
		echo;\
                echo $(@:log%=%) MUST be configured before log!!!;\
		echo;\
        fi;


RELEASE_MAK=$(COMMON)release_mak/
MAKE_RELEASE=@$(MAKE) -s -r -f $(RELEASE_MAK)Makefile.res RELEASE_PROCESS=1
MAKE_RELEASE_SPEED=$(MAKE_RELEASE) SPEED=1

#-------------------------------------------------------------------------------
# SCM make commands
#-------------------------------------------------------------------------------
SCM_clean:
	$(MAKE_RELEASE) SCM_clean

REL_DIR = $(TOP)rel_src/

SCM_clean_source:
	$(TNG_MAKE) -f $(PRODUCT_MAK) SCM_clean $(LOG_LINE)
	cp -r $(REL_DIR)sc $(TOP)
	$(CLEAN) $(REL_DIR)

gen_pure_lib:
	@echo generate pure lib...
	@$(GEN_SOURCE_CODE_LIB)
	
release_DZbuild:
	@$(MAKE) -sr -f $(RELEASE_MAK)Makefile.res release_fast IBUILD=1 FAST=1 SPEED=1 AUTO_CLEAN=1 SKIP_E2P_HTML=0 RELEASE_PROCESS=1

#-------------------------------------------------------------------------------
# release package make commands
#-------------------------------------------------------------------------------
release_undo:
	$(MAKE_RELEASE) release_undo
	
release_log:
	$(MAKE_RELEASE) release_log
	
release_build:
	$(MAKE_RELEASE) release_build

release_ibuild:
	@echo -n -e "\e[1m\e[34m Use Incredibuild.\e[0m\n";
	$(MAKE_RELEASE) release_ibuild IBUILD=1 SPEED=1 IBUILD_ENHANCE=1

release_fast:
	@echo -n -e "\e[1m\e[34m fast mode.\e[0m\n";
	@$(MAKE) -sr -f $(RELEASE_MAK)Makefile.res release_fast SPEED=1 IBUILD=1 FAST=1 XRG_CUS=LangPack0000 RELEASE_PROCESS=1

release_mmi_app:
	$(MAKE_RELEASE_SPEED) release_mmi_app

release_mmi_srv:
	$(MAKE_RELEASE_SPEED) release_mmi_srv

release_mmi_mae:
	$(MAKE_RELEASE_SPEED) release_mmi_mae

release_mmi_core:
	$(MAKE_RELEASE_SPEED) release_mmi_core

release_mmi_common:
	$(MAKE_RELEASE_SPEED) release_mmi_common

release_mmi_widget:
	$(MAKE_RELEASE_SPEED) release_mmi_widget

release_mmi_res:
	$(MAKE_RELEASE_SPEED) release_mmi_res

release_speed:
	$(MAKE_RELEASE_SPEED) release_build

release_speed_cus0:
	$(MAKE_RELEASE_SPEED) release_build	XRG_CUS=LangPack0000

release_mdl:
	$(MAKE_RELEASE_SPEED) release_mdl

release_drv:
	$(MAKE_RELEASE_SPEED) release_drv

release_sys:
	$(MAKE_RELEASE_SPEED) release_sys

release_mmi:
	$(MAKE_RELEASE_SPEED) release_mmi

release_3rd:
	$(MAKE_RELEASE_SPEED) release_3rd

release_libs:
	$(MAKE_RELEASE_SPEED) release_libs

release_final:
	$(MAKE_RELEASE_SPEED) release_final

release_e2p:
	$(MAKE_RELEASE_SPEED) release_e2p


#-------------------------------------------------------------------------------
# partial source code make commands
#-------------------------------------------------------------------------------
	
prepare:
	@echo -n -e "\e[1m\e[34mPreparing libraries from full source. Make sure you have all of them.\e[0m\n";
	@echo -n -e "\e[1m\e[34mLater you can do quick build by \"make quick\" and skip the prepared libraries.\e[0m\n";
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -r -s PREPARE=1 SPEED=1

prepare_files:
	@echo -n -e "\e[1m\e[34mPreparing files...\e[0m\n";
	@$(MAKE) -r -s final PREPARE=1 SPEED=1 SKIP_E2P_HTML=1

quick_ps:
	@echo -n -e "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -n -e "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -n -e "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -r -s QUICK=ps SPEED=1

quick_ap:
	@echo -n -e "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -n -e "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -n -e "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -r -s QUICK=ap SPEED=1
	
quick_sys:
	@echo -n -e "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -n -e "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -r -s QUICK=sys SPEED=1

quick_ps_fast:
	@echo -ne "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -ne "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -ne "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -ne "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -rs __fast QUICK=ps SPEED=1 IBUILD=1 IBUILD_ENHANCE=0 FAST=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

quick_ap_fast:
	@echo -ne "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -ne "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -ne "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -ne "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -rs __fast QUICK=ap SPEED=1 IBUILD=1 IBUILD_ENHANCE=0 FAST=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"
	
quick_sys_fast:
	@echo -ne "\e[1m\e[34mQuick mode, skipping prepared libraries.\e[0m\n";
	@echo -ne "\e[1m\e[34mYou can specifiy which library should be prepared in lib_paths.mak, and prepare them by \"make prepare\".\e[0m\n";
	@echo -ne "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -rs __fast QUICK=sys SPEED=1 IBUILD=1 IBUILD_ENHANCE=0 FAST=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

DZ_quick_MSC:
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -n -e "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -r -s QUICK=MSC SPEED=1 AUTO_CLEAN=1

DZ_quick_MSZ:
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@echo -n -e "\e[1m\e[34mIf the above parsing fails, please analyze make_src_dir.log or provide this log to SCM for analysis.\e[0m\n";
	@$(MAKE) -r -s QUICK=MSZ SPEED=1 AUTO_CLEAN=1

ibuild_mst:
	@echo -n -e "\e[1m\e[34m Incredibuild for MST.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@$(MAKE) -r __ibuild_mst -s QUICK=MST SPEED=1 IBUILD=1 IBUILD_ENHANCE=1

ibuild_msz:
	@echo -n -e "\e[1m\e[34m Incredibuild for MST.\e[0m\n";
	@perl $(TNG)p4/make_src_dir.pl $(TNG)p4/p4_access.txt $(TOP)/.. > $(TNG)p4/make_src_dir.log
	@$(MAKE) -r __ibuild_mst -s QUICK=MSZ SPEED=1 IBUILD=1 IBUILD_ENHANCE=1


#----------------------------------------
# obsolete  command for quick build
#----------------------------------------
quick:
	@echo -n -e "\e[31m Please use \"make quick_MSZ\" instead of \"make quick\" \n\e[0m";
	@echo "QUICK=$(QUICK)"
	$(if $(strip $(QUICK)),,$(error QUICK variable is not set!!))
	@$(MAKE) -r -s QUICK=$(QUICK) SPEED=1

quick_fast:
	@echo -n -e "\e[31m Please use \"make quick_MSZ\" instead of \"make quick\" \n\e[0m";
	$(if $(strip $(QUICK)),,$(error QUICK variable is not set!!))
	@$(MAKE) -rs __fast QUICK=$(QUICK) SPEED=1 IBUILD=1 IBUILD_ENHANCE=0 FAST=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

#-------------------------------------------------------------------------------
# full source code make commands for RD
#-------------------------------------------------------------------------------
mmi_cus0:
	@echo -n -e "\e[1m\e[34m Gen 1 language package \e[0m\n" ;
	@$(MAKE) -r -s SPEED=1 mmi_cus XRG_CUS=LangPack0000

debug_cus0:
	@echo -n -e "\e[1m\e[34m Gen 1 language package Debug Mode\e[0m\n" ;
	@$(MAKE) -s SPEED=1 debug_cus XRG_CUS=LangPack0000

speed_cus0:
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console. (only one CUS) \e[0m\n";
	@$(MAKE) -r -s SPEED=1 XRG_CUS=LangPack0000

speed:
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -r -s SPEED=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

speed_g1:
	@echo -n -e "\e[1m\e[34mSpeed mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -r -s SPEED=1 AUTO_CLEAN=1 NUM_THREAD=200 NUM_THREAD_FOR_TPP=50 PARAL_TPP=1 SKIP_E2P_HTML=1 XRG_CUS=LangPack0000

fast:
	@echo -n -e "\e[1m\e[34mFast mode. Not display lots compile information on Console.\e[0m\n";
	@$(MAKE) -r -s __fast SPEED=1 IBUILD=1 IBUILD_ENHANCE=0 FAST=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

ibuild:
	@echo -n -e "\e[1m\e[34m Use Incredibuild.\e[0m\n";
	@$(MAKE) -r -s IBUILD=1 SPEED=1 IBUILD_ENHANCE=1 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))"

dzibuild_1:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server, using Incredibuild\e[0m\n" ;
	@$(MAKE) -r -s IBUILD=1 SPEED=1 IBUILD_ENHANCE=1 AUTO_CLEAN=1 PARAL_TPP=1

dzibuild:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server, using Incredibuild\e[0m\n" ;
	@$(MAKE) -r -s IBUILD=1 SPEED=1 IBUILD_ENHANCE=1 AUTO_CLEAN=1 PARAL_TPP=1 SKIP_E2P_HTML=0 XRG_FIRST_CUS=1 NO_DEBUG=1

e2p_fast:
	@echo -n -e "\e[1m\e[34m This make command is the same as 'make e2p'\e[0m\n";
	@echo -n -e "\e[1m\e[34m except it skips e2p html generation\e[0m\n";
	@$(MAKE) -r e2p SKIP_E2P_HTML=1
	
final_fast:
	@echo -n -e "\e[1m\e[34m This make command is the same as 'make final' \e[0m\n";
	@echo -n -e "\e[1m\e[34m except it skips e2p html generation\e[0m\n";
	@$(MAKE) -r final SKIP_E2P_HTML=1 SKIP_GEN_MSG_MAE_ID=0

final_fast2:
	@echo -n -e "\e[1m\e[34m This make command is the same as 'make final' except it does \e[0m\n";
	@echo -n -e "\e[1m\e[34m not generate msg id for backtrace and it skips e2p html generation\e[0m\n";
	@$(MAKE) -r final SKIP_E2P_HTML=1 SKIP_GEN_MSG_MAE_ID=1

link_debug:
	@echo -n -e "\e[1m\e[34m It is link stage with showing degug info in link.info  \e[0m\n";
	@$(MAKE) -r link LINK_VERBOSE=1

find_multiple_symbol_definition:
	@echo -n -e "\e[1m\e[34m This command is for G1 only !!  \e[0m\n";
	@$(MAKE) -r SPEED=1 XRG_CUS=LangPack0000 CHK_MULTIPLE_SYMBOL_DEF=1
	
gen_path:
	@$(MAKE) -r _gen_path

lint_preprocess:
	@$(MAKE) -r _lint_preprocess

#-------------------------------------------------------------------------------
# full source code make commands for server
#-------------------------------------------------------------------------------
DZbuild_2core:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server, and the build process using 4 threads \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=4 NUM_THREAD_FOR_TPP=4 PARAL_TPP=1 SKIP_E2P_HTML=0 XRG_CUS=LangPack0000

# for P4Checker
DZbuild:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@$(MAKE) -s -r __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 PARAL_TPP=1 SKIP_E2P_HTML=0 XRG_CUS="$(if $(strip $(XRG_CUS)),$(XRG_CUS),$(if $(filter DEFAULT,$(LANGUAGE_PACK_LIST)),LangPack0000,$(LANGUAGE_PACK_LIST)))" NO_DEBUG=1

DZbuild_debug:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@echo -n -e "\e[1m\e[34m with debug info \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=16 NUM_THREAD_FOR_TPP=4 PARAL_TPP=1 SKIP_E2P_HTML=0 XRG_CUS=LangPack0000

# For DropZone (Default)
DZbuild_2:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=16 NUM_THREAD_FOR_TPP=4 PARAL_TPP=1 SKIP_E2P_HTML=1 SKIP_GEN_MSG_MAE_ID=1 XRG_CUS=LangPack0000 NO_DEBUG=1

# For DropZone with test E2P
DZbuild_3:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=16 NUM_THREAD_FOR_TPP=4 PARAL_TPP=1 SKIP_E2P_HTML=0 SKIP_GEN_MSG_MAE_ID=1 XRG_CUS=LangPack0000 NO_DEBUG=1

# for Superfast build machine
DZbuild_4:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=16 NUM_THREAD_FOR_TPP=4 PARAL_TPP=1 SKIP_E2P_HTML=0 LINK_CALL_GRAPH=1

# For G1 fast DropZone
DZbuild_G1:
	@echo -n -e "\e[1m\e[34m This mode is for DZ server \e[0m\n" ;
	@$(MAKE) -r -s __fast IBUILD=1 IBUILD_ENHANCE=0 FAST=1 SPEED=1 AUTO_CLEAN=1 NUM_THREAD=48 NUM_THREAD_FOR_TPP=12 PARAL_TPP=1 SKIP_E2P_HTML=1 XRG_CUS=LangPack0000

#
# only execute step1 of library generation (tpp file generation)
#
MAKE_CHECK_FILE=@$(MAKE) -r -s file_checking SPEED=1 AUTO_CLEAN=1 NUM_THREAD=48 NUM_THREAD_FOR_TPP=12 PARAL_TPP=1 FILE_CHECK=1 RELEASE_PROCESS=0

check_file_for_partial_code_P4_account_G1_MSC: .phony
	$(MAKE_CHECK_FILE) QUICK=MSC XRG_CUS=LangPack0000
	-$(CLEAN) $(LIST_MODULE_MAK)

check_file_for_partial_code_P4_account_G1_MSZ: .phony
	$(MAKE_CHECK_FILE) QUICK=MSZ XRG_CUS=LangPack0000
	-$(CLEAN) $(LIST_MODULE_MAK)

#-------------------------------------------------------------------------------
# Partial Make
#-------------------------------------------------------------------------------

LIB_PARTIAL=$(L1) $(L2) $(L3) $(L4) $(L5) $(L6) $(L7) $(L8) $(L9)

# set $(LIB_PARTIAL) = 'NULL'for CTS to per file scanning if $(PER_FILE)=1 
LIB_PARTIAL:=$(if $(filter 1, $(PER_FILE)),, $(LIB_PARTIAL))

Declaration:
	@echo -n -e "\e[1m\e[34mIn this mode, Makefile does not call XRGConsole.exe, CusPack.exe, and LoadConverter.exe.  \e[0m";
	@echo -n -e "\e[1m\e[34mIf user wants to call XRGConsole.exe, user should type in\e[0m  make mmi_cus.  ";
	@echo -n -e "\e[1m\e[34mIf user wants to call CusPack.exe and LoadConverter.exe, user should type in\e[0m make driver_cus. ";
	@echo -n -e "\e[1m\e[34mOtherwise, this build command does not update software version, user should type in\e[0m";
	@echo -n -e " make \e[1m\e[34mor\e[0m make speed \e[1m\e[34mto update software version.  \e[0m";   
	@echo -n -e "\n"

PartialMake: Declaration
	@$(MAKE) -r -s -f $(PRODUCT_MAK) BuildSubLib 'LIB_PARTIAL=$(LIB_PARTIAL)' $(LOG_LINE)
	@echo -n -e "\n"

PartialMake_fast: Declaration
	@$(TNG_MAKE) -rs -f $(PRODUCT_MAK) BuildSubLib_fast \
		IBUILD=1 \
		FAST=1 \
		SPEED=1 \
		IBUILD_ENHANCE=0 \
		"'LIB_PARTIAL=$(LIB_PARTIAL)'" \
		$(LOG_LINE)

release_PartialMake_fast: Declaration
	@$(MAKE) -rs BuildSubLib_fast -f $(RELEASE_MAK)Makefile.res \
		SPEED=1 \
		IBUILD=1 \
		FAST=1 \
		RELEASE_PROCESS=1 \
		IBUILD_ENHANCE=3 \
		QUICK=$(QUICK) \
		AUTO_CLEAN=$(AUTO_CLEAN) \
		LIB_PARTIAL="$(LIB_PARTIAL)"



#-------------------------------------------------------------------------------
# for ABI checking
#-------------------------------------------------------------------------------
abi-so: 
ifeq ($(ABI_VER), )
	@echo -n -e "Please specify the ABI_VER"
else	
	@$(MAKE) -r -s -f $(PRODUCT_MAK) BuildSubLib1 RELEASE_PROCESS=0 SPEED=1 ABI_VER=$(ABI_VER) $(LOG_LINE)
endif

abi-dump: 
ifeq ($(ABI_VER), )
	@echo -n -e "Please specify the ABI_VER"
else	
	@$(TNG)abilibs_dump.sh "$(ABI_VER)" "$(OUT)" "$(CFLAGS)" "$(PATH_H)"
	@echo -n -e "\n"
endif

abi-cc: 
ifeq ($(ABI_BASE), )
	@echo -n -e "Please specify the ABI_BASE and ABI_VER"
else ifeq ($(ABI_VER), )
	@echo -n -e "Please specify the ABI_BASE and ABI_VER"
else	
	@$(TNG)abilibs_cc.sh "$(ABI_BASE)" "$(ABI_VER)"
	@echo -n -e "\n"
endif

	
#-------------------------------------------------------------------------------
# commands to build common libraries, libraries categorized by feature, libraries categorized by chip
#-------------------------------------------------------------------------------
build_common_libs:
	@$(TNG_MAKE) -sr -f $(PRODUCT_MAK) build_common_libs IBUILD=1 FAST=1 SPEED=1 IBUILD_ENHANCE=0 $(LOG_LINE)

build_feature_libs:
	@$(TNG_MAKE) -sr -f $(PRODUCT_MAK) build_feature_libs IBUILD=1 FAST=1 SPEED=1 IBUILD_ENHANCE=0 $(LOG_LINE)

build_bsp_libs:
	@$(TNG_MAKE) -sr -f $(PRODUCT_MAK) build_bsp_libs IBUILD=1 FAST=1 SPEED=1 IBUILD_ENHANCE=0 $(LOG_LINE)

build_chip_libs:
	@$(TNG_MAKE) -sr -f $(PRODUCT_MAK) build_chip_libs IBUILD=1 FAST=1 SPEED=1 IBUILD_ENHANCE=0 $(LOG_LINE)

%.check_3rd:
	$(call do_if_order, \
		$(OUT)$*.lib, \
		$(PATH_common_mak)paths_3rd.mak,\
		$(PRODUCT_SC_3RD:%=$(MAKE) clean_lib TARGET=%;) $(PRODUCT_LIB_3RD:%=$(MAKE) clean_lib TARGET=%;))
	
check_paths_3rd: $(PRODUCT_SC_3RD:%=%.check_3rd)  $(PRODUCT_LIB_3RD:%=%.check_3rd)
	
release_PartialMake: Declaration check_paths_3rd
	@$(MAKE) -r -s release_build \
	NoFinalAndDRVcusMMIcus=1 \
	QUICK=$(QUICK) \
	SPEED=$(SPEED) \
	AUTO_CLEAN=$(AUTO_CLEAN) \
	REL_NUM_THREAD=$(REL_NUM_THREAD) \
	REL_NUM_THREAD_FOR_TPP=$(REL_NUM_THREAD_FOR_TPP) \
	PARAL_TPP=$(PARAL_TPP) \
	\
	'PRODUCT_SC_CUS=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_CUS))' \
	\
	'PRODUCT_SC=$(filter $(LIB_PARTIAL), $(PRODUCT_SC))' \
	'PRODUCT_SC_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_STACK2))' \
	'PRODUCT_SC_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_DRV))' \
	'PRODUCT_SC_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MMI))' \
	'PRODUCT_SC_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_MDL))' \
	'PRODUCT_SC_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_SYS))' \
	'PRODUCT_SC_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_SC_3RD))' \
	\
	'PRODUCT_LIB=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB))' \
	'PRODUCT_LIB_STACK2=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_STACK2))' \
	'PRODUCT_LIB_DRV=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_DRV))' \
	'PRODUCT_LIB_MMI=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MMI))' \
	'PRODUCT_LIB_MDL=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_MDL))' \
	'PRODUCT_LIB_SYS=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_SYS))' \
	'PRODUCT_LIB_3RD=$(filter $(LIB_PARTIAL), $(PRODUCT_LIB_3RD))'

quota_check: LOG_FILE:=$(TOP)quota-check.log

quota_check: 
	$(TNG_MAKE) -f $(PRODUCT_MAK) $@ $(LOG_LINE)
	if grep -q 'start test' $(LOG_FILE) ; then \
		if grep -q 'DZ CHECK QUOTA DONE:FAIL' $(LOG_FILE) ; then \
			echo -ne "\e[1m\e[31mDZ CHECK QUOTA DONE: FAIL\nPlease check $(LOG_FILE) to see the quota-check log\e[0m\n"; \
		else \
			echo -ne "\e[1m\e[32mDZ CHECK QUOTA DONE: PASS\e[0m\n"; \
		fi;\
	else\
		echo -ne "\e[1m\e[31mDZ CHECK QUOTA DONE: FAIL(not start)\nPlease check $(LOG_FILE) to see the quota-check log\e[0m\n";\
	fi;

check_dup_source: 
	$(TNG_MAKE) -f $(PRODUCT_MAK) $@ $(LOG_LINE)
	if grep -q 'is duplicated in' $(LOG_FILE) ; then \
		echo -ne "\e[1m\e[31mDUP SOURCE FOUND\nPlease check $(LOG_FILE) for details\e[0m\n"; \
	else \
		echo -ne "\e[1m\e[32mNO DUP SOURCE\e[0m\n"; \
	fi


#-------------------------------------------------------------------------------
# Help
#-------------------------------------------------------------------------------
help:
	$(MAKE) -f $(MAKE_HELP_COMMON);
	if [ -e $(MAKE_HELP_NORMAL) ]; then \
		$(MAKE) -f $(MAKE_HELP_NORMAL);\
    fi
	if [ ! -e $(MAKE_HELP_NORMAL) ]; then \
		$(MAKE) -f $(MAKE_HELP_RELEASE);\
    fi
# DO NOT DELETE
