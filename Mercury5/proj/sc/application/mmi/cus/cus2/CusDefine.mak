#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
    mmi_cus_clsrv.c

MMI_PATH_H += \
	$(PATH_mae)/inc \
	$(PATH_mae)/pub \
	$(PATH_srv)/inc \
	$(PATH_srv)/pub \
	$(PATH_ResMgr)/inc \
	$(PATH_ResMgr)/inc/ABL \
	$(PATH_ResMgr)/inc/DataStruct \
    $(PATH_mmmanager)/pub \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager_lib)/pub \
    $(PATH_mmmanager_lib)/inc \
	$(PATH_ResMgr)/inc/DBL \
	$(PATH_ResMgr)/inc/HAL \
	$(PATH_ResMgr)/inc/MediaCmd \
	$(PATH_ResMgr)/inc/ResMgr \
	$(PATH_ResMgr)/inc/Util \
	$(PATH_ResMgr)/pub \
	$(PATH_rtk)/inc \
	$(PATH_rtk)/pub\
	$(PATH_rtk)/itf \
	$(PATH_rtk)/itf_open\
	$(PATH_mmicomn)/inc \
	$(PATH_mmicomn)/res \
	$(PATH_mmicomn)/cfg \
	$(PATH_image_codec)/inc \
	$(PATH_image_codec)/pub \
	$(PATH_model)/inc \
    $(PATH_model)/pub \
	$(PATH_sys)/itf_open \
	$(PATH_sys)/pub \
	$(PATH_SrvWrapper)/pub \
	$(PATH_AppLauncher)/inc \
	$(PATH_utility)/inc \
	$(PATH_widget)/inc \
	$(PATH_widget)/inc/priv\
	$(PATH_widget)/pub \
	$(PATH_build) \
	$(PATH_CusDefine)/pub

PATH_C =\
	$(PATH_CusDefine)/src
