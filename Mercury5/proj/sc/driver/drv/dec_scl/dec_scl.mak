#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
          $(PATH_dec_scl)/src
ifeq ($(call FIND_COMPILER_OPTION, __BUILD_DEC_SCL_PQ_), TRUE)          
PATH_C += $(PATH_dec_scl)/src/pq
endif

PATH_H+=            $(PATH_dec_scl_hal)/inc\
                    $(PATH_dec_scl)/inc\
                    $(PATH_dec_scl)/pub\
                    $(PATH_dec_scl_hal)/pub\
                    $(PATH_project_Dvr_CarDV_SDK_cfg_pq)/inc
ifeq ($(call FIND_COMPILER_OPTION, __BUILD_DEC_SCL_PQ_), TRUE)          
PATH_H+=            $(PATH_scl)/src/pq\
                    $(PATH_scl)/inc/pq\
                    $(PATH_dec_scl_hal)/inc/pq
endif          

SRC_C_LIST+=        drv_dec_scl_hvsp.c\
                    dec_scl_test.c
ifeq ($(call FIND_COMPILER_OPTION, __BUILD_DEC_SCL_HVSP_IO_), TRUE)    
SRC_C_LIST+=        drv_dec_scl_hvsp_m.c\
                    drv_dec_scl_hvsp_io.c 
endif
ifeq ($(call FIND_COMPILER_OPTION, __BUILD_DEC_SCL_PQ_), TRUE)
SRC_C_LIST+=        drv_dec_scl_pq_bin.c\
                    drv_dec_scl_pq.c
endif

#------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __BUILD_DEC_SCL_TEST_), TRUE)
SRC_C_LIST+=		dec_scl_test
endif

