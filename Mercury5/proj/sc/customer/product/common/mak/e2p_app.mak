# David Chang 2007.02.27 */
ifeq ($(filter __APP_E2P_MML__ ,$(PP_OPT_COMMON)),__APP_E2P_MML__)
VALUES_E2P_LIST = \
           app_mmi.e2p.val \
           app_mml.e2p.val
else
VALUES_E2P_LIST = \
           app_mmi.e2p.val
endif



STRUCT_HDR_LIST = vm_e2p_app.ho
STRUCT_SRC_NAME = __e2p__app__.c

GENE2P_E2P_FILE=app.e2p
GENE2P_DWL_FILE=app.dwl
GENE2P_HEADER=e2p_app.h
GENE2P_CSN=e2p_csn_app.csn

ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)),__NAND__)
GENE2P_OFFSET=0x00006000
else
GENE2P_OFFSET=0x00001E80
endif

GENE2P_LEVEL=level1
GENE2P_TOP=E2pAppl_t
GENE2P_OMMI=-ommi
GENE2P_MASK=0x00000000
