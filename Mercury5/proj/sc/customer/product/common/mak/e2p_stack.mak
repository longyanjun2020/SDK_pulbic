E2P_TO_DWL += hw_default.e2p\
              audioparam.e2p

E2P_TO_DWL += $(foreach n, $(RF_E2P), $(n))

ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
VALUES_E2P_LIST = stack_nand.e2p.val
else
VALUES_E2P_LIST = stack_nor.e2p.val
endif

STRUCT_HDR_LIST = e2p_cust.ho
STRUCT_SRC_NAME = __e2p__stack__.c

GENE2P_E2P_FILE=stack.e2p
GENE2P_DWL_FILE=stack.dwl
GENE2P_HEADER=e2p_stack.h
GENE2P_CSN=e2p_csn_stack.csn
GENE2P_OFFSET=0x00000000
GENE2P_LEVEL=level2
GENE2P_TOP=Eeprom_t
GENE2P_OMMI=-ommi
GENE2P_MASK=0x00000000

