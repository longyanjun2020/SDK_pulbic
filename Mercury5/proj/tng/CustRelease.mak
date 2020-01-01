#---------------------------------------------------------------------------------------------------
#	Generate file list of customer's source for release script used
#
#   [Example]
#       make -f CustRelease.mak
#       make -f CustRelease.mak clean
#----------------------------------------------------------------------------------------------------

WARN := @
PATH_ROOT    := ./
PATH_PRODUCT := $(PATH_ROOT)mak
PATH_GENTOOL := tng/GenCustMak.mak
EXCEP_FILES  := options_i_sw_os_b3.mak
EXCEP_LIST   := $(EXCEP_FILES:%=$(PATH_PRODUCT)/%)
PRODUCT_FILE := $(filter-out $(EXCEP_LIST),$(wildcard $(PATH_PRODUCT)/options_*))
PRODUCT_LIST := $(PRODUCT_FILE:$(PATH_PRODUCT)/%=%)

all:
	make gen_lcd_update
	$(WARN) for PREFIX in $(PRODUCT_LIST);do\
			make -s -f "$(PATH_GENTOOL)"\
			            PATH="$(PATH_PRODUCT)"\
			            TARGET=$$PREFIX;\
	done;


.PHONY: clean
clean:
	$(WARN) for PREFIX in $(PRODUCT_LIST);do\
	    if [ -f $(PATH_PRODUCT)/$$PREFIX ]; then\
	        make -s -f "$(PATH_GENTOOL)" PATH="$(PATH_PRODUCT)" TARGET=$$PREFIX clean;\
	    fi;\
	done;

