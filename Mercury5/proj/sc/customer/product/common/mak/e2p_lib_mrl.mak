
ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)

VALUES_E2P_LIST = middleware_nand.e2p.val\
                  middleware_2_nand.e2p.val\
                  middleware_cus_mrl_nand.e2p.val\

GENE2P_OFFSET=0x00005800

else

VALUES_E2P_LIST = middleware_nor.e2p.val\
                  middleware_2_nor.e2p.val\
                  middleware_cus_mrl_nor.e2p.val\

GENE2P_OFFSET=0x000019D0

endif

STRUCT_HDR_LIST = vm_e2p_lib.ho
STRUCT_SRC_NAME = __e2p__lib__.c

GENE2P_E2P_FILE=lib.e2p
GENE2P_DWL_FILE=lib.dwl
GENE2P_HEADER=e2p_lib.h
GENE2P_CSN=e2p_csn_lib.csn
GENE2P_LEVEL=level1
GENE2P_TOP=E2pLib_t
GENE2P_OMMI=-ommi
GENE2P_MASK=0x00000000

