#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

NO_PLATFORM_INCLUDE = yes

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# for core
SRC_C_LIST = \
	fw_file.c\
	fw_porting.c\
	fw_long64.c\
	fw_mm.c\
	fw_profiling.c\
	fw_unicode.c\
	fw_arena.c\
	fw_degree.c\
	fw_dist.c\
  fw_permstr.c\
	fw_pool.c\
	fw_hash.c\
	fw_filePath.c\
	fw_bbox.c\
	fw_time.c\
	fw_util.c\
	fw_timer.c\
	db_rdgeoAPI.c\
	db_rdgeoDecoder.c\
  db_rdgeoFileCache.c\
  db_rdgeoGrid.c\
  db_rdgeoNameCache.c\
  db_poi.c\
  db_district.c\
	rm_IniReader.c\
	rm_UserSetting.c

# for internet
SRC_C_LIST +=\
  srv_api.c

MMI_PATH_H += \
	$(PATH_mae)/inc \
		$(PATH_mae)/pub \
	$(PATH_mmi_res)/resourceLib \
	$(PATH_widget)/inc \
	$(PATH_widget)/inc/priv \
	$(PATH_mmicomn)/inc \
	$(PATH_srv)/inc \
	$(PATH_srv)/pub \
	$(PATH_ril_itf)\
 	$(PATH_acc_inc)/itf\
 	$(PATH_acc_inc)/itf_open\
	$(PATH_esl)/pub\
 	$(PATH_vfs)/itf\
 	$(PATH_vfs)/pub\
 	$(PATH_vfs)/inc\
 	$(PATH_fat)/itf\
 	$(PATH_fat)/pub\
 	$(PATH_rtk)/itf\
 	$(PATH_rtk)/itf_open\
 	$(PATH_rtk)/inc\
 	$(PATH_rtk)/pub\
 	$(PATH_fc)/pub\
 	$(PATH_kernel_hal)/inc \
 	$(PATH_sys)/itf_open\
 	$(PATH_sys)/itf\
	$(PATH_sys)/pub\
 	$(PATH_trc)/inc\
 	$(PATH_trc)/pub\
 	$(PATH_audio)/itf_open\
 	$(PATH_fms)/itf_open\
 	$(PATH_fc)/pub\
 	$(PATH_fms)/inc/\
 	$(PATH_map)/core/exFramework/fwBase/inc\
 	$(PATH_map)/core/exFramework/fwUtil/inc\
 	$(PATH_map)/core/exFramework/fwTimer/inc\
	$(PATH_map)/core/exDb/mapDb/inc\
	$(PATH_map)/core/exDb/mapPOI/inc\
	$(PATH_map)/core/exDB/mapDistrict/inc\
	$(PATH_map)/core/exResourceMgr/rmUserSetting/inc\
	$(PATH_map)/core/exResourceMgr/rmIniReader/inc\
	$(PATH_cus_app)/inc\
	$(PATH_MsWrapper)/pub \
	$(PATH_timer)/pub \
	$(PATH_timer_hal)/pub \
	$(PATH_int_hal)/inc \

# for internet
MMI_PATH_H += \
  $(PATH_sdk)/inc\
	$(PATH_mserv)/inc\
	$(PATH_map)/core/exServ/inc

PATH_C =\
	$(PATH_map)/core/exFramework/fwBase/src\
	$(PATH_map)/core/exFramework/fwUtil/src\
	$(PATH_map)/core/exFramework/fwTimer/src\
	$(PATH_map)/core/exDb/mapDb/src\
	$(PATH_map)/core/exDb/mapPOI/src\
	$(PATH_map)/core/exDb/mapDistrict/src\
	$(PATH_map)/core/exServ/src\
	$(PATH_map)/core/exResourceMgr/rmUserSetting/src\
	$(PATH_map)/core/exResourceMgr/rmIniReader/src\


