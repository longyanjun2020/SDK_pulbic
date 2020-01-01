#---------------------------------------------------------------------------------------------------
#	Generate cust's file list specified in seperate options.mak
#
#   [Parameters]
#       PATH   : The product path where file will copy to.
#       TARGET : The target product name.
#
#   [Example]
#       make -f GenCustFileList.mak PATH=sc/customer/product/8533n_512_256_3301/make TARGET=8533n_512_256_3301
#----------------------------------------------------------------------------------------------------

BIN         := /usr/bin
RM          := $(BIN)/rm
REL_SRC     := REL_SRC_C_LIST
REL_LIB     := SRC_C_LIST
REL_METHOD  := $(REL_SRC)
REL_FOLDER	:= sc/customer/product/cust/
RELEASE_MAK := $(TARGET:options%=release%)
Destination	:= CustReleaseFiles_$(TARGET:options_%.mak=%).txt
HEADER_LIST := sc/customer/product/common/mak/paths.mak \
			   sc/customer/product/cust/drv/cust_drv.mak \
			   sc/customer/product/cust/drv/cust_drv_dummy.mak \
               sc/customer/product/cust/sys/cust_sys.mak \
               sc/customer/product/cust/mmi/cust_mmi.mak             

SEARCH_COMPILER_OPTION=$(firstword $(filter $(1),$(PP_OPT_COMMON)) \
                                   $(filter $(1),$(PP_OPT_TARGET)) \
                                   $(filter $(1),$(PP_OPT_DUO)))
FIND_COMPILER_OPTION=$(if $(call SEARCH_COMPILER_OPTION,$(1)),TRUE,FALSE)

PP_OPT_COMMON = $(CHIP_TYPE) __COMPONENT_BASE_CONFIGURATION__

include $(PATH)/$(TARGET)
-include $(HEADER_LIST)



DISP_PATH_SRC := $(addprefix $(PATH_customer_product_disptbl)/,$(DISP_CUS_SRC))
DISP_PATH_SRC += $(wildcard $(PATH_customer_product_disptbl)/DT_DEFAULT_*.dat)
DISP_PATH_SRC += $(wildcard $(PATH_customer_product_disptbl)$(DISP_CUS_FOLDER)/DT_*.dat)



CUST_RELEASE_LIST := $(CUS_DRV_SRC_LIST) \
                     $(CUS_SYS_SRC_LIST) \
                     $(CUS_EM_SRC_LIST) \
                     $(CUS_DRV_DUMMY_SRC_LIST) \
                     $(SAVE_DATABSE)



CUST_SAVE_LIST := $(PATH_product_cust)e2p/audioparam_$(strip $(MAKE_AUD_E2P)).e2p \
										 $(PATH_product_cust)e2p/audioparam_default.e2p \
                     $(PATH_product_cust)e2p/cusSetting_$(strip $(MAKE_CUS_E2P)).e2p.val \
                     $(DISP_PATH_SRC) \
                     


ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
COMPONENT_BASE := "TRUE"
else
COMPONENT_BASE := "FALSE"
endif

all:
	echo "[$(TARGET:options_%.mak=%)]";
	if [ -f $(PATH)/$(TARGET) ] ; then\
	    $(RM) -rf $(REL_FOLDER)/$(RELEASE_MAK); \
	    echo "$(REL_METHOD) =\ " >> "$(REL_FOLDER)/$(RELEASE_MAK)"; \
	    for INDEX in $(CUST_RELEASE_LIST); do \
	        echo "    $$INDEX ==> $(REL_FOLDER)/$(RELEASE_MAK)";\
	        echo "    $$INDEX \\ " >> "$(REL_FOLDER)/$(RELEASE_MAK)"; \
	    done;\
		echo "" >> "$(REL_FOLDER)/$(RELEASE_MAK)";\
	else\
	    echo "    PASS (Product Base)";\
	fi
	
	
	echo "[$(TARGET:options_%.mak=%) non-c files]";
	if [ -f $(PATH)/$(TARGET) ] ; then\
	    $(RM) -rf $(REL_FOLDER)/$(Destination); \
	    for INDEX in $(CUST_SAVE_LIST); do \
	        echo "    $$INDEX ==> $(REL_FOLDER)/$(Destination)";\
	        echo "copy ./../$$INDEX" >> "$(REL_FOLDER)/$(Destination)"; \
	    done;\
		echo "" >> "$(REL_FOLDER)/$(Destination)";\
	else\
	    echo "    PASS (Product Base)";\
	fi
	
	# Create saveLCMBase.txt, for duplicate file name issue.
	echo "$(LCD_BASE)" >> "$(REL_FOLDER)/saveLCMBase.txt";
	echo "allinone_base" >> "$(REL_FOLDER)/saveLCMBase.txt";
	echo "global_base" >> "$(REL_FOLDER)/saveLCMBase.txt";


.PHONY: clean
clean:
	echo "[$(TARGET:options_%.mak=%)]";
	if [ -f $(REL_FOLDER)/$(RELEASE_MAK) ]; then\
	    echo "    Delete $(FILELIST)";\
	    $(RM) -rf $(REL_FOLDER)/$(RELEASE_MAK); \
	    $(RM) -rf $(REL_FOLDER)/$(Destination); \
	    $(RM) -rf $(REL_FOLDER)/saveLCMBase.txt; \
	else \
	    echo "    $(FILELIST) no exist"; \
	fi


