PATH_H = \
    $(PATH_dynldr)/pub \
    $(PATH_fc)/pub \
    $(PATH_fms)/pub \
    $(PATH_mserv)/inc \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_tencentmcare)/inc\
    $(PATH_mae)/pub\
    $(PATH_core)/pub\
    $(PATH_trc)/pub\
    $(PATH_rtk)/pub\
    $(PATH_drv)/timer/pub\
    $(PATH_mmicomn)/inc\
    $(PATH_sys)/pub

MMI_PATH_H =

PROCESS		= lib

PATH_C +=\
	$(PATH_tencentmcare)/src
PATH_H +=\
		$(PATH_tencentmcare)/inc
PATH_EXT_LIB +=\
	$(PATH_tencentmcare)/lib

ifeq (RVCTV22,$(COMPILER_VERSION))
C_OPTIONS += --diag_suppress 1,177,494,550,1295
endif

#PORTING
REL_SRC_C_LIST += TencentMcare_app.c
REL_SRC_C_LIST += adaptVendor.c
