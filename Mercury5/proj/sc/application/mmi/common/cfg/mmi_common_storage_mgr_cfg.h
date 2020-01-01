/**
 * @file    mmi_common_storage_mgr_cfg.h
 *
 * @brief   This file is auto generate by XRG tool. Do not modify file directly
 *
 * @version $Id:$
 *
 * @time
 */

#ifndef __MMI_COMMON_STORAGE_MGR_CFG__H__
#define __MMI_COMMON_STORAGE_MGR_CFG__H__


#include "mdl_vfs_struct.h"
enum
{
    STORAGE_AUTO_SWITCH_OFF=0,
    STORAGE_AUTO_SWITCH_ON=1
};
typedef u32 StorageSelectRule_e;
enum
{
    STORAGE_CARD=0,
    STORAGE_CARD2 =1,
    STORAGE_PHONE=2
};
typedef u8 StorageType_e;
typedef struct _StorageCfg_t
{
    StorageType_e eSelectedStorage;
} StorageCfg_t ;
typedef struct _StorageMgrCfg_t
{
    StorageSelectRule_e eStorageSelectRule;
} StorageMgrCfg_t;

// Allow Mater Reset
#if defined(__ONBOARD_USER_STORAGE_MMI__)
#define CONFIG_AMR_STORAGE_CAM_PIC          CONFIG_DEFINE(CFGIT_CAMERA_STORAGE_PIC_CONFIG,      StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_CAM_VDO          CONFIG_DEFINE(CFGIT_CAMERA_STORAGE_VDO_CONFIG,      StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_SUBCAM_PIC       CONFIG_DEFINE(CFGIT_SUBCAMERA_STORAGE_PIC_CONFIG,   StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_SUBCAM_VDO       CONFIG_DEFINE(CFGIT_SUBCAMERA_STORAGE_VDO_CONFIG,   StorageCfg_t,       1,  {STORAGE_CARD} )
#ifdef __NAND_MMI__
#define CONFIG_AMR_STORAGE_MMS              CONFIG_DEFINE(CFGIT_MMS_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_PHONE} )
#else
#define CONFIG_AMR_STORAGE_MMS              CONFIG_DEFINE(CFGIT_MMS_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )
#endif

#ifdef __APP_MMI_VOICE_MEMO__
#define CONFIG_AMR_STORAGE_VM               CONFIG_DEFINE(CFGIT_VOICEMEMO_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_CARD} )
#else
#define CONFIG_AMR_STORAGE_VM
#endif

#if defined(__ATV_MMI__) && !defined(__APP_MMI_SMALLROM__)
#define CONFIG_AMR_STORAGE_ATV              CONFIG_DEFINE(CFGIT_ATV_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )
#else //__ATV_MMI__ && !__APP_MMI_SMALLROM__
#define CONFIG_AMR_STORAGE_ATV
#endif //__ATV_MMI__ && !__APP_MMI_SMALLROM__

#ifdef __WAP_MMI_CDWAP__
#define CONFIG_AMR_STORAGE_WAP              CONFIG_DEFINE(CFGIT_WAP_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_PHONE} )
#else
#define CONFIG_AMR_STORAGE_WAP
#endif

#ifdef __MMI_KING_MOVIE__
#define CONFIG_AMR_STORAGE_KMV              CONFIG_DEFINE(CFGIT_KMV_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_PHONE} )
#else
#define CONFIG_AMR_STORAGE_KMV
#endif

#define CONFIG_AMR_STORAGE_PICVIWER         CONFIG_DEFINE(CFGIT_PICVIEWER_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_PHONE} )
#define CONFIG_AMR_WALLPAPER_STORAGE_CONFIG CONFIG_DEFINE(CFGIT_WALLPAPER_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_PHONE} )
#define CONFIG_AMR_STORAGE_FM               CONFIG_DEFINE(CFGIT_FM_STORAGE_CONFIG,              StorageCfg_t,       1,  {STORAGE_PHONE} )
#define CONFIG_AMR_STORAGE_MANAGER          CONFIG_DEFINE(CFGIT_STORAGE_MANAGER_CONFIG,         StorageMgrCfg_t,    1,  {STORAGE_AUTO_SWITCH_ON} )

#ifdef __APP_MMI_TUDOU__
#define CONFIG_AMR_TUDOU_STORAGE                   CONFIG_DEFINE(CFGIT_TUDOU_STORAGE_CONFIG, StorageCfg_t, 1, {STORAGE_CARD} )
#else
#define CONFIG_AMR_TUDOU_STORAGE
#endif

#else //__ONBOARD_USER_STORAGE_MMI__
#define CONFIG_AMR_STORAGE_CAM_PIC          CONFIG_DEFINE(CFGIT_CAMERA_STORAGE_PIC_CONFIG,      StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_CAM_VDO          CONFIG_DEFINE(CFGIT_CAMERA_STORAGE_VDO_CONFIG,      StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_SUBCAM_PIC       CONFIG_DEFINE(CFGIT_SUBCAMERA_STORAGE_PIC_CONFIG,   StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_SUBCAM_VDO       CONFIG_DEFINE(CFGIT_SUBCAMERA_STORAGE_VDO_CONFIG,   StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_MMS              CONFIG_DEFINE(CFGIT_MMS_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )

#ifdef __APP_MMI_VOICE_MEMO__
#define CONFIG_AMR_STORAGE_VM               CONFIG_DEFINE(CFGIT_VOICEMEMO_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_CARD} )
#else
#define CONFIG_AMR_STORAGE_VM
#endif

#if defined(__ATV_MMI__) && !defined(__APP_MMI_SMALLROM__)
#define CONFIG_AMR_STORAGE_ATV              CONFIG_DEFINE(CFGIT_ATV_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )
#else //__ATV_MMI__ && !__APP_MMI_SMALLROM__
#define CONFIG_AMR_STORAGE_ATV
#endif //__ATV_MMI__ && !__APP_MMI_SMALLROM__

#ifdef __WAP_MMI_CDWAP__
#define CONFIG_AMR_STORAGE_WAP              CONFIG_DEFINE(CFGIT_WAP_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )
#else
#define CONFIG_AMR_STORAGE_WAP
#endif

#ifdef __MMI_KING_MOVIE__
#define CONFIG_AMR_STORAGE_KMV              CONFIG_DEFINE(CFGIT_KMV_STORAGE_CONFIG,             StorageCfg_t,       1,  {STORAGE_CARD} )
#else
#define CONFIG_AMR_STORAGE_KMV
#endif

#define CONFIG_AMR_STORAGE_PICVIWER         CONFIG_DEFINE(CFGIT_PICVIEWER_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_WALLPAPER_STORAGE_CONFIG CONFIG_DEFINE(CFGIT_WALLPAPER_STORAGE_CONFIG,       StorageCfg_t,       1,  {STORAGE_CARD} )
#define CONFIG_AMR_STORAGE_FM               CONFIG_DEFINE(CFGIT_FM_STORAGE_CONFIG,              StorageCfg_t,       1,  {STORAGE_PHONE} )
#define CONFIG_AMR_STORAGE_MANAGER          CONFIG_DEFINE(CFGIT_STORAGE_MANAGER_CONFIG,         StorageMgrCfg_t,    1,  {STORAGE_AUTO_SWITCH_ON} )
#ifdef __APP_MMI_TUDOU__
#define CONFIG_AMR_TUDOU_STORAGE                   CONFIG_DEFINE(CFGIT_TUDOU_STORAGE_CONFIG, StorageCfg_t, 1, {STORAGE_CARD} )
#else
#define CONFIG_AMR_TUDOU_STORAGE
#endif
#endif //__ONBOARD_USER_STORAGE_MMI__

#define CONFIG_AMR_STORAGE_VDO  CONFIG_DEFINE(CFGIT_VDO_STORAGE_CONFIG, StorageCfg_t,    1,      {STORAGE_CARD} )

#define STORAGE_MGR_AMR_ALL_CONFIG \
                        CONFIG_AMR_STORAGE_CAM_PIC \
                        CONFIG_AMR_STORAGE_CAM_VDO \
                        CONFIG_AMR_STORAGE_SUBCAM_PIC \
                        CONFIG_AMR_STORAGE_SUBCAM_VDO \
                        CONFIG_AMR_STORAGE_MMS \
                        CONFIG_AMR_STORAGE_VM \
                        CONFIG_AMR_STORAGE_PICVIWER \
                        CONFIG_AMR_STORAGE_ATV \
                        CONFIG_AMR_STORAGE_WAP \
                        CONFIG_AMR_STORAGE_KMV \
                        CONFIG_AMR_WALLPAPER_STORAGE_CONFIG \
                        CONFIG_AMR_STORAGE_FM \
                        CONFIG_AMR_STORAGE_VDO \
                        CONFIG_AMR_TUDOU_STORAGE \
                        CONFIG_AMR_STORAGE_MANAGER

#endif /* __MMI_COMMON_STORAGE_MGR_CFG__H__ */
