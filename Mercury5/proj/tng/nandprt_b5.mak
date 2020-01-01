
TARGET=nandprt

include $(CONFIG_MAK)
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
include $(PATH_cust_nandprt)/nand_conf_b3.mak
else
include $(PATH_sc)customer/product/$(PRODUCT)/mak/nand_conf.mak
endif

NAND_CONF_DIR=$(COMMON_NAND_DIR)/nand_conf/

cpimg:
ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)

#1. pni
	cp $(PATH_cust_nandprt)PARTITION_v2_$(strip $(PARTITION_V2_PNI)).pni  $(OUT)PARTITION_v2.pni

#2. nni
	$(COPY) -f $(PATH_cust_nandprt)nand_partition.ini            $(OUT)nand_partition.ini;
	unix2dos --unix2dos $(OUT)nand_partition.ini

#3. nni
	$(COPY) -f $(PATH_cust_nandprt)NANDINFO_v2.nni           $(OUT)NANDINFO_v2.nni;

else  ### ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)

#1. pni
	@if [ -e $(NAND_DIR)PARTITION_v2.pni ];then\
		echo "using $(NAND_DIR)/PARTITION_v2.pni";\
		cp $(NAND_DIR)PARTITION_v2.pni $(OUT);\
	else\
		echo "using $(NAND_CONF_DIR)PARTITION_v2.pni";\
		cp $(NAND_CONF_DIR)PARTITION_v2.pni $(OUT);\
	fi;

#2. ini
	if [ -e $(NAND_DIR)nand_partition.ini ];then\
		echo "using $(NAND_DIR)/nand_partition.ini";\
		cp $(NAND_DIR)nand_partition.ini $(OUT);\
	else\
		echo "using $(NAND_CONF_DIR)nand_partition.ini";\
		cp $(NAND_CONF_DIR)nand_partition.ini $(OUT);\
	fi;

#3. nni
	unix2dos --unix2dos $(OUT)/nand_partition.ini
#	cp $(COMMON_NAND_DIR)*.* $(OUT)
	cp $(NAND_DIR)NANDINFO_v2.nni $(OUT)

endif
	
mkimg:
ifeq ($(call FIND_COMPILER_OPTION, __IMAGE_COMPRESSION__), TRUE)
	echo -ne "TARGET_BINARY_INFO:"`wc -c $(NAND_BIN_HOSTRUNTIME)|cut -f1 -d' '` `date +"%m%d%y %H:%M"`"      \000" >> $(NAND_BIN_HOSTRUNTIME)
	$(NAND_MKCOM) -s$(NAND_COM_BLOCK_SIZE) -f$(NAND_BIN_HOSTRUNTIME) -o$(NAND_BIN_HOSTRUNTIMECOMP)
	$(NAND_MKIMG) -a $(NAND_SDRAM_ADDR) -n $(NAND_IMGTYPE_NAME_MMPCOM) -t $(NAND_IMGTYPE_HOSTRUNTIME) $(NAND_BIN_HOSTRUNTIMECOMP)
else
	echo -ne "TARGET_BINARY_INFO:"`wc -c $(NAND_BIN_HOSTRUNTIME)|cut -f1 -d' '` `date +"%m%d%y %H:%M"`"      \000" >> $(NAND_BIN_HOSTRUNTIME)
	$(NAND_MKIMG) -a $(NAND_SDRAM_ADDR) -n $(NAND_IMGTYPE_HOSTRUNTIME) -t $(NAND_IMGTYPE_HOSTRUNTIME) $(NAND_BIN_HOSTRUNTIME)

endif
mkptbl:
	$(NAND_MKPTB) -c $(NAND_INI_PTABLE) -o $(NAND_PTB_PTABLE)

mkprt:
ifeq ($(call FIND_COMPILER_OPTION, __IMAGE_COMPRESSION__), TRUE)
	$(NAND_MKPRT) -i $(NAND_IMG_HOSTRUNTIMECOMP) $(NAND_PRT)
else
	$(NAND_MKPRT) -i $(NAND_IMG_HOSTRUNTIME) $(NAND_PRT)
endif
	if [ $$(($$(ls -g $(NAND_PRT) | awk '{print $$4}')+0)) -ge $$(($(NAND_PRT_SIZE)+0)) ]; then \
        echo NAND Image PRT file size exceeded!!!; \
        exit 1; \
    fi
