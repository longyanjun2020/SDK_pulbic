# ****************************************************************************
# *  File    : $Workfile:   $       $Revision:  $
# *--------------------------------------------------------------------------*
# *  Scope   :   Description of the library to generate                     *
# *                                                                          *
# *                                                                          *
# ****************************************************************************




#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib

PP_OPT_FMS_DEF    = __NEW_NOR_ARCH__

PP_OPT_FMS_UNDEF  = __NAND__
PP_OPT_FMS_UNDEF += __FMS_E2P_NAND_MIRROR__
PP_OPT_FMS_UNDEF += __CUS_DYNAMIC_LOAD_DRV__
PP_OPT_FMS_UNDEF += USE_GET_NRAI_INFO

PP_OPT_COMMON := $(filter-out $(PP_OPT_FMS_UNDEF), $(PP_OPT_COMMON))
PP_OPT_COMMON += $(PP_OPT_FMS_DEF)

PATH_H +=\
  $(PATH_emi)/pub\
  $(PATH_flash)/pub\
  $(PATH_flash)/inc\
  $(PATH_rai)/pub\
  $(PATH_fms)/itf\
  $(PATH_fms)/inc\
  $(PATH_fms)/itf_open\
  $(PATH_acc_inc)/pub

PATH_C +=\
  $(PATH_fms)/src\
  $(PATH_fms)/opxc

C_E2P_OBJS = opec_e2p.o fms_e2p_mirror_nor.o

ifeq ($(COMPILER_VERSION),RVCTV22)
$(C_E2P_OBJS:%=$(OUT)%): C_OPTIONS += --diag_suppress 1296,170
endif

#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =\
  abi_headers_fms.c\
  fms_map_nor.c\
  fms_core.c\
  fms_core_bsp.c\
  fms_core_detect.c\
  fms_panic.c\
  fms_bin.c\
  fms_flat.c\
  fms_flat_ctx.c\
  fms_flat_repack.c\
  fms_e2p_init.c\
  fms_e2p_main.c\
  fms_e2p_mirror_nor.c\
  fms_e2p_sector.c\
  fms_e2p_cache.c\
  fms_ad_nor.c\
  fms_trace.c\
  fms_rai_hash_nor.c\
  fms_rai_items_nor.c\
  fms_map_common.c\
  fms_core_util.c\
  fms_cus.c\
  opec_e2p.c\
  opec_rai.c\
  opec_ad.c\
  opec_bin.c\
  fms_rai_m18.c\
  fms_trc_m18.c

SRC_C_LIST +=\
  fms_rai_store_nor.c\
  fms_e2p_itf_nor.c

ifeq ($(COMPILER_VERSION),RVCTV22)
SRC_ASM_LIST = fms_flat_util.asm
endif

#SRC_C_LIST +=\
#  fms_e2p_on_rai.c\
#  fms_cali.c\
#  fms_perf1.c

#ifeq ($(COMPILER_VERSION),RVCTV22)
#SRC_ASM_LIST +=\
#  read_seq.asm\
#  read_nonseq.asm\
#  write_seq.asm\
#  write_nonseq.asm
#endif
